#include "firstTask.h"
#include <random>
#include <cstdlib>
#include <ctime>

#include <QTimer>
#include <QThread>

static QTimer _timer;
static std::default_random_engine re;
static double maxRange = 5.0;
static bool bIsPaused = false;

firstTask::firstTask(IReceiver *receiver) : m_Receiver(receiver) {
    maxRange = receiver->getMaxValue();
    connect(&_timer, SIGNAL(timeout()), this, SLOT(onTimerTick()));
}

firstTask::~firstTask()
{
    stop();
}

double getNumber(double upper_bound){
    double lower_bound = 0;
    std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
    return unif(re);
}

void firstTask::start(int nInterval){
    if(!_timer.isActive()){
        _timer.setInterval(nInterval);
        _timer.start();
    }
    else if(bIsPaused) {
        bIsPaused = false;
        _timer.blockSignals(false);
    }
}

void firstTask::stop(){
    _timer.stop();
}

void firstTask::pause(){
    _timer.blockSignals(true);
    bIsPaused = true;
}

void firstTask::onTimerTick(){    
    m_Receiver->addPoint(getNumber(maxRange), getNumber(maxRange));
}

void firstTask::onIntervalChange(int nNewInterval){
    _timer.stop();
    _timer.setInterval(nNewInterval);
    _timer.start();
}
