#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QIcon>
#include <QVector>
#include "AdminMainwindow.h"
#include "TeacherMainwindow.h"
#include "StudentMainwindow.h"
extern QString user_account;
extern QSqlDatabase db;
extern QString user_identity;
class Login : public QDialog
{
public:
    Login();
public slots:
    void handleLogin();
    void selectTeacher();
    void selectStudent();
    void selectAdmin();
private:
    QLineEdit *accountInput;
    QLineEdit *passwordInput;
    QString identityType;

    QVector<QPushButton*> btnVec;
    bool correct(QString id,QString password);
public slots:
    void pressColor(QPushButton * btn);
};

#endif // LOGIN_H
