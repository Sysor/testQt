#ifndef SECONDTASK_H
#define SECONDTASK_H

#include <QAbstractTableModel>
#include <QList>

class Model : public QAbstractTableModel
{
public:
	Model(int nRows, QList<QString> &columns);
    ~Model();
    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent);
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

#endif // SECONDTASK_H
