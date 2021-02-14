#include <iostream>
#include <stdexcept>
#include <QMessageLogger>
#include <QJsonObject>

#include "http_server.h"
#include "http_request_parser.h"

HttpServer::HttpServer(quint16 port, QObject* parent):
    QTcpServer(parent)
{
    listen(QHostAddress::Any, port);
}

void HttpServer::incomingConnection(long long socket)
{
    QTcpSocket* tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readFromClient()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(discardClient()));
    tcpSocket->setSocketDescriptor(socket);
}

namespace {
    constexpr char kUnsupportedRequestError[] = "Your request is unsupported, server supports\n"
                                                "only GET request";
    constexpr char kInvalidRequest[] = "Invalid Request";
    constexpr char kNotFoundResponse[] = " - file path is not exists";
    constexpr char kInvalidEndpoint[] = "Server supports only 2 endpoints:\n"
                                        "\"files/root\" and \"files?path=\"";
    constexpr char kNULLSocketReadError[] = "Socket points to nullptr in\n"
                                            "readMessage method";
    constexpr char kNULLSocketDiscardError[] = "Socket points to nullptr in\n"
                                               "discardClient method";
    constexpr char kNULLSocketSendError[] = "Socket points to nullptr in\n"
                                            "sendResponce method";
}

//NOLINTNEXTLINE
QString HttpServer::readMessage(QTcpSocket *socket)
{
    if(socket == nullptr){
        throw std::logic_error(kNULLSocketReadError);
    }
    QString request;
    // Read a message from socket here
    if(socket->bytesAvailable()){
        request = QString(socket -> readAll());
    }
    return request;
}

//NOLINTNEXTLINE
void HttpServer::closeSocket(QTcpSocket *socket)
{
    socket->close();

    if (socket->state() == QTcpSocket::UnconnectedState)
    {
        delete socket;
    }
}

void HttpServer::readFromClient()
{
    QTcpSocket* socket = dynamic_cast<QTcpSocket*> (sender());

    if (socket == nullptr) {
        QMessageLogger().info() << "socket is not QTcpSocket";
        return;
    }
    try{
        QString request = readMessage(socket);

        QMessageLogger().info() << request;

        HttpResponse response = processRequest(request);

        sendResponse(socket, response.toQStr());
    } catch(const std::exception& e) {
        QMessageLogger().info() << e.what();
    }
    closeSocket(socket);
}

void HttpServer::discardClient()
{
    QTcpSocket* socket = dynamic_cast<QTcpSocket*> (sender());

    if (socket == nullptr) {
        // Log error and handle it
        QMessageLogger().info() << kNULLSocketDiscardError;
        return;
    }

    socket->deleteLater();
}

//NOLINTNEXTLINE
void HttpServer::sendResponse(QTcpSocket* socket, const QString& response) {
    if(socket == nullptr){
        throw std::logic_error(kNULLSocketSendError);
    }
    socket -> write(response.toUtf8());
}

//NOLINTNEXTLINE
HttpResponse HttpServer::createInvalidRequestResponse(const QString &error){
    HttpResponse httpResponse;
    QJsonObject errorBodyResponse;
    errorBodyResponse.insert("Error", error);
    httpResponse.setBody(QJsonDocument(errorBodyResponse));
    return httpResponse.setStatusCode(400);
}

HttpResponse HttpServer::createNotFoundResponse(const QString &path) {
    HttpResponse response;
    QJsonObject errorBodyResponse;
    errorBodyResponse.insert("Error", path + kNotFoundResponse);
    response.setBody(QJsonDocument(errorBodyResponse));
    return response.setStatusCode(404);
}
HttpResponse HttpServer::processGETRequest(HttpRequest &request) {
    if(request.getMethod() != GET){
        throw std::logic_error(kInvalidRequest);
    }
    HttpResponse response;
    response.setHttpVersion(request.getVersion());
    if(request.getTarget().endsWith("/files/root")){
        if(!request.getQueryParams().isEmpty()){
            return createInvalidRequestResponse(kInvalidEndpoint);
        }
        response.setBody(fileSystem.getRootFiles());
        return response.setStatusCode(200);
    }
    if(request.getTarget().endsWith("/files")){
        QMap<QString, QString> queryParams = request.getQueryParams();
        if(queryParams.contains("path") && queryParams.size() == 1){
            QString path = queryParams["path"];
            QMessageLogger().info() << path;
            if(fileSystem.isPathExist(path)){
                response.setBody(fileSystem.getFilesByPath(path));
                return response.setStatusCode(200);
            } else {
                return createNotFoundResponse(path);
            }
        }
    }
    return createInvalidRequestResponse(kInvalidEndpoint);
}

HttpResponse HttpServer::processRequest(const QString& request) {
    HttpRequestParser httpRequestParser(request);
    HttpRequest httpRequest;
    HttpResponse httpResponse;
    try {
        httpRequest = httpRequestParser.parse();
    } catch (const std::exception& e){
        return createInvalidRequestResponse(e.what());
    }
    if(httpRequest.getMethod() == GET){
        return processGETRequest(httpRequest);
    }
    return createInvalidRequestResponse(kUnsupportedRequestError);
}