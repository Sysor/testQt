#include "dialogfirsttask.h"
#include "ui_dialogfirsttask.h"
#include "qcustomplot/qcustomplot.h"
#include "firstTask/firstTask.h"

static QCPGraph *graph = nullptr;
static QVector<double> xValues = {0};
static QVector<double> yValues = {0};
static firstTask *task = nullptr;

DialogFirstTask::DialogFirstTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFirstTask)
{
    ui->setupUi(this);

    graph = ui->plot->addGraph(new QCPAxis(ui->plot->axisRect(), QCPAxis::AxisType::atLeft), new QCPAxis(ui->plot->axisRect(), QCPAxis::AxisType::atBottom));
    graph->setName("test");
    graph->setData(xValues, yValues, true);
    task = new firstTask(this);
}

DialogFirstTask::~DialogFirstTask()
{
    if(graph){
        ui->plot->removeGraph(graph);
    }

    if(task){
        task->stop();
        delete task;
    }
    delete ui;
}

void DialogFirstTask::addPoint(double x, double y){
    xValues.push_back(x);
    yValues.push_back(y);
}

void DialogFirstTask::on_toolButton_3_clicked()
{
    task->start();
}

void DialogFirstTask::on_toolButton_2_clicked()
{
    task->stop();
}

void DialogFirstTask::on_toolButton_clicked()
{
    task->pause();
}
