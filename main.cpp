//
// Created by yongqi on 17-7-9.
//

#include "dmz.h"
#include "scan/scan.h"
#include </usr/include/opencv2/highgui/highgui_c.h>
#include <iostream>
#include <scan/scan.h>

int main(int argc, char **argv) {
  IplImage *src = cvLoadImage("transformed.jpg", CV_LOAD_IMAGE_GRAYSCALE);
//  IplImage *dst = cvCreateImage(cvSize(src->width, src->height),8,1);
//  cvCvtColor(src, dst, CV_RGB2GRAY);
  FrameScanResult result;
  ScannerState state;
  scanner_initialize(&state);
  scanner_add_frame_with_expiry(&state, src, true, &result);
//  if (result.usable) {
    ScannerResult scannerResult;
    scanner_result(&state, &scannerResult);
    std::cout << scannerResult.n_numbers << std::endl;
//  }
}
