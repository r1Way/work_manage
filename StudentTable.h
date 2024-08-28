#ifndef STUDENTTABLE_H
#define STUDENTTABLE_H

#include <QWidget>
#include <MyTableWidget.h>
#include <QHeaderView>


class StudentTable:public MyTableWidget
{
public:
    StudentTable();
private:
    void addStudent(const QString &name, const QString &id, const QString &major);
};

#endif // STUDENTTABLE_H
