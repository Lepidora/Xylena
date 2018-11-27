#pragma once

#include <functional>

namespace Xylena {
    
    //Task type definition
    #define TaskType std::function<void()>
    #define block(code) [=](){code;}
    
    class Task {
    private:
        TaskType task;
    public:
        Task();
        Task(TaskType taskRunnable);
        
        void execute();
        
        void operator()(){
            //task();
        }
    };
}