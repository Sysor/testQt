#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QItemDelegate>
#include <QWidget>
#include "../model/Model.h"
#include "../iview.h"

class Controller : public QItemDelegate
{
    Q_OBJECT
private:
    Model *_model;
    IView *_view;
    Controller(IView *view);
public:
    static Controller *getInstance(IView *view);
    ~Controller();
    // QAbstractItemDelegate interface
public:
//    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
//    void destroyEditor(QWidget *editor, const QModelIndex &index) const;
//    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
//    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
//    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

private slots:
    void addNewRow();
};

#endif // CONTROLLER_H
