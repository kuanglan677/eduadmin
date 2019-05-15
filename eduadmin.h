#ifndef EDUADMIN_H
#define EDUADMIN_H

#include <QWidget>
class Window;
class GradeData;
class Sqlite;
#include <QSqlQueryModel>
class EduAdmin : public QWidget
{
    Q_OBJECT

public:
    EduAdmin(QWidget *parent = nullptr);
    ~EduAdmin();

    void addRecord();
    //sqlite 相关函数
    void initSqlite();

    //window 相关函数
    //课程管理界面
    bool addCourse(QString semester,QString courseName,QString teacherName,QString capacity);//添加新的课程
    void showAllCourse();//展示所有课程
    bool deleteCourse(const QString& courseName);//删除课程
    bool updateCourseInfo(const QString& oldName,const QString& newCourseName,const QString& newSemester,const QString& newTeacherName,const QString& newCapasity);//更改课程信息
//    bool addIntoSemesterCourse(const QString& semester,const QString& courseName); //添加到相应的学期选课表
    bool addIntoSemesterCourse(int semester,const QString& courseName); //添加到相应的学期选课表
//    bool deleteFromSemesterCourse(const QString& semester,const QString& courseName); //从相应的学期选课表中删除
    bool deleteFromSemesterCourse(int semester,const QString& courseName); //从相应的学期选课表中删除
    //学生选课界面
    void showAllCurrentSemesterCourse(const QString& semester);//显示当前学期课程
    bool insertIntoSCT(const QString& semesterTable,const QString& studentNo,QStringList il);//学生添加课程
private:
    Window *_window;
    GradeData *_gradaData;
    Sqlite *_sqlite;
};

#endif // EDUADMIN_H
