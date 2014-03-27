#include "svsconvert.h"


#define TIFF_TILE_SIZE 1024

svsconvert::svsconvert( const char * filename){
	image = openslide_open(filename);
	if(!image){
		printf("%s\n", openslide_get_error(image));
	}
	
	// GET IMAGE HEADER INFROMATION

	// GET LEVEL COUNT
	header.level_count = openslide_get_level_count( image );
	header.levels = new openslide_level[header.level_count];

	for (uint32 i = 0; i < header.level_count; ++i){
		openslide_level & r = header.levels[i];

		openslide_get_level_dimensions( image, i, &r.w, &r.h );
		r.downsample = openslide_get_level_downsample( image, i );
	}
}

svsconvert::~svsconvert(){
	openslide_close(image);
}

TIFF * svsconvert::tiff(const char * filename){
	TIFF * file;
	uint32_t * svsbuf;

	// DETERMINE THE NUMBER OF TILES
	unsigned int NUM_TILES = header.levels->w / TIFF_TILE_SIZE + (header.levels->w % 2);
	NUM_TILES *= header.levels->h / TIFF_TILE_SIZE + (header.levels->w % 2);
	unsigned int TILE_SIZE_WIDTH, TILE_SIZE_HEIGHT;

	printf("Number of Tiles: %d\n", NUM_TILES);
	

	svsbuf = new uint32_t[TIFF_TILE_SIZE * TIFF_TILE_SIZE];
	for( unsigned int i = 0; i < header.levels[0].w; i += TIFF_TILE_SIZE){
		for( unsigned int j = 0; j < header.levels[0].h; j += TIFF_TILE_SIZE){
			// NEED TO HANDLE THE EDGE SITUATION: MUST ONLY READ UP UNTIL THE LIMIT IN IMAGE.W && IMAGE.H
			TILE_SIZE_WIDTH  = (header.levels[0].w - i > TIFF_TILE_SIZE) ? (TIFF_TILE_SIZE) : (header.levels[0].w - i);
			TILE_SIZE_HEIGHT = (header.levels[0].h - j > TIFF_TILE_SIZE) ? (TIFF_TILE_SIZE) : (header.levels[0].h - j);

			openslide_read_region(image, svsbuf, i, j, 0, TILE_SIZE_WIDTH, TILE_SIZE_HEIGHT);

			// COPY BUFFER TO INTO TIFF TILE


		}
	}
	delete [] svsbuf;
			printf("Tile Width : %d ", TILE_SIZE_WIDTH);
			printf("Tile Height: %d\n", TILE_SIZE_HEIGHT);

	printf("Out of Four loops\n");

	return NULL;
}