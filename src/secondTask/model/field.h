#ifndef FIELD_H
#define FIELD_H

#include <QString>

class field
{
public:
    field(QString &name);
    QString getName();
    QString getValue();

    void setValue(QString &value);
private:
    QString name;
    QString value;
};

#endif // FIELD_H
