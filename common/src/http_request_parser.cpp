#include "http_request_parser.h"
#include <utility>

HttpRequestParser::HttpRequestParser(QString req) : request(std::move(req)), httpRequest() {}

namespace {
    constexpr char kEmptyRequest[] = "Empty HTTP Request";
    constexpr char kInvalidHeader[] = "Invalid header: ";
    constexpr char kInvalidFirstLine[] = "Invalid start line: ";
    constexpr char kInvalidQuery[] = "Invalid Query params";
}

HttpRequest HttpRequestParser::parse() {
    QStringList lines = request.split(QString("\r\n"));
    if (lines.empty()) {
        throw std::logic_error(kEmptyRequest);
    }
    parseStartLine(lines[0]);
    for (int i = 1; i < lines.size() && !lines[i].isEmpty(); ++i) {
        QStringList currentHeader = lines[i].split(": ");
        if (currentHeader.size() != 2) {
            throw std::logic_error(kInvalidHeader + lines[i].toStdString());
        }
        httpRequest.addHeader(currentHeader[0], currentHeader[1]);
    }
    return httpRequest;
}

void HttpRequestParser::parseStartLine(const QString &startLine) {
    QStringList startLineList = startLine.split(' ');
    if (startLineList.size() != 3) {
        throw std::logic_error(kInvalidFirstLine + startLine.toStdString());
    }
    httpRequest.setMethod(startLineList[0]);
    QStringList targetAndQueryParams = startLineList[1].split('?');
    if (targetAndQueryParams.size() > 2) {
        throw std::logic_error(kInvalidQuery);
    }
    httpRequest.setTarget(targetAndQueryParams[0]);
    if (targetAndQueryParams.size() == 2) {
        QStringList queryParams = targetAndQueryParams[1].split('&');
        parseQueryParams(queryParams);
    }
    httpRequest.setHttpVersion(startLineList[2]);
}

void HttpRequestParser::parseQueryParams(const QStringList &queryParams) {
    for (const QString &param: queryParams) {
        QStringList paramList = param.split('=');
        if (paramList.size() != 2) {
            throw std::logic_error(kInvalidQuery);
        }
        httpRequest.addQueryParams(paramList[0], paramList[1]);
    }
}