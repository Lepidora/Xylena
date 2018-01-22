#pragma once

//Defines
#define CACHE_SIZE 64

//System includes
#include <atomic>

namespace Xylena {
    
    template <typename T>
    class Store {
    private:
        alignas(CACHE_SIZE) volatile std::atomic<bool> lockval;
        unsigned char data[CACHE_SIZE - sizeof(lockval)];
        
    public:
        Store();
        bool locked();
        void lock();
        void unlock();
        void put(T item);
        void * get();
    };
}
