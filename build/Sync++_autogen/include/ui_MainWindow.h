/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QListWidget *fileList;
    QProgressBar *progressBar;
    QPushButton *uploadButton;
    QPushButton *addPhotosButton;
    QGroupBox *serverInfoBox;
    QVBoxLayout *verticalLayout;
    QLabel *serverUrlLabel;
    QLabel *serverSizeLabel;
    QLabel *totalFilesLabel;
    QLabel *fileCountLabel;
    QLabel *uploadedFilesLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *mainWindow)
    {
        if (mainWindow->objectName().isEmpty())
            mainWindow->setObjectName("mainWindow");
        mainWindow->resize(400, 300);
        centralwidget = new QWidget(mainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        fileList = new QListWidget(centralwidget);
        fileList->setObjectName("fileList");

        gridLayout->addWidget(fileList, 0, 0, 3, 2);

        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName("progressBar");
        progressBar->setValue(24);

        gridLayout->addWidget(progressBar, 4, 0, 1, 2);

        uploadButton = new QPushButton(centralwidget);
        uploadButton->setObjectName("uploadButton");

        gridLayout->addWidget(uploadButton, 3, 1, 1, 1);

        addPhotosButton = new QPushButton(centralwidget);
        addPhotosButton->setObjectName("addPhotosButton");

        gridLayout->addWidget(addPhotosButton, 3, 0, 1, 1);

        serverInfoBox = new QGroupBox(centralwidget);
        serverInfoBox->setObjectName("serverInfoBox");
        verticalLayout = new QVBoxLayout(serverInfoBox);
        verticalLayout->setObjectName("verticalLayout");
        serverUrlLabel = new QLabel(serverInfoBox);
        serverUrlLabel->setObjectName("serverUrlLabel");

        verticalLayout->addWidget(serverUrlLabel);

        serverSizeLabel = new QLabel(serverInfoBox);
        serverSizeLabel->setObjectName("serverSizeLabel");

        verticalLayout->addWidget(serverSizeLabel);

        totalFilesLabel = new QLabel(serverInfoBox);
        totalFilesLabel->setObjectName("totalFilesLabel");

        verticalLayout->addWidget(totalFilesLabel);


        gridLayout->addWidget(serverInfoBox, 0, 3, 5, 1);

        fileCountLabel = new QLabel(centralwidget);
        fileCountLabel->setObjectName("fileCountLabel");

        gridLayout->addWidget(fileCountLabel, 5, 0, 1, 1);

        uploadedFilesLabel = new QLabel(centralwidget);
        uploadedFilesLabel->setObjectName("uploadedFilesLabel");

        gridLayout->addWidget(uploadedFilesLabel, 5, 1, 1, 1);

        mainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(mainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 400, 24));
        mainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(mainWindow);
        statusbar->setObjectName("statusbar");
        mainWindow->setStatusBar(statusbar);

        retranslateUi(mainWindow);

        QMetaObject::connectSlotsByName(mainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *mainWindow)
    {
        mainWindow->setWindowTitle(QCoreApplication::translate("mainWindow", "Immich Photo Uploader", nullptr));
        uploadButton->setText(QCoreApplication::translate("mainWindow", "Upload to Immich", nullptr));
        addPhotosButton->setText(QCoreApplication::translate("mainWindow", "Add Photos", nullptr));
        serverInfoBox->setTitle(QCoreApplication::translate("mainWindow", "Server Info", nullptr));
        serverUrlLabel->setText(QCoreApplication::translate("mainWindow", "URL", nullptr));
        serverSizeLabel->setText(QCoreApplication::translate("mainWindow", "TextLabel", nullptr));
        totalFilesLabel->setText(QCoreApplication::translate("mainWindow", "TextLabel", nullptr));
        fileCountLabel->setText(QCoreApplication::translate("mainWindow", "Files In List", nullptr));
        uploadedFilesLabel->setText(QCoreApplication::translate("mainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainWindow: public Ui_mainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
