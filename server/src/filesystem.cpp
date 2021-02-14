#include <QDir>
#include <QJsonArray>

#include "filesystem.h"
#include "file_info.h"

FileSystem::FileSystem() {}

QJsonDocument FileSystem::getRootFiles()
{
    /*
     * Add your root files info here
     * To list all files in the root directory, use QDir::drives()
     * Note that FileInfo class has a method called toJson()
     */
    QFileInfoList root = QDir::drives();
    if(root.size() == 1 && root[0].filePath() == QString("/")){
        root = QDir::root().entryInfoList();

    }
    return getFilesByQFileList(QString("root"), root);
}

bool FileSystem::isPathExist(const QString &path) {
    return QDir(path).exists();
}


QJsonDocument FileSystem::getFilesByPath(const QString& path)
{
    /*
     * Add your files info here
     * Note that FileInfo class has a method called toJson()
     */
    QDir dir(path);
    QFileInfoList filesList = dir.entryInfoList();
    return getFilesByQFileList(path, filesList);
}

QJsonDocument FileSystem::getFilesByQFileList(const QString& path, const QFileInfoList &fileList) {
    QJsonDocument result;
    QJsonArray jsonFilesArray;
    for(const QFileInfo& file: fileList){
        jsonFilesArray.append(FileInfo(file).toJson());
    }
    QJsonObject resultObject;
    resultObject.insert(QString("directory"),  path);
    resultObject.insert(QString("files"), jsonFilesArray);
    result.setObject(resultObject);
    return result;
}
