#ifndef ADDPHOTOS_H
#define ADDPHOTOS_H
#include <QDialog>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui {class AddPhotos;}
QT_END_NAMESPACE

class AddPhotos : public QDialog {
    Q_OBJECT
public:
    explicit AddPhotos(QWidget *parent = nullptr);
    ~AddPhotos();
    QStringList getSelectedFiles() const;
private slots:
    void onSelectFiles();
private:
    Ui::AddPhotos *ui;
    QStringList selectFiles;
};
#endif