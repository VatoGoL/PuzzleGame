#ifndef SELECTDIFFICULTGAME_H
#define SELECTDIFFICULTGAME_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QFile>
#include "ui_SelectDifficultGame.h"
#include <QString>
#include "../selectLevel/SelectLevel.h"
#include "../createOwnGame/createOwnGame.h"
#include "../../control/ControlFileManager.h"

namespace Ui {
class SelectDifficultGame;
}

class SelectDifficultGame : public QWidget
{
    Q_OBJECT
private:
    Ui::SelectDifficultGame *ui;

    enum {
        __content_box = 0,
        __button_back,
        __w_text_box_1,
        __w_text_box_2,
        __w_text_box_3,
        __w_text_box_4
    };

    QString **__game_settings = nullptr;
    level_save_t *__last_game = nullptr;
    QMap<QString,QString> *__style_files = nullptr;
    int __COUNT_SETTINGS_FIELD = 3;

    QString __last_screen;
    const int __COUNT_SHADOW_ELEMENT = 6;
    const int __COUNT_DIFFICULT_CARDS = 4;
    QGraphicsDropShadowEffect *__effect_shadow;
    QFile *__file_style;


public:
    explicit SelectDifficultGame(QString **game_settings, level_save_t *last_game, QMap<QString,QString> *style_files,
                                 QString last_screen = "",QWidget *parent = 0);
    virtual void mousePressEvent(QMouseEvent *event) override;
    ~SelectDifficultGame();
signals:
    void signalGoToScreen(QWidget*);
public slots:
    void slotGoToLastScreen();

};

#endif // SELECTDIFFICULTGAME_H
