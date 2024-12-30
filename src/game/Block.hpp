#pragma once

#include <glm/glm.hpp>

#include "graphics/Mesh.hpp"

enum BlockType {
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
	private:
		BlockType m_blockType;
};