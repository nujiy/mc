#include "MapGenerator.h"
#include <time.h>

MapGenerator::MapGenerator()
{
}

void MapGenerator::generateMap(Chunk* chunks[CHUNKSIZE][CHUNKSIZE], int startX, int startY)
{
	//render a chunk
// ���ɸ߶�
	for (int i = 0; i < mapWidth ; ++i) {
		double radio = 1.0;
		for (int j = 0; j < mapWidth; ++j) {
			int h = generateHeight((startX + i) * radio, (startY + j) * radio, radio); //��ȡ��ǰλ�÷���������ɵĸ߶�ֵ 
			heightMap[i][j] = h; //write down random visible height
		}
	}
	for (int m = 0; m < CHUNKSIZE; ++m) {
		for (int n = 0; n < CHUNKSIZE; ++n) {
			Chunk* c = chunks[m][n];
		}
	}
}

int MapGenerator::generateHeight(double x, double y, double interval)
{
	double small = PNoiseSmoth2D(x, y, 0.025, 4, interval) * 24 + 24;
	double large = PNoiseSmoth2D(-x, -y, 0.025, 2, interval) / 2 + 1;
	int h = (int)(small * large) + 2;
	//std::cout << h <<std:: endl;
	return h > waterheight ? h : waterheight;
}

Block::blockType MapGenerator::generateBlockType(int z, int h) {
	if (z > h) { //��ǰ����λ�ø���������ɵĸ߶�ֵʱ����ǰ��������Ϊ�� 
		return Block::Air;
	}
	if (h > sandheight) {
		if (z == h) { //��ǰ����λ�õ���������ɵĸ߶�ֵʱ����ǰ��������Ϊ�ݵ� 
			return Block::Grass;
		}
		//��ǰ����λ��С��������ɵĸ߶�ֵ �� ���� genHeight - 5ʱ����ǰ��������Ϊ���� 
		if (z < h && z > h - 5) {
			return Block::Soil;
		}
		else return Block::Stone; //�����������ǰ��������Ϊ��ʯ
	}
	else if (h > waterheight) {
		if (z <= h && z > h - 5) {
			return Block::Sand;
		}
		else return Block::Stone;
	}
	else {
		if (z <= h && z > h - 5) {
			return Block::Water;
		}
		else return Block::Sand;
	}
}

bool MapGenerator::isVisible(Chunk* c, int i, int j, int k)       //block��chunk�е�����
{	//flag==true, render; flag==false, not render
		bool flag = false;
		if (k >= heightMap[i + c->x * CHUNKWIDTH][j + c->y * CHUNKWIDTH]) {
			flag = true;
		}
		if (k > heightMap[i + 1 + c->x * CHUNKWIDTH][j + c->y * CHUNKWIDTH]) {
			flag = true;
		}
		if (k > heightMap[i - 1 + c->x * CHUNKWIDTH][j + c->y * CHUNKWIDTH]) {
			flag = true;
		}
		if (k >= heightMap[i + c->x * CHUNKWIDTH][j + 1 + c->y * CHUNKWIDTH]) {
			flag = true;
		}
		if (k >= heightMap[i + c->x * CHUNKWIDTH][j - 1 + c->y * CHUNKWIDTH]) {
			flag = true;
		}
		return flag;
}

void MapGenerator::generateBlock(Chunk* c)
{	
	// ���ɻ�����������
	for (int i = 0; i < CHUNKWIDTH; ++i) {
		for (int j = 0; j < CHUNKWIDTH; ++j) {
			for (int k = 0; k < CHUNKHEIGHT; ++k) {
				c->blocks[i][j][k] = generateBlockType(k, heightMap[i + c->x * CHUNKWIDTH][j + c->y * CHUNKWIDTH]);
			}
		}
	}
	// �ɼ��б�
	for (int i = 0; i < CHUNKWIDTH; ++i) {
		double radio = 3;
		for (int j = 0; j < CHUNKWIDTH; ++j) {
			for (int k = 0; k < CHUNKHEIGHT; ++k) {
				c->isRender[i][j][k] = false;
				if (k <= Chunk * c, int i, int j, int k) {
					chunks[m]->isRender[i][j][k] = isVisible(m, i, j, k);
				}
			}
		}
	}

	// �����ƶ�
	for (int i = 0; i < CHUNKWIDTH; ++i) {
		double radio = 3;
		for (int j = 0; j < CHUNKWIDTH; ++j) {
			if (PerlinNoise2D(chunks[m]->x * radio + i * radio / CHUNKWIDTH, chunks[m]->y * radio + j * radio / CHUNKWIDTH, 0.5, 1) > 0.2) {
				chunks[m]->blocks[i][j][Chunk::height - 1] = Block::Cloud;
				chunks[m]->isRender[i][j][Chunk::height - 1] = true;
			}
		}
	}

	// ���ɻ�����ľ
	for (int i = 0; i < Chunk::width; ++i) {
		for (int j = 0; j < Chunk::width; ++j) {
			if (chunks[m]->visibleHeight[i + 1][j + 1] > sandheight) {
				if (PerlinNoise2D(chunks[m]->x * CHUNKWIDTH + i, chunks[m]->y * CHUNKWIDTH + j, 2, 1) > 0.47) {
					MapGenerator::makePalmTree(*chunks[m], i * j + m, i, j, chunks[m]->visibleHeight[i + 1][j + 1]);
				}
			}
			else if (chunks[m]->visibleHeight[i + 1][j + 1] > waterheight) {
				if (PerlinNoise2D(chunks[m]->x * CHUNKWIDTH + i, chunks[m]->y * CHUNKWIDTH + j, 2, 1) > 0.45) {
					MapGenerator::makeCactus(*chunks[m], i * j + m, i, j, chunks[m]->visibleHeight[i + 1][j + 1]);
				}
			}
		}
	}
}

void MapGenerator::makePalmTree(Chunk& chunk, int seed, int x, int y, int z)
{
	StructureBuilder builder;
	srand(seed + clock());
	int height = rand() % 6 + 4;//range 7-9
	for (int h = height + 1; h > height - 3 && h > 3; --h) {
		int diameter = rand() % 1 + 9 / h;//range 1 - 2
		for (int yLeaf = -diameter; yLeaf <= diameter; yLeaf++) {
			for (int xLeaf = -diameter; xLeaf <= diameter; xLeaf++) {
				if (xLeaf != x && yLeaf != y) {
					builder.addBlock(xLeaf + x, y + yLeaf, z + h, Block::Leaf);
				}
			}
		}
	}
	builder.addBlock(x, y, z + height + 1, Block::Leaf);
	builder.addBlock(x, y, z + height + 2, Block::Leaf);
	builder.addZ(z, z + height, x, y, Block::Bark);
	builder.build(chunk);
}

void MapGenerator::makeCactus(Chunk& chunk, int seed, int x, int y, int z)
{
	srand(seed);
	int choice = rand() % 6;
	if (choice > 4) {
		cactus2(chunk, seed, x, y, z);
	}
	else {
		cactus1(chunk, seed, x, y, z);
	}
}

void MapGenerator::cactus1(Chunk& chunk, int seed, int x, int y, int z)
{
	StructureBuilder builder;
	srand((unsigned)time(NULL) + seed);
	builder.addZ(z, z + rand() % 3 + 1, x, y, Block::Cactus);
	builder.build(chunk);
}

void MapGenerator::cactus2(Chunk& chunk, int seed, int x, int y, int z)
{
	StructureBuilder builder;
	srand((unsigned)time(NULL) + seed);
	int height = rand() % 3 + 5;//range 6 - 8
	builder.addZ(z, z + height, x, y, Block::Cactus);

	int stem = height / 2;
	builder.addX(x - 2, x + 2, y, z + height - 2, Block::Cactus);
	builder.addBlock(x, y + 1, z + height - 1, Block::Cactus);
	builder.addBlock(x, y - 1, z + height - 1, Block::Cactus);
	builder.build(chunk);
}