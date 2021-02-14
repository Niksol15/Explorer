#ifndef EXPLORER_HTTP_REQUEST_H
#define EXPLORER_HTTP_REQUEST_H

#include "http_message.h"

enum Method { GET, HEAD, POST, PUT, DELETE, CONNECT, OPTIONS, TRACE, PATCH };

QString MethodToQStr(Method method);

class HttpRequest : public HttpMessage
{
private:
    Method method;

    QString target; // example: '/files'

    QMap<QString, QString> queryParams;

public:
    Method getMethod();

    QString getTarget();

    QMap<QString, QString> getQueryParams();

    HttpRequest& setMethod(Method newMethod);

    HttpRequest& setMethod(const QString& newMethod);

    HttpRequest& setTarget(QString newTarget);

    HttpRequest& addQueryParams(const QString& key, const QString& value);

    QString toQStr();
};

#endif //EXPLORER_HTTP_REQUEST_H
