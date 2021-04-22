#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#----------------------Yosra---------------------------

QT       += core gui sql printsupport charts network multimedia widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Atelier_Connexion
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    accueil.cpp \
    analogclock.cpp \
    calculator.cpp \
    evenement.cpp \
        main.cpp \
        mainwindow.cpp \
    connection.cpp \
    notification.cpp \
    smtp.cpp \
    stats.cpp \
    tableprinter.cpp \
    ticket.cpp \
    widget.cpp

HEADERS += \
    accueil.h \
    analogclock.h \
    calculator.h \
    evenement.h \
        mainwindow.h \
    connection.h \
    notification.h \
    smtp.h \
    stats.h \
    tableprinter.h \
    ticket.h \
    widget.h

FORMS += \
        accueil.ui \
        analogclock.ui \
        calculator.ui \
        mainwindow.ui \
        stats.ui \
        widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    buttons.qrc \
    buttons.qrc \
    buttons.qrc \
    ressource.qrc \
    ressource.qrc \
    ressource.qrc

DISTFILES += \
    buttons/close-gray.png \
    buttons/close-orange.png \
    buttons/close.png \
    buttons/icon.png \
    buttons/kiss_fm.png \
    buttons/lakhanda.png \
    buttons/neth.png \
    buttons/pause-orange.png \
    buttons/pause.png \
    buttons/play-orange.png \
    buttons/play.png \
    buttons/plus-orange.png \
    buttons/plus.png \
    buttons/rathumakara.png \
    buttons/rhythm_world.png \
    buttons/siyatha.png \
    buttons/skip-next-orange.png \
    buttons/skip-next.png \
    buttons/skip-previous-orange.png \
    buttons/skip-previous.png \
    buttons/stop-orange.png \
    buttons/stop.png \
    buttons/window-maximize-gray.png \
    buttons/window-maximize.png \
    buttons/window-minimize-gray.png \
    buttons/window-minimize.png \
    buttons/window-restore-gray.png \
    buttons/window-restore.png \
    img/17402.png \
    img/Nuit-de-leau.jpg \
    img/button-304224_960_720.png \
    img/chess.jpg \
    img/chess.png \
    img/echec.jpg \
    img/echecccccc.jpg \
    img/echecccccc.png \
    img/echecccccc.psd \
    img/endgames.png \
    img/fichier-pdf.png \
    img/frensh.png \
    img/icon edit.jpg \
    img/icon edit.jpg \
    img/imprimer.png \
    img/kisspng-button-icon-delete-button-png-image-5a756de9e12917.7504282715176452899223.jpg \
    img/logo.jpg \
    img/logooo.png \
    img/new_account.png \
    img/pdf.png \
    img/recherche.jpg \
    img/sup.png \
    img/supp.jpg \
    img/supprimer.png \
    img/téléchargement.png \
    img/téléchargement.png \
    img/téléchargement.png \
    pdf/pdfVide (1).pdf \
    pdf/pdfVide (1).pdf \
    pdf/pdfVide (2).pdf \
    pdf/pdfVide (2).pdf \
    pdf/pdfVide.pdf \
    pdf/yosra.pdf \
    sond/632.wav \
    sond/Best and sound effects welcome intro [Mpgun.com].wav \
    sond/Best and sound effects welcome intro [Mpgun.com].wav \
    sond/Click button.wav \
    sond/Click button.wav \
    sond/Click button.wav \
    sond/Click button.wav \
    sond/button.mp3

SUBDIRS += \
    qt-simple-calculator-master/simpleCalculator.pro
