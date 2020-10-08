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


class Authentication : public QObject
{
    Q_OBJECT

    private :
        QTimer *refreshTimer;
        QString url;
        QVector<QPair<QString, QString>> header;
        QVector<QPair<QString, QString>> body;
        QString token;
        bool sessionValid;
        Session session;
        bool workInProgress;
        explicit Authentication(QObject *parent = nullptr);

        friend class AuthSingleton;

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

/*
template <class T> class Singleton {

    static Authentication* getInstance(QObject *parent = nullptr){
        static Authentication *instance = nullptr;
            if(instance == nullptr && parent != nullptr)
            {
                instance = new Authentication(parent);
            }
        return instance;
    };
};
*/


class AuthSingleton
{
    private :
        static Authentication* instance;

    public :
        static void initInstance(QObject *parent);
        static Authentication* GetInstance();
};

} // END NAMESPACE mariongiciel::core::network

#endif // AUTHENTICATION_NETWORK_H
