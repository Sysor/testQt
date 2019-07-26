#include "controller.h"

static Controller *ctrl = nullptr;

Controller::Controller(IView *view){
    this->_model = new Model(5, 5);
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

}


Controller *Controller::getInstance(IView *view){
    if(ctrl == nullptr){
        ctrl = new Controller(view);
    }
    return ctrl;
}
