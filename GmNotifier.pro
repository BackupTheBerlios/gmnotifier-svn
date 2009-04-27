# -------------------------------------------------
# Project created by QtCreator 2009-04-26T14:30:13
# -------------------------------------------------
QT += network \
    xml
TARGET = GmNotifier
TEMPLATE = app
SOURCES += main.cpp \
    program.cpp \
    notifier.cpp \
    configuration.cpp \
    configurationwindow.cpp
HEADERS += program.h \
    notifier.h \
    configuration.h \
    configurationwindow.h
RESOURCES += resources.qrc
TRANSLATIONS += translation_nl.ts
RC_FILE = icon.rc