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
class myTableWidget:public QWidget
{
public:
    myTableWidget();
protected:
    QFont * font;
    QPushButton *add;
    QPushButton *batch;
    QLineEdit *searchEdit;
    QPushButton *searchBtn;
    QHBoxLayout * searchLayOut;
    QTableWidget * tableWidget;
    QScrollArea *scrollArea;
    QPushButton *ensureBatch;
    void search(const QString &keyword);
};

#endif // MYTABLEWIDGET_H
