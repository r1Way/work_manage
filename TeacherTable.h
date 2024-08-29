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
    void addTeacher(const QString &id, const QString &name, const QString &institute);
public slots:
    void showContextMenu(const QPoint &pos);
};

#endif // TEACHERTABLE_H
