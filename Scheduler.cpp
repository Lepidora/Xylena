#include "Scheduler.h"

namespace Xylena {
    
    int maxWorkers = 0;
    std::thread mainThread;
    
    void Scheduler::setMaxWorkers(int max) {
        maxWorkers = max;
    }
    
    void Scheduler::initialize() {
        
        unsigned int supportedWorkers = std::thread::hardware_concurrency();
        
        if (maxWorkers > 0) {
            if (supportedWorkers > maxWorkers) {
                createWorkers(maxWorkers);
            } else {
                createWorkers(supportedWorkers);
            }
        }
    }
    
    void Scheduler::start() {
        for(auto worker: workers) {
            worker->start();
        }
    }
    
    void Scheduler::createWorkers(int workerCount) {
        for (int id = 0; id < workerCount; id++) {
            Worker *worker = new Worker();
            workers.push_back(worker);
        }
    }
    
    void Scheduler::enqueue(Task task) {
        
    }
    
    void Scheduler::enqueue(Task task, int threadid) {
        
        Worker *worker = getWorker(threadid);
        
        if (worker) {
            //worker->
        }
    }
    
    void Scheduler::enqueueMain(Task task) {
        enqueue(task, 0);
    }
    
    Worker * Scheduler::getWorker(int id) {
        
        if (id >= 0 && id < workers.size()) {
            return workers[id];
        } else {
            return nullptr;
        }
    }
    
    
    
}