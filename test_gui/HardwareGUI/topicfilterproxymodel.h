#ifndef TOPICFILTERPROXYMODEL_H
#define TOPICFILTERPROXYMODEL_H

#include <set>
#include <QSortFilterProxyModel>

#include "logmodel.h"

class TopicFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit TopicFilterProxyModel(QObject* parent = nullptr);

    void InsertTopicsInFilter(const QVector<QString> &topics);

    void EraseTopicsFromFilter(const QVector<QString> &topics);

protected:
    bool filterAcceptsRow(int soureRow, const QModelIndex&) const override;

private:
    std::set<QString> m_topics;
};

#endif // TOPICFILTERPROXYMODEL_H
