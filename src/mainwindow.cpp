#include "mainwindow.h"
#include <QToolButton>
#include <QDockWidget>
#include "dialogfirsttask.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bntFirst_clicked()
{
    QDialog *dlg = new DialogFirstTask(this);    
    dlg->setModal(true);
    dlg->show();
}
