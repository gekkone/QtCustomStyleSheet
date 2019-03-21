TEMPLATE = lib
TARGET = CustomStyleSheet
VERSION = 1.1.0

OBJECTS_DIR = .build
MOC_DIR = .build
RCC_DIR = .build

DESTDIR = lib

SOURCES += \
    src/CustomStyleSheetStyle.cpp \
    src/CssParser.cpp \
    src/CssScaner.cpp \
    src/StyleAnimation.cpp \
    src/CssUtil.cpp \
    src/CssGenerator.cpp

HEADERS += \
    src/CustomStyleSheetStyle.h \
    src/CssParser.h \
    src/CssScaner.h \
    src/StyleAnimation.h \
    src/CssUtil.h

target.path = /usr/local/lib
headers.path = /usr/local/include
headers.files = $$HEADERS

INSTALLS += target headers

RESOURCES += \
    CustomStyleSheetResource.qrc
