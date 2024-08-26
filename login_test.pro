QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    StudentTable.cpp \
    TeacherTable.cpp \
    admin.cpp \
    adminmainwindow.cpp \
    headwidget.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    myTableWidget.cpp \
    teachermainwindow.cpp

HEADERS += \
    StudentTable.h \
    TeacherTable.h \
    admin.h \
    adminmainwindow.h \
    headwidget.h \
    login.h \
    mainwindow.h \
    myTableWidget.h \
    teachermainwindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    login_test_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
