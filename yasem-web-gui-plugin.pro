
VERSION = 0.1.0
TARGET = yasem-web-gui-plugin
TEMPLATE = lib

include($${top_srcdir}/common.pri)

QT += network

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
    webguipluginobject.cpp

HEADERS += \
    webguiplugin.h \
    guiconfigprofile.h \
    guistbobject.h \
    webguipluginobject.h

OTHER_FILES += \
    metadata.json

GUI_SRC_DIR = $$PWD/gui
macx:!contains(CONFIG, NO_BUNDLE): {
    GUI_DEST_DIR = $$OUT_DIR/$${top_target_app}.app/Contents/Resources/gui
} else {
    GUI_DEST_DIR = $$OUT_DIR/gui
}
!build_pass:message("Web GUI dir:" $$GUI_DEST_DIR)

# Copy all GUI files (html, js, css etc.) into gui subfolder
copydata.commands = $(COPY_DIR) $$shell_path($$GUI_SRC_DIR) $$shell_path($$GUI_DEST_DIR)
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

