#ifndef EXPLORER_HTTP_RESPONSE_PARSER_H
#define EXPLORER_HTTP_RESPONSE_PARSER_H

#include "http_response.h"

class HttpResponseParser
{
public:
    HttpResponseParser(QString init_response);

    HttpResponse parse();
private:
    QString strResponse;
    HttpResponse httpResponse;

    void parseStartLine(const QString &startLine);
    void parseBody();
};

#endif //EXPLORER_HTTP_RESPONSE_PARSER_H
