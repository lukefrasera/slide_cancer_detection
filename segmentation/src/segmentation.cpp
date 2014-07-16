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
#include <stdio.h>
#include <vector>
#include "./sgsmooth.h"

namespace tma {
TmaMaker::TmaMaker() {
  cv::Mat image = NULL;
}
TmaMaker::~TmaMaker() {}

void TmaMaker::Init(const cv::Mat &image) {
  image_ = image;
}
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

std::vector<float> TmaMaker::GetNormalizedHist(const cv::Mat &mask,
      const cv::Mat &image) {
  cv::Mat hsv;
  cv::cvtColor(image, hsv, CV_RGB2HSV);
  // Calculate histrogram
  int hbins = 60;
  int histsize[] = {hbins};
  float hrange[] = {0, 180};
  const float * ranges[] = {hrange};
  int channels[] = {0};
  cv::Mat hist;
  cv::calcHist(&hsv, 1, channels, mask, hist, 1, histsize, ranges, true, false);

  // convert hist to vectors
  const float * h1 = hist.ptr<float>(0);
  std::vector<float> vec_hist(h1, h1 + hist.rows);

  // normalize histogram
  int sum = 0;
  for (int i = 0; i < vec_hist.size(); ++i) {
    sum += vec_hist[i];
  }
  for (int i = 0; i < vec_hist.size(); ++i) {
    vec_hist[i] = vec_hist[i]/sum;
  }

  return vec_hist;
}

std::vector<float> TmaMaker::GetSmoothHist(const std::vector<float> &data) {
  // Pass data to smoothing filter
  int size = data.size();
  double *d_ptr = NULL;
  std::vector<float> result;
  d_ptr = new double[size];
  if (d_ptr) {
    for (int i = 0; i < size; ++i) {
      d_ptr[i] = data[i];
    }
    double * smooth_data = calc_sgsmooth(size, d_ptr, 20, 5);
    delete [] d_ptr;

    // Normalize smoothed data
    float sum = 0;
    for (int i = 0; i < size; ++i) {
      sum += smooth_data[i];
    }
    for (int i = 0; i < size; ++i) {
      result.push_back(smooth_data[i]/sum);
    }
  }
  return result;
}

int TmaMaker::GetNumColorGroups(const std::vector<float> &data) {
  // Find local maxima
  std::vector<int> maxima = FindLocalMaxima(data);
  // threshold above certain value
  int sum = 0;
  float thresh = .001;
  for (int i = 0; i < maxima.size(); ++i) {
    if (data[maxima[i]] > thresh)
      sum++;
    printf("Maxima: %f\n", data[maxima[i]]);
  }
  return sum;
}

std::vector<cv::Mat> SegmentImageKMeans(const cv::Mat & image, int iterations) {
  
}

std::vector<int> TmaMaker::FindLocalMaxima(const std::vector<float> &data) {
  // Find the first derivative of he data
  // std::vector<float> deriv = CentralDifference(data);
  std::vector<float> deriv = SgsDerivative(data);
  // Find positive to negative zero crossings
  std::vector<int> result;
  for (int i = 0; i < deriv.size()-1; ++i) {
    if (deriv[i] >= 0 && deriv[i+1] < 0)
      result.push_back(i);
  }
  return result;
}

std::vector<float> TmaMaker::CentralDifference(const std::vector<float> &data) {
  // perform central difference
  std::vector<float> result;
  // Handle Frst boundry condition
  result.push_back(data[1]-data[0]);
  for (int i = 1; i < data.size()-1; ++i) {
    result.push_back((data[i+1] - data[i-1])/2);
  }
  // Handle past boundry conditions
  result.push_back(data[data.size()-1] - data[data.size()-2]);
  return result;
}

std::vector<float> TmaMaker::SgsDerivative(const std::vector<float> &data) {
  int size = data.size();
  double * d_ptr = NULL;
  std::vector<float> result;
  d_ptr = new double[size];
  if (d_ptr) {
    for (int i = 0; i < size; ++i) {
      d_ptr[i] = data[i];
    }
    double * deriv = calc_sgsderiv(size, d_ptr, 9, 8, 1);
    if (deriv) {
      for (int i = 0; i < size; ++i) {
        result.push_back(deriv[i]);
      }
    }
  }
  return result;
}

void TmaMaker::CellImageSegmentation() {
  // Find region mask
  // Get normalized histogram
  // smooth histrogram
  // store segmented regions
}
};  // namespace tma
