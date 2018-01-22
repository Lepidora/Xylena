#include "Store.h"

//System includes
#include <cstring>

namespace Xylena {
    
    template<typename T>
    bool Store<T>::locked() {
        return lockval;
    }
    
    template<typename T>
    void Store<T>::lock() {
        lockval = true;
    }
    
    template<typename T>
    void Store<T>::unlock() {
        lockval = false;
    }
    
    template<typename T>
    void Store<T>::put(T item) {
        
        std::memcpy(data, item, sizeof(item));
    }
    
    template<typename T>
    void * Store<T>::get() {
        return (void *)(data);
    }
    
}