#include "Worker.h"

namespace Xylena {
    
    void Worker::runQueue() {
        
        while (!taskQueue.empty()) {
            Task currentTask = taskQueue.front();
            taskQueue.pop();
            
            currentTask();
        }
        
    }
    
    void Worker::start() {
        //thread = std::thread(&Worker::runQueue);
    }
    
    void Worker::pause() {
        
    }
    
    void Worker::resume() {
        
    }
    
    void Worker::stop() {
        
    }
    
    void Worker::halt() {
        
    }
    
    void Worker::enqueue(Task task) {
        taskQueue.push(task);
    }
    
}