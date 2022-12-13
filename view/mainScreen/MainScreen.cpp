#include "MainScreen.h"

MainScreen::MainScreen(QString **game_settings, level_save_t *last_game, QMap<QString,QString> *style_files, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainScreen)
{
    ui->setupUi(this);

    __game_settings = game_settings;
    __last_game = last_game;

    __style_files = style_files;
    __file_style = new QFile( (*style_files)["MainScreen"] );
    __file_style->open(QFile::ReadOnly);
    this->setStyleSheet(__file_style->readAll());

    QGraphicsDropShadowEffect *__effect_shadow = new QGraphicsDropShadowEffect [__COUNT_SHADOW_ELEMENT];

    for(int i = 0; i < __COUNT_SHADOW_ELEMENT; ++i){
        __effect_shadow[i].setBlurRadius(8);
        __effect_shadow[i].setXOffset(0);
        __effect_shadow[i].setYOffset(4);
        __effect_shadow[i].setColor(QColor(0,0,0,64));
    }

    ui->__button_start->setGraphicsEffect(&__effect_shadow[__button_start]);
    ui->__button_settings->setGraphicsEffect(&__effect_shadow[__button_settings]);
    ui->__button_exit->setGraphicsEffect(&__effect_shadow[__button_exit]);

    connect(ui->__button_settings,SIGNAL(clicked()),this,SLOT(slotGoToSettingsScreen()));
    connect(ui->__button_start,SIGNAL(clicked()),this,SLOT(slotGoToSelectGameMode()));
    connect(ui->__button_reference, SIGNAL(clicked()), this, SLOT(slotGoToReferencesScreen()));
    connect(ui->__button_exit,SIGNAL(clicked()),this,SLOT(slotExit()));
}

void MainScreen::slotGoToReferencesScreen(){
    RefPage_1 *screen = new RefPage_1(__game_settings, __last_game, __style_files);
    emit signalGoToScreen(screen);
}
void MainScreen::slotGoToSettingsScreen(){
    SettingsScreen *screen = new SettingsScreen(__game_settings,__last_game, __style_files);
    emit signalGoToScreen(screen);
}
void MainScreen::slotGoToSelectGameMode(){
    SelectGameMode *screen = new SelectGameMode(__game_settings,__last_game, __style_files);
    emit signalGoToScreen(screen);
}
void MainScreen::slotExit(){
    emit signalExit();
}
MainScreen::~MainScreen()
{
    disconnect(ui->__button_settings,SIGNAL(clicked()),this,SLOT(slotGoToSettingsScreen()));
    disconnect(ui->__button_start,SIGNAL(clicked()),this,SLOT(slotGoToSelectGameMode()));
    disconnect(ui->__button_reference, SIGNAL(clicked()), this, SLOT(slotGoToReferencesScreen()));
    disconnect(ui->__button_exit,SIGNAL(clicked()),this,SLOT(slotExit()));
    delete __file_style;
    delete ui;
}
