#ifndef SECONDTASK_H
#define SECONDTASK_H

#include "row.h"

#include <QVector>


class Model
{
public:
    Model();
    void insert(row &r);
    void remove(int nIndex);
    void copy(int nIndex);
private:
    QVector<row> rows;
};

#endif // SECONDTASK_H
