#ifndef SECONDTASKDIALOG_H
#define SECONDTASKDIALOG_H

#include "iview.h"
#include <QDialog>
#include <qabstractbutton.h>

namespace Ui {
    class secondTaskDialog;
    }

class secondTaskDialog : public QDialog//, public IView
{
    Q_OBJECT

public:
    explicit secondTaskDialog(QWidget *parent = nullptr);
    ~secondTaskDialog();

// IView interface
    void setModel(QAbstractTableModel *model);

private slots:
    void onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);

    void on_buttonBox_clicked(QAbstractButton *button);

    void on_actionadd_triggered();

    void on_actioncopy_triggered();

    void on_actiondelete_triggered();

private:
    Ui::secondTaskDialog *ui;  
    QAbstractItemModel *_model;

};

#endif // SECONDTASKDIALOG_H
