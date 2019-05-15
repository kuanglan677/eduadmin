#include "eduadmin.h"
#include "window.h"
#include "ui_window.h"
#include "gradedata.h"
#include "sqlite.h"
#include <QStringListModel>
#include <QStandardItem>
#include <QSqlTableModel>
#include <QStandardItemModel>

#include <QSqlQueryModel>
#include <QModelIndex>
#include <QCheckBox>

#include <QDebug>

//#include <QItemDelegate>
//class CheckBox:public QItemDelegate{
//    Q_OBJECT
//public:
//    CheckBox();
//    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
//private:
//    QPushButton *select;
//};
//CheckBox::CheckBox(){}
//void CheckBox::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const{
//    select->show();

//}


EduAdmin::EduAdmin(QWidget *parent)
    : QWidget(parent),_window(new Window(this,this)),_gradaData(new GradeData),_sqlite(new Sqlite)
{
    //初始化课程表
    initSqlite();
    showAllCourse();//展示课程
    showAllCurrentSemesterCourse();
}

EduAdmin::~EduAdmin()
{
}
//=========================================================================
// 数据库相关函数
//=========================================================================
void EduAdmin::initSqlite(){
    if(!_sqlite->createDatabase("eduadmin")){}
    if(!_sqlite->createTables({"CourseTable",
                              "CourseName","varchar(20)",
                              "Semester","varchar(20)" ,
                              "TeacherName","varchar(20)", "Capacity","varchar(5)"})){
        /*
         * 错误检测
         */
    }

}

//=========================================================================
// 界面相关函数
//=========================================================================
//课程管理界面
bool EduAdmin::addCourse(QString semester,QString courseName,QString teacherName,QString capacity){
    QString query = tr("insert into CourseTable values('%1','%2','%3','%4')").arg(courseName,semester,teacherName,capacity);
    if(!_sqlite->execQuery(query)){
        /*
         * 错误检测
         */
        return false;
    }
    return true;
}//添加新的课程
bool EduAdmin::deleteCourse(const QString& courseName){
    QString query;
    query = tr("delete from CourseTable where CourseName = '%1'").arg(courseName);
    if(_sqlite->execQuery(query)){
        return true;
    }else{
        /*
         * 纠错机制
         */
        return false;
    }
}//删除课程
void EduAdmin::showAllCourse(){
    QSqlQueryModel *model = new QSqlQueryModel;
    _sqlite->execInquiryAll("CourseTable",model);

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CourseName"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Semester"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("TeacherName"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Capacity"));



    _window->ui->tableView_allCourse->setModel(model);
    _window->ui->tableView_allCourse->verticalHeader()->hide();

}//展示所有课程
bool EduAdmin::updateCourseInfo(const QString& oldName,const QString& newCourseName,const QString& newSemester,const QString& newTeacherName,const QString& newCapasity){
    if(!_sqlite->updateCourseInfo(oldName,newCourseName,newSemester,newTeacherName,newCapasity)){
        return false;
    }
    return true;
}//更改课程信息

//学生选课界面
void EduAdmin::showAllCurrentSemesterCourse(){
    QSqlQueryModel *model = new QSqlQueryModel;
    _sqlite->selectSemesterCourse("第一学期",model);


    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CourseName"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TeacherName"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Capacity"));
    model->insertColumn(3);
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Selected"));

    _window->ui->tableView_selectCourse->setModel(model);

    for(int i=0;i<model->rowCount();++i){
        QCheckBox *ch = new QCheckBox;
//        ch->setText("选择");//不会显示
        ch->setCheckable(false);//设置不可编辑
        ch->setEnabled(true);//设置可选
        _window->ui->tableView_selectCourse->setIndexWidget(model->index(i,3),new QCheckBox(this));
    }

    _window->ui->tableView_selectCourse->verticalHeader()->hide();
}//显示当前学期课程

void EduAdmin::addRecord(){
    //    QString fileName = _window->getOpenFileName();
    //    QStringList strList = _gradaData->openSource(fileName);
    //    QStandardItemModel *model = new QStandardItemModel();
    //    for (int i=0;i<strList.size();++i) {
    //         QStringList current = strList.at(i).split(' ');
    //         for (int j=0;j<current.size();++j) {
    //             QStandardItem *item = new QStandardItem(current.at(j));
    //             model->setItem(i,j,item);
    //         }
    //    }

    //    _window->ui->tableView->setModel(model);
    //    _window->ui->tableView->verticalHeader()->hide();
    //    _window->ui->tableView->horizontalHeader()->hide();
}
