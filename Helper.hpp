
#pragma once

#include "iostream"
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

namespace Utils {

    typedef struct {
        double dx;
        double dy;
        double val;
        int deg;
        int dirX;
        int dirY;
    } Grad;

    typedef struct {
        double lowerThresh;
        double higherThresh;
    } Thresh;

    typedef struct
    {
        double** matrix;
        uint* ankerPosition;
    } FilterKernel;

    enum Algorithm {sobel, diffQ, diffQN};

    class Helper
    {
        public:
            static constexpr double rad2deg = 180.0/M_PI;
            static constexpr double deg2rad = M_PI/180.0;
            static cv::Mat Array2D2Mat(int** input, uint row, uint cols);


        private:

    };

    template<class TYPE> void clearMatrix(TYPE** data, int size)
    {
        for( int i = 0 ; i < size; i++ )
        {
            delete[] data[i]; // delete array within matrix
        }

        delete[] data;
    }

    template<typename TYPE> TYPE** createMatrix(int rows, int cols)
    {
        TYPE** data;
        data = new TYPE*[rows];
        for (int i = 0; i < rows; ++i)
        {
            data[i] = new TYPE[cols];
        }

        return data;
    }
}
