#pragma once

//System includes
#include <string>

//Local includes
#include "Panel.h"
#include "Script.h"

namespace Xylena {
    
    class PanelHandler {
    private:
        static void addPanelToScript(ScriptPtr script, PanelPtr panel);
    public:
        
        static PanelPtr createPanel(std::string filename);
        
    };
}