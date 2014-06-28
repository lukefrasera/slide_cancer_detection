/*
 * segmentation.cpp
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
#include "./segmentation.h"
#include "stdio.h"
namespace tma {
TmaMaker::TmaMaker() {}
TmaMaker::~TmaMaker() {}
// Return a thresheld image mask signifying the tissue regions of a given iamge
cv::Mat TmaMaker::GetTissueRegionMask(const cv::Mat &image) {
  // Convert image from 8-bit-RGB to 8-bit-single-channel-luminance image
  cv::Mat lum_image;
  cv::cvtColor(image, lum_image, CV_RGB2GRAY);

  // Threshold image
  double max_val = 255;
  double thresh = 204;
  cv::Mat bin_mask;
  cv::threshold(lum_image, bin_mask, thresh, max_val, CV_THRESH_BINARY_INV);

  cv::Mat element;
  element = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(11, 11));
  // Erode image
  cv::erode(bin_mask, bin_mask, element);
  // Dilate image
  cv::dilate(bin_mask, bin_mask, element);

  return bin_mask;
}

cv::Mat TmaMaker::GetNormalizedHist(const cv::Mat &mask,
      const cv::Mat &image) {
  cv::Mat hsv;
  cv::cvtColor(image, hsv, CV_RGB2HSV);
  // Calculate histrogram
  int hbins = 30;
  int histsize[] = {hbins};
  float hrange[] = {0, 180};
  const float * ranges[] = {hrange};
  int channels[] = {0};
  cv::Mat hist;
  // std::vector< cv::Vec2i > hist;

  cv::calcHist(&hsv, 1, channels, mask, hist, 1, histsize, ranges, true, false);
  printf("made it here\n");
  // normalize histogram
  return hist;
}
};  // namespace tma
