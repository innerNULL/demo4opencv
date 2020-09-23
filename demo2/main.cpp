// 2020-09-20



#include <iostream>
#include <string>
#include <sstream>

#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp" 




const std::string DEMO_NAME = "demo2";


void apply_filters(cv::Mat* input_data, std::string target_filter) {
  cv::Mat result;
  input_data->copyTo(result);

  if (target_filter == "blur") {
    cv::blur(result, result, cv::Size(15, 15));  
  } else if (target_filter == "convert2gray") {
    cv::cvtColor(result, result, cv::COLOR_BGR2GRAY);
  } else if (target_filter == "convert2rgb") {
  } else if (target_filter == "sobel") {
    cv::Sobel(result, result, CV_8U, 1, 1);
  }

  cv::imshow(DEMO_NAME, result);
  return;
}


void blur_callback(int state, void* input_data) {
  apply_filters((cv::Mat*)input_data, "blur");
  return;
}


void gray_callback(int state, void* input_data) {
  apply_filters((cv::Mat*)input_data, "convert2gray");
  return;
}


void rgb_callback(int state, void* input_data) {
  apply_filters((cv::Mat*)input_data, "convert2rgb");
  return;
}


void sobel_callback(int state, void* input_data) {
  apply_filters((cv::Mat*)input_data, "sobel");
  return;
}


int main(int argc, char *argv[]) {
  int32_t blur_amount = 15;
  std::string target_img_path = "../../demo_imgs/demo_img1.jpg";

  cv::Mat color_img = cv::imread(target_img_path);

  if (!color_img.data) { return 1; }

  cv::namedWindow(DEMO_NAME);
  
  cv::createButton("blur", blur_callback, &color_img, cv::QT_CHECKBOX, 0);
  cv::createButton("convert2gray", gray_callback, &color_img, cv::QT_RADIOBOX);
  cv::createButton("convert2rgb", rgb_callback, &color_img, cv::QT_RADIOBOX);
  cv::createButton("sobel", sobel_callback, &color_img, cv::QT_PUSH_BUTTON);

  cv::waitKey(0);
  cv::destroyWindow(DEMO_NAME);

  return 0;
}
