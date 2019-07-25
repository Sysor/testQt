#ifndef SECONDTASKDIALOG_H
#define SECONDTASKDIALOG_H

#include <QDialog>

namespace Ui {
    class secondTaskDialog;
    }

class secondTaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit secondTaskDialog(QWidget *parent = nullptr);
    ~secondTaskDialog();

private:
    Ui::secondTaskDialog *ui;
};

#endif // SECONDTASKDIALOG_H
