#ifndef SQLITE_H
#define SQLITE_H

#include <list>
#include <QString>
//class QString;
//class initializer_list;
class QSqlQueryModel;
#include <QSqlDatabase>
#include <QObject>
class Sqlite:public QSqlDatabase{
public:
    bool createTables(std::initializer_list<QString> il);  //list 依次为tablename arg1 arg1type arg2 arg2type...
//    bool execInquiry(std::initializer_list<QString> il);  //list 依次为tablename 条件1 值1
    bool createDatabase(const QString& databaseName , const QString& databasetype = "QSQLITE");  //创建QSQLITE数据库
    bool execQuery(const QString& query);  //执行普通sql语句 增删改
    bool execInquiryAll(const QString& tableName,QSqlQueryModel *model); //执行(全部)查找

    bool updateCourseInfo(const QString& oldName,const QString& newCourseName,const QString& newSemester,const QString& newTeacherName,const QString& newCapasity);//更新课程信息
    bool selectSemesterCourse(const QString& semester,QSqlQueryModel *model); //查找该学期的课程
    bool inquiryData();//查找

//    bool initCoursetable();//初始化课程表
};
#endif // SQLITE_H
