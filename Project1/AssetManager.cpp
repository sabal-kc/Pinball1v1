#include "AssetManager.h"
#include<assert.h>

AssetManager* AssetManager::sInstance = nullptr;

AssetManager::AssetManager()
{
	assert(sInstance == nullptr);
	sInstance = this;
}


AssetManager::~AssetManager()
{
}

sf::Texture & AssetManager::GetTexture(std::string const & filename)
{
	// TODO: insert return statement here
	auto& texMap = sInstance->m_Textures;
	auto pairFound = texMap.find(filename);
	if (pairFound != texMap.end())
		return pairFound->second;
	else {
		auto& texture = texMap[filename];
		texture.loadFromFile(filename);
		return texture;
	}
	
}
