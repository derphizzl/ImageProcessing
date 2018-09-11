#pragma once

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <exception>
#include "Helper.hpp"
#include <iostream>
#include "Filter.hpp"

using namespace Utils;
using namespace filter;

class Gradient 
{
	public:
        Gradient(){}
		Gradient(cv::Mat& input);
		~Gradient();
		
		void setInput(cv::Mat input);
		/**
		 * \brief returns cv::Mat gradient value image
		 * \param threshold sets threshold for b/w values, 0 is no threshold */
		cv::Mat getGradientImg(int lowT, int highT, Algorithm alg);
		/**
		 * \brief returns Gradient vector and value
		 * \param xy pixel coordinates */
		Grad getGradient(int x, int y);
		/**
		 * \brief calculates gradient of input and returns the non maxima suppressed gradient img */
		cv::Mat NonMaxSuppression(Utils::Algorithm alg);
		
		void setAlgorithm(Algorithm alg);

        cv::Mat getGradientStream(int lowT, int highT, Algorithm alg);
	
	private:
		cv::Mat m_img;
		cv::Mat m_gradientImg;
		Grad** m_gradientParam;
		Thresh** m_threshold;
		cv::Mat m_output;
		cv::Mat m_binary;
		cv::Mat m_testOut;
		int** m_visited;
		Algorithm m_algo;
		int m_counter;
        cv::Mat m_outputStream;
		

		void diffInX(Grad& in, int x, int y);
		void diffInY(Grad& in, int x, int y); 
		void calculateGradientValue(Grad& input);
		Grad calculateGradient(int x, int y);
		void iterateOverImg();  
		void calculateEdgeDirection(Grad& grad);
		void NonMaximumSuppression();
		void Thresholding(int lower, int higher);
		void generateOutput();
		void Hysteresis();
		bool Travers(int x, int y);
};  
