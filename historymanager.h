#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QObject>
#include <QVariantList>
#include <QSqlDatabase>

class HistoryManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList history READ history NOTIFY historyChanged)

public:
    explicit HistoryManager(QObject *parent = nullptr);

    void initDatabase();
    void createTable();

    Q_INVOKABLE void addHistory(const QString &expression);
    Q_INVOKABLE void loadHistory();
    Q_INVOKABLE void clearHistory();

    QVariantList history() const;

signals:
    void historyChanged();

private:
    QSqlDatabase m_db;
    QVariantList m_history;
};

#endif
