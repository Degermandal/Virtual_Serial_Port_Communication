#-------------------------------------------------
#
# Project created by QtCreator 2019-04-19T15:00:04
#
#-------------------------------------------------
QT += widgets serialport
requires(qtConfig(combobox))

TARGET = Qt_Serio
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

CPPREST_PATH = /usr/local/Cellar/cpprestsdk/2.10.8
BOOST_PATH = /usr/local/Cellar/boost/1.68.0_1
OPENSSL_PATH = /usr/local/opt/openssl/

INCLUDEPATH += $${CPPREST_PATH}/include/
INCLUDEPATH += $${BOOST_PATH}/include/
INCLUDEPATH += $${OPENSSL_PATH}/include/
INCLUDEPATH += $$PWD/../Server
INCLUDEPATH += $$PWD/

SOURCES += \
        adapter.cpp \
        main.cpp \
        mainwindow.cpp \
        myserver.cpp \
        timeoutserial.cpp \
        ../Server/TLV.cpp

HEADERS += \
        adapter.h \
        mainwindow.h \
        myserver.h \
        timeoutserial.h

LIBS += "-L$${BOOST_PATH}/lib/" -lboost_system -lboost_thread-mt -lboost_chrono
LIBS += "-L$${CPPREST_PATH}/lib/" -lcpprest
LIBS += "-L$${OPENSSL_PATH}/lib/" -lssl -lcrypto

DISTFILES += \
    config.txt

