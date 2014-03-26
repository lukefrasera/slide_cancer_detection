#ifndef SVS_CONVERT_HEADER
#define SVS_CONVERT_HEADER
#include "openslide.h"
#include "tiffio.h"

typedef struct svslevel
{
	int64 w,h;
	double downsample;
}openslide_level;

typedef struct svsHeader
{
	int32 level_count;
	openslide_level * levels;
} openslide_header;

class svsconvert
{
public:
	svsconvert(const char *);
	~svsconvert();

	// CONVERSION TYPES
	TIFF * tiff(const char *);
private:
	openslide_t * image;
	openslide_header header;
};
#endif