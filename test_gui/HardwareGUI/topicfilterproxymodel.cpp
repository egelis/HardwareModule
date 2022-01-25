#include "topicfilterproxymodel.h"

TopicFilterProxyModel::TopicFilterProxyModel(QObject* parent) : QSortFilterProxyModel(parent)
{
}

bool TopicFilterProxyModel::filterAcceptsRow(int soureRow, const QModelIndex &) const {
    if (m_topics.empty()) {
        return true;
    }

    auto index = sourceModel()->index(soureRow, 0);
    auto data = sourceModel()->data(index, LogModel::LogRoles::TopicRole).toString();

    return !m_topics.count(data);
}

void TopicFilterProxyModel::InsertTopicsInFilter(const QVector<QString> &topics)
{
    for (auto &topic: topics) {
        m_topics.insert(topic);
    }
    invalidate();
}

void TopicFilterProxyModel::EraseTopicsFromFilter(const QVector<QString> &topics)
{
    for (auto &topic: topics) {
        m_topics.erase(topic);
    }
    invalidate();
}
