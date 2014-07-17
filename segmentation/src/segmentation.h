  /*
 * segmentation.h
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

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#ifndef SEGMENTATION_SRC_SEGMENTATION_H_
#define SEGMENTATION_SRC_SEGMENTATION_H_

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

#include <vector>
#include "opencv2/opencv.hpp"

namespace tma{
class TmaMaker {
 public:
  TmaMaker();
  ~TmaMaker();
  
  void Init(const cv::Mat &image);
  cv::Mat GetTissueRegionMask(const cv::Mat &image);
  std::vector<float> GetNormalizedHist(const cv::Mat &mask,
      const cv::Mat &image);
  std::vector<float> GetSmoothHist(const std::vector<float> &data);
  int GetNumColorGroups(const std::vector<float> &data);
  void CellImageSegmentation();
  std::vector<cv::Mat> HistogramSegmentation(const cv::Mat &image);
  std::vector<cv::Mat> SmoothedHistogramSegmentation();
  std::vector<cv::Mat> KmeansSegmentation();

 private:
  std::vector<float> CentralDifference(const std::vector<float> &data);
  std::vector<float> SgsDerivative(const std::vector<float> &data);
  std::vector<int> FindLocalMaxima(const std::vector<float> &data);
  
  cv::Mat image_;

  DISALLOW_COPY_AND_ASSIGN(TmaMaker);
};
};  // namespace tma
#endif  // SEGMENTATION_SRC_SEGMENTATION_H_
