#ifndef CREATEOWNGAME_H
#define CREATEOWNGAME_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QFileDialog>
#include <QFile>
#include "ui_createOwnGame.h"
#include "../selectGameMode/SelectGameMode.h"
#include "../selectDifficultGame/SelectDifficultGame.h"
#include "../../control/ControlFileManager.h"

namespace Ui {
class createOwnGame;
}

class createOwnGame : public QWidget
{
    Q_OBJECT
private:
    Ui::createOwnGame *ui;

    enum {
        __content_box = 0,
        __w_load_images,
        __button_back,
        __button_next
    };

    QString **__game_settings = nullptr;
    level_save_t *__last_game = nullptr;
    int __COUNT_SETTINGS_FIELD = 3;

    const int __COUNT_SHADOW_ELEMENT = 4;
    QGraphicsDropShadowEffect *__effect_shadow;
    QFile *__file_style = nullptr;
    QString __file_name;
    QPixmap *__preview_image = nullptr;
    QMap<QString,QString> *__style_files = nullptr;

    virtual void mousePressEvent(QMouseEvent *event) override;
public:
    explicit createOwnGame(QString **game_settings, level_save_t *last_game, QMap<QString,QString> *style_files, QWidget *parent = 0);
    ~createOwnGame();

signals:
    void signalGoToScreen(QWidget*);
public slots:
    void slotGoToSelectGameMode();
    void slotGoToSelectDifficultGame();
};

#endif // CREATEOWNGAME_H
