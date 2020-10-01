#include "account.h"

mariongiciel::core::Account::Account(QObject *parent)
    : QObject(parent)
{
    using namespace mariongiciel::global::rcs;

    if(!this->fileExist() && !this->fileIsValid())
    {

    }
}

bool mariongiciel::core::Account::fileExist()
{
    using namespace mariongiciel::global::rcs;

    QFile file;
    if(file.exists(account::_ACCOUNT_+account::_DEFAULT_FORMAT_))
    {
        this->format = account::_DEFAULT_FORMAT_;
    } else if(file.exists(account::_ACCOUNT_+account::_COMPRESS_FORMAT_)) {
        this->format = account::_COMPRESS_FORMAT_;
    } else {
        file.close();
        return false;
    }

    this->location = account::_ACCOUNT_+this->format;
    file.close();
    return true;
}

bool mariongiciel::core::Account::fileIsValid()
{
    QString data = this->getFileData();
    if(data.isEmpty())
    {
        return false;
    }

    QJsonDocument document = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject mainObject = document.object();
    if(!mainObject["key"].isString() || !mainObject["id"].isString())
    {
        // create account
        return false;
    }

    return true;
}

QString mariongiciel::core::Account::getFileData()
{
    using namespace mariongiciel::global::rcs;

    QFile file(this->location);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        file.close();
        return "";
    }
    QByteArray data = file.readAll();

    if("."+QFileInfo(file).completeSuffix() == account::_COMPRESS_FORMAT_)
    {
        //add compress format
        //add AES256
        //add 7zip lib
    }
    file.close();
    return data;
}

void mariongiciel::core::Account::createAccount()
{
    //empty section
}

mariongiciel::core::AccountData mariongiciel::core::Account::getAccountData()
{
    QString data = this->getFileData();

    AccountData accountData;

    QJsonDocument document = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject mainObject = document.object();
    if(this->fileIsValid())
    {
        accountData.id = mainObject["id"].toString();
        accountData.key = mainObject["key"].toString();
    }
    return accountData;
}

mariongiciel::core::Account::~Account() noexcept
{

}
