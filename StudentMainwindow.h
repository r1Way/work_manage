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
#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QProcess>
#include <QByteArray>
#include <QMessageBox>
#include "HeadWidget.h"
#include "TableWindow.h"
#include "FileWindow.h"
#include "LabelEdit.h"
extern QSqlDatabase db;
extern QString user_account;
extern QString PATH;
class StudentMainwindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit StudentMainwindow(QWidget *parent = nullptr);
    TableWindow *tableWindow;
signals:
public slots:
    void itemDoubleClicked(QString classId,QStackedWidget *stackedWidget);
    void homeworkDoubleClicked(QString classId,QString homeworkName, QStackedWidget *stackedWidget,TableWindow *tableWindow2);//选中是哪次作业
    void handIn(QString classId,QString homeworkName,FileWindow *fileWindow);
};

#endif // STUDENTMAINWINDOW_H
