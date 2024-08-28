#include <QApplication>
#include "StudentMainwindow.h"
#include "BasicWindow.h"
#include "FileWindow.h"
#include "HeadWidget.h"
#include "Highlighter.h"
#include "TableWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StudentMainwindow w;
    w.show();
    return a.exec();
}
