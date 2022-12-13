#ifndef SELECTLEVEL_H
#define SELECTLEVEL_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QFile>
#include <QScrollArea>
#include <QVBoxLayout>
#include "ui_SelectLevel.h"
#include "../selectGameMode/SelectGameMode.h"
#include "../selectDifficultGame/SelectDifficultGame.h"
#include "../../control/ControlFileManager.h"
#include "../../control/ControlDataBaseManager.h"

namespace Ui {
class SelectLevel;
}

class SelectLevel : public QWidget
{
    Q_OBJECT
private:
    Ui::SelectLevel *ui;

    enum {
        __content_box = 0,
        __level_slider,
        __level_number_1,
        __button_back,
        __levels_box,
    };
    enum {
        __level_box = 0,
        __level_image_box,
        __level_number_box
    };
    enum {
        __level_image = 0,
        __level_number
    };

    QString __path_to_image_level_1 = ":/level_images/level_1_image.jpg";

    QString **__game_settings = nullptr;
    int __COUNT_SETTINGS_FIELD = 3;
    level_save_t *__last_game = nullptr;
    QMap<QString,QString> *__style_files = nullptr;

    const int __COUNT_SHADOW_ELEMENT = 5;
    const int __COUNT_LEVEL_CARD = 1;
    QGraphicsDropShadowEffect *__effect_shadow;
    QFile *__file_style;
    QScrollArea *__scroll_area = nullptr;
    QVector<level_info_t> *__levels_info = nullptr;
    QWidget **__widget_levels_element = nullptr;
    const int __COUNT_WIDGET_ELEMENT = 3;
    QLabel **__label_levels_element = nullptr;
    const int __COUNT_LABEL_ELEMENT = 2;
    QVBoxLayout **__v_layout_levels = nullptr;
    const int __COUNT_V_LOYOUT_ELEMENT = 2;

    void __createLevels();
public:
    explicit SelectLevel(QString **game_settings, level_save_t *last_game, QMap<QString,QString> *style_files, QWidget *parent = 0);
    virtual void mousePressEvent(QMouseEvent *event) override;
    ~SelectLevel();
signals:
    void signalGoToScreen(QWidget*);
public slots:
    void slotGoToLastScreen();
};

#endif // SELECTLEVEL_H
