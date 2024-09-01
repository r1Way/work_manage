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
    tableWindow->mainSplitter->setSizes(QList<int>() <<1<<10000);
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
    QString filePath=PATH+QString("/%1/%2/%3").arg(classId).arg(homeworkName).arg(user_account);
    fileWindow->import(filePath);
    stackedWidget->setCurrentIndex(2);

    //返回
    connect(fileWindow->returnBtn,&QPushButton::clicked,[stackedWidget,fileWindow]()
    {
        stackedWidget->setCurrentIndex(1);
        stackedWidget->removeWidget(fileWindow);
        fileWindow->deleteLater();
    });

    //search layout
    //提交作业
    QPushButton *handInHomework=new QPushButton("提交作业");
    fileWindow->searchLayout->insertWidget(0,handInHomework);
    connect(handInHomework,&QPushButton::clicked,[this,classId,homeworkName]()
    {
        handIn(classId,homeworkName);
    });

    //search layout
    //编译运行
    QPushButton *compile=new QPushButton("编译运行");
    fileWindow->searchLayout->addWidget(compile);
    connect(compile,&QPushButton::clicked,[this,filePath]()
    {
        QDir directory(filePath);
        QStringList fileAll = directory.entryList(QDir::Files);
        QStringList fileCompile;
        for(auto fileName:fileAll)
        {
            if(fileName.contains(".cpp"))
            {
                fileCompile.push_back(fileName);
            }
        }
        QProcess * process=new QProcess(this);
        // 切换目录
        process->setWorkingDirectory(filePath);
        // 启动 g++ 命令
        process->start("g++", QStringList()<<fileCompile<<"-o"<<"main");

        if (!process->waitForFinished()) {
            qDebug() << "Failed to execute g++ command.";
            qDebug() << process->errorString(); // 输出错误信息
        }
        else
        {
            // 输出命令执行结果和错误信息
            qDebug() << process->readAllStandardOutput();
            qDebug() << process->readAllStandardError();
        }

        QStringList arguments;
        // arguments << "2";  // 这里替换为你需要传递的参数
        process->start(filePath+"/main.exe");
        // process->write(QString::number(2).toUtf8() + "\n");
        process->write("3\n6\n");
        // process->closeWriteChannel(); // 关闭写通道，表示输入结束
        if (!process->waitForFinished())
        { // 等待程序执行完成
        qDebug() << "Execution failed:" << process->errorString();
        return 1;
        }

        QByteArray output = process->readAllStandardOutput(); // 读取标准输出
        QByteArray errorOutput = process->readAllStandardError(); // 读取错误输出

        qDebug() << "Output:" << output;
        if (!errorOutput.isEmpty())
        {
            qDebug() << "Error Output:" << errorOutput;
        }
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

    if(fileNames.size()!=0)//如果提交了文件
    {
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
        // qDebug()<<fileName;
        QFileInfo srcFileInfo(fileName);
        QFile::copy(fileName, destPath+"/"+srcFileInfo.fileName());
        }

        QString date=QDate::currentDate().toString("yyyy-MM-dd");
        QString time=QTime::currentTime().toString("HH:mm:ss");

        QSqlQuery query;
        //检查是否已经提交
        QString check=QString("SELECT count(*) FROM homework_student "
                    "WHERE student_id=%1 and "
                    "class_id=%2 and "
                    "name='%3';").arg(user_account).arg(classId).arg(homeworkName);
        int nums=-1;
        query.exec(check);
        if(query.next())
        {
        nums=query.value(0).toString().toInt();
        qDebug()<<"nums="<<nums;
        }

        if(nums==0)//未曾提交
        {
        QString sql=QString("INSERT INTO homework_student(student_id,class_id,name,d,t) value(%1,%2,'%3','%4','%5');")
              .arg(user_account).arg(classId).arg(homeworkName).arg(date).arg(time);
        query.exec(sql);
        }
        else//曾提交
        {
        QString sql=QString("UPDATE homework_student SET d='%1' ,t='%2' "
                      "WHERE student_id=%3 and "
                      "class_id=%4 and "
                      "name='%5';").arg(date).arg(time).arg(user_account).arg(classId).arg(homeworkName);
        query.exec(sql);
        }
    }
    else{}//如果没有提交文件
}
