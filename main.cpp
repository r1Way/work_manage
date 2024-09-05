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
    QApplication a(argc, argv);
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

    //查找数据库信息
    QFile file(PATH+"/databaseInfo.txt");
    // 检查文件是否存在
    if (!file.exists())
    {
        // 打开文件进行写入
        if (file.open(QIODevice::WriteOnly))
        {
            QTextStream out(&file);

            out <<SET_HOST_NAME<<"\n";
            out <<SET_DATABASE_NAME<<"\n";
            out <<SET_USER_NAME<<"\n";
            out <<SET_PASSWORD<<"\n";
            file.close();
        }
    }

    QStringList lines;
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);

        while (!in.atEnd())
        {
            QString line = in.readLine();
            lines.append(line);
        }
        file.close();
    }
    else
    {
        QMessageBox messageBox;
        messageBox.setWindowIcon(QIcon("://img/icopng"));
        messageBox.setWindowTitle("数据库信息");
        messageBox.setText("数据库信息打开失败。");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.setStandardButtons(QMessageBox::Ok);
        messageBox.exec();
    }


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
    db.setHostName(lines[0]);
    db.setDatabaseName(lines[1]);
    db.setUserName(lines[2]);
    db.setPassword(lines[3]); //用数据库实际账号密码代替
    // 打开数据库连接
    if (!db.open())
    {
        qDebug("打开数据库连接失败" );
        QMessageBox messageBox;
        messageBox.setWindowIcon(QIcon("://img/icopng"));
        messageBox.setWindowTitle("数据库验证");
        messageBox.setText("数据库连接失败，请修改配置。");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.setStandardButtons(QMessageBox::Ok);
        messageBox.exec();
    }

    Login login;
    login.show();

    return a.exec();
}

