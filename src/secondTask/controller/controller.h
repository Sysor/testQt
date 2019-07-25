#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "icontroller.h"

class Controller : public IController
{
public:
    Controller();
    ~Controller();

    // IController interface
public:
    void addListener();
    void removeListener();
};

#endif // CONTROLLER_H
