#pragma once

//System includes
#include <vector>
#include <memory>

//OpenGL include
#include "OpenGL.h"

//Local includes
#include "GLTypes.h"

namespace Xylena {

	//Structs
	/*struct TextureImage {
		std::vector<char> data;
		int width;
		int height;
	};*/

	//Typedefs
	//typedef GLuint TextureImage;

	class Texture {

	protected:

		///Stores an index for keeping track of animated textures
		unsigned long index;

		///Stores an array of images for rendering animated textures
		std::vector<TextureImage> images;

	public:
        Texture();
        ~Texture() {};

		///Gets the image at the current value of index, then increments index. This is also used to get the texture if only one texture image is stored
		TextureImage getNextTexture();
        void tickAnimation();

		///Gets the texture at the specified index. Throws std::out_of_bounds if the given index is larger than the size of the images vector
		TextureImage getTextureAtIndex(unsigned long _index);

        ///Sets the texture at the specified index. Throws std::out_of_bounds if the given index is larger than the size of the images vector
        void setTextureAtIndex(TextureImage textureID, unsigned long _index);

        ///Adds a texture to the end of the images vector
        void addTexture(TextureImage textureID);

		///Increment and decrement index by a given amount. If the amount given is larger than the size of the images vector, it will wrap around
		void incrementIndex(unsigned long amount);
		void decrementIndex(unsigned long amount);

		///Set index to the given index. Throws std::out_of_bounds if the given index is larger than the size of the images vector
		void setIndex(unsigned long _index);
	};

	//Typedefs
	typedef std::shared_ptr<Texture> TexturePtr;
	

}
