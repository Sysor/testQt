#ifndef SECONDTASK_H
#define SECONDTASK_H

#include <QAbstractTableModel>

class Model : public QAbstractTableModel
{
public:
    Model();
    void add(QVariant &data);
    void remove(int nIndex);
    void copy(int nIndex);    

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles);
    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);
};

#endif // SECONDTASK_H
