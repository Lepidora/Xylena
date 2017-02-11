#pragma once

//System includes
#include <vector>

//Local includes
#include "Panel.h"

namespace Xylena {
    class Hive {
    private:
        std::vector<PanelPtr> panels;
        std::vector<PanelPtr>::iterator findPanel(PanelPtr panel);
    public:
        void addPanel(PanelPtr panel);
        
        void insertPanelBefore(PanelPtr insert, PanelPtr before);
        void insertPanelAfter(PanelPtr insert, PanelPtr after);

        void bringForward(PanelPtr panel);
        void sendBack(PanelPtr panel);
        
        void bringToFront(PanelPtr panel);
        void sendToBack(PanelPtr panel);
        
        void removePanel(PanelPtr panel);
        std::vector<PanelPtr> getPanels();
    };
}