#ifndef SELECTGAMEMODE_H
#define SELECTGAMEMODE_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QFile>
#include <QDir>
#include <QStringList>
#include <QRandomGenerator>
#include "ui_SelectGameMode.h"
#include "QMouseEvent"
#include "../mainScreen/MainScreen.h"
#include "../createOwnGame/createOwnGame.h"
#include "../gameWindow/GameWindow.h"
#include "../selectLevel/SelectLevel.h"
#include "../../control/ControlFileManager.h"

namespace Ui {
class SelectGameMode;
}

class SelectGameMode : public QWidget
{
    Q_OBJECT

private:
    Ui::SelectGameMode *ui;

    enum{
        __button_back = 0,
        __w_text_box_1,
        __w_text_box_2,
        __w_text_box_3,
        __w_text_box_4,
        __content_box
    };
    enum{
        __game_mode_continue = 0,
        __game_mode_select_level,
        __game_mode_random_game,
        __game_mode_own_game
    };

    QString **__game_settings = nullptr;
    level_save_t *__last_game = nullptr;
    QMap<QString,QString> *__style_files = nullptr;
    int __COUNT_SETTINGS_FIELD = 3;

    const int __COUNT_SHADOW_ELEMENT = 6;
    const int __COUNT_GAME_MODE_CARDS = 4;
    QGraphicsDropShadowEffect *__effect_shadow;
    QFile *__file_style;

public:
    explicit SelectGameMode(QString **game_settings, level_save_t *last_game, QMap<QString,QString> *style_files, QWidget *parent = 0);
    virtual void mousePressEvent(QMouseEvent *event) override;
    ~SelectGameMode();

signals:
    void signalGoToScreen(QWidget*);
public slots:
    void slotGoToMainScreen();
};

#endif // SELECTGAMEMODE_H
