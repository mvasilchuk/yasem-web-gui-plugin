
include(../../common.pri)

GONFIG -= gui

CONFIG += c++11

TARGET = yasem-web-gui-plugin
TEMPLATE = lib

DEFINES += WEBGUI_LIBRARY
DESTDIR = $$DEFAULT_PLUGIN_DIR

INCLUDEPATH += ../../yasem-core

DISTFILES += \
    gui/index.html \
    gui/html/main.html \
    gui/html/profiles.html \
    metadata.json

SOURCES += \
    webguiplugin.cpp \
    guiconfigprofile.cpp \
    guistbobject.cpp

HEADERS += \
    webguiplugin.h \
    guiconfigprofile.h \
    guistbobject.h

# Copy all GUI files (html, js, css etc.) into gui subfolder
copydata.commands = $(COPY_DIR) $$PWD/gui $$DESTDIR/../gui
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

OTHER_FILES += \
    metadata.json
