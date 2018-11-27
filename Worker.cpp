#include "Worker.h"

//System includes


namespace Xylena {
    
    Worker::Worker() {
        stopped = false;
    }
    
    void Worker::runQueue() {
        
        
        while (!stopped) {
            
            Task currentTask;
            
            std::lock_guard<std::mutex> lock(queueLock);
            
            if (!taskQueue.empty()) {
                
                currentTask = taskQueue.front();
                taskQueue.pop();
            }
            
            lock.~lock_guard();
            
            currentTask();
            
            if (stopped) {
                return;
            }
            
            //lock.lock();
        }
        
        //lock.release();
    }
    
    void Worker::start() {
        thread = std::thread(&Worker::runQueue, this);
    }
    
    void Worker::stop() {
        stopped = true;
    }
    
    void Worker::enqueue(Task task) {
        std::lock_guard<std::mutex> lock(queueLock);
        taskQueue.push(task);
    }
    
}