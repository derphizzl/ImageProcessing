/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_4;
    QLabel *labelView;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *saveButton;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *laptopRadioButton;
    QRadioButton *webcamRadioButton;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_5;
    QCheckBox *preFilterCheckBox;
    QCheckBox *enableGradientButton;
    QCheckBox *cannyChekBox;
    QComboBox *gradientFilterComboBox;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *HTSpinBox;
    QLabel *label;
    QGroupBox *groupBox_5;
    QHBoxLayout *horizontalLayout_3;
    QSpinBox *LTSpinBox;
    QLabel *label_2;
    QWidget *tab_3;
    QHBoxLayout *horizontalLayout_5;
    QGroupBox *groupBox_8;
    QVBoxLayout *verticalLayout_6;
    QCheckBox *houghLinesCheckBox;
    QComboBox *houghLinesComboBox;
    QGroupBox *groupBox_7;
    QHBoxLayout *horizontalLayout_6;
    QSpinBox *houghThresholdSpinBox;
    QLabel *label_3;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(1141, 846);
        verticalLayout_4 = new QVBoxLayout(Widget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        labelView = new QLabel(Widget);
        labelView->setObjectName(QStringLiteral("labelView"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelView->sizePolicy().hasHeightForWidth());
        labelView->setSizePolicy(sizePolicy);
        labelView->setMinimumSize(QSize(800, 600));

        verticalLayout_4->addWidget(labelView);

        tabWidget = new QTabWidget(Widget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        horizontalLayout = new QHBoxLayout(tab);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        startButton = new QPushButton(groupBox);
        startButton->setObjectName(QStringLiteral("startButton"));

        verticalLayout->addWidget(startButton);

        stopButton = new QPushButton(groupBox);
        stopButton->setObjectName(QStringLiteral("stopButton"));

        verticalLayout->addWidget(stopButton);

        saveButton = new QPushButton(groupBox);
        saveButton->setObjectName(QStringLiteral("saveButton"));

        verticalLayout->addWidget(saveButton);


        horizontalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        laptopRadioButton = new QRadioButton(groupBox_2);
        laptopRadioButton->setObjectName(QStringLiteral("laptopRadioButton"));

        verticalLayout_2->addWidget(laptopRadioButton);

        webcamRadioButton = new QRadioButton(groupBox_2);
        webcamRadioButton->setObjectName(QStringLiteral("webcamRadioButton"));

        verticalLayout_2->addWidget(webcamRadioButton);


        horizontalLayout->addWidget(groupBox_2);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        horizontalLayout_4 = new QHBoxLayout(tab_2);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        groupBox_6 = new QGroupBox(tab_2);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        verticalLayout_5 = new QVBoxLayout(groupBox_6);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        preFilterCheckBox = new QCheckBox(groupBox_6);
        preFilterCheckBox->setObjectName(QStringLiteral("preFilterCheckBox"));

        verticalLayout_5->addWidget(preFilterCheckBox);

        enableGradientButton = new QCheckBox(groupBox_6);
        enableGradientButton->setObjectName(QStringLiteral("enableGradientButton"));

        verticalLayout_5->addWidget(enableGradientButton);

        cannyChekBox = new QCheckBox(groupBox_6);
        cannyChekBox->setObjectName(QStringLiteral("cannyChekBox"));

        verticalLayout_5->addWidget(cannyChekBox);

        gradientFilterComboBox = new QComboBox(groupBox_6);
        gradientFilterComboBox->setObjectName(QStringLiteral("gradientFilterComboBox"));

        verticalLayout_5->addWidget(gradientFilterComboBox);


        horizontalLayout_4->addWidget(groupBox_6);

        groupBox_3 = new QGroupBox(tab_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox_4 = new QGroupBox(groupBox_3);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_4);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        HTSpinBox = new QSpinBox(groupBox_4);
        HTSpinBox->setObjectName(QStringLiteral("HTSpinBox"));
        HTSpinBox->setSingleStep(1);
        HTSpinBox->setValue(5);

        horizontalLayout_2->addWidget(HTSpinBox);

        label = new QLabel(groupBox_4);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);


        verticalLayout_3->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(groupBox_3);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_5);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        LTSpinBox = new QSpinBox(groupBox_5);
        LTSpinBox->setObjectName(QStringLiteral("LTSpinBox"));
        LTSpinBox->setSingleStep(1);
        LTSpinBox->setValue(3);

        horizontalLayout_3->addWidget(LTSpinBox);

        label_2 = new QLabel(groupBox_5);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);


        verticalLayout_3->addWidget(groupBox_5);


        horizontalLayout_4->addWidget(groupBox_3);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        horizontalLayout_5 = new QHBoxLayout(tab_3);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        groupBox_8 = new QGroupBox(tab_3);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        verticalLayout_6 = new QVBoxLayout(groupBox_8);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        houghLinesCheckBox = new QCheckBox(groupBox_8);
        houghLinesCheckBox->setObjectName(QStringLiteral("houghLinesCheckBox"));

        verticalLayout_6->addWidget(houghLinesCheckBox);

        houghLinesComboBox = new QComboBox(groupBox_8);
        houghLinesComboBox->setObjectName(QStringLiteral("houghLinesComboBox"));

        verticalLayout_6->addWidget(houghLinesComboBox);


        horizontalLayout_5->addWidget(groupBox_8);

        groupBox_7 = new QGroupBox(tab_3);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        horizontalLayout_6 = new QHBoxLayout(groupBox_7);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        houghThresholdSpinBox = new QSpinBox(groupBox_7);
        houghThresholdSpinBox->setObjectName(QStringLiteral("houghThresholdSpinBox"));
        houghThresholdSpinBox->setMaximum(500);
        houghThresholdSpinBox->setSingleStep(1);
        houghThresholdSpinBox->setValue(120);

        horizontalLayout_6->addWidget(houghThresholdSpinBox);

        label_3 = new QLabel(groupBox_7);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_6->addWidget(label_3);


        horizontalLayout_5->addWidget(groupBox_7);

        tabWidget->addTab(tab_3, QString());

        verticalLayout_4->addWidget(tabWidget);


        retranslateUi(Widget);

        tabWidget->setCurrentIndex(2);
        houghLinesComboBox->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        labelView->setText(QString());
        groupBox->setTitle(QApplication::translate("Widget", "Controls", 0));
        startButton->setText(QApplication::translate("Widget", "Start", 0));
        stopButton->setText(QApplication::translate("Widget", "Stop", 0));
        saveButton->setText(QApplication::translate("Widget", "Save Image", 0));
        groupBox_2->setTitle(QApplication::translate("Widget", "Camera", 0));
        laptopRadioButton->setText(QApplication::translate("Widget", "Laptop", 0));
        webcamRadioButton->setText(QApplication::translate("Widget", "WebCam", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Widget", "Setup", 0));
        groupBox_6->setTitle(QApplication::translate("Widget", "Controls", 0));
        preFilterCheckBox->setText(QApplication::translate("Widget", "Pre Filter", 0));
        enableGradientButton->setText(QApplication::translate("Widget", "Enable Gradient Edges Stream", 0));
        cannyChekBox->setText(QApplication::translate("Widget", "Enable Canny Edge Detector", 0));
        gradientFilterComboBox->setCurrentText(QString());
        groupBox_3->setTitle(QApplication::translate("Widget", "Thresholds", 0));
        groupBox_4->setTitle(QString());
        label->setText(QApplication::translate("Widget", "Higher Threshold", 0));
        groupBox_5->setTitle(QString());
        label_2->setText(QApplication::translate("Widget", "Lower Threshold", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Widget", "Gradient", 0));
        groupBox_8->setTitle(QApplication::translate("Widget", "Controls", 0));
        houghLinesCheckBox->setText(QApplication::translate("Widget", "Enable Hough Lines", 0));
        groupBox_7->setTitle(QApplication::translate("Widget", "Thresholds", 0));
        label_3->setText(QApplication::translate("Widget", "Threshold", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("Widget", "Hough Lines", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
