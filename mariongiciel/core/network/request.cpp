#include "request.h"

/* ********* REQUEST ********* */

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
            qDebug()<<reply->rawHeader("Content-Range");
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

/* ********* REQUESTBASE ********* */

/* ********* CONSTRUCT/DESTRUCT ********* */
mariongiciel::core::network::RequestBase::RequestBase(QUrl url, QObject  *parent)
    : QObject(parent), url(url)
{
    this->requestManager = new QNetworkAccessManager(this);
    this->sslConfiguration.setProtocol(QSsl::TlsV1_2); // default
}

mariongiciel::core::network::RequestBase::RequestBase(QString url, QObject  *parent)
    : QObject(parent), url(url)
{
    this->requestManager = new QNetworkAccessManager(this);
    this->sslConfiguration.setProtocol(QSsl::TlsV1_2); // default
}

mariongiciel::core::network::RequestBase::~RequestBase() noexcept
{

}

/* ********* ACCESSOR ********* */

void mariongiciel::core::network::RequestBase::setHeaders(QMap<QString, QString> headers)
{
    this->headers = headers;
}

const QMap<QString, QString> mariongiciel::core::network::RequestBase::setHeaders() const
{
    return this->headers;
}

void mariongiciel::core::network::RequestBase::setQueryParam(QUrlQuery queryParam)
{
    this->queryParam = queryParam;
}

void mariongiciel::core::network::RequestBase::setQueryParam(const QMap<QString, QString> &body)
{
    QUrlQuery queryParam;
    for(auto &i : body)
    {
        queryParam.addQueryItem(i, body.value(i));
    }
}


const QUrlQuery mariongiciel::core::network::RequestBase::getQueryParam() const
{
    return this->queryParam;
}

void mariongiciel::core::network::RequestBase::setSslConfiguration(QSslConfiguration sslConfiguration)
{
    this->sslConfiguration = sslConfiguration;
}

QSslConfiguration mariongiciel::core::network::RequestBase::getSslConfiguration() const
{
    return this->sslConfiguration;
}

/* ********* METHOD ********* */

void mariongiciel::core::network::RequestBase::sendRequest(QNetworkAccessManager::Operation operation)
{
    QNetworkRequest request(QUrl(this->url));

    for(auto &i : this->headers.keys())
    {
        request.setRawHeader(i.toUtf8(), this->headers.value(i).toUtf8());
    }

    request.setSslConfiguration(this->sslConfiguration);

    if(QNetworkAccessManager::Operation::PostOperation == operation)
    {
        this->requestManager->post(request, queryParam.query().toUtf8());
    }

    if(QNetworkAccessManager::Operation::GetOperation == operation)
    {
        request.setUrl(QUrl(request.url().toString()+queryParam.query().toUtf8()));
        this->requestManager->get(request);
    }

    QObject::connect(this->requestManager, &QNetworkAccessManager::sslErrors, [this](QNetworkReply *reply, const QList<QSslError> &errors)->void {
        emit requestBaseError(reply, errors);
    });

    QObject::connect(this->requestManager, &QNetworkAccessManager::finished, [this](QNetworkReply *reply)->void {
        if (reply->error())
        {
            emit requestBaseError(reply);
        } else {
            emit requestBaseFinished(reply);
        }
    });
}
