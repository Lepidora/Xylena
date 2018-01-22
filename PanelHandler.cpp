#include "PanelHandler.h"

namespace Xylena {
    
    PanelPtr PanelHandler::createPanel(std::string filename) {
        return PanelPtr(new Panel(filename));
    }
    
}