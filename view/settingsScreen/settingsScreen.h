#ifndef SETTINGSSCREEN_H
#define SETTINGSSCREEN_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QFile>
#include "ui_settingsScreen.h"
#include "../mainScreen/MainScreen.h"
#include "../../control/ControlFileManager.h"

namespace Ui {
class SettingsScreen;
}

class SettingsScreen : public QWidget
{
    Q_OBJECT
private:

    enum{
        __check_box_1 = 0,
        __check_box_2,
        __combo_box,
        __check_zone_1,
        __check_zone_2,
        __button_back,
        __content_box
    };
    enum{
        __settings_screen_size = 0,
        __settings_fullscreen,
        __settings_music
    };

    int __settings_key = 0, __settings_value = 1;

    Ui::SettingsScreen *ui;

    QString **__game_settings = nullptr;
    const int __COUNT_SETTINGS_FIELD = 3;
    level_save_t *__last_game = nullptr;
    QMap<QString,QString> *__style_files = nullptr;

    const int __COUNT_SHADOW_ELEMENT = 7;
    QGraphicsDropShadowEffect *__effect_shadow;

    const int __COUNT_CHECK_BOX = 2;
    bool *__check_box_active;

    QFile *__file_style;

public:
    explicit SettingsScreen(QString **game_settings, level_save_t *last_game, QMap<QString,QString> *style_files, QWidget *parent = 0);
    virtual void mousePressEvent(QMouseEvent *event) override;
    ~SettingsScreen();

signals:
    void signalGoToScreen(QWidget*);
    void signalSaveSettings();
public slots:
    void slotGoToMainScreen();
    void slotSetCurrentIndex(int value);
};

#endif // SETTINGSSCREEN_H
