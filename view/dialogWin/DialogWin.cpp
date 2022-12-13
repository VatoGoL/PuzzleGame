#include "DialogWin.h"

DialogWin::DialogWin(QString time_win,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogWin)
{
    ui->setupUi(this);

    __file_style = new QFile(":/styleDialogWin.css");
    __file_style->open(QFile::ReadOnly);
    this->setStyleSheet(__file_style->readAll());

    __time_win = time_win;
    ui->__text_time->setText("Ваше время: " + __time_win);
    connect(ui->__button_ok, SIGNAL(clicked(bool)),this,SLOT(slotCloseWindow()));
}

void DialogWin::slotCloseWindow(){
    emit signalClickOk();
    this->close();
}

DialogWin::~DialogWin()
{
    disconnect(ui->__button_ok, SIGNAL(clicked(bool)),this,SLOT(slotCloseWindow()));
    delete ui;
}
