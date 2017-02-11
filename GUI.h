#pragma once

//System includes
#include <vector>

//Local includes
#include "Panel.h"

namespace Xylena {
    
    class GUI {
    private:
        
        static PanelPtr currentPanel;
        
    public:
        
        
        
        void setCurrentPanel(PanelPtr panel);
        
        void render();
        
    };
}