#ifndef EXPLORER_HTTP_REQUEST_PARSER_H
#define EXPLORER_HTTP_REQUEST_PARSER_H

#include "http_request.h"

class HttpRequestParser {
public:
    explicit HttpRequestParser(QString req);

    HttpRequest parse();

private:
    QString request;
    HttpRequest httpRequest;

    void parseStartLine(const QString &startLine);

    void parseQueryParams(const QStringList &queryParams);
};

#endif //EXPLORER_HTTP_REQUEST_PARSER_H
