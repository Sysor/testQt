#ifndef SECONDTASK_H
#define SECONDTASK_H

#include <QAbstractTableModel>

class Model : public QAbstractTableModel
{
public:
    Model(int nRows, int nColumns);
    ~Model();
    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    //bool setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles);
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex());
    //QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    //bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role);
    bool removeRows(int row, int count, const QModelIndex &parent);

};

#endif // SECONDTASK_H
