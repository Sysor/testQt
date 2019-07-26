#ifndef IVIEW_H
#define IVIEW_H

#include <QAbstractTableModel>

class IView{
public:
    virtual ~IView(){}

    virtual void newRow() = 0;
    virtual void deleteRow() = 0;
    virtual void copyRow() = 0;
    virtual void setModel(QAbstractTableModel *model) = 0;
};

#endif // IVIEW_H
