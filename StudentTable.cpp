#include "StudentTable.h"

StudentTable::StudentTable():MyTableWidget()
{

    tableWidget->setColumnCount(3);  // 设置列数为3
    information={ "学号","姓名", "专业"};
    tableWidget->setHorizontalHeaderLabels(information);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 添加数据
    QSqlQuery query("SELECT * FROM student");
    while (query.next())
    {
        addStudent(query.value("student_id").toString(),query.value("name").toString(),query.value("major").toString());
    }

    // 连接搜索按钮点击信号到槽函数
    connect(searchBtn, &QPushButton::clicked, [this]{
        search(searchEdit->text());
    });

    //鼠标右键菜单
    connect(tableWidget, &QTableWidget::customContextMenuRequested, this, &StudentTable::showContextMenu);


    //addBtn的槽
    connect(add,&QPushButton::clicked,[this]()
            {
                //font
                QFont *font=new QFont;
                font->setPointSize(13);
                QDialog *dialog=new QDialog();

                //title
                dialog->setWindowTitle("添加学生");

                //main layout
                QVBoxLayout *dialogMainLayout=new QVBoxLayout;
                dialog->setLayout(dialogMainLayout);

                //姓名
                QHBoxLayout *layout1=new QHBoxLayout;
                QLabel * name=new QLabel("姓名");
                QLineEdit *nameEdit=new QLineEdit;
                name->setFont(*font);
                layout1->addWidget(name);
                layout1->addWidget(nameEdit);

                //学号
                QHBoxLayout *layout2=new QHBoxLayout;
                QLabel *stuNum=new QLabel("学号");
                QLineEdit *stuNumEdit=new QLineEdit;
                stuNum->setFont(*font);
                layout2->addWidget(stuNum);
                layout2->addWidget(stuNumEdit);

                //专业
                QHBoxLayout *layout3=new QHBoxLayout;
                QLabel *major=new QLabel("专业");
                QLineEdit *majorEdit=new QLineEdit;
                major->setFont(*font);
                layout3->addWidget(major);
                layout3->addWidget(majorEdit);

                dialogMainLayout->addLayout(layout1);
                dialogMainLayout->addLayout(layout2);
                dialogMainLayout->addLayout(layout3);

                //确定
                QPushButton *ensureAdd=new QPushButton("确定");
                ensureAdd->setFont(*font);
                dialogMainLayout->addWidget(ensureAdd);


                connect(ensureAdd,&QPushButton::clicked,[this,nameEdit,stuNumEdit,majorEdit,dialog]()
                {
                    this->addStudent(stuNumEdit->text(),nameEdit->text(),majorEdit->text());
                    QString sql=QString("insert into student(student_id,name,major) value('%1','%2','%3')").arg(stuNumEdit->text()).arg(nameEdit->text()).arg(majorEdit->text());
                    QSqlQuery queryAdd;
                    queryAdd.exec(sql);
                    dialog->close();

                    QSqlQuery query(QString("SELECT count(*) FROM pass where user='student' and id=%1").arg(stuNumEdit->text().toInt()));
                    while (query.next())
                    {
                        query.exec(QString("INSERT INTO pass value('student',%1,'8888')").arg(stuNumEdit->text().toInt()));
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
                        QString sql=QString("delete from student where student_id=%1;").arg(id.toInt());
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

void StudentTable::addStudent(const QString &id, const QString &name, const QString &major)
{
    int row = tableWidget->rowCount();
    tableWidget->insertRow(row);
    tableWidget->setItem(row, 0, new QTableWidgetItem(id));
    tableWidget->setItem(row, 1, new QTableWidgetItem(name));
    tableWidget->setItem(row, 2, new QTableWidgetItem(major));
}

void StudentTable::showContextMenu(const QPoint &pos)
{
    //菜单栏
    QMenu contextMenu(tr("Context menu"), this);

    QTableWidgetItem *item=tableWidget->itemAt(pos);
    int row=item->row();
    QAction * action1=new QAction("删除此行", this);
    connect(action1, &QAction::triggered, this, [this,row]()
    {
        QSqlQuery query_remove;
        QString id=tableWidget->takeItem(row,0)->text();
        //tableWidget中删除
        tableWidget->removeRow(row);
        //sql中删除
        QString sql=QString("delete from student where student_id=%1;").arg(id.toInt());
        query_remove.exec(sql);
    });
    contextMenu.addAction(action1);

    contextMenu.exec(tableWidget->mapToGlobal(pos));//阻塞
}

void StudentTable::editStudent(int row)
{

    QDialog *dialog=new QDialog;
    dialog->setWindowTitle("修改学生");
    QVector<QLabel*> labels;
    QVector<QLineEdit*> lineEdits;
    QVector<QHBoxLayout*> hLayouts;
    QVBoxLayout * layout=new QVBoxLayout(dialog);
    QPushButton *ensure=new QPushButton("确认");
    for(int i=0;i<information.size();i++)
    {
        labels.push_back(new QLabel(information[i]));
        lineEdits.push_back(new QLineEdit);
        hLayouts.push_back(new QHBoxLayout);
        layout->addLayout(hLayouts[i]);
        hLayouts[i]->addWidget(labels[i]);
        QTableWidgetItem *tempItem=tableWidget->itemAt(row,i);
        labels[i]->setText(tempItem->text());
        hLayouts[i]->addWidget(lineEdits[i]);
    }
    layout->addWidget(ensure);
    dialog->exec();
}
