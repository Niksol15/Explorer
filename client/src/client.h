#include <QString>
#include <QTcpSocket>
#include <QList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "fileinfo.h"

class Client: public QObject{
    Q_OBJECT
    Q_PROPERTY(QList<QObject*> files READ files NOTIFY filesChanged);
    Q_PROPERTY(QString currentDir READ currentDir NOTIFY currentDirChanged);
    //Q_PROPERTY(bool isLoad READ isLoad NOTIFY isLoadChanged);
public:
    explicit Client(QObject* parent = nullptr);
    Q_INVOKABLE void sendRequest(const QString& request);
    Q_INVOKABLE void back();
    Q_INVOKABLE void home();
    Q_INVOKABLE void next(const QString& nextDir);
    QList<QObject*> files();
    QString currentDir();
    void processResponse(const QString& response);
signals:
    void filesChanged(const QList<QObject*>& fls);
    void currentDirChanged(const QString& dir);
private:
    QString m_currentDir;
    QList<QObject*> m_files;
};
