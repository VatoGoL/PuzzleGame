#include "GameWindow.h"

GameWindow::GameWindow(QString **game_settings, level_save_t *last_game, QMap<QString,QString> *style_files, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    __game_settings = game_settings;
    __last_game = last_game;

    __style_files = style_files;
    __file_style = new QFile( (*style_files)["GameWindow"] );
    __file_style->open(QFile::ReadOnly);
    this->setStyleSheet(__file_style->readAll());

    __effect_shadow = new QGraphicsDropShadowEffect [__COUNT_SHADOW_ELEMENT];
    for(int i = 0; i < __COUNT_SHADOW_ELEMENT; ++i){
        __effect_shadow[i].setBlurRadius(8);
        __effect_shadow[i].setXOffset(0);
        __effect_shadow[i].setYOffset(4);
        __effect_shadow[i].setColor(QColor(0,0,0,64));
    }

    ui->__game_zone_box->setGraphicsEffect(&__effect_shadow[__game_zone_box]);
    ui->__game_zone->setGraphicsEffect(&__effect_shadow[__game_zone]);
    ui->__preview_box->setGraphicsEffect(&__effect_shadow[__preview_box]);
    ui->__preview_image->setGraphicsEffect(&__effect_shadow[__preview_image]);
    ui->__tools_box->setGraphicsEffect(&__effect_shadow[__tools_box]);


    __game_image = new QPixmap(__last_game->path_to_image);
    *__game_image = __game_image->scaled(ui->__game_zone->width(),ui->__game_zone->height());
    ui->__preview_label->setPixmap(*__game_image);
    __generateGameTable();

    for(int i = 0; i < __last_game->size_y; ++i){
        for(int j = 0; j < __last_game->size_x; ++j){
            connect(__game_table[i][j], SIGNAL(clicked(bool)),this, SLOT(slotGameZoneClick()));
        }
    }

    __time_game = new QTime(0,0,__last_game->time_m,__last_game->time_s);
    *__time_game = __time_game->addSecs(__last_game->time_m * 60 + __last_game->time_s);
    ui->__time_text->setText("Время " + __time_game->toString("mm:ss"));

    __timer = new QTimer(this);
    connect(__timer,SIGNAL(timeout()),this,SLOT(slotTimeOut()));
    __timer->start(1000);

}

void GameWindow::slotWinGame(){
    SelectGameMode *screen;
    if(__last_game != nullptr){
        if(__last_game->game_table != nullptr){
            for(int i = 0; i < __last_game->size_y; ++i){
                for(int j = 0; j < __last_game->size_y; ++j){
                    disconnect(__game_table[i][j], SIGNAL(clicked()),this, SLOT(slotGameZoneClick()));
                }
                delete[] __game_table[i];
                delete[] __last_game->game_table[i];
            }
            delete[] __game_table;
            delete[] __image_game_table;
            delete[] __last_game->game_table;
        }
        delete __last_game;
    }
    __last_game = nullptr;
    screen = new SelectGameMode(__game_settings,__last_game, __style_files);
    emit signalGoToScreen(screen);
}

bool GameWindow::__checkWinGame(){
    for(int i = 0, temp = 0; i < __last_game->size_y; ++i){
        for(int j = 0; j < __last_game->size_x; ++j){
            if(temp != __last_game->game_table[i][j]){
                return false;

            }
            temp++;
        }
    }
    return true;
}

void GameWindow::slotTimeOut(){
    *__time_game = __time_game->addSecs(1);
    ui->__time_text->setText("Время " + __time_game->toString("mm:ss"));
}

void GameWindow::__viewHelp(){
    if(__view_help == false){
        __view_help = true;

        for(int i = 0; i < __last_game->size_y; ++i){
            for(int j = 0; j < __last_game->size_x; ++j){
                __game_table[i][j]->setText( QString().setNum(__last_game->game_table[i][j] + 1) );
                __game_table[i][j]->setIconSize(QSize(0,0));
            }
        }
    }
    else{
        __view_help = false;

        for(int i = 0; i < __last_game->size_y; ++i){
            for(int j = 0; j < __last_game->size_x; ++j){
                __game_table[i][j]->setText("");
                __game_table[i][j]->setIconSize(QSize(size_x,size_y));
            }
        }
    }
}
void GameWindow::slotGameZoneClick(){
    if(__view_help == true){
        __viewHelp();
    }

    for(int i = 0; i < __last_game->size_y; ++i){
        for(int j = 0; j < __last_game->size_x; ++j){
            if(__game_table[i][j]->objectName() == QObject::sender()->objectName()){
                if(__swap_y == -1){
                    __swap_y = i;
                    __swap_x = j;
                }
                else{
                    if(i != __swap_y || j != __swap_x){
                        QString temp_str_one = __game_table[__swap_y][__swap_x]->objectName();
                        QIcon temp_icon_one = __game_table[__swap_y][__swap_x]->icon();
                        QSize temp_icon_size_one = __game_table[__swap_y][__swap_x]->iconSize();

                        QString temp_str_two = __game_table[i][j]->objectName();
                        QIcon temp_icon_two = __game_table[i][j]->icon();
                        QSize temp_icon_size_two = __game_table[i][j]->iconSize();

                        __game_table[__swap_y][__swap_x]->setObjectName(temp_str_two);
                        __game_table[__swap_y][__swap_x]->setIcon(temp_icon_two);
                        __game_table[__swap_y][__swap_x]->setIconSize(temp_icon_size_two);

                        __game_table[i][j]->setObjectName(temp_str_one);
                        __game_table[i][j]->setIcon(temp_icon_one);
                        __game_table[i][j]->setIconSize(temp_icon_size_one);

                        int temp = __last_game->game_table[__swap_y][__swap_x];
                        __last_game->game_table[__swap_y][__swap_x] = __last_game->game_table[i][j];
                        __last_game->game_table[i][j] = temp;

                        __swap_y = -1;
                        __swap_x = -1;

                        //Победа в игре
                        if(__checkWinGame()){
                            __timer->stop();
                            __dialog_win = new DialogWin(__time_game->toString("mm:ss"),this);
                            connect(__dialog_win,SIGNAL(signalClickOk()),this,SLOT(slotWinGame()));
                            __dialog_win->open();
                        }
                    }
                }
            }
        }
    }
}
void GameWindow::__generateGameTable(){

    int temp_x = 0;
    int temp_y = 0;
    int temp = 0;
    if(__last_game->time_s == 0 && __last_game->time_m == 0){
        for(int i = 0; i < __last_game->size_y; ++i){
            for(int j = 0; j < __last_game->size_x; ++j){
                temp_y = QRandomGenerator::global()->bounded(0, __last_game->size_y);
                temp_x = QRandomGenerator::global()->bounded(0, __last_game->size_x);
                temp = __last_game->game_table[temp_y][temp_x];
                __last_game->game_table[temp_y][temp_x] = __last_game->game_table[i][j];
                __last_game->game_table[i][j] = temp;
            }
        }
    }

    __image_game_table = new QPixmap [__last_game->size_y * __last_game->size_x];
    temp = 0;
    temp_x = ui->__game_zone->width() / __last_game->size_x;
    temp_y = ui->__game_zone->height() / __last_game->size_y;
    size_x = temp_x;
    size_y = temp_y;
    for(int i = 0; i < __last_game->size_y; ++i){
        for(int j = 0; j < __last_game->size_x; ++j){
            __image_game_table[temp] = __game_image->copy(j * temp_x, i * temp_y, temp_x, temp_y);
            temp++;
        }
    }

    temp = 0;
    __grid_layout = new QGridLayout(this);
    __grid_layout->setMargin(0);
    __grid_layout->setContentsMargins(0,30,0,30);
    __grid_layout->setVerticalSpacing(0);
    __grid_layout->setHorizontalSpacing(0);

    __game_table = new QPushButton **[__last_game->size_y];
    for(int i = 0; i < __last_game->size_y; ++i){
        __game_table[i] = new QPushButton *[__last_game->size_x];
        for(int j = 0; j < __last_game->size_x; ++j){
            QFont font;
            font.setFamily("Marmelad");
            font.setPointSize(30);
            __game_table[i][j] = new QPushButton;
            __game_table[i][j]->setIcon(QIcon(__image_game_table[ __last_game->game_table[i][j] ]));
            __game_table[i][j]->setIconSize(QSize(temp_x,temp_y));
            __game_table[i][j]->setObjectName(QString("__game_table_but_") + QString().setNum(temp));
            __game_table[i][j]->setMinimumSize(temp_x, temp_y);
            __game_table[i][j]->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
            __game_table[i][j]->setParent(ui->__game_zone);
            __game_table[i][j]->setCursor(QCursor(Qt::PointingHandCursor));
            __game_table[i][j]->setFont(font);
            __game_table[i][j]->setStyleSheet("background-color: #00635B; color: #F9F9F9;");
            __grid_layout->addWidget(__game_table[i][j],i,j);
            temp++;
        }
    }

    ui->__game_zone->setLayout(__grid_layout);
}

void GameWindow::mousePressEvent(QMouseEvent *event){
    QLabel **tools_element = new QLabel *[__COUNT_TOOLS];
    tools_element[__tool_help] = ui->__tools_help;
    tools_element[__tool_start] = ui->__tools_start;
    tools_element[__tool_pause] = ui->__tools_pause;
    tools_element[__tool_home] = ui->__tools_home;

    for(int i = 0; i < __COUNT_TOOLS; ++i){

        if(event->x() >= (tools_element[i]->x() +
                          ui->__contact_box->pos().x() +
                          ui->__tools_box->pos().x())
            && event->x() <= (ui->__contact_box->pos().x() +
                              ui->__tools_box->pos().x() +
                              (tools_element[i]->x()+tools_element[i]->width())))
        {
            if(event->y() >= (tools_element[i]->y() +
                              ui->__contact_box->pos().y() +
                              ui->__tools_box->pos().y())
                && event->y() <= (ui->__contact_box->pos().y() +
                                  ui->__tools_box->pos().y() +
                                  (tools_element[i]->y()+tools_element[i]->height())))
            {
                SelectGameMode *screen;
                switch(i){
                    case __tool_home:
                        __last_game->time_m = __time_game->minute();
                        __last_game->time_s = __time_game->second();
                        screen = new SelectGameMode(__game_settings,__last_game,__style_files);
                        emit signalGoToScreen(screen);
                        break;
                    case __tool_pause:
                        __timer->stop();
                        break;
                    case __tool_start:
                        __timer->start(1000);
                        break;
                    case __tool_help:
                        __viewHelp();
                        break;
                }

            }
        }
    }

    delete[] tools_element;
}
GameWindow::~GameWindow()
{
    disconnect(__timer,SIGNAL(timeout()),this,SLOT(slotTimeOut()));
    disconnect(__dialog_win,SIGNAL(signalClickOk()),this,SLOT(slotWinGame()));
    if(__dialog_win != nullptr){
        delete __dialog_win;
    }
    delete __timer;
    delete __time_game;
    delete __game_image;
    delete __file_style;
    delete ui;
}
