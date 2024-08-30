#include "StudentMainwindow.h"

StudentMainwindow::StudentMainwindow(QWidget *parent)
    : QMainWindow{parent}
{
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
    QStringList list1={"课程代号","课程名称","描述"};
    tableWindow=new TableWindow(list1);
    tableWindow->connectDataBase(QString("SELECT class.class_id,class.name,class.description FROM class "
                                 "JOIN class_student ON class.class_id=class_student.class_id "
                                         "WHERE class_student.student_id=%1").arg(user_account));
    stackedWidget->addWidget(tableWindow);

    //选择班级
    connect(tableWindow->tableWidget,&QTableWidget::itemDoubleClicked,[this,stackedWidget](QTableWidgetItem *item)
    {
        int row=item->row();
        QString classId=tableWindow->tableWidget->item(row,0)->text();
        itemDoubleClicked(classId,stackedWidget);
    });
}

void StudentMainwindow::itemDoubleClicked(QString classId, QStackedWidget *stackedWidget)
{
    //选择完班级以后，显示作业
    QStringList list2={"作业名称","作业介绍","截止日期","截止时间"};
    TableWindow *tableWindow2=new TableWindow(list2);
    tableWindow2->connectDataBase(QString("SELECT name,description,"
                          "d,t FROM homework_class "
                          "WHERE class_id=%1;").arg(classId));
    stackedWidget->addWidget(tableWindow2);
    stackedWidget->setCurrentIndex(1);

    //left layout
    QPushButton *returnBtn=new QPushButton("返回");
    //返回
    connect(returnBtn,&QPushButton::clicked,[stackedWidget,tableWindow2]()
    {
        stackedWidget->setCurrentIndex(0);
        stackedWidget->removeWidget(tableWindow2);
        tableWindow2->deleteLater();
    });
    tableWindow2->leftLayout->addWidget(returnBtn);
    QTextEdit *textEdit=new QTextEdit;
    textEdit->setText("<b>班级</b>：09132班<br> <b>上课时间</b>：星期四2~3节");
    tableWindow2->leftLayout->addWidget(textEdit);

    //search layout

    //选择何次作业 double clicked
    connect(tableWindow2->tableWidget,&QTableWidget::itemDoubleClicked,[this,stackedWidget,classId,tableWindow2](QTableWidgetItem *item)
    {
        int row=item->row();
        QString homeworkName=tableWindow2->tableWidget->item(row,0)->text();
        homeworkDoubleClicked(classId,homeworkName,stackedWidget);
    });
}

void StudentMainwindow::homeworkDoubleClicked(QString classId,QString homeworkName, QStackedWidget *stackedWidget)
{
    //已选择是何次作业
    FileWindow *fileWindow=new FileWindow;
    stackedWidget->addWidget(fileWindow);
    fileWindow->import(PATH+QString("/%1/%2").arg(classId).arg(homeworkName));
    stackedWidget->setCurrentIndex(2);

    //返回
    connect(fileWindow->returnBtn,&QPushButton::clicked,[stackedWidget,fileWindow]()
    {
        stackedWidget->setCurrentIndex(1);
        stackedWidget->removeWidget(fileWindow);
        fileWindow->deleteLater();
    });

    QPushButton *handInHomework=new QPushButton("提交作业");
    fileWindow->searchLayout->insertWidget(0,handInHomework);
    connect(handInHomework,&QPushButton::clicked,[this,classId,homeworkName]()
    {
        handIn(classId,homeworkName);
    });
}

void StudentMainwindow::handIn(QString classId, QString homeworkName)
{
    QStringList fileNames= QFileDialog::getOpenFileNames(
        this,
        "Open Files",
        "/home",
        "C++ Files (*.cpp *.h);;Executable Files (*.exe)"
        );

    QString destPath=PATH+QString("/%1/%2/%3").arg(classId).arg(homeworkName).arg(user_account);
    qDebug()<<destPath;
    QDir dir(destPath);
    //检查目的文件夹是否存在
    if(!dir.exists())
    {
        bool success = dir.mkpath(".");
        if (!success) {
            // qDebug() << "Failed to create directory";
        } else {
            // qDebug() << "Directory created";
        }
    }

    // 获取文件夹中的所有文件，包括隐藏文件
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Hidden);
    foreach(QString dirItem, dir.entryList())
    {
        dir.remove(dirItem);
    }

    // 获取文件夹中的所有子文件夹
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
    foreach(QString dirItem, dir.entryList())
    {
        QDir subDir(dir.absoluteFilePath(dirItem));
        // 使用递归删除子文件夹
        subDir.removeRecursively();
    }

    //文件复制
    for(auto fileName:fileNames)
    {
        qDebug()<<fileName;
        QFileInfo srcFileInfo(fileName);
        QFile::copy(fileName, destPath+"/"+srcFileInfo.fileName());
    }

    QString date=QDate::currentDate().toString("yyyy-MM-dd");
    QString time=QTime::currentTime().toString("HH:mm:ss");

    QSqlQuery query;
    QString sql=QString("INSERT INTO homework_student(student_id,class_id,name,d,t) value(%1,%2,'%3','%4','%5')")
                      .arg(user_account).arg(classId).arg(homeworkName).arg(date).arg(time);
    query.exec(sql);
}
