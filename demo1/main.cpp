// 2020-09-20



#include <iostream>
#include <string>
#include <sstream>

#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp" 




const std::string DEMO_NAME = "demo1";


static void on_change(int pos, void* user_input) {
  if (pos <= 0) { return; }

  cv::Mat blur_img;

  cv::Mat* input_img = (cv::Mat*)user_input;
  cv::blur(*input_img, blur_img, cv::Size(pos, pos));
  cv::imshow(DEMO_NAME, blur_img);

  return;
}


static void on_mouse(int event, int x, int y, int, void* user_input) {
  if (event != cv::EVENT_LBUTTONDOWN) { return; }

  cv::Mat* input_img = (cv::Mat*)user_input;
  cv::circle(*input_img, cv::Point(x, y), 10, cv::Scalar(0, 255, 0), 3);
  //on_change(blur_amount, input_img);
  cv::imshow(DEMO_NAME, *input_img);
  return;
}


int main(int argc, char *argv[]) {
  int32_t blur_amount = 15;
  std::string target_img_path = "../../demo_imgs/demo_img0.jpg";

  cv::Mat color_img = cv::imread(target_img_path);

  if (!color_img.data) { return 1; }

  cv::namedWindow(DEMO_NAME);
  cv::createTrackbar(DEMO_NAME + "_tracker0", DEMO_NAME, &blur_amount, 30, on_change, &color_img);
  cv::setMouseCallback(DEMO_NAME, on_mouse, &color_img);
  on_change(blur_amount, &color_img);
  cv::imshow(DEMO_NAME, color_img);
  // Using qt gui
  //cv::displayOverlay(DEMO_NAME, "Overlay 5secs", 5000);
  cv::waitKey(0);
  cv::destroyWindow(DEMO_NAME);

  return 0;
}
