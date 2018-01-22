#include "Panel.h"

#include "TextureHandler.h"

namespace Xylena {
    
    Panel::Panel() {
        xAnchor = 0;
        yAnchor = 0;
        opacity = 1.0;
        backgroundTexture = nullptr;
        component = nullptr;
    }
    
    Panel::Panel(std::string scriptLocation): Panel() {
        script = ScriptPtr(new Script(scriptLocation));
        initialise();
    }
    
    std::vector<PanelPtr>::iterator Panel::findPanel(PanelPtr panel) {
        return std::find(panels.begin(), panels.end(), panel);
    }
    
    void Panel::setAnchor(Anchor a) {
        switch (a) {
            case TOP_LEFT: {
                setAnchor(0.0, 0.0);
                break;
            }
                
            case TOP_MIDDLE: {
                setAnchor(0.5, 0.0);
                break;
            }
                
            case TOP_RIGHT: {
                setAnchor(1.0, 0.0);
                break;
            }
                
            case MIDDLE_LEFT: {
                setAnchor(0.0, 0.5);
                break;
            }
                
            case MIDDLE: {
                setAnchor(0.5, 0.5);
                break;
            }
                
            case MIDDLE_RIGHT: {
                setAnchor(1.0, 0.0);
                break;
            }
                
            case BOTTOM_LEFT: {
                setAnchor(0.0, 1.0);
                break;
            }
                
            case BOTTOM_MIDDLE: {
                setAnchor(0.5, 1.0);
                break;
            }
                
            case BOTTOM_RIGHT: {
                setAnchor(1.0, 1.0);
                break;
            }
                
            default:
                break;
        }
    }
    
    void Panel::setXAnchor(float x) {
        xAnchor = x;
    }
    
    void Panel::setYAnchor(float y) {
        yAnchor = y;
    }
    
    void Panel::setAnchor(float x, float y) {
        setXAnchor(x);
        setYAnchor(y);
    }
    
    float Panel::getXAnchor() {
        return xAnchor;
    }
    
    float Panel::getYAnchor() {
        return yAnchor;
    }
    
    void Panel::addPanel(PanelPtr panel) {
        panels.push_back(panel);
    }
    
    void Panel::insertPanelBefore(PanelPtr insert, PanelPtr before) {
        panels.insert(findPanel(before), insert);
    }
    
    void Panel::insertPanelAfter(PanelPtr insert, PanelPtr after) {
        panels.insert(findPanel(after)++, insert);
    }
    
    void Panel::bringForward(PanelPtr panel) {
        
        auto it = findPanel(panel);
        
        if (it != panels.begin()) {
            std::iter_swap(it, it--);
        }
    }
    
    void Panel::sendBack(PanelPtr panel) {
        
        auto it = findPanel(panel);
        
        if (it != panels.end()) {
            std::iter_swap(it, it++);
        }
    }
    
    void Panel::bringToFront(PanelPtr panel) {
        
        auto it = findPanel(panel);
        
        panels.erase(it);
        panels.insert(panels.begin(), panel);
    }
    
    void Panel::sendToBack(PanelPtr panel) {
        
        auto it = findPanel(panel);
        
        panels.erase(it);
        panels.insert(panels.end(), panel);
    }
    
    void Panel::removePanel(PanelPtr panel) {
        panels.erase(std::remove(panels.begin(), panels.end(), panel), panels.end());
    }
    
    std::vector<PanelPtr> Panel::getPanels() {
        return panels;
    }
    
    void Panel::setOpacity(float _opacity) {
        opacity = _opacity;
    }
    
    float Panel::getOpacity() {
        return opacity;
    }
    
    void Panel::setBackgroundTexture(TexturePtr tex) {
        backgroundTexture = tex;
    }
    
    void Panel::setBackgroundImage(char * filename) {
        TexturePtr tex = TexturePtr(TextureHandler::createTextureFromFile(filename));
        backgroundTexture = tex;
    }
    
    TexturePtr Panel::getBackgroundImage() {
        return backgroundTexture;
    }
    
    void Panel::setRenderComponent(RenderComponent *_component) {
        component = _component;
    }
    
    RenderComponent * Panel::getRenderComponent() {
        return component;
    }
    
    void Panel::initialise() {
        
        void (Panel::*setAnchorFptr)(std::string) = &Panel::setAnchor;
        void (Panel::*setXAnchorFptr)(float) = &Panel::setXAnchor;
        void (Panel::*setYAnchorFptr)(float) = &Panel::setYAnchor;
        void (Panel::*setXYAnchorFptr)(float, float) = &Panel::setAnchor;
        
        float (Panel::*getXAnchorFptr)() = &Panel::getXAnchor;
        float (Panel::*getYAnchorFptr)() = &Panel::getYAnchor;
        
        void (Panel::*setOpacityFptr)(float) = &Panel::setOpacity;
        float (Panel::*getOpacityFptr)() = &Panel::getOpacity;
              
        
        script->addObject("self", *this,
                          "setAnchor", setAnchorFptr,
                          "setXAnchor", setXAnchorFptr,
                          "setYAnchor", setYAnchorFptr,
                          "setXYAnchor", setXYAnchorFptr,
                          
                          "getXAnchor", getXAnchorFptr,
                          "getYAnchor", getYAnchorFptr,
                          
                          "setOpacity", setOpacityFptr,
                          "getOpacity", getOpacityFptr
                          );
        
        createSelector = getSelector("create");
        callScriptFunction(createSelector);
        
    }

}