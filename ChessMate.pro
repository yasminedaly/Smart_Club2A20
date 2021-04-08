QT       += core gui printsupport
QT += sql
QT       += core gui
QT       += multimedia
CONFIG   += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia


CONFIG += c++
TARGET = QtMusicPlayer

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connection.cpp \
    exportexcelobject.cpp \
    main.cpp \
    abonnes.cpp \
    playlist.cpp \
    qcustomplot.cpp \
    seances.cpp \
    sub.cpp \
    track.cpp

HEADERS += \
      \
    abonnes.h \
    connection.h \
    exportexcelobject.h \
    playlist.h \
    qcustomplot.h \
    seances.h \
    sub.h \
    track.h \
    utils.h

FORMS += \
    abonnes.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
