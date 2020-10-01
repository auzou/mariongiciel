#include "request.h"


mariongiciel::core::network::Request::Request(QObject *parent)
    :QObject(parent)
{
    this->requestManager = new QNetworkAccessManager(this);
}

void mariongiciel::core::network::Request::sendRequest(
                                                       QNetworkAccessManager::Operation operation,
                                                       QString url,
                                                       QVector<QPair<QString,QString>> header,
                                                       QVector<QPair<QString, QString>> param
                                                       )
{
    QNetworkRequest request(QUrl(url.toUtf8()));

    for(auto &i : header)
    {
        request.setRawHeader(i.first.toUtf8(), i.second.toUtf8());
    }

    QUrlQuery queryParam;
    for(auto &i : param)
    {
        if(!i.second.isEmpty())
        {
            queryParam.addQueryItem(i.first, i.second);
        }
    }


    QObject::connect(this->requestManager, &QNetworkAccessManager::finished, [this](QNetworkReply *reply)->void {
        if (reply->error())
        {
#ifdef QT_DEBUG
            qDebug()<<"error";
#endif
            emit requestError(reply->errorString());
        } else{
            emit requestFinished(QString(reply->rawHeader("Content-Range")), reply->readAll());
        }
    });

    QObject::connect(this->requestManager, &QNetworkAccessManager::sslErrors, []()->void {
#ifdef QT_DEBUG
        qDebug()<<"ssl error";
#endif
    });

#ifdef QT_DEBUG
    qDebug()<< url <<queryParam.query().toUtf8();
#endif

    QSslConfiguration sslConfiguration(QSslConfiguration::defaultConfiguration());
    // ne gere pas v1_3
    sslConfiguration.setProtocol(QSsl::TlsV1_2);
    request.setSslConfiguration(sslConfiguration);
    // post
    if(operation == QNetworkAccessManager::Operation::PostOperation)
    {
        this->requestManager->post(request, queryParam.query().toUtf8());
    }
    // get
    if(operation == QNetworkAccessManager::Operation::GetOperation)
    {
        request.setUrl(QUrl(request.url().toString()+queryParam.query().toUtf8()));
        this->requestManager->get(request);
    }

#ifdef QT_DEBUG
    qDebug()
        << QSslSocket::supportsSsl()
        << QSslSocket::sslLibraryBuildVersionString()
        << QSslSocket::sslLibraryVersionString();
#endif

}
mariongiciel::core::network::Request::~Request() noexcept
{

}
