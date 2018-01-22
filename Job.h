#pragma once

//System includes
#include <functional>

//Local includes
//#include "Worker.h"

namespace Xylena {
    
    class Job {
    private:
        int priority;
        unsigned int id;
    public:
        int getPriority() { return priority; };
        void setPriority(int _priority) { priority = _priority; };
        //void execute(Job *parent, Worker *worker, std::function function);
        
    };
}