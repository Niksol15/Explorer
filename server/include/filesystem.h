#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QJsonDocument>
#include <QFileInfoList>



class FileSystem
{
public:
    FileSystem();

    QJsonDocument getRootFiles();

    QJsonDocument getFilesByPath(const QString& path);

    bool isPathExist(const QString& path);

private:
    QJsonDocument getFilesByQFileList(const QString& path, const QFileInfoList& fileList);
};

#endif // FILESYSTEM_H
