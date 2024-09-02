#ifndef LABELEDIT_H
#define LABELEDIT_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>

class LabelEdit : public QWidget
{
    Q_OBJECT
public:
    QVBoxLayout * mainLayout;
    QHBoxLayout * upLayout;
    QWidget *upWidget;
    QLabel *label;
    explicit LabelEdit(QWidget *parent = nullptr);
    void setText(QString text);
    void addDown(QWidget * widget);
    void addUp(QWidget *widget);
signals:
};

#endif // LABELEDIT_H
