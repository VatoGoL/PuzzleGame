#include "ControlDataBaseManager.h"

ControlDataBaseManager::ControlDataBaseManager()
{
    __data_base_manager = new ModelDataBaseManager(__path_to_DB);
}
QMap<QString,QString>* ControlDataBaseManager::getStylesPath(){

    QString query = "SELECT name_screen, path FROM Path_to_css";
    QMap<QString,QString> *result;

    if(__data_base_manager->getConnectDB()){
        result = new QMap<QString,QString>;
        QSqlQuery *query_result = __data_base_manager->queryToDB(query);
        QString key, value;

        for(;query_result->next();){
            key = query_result->value("name_screen").toString();
            value = query_result->value("path").toString();
            (*result)[key] = value;
        }
    }
    else{
        return nullptr;
    }

    return result;
}
QMap<QString,QString>* ControlDataBaseManager::getMusicsPath(){

    QString query = "SELECT id, path_to_music FROM Path_to_music";
    QMap<QString,QString> *result;

    if(__data_base_manager->getConnectDB()){
        result = new QMap<QString,QString>;

        QSqlQuery *query_result = __data_base_manager->queryToDB(query);
        QString key, value;

        for(;query_result->next();){
            key = query_result->value("id").toString();
            value = query_result->value("path_to_music").toString();
            (*result)[key] = value;
        }

    }
    else{
        return nullptr;
    }

    return result;
}
QVector<level_info_t>* ControlDataBaseManager::getLevels(){
    QString query = "SELECT level_number, path_to_level_image, path_to_level_preview FROM Info_level";
    QVector<level_info_t> *result;

    if(__data_base_manager->getConnectDB()){
        result = new QVector<level_info_t>;

        QSqlQuery *query_result = __data_base_manager->queryToDB(query);
        level_info_t temp_result;
        for(;query_result->next();){
            temp_result.number = query_result->value("level_number").toInt();
            temp_result.path_to_image = query_result->value("path_to_level_image").toString();
            temp_result.path_to_preview = query_result->value("path_to_level_preview").toString();

            result->push_back(temp_result);
        }

    }
    else{
        return nullptr;
    }

    return result;
}

ControlDataBaseManager::~ControlDataBaseManager(){
    delete __data_base_manager;
}
