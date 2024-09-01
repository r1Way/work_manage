#ifndef FILEWINDOW_H
#define FILEWINDOW_H
#include <QPushButton>
#include <QWidget>
#include <QTextEdit>
#include <QTabWidget>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDir>
#include <QPlainTextEdit>
#include <QWheelEvent>
#include "BasicWindow.h"
#include "Highlighter.h"
#include "CodeEditor.h"
class FileWindow:public BasicWindow
{
public:
    FileWindow();
    bool import(QString path);
    QTabWidget *tabWidget;
    Highlighter * highlighter;
    QPushButton *returnBtn;
signals:
    void wheelAll(QWheelEvent *e,CodeEditor *codeEdit);
};

#endif // FILEWINDOW_H
