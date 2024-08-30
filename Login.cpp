#include "Login.h"

Login::Login()
{
    // //身份信息
    // this->identityType="";
    setWindowIcon(QIcon("://img/icopng"));
    setWindowTitle("C++作业管理系统");
    QVBoxLayout * mainLayOut=new QVBoxLayout(this);
    // 创建三个按钮
    QPushButton *teacherButton = new QPushButton("教师");
    QPushButton *studentButton = new QPushButton("学生");
    QPushButton *adminButton = new QPushButton("管理员");

    // 创建水平布局来放置三个按钮
    QHBoxLayout *identityButton= new QHBoxLayout;
    identityButton->addWidget(studentButton);
    identityButton->addWidget(teacherButton);
    identityButton->addWidget(adminButton);

    // 创建账号标签和输入框
    QHBoxLayout *accountLayOut=new QHBoxLayout;
    QLabel *accountLabel = new QLabel("账号:");
    accountInput = new QLineEdit();
    accountLayOut->addWidget(accountLabel);
    accountLayOut->addWidget(accountInput);
    accountInput->setPlaceholderText("请输入账号");


    // 创建密码标签和输入框
    QHBoxLayout *passwordLayOut=new QHBoxLayout;
    QLabel *passwordLabel = new QLabel("密码:");
    passwordInput = new QLineEdit();
    passwordInput->setEchoMode(QLineEdit::Password);  // 设置密码隐藏模式
    passwordLayOut->addWidget(passwordLabel);
    passwordLayOut->addWidget(passwordInput);
    passwordInput->setPlaceholderText("请输入密码");


    // 登录按钮
    QPushButton *logInButton=new QPushButton("登录");

    // 将按钮布局添加到主布局
    mainLayOut->addLayout(identityButton);
    mainLayOut->addLayout(accountLayOut);
    mainLayOut->addLayout(passwordLayOut);
    mainLayOut->addWidget(logInButton);

    //信号与槽
    connect(logInButton,&QPushButton::clicked,this,&Login::handleLogin);
    connect(teacherButton,&QPushButton::clicked,this,&Login::selectTeacher);
    connect(studentButton,&QPushButton::clicked,this,&Login::selectStudent);
    connect(adminButton,&QPushButton::clicked,this,&Login::selectAdmin);
}

void Login::handleLogin()
{
    if(identityType=="")//未选择身份
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("提示"));
        msgBox.setText(tr("请选择你的身份！"));
        msgBox.setIcon(QMessageBox::Information);  // 这里设置了警告图标
        msgBox.setStandardButtons(QMessageBox::Ok);

        // 可选：自定义样式
        msgBox.setStyleSheet(
            "QMessageBox {"
            "background-color: #2E2E2E;"  // 设置背景颜色
            "color: #FFFFFF;"             // 设置文字颜色
            "}"
            "QPushButton {"
            "color: #000000;"             // 按钮文字颜色
            "background-color: #A9A9A9;"  // 按钮背景颜色
            "}"
            );

        msgBox.exec();  // 显示消息框
    }
    else//已选择身份
    {
        //用户名或密码正确
        //update
        //test begin
        //if(correct(accountInput->text(),passwordInput->text()))
        if(true)// test end
        {
            this->close();

            //test begin
            // identityType="teacher";
            //test end
            if (identityType=="admin")
            {
                ::user_account=accountInput->text();
                AdminMainWindow *window=new AdminMainWindow;
                window->show();
            }
            else if(identityType=="teacher")
            {
                // ::user_account=accountInput->text();
                ::user_account="113210";
                TeacherMainWindow *window=new TeacherMainWindow;
                window->show();
            }
            else if(identityType=="student")
            {
                // ::user_account=accountInput->text();
                ::user_account="17514";
                StudentMainwindow * window=new StudentMainwindow;
                window->show();
            }
            else
            {
                qDebug()<<"Login::handleLogin in ' else else '";
            }
        }
        else//用户名或密码输入错误
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle(tr("登录失败"));
            msgBox.setText(tr("用户名或密码输入错误！"));
            msgBox.setIcon(QMessageBox::Warning);  // 这里设置了警告图标
            msgBox.setStandardButtons(QMessageBox::Ok);

            // 可选：自定义样式
            msgBox.setStyleSheet(
                "QMessageBox {"
                "background-color: #2E2E2E;"  // 设置背景颜色
                "color: #FFFFFF;"             // 设置文字颜色
                "}"
                "QPushButton {"
                "color: #000000;"             // 按钮文字颜色
                "background-color: #A9A9A9;"  // 按钮背景颜色
                "}"
                );

            msgBox.exec();  // 显示消息框
            this->accountInput->clear();
            this->passwordInput->clear();
            this->accountInput->setFocus();
        }
    }
}

void Login::selectTeacher()
{
    this->identityType="teacher";
}

void Login::selectStudent()
{
    this->identityType="student";
}

void Login::selectAdmin()
{
    this->identityType="admin";
}

bool Login::correct(QString id, QString password)
{
    QSqlQuery query(QString("SELECT count(*) FROM pass where user='%1' and id=%2 and password='%3'").arg(identityType).arg(id).arg(password));
    while(query.next())
    {
        if(query.isActive())
        {
            if(query.value(0).toInt()==1)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    qDebug()<<"Login::correct";
    return false;
}
