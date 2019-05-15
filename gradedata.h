#ifndef GRADEDATA_H
#define GRADEDATA_H

class QStringList;
class QString;

class GradeData{
public:
    GradeData();
    ~GradeData();
//private:
public:
    QStringList openSource(QString name);
};
#endif // GRADEDATA_H
