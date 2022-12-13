#include "SelectGameMode.h"
#include <QDebug>
SelectGameMode::SelectGameMode(QString **game_settings, level_save_t *last_game,QMap<QString,QString> *style_files, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectGameMode)
{
    ui->setupUi(this);

    __game_settings = game_settings;
    __last_game = last_game;

    __style_files = style_files;
    __file_style = new QFile( (*style_files)["SelectGameMode"] );
    __file_style->open(QFile::ReadOnly);
    QString a = __file_style->readAll();
    this->setStyleSheet(a);

    __effect_shadow = new QGraphicsDropShadowEffect [__COUNT_SHADOW_ELEMENT];
    for(int i = 0; i < __COUNT_SHADOW_ELEMENT; ++i){
        __effect_shadow[i].setBlurRadius(4);
        __effect_shadow[i].setXOffset(0);
        __effect_shadow[i].setYOffset(4);
        __effect_shadow[i].setColor(QColor(0,0,0,64));
    }

    ui->__button_back->setGraphicsEffect(&__effect_shadow[__button_back]);
    ui->__w_text_box_1->setGraphicsEffect(&__effect_shadow[__w_text_box_1]);
    ui->__w_text_box_2->setGraphicsEffect(&__effect_shadow[__w_text_box_2]);
    ui->__w_text_box_3->setGraphicsEffect(&__effect_shadow[__w_text_box_3]);
    ui->__w_text_box_4->setGraphicsEffect(&__effect_shadow[__w_text_box_4]);
    ui->__content_box->setGraphicsEffect(&__effect_shadow[__content_box]);

    if(__last_game == nullptr){
        ui->__card_content_1->setStyleSheet("#__card_content_1{background-color:#698683;}");
        ui->__w_text_box_1->setStyleSheet("#__card_content_1{background-color:#52A68C;}");
    }

    connect(ui->__button_back,SIGNAL(clicked()),this,SLOT(slotGoToMainScreen()));

}
void SelectGameMode::slotGoToMainScreen(){
    MainScreen *screen = new MainScreen(__game_settings,__last_game, __style_files);
    emit signalGoToScreen(screen);
}
void SelectGameMode::mousePressEvent(QMouseEvent *event){
    QWidget **game_mode_cards = new QWidget *[__COUNT_GAME_MODE_CARDS];
    game_mode_cards[__game_mode_continue] = ui->__card_1;
    game_mode_cards[__game_mode_select_level] = ui->__card_2;
    game_mode_cards[__game_mode_random_game] = ui->__card_3;
    game_mode_cards[__game_mode_own_game] = ui->__card_4;

    int *difficult_int = new int [3];
    difficult_int[0] = 4;
    difficult_int[1] = 8;
    difficult_int[2] = 16;


    for(int i = 0; i < __COUNT_GAME_MODE_CARDS; ++i){

        if(event->x() >= (game_mode_cards[i]->x() +
                          ui->__content_box->pos().x())
            && event->x() <= (ui->__content_box->pos().x() +
                              (game_mode_cards[i]->x()+game_mode_cards[i]->width())))
        {
            if(event->y() >= (game_mode_cards[i]->y() +
                              ui->__content_box->pos().y())
                && event->y() <= (ui->__content_box->pos().y() +
                                  (game_mode_cards[i]->y()+game_mode_cards[i]->height())))
            {
                GameWindow *screen_GW;
                SelectLevel *screen_SL;
                createOwnGame *screen_COG;

                QStringList list_file;
                QDir img_dir(":/level_images");
                int temp;
                QString temp_str;

                switch(i){
                    case __game_mode_continue:
                        if(__last_game != nullptr){
                            screen_GW = new GameWindow(__game_settings,__last_game, __style_files);
                            emit signalGoToScreen(screen_GW);
                        }
                        break;
                    case __game_mode_select_level:
                        screen_SL = new SelectLevel(__game_settings,__last_game, __style_files);
                        emit signalGoToScreen(screen_SL);
                        break;
                    case __game_mode_random_game:
                        if(__last_game == nullptr){
                            __last_game = new level_save_t;
                        }

                        list_file << "*.jpg" << "*.png" << "*.webp";
                        img_dir.setNameFilters(list_file);
                        temp = QRandomGenerator::global()->bounded(0, (int)img_dir.count());
                        temp_str = img_dir[temp];
                        __last_game->name_level = "Random game";
                        __last_game->path_to_image = ":/level_images/" + temp_str;
                        __last_game->time_m = 0;
                        __last_game->time_s = 0;

                        temp = QRandomGenerator::global()->bounded(0, 3);
                        __last_game->size_x = difficult_int[temp];
                        __last_game->size_y = difficult_int[temp];

                        temp = 0;
                        __last_game->game_table = new int *[__last_game->size_y];
                        for(int j = 0; j < __last_game->size_y; ++j){
                            __last_game->game_table[j] = new int [__last_game->size_x];
                            for(int k = 0; k < __last_game->size_x; ++k){
                                __last_game->game_table[j][k] = temp;
                                temp++;
                            }
                        }

                        screen_GW = new GameWindow(__game_settings,__last_game, __style_files);
                        emit signalGoToScreen(screen_GW);
                        break;
                    case __game_mode_own_game:
                        screen_COG = new createOwnGame(__game_settings,__last_game, __style_files);
                        emit signalGoToScreen(screen_COG);
                        break;
                }

            }
        }
    }
    delete[] difficult_int;
    delete[] game_mode_cards;
}
SelectGameMode::~SelectGameMode()
{
    disconnect(ui->__button_back,SIGNAL(clicked()),this,SLOT(slotGoToMainScreen()));
    delete __file_style;
    delete ui;
}
