#include "ModelDataBaseManager.h"

ModelDataBaseManager::ModelDataBaseManager(QString path_to_DB)
{
    __data_base = new QSqlDatabase();

    *__data_base = __data_base->addDatabase("QSQLITE");
    __data_base->setDatabaseName(path_to_DB);
    __connect_to_DB = __data_base->open();

    __query = new QSqlQuery(*__data_base);
}

QSqlQuery* ModelDataBaseManager::queryToDB(QString query){
    __query->exec(query);
    return __query;
}

bool ModelDataBaseManager::connectToDB(QString path_to_DB){
    __data_base->setDatabaseName(path_to_DB);
    __connect_to_DB = __data_base->isOpen();

    return __connect_to_DB;
}
bool ModelDataBaseManager::getConnectDB(){
    return __connect_to_DB;
}

ModelDataBaseManager::~ModelDataBaseManager(){
    delete __query;
    delete __data_base;
}
