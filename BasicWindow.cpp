#include "BasicWindow.h"

BasicWindow::BasicWindow(QWidget *parent):QWidget(parent)
{
    //主要布局
    QHBoxLayout *mainLayout=new QHBoxLayout;
    this->setLayout(mainLayout);

    //left layout
    leftLayout=new  QVBoxLayout;
    mainLayout->addLayout(leftLayout);

    //right layout
    rightLayout=new QVBoxLayout;
    mainLayout->addLayout(rightLayout);

    //search layout
    searchLayout=new QHBoxLayout;
    rightLayout->addLayout(searchLayout);
}

void BasicWindow::addSearchLayoutBtn(QPushButton *btn)
{
    searchLayout->addWidget(btn);
}
