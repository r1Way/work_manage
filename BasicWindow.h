#ifndef BASICWINDOW_H
#define BASICWINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLayout>
#include <QPushButton>
#include <QSplitter>
class BasicWindow:public QWidget
{
    Q_OBJECT
public:
    BasicWindow(QWidget *parent=nullptr);
    QVBoxLayout *leftLayout;
    QWidget *leftWidget;
    QSplitter *leftSplitter;
    QVBoxLayout *rightLayout;
    QWidget *rightWidget;
    QSplitter *mainSplitter;
    QHBoxLayout *searchLayout;
    void addSearchLayoutBtn(QPushButton *btn);
};

#endif // BASICWINDOW_H
