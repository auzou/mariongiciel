#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <QByteArray>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileInfo>

#include "../global.h"
#include "iomanagement.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

namespace mariongiciel::core {

struct AccountData final
{
    //QString uId;
    QString key;
    QString id;
    //QString realms;
};

class Account : public QObject
{
    Q_OBJECT

    public :
        explicit Account(QObject *parent = nullptr);
        void createAccount(AccountData accoundData);
        AccountData getAccountData();
        ~Account() noexcept;
};

} // END NAMESPACE mariongiciel::core

#endif // ACCOUNT_H
