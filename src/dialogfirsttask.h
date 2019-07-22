#ifndef DIALOGFIRSTTASK_H
#define DIALOGFIRSTTASK_H

#include <QDialog>
#include "firstTask/ireceiver.h"

namespace Ui {
    class DialogFirstTask;
    }

class DialogFirstTask : public QDialog, IReceiver
{
    Q_OBJECT

public:
    explicit DialogFirstTask(QWidget *parent = nullptr);
    ~DialogFirstTask();

    void addPoint(double x, double y);
private slots:
    void on_toolButton_3_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_clicked();

private:
    Ui::DialogFirstTask *ui;
};

#endif // DIALOGFIRSTTASK_H
