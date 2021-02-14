#include "http_response.h"

int HttpResponse::getStatusCode() {
    return statusCode;
}

QString HttpResponse::getStatusCodeStr() {
    return statusCodeStr;
}

namespace {
    constexpr char kBadToQStrCalled[] = "An attempt to call a method toQStr for a response\n"
                                        "that is not given a code";
    constexpr char kDefaultHTTPVer[] = "HTTP/1.1";
    constexpr char k200StrCode[] = "OK";
    constexpr char k400StrCode[] = "Bad Request";
    constexpr char k404StrCode[] = "Not Found";
    constexpr char kInvalidCodeError[] = "Invalid status code";
}

HttpResponse& HttpResponse::setStatusCode(int code) {
    switch (code) {
        case 200:
            statusCode = 200;
            statusCodeStr = k200StrCode;
            return *this;
        case 400:
            statusCode = 400;
            statusCodeStr = k400StrCode;
            return *this;
        case 404:
            statusCode = 404;
            statusCodeStr = k404StrCode;
            return *this;
        default:
            throw std::logic_error(kInvalidCodeError);
    }
}

QString HttpResponse::toQStr() {
    if (statusCodeStr.isEmpty()) {
        throw std::logic_error(kBadToQStrCalled);
    }
    QString res;
    if(httpVersion.isEmpty()){
        res += kDefaultHTTPVer;
    } else {
        res += httpVersion;
    }
    res += " " + QString::number(statusCode) + " " + statusCodeStr + "\r\n";
    for(const QString& key: headers.keys()){
        res += key + ": " + headers.value(key) + "\r\n";
    }
    if(!body.isEmpty()){
        res += "\r\n";
        res += body.toJson();
        res += "\r\n";
    }
    return res;
}