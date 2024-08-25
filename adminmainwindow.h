#ifndef ADMINMAINWINDOW_H
#define ADMINMAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

#include "headwidget.h"
#include "myTableWidget.h"
#include "StudentTable.h"
#include "TeacherTable.h"
class AdminMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit AdminMainWindow(QWidget *parent = nullptr);
private:
    myTableWidget *tableWidget;
signals:
};

#endif // ADMINMAINWINDOW_H
