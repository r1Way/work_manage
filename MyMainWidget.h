#ifndef MYMAINWIDGET_H
#define MYMAINWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLayout>
#include "MyTableWidget.h"
class MyMainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyMainWidget(QWidget *parent = nullptr);
    QLayout *leftLayout;
private:
    MyTableWidget *tableWidget;
signals:

};

#endif // MYMAINWIDGET_H
