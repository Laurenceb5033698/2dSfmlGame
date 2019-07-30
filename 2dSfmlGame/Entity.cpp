#include "Entity.h"

Entity::Entity()
	:rm(NULL)
{

}


Entity::~Entity()
{

	delete[] m_frames;

}

bool Entity::LoadTexture(const std::string& textureFilepath)
{
	//Try to Load texture and store it into m_pTexture
	if (rm->GetTexture(textureFilepath, m_ptexture)) {
		DBOUT("failed to Get texture" << textureFilepath);
			return EXIT_FAILURE;

	}
	return EXIT_SUCCESS;
}
