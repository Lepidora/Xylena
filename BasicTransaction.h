#pragma once

//Local includes
#include "Transaction.h"

namespace Xylena {
    
    class BasicTransaction: public Transaction {
    private:
        void basicTransactionFunction(void *_object, void *_data);
    public:
        BasicTransaction(void *_object, void *_data);
    };
}