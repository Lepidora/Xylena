#include "Transaction.h"

namespace Xylena {
    
    Transaction::Transaction(TransactionFunction _function, void *_object, void *_data) {
        
        function = _function;
        object = _object;
        data = _data;
    }
    
    void Transaction::execute() {
        function(object, data);
    }
    
}