#ifndef BACKGROUND_H
#define BACKGROUND_H

#define TILE_SIZE_WIDTH 32
#define TILE_SIZE_HEIGHT 32
#define IMAGE_AREA_WIDTH 500
#define IMAGE_AREA_HEIGHT 500
#define MAP_CLOSED 1
#define MAP_OPEN 2
#define MAP_NONE 0

#include "utils\config.h"
#include <vector>
#include "rendering\CRenderer.h"

struct ImageDetails {
	char *name;
	unsigned width, height;
};

typedef std::map<unsigned, ImageDetails> ImageIdMap;
typedef ImageIdMap::iterator ImageIdMapIter;

class Background  
{
private:
	struct Area {
		unsigned int top_x;
		unsigned int top_y;
		unsigned int bottom_x;
		unsigned int bottom_y;
	};
	ImageIdMap *mappings;
	static Background *instance;
	char *imageName, *rootDir;
	unsigned imageWidth, imageHeight, lastx, lasty, dim_x, dim_y, dim,
		nrImageAreasX, nrImageAreasY;
	unsigned *walkMap;
	std::vector<unsigned> cost_f;
	Background();
	~Background();
	void ReadMappings(const char *);
	ImageDetails *FindImageById(unsigned);
	unsigned PixelToTileY(unsigned y) { return y / TILE_SIZE_HEIGHT; }
	unsigned PixelToTileX(unsigned x) { return x / TILE_SIZE_WIDTH; }
	unsigned int GetImageAreaNr(unsigned int x, unsigned int y)
		{ return nrImageAreasX * (y - 1) + (x - 1); }
	void RenderArea(unsigned int, unsigned int, unsigned int, unsigned int,
		unsigned int, unsigned int);
	unsigned TileToPixelX(unsigned x) { return x * TILE_SIZE_WIDTH + TILE_SIZE_WIDTH / 2; }
	unsigned TileToPixelY(unsigned y) { return y * TILE_SIZE_HEIGHT + TILE_SIZE_WIDTH / 2; }
	bool IsMapWalkable(unsigned index) {
		return (*(walkMap + index / sizeof(unsigned))) >> (index % sizeof(unsigned)) & 1;
	}
	static bool HeapCompare(unsigned x, unsigned y) {
		return Background::GetInstance()->cost_f[x] > Background::GetInstance()->cost_f[y];
	}
	void ReadWalkMap(const char *);
public:
	static Background *GetInstance() {
		if (instance == NULL) instance = new Background();
		return instance;
	}
	void LoadBackground(unsigned);
	void Render(unsigned int, unsigned int);
	static void Close() { delete instance; }
	unsigned GetWidth() { return imageWidth; }
	unsigned GetHeight() { return imageHeight; }
	unsigned *FindPath(unsigned, unsigned, unsigned, unsigned, unsigned *);
	unsigned TileNumber(unsigned tx, unsigned ty) {
		return tx + ty * dim_x;
	}
	unsigned MapXToScreenX(unsigned x) { return x; }
	unsigned MapYToScreenZ(unsigned y) { return y; }
	bool IsVisible(unsigned px, unsigned py) {
		return (abs(px - lastx) <= SCREEN_WIDTH && abs(py - lasty) <= SCREEN_HEIGHT) ? true : false;
	}
};

#endif