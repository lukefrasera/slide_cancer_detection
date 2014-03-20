#include "svsconvert.h"

svsconvert::svsconvert( const char * filename){
	image = openslide_open(filename);
	if(!image){
		printf("%s\n", openslide_get_error(image));
	}
	
	// GET IMAGE HEADER INFROMATION

	// GET LEVEL COUNT
	header.level_count = openslide_get_level_count( image );

	for (uint32 i = 0; i < header.level_count; ++i){
		openslide_level & r = header.levels[i];

		openslide_get_level_dimensions( image, i, &r.w, &r.h );
		r.downsample = openslide_get_level_downsample( image, i );
	}

}

svsconvert::~svsconvert(){
	openslide_close(image);
}

TIFF * svsconvert::tiff(){
	
}