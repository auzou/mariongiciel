#ifndef REQUEST_NETWORK_H
#define REQUEST_NETWORK_H
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSslConfiguration>

#ifdef QT_DEBUG
#include <QDebug>
#endif

namespace mariongiciel::core::network {

class Request : public QObject
{
    Q_OBJECT

    private :
        QNetworkAccessManager *requestManager;

    public :
        explicit Request(QObject *parent = nullptr);
        void sendRequest(QNetworkAccessManager::Operation operation, QString url, QVector<QPair<QString,QString>> header, QVector<QPair<QString, QString>> param);
        ~Request() noexcept;

    signals :
        void requestFinished(QString content, QString data);
        void requestError(QString data);
};

/*
class RequestBase : QObject
{
    private :
        QNetworkAccessManager *requestManager;
        QString url;
        QVector<QMap<QString, QString>> headers;
        QUrlParam param;
        QNetworkAccessManager::Operation operation;

    public :
        explicit RequestBase(QObject  *parent = nullptr);
        ~RequestBase() noexcept;

    public :

};
*/

} // END NAMESPACE mariongiciel::core::network

#endif // REQUEST_NETWORK_H
