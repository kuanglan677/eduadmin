#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

//class QListView;
class QTabelView;
class EduAdmin;
namespace Ui {
class Window;
}


class Window:public QWidget{
    Q_OBJECT
public:
    Window(EduAdmin *eduadmin,QWidget *parent = nullptr);
    ~Window();
    QString getOpenFileName();

//private:
    Ui::Window *ui;
    EduAdmin *_eduadmin;
private slots:
    int semesterStringToInt(const QString& semester);//String 类型semester转化为int类型
    //学生界面
    void on_personInfo_clicked();
    void on_studentGrade_clicked();
    void on_selectCourse_clicked();
    void on_schoolCalendar_clicked();
    void on_evaluateTeacher_clicked();
    void on_questionnairSurvey_clicked();
    void on_library_clicked();
    //教师界面
    void on_teacherinfo_clicked();
    void on_gradeManager_clicked();
    void on_selectResult_clicked();
    void on_schoolcalendar_2_clicked();
    void on_evaluateResult_clicked();
    void on_viewResult_clicked();
    void on_bookManager_clicked();
    //selectResult
    void on_addCourse_clicked();
    void on_pushButton_inquiry_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_modify_clicked();
    void on_pushButton_selectCourse_Ok_clicked();
    void on_pushButton_refresh_clicked();//刷新课表
    void on_pushButton_checkHasSelected_clicked();//查看已选课程
};
#endif // WINDOW_H
