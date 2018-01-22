#pragma once

//System includes
#include <vector>
#include <memory>
#include <string>

//Local includes
#include "RenderComponent.h"
#include "Texture.h"
#include "Scriptable.h"

namespace Xylena {
    
    typedef enum : unsigned int {
        TOP_LEFT,
        TOP_MIDDLE,
        TOP_RIGHT,
        MIDDLE_LEFT,
        MIDDLE,
        MIDDLE_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_MIDDLE,
        BOTTOM_RIGHT
    } Anchor;
    
    class Panel;
    typedef std::shared_ptr<Panel> PanelPtr;
    
    class Panel: public Scriptable {
    private:
        std::vector<PanelPtr> children;
        
        std::vector<PanelPtr> panels;
        std::vector<PanelPtr>::iterator findPanel(PanelPtr panel);
        
        float xAnchor;
        float yAnchor;
        
        float opacity;
        
        TexturePtr backgroundTexture;
        
        RenderComponent *component;
        
        SelectorPtr createSelector;
        
    public:
        
        Panel();
        Panel(std::string filename);
        
        void setAnchor(Anchor a);
        void setAnchor(std::string s);
        
        void setXAnchor(float x);
        void setYAnchor(float y);
        
        void setAnchor(float x, float y);
        
        float getXAnchor();
        float getYAnchor();
        
        void addPanel(PanelPtr panel);
        
        void insertPanelBefore(PanelPtr insert, PanelPtr before);
        void insertPanelAfter(PanelPtr insert, PanelPtr after);
        
        void bringForward(PanelPtr panel);
        void sendBack(PanelPtr panel);
        
        void bringToFront(PanelPtr panel);
        void sendToBack(PanelPtr panel);
        
        void removePanel(PanelPtr panel);
        
        std::vector<PanelPtr> getPanels();
        
        void setOpacity(float _opacity);
        float getOpacity();
        
        void setBackgroundTexture(TexturePtr tex);
        void setBackgroundImage(char * filename);
        TexturePtr getBackgroundImage();
        
        void setRenderComponent(RenderComponent *component);
        RenderComponent *getRenderComponent();
        
        void initialise();
        
    };
}