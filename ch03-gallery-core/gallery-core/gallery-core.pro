QT -= gui
QT += sql

TEMPLATE = lib
DEFINES += GALLERYCORE_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    album.cpp \
    albumdigitalaccessobject.cpp \
    databasemanager.cpp \
    picture.cpp

HEADERS += \
    albumdigitalaccessobject.h \
    databasemanager.h \
    gallery-core_global.h \
    album.h \
    picture.h

!isEmpty(target.path): INSTALLS += target
