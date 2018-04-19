SUBDIRS += \
    BlockEditorQt.pro

DISTFILES += \
    ../a.out \
    .gitignore \
    ../.gitattributes

HEADERS += \
    ../src/block.h \
    ../src/linker.h \
    ../src/port.h

SOURCES += \
    ../src/block.cpp \
    ../src/linker.cpp \
    ../src/port.cpp \
    ../test.cpp
