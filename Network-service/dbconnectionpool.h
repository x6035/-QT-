// DbConnectionPool.h
#ifndef DBCONNECTIONPOOL_H
#define DBCONNECTIONPOOL_H

#include <QSqlDatabase>
#include <QMutex>
#include <QQueue>
#include <QDebug>

class DbConnectionPool
{
public:
    static DbConnectionPool& getInstance() {
        static DbConnectionPool instance;
        return instance;
    }

    QSqlDatabase getConnection() {
        QMutexLocker locker(&mutex);
        if (!availableConnections.isEmpty()) {
            return availableConnections.dequeue();
        } else {
            return QSqlDatabase::addDatabase("QSQLITE", QString("Conn%1").arg(++connectionCount));
        }
    }

    void releaseConnection(const QSqlDatabase& db) {
        QMutexLocker locker(&mutex);
        availableConnections.enqueue(db);
    }

private:
    DbConnectionPool() : connectionCount(0) {}
    ~DbConnectionPool() {
        while (!availableConnections.isEmpty()) {
            QSqlDatabase db = availableConnections.dequeue();
            db.close();
        }
    }

    DbConnectionPool(const DbConnectionPool&) = delete;
    DbConnectionPool& operator=(const DbConnectionPool&) = delete;

    QMutex mutex;
    QQueue<QSqlDatabase> availableConnections;
    int connectionCount;
};

#endif // DBCONNECTIONPOOL_H
