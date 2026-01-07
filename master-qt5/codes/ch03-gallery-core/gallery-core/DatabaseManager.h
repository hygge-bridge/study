#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

class QSqlDatabase;

class DatabaseManager
{
public:
    static DatabaseManager& instance();

private:
    DatabaseManager();
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

private:
    QSqlDatabase& mDatabase;
};

#endif // DATABASEMANAGER_H
