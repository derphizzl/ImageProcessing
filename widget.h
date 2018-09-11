#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QObject>
#include <QImage>
#include <QThread>

#include "mainworker.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include "Gradient.hpp"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QThread *thread;

    void setup();
    void setupUI();

    bool cameraToggle;
    unsigned int device;

    bool isGradient;
    bool isCanny;

    bool isHoughLines;

signals:
    void sendSetup();
    void sendToggleStream();

    void sendSetLaptopCamera(unsigned int dev);
    void sendSetWebCam(unsigned int dev);

private slots:
    void receiveFrame(QImage frame);
    void receiveToggleCamera(unsigned int device);

    void receiveStartButtonClicked();
    void receiveStopButtonClicked();

    void receiveSetLaptopCamera();
    void receiveSetWebCam();

    void receiveGradientStream();
    void receiveCannyStream();

    void receiveHoughStream();
};

#endif // WIDGET_H
