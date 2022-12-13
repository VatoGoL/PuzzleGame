#ifndef CONTROLFILEMANAGER_H
#define CONTROLFILEMANAGER_H
#include <QDebug>
#include <QString>

#include "../model/ModelFileManager.h"

class ControlFileManager
{
private:
    ModelFileManager *__file_manager = nullptr;
    QString __path_to_settings_file;
    QString __path_to_game_save_file;

    static const int __COUNT_SETTINGS_FIELDS = 3;
    int __field_key_and_value = 2;
    int __field_key = 0;
    int __field_value = 1;
    QString __settings_fields[__COUNT_SETTINGS_FIELDS] = {
        "Screen_resolution",
        "Fullscreen",
        "Music"
    };
    QString __default_settings_fields_value [__COUNT_SETTINGS_FIELDS]{
        "1920x1080",
        "true",
        "false"
    };
public:
    ControlFileManager(QString path_to_settings_file, QString path_to_game_save_file);

    QString** loadSettingsGame();
    void saveSettingsGame(QString **array_tags);
    struct level_save_t* loadLastLevel();
    void saveLastLevel(struct level_save_t level_save);

    ~ControlFileManager();
};

#endif // CONTROLFILEMANAGER_H
