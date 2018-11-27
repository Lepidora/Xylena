#pragma once

//System includes
#include <thread>
#include <queue>
#include <atomic>
#include <mutex>

//Local includes
#include "AsyncTypes.h"

namespace Xylena {
    
    class Worker {
    private:
        void runQueue();
        std::thread thread;
        std::queue<Task> taskQueue;
        
        std::mutex queueLock;
        
        std::atomic<bool> stopped;
    public:
        
        Worker();
        
        void start();
        void stop();
        
        void enqueue(Task task);
    };
}