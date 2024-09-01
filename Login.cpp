#include "Login.h"

Login::Login()
{
    //图片
    setWindowIcon(QIcon("://img/icopng"));
    setWindowTitle("C++作业管理系统");
    QHBoxLayout *backLayout=new QHBoxLayout(this);
    QLabel *avatar = new QLabel(this);
    QPixmap pix("://img/light.jpg");
    avatar->setPixmap(pix.scaled(400, 400, Qt::KeepAspectRatio));
    backLayout->addWidget(avatar);

    //main layout
    QVBoxLayout * mainLayOut=new QVBoxLayout;
    backLayout->addLayout(mainLayOut);

    // 创建标题标签
    QLabel *titleLabel = new QLabel("C++作业管理系统");
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; font-family: 'Microsoft YaHei'; text-align: center;");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayOut->addWidget(titleLabel);

    // 创建三个按钮
    btnVec.push_back(new QPushButton("教师"));
    btnVec[0]->setStyleSheet("QPushButton {"
                                "   border-radius: 10px;"         // 边框圆角半径
                                "   background-color: #99d9df ;"   // 背景颜色
                                "   padding: 5px;"               // 内边距
                                "   color: black ;"               // 文本颜色
                                " font-size: 15px;"
                                "}"
                                 "QPushButton:hover {"
                                 "   background-color: #66cccc;"    // 鼠标悬停时的背景颜色
                                 "}");
    btnVec.push_back(new QPushButton("学生"));
    btnVec[1]->setStyleSheet("QPushButton {"
                                 "   border-radius: 10px;"         // 边框圆角半径
                                 "   background-color: #99d9df ;"   // 背景颜色
                                 "   padding: 5px;"               // 内边距
                                 "   color: black;"               // 文本颜色
                                 " font-size: 15px;"
                                 "}"
                                 "QPushButton:hover {"
                                 "   background-color: #66cccc;"    // 鼠标悬停时的背景颜色
                                 "}"
                                 );
    btnVec.push_back(new QPushButton("管理员"));
    btnVec[2]->setStyleSheet("QPushButton {"
                                 "   border-radius: 10px;"         // 边框圆角半径
                                 "   background-color: #99d9df ;"   // 背景颜色
                                 "   padding: 5px;"               // 内边距
                                 "   color: black;"               // 文本颜色
                                 " font-size: 15px;"
                                 "}"
                             "QPushButton:hover {"
                             "   background-color: #66cccc;"    // 鼠标悬停时的背景颜色
                             "}");

    // 创建水平布局来放置三个按钮
    QHBoxLayout *identityButton= new QHBoxLayout;
    for(int i=0;i<btnVec.size();i++)
    {
        identityButton->addWidget(btnVec[i]);
    }

    // 创建账号标签和输入框
    QHBoxLayout *accountLayOut=new QHBoxLayout;
    accountInput = new QLineEdit();
    accountLayOut->addWidget(accountInput);
    accountInput->setPlaceholderText("请输入账号");
    accountInput->setStyleSheet("QLineEdit {"
                               "   border-radius: 10px;"         // 边框圆角半径
                               "   background-color: white ;"   // 背景颜色
                               "   padding: 5px;"               // 内边距
                               "   color: #9e9e9e;"               // 文本颜色
                               " font-size: 15px;"
                               "}");


    // 创建密码标签和输入框
    QHBoxLayout *passwordLayOut=new QHBoxLayout;
    passwordInput = new QLineEdit();
    passwordInput->setEchoMode(QLineEdit::Password);  // 设置密码隐藏模式
    passwordLayOut->addWidget(passwordInput);
    passwordInput->setPlaceholderText("请输入密码");
    passwordInput->setStyleSheet("QLineEdit {"
                                "   border-radius: 10px;"         // 边框圆角半径
                                "   background-color: white ;"   // 背景颜色
                                "   padding: 5px;"               // 内边距
                                "   color: #9e9e9e;"               // 文本颜色
                                " font-size: 15px;"
                                "}");


    // 登录按钮
    QPushButton *logInButton=new QPushButton("登录");
    logInButton->setStyleSheet("QPushButton {"

                       "   border-radius: 10px;"         // 边框圆角半径
                       "   background-color: #7cc261;"   // 背景颜色
                       "   padding: 5px;"               // 内边距
                       "   color: white;"               // 文本颜色
                        " font-size: 18px;"
                       "}");

    // 将按钮布局添加到主布局
    mainLayOut->addLayout(identityButton);
    mainLayOut->addSpacing(15); // 这里设置间距
    mainLayOut->addLayout(accountLayOut);
    mainLayOut->addSpacing(5); // 这里设置间距
    mainLayOut->addLayout(passwordLayOut);
    mainLayOut->addSpacing(13); // 这里设置间距
    mainLayOut->addWidget(logInButton);

    //信号与槽
    connect(logInButton,&QPushButton::clicked,this,&Login::handleLogin);
    connect(btnVec[0],&QPushButton::clicked,this,&Login::selectTeacher);
    connect(btnVec[1],&QPushButton::clicked,this,&Login::selectStudent);
    connect(btnVec[2],&QPushButton::clicked,this,&Login::selectAdmin);

    for(int i=0;i<btnVec.size();i++)
    {
        connect(btnVec[i],&QPushButton::clicked,[this,btn=btnVec[i]]()
        {
            pressColor(btn);
        });
    }
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
                ::user_identity="admin";
                AdminMainWindow *window=new AdminMainWindow;
                window->show();
            }
            else if(identityType=="teacher")
            {
                // ::user_account=accountInput->text();
                ::user_account="113210";
                ::user_identity="teacher";
                TeacherMainWindow *window=new TeacherMainWindow;
                window->show();
            }
            else if(identityType=="student")
            {
                // ::user_account=accountInput->text();
                ::user_account="17514";
                ::user_identity="student";
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

void Login::pressColor(QPushButton *btn)
{
    btn->setStyleSheet("QPushButton {"
                                "   border-radius: 10px;"         // 边框圆角半径
                                "   background-color: #44aacc;"   // 背景颜色
                                "   padding: 5px;"               // 内边距
                                "   color: black ;"               // 文本颜色
                                " font-size: 15px;"
                       "}");

    for(int i=0;i<btnVec.size();i++)
    {
        if(btnVec[i]!=btn)
        {
            btnVec[i]->setStyleSheet("QPushButton {"
                                "   border-radius: 10px;"         // 边框圆角半径
                                "   background-color: #99d9df ;"   // 背景颜色
                                "   padding: 5px;"               // 内边距
                                "   color: black ;"               // 文本颜色
                                " font-size: 15px;"
                                "}");
        }
    }
}
