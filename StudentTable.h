#ifndef STUDENTTABLE_H
#define STUDENTTABLE_H

#include <QWidget>
#include <MyTableWidget.h>
#include <QHeaderView>
#include <QVector>
#include "TableWindow.h"

class StudentTable:public MyTableWidget
{
public:
    StudentTable();
private:
    void addStudent(const QString &id, const QString &name, const QString &major);
public slots:
    void showContextMenu(const QPoint &pos);
    void editStudent(int row);
};

#endif // STUDENTTABLE_H
