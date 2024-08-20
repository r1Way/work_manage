#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
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
};

#endif // LOGIN_H
