QT += core gui sql charts network serialport
QT += multimedia
QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

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
    arduino.cpp \
    button_g_fournisseurs.cpp \
    calculator_g_fournisseurs.cpp \
    calendar_g_fournisseur.cpp \
    connection.cpp \
    exportexcelobject.cpp \
    factures.cpp \
    fournisseur_fidele.cpp \
    fournisseurs.cpp \
    main.cpp \
    g_fournisseurs.cpp \
    notepad.cpp \
    paint_g_fournisseurs.cpp \
    pieces_g_fournisseurs.cpp \
    produits.cpp \
    puzzle_g_fournisseurs.cpp \
    puzzle_main_window_g_fournisseurs.cpp \
    scribblearea.cpp \
    statistics.cpp

HEADERS += \
    arduino.h \
    button_g_fournisseurs.h \
    calculator_g_fournisseurs.h \
    calendar_g_fournisseur.h \
    connection.h \
    exportexcelobject.h \
    factures.h \
    fournisseur_fidele.h \
    fournisseurs.h \
    g_fournisseurs.h \
    notepad.h \
    paint_g_fournisseurs.h \
    pieces_g_fournisseurs.h \
    produits.h \
    puzzle_g_fournisseurs.h \
    puzzle_main_window_g_fournisseurs.h \
    scribblearea.h \
    statistics.h


FORMS += \
    g_fournisseurs.ui \
    notepad.ui \
    paint_g_fournisseurs.ui \
    statistics.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc


