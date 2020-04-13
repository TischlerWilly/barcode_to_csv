#-------------------------------------------------
#
# Project created by QtCreator 2017-04-14T12:08:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BARCODE_TO_CSV
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    text_zeilenweise.cpp \
    dialog_leere_unterurdner_entfernen.cpp \
    bibiothek_oliver.cpp

HEADERS  += mainwindow.h \
    text_zeilenweise.h \
    dialog_leere_unterurdner_entfernen.h \
    bibiothek_oliver.h \
    todo.h

FORMS    += mainwindow.ui \
    dialog_leere_unterurdner_entfernen.ui

DISTFILES += \
    barcode_gelb.ico

RC_ICONS = barcode_gelb.ico
