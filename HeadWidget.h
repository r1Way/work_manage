#ifndef HEADWIDGET_H
#define HEADWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFont>
#include <QSqlQuery>
extern QString user_account;
extern QString user_identity;
class HeadWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HeadWidget(QWidget *parent = nullptr);

signals:
};

#endif // HEADWIDGET_H
