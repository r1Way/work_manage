#include "StudentMainwindow.h"

StudentMainwindow::StudentMainwindow(QWidget *parent)
    : QMainWindow{parent}
{
    // ///////////////////////////////layer1///////////////////////////
    //全屏
    this->showMaximized();
    this->setWindowFlags(Qt::Dialog|Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);


    // 创建中心小部件
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    //central layout
    QVBoxLayout * mainLayout=new QVBoxLayout(centralWidget);

    //kid widget
    HeadWidget *headWidget=new HeadWidget();
    mainLayout->addWidget(headWidget);

    //table
    QStackedWidget *stackedWidget =new QStackedWidget;
    mainLayout->addWidget(stackedWidget);
    QStringList list1={"课程代号","课程名称","教师","描述"};
    tableWindow=new TableWindow(list1);
    tableWindow->connectDataBase("select * from class");
    stackedWidget->addWidget(tableWindow);

    //选择班级
    connect(tableWindow->tableWidget,&QTableWidget::itemDoubleClicked,[this,stackedWidget](QTableWidgetItem *item){itemDoubleClicked(item,stackedWidget);});
}

void StudentMainwindow::itemDoubleClicked(QTableWidgetItem *item, QStackedWidget *stackedWidget)
{
    QStringList list2={"学号","姓名","专业"};//update

    TableWindow *tableWindow2=new TableWindow(list2);
    tableWindow2->connectDataBase("select *from student");
    stackedWidget->addWidget(tableWindow2);
    stackedWidget->setCurrentIndex(1);

    //left layout
    QPushButton *returnBtn=new QPushButton("返回");
    connect(returnBtn,&QPushButton::clicked,[stackedWidget](){stackedWidget->setCurrentIndex(0);});
    tableWindow2->leftLayout->addWidget(returnBtn);
    QTextEdit *textEdit=new QTextEdit;
    textEdit->setText("<b>班级</b>：09132班<br> <b>上课时间</b>：星期四2~3节");
    tableWindow2->leftLayout->addWidget(textEdit);

    //search layout
    QPushButton *batchBtn=new QPushButton("批量管理");
    tableWindow2->searchLayout->insertWidget(0,batchBtn);
    QPushButton *assignBtn=new QPushButton("布置作业");
    tableWindow2->searchLayout->insertWidget(0,assignBtn);

    //double clicked
    connect(tableWindow2->tableWidget,&QTableWidget::itemDoubleClicked,[this,stackedWidget](QTableWidgetItem *item){homeworkDoubleClicked(item,stackedWidget);});
}

void StudentMainwindow::homeworkDoubleClicked(QTableWidgetItem *item, QStackedWidget *stackedWidget)
{
    FileWindow *fileWindow=new FileWindow;
    stackedWidget->addWidget(fileWindow);
    stackedWidget->setCurrentIndex(2);
    connect(fileWindow->returnBtn,&QPushButton::clicked,[stackedWidget](){stackedWidget->setCurrentIndex(1);});

}
