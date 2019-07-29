#include "controller.h"
#include <QList>

static Controller *ctrl = nullptr;

Controller::Controller(IView *view){
    QList<QString> columns = {"X", "Y", "Z"};
    this->_model = new Model(5, columns);
    this->_view = view;

    _view->setModel(_model);

    auto *obj = dynamic_cast<QObject*>(view);
    connect(obj, SIGNAL(newRow()), this, SLOT(addNewRow()));
}

Controller::~Controller(){
    delete _model;
}

void Controller::addNewRow()
{
    _model->insertRow(_model->rowCount());
}


Controller *Controller::getInstance(IView *view){
    if(ctrl == nullptr){
        ctrl = new Controller(view);
    }
    return ctrl;
}
