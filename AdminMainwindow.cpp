#include "AdminMainwindow.h"

AdminMainWindow::AdminMainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    //全屏
    this->showMaximized();
    this->setWindowFlags(Qt::Dialog|Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);

    setWindowIcon(QIcon("://img/icopng"));
    setWindowTitle("C++作业管理系统");
    // 创建中心小部件
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    //central layout
    QVBoxLayout *mainLayOut=new QVBoxLayout(centralWidget);

    //kid widget
    HeadWidget *headWidget=new HeadWidget();

    //kid layout
    QHBoxLayout *downLayOut=new QHBoxLayout();
    QVBoxLayout *leftLayOut=new QVBoxLayout();
    QVBoxLayout *rightLayOut=new QVBoxLayout();


    //layout 管理
    mainLayOut->addWidget(headWidget);
    mainLayOut->addLayout(downLayOut);

    downLayOut->addLayout(leftLayOut);
    downLayOut->addLayout(rightLayOut);

    //leftLayOut
    QFont * font=new QFont;
    font->setPointSize(15);

    QPushButton * studentButton=new QPushButton("学生管理");
    studentButton->setFixedSize(100,50);
    studentButton->setFont(*font);

    QPushButton * teacherButton=new QPushButton("教师管理");
    teacherButton->setFixedSize(100,50);
    teacherButton->setFont(*font);

    QPushButton * classButton=new QPushButton("课程管理");
    classButton->setFixedSize(100,50);
    classButton->setFont(*font);

    //category button manage
    leftLayOut->addWidget(studentButton);
    leftLayOut->addWidget(teacherButton);
    leftLayOut->addWidget(classButton);
    leftLayOut->addStretch();

    //rightLayOut
    tableWidget=new StudentTable;
    rightLayOut->addWidget(tableWidget);

    //修改密码
    connect(headWidget->changePass,&QPushButton::clicked,[this]()
            {
        QFont font_dialog;
        font_dialog.setPointSize(13);

        QDialog *dialog=new QDialog(this);
        dialog->setWindowTitle("修改密码");
        dialog->setWindowIcon(QIcon("://img/icopng"));

        QVBoxLayout *dialogLayout=new QVBoxLayout;
        dialog->setLayout(dialogLayout);

        QLabel *oldPassLabel=new QLabel("请输入旧密码");
        dialogLayout->addWidget(oldPassLabel);
        oldPassLabel->setFont(font_dialog);

        QLineEdit *oldPassEdit=new QLineEdit;
        dialogLayout->addWidget(oldPassEdit);
        oldPassEdit->setFont(font_dialog);

        QLabel *newPassLabel=new QLabel("请输入新密码");
        dialogLayout->addWidget(newPassLabel);
        newPassLabel->setFont(font_dialog);

        QLineEdit *newPassEdit=new QLineEdit;
        dialogLayout->addWidget(newPassEdit);
        newPassEdit->setFont(font_dialog);

        QPushButton *ensure=new QPushButton("确认");
        dialogLayout->addWidget(ensure);
        connect(ensure,&QPushButton::clicked,[dialog,oldPassEdit,newPassEdit]()
        {
            QSqlQuery query;
            QString sql=QString("SELECT COUNT(*) FROM pass "
                       "WHERE user='admin' AND "
                                  "id=%1 AND "
                                  "password='%2'").arg(user_account).arg(oldPassEdit->text());
            query.exec(sql);
            int nums=-1;
            while(query.next())
            {
                nums=query.value(0).toInt();
            }

            if(nums==0)
            {
                QMessageBox messageBox;
                messageBox.setWindowIcon(QIcon("://img/icopng"));
                messageBox.setWindowTitle("更改密码验证");
                messageBox.setText("旧密码输入错误，请重新输入。");
                messageBox.setIcon(QMessageBox::Warning);
                messageBox.setStandardButtons(QMessageBox::Ok);
                messageBox.exec();
            }
            else
            {
                sql=QString("UPDATE pass "
                              "SET password='%1' "
                              "WHERE user='admin' AND "
                              "id=%2 ").arg(newPassEdit->text()).arg(user_account);

                query.exec(sql);

                QMessageBox messageBox;
                messageBox.setWindowIcon(QIcon("://img/icopng"));
                messageBox.setWindowTitle("更改密码验证");
                messageBox.setText("更改密码成功，请重新登录。");
                messageBox.setIcon(QMessageBox::Warning);
                messageBox.setStandardButtons(QMessageBox::Ok);
                messageBox.exec();
                dialog->close();
            }
        });
        dialog->show();
    });


    //学生管理
    connect(studentButton,&QPushButton::clicked,this,[this,rightLayOut]()
    {
        if(tableWidget!=nullptr)
        {
            tableWidget->setParent(nullptr);
            rightLayOut->removeWidget(tableWidget);
            delete tableWidget;
            tableWidget=nullptr;
        }
        tableWidget=new StudentTable;
        rightLayOut->addWidget(tableWidget);
    });

    //教师管理
    connect(teacherButton,&QPushButton::clicked,this,[this,rightLayOut]()
    {
        if(tableWidget!=nullptr)
        {
            tableWidget->setParent(nullptr);
            rightLayOut->removeWidget(tableWidget);
            delete tableWidget;
            tableWidget=nullptr;
        }
        tableWidget=new TeacherTable;//update
        rightLayOut->addWidget(tableWidget);

    });

    //课程管理
    connect(classButton,&QPushButton::clicked,this,[this,rightLayOut]()
    {
        if(tableWidget!=nullptr)
        {
            tableWidget->setParent(nullptr);
            rightLayOut->removeWidget(tableWidget);
            delete tableWidget;
            tableWidget=nullptr;
        }
        tableWidget=new ClassTable;//update
        rightLayOut->addWidget(tableWidget);
    });
}
