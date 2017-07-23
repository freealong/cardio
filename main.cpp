//
// Created by yongqi on 17-7-9.
//

#include <stdio.h>
#include </usr/include/opencv2/imgproc/imgproc_c.h>
#include </usr/include/opencv2/highgui/highgui_c.h>
#include "scan/scan.h"

int main(int argc, char **argv) {
  IplImage *src = cvLoadImage(argv[1]);
  IplImage *dst = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 3);
  cvCvtColor(src, dst, CV_RGB2YCrCb);
  IplImage* y = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
  IplImage* cb = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
  IplImage* cr = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
  cvSplit(dst, y, cb, cr, NULL);

  float focus_score = dmz_focus_score(y, false);
  printf("Focus score: %f\n", focus_score);

  dmz_edges found_edges;
  dmz_corner_points corner_points;
  FrameOrientation orientation = FrameOrientationLandscapeRight;
  bool card_detected = dmz_detect_edges(y, cb, cr, orientation, &found_edges, &corner_points);
  printf("Card detected: %s\n", card_detected ? "true" : "false");
  printf("Found all edges: %s\n", dmz_found_all_edges(found_edges) ? "true" : "false");

  dmz_context* context = dmz_context_create();
  IplImage* card_y = NULL;
  dmz_transform_card(context, y, corner_points, orientation, false, &card_y);

  FrameScanResult result;
  result.focus_score = focus_score;
  result.flipped = false;

  ScannerState scanner_state;
  scanner_initialize(&scanner_state);
  scanner_add_frame_with_expiry(&scanner_state, card_y, true, &result);
  scanner_add_frame_with_expiry(&scanner_state, card_y, true, &result);
  scanner_add_frame_with_expiry(&scanner_state, card_y, true, &result);

  printf("Usable: %s\n", result.usable ? "true" : "false");
  printf("Upside down: %s\n", result.upside_down ? "ture" : "false");
  printf("vseg score: %f\n", result.vseg.score);

  ScannerResult scan_result;
  scanner_result(&scanner_state, &scan_result);
  printf("Scan complete: %s\n", scan_result.complete ? "true" : "false");
  printf("# of numbers: %d\n", scan_result.n_numbers);
  printf("Expiry month: %d\n", scan_result.expiry_month);
  printf("Expiry year: %d\n", scan_result.expiry_year);
  for (int i = 0; i < scan_result.n_numbers; ++i)
    printf("%d ", scan_result.predictions[i]);

  return 0;
}
