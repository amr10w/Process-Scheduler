#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "process.h"
#include <queue>

class processor
{
private:
    queue<process*> ready_queue;
    
public:
    processor();
    ~processor();
};

#endif