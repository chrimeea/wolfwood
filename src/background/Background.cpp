#pragma warning(disable : 4786)

#include <stdio.h>
#include <malloc.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "background\Background.h"
#include "background\CImageAreaBufferPool.h"

Background *Background::instance = NULL;

Background::Background() {
	char *mf = Config::GetValue("config/background/file");
	mappings = new ImageIdMap();
	if (mf) {
		ReadMappings(mf);
	}
	mf = Config::GetValue("config/background/dir");
	if (mf) {
		rootDir = (char *) malloc(strlen(mf) + 1);
		strcpy(rootDir, mf);
	}
	imageName = NULL;
	imageWidth = imageHeight = dim_x = dim_y = nrImageAreasX = nrImageAreasY = 0;
	lastx = -SCREEN_WIDTH - 1;
	lasty = -SCREEN_HEIGHT - 1;
	walkMap = NULL;
	CImageAreaBufferPool::getInstance();
}

Background::~Background() {
	CImageAreaBufferPool::Close();
	if(imageName) free(imageName);
	if(walkMap) free(walkMap);
	if(mappings) delete mappings;
	if(rootDir) free(rootDir);
}

void Background::LoadBackground(unsigned imageId) {
	if (imageName) free(imageName);
	ImageDetails *i = FindImageById(imageId);
	imageName = (char *) malloc(strlen(i->name) + 1);
	strcpy(imageName, i->name);
	imageWidth = i->width;
	imageHeight = i->height;
	nrImageAreasX = (imageWidth - 1) / IMAGE_AREA_WIDTH + 1;
	nrImageAreasY = (imageHeight - 1) / IMAGE_AREA_HEIGHT + 1;
	dim_x = imageWidth / TILE_SIZE_WIDTH;
	dim_y = imageHeight / TILE_SIZE_HEIGHT;
	dim = dim_x * dim_y;
	if (walkMap) free (walkMap);
	walkMap = (unsigned *) malloc(((dim - 1) / (sizeof(unsigned) * 8) + 1) * sizeof(unsigned));
	char *wf = (char *) malloc(strlen(imageName) + strlen(rootDir) + 5);
	sprintf(wf, "%s%s.wlk", rootDir, imageName);
	ReadWalkMap(wf);
	free(wf);
}

void Background::RenderArea(unsigned int px, unsigned int py, unsigned int scr_w,
							unsigned int scr_h, unsigned int posx, unsigned int posy)
{
	unsigned int x1, y1, x2, y2, cx, cy = py;
	Area area;
	ImageAreaData *imageAreaData;
	x1 = px / IMAGE_AREA_WIDTH + 1;
	y1 = py / IMAGE_AREA_HEIGHT + 1;
	x2 = (px + scr_w - 1) / IMAGE_AREA_WIDTH + 1;
	y2 = (py + scr_h - 1) / IMAGE_AREA_HEIGHT + 1;
	char filename[50];
	for(int i = y1; i <= y2; i++)
	{
		cx = px;
		for(int j = x1; j <= x2; j++)
		{
			sprintf(filename,"%s%s_%02u", rootDir, imageName, GetImageAreaNr(j, i));
			imageAreaData = (ImageAreaData *)(CImageAreaBufferPool::getInstance()->getBuffer(filename)->data);
			area.top_x = cx;
			area.top_y = cy;
			area.bottom_x = (IMAGE_AREA_WIDTH * j < scr_w + px ? IMAGE_AREA_WIDTH * j - 1 : px + scr_w - 1);
			area.bottom_y = (IMAGE_AREA_HEIGHT * i < scr_h + py ? IMAGE_AREA_HEIGHT * i - 1: py + scr_h - 1);
			CRenderer::GetInstance()->DrawArea(
				posx + area.top_x - px,
				posy + area.bottom_y - py + 1,
				area.bottom_x - area.top_x + 1,
				area.bottom_y - area.top_y + 1,
				area.top_x - IMAGE_AREA_WIDTH * (j - 1),
				(IMAGE_AREA_HEIGHT * i > imageHeight ? imageHeight - area.bottom_y - 1:
					IMAGE_AREA_HEIGHT * i - area.bottom_y - 1),
				(IMAGE_AREA_WIDTH * j > imageWidth ? imageWidth - IMAGE_AREA_WIDTH * (j - 1) : IMAGE_AREA_WIDTH),
				imageAreaData->imgareapx, imageAreaData->zimgareapx);
			cx = area.bottom_x + 1;
			CImageAreaBufferPool::getInstance()->closeBuffer(filename);
		}
		cy = i * IMAGE_AREA_HEIGHT;
	}
}

void Background::Render(unsigned int px, unsigned int py)
{
	if(!IsVisible(px, py) || (px == lastx && py == lasty))
	{
		RenderArea(px, py, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
	}
	else
	{
		int dx = px - lastx, dy = py - lasty;
		// common_area este aria comuna deplasarii ecranului, cu coordonatele 
		// relative la ecranul dinaintea deplasarii.
		Area common_area, new_area;
		common_area.top_x = (dx > 0 ? dx : 0);
		common_area.top_y = (dy > 0 ? dy : 0);
		common_area.bottom_x = (dx > 0 ? SCREEN_WIDTH - 1 : SCREEN_WIDTH + dx - 1);
		common_area.bottom_y = (dy > 0 ? SCREEN_HEIGHT - 1 : SCREEN_HEIGHT + dy - 1);
		CRenderer::GetInstance()->ScrollArea(
			common_area.top_x,
			SCREEN_HEIGHT - common_area.bottom_y - 1,
			common_area.bottom_x - common_area.top_x + 1,
			common_area.bottom_y - common_area.top_y + 1,
			common_area.top_x - dx,
			common_area.bottom_y - dy + 1);
		if(dx != 0)
		{
			// Definim dreptunghiul ramas pe axa X
			new_area.top_x = (dx > 0 ? px + SCREEN_WIDTH - dx : px);
			new_area.top_y = (dy > 0 ? py : py - dy);
			new_area.bottom_x = (dx > 0 ? px + SCREEN_WIDTH - 1 : px - dx - 1);
			new_area.bottom_y = (dy > 0 ? py + SCREEN_HEIGHT - dy - 1 : py + SCREEN_HEIGHT - 1);
			RenderArea(
				new_area.top_x,
				new_area.top_y,
				abs(dx),
				new_area.bottom_y - new_area.top_y + 1,
				new_area.top_x - px,
				new_area.top_y - py);
			if(dy != 0)
			{
				// Definim dreptunghiul din colt
				new_area.top_x = (dx > 0 ? px + SCREEN_WIDTH - dx : px);
				new_area.top_y = (dy > 0 ? py + SCREEN_HEIGHT - dy : py);
				new_area.bottom_x = (dx > 0 ? px + SCREEN_WIDTH - 1 : px - dx - 1);
				new_area.bottom_y = (dy > 0 ? py + SCREEN_HEIGHT - 1 : py - dy - 1);
				RenderArea(
					new_area.top_x,
					new_area.top_y,
					abs(dx),
					abs(dy),
					new_area.top_x - px,
					new_area.top_y - py);
			}
		}
		if (dy != 0)
		{
			// Definim dreptunghiul ramas pe axa Y
			new_area.top_x = (dx > 0 ? px : px - dx);
			new_area.top_y = (dy > 0 ? py + SCREEN_HEIGHT - dy : py);
			new_area.bottom_x = (dx > 0 ? px + SCREEN_WIDTH - dx - 1 : px + SCREEN_WIDTH - 1);
			new_area.bottom_y = (dy > 0 ? py + SCREEN_HEIGHT - 1 : py - dy - 1);
			RenderArea(
				new_area.top_x,
				new_area.top_y,
				new_area.bottom_x - new_area.top_x + 1,
				abs(dy),
				new_area.top_x - px,
				new_area.top_y - py);
		}
	}
	lastx = px;
	lasty = py;
}

void Background::ReadMappings(const char *f)
{
	char strname[50];
	unsigned id, w, h;
	std::ifstream ifs(f);
	while(!ifs.eof())
	{
		ifs >> id >> strname >> w >> h;
		ImageDetails *i = (ImageDetails *) malloc(sizeof(ImageDetails));
		i->name = (char *) malloc(strlen(strname));
		strcpy(i->name, strname);
		i->width = w;
		i->height = h;
		mappings->insert(ImageIdMap::value_type(id, *i));
	}
}

ImageDetails *Background::FindImageById(unsigned id) {
	ImageIdMapIter iter;
	if((iter = mappings->find(id)) != mappings->end()) return &((*iter).second);
	return NULL;
}

void Background::ReadWalkMap(const char *f) {
	unsigned k = 0;
	std::ifstream ifs(f);
	char *w = (char *) walkMap;
	while (ifs) {
		ifs.read(w, 1024);
		w += ifs.gcount();
	}
	ifs.close();
}

unsigned *Background::FindPath(unsigned startPosX,
						       unsigned startPosY,
							   unsigned endPosX,
							   unsigned endPosY,
							   unsigned *path_length)
{
  unsigned start_x = PixelToTileX(startPosX);
  unsigned start_y = PixelToTileY(startPosY);
  unsigned end_x = PixelToTileX(endPosX);
  unsigned end_y = PixelToTileY(endPosY);
  unsigned *path;
  if (start_x == end_x && start_y == end_y)
  {
    path = (unsigned *) malloc(2 * sizeof(unsigned));
    *path = TileToPixelX(start_x);
    *(path + 1) = TileToPixelY(start_y);
    *path_length = 1;
    return path;
  }
  *path_length = 0;
  if (!IsMapWalkable(end_y * dim_x + end_x)) {
	  return NULL;
  }
  int a, b;
  unsigned pos, open_list_count, last_open = 0, par_x_val, par_y_val, path_x, path_y, k;
  unsigned *parent_x, *parent_y;
  unsigned *cost_g, *which_list;
  std::vector<unsigned> open_x(1);
  std::vector<unsigned> open_y(1);
  parent_x = (unsigned *) malloc(dim * sizeof(unsigned));
  parent_y = (unsigned *) malloc(dim * sizeof(unsigned));
  cost_g = (unsigned *) malloc(dim * sizeof(unsigned));
  std::vector<unsigned> cost_h;
  open_list_count = 1;
  std::vector<unsigned> open_list(1);
  which_list = (unsigned *) malloc(dim * sizeof(unsigned));
  pos = start_y * dim_x + start_x;
  cost_g[pos] = 0;
  open_list[0] = 0;
  open_x[0] = start_x;
  open_y[0] = start_y;
  cost_f.push_back(0);
  cost_h.push_back(0);
  memset(which_list, MAP_NONE, dim * sizeof(unsigned));
  do
  {
    if (open_list_count > 0)
    {
      par_x_val = open_x[open_list[0]];
      par_y_val = open_y[open_list[0]];
      which_list[par_y_val * dim_x + par_x_val] = MAP_CLOSED;
      open_list_count--;
	  std::pop_heap(open_list.begin(), open_list.end(), this->HeapCompare);
	  open_list.pop_back();
      for (b = (int) par_y_val - 1; b <= (int) par_y_val + 1; b++)
      {
        for (a = (int) par_x_val - 1; a <= (int) par_x_val + 1; a++)
        {
          if (a != -1 && b != -1 && a != (int) dim_x && b != (int) dim_y)
          {
            pos = b * dim_x + a;
            if (which_list[pos] != MAP_CLOSED)
            {
              if (IsMapWalkable(pos))
              {
                bool cornerWalkable = true;
                if (a == (int) par_x_val - 1) 
                {
                  if (b == (int) par_y_val - 1)
                  {
                    if (!IsMapWalkable(par_y_val * dim_x + par_x_val - 1) || !IsMapWalkable((par_y_val - 1) * dim_x + par_x_val))
                      cornerWalkable = false;
                  }
                  else if (b == (int) par_y_val + 1)
                  {
                    if (!IsMapWalkable((par_y_val + 1) * dim_x + par_x_val) || !IsMapWalkable(par_y_val * dim_x + par_x_val - 1))
                      cornerWalkable = false; 
                  }
                }
                else if (a == (int) par_x_val + 1)
                {
                  if (b == (int) par_y_val - 1)
                  {
                    if (!IsMapWalkable((par_y_val - 1) * dim_x + par_x_val) || !IsMapWalkable(par_y_val * dim_x + par_x_val + 1))
                      cornerWalkable = false;
                  }
                  else if (b == (int) par_y_val + 1)
                  {
                    if (!IsMapWalkable(par_y_val * dim_x + par_x_val + 1) || !IsMapWalkable((par_y_val + 1) * dim_x + par_x_val))
                      cornerWalkable = false;
                  }
                }
                if (cornerWalkable)
                {
                  if (which_list[pos] != MAP_OPEN)
                  {
                    unsigned added_cost_g = 0;
                    open_list.push_back(++last_open);
                    open_x.push_back(a);
                    open_y.push_back(b);
                    if (abs(a - par_x_val) == 1 && abs(b - par_y_val) == 1) added_cost_g = 14;
                    else added_cost_g = 10;
                    cost_g[pos] = cost_g[par_y_val * dim_x + par_x_val] + added_cost_g;
                    cost_h.push_back(10 * (abs(a - end_x) + abs(b - end_y)));
                    cost_f.push_back(cost_g[pos] + cost_h[open_list[open_list_count]]);
                    parent_x[pos] = par_x_val;
                    parent_y[pos] = par_y_val;
					std::push_heap(open_list.begin(), open_list.end(), this->HeapCompare);
                    open_list_count++;
                    which_list[pos] = MAP_OPEN;
                  }
                  else
                  {
                    unsigned temp_cost_g, added_cost_g;
                    if (abs(a - par_x_val) == 1 && abs(b - par_y_val) == 1) added_cost_g = 14;
                    else added_cost_g = 10;
                    temp_cost_g = cost_g[par_y_val * dim_x + par_x_val] + added_cost_g;
                    if (temp_cost_g < cost_g[pos])
                    {
                      parent_x[pos] = par_x_val;
                      parent_y[pos] = par_y_val;
                      cost_g[pos] = temp_cost_g;
					  for (std::vector<unsigned>::iterator x = open_list.begin(); x < open_list.end(); x++) {
						if ((int) open_x[*x] == a && (int) open_y[*x] == b) {
						  cost_f[*x] = cost_g[pos] + cost_h[*x];
						  std::push_heap(open_list.begin(), x, this->HeapCompare);
						  break;
						}
					  }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    else {
		free(parent_x);free(parent_y);
		free(cost_g);free(which_list);
		return NULL;
	}
    if (which_list[end_y * dim_x + end_x] == MAP_OPEN) break;
  }
  while(1);
  path_x = end_x;
  path_y = end_y;
  do
  {
    pos = path_y * dim_x + path_x;
    path_x = parent_x[pos];
    path_y = parent_y[pos];
    *path_length = *path_length + 1;
  }
  while (path_x != start_x || path_y != start_y);
  path = (unsigned *) malloc(*path_length * 2 * sizeof(unsigned));
  path_x = end_x;
  path_y = end_y;
  k = (*path_length - 1) * 2;
  path[k] = endPosX;
  path[k + 1] = endPosY;
  pos = path_y * dim_x + path_x;
  path_x = parent_x[pos];		
  path_y = parent_y[pos];
  while (path_x != start_x || path_y != start_y)
  {
    k -= 2;
    path[k] = TileToPixelX(path_x);
    path[k + 1] = TileToPixelY(path_y);
    pos = path_y * dim_x + path_x;
    path_x = parent_x[pos];		
    path_y = parent_y[pos];
  }
  free(parent_x);free(parent_y);
  free(cost_g);free(which_list);
  return path;
}
