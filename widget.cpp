#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    device(0),
    isGradient(false),
    isCanny(false),
    isHoughLines(false)
{
    ui->setupUi(this);
    ui->labelView->setScaledContents(true);
    setup();
}

Widget::~Widget()
{
    thread->quit();
    while(!thread->isFinished());

    delete thread;
    delete ui;
}

void Widget::setup()
{
    ui->laptopRadioButton->setChecked(true);
    ui->laptopRadioButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
    ui->gradientFilterComboBox->addItem("Filter Kernel");
    ui->gradientFilterComboBox->addItem("d/dx d/dy");
    ui->gradientFilterComboBox->addItem("d/dx* d/dy*");
    ui->gradientFilterComboBox->addItem("Sobel Filter");
    ui->houghLinesComboBox->addItem("Hough Lines");
    ui->houghLinesComboBox->addItem("Hough Space");

    thread = new QThread();
    MainWorker *worker = new MainWorker();
    QTimer *workerTrigger = new QTimer();
    workerTrigger->setInterval(10);

    connect(workerTrigger, SIGNAL(timeout()), worker, SLOT(receiveGrabFrame()));
    connect(thread, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), workerTrigger, SLOT(deleteLater()));
    connect(this, SIGNAL(sendSetup()), worker, SLOT(receiveSetup()));
    connect(this, SIGNAL(sendToggleStream()), worker, SLOT(receiveToggleStream()));
    connect(ui->startButton, SIGNAL(clicked(bool)), this, SLOT(receiveStartButtonClicked()));
    connect(ui->startButton, SIGNAL(clicked(bool)), workerTrigger, SLOT(start()));
    connect(ui->startButton, SIGNAL(clicked(bool)), worker, SLOT(receiveSetup()));
    connect(ui->stopButton, SIGNAL(clicked(bool)), this, SLOT(receiveStopButtonClicked()));
    connect(ui->stopButton, SIGNAL(clicked(bool)), worker, SLOT(receiveStopStream()));
    connect(ui->webcamRadioButton, SIGNAL(clicked(bool)), this, SLOT(receiveSetWebCam()));
    connect(ui->laptopRadioButton, SIGNAL(clicked(bool)), this, SLOT(receiveSetLaptopCamera()));
    connect(this, SIGNAL(sendSetLaptopCamera(uint)), worker, SLOT(receiveToggleCamera(uint)));
    connect(this, SIGNAL(sendSetWebCam(uint)), worker, SLOT(receiveToggleCamera(uint)));
    connect(this, SIGNAL(sendSetLaptopCamera(uint)), this, SLOT(receiveToggleCamera(uint)));
    connect(this, SIGNAL(sendSetWebCam(uint)), this, SLOT(receiveToggleCamera(uint)));
    connect(ui->saveButton, SIGNAL(pressed()), worker, SLOT(receiveSaveImage()));
    connect(worker, SIGNAL(sendFrame(QImage)), this, SLOT(receiveFrame(QImage)));
    connect(thread, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), workerTrigger, SLOT(deleteLater()));
    connect(ui->enableGradientButton, SIGNAL(toggled(bool)), worker, SLOT(receiveGradientButtonEnable()));
    connect(ui->enableGradientButton, SIGNAL(toggled(bool)), this, SLOT(receiveGradientStream()));
    connect(ui->cannyChekBox, SIGNAL(toggled(bool)), this, SLOT(receiveCannyStream()));
    connect(ui->cannyChekBox, SIGNAL(toggled(bool)), worker, SLOT(receiveEnableCannyFilter()));
    connect(ui->HTSpinBox, SIGNAL(valueChanged(int)), worker, SLOT(receiveHigherThreshold(int)));
    connect(ui->LTSpinBox, SIGNAL(valueChanged(int)), worker, SLOT(receiveLowerThreshold(int)));
    connect(ui->gradientFilterComboBox, SIGNAL(currentIndexChanged(int)), worker, SLOT(receiveGradientFilterAlgorithm(int)));
    connect(ui->preFilterCheckBox, SIGNAL(toggled(bool)), worker, SLOT(receiveEnablePreFiltering()));
    connect(ui->houghLinesCheckBox, SIGNAL(toggled(bool)), this, SLOT(receiveHoughStream()));
    connect(ui->houghLinesCheckBox, SIGNAL(toggled(bool)), worker, SLOT(receiveEnableHoughLines()));
    connect(ui->houghLinesComboBox, SIGNAL(currentIndexChanged(int)), worker, SLOT(receiveHoughLinesToggle(int)));
    connect(ui->houghThresholdSpinBox, SIGNAL(valueChanged(int)), worker, SLOT(receiveHuoughThreshold(int)));

    worker->moveToThread(thread);
    //    worker->deleteLater();
    workerTrigger->moveToThread(thread);
    //    workerTrigger->deleteLater();

    thread->start();

    emit sendSetup();
}

void Widget::receiveFrame(QImage frame)
{
    ui->labelView->setPixmap(QPixmap::fromImage(frame));
}

void Widget::receiveToggleCamera(unsigned int device)
{
    if(device == 1) {
        ui->webcamRadioButton->setChecked(true);
        ui->laptopRadioButton->setChecked(false);
    }
    else if (device == 0) {
        ui->webcamRadioButton->setChecked(false);
        ui->laptopRadioButton->setChecked(true);
    }
}

void Widget::receiveStartButtonClicked()
{
    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(true);
    emit sendToggleStream();
}

void Widget::receiveStopButtonClicked()
{
    emit sendToggleStream();
    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
}

void Widget::receiveSetLaptopCamera()
{
    emit sendSetLaptopCamera(0);
}

void Widget::receiveSetWebCam()
{
    emit sendSetWebCam(1);
}

void Widget::receiveGradientStream()
{
    isGradient = !isGradient;
    if(isGradient) {
        ui->cannyChekBox->setCheckable(false);
        ui->cannyChekBox->setChecked(false);
        ui->houghLinesCheckBox->setCheckable(false);
        ui->houghLinesCheckBox->setChecked(false);
    }
    else
    {
        ui->cannyChekBox->setCheckable(true);
        ui->houghLinesCheckBox->setCheckable(true);
    }
}

void Widget::receiveCannyStream() {
    isCanny = !isCanny;
    if(isCanny) {
        ui->enableGradientButton->setCheckable(false);
        ui->enableGradientButton->setChecked(false);
        ui->houghLinesCheckBox->setChecked(false);
        ui->houghLinesCheckBox->setCheckable(false);
    }
    else
    {
        ui->enableGradientButton->setCheckable(true);
        ui->houghLinesCheckBox->setCheckable(true);
    }
}

void Widget::receiveHoughStream()
{
    isHoughLines = !isHoughLines;
    if(isHoughLines) {
        ui->enableGradientButton->setCheckable(false);
        ui->enableGradientButton->setChecked(false);
        ui->cannyChekBox->setCheckable(false);
        ui->cannyChekBox->setChecked(false);
    }
    else {
        ui->enableGradientButton->setCheckable(true);
        ui->cannyChekBox->setCheckable(true);
    }
}




