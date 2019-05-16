#include "window.h"
#include "ui_window.h"
#include "eduadmin.h"
#include <QTableWidget>
#include <QFileDialog>

#include <QMessageBox>
#include <QDebug>

#include <QAbstractItemModel>
#include <QItemSelectionModel>
#include <QModelIndex>
#include <QStandardItemModel>

#include <QCheckBox>
#include <QInputDialog>
#include <vector>

//debug
#include "sqlite.h"
#define DEBUG 1

Window::Window(EduAdmin *eduadmin,QWidget *parent)
    :QWidget(parent),ui(new Ui::Window),_eduadmin(eduadmin)
{
    ui->setupUi(this);
    ui->tableView_allCourse->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选择模式设为整行
    ui->tableView_allCourse->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置表格的单元为只读属性，即不能编辑

    ui->tableView_selectCourse->setSelectionMode(QAbstractItemView::NoSelection);
}

Window::~Window(){
    delete ui;
//        delete _eduadmin;
}

int Window::semesterStringToInt(const QString& semester){
    if(semester =="第一学期")
        return 1;
    else if(semester =="第二学期")
        return 2;
    else if(semester =="第三学期")
        return 3;
    else if(semester =="第四学期")
        return 4;

    return -1;
}

QString Window::getOpenFileName(){
    return QFileDialog::getOpenFileName(this,QString(""),tr("."),tr("*.txt"));
}

//Page_Changed
void Window::on_personInfo_clicked()
{
    ui->stackedWidget_down->setCurrentIndex(0);
}
void Window::on_studentGrade_clicked()
{
    ui->stackedWidget_down->setCurrentIndex(1);
}
void Window::on_selectCourse_clicked()
{
    ui->stackedWidget_down->setCurrentIndex(2);
}
void Window::on_schoolCalendar_clicked()
{
    ui->stackedWidget_down->setCurrentIndex(3);
}
void Window::on_evaluateTeacher_clicked()
{
    ui->stackedWidget_down->setCurrentIndex(4);
}
void Window::on_questionnairSurvey_clicked()
{
    ui->stackedWidget_down->setCurrentIndex(5);
}
void Window::on_library_clicked()
{
    ui->stackedWidget_down->setCurrentIndex(6);
}
void Window::on_teacherinfo_clicked()
{
    ui->stackedWidget_down->setCurrentIndex(7);
}
void Window::on_gradeManager_clicked()
{
    ui->stackedWidget_down->setCurrentIndex(8);
}
void Window::on_selectResult_clicked()
{
    ui->stackedWidget_down->setCurrentIndex(9);
}
void Window::on_schoolcalendar_2_clicked()
{
    ui->stackedWidget_down->setCurrentIndex(10);
}
void Window::on_evaluateResult_clicked()
{
    ui->stackedWidget_down->setCurrentIndex(11);
}
void Window::on_viewResult_clicked()
{
    ui->stackedWidget_down->setCurrentIndex(12);
}
void Window::on_bookManager_clicked()
{
    ui->stackedWidget_down->setCurrentIndex(13);
}


void Window::on_addCourse_clicked()
{
    QString semester = ui->comboBox->currentText();
    QString courseName = ui->lineEdit_courseName->text();
    QString teacherName = ui->lineEdit_courseTeacher->text();
    QString capacity = ui->studentCapacity->text();
    if((courseName.isEmpty()||teacherName.isEmpty())){
        QMessageBox::critical(this,tr("提示"),tr("请先输入有效的课程及教师"),QMessageBox::Ok,QMessageBox::Ok);
    }else{
        _eduadmin->addCourse(semester,courseName,teacherName,capacity);//添加到课程表
        _eduadmin->addIntoSemesterCourse(semesterStringToInt(semester),courseName);//添加到相应的学期选课情况表
    }
    _eduadmin->showAllCourse();
}//添加课程
void Window::on_pushButton_inquiry_clicked()
{
    ui->tableView_allCourse->clearSelection(); //清空选中行

    QString inquiry = ui->lineEdit_courseName2->text();
    if(inquiry.isEmpty()){
        QMessageBox::critical(this,tr("提示"),tr("输入为空"),
                              QMessageBox::Ok,QMessageBox::Ok);
        return;
    }
    QAbstractItemModel *model = ui->tableView_allCourse->model();

    bool flag = false;
    for (int i = 0; i < model->rowCount(); ++i) { //在视图中查找 找到就删除
        if(inquiry == model->index(i,0).data().toString()){
            flag = true;
            ui->tableView_allCourse->selectRow(i);
            break;
        }
    }

    if(!flag){
        QMessageBox::critical(this,tr("提示"),tr("你输入的课程未找到,请输入有效的课程"),QMessageBox::Ok,QMessageBox::Ok);
    }

}//查找课程
void Window::on_pushButton_delete_clicked()
{
    QAbstractItemModel *model = ui->tableView_allCourse->model();
    QItemSelectionModel *selections = ui->tableView_allCourse->selectionModel();
    QModelIndexList selected = selections->selectedIndexes();

    if(selected.isEmpty()){
        QMessageBox::critical(this,tr("提示"),tr("请先查询课程"),QMessageBox::Ok,QMessageBox::Ok);
        return;
    }

    QMap<QString,QString> rowMap;//储存选择的课程名和学期

    foreach(QModelIndex index,selected){
        QString courseName = model->index(index.row(),0).data().toString();
        QString semester =model->index(index.row(),1).data().toString();
        rowMap.insert(courseName,semester);
    }

    QMapIterator<QString,QString>rowMapIterator(rowMap);
    rowMapIterator.toBack();  //从后向前删
    while(rowMapIterator.hasPrevious()){
        rowMapIterator.previous();
        QString deleteCourse = rowMapIterator.key();
        QString CourseSemester = rowMapIterator.value();
        if(_eduadmin->deleteCourse(deleteCourse)){  //从总的课程表删除
            _eduadmin->deleteFromSemesterCourse(semesterStringToInt(CourseSemester),deleteCourse); //从相应的学期选课情况表中删除
            QMessageBox::information(this,tr("提示"),tr("成功删除 %1").arg(deleteCourse),QMessageBox::Ok,QMessageBox::Ok);
            //            qDebug() << "删除成功";
        }else{
            QMessageBox::critical(this,tr("提示"),tr("删除失败 %1").arg(deleteCourse),QMessageBox::Ok,QMessageBox::Ok);
            //            qDebug() << "删除失败";
        }
    }
    _eduadmin->showAllCourse();

}//删除课程
void Window::on_pushButton_modify_clicked()
{
    QItemSelectionModel *selections = ui->tableView_allCourse->selectionModel();
    QModelIndexList selected = selections->selectedIndexes();

    if(selected.isEmpty()){
        QMessageBox::critical(this,tr("提示"),tr("请先查询课程"),QMessageBox::Ok,QMessageBox::Ok);
        return;
    }
    QString newData = QInputDialog::getText(this,tr("输入信息"),tr("请按照下列格式依次输入新的\n课程名称/学期/授课老师/容量"));
    if(!newData.isEmpty()){
        QStringList newDataList =  newData.split('/');
        if (newDataList.size()!=4){
            QMessageBox::critical(this,tr("提示"),tr("请输入有效的更改信息"),QMessageBox::Ok,QMessageBox::Ok);
            return;
        }
        QString courseName = newDataList.at(0);
        QString semester = newDataList.at(1);
        QString courseTeacher = newDataList.at(2);
        QString capasity = newDataList.at(3);
        QString oldName = ui->lineEdit_courseName2->text();
        if(_eduadmin->updateCourseInfo(oldName,courseName,semester,courseTeacher,capasity)){
            _eduadmin->showAllCourse();
        }
    }
}//修改课程信息

void Window::on_pushButton_selectCourse_Ok_clicked()
{

    QAbstractItemModel *model= ui->tableView_selectCourse->model();

    /*static*/
    QStringList selectedCourse;
    QStringList selectedCourseName;
//    static std::initializer_list<QString> il;
//    static std::vector<QString> vs;
    for(int i=0;i<model->rowCount();++i){
        QCheckBox *checkbox = new QCheckBox;
        checkbox = static_cast<QCheckBox*>(ui->tableView_selectCourse->indexWidget( model->index(i,3)));
        selectedCourseName << ui->tableView_selectCourse->model()->data( model->index(i,0)).toString();
        if(checkbox->isChecked()){
            selectedCourse << "Yes";

        }else {
            selectedCourse << "Not";
        }
    }
    if(!selectedCourse.isEmpty()){
        if(_eduadmin->insertIntoSCT("FirstSCT","201701",selectedCourse,selectedCourseName)){
            QMessageBox::information(this,tr("提示"),tr("选课成功"),QMessageBox::Ok,QMessageBox::Ok);
        }else {
            QMessageBox::information(this,tr("提示"),tr("选课失败"),QMessageBox::Ok,QMessageBox::Ok);
        }
    }

}//确认选课
void Window::on_pushButton_refresh_clicked()
{
    _eduadmin->showAllCurrentSemesterCourse("第一学期");
}//刷新课表
void Window::on_pushButton_checkHasSelected_clicked()
{
    QString selectedCourse = _eduadmin->checkHaschecked("201701",1);

    if(!selectedCourse.isEmpty()){
        QMessageBox::information(this,tr("提示"),tr("已选课程：\n")+selectedCourse,QMessageBox::Ok,QMessageBox::Ok);
    }
}//查看已选课程
