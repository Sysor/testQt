#include "secondtaskdialog.h"
#include "ui_secondtaskdialog.h"

secondTaskDialog::secondTaskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secondTaskDialog)
{
    ui->setupUi(this);
}

secondTaskDialog::~secondTaskDialog()
{
    delete ui;
}
