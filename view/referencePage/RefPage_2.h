#ifndef REFPAGE_2_H
#define REFPAGE_2_H

#include <QWidget>
#include "ui_RefPage_2.h"

#include "RefPage_1.h"
#include "RefPage_3.h"
namespace Ui {
class RefPage_2;
}

class RefPage_2 : public QWidget
{
    Q_OBJECT
private:
    Ui::RefPage_2 *ui;
    QFile *__file_style = nullptr;
    level_save_t *__last_game = nullptr;
    QString **__game_settings = nullptr;
    QMap<QString,QString> *__style_files = nullptr;

public:
    explicit RefPage_2(QString **game_settings, level_save_t *last_game, QMap<QString,QString> *style_files, QWidget *parent = 0);
    ~RefPage_2();
signals:
    void signalGoToScreen(QWidget *);
public slots:
    void slotGoToNext();
    void slotGoToBack();

};

#endif // REFPAGE_2_H
