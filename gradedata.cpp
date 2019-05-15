#include "gradedata.h"
#include <QStringList>
#include <QString>
#include <QFile>
GradeData::GradeData(){

}
GradeData::~GradeData(){

}

QStringList GradeData::openSource(QString name){
    QStringList grade;
    if(!QFile::exists(name))
        return grade;

    QFile file(name);
    if(file.open(QFile::ReadOnly)){
        QString str = file.readAll();
        grade = str.split('\n');
    }
    return grade;
}
