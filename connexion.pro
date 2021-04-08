<<<<<<< HEAD
QT       += core gui sql  printsupport network multimedia
=======
QT       += core gui sql printsupport network
>>>>>>> 4c29bb4565b29a6c0eaee925a88ecfbd05eec123

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connection.cpp \
<<<<<<< HEAD
    exportexcelobject.cpp \
=======
>>>>>>> 4c29bb4565b29a6c0eaee925a88ecfbd05eec123
    historique.cpp \
    joueur.cpp \
    main.cpp \
    mainwindow.cpp \
    partie.cpp \
<<<<<<< HEAD
    qcustomplot.cpp \
=======
>>>>>>> 4c29bb4565b29a6c0eaee925a88ecfbd05eec123
    smtp.cpp

HEADERS += \
    connection.h \
<<<<<<< HEAD
    exportexcelobject.h \
=======
>>>>>>> 4c29bb4565b29a6c0eaee925a88ecfbd05eec123
    historique.h \
    joueur.h \
    mainwindow.h \
    partie.h \
<<<<<<< HEAD
    qcustomplot.h \
=======
>>>>>>> 4c29bb4565b29a6c0eaee925a88ecfbd05eec123
    smtp.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Images/pb_afficher.png

RESOURCES += \
    Images.qrc
