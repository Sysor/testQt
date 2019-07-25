#ifndef ROW_H
#define ROW_H

#include <QString>
#include <QList>
#include "field.h"

class row
{
public:
    row(QList<QString> names);
    row(QList<field> fields);

    QList<field> getFields();
    field getFieldByName(QString &name);
    field getFieldByIndex(int nIndex);
    QString getFieldValue(QString &name);
    QString getFieldValue(int nIndex);
private:
    QList<field> _fields;
};

#endif // ROW_H
