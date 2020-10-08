#include "referencial.h"

mariongiciel::core::network::Referencial::Referencial(Authentication *auth, QObject *parent)
    : QObject(parent),
      baseUrl(QStringLiteral("https://api.emploi-store.fr/partenaire/offresdemploi/v2/referentiel/")),
      auth(auth),
      isWait(false)
{
    QObject::connect(this->auth, &mariongiciel::core::network::Authentication::authenticationFinished, [this]()->void {
        this->setHeader();
        if(this->isWait)
        {
            this->runReferencial(this->currentData);
        }
    });
}

void mariongiciel::core::network::Referencial::setHeader()
{
    Session session = this->auth->getCurrentSession();
    this->header = {
              {"Content-Type","application/json"},
              {"Accept","application/json"},
              {"Authorization", session.tokenType+" "+session.token},
    };
}

void mariongiciel::core::network::Referencial::runReferencial(const QString &refName)
{

    if(!this->auth->getSessionValid() && !this->auth->getWorkInProgress())
    {
        isWait = true;
        this->currentData = refName;
        this->auth->runAuth();
        return;
    } else {
        isWait = false;
        this->setHeader();
    }

    Request *request = new Request(this);

    request->sendRequest(QNetworkAccessManager::Operation::GetOperation,
                                                  this->baseUrl+refName,
                                                           this->header,
                                                                      {}
    );

    QObject::connect(request, &Request::requestFinished, [request, this](QString content, QString data)->void {
        Q_UNUSED(content)
        request->deleteLater();
        emit referencialFinished(data);
    });

    QObject::connect(request, &Request::requestError, [request, this](QString errorMsg)->void {
        request->deleteLater();
        emit referencialError(errorMsg);
    });
}

mariongiciel::core::network::Referencial::~Referencial() noexcept
{

}
