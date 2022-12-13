#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QGraphicsDropShadowEffect>
#include <QObjectData>
#include <QFile>
#include <QFont>
#include <QTimer>
#include <QTime>
#include <QRandomGenerator>
#include <QPixmap>
#include "ui_GameWindow.h"
#include "../dialogWin/DialogWin.h"
#include "../selectGameMode/SelectGameMode.h"
#include "../../control/ControlFileManager.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

private:
    Ui::GameWindow *ui;

    enum {
        __game_zone_box = 0,
        __game_zone,
        __preview_box,
        __preview_image,
        __tools_box
    };
    enum {
        __tool_home = 0,
        __tool_pause,
        __tool_start,
        __tool_help
    };
    QString **__game_settings = nullptr;
    level_save_t *__last_game = nullptr;
    QMap<QString,QString> *__style_files = nullptr;

    int __COUNT_SETTINGS_FIELD = 3;

    const int __COUNT_SHADOW_ELEMENT = 5;
    const int __COUNT_TOOLS = 4;
    QGraphicsDropShadowEffect *__effect_shadow;
    QPixmap *__game_image = nullptr;
    QPixmap *__image_game_table = nullptr;
    QPushButton ***__game_table = nullptr;
    QFile *__file_style;
    QGridLayout *__grid_layout = nullptr;
    QTimer *__timer = nullptr;
    QTime *__time_game = nullptr;
    int __swap_x = -1, __swap_y = -1;
    int size_x = 0, size_y = 0;
    bool __view_help = false;
    DialogWin *__dialog_win = nullptr;

    bool __checkWinGame();
    void __generateGameTable();
    void __viewHelp();
    virtual void mousePressEvent(QMouseEvent *event) override;

public:
    explicit GameWindow(QString **game_settings, level_save_t *last_game, QMap<QString,QString> *style_files, QWidget *parent = 0);
    ~GameWindow();
signals:
    void signalGoToScreen(QWidget*);
public slots:
    void slotGameZoneClick();
    void slotTimeOut();
    void slotWinGame();
};

#endif // GAMEWINDOW_H
