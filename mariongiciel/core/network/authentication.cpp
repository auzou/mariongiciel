#include "authentication.h"

mariongiciel::core::network::Authentication::Authentication(QObject *parent)
    : QObject(parent), workInProgress(false)
{
    this->sessionValid = false;

    this->url = "https://entreprise.pole-emploi.fr/connexion/oauth2/access_token?";
    this->header = {
        {"Content-Type", "application/x-www-form-urlencoded"},
    };

    this->refreshAccount();

    this->refreshTimer = new QTimer(this);
    // 1490000
    this->refreshTimer->setInterval(1490000);
    // token expire (25min)
    QObject::connect(this->refreshTimer, &QTimer::timeout, [this]()->void {
        // refresh token
        this->sessionValid = false;
        this->refreshTimer->stop();
    });
}

void mariongiciel::core::network::Authentication::refreshAccount()
{
    mariongiciel::core::Account account;
    mariongiciel::core::AccountData accountData = account.getAccountData();
    this->body = {
        {"realm", "/partenaire"},
        {"grant_type", "client_credentials"},
        {"client_id", accountData.id},
        {"client_secret", accountData.key},
        {"scope", "api_offresdemploiv2%20application_"+accountData.id+"%20o2dsoffre"},
    };
}

bool mariongiciel::core::network::Authentication::getSessionValid() const
{
    return this->sessionValid;
}

bool mariongiciel::core::network::Authentication::getWorkInProgress() const
{
    return workInProgress;
}

void mariongiciel::core::network::Authentication::runAuth()
{
    if(workInProgress)
    {
        return;
    }

    workInProgress = true;

    Request *request = new Request(this);
    request->sendRequest(QNetworkAccessManager::Operation::PostOperation, this->url, this->header, this->body);

    QObject::connect(request, &Request::requestFinished, [this](QString content, QString data)->void {
        Q_UNUSED(content)
        QJsonDocument document = QJsonDocument::fromJson(data.toUtf8());
        QJsonObject mainObject = document.object();

        this->session.scope = mainObject["scope"].toString();
        this->session.expire = mainObject["expires_in"].toInt();
        this->session.token = mainObject["access_token"].toString();
        this->session.tokenType = mainObject["token_type"].toString();

        this->refreshTimer->start();

        if(session.scope.isEmpty()
                || QString::number(session.expire).isEmpty()
                || session.token.isEmpty()
                || session.tokenType.isEmpty())
        {
            this->sessionValid = false;
        } else {
            this->sessionValid = true;
            this->workInProgress = false;
            emit authenticationFinished();
        }
    });
}

mariongiciel::core::network::Session mariongiciel::core::network::Authentication::getCurrentSession() const
{
    return this->session;
}

mariongiciel::core::network::Authentication::~Authentication() noexcept
{

}



mariongiciel::core::network::Authentication* mariongiciel::core::network::AuthSingleton::instance = nullptr;


void  mariongiciel::core::network::AuthSingleton::initInstance(QObject *parent)
{
    if(AuthSingleton::instance == nullptr)
    {
        AuthSingleton::instance = new Authentication(parent);
    }
}

mariongiciel::core::network::Authentication*  mariongiciel::core::network::AuthSingleton::GetInstance()
{
    return AuthSingleton::instance;
}
