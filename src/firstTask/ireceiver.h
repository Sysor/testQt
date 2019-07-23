#ifndef IRECEIVER_H
#define IRECEIVER_H

class IReceiver{
public:
	virtual void addPoint(double x, double y) = 0;
    virtual double getMaxValue() = 0;
};

#endif // IRECEIVER_H
