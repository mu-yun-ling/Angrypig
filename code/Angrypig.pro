QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bird.cpp \
    loading.cpp \
    main.cpp \
    musicplayer.cpp \
    mybutton.cpp \
    pig.cpp \
    playing.cpp \
    start.cpp

HEADERS += \
    bird.h \
    loading.h \
    musicplayer.h \
    mybutton.h \
    pig.h \
    playing.h \
    start.h

TRANSLATIONS += \
    Angrypig_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    birds.qrc \
    pig.qrc \
    sound.qrc \
    start.qrc
