#include "HarrisCorners.hpp"

Harris::Harris(cv::Mat input) : m_gradient(input)
{
	m_gradient.setAlgorithm(Utils::diffQ);
	this->m_input = input.clone();
	m_mat = createMatrix<long>(m_input.rows, m_input.cols);
	m_dprod = createMatrix<DProd>(m_input.rows, m_input.cols);
	
	for (uint i = 0; i < m_input.rows; ++i) 
	{
		for (uint j = 0; j < m_input.cols; ++j) 
		{
			this->m_mat[i][j] = 0;
		}
	}
	
}

//////////////////////////////////////////////////////////////////////////////////////////

Harris::~Harris()
{
	clearMatrix<long>(m_mat, m_input.rows);
	clearMatrix<DProd>(m_dprod, m_input.rows);
}

//////////////////////////////////////////////////////////////////////////////////////////

H_Corners Harris::getHarrisCorners()
{
	filter::Filter f(m_input, 5);
	f.gaussian();
	m_input = f.getFilteredImg();
	
	std::vector<double> gK = Filter::getGaussianKernel(6, 3);
// 	Gradient g(m_input);
// 	g.setAlgorithm(Utils::sobel);
	
	for (uint i = 0; i < this->m_input.rows; ++i) 
	{
		for (uint j = 0; j < this->m_input.cols; ++j) 
		{
			double resp = computeDetectorResponse(getStructureMatrix(i, j, gK));
			m_response.push_back((long) round(resp));
			
// 			if (i % 10 == 0 && j % 10 == 0)
// 				std::cout << "Rows: " <<  i << "\tCols: " << j << std::endl;
		}
	}
	
	Thresholding();
	NMS();
	
	getDebugValues();
	
	return getOutput();
}

//////////////////////////////////////////////////////////////////////////////////////////

DProd Harris::getHCParams(int x, int y)
{
	return m_dprod[x][y];
}


//////////////////////////////////////////////////////////////////////////////////////////

DProd Harris::saveParams()
{
	DProd o;
	o.Ix = m_Ix;
	o.Iy = m_Iy;
	o.Ixy = m_Ixy;
	o.Sx = m_Sx;
	o.Sy = m_Sy;
	o.Sxy = m_Sxy;
	o.detH = m_detH;
	o.traceH = m_traceH;
	o.response = m_resp;
	
	return o;
}

///////////////////////////////////////////////////////////////////////////////////////////

vector< double > Harris::getStructureMatrix(int row, int col, std::vector<double> gaussianK)
{
	Grad gr;
	
	std::vector<double> Ix ,Iy, Ixy, structMatrix; 
	
	// get window function
	for (int i = -1; i <= 1; ++i) 
	{
		for (int j = -1; j <= 1; ++j) 
		{
			if (row + i >= 0 && row + i < m_input.rows) 
			{
				if (col + j >= 0 && col + j < m_input.cols) 
				{
					gr = m_gradient.getGradient(row + i, col + j);
					Ix.push_back(gr.dx * gr.dx);
					Iy.push_back(gr.dy * gr.dy);
					Ixy.push_back(gr.dx * gr.dy);
				}
				else 
				{
					Ix.push_back(.0);
					Iy.push_back(.0);
					Ixy.push_back(.0);
				}
			}
			else
			{
					Ix.push_back(.0);
					Iy.push_back(.0);
					Ixy.push_back(.0);
			}
		}
	}
	
	// smooth window
	auto it = gaussianK.begin(), end = gaussianK.end();
	auto x = Ix.begin(), y = Iy.begin(), xy = Ixy.begin();
	
	double a = .0, b = .0, c = .0, d = .0;
		
	for (; it != end; ++it, ++x, ++y, ++xy) 
	{
		a += (*x * *it);
		b += (*xy * *it);
		d += (*y * *it);
	}
	
// 	a /= 9;
// 	b /= 9;
// 	c = b;
// 	d /= 9;
		
	// return Harris matrix
	structMatrix.push_back(a);
	structMatrix.push_back(b);
	structMatrix.push_back(c);
	structMatrix.push_back(d);
	
	
	return structMatrix;
}


///////////////////////////////////////////////////////////////////////////////////////////

double Harris::computeDetectorResponse(std::vector<double> structMat)
{
	double response = .0;
	if (structMat.size() == 0)
		return response;
	else 
	{
		double detH = (structMat[0] * structMat[3]) - (structMat[1] * structMat[2]);
		double traceH = structMat[0] * structMat[3];
		response = detH - 0.04 * traceH * traceH;
	}
	return response;	
}

////////////////////////////////////////////////////////////////////////////////////////////

void Harris::setThreshold(long threshold)
{
	this->m_threshold = threshold;
}

////////////////////////////////////////////////////////////////////////////////////////////

void Harris::Thresholding()
{
	auto it = m_response.begin(), end = m_response.end();
	for (; it != end; ++it) 
	{
		if(*it > m_threshold)
			*it = 0;			
	}
}

////////////////////////////////////////////////////////////////////////////////////////////

H_Corners Harris::getOutput()
{
	H_Corners out;
	
	auto it = m_response_out.begin();
		
	for (uint i = 0; i < m_input.rows; ++i) 
	{
		for (uint j = 0; j < m_input.cols; ++j) 
		{
			cv::Point p;
			if (*it != 0) 
			{
				p.x = j;
				p.y = i;
				out.push_back(p);				
			}
			++it;
		}	
	}	
	
	return out;		
}

/////////////////////////////////////////////////////////////////////////////////////////////

void Harris::NMS()
{
	
	auto it = m_response.begin();
		
	for (uint x = 0; x < m_input.rows; ++x) 
	{
		for (uint y = 0; y < m_input.cols; ++y) 
		{
			m_mat[x][y] = (long) round(*it);
			++it;
		}
	}
	
	for (int x = 0; x < m_input.rows; ++x) 
	{
		for (int y = 0; y < m_input.cols; ++y) 
		{			
			long max = m_mat[x][y];
			for (int lx = -3; lx <= 3; ++lx) 
			{
				for (int ly = -3; ly <= 3; ++ly) 
				{
					if ((lx + x >= 0) && (lx + x < m_input.rows) && (ly + y >= 0) && (ly + y < m_input.cols)) 
					{
						if (m_mat[x + lx][y + ly] > max) 
						{
							max = m_mat[x + lx][y + ly];
							ly = lx = 7;
						}
					}
				}
			}
// 			if (max > m_mat[x][y])
// 				max = 0;
			this->m_response_out.push_back(max);
		}
	}
	
	return;
}

////////////////////////////////////////////////////////////////////////////////////////////


void Harris::getDebugValues() 
{
	auto it = m_response_out.begin(), end = m_response_out.end();
	long min = 100000000000;
	long max = -100000000000;
	int i = 0;
	for (; it != end; ++it) 
	{
		if (*it < min)
			min = *it;
		if (*it > max)
			max = *it;
		if (*it != 0)
			std::cout << "Response value: " << *it << std::endl;
		++i;
	}
	
	std::cout << "Length: " << m_response_out.size() << std::endl;
	std::cout << "Max: " << max << std::endl;
	std::cout << "Min: " << min << std::endl;

}

///////////////////////////////////////////////////////////////////////////////////////////////
