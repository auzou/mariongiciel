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

    public :
        explicit SearchQuery(QObject *parent = nullptr);
        ~SearchQuery() noexcept;

    public :
        void runSearchQuery(const network::SearchParam &searchParam);

        void setMod(SearchMod_E searchMod_e);
        SearchMod_E getMod() const;

    private slots :
        void searchFinished(network::SearchContent, QString data);
};

class SearchByRangeMax : public QObject
{
    Q_OBJECT

    private :
        const int waitingTime = 1000;
        const int maxRange = 1149;
        const int rangeJump = 50;
        QTimer *requestTimer;
        network::Search *search;
        network::SearchParam searchParam;

    private :
        void setRange();

    public :
        explicit SearchByRangeMax(network::SearchParam searchParam, network::Search *search, QObject *parent = nullptr);
        ~SearchByRangeMax() noexcept;

};

} // END NAMESPACE mariongiciel::core

#endif // SEARCHQUERY_H
