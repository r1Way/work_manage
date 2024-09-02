#include "TeacherMainwindow.h"

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
    QVBoxLayout * mainLayout=new QVBoxLayout(centralWidget);

    //kid widget
    HeadWidget *headWidget=new HeadWidget();
    mainLayout->addWidget(headWidget);

    //table
    QStackedWidget *stackedWidget =new QStackedWidget;
    mainLayout->addWidget(stackedWidget);
    QStringList list={"课程代号","课程名称","描述"};
    tableWindow=new TableWindow(list);
    tableWindow->mainSplitter->setSizes(QList<int>() <<1<<10000);
    // qDebug()<<"front"<<user_account<<"back";//check
    QString sql=QString("SELECT class.class_id,class.name,class.description from class "
                          "JOIN class_teacher ON class.class_id=class_teacher.class_id "
                          "WHERE class_teacher.teacher_id=%1;").arg(user_account.toInt());
    tableWindow->connectDataBase(sql);
    stackedWidget->addWidget(tableWindow);
    connect(tableWindow->tableWidget,&QTableWidget::itemDoubleClicked,[this,stackedWidget](QTableWidgetItem *item){itemDoubleClicked(item,stackedWidget);});


}

void TeacherMainWindow::itemDoubleClicked(QTableWidgetItem *item,QStackedWidget *stackedWidget)
{
    QFont font;
    font.setPointSize(14);
    //选择班级以后
    int row=item->row();
    QString classId=tableWindow->tableWidget->item(row,0)->text();//获取班级id
    QStringList list2={"作业名称","作业介绍","截止日期","截止时间"};
    TableWindow *tableWindow2=new TableWindow(list2);
    QString sql=QString("SELECT name,description,"
                          "d,t FROM homework_class "
                          "WHERE class_id=%1;").arg(classId);
    tableWindow2->connectDataBase(sql);
    stackedWidget->addWidget(tableWindow2);
    stackedWidget->setCurrentIndex(1);

    //left layout

    QPushButton *returnBtn=new QPushButton("返回");
    returnBtn->setFont(font);

    connect(returnBtn,&QPushButton::clicked,[stackedWidget,tableWindow2]()
    {
        stackedWidget->setCurrentIndex(0);
        //还需要释放内存，并从stackedWidget上取出第二页
        stackedWidget->removeWidget(tableWindow2);
        tableWindow2->deleteLater();
    });
    tableWindow2->leftLayout->addWidget(returnBtn);
    QTextEdit *textEdit=new QTextEdit;
    LabelEdit *labelEdit=new LabelEdit;
    labelEdit->mainLayout->addWidget(textEdit);
    labelEdit->label->setText("基本信息");

    QSqlQuery query;//获取班级名
    query.exec(QString("SELECT name,description FROM class WHERE class_id=%1").arg(classId));
    QString className;
    QString description;
    while(query.next())
    {
        className=query.value(0).toString();
        description=query.value(1).toString();
    }
    textEdit->setText(QString("<b>班级</b>：%1<br> <b>描述</b>：%2").arg(className).arg(description));
    tableWindow2->leftLayout->addWidget(labelEdit);

    //search layout
    //批量删除batchBtn
    QPushButton *batchBtn=new QPushButton("批量删除");
    batchBtn->setFont(font);
    tableWindow2->searchLayout->insertWidget(0,batchBtn);

    connect(batchBtn,&QPushButton::clicked,this,[tableWindow2,this,batchBtn,classId,font]()
    {

        int cols=tableWindow2->tableWidget->columnCount();//未添加复选框时的列数

        if(batchBtn->text()=="批量删除")//批量删除功能
        {
            //复选框配置
            tableWindow2->tableWidget->insertColumn(cols);//增加新的一列
            ensureBatch=new QPushButton("确认删除");
            ensureBatch->setFont(font);

            for (int i = 0; i < tableWindow2->tableWidget->rowCount(); ++i)
            {
                //在最后一列添加复选框
                QCheckBox *checkBox = new QCheckBox();
                tableWindow2->tableWidget->setCellWidget(i, cols, checkBox);
            }
            //取消批量管理, 确认删除按钮配置
            batchBtn->setText("取消批量删除");

            tableWindow2->searchLayout->insertWidget(2,ensureBatch);
            QFont font=ensureBatch->font();
            font.setPointSize(14);
            ensureBatch->setFont(font);

            connect(ensureBatch,&QPushButton::clicked,[cols,tableWindow2,batchBtn,classId]()
            {
                for (int i = tableWindow2->tableWidget->rowCount() - 1; i >= 0; --i)
                {
                    QCheckBox *checkBox = qobject_cast<QCheckBox*>(tableWindow2->tableWidget->cellWidget(i, cols));
                    if (checkBox && checkBox->isChecked())
                    {
                        QSqlQuery query_remove;
                        QString workName=tableWindow2->tableWidget->takeItem(i,0)->text();
                        //tableWidget中删除
                        tableWindow2->tableWidget->removeRow(i);
                        //sql中删除
                        QString sql=QString("delete from homework_class where class_id=%1 and name='%2';").arg(classId.toInt()).arg(workName);
                        query_remove.exec(sql);

                        emit batchBtn->clicked();
                    }
                }
            });
        }
        else
        {
            //取消批量删除
            batchBtn->setText("批量删除");
            ensureBatch->setParent(this);
            tableWindow2->searchLayout->removeWidget(ensureBatch);
            delete ensureBatch;

            //删除复选框
            tableWindow2->tableWidget->removeColumn(cols-1);
        }
        //设置列的大小调整模式以填充表格的宽度
        tableWindow2->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    });

    QPushButton *assignBtn=new QPushButton("布置作业");
    assignBtn->setFont(font);
    tableWindow2->searchLayout->insertWidget(0,assignBtn);
    connect(assignBtn,&QPushButton::clicked,[this,classId,tableWindow2](){assignHomework(classId,tableWindow2);});

    //双击作业double clicked
    connect(tableWindow2->tableWidget,&QTableWidget::itemDoubleClicked,[className,classId,tableWindow2,this,stackedWidget](QTableWidgetItem *item)
    {
        int row=item->row();
        QString homeworkName=tableWindow2->tableWidget->item(row,0)->text();
        homeworkDoubleClicked(classId,homeworkName,stackedWidget,tableWindow2);
    });


}

void TeacherMainWindow::homeworkDoubleClicked(QString classId,QString homeworkName, QStackedWidget *stackedWidget,TableWindow *tableWindow2)
{
    QFont font;
    font.setPointSize(14);
    //选择了是哪次作业以后,显示学生的提交记录
    //界面切换
    QStringList list3={"学号","姓名","提交日期","提交时间","分数"};
    TableWindow *tableWindow3=new TableWindow(list3);
    QString sql=QString("SELECT homework_student.student_id,student.name,homework_student.d,"
                          "homework_student.t,homework_student.score "
                          "FROM homework_student "
                          "JOIN student ON homework_student.student_id = student.student_id "
                          "WHERE homework_student.class_id=%1 and "
                          "homework_student.name='%2';").arg(classId).arg(homeworkName);
    tableWindow3->connectDataBase(sql);
    stackedWidget->addWidget(tableWindow3);
    stackedWidget->setCurrentIndex(2);

    //left layout
    QPushButton *returnBtn=new QPushButton("返回");
    returnBtn->setFont(font);
    tableWindow3->leftLayout->addWidget(returnBtn);
    connect(returnBtn,&QPushButton::clicked,[stackedWidget,tableWindow3]()
    {
        stackedWidget->setCurrentIndex(1);
        stackedWidget->removeWidget(tableWindow3);
        tableWindow3->deleteLater();
    });

    LabelEdit *labelEdit=new LabelEdit;
    labelEdit->label->setText("基本信息");
    QTextEdit *textEdit=new QTextEdit;
    labelEdit->mainLayout->addWidget(textEdit);
    textEdit->setText("<b>班级</b>：09132班<br> <b>上课时间</b>：星期四2~3节<br> <b>作业</b>：Ex01");
    tableWindow3->leftLayout->addWidget(labelEdit);

    //search layout
    //添加测试样例
    QPushButton *exampleBtn=new QPushButton("添加测试样例");
    exampleBtn->setFont(font);
    tableWindow3->searchLayout->insertWidget(0,exampleBtn);
    connect(exampleBtn,&QPushButton::clicked,[this,classId,homeworkName](){addExample(classId,homeworkName);});

    //选择了查看哪位学生的作业 double clicked
    connect(tableWindow3->tableWidget,&QTableWidget::itemDoubleClicked,[tableWindow3,classId,homeworkName,this,stackedWidget](QTableWidgetItem *item)
    {
        int row=item->row();
        QString studentId=tableWindow3->tableWidget->item(row,0)->text();
        QString studentName=tableWindow3->tableWidget->item(row,1)->text();
        studentDoubleClicked(studentName,studentId,classId,homeworkName,stackedWidget,tableWindow3);
    });
}

void TeacherMainWindow::studentDoubleClicked(QString studentName,QString studentId,QString classId,QString homeworkName,QStackedWidget *stackedWidget,TableWindow *tableWindow3)
{
    QFont font;
    font.setPointSize(14);
    //选择了打开哪位学生的作业
    FileWindow *fileWindow=new FileWindow;
    stackedWidget->addWidget(fileWindow);
    stackedWidget->setCurrentIndex(3);
    fileWindow->import(PATH+QString("/%1/%2/%3").arg(classId).arg(homeworkName).arg(studentId));

    //left layout
    //介绍
    LabelEdit *labelEditIntro=new LabelEdit;
    labelEditIntro->label->setText("基本信息");

    QTextEdit *textEdit=new QTextEdit;
    labelEditIntro->mainLayout->addWidget(textEdit);
    textEdit->setText(QString("<b>班级</b>：%1<br> <b>作业</b>：%2 <br><b>学生</b>：%3").arg(classId).arg(homeworkName).arg(studentName));
    fileWindow->leftSplitter->addWidget(labelEditIntro);

    //分数栏
    QWidget *scoreWidget=new QWidget;
    QHBoxLayout *scoreLayout=new QHBoxLayout(scoreWidget);
    QLabel *score=new QLabel("分数");
    QLineEdit *scoreEdit=new QLineEdit;
    QPushButton *ensureScore=new QPushButton("确定");
    QFont temp=ensureScore->font();
    temp.setPointSize(11);
    ensureScore->setFont(temp);
    scoreLayout->addWidget(score);
    scoreLayout->addWidget(scoreEdit);
    scoreLayout->addWidget(ensureScore);
    fileWindow->leftSplitter->addWidget(scoreWidget);
    // fileWindow->leftLayout->insertLayout(2,scoreLayout);
    connect(ensureScore,&QPushButton::clicked,[studentId,classId,homeworkName,scoreEdit]()
    {
        int score=scoreEdit->text().toInt();
        QSqlQuery query;
        QString sql=QString("UPDATE homework_student "
                              "SET score=%1 "
                              "WHERE student_id=%2 and "
                              "class_id=%3 and "
                              "name='%4';").arg(score).arg(studentId).arg(classId).arg(homeworkName);
        query.exec(sql);
    });


    //测试样例
    //读入
    LabelEdit *labelEditInput=new LabelEdit;
    QFont fontInput;
    fontInput.setPointSize(12);
    labelEditInput->label->setText("样例输入");
    QPlainTextEdit *exampleEdit=new QPlainTextEdit;
    exampleEdit->setFont(fontInput);
    labelEditInput->mainLayout->addWidget(exampleEdit);
    fileWindow->leftSplitter->addWidget(labelEditInput);
    QString fileName=PATH+QString("/%1/%2/example.txt").arg(classId).arg(homeworkName);
    if (!QFile::exists(fileName))
    {
        qDebug()<<"file not exist";
        QFile file(fileName);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        out << ""; // 写入文本
        file.close();//创建txt文件
    }
    QFile file(fileName);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&file);
    QString argument=in.readAll();//读入的参数
    exampleEdit->setPlainText(argument);
    file.close();
    QPushButton *resetBtn=new QPushButton;//重置测试样例
    resetBtn->setIcon(QIcon("://img/reset.png"));
    resetBtn->setStyleSheet("QPushButton {"
                             "background-color: #eeeeee;"
                            "}"
                            "QPushButton:hover "
                            "{"
                            "background-color: #cdcdcd ;" /* 鼠标悬停时的背景颜色 */
                            "}"
                            "QPushButton:pressed {"
                            "background-color: #a9a9a9;" /* 按下时的背景颜色 */
                            "}");
    resetBtn->setFixedSize(20,20);
    connect(resetBtn,&QPushButton::clicked,[argument,exampleEdit]()
    {
        exampleEdit->setPlainText(argument);
    });
    labelEditInput->addUp(resetBtn);

    //process对话框
    //编译运行
    QPushButton *compile=new QPushButton("编译运行");
    compile->setToolTip("F5");
    compile->setFont(font);
    fileWindow->searchLayout->addWidget(compile);
    QString filePath=PATH+QString("/%1/%2/%3").arg(classId).arg(homeworkName).arg(studentId);

    //输出框
    LabelEdit *labelEditOutput=new LabelEdit;
    labelEditOutput->label->setText("程序输出信息");
    CodeEditor *outputEdit=new CodeEditor;
    labelEditOutput->mainLayout->addWidget(outputEdit);
    fileWindow->leftSplitter->addWidget(labelEditOutput);
    compile->setShortcut(QKeySequence("F5"));
    connect(compile,&QPushButton::clicked,[this,filePath,exampleEdit,outputEdit]()
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

        process->start(filePath+"/main.exe");
        QString argument=exampleEdit->toPlainText();
        process->write(argument.toUtf8().constData());
        process->closeWriteChannel(); // 关闭写通道，表示输入结束
        if (!process->waitForFinished())
        { // 等待程序执行完成
        qDebug() << "Execution failed:" << process->errorString();
        }

        QByteArray output = process->readAllStandardOutput(); // 读取标准输出
        QByteArray errorOutput = process->readAllStandardError(); // 读取错误输出
        outputEdit->appendPlainText(QString::fromUtf8(output));
        qDebug() << "Output:" << output;

        if (!errorOutput.isEmpty())
        {
            qDebug() << "Error Output:" << errorOutput;
        }
    });


    //返回
    connect(fileWindow->returnBtn,&QPushButton::clicked,[stackedWidget,fileWindow,tableWindow3]()
    {
        stackedWidget->setCurrentIndex(2);
        stackedWidget->removeWidget(fileWindow);
        fileWindow->deleteLater();
        tableWindow3->fresh();
    });

}

void TeacherMainWindow::assignHomework(QString classId,TableWindow *tableWindow2)
{
    QDialog *dialog=new QDialog;
    QVBoxLayout *mainLayout=new QVBoxLayout;
    dialog->setLayout(mainLayout);

    QVector<QHBoxLayout* > layouts;
    for(int i=0;i<4;i++)//modify
    {
        QHBoxLayout *layout = new QHBoxLayout;
        layouts.push_back(layout);
        mainLayout->addLayout(layouts[i]);
    }

    QLabel *name=new QLabel("作业名");
    QLineEdit * nameEdit=new QLineEdit;
    layouts[0]->addWidget(name);
    layouts[0]->addWidget(nameEdit);

    QLabel *description=new QLabel("描述");
    QLineEdit *descriptionEdit=new QLineEdit;
    layouts[1]->addWidget(description);
    layouts[1]->addWidget(descriptionEdit);

    QLabel *date=new QLabel("截止日期");
    QDateEdit *dateEdit=new QDateEdit;
    layouts[2]->addWidget(date);
    layouts[2]->addWidget(dateEdit);

    QLabel *time =new QLabel("截止时间");
    QTimeEdit *timeEdit=new QTimeEdit;
    layouts[3]->addWidget(time);
    layouts[3]->addWidget(timeEdit);

    QPushButton *ensure=new QPushButton("确认");
    mainLayout->addWidget(ensure);
    connect(ensure,&QPushButton::clicked,[this,nameEdit,descriptionEdit,dateEdit,timeEdit,classId,dialog,tableWindow2]()
    {
        //qDebug()<<classId<<dateEdit->date().toString("yyyy-MM-dd")<<"   "<<timeEdit->time().toString("HH:mm:ss");
        //添加到表
        addHomework(classId,nameEdit->text(),descriptionEdit->text(),dateEdit->date().toString("yyyy-MM-dd"),timeEdit->time().toString("HH:mm:ss"),tableWindow2);
        //添加到数据库
        QSqlQuery query;
        QString sql=QString("INSERT INTO homework_class value(%1,'%2','%3','%4','%5')")
                          .arg(classId)
                          .arg(nameEdit->text())
                          .arg(descriptionEdit->text())
                          .arg(dateEdit->date().toString("yyyy-MM-dd"))
                          .arg(timeEdit->time().toString("HH:mm:ss"));
        query.exec(sql);
        dialog->close();
        //创建文件夹
        QDir dir(PATH+"/"+classId);
        if(!dir.exists(nameEdit->text()))
        {
            dir.mkdir(nameEdit->text());
        }
    });
    dialog->show();
}

void TeacherMainWindow::addHomework(QString classId, QString name, QString description, QString date, QString time,TableWindow *tableWindow2)
{
    int row = tableWindow2->tableWidget->rowCount();
    tableWindow2->tableWidget->insertRow(row);
    tableWindow2->tableWidget->setItem(row, 0, new QTableWidgetItem(name));
    tableWindow2->tableWidget->setItem(row, 1, new QTableWidgetItem(description));
    tableWindow2->tableWidget->setItem(row, 2, new QTableWidgetItem(date));
    tableWindow2->tableWidget->setItem(row, 3, new QTableWidgetItem(time));
}

void TeacherMainWindow::addExample(QString classId, QString homeworkName)
{
    QDialog *dialog=new QDialog;
    QVBoxLayout *mainLayout=new QVBoxLayout;
    dialog->setLayout(mainLayout);
    QString fileName=PATH+QString("/%1/%2/example.txt").arg(classId).arg(homeworkName);

    QLabel *label=new QLabel("请输入测试样例");
    mainLayout->addWidget(label);

    //写入
    QPlainTextEdit *exampleEdit=new QPlainTextEdit;
    mainLayout->addWidget(exampleEdit);
    if (!QFile::exists(fileName))
    {
        qDebug()<<"file not exist";
        QFile file(fileName);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        out << ""; // 写入文本
        file.close();//创建txt文件
    }

    //读入
    QFile file(fileName);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&file);
    exampleEdit->setPlainText(in.readAll());
    file.close();

    //写出
    QPushButton *save=new QPushButton("保存");
    mainLayout->addWidget(save);
    connect(save,&QPushButton::clicked,[fileName,exampleEdit,dialog]()
    {
        QFile file(fileName);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        out<<exampleEdit->toPlainText();
        file.close();
        dialog->close();
    });
    dialog->show();
}


