#include "mainwindow.h"
#include <QToolButton>
#include <QDockWidget>
#include <qevent.h>
#include "firstTask/dialogfirsttask.h"
#include "secondTask/secondtaskdialog.h"
#include "secondTask/controller/controller.h"
#include "ui_mainwindow.h"

//static Controller *ctrl = nullptr;
static Model *model = nullptr;

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
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setModal(true);
    dlg->show();
}

void MainWindow::on_btnSecond_clicked()
{
    auto *dlg = new secondTaskDialog(this);
    model = new Model(5, 5);
    //ctrl = Controller::getInstance(static_cast<IView*>(dlg));
    dlg->setModel(model);
    dlg->setModal(true);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
    if(model != nullptr){
        delete model;
    }
//    if(ctrl != nullptr){
//        delete ctrl;
//    }
}
