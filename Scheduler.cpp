#include "Scheduler.h"

namespace Xylena {
    
    std::thread Scheduler::mainThread;
    
    int Scheduler::maxWorkers = 0;
    std::vector<Worker *> Scheduler::workers;
    
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
    
    Task Scheduler::enqueue(TaskType taskRunnable) {
        
        Task task(taskRunnable);
        Scheduler::enqueue(task);
        
        return task;
    }
    
    void Scheduler::enqueue(Task task) {
        Scheduler::enqueue(task, 1);
    }
    
    void Scheduler::enqueue(Task task, int threadid) {
        
        Worker *worker = getWorker(threadid);
        
        if (worker) {
            worker->enqueue(task);
        }
    }
    
    void Scheduler::enqueueMain(Task task) {
        enqueue(task, 0);
    }
    
    Task Scheduler::enqueueMain(TaskType taskRunnable) {
        
        Task task(taskRunnable);
        enqueue(task, 0);
        
        return task;
    }
    
    int Scheduler::hardwareThreads() {
        return std::thread::hardware_concurrency();
    }
    
    int Scheduler::workerCount() {
        return (int)workers.size();
    }
    
    Worker * Scheduler::getWorker(int id) {
        
        if (id >= 0 && id < workers.size()) {
            return workers[id];
        } else {
            return nullptr;
        }
    }
}