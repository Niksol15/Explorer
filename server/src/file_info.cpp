//#include <QDir>

#include "file_info.h"

//extern Q_CORE_EXPORT int qt_ntfs_permission_lookup;

FileInfo::FileInfo(const QFileInfo& fileInfo): name(fileInfo.fileName()),
    type(fileInfo.isDir() ? DIRECTORY : FS_FILE),
    isHidden(fileInfo.isHidden()), isReadable(fileInfo.isReadable())
{
    //qt_ntfs_permission_lookup++;
}

QString FileTypeToQStr(FileType type){
    switch (type) {
        case DIRECTORY:
            return "DIRECTORY";
        case FS_FILE:
            return "FS_FILE";
    }
    return "Undefined";
}

QJsonObject FileInfo::toJson()
{
    QJsonObject result;
    /* example:
    {
        "isHidden": false,
        "isReadable": true,
        "name": "Qt",
        "type": "DIRECTORY"
    }*/
    // Convert all FileInfo fields to a JSON object. Use this object in response
    result.insert(QString("isHidden"), isHidden);
    result.insert(QString("isReadable"), isReadable);
    result.insert(QString("name"), name);
    result.insert(QString("type"), FileTypeToQStr(type));
    return result;
}
