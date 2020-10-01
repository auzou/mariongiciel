#include "searchquery.h"


mariongiciel::core::SearchQuery::SearchQuery(QObject *parent)
    : QObject(parent),
      search(new network::Search(this)),
      searchMod_e(SearchMod_E::_NORMAL_)
{
    QObject::connect(this->search, &network::Search::searchFinished, this, &SearchQuery::searchFinished);
}

mariongiciel::core::SearchQuery::~SearchQuery() noexcept
{

}


void mariongiciel::core::SearchQuery::runSearchQuery(const network::SearchParam &searchParam)
{
    this->searchParam = searchParam;
    this->currentDir = QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd_hh-mm-ss");
    switch(this->searchMod_e)
    {
        case SearchMod_E::_NORMAL_ :
            this->search->runSearch(this->searchParam);
        break;
        case SearchMod_E::_BY_COMMUNE_ :
        {

        }
        break;
        case SearchMod_E::_BY_RANGE_MAX_ :
            SearchByRangeMax *searchByRangMax = new SearchByRangeMax(this->searchParam, this->search, this);
        break;
    }
}

void mariongiciel::core::SearchQuery::setMod(SearchMod_E searchMod_e)
{
    this->searchMod_e = searchMod_e;
}

mariongiciel::core::SearchMod_E mariongiciel::core::SearchQuery::getMod() const
{
    return this->searchMod_e;
}

void mariongiciel::core::SearchQuery::searchFinished(network::SearchContent content, QString data)
{
    SearchResponse response;
    response.setPath(this->currentDir);
    response.cutSearchResponse(data);
    response.runConversionProcess();
    /*
    switch(this->searchMod_e)
    {
        case SearchMod_E::_NORMAL_ :
        {
            SearchResponse response;
            response.setPath(this->currentDir);
            response.cutSearchResponse(data);
            response.runConversionProcess();
        }
        break;
        case SearchMod_E::_BY_COMMUNE_ :

        break;
        case SearchMod_E::_BY_RANGE_MAX_ :

        break;
    }*/
}

void mariongiciel::core::SearchByRangeMax::setRange()
{
    if(this->searchParam.rangeMax <= this->maxRange)
    {
        this->searchParam.rangeMin += this->rangeJump;
        this->searchParam.rangeMax += this->rangeJump;

    } else {
        this->requestTimer->stop();
    }
}

mariongiciel::core::SearchByRangeMax::SearchByRangeMax(network::SearchParam searchParam,
                                                                network::Search *search,
                                                                         QObject *parent
                                                       )
    : QObject(parent),
      waitingTime(int(1000))
{
    this->requestTimer = new QTimer(this);
    this->requestTimer->setInterval(1000);

    this->search = search;
    this->searchParam = searchParam;
    this->searchParam.rangeMin = 0;
    this->searchParam.rangeMax = 49;

    this->requestTimer->start();

    QObject::connect(network::Search)

    QObject::connect(this->requestTimer, &QTimer::timeout, [this]()->void {
        this->search->runSearch(this->searchParam);
        this->setRange();
    });
}

mariongiciel::core::SearchByRangeMax::~SearchByRangeMax() noexcept
{

}

