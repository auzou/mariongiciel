#ifndef SEARCHQUERY_H
#define SEARCHQUERY_H

#include "network/search.h"
#include "referencialdata.h"
#include "response.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

namespace mariongiciel::core {

enum SearchMod_E {
    _NORMAL_        = 0,
    _BY_COMMUNE_    = 1,
    _BY_RANGE_MAX_  = 2,
};

class SearchQuery : public QObject
{
    Q_OBJECT

    private :
        network::Search *search;
        network::SearchParam searchParam;
        SearchMod_E searchMod_e;
        QString currentDir;
        Filter *filter;

    private :
        void saveData(const QString &data) const;

    public :
        explicit SearchQuery(QObject *parent = nullptr);
        ~SearchQuery() noexcept;

    public :
        void runSearchQuery(const QString &filterName, const network::SearchParam &searchParam);

        void setMod(SearchMod_E searchMod_e);
        SearchMod_E getMod() const;

    private slots :
        void searchFinished(network::SearchContent, QString data);
};


class SearchByRangeMax : public QObject
{
    Q_OBJECT

    private :
        struct RangeInfo final {
            const int rangeMinMax = 1000;
            const int rangeMaxMax = 1149;
            const int jumpMax = 150;
            const int jumpMin = 0;
        } rangeInfo;

    private :
        const int waitingTime;
        int currentJump = rangeInfo.jumpMax;
        int searchNumber = -1;

    private :
        QTimer *requestTimer;
        network::Search *search;
        network::SearchParam searchParam;

    private :
        bool setRange();
        void initRange();

    public :
        explicit SearchByRangeMax(network::SearchParam searchParam, QObject *parent = nullptr);
        ~SearchByRangeMax() noexcept;

    signals :
        void stepFinished(const QString &data);
        void searchFinished(const QString &data);

};


class SearchByCommune : public QObject
{
    Q_OBJECT

    private :
        network::SearchParam searchParam;
        QString departement;
        QVector<QString> communeVector;
        int cursor;

    public :
        explicit SearchByCommune(network::SearchParam searchParam, QObject *parent = nullptr);
        ~SearchByCommune() noexcept;

    public :
        void run();

   signals :
        void stepFinished(const QString data);
        void subStepFinished(const QString data);
        void searchFinished();
};

} // END NAMESPACE mariongiciel::core

#endif // SEARCHQUERY_H
