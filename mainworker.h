#ifndef MAINWORKER_H
#define MAINWORKER_H

#include <QObject>
#include <QImage>
#include <QTimer>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include "Corners.hpp"
#include "HarrisCorners.hpp"

enum ActiveFilter {grayscale, grad, canny, houghtransform};

using namespace filter;
using namespace Utils;

class MainWorker : public QObject
{
    Q_OBJECT
public:
    explicit MainWorker(QObject *parent = 0);
    ~MainWorker();

private:
    cv::Mat _frameOriginal;
    cv::Mat _frameProcessed;
    cv::Mat _frameBuffer;
    cv::Mat _frameOut;
    cv::VideoCapture *cap;

    bool status;
    bool toggleStream;
    bool toggleCamera;

    unsigned int m_device;

    void checkIfDeviceAlreadyOpened();
    void process();

    unsigned int imgNumber;

    ActiveFilter imgFilter;
    int higherThreshold;
    int lowerThreshold;
    Algorithm gradientFilterKernel;
    bool gradientToggle;
    void getGradientImage();
    bool enableGradientPreFilter;
    void getCannyImage();
    bool cannyToggle;

    void getHoughLines();
    bool houghToggle;
    bool houghStreamToggle;
    int houghThreshold;

signals:
    void sendFrame(QImage frameProcessed);

public slots:
    void receiveGrabFrame();
    void receiveSetup();
    void receiveToggleStream();
    void receiveToggleCamera(unsigned int dev);
    void receiveSaveImage();
    void receiveStopStream();
    void receiveGradientButtonEnable();
    void receiveHigherThreshold(int hThresh);
    void receiveLowerThreshold(int lThresh);
    void receiveGradientFilterAlgorithm(int alg);
    void receiveEnablePreFiltering();
    void receiveEnableCannyFilter();
    void receiveEnableHoughLines();
    void receiveHoughLinesToggle(int);
    void receiveHuoughThreshold(int thresh);
};

#endif // MAINWORKER_H
