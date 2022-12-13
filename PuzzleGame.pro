#-------------------------------------------------
#
# Project created by QtCreator 2022-11-26T22:17:15
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PuzzleGame
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


SOURCES += \
        main.cpp \
    view/settingsScreen/settingsscreen.cpp \
    view/selectGameMode/SelectGameMode.cpp \
    view/createOwnGame/createOwnGame.cpp \
    view/selectLevel/SelectLevel.cpp \
    view/selectDifficultGame/SelectDifficultGame.cpp \
    view/gameWindow/GameWindow.cpp \
    view/mainScreen/MainScreen.cpp \
    MainWindow.cpp \
    model/ModelFileManager.cpp \
    control/ControlFileManager.cpp \
    view/dialogWin/DialogWin.cpp \
    model/ModelDataBaseManager.cpp \
    control/ControlDataBaseManager.cpp \
    view/referencePage/RefPage_1.cpp \
    view/referencePage/RefPage_2.cpp \
    view/referencePage/RefPage_3.cpp \
    view/referencePage/RefPage_4.cpp \
    view/referencePage/RefPage_5.cpp

HEADERS += \
    view/settingsScreen/settingsscreen.h \
    view/selectGameMode/SelectGameMode.h \
    view/createOwnGame/createOwnGame.h \
    view/selectLevel/SelectLevel.h \
    view/selectDifficultGame/SelectDifficultGame.h \
    view/gameWindow/GameWindow.h \
    view/mainScreen/MainScreen.h \
    MainWindow.h \
    model/ModelFileManager.h \
    control/ControlFileManager.h \
    view/dialogWin/DialogWin.h \
    model/ModelDataBaseManager.h \
    control/ControlDataBaseManager.h \
    view/referencePage/RefPage_1.h \
    view/referencePage/RefPage_2.h \
    view/referencePage/RefPage_3.h \
    view/referencePage/RefPage_4.h \
    view/referencePage/RefPage_5.h
FORMS += \
    view/settingsScreen/settingsscreen.ui \
    view/selectGameMode/SelectGameMode.ui \
    view/createOwnGame/createOwnGame.ui \
    view/selectLevel/SelectLevel.ui \
    view/selectDifficultGame/SelectDifficultGame.ui \
    view/gameWindow/GameWindow.ui \
    view/mainScreen/MainScreen.ui \
    MainWindow.ui \
    view/dialogWin/DialogWin.ui \
    view/referencePage/RefPage_1.ui \
    view/referencePage/RefPage_2.ui \
    view/referencePage/RefPage_3.ui \
    view/referencePage/RefPage_4.ui \
    view/referencePage/RefPage_5.ui

RESOURCES += \
    sources/project_sources.qrc

DISTFILES += \
    sources/level_images/level_1_image.jpg
