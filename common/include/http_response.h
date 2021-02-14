#ifndef EXPLORER_HTTP_RESPONSE_H
#define EXPLORER_HTTP_RESPONSE_H

#include <QString>

#include "http_message.h"

class HttpResponse : public HttpMessage
{
private:
    int statusCode; // example: 200

    QString statusCodeStr; // example: 'OK'

public:
    int getStatusCode();

    QString getStatusCodeStr();

    HttpResponse& setStatusCode(int code);

    QString toQStr();
};

#endif //EXPLORER_HTTP_RESPONSE_H
