#include "ui_MainWindow.h"  // Ensure correct casing
#include "MainWindow.h"
#include "sync.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), syncManager(new Sync(this)) {
    ui->setupUi(this);

    connect(ui->addPhotosButton, &QPushButton::clicked, this, &MainWindow::openFileDialog);
    connect(ui->uploadButton, &QPushButton::clicked, this, &MainWindow::uploadFiles);
    connect(syncManager, &Sync::uploadProgress, this, &MainWindow::updateProgress);
    connect(syncManager, &Sync::serverInfoFetched, this, &MainWindow::updateServerInfo);

    syncManager->fetchServerInfo();
}
MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::openFileDialog() {
    selectedFiles = QFileDialog::getOpenFileNames(this, "Select Photos", "", "Images (*.png *.jpg *.jpeg)");
    ui->fileList->clear();
    for (const QString &file : selectedFiles) {
        ui->fileList->addItem(file);
    }
    ui->fileCountLabel->setText(QString("Files in List:%1").arg(selectedFiles.size()));
}

void MainWindow::uploadFiles() {
    if (selectedFiles.isEmpty()) return;
    ui->progressBar->setValue(0);

    for (const QString &filePath : selectedFiles) {
        syncManager->uploadFile(filePath);
    }
}

void MainWindow::updateProgress(int uploaded, int total) {
    ui->uploadedFilesLabel->setText(QString("Uploaded: %1").arg(uploaded));
    ui->progressBar->setValue((uploaded * 100) / total);
}

void MainWindow::updateServerInfo(int totalFiles, double storageSize) {
    ui->totalFilesLabel->setText(QString("Total Files: %1").arg(totalFiles));
    ui->serverSizeLabel->setText(QString("Storage: %1 GB").arg(storageSize));
}