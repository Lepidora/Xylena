#pragma once

//System includes
#include <string>

//Local includes
#include "Panel.h"

namespace Xylena {
    
    class PanelHandler {
    public:
        
        static PanelPtr parsePanelFromFile(std::string filename);
        
    };
}