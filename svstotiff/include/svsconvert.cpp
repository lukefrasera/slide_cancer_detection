#include "svsconvert.h"


#define TIFF_TILE_SIZE 128

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

	printf("Number of Tiles: %d\n", NUM_TILES);
	

	for( unsigned int i = 0; i < header.levels[0].w; i += TIFF_TILE_SIZE){
		for( unsigned int j = 0; j < header.levels[0].h; j += TIFF_TILE_SIZE){
			openslide_read_region(image, svsbuf, i, j, 0, TIFF_TILE_SIZE, TIFF_TILE_SIZE);
		}
	}
	return NULL;
}