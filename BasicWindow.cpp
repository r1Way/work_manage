#include "BasicWindow.h"

BasicWindow::BasicWindow(QWidget *parent):QWidget(parent)
{
    //主要布局
    QHBoxLayout *mainLayout=new QHBoxLayout;
    this->setLayout(mainLayout);
    mainSplitter=new QSplitter(Qt::Horizontal);
    mainLayout->addWidget(mainSplitter);


    //left layout
    leftSplitter=new QSplitter(Qt::Vertical);
    mainSplitter->addWidget(leftSplitter);
    leftWidget=new QWidget;
    leftSplitter->addWidget(leftWidget);
    leftLayout=new  QVBoxLayout;
    leftWidget->setLayout(leftLayout);


    //right layout
    rightWidget=new QWidget;
    mainSplitter->addWidget(rightWidget);
    rightLayout=new QVBoxLayout;
    rightWidget->setLayout(rightLayout);

    //search layout
    searchLayout=new QHBoxLayout;
    rightLayout->addLayout(searchLayout);

    //splitter
    // 设置部件的初始大小
    mainSplitter->setSizes(QList<int>() << 15000 << 70000);
}

void BasicWindow::addSearchLayoutBtn(QPushButton *btn)
{
    searchLayout->addWidget(btn);
}
