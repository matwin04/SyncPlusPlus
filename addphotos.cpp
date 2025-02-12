#include "addPhotos.h"
#include "ui_addPhotos.h"
#include <QFileDialog>

addPhotos::addPhotos(QWidget *parent)
    : QDialog(parent), ui(new Ui::AddPhotos) {
    ui->setupUi(this);
    connect(ui->selectFilesButton, &QPushButton::clicked, this, &AddPhotos::onSelectFiles);
}
addPhotos::~addPhotos() {
    delete ui;
}

void AddPhotos::onSelectFiles() {
    selectedFiles = QFileDialog::getOpenFileName(this,"Select Photos","","Images(*.png,*.jpg,*.jpeg)");
}
QStringList AddPhotos::getSelectedFiles() const {
    return selectedFiles;
}
