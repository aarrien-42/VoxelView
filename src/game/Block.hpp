#pragma once

#include <glm/glm.hpp>

#include <string>

#include "graphics/Mesh.hpp"
#include "graphics/OpenGL/Texture.hpp"

enum BlockType {
	GRASS,
	DIRT,
	STONE
};

/**
* @brief A block in the world
*/
class Block : public Mesh {
	public:
		Block (BlockType blockType, glm::vec3 position);
		~Block () = default;

		std::vector<std::string> GetTexturePaths () const;
	private:
		BlockType m_blockType;
};