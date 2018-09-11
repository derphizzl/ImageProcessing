#pragma once  

#include "CannyEdge.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using namespace Utils;


namespace houghline {

typedef struct {
	int x;
	int y;
	int counter;
	bool turn;
	int orig;
} Max;
	
typedef std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > HoughL;

class HoughLines 
{
	private:
		
		int** m_Accumulator; 
		cv::Mat m_input;
		int m_w;
		int m_h;
		int m_accu_h;
		int m_accu_w;
		double m_center_x;
		double m_center_y;
		int** m_Acc_out;
		uint m_Threshold;
		
		HoughL HoughPeaks(int** Accumulator);
		
		void NMS(int** Accum);
		
	public:
		
		HoughL HoughTransform();
		int** getAccumulator();
		void getAccumulatorSize(int* size);
		
		HoughLines(cv::Mat in, uint threshold) 
		{
			this->m_Threshold = threshold;
			this->m_input = in;
			this->m_w = this->m_input.cols;
			this->m_h = this->m_input.rows;
			
			this->m_accu_w = 180;
			this->m_accu_h = 2 * (int) round(sqrt(2) * (m_h > m_w ? m_h : m_w ) / 2);
			
			this->m_Accumulator = createMatrix<int>(this->m_accu_h, this->m_accu_w);	
			this->m_Acc_out = createMatrix<int>(this->m_accu_h, this->m_accu_w);
			for (uint i = 0; i < m_accu_h; ++i) 
			{
				for (uint j = 0; j < m_accu_w; ++j) 
				{
					this->m_Accumulator[i][j] = 0;
					this->m_Acc_out[i][j] = 0;
				}
			}
			
			m_center_x = m_w / 2;
			m_center_y = m_h / 2;
		}
		
		~HoughLines() 
		{
			clearMatrix<int>(m_Accumulator, m_accu_h);
			clearMatrix<int>(m_Acc_out, m_accu_h);
		}
		
};

}
