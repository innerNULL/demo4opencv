

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp" 




const std::string DEMO_NAME = "demo3";
const char* args = {
  "{help h usage ? | | print this message}" 
  "{@image | ../../demo_imgs/demo_img1.jpg | Image to process}"
};


void show_histogram_callback(int state, void* input_data) {
  std::cout << "ont times execute histogram callback." << std::endl;

  // Internal vars def
  cv::Mat* input_img;
  std::vector<cv::Mat> bgr_channels;
  int pixel_num = 256;
  float pixel_range[] = {0, 256};
  const float* pixel_ranges = { pixel_range };
  std::vector<cv::Mat> bgr_histogram_data;
  int figure_width = 512;
  int figure_height = 256; 
  int histogram_step = std::round((float)figure_width / (float)pixel_num);
  // Initialize a gray based image.
  cv::Mat histogram_image(figure_height, figure_width, CV_8UC3, cv::Scalar(20, 20, 20));

  // Internal vars initialization
  input_img = (cv::Mat*)input_data;
  cv::split(*input_img, bgr_channels);
  bgr_histogram_data.resize(3);

  //std::cout << "histogram_step=" + std::to_string(histogram_step) << std::endl;

  for (int32_t i = 0; i < bgr_channels.size(); ++i) {
    cv::calcHist(&bgr_channels[i], 1, 0, cv::Mat(), bgr_histogram_data[i], 1, &pixel_num, &pixel_ranges);
    cv::normalize(bgr_histogram_data[i], bgr_histogram_data[i], 0, figure_height, cv::NORM_MINMAX);
    cv::Scalar ploting_color;

    //std::cout << bgr_histogram_data[i] << std::endl;

    if (i == 0) { ploting_color = cv::Scalar(255, 0, 0); }
    if (i == 1) { ploting_color = cv::Scalar(0, 255, 0); }
    if (i == 2) { ploting_color = cv::Scalar(0, 0, 255); }

    for (int32_t j = 1; j < pixel_num; ++j) {
      int start_point_x = histogram_step * (j - 1);
      float start_point_y = bgr_histogram_data[i].at<float>(j - 1);
      int end_point_x = histogram_step * j;
      float end_point_y = bgr_histogram_data[i].at<float>(j - 1);

      cv::Point line_start = cv::Point(start_point_x, start_point_y);
      cv::Point line_end = cv::Point(end_point_x, end_point_y);
      cv::line(histogram_image, line_start, line_end, ploting_color);
    }
    cv::imshow("img", histogram_image);
  }

  return;
}


void equalize_histogram_callback(int state, void* input_data) {
  cv::Mat target_img;
  cv::Mat ycrcb_img;
  std::vector<cv::Mat> ycrcb_channels;

  ((cv::Mat*)input_data)->copyTo(target_img);
  cv::cvtColor(target_img, ycrcb_img, cv::COLOR_BGR2YCrCb);
  cv::split(ycrcb_img, ycrcb_channels);

  cv::equalizeHist(ycrcb_channels[0], ycrcb_channels[0]);
  cv::merge(ycrcb_channels, ycrcb_img);

  cv::cvtColor(ycrcb_img, target_img, cv::COLOR_YCrCb2BGR);

  cv::imshow("img", target_img);
  return;
}


void lomography_effect_callback(int state, void* input_data) {
  return;
}


void cartoonize_effect_callback(int state, void* input_data) {
  return;
}


int main(int argc, char *argv[]) {
  cv::CommandLineParser parser(argc, argv, args);
  parser.about("demo3 arguments parser.");
  if (parser.has("help")) {
    parser.printMessage();
  }

  std::string img_file = parser.get<std::string>(0);
  std::cout << "img_file=" + img_file << std::endl;

  cv::Mat img = cv::imread(img_file);
  cv::namedWindow("img");
  cv::createButton("Show histogram", show_histogram_callback, &img, 0);
  cv::createButton("Equalize histogram", equalize_histogram_callback, &img, 0);
  cv::createButton("Lomography effect", lomography_effect_callback, &img, 0);
  cv::createButton("Cartoonize effect", cartoonize_effect_callback, &img, 0);
  cv::imshow("img", img);
  cv::waitKey(0);
  cv::destroyWindow("img");

  return 0;
}


