#include "eduadmin.h"
#include <QApplication>


//test
#include "window.h"
#include "gradedata.h"
#include "sqlite.h"
#include <QtDebug>
#include <QString>
#include <QTableView>
#include <QSqlQueryModel>

#include <QCheckBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

            EduAdmin w;
            w.show();


    //test
//    QCheckBox *ab  = new QCheckBox;
//    ab->setChecked(true);
//    ab->setCheckable(true);
//    ab->show();
    //    Window w;
    //    w.show();

    //    GradeData w;
    //    QStringList grade = w.openSource(QString("grade.txt"));
    //    if(!grade.isEmpty()){
    //        for (int i=0;i<grade.size();++i) {
    //            qDebug() <<  grade.at(i);
    //        }
    //    }

//    Sqlite sql;
//    sql.createDatabase("eduadmin");
//    qDebug() <<"1------";
//    sql.inquiryData();
//    sql.execQuery("delete from CourseTable where CourseName = 'aa'");
//    qDebug() <<"2------";
//    sql.inquiryData();
//    if(sql.rollback())
//        qDebug() <<"3------";
//    qDebug() <<"4------";
//    sql.inquiryData();

    //    sql.createDatabase("eduadmin");
    //    QSqlQueryModel *model = new QSqlQueryModel();

    //    //        sql.execQuery("select * from CousrseTable ");
    //    sql.execInquiryAll("CousrseTable",model);

    //    QTableView *tab = new QTableView();
    //    tab->show();

    //    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Semester"));
    //    model->setHeaderData(1,Qt::Horizontal,QObject::tr("CourseName"));
    //    model->setHeaderData(2,Qt::Horizontal,QObject::tr("TeacherName"));
    //    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Capacity"));

    //    tab->setModel(model);




    //        sql.createDatabase(QString("test.db")); //创建数据库
    //        sql.createTables({"student", "id", "int", "name", "text","age", "int"});//创建表
    //        sql.execQuery("insert into student values(201701,\"Wang\",23)");//插入数据
    //        sql.execQuery("update student set name =\"QT\" where id = 201701");//更新数据
    //        sql.inquiryData();//查询数据
    //        sql.execQuery("delete from student where id = 201701");//删除数据
    //        sql.execQuery("drop table student");//删除表

    return a.exec();

}
