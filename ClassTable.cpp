#include "ClassTable.h"

ClassTable::ClassTable()
{

    tableWidget->setColumnCount(3);  // 设置列数为3
    tableWidget->setHorizontalHeaderLabels({ "课程编号","课程名称", "课程描述"});
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 添加数据
    QSqlQuery query("SELECT * FROM class");
    while (query.next())
    {
        addClass(query.value("class_id").toString(),query.value("name").toString(),query.value("description").toString());
    }

    // 连接搜索按钮点击信号到槽函数
    connect(searchBtn, &QPushButton::clicked, [this]{
        search(searchEdit->text());
    });

    //searchEdit
    searchEdit->setPlaceholderText("输入课程编号，名称，描述以筛选");

    //鼠标右键菜单
    connect(tableWidget, &QTableWidget::customContextMenuRequested, this, &ClassTable::showContextMenu);

    //addBtn的槽
    connect(add,&QPushButton::clicked,[this]()
            {
                //font
                QFont *font=new QFont;
                font->setPointSize(13);
                QDialog *dialog=new QDialog();
                dialog->setWindowIcon(QIcon("://img/icopng"));
                //title
                dialog->setWindowTitle("添加课程");

                //main layout
                QVBoxLayout *dialogMainLayout=new QVBoxLayout;
                dialog->setLayout(dialogMainLayout);

                //课程名称
                QHBoxLayout *layout1=new QHBoxLayout;
                QLabel * name=new QLabel("课程名称");
                QLineEdit *nameEdit=new QLineEdit;
                name->setFont(*font);
                layout1->addWidget(name);
                layout1->addWidget(nameEdit);

                //课程编号
                QHBoxLayout *layout2=new QHBoxLayout;
                QLabel *id=new QLabel("课程编号");
                QLineEdit *idEdit=new QLineEdit;
                idEdit->setValidator(new QIntValidator(idEdit));
                id->setFont(*font);
                layout2->addWidget(id);
                layout2->addWidget(idEdit);

                //描述
                QHBoxLayout *layout3=new QHBoxLayout;
                QLabel *desc=new QLabel("描述");
                QLineEdit *descEdit=new QLineEdit;
                desc->setFont(*font);
                layout3->addWidget(desc);
                layout3->addWidget(descEdit);

                dialogMainLayout->addLayout(layout1);
                dialogMainLayout->addLayout(layout2);
                dialogMainLayout->addLayout(layout3);

                //确定
                QPushButton *ensureAdd=new QPushButton("确定");
                ensureAdd->setFont(*font);
                dialogMainLayout->addWidget(ensureAdd);


                connect(ensureAdd,&QPushButton::clicked,[this,idEdit,nameEdit,descEdit,dialog]()
                        {
                            if(nameEdit->text()!=""&&idEdit->text()!="")
                            {
                                QSqlQuery queryAdd;
                                queryAdd.exec(QString("SELECT COUNT(*) FROM class "
                                                      "WHERE class_id=%1").arg(idEdit->text()));
                                int nums=-1;
                                while(queryAdd.next())
                                {
                                    nums=queryAdd.value(0).toInt();
                                }
                                if(nums==0)
                                {
                                    QString sql=QString("insert into class(class_id,name,description) value(%1,'%2','%3')").arg(idEdit->text()).arg(nameEdit->text()).arg(descEdit->text());
                                    this->addClass(idEdit->text(),nameEdit->text(),descEdit->text());
                                    queryAdd.exec(sql);
                                    dialog->close();
                                    //创建文件夹
                                    QDir dir(PATH);
                                    if(!dir.exists(idEdit->text()))
                                    {
                                        dir.mkdir(idEdit->text());
                                    }
                                }
                                else
                                {
                                    QMessageBox messageBox;
                                    messageBox.setWindowIcon(QIcon("://img/icopng"));
                                    messageBox.setWindowTitle("输入验证");
                                    messageBox.setText("该课程代号已存在,请重新输入。");
                                    messageBox.setIcon(QMessageBox::Warning);
                                    messageBox.setStandardButtons(QMessageBox::Ok);
                                    messageBox.exec();
                                }
                            }
                            else
                            {
                                // 创建一个 QMessageBox 对象
                                QMessageBox messageBox;
                                messageBox.setWindowIcon(QIcon("://img/icopng"));
                                messageBox.setWindowTitle("填写验证");
                                messageBox.setText("信息填写不完整，请继续填写。");
                                messageBox.setIcon(QMessageBox::Warning);
                                messageBox.setStandardButtons(QMessageBox::Ok);
                                messageBox.exec();
                            }
                        });

                dialog->show();

            });

    //batchBtn的槽
    connect(batch,&QPushButton::clicked,[this]()
            {
                int cols=tableWidget->columnCount();//未添加复选框时的列数

                if(batch->text()=="批量删除")//批量删除功能
                {
                    //复选框配置
                    tableWidget->insertColumn(cols);//增加新的一列

                    for (int i = 0; i < tableWidget->rowCount(); ++i)
                    {
                        //在最后一列添加复选框
                        QCheckBox *checkBox = new QCheckBox();
                        tableWidget->setCellWidget(i, cols, checkBox);
                    }

                    //取消批量管理, 确认删除按钮配置
                    this->batch->setText("取消批量管理");

                    ensureBatch=new QPushButton("确认删除");
                    QFont font=ensureBatch->font();
                    font.setPointSize(14);
                    ensureBatch->setFont(font);

                    this->searchLayOut->insertWidget(2,ensureBatch);

                    connect(ensureBatch,&QPushButton::clicked,[this,cols]()
                            {
                                for (int i = tableWidget->rowCount() - 1; i >= 0; --i)
                                {
                                    QCheckBox *checkBox = qobject_cast<QCheckBox*>(tableWidget->cellWidget(i, cols));
                                    if (checkBox && checkBox->isChecked())
                                    {
                                        QSqlQuery query_remove;
                                        QString id=tableWidget->takeItem(i,0)->text();
                                        //tableWidget中删除
                                        tableWidget->removeRow(i);
                                        //sql中删除
                                        QString sql=QString("delete from class where class_id=%1;").arg(id.toInt());
                                        query_remove.exec(sql);
                                        emit batch->clicked();
                                    }
                                }
                            });

                }
                else
                {
                    //取消批量删除
                    this->batch->setText("批量删除");
                    ensureBatch->setParent(this);
                    searchLayOut->removeWidget(ensureBatch);
                    delete ensureBatch;

                    //删除复选框
                    tableWidget->removeColumn(cols-1);
                }

            });
}

void ClassTable::addClass(QString id, QString name, QString description)
{
    int row = tableWidget->rowCount();
    tableWidget->insertRow(row);
    tableWidget->setItem(row, 0, new QTableWidgetItem(id));
    tableWidget->setItem(row, 1, new QTableWidgetItem(name));
    tableWidget->setItem(row, 2, new QTableWidgetItem(description));
}

void ClassTable::showContextMenu(const QPoint &pos)
{
    //菜单栏
    QTableWidgetItem *item=tableWidget->itemAt(pos);
    if(item!=nullptr)
    {
            int row=item->row();
        QMenu contextMenu(tr("Context menu"), this);
        qDebug()<<"ClassTable::showContextMenu: row="<<row;

        //action1 删除此行
        QAction * action1=new QAction("删除此行", this);
        connect(action1, &QAction::triggered, this, [this,row]()
            {
            // 创建一个确认删除的对话框
            QMessageBox msgBox;
            msgBox.setWindowIcon(QIcon("://img/icopng"));
            msgBox.setWindowTitle("删除确认");
            msgBox.setText("确定删除此课程？");

            QPushButton *confirmButton = msgBox.addButton("确认", QMessageBox::YesRole);
            QPushButton *cancelButton = msgBox.addButton("取消", QMessageBox::NoRole);
            msgBox.exec();

                // 判断用户点击了哪个按钮
                if (msgBox.clickedButton() == confirmButton)
                {
                    QSqlQuery query_remove;
                    QString classId=tableWidget->item(row,0)->text();
                    //tableWidget中删除
                    tableWidget->removeRow(row);
                    //sql中删除
                    QString sql=QString("delete from class where class_id=%1;").arg(classId.toInt());
                    query_remove.exec(sql);

                    //删除文件夹
                    QDir dir(PATH+QString("/%1").arg(classId));
                    dir.removeRecursively();
                }
                else if (msgBox.clickedButton() == cancelButton)
                {

                }

            });
        contextMenu.addAction(action1);

        QMenu *addMenu=new QMenu("添加");
        contextMenu.addMenu(addMenu);


        //action2 添加学生
        QAction *action2=new QAction("添加学生",this);
        addMenu->addAction(action2);
        connect(action2,&QAction::triggered,this,[this, row]()
        {
        QDialog *dialog=new QDialog;
        dialog->setWindowIcon(QIcon("://img/icopng"));
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        QVBoxLayout *layout=new QVBoxLayout;
        dialog->setLayout(layout);
        dialog->setWindowTitle("添加学生至课程");
        QLabel *label=new QLabel("学号");
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        layout->addWidget(label);
        QLineEdit *edit=new QLineEdit;
        layout->addWidget(edit);
        edit->setValidator(new QIntValidator(edit));
        edit->setPlaceholderText("请输入学生学号");
        edit->setFont(font);
        QPushButton *ensure=new QPushButton("确认");
        layout->addWidget(ensure);

            connect(ensure,&QPushButton::clicked,[this,edit,row,dialog]()
            {
                if(edit->text()!="")
                {
                    QSqlQuery query;
                    query.exec(QString("SELECT count(*) FROM student "
                                       "WHERE student.student_id=%1").arg(edit->text()));
                    int nums=-1;
                    while(query.next())
                    {
                        nums=query.value(0).toInt();
                    }
                    if(nums!=0)
                    {
                        query.exec(QString("INSERT INTO class_student value(%1,%2)").arg(tableWidget->itemAt(row,0)->text().toInt()).arg(edit->text().toInt()));
                        dialog->close();
                        QMessageBox messageBox;
                        messageBox.setWindowIcon(QIcon("://img/icopng"));
                        messageBox.setWindowTitle("输入验证");
                        messageBox.setText("添加学生成功。");
                        messageBox.setIcon(QMessageBox::Warning);
                        messageBox.setStandardButtons(QMessageBox::Ok);
                        messageBox.exec();
                    }
                    else
                    {
                        QMessageBox messageBox;
                        messageBox.setWindowIcon(QIcon("://img/icopng"));
                        messageBox.setWindowTitle("输入验证");
                        messageBox.setText("不存在此学号，请重新输入。");
                        messageBox.setIcon(QMessageBox::Warning);
                        messageBox.setStandardButtons(QMessageBox::Ok);
                        messageBox.exec();
                    }
                }
                else
                {
                    // 创建一个 QMessageBox 对象
                    QMessageBox messageBox;

                    // 设置消息框的标题
                    messageBox.setWindowTitle("输入验证");

                    // 设置消息框显示的文本
                    messageBox.setText("输入为空，请重新输入。");

                    // 设置消息框的图标类型
                    messageBox.setIcon(QMessageBox::Warning);

                    // 设置消息框的标准按钮
                    messageBox.setStandardButtons(QMessageBox::Ok);

                    messageBox.setWindowIcon(QIcon("://img/icopng"));
                    // 显示消息框
                    messageBox.exec();
                }
            });
        dialog->show();
        });

        //添加教师
        QAction *action3=new QAction("添加教师",this);
        addMenu->addAction(action3);
        connect(action3,&QAction::triggered,this,[this, row]()
            {
            QDialog *dialog=new QDialog;
            dialog->setWindowIcon(QIcon("://img/icopng"));
            dialog->setAttribute(Qt::WA_DeleteOnClose);
            QVBoxLayout *layout=new QVBoxLayout;
            dialog->setLayout(layout);
            dialog->setWindowTitle("添加教师至课程");
            QLabel *label=new QLabel("工号");
            QFont font;
            font.setPointSize(12);
            label->setFont(font);
            layout->addWidget(label);
            QLineEdit *edit=new QLineEdit;
            edit->setFont(font);
            layout->addWidget(edit);
            edit->setPlaceholderText("请输入教师工号");
            edit->setValidator(new QIntValidator(edit));
            QPushButton *ensure=new QPushButton("确认");
            layout->addWidget(ensure);
            connect(ensure,&QPushButton::clicked,[this,edit,row,dialog]()
                {
                    if(edit->text()!="")
                    {
                        // qDebug()<<"ClassTable::showContextMenu: connect"<<tableWidget->item(row,0)->text();
                        QSqlQuery query;
                        query.exec(QString("SELECT count(*) FROM teacher "
                                           "WHERE teacher.teacher_id=%1").arg(edit->text()));
                        int nums=-1;
                        while(query.next())
                        {
                            nums=query.value(0).toInt();
                        }
                        if(nums!=0)
                        {
                            query.exec(QString("INSERT INTO class_teacher value(%1,%2)").arg(tableWidget->item(row,0)->text().toInt()).arg(edit->text().toInt()));
                            dialog->close();
                            QMessageBox messageBox;
                            messageBox.setWindowIcon(QIcon("://img/icopng"));
                            messageBox.setWindowTitle("输入验证");
                            messageBox.setText("添加教师成功。");
                            messageBox.setIcon(QMessageBox::Warning);
                            messageBox.setStandardButtons(QMessageBox::Ok);
                            messageBox.exec();
                        }
                        else
                        {
                            QMessageBox messageBox;
                            messageBox.setWindowIcon(QIcon("://img/icopng"));
                            messageBox.setWindowTitle("输入验证");
                            messageBox.setText("不存在此工号，请重新输入。");
                            messageBox.setIcon(QMessageBox::Warning);
                            messageBox.setStandardButtons(QMessageBox::Ok);
                            messageBox.exec();
                        }
                    }
                    else
                    {
                        // 创建一个 QMessageBox 对象
                        QMessageBox messageBox;

                        // 设置消息框的标题
                        messageBox.setWindowTitle("输入验证");

                        // 设置消息框显示的文本
                        messageBox.setText("输入为空，请重新输入。");

                        // 设置消息框的图标类型
                        messageBox.setIcon(QMessageBox::Warning);

                        // 设置消息框的标准按钮
                        messageBox.setStandardButtons(QMessageBox::Ok);

                        messageBox.setWindowIcon(QIcon("://img/icopng"));
                        // 显示消息框
                        messageBox.exec();
                    }
                });
             dialog->show();
            });

        QMenu *partMenu=new QMenu("查看组成");
        contextMenu.addMenu(partMenu);

        //教师组成
        QAction *action4=new QAction("教师组成",this);
        connect(action4,&QAction::triggered,[this,row]()
        {
            QString classId=tableWidget->item(row,0)->text();
            QStringList list1={"工号","姓名","专业"};
            TableWindow *tableWindow1=new TableWindow(list1);//显示教师
            tableWindow1->setWindowIcon(QIcon("://img/icopng"));
            QString sql=QString("SELECT teacher.teacher_id,teacher.name,teacher.major FROM teacher "
                                  "JOIN class_teacher ON class_teacher.teacher_id=teacher.teacher_id "
                                  "WHERE class_teacher.class_id=%1").arg(classId);
            tableWindow1->connectDataBase(sql);
            tableWindow1->mainSplitter->setSizes(QList<int>() <<0<<10000);
            tableWindow1->show();
        });
        partMenu->addAction(action4);

        //学生组成
        QAction *action5=new QAction("学生组成",this);
        connect(action5,&QAction::triggered,[this,row]()
        {
            QString classId=tableWidget->item(row,0)->text();
            QStringList list1={"学号","姓名","专业"};
            TableWindow *tableWindow1=new TableWindow(list1);//显示学生
            tableWindow1->setWindowIcon(QIcon("://img/icopng"));
            QString sql=QString("SELECT student.student_id,student.name,student.major FROM student "
                                  "JOIN class_student ON class_student.student_id=student.student_id "
                                  "WHERE class_student.class_id=%1").arg(classId);
            tableWindow1->connectDataBase(sql);
            tableWindow1->mainSplitter->setSizes(QList<int>() <<0<<10000);
            tableWindow1->show();
        });
        partMenu->addAction(action5);

        QMenu *removeMenu=new QMenu("删除");
        contextMenu.addMenu(removeMenu);

        QAction *action6=new QAction("删除教师");
        removeMenu->addAction(action6);
        connect(action6,&QAction::triggered,[]()
               {
                QDialog *dialog=new QDialog;
                dialog->setWindowIcon(QIcon("://img/icopng"));
                dialog->setAttribute(Qt::WA_DeleteOnClose);
                QVBoxLayout *layout=new QVBoxLayout;
                dialog->setLayout(layout);
                dialog->setWindowTitle("从课程删除教师");
                QLabel *label=new QLabel("工号");
                layout->addWidget(label);
                QLineEdit *edit=new QLineEdit;
                edit->setValidator(new QIntValidator(edit));
                layout->addWidget(edit);
                edit->setPlaceholderText("请输入教师工号");
                QPushButton *ensure=new QPushButton("确认");
                layout->addWidget(ensure);

                connect(ensure,&QPushButton::clicked,[edit,dialog]()
                {
                    QSqlQuery query;
                    query.exec(QString("SELECT COUNT(*) FROM class_teacher "
                                        "WHERE class_teacher.teacher_id=%1").arg(edit->text().toInt()));
                    int nums=-1;
                    while(query.next())
                    {
                        nums=query.value(0).toInt();
                    }
                    if(nums!=0)
                    {

                        query.exec(QString("DELETE FROM class_teacher WHERE class_teacher.teacher_id=%1").arg(edit->text().toInt()));

                        QMessageBox messageBox;
                        messageBox.setWindowIcon(QIcon("://img/icopng"));
                        messageBox.setWindowTitle("删除验证");
                        messageBox.setText("删除成功");
                        messageBox.setIcon(QMessageBox::Warning);
                        messageBox.setStandardButtons(QMessageBox::Ok);
                        messageBox.exec();
                        dialog->close();
                    }
                    else if(nums==0)
                    {
                        QMessageBox messageBox;
                        messageBox.setWindowIcon(QIcon("://img/icopng"));
                        messageBox.setWindowTitle("删除验证");
                        messageBox.setText("不存在该教师，删除失败,请重新输入。");
                        messageBox.setIcon(QMessageBox::Warning);
                        messageBox.setStandardButtons(QMessageBox::Ok);
                        messageBox.exec();
                    }
                });
                dialog->show();

        });

        QAction *action7=new QAction("删除学生");
        removeMenu->addAction(action7);
        connect(action7,&QAction::triggered,[]()
                {
                    QDialog *dialog=new QDialog;
                    dialog->setWindowIcon(QIcon("://img/icopng"));
                    dialog->setAttribute(Qt::WA_DeleteOnClose);
                    QVBoxLayout *layout=new QVBoxLayout;
                    dialog->setLayout(layout);
                    dialog->setWindowTitle("从课程删除学生");
                    QLabel *label=new QLabel("学号");
                    layout->addWidget(label);
                    QLineEdit *edit=new QLineEdit;
                    edit->setValidator(new QIntValidator(edit));
                    layout->addWidget(edit);
                    edit->setPlaceholderText("请输入学生学号");
                    QPushButton *ensure=new QPushButton("确认");
                    layout->addWidget(ensure);

                    connect(ensure,&QPushButton::clicked,[edit,dialog]()
                            {
                                QSqlQuery query;
                                query.exec(QString("SELECT COUNT(*) FROM class_student "
                                           "WHERE class_student.student_id=%1").arg(edit->text().toInt()));
                                int nums=-1;
                                while(query.next())
                                {
                                    nums=query.value(0).toInt();
                                }
                                if(nums!=0)
                                {
                                    query.exec(QString("DELETE FROM class_student WHERE class_student.student_id=%1").arg(edit->text().toInt()));

                                    QMessageBox messageBox;
                                    messageBox.setWindowIcon(QIcon("://img/icopng"));
                                    messageBox.setWindowTitle("删除验证");
                                    messageBox.setText("删除成功");
                                    messageBox.setIcon(QMessageBox::Warning);
                                    messageBox.setStandardButtons(QMessageBox::Ok);
                                    messageBox.exec();
                                    dialog->close();
                                }
                                else if(nums==0)
                                {
                                    QMessageBox messageBox;
                                    messageBox.setWindowIcon(QIcon("://img/icopng"));
                                    messageBox.setWindowTitle("删除验证");
                                    messageBox.setText("不存在该学生，删除失败,请重新输入。");
                                    messageBox.setIcon(QMessageBox::Warning);
                                    messageBox.setStandardButtons(QMessageBox::Ok);
                                    messageBox.exec();
                                }
                            });
                    dialog->show();

                });

        QAction *action8=new QAction("修改此行",this);
        connect(action8,&QAction::triggered,this,[this,row]()
                {
                    QDialog *dialog=new QDialog;
                    QVBoxLayout *mainLayout=new QVBoxLayout;
                    dialog->setLayout(mainLayout);
                    QString idRow=this->tableWidget->item(row,0)->text();
                    QString nameRow=this->tableWidget->item(row,1)->text();
                    QString descRow=this->tableWidget->item(row,2)->text();

                    QFont font;
                    font.setPointSize(12);
                    //姓名
                    QHBoxLayout *layout1=new QHBoxLayout;
                    QLabel * name=new QLabel("姓名");
                    QLineEdit *nameEdit=new QLineEdit;
                    nameEdit->setText(nameRow);
                    name->setFont(font);
                    layout1->addWidget(name);
                    layout1->addWidget(nameEdit);

                    //描述
                    QHBoxLayout *layout3=new QHBoxLayout;
                    QLabel *desc=new QLabel("专业");
                    QLineEdit *descEdit=new QLineEdit;
                    descEdit->setText(descRow);
                    desc->setFont(font);
                    layout3->addWidget(desc);
                    layout3->addWidget(descEdit);

                    mainLayout->addLayout(layout1);
                    mainLayout->addLayout(layout3);

                    QPushButton *ensure=new QPushButton("保存");
                    mainLayout->addWidget(ensure);

                    connect(ensure,&QPushButton::clicked,this,[this,dialog,idRow,nameEdit,descEdit,row](){
                        QSqlQuery query;
                        query.exec(QString("UPDATE class "
                                           "SET name='%1',description='%2' "
                                           "WHERE class_id=%3").arg(nameEdit->text()).arg(descEdit->text()).arg(idRow));
                        QMessageBox messageBox;
                        messageBox.setWindowIcon(QIcon("://img/icopng"));
                        messageBox.setWindowTitle("编辑验证");
                        messageBox.setText("保存成功。");
                        messageBox.setIcon(QMessageBox::Warning);
                        messageBox.setStandardButtons(QMessageBox::Ok);
                        messageBox.exec();
                        this->tableWidget->item(row,1)->setText(nameEdit->text());
                        this->tableWidget->item(row,2)->setText(descEdit->text());
                        dialog->close();
                    });

                    dialog->show();
                });
        contextMenu.addAction(action8);

        contextMenu.exec(tableWidget->mapToGlobal(pos));
    }

}
