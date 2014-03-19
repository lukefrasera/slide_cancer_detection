#include "svsconvert.h"

svsconvert::svsconvert(openside_t * file){
	image = file;
}

svsconvert::~svsconvert(){
	iamge = NULL;
}

TIFF * svsconvert::tiff(){
	
}