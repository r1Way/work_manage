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
#include "BasicWindow.h"
#include "Highlighter.h"
class FileWindow:public BasicWindow
{
public:
    FileWindow();
    QTabWidget *tabWidget;
    Highlighter * highlighter;
    QPushButton *returnBtn;

};

#endif // FILEWINDOW_H
