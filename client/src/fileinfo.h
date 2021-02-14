#ifndef FILEINFO_H
#define FILEINFO_H

#include <QObject>
#include <QString>
#include <QJsonObject>
#include <QJsonValue>

class FileInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString fileType READ fileType NOTIFY fileTypeChanged)
    Q_PROPERTY(bool isHidden READ isHidden NOTIFY isHiddenChanged)
    Q_PROPERTY(bool isReadable READ isReadable NOTIFY isReadable)
public:
    explicit FileInfo(QObject *parent = nullptr);
    explicit FileInfo(const QJsonValue& json, QObject *parent = nullptr);
    explicit FileInfo(const QJsonObject& jsonObj, QObject *parent = nullptr);
    QString name();
    QString fileType();
    bool isHidden();
    bool isReadable();
signals:
    void nameChanged(const QString& nm);
    void fileTypeChanged(const QString& flyp);
    void isHiddenChanged(bool hidden);
    void isReadable(bool readable);
private:
    QString m_name;
    bool m_isHidden;
    bool m_isReadable;
    QString m_fileType;
};



#endif // FILEINFO_H
