#include "TableWindow.h"

TableWindow::TableWindow(QStringList information)
{
    //line edit
    searchEdit=new QLineEdit;
    searchLayout->addWidget(searchEdit);
    //rightLayout->addLayout(searchLayout);基类中已经实现

    //search btn
    searchBtn=new QPushButton("搜索");
    connect(searchBtn,&QPushButton::clicked,[this](){search(searchEdit->text());});
    connect(searchEdit,&QLineEdit::returnPressed,this,[this](){searchBtn->click();});//搜索框内回车与搜索键绑定
    searchLayout->addWidget(searchBtn);

    //table
    tableWidget=new QTableWidget;
    rightLayout->addWidget(tableWidget);
    tableInit(information);

    //滚轮条
    scrollArea = new QScrollArea;
    scrollArea->setWidget(tableWidget);
    scrollArea->setWidgetResizable(true); // 让 QTableWidget 随着 QScrollArea 的大小变化
    rightLayout->addWidget(scrollArea);//不可删掉这一行
}

void TableWindow::tableInit(QStringList information)
{
    this->information=information;
    tableWidget->setColumnCount(information.size());  // 设置列数
    tableWidget->setHorizontalHeaderLabels(information); //设置各列的名称
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void TableWindow::connectDataBase(QString select,QString driver,QString hostName,QString databaseName,QString userName,QString password)
{
    //赋值
    this->tableName=tableName;
    this->driver=driver;
    this->hostName=hostName;
    this->databaseName=databaseName;
    this->userName=userName;
    this->password=password;

    // 创建 ODBC 数据库对象
    db = QSqlDatabase::addDatabase(driver);
    // 设置 DSN
    db.setHostName(hostName);
    db.setDatabaseName(databaseName);
    db.setUserName(userName);
    db.setPassword(password); //用数据库实际账号密码代替
    // 打开数据库连接
    if (!db.open())
    {
        qDebug("打开数据库连接失败" );
    }
    QSqlQuery query=QSqlQuery(QString(select));
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
