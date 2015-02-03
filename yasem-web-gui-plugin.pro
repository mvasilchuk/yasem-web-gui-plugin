
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

OTHER_FILES += \
    metadata.json

GUI_SRC_DIR = $$PWD/gui
GUI_DEST_DIR = $$DESTDIR/../gui

win32:GUI_SRC_DIR ~= s,/,\\,g
win32:GUI_DEST_DIR ~= s,/,\\,g

# Copy all GUI files (html, js, css etc.) into gui subfolder
copydata.commands = $(COPY_DIR) $$GUI_SRC_DIR $$GUI_DEST_DIR
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

