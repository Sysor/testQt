#include "secondtaskdialog.h"
#include "ui_secondtaskdialog.h"

#include <QMenu>

static QTableView *table = nullptr;

secondTaskDialog::secondTaskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secondTaskDialog)
{
    ui->setupUi(this);    
    table = ui->table;
}

secondTaskDialog::~secondTaskDialog()
{
    delete ui;
}

void secondTaskDialog::setModel(QAbstractTableModel *model)
{
    table->setModel(model);
    connect(model, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&, const QVector<int>&)), this, SLOT(onDataChanged(const QModelIndex&, const QModelIndex&, const QVector<int>&)));
    connect(model, SIGNAL(headerDataChanged(Qt::Orientation, int, int)), table, SLOT(update(const QModelIndex&)));
}

void secondTaskDialog::contextMenuTriggered(QPoint pos)
{
    QMenu * menu = new QMenu(this);
    menu->addAction(table->actions().at(0));
    menu->addAction(table->actions().at(1));
    connect(table->actions().at(0), SIGNAL(triggered()), this, SLOT(slotEditRecord()));     // Обработчик вызова диалога редактирования
    connect(table->actions().at(1), SIGNAL(triggered()), this, SLOT(slotRemoveRecord())); // Обработчик удаления записи
    /* Вызываем контекстное меню */
    menu->popup(table->viewport()->mapToGlobal(pos));
}


void secondTaskDialog::on_actionadd_triggered()
{
    table->edit(table->currentIndex());
}

void secondTaskDialog::slotEditRecord()
{

}

void secondTaskDialog::slotRemoveRecord()
{

}

void secondTaskDialog::onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    table->update();
}
