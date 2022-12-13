#ifndef DIALOGWIN_H
#define DIALOGWIN_H

#include <QDialog>
#include <QFile>
#include "ui_DialogWin.h"

namespace Ui {
class DialogWin;
}

class DialogWin : public QDialog
{
    Q_OBJECT

private:
    Ui::DialogWin *ui;
    QString __time_win;
    QFile *__file_style;

public:
    explicit DialogWin(QString time_win, QWidget *parent = 0);
    ~DialogWin();
signals:
    void signalClickOk();
public slots:
    void slotCloseWindow();
};

#endif // DIALOGWIN_H
