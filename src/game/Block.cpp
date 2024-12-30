#include "Block.hpp"

std::vector<Vertex> vertices {
	// FRONT
	{glm::vec3 (-0.5f, -0.5f,  0.5f), glm::vec3 (0.0f,  0.0f,  1.0f), glm::vec2 (0.0f,  0.0f)}, // 0 => Bottom Left
	{glm::vec3 (0.5f, -0.5f,  0.5f), glm::vec3 (0.0f,  0.0f,  1.0f), glm::vec2 (1.0f,  0.0f)}, // 1 => Bottom Right
	{glm::vec3 (0.5f,  0.5f,  0.5f), glm::vec3 (0.0f,  0.0f,  1.0f), glm::vec2 (1.0f,  1.0f)}, // 2 => Top Right
	{glm::vec3 (-0.5f,  0.5f,  0.5f), glm::vec3 (0.0f,  0.0f,  1.0f), glm::vec2 (0.0f,  1.0f)}, // 3 => Top Left

	// BACK
	{glm::vec3 (-0.5f, -0.5f, -0.5f), glm::vec3 (0.0f,  0.0f, -1.0f), glm::vec2 (0.0f,  0.0f)}, // 4
	{glm::vec3 (0.5f, -0.5f, -0.5f), glm::vec3 (0.0f,  0.0f, -1.0f), glm::vec2 (1.0f,  0.0f)}, // 5 
	{glm::vec3 (0.5f,  0.5f, -0.5f), glm::vec3 (0.0f,  0.0f, -1.0f), glm::vec2 (1.0f,  1.0f)}, // 6
	{glm::vec3 (-0.5f,  0.5f, -0.5f), glm::vec3 (0.0f,  0.0f, -1.0f), glm::vec2 (0.0f,  1.0f)}, // 7

	// LEFT
	{glm::vec3 (-0.5f, -0.5f, -0.5f), glm::vec3 (-1.0f,  0.0f,  0.0f), glm::vec2 (0.0f,  0.0f)}, // 8
	{glm::vec3 (-0.5f, -0.5f,  0.5f), glm::vec3 (-1.0f,  0.0f,  0.0f), glm::vec2 (1.0f,  0.0f)}, // 9
	{glm::vec3 (-0.5f,  0.5f,  0.5f), glm::vec3 (-1.0f,  0.0f,  0.0f), glm::vec2 (1.0f,  1.0f)}, // 10
	{glm::vec3 (-0.5f,  0.5f, -0.5f), glm::vec3 (-1.0f,  0.0f,  0.0f), glm::vec2 (0.0f,  1.0f)}, // 11

	// RIGTH
	{glm::vec3 (0.5f, -0.5f, -0.5f), glm::vec3 (1.0f,  0.0f,  0.0f), glm::vec2 (0.0f,  0.0f)}, // 12
	{glm::vec3 (0.5f, -0.5f,  0.5f), glm::vec3 (1.0f,  0.0f,  0.0f), glm::vec2 (1.0f,  0.0f)}, // 13
	{glm::vec3 (0.5f,  0.5f,  0.5f), glm::vec3 (1.0f,  0.0f,  0.0f), glm::vec2 (1.0f,  1.0f)}, // 14
	{glm::vec3 (0.5f,  0.5f, -0.5f), glm::vec3 (1.0f,  0.0f,  0.0f), glm::vec2 (0.0f,  1.0f)}, // 15

	// TOP
	{glm::vec3 (-0.5f,  0.5f, -0.5f), glm::vec3 (0.0f,  1.0f,  0.0f), glm::vec2 (0.0f,  0.0f)}, // 16
	{glm::vec3 (0.5f,  0.5f, -0.5f), glm::vec3 (0.0f,  1.0f,  0.0f), glm::vec2 (1.0f,  0.0f)}, // 17
	{glm::vec3 (0.5f,  0.5f,  0.5f), glm::vec3 (0.0f,  1.0f,  0.0f), glm::vec2 (1.0f,  1.0f)}, // 18
	{glm::vec3 (-0.5f,  0.5f,  0.5f), glm::vec3 (0.0f,  1.0f,  0.0f), glm::vec2 (0.0f,  1.0f)}, // 19

	// BOTTOM
	{glm::vec3 (-0.5f, -0.5f, -0.5f), glm::vec3 (0.0f, -1.0f,  0.0f), glm::vec2 (0.0f,  0.0f)}, // 20
	{glm::vec3 (0.5f, -0.5f, -0.5f), glm::vec3 (0.0f, -1.0f,  0.0f), glm::vec2 (1.0f,  0.0f)}, // 21
	{glm::vec3 (0.5f, -0.5f,  0.5f), glm::vec3 (0.0f, -1.0f,  0.0f), glm::vec2 (1.0f,  1.0f)}, // 22
	{glm::vec3 (-0.5f, -0.5f,  0.5f), glm::vec3 (0.0f, -1.0f,  0.0f), glm::vec2 (0.0f,  1.0f)}  // 23
};

std::vector<unsigned int> indices {
	// FRONT
	0, 2, 1,
	0, 2, 3,
	// BACK
	4, 6, 5,
	4, 6, 7,
	// LEFT
	8, 10, 9,
	8, 10, 11,
	// RIGHT
	12, 14, 13,
	12, 14, 15,
	// TOP
	16, 18, 17,
	16, 18, 19,
	// BOTTOM
	20, 22, 21,
	20, 22, 23
};

Block::Block (BlockType blockType, glm::vec3 position)
	: Mesh (vertices, indices), m_blockType (blockType)
{
	m_position = position;
}