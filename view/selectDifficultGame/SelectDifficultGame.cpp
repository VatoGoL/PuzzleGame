#include "SelectDifficultGame.h"
#include <QDebug>
SelectDifficultGame::SelectDifficultGame(QString **game_settings, level_save_t *last_game, QMap<QString,QString> *style_files,
                                         QString last_screen, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectDifficultGame)
{
    ui->setupUi(this);

    __game_settings = game_settings;
    __last_game = last_game;

    __style_files = style_files;
    __last_screen = last_screen;
    __file_style = new QFile( (*style_files)["SelectDifficultGame"] );
    __file_style->open(QFile::ReadOnly);
    this->setStyleSheet(__file_style->readAll());

    __effect_shadow = new QGraphicsDropShadowEffect [__COUNT_SHADOW_ELEMENT];
    for(int i = 0; i < __COUNT_SHADOW_ELEMENT; ++i){
        __effect_shadow[i].setBlurRadius(4);
        __effect_shadow[i].setXOffset(0);
        __effect_shadow[i].setYOffset(4);
        __effect_shadow[i].setColor(QColor(0,0,0,64));
    }

    ui->__content_box->setGraphicsEffect(&__effect_shadow[__content_box]);
    ui->__button_back->setGraphicsEffect(&__effect_shadow[__button_back]);
    ui->__w_text_box_1->setGraphicsEffect(&__effect_shadow[__w_text_box_1]);
    ui->__w_text_box_2->setGraphicsEffect(&__effect_shadow[__w_text_box_2]);
    ui->__w_text_box_3->setGraphicsEffect(&__effect_shadow[__w_text_box_3]);
    ui->__w_text_box_4->setGraphicsEffect(&__effect_shadow[__w_text_box_4]);

    connect(ui->__button_back,SIGNAL(clicked()),this,SLOT(slotGoToLastScreen()));
}
void SelectDifficultGame::slotGoToLastScreen(){
    if(__last_game != nullptr){
        if(__last_game->game_table != nullptr){
            for(int i = 0; i < __last_game->size_y; ++i){
                delete[] __last_game->game_table[i];
            }
            delete[] __last_game->game_table;
        }
        delete __last_game;
        __last_game = nullptr;
    }

    if(__last_screen == "SelectLevel"){
        SelectLevel *screen = new SelectLevel(__game_settings,__last_game,__style_files);
        emit signalGoToScreen(screen);
    }
    else if(__last_screen == "CreateOwnGame"){
        createOwnGame *screen = new createOwnGame(__game_settings,__last_game,__style_files);
        emit signalGoToScreen(screen);
    }
}

void SelectDifficultGame::mousePressEvent(QMouseEvent *event){
    QWidget **difficult_card = new QWidget *[__COUNT_DIFFICULT_CARDS];
    difficult_card[0] = ui->__card_1;
    difficult_card[1] = ui->__card_2;
    difficult_card[2] = ui->__card_3;
    difficult_card[3] = ui->__card_4;

    int *difficult_int = new int [__COUNT_DIFFICULT_CARDS];
    difficult_int[0] = 2;
    difficult_int[1] = 8;
    difficult_int[2] = 16;
    difficult_int[3] = 1;


    for(int i = 0; i < __COUNT_DIFFICULT_CARDS; ++i){
        if(event->x() >= difficult_card[i]->x()+ui->__content_box->pos().x()
            && event->x() <= ui->__content_box->pos().x() + (difficult_card[i]->x()+difficult_card[i]->width()))
        {
            if(event->y() >= difficult_card[i]->y()+ui->__content_box->pos().y()
               && event->y() <= ui->__content_box->pos().y() + (difficult_card[i]->y()+difficult_card[i]->height()))
            {
                if(i != __COUNT_DIFFICULT_CARDS-1){
                    __last_game->size_x = difficult_int[i];
                    __last_game->size_y = difficult_int[i];
                    int count = 0;
                    __last_game->game_table = new int *[__last_game->size_y];
                    for(int j = 0; j < __last_game->size_y; ++j){
                        __last_game->game_table[j] = new int [__last_game->size_x];
                        for(int k = 0; k < __last_game->size_x; ++k){
                            __last_game->game_table[j][k] = count;
                            count++;
                        }
                    }

                    GameWindow *screen = new GameWindow(__game_settings,__last_game,__style_files);
                    emit signalGoToScreen(screen);
                }

            }
        }
    }

    delete[] difficult_int;
    delete[] difficult_card;
}

SelectDifficultGame::~SelectDifficultGame()
{
    connect(ui->__button_back,SIGNAL(clicked()),this,SLOT(slotGoToLastScreen()));
    delete __file_style;
    delete ui;
}
