#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>
#include "ui_MainScreen.h"
#include <QGraphicsDropShadowEffect>
#include <QFile>
#include "../settingsScreen/settingsScreen.h"
#include "../selectGameMode/SelectGameMode.h"
#include "../../control/ControlFileManager.h"
#include "../referencePage/RefPage_1.h"

namespace Ui {
class MainScreen;
}

class MainScreen : public QWidget
{
    Q_OBJECT
private:
    Ui::MainScreen *ui;

    enum {
        __button_start = 0,
        __button_settings,
        __button_exit
    };

    QString **__game_settings = nullptr;
    level_save_t *__last_game = nullptr;
    QMap<QString,QString> *__style_files = nullptr;
    int __COUNT_SETTINGS_FIELD = 3;

    const int __COUNT_SHADOW_ELEMENT = 3;
    QGraphicsDropShadowEffect *__effect_shadow;
    QFile *__file_style;    

public:
    explicit MainScreen(QString **game_settings, level_save_t *last_game,QMap<QString,QString> *style_files, QWidget *parent = 0);
    ~MainScreen();

signals:
    void signalGoToScreen(QWidget *);
    void signalExit();
public slots:
    void slotGoToSettingsScreen();
    void slotGoToSelectGameMode();
    void slotGoToReferencesScreen();
    void slotExit();
};

#endif // MAINSCREEN_H
