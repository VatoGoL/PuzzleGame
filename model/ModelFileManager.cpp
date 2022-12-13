#include "ModelFileManager.h"
#include "QDebug"
ModelFileManager::ModelFileManager(QString path_to_file)
{
    __path_to_file = path_to_file;
}

QString* ModelFileManager::readStartSettings(QString *array_tags, int size_array_tags,
                                                      bool *array_statistic_search)
{
    QFile file_open(__path_to_file);
    file_open.open(QFile::ReadOnly);

    if(!file_open.isOpen()){
        return nullptr;
    }

    QString text_test = file_open.readAll();
    __text_stream = new QTextStream(&text_test);

    QString *result = new QString [size_array_tags];
    QString temp;

    for(;!__text_stream->atEnd();){
        *__text_stream >> temp;

        for(int i = 0; i < size_array_tags; ++i){
            if(temp == array_tags[i]){
                *__text_stream >> result[i];
                array_statistic_search[i] = true;
            }
        }
    }

    file_open.close();
    delete __text_stream;
    __text_stream = nullptr;

    return result;
}
int ModelFileManager::saveStartSettings(QString **array_tags, int size_array_tags){

    QFile file_open(__path_to_file);
    file_open.open(QFile::WriteOnly);


    if(!file_open.isOpen()){
        qDebug() << "Не открыли";
        return ERROR_OPEN_FILE;
    }

    QString text_test = "";
    __text_stream = new QTextStream(&text_test);

    int key = 0, value = 1;

    for(int i = 0; i < size_array_tags; ++i){
        *__text_stream << array_tags[i][key] << ' ' << array_tags[i][value] << "\n";
    }

    file_open.write(text_test.toUtf8());

    file_open.close();
    delete __text_stream;
    __text_stream = nullptr;

    return WRITE_SUCCEFUL;
}

struct level_save_t* ModelFileManager::readGameSave(){
    QFile file_open(__path_to_file);
    file_open.open(QFile::ReadOnly);

    if(!file_open.isOpen()){
        return nullptr;
    }

    QString text_test = file_open.readAll();
    __text_stream = new QTextStream(&text_test);

    struct level_save_t *game_save = new level_save_t;

    *__text_stream >> game_save->name_level;
    *__text_stream >> game_save->size_x;
    *__text_stream >> game_save->size_y;
    *__text_stream >> game_save->time_m;
    *__text_stream >> game_save->time_s;
    *__text_stream >> game_save->path_to_image;

    int **game_table = new int *[game_save->size_y];
    for(int i = 0; i < game_save->size_y; ++i){

        game_table[i] = new int [game_save->size_x];
        for(int j = 0; j < game_save->size_x; ++j){

            if(__text_stream->atEnd()){
                file_open.close();
                return nullptr;
            }

            *__text_stream >> game_table[i][j];
        }
    }
    game_save->game_table = game_table;

    file_open.close();
    delete __text_stream;
    __text_stream = nullptr;

    return game_save;
}

int ModelFileManager::saveGameSave(level_save_t level_save){
    QFile file_open(__path_to_file);
    file_open.open(QFile::WriteOnly | QIODevice::Text);

    if(!file_open.isOpen()){
        return ERROR_OPEN_FILE;
    }

    QString text_test = "";
    __text_stream = new QTextStream(&text_test);

    *__text_stream << level_save.name_level << ' ';
    *__text_stream << level_save.size_x << ' ';
    *__text_stream << level_save.size_y << ' ';
    *__text_stream << level_save.time_m << ' ';
    *__text_stream << level_save.time_s << ' ';
    *__text_stream << level_save.path_to_image << ' ';

    for(int i = 0; i < level_save.size_x; ++i){
        for(int j = 0; j < level_save.size_y; ++j){
            *__text_stream << level_save.game_table[i][j];
        }
    }
    file_open.write(text_test.toUtf8());

    file_open.close();
    delete __text_stream;
    __text_stream = nullptr;

    return WRITE_SUCCEFUL;
}

void ModelFileManager::setPathToFile(QString path_to_file){
    __path_to_file = path_to_file;
}
QString ModelFileManager::getPathToFile(){
    return __path_to_file;
}

ModelFileManager::~ModelFileManager()
{
    if(__text_stream != nullptr){
        delete __text_stream;
    }
}
