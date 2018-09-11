

#include "Corners.hpp"


vector< cv::Point > Corners::getLineCrossings(HoughL lines)
{
	HoughL::iterator it1 = lines.begin(), it2;
	HoughL::iterator end1 = lines.end();

	// calculate the line intersections and return the points
	
	vector< cv::Point > intersections;
	
	uint i = 0;
	for (; it1 != end1; ++it1)
	{
		it2 = it1 + 1;
		for (; it2 != lines.end(); ++it2) 
		{
			cv::Point x1(it1->first.first, it1->first.second);
			cv::Point y1(it1->second.first, it1->second.second);
			
			cv::Point x2(it2->first.first, it2->first.second);
			cv::Point y2(it2->second.first, it2->second.second);
			
			cv::Point pnt;
			if(getIntersectionPoint(x1, y1, x2, y2, pnt))
				intersections.push_back(pnt);
		}
	}
	
	std::cout << "Intersections: " << intersections.size() << std::endl;
	
	return intersections;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Corners::getIntersectionPoint(cv::Point a1, cv::Point a2, cv::Point b1, cv::Point b2, cv::Point& intPnt)
{
    cv::Point p = a1;
    cv::Point q = b1;
    cv::Point r(a2-a1);
    
    cv::Point s(b2-b1);

    if(cross(r,s) == 0) 
	    return false;

    double t = cross(q-p,s) / cross(r,s);

    intPnt = p + t * r;
    
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double Corners::cross(cv::Point v1, cv::Point v2)
{
    return v1.x * v2.y - v1.y * v2.x;
}
