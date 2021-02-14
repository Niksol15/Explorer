#include "http_request.h"

Method HttpRequest::getMethod() {
    return method;
}

QString HttpRequest::getTarget() {
    return target;
}

QMap<QString, QString> HttpRequest::getQueryParams() {
    return queryParams;
}

namespace {
    constexpr char kStrGET[] = "GET";
    constexpr char kStrHEAD[] = "HEAD";
    constexpr char kStrPOST[] = "POST";
    constexpr char kStrPUT[] = "PUT";
    constexpr char kStrDELETE[] = "DELETE";
    constexpr char kStrCONNECT[] = "CONNECT";
    constexpr char kStrOPTIONS[] = "OPTIONS";
    constexpr char kStrTRACE[] = "TRACE";
    constexpr char kStrPATCH[] = "PATCH";
    constexpr char kUndefinedMethod[] = "Undefined Method";
    constexpr char kEmptyTargetError[] = "An attempt to call a method toQStr for a request\n"
                                         "that is not given a target";
    constexpr char kDefaultHttpVer[] = "HTTP/1.1";
}

QString MethodToQStr(Method method){
    switch (method) {
        case GET:
            return kStrGET;
        case HEAD:
            return kStrHEAD;
        case POST:
            return kStrPOST;
        case PUT:
            return kStrPUT;
        case DELETE:
            return kStrDELETE;
        case CONNECT:
            return kStrCONNECT;
        case OPTIONS:
            return kStrOPTIONS;
        case TRACE:
            return kStrTRACE;
        case PATCH:
            return kStrPATCH;
        default:
            return kUndefinedMethod;
    }
}
HttpRequest& HttpRequest::setMethod(const QString &newMethod) {
    if (newMethod == kStrGET) {
        method = GET;
    } else if (newMethod == kStrHEAD) {
        method = HEAD;
    } else if (newMethod == kStrPOST) {
        method = POST;
    } else if (newMethod == kStrPUT) {
        method = PUT;
    } else if (newMethod == kStrDELETE) {
        method = DELETE;
    } else if (newMethod == kStrCONNECT) {
        method = CONNECT;
    } else if (newMethod == kStrOPTIONS) {
        method = OPTIONS;
    } else if (newMethod == kStrTRACE) {
        method = TRACE;
    } else if (newMethod == kStrPATCH) {
        method = PATCH;
    } else {
        throw std::logic_error( kUndefinedMethod + std::string(": ") + newMethod.toStdString());
    }
    return *this;
}

HttpRequest& HttpRequest::setMethod(Method newMethod) {
    method = newMethod;
    return *this;
}

HttpRequest& HttpRequest::setTarget(QString newTarget) {
    if(newTarget[0] != '/'){
        throw std::logic_error("Wrong target: " + newTarget.toStdString());
    }
    target = std::move(newTarget);
    return *this;
}

HttpRequest& HttpRequest::addQueryParams(const QString &key, const QString &value) {
    queryParams.insert(key, value);
    return *this;
}

QString HttpRequest::toQStr(){
    if(target.isEmpty()){
        throw std::logic_error(kEmptyTargetError);
    }
    QString res(MethodToQStr(method) + " " + target);
    for(const QString& key: queryParams.keys()){
        if(res.back() != '?'){
            res += "&";
        }
        res += key + "=" + queryParams.value(key);
    }
    res += " ";
    if(httpVersion.isEmpty()){
        res += kDefaultHttpVer;
    } else {
        res += httpVersion;
    }
    return res;
}