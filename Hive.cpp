#include "Hive.h"

//System includes
#include <algorithm>

namespace Xylena {
    
    std::vector<PanelPtr>::iterator Hive::findPanel(PanelPtr panel) {
        return std::find(panels.begin(), panels.end(), panel);
    }
    
    void Hive::addPanel(PanelPtr panel) {
        panels.push_back(panel);
    }
    
    void Hive::insertPanelBefore(PanelPtr insert, PanelPtr before) {
        panels.insert(findPanel(before), insert);
    }
    
    void Hive::insertPanelAfter(PanelPtr insert, PanelPtr after) {
        panels.insert(findPanel(after)++, insert);
    }
    
    void Hive::bringForward(PanelPtr panel) {
        
        auto it = findPanel(panel);
        
        if (it != panels.begin()) {
            std::iter_swap(it, it--);
        }
    }
    
    void Hive::sendBack(PanelPtr panel) {
        
        auto it = findPanel(panel);
        
        if (it != panels.end()) {
            std::iter_swap(it, it++);
        }
    }

    void Hive::bringToFront(PanelPtr panel) {
        
        auto it = findPanel(panel);
        
        panels.erase(it);
        panels.insert(panels.begin(), panel);
    }
    
    void Hive::sendToBack(PanelPtr panel) {
        
        auto it = findPanel(panel);
        
        panels.erase(it);
        panels.insert(panels.end(), panel);
    }
    
    void Hive::removePanel(PanelPtr panel) {
        panels.erase(std::remove(panels.begin(), panels.end(), panel), panels.end());
    }
    
    std::vector<PanelPtr> Hive::getPanels() {
        return panels;
    }
    
}