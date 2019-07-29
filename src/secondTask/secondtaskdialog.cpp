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
    table->addAction(ui->actionadd);
    table->addAction(ui->actioncopy);
    table->addAction(ui->actiondelete);
}

secondTaskDialog::~secondTaskDialog()
{
    delete ui;
}

void secondTaskDialog::setModel(QAbstractTableModel *model)
{
    this->_model = model;
    table->setModel(model);

    connect(model, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&, const QVector<int>&)), this, SLOT(onDataChanged(const QModelIndex&, const QModelIndex&, const QVector<int>&)));
    //connect(model, SIGNAL(headerDataChanged(Qt::Orientation, int, int)), table, SLOT(update(const QModelIndex&)));
}

void secondTaskDialog::onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    Q_UNUSED(topLeft)
    Q_UNUSED(bottomRight)
    Q_UNUSED(roles)

    table->update();
}

void secondTaskDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    switch(ui->buttonBox->buttonRole(button)){
    case QDialogButtonBox::AcceptRole:
        break;
    case QDialogButtonBox::RejectRole:
        this->close();
        break;
    default:
        break;
    }
}

void secondTaskDialog::on_actionadd_triggered()
{
    this->_model->insertRow(_model->rowCount());
}

void secondTaskDialog::on_actioncopy_triggered()
{
    QItemSelectionModel *select = table->selectionModel();
    if(select->hasSelection()){
        QModelIndexList indexes = select->selectedIndexes();
        QModelIndex &index = indexes.first();
        this->_model->insertRow(_model->rowCount(), index);
    }
}

void secondTaskDialog::on_actiondelete_triggered()
{
    QItemSelectionModel *select = table->selectionModel();
    if(select->hasSelection()){
        QModelIndexList indexes = select->selectedIndexes();
        QModelIndex &index = indexes.first();
        this->_model->removeRow(index.row());
    }
}
