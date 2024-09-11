QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AdminMainwindow.cpp \
    BasicWindow.cpp \
    ClassTable.cpp \
    CodeEditor.cpp \
    FileWindow.cpp \
    HeadWidget.cpp \
    Highlighter.cpp \
    LabelEdit.cpp \
    Login.cpp \
    MyTableWidget.cpp \
    StudentMainwindow.cpp \
    StudentTable.cpp \
    TableWindow.cpp \
    TeacherMainwindow.cpp \
    TeacherTable.cpp \
    main.cpp

HEADERS += \
    AdminMainwindow.h \
    BasicWindow.h \
    ClassTable.h \
    CodeEditor.h \
    FileWindow.h \
    HeadWidget.h \
    Highlighter.h \
    LabelEdit.h \
    Login.h \
    MyTableWidget.h \
    StudentMainwindow.h \
    StudentTable.h \
    TableWindow.h \
    TeacherMainwindow.h \
    TeacherTable.h

FORMS +=

TRANSLATIONS += \
    login_test_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../build-login_test-Desktop_Qt_6_7_0_MinGW_64_bit-Debug/debug/resource.qrc
