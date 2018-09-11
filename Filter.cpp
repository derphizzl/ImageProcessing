#include "Filter.hpp"

using namespace filter;
using namespace Utils;
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Filter::setInputKernel(FilterKernel kern, uint size)
{
	
	this->inputKernel.matrix = kern.matrix;
	m_kernelSize = size;
	
	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Filter::Filter(cv::Mat in, uint size)
{
	this->m_input = in;
	if (size > 0) 
	{
		
		m_kernelSize = size;
		inputKernel.matrix = createMatrix<double>(m_kernelSize, m_kernelSize);
		gaussian();
	}	
	
	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Filter::~Filter()
{
	clearMatrix<double>(this->inputKernel.matrix, m_kernelSize);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

cv::Mat Filter::getFilteredImg()
{	
	this->m_output = cv::Mat::zeros(m_input.rows, m_input.cols, CV_8UC1/*CV_64F*/);
// 	gaussian(this->inputKernel);
	iterateOverImg();
	return m_output;	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void Filter::iterateOverImg()
{
	
	calcFilterSum();
	
	for(int row = 0; row < this->m_output.rows; ++row) 
	{
		for(int col = 0; col < this->m_output.cols; ++col) 
		{		
			executeConvolution(row, col);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Filter::executeConvolution(int row, int col)
{
	int var = (m_kernelSize - 1) / 2;
	
		double tmp = 0.0;	  
		
		for (int i = - var; i <= var; i++) 
		{
			for (int j = -var; j <= var; j++) 
			{
				if (row + i < 0)
					continue;
				if (col + j < 0)
					continue;
				if (row + i >= m_input.rows)
					continue;
				if (col + j >= m_input.cols)
					continue;
				
				double t = ((double) this->m_input.at<uchar>(row + i, col + j) * this->inputKernel.matrix[i + var][j + var]);
				tmp += t;
			}	
		}	     
		this->m_output.at<uchar>(row, col) = (uchar) round(abs(tmp));      
//		std::cout << "Row: " << row << " Col: " << col << " Tmp: " << tmp << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double Filter::SobelX(cv::Mat& input, uint row, uint col) 
{
	int var = 1;
	
	FilterKernel kern;
	kern.matrix = createMatrix<double>(3, 3);
	kern.matrix[0][0] = 1.0;
	kern.matrix[0][1] = 0.0;
	kern.matrix[0][2] = -1.0;
	kern.matrix[1][0] = 2.0;
	kern.matrix[1][1] = 0.0;
	kern.matrix[1][2] = -2.0;
	kern.matrix[2][0] = 1.0;
	kern.matrix[2][1] = 0.0;
	kern.matrix[2][2] = -1.0;
	
	double tmp = 0.0;	  
		
	for (int i = - var; i <= var; i++) 
	{
		for (int j = -var; j <= var; j++) 
		{
			if (row + var >= 0 && row + var < input.rows && col + var >= 0 && col + var < input.cols) 
			{
//				std::cout << "row+i: " << row + i << " col+i: " << col + j << std::endl;
				double t = (double) input.at<uchar>(row + i, col + j);
				tmp  += (t * kern.matrix[i + var][j + var]);
			}	
		}	
	}	    
	clearMatrix<double>(kern.matrix, 3);
	return abs(tmp); 
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double Filter::SobelY(cv::Mat& input, uint row, uint col) 
{
	int var = 1;
	
	FilterKernel kern;
	kern.matrix = createMatrix<double>(3, 3);
	kern.matrix[0][0] = 1.0;
	kern.matrix[0][1] = 2.0;
	kern.matrix[0][2] = 1.0;
	kern.matrix[1][0] = 0.0;
	kern.matrix[1][1] = 0.0;
	kern.matrix[1][2] = 0.0;
	kern.matrix[2][0] = -1.0;
	kern.matrix[2][1] = -2.0;
	kern.matrix[2][2] = -1.0;
		
	double tmp = 0.0;	  
		
	for (int i = - var; i <= var; i++) 
	{
		for (int j = -var; j <= var; j++) 
		{
			if (row + var >= 0 && row + var < input.rows && col + var >= 0 && col + var < input.cols) 
			{
				double t = (double) input.at<uchar>(row + i, col + j); 
				tmp += (t * kern.matrix[i + var][j + var]);
			}	
			
		}	
	}	    
	clearMatrix<double>(kern.matrix, 3);
	return abs(tmp);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Filter::calcFilterSum() 
{
	double tmp = 0;
	
	for (uint i = 0; i < m_kernelSize; ++i) 
	{
		for (uint j = 0; j < m_kernelSize; ++j) 
		{
			tmp += this->inputKernel.matrix[i][j]; 
		}	
	}
	
	m_FilterSum = abs(tmp);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Filter::gaussian()
{
    // set standard deviation to 1.0
	double sigma = 1.0;
	double r, s = 2.0 * sigma * sigma;
 
    // sum is for normalization
	double sum = 0.0;
 
	int var = (m_kernelSize - 1) / 2;
	
    // generate 5x5 kernel
	for (int x = -var ; x <= var; x++)
	{
		for(int y = -var; y <= var; y++)
		{
			r = sqrt(x*x + y*y);
			inputKernel.matrix[x + var][y + var] = (exp(-(r*r)/s))/(M_PI * s);
			sum += inputKernel.matrix[x + var][y + var];
		}
	}
 
    // normalize the Kernel
	for(int i = 0; i < m_kernelSize; ++i) 
	{
		for(int j = 0; j < m_kernelSize; ++j) 
		{
			inputKernel.matrix[i][j] /= (sum);
// 			std::cout << inputKernel.matrix[i][j] << std::endl;
// 			std::cout << k.matrix[i][j] << std::endl;
		}    
	}	
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<double> Filter::getGaussianKernel(double sigma, uint kernelSize) 
{
	double** KernelMatrix = createMatrix<double>(kernelSize, kernelSize);
	double r, s = 2.0 * sigma * sigma;
 
    // sum is for normalization
	double sum = 0.0;
 
	int var = (kernelSize - 1) / 2;
	
    // generate 5x5 kernel
	for (int x = -var ; x <= var; x++)
	{
		for(int y = -var; y <= var; y++)
		{
			r = sqrt(x*x + y*y);
			KernelMatrix[x + var][y + var] = (exp(-(r*r)/s))/(M_PI * s);
			sum += KernelMatrix[x + var][y + var];
		}
	}
 
	std::vector<double> out;
    // normalize the Kernel
	for(int i = 0; i < kernelSize; ++i) 
	{
		for(int j = 0; j < kernelSize; ++j) 
		{
			out.push_back(KernelMatrix[i][j] /= (sum));
// 			std::cout << inputKernel.matrix[i][j] << std::endl;
// 			std::cout << k.matrix[i][j] << std::endl;
		}    
	}
	clearMatrix<double>(KernelMatrix, kernelSize);
	
	return out;
}
