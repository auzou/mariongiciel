#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QLineEdit>
#include <QRadioButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QSpinBox>
#include <QLabel>
#include <QDateTime>
#include <QGroupBox>
#include <QCompleter>

#include "dropdown/dropdown.h"
#include "searchparammanager.h"
#include "../core/referencialdata.h"
#include "../core/searchquery.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

namespace mariongiciel::gui {

class SearchWidget : public QWidget
{
    Q_OBJECT

    private :
        QScrollArea *scrollArea;
        SearchParamManager *searchParamManager;

    private :
        mariongiciel::core::SearchQuery *searchQuery;
        mariongiciel::core::network::SearchParam searchParam;

    public :
        explicit SearchWidget(QWidget * parent = nullptr);
        void refreshMainWidget();
        QWidget *getMainWidget();
        ~SearchWidget() noexcept;


    public :
        QWidget *getRangeWidget(QWidget *mainWidget);
        QWidget *getSortWidget(QWidget *mainWidget);
        QWidget *getDomaineWidget(QWidget *mainWidget);
        QWidget *getcodeRomeWidget(QWidget *mainWidget);
        QWidget *getThemeWidget(QWidget *mainWidget);
        QWidget *getAppellationWidget(QWidget *mainWidget);
        QWidget *getSecteurActiviteWidget(QWidget *mainWidget);
        QWidget *getExperienceWidget(QWidget *mainWidget); // string 1 -> 2 -> 3
        QWidget *getTypeContratWidget(QWidget *mainWidget); // string cdd,cdi
        QWidget *getNatureContratWidget(QWidget *mainWidget); // not implemented
        QWidget *getOrigineOffreWidget(QWidget *mainWidget); // 1 -> pole emploi 2-> partenaire
        QWidget *getQualificationWidget(QWidget *mainWidget); // 0 -> non cadre 9 -> cadre
        QWidget *getTempsPleinWidget(QWidget *mainWidget); // true false
        QWidget *getCommuneWidget(QWidget *mainWidget); // not implemented
        QWidget *getDistanceWidget(QWidget *mainWidget); // default 10
        QWidget *getDepartementWidget(QWidget *mainWidget); // departement (94)
        QWidget *getInclureLimitrophesWidget(QWidget *mainWidget); // Inclure les départements limitrophes dans la recherche
        QWidget *getRegionWidget(QWidget *mainWidget); // not implemented
        QWidget *getPaysContinentWidget(QWidget *mainWidget);// not implemented
        QWidget *getNiveauFormationWidget(QWidget *mainWidget); // not implemented
        QWidget *getPermisWidget(QWidget *mainWidget); // not implemented
        QWidget *getMotsClesWidget(QWidget *mainWidget); // not implemented
        QWidget *getSalaireMinWidget(QWidget *mainWidget);// not implemented
        QWidget *getPeriodeSalaireWidget(QWidget *mainWidget);// not implemented M → Mensuel A → Annuel H → Horaire C → Cachet
        QWidget *getAccesTravailleurHandicapeWidget(QWidget *mainWidget); // not implemented
        QWidget *getOffresMrsWidget(QWidget *mainWidget); // not implemented
        QWidget *getGrandDomaineWidget(QWidget *mainWidget); // not implemented
        QWidget *getExperienceExigenceWidget(QWidget *mainWidget); //not implemented
        QWidget *getPublieeDepuisWidget(QWidget *mainWidget);//not implemented
        QWidget *getMinCreationDateWidget(QWidget *mainWidget); // not implemented Norme ISO-8601 (YYYY-MM-DDTHH:MM:SSZ)
        QWidget *getMaxCreationDateWidget(QWidget *mainWidget);// not implemented Norme ISO-8601 (YYYY-MM-DDTHH:MM:SSZ)
        QWidget *getRunSearchWidget(QWidget *mainWidget);
};

} // END NAMESPACE mariongiciel::gui

#endif // SEARCHWIDGET_H
