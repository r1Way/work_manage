#ifndef BASICWINDOW_H
#define BASICWINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLayout>
#include <QPushButton>
class BasicWindow:public QWidget
{
    Q_OBJECT
public:
    BasicWindow(QWidget *parent=nullptr);
    QVBoxLayout *leftLayout;
    QVBoxLayout *rightLayout;
    QHBoxLayout *searchLayout;
    void addSearchLayoutBtn(QPushButton *btn);
};

#endif // BASICWINDOW_H
