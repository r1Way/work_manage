#ifndef CLASSTABLE_H
#define CLASSTABLE_H
#include <QWidget>
#include "MyTableWidget.h"
#include <QHeaderView>
#include <Qdir>
extern QString PATH;
class ClassTable: public MyTableWidget
{
public:
    ClassTable();
private:
    void addClass(QString id,QString name,QString description);
public slots:
    void showContextMenu(const QPoint &pos);
};

#endif // CLASSTABLE_H
