#pragma once
#ifndef  BLOCK_H
#define BLOCK_H
#include <string>
#include "Texture.h"
#include <glm/glm.hpp>
class Block
{
public:

	enum blockType { //Block������ 
		Air = 0,//����
		Water =1,//ˮ
		Soil = 2,//����
		Stone = 3,//ʯ
		Grass = 4,//��Ƥ
		Sand = 5,//ɳ��
		StondBrick = 6,//ʯש
		Leaf = 7,//��Ҷ
		Bark = 8,//��Ƥ
		Cactus = 9,//������
		Cloud = 10,//�ƶ�
	};

	static std::vector<Texture> textures;
    const static float vertices[];
	const static size_t vsize;

	static int loadTextures();

};
class operateBlock//the placed block's information
{
public:
	void init();
	operateBlock();
	int mapCoord[3];
	Block::blockType type;
};

#endif // 
