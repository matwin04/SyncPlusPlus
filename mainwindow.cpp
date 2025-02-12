#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,syncManager(new Sync(this))
{
    ui->setupUi(this);
    connect(ui->addPhotosButton,&QPushButton::clicked,this,&MainWindow::openFileDialog);
    connect(ui->uploadFilesButton,&QPushButton::clicked,this,&MainWindow::uploadFiles);
    connect(syncManager, &Sync::uploadProgress, this, &MainWindow::updateProgress);
    connect(syncManager, &Sync::serverInfoFetched, this, &MainWindow::updateServerInfo);

    syncManager->fetchServerInfo();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::openFileDialog() {
    selectedFiles = QFileDialog::getOpenFileNames(
            this,
            "Select Photos and Videos",
            "",
            "Media Files (*.png *.jpg *.jpeg *.mp4 *.mov *.avi *.mkv)"
    );
    ui->fileList->clear();
    for (const QString &file : selectedFiles) {
        ui->fileList->addItem(file);
    }
    ui->fileCountLabel->setText(QString("Files in List: %1").arg(selectedFiles.size()));
}
void MainWindow::uploadFiles() {
    if (selectedFiles.isEmpty())return;
    ui->progressBar->setValue(0);
    for (const QString &filePath:selectedFiles) {
        syncManager->uploadFile(filePath);
    }
}
void MainWindow::updateProgress(int uploaded, int total) {
    ui->uploadedFilesLabel->setText(QString("Uploaded: %1").arg(uploaded));
    ui->progressBar->setValue((uploaded*100)/total);
}
void MainWindow::updateServerInfo(int totalFiles,double storageSize) {
    ui->totalFilesLabel->setText(QString("TotalFiles: %1").arg(totalFiles));
    ui->serverSizeLabel->setText(QString("Storage: %1 GB").arg(storageSize));
}
