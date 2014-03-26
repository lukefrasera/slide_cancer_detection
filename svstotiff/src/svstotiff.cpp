#include "svsconvert.h"

int main(int argc, char const *argv[])
{
	
	svsconvert * svs_image_object;

	if( argc < 2 ){
		return -1;
	}

	svs_image_object = new svsconvert(argv[1]);

	TIFF * image = svs_image_object->tiff("test.tiff");

	return 0;
}