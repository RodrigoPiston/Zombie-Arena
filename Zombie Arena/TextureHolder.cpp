#include "TextureHolder.h"

// Include the "assert feature"
#include <assert.h>

TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder() {
	// Ensures that m_s_Instance is not setted yet
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

Texture& TextureHolder::GetTexture(string const& filename) {

	// Get a reference to m_Textures using m_s_Instance
	auto& m = m_s_Instance -> m_Textures;
	// Auto is the equivalent of map<string,Texture>

	// Create an iterator to hold a key-value-pair
	// and search for the required kvp
	// using the passed in file name
	auto keyValuePair = m.find(filename);
	// auto is equivalent of map<string,Texture>::iterator

	// Did find a match?
	if (keyValuePair != m.end()) {
		return keyValuePair->second;
	}
	else {
		// File name not found
		// Create a new kvp using the filename
		auto& texture = m[filename];

		// Load the texture from file in the usual way
		texture.loadFromFile(filename);

		return texture;
	}

}