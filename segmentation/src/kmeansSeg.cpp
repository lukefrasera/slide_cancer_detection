  /*
 * histogramSmoothSegmentation.cpp
 *    Copyright (C) 2014 Luke Fraser
 *
 *    This file is part of TMAker.
 *
 *    TMAker is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published 
 *    by the Free Software Foundation, either version 3 of the License, or
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
#include "segmentation.h"
#include "opencv2/opencv.hpp"
#include <vector>
#include <string>
#include <cstdio>

int main(int argc, char const *argv[]) {
  tma::TmaMaker maker;
  std::string output_dir = argv[2];
  std::string input_dir = argv[1];
  cv::Mat image = cv::imread(argv[1]);
  std::vector<cv::Mat> regions = maker.KmeansSegmentation(image);
  for (int i = 0; i < regions.size(); ++i) { 
    char buffer[3];
    std::sprintf(buffer, "%d",i);
    std::string value = buffer;
    std::string filename = output_dir + "Region_" + value + "_" + input_dir.substr(input_dir.find_last_of("\\/") + 1);
    printf("%s\n", filename.c_str());
    cv::imwrite(filename.c_str(), regions[i]);
  }
  return 0;
}