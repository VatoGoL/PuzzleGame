#include "RefPage_5.h"

RefPage_5::RefPage_5(QString **game_settings, level_save_t *last_game, QMap<QString,QString> *style_files, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RefPage_5)
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
}
void RefPage_5::slotGoToBack(){
    RefPage_4 *screen = new RefPage_4(__game_settings,__last_game,__style_files);
    emit signalGoToScreen(screen);
}


RefPage_5::~RefPage_5()
{
    disconnect(ui->__button_back, SIGNAL(clicked()),this,SLOT(slotGoToBack()));
    delete __file_style;
    delete ui;
}
