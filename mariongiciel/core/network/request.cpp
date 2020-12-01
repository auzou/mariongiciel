#include "request.h"

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

void mariongiciel::core::network::RequestBase::setHeader(const QMap<QString, QString> &header)
{
    this->header = header;
}

const QMap<QString, QString> &mariongiciel::core::network::RequestBase::getHeader() const
{
    return this->header;
}

void mariongiciel::core::network::RequestBase::setQueryParam(const QUrlQuery &queryParam)
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


const QUrlQuery &mariongiciel::core::network::RequestBase::getQueryParam() const
{
    return this->queryParam;
}

void mariongiciel::core::network::RequestBase::setSslConfiguration(const QSslConfiguration &sslConfiguration)
{
    this->sslConfiguration = sslConfiguration;
}

const QSslConfiguration &mariongiciel::core::network::RequestBase::getSslConfiguration() const
{
    return this->sslConfiguration;
}

/* ********* METHOD ********* */

void mariongiciel::core::network::RequestBase::sendRequest(QNetworkAccessManager::Operation operation)
{
    QNetworkRequest request(QUrl(this->url));

    for(auto &i : this->header.keys())
    {
        request.setRawHeader(i.toUtf8(), this->header.value(i).toUtf8());
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
