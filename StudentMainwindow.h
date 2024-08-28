#ifndef STUDENTMAINWINDOW_H
#define STUDENTMAINWINDOW_H
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
#include <QMainWindow>
#include "HeadWidget.h"
#include "TableWindow.h"
#include "FileWindow.h"
class StudentMainwindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit StudentMainwindow(QWidget *parent = nullptr);
    TableWindow *tableWindow;
signals:
public slots:
    void itemDoubleClicked(QTableWidgetItem* item,QStackedWidget *stackedWidget);
    void homeworkDoubleClicked(QTableWidgetItem* item,QStackedWidget *stackedWidget);//选中是哪次作业
};

#endif // STUDENTMAINWINDOW_H
