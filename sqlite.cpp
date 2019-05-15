#include "sqlite.h"

#include<QDebug>
#include<QSqlDatabase>
#include<QSqlError>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QSqlTableModel>

#include <string>
#include <list>

bool Sqlite::createDatabase(const QString& databaseName , const QString& databasetype){
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase(databasetype);
    database.setDatabaseName(databaseName);
    if(!database.open()){
        qDebug() << "Error:Fail to connect database." << database.lastError();
        return false;
    }else {
        qDebug() << "Succeed to connect database : "+databaseName;
        return true;
    }
}  //创建QSQLITE数据库
bool Sqlite::createTables(std::initializer_list<QString> il){
    QSqlQuery sqlQuery;

    auto size = il.size();//检查输入是否规范
    if(size%2==0||size<3)
        return false;

    QString query;
    int itemnum = (static_cast<int>(size)-1)/2;
    auto it = il.begin();

    //query语句
    query="create table " + *it++ +"(";
    //默认第一项为 primary key
    query += *it++;
    query += " ";
    query += *it++;
    query += " primary key";
    //依次添加每一项
    for (int i=0;i<itemnum-1;++i) {
        query += ",";
        query += *it++;
        query += " ";
        query += *it++;
    }
    //最后的括号
    query += ")";
    //debug
    //    qDebug() <<query;
    if(it!=il.end()){
        qDebug() << "query 语句添加有误";
        return false;
    }

    if(!sqlQuery.exec(query)){
        qDebug() << "Error:Fail to create table" << sqlQuery.lastError();
        return false;
    }else {
        qDebug() << "Succeed to create table : "+ *il.begin();
        return true;
    }
}  //创建表 list 依次为tablename arg1 arg1type arg2 arg2type...
bool Sqlite::execQuery(const QString& query){

    std::string a = query.toStdString().substr(0,query.toStdString().find(' '));//截取从开始到第一个' '的字符串
    QString type = QString::fromStdString(a);

    QSqlQuery sqlQuery;
    if(!sqlQuery.exec(query)){
        qDebug() << "Error:Fail to " << type << sqlQuery.lastError();
        return false;
    }else{
        qDebug() << "Succeed to " << type ;
        return true;
    }
}  //增删改 删除表可以用同一个函数执行sql语句
bool Sqlite::execInquiryAll(const QString& tableName,QSqlQueryModel *model){
    QString query = (QString("select * from %1 ").arg(tableName));
    model->setQuery(query);
    return true;
}  //执行(全部)查找

bool Sqlite::selectSemesterCourse(const QString& semester,QSqlQueryModel *model){
    QString query;
    query = QObject::tr("select CourseName,TeacherName,Capacity from CourseTable where Semester = '%1'").arg(semester);
    model ->setQuery(query);
    return true;
} //查找该学期的课程

bool Sqlite::updateCourseInfo(const QString& oldName,const QString& newCourseName,const QString& newSemester,const QString& newTeacherName,const QString& newCapacity){
    QString query;
    query = QObject::tr("update CourseTable set CourseName='%1', Semester='%2', TeacherName='%3',Capacity = '%4' where CourseName='%5'").
            arg(newCourseName,newSemester,newTeacherName,newCapacity,oldName);
    if(!execQuery(query)){
        return false;
    }
    return true;
}//更新课程信息
bool Sqlite::inquiryData(){
    QSqlQuery sqlQuery;
    if(!sqlQuery.exec("select * from CourseTable")){
        qDebug() << "Error:Fail to inquiry data" << sqlQuery.lastError();
        return false;
    }else{
        qDebug() << "Succeed to inquiry Data";
        while (sqlQuery.next()) {
            QString name = sqlQuery.value(0).toString();
            QString semester = sqlQuery.value(1).toString();
            QString teacher = sqlQuery.value(2).toString();
            QString capasity = sqlQuery.value(3).toString();
            qDebug() << QString("id:%1 name:%2 age:%3-%4").arg(name,semester,teacher,capasity);
        }
        return true;
    }
}//查找数据select

