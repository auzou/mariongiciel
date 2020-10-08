#include "searchquery.h"

void mariongiciel::core::SearchQuery::saveData(const QString &data) const
{
    SearchResponse response;
    response.setPath(this->currentDir);
    response.cutSearchResponse(data);
    response.runConversionProcess();
}


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
        {
            SearchByRangeMax *searchByRangMax = new SearchByRangeMax(this->searchParam, this);
            QObject::connect(searchByRangMax, &SearchByRangeMax::stepFinished, [this](QString data)->void {
                this->saveData(data);
            });

            QObject::connect(searchByRangMax, &SearchByRangeMax::searchFinished, [searchByRangMax]()->void {
                searchByRangMax->deleteLater();
            });
        }
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
    Q_UNUSED(content);
    this->saveData(data);
}

bool mariongiciel::core::SearchByRangeMax::setRange()
{
    if((this->searchParam.rangeMax >= this->searchNumber))
    {
        return false;
    }

    if(this->searchNumber == this->rangeInfo.rangeMaxMax)
    {
        if((this->searchParam.rangeMax + this->currentJump) >= this->rangeInfo.rangeMinMax)
        {
            if((this->searchParam.rangeMax + 1) == this->rangeInfo.rangeMinMax)
            {
                this->currentJump = this->rangeInfo.jumpMax;
            } else {
                this->currentJump = (this->rangeInfo.rangeMinMax - this->searchParam.rangeMax - 1);
            }
        }

        this->searchParam.rangeMin = this->searchParam.rangeMax + 1;
        this->searchParam.rangeMax += this->currentJump;

        return true;

    } else {

        if((this->searchParam.rangeMax + this->currentJump) > this->searchNumber)
        {
            this->currentJump = this->searchNumber - this->searchParam.rangeMax;
        }

        this->searchParam.rangeMin = this->searchParam.rangeMax + 1;
        this->searchParam.rangeMax += this->currentJump;
        return true;
    }

    return false;
}

void mariongiciel::core::SearchByRangeMax::initRange()
{
    this->searchParam.rangeMin = 0;

    if(this->searchNumber >= this->rangeInfo.jumpMax)
    {
        this->searchParam.rangeMax = this->rangeInfo.jumpMax - 1;
    } else {
        this->searchParam.rangeMax = this->searchNumber;
    }
}

mariongiciel::core::SearchByRangeMax::SearchByRangeMax(
                                                        network::SearchParam searchParam,
                                                                         QObject *parent
                                                       )
    : QObject(parent),
      waitingTime(int(1000))
{
    this->requestTimer = new QTimer(this);

    this->search = new network::Search(this);
    this->searchParam = searchParam;

    // first search by default values
    // get content struct
    this->searchParam.rangeMin = -1;
    this->searchParam.rangeMax = -1;

    this->requestTimer->start();

    QObject::connect(this->search, &network::Search::searchError, [this]()->void {
        this->requestTimer->start(this->waitingTime);
        // abort or continue ???
        /*
        if(this->searchNumber < this->searchParam.rangeMax)
        {
            this->requestTimer->stop();
        }
        */
    });

    QObject::connect(this->search, &network::Search::searchFinished, [this]
                     (network::SearchContent content, QString data)->void {
        // init searchNumber content -> max search
        if(this->searchNumber == -1)
        {
            if(content.maxLenght.toInt() < this->rangeInfo.rangeMaxMax)
            {
                this->searchNumber = content.maxLenght.toInt();
            } else {
                this->searchNumber = this->rangeInfo.rangeMaxMax;
            }

            qDebug()<< QString::number(this->searchNumber);
            qDebug()<< content.maxLenght;

            this->initRange();
            this->requestTimer->start();
        } else {
            if(this->setRange())
            {
                emit stepFinished(data);
                this->requestTimer->start(this->waitingTime);
            } else {
                emit searchFinished();
                this->requestTimer->stop();
            }
        }
    });

    QObject::connect(this->requestTimer, &QTimer::timeout, [this]()->void {
        this->search->runSearch(this->searchParam);
        this->requestTimer->stop();
    });
}

mariongiciel::core::SearchByRangeMax::~SearchByRangeMax() noexcept
{

}

