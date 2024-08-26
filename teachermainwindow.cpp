#include "teachermainwindow.h"

TeacherMainWindow::TeacherMainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    //全屏
    this->showMaximized();
    this->setWindowFlags(Qt::Dialog|Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);


    // 创建中心小部件
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    //central layout
    QVBoxLayout *mainLayOut=new QVBoxLayout(centralWidget);

    //kid widget
    HeadWidget *headWidget=new HeadWidget();

    //kid layout
    QHBoxLayout *downLayOut=new QHBoxLayout();
    QStackedLayout * stackedLayout
    QVBoxLayout *leftLayout1=new QVBoxLayout();
    QVBoxLayout *leftLayout2=new QVBoxLayout();
    QVBoxLayout *rightLayout=new QVBoxLayout();


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

    // //rightLayOut
    // tableWidget=new StudentTable;
    // rightLayOut->addWidget(tableWidget);


    // //学生管理
    // connect(studentButton,&QPushButton::clicked,this,[this,rightLayOut]()
    //         {
    //             if(tableWidget!=nullptr)
    //             {
    //                 tableWidget->setParent(nullptr);
    //                 rightLayOut->removeWidget(tableWidget);
    //                 delete tableWidget;
    //                 tableWidget=nullptr;
    //             }
    //             tableWidget=new StudentTable;
    //             rightLayOut->addWidget(tableWidget);
    //         });

    // //教师管理
    // connect(teacherButton,&QPushButton::clicked,this,[this,rightLayOut]()
    //         {
    //             if(tableWidget!=nullptr)
    //             {
    //                 tableWidget->setParent(nullptr);
    //                 rightLayOut->removeWidget(tableWidget);
    //                 delete tableWidget;
    //                 tableWidget=nullptr;
    //             }
    //             tableWidget=new TeacherTable;//update
    //             rightLayOut->addWidget(tableWidget);

    //         });

    // //课程管理
    // connect(classButton,&QPushButton::clicked,this,[this,rightLayOut]()
    //         {
    //             if(tableWidget!=nullptr)
    //             {
    //                 tableWidget->setParent(nullptr);
    //                 rightLayOut->removeWidget(tableWidget);
    //                 delete tableWidget;
    //                 tableWidget=nullptr;
    //             }
    //             tableWidget=new myTableWidget;//update
    //             rightLayOut->addWidget(tableWidget);
    //         });
}
