#include "http_response_parser.h"
#include <utility>

HttpResponseParser::HttpResponseParser(QString init_response) :
        strResponse(std::move(init_response)), httpResponse() {}

namespace {
    constexpr char kEmptyResponse[] = "Empty HTTP Response";
    constexpr char kInvalidHeader[] = "Invalid header: ";
    constexpr char kInvalidFirstLine[] = "Invalid start line: ";
}

HttpResponse HttpResponseParser::parse() {
    QStringList lines = strResponse.split(QString("\r\n"));
    if (lines.empty()) {
        throw std::logic_error(kEmptyResponse);
    }
    parseStartLine(lines[0]);
    size_t linesCounter;
    for (linesCounter = 1; linesCounter < lines.size() && !lines[linesCounter].isEmpty(); ++linesCounter) {
        QStringList currentHeader = lines[linesCounter].split(": ");
        if (currentHeader.size() != 2) {
            throw std::logic_error(kInvalidHeader + lines[linesCounter].toStdString());
        }
        httpResponse.addHeader(currentHeader[0], currentHeader[1]);
    }
    parseBody();
    return httpResponse;
}

void HttpResponseParser::parseStartLine(const QString &startLine) {
    QStringList startLineList = startLine.split(' ');
    httpResponse.setHttpVersion(startLineList[0]);
    if (startLineList.size() == 3 && startLineList[1] == "200" && startLineList[2] == "OK") {
        httpResponse.setStatusCode(200);
        return;
    }
    if (startLineList.size() == 4) {
        if (startLineList[1] == "400" && startLineList[2] == "Bad" && startLineList[2] == "Request") {
            httpResponse.setStatusCode(400);
            return;
        }
        if (startLineList[1] == "404" && startLineList[2] == "Not" && startLineList[2] == "Found") {
            httpResponse.setStatusCode(404);
            return;
        }
    }
    throw std::logic_error(kInvalidFirstLine);
}

void HttpResponseParser::parseBody() {
    QStringList responseList = strResponse.split("\r\n\r\n");
    if(responseList.size() == 2){
        httpResponse.setBody(responseList[1]);
    }
}