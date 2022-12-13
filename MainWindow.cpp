#include "MainWindow.h"

MainWindow::MainWindow(QApplication *app, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    __app = app;

    __control_file_manager = new ControlFileManager(__default_path_to_settings_file, __default_path_to_game_save_file);
    __game_settings = __control_file_manager->loadSettingsGame();
    __last_game = __control_file_manager->loadLastLevel();

    __control_DB_manager = new ControlDataBaseManager();
    __style_files = __control_DB_manager->getStylesPath();
    __music_files = __control_DB_manager->getMusicsPath();

    __screen = new MainScreen(__game_settings,__last_game,__style_files,this);
    this->setCentralWidget(__screen);
    if(__game_settings[__settings_fullscreen][__settings_value] == "true"){
        this->setWindowState(Qt::WindowFullScreen);
    }
    else{
        this->setWindowState(Qt::WindowMaximized);
    }


    setAllConnect();
}
void MainWindow::setAllConnect(){
    connect(__screen,SIGNAL(signalGoToScreen(QWidget*)),this,SLOT(slotSetScreen(QWidget*)));
    connect(__screen,SIGNAL(signalSaveSettings()), this, SLOT(slotSaveSettings()));
    connect(__screen,SIGNAL(signalExit()),this,SLOT(slotExit()));
}
void MainWindow::setAllDisconnect(){
    disconnect(__screen,SIGNAL(signalGoToScreen(QWidget*)),this,SLOT(slotSetScreen(QWidget*)));
    disconnect(__screen,SIGNAL(signalSaveSettings()), this, SLOT(slotSaveSettings()));
    disconnect(__screen,SIGNAL(signalExit()),this,SLOT(slotExit()));
}
void MainWindow::slotSaveSettings(){
    __control_file_manager->saveSettingsGame(__game_settings);
    if(__game_settings[__settings_fullscreen][__settings_value] == "true"){
        this->setWindowState(Qt::WindowFullScreen);
    }
    else{
        this->setWindowState(Qt::WindowMaximized);
    }
}
void MainWindow::slotSetScreen(QWidget *screen){
    setAllDisconnect();

    __screen = screen;
    this->setCentralWidget(__screen);
    if(__last_game != nullptr){
        __control_file_manager->saveLastLevel(*__last_game);
    }
    setAllConnect();
}
void MainWindow::slotExit(){
    __app->closeAllWindows();
}
MainWindow::~MainWindow()
{
    delete __control_file_manager;

    for(int i = 0; i < __COUNT_SETTINGS_FIELD; ++i){
        delete[] __game_settings[i];
    }
    if(__last_game != nullptr){
        delete __last_game;
    }
    setAllDisconnect();
    delete ui;
}
