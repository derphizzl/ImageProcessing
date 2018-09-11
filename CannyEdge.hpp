

#pragma once

#include "Gradient.hpp"
#include "Filter.hpp"
#include "Helper.hpp"

class canny {
	public:
		/** \brief Canny edge detection
		 * \param input input image
		 * \param output output image (still cv::Mat)
		 * \param lowT low threshold for hysteresis
		 * \param highT high threshold for hysteresis
		 * \param kernelSize size of the gaussian smoothing kernel, MUST be an odd number starting with 3!!
		 * \param alg Algorithm to choose: sobel: Sobel filter kernel (3x3), diffQ: partial derivative using 2 neighbourhood pixels in x and y direction, diffQN: uses an evolved formula for 		the partial derivative */
		static void getCannyEdge(cv::Mat& input, cv::Mat& output, float lowT, float highT, int kernelSize, Algorithm alg) 
		{
			Filter f(input, kernelSize);

			cv::Mat filtered = f.getFilteredImg();
	
			Gradient gr(filtered);
			output = gr.getGradientImg(lowT, highT, alg);
			return;
		}
};