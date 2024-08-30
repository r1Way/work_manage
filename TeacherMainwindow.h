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
#include <QDialog>
#include <QDateEdit>
#include <QTimeEdit>
#include <QVector>
#include <QCheckBox>
#include "HeadWidget.h"
#include "TableWindow.h"
#include "FileWindow.h"
extern QString user_account;
extern QSqlDatabase db;
extern QString PATH;
class TeacherMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit TeacherMainWindow(QWidget *parent = nullptr);

    TableWindow *tableWindow;
    QPushButton *ensureBatch;
signals:
public slots:
    void itemDoubleClicked(QTableWidgetItem* item,QStackedWidget *stackedWidget);
    void homeworkDoubleClicked(int row, QStackedWidget *stackedWidget,TableWindow *tableWindow2);//选中是哪次作业
    void studentDoubleClicked(QTableWidgetItem* item,QStackedWidget *stackedWidget);
    void assignHomework(QString classId,TableWindow *tableWindow2);
    void addHomework(QString,QString,QString,QString,QString,TableWindow *tableWindow2);
};

#endif // TEACHERMAINWINDOW_H
