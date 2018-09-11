
#include "Gradient.hpp"

using namespace Utils;

////////////////////////////////////////////////////////////////////////////

Gradient::Gradient(cv::Mat& input)
{
	// set input img for gradient calculation
	this->m_gradientImg = cv::Mat::zeros(input.rows, input.cols, /*CV_64FC1*/CV_8UC1);
	this->m_output = cv::Mat::zeros(input.rows, input.cols, /*CV_64F*/CV_8UC1);
	this->m_binary = cv::Mat::zeros(input.rows, input.cols, /*CV_64F*/CV_8UC1);
	this->m_img = input;
	
	this->m_threshold = createMatrix<Thresh>(this->m_img.rows, this->m_img.cols);
	this->m_gradientParam = createMatrix<Grad>(this->m_img.rows, this->m_img.cols);
	this->m_visited = createMatrix<int>(this->m_img.rows, this->m_img.cols);

	m_counter = 0;
	
	return;
}

////////////////////////////////////////////////////////////////////////////////////////

Gradient::~Gradient()
{

	clearMatrix<Thresh>(this->m_threshold, this->m_img.rows);
	clearMatrix<Grad>(this->m_gradientParam, this->m_img.rows);
	clearMatrix<int>(this->m_visited, this->m_img.rows);
}


////////////////////////////////////////////////////////////////////////////////////////

void Gradient::setInput(cv::Mat input)
{
	this->m_img = input.clone();
}


////////////////////////////////////////////////////////////////////////////////////////

void Gradient::setAlgorithm(Algorithm alg)
{
	this->m_algo = alg;
}


////////////////////////////////////////////////////////////////////////////////////////

cv::Mat Gradient::getGradientImg(int lowT, int highT, Algorithm alg) 
{
	m_algo = alg;
	iterateOverImg();
    //std::cout << "m_img:rows: " << m_gradientImg.rows << " Cols: " << m_gradientImg.cols << std::endl;
    m_outputStream = m_gradientImg.clone();
	NonMaximumSuppression();
	Thresholding(lowT, highT);
	Hysteresis();
	generateOutput();

	return this->m_output; // m_output
}

//////////////////////////////////////////////////////////////////////////

cv::Mat Gradient::getGradientStream(int lowT, int highT, Algorithm alg)
{
    m_algo = alg;
    iterateOverImg();
    m_outputStream = m_gradientImg.clone();
    return m_outputStream;
}

//////////////////////////////////////////////////////////////////////////

void Gradient::calculateGradientValue(Grad& input)
{
    if ((input.val = sqrt(input.dx * input.dx + input.dy * input.dy)) < 0.00000000001)
        input.val = .0;
	
	return;
}

//////////////////////////////////////////////////////////////////////////

Grad Gradient::calculateGradient(int x, int y) 
{
	Grad grad;
	
	diffInX(grad, x, y);
	diffInY(grad, x, y);	
	calculateEdgeDirection(grad);
	calculateGradientValue(grad);
	
	m_gradientParam[x][y] = grad;
	
	return grad;	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Gradient::calculateEdgeDirection(Grad& grad) 
{
	double num = atan2(grad.dy, grad.dx);
	num *= Helper::rad2deg;
	/*if (m_counter < 200) 
	{
		std::cout << "DEG: " << num << std::endl;
		std::cout << "Dx: " << grad.dx << std::endl;
		std::cout << "Dy: " << grad.dy << std::endl;
	}*/	
	if (num < 22.5 && num > 0) 
	{
		grad.deg = 0;
		return;
	}	
	else if (num < 0 && num > -22.5) 
	{
		grad.deg = 0;
		return;
	}
	else if (num > 157.5) 
	{
		grad.deg = 0;
		return;
	}
	else if (num < -157.5) 
	{
		grad.deg = 0;
		return;
	}
	else if (num < 67.5 && num > 22.5) 
	{
		grad.deg = 45;
		return;
	}
	else if (num < -22.5 && num > -67.5) 
	{
		grad.deg = 45;
		return;
	}
	else if (num < 112.5 && num > 67.5) 
	{
		grad.deg = 90;
		return;
	}
	else if (num < -67.5 && num > -112.5) 
	{
		grad.deg = 90;
		return;
	}
	else if (num < 157.5 && num > 112.5) 
	{
		grad.deg = 135;
		return;
	}
	else if (num < -112.5 && num > -157.5) 
	{
		grad.deg = 135;
		return;
	}
	
	
	
	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Gradient::diffInX(Grad& in, int x, int y) 
{
	switch (m_algo) 
	{
		case diffQ:
			if (x - 1 >= 0 && x + 1 < m_img.rows && y - 1 >= 0 && y + 1 < m_img.cols)
			{
				in.dx = this->m_img.at<uchar>(x + 1, y) - this->m_img.at<uchar>(x, y);
			}
			else
			{
				in.dx = .0;
				in.dy = .0;
			}
			return;
		case diffQN:
			if (x - 1 >= 0 && x + 1 < m_img.rows && y - 1 >= 0 && y + 1 < m_img.cols)
			{
				in.dx = ((this->m_img.at<uchar>(x, y + 1) - this->m_img.at<uchar>(x, y - 1) + this->m_img.at<uchar>(x - 1, y + 1) - this->m_img.at<uchar>(x - 1, y - 1) +
					this->m_img.at<uchar>(x + 1, y + 1) - this->m_img.at<uchar>(x + 1, y - 1)) / 2);
			}
			else
			{
				in.dx = .0;
				in.dy = .0;
			}
			return;
		case sobel:
				in.dx = Filter::SobelX(this->m_img, x, y);
				return;
		default:
			// possible uncaught error
			return;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Gradient::diffInY(Grad& in, int x, int y) 
{
	switch (m_algo) {
		case diffQ:
			if (x - 1 >= 0 && x + 1 < m_img.rows && y - 1 >= 0 && y + 1 < m_img.cols)
			{
				in.dy = this->m_img.at<uchar>(x, y + 1) - this->m_img.at<uchar>(x, y);
			}
			else
			{
				in.dx = .0;
				in.dy = .0;
			}
			return;
		case diffQN:
			if (x - 1 >= 0 && x + 1 < m_img.rows && y - 1 >= 0 && y + 1 < m_img.cols)
			{
				in.dy = ((this->m_img.at<uchar>(x + 1, y) - this->m_img.at<uchar>(x - 1, y) + this->m_img.at<uchar>(x + 1, y - 1) - this->m_img.at<uchar>(x - 1, y - 1) +
					this->m_img.at<uchar>(x + 1, y + 1) - this->m_img.at<uchar>(x - 1, y + 1)) / 2);
			}
			else
			{
				in.dx = .0;
				in.dy = .0;
			}
			return;
		case sobel:
			in.dy = Filter::SobelY(this->m_img, x, y);
			return;
		default:
			// possible uncaught error
			return;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Gradient::iterateOverImg()
{	
	// performs the gradient calculation over the whole image
	for(int row = 0; row < this->m_gradientImg.rows; ++row) 
	{
		for(int col = 0; col < this->m_gradientImg.cols; ++col) 
		{
			this->m_gradientImg.at<uchar>(row, col) = abs(calculateGradient(row, col).val);
		}
	}
	
	this->m_testOut = this->m_gradientImg;
	
	return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Grad Gradient::getGradient(int x, int y)
{
	return calculateGradient(x, y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Gradient::NonMaximumSuppression()
{	
	for(int row = 0; row < this->m_gradientImg.rows; ++row) 
	{
		for(int col = 0; col < this->m_gradientImg.cols; ++col) 
		{
//			std::cout << "Row: " << row << " Col: " << col << std::endl;
			switch (m_gradientParam[row][col].deg) 
			{
				case 0:
					m_gradientParam[row][col].dirX = 0;					
					m_gradientParam[row][col].dirY = 0;
					break;
				case 45:
					m_gradientParam[row][col].dirX = 1;
					m_gradientParam[row][col].dirY = -1;
					break;
				case 90:
					m_gradientParam[row][col].dirX  = 0;
					m_gradientParam[row][col].dirY = -1;
					break;
				case 135:
					m_gradientParam[row][col].dirX = -1;
					m_gradientParam[row][col].dirY = -1;
					break;
				default:
					m_gradientParam[row][col].dirX = 0;
					m_gradientParam[row][col].dirY = 0;
					break;
			}
		
			double anker, plusDir, minusDir;
			
			if (row - 1 >= 0 && row + 1 < this->m_gradientImg.rows) 
			{
				if (col - 1 >= 0 && col + 1 < this->m_gradientImg.cols) 
				{
					anker = this->m_gradientImg.at<uchar>(row, col);
					plusDir = this->m_gradientImg.at<uchar>(row + m_gradientParam[row][col].dirX, col + m_gradientParam[row][col].dirY);
					minusDir = this->m_gradientImg.at<uchar>(row - m_gradientParam[row][col].dirX, col - m_gradientParam[row][col].dirY);

					if (plusDir > anker || minusDir > anker) 
					{
						this->m_gradientImg.at<uchar>(row, col) = (uchar) 0;
						
					}
				}
			}
			else
				this->m_gradientImg.at<uchar>(row, col) = (uchar) 0;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Gradient::Thresholding(int lower, int higher) 
{
	
	for(int row = 0; row < this->m_gradientImg.rows; ++row) 
	{
		for(int col = 0; col < this->m_gradientImg.cols; ++col) 
		{
			if ((int) abs(this->m_gradientImg.at<uchar>(row, col)) < lower) 
			{
				this->m_gradientImg.at<uchar>(row, col) = 0.0;
				this->m_threshold[row][col].lowerThresh = 0.0;
				this->m_threshold[row][col].higherThresh = 0.0;
			}	
			else if ((int) abs(this->m_gradientImg.at<uchar>(row, col)) >= lower && (double) abs(this->m_gradientImg.at<uchar>(row, col)) < higher)
			{
				this->m_threshold[row][col].lowerThresh = (double) abs(this->m_gradientImg.at<uchar>(row, col));
				this->m_threshold[row][col].higherThresh = 0.0;
			}
			else if ((int) abs(this->m_gradientImg.at<uchar>(row, col)) >= higher)
			{
				this->m_threshold[row][col].lowerThresh = 0.0;
				this->m_threshold[row][col].higherThresh = (double) abs(this->m_gradientImg.at<uchar>(row, col));
			}			
		}
	}
	
	return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Gradient::generateOutput()
{		
	this->m_output = this->m_binary;
	return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Gradient::Hysteresis() 
{
	//initialize m_visited with 0
	for(int row = 0; row < this->m_gradientImg.rows; ++row) 
	{
		for(int col = 0; col < this->m_gradientImg.cols; ++col) 
		{			
			this->m_visited[row][col] = 0;
		}
	}
	
	
	for(int row = 0; row < this->m_gradientImg.rows; ++row) 
	{
		for(int col = 0; col < this->m_gradientImg.cols; ++col) 
		{			
			if (this->m_threshold[row][col].higherThresh > 0.0)
			{
				bool t;
				t = Travers(row, col);
//				this->m_visited[row][col] = 1;
				
				if (t)
					this->m_binary.at<uchar>(row, col) = 255;
				else
					this->m_binary.at<uchar>(row, col) = 0;
				
			}
		}
	}
	
	return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Gradient::Travers(int x, int y) 
{
	
	// follows the edges and connects them
	
	if (x + 1 > this->m_gradientImg.rows || x - 1 < 0)
		return false;
	if (y + 1 > this->m_gradientImg.cols || y - 1 < 0)
		return false;
	
	if (m_visited[x][y] == 1)
		return true;
	
	if (this->m_visited[x + 1][y] < 1 && this->m_threshold[x + 1][y].lowerThresh > 0.0 && this->m_gradientParam[x + 1][y].dirX == this->m_gradientParam[x][y].dirX && 
	    this->m_gradientParam[x + 1][y].dirY == this->m_gradientParam[x][y].dirY) 
	{
		this->m_visited[x + 1][y] = 1;
		this->m_binary.at<uchar>(x + 1, y) = 255;
		Travers(x + 1, y);
		return true;
		
	}
	
	else if (this->m_visited[x][y + 1] < 1 && this->m_threshold[x][y + 1].lowerThresh > 0.0 && this->m_gradientParam[x][y  + 1 ].dirX == this->m_gradientParam[x][y].dirX &&
		this->m_gradientParam[x][y + 1].dirY == this->m_gradientParam[x][y].dirY) 
	{
		this->m_visited[x][y  + 1] = 1;
		this->m_binary.at<uchar>(x, y  + 1) = 255;
		Travers(x, y  + 1);
		return true;
		
	}
	
	else if (this->m_visited[x - 1][y] < 1 && this->m_threshold[x - 1][y].lowerThresh > 0.0 && this->m_gradientParam[x - 1][y].dirX == this->m_gradientParam[x][y].dirX &&
		this->m_gradientParam[x - 1][y].dirY == this->m_gradientParam[x][y].dirY) 
	{
		this->m_visited[x - 1][y] = 1;
		this->m_binary.at<uchar>(x - 1, y) = 255;
		Travers(x - 1, y);
		return true;
		
	}
	
	else if (this->m_visited[x][y - 1] < 1 && this->m_threshold[x][y - 1].lowerThresh > 0.0 && this->m_gradientParam[x][y - 1].dirX == this->m_gradientParam[x][y].dirX &&
		this->m_gradientParam[x][y - 1].dirY == this->m_gradientParam[x][y].dirY) 
	{
		this->m_visited[x][y - 1] = 1;
		this->m_binary.at<uchar>(x, y - 1) = 255;
		Travers(x, y - 1);
		return true;
		
	}
	
	else if (this->m_visited[x - 1][y - 1] < 1 && this->m_threshold[x - 1][y - 1].lowerThresh > 0.0 && this->m_gradientParam[x - 1][y - 1].dirX == this->m_gradientParam[x][y].dirX &&
		this->m_gradientParam[x - 1][y - 1].dirY == this->m_gradientParam[x][y].dirY) 
	{
		this->m_visited[x - 1][y - 1] = 1;
		this->m_binary.at<uchar>(x - 1, y - 1) = 255;
		Travers(x - 1, y - 1);
		return true;
		
	}
	
	else if (this->m_visited[x + 1][y - 1] < 1 && this->m_threshold[x + 1][y - 1].lowerThresh > 0.0 && this->m_gradientParam[x + 1][y - 1].dirX == this->m_gradientParam[x][y].dirX &&
		this->m_gradientParam[x + 1][y - 1].dirY == this->m_gradientParam[x][y].dirY) 
	{
		this->m_visited[x + 1][y - 1] = 1;
		this->m_binary.at<uchar>(x + 1, y - 1) = 255;
		Travers(x + 1, y - 1);
		return true;
		
	}
	
	else if (this->m_visited[x - 1][y + 1] < 1 && this->m_threshold[x - 1][y + 1].lowerThresh > 0.0 && this->m_gradientParam[x - 1][y + 1].dirX == this->m_gradientParam[x][y].dirX &&
		this->m_gradientParam[x - 1][y + 1].dirY == this->m_gradientParam[x][y].dirY) 
	{
		this->m_visited[x][y] = 1;
		this->m_visited[x - 1][y + 1] = 1;
		this->m_binary.at<uchar>(x - 1, y + 1) = 255;
		Travers(x - 1, y + 1);
		return true;
		
	}
	
	else if (this->m_visited[x + 1][y + 1] < 1 && this->m_threshold[x + 1][y + 1].lowerThresh > 0.0 && this->m_gradientParam[x + 1][y + 1].dirX == this->m_gradientParam[x][y].dirX &&
		this->m_gradientParam[x + 1][y + 1].dirY == this->m_gradientParam[x][y].dirY) 
	{
		this->m_visited[x][y] = 1;
		this->m_visited[x + 1][y + 1] = 1;
		this->m_binary.at<uchar>(x + 1, y + 1) = 255;
		Travers(x + 1, y + 1);
		return true;
		
	}
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

cv::Mat Gradient::NonMaxSuppression(Utils::Algorithm alg) 
{
	m_algo = alg;
	iterateOverImg();
	NonMaximumSuppression();
	
	return this->m_gradientImg;
}
