#include "searchquery.h"

void mariongiciel::core::SearchQuery::saveData(const QString &data) const
{
    SearchResponse response(this->filter);
    response.setPath(this->currentDir);
    response.cutSearchResponse(data);
}


mariongiciel::core::SearchQuery::SearchQuery(QObject *parent)
    : QObject(parent),
      search(new network::Search(this)),
      searchMod_e(SearchMod_E::_NORMAL_)
{
    this->filter = new Filter(this);
    QObject::connect(this->search, &network::Search::searchFinished, this, &SearchQuery::searchFinished);
}

mariongiciel::core::SearchQuery::~SearchQuery() noexcept
{

}


void mariongiciel::core::SearchQuery::runSearchQuery(const QString &filterName, const network::SearchParam &searchParam)
{
    this->filter->setFilter(filterName);

    this->searchParam = searchParam;
    this->currentDir = QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd_hh-mm-ss");
    switch(this->searchMod_e)
    {
        case SearchMod_E::_NORMAL_ :
            this->search->runSearch(this->searchParam);
            QObject::connect(this->search, &mariongiciel::core::network::Search::searchError,[this]()->void {
                this->search->runSearch(this->searchParam);
            });
        break;
        case SearchMod_E::_BY_COMMUNE_ :
        {
            if(!this->searchParam.departement.isEmpty())
            {
                SearchByCommune *searchByCommun = new SearchByCommune(this->searchParam, this);
                QObject::connect(searchByCommun, &SearchByCommune::subStepFinished, [this](const QString &data)->void {
                   this->saveData(data);
                });
                QObject::connect(searchByCommun, &SearchByCommune::stepFinished, [this](const QString &data)->void {
                   this->saveData(data);
                });
                QObject::connect(searchByCommun, &SearchByCommune::searchFinished, [this, searchByCommun]()->void {
                   searchByCommun->deleteLater();
                    emit searchQueryFinished();
                });
                searchByCommun->run();
            }
        }
        break;
        case SearchMod_E::_BY_RANGE_MAX_ :
        {
            SearchByRangeMax *searchByRangMax = new SearchByRangeMax(this->searchParam, this);
            QObject::connect(searchByRangMax, &SearchByRangeMax::stepFinished, [this](const QString &data)->void {
                this->saveData(data);
            });

            QObject::connect(searchByRangMax, &SearchByRangeMax::searchFinished, [this, searchByRangMax](const QString &data)->void {
                this->saveData(data);
                searchByRangMax->deleteLater();
                emit searchQueryFinished();
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

QString mariongiciel::core::SearchQuery::getCurrentDir() const
{
    return this->currentDir;
}

void mariongiciel::core::SearchQuery::searchFinished(network::SearchContent content, QString data)
{
    Q_UNUSED(content)
    this->saveData(data);
    emit searchQueryFinished();
}

bool mariongiciel::core::SearchByRangeMax::setRange()
{
    if((this->searchParam.rangeMax >= this->searchNumber - 1))
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

        this->searchParam.rangeMin = this->searchParam.rangeMax;
        this->searchParam.rangeMax += this->currentJump;

        return true;

    } else {

        if((this->searchParam.rangeMax + this->currentJump) > this->searchNumber)
        {
            this->currentJump = this->searchNumber - this->searchParam.rangeMax - 1;
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
      waitingTime(int(500))
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

            this->initRange();
            this->requestTimer->start();
        } else {
            if(this->setRange())
            {
                emit stepFinished(data);
                this->requestTimer->start(this->waitingTime);
            } else {
                emit searchFinished(data);
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

mariongiciel::core::SearchByCommune::SearchByCommune(network::SearchParam searchParam, QObject *parent)
    : QObject(parent), searchParam(searchParam), cursor(0), waitingTime(350)
{
    this->timer = new QTimer(this);

    this->departement = searchParam.departement;
    this->searchParam.distance = 0;
    this->searchParam.departement = "";
    Referencial ref;
    auto refData = ref.getReferancial(Referencial_E::_COMMUNES_);
    for(auto &i : refData)
    {
        if(i["codeDepartement"] == this->departement)
        {
            this->communeVector.push_back(i["code"]);
        }
    }
    QObject::connect(this->timer, &QTimer::timeout, [this]()->void {
        this->timer->stop();
        this->run();
    });
}

mariongiciel::core::SearchByCommune::~SearchByCommune() noexcept
{

}

void mariongiciel::core::SearchByCommune::run()
{
    if(this->cursor < this->communeVector.size())
    {
        this->searchParam.commune = this->communeVector[this->cursor];
    } else {
         emit searchFinished();
    }
    SearchByRangeMax *searchByRangeMax = new SearchByRangeMax(this->searchParam, this);

    QObject::connect(searchByRangeMax, &SearchByRangeMax::stepFinished, [this](const QString &data)->void {
        emit subStepFinished(data);
    });

    QObject::connect(searchByRangeMax, &SearchByRangeMax::searchFinished, [this, searchByRangeMax](const QString &data)->void {
        emit stepFinished(data);
        searchByRangeMax->deleteLater();
        this->cursor++;
        this->timer->start(this->waitingTime);
    });
}


