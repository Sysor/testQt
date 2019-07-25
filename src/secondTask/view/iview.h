#ifndef IVIEW_H
#define IVIEW_H


class IView
{
private:
    IController *controller;
public:
    IView() {};
    virtual IView() abstract;
};

#endif // IVIEW_H
