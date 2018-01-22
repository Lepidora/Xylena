#pragma once

//System includes
#include <functional>

namespace Xylena {
    
    //Typedefs
    typedef std::function<void(void *, void *)> TransactionFunction;
    
    class Transaction {
    private:
        
        TransactionFunction function;
        
        void *object;
        void *data;
        
    public:
        //Sets up the transaction
        Transaction(TransactionFunction _function, void *_object, void *_data);
        
        //Executes the transaction, passing the given object and data pointers to the given transaction function
        void execute();
    };
}