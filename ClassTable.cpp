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

    //鼠标右键菜单
    connect(tableWidget, &QTableWidget::customContextMenuRequested, this, &ClassTable::showContextMenu);

    //addBtn的槽
    connect(add,&QPushButton::clicked,[this]()
            {


                //font
                QFont *font=new QFont;
                font->setPointSize(13);
                QDialog *dialog=new QDialog();

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
                            this->addClass(idEdit->text(),nameEdit->text(),descEdit->text());
                            QString sql=QString("insert into class(class_id,name,description) value(%1,'%2','%3')").arg(idEdit->text()).arg(nameEdit->text()).arg(descEdit->text());
                            QSqlQuery queryAdd;
                            queryAdd.exec(sql);
                            dialog->close();
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
    QMenu contextMenu(tr("Context menu"), this);
    QTableWidgetItem *item=tableWidget->itemAt(pos);
    int row=item->row();
    qDebug()<<"ClassTable::showContextMenu: row="<<row;

    //action1 删除此行
    QAction * action1=new QAction("删除此行", this);
    connect(action1, &QAction::triggered, this, [this,row]()
            {
                QSqlQuery query_remove;
                QString id=tableWidget->takeItem(row,0)->text();
                //tableWidget中删除
                tableWidget->removeRow(row);
                //sql中删除
                QString sql=QString("delete from class where class_id=%1;").arg(id.toInt());
                query_remove.exec(sql);
            });
    contextMenu.addAction(action1);

    //action2 添加学生
    QAction *action2=new QAction("添加学生",this);
    connect(action2,&QAction::triggered,this,[this, row]()
    {
        QDialog *dialog=new QDialog;
        QVBoxLayout *layout=new QVBoxLayout;
        dialog->setLayout(layout);
        dialog->setWindowTitle("添加学生至课程");
        QLabel *label=new QLabel("学号");
        layout->addWidget(label);
        QLineEdit *edit=new QLineEdit;
        layout->addWidget(edit);
        edit->setPlaceholderText("请输入学生学号");
        QPushButton *ensure=new QPushButton("确认");
        layout->addWidget(ensure);
        connect(ensure,&QPushButton::clicked,[this,edit,row,dialog]()
        {
            QSqlQuery query;
            query.exec(QString("INSERT INTO class_student value(%1,%2)").arg(tableWidget->itemAt(row,0)->text().toInt()).arg(edit->text().toInt()));
            dialog->close();
        });
        dialog->show();
    });
    contextMenu.addAction(action2);

    //添加教师
    QAction *action3=new QAction("添加教师",this);
    connect(action3,&QAction::triggered,this,[this, row]()
            {
                QDialog *dialog=new QDialog;
                QVBoxLayout *layout=new QVBoxLayout;
                dialog->setLayout(layout);
                dialog->setWindowTitle("添加教师至课程");
                QLabel *label=new QLabel("工号");
                layout->addWidget(label);
                QLineEdit *edit=new QLineEdit;
                layout->addWidget(edit);
                edit->setPlaceholderText("请输入教师工号");
                QPushButton *ensure=new QPushButton("确认");
                layout->addWidget(ensure);
                connect(ensure,&QPushButton::clicked,[this,edit,row,dialog]()
                        {
                            qDebug()<<"ClassTable::showContextMenu: connect"<<tableWidget->item(row,0)->text();
                            QSqlQuery query;
                            query.exec(QString("INSERT INTO class_teacher value(%1,%2)").arg(tableWidget->item(row,0)->text().toInt()).arg(edit->text().toInt()));
                            dialog->close();
                        });
                dialog->show();
            });
    contextMenu.addAction(action3);

    contextMenu.exec(tableWidget->mapToGlobal(pos));//阻塞
}
