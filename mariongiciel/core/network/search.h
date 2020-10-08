#ifndef SEARCH_NETWORK_H
#define SEARCH_NETWORK_H

#include "authentication.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

namespace mariongiciel::core::network {

struct SearchParam final
{
    int rangeMin = -1; // string rangeMin-rangeMax
    int rangeMax = -1; // string rangeMin-rangeMax
    int sort = -1; // string 0 -> 1 -> 2
    QString domaine = QString(); // not implemented
    QString codeROME = QString(); // not implemented
    QString theme = QString(); // not implemented
    QString appellation = QString(); // not implemented
    QString secteurActivite; // not implemented
    int experience = -1; // string 1 -> 2 -> 3
    QString typeContrat; // string cdd,cdi
    QString natureContrat; // not implemented
    int origineOffre = -1; // 1 -> pole emploi 2-> partenaire
    QString qualification = ""; // 0 -> non cadre 9 -> cadre
    QString tempsPlein = QString(); // true false
    QString commune = QString(); // not implemented
    int distance = -1; // default 10
    QString departement = QString(); // departement (94)
    QString inclureLimitrophes = QString(); // Inclure les départements limitrophes dans la recherche
    QString region; // not implemented
    QString paysContinent;// not implemented
    QString niveauFormation; // not implemented
    QString permis; // not implemented
    QString motsCles; // not implemented
    double salaireMin = -1;// not implemented
    QString periodeSalaire;// not implemented M → Mensuel A → Annuel H → Horaire C → Cachet
    QString accesTravailleurHandicape = QString(); // not implemented
    QString offresMRS = QString(); // not implemented
    QString grandDomaine; // not implemented
    QString experienceExigence; //not implemented
    int publieeDepuis = -1;//not implemented
    QDateTime minCreationDate; // not implemented Norme ISO-8601 (YYYY-MM-DDTHH:MM:SSZ)
    QDateTime maxCreationDate;// not implemented Norme ISO-8601 (YYYY-MM-DDTHH:MM:SSZ)
};

struct SearchContent {
    QString begin;
    QString end;
    QString maxLenght;
};

class Search : public QObject
{
    Q_OBJECT

    private :
        const QString url;
        QVector<QPair<QString, QString>> header;
        QVector<QPair<QString, QString>> getSearchParam(SearchParam searchParam);
        Authentication *auth;
        SearchParam searchParam;
        bool isWait;

     public :
        explicit Search(QObject *parent = nullptr);
        void setHeader();
        void runSearch();
        void runSearch(SearchParam searchParam);
        ~Search() noexcept;

    signals :
        void searchFinished(SearchContent searchContent, QString data);
        void searchError(QString);
};

} // END NAMESPACE mariongiciel::core::network

#endif // SEARCH_NETWORK_H
