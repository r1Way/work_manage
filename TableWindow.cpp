#include "TableWindow.h"

TableWindow::TableWindow(QStringList information)
{
    QFont font;
    font.setPointSize(14);

    //search layout
    QSpacerItem *spacerItem=new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);
    searchLayout->addSpacerItem(spacerItem);

    //line edit
    //searchEdit
    searchEdit=new QLineEdit;
    searchEdit->setFont(font);
    searchLayout->addWidget(searchEdit);

    //search btn
    searchBtn=new QPushButton("搜索");
    searchBtn->setFont(font);
    connect(searchBtn,&QPushButton::clicked,[this](){search(searchEdit->text());});
    connect(searchEdit,&QLineEdit::returnPressed,this,[this](){searchBtn->click();});//搜索框内回车与搜索键绑定
    searchLayout->addWidget(searchBtn);

    //table
    tableWidget=new QTableWidget;
    tableWidget->setSortingEnabled(true);//启用排序功能
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//不允许编辑
    rightLayout->addWidget(tableWidget);
    tableInit(information);

    //滚轮条
    scrollArea = new QScrollArea;
    scrollArea->setWidget(tableWidget);
    scrollArea->setWidgetResizable(true); // 让 QTableWidget 随着 QScrollArea 的大小变化
    rightLayout->addWidget(scrollArea);//不可删掉这一行
}

void TableWindow::fresh()
{
    tableWidget->setRowCount(0);
    QSqlQuery query;
    query.exec(selectFresh);
    while (query.next())
    {
        QStringList list;
        for(int i=0;i<information.size();i++)
        {
            list.append(query.value(i).toString());
        }
        add(list);
    }
}



void TableWindow::tableInit(QStringList information)
{
    this->information=information;
    tableWidget->setColumnCount(information.size());  // 设置列数
    tableWidget->setHorizontalHeaderLabels(information); //设置各列的名称
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QFont font;
    font.setPointSize(13);
    tableWidget->setFont(font);
}

void TableWindow::connectDataBase(QString select,QString driver,QString hostName,QString databaseName,QString userName,QString password)
{
    //赋值
    this->selectFresh=select;
    QSqlQuery query=QSqlQuery(select);
    while (query.next())
    {
        QStringList list;
        for(int i=0;i<information.size();i++)
        {
            list.append(query.value(i).toString());
            // qDebug()<<"TableWindow::connectDataBase"<<list;
        }
        add(list);
    }
}

void TableWindow::add(QStringList list)
{
    int row=tableWidget->rowCount();
    tableWidget->insertRow(row);
    for(int i=0;i<list.size();i++)
    {
        tableWidget->setItem(row,i,new QTableWidgetItem(list[i]));
    }
}

void TableWindow::changeTable(QString select, QStringList information)
{
    closeDatabase();
    tableInit(information);
    connectDataBase(select);
}

void TableWindow::search(QString keyword)
{
    for (int i = 0; i < tableWidget->rowCount(); ++i) {
        bool match = false;
        for (int j = 0; j < tableWidget->columnCount(); ++j) {
            QTableWidgetItem *item = tableWidget->item(i, j);
            if (item->text().contains(keyword, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }
        tableWidget->setRowHidden(i, !match);
    }
}

void TableWindow::clearLeftLayout()
{
    QLayoutItem *item;
    while((item=leftLayout->takeAt(0))!=nullptr)
    {
        if(QWidget *widget=item->widget())
        {
            widget->deleteLater();
        }
    }
}

void TableWindow::closeDatabase()
{
    // db.close();
    // QSqlDatabase::removeDatabase(databaseName);
}
