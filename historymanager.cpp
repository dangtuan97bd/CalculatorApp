#include "historymanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

HistoryManager::HistoryManager(QObject *parent)
    : QObject(parent)
{
    initDatabase();
}

void HistoryManager::initDatabase()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("calculator.db");

    if (!m_db.open()) {
        qDebug() << "DB open failed:" << m_db.lastError().text();
        return;
    }

    createTable();
}

void HistoryManager::createTable()
{
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS history ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "expression TEXT)");
}

void HistoryManager::addHistory(const QString &expression)
{
    QSqlQuery query;
    query.prepare("INSERT INTO history (expression) VALUES (:exp)");
    query.bindValue(":exp", expression);

    if (!query.exec()) {
        qDebug() << "Insert failed:" << query.lastError().text();
        return;
    }

    m_history.prepend(expression);
    emit historyChanged();
}

void HistoryManager::loadHistory()
{
    m_history.clear();

    QSqlQuery query("SELECT expression FROM history ORDER BY id DESC LIMIT 50");

    while (query.next()) {
        m_history.append(query.value(0).toString());
    }

    emit historyChanged();
}

void HistoryManager::clearHistory()
{
    QSqlQuery query;
    query.exec("DELETE FROM history");

    m_history.clear();
    emit historyChanged();
}

QVariantList HistoryManager::history() const
{
    return m_history;
}
