#include "stdlib.h"
#include <stdio.h>
#include "openslide/openslide.h"

int main( int argc, char* argv[] ){

	const char * vendor = openslide_detect_vendor(argv[1]);
	printf("%s\n", vendor );

	openslide_t * image = openslide_open(argv[1]);
	int levels = openslide_get_level_count(image);
	printf("Levels: %d\n", levels);

	for(int i = 0; i < levels; i++){
		int64_t x, y;
		openslide_get_level_dimensions(image, i, &x, &y);
		printf("Dimensions: Width: %d , Height: %d\n", (int)x, (int)y );
	}

	// READ ACROSS ENTIRE IMAGE: THRESHOLDING FOR COLOR

	
	return 0;
}  