#include "settingsScreen.h"
#include <QDebug>
SettingsScreen::SettingsScreen(QString **game_settings, level_save_t *last_game, QMap<QString,QString> *style_files, QWidget *parent) :
    ui(new Ui::SettingsScreen),
    QWidget(parent)
{
    ui->setupUi(this);

    __game_settings = game_settings;
    __last_game = last_game;

    __style_files = style_files;
    __file_style = new QFile( (*style_files)["SettingsScreen"] );
    __file_style->open(QFile::ReadOnly);
    QString a = __file_style->readAll();
    this->setStyleSheet(a);

    __effect_shadow = new QGraphicsDropShadowEffect [__COUNT_SHADOW_ELEMENT];
    for(int i = 0; i < __COUNT_SHADOW_ELEMENT; ++i){
        __effect_shadow[i].setBlurRadius(8);
        __effect_shadow[i].setXOffset(0);
        __effect_shadow[i].setYOffset(4);
        __effect_shadow[i].setColor(QColor(0,0,0,64));
    }

    ui->__combo_box->setGraphicsEffect(&__effect_shadow[__combo_box]);
    ui->__check_box_1->setGraphicsEffect(&__effect_shadow[__check_box_1]);
    ui->__check_box_2->setGraphicsEffect(&__effect_shadow[__check_box_2]);
    ui->__check_zone_1->setGraphicsEffect(&__effect_shadow[__check_zone_1]);
    ui->__check_zone_2->setGraphicsEffect(&__effect_shadow[__check_zone_2]);
    ui->__button_back->setGraphicsEffect(&__effect_shadow[__button_back]);
    ui->__content_box->setGraphicsEffect(&__effect_shadow[__content_box]);

    if(__game_settings[0][__settings_value] == "1920x1080"){
        ui->__combo_box->setCurrentIndex(0);
    }
    else if(__game_settings[0][__settings_value] == "1440x720"){
        ui->__combo_box->setCurrentIndex(1);
    }


    __check_box_active = new bool [__COUNT_CHECK_BOX];
    QWidget **check_zones = new QWidget *[__COUNT_CHECK_BOX];
    check_zones[__check_box_1] = ui->__check_zone_1;
    check_zones[__check_box_2] = ui->__check_zone_2;

    for(int i = 0; i < __COUNT_CHECK_BOX; ++i){
        if(__game_settings[i+1][__settings_value] == "true"){
            __check_box_active[i] = true;
            check_zones[i]->setStyleSheet(QString("#__check_zone_") + QString('0' + i+1) + QString("{background-color: #536B69;}"));
        }
        else{
            __check_box_active[i] = false;
            check_zones[i]->setStyleSheet(QString("#__check_zone_") + QString('0' + i+1) + QString("{background-color: none;}"));
        }
    }

    delete[] check_zones;

    connect(ui->__button_back,SIGNAL(clicked()),this,SLOT(slotGoToMainScreen()));
    connect(ui->__combo_box,SIGNAL(currentIndexChanged(int)),this,SLOT(slotSetCurrentIndex(int)));
}
void SettingsScreen::slotSetCurrentIndex(int value){
    ui->__combo_box->setCurrentIndex(value);
    if(ui->__combo_box->currentText() == "1920 x 1080"){
        __game_settings[0][__settings_value] = "1920x1080";
    }
    else if(ui->__combo_box->currentText() == "1440 x 720"){
        __game_settings[0][__settings_value] = "1440x720";
    }

}
void SettingsScreen::slotGoToMainScreen(){
    emit signalSaveSettings();

    MainScreen *screen = new MainScreen(__game_settings,__last_game, __style_files);
    emit signalGoToScreen(screen);
}
void SettingsScreen::mousePressEvent(QMouseEvent *event){
    QWidget **check_boxes = new QWidget *[__COUNT_CHECK_BOX];
    check_boxes[__check_box_1] = ui->__check_box_1;
    check_boxes[__check_box_2] = ui->__check_box_2;

    for(int i = 0; i < __COUNT_CHECK_BOX; ++i){
        if(event->x() >= (check_boxes[i]->x() +
                          ui->__content_box->pos().x() +
                          ui->__form_box->pos().x())
            && event->x() <= (ui->__content_box->pos().x() +
                              ui->__form_box->pos().x() +
                              (check_boxes[i]->x()+check_boxes[i]->width())))
        {
            if(event->y() >= (check_boxes[i]->y() +
                              ui->__content_box->pos().y()+
                              ui->__form_box->pos().y())
                && event->y() <= (ui->__content_box->pos().y() +
                                  ui->__form_box->pos().y() +
                                  (check_boxes[i]->y()+check_boxes[i]->height())))
            {

                switch(i){
                    case __check_box_1:
                        if(__check_box_active[__check_box_1] == true){
                            ui->__check_zone_1->setStyleSheet("#__check_zone_1{background-color: none;}");
                            __check_box_active[__check_box_1] = false;
                            __game_settings[__check_box_1+1][__settings_value] = "false";
                        }else{
                            ui->__check_zone_1->setStyleSheet("#__check_zone_1{background-color: #536B69;}");
                            __check_box_active[__check_box_1] = true;
                            __game_settings[__check_box_1+1][__settings_value] = "true";
                        }

                        break;
                    case __check_box_2:
                        if(__check_box_active[__check_box_2] == true){
                            ui->__check_zone_2->setStyleSheet("#__check_zone_2{background-color: none;}");
                            __check_box_active[__check_box_2] = false;
                            __game_settings[__check_box_2+1][__settings_value] = "false";
                        }else{
                            ui->__check_zone_2->setStyleSheet("#__check_zone_2{background-color: #536B69;}");
                            __check_box_active[__check_box_2] = true;
                            __game_settings[__check_box_2+1][__settings_value] = "true";
                        }
                        break;
                }

            }
        }
    }

    delete[] check_boxes;
}
SettingsScreen::~SettingsScreen()
{
    disconnect(ui->__button_back,SIGNAL(clicked()),this,SLOT(slotGoToMainScreen()));
    disconnect(ui->__combo_box,SIGNAL(currentIndexChanged(int)),this,SLOT(slotSetCurrentIndex(int)));
    delete __check_box_active;
    delete __file_style;
    delete ui;
}
