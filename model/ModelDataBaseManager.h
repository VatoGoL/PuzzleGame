#ifndef MODELDATABASEMANAGER_H
#define MODELDATABASEMANAGER_H

#include <QtSql/QtSql>
#include <QString>

class ModelDataBaseManager
{
private:

    QSqlDatabase *__data_base = nullptr;
    QSqlQuery *__query = nullptr;
    bool __connect_to_DB = false;

public:
    ModelDataBaseManager(QString path_to_DB);

    QSqlQuery* queryToDB(QString query);
    bool connectToDB(QString path_to_DB);
    bool getConnectDB();

    ~ModelDataBaseManager();
};

#endif // MODELDATABASEMANAGER_H
