#ifndef AUTHENTICATION_NETWORK_H
#define AUTHENTICATION_NETWORK_H

/**
 * \file request.h
 * \brief ...
 * \author Auzou
 * \version ..
 *
 * ...
 *
 */

#include <QObject>
#include <QVector>
#include <QPair>
#include <QTimer>

#include "../account.h"
#include "request.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

/**
 * \namespace mariongiciel::core::network
 * \brief Network namespace
 *
 * Namespace that contains network functionality
 *
 */
namespace mariongiciel::core::network {

/**
 * \struct Session
 * \brief Represents a session
 *
 */
struct Session final
{
    int expire;
    bool valid;
    QString scope;
    QString tokenType;
    QString token;
};

/**
 * \class Authentication
 * \brief Represents an authentication to the API
 * This class cannot be instantiated
 * It is accessible from the network/global.h as a singleton
 */
class Authentication : public RequestBase
{
    Q_OBJECT

    private :
         /* my friend and in network/global.h and it's a template */
         template<typename T> friend struct Singleton;

    private :
        QTimer *refreshTimer;
        QVector<QPair<QString, QString>> body;
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
