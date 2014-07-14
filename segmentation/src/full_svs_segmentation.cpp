/*
 * full_svs_segmentation.cpp
 *    Copyright (C) 2014 Luke Fraser
 *
 *    This file is part of TMAker.
 *
 *    TMAker is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    TMAker is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with TMAker.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "stdlib.h"
#include <stdio.h>
#include "openslide/openslide.h"
#include "opencv2/opencv.hpp"
#include "segmentation.h"
#include <vector>

int main( int argc, char* argv[] ) {
	// READ ACROSS ENTIRE IMAGE: THRESHOLDING FOR COLOR
  tma::TmaMaker maker;

  cv::Mat image = cv::imread(argv[1]);
  cv::Mat mask = maker.GetTissueRegionMask(image);
  std::vector<float> hist = maker.GetNormalizedHist(mask, image);
  // std::vector<float> smoothed = maker.GetSmoothHist(hist);
  int groups = maker.GetNumColorGroups(hist);

  // for (int i = 0; i < hist.size(); ++i) {
  //   printf("Original: %f\n", hist[i]);
  // }
  printf("Groups: %d\n", groups);
  // std::vector<int> compression_param;
  // compression_param.push_back(CV_IMWRITE_JPEG_QUALITY);
  // compression_param.push_back(95);
  // cv::imwrite("test.jpeg", image, compression_param);
	// EDGE DETECTION
	return 0;
}  
