#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_MainWindow.h"
#include <QGraphicsDropShadowEffect>
#include <QFile>

#include "./view/mainScreen/MainScreen.h"
#include "./view/settingsScreen/settingsScreen.h"
#include "./view/selectGameMode/SelectGameMode.h"
#include "./view/createOwnGame/createOwnGame.h"
#include "./view/selectLevel/SelectLevel.h"
#include "./view/selectDifficultGame/SelectDifficultGame.h"
#include "./view/gameWindow/GameWindow.h"

#include "./control/ControlFileManager.h"
#include "./control/ControlDataBaseManager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:

    enum {
        __settings_screen_resolution = 0,
        __settings_fullscreen,
        __settings_music
    };
    int __settings_key = 0, __settings_value = 1;

    Ui::MainWindow *ui;
    QWidget *__screen = nullptr;
    QApplication *__app = nullptr;

    ControlFileManager *__control_file_manager = nullptr;
    QString __default_path_to_settings_file = ":/config.txt";
    QString __default_path_to_game_save_file = ":/game_save.bin";
    QString **__game_settings = nullptr;
    int __COUNT_SETTINGS_FIELD = 3;
    level_save_t *__last_game = nullptr;

    ControlDataBaseManager *__control_DB_manager = nullptr;
    QMap<QString,QString> *__style_files = nullptr;
    QMap<QString,QString> *__music_files = nullptr;

    void setAllConnect();
    void setAllDisconnect();

public:
    explicit MainWindow(QApplication *app,QWidget *parent = 0);
    ~MainWindow();
signals:
    void signalExit();
public slots:
    void slotSetScreen(QWidget *screen);
    void slotSaveSettings();
    void slotExit();
};

#endif // MAINWINDOW_H
