

#pragma once

#include "CannyEdge.hpp"
#include "HoughLines.hpp"

using namespace houghline;

class Corners 
{
public:
	std::vector<cv::Point> getLineCrossings(HoughL lines);
		
private:
	bool getIntersectionPoint(cv::Point a1, cv::Point a2, cv::Point b1, cv::Point b2, cv::Point& intPnt);
	double cross(cv::Point v1,cv::Point v2);
};