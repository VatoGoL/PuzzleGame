#ifndef REFPAGE_3_H
#define REFPAGE_3_H

#include <QWidget>
#include "ui_RefPage_3.h"

#include "RefPage_2.h"
#include "RefPage_4.h"

namespace Ui {
class RefPage_3;
}

class RefPage_3 : public QWidget
{
    Q_OBJECT

private:
    Ui::RefPage_3 *ui;
    QFile *__file_style = nullptr;
    level_save_t *__last_game = nullptr;
    QString **__game_settings = nullptr;
    QMap<QString,QString> *__style_files = nullptr;

public:
    explicit RefPage_3(QString **game_settings, level_save_t *last_game, QMap<QString,QString> *style_files, QWidget *parent = 0);
    ~RefPage_3();
signals:
    void signalGoToScreen(QWidget *);
public slots:
    void slotGoToNext();
    void slotGoToBack();

};

#endif // REFPAGE_3_H
