#include "dialogfirsttask.h"
#include "ui_dialogfirsttask.h"
#include "qcustomplot/qcustomplot.h"
#include "firstTask/firstTask.h"
#include <string>

#include <QtGlobal>

static QCPGraph *graph = nullptr;
static QVector<double> xValues = {0};
static QVector<double> yValues = {0};
static firstTask *task = nullptr;
static QCustomPlot *plot = nullptr;

static double upperValue = 10.0;
static int nInterval = 1;

QCPGraph *initGraph(QCustomPlot *plot){
    QCPGraph *graph = plot->addGraph();
    plot->axisRect()->axis(QCPAxis::AxisType::atLeft)->setRange(0, 10.0);
    plot->axisRect()->axis(QCPAxis::AxisType::atBottom)->setRange(0, 10.0);

    QCPScatterStyle style(QCPScatterStyle::ScatterShape::ssStar);

    graph->setName("test");
    graph->setAdaptiveSampling(true);
    graph->setLineStyle(QCPGraph::LineStyle::lsNone);
    graph->setScatterStyle(style);
    return graph;
}

DialogFirstTask::DialogFirstTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFirstTask)
{
    ui->setupUi(this);    
    ui->edInterval->setText(QString(std::to_string(ui->sldInterval->value()).c_str()));

    plot = ui->plot;
    graph = initGraph(plot);
    task = new firstTask(this);
}

DialogFirstTask::~DialogFirstTask()
{
    if(task){
        task->stop();
        delete task;
    }
    plot->clearGraphs();
    delete ui;
}

double DialogFirstTask::getMaxValue(){
    return upperValue;
}

void DialogFirstTask::addPoint(double x, double y){
    xValues.push_back(x);
    yValues.push_back(y);
    graph->setData(xValues, yValues);
    plot->replot();
    qDebug() << "x: " << x << " y: " << y;
}

void DialogFirstTask::on_toolButton_3_clicked()
{
    task->start(nInterval*1000);
}

void DialogFirstTask::on_toolButton_2_clicked()
{
    task->stop();
    graph->data().data()->clear();
    xValues.clear();
    yValues.clear();
    plot->replot();
}

void DialogFirstTask::on_toolButton_clicked()
{
    task->pause();
}

void DialogFirstTask::on_sldInterval_valueChanged(int value)
{
    ui->edInterval->setText(QString(std::to_string(value).c_str()));
}

void DialogFirstTask::on_edInterval_returnPressed()
{
     nInterval = ui->edInterval->text().toInt();
     ui->sldInterval->setValue(nInterval);
}
