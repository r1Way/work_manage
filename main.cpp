#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QLineEdit>
#include <QWidget>
#include <QVBoxLayout>
#include "login.h"
#include "headwidget.h"
#include "adminmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QT 装载中文
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "login_test_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    AdminMainWindow w;
    w.show();

    return a.exec();
}
