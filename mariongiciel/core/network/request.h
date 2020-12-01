#ifndef REQUEST_NETWORK_H
#define REQUEST_NETWORK_H

/**
 * \file request.h
 * \brief ...
 * \author Auzou
 * \version ..
 *
 * ...
 *
 */

#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSslConfiguration>

#include <core/iomanagement.h>

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
 * \class RequestBase
 * \brief Base class to perform queries
 * \todo Replace @comment with the real comments
 */
class RequestBase : public QObject
{
    Q_OBJECT

    private :

        /**
         * @brief url
         */
        const QUrl url;

        /**
         * @brief headers
         */
        QMap<QString, QString> header;

        /**
         * @brief queryParam
         */
        QUrlQuery queryParam;

        /**
         * @brief sslConfiguration
         */
        QSslConfiguration sslConfiguration;

    private :
        QNetworkAccessManager *requestManager;

    public :

        /**
          * \fn explicit RequestBase(QUrl url, QObject  *parent = nullptr)
          * \brief ..
          *
          * \param QUrl url, QObject  *parent = nullptr
          * \return void
          */
        explicit RequestBase(QUrl url, QObject  *parent = nullptr);

        /**
          * \fn RequestBase(QString url, QObject  *parent = nullptr)
          * \brief ...
          *
          * \param QString url, QObject  *parent = nullptr
          * \return void
          */
        explicit RequestBase(QString url, QObject  *parent = nullptr);

        /**
          * \fn ~RequestBase() noexcept
          * \brief ..
          *
          * \param void
          * \return void
          */
        virtual ~RequestBase() noexcept;

    protected:
        /**
         * @brief setHeaders
         * @param headers
         */
        void setHeader(const QMap<QString, QString> &header);

        /**
         * @brief setHeaders
         * @return
         */
        const QMap<QString, QString> &getHeader() const;

        /**
         * @brief setQueryParam
         * @param queryParam
         */
        void setQueryParam(const QUrlQuery &queryParam);

        /**
         * @brief getQueryParam
         * @return
         */
        const QUrlQuery &getQueryParam() const;

        /**
         * @brief setQueryParam
         * @param body
         */
        void setQueryParam(const QMap<QString, QString> &body);

        /**
         * @brief setSslConfiguration
         * @param sslConfiguration
         */
        void setSslConfiguration(const QSslConfiguration &sslConfiguration);

        /**
         * @brief getSslConfiguration
         * @return
         */
        const QSslConfiguration &getSslConfiguration() const;

        /**
         * @brief sendRequest
         * @param operation
         */
        void sendRequest(QNetworkAccessManager::Operation operation);

    signals :

        /**
         * @brief requestBaseFinished
         * @param reply
         */
        void requestBaseFinished(QNetworkReply *reply);

        /**
         * @brief requestBaseError
         * @param reply
         */
        void requestBaseError(QNetworkReply *reply);

        /**
         * @brief requestBaseError
         * @param reply
         * @param errors
         */
        void requestBaseError(QNetworkReply *reply, const QList<QSslError> &errors);
};


} // END NAMESPACE mariongiciel::core::network

#endif // REQUEST_NETWORK_H
