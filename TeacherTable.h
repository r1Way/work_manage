#ifndef TEACHERTABLE_H
#define TEACHERTABLE_H

#include <QWidget>
#include "myTableWidget.h"
#include <QHeaderView>

class TeacherTable : public myTableWidget
{
public:
    TeacherTable();
private:
    void addTeacher(const QString &name, const QString &id, const QString &institute);
};

#endif // TEACHERTABLE_H
