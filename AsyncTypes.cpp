#include "AsyncTypes.h"

namespace Xylena {
    
    Task::Task() {}
    
    Task::Task(TaskType taskRunnable) {
        task = taskRunnable;
    }
    
    void Task::execute() {
        task();
    }
}