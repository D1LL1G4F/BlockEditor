QT    += widgets

SUBDIRS += \
    BlockEditorQt.pro

DISTFILES += \
    ../a.out \
    .gitignore \
    ../.gitattributes

HEADERS += \
    ../src/block.h \
    ../src/port.h \
    ../src/mainwindow.h

SOURCES += \
    ../src/block.cpp \
    ../src/port.cpp \
    ../test.cpp \
    ../src/main.cpp \
    ../src/mainwindow.cpp
