#include "http_message.h"

QString HttpMessage::getVersion(){
    return httpVersion;
}

QMap<QString, QString> HttpMessage::getHeaders(){
    return headers;
}

QJsonDocument HttpMessage::getBody(){
    return body;
}

namespace {
    constexpr char kHttpVer0[] = "HTTP/1.0";
    constexpr char kHttpVer1[] = "HTTP/1.1";
    constexpr char kHttpVer2[] = "HTTP/1.2";
    constexpr char kHttpWrongVer[] = "Wrong HTTP version";
}

HttpMessage& HttpMessage::setHttpVersion(QString ver) {
    if (ver == kHttpVer0 || ver == kHttpVer1 || ver == kHttpVer2) {
        httpVersion = std::move(ver);
    } else {
        throw std::logic_error(kHttpWrongVer + std::string(": ") + ver.toStdString());
    }
    return *this;
}

HttpMessage& HttpMessage::addHeader(const QString& header, const QString& value) {
    headers.insert(header, value);
    return *this;
}

HttpMessage& HttpMessage::setBody(const QString &json) {
    body  = QJsonDocument::fromJson(json.toUtf8());
    return *this;
}
HttpMessage & HttpMessage::setBody(const QJsonDocument &json) {
    body = json;
    return *this;
}
