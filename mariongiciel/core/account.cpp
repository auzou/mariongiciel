#include "account.h"

mariongiciel::core::Account::Account(QObject *parent)
    : QObject(parent)
{

}

void mariongiciel::core::Account::createAccount(AccountData accountData)
{
    QJsonDocument document;
    QJsonObject mainObject {
        {"key", accountData.key},
        {"id", accountData.id},
    };

    document.setObject(mainObject);
    FileManagement::write(document.toJson(), global::rcs::account::_ACCOUNT_);
}

mariongiciel::core::AccountData mariongiciel::core::Account::getAccountData()
{
    AccountData accountData;
    if(!FileManagement::isExist(global::rcs::account::_ACCOUNT_))
    {
        return accountData;
    }

    QJsonDocument document = QJsonDocument::fromJson(FileManagement::readFile(global::rcs::account::_ACCOUNT_).toUtf8());
    QJsonObject mainObject = document.object();
    accountData.id = mainObject["id"].toString();
    accountData.key = mainObject["key"].toString();

    return accountData;
}

mariongiciel::core::Account::~Account() noexcept
{

}
