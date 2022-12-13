#ifndef REFPAGE_4_H
#define REFPAGE_4_H

#include <QWidget>
#include "ui_RefPage_4.h"

#include "RefPage_3.h"
#include "RefPage_5.h"

namespace Ui {
class RefPage_4;
}

class RefPage_4 : public QWidget
{
    Q_OBJECT
private:
    Ui::RefPage_4 *ui;
    QFile *__file_style = nullptr;
    level_save_t *__last_game = nullptr;
    QString **__game_settings = nullptr;
    QMap<QString,QString> *__style_files = nullptr;

public:
    explicit RefPage_4(QString **game_settings, level_save_t *last_game, QMap<QString,QString> *style_files, QWidget *parent = 0);
    ~RefPage_4();
signals:
    void signalGoToScreen(QWidget *);
public slots:
    void slotGoToNext();
    void slotGoToBack();
};

#endif // REFPAGE_4_H
