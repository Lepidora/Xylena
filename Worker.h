#pragma once

//System includes
#include <thread>
#include <queue>

//Local includes
#include "AsyncTypes.h"

namespace Xylena {
    
    class Worker {
    private:
        void runQueue();
        std::thread thread;
        std::queue<Task> taskQueue;
    public:
        
        void start();
        void pause();
        void resume();
        void stop();
        void halt();
        
        void enqueue(Task task);
    };
}