#include "ControlFileManager.h"

ControlFileManager::ControlFileManager(QString path_to_settings_file, QString path_to_game_save_file)
{
    __path_to_settings_file = path_to_settings_file;
    __path_to_game_save_file = path_to_game_save_file;
    __file_manager = new ModelFileManager(__path_to_settings_file);
}

QString** ControlFileManager::loadSettingsGame(){
    QString **result = new QString *[__COUNT_SETTINGS_FIELDS];
    bool *settings_field_flags = new bool [__COUNT_SETTINGS_FIELDS];

    for(int i = 0; i < __COUNT_SETTINGS_FIELDS; ++i){
        result[i] = new QString [__field_key_and_value];
        result[i][__field_key] = __settings_fields[i];
        settings_field_flags[i] = false;
    }

    __file_manager->setPathToFile(__path_to_settings_file);

    QString *temp;
    temp = __file_manager->readStartSettings(__settings_fields,__COUNT_SETTINGS_FIELDS,settings_field_flags);

    if(temp == nullptr){
        qDebug() << "Файлы настроек не загрузились";
        temp = new QString [__COUNT_SETTINGS_FIELDS];
    }

    for(int i = 0; i < __COUNT_SETTINGS_FIELDS; ++i){
        if(settings_field_flags[i] == false){
            temp[i] = __default_settings_fields_value[i];
        }
        result[i][__field_value] = temp[i];

    }

    delete[] temp;
    delete[] settings_field_flags;

    return result;
}
void ControlFileManager::saveSettingsGame(QString **array_tags){
    int flag_save;

    __file_manager->setPathToFile(__path_to_settings_file);

    flag_save = __file_manager->saveStartSettings(array_tags,__COUNT_SETTINGS_FIELDS);
    if(flag_save == ERROR_OPEN_FILE){
        qDebug() << "Ошибка сохранения настроек приложения! Возможно нет доступа к указаной директории\n";
    }
    return;
}
struct level_save_t* ControlFileManager::loadLastLevel(){
    struct level_save_t *result = new struct level_save_t;

    __file_manager->setPathToFile(__path_to_game_save_file);

    result = __file_manager->readGameSave();
    if(result == nullptr){
        qDebug() << "Не получилось загрузить сохранение игры.\n Возможные причины:\n";
        qDebug() << "1. Ошибка с открытием файла, нет у пользователя прав доступа к этой директории\n";
        qDebug() << "2. Файл не содержит достаточно данных он битый.";
    }

    return result;
}
void ControlFileManager::saveLastLevel(struct level_save_t level_save){
    int flag_save;

    __file_manager->setPathToFile(__path_to_game_save_file);

    flag_save = __file_manager->saveGameSave(level_save);
    if(flag_save == ERROR_OPEN_FILE){
        qDebug() << "Ошибка сохранения настроек приложения! Возможно нет доступа к указаной директории\n";
    }
    return;
}

ControlFileManager::~ControlFileManager()
{
    delete __file_manager;
}
