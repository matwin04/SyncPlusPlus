#include "sync.h"
#include <QHttpMultiPart>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QFileInfo>
#include <iostream>
#include <QMimeDatabase>

Sync::Sync(QObject *parent)
    : QObject(parent), networkManager(new QNetworkAccessManager(this)), serverInfoManager(new QNetworkAccessManager(this)),uploadedPhotos(0) {
    QSettings settings("config.ini", QSettings::IniFormat);
    serverUrl = settings.value("Immich/server_url", "").toString();
    apiKey = settings.value("Immich/api_key", "").toString();

    connect(networkManager, &QNetworkAccessManager::finished, this, &Sync::handleUploadFinished);
    connect(serverInfoManager, &QNetworkAccessManager::finished, this, &Sync::handleServerInfo);
}

void Sync::uploadFile(const QString &filePath) {
    QFile *file = new QFile(filePath);
    if (!file->open(QIODevice::ReadOnly)) {
        qDebug() << "❌ Error: Cannot open file:" << filePath;
        delete file;
        return;
    }

    QMimeDatabase mimeDB;
    QString mimeType = mimeDB.mimeTypeForFile(filePath).name();

    //Accept img and vid
    if (!mimeType.startsWith("image/")&&!mimeType.startsWith("video/")) {
        std::cout << "UNSUPORTED FILE:" << filePath.toStdString() << "(" << mimeType.toStdString() << ")" << std::endl;
        file->close();
        delete file;
        return;
    }
    QNetworkRequest request(QUrl(serverUrl + "/api/assets"));
    request.setRawHeader("x-api-key", apiKey.toUtf8());
    request.setRawHeader("Accept", "application/json");

    // Creating multipart form data
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    // File Part
    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QVariant("form-data; name=\"assetData\"; filename=\"" + QFileInfo(filePath).fileName() + "\""));
    filePart.setBody(file->readAll());
    multiPart->append(filePart);

    // Required metadata for Immich API
    QHttpPart deviceAssetIdPart, deviceIdPart, fileCreatedAtPart, fileModifiedAtPart;
    deviceAssetIdPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"deviceAssetId\""));
    deviceAssetIdPart.setBody(QFileInfo(filePath).fileName().toUtf8());

    deviceIdPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"deviceId\""));
    deviceIdPart.setBody("QtUploader");

    fileCreatedAtPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"fileCreatedAt\""));
    fileCreatedAtPart.setBody(QDateTime::currentDateTimeUtc().toString(Qt::ISODate).toUtf8());

    fileModifiedAtPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"fileModifiedAt\""));
    fileModifiedAtPart.setBody(QDateTime::currentDateTimeUtc().toString(Qt::ISODate).toUtf8());

    multiPart->append(deviceAssetIdPart);
    multiPart->append(deviceIdPart);
    multiPart->append(fileCreatedAtPart);
    multiPart->append(fileModifiedAtPart);

    // Send request
    QNetworkReply *reply = networkManager->post(request, multiPart);
    multiPart->setParent(reply);
    file->close();
    file->deleteLater();
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        handleUploadFinished(reply);
    });

    std::cout << "📤 Uploading: " << filePath.toStdString() << std::endl;
}

void Sync::fetchServerInfo() {
    QNetworkRequest request(QUrl(serverUrl + "/api/assets/statistics"));
    request.setRawHeader("x-api-key", apiKey.toUtf8());
    serverInfoManager->get(request);
}

void Sync::handleServerInfo(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject obj = doc.object();
        int totalFiles = obj["totalFiles"].toInt();
        qDebug() << "Total Files" << totalFiles;
        double totalSizeGB = obj["totalUsage"].toDouble() / (1024 * 1024 * 1024);
        emit serverInfoFetched(totalFiles, totalSizeGB);
    } else {
        qDebug() << "Failed to fetch server info:" << reply->errorString();
    }
    reply->deleteLater();
}

void Sync::handleUploadFinished(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        uploadedPhotos++;
        std::cout << "✅ Upload successful! | Total Uploaded: " << uploadedPhotos << std::endl;
        emit uploadProgress(uploadedPhotos, 1);
    } else {
        std::cout << "❌ Upload failed | Error: " << reply->errorString().toStdString() << std::endl;
    }
    reply->deleteLater();
}
