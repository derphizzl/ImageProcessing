

#include "Helper.hpp"

using namespace Utils;

///////////////////////////////////////////////////////////////////////////////////////////////

cv::Mat Helper::Array2D2Mat(int** input, uint rows, uint cols)
{
	cv::Mat out = cv::Mat::zeros(cols, rows, CV_8UC1);
	for (uint i = 0; i < cols; ++i) 
	{
		for (uint j = 0; j < rows; ++j) 
		{
			out.at<uchar>(i, j) = input[i][j];
		}
	}
	
	return out;
}

////////////////////////////////////////////////////////////////////////////////////////////////

