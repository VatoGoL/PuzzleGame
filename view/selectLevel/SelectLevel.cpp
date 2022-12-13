#include "SelectLevel.h"

SelectLevel::SelectLevel(QString **game_settings, level_save_t *last_game, QMap<QString,QString> *style_files, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectLevel)
{
    ui->setupUi(this);

    __game_settings = game_settings;
    __last_game = last_game;

    __style_files = style_files;
    __file_style = new QFile( (*style_files)["SelectLevel"] );
    __file_style->open(QFile::ReadOnly);
    this->setStyleSheet(__file_style->readAll());

    __effect_shadow = new QGraphicsDropShadowEffect [__COUNT_SHADOW_ELEMENT];
    for(int i = 0, length = __COUNT_SHADOW_ELEMENT-1; i < length; ++i){
        __effect_shadow[i].setBlurRadius(4);
        __effect_shadow[i].setXOffset(0);
        __effect_shadow[i].setYOffset(4);
        __effect_shadow[i].setColor(QColor(0,0,0,64));
    }

    ui->__content_box->setGraphicsEffect(&__effect_shadow[__content_box]);
    ui->__button_back->setGraphicsEffect(&__effect_shadow[__button_back]);
    ui->__level_slider->setGraphicsEffect(&__effect_shadow[__level_slider]);
    //ui->__level_number_1->setGraphicsEffect(&__effect_shadow[__level_number_1]);


    connect(ui->__button_back,SIGNAL(clicked()),this,SLOT(slotGoToLastScreen()));
    __createLevels();
}

void SelectLevel::__createLevels(){

    QFont temp_font("Marmelad",36);
    __scroll_area = new QScrollArea(ui->__content_box);

    __scroll_area->setWidget(ui->__levels_box);
    __scroll_area->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    __scroll_area->setGeometry(34,23,1731,520);
    __scroll_area->setMinimumSize(1731,520);
    __scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    __scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    __scroll_area->setStyleSheet("border:none;");
    ui->__content_box->layout()->removeWidget(ui->__tools_w);
    ui->__content_box->layout()->addWidget(__scroll_area);
    ui->__content_box->layout()->addWidget(ui->__tools_w);
    __scroll_area->widget()->layout()->setSpacing(40);
    __scroll_area->setWidgetResizable(false);

    //__scroll_area->scroll(10,0);
    ControlDataBaseManager dbm;
    __levels_info = dbm.getLevels();

    __widget_levels_element = new QWidget *[__levels_info->size()];
    __label_levels_element = new QLabel *[__levels_info->size()];
    __v_layout_levels = new QVBoxLayout *[__levels_info->size()];

    for(int i = 0; i < __levels_info->size(); ++i){
        __widget_levels_element[i] = new QWidget [__COUNT_WIDGET_ELEMENT];
        __label_levels_element[i] = new QLabel [__COUNT_LABEL_ELEMENT];
        __v_layout_levels[i] = new QVBoxLayout[__COUNT_V_LOYOUT_ELEMENT];

        //__widget_levels_element[i][__level_box].setParent(ui->__levels_box);
        ui->__levels_box->layout()->addWidget(&__widget_levels_element[i][__level_box]);
        __widget_levels_element[i][__level_image_box].setParent(&__widget_levels_element[i][__level_box]);
        __widget_levels_element[i][__level_number_box].setParent(&__widget_levels_element[i][__level_box]);

        __label_levels_element[i][__level_image].setParent(&__widget_levels_element[i][__level_image_box]);
        __label_levels_element[i][__level_number].setParent(&__widget_levels_element[i][__level_number_box]);

        __widget_levels_element[i][__level_box].setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        __widget_levels_element[i][__level_box].setGeometry(0,0,374,456);
        __widget_levels_element[i][__level_box].setMinimumSize(374,456);
        __widget_levels_element[i][__level_image_box].setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        __widget_levels_element[i][__level_image_box].setGeometry(20,0,334,456);
        __widget_levels_element[i][__level_image_box].setMinimumSize(334,456);
        __widget_levels_element[i][__level_number_box].setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        __widget_levels_element[i][__level_number_box].setGeometry(0,349,374,90);
        __widget_levels_element[i][__level_number_box].setMinimumSize(374,90);

        ui->__levels_box->layout()->addWidget(&__widget_levels_element[i][__level_box]);
        __v_layout_levels[i][__level_image].addWidget(&__label_levels_element[i][__level_image]);
        __v_layout_levels[i][__level_number].addWidget(&__label_levels_element[i][__level_number]);

        __widget_levels_element[i][__level_image_box].setLayout(&__v_layout_levels[i][__level_image]);
        __widget_levels_element[i][__level_number_box].setLayout(&__v_layout_levels[i][__level_number]);

        __label_levels_element[i][__level_image].setPixmap(QPixmap(__levels_info->at(i).path_to_preview));
        __label_levels_element[i][__level_number].setFont(temp_font);
        __label_levels_element[i][__level_number].setText(QString("Уровень ") + QString().setNum(__levels_info->at(i).number) );
        __label_levels_element[i][__level_number].setAlignment(Qt::AlignCenter);
        __widget_levels_element[i][__level_image_box].setStyleSheet("background-color: #536B69;");
        __widget_levels_element[i][__level_number_box].setStyleSheet("background-color: #00CA8D;");
        __label_levels_element[i][__level_number].setStyleSheet("color: #F9F9F9;");

    }

}

void SelectLevel::slotGoToLastScreen(){
    SelectGameMode *screen = new SelectGameMode(__game_settings,__last_game, __style_files);
    emit signalGoToScreen(screen);
}
void SelectLevel::mousePressEvent(QMouseEvent *event){
   // QWidget **level_card = new QWidget *[__levels_info->size()];


    for(int i = 0; i < __levels_info->size(); ++i){

        if(event->x() >= (__widget_levels_element[i][__level_box].x() +
                          ui->__content_box->pos().x() +
                          ui->__levels_box->pos().x())
            && event->x() <= (ui->__content_box->pos().x() +
                              ui->__levels_box->pos().x() +
                              (__widget_levels_element[i][__level_box].x()+__widget_levels_element[i][__level_box].width())))
        {
            if(event->y() >= (__widget_levels_element[i][__level_box].y() +
                              ui->__content_box->pos().y() +
                              ui->__levels_box->pos().y())
                && event->y() <= (ui->__content_box->pos().y() +
                                  ui->__levels_box->pos().y() +
                                  (__widget_levels_element[i][__level_box].y()+__widget_levels_element[i][__level_box].height())))
            {
                //Создаём уровень 1
                if(__last_game == nullptr){
                    __last_game = new level_save_t;
                }
                __last_game->name_level = "level_" + QString().setNum(__levels_info->at(i).number);
                __last_game->path_to_image = __levels_info->at(i).path_to_image;
                __last_game->time_m = 0;
                __last_game->time_s = 0;
                SelectDifficultGame *screen = new SelectDifficultGame(__game_settings,__last_game,__style_files, "SelectLevel");
                emit signalGoToScreen(screen);
            }
        }
    }

    //delete[] level_card;
}
SelectLevel::~SelectLevel()
{
    disconnect(ui->__button_back,SIGNAL(clicked()),this,SLOT(slotGoToLastScreen()));
    delete __file_style;
    delete ui;
}
