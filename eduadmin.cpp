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

EduAdmin::EduAdmin(QWidget *parent)
    : QWidget(parent),_window(new Window(this,this)),_gradaData(new GradeData),_sqlite(new Sqlite)
{
    //初始化课程表
    initSqlite();
    showAllCourse();//展示课程
    showAllCurrentSemesterCourse("第一学期");//展示可选课程
}

EduAdmin::~EduAdmin()
{
}

//初始化数据库
void EduAdmin::initSqlite(){
    if(!_sqlite->createDatabase("eduadmin")){}  //连接数据库
    if(!_sqlite->createTables({"CourseTable",  //创建课程表（包含所有课程的表）
                              "CourseName","varchar(20)",
                              "Semester","varchar(20)" ,
                              "TeacherName","varchar(20)", "Capacity","varchar(5)"})){/*错误检测*/}
    if(!_sqlite->createTables({"FirstSCT",   //创建第一学期课程表
                              "StudentNo","int"})){}
    if(!_sqlite->createTables({"SecondSCT",  //创建第二学期课程表
                              "StudentNo","int"})){}
    if(!_sqlite->createTables({"ThirdSCT",  //创建第三学期课程表
                              "StudentNo","int"})){}
    if(!_sqlite->createTables({"FourthSCT",  //创建第四学期课程表
                              "StudentNo","int"})){}

}

//=========================================================================
// 界面相关函数
//=========================================================================
//课程管理界面

bool EduAdmin::addCourse(QString semester,QString courseName,QString teacherName,QString capacity){
    if(!_sqlite->addCourse(semester,courseName,teacherName,capacity)){return false;}
    else return true;
}//添加新的课程
bool EduAdmin::deleteCourse(const QString& courseName){
    if(!_sqlite->deleteCourse(courseName)){return false;}
    else return true;
}//删除课程
bool EduAdmin::updateCourseInfo(const QString& oldName,const QString& newCourseName,const QString& newSemester,const QString& newTeacherName,const QString& newCapasity){
    if(!_sqlite->updateCourseInfo(oldName,newCourseName,newSemester,newTeacherName,newCapasity)){return false;}
    return true;
}//更改课程信息
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

bool EduAdmin::addIntoSemesterCourse(int semester,const QString& courseName){
    if(!_sqlite->addIntoSemesterCourse(semester,courseName)){return false;}
    return true;
} //添加到相应的学期选课表
bool EduAdmin::deleteFromSemesterCourse(int semester,const QString& courseName){
    if(!_sqlite->deleteFromSemesterCourse(semester,courseName)){return false;}
    return true;
} //从相应的学期选课表中删除


//学生选课界面

void EduAdmin::showAllCurrentSemesterCourse(const QString& semester = "第一学期"){
    QSqlQueryModel *model = new QSqlQueryModel; //从数据库获取模型
    _sqlite->selectSemesterCourse(semester,model);

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CourseName"));//设置表头
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TeacherName"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Capacity"));
    model->insertColumn(3);
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Selected"));

    _window->ui->tableView_selectCourse->setModel(model);//设置模型
    _window->ui->tableView_selectCourse->verticalHeader()->hide();

    for(int i=0;i<model->rowCount();++i){//设置checkbox
        QCheckBox *ch = new QCheckBox;
//        ch->setText("选择");//不会显示
        ch->setCheckable(true);//设置不可编辑
        ch->setChecked(true);
//        ch->setEnabled(true);//设置可选

        QString  select = _sqlite->checkHaschecked("201701",1);
        QStringList list = select.split('/');
        for (int i=0;i<list.size();++i) {
            QString s= model->data(model->index(i,0)).toString();
            if(list.at(i)==s){
                ch->setChecked(true);
//                ch->setCheckable(false);
                break;
            }
        }


        /*
         * 判断课程是否被选择
         * 如果已选checkbox->setchecked;
         */

        _window->ui->tableView_selectCourse->setIndexWidget(model->index(i,3),new QCheckBox(this));
    }    
}//显示当前学期课程
bool EduAdmin::insertIntoSCT(const QString& semesterTable,const QString& studentNo,const QStringList& il,const QStringList& ilName){
    if(!_sqlite->insertIntoSCT(semesterTable,studentNo,il,ilName)){return false;}
    else return true;
}//学生添加课程

QString EduAdmin::checkHaschecked(const QString& studentNo,int semester){
    return _sqlite->checkHaschecked(studentNo,semester);
}//查询学生已选课程

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
