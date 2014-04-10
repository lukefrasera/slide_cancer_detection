#include "svsconvert.h"


#define TIFF_TILE_SIZE 2048
#define SVS_LEVEL 3
#define BITSPERSAMPLE 8

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
	TIFF * file, * slide;
	uint32_t * buf;

	// DETERMINE THE NUMBER OF TILES
	unsigned int NUM_TILES_WIDTH	= header.levels[SVS_LEVEL].w / TIFF_TILE_SIZE + (header.levels[SVS_LEVEL].w % 2);
	unsigned int NUM_TILES_HEIGHT	= header.levels[SVS_LEVEL].h / TIFF_TILE_SIZE + (header.levels[SVS_LEVEL].h % 2);
	unsigned int NUM_TILES 			= NUM_TILES_WIDTH * NUM_TILES_HEIGHT;
	unsigned int TILE_SIZE_WIDTH, TILE_SIZE_HEIGHT;

	file = TIFFOpen(filename, "w");
	if(slide = TIFFOpen("../CMU-2.svs", "r")) {
		printf("%s\n", "it opened");
	}


	if( !file )
		return NULL;
	printf("Number of Tiles: %d\n", NUM_TILES);
	
	// SET UP IMAGE HEADER
	TIFFSetField(file, TIFFTAG_IMAGEWIDTH, header.levels[SVS_LEVEL].w);
	TIFFSetField(file, TIFFTAG_IMAGELENGTH, header.levels[SVS_LEVEL].h);
	TIFFSetField(file, TIFFTAG_TILEWIDTH, TIFF_TILE_SIZE);
	TIFFSetField(file, TIFFTAG_TILELENGTH, TIFF_TILE_SIZE);
	TIFFSetField(file, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
	TIFFSetField(file, TIFFTAG_BITSPERSAMPLE, BITSPERSAMPLE);
	TIFFSetField(file, TIFFTAG_SAMPLESPERPIXEL, 4);
	TIFFSetField(file, TIFFTAG_COMPRESSION, COMPRESSION_LZW);
	TIFFSetField(file, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
	TIFFSetField(file, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
	TIFFSetField(file, TIFFTAG_SOFTWARE, TIFFGetVersion());

	buf = (uint32_t*)_TIFFmalloc(sizeof(uint32_t)*TIFF_TILE_SIZE*TIFF_TILE_SIZE);

	for( unsigned int j = 0; j < header.levels[SVS_LEVEL].h; j += TIFF_TILE_SIZE){
		for( unsigned int i = 0; i < header.levels[SVS_LEVEL].w; i += TIFF_TILE_SIZE){
			// NEED TO HANDLE THE EDGE SITUATION: MUST ONLY READ UP UNTIL THE LIMIT IN IMAGE.W && IMAGE.H
			TILE_SIZE_WIDTH  = (header.levels[SVS_LEVEL].w - i > TIFF_TILE_SIZE) ? (TIFF_TILE_SIZE) : (header.levels[SVS_LEVEL].w - i);
			TILE_SIZE_HEIGHT = (header.levels[SVS_LEVEL].h - j > TIFF_TILE_SIZE) ? (TIFF_TILE_SIZE) : (header.levels[SVS_LEVEL].h - j);

			// openslide_read_region(image, buf, i, j, SVS_LEVEL, TILE_SIZE_WIDTH, TILE_SIZE_HEIGHT);
			openslide_read_region(image, buf, i, j, SVS_LEVEL, TIFF_TILE_SIZE, TIFF_TILE_SIZE);

			// for ( int k = 0; k < TIFF_TILE_SIZE * TIFF_TILE_SIZE; k++) {
			// 	printf("Red  :%d\t", (unsigned char)(buf[k] >> 0));
			// 	printf("Green:%d\t", (unsigned char)(buf[k] >> 8));
			// 	printf("Blue :%d\t", (unsigned char)(buf[k] >> 16));
			// 	printf("Aplha:%d\n", (unsigned char)(buf[k] >> 24));
			// }
			// printf("Tile ONE Complete\n");
			// COPY BUFFER TO INTO TIFF TILE
			// printf("Tile Number: %d\n", (j / TIFF_TILE_SIZE * NUM_TILES_WIDTH) + (i / TIFF_TILE_SIZE));

			// TIFFWriteEncodedTile(file, (j / TIFF_TILE_SIZE * NUM_TILES_WIDTH) + (i / TIFF_TILE_SIZE), (tdata_t)buf, sizeof(uint32_t)*TIFF_TILE_SIZE*TIFF_TILE_SIZE);
			TIFFWriteEncodedTile(file, TIFFComputeTile(file, i, j, 0, 0), (tdata_t)buf, sizeof(uint32_t)*TIFF_TILE_SIZE*TIFF_TILE_SIZE);
		}
	}
	// delete [] svsbuf;
	_TIFFfree(buf);
	TIFFClose(file);

	return NULL;
}