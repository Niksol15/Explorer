#ifndef HTTPDAEMON_H
#define HTTPDAEMON_H

#include <QTcpServer>
#include <QTcpSocket>
#include "filesystem.h"
#include "http_request.h"
#include "http_response.h"
#include "http_request_parser.h"

class HttpServer : public QTcpServer
 {
     Q_OBJECT
 public:
     HttpServer(quint16 port, QObject* parent = nullptr);

     void incomingConnection(long long socket);

 private slots:
     void readFromClient();

     void discardClient();

 private:
     QString readMessage(QTcpSocket* socket);

     void closeSocket(QTcpSocket* socket);

     HttpResponse createInvalidRequestResponse(const QString& error);

     HttpResponse createNotFoundResponse(const QString& path);

     //Due to the fact that it is prohibited to change the signature of functions,
     //I cannot pass a request by a const reference
     HttpResponse processGETRequest(HttpRequest& request);

     void sendResponse(QTcpSocket* socket, const QString& response);

     HttpResponse processRequest(const QString& request);

     FileSystem fileSystem;
 };

#endif // HTTPDAEMON_H
