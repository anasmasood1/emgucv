#include "cvaux.h"

CVAPI(void) cvHOGDescriptorPeopleDetectorCreate(CvSeq* seq) 
{   
   cv::Vector<float> v = cv::HOGDescriptor::getDefaultPeopleDetector();  
   cvSeqPushMulti(seq, v.begin(), v.size()); 
}
CVAPI(cv::HOGDescriptor*) cvHOGDescriptorCreateDefault() { return new cv::HOGDescriptor; }

CVAPI(cv::HOGDescriptor*) cvHOGDescriptorCreate(
   cv::Size _winSize, 
   cv::Size _blockSize, 
   cv::Size _blockStride,
   cv::Size _cellSize, 
   int _nbins, 
   int _derivAperture, 
   double _winSigma,
   int _histogramNormType, 
   double _L2HysThreshold, 
   bool _gammaCorrection)
{
   return new cv::HOGDescriptor(_winSize, _blockSize, _blockStride, _cellSize, _nbins, _derivAperture, _winSigma, _histogramNormType, _L2HysThreshold, _gammaCorrection);
}
CVAPI(void) cvHOGSetSVMDetector(cv::HOGDescriptor* descriptor, float* svmDetector, int detectorSize) 
{ 
   std::vector<float> v = std::vector<float>(detectorSize); 
   memcpy(&v[0], svmDetector, detectorSize * sizeof(float));  
   descriptor->setSVMDetector(v); 
}

CVAPI(void) cvHOGDescriptorRelease(cv::HOGDescriptor* descriptor) { delete descriptor; }

CVAPI(void) cvHOGDescriptorDetectMultiScale(
   cv::HOGDescriptor* descriptor, 
   CvArr* img, 
   CvSeq* foundLocations,
   double hitThreshold, 
   CvSize winStride,
   CvSize padding, 
   double scale,
   int groupThreshold)
{
   cvClearSeq(foundLocations);

   std::vector<cv::Rect> rects;
   cv::Mat mat = cv::cvarrToMat(img);
   descriptor->detectMultiScale(mat, rects, hitThreshold, winStride, padding, scale, groupThreshold);
   cvSeqPushMulti(foundLocations, &rects[0], rects.size());
}

/*
CVAPI(void) cvHOGDescriptorDetect(
   cv::HOGDescriptor* descriptor, 
   CvArr* img, 
   CvSeq* foundLocations,
   double hitThreshold, 
   CvSize winStride,
   CvSize padding)
{
   cvClearSeq(foundLocations);

   cv::Vector<cv::Rect> rects;
   cv::Mat mat = cv::cvarrToMat(img);
   descriptor->detect(mat, rects, hitThreshold, winStride, padding);
   cvSeqPushMulti(foundLocations, rects.begin(), rects.size());
}*/
