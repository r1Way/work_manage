#include <QApplication>
#include <QDir>
#include <QSplitter>
#include "StudentMainwindow.h"
#include "BasicWindow.h"
#include "FileWindow.h"
#include "HeadWidget.h"
#include "Highlighter.h"
#include "TableWindow.h"
#include "Login.h"
#include "Highlighter.h"
#include "MyTableWidget.h"
#include "StudentMainwindow.h"
#include "TeacherMainwindow.h"
#include "AdminMainwindow.h"
#include "StudentTable.h"
#include "TeacherTable.h"
#include "LabelEdit.h"
#include <QDoubleValidator>
QSqlDatabase db;
QString user_account;
QString PATH;
QString user_identity;

//database
QString SET_HOST_NAME="127.0.0.1";
QString SET_DATABASE_NAME="Mysql";
QString SET_USER_NAME="root";
QString SET_PASSWORD="111111";

int main(int argc, char *argv[])
{
    //获取当前路径
    QDir dir(QDir::currentPath());
    PATH=dir.path()+"/data";
    // qDebug()<<PATH;
    if(!dir.exists("data"))
    {
        dir.mkdir("data");    //创建文件夹（名为Images）

        qDebug()<<QString("文件夹%1创建成功！").arg("data");
    }
    else
    {
        qDebug()<<QString("文件夹%1已存在！").arg("data");
    }

    QApplication a(argc, argv);
    // 创建 ODBC 数据库对象
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        db=QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QODBC");
    }
    // 设置 DSN
    db.setHostName(SET_HOST_NAME);
    db.setDatabaseName(SET_DATABASE_NAME);
    db.setUserName(SET_USER_NAME);
    db.setPassword(SET_PASSWORD); //用数据库实际账号密码代替
    // 打开数据库连接
    if (!db.open())
    {
        qDebug("打开数据库连接失败" );
    }

    Login login;
    login.show();
    // LabelEdit edit;
    // edit.show();

    return a.exec();
}

