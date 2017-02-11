#pragma once

//System includes
#include <queue>
#include <map>

//Local includes
#include "GameObject.h"
#include "GLTypes.h"

namespace Xylena {

	//Typedefs
	typedef GLuint VAO;

    struct RenderSprite {
        TexturePtr texturePtr;
        LocationPtr locationPtr;
        float rotation;
        float depth;
        
    };

	class Render {
	private:

        ///Static queue for rendering a simple sprite
        static std::queue<RenderSprite> spriteRenderQueue;
        static std::map<unsigned int, std::map<float, std::vector<GameObjectPtr>>> testMap;
        static std::map<ComponentUID, std::map<float, std::vector<GameObjectPtr>>> renderOrderMap;

		static VAO vertexArray;

        static VAO textureVertexArray;
        static VBO textureBuffer;
        static ShaderProgram textureProgram;
        
        static bool cullOutOfFrame;

        static void addGameObjectToMap(GameObjectPtr objectPtr);

	public:
		Render();

		static void initRenderer();
		static GLuint getVertexArray() { return vertexArray; };
        static void rebindVertexArray(VAO newVertexArray);
        
        static void setBackgroundColor(int red, int green, int blue, int alpha);

		static void render(double interpolation);
		static void renderSimpleObject(GameObjectPtr object);

        static void renderSprite(TexturePtr texture, LocationPtr location, float rotation, float depth);
        static void renderSprite(RenderSprite sprite);
        
        static void cullOutOfFrameObjects(bool cull);
	};

}
