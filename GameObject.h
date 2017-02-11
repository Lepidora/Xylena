#pragma once

//System includes
#include <memory>

//Local includes
#include "Location.h"
#include "Texture.h"
#include "GLTypes.h"
#include "InputEvent.h"

//Component includes
#include "RenderComponent.h"
#include "InputComponent.h"

namespace Xylena {
		
	class Stage;
	typedef std::shared_ptr<Stage> StagePtr;

	class GameObject {
    private:
        static unsigned long int uidCounter;
	protected:
        
        unsigned long int uid;
        
		bool visible;

		LocationPtr location;
		TexturePtr texture;

        ///Rotation values in degrees
        float objectRotation;
        float textureRotation;

        ///Offset from the object's position that the texture should be rendered
        float texXOffset;
        float texYOffset;

        ///Render order level
        float renderOrderLevel;

		///Reference to stage that the object is in
		Stage *stage;

        ///Components
        RenderComponent *renderComponent;
        InputComponent *inputComponent;

	public:
        GameObject();
        ~GameObject();

		///Visibility setting
		void setVisibility(bool _visible);
		bool isVisible();

		///Update methods
		virtual void preUpdate();
		virtual void update();
		virtual void postUpdate();
        
        ///Stage assignment/retrieval
        void setStage(Stage *_stage) { stage = _stage; };
        Stage* getStage() { return stage; };

		///Location assignment/retrieval
		void setLocation(LocationPtr _location) { location = _location; };
		LocationPtr getLocation() { return location; };

		///Texture assignment/retrieval
		void setTexture(TexturePtr _texture) { texture = _texture; };
        void setTexture(const char * filename);
		TexturePtr getTexture() { return texture; };

        ///Direct position setting
        void setPosition(float x, float y);
        void setPosition(float x, float y, float z);
        void setPosition(Coordinate position);
        Coordinate getPosition();

        ///Relative position setting
        void translatePosition(float x, float y);
        void translatePosition(float x, float y, float z);

        ///Direct size setting
        void setSize(float width, float height);
        void setSize(float width, float height, float depth);
        Coordinate getSize();

        ///Get/set object rotation
        void setRotation(float rotation) { objectRotation = rotation; };
        float getRotation() { return objectRotation; };

        ///Get/set texture rotation
        void setTextureRotation(float rotation) { textureRotation = rotation; };
        float getTextureRotation() { return textureRotation; };

        ///Get/set texture
        void setTextureOffset(float x, float y) { texXOffset = x; texYOffset = y; };
        float getTextureXOffset() { return texXOffset; };
        float getTextureYOffset() { return texYOffset; };
        
        ///Get/set render level
        void setRenderLevel(float renderLevel) { renderOrderLevel = renderLevel; };
        float getRenderLevel() { return renderOrderLevel; };

        ///Get/set render components
        void setRenderComponent(RenderComponent *component) { renderComponent = component; };
        RenderComponent* getRenderComponent() { return renderComponent; };

        ///Get/set input components
        void setInputComponent(InputComponent *component) { inputComponent = component; };
        InputComponent* getInputComponent() { return inputComponent; };
        
        ///Get UID
        unsigned long int getUID();
        
        ///Removes this object from the stage it's in
        void destroy();

        //Advanced functions
        
        ///Collision handling
        virtual void collide(GameObject *target) {};
        
        ///Rotate the object towards the mouse pointer
        void pointToMouse();
        
        //Event Handlers
        
        //Mouse Event Handlers
        
        //Called when object is clicked on
        virtual void onClick(KeyCode button, double mouseX, double mouseY, bool top);
        
        //Called when the mouse is pressed down over the object
        virtual void mouseDown(KeyCode button, double mouseX, double mouseY, bool top);
        
        //Called when the mouse is released over the object
        virtual void mouseUp(KeyCode button, double mouseX, double mouseY, bool top);
        
        //Called when the mouse is over the object's bounding box
        virtual void mouseOver(double mouseX, double mouseY, bool top);
        
        //Called when the mouse enters the object's bounding box
        virtual void mouseEnter(double mouseX, double mouseY, bool top);
        
        //Called when the mouse leaves the object's bounding box
        virtual void mouseLeave(double mouseX, double mouseY, bool top);
        

	};

	//Typedefs
	typedef std::shared_ptr<GameObject> GameObjectPtr;

}