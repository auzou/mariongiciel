#ifndef REFERENCIAL_H
#define REFERENCIAL_H

#include "authentication.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

namespace  mariongiciel::core::network {

class Referencial : public QObject
{
    Q_OBJECT

    private :
        const QString baseUrl;
        QVector<QPair<QString, QString>> header;
        Authentication *auth;
        QString currentData;
        bool isWait;

    public :
        explicit Referencial(Authentication *auth, QObject *parent = nullptr);
        void setHeader();
        void runReferencial(const QString &refName);
        ~Referencial() noexcept;

    signals :
        void referencialFinished(QString);
        void referencialError(QString);
};

} // END NAMESPACE mariongiciel::core::network

#endif // REFERENCIAL_H
