#include "createOwnGame.h"

createOwnGame::createOwnGame(QString **game_settings, level_save_t *last_game, QMap<QString,QString> *style_files, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::createOwnGame)
{
    ui->setupUi(this);

    __game_settings = game_settings;
    __last_game = last_game;

    __style_files = style_files;
    __file_style = new QFile( (*style_files)["CreateOwnGame"] );
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
    ui->__w_load_images->setGraphicsEffect(&__effect_shadow[__w_load_images]);
    ui->__button_back->setGraphicsEffect(&__effect_shadow[__button_back]);
    ui->__button_next->setGraphicsEffect(&__effect_shadow[__button_next]);
    ui->__button_next->setStyleSheet("background-color: #377873;");

    connect(ui->__button_back,SIGNAL(clicked()),this,SLOT(slotGoToSelectGameMode()));
    connect(ui->__button_next,SIGNAL(clicked()),this,SLOT(slotGoToSelectDifficultGame()));
}

void createOwnGame::mousePressEvent(QMouseEvent *event){
    if(event->x() >= (ui->__w_load_images->x() +
                      ui->__wrapper->pos().x() +
                      ui->__content_box->pos().x())
        && event->x() <= (ui->__wrapper->pos().x() +
                          ui->__content_box->pos().x() +
                          (ui->__w_load_images->x()+ui->__w_load_images->width())))
    {
        if(event->y() >= (ui->__w_load_images->y() +
                          ui->__wrapper->pos().y() +
                          ui->__content_box->pos().y())
            && event->y() <= (ui->__wrapper->pos().y() +
                              ui->__content_box->pos().y() +
                              (ui->__w_load_images->y()+ui->__w_load_images->height())))
        {
            __file_name = QFileDialog::getOpenFileName(this,tr("Открыть изображение"), "../../", tr("Изображения (*.png *.jpg *.bmp *.webp)"));
            if(__file_name != ""){
                ui->__button_next->setStyleSheet("background-color: #00635B;");
                __preview_image = new QPixmap(__file_name);
                ui->__preview_label->setPixmap(*__preview_image);
            }
        }
    }
}

void createOwnGame::slotGoToSelectGameMode(){
    SelectGameMode *screen = new SelectGameMode(__game_settings,__last_game, __style_files);
    emit signalGoToScreen(screen);
}
void createOwnGame::slotGoToSelectDifficultGame(){

    if(__file_name != ""){
        if(__last_game == nullptr){
            __last_game = new level_save_t;
        }
        __last_game->name_level = "Own game";
        __last_game->path_to_image = __file_name;
        __last_game->time_m = 0;
        __last_game->time_s = 0;
        SelectDifficultGame *screen = new SelectDifficultGame(__game_settings,__last_game,__style_files, "CreateOwnGame");
        emit signalGoToScreen(screen);
    }

}
createOwnGame::~createOwnGame()
{
    disconnect(ui->__button_back,SIGNAL(clicked()),this,SLOT(slotGoToSelectGameMode()));
    disconnect(ui->__button_next,SIGNAL(clicked()),this,SLOT(slotGoToSelectDifficultGame()));
    if(__preview_image != nullptr){
        delete __preview_image;
    }
    delete __file_style;
    delete ui;
}
