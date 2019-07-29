#include "Model.h"
#include <random>
#include <ctime>

#include <QMap>
#include <QList>

typedef QMap<int, QVariant> field;
typedef QList<field*> row;
typedef QList<row*> items;

static items *_data = nullptr;
static QMap<int, QVariant> columns_header;
static Model *pThis = nullptr;

bool vaidateIndex(const QModelIndex &index){
    bool bResult = false;
    if(!_data->isEmpty() && index.isValid()){
        row *r = _data->at(0);
        if((index.row() >=0 && index.row() < _data->size()) &&
                index.column() >= 0 && index.column() < r->size()){
            bResult = true;
        }
    }
    return bResult;
}

int genIntValue(int nMax){
    return rand() % nMax;
}

void fillField(field *f, field *original_field){
    for(field::iterator f_it=original_field->begin(); f_it!=original_field->end(); f_it++){
//        pThis->setData(_index, f_it.value(), f_it.key());
        f->insert(f_it.key(), f_it.value());
    }
}

void fillRow(row *r, row *original_row){
    int _column_index = 0;
    for(row::iterator it = original_row->begin(); it!=original_row->end(); it++){
        field *original_field = *it;
        field *f = r->at(_column_index++);
        //QModelIndex _index = pThis->index(nRow, _column_index++);
        fillField(f, original_field);
    }
}

Model::Model(int nRows, QList<QString> &columns){
    pThis = this;
    _data = new items();

    insertRows(0, nRows -1);
    insertColumns(0, columns.size()-1);

    srand(static_cast<unsigned int>(time(nullptr)));
    for(int r=0; r<nRows; r++){
        int nColumnIndex = 0;
        setHeaderData(r, Qt::Vertical, QVariant(r), Qt::DisplayRole);
        for(QList<QString>::iterator it = columns.begin(); it!=columns.end(); it++){
            setHeaderData(nColumnIndex, Qt::Horizontal, QVariant(*it), Qt::DisplayRole);
            columns_header.insert(nColumnIndex, *it);
            QModelIndex index = createIndex(r, nColumnIndex);
            setData(index, QVariant(genIntValue(10)), Qt::DisplayRole);
            nColumnIndex++;
        }
    }
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
    Q_UNUSED(parent)
    return _data->size();
}

int Model::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
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

bool Model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool bResult = false;
    if(vaidateIndex(index)){
        field *f =_data->at(index.row())->at(index.column());
        if(f != nullptr){
            f->insert(role, value);
            emit dataChanged(index, index);
            bResult = true;
        }
    }

    return bResult;
}

bool Model::insertRows(int _row, int _count, const QModelIndex &parent)
{
    bool bResult = false;
    row *original_row = nullptr;
    if(vaidateIndex(parent)){
        original_row = _data->at(parent.row());
    }

    beginInsertRows(parent, _row, _row + _count-1);
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
            _data->push_front(r);
        }
        else if(_row == _data->size()){
            _data->push_back(r);
        }
        else{
            _data->insert(_row, r);
        }

        //Копирование полей parent ряда в новые ряды
        if(vaidateIndex(parent)){
            for(int j=0; j<original_row->size(); j++){
                QModelIndex _index = index(_data->indexOf(r), j);
                field *original_field = original_row->at(j);
                for(field::iterator it=original_field->begin(); it!=original_field->end(); it++){
                    setData(_index, it.value(), it.key());
                }
            }
        }
    }
    endInsertRows();

    return bResult;
}

bool Model::insertColumns(int _column, int _count, const QModelIndex &parent)
{
    bool bResult = false;    
    beginInsertColumns(parent, _column, _column + _count-1);
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
                    r->push_front(new_field);
                }
                else if(!_data->isEmpty() && _column == _data->at(0)->size()){
                    r->push_back(new_field);
                }
                else{
                    r->insert(_column, new_field);
                }
            }
        }
    }
    endInsertColumns();
    return bResult;
}

bool Model::removeRows(int _row, int _count, const QModelIndex &parent)
{
    bool bResult = false;
    beginRemoveRows(parent, _row, _row + _count - 1);
    if(_row >=0 && _row < _data->size()){
        for(int i=0; i<_count; i++){
            _data->removeAt(_row);
        }
    }
    endRemoveRows();
    return bResult;
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(role)

    QVariant result = QVariant();
    if(orientation == Qt::Vertical){
        result.setValue(section);
    }
    else{
        QMap<int, QVariant>::iterator it = columns_header.find(section);
        if(it!=columns_header.end()){
            result = *it;
        }
    }
    return result;
}

