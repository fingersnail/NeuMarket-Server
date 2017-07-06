#-------------------------------------------------
#
# Project created by QtCreator 2017-06-26T15:47:22
#
#-------------------------------------------------

QT       += core gui
QT += network
QT += sql
CONFIG += c++11
LIBS += -LC:\Users\Kevin\Desktop\server\qjson\bin -llibqjson-qt5
INCLUDEPATH += C:\Users\Kevin\Desktop\server\qjson\include\qjson-qt5

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NeuMarketServer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    serverthread.cpp \
    server.cpp \
    module/abstractmodule.cpp \
    module/loginmodule.cpp \
    module/personnelmanagementmodule.cpp \
    module/purchasemanagementmodule.cpp \
    module/salesmanagementmodule.cpp \
    module/stockmanagementmodule.cpp \
    module/systemmanagementmodule.cpp \
    entity/abstractobject.cpp \
    entity/employee.cpp \
    entity/loginuser.cpp \
    entity/product.cpp \
    entity/purchaserecord.cpp \
    entity/salesrecord.cpp \
    entity/supplier.cpp \
    entity/user.cpp \
    util/databasemediator.cpp \
    util/utilities.cpp \
    entity/productkindstatistic.cpp \
    entity/saleskindstatistic.cpp \
    entity/salesmonthstatistic.cpp \
    entity/userdetail.cpp

HEADERS += \
        widget.h \
    serverthread.h \
    server.h \
    module/abstractmodule.h \
    module/loginmodule.h \
    module/personnelmanagementmodule.h \
    module/purchasemanagementmodule.h \
    module/salesmanagementmodule.h \
    module/stockmanagementmodule.h \
    module/systemmanagementmodule.h \
    entity/abstractobject.h \
    entity/employee.h \
    entity/loginuser.h \
    entity/product.h \
    entity/purchaserecord.h \
    entity/salesrecord.h \
    entity/supplier.h \
    entity/user.h \
    util/databasemediator.h \
    util/utilities.h \
    entity/productkindstatistic.h \
    entity/saleskindstatistic.h \
    entity/salesmonthstatistic.h \
    entity/userdetail.h

FORMS += \
        widget.ui

DISTFILES += \
    supermarket.db
