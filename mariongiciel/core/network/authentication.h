#ifndef AUTHENTICATION_NETWORK_H
#define AUTHENTICATION_NETWORK_H
#include <QObject>
#include <QVector>
#include <QPair>
#include <QTimer>

#include "../account.h"
#include "request.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

namespace mariongiciel::core::network {

struct Session final
{
    QString scope;
    int expire;
    QString tokenType;
    QString token;
};


class Authentication : public RequestBase
{
    Q_OBJECT

    private :
         template<typename T> friend struct Singleton;

    private :
        QTimer *refreshTimer;
        QVector<QPair<QString, QString>> body;
        QString token;
        bool sessionValid;
        Session session;
        bool workInProgress;
        explicit Authentication(RequestBase *parent = nullptr);

    public :
        void runAuth();
        bool getSessionValid() const;
        bool getWorkInProgress() const;
        void refreshAccount();
        Session getCurrentSession() const;
        ~Authentication() noexcept;

    signals :
        void authenticationFinished();
};

} // END NAMESPACE mariongiciel::core::network

#endif // AUTHENTICATION_NETWORK_H
