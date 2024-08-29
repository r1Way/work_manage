#include <QApplication>
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

QSqlDatabase db;
QString user_account;
int main(int argc, char *argv[])
{
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
    db.setHostName("127.0.0.1");
    db.setDatabaseName("Mysql");
    db.setUserName("root");
    db.setPassword("111111"); //用数据库实际账号密码代替
    // 打开数据库连接
    if (!db.open())
    {
        qDebug("打开数据库连接失败" );
    }
    Login login;
    login.show();
    return a.exec();
}
