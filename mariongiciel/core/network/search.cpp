#include "search.h"

QVector<QPair<QString, QString>> mariongiciel::core::network::Search::getSearchParam(SearchParam searchParam)
{
    return  {
        {"range", (searchParam.rangeMin == -1 && searchParam.rangeMax == -1) ? ""
        : QString::number(searchParam.rangeMin) + "-" + QString::number(searchParam.rangeMax) },
        {"sort", (searchParam.sort == -1) ? "" : QString::number(searchParam.sort)},
        {"domaine", searchParam.domaine},
        {"codeRome", searchParam.codeROME},
        {"theme", searchParam.theme},
        {"appelation", searchParam.appellation},
        {"secteurActivite", searchParam.secteurActivite},
        {"experience", (searchParam.experience == -1) ? "" :QString::number(searchParam.experience)},
        {"typeContrat", searchParam.typeContrat},
        {"natureContrat", searchParam.natureContrat},
        {"origineOffre", (searchParam.origineOffre == -1) ? "" : QString::number(searchParam.origineOffre)},
        {"qualification", searchParam.qualification},
        {"tempsPlein", searchParam.tempsPlein},
        {"commune", searchParam.commune},
        {"distance", (searchParam.distance) ? "" : QString::number(searchParam.distance)},
        {"departement", searchParam.departement},
        {"inclureLimitrophes", searchParam.inclureLimitrophes},
        {"region", searchParam.region},
        {"paysContinent", searchParam.paysContinent},
        {"niveauFormation", searchParam.niveauFormation},
        {"permis", searchParam.permis},
        {"motsCles", searchParam.motsCles},
        {"salaireMin", (searchParam.salaireMin == -1) ? "" : QString::number(searchParam.salaireMin)},
        {"periodeSalaire", searchParam.periodeSalaire},
        {"accesTravailleurHandicape", searchParam.accesTravailleurHandicape},
        {"offresMRS", searchParam.offresMRS},
        {"grandDomaine", searchParam.grandDomaine},
        {"experienceExigence", searchParam.experienceExigence},
        {"publieeDepuis", (searchParam.publieeDepuis == -1) ?  "" : QString::number(searchParam.publieeDepuis)},
        {"minCreationDate", searchParam.minCreationDate.toString("YYYY-MM-DDTHH:MM:SSZ")},
        {"maxCreationDate", searchParam.maxCreationDate.toString("YYYY-MM-DDTHH:MM:SSZ")},
    };
}

mariongiciel::core::network::Search::Search(QObject *parent)
    : QObject(parent),
      url(QStringLiteral("https://api.emploi-store.fr/partenaire/offresdemploi/v2/offres/search?")),
      auth(AuthSingleton::GetInstance()),
      isWait(false)
{
    QObject::connect(this->auth, &mariongiciel::core::network::Authentication::authenticationFinished, [this]()->void {
        this->setHeader();
        if(isWait)
        {
            this->runSearch();
        }
    });
}

void mariongiciel::core::network::Search::setHeader()
{
    Session session = this->auth->getCurrentSession();
    this->header = {
              {"Content-Type","application/json"},
              {"Accept","application/json"},
              {"Authorization", session.tokenType+" "+session.token},
    };
}

void mariongiciel::core::network::Search::runSearch()
{
    if(!this->auth->getSessionValid() && !this->auth->getWorkInProgress())
    {
        isWait = true;
        this->auth->runAuth();
        return;
    } else {
        isWait = false;
        this->setHeader();
    }

    Request *request = new Request(this);

    request->sendRequest(QNetworkAccessManager::Operation::GetOperation,
                                                              this->url,
                                                           this->header,
                                  this->getSearchParam(this->searchParam)
    );

    QObject::connect(request, &Request::requestFinished, [request, this](QString content, QString data)->void {
        request->deleteLater();
        content.replace("offres", "");
        content.replace(" ", "");
        QStringList contentList = content.split("/");
        contentList.end();

        SearchContent searchContent;
        searchContent.maxLenght = contentList.constLast();

        contentList = contentList.first().split("-");
        searchContent.begin = contentList.first();
        searchContent.end = contentList.constLast();
        emit searchFinished(searchContent, data);
    });

    QObject::connect(request, &Request::requestError, [request, this](QString errorMsg)->void {
        request->deleteLater();
        emit searchError(errorMsg);
    });
}

void mariongiciel::core::network::Search::runSearch(SearchParam searchParam)
{
    this->searchParam = searchParam;
    this->runSearch();
}

mariongiciel::core::network::Search::~Search() noexcept
{

}
