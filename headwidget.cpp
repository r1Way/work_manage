#include "headwidget.h"

HeadWidget::HeadWidget(QWidget *parent)
    : QWidget{parent}
{
    //调节大小
    QFont *font=new QFont;
    font->setPointSize(25);

    //update
    QLabel* systemName=new QLabel("c++作业管理系统");
    systemName->setFont(*font);
    QLabel* userName=new QLabel("r1Way");
    font->setPointSize(20);
    userName->setFont(*font);
    QPushButton * photo=new QPushButton();


    //设置布局
    QHBoxLayout *layOut=new QHBoxLayout(this);
    layOut->addWidget(systemName);
    layOut->addStretch();
    layOut->addWidget(photo);
    layOut->addWidget(userName);
}
