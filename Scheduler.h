#pragma once

//System includes
#include <vector>
#include <thread>
#include <functional>

//Local includes
#include "AsyncTypes.h"
#include "Worker.h"

namespace Xylena {
    
    class Scheduler {
    private:
        static std::thread mainThread;
        
        static int maxWorkers;
        static std::vector<Worker *> workers;
        
        static void createWorkers(int workers);
    public:
        static void setMaxWorkers(int max);
        static void initialize();
        static void start();
        static void enqueue(Task task);
        static void enqueue(Task task, int threadid);
        static void enqueueMain(Task task);
        
        static Worker * getWorker(int id);
        
    };
    
}