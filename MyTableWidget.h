#ifndef MYTABLEWIDGET_H
#define MYTABLEWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>
#include <QCheckBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMenu>
#include <QAction>
#include <QPoint>
class MyTableWidget:public QWidget
{
public:
    MyTableWidget();
    QFont * font;//字体

    QHBoxLayout * searchLayOut;

    QPushButton *add;
    QPushButton *batch;

    QLineEdit *searchEdit;
    QPushButton *searchBtn;

    QTableWidget * tableWidget;
    QScrollArea *scrollArea;
    QPushButton *ensureBatch;
    void search(const QString &keyword);

public slots:
    void showContextMenu(const QPoint &pos);
};

#endif // MYTABLEWIDGET_H
