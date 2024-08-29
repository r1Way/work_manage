#ifndef ADMINMAINWINDOW_H
#define ADMINMAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

#include "HeadWidget.h"
#include "MyTableWidget.h"
#include "StudentTable.h"
#include "TeacherTable.h"
#include "ClassTable.h"
class AdminMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit AdminMainWindow(QWidget *parent = nullptr);
private:
    MyTableWidget *tableWidget;
signals:
};

#endif // ADMINMAINWINDOW_H
