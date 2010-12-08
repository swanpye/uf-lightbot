/**
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 */
#include <iostream>
#include "HaarCascadeObjectDetector.h"
#include "FaceDetector.h"

using namespace std;
using namespace cv;

FaceDetector::FaceDetector(string face_cascade_file, string mouth_cascade_file)
{
  this->detector             = new HaarCascadeObjectDetector(face_cascade_file);
  this->mouthFeatureDetector = new MouthFeatureDetector(mouth_cascade_file);
}

FaceDetector::FaceDetector(cv::CascadeClassifier face_cascade, cv::CascadeClassifier mouth_cascade)
{
  this->detector             = new HaarCascadeObjectDetector(face_cascade);
  this->mouthFeatureDetector = new MouthFeatureDetector(mouth_cascade);
}

FaceDetector::~FaceDetector()
{
  delete this->detector;
  delete this->mouthFeatureDetector;
}

int 
FaceDetector::detect(Mat image, vector<Face>& faces)
{
  Mat gray;
  vector<Rect> face_rects;
  Face tmp;

  cvtColor(image, gray, CV_BGR2GRAY);
  detector->detect(gray, face_rects); /*Detect using Haar cascades*/ 

  /*Do feature detection*/
  vector<Rect>::const_iterator it;
  for(it = face_rects.begin(); it != face_rects.end(); it++) {
    tmp.face_box = *it;
    this->mouthFeatureDetector->detect(gray, *it, tmp.features.mouth);
    //cout<<tmp.features.mouth.lip_left_edge<<endl;
  }

}

#ifdef __TEST__
int 
main(int argc, char *argv[])
{
  return 0;
}
#endif
