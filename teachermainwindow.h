#ifndef TEACHERMAINWINDOW_H
#define TEACHERMAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

#include "headwidget.h"
#include "myTableWidget.h"
class TeacherMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit TeacherMainWindow(QWidget *parent = nullptr);

signals:
private:
    myTableWidget *tableWidget;
};

#endif // TEACHERMAINWINDOW_H
