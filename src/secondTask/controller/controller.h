#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QItemDelegate>
#include <QWidget>
#include "../model/Model.h"
#include "../iview.h"

class Controller : public QItemDelegate
{
    Q_OBJECT
private:
    Model *_model;
    IView *_view;
    Controller(IView *view);
public:
    static Controller *getInstance(IView *view);
    ~Controller();
private slots:
    void addNewRow();
};

#endif // CONTROLLER_H
