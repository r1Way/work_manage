#include "LabelEdit.h"

LabelEdit::LabelEdit(QWidget *parent)
    : QWidget{parent}
{
    //main layout
    mainLayout=new QVBoxLayout(this);

    //up
    upWidget=new QWidget;
    mainLayout->addWidget(upWidget);

    upLayout = new QHBoxLayout;
    upWidget->setLayout(upLayout);
    upWidget->setFixedHeight(30); // 设置高度为30像素
    label=new QLabel;
    upWidget->setStyleSheet("QWidget{"
                         "color: white;"
                         "background-color: #989898;"
                         "font: bold 14px;"         // 字体为粗体，大小为14px
                         "padding: 0px;"            // 内边距为5像素
                         "margin: 0px;"            // 外边距为10像素
                         "border-top-left-radius: 10px;" // 左上角圆角为10像素
                         "border-top-right-radius: 10px;" // 右上角圆角为10像素
                         "}");
    upLayout->addWidget(label);

    //down
    // text=new QPlainTextEdit;
    // text->setStyleSheet("QPlainTextEdit{"
    //                         "font: bold 14px;"         // 字体为粗体，大小为14px
    //                         "padding: 5px;"            // 内边距为5像素
    //                         "margin: 0px;"            // 外边距为10像素
    //                         "background-color:  white;"
    //                         "}");
    // mainLayout->addWidget(text);
    mainLayout->setSpacing(0);
}

void LabelEdit::setText(QString text)
{
    this->label->setText(text);
}

void LabelEdit::addDown(QWidget *widget)
{
    this->mainLayout->addWidget(widget);
}

void LabelEdit::addUp(QWidget *widget)
{
    this->upLayout->addWidget(widget);
}
