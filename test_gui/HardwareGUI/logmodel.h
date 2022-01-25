#ifndef TOPICMODEL_H
#define TOPICMODEL_H

#include <QAbstractListModel>
#include <QColor>
#include <algorithm>

#include "topics.h"

struct Log {
    QString topic;
    QString message;
};

class LogModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum LogRoles {
        TopicRole = Qt::UserRole + 1,
        MessageRole
    };

    LogModel(QObject *parent = nullptr);

    void addLog(const Log &log);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

private:
    Q_DISABLE_COPY(LogModel)
    QList<Log> m_logs;
};

#endif // TOPICMODEL_H
