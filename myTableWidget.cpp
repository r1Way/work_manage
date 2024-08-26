#include "myTableWidget.h"

myTableWidget::myTableWidget(){
    //font
    font=new QFont;
    font->setPointSize(14);

    //main layout
    QVBoxLayout *mainLayout=new QVBoxLayout();
    this->setLayout(mainLayout);

    //widget
    add=new QPushButton("增加");
    add->setFont(*font);

    batch=new QPushButton("批量删除");
    batch->setFont(*font);

    QSpacerItem *spacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

    searchEdit=new QLineEdit;
    searchEdit->setPlaceholderText("输入姓名、学号或专业进行搜索...");
    searchEdit->setFont(*font);
    connect(searchEdit,&QLineEdit::returnPressed,this,[this](){searchBtn->click();});//搜索框内回车与搜索键绑定

    searchBtn=new QPushButton("搜索");
    searchBtn->setFont(*font);

    //searchLayOut
    searchLayOut=new QHBoxLayout;
    mainLayout->addLayout(searchLayOut);
    searchLayOut->addWidget(add);
    searchLayOut->addWidget(batch);
    searchLayOut->addSpacerItem(spacer);
    searchLayOut->addWidget(searchEdit);
    searchLayOut->addWidget(searchBtn);


    //table
    tableWidget = new QTableWidget;
    mainLayout->addWidget(tableWidget);//挂在layout上
    tableWidget->setSortingEnabled(true);// 启用表头的排序功能
    font->setPointSize(13);
    tableWidget->setFont(*font);

    //滚轮条
    scrollArea = new QScrollArea;
    scrollArea->setWidget(tableWidget);
    scrollArea->setWidgetResizable(true); // 让 QTableWidget 随着 QScrollArea 的大小变化
    mainLayout->addWidget(scrollArea);

    //各btn与table connect


    //鼠标右键菜单栏
    // 在你的类的构造函数中或者初始化UI函数中
    tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(tableWidget, &QTableWidget::customContextMenuRequested, this, &myTableWidget::showContextMenu);
}

void myTableWidget::search(const QString &keyword)
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

void myTableWidget::showContextMenu(const QPoint &pos)
{
    // 为了在选中行时弹出菜单，你可以使用下面的代码
    QMenu contextMenu(tr("Context menu"), this);
    //update
    QAction action1("修改此项", this);
    connect(&action1, &QAction::triggered, this, [](){qDebug()<<"modify";});
    contextMenu.addAction(&action1);

    QAction action2("删除", this);
    connect(&action2, &QAction::triggered, this, [](){qDebug()<<"deleteRow";});
    contextMenu.addAction(&action2);

    QAction action3("修改此行",this);
    connect(&action3, &QAction::triggered, this, [](){qDebug()<<"deleteRow";});
    contextMenu.addAction(&action3);

    contextMenu.exec(tableWidget->mapToGlobal(pos));
}

