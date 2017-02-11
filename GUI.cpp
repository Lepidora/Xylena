#include "GUI.h"

namespace Xylena {
    
    PanelPtr GUI::currentPanel = nullptr;
    
    void GUI::setCurrentPanel(PanelPtr panel) {
        currentPanel = panel;
    }
    
    void GUI::render() {
        if (currentPanel) {
            
        }
    }
    
}