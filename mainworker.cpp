#include "mainworker.h"

MainWorker::MainWorker(QObject *parent) :
    QObject(parent),
    status(false),
    toggleStream(false),
    toggleCamera(false),
    m_device(0),
    imgNumber(0),
    imgFilter(grayscale),
    higherThreshold(5),
    lowerThreshold(1),
    gradientToggle(true),
    gradientFilterKernel(diffQ),
    enableGradientPreFilter(false ),
    cannyToggle(false),
    houghToggle(false),
    houghStreamToggle(false),
    houghThreshold(120)
{
    cap = new cv::VideoCapture();

}

MainWorker::~MainWorker()
{
    if(cap->isOpened()) cap->release();
    delete cap;
}

void MainWorker::checkIfDeviceAlreadyOpened()
{
    if(cap->isOpened()) cap->release();
    cap->open(m_device);
}

void MainWorker::process()
{
    switch(imgFilter) {
    case grayscale:
        cv::cvtColor(_frameOriginal, _frameProcessed, cv::COLOR_BGR2GRAY);
        break;
    case grad:
        getGradientImage();
        break;
    case canny:
        getCannyImage();
        break;
    case houghtransform:
        getHoughLines();
        break;
    default:
        cv::cvtColor(_frameOriginal, _frameProcessed, cv::COLOR_BGR2GRAY);
        break;
    }
}

void MainWorker::getGradientImage()
{
    cv::cvtColor(_frameOriginal, _frameBuffer, cv::COLOR_BGR2GRAY);
    if(enableGradientPreFilter)
    {
        Filter f(_frameBuffer, 5);
        cv::Mat _frameOut = f.getFilteredImg();
        Gradient gradient(_frameOut);
        _frameProcessed = gradient.getGradientImg(lowerThreshold, higherThreshold, gradientFilterKernel);
        return;
    }
    Gradient gradient(_frameBuffer);
    _frameProcessed = gradient.getGradientImg(lowerThreshold, higherThreshold, gradientFilterKernel);


}

void MainWorker::getCannyImage()
{
    cv::cvtColor(_frameOriginal, _frameBuffer, cv::COLOR_BGR2GRAY);
    canny::getCannyEdge(_frameBuffer, _frameProcessed, lowerThreshold, higherThreshold, 3, gradientFilterKernel);
}

void MainWorker::getHoughLines()
{
    getGradientImage();
    HoughLines newL(_frameProcessed, houghThreshold); // 120
    HoughL lines = newL.HoughTransform();

    int acc_size[2];
    newL.getAccumulatorSize(acc_size);
    cv::Mat accu = Helper::Array2D2Mat(newL.getAccumulator(), acc_size[0], acc_size[1]);

    if(houghStreamToggle == true) {
        _frameProcessed = accu.clone();
        return;
    }

    HoughL::iterator it = lines.begin();
    HoughL::iterator end = lines.end();

    for (; it != end; ++it)
    {
        cv::line(_frameBuffer, cv::Point(it->first.first, it->first.second), cv::Point(it->second.first, it->second.second), cv::Scalar(255, 0, 0), 1, 8);
    }

    _frameProcessed = _frameBuffer.clone();

}

void MainWorker::receiveGrabFrame()
{
    if(!toggleStream) return;

    (*cap) >> _frameOriginal;
    if(_frameOriginal.empty()) return;

    process();

    QImage output((const unsigned char *)_frameProcessed.data, _frameProcessed.cols, _frameProcessed.rows, QImage::Format_Indexed8);
    emit sendFrame(output);
}

void MainWorker::receiveSetup()
{
    checkIfDeviceAlreadyOpened();
    if(!cap->isOpened()) {
        status = false;
        return;
    }

    status = true;
}

void MainWorker::receiveToggleStream() {
    toggleStream = !toggleStream;
}

void MainWorker::receiveToggleCamera(unsigned int dev) {
    m_device = dev;
    if(cap->isOpened()) cap->release();
    cap->open(dev);
}

void MainWorker::receiveSaveImage()
{
    if(!cap->isOpened())
        return;
    imgNumber++;
    std::string imgName = "C:/Users/phili/Documents/QTprojects/ImageProcessing_UI/ImgUIScreenShot_" + std::to_string(imgNumber) + ".png";
    cv::imwrite(imgName, _frameProcessed);
}

void MainWorker::receiveStopStream()
{
    if(cap->isOpened()) cap->release();
}

void MainWorker::receiveGradientButtonEnable()
{
    gradientToggle = !gradientToggle;
    if(!gradientToggle) {
        imgFilter = grad;
    }
    else {
        imgFilter = grayscale;
    }
}

void MainWorker::receiveHigherThreshold(int hThresh)
{
    higherThreshold = hThresh;
}

void MainWorker::receiveLowerThreshold(int lThresh)
{
    lowerThreshold = lThresh;
}

void MainWorker::receiveGradientFilterAlgorithm(int alg)
{
    switch(alg) {
    case 0:
        gradientFilterKernel = diffQ;
        break;
    case 1:
        gradientFilterKernel = diffQ;
        break;
    case 2:
        gradientFilterKernel = diffQN;
        break;
    case 3:
        gradientFilterKernel = sobel;
        break;
    default:
        gradientFilterKernel = diffQ;
        break;
    }
}

void MainWorker::receiveEnablePreFiltering()
{
    enableGradientPreFilter = !enableGradientPreFilter;
}

void MainWorker::receiveEnableCannyFilter()
{
    cannyToggle = !cannyToggle;
    if(cannyToggle)
        imgFilter = canny;
    else
        imgFilter = grayscale;
}

void MainWorker::receiveEnableHoughLines()
{
    houghToggle = !houghToggle;
    if(houghToggle)
        imgFilter = houghtransform;
    else
        imgFilter = grayscale;
}

void MainWorker::receiveHoughLinesToggle(int num)
{
    if(num == 1)
        houghStreamToggle = true;
    else
        houghStreamToggle = false;
}

void MainWorker::receiveHuoughThreshold(int thresh)
{
    houghThreshold = thresh;
}
