#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H

#include <QTableWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStringList>
#include <QHeaderView>
#include <QScrollArea>
#include "BasicWindow.h"
class TableWindow:public BasicWindow
{
public:
    QLineEdit *searchEdit;
    QPushButton *searchBtn;
    QTableWidget *tableWidget;
    QScrollArea *scrollArea;
    QSqlDatabase db;
    QSqlQuery query;
    QStringList information;
    QString tableName;
    QString driver;
    QString hostName;
    QString databaseName;
    QString userName;
    QString password;
    QString selectFresh;
    TableWindow(QStringList information);
    void fresh();
    void tableInit(QStringList information);//初始化列数以及各列名称
    void connectDataBase(QString select,QString driver="QODBC", QString hostName="127.0.0.1", QString databaseName="Mysql", QString userName="root", QString password="111111");//连接数据库
    void add(QStringList list);
    void search(QString keyword);
    void changeLayout(QLayout *layout);//更换layout,但不删除原布局
    void clearLeftLayout();//清除leftLayout上的所有部件，并delete
    void closeDatabase();
    void changeTable(QString tableName,QStringList information);
};

#endif // TABLEWINDOW_H
