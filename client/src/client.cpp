#include "client.h"
#include <QHostAddress>
#include <QJsonArray>
#include "http_response_parser.h"
#include "http_response.h"
#include <QQuickView>


namespace {
    constexpr char kDefaultAddress[] = "127.0.0.1";
    constexpr int kDefaultPort = 8090;
    const QString GETFileByPathTemplate = "GET /files?path=%1 HTTP/1.1\r\n";
    constexpr char GETRootFiles[] = "GET /files/root HTTP/1.1\r\n";
}
Client::Client(QObject *parent): QObject(parent) {
    sendRequest(GETRootFiles);
}

void Client::sendRequest(const QString& request){
    QTcpSocket* socket = new QTcpSocket();
    socket->connectToHost(QHostAddress(kDefaultAddress), kDefaultPort);
    if (socket->waitForConnected()) {
        qDebug() << "Connected";
    } else {
        qDebug() << "Not connected";
        return;
    }
    socket->write(request.toUtf8());
    if(socket->waitForReadyRead()){
        processResponse(socket->readAll());
        qDebug() << "Readed";
    }
    delete socket;
}

/*
QJsonArray Client::files(){
    return m_files;
}*/
/*
QList<QJsonObject> Client::files(){
    return m_files;
}
*/
QList<QObject*> Client::files(){
    return m_files;
}
QString Client::currentDir(){
    return m_currentDir;
}

void Client::processResponse(const QString& response){
    HttpResponseParser httpParser(response);
    qDebug() << response;
    HttpResponse httpResponse;
    try{
        httpResponse = httpParser.parse();
    } catch(const std::exception& e){
        qDebug() << e.what();
        return;
    }
    if(httpResponse.getStatusCode() != 200){
        QJsonDocument json = httpResponse.getBody();
        qDebug() << json["Error"].toString();
        return;
    }
    QJsonDocument json = httpResponse.getBody();
    m_currentDir = json["directory"].toString();
    emit currentDirChanged(m_currentDir);
    QJsonArray jsonFiles = json["files"].toArray();
    m_files.clear();
    for(const QJsonValue& jVal: jsonFiles){
        QJsonObject jObj = jVal.toObject();
        if(!jObj["isHidden"].toBool()){
            FileInfo* fileInfo = new FileInfo(jObj);
            m_files.append(fileInfo);
        }
    }
    emit filesChanged(m_files);
    qDebug() << "files changed";
}

void Client::back(){
    if(m_currentDir == "/" || m_currentDir == "root"){
        return;
    }
    if(m_currentDir.count("/") == 1){
        home();
        return;
    }
    QString temp = m_currentDir;
    int pos = temp.lastIndexOf("/");
    temp.truncate(pos);
    sendRequest(GETFileByPathTemplate.arg(temp));
}

void Client::next(const QString &nextDir){
    QString temp;
     if(m_currentDir != "root"){
         qDebug() << m_currentDir;
         temp += m_currentDir;
     }
    temp += "/" + nextDir;
    qDebug() << GETFileByPathTemplate.arg(temp);
    sendRequest(GETFileByPathTemplate.arg(temp));
}

void Client::home(){
    if(currentDir() != "root"){
        sendRequest(GETRootFiles);
    }
}
