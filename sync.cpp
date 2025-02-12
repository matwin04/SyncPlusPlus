#include "sync.h"
#include <QHttpMultiPart>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

Sync::Sync(QObject *parent)
    : QObject(parent), networkManager(new QNetworkAccessManager(this)), serverInfoManager(new QNetworkAccessManager(this)) {
    QSettings settings("config.ini", QSettings::IniFormat);
    serverUrl = settings.value("Immich/server_url", "").toString();
    apiKey = settings.value("Immich/api_key", "").toString();

    connect(networkManager, &QNetworkAccessManager::finished, this, &Sync::handleUploadFinished);
    connect(serverInfoManager, &QNetworkAccessManager::finished, this, &Sync::handleServerInfo);
}

void Sync::uploadFile(const QString &filePath) {
    QFile *file = new QFile(filePath);
    if (!file->open(QIODevice::ReadOnly)) {
        delete file;
        return;
    }

    QNetworkRequest request(QUrl(serverUrl + "/api/assets"));
    request.setRawHeader("x-api-key", apiKey.toUtf8());

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"assetData\"; filename=\"" + file->fileName() + "\""));
    filePart.setBody(file->readAll());
    multiPart->append(filePart);

    QNetworkReply *reply = networkManager->post(request, multiPart);
    multiPart->setParent(reply);
    file->close();
    file->deleteLater();
}

void Sync::handleUploadFinished(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        emit uploadProgress(1, 1);  // Increment progress
    } else {
        qDebug() << "Upload failed:" << reply->errorString();
    }
    reply->deleteLater();
}

void Sync::fetchServerInfo() {
    QNetworkRequest request(QUrl(serverUrl + "/api/server-info"));
    request.setRawHeader("x-api-key", apiKey.toUtf8());
    serverInfoManager->get(request);
}

void Sync::handleServerInfo(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject obj = doc.object();
        int totalFiles = obj["totalFiles"].toInt();
        double totalSizeGB = obj["totalUsage"].toDouble() / (1024 * 1024 * 1024);
        emit serverInfoFetched(totalFiles, totalSizeGB);
    } else {
        qDebug() << "Failed to fetch server info:" << reply->errorString();
    }
    reply->deleteLater();
}