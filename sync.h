#ifndef SYNC_H
#define SYNC_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSettings>

class Sync : public QObject {
Q_OBJECT

public:
    explicit Sync(QObject *parent = nullptr);
    void uploadFile(const QString &filePath);
    void fetchServerInfo();

signals:
    void uploadProgress(int uploaded, int total);
    void serverInfoFetched(int totalFiles, double storageSize);

private slots:
    void handleUploadFinished(QNetworkReply *reply);  // FIX: Removed extra argument
    void handleServerInfo(QNetworkReply *reply);

private:
    QNetworkAccessManager *networkManager;
    QNetworkAccessManager *serverInfoManager;
    QString serverUrl;
    QString apiKey;
    int uploadedPhotos = 0;
};

#endif // SYNC_H
