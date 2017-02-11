#include "stdafx.h"
#include "Texture.h"

namespace Xylena {

    Texture::Texture() {
        index = 0;
    }

	TextureImage Texture::getNextTexture() {

		//If there's nothing in the images vector, return an empty texture
		if (images.empty() == true) {
			return TextureImage();
		} else {

			//Try to return the image at the index. If that fails, return an empty image
			try {
				TextureImage image = images.at(index);
				return image;
			} catch (const std::out_of_range&) {
				return TextureImage();
			}
			
		}
	}

    void Texture::tickAnimation() {
        this->incrementIndex(1);
    }

	TextureImage Texture::getTextureAtIndex(unsigned long _index) {
		return images.at(_index);
	}

    void Texture::setTextureAtIndex(TextureImage textureID, unsigned long _index) {
        images[_index] = textureID;
    }

    void Texture::addTexture(TextureImage textureID) {
        images.push_back(textureID);
    }

	void Texture::incrementIndex(unsigned long amount) {

		//The amount of images stored represents the maximum that the index can be
		size_t max = images.size();

		//If there is only one image stored, forego calculating the increment
		if (max > 1) {
			//If the increment will be less than the amount of images stored, just add it on
			if ((index + amount) < max) {
				index += amount;
			} else {
				//If not, take the modulous of the proposed index. This prevents issues for when it is asked to increment by numbers far larger than the total size
				index = (index + amount) % max;
			}
		}
	}

	void Texture::decrementIndex(unsigned long amount) {
		
		//The amount of images stored represents the maximum that the index can be
		size_t max = images.size();

		//If there is only one image stored, forego calculating the decrement
		if (max > 1) {
			//If the decrement will be greater than zero, just subtract it
			if ((index - amount) > 0) {
				index -= amount;
			} else {
				//If not, subtract the modulous of the amount and the maximum index and subtract it from the maximum index. This prevents issues with decrements much larger than the total size
				index = max - (amount % max);
			}
		}
	}

	void Texture::setIndex(unsigned long _index) {
		//If the index is within the possible range of indices, set it
		if (_index < images.size()) {
			index = _index;
		} else {
			//If not, throw a standard out of range error
			throw std::out_of_range("index out of range");
		}
	}

}