#include "HeadWidget.h"

HeadWidget::HeadWidget(QWidget *parent)
    : QWidget{parent}
{
    // this->setStyleSheet("QWidget {background-color: #61d4df; }");
    //调节大小
    QFont *font=new QFont;
    font->setPointSize(25);

    //update
    QLabel* systemName=new QLabel("c++作业管理系统");
    systemName->setFont(*font);

    QLabel *avatar = new QLabel(this);
    QPixmap pix("://img/identity");
    avatar->setPixmap(pix.scaled(50, 50, Qt::KeepAspectRatio));


    QLabel* userName=new QLabel;
    font->setPointSize(20);
    userName->setFont(*font);
    if(::user_identity=="admin")
    {
        userName->setText("管理员");
    }
    else
    {
        QSqlQuery query;
        QString sql=QString("SELECT name FROM %1 "
                              "WHERE %2_id=%3;").arg(::user_identity).arg(::user_identity).arg(::user_account);
        query.exec(sql);
        while(query.next())
        {
            userName->setText(query.value(0).toString());
        }
    }


    //设置布局
    QHBoxLayout *layOut=new QHBoxLayout(this);
    layOut->addWidget(systemName);
    layOut->addStretch();
    layOut->addWidget(avatar);
    layOut->addWidget(userName);
}
