#ifndef TEACHERTABLE_H
#define TEACHERTABLE_H

#include <QWidget>
#include "MyTableWidget.h"
#include <QHeaderView>

class TeacherTable : public MyTableWidget
{
public:
    TeacherTable();
private:
    void addTeacher(const QString &name, const QString &id, const QString &institute);
};

#endif // TEACHERTABLE_H
