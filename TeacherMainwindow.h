#ifndef TEACHERMAINWINDOW_H
#define TEACHERMAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStackedLayout>
#include <QSharedPointer>
#include <QStackedWidget>
#include <QTextEdit>
#include "HeadWidget.h"
#include "TableWindow.h"
#include "FileWindow.h"
class TeacherMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit TeacherMainWindow(QWidget *parent = nullptr);

    TableWindow *tableWindow;

signals:
public slots:
    void itemDoubleClicked(QTableWidgetItem* item,QStackedWidget *stackedWidget);
    void homeworkDoubleClicked(QTableWidgetItem* item,QStackedWidget *stackedWidget);//选中是哪次作业
    void studentDoubleClicked(QTableWidgetItem* item,QStackedWidget *stackedWidget);
};

#endif // TEACHERMAINWINDOW_H
