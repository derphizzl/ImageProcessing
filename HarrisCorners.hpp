#pragma once

#include "Gradient.hpp"

typedef std::vector<cv::Point> H_Corners;

typedef struct 
{
	double Ix;
	double Iy;
	double Ixy;
	double Sx;
	double Sy;
	double Sxy;
	double detH;
	double traceH;
	double response;
} DProd;

class Harris
{
	
public:
	Harris(cv::Mat input);
	~Harris();
	
	// set threshold for output values
	void setThreshold(long threshold);
	
	// get corners as cv::point vector
	H_Corners getHarrisCorners();
	
	// returns the Matrix parameters of the chosen point
	DProd getHCParams(int x, int y);
	
	
private:
	// private member var
	cv::Mat m_input;
	long m_threshold;
	std::vector<long> m_response;
	std::vector<long> m_response_out;
	long** m_mat;
	DProd** m_dprod;
	Gradient m_gradient;
	
	// private member func
	double computeDetectorResponse(std::vector<double> structMat);
	void Thresholding();
	void NMS();
	H_Corners getOutput();
	DProd saveParams();
	std::vector<double> getStructureMatrix(int row, int col, std::vector<double> gaussianK);
	
	// debug variables //
	Grad m_grad;
	double m_Ix, m_Iy, m_Ixy;
	double m_Sx, m_Sy, m_Sxy;
	double m_detH, m_traceH;
	double m_resp;
	
	void getDebugValues();
};