// 2020-09-20



#include <iostream>
#include <string>
#include <sstream>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp" 




int main(int argc, char *argv[]) {
  std::string target_img_path = "../../demo_imgs/demo_img0.jpg";

  cv::Mat color_img = cv::imread(target_img_path);
  cv::Mat gray_img = cv::imread(target_img_path, 0); 

  if (!color_img.data) { return 1; }

  int32_t img_height = color_img.rows - 1;
  int32_t img_width = color_img.cols - 1;
  cv::Vec3b tmp_pixel = color_img.at<cv::Vec3b>(img_height, img_width);
  std::cout << "B, G, R pixel equals " 
      << (int)tmp_pixel[0] << ", " << (int)tmp_pixel[1] << ", " << (int)tmp_pixel[2] << std::endl;

  cv::imwrite("./out.jpg", gray_img);

  cv::imshow("Lena BGR", color_img);
  cv::imshow("Lena GRAY", gray_img);
  cv::waitKey(0);

  return 0;
}
