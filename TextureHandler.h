#pragma once

//System includes
#include <vector>

//Local includes
#include "Texture.h"

namespace Xylena {

	class TextureHandler {
    private:
        static TextureImage bindImageDataForFilename(const char* filename);
        static std::vector<unsigned char> convertIntArrayToVector(unsigned char * data, int pixelcount, int bitdepth);
        static std::vector<unsigned char> flipVertically(std::vector<unsigned char> data, unsigned int width, unsigned int height);
        static std::vector<unsigned char> convertRGBtoRGBA(std::vector<unsigned char> data, const unsigned int pixelcount);
	public:
		TextureHandler() {};
		~TextureHandler() {};

		///Reads image data from the given file and binds it to an OpenGL texture, then returns a Texture object
		static Texture * createTextureFromFile(const char* filename);

        ///Reads image data from the given file names and binds them to OpenGL textures and returns a Texture object
        static Texture * createTextureFromFiles(std::vector<char *> filenames);
        
        static Texture * createTextureFromPixelArray(std::vector<unsigned char> pixels, int width, int height);
	};
}
