QT       += core gui network widgets sql core5compat


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    display_label.cpp \
    end_btn.cpp \
    loghistory.cpp \
    main.cpp \
    mainwindow.cpp \
    servicemonitor.cpp \
    zsmtp.cpp

HEADERS += \
    dbconnectionpool.h \
    display_label.h \
    end_btn.h \
    loghistory.h \
    mainwindow.h \
    monitor_timer.h \
    servicemonitor.h \
    zsmtp.h

FORMS += \
    loghistory.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
