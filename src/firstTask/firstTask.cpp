#include "firstTask.h"
#include <random>
#include <cstdlib>
#include <ctime>

static bool bStop = false;
static bool bPause = false;

firstTask::firstTask(IReceiver *receiver) : m_Receiver(receiver) {
}

firstTask::~firstTask()
{
    bStop = true;
}

double getNumber(double upper_bound){
    double lower_bound = 0;
    std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
    std::default_random_engine re;
    return unif(re);
}

void firstTask::run(){
    while(!bStop){
        if(!bPause){
            m_Receiver->addPoint(getNumber(5), getNumber(5));
        }
        msleep(100L);
    }
}

void firstTask::start(){    
    this->run();
}

void firstTask::stop(){
    exit();
}

void firstTask::pause(){
    bPause = isRunning();
    if(isRunning()){
        emit onPause();
    }
    else{
        emit onResume();
    }
}

void firstTask::onPause(){}

void firstTask::onResume(){}
