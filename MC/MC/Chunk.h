#pragma once
#ifndef CHUNK_H
#define CHUNK_H
#include<list>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Block.h"
#include"PerlinNoise.h"
#include "Shader.h"
#include "config.h"

class Chunk {
public:
	//const static int width = 16; //ÿ��Chunk�ĳ���Size 
	//const static int height = 64; //ÿ��Chunk�ĸ߶� 
	//int seed; //������� 
	bool isLoad;

	Chunk(int x,int y);
	void renderChunk(glm::mat4 model, unsigned int VAO, Shader* myShader);

	Block::blockType blocks[CHUNKWIDTH][CHUNKWIDTH][CHUNKHEIGHT];	// Chunk������
	bool isRender[CHUNKWIDTH][CHUNKWIDTH][CHUNKHEIGHT];			// ��ǵ�ǰ������Ƿ��б���Ⱦ
	//int visibleHeight[ width + 2 ][ width + 2 ];	// ������ɵĿɼ��ر�߶� 
	bool layerRender[CHUNKHEIGHT];
	//chunk��map�е����꣺
	int x;
	int y;

	void updateRenderInformation();

};
#endif 