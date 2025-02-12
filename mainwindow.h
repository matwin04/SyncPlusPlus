//
// Created by mwiner on 2/11/25.
//

#ifndef SYNCPLUSPLUS_MAINWINDOW_H
#define SYNCPLUSPLUS_MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QProgressBar>
#include <QLabel>
#include "sync.h"

QT_BEGIN_NAMESPACE
namespace Ui{ class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
private slots:
    void openFileDialog();
    void uploadFiles();
    void updateProgress(int uploaded,int total);
    void updateServerInfo(int totalFiles,double storageSize);

private:
    Ui::MainWindow *ui;
    Sync *syncManager;
    QStringList selectedFiles;
};


#endif //SYNCPLUSPLUS_MAINWINDOW_H
