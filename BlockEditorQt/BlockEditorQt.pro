QT    += widgets

INCLUDEPATH += \
    C:\boost\boost_1_67_0

SUBDIRS += \
    BlockEditorQt.pro

DISTFILES += \
    ../a.out \
    .gitignore \
    ../.gitattributes

HEADERS += \
    ../src/block.h \
    ../src/port.h \
    ../src/mainwindow.h \
    ../src/scheme.h \
    ../src/canvas.h \
    ../src/linker.h

SOURCES += \
    ../src/block.cpp \
    ../src/port.cpp \
    ../src/main.cpp \
    ../src/mainwindow.cpp \
    ../src/scheme.cpp \
    ../src/canvas.cpp \
    ../src/linker.cpp
