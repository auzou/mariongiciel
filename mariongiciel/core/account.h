#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <QByteArray>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileInfo>

#include "../global.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

namespace mariongiciel::core {

struct AccountData final
{
    QString uId;
    QString key;
    QString id;
    QString realms;
};

class Account : public QObject
{
    Q_OBJECT

    private :
       QString location;
       QString format;

    public :
        explicit Account(QObject *parent = nullptr);
        bool fileExist();
        bool fileIsValid();
        QString getFileData();
        void createAccount();
        AccountData getAccountData();
        ~Account() noexcept;
};

} // END NAMESPACE mariongiciel::core

#endif // ACCOUNT_H
