#include "ireceiver.h"
#include <QObject>

class firstTask : public QObject{
    Q_OBJECT
public:
    firstTask(IReceiver *receiver);
    ~firstTask();

    void start(int nInterval);
    void stop();
    void pause();

    bool isRunning();
private:
    IReceiver *m_Receiver;
public slots:
    void onIntervalChange(int nNewInterval);
private slots:
    void onTimerTick();
};
