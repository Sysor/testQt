#include "Model.h"
#include <random>
#include <ctime>

#include <QMap>
#include <QList>

typedef QMap<int, QVariant> field;
typedef QList<field*> row;
typedef QList<row*> items;

static items *_data = nullptr;
static row *columns_header = nullptr;
static row *rows_header = nullptr;

bool vaidateIndex(const QModelIndex &index){
    bool bResult = false;
    if(!_data->isEmpty() && index.isValid()){
        row *r = _data->at(0);
        field *f = r->at(0);
        if((index.row() >=0 && index.row() < _data->size()) &&
                index.column() >= 0 && index.column() < f->size()){
            bResult = true;
        }
    }
    return bResult;
}

int genIntValue(int nMax){
    return rand() % nMax;
}

Model::Model(int nRows, int nColumns){
    _data = new items();
    columns_header = new row();
    rows_header = new row();

    insertRows(0, nRows);
    insertColumns(0, nColumns);

    field *f = new field();

    srand(static_cast<unsigned int>(time(nullptr)));
    for(int r=0; r<nRows; r++){
        int nRowIndex = r + 1;
        setHeaderData(r, Qt::Horizontal, QVariant(nRowIndex), Qt::DisplayRole);
        for(int c=0; c<nColumns; c++){
            int nColumnIndex = c + 1;
            setHeaderData(c, Qt::Vertical, QVariant(nColumnIndex), Qt::DisplayRole);
            QModelIndex index = createIndex(r, c);
            f->insert(Qt::EditRole, QVariant(genIntValue(10)));
            setItemData(index, *f);
            f->clear();
        }
    }
    delete f;
    QModelIndex topLeft = createIndex(0, 0);
    QModelIndex bottomRight = createIndex(nRows, nColumns);
    emit dataChanged(topLeft, bottomRight);
}

Model::~Model(){
    if(!_data->isEmpty()){
        for(QList<row*>::Iterator it=_data->begin(); it!=_data->end(); it++){
            row *r = *it;
            for(row::iterator r_it = r->begin(); r_it!= r->end(); r_it++){
                delete (*r_it);
            }
        }
    }
}

int Model::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _data->size();
}

int Model::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    int nResult = 0;
    if(!_data->isEmpty()){
        nResult = _data->first()->size();
    }
    return nResult;
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    QVariant result = QVariant::Invalid;
    if(vaidateIndex(index)){
        field *f= _data->at(index.row())->at(index.column());
        field::iterator it = f->find(role);
        if(it != f->end()){
            result = it.value();
        }
    }
    return result;
}

bool Model::setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles)
{
    bool bResult = false;
    if(vaidateIndex(index)){
        field *f =_data->at(index.row())->at(index.column());
        for(QMap<int, QVariant>::const_iterator it = roles.begin(); it!= roles.end(); it++){
            f->insert(it.key(), it.value());
        }
        bResult = true;
    }

    return bResult;
}

void fillField(field *new_field, field *original_field){
    for(field::iterator f_it=original_field->begin(); f_it!=original_field->end(); f_it++){
        new_field->insert(f_it.key(), f_it.value());
    }
}

void fillRow(row *r, row *original_row){
    for(row::iterator it = original_row->begin(); it!=original_row->end(); it++){
        field *original_field = *it;
        field *new_field = new field();
        fillField(new_field, original_field);
        r->push_back(new_field);
    }
}

bool Model::insertRows(int _row, int _count, const QModelIndex &parent)
{
    bool bResult = false;
    for(int i=0; i<_count; i++){
        row *r = new QList<field*>();
        if(_data->isEmpty()){
            //Если модель пустая, то добавляем _count рядов с одним полем
            field *f = new field();
            f->insert(Qt::DisplayRole, QVariant());
            r->push_back(f);
            bResult = true;
        }
        else{
            row *header = _data->at(0);
            //заполняем новый ряд пустыми полями
            for(row::iterator it=header->begin(); it!=header->end(); it++){
                field *f = new field();
                r->push_back(f);
            }
            bResult = true;
        }

        if(_row == 0){
            //Копирование полей parent ряда в новые ряды
            if(vaidateIndex(parent)){
                bResult = true;
                row *original_row = _data->at(parent.row());
                fillRow(r, original_row);
            }
            _data->push_front(r);
        }
        else if(_row == _data->size()){
            //Копирование полей parent ряда в новые ряды
            if(vaidateIndex(parent)){
                bResult = true;
                row *original_row = _data->at(parent.row());
                fillRow(r, original_row);
            }
            _data->push_back(r);
        }
        else{
            _data->insert(_row, r);
        }
    }
    return bResult;
}

bool Model::insertColumns(int _column, int _count, const QModelIndex &parent)
{
    bool bResult = false;
    if(_data->isEmpty()){
        row *r = new row();
        for(int i=0; i<_count; i++){
            r->push_back(new field());
        }
        _data->push_back(r);
    }
    else{
        for(int i=0; i<_count; i++){
            for(QList<row*>::Iterator it = _data->begin(); it!=_data->end(); it++){
                row *r = *it;
                field *new_field = new field();
                if(_column == 0){
                    if(vaidateIndex(parent)){
                        field *original_field = _data->at(parent.row())->at(parent.column());
                        fillField(new_field, original_field);
                    }
                    r->push_front(new_field);
                }
                else if(!_data->isEmpty() && _column == _data->at(0)->size()){
                    if(vaidateIndex(parent)){
                        field *original_field = _data->at(parent.row())->at(parent.column());
                        fillField(new_field, original_field);
                    }
                    r->push_back(new_field);
                }
                else{
                    r->insert(_column, new_field);
                }
            }
        }
    }
    return bResult;
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant result;
    row * r = nullptr;

    switch (orientation) {
    case Qt::Horizontal:
        r = rows_header;
        break;
    case Qt::Vertical:
        r = columns_header;
        break;
    }

    if(!r->isEmpty()){
        if(section >=0 && section < r->size()){
            field *f = r->at(section);
            field::iterator it = f->find(role);
            if(it != f->end()){
                result = it.value();
            }
        }
    }

    return result;
}

bool Model::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    bool bResult = false;

    field *f = new field();
    f->insert(role, value);
    row *r = nullptr;
    switch(orientation){
    case Qt::Vertical:
        r = rows_header;
        break;
    case Qt::Horizontal:
        r = columns_header;
        break;
    }

    if(r != nullptr){
        if(section >=0){
            if(section < r->size()){
                r->replace(section, f);
            }
            else{
                r->insert(section, f);
            }
            bResult = true;
            emit headerDataChanged(orientation, section, section);
        }
    }
    return bResult;
}

