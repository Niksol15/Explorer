#ifndef FILE_INFO_H
#define FILE_INFO_H

#include <QString>
#include <QFileInfo>
#include <QJsonObject>

#include "file_type.h"

class FileInfo
{
public:
    FileInfo(const QFileInfo& fileInfo);

    QJsonObject toJson(); 

private:
    QString name;

    FileType type;

    bool isHidden;

    bool isReadable;
};

#endif // FILE_INFO_H
