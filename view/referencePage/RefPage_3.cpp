#include "RefPage_3.h"

RefPage_3::RefPage_3(QString **game_settings, level_save_t *last_game, QMap<QString,QString> *style_files, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RefPage_3)
{
    ui->setupUi(this);
    __game_settings = game_settings;
    __last_game = last_game;
    __style_files = style_files;

    __file_style = new QFile(":/styleReferencesScreen.css");
    __file_style->open(QFile::ReadOnly);
    this->setStyleSheet(__file_style->readAll());
    __file_style->close();

    connect(ui->__button_back, SIGNAL(clicked()),this,SLOT(slotGoToBack()));
    connect(ui->__button_next, SIGNAL(clicked()),this,SLOT(slotGoToNext()));
}

void RefPage_3::slotGoToBack(){
    RefPage_2 *screen = new RefPage_2(__game_settings,__last_game,__style_files);
    emit signalGoToScreen(screen);
}

void RefPage_3::slotGoToNext(){
    RefPage_4 *screen = new RefPage_4(__game_settings,__last_game,__style_files);
    emit signalGoToScreen(screen);
}

RefPage_3::~RefPage_3()
{
    disconnect(ui->__button_back, SIGNAL(clicked()),this,SLOT(slotGoToBack()));
    disconnect(ui->__button_next, SIGNAL(clicked()),this,SLOT(slotGoToNext()));
    delete __file_style;
    delete ui;
}
