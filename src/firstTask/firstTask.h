#include <QThread>
#include "ireceiver.h"

class firstTask : public QThread{
public:
    firstTask(IReceiver *receiver);
    ~firstTask();

    void start();
    void stop();
    void pause();
private:
    IReceiver *m_Receiver;

    void run();
public:
    signals:
    void onPause();
    void onResume();
};
