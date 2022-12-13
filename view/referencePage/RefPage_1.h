#ifndef REFPAGE_1_H
#define REFPAGE_1_H

#include <QWidget>
#include <QFile>
#include "ui_RefPage_1.h"

#include "../mainScreen/MainScreen.h"
#include "RefPage_2.h"

namespace Ui {
class RefPage_1;
}

class RefPage_1 : public QWidget
{
    Q_OBJECT


private:
    Ui::RefPage_1 *ui;
    QFile *__file_style = nullptr;
    level_save_t *__last_game = nullptr;
    QString **__game_settings = nullptr;
    QMap<QString,QString> *__style_files = nullptr;

public:
    explicit RefPage_1(QString **game_settings, level_save_t *last_game, QMap<QString,QString> *style_files, QWidget *parent = 0);
    ~RefPage_1();

signals:
    void signalGoToScreen(QWidget *);
public slots:
    void slotGoToNext();
    void slotGoToBack();
};

#endif // REFPAGE_1_H
