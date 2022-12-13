#ifndef CONTROLDATABASEMANAGER_H
#define CONTROLDATABASEMANAGER_H

#include <QMap>
#include <QString>
#include <QSqlRecord>
#include "../model/ModelDataBaseManager.h"

struct level_info_t{
    int number;
    QString path_to_image;
    QString path_to_preview;
};

class ControlDataBaseManager
{
private:
    ModelDataBaseManager *__data_base_manager = nullptr;
    QString __path_to_DB = "Puzzle_game_DB.db";
public:
    ControlDataBaseManager();

    QMap<QString,QString>* getStylesPath();
    QMap<QString,QString>* getMusicsPath();
    QVector<level_info_t>* getLevels();

    ~ControlDataBaseManager();
};

#endif // CONTROLDATABASEMANAGER_H
