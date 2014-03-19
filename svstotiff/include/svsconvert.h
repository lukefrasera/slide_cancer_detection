#ifndef SVS_CONVERT_HEADER
#define SVS_CONVERT_HEADER
#include "openslide.h"
#include "tiffio.h"

class svsconvert
{
public:
	svsconvert(openslide_t*);
	~svsconvert();

	// CONVERSION TYPES
	TIFF * tiff();
private:
	openslide_t * image;
};
#endif