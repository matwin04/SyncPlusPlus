#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QProgressBar>
#include <QLabel>
#include "sync.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
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

#endif // MAINWINDOW_H
