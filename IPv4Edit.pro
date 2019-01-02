CONFIG      += widgets plugin debug_and_release
TARGET      = $$qtLibraryTarget(ipv4editplugin)
TEMPLATE    = lib

HEADERS     = ipv4editplugin.h
SOURCES     = ipv4editplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. \
                -L/usr/lib/x86_64-linux-gnu


greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer core gui widgets network
} else {
    CONFIG += designer 
    QT += network
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(ipv4edit.pri)

