#ifndef REFPAGE_5_H
#define REFPAGE_5_H

#include <QWidget>
#include "ui_RefPage_5.h"

#include "RefPage_4.h"

namespace Ui {
class RefPage_5;
}

class RefPage_5 : public QWidget
{
    Q_OBJECT
private:
    Ui::RefPage_5 *ui;
    QFile *__file_style = nullptr;
    level_save_t *__last_game = nullptr;
    QString **__game_settings = nullptr;
    QMap<QString,QString> *__style_files = nullptr;

public:
    explicit RefPage_5(QString **game_settings, level_save_t *last_game, QMap<QString,QString> *style_files, QWidget *parent = 0);
    ~RefPage_5();
signals:
    void signalGoToScreen(QWidget *);
public slots:
    void slotGoToBack();

};

#endif // REFPAGE_5_H
