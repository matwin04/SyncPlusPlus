#include "sync.h"
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSettings>
#include <QDebug>
#include <QHttpMultiPart>
#include <QFile>
#include <QFileInfo>
Sync::Sync(QObject *parent) : QObject(parent), networkManager(new QNetworkAccessManager(this)) {
    QSettings settings("config.ini", QSettings::IniFormat);
    serverUrl = settings.value("Immich/server_url", "").toString();
    apiKey = settings.value("Immich/api_key", "").toString();

    if (serverUrl.isEmpty() || apiKey.isEmpty()) {
        qCritical() << "❌ ERROR: API Key or Server URL is missing! Check config.ini";
    }
}

// ✅ Fetch server info
void Sync::fetchServerInfo() {
    QNetworkRequest request(QUrl(serverUrl + "/api/statistics"));
    request.setRawHeader("x-api-key", apiKey.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, &Sync::handleServerInfo);
}

// ✅ Handle server response
void Sync::handleServerInfo(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "⚠️ Failed to fetch server info:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsonObject = jsonResponse.object();

    int totalFiles = jsonObject["totalFiles"].toInt();
    double storageSize = jsonObject["usedStorageGB"].toDouble();

    emit serverInfoFetched(totalFiles, storageSize);
    reply->deleteLater();
}

// ✅ Upload file
void Sync::uploadFile(const QString &filePath) {
    QFile *file = new QFile(filePath);
    if (!file->open(QIODevice::ReadOnly)) {
        qWarning() << "❌ Error opening file:" << filePath;
        delete file;
        return;
    }

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"assetData\"; filename=\"" + QFileInfo(filePath).fileName() + "\""));
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/octet-stream"));
    filePart.setBodyDevice(file);
    file->setParent(multiPart);
    multiPart->append(filePart);

    QNetworkRequest request(QUrl(serverUrl + "/api/assets"));
    request.setRawHeader("x-api-key", apiKey.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data");

    QNetworkReply *reply = networkManager->post(request, multiPart);
    multiPart->setParent(reply);

    connect(reply, &QNetworkReply::finished, this, &Sync::handleUploadFinished);
}

// ✅ Handle upload response
void Sync::handleUploadFinished() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) return;

    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "✅ Upload success:" << reply->readAll();
        emit uploadComplete();
    } else {
        qWarning() << "❌ Upload failed:" << reply->errorString();
    }
    reply->deleteLater();
}

void Sync::uploadComplete() {

}
