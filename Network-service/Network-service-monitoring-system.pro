QT       += core gui network widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialog_config.cpp \
    dialog_function.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    dialog_config.h \
    dialog_function.h \
    mainwindow.h

FORMS += \
    dialog_config.ui \
    dialog_function.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    printtest.py

INCLUDEPATH += E:\dev\anaconda3\envs\py3109\include

LIBS += -LE:\dev\anaconda3\envs\py3109\libs -lpython310
