#include "logmodel.h"

using namespace std;

LogModel::LogModel(QObject *parent) : QAbstractListModel(parent)
{
}

void LogModel::addLog(const Log &log) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_logs << log;
    endInsertRows();
}

int LogModel::rowCount(const QModelIndex &) const {
    return m_logs.count();
}

QColor getTopicColor(const QString &topic) {
    // motor
    if (find(Topics::motor_topics.begin(), Topics::motor_topics.end(), topic)
            != Topics::motor_topics.end())
    {
        return QColor(0,195,195);
    }
    // light
    else if (Topics::experimental_topics["light_enable1"]  == topic ||
             Topics::experimental_topics["light_enable2"]  == topic ||
             Topics::experimental_topics["light_current1"] == topic ||
             Topics::experimental_topics["light_current2"] == topic)
    {
        return QColor(190, 170, 0); // dark yellow
    }
    // knife
    else if (Topics::control_topics["knife_current1"] == topic ||
             Topics::control_topics["knife_current2"] == topic)
    {
        return QColor(30, 125, 255); // light blue
    }
    // temperature and pressure
    else if (Topics::control_topics["temperature"]      == topic ||
             Topics::control_topics["pressure"]         == topic ||
             Topics::experimental_topics["temperature"] == topic ||
             Topics::experimental_topics["pressure"]    == topic)
    {
        return QColor(25, 115, 70); // green
    }
    // openbank
    else if (Topics::control_topics["openbank"] == topic)
    {
        return QColor(Qt::magenta);
    }
    // vibrobank
    else if (Topics::control_topics["vibrobank"] == topic)
    {
        return QColor(Qt::darkMagenta);
    }
    // disclosure
    else if (Topics::experimental_topics["disclosure"] == topic)
    {
        return QColor(153, 51, 255);
    }
    // syncro
    else if (Topics::experimental_topics["knifes_syncrocam_enable"] == topic)
    {
        return QColor(255, 153, 255);
    }
    // error
    else if (topic == "error")
    {
        return QColor(Qt::red);
    }
    // other
    return QColor(Qt::black);
}

QVariant LogModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= rowCount())
        return QVariant();

    if (role == Qt::DisplayRole)
        return m_logs[index.row()].message;
    else if (role == TopicRole)
        return m_logs[index.row()].topic;
    else if (role == MessageRole)
        return m_logs[index.row()].message;
    else if (role == Qt::ForegroundRole) {
        QColor color = getTopicColor(m_logs[index.row()].topic);
        return QVariant(color);
    }

    return QVariant();
}
