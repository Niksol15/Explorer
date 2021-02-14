#include "fileinfo.h"

FileInfo::FileInfo(QObject *parent) : QObject(parent)
{

}


FileInfo::FileInfo(const QJsonValue& json, QObject *parent): QObject(parent){
   QJsonObject jObj = json.toObject();
   m_name = jObj["name"].toString();
   m_fileType = jObj["type"].toString();
   m_isHidden = jObj["isHidden"].toBool();
   m_isReadable = jObj["isReadable"].toBool();
}

FileInfo::FileInfo(const QJsonObject& jsonObj, QObject *parent):
    QObject(parent){
    m_name = jsonObj["name"].toString();
    m_fileType = jsonObj["type"].toString();
    m_isHidden = jsonObj["isHidden"].toBool();
    m_isReadable = jsonObj["isReadable"].toBool();
}
QString FileInfo::name(){
    return m_name;
}

QString FileInfo::fileType(){
    return m_fileType;
}

bool FileInfo::isHidden(){
    return m_isHidden;
}

bool FileInfo::isReadable(){
    return  m_isReadable;
}
