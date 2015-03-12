
VERSION = 0.1.0
TARGET = yasem-web-gui-plugin
TEMPLATE = lib

include($${top_srcdir}/common.pri)

GONFIG -= gui

DEFINES += WEBGUI_LIBRARY

DISTFILES += \
    gui/index.html \
    gui/html/main.html \
    gui/html/profiles.html \
    metadata.json

SOURCES += \
    webguiplugin.cpp \
    guiconfigprofile.cpp \
    guistbobject.cpp \
    webguipluginobject.cpp \
    $${CORE_ROOT_DIR}/stbpluginobject.cpp

HEADERS += \
    webguiplugin.h \
    guiconfigprofile.h \
    guistbobject.h \
    $${CORE_ROOT_DIR}/stbpluginobject.h \
    $${CORE_ROOT_DIR}/browserpluginobject.h \
    webguipluginobject.h

OTHER_FILES += \
    metadata.json

GUI_SRC_DIR = $$PWD/gui
GUI_DEST_DIR = $$OUT_DIR/gui

win32:GUI_SRC_DIR ~= s,/,\\,g
win32:GUI_DEST_DIR ~= s,/,\\,g

# Copy all GUI files (html, js, css etc.) into gui subfolder
copydata.commands = $(COPY_DIR) $$GUI_SRC_DIR $$GUI_DEST_DIR
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

