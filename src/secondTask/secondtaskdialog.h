#ifndef SECONDTASKDIALOG_H
#define SECONDTASKDIALOG_H

#include "iview.h"
#include <QDialog>

namespace Ui {
    class secondTaskDialog;
    }

class secondTaskDialog : public QDialog, public IView
{
    Q_OBJECT

public:
    explicit secondTaskDialog(QWidget *parent = nullptr);
    ~secondTaskDialog();

// IView interface
    void setModel(QAbstractTableModel *model);

signals:
    void newRow();
    void deleteRow();
    void copyRow();


private slots:
    void contextMenuTriggered(QPoint);
    void on_actionadd_triggered();
    void slotEditRecord();
    void slotRemoveRecord();

    void onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);

private:
    Ui::secondTaskDialog *ui;  
    QAbstractItemModel *_model;

};

#endif // SECONDTASKDIALOG_H
