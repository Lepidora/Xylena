#include "stdafx.h"
#include "TextureHandler.h"

//Library Includes
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

//Local includes
#include "GLTypes.h"

namespace Xylena {

	Texture * TextureHandler::createTextureFromFile(const char* filename) {
		
        ///Creates a new texture and binds the data in the given file to a GL texture
        Texture *texture = new Texture();
        TextureImage textureID = bindImageDataForFilename(filename);

        ///Adds the GL texture to the texture object and returns it
        texture->addTexture(textureID);
        return texture;
	}

    Texture * TextureHandler::createTextureFromFiles(std::vector<char *> filenames) {
        
        Texture *texture = new Texture();

        ///Iterate through the vector of filenames, bind a texture for each one and add the texture to the Texture object
        for (unsigned int i = 0; i < filenames.size(); i++) {
            TextureImage textureID = bindImageDataForFilename(filenames[i]);
            texture->addTexture(textureID);
        }

        return texture;

    }

    std::vector<unsigned char> TextureHandler::convertIntArrayToVector(unsigned char * data, int pixelcount, int bitdepth) {

        unsigned int byteCount = pixelcount * bitdepth;

        ///Construct the vector and manually reserve enough space to put all of the pixel data into
        std::vector<unsigned char> vectorData;
        vectorData.reserve(byteCount);
        
        ///Run a simple loop through the data and add it all to the vector
        for (size_t byteIndex = 0; byteIndex < byteCount; byteIndex++) {
            //vectorData[byteIndex] = data[byteIndex];
            vectorData.push_back(data[byteIndex]);
        }

        return vectorData;
    }

    std::vector<unsigned char> TextureHandler::convertRGBtoRGBA(std::vector<unsigned char> data, const unsigned int pixelcount) {

        ///Construct a vector and manually reserve enough space to hold all of the pixel data by multiplying (width * height) by the desired bit depth
        std::vector<unsigned char> tempdata;
        tempdata.reserve(pixelcount * 4);

        for (size_t pixelindex = 0; pixelindex < pixelcount; pixelindex++) {

            ///Calculate the initial positions for each pixel in the input data by multiplying the current pixel by the bit depth of the data set
            size_t dataindex = pixelindex * 3;
            size_t tempdataindex = pixelindex * 4;

            ///Fill the first three output pixels with the relevant image data and fill the last one with 1.0f alpha value
            tempdata.push_back(data[dataindex + 0]);
            tempdata.push_back(data[dataindex + 1]);
            tempdata.push_back(data[dataindex + 2]);
            tempdata.push_back(255);
        }

        return tempdata;
    }

    std::vector<unsigned char> TextureHandler::flipVertically(std::vector<unsigned char> data, unsigned int width, unsigned int height) {

        ///Iterate through the rows in the image up until the height divided by 2. This is because further iteration beyond that is unnecessary. In an image with an odd height, the middle row will be ignored intentionally
        for (size_t rowIndex = 0; rowIndex < height / 2; rowIndex++) {

            ///Iterate through each column in the image
            for (size_t columnIndex = 0; columnIndex < width; columnIndex++) {

                for (size_t bitIndex = 0; bitIndex < 4; bitIndex++) {
                    ///Pre calculate the necessary indicies because they are used more than once
                    size_t firstIndex = (((rowIndex * width) + columnIndex) * 4) + bitIndex;
                    ///This index is the first index mirrored vertically along the centre of the image
                    size_t secondIndex = ((((height - 1 - rowIndex) * width) + columnIndex) * 4) + bitIndex;

                    ///Take a buffer of the data at the first index
                    unsigned char bufferValue = data[firstIndex];

                    ///Swap the data in the first and second indicies
                    data[firstIndex] = data[secondIndex];
                    data[secondIndex] = bufferValue;
                }

                
            }
        }

        return data;
    }

    TextureImage TextureHandler::bindImageDataForFilename(const char* filename) {

        ///Get the width, height and bytes
        int width, height, bytedepth, pixelcount;
        unsigned char *rawdata = stbi_load(filename, &width, &height, &bytedepth, 0);

        std::vector<unsigned char> data;
        
        if (!rawdata) {
            printf("No image data read for %s\n", filename);
            
            std::vector<unsigned char> missingTexture = {0xFF, 0x00, 0xDA, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xDA, 0xFF, 0x00, 0x00, 0x00, 0xFF};
            
            data = missingTexture;
            pixelcount = 4;
            bytedepth = 4;
            
        } else {
            
            pixelcount = width * height;
            
            ///Convert the raw data to a vector format for easy use
            data = convertIntArrayToVector(rawdata, pixelcount, bytedepth);
        }

        ///If the byte depth isn't RGBA, convert the data to it
        if (bytedepth != 4) {
            if (bytedepth == 3) {
                
                data = convertRGBtoRGBA(data, pixelcount);

                ///Set the byte depth to 4 to represent the current data
                bytedepth = 4;
            }
        }

        ///Flip the data vertically so that it works with OpenGL's texture coordinate system
        data = flipVertically(data, width, height);

        ///Create a new texture and generate a buffer for it
        TextureImage textureID;
        glGenTextures(1, &textureID);
        
        glBindTexture(GL_TEXTURE_2D, textureID);        

        ///Makes sure only RGBA data is used. Greyscale images are not currently supported
        if (bytedepth == 4) {

            ///Pass the data to OpenGL
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data.front());
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        ///Bind a NULL texture, just so nothing accidentally happens to our texture somewhere else
        glBindTexture(GL_TEXTURE_2D, NULL);

        ///Free the image data after we're done with the textures
        stbi_image_free(rawdata);

        return textureID;

    }
    
    Texture * TextureHandler::createTextureFromPixelArray(std::vector<unsigned char> pixels, int width, int height) {
        
        Texture * texture = new Texture();
        
        ///Create a new texture and generate a buffer for it
        TextureImage textureID;
        glGenTextures(1, &textureID);
        
        glBindTexture(GL_TEXTURE_2D, textureID);
        
        ///Makes sure only RGBA data is used. Greyscale images are not currently supported
        //if (bytedepth == 4) {
            
            ///Pass the data to OpenGL
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels.front());
        //}
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        
        ///Bind a NULL texture, just so nothing accidentally happens to our texture somewhere else
        glBindTexture(GL_TEXTURE_2D, NULL);
        
        texture->addTexture(textureID);
        
        return texture;
        
    }
    
}