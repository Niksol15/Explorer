#ifndef EXPLORER_HTTP_MESSAGE_H
#define EXPLORER_HTTP_MESSAGE_H

#include <QMap>
#include <QString>
#include <QJsonDocument>

class HttpMessage
{
protected:
    QString httpVersion; // example: 'HTTP/1.1'

    QMap<QString, QString> headers;

    QJsonDocument body;

public:
    QString getVersion();

    QMap<QString, QString> getHeaders();

    QJsonDocument getBody();

    HttpMessage& setHttpVersion(QString ver);

    HttpMessage& addHeader(const QString& header, const QString& value);

    HttpMessage& setBody(const QString& json);
    HttpMessage& setBody(const QJsonDocument& json);
};

#endif //EXPLORER_HTTP_MESSAGE_H
