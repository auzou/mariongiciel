#include "searchwidget.h"


mariongiciel::gui::SearchWidget::SearchWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setObjectName("search-widget");

    this->scrollArea = new QScrollArea(this);
    this->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->scrollArea->setVerticalScrollBarPolicy (Qt::ScrollBarAsNeeded);
    this->scrollArea->setWidgetResizable (true);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    this->searchParamManager = new SearchParamManager(this);
    this->searchMod_E = mariongiciel::core::SearchMod_E::_NORMAL_;
    QGroupBox *modBox = new QGroupBox(QObject::tr("Mode de recherche"), this);
    QVBoxLayout *modLayout = new QVBoxLayout(modBox);
    QRadioButton *modNormal = new QRadioButton(QObject::tr("Recherche uniquement via les paramètre"), this);
    QObject::connect(modNormal, &QRadioButton::clicked, [this]()->void {
        this->searchMod_E = mariongiciel::core::SearchMod_E::_NORMAL_;
    });

    QRadioButton *modCommune = new QRadioButton(QObject::tr("Recherche dans chaque communes"), this);
    QObject::connect(modCommune, &QRadioButton::clicked, [this]()->void {
         this->searchMod_E = mariongiciel::core::SearchMod_E::_BY_COMMUNE_;
    });

    QRadioButton *modRangeMax = new QRadioButton(QObject::tr("Recherche de 0 à 1149"), this);
    QObject::connect(modRangeMax, &QRadioButton::clicked, [this]()->void {
         this->searchMod_E = mariongiciel::core::SearchMod_E::_BY_RANGE_MAX_;
    });

    modLayout->addWidget(modNormal);
    modLayout->addWidget(modCommune);
    modLayout->addWidget(modRangeMax);
    modLayout->addWidget(this->getRunSearchWidget(this));

    modBox->setLayout(modLayout);

    QHBoxLayout *filterLayout = new QHBoxLayout();

    QPushButton *filterButton = new QPushButton(QObject::tr("Filtre"), this);
    filterLayout->addWidget(filterButton);

    QLabel *filterLabel = new QLabel(QObject::tr("<center>Aucun filtre</center>"), this);
    filterLayout->addWidget(filterLabel);
    filterLabel->setStyleSheet("font-size: smaller; color:red;");

    QObject::connect(filterButton, &QPushButton::clicked, [this, filterLabel]()->void {
           FilterDialog filterDialog(filterLabel->text());
           filterDialog.exec();
           this->currentFilterPath = filterDialog.getFilterName();
           if(this->currentFilterPath == "Aucun filtre")
           {
                this->currentFilterPath = "";
               filterLabel->setText(QString("<center>" + this->currentFilterPath + "</center>"));
               filterLabel->setStyleSheet("color:red");
           } else {
               filterLabel->setText(QString("<center>" + this->currentFilterPath + "</center>"));
               filterLabel->setStyleSheet("color:lime");
           }
    });

    mainLayout->addWidget(this->searchParamManager);
    mainLayout->addLayout(filterLayout);
    mainLayout->addWidget(modBox);
    mainLayout->addWidget(this->scrollArea);
    this->refreshMainWidget();
    this->setLayout(mainLayout);
}

void mariongiciel::gui::SearchWidget::refreshMainWidget()
{
    this->searchParam = mariongiciel::core::network::SearchParam();
    this->scrollArea->setWidget(this->getMainWidget());
}

QWidget *mariongiciel::gui::SearchWidget::getMainWidget()
{
    QWidget *mainWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);

    mainLayout->addWidget(this->getRangeWidget(mainWidget));
    mainLayout->addWidget(this->getSortWidget(mainWidget));
    mainLayout->addWidget(this->getDomaineWidget(mainWidget));
    mainLayout->addWidget(this->getcodeRomeWidget(mainWidget));
    mainLayout->addWidget(this->getThemeWidget(mainWidget));
    mainLayout->addWidget(this->getAppellationWidget(mainWidget));
    mainLayout->addWidget(this->getSecteurActiviteWidget(mainWidget));
    mainLayout->addWidget(this->getExperienceWidget(mainWidget));
    mainLayout->addWidget(this->getTypeContratWidget(mainWidget));
    mainLayout->addWidget(this->getNatureContratWidget(mainWidget));
    mainLayout->addWidget(this->getOrigineOffreWidget(mainWidget));
    mainLayout->addWidget(this->getQualificationWidget(mainWidget));
    mainLayout->addWidget(this->getTempsPleinWidget(mainWidget));
    //mainLayout->addWidget(this->getCommuneWidget(mainWidget));
    mainLayout->addWidget(this->getDistanceWidget(mainWidget));
    mainLayout->addWidget(this->getDepartementWidget(mainWidget));
    mainLayout->addWidget(this->getInclureLimitrophesWidget(mainWidget));
    mainLayout->addWidget(this->getRegionWidget(mainWidget));
    mainLayout->addWidget(this->getPaysContinentWidget(mainWidget));
    mainLayout->addWidget(this->getNiveauFormationWidget(mainWidget));
    mainLayout->addWidget(this->getPermisWidget(mainWidget));
    mainLayout->addWidget(this->getMotsClesWidget(mainWidget));
    mainLayout->addWidget(this->getSalaireMinWidget(mainWidget));
    mainLayout->addWidget(this->getPeriodeSalaireWidget(mainWidget));
    mainLayout->addWidget(this->getAccesTravailleurHandicapeWidget(mainWidget));
    mainLayout->addWidget(this->getOffresMrsWidget(mainWidget));
    mainLayout->addWidget(this->getGrandDomaineWidget(mainWidget));
    mainLayout->addWidget(this->getExperienceExigenceWidget(mainWidget));
    mainLayout->addWidget(this->getPublieeDepuisWidget(mainWidget));
    mainLayout->addWidget(this->getMinCreationDateWidget(mainWidget));
    mainLayout->addWidget(this->getMaxCreationDateWidget(mainWidget));

    mainWidget->setLayout(mainLayout);

    return mainWidget;
}

mariongiciel::gui::SearchWidget::~SearchWidget() noexcept
{

}

QWidget *mariongiciel::gui::SearchWidget::getRangeWidget(QWidget *mainWidget)
{
    QGroupBox *rangeWidget = new QGroupBox(QObject::tr("Pagination des données"), mainWidget);
    QHBoxLayout *mainLayout = new QHBoxLayout();

    QLabel *labelMin = new QLabel(QObject::tr("Plage minimal : "), rangeWidget);
    QSpinBox *rangeMin = new QSpinBox(rangeWidget);
    rangeMin->setMaximum(2000);
    QLabel *labelMax = new QLabel(QObject::tr("Plage maximal : "), rangeWidget);
    QSpinBox *rangeMax = new QSpinBox(rangeWidget);
    rangeMax->setMaximum(2000);

    mainLayout->addWidget(labelMin);
    mainLayout->addWidget(rangeMin);
    mainLayout->addWidget(labelMax);
    mainLayout->addWidget(rangeMax);

    rangeWidget->setLayout(mainLayout);

    QObject::connect(rangeMax, qOverload<int>(&QSpinBox::valueChanged), [rangeMax, this]()->void {
        this->searchParam.rangeMax = rangeMax->value();
    });

    QObject::connect(rangeMin, qOverload<int>(&QSpinBox::valueChanged), [rangeMin, this]()->void {
        this->searchParam.rangeMin = rangeMin->value();
    });

    return rangeWidget;
}

QWidget *mariongiciel::gui::SearchWidget::getSortWidget(QWidget *mainWidget)
{
    QGroupBox *sortWidget = new QGroupBox(QObject::tr("Tri des données"), mainWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(sortWidget);

    for(auto &i : {0, 1, 2, 3})
    {
        QString text;
        switch (i) {
            case 0 : text = QObject::tr(" → Tri par pertinence décroissante, distance croissante, date de création décroissante");
            break;
            case 1 : text = QObject::tr(" → Tri par date de création décroissant, pertinence décroissante, distance croissante");
            break;
            case 2 : text = QObject::tr(" → Tri par distance croissante, pertinence décroissante, date de création décroissante");
            break;
            default : text = QObject::tr(" → Défaut");
            break;
        }

        QHBoxLayout *sortLayout = new QHBoxLayout();
        sortLayout->setAlignment(Qt::AlignLeft);
        QRadioButton *sortButton = new QRadioButton(QString::number(i), sortWidget);

        QObject::connect(sortButton, &QRadioButton::clicked, [this, sortButton]()->void {
            if(sortButton->text().toInt() == 3) {
                this->searchParam.sort = -1;
            } else {
                this->searchParam.sort = sortButton->text().toInt();
            }
        });

        QLabel *sortLabel = new QLabel(text);

        sortLayout->addWidget(sortButton);
        sortLayout->addWidget(sortLabel);

        mainLayout->addLayout(sortLayout);
    }

    sortWidget->setLayout(mainLayout);

    return sortWidget;
}

QWidget *mariongiciel::gui::SearchWidget::getDomaineWidget(QWidget *mainWidget)
{
    QGroupBox *domaineWidget = new QGroupBox(QObject::tr("Domaines"), mainWidget);
    QHBoxLayout *domaineLayout = new QHBoxLayout();


    mariongiciel::core::Referencial ref;
    QStringList list;

    for(auto &i : ref.getReferancial(mariongiciel::core::Referencial_E::_DOMAINES_))
    {
        list.push_back(i["code"]+":"+i["libelle"]);
    }

    mariongiciel::core::ReferencialOutput refOut;

    DropDown *dropDown = new DropDown(QIcon(global::rcs::icon::_ACTION_), list, domaineWidget);

    domaineLayout->addWidget(dropDown);

    domaineWidget->setLayout(domaineLayout);

    QObject::connect(dropDown, &DropDown::textChanged, [this](const QString &text)->void {
        if(text.isEmpty())
        {
            this->searchParam.domaine = QString();
        } else {
            this->searchParam.domaine = text.split(":").constFirst();
        }
    });

    return domaineWidget;
}

QWidget *mariongiciel::gui::SearchWidget::getcodeRomeWidget(QWidget *mainWidget)
{
    QGroupBox *romeWidget = new QGroupBox(mainWidget);
    QVBoxLayout *romeLayout = new QVBoxLayout();
    QLabel *nameLabel = new QLabel(QObject::tr("Selection de 3 valeurs maximum"), romeWidget);

    romeLayout->addWidget(nameLabel);

    mariongiciel::core::Referencial ref;
    QStringList list;

    for(auto &i : ref.getReferancial(mariongiciel::core::Referencial_E::_METIERS_))
    {
        list.push_back(i["code"]+":"+i["libelle"]);
    }

    mariongiciel::core::ReferencialOutput refOut;

    DropDown *dropDown = new DropDown(QIcon(global::rcs::icon::_ACTION_), list, romeWidget);
    MultiSelectDropDown *multiDropDown = new MultiSelectDropDown(3, QIcon(global::rcs::icon::_REMOVE_), dropDown, romeWidget);

    romeLayout->addWidget(multiDropDown);

    QObject::connect(multiDropDown, &MultiSelectDropDown::selectChanged, [this]
                     (const QStringList &list)->void {
        if(list.isEmpty())
        {
            this->searchParam.codeROME = QString();
        } else {
            QString data;
            for(auto &i : list)
            {
                data += i.split(":").constFirst();
                if(i != list.constLast())
                {
                    data+=",";
                }
            }
            this->searchParam.codeROME = data;
        }
    });

    romeWidget->setLayout(romeLayout);

    return romeWidget;
}

QWidget *mariongiciel::gui::SearchWidget::getThemeWidget(QWidget *mainWidget)
{
    QGroupBox *themeWidget = new QGroupBox(QObject::tr("Thème"), mainWidget);
    QHBoxLayout *themeLayout = new QHBoxLayout(themeWidget);

    mariongiciel::core::Referencial ref;
    QStringList list;

    for(auto &i : ref.getReferancial(mariongiciel::core::Referencial_E::_THEMES_))
    {
        list.push_back(i["code"]+":"+i["libelle"]);
    }

    mariongiciel::core::ReferencialOutput refOut;

    DropDown *dropDown = new DropDown(QIcon(global::rcs::icon::_ACTION_), list, themeWidget);

    themeLayout->addWidget(dropDown);

    themeWidget->setLayout(themeLayout);

    QObject::connect(dropDown, &DropDown::textChanged, [this](const QString &text)->void {
        if(text.isEmpty())
        {
            this->searchParam.theme = QString();
        } else {
            this->searchParam.theme = text.split(":").constFirst();
        }
    });


    themeWidget->setLayout(themeLayout);

    return themeWidget;
}
QWidget *mariongiciel::gui::SearchWidget::getAppellationWidget(QWidget *mainWidget)
{
    QGroupBox *appellationWidget = new QGroupBox(QObject::tr("Appelation"), mainWidget);
    QHBoxLayout *appellationLayout = new QHBoxLayout(appellationWidget);


    mariongiciel::core::Referencial ref;
    QStringList list;

    for(auto &i : ref.getReferancial(mariongiciel::core::Referencial_E::_APPELLATIONS_))
    {
        list.push_back(i["code"]+":"+i["libelle"]);
    }

    mariongiciel::core::ReferencialOutput refOut;

    DropDown *dropDown = new DropDown(QIcon(global::rcs::icon::_ACTION_), list, appellationWidget);

    appellationLayout->addWidget(dropDown);

    appellationWidget->setLayout(appellationLayout);

    QObject::connect(dropDown, &DropDown::textChanged, [this](const QString &text)->void {
        if(text.isEmpty())
        {
            this->searchParam.appellation = QString();
        } else {
            this->searchParam.appellation = text.split(":").constFirst();
        }
    });

    appellationWidget->setLayout(appellationLayout);

    return appellationWidget;
}

QWidget *mariongiciel::gui::SearchWidget::getSecteurActiviteWidget(QWidget *mainWidget)
{
    QGroupBox *secteurActiviteWidget = new QGroupBox(QObject::tr("Secteurs d'activités"), mainWidget);
    QVBoxLayout *secteurActiviteLayout = new QVBoxLayout(secteurActiviteWidget);

    QLabel *nameLabel = new QLabel(QObject::tr("Selection de 2 valeurs maximum"), secteurActiviteWidget);
    secteurActiviteLayout->addWidget(nameLabel);

    mariongiciel::core::Referencial ref;
    QStringList list;

    for(auto &i : ref.getReferancial(mariongiciel::core::Referencial_E::_SECTEURS_ACTIVITES_))
    {
        list.push_back(i["code"]+":"+i["libelle"]);
    }

    mariongiciel::core::ReferencialOutput refOut;

    DropDown *dropDown = new DropDown(QIcon(global::rcs::icon::_ACTION_), list, secteurActiviteWidget );
    MultiSelectDropDown *multiDropDown = new MultiSelectDropDown(2, QIcon(global::rcs::icon::_REMOVE_), dropDown, secteurActiviteWidget);

    secteurActiviteLayout->addWidget(multiDropDown);

    QObject::connect(multiDropDown, &MultiSelectDropDown::selectChanged, [this]
                     (const QStringList &list)->void {
        if(list.isEmpty())
        {
            this->searchParam.secteurActivite = QString();
        } else {
            QString data;
            for(auto &i : list)
            {
                data += i.split(":").constFirst();
                if(i != list.constLast())
                {
                    data+=",";
                }
            }
            this->searchParam.secteurActivite = data;
        }
    });

    secteurActiviteWidget->setLayout(secteurActiviteLayout);

    return secteurActiviteWidget;
}
QWidget *mariongiciel::gui::SearchWidget::getExperienceWidget(QWidget *mainWidget)
{
    QGroupBox *experienceWidget = new QGroupBox(QObject::tr("Experience"), mainWidget);
    QVBoxLayout *experienceLayout = new QVBoxLayout(experienceWidget);

    for(auto &i : {0, 1, 2, 3})
    {
        QString text;
        switch (i) {
            case 0 : text = QObject::tr(" → Défaut");
            break;
            case 1 : text = QObject::tr(" → Moins d'un an d'expérience");
            break;
            case 2 : text = QObject::tr(" → De 1 à 3 ans d'expérience");
            break;
            case 3 : text = QObject::tr(" → Plus de 3 ans d'expérience");
            break;
        }

        QHBoxLayout *boxLayout = new QHBoxLayout();
        boxLayout->setAlignment(Qt::AlignLeft);
        QRadioButton *sortButton = new QRadioButton(QString::number(i), experienceWidget);

        QObject::connect(sortButton, &QRadioButton::clicked, [this, sortButton]()->void {
            if(sortButton->text().toInt() == 0) {
                this->searchParam.experience = -1;
            } else {
                this->searchParam.experience = sortButton->text().toInt();
            }
        });

        QLabel *sortLabel = new QLabel(text);

        boxLayout->addWidget(sortButton);
        boxLayout->addWidget(sortLabel);
        experienceLayout->addLayout(boxLayout);
    }


    experienceWidget->setLayout(experienceLayout);
    return experienceWidget;
}

QWidget *mariongiciel::gui::SearchWidget::getTypeContratWidget(QWidget *mainWidget) // string cdd,cdi
{
    QGroupBox *typeContratWidget = new QGroupBox(QObject::tr("Type Contrat"), mainWidget);
    QVBoxLayout *typeContratLayout = new QVBoxLayout(typeContratWidget);

    QLabel *nameLabel = new QLabel(QObject::tr("Selection de 10 valeurs maximum"), typeContratWidget);
    typeContratLayout->addWidget(nameLabel);

    mariongiciel::core::Referencial ref;
    QStringList list;

    for(auto &i : ref.getReferancial(mariongiciel::core::Referencial_E::_TYPES_CONTRATS_))
    {
        list.push_back(i["code"]+":"+i["libelle"]);
    }

    mariongiciel::core::ReferencialOutput refOut;

    DropDown *dropDown = new DropDown(QIcon(global::rcs::icon::_ACTION_), list, typeContratWidget);
    MultiSelectDropDown *multiDropDown = new MultiSelectDropDown(10, QIcon(global::rcs::icon::_REMOVE_), dropDown, typeContratWidget);

    typeContratLayout->addWidget(multiDropDown);

    QObject::connect(multiDropDown, &MultiSelectDropDown::selectChanged, [this]
                     (const QStringList &list)->void {
        if(list.isEmpty())
        {
            this->searchParam.typeContrat = QString();
        } else {
            QString data;
            for(auto &i : list)
            {
                data += i.split(":").constFirst();
                if(i != list.constLast())
                {
                    data+=",";
                }
            }
            this->searchParam.typeContrat = data;
        }
    });

    typeContratWidget->setLayout(typeContratLayout);

    return typeContratWidget;
}
QWidget *mariongiciel::gui::SearchWidget::getNatureContratWidget(QWidget *mainWidget) // not implemented
{
    QGroupBox *natureContratWidget = new QGroupBox(QObject::tr("Nature Contrat"), mainWidget);
    QHBoxLayout *natureContratLayout = new QHBoxLayout(natureContratWidget);

    mariongiciel::core::Referencial ref;
    QStringList list;

    for(auto &i : ref.getReferancial(mariongiciel::core::Referencial_E::_NATURES_CONTRATS_))
    {
        list.push_back(i["code"]+":"+i["libelle"]);
    }

    mariongiciel::core::ReferencialOutput refOut;

    DropDown *dropDown = new DropDown(QIcon(global::rcs::icon::_ACTION_), list, natureContratWidget);
    natureContratLayout->addWidget(dropDown);

    QObject::connect(dropDown, &DropDown::textChanged, [this](const QString &text)->void {
        if(text.isEmpty())
        {
            this->searchParam.natureContrat = QString();
        } else {
            this->searchParam.natureContrat = text.split(":").constFirst();
        }
    });

    natureContratWidget->setLayout(natureContratLayout);

    return natureContratWidget;
}

QWidget *mariongiciel::gui::SearchWidget::getOrigineOffreWidget(QWidget *mainWidget)// 1 -> pole emploi 2-> partenaire
{
    QGroupBox *origineOffreWidget = new QGroupBox(QObject::tr("Origine de l'offre"), mainWidget);
    QVBoxLayout *origineOffreLayout = new QVBoxLayout(origineOffreWidget);

    for(auto &i : {0, 1, 2})
    {
        QString text;
        switch (i) {
            case 0 : text = QObject::tr(" → Défaut");
            break;
            case 1 : text = QObject::tr(" → Pôle emploi");
            break;
            case 2 : text = QObject::tr(" → Partenaire");
            break;
        }

        QHBoxLayout *boxLayout = new QHBoxLayout();
        boxLayout->setAlignment(Qt::AlignLeft);
        QRadioButton *sortButton = new QRadioButton(QString::number(i), origineOffreWidget);

        QObject::connect(sortButton, &QRadioButton::clicked, [this, sortButton]()->void {
            if(sortButton->text().toInt() == 0) {
                this->searchParam.origineOffre = -1;
            } else {
                this->searchParam.origineOffre = sortButton->text().toInt();
            }
        });

        QLabel *sortLabel = new QLabel(text);

        boxLayout->addWidget(sortButton);
        boxLayout->addWidget(sortLabel);
        origineOffreLayout->addLayout(boxLayout);
    }

    origineOffreWidget->setLayout(origineOffreLayout);

    return origineOffreWidget;
}
QWidget *mariongiciel::gui::SearchWidget::getQualificationWidget(QWidget *mainWidget)// 0 -> non cadre 9 -> cadre
{
    QGroupBox *qualificationWidget = new QGroupBox(QObject::tr("Code de la qualification"), mainWidget);
    QVBoxLayout *qualificationLayout = new QVBoxLayout();

    for(auto &i : {QString("0"), QString("1"), QString("9"), QString("X")})
    {
        QString text;

        if(i == "0")
        {
            text = QObject::tr(" → Non cadre");
        } else if(i == "1") {
            text = QObject::tr(" → Défaut");
        } else if(i == "9") {
            text = QObject::tr(" → Cadre");
        } else if(i == "X") {
            text = QObject::tr(" → Non renseignée");
        }

        QHBoxLayout *boxLayout = new QHBoxLayout();
        boxLayout->setAlignment(Qt::AlignLeft);
        QRadioButton *sortButton = new QRadioButton(i, qualificationWidget);

        QObject::connect(sortButton, &QRadioButton::clicked, [this, sortButton]()->void {
            if(sortButton->text() == "1") {
                this->searchParam.qualification = "";
            } else {
                this->searchParam.qualification = sortButton->text();
            }
        });

        QLabel *sortLabel = new QLabel(text);

        boxLayout->addWidget(sortButton);
        boxLayout->addWidget(sortLabel);
        qualificationLayout->addLayout(boxLayout);
    }

    qualificationWidget->setLayout(qualificationLayout);

    return qualificationWidget;
}

QWidget *mariongiciel::gui::SearchWidget::getTempsPleinWidget(QWidget *mainWidget)// true false
{
    QGroupBox *tempsPleinWidget = new QGroupBox(QObject::tr("Temps plein"), mainWidget);
    QVBoxLayout *tempsPleinLayout = new QVBoxLayout(tempsPleinWidget);
    QLabel *info = new QLabel(QObject::tr(" Si le paramètre n'est pas renseigné, alors toutes les offres sont remontés"), tempsPleinWidget);

    tempsPleinLayout->addWidget(info);

    for(auto &i : {0, 1, 2})
    {
        QString textButton,textInfo;
        switch (i) {
            case 0 : textButton = QObject::tr("défaut"); textInfo = QObject::tr(" → Défaut");
            break;
            case 1 : textButton = QObject::tr("true"); textInfo = QObject::tr(" → Temps plein");
            break;
            case 2 : textButton = QObject::tr("false"); textInfo = QObject::tr(" → Temps partiel");
            break;
        }

        QHBoxLayout *boxLayout = new QHBoxLayout();
        boxLayout->setAlignment(Qt::AlignLeft);
        QRadioButton *sortButton = new QRadioButton(textButton, tempsPleinWidget);

        QObject::connect(sortButton, &QRadioButton::clicked, [this, sortButton]()->void {
            if(sortButton->text() == "défaut") {
                this->searchParam.tempsPlein = "";
            } else {
                this->searchParam.tempsPlein = sortButton->text();
            }
        });

        QLabel *sortLabel = new QLabel(textInfo);

        boxLayout->addWidget(sortButton);
        boxLayout->addWidget(sortLabel);
        tempsPleinLayout->addLayout(boxLayout);
    }


    tempsPleinWidget->setLayout(tempsPleinLayout);
    return tempsPleinWidget;
}
QWidget *mariongiciel::gui::SearchWidget::getCommuneWidget(QWidget *mainWidget)// not implemented
{
    QGroupBox *communeWidget = new QGroupBox(QObject::tr("Code INSEE de la commune"), mainWidget);
    QVBoxLayout *communeLayout = new QVBoxLayout(communeWidget);
    QLabel *info = new QLabel(QObject::tr("Selection de 5 valeurs maximum"), communeWidget);
    communeLayout->addWidget(info);




    communeWidget->setLayout(communeLayout);

    return communeWidget;
}

QWidget *mariongiciel::gui::SearchWidget::getDistanceWidget(QWidget *mainWidget) // default 10
{
    QWidget *notImplementedWidget = new QWidget(mainWidget);
    QHBoxLayout *notImplementedLayout = new QHBoxLayout();
    QLabel *nameLabel = new QLabel(QObject::tr("Distance"), notImplementedWidget);
    QLabel *notImplementedLabel = new QLabel(QObject::tr("Cette fonctionnalité n'est pas implémentée"), notImplementedWidget);
    notImplementedLayout->addWidget(nameLabel);
    notImplementedLayout->addWidget(notImplementedLabel);

    notImplementedWidget->setLayout(notImplementedLayout);
    return notImplementedWidget;
}

QWidget *mariongiciel::gui::SearchWidget::getDepartementWidget(QWidget *mainWidget) // departement (94)
{
    QGroupBox *departementWidget = new QGroupBox(QObject::tr("Departement"), mainWidget);
    QHBoxLayout *departementLayout = new QHBoxLayout(departementWidget);

    mariongiciel::core::ReferencialOutput refOut;
    DropDown *dropDown = new DropDown(QIcon(global::rcs::icon::_ACTION_), refOut.getDepartements(), departementWidget);


    departementLayout->addWidget(dropDown);

    QObject::connect(dropDown, &DropDown::textChanged, [this]
                     (const QString &text)->void {
        if(text.isEmpty())
        {
            this->searchParam.departement = QString();
        } else {
            this->searchParam.departement = text.split(":").first();
        }
    });

    departementWidget->setLayout(departementLayout);

    return departementWidget;
}

QWidget *mariongiciel::gui::SearchWidget::getInclureLimitrophesWidget(QWidget *mainWidget) // Inclure les départements limitrophes dans la recherche
{
    QWidget *notImplementedWidget = new QWidget(mainWidget);
    QHBoxLayout *notImplementedLayout = new QHBoxLayout();
    QLabel *nameLabel = new QLabel(QObject::tr("Inclure Limitrophes"), notImplementedWidget);
    QLabel *notImplementedLabel = new QLabel(QObject::tr("Cette fonctionnalité n'est pas implémentée"), notImplementedWidget);
    notImplementedLayout->addWidget(nameLabel);
    notImplementedLayout->addWidget(notImplementedLabel);

    notImplementedWidget->setLayout(notImplementedLayout);
    return notImplementedWidget;
}

QWidget *mariongiciel::gui::SearchWidget::getRegionWidget(QWidget *mainWidget) // not implemented
{
    QWidget *notImplementedWidget = new QWidget(mainWidget);
    QHBoxLayout *notImplementedLayout = new QHBoxLayout();
    QLabel *nameLabel = new QLabel(QObject::tr("Region"), notImplementedWidget);
    QLabel *notImplementedLabel = new QLabel(QObject::tr("Cette fonctionnalité n'est pas implémentée"), notImplementedWidget);
    notImplementedLayout->addWidget(nameLabel);
    notImplementedLayout->addWidget(notImplementedLabel);

    notImplementedWidget->setLayout(notImplementedLayout);
    return notImplementedWidget;
}
QWidget *mariongiciel::gui::SearchWidget::getPaysContinentWidget(QWidget *mainWidget)// not implemented
{
    QWidget *notImplementedWidget = new QWidget(mainWidget);
    QHBoxLayout *notImplementedLayout = new QHBoxLayout();
    QLabel *nameLabel = new QLabel(QObject::tr("Pays Continent"), notImplementedWidget);
    QLabel *notImplementedLabel = new QLabel(QObject::tr("Cette fonctionnalité n'est pas implémentée"), notImplementedWidget);
    notImplementedLayout->addWidget(nameLabel);
    notImplementedLayout->addWidget(notImplementedLabel);

    notImplementedWidget->setLayout(notImplementedLayout);
    return notImplementedWidget;
}

QWidget *mariongiciel::gui::SearchWidget::getNiveauFormationWidget(QWidget *mainWidget) // not implemented
{
    QWidget *notImplementedWidget = new QWidget(mainWidget);
    QHBoxLayout *notImplementedLayout = new QHBoxLayout();
    QLabel *nameLabel = new QLabel(QObject::tr("Niveau Formation"), notImplementedWidget);
    QLabel *notImplementedLabel = new QLabel(QObject::tr("Cette fonctionnalité n'est pas implémentée"), notImplementedWidget);
    notImplementedLayout->addWidget(nameLabel);
    notImplementedLayout->addWidget(notImplementedLabel);

    notImplementedWidget->setLayout(notImplementedLayout);
    return notImplementedWidget;
}
QWidget *mariongiciel::gui::SearchWidget::getPermisWidget(QWidget *mainWidget) // not implemented
{
    QWidget *notImplementedWidget = new QWidget(mainWidget);
    QHBoxLayout *notImplementedLayout = new QHBoxLayout();
    QLabel *nameLabel = new QLabel(QObject::tr("Permis"), notImplementedWidget);
    QLabel *notImplementedLabel = new QLabel(QObject::tr("Cette fonctionnalité n'est pas implémentée"), notImplementedWidget);
    notImplementedLayout->addWidget(nameLabel);
    notImplementedLayout->addWidget(notImplementedLabel);

    notImplementedWidget->setLayout(notImplementedLayout);
    return notImplementedWidget;
}

QWidget *mariongiciel::gui::SearchWidget::getMotsClesWidget(QWidget *mainWidget) // not implemented
{
    QWidget *notImplementedWidget = new QWidget(mainWidget);
    QHBoxLayout *notImplementedLayout = new QHBoxLayout();
    QLabel *nameLabel = new QLabel(QObject::tr("Mots Cles"), notImplementedWidget);
    QLabel *notImplementedLabel = new QLabel(QObject::tr("Cette fonctionnalité n'est pas implémentée"), notImplementedWidget);
    notImplementedLayout->addWidget(nameLabel);
    notImplementedLayout->addWidget(notImplementedLabel);

    notImplementedWidget->setLayout(notImplementedLayout);
    return notImplementedWidget;
}

QWidget *mariongiciel::gui::SearchWidget::getSalaireMinWidget(QWidget *mainWidget)// not implemented
{
    QWidget *notImplementedWidget = new QWidget(mainWidget);
    QHBoxLayout *notImplementedLayout = new QHBoxLayout();
    QLabel *nameLabel = new QLabel(QObject::tr("Salaire Min"), notImplementedWidget);
    QLabel *notImplementedLabel = new QLabel(QObject::tr("Cette fonctionnalité n'est pas implémentée"), notImplementedWidget);
    notImplementedLayout->addWidget(nameLabel);
    notImplementedLayout->addWidget(notImplementedLabel);

    notImplementedWidget->setLayout(notImplementedLayout);
    return notImplementedWidget;
}
QWidget *mariongiciel::gui::SearchWidget::getPeriodeSalaireWidget(QWidget *mainWidget)// not implemented M → Mensuel A → Annuel H → Horaire C → Cachet
{
    QWidget *notImplementedWidget = new QWidget(mainWidget);
    QHBoxLayout *notImplementedLayout = new QHBoxLayout();
    QLabel *nameLabel = new QLabel(QObject::tr("Periode Salaire"), notImplementedWidget);
    QLabel *notImplementedLabel = new QLabel(QObject::tr("Cette fonctionnalité n'est pas implémentée"), notImplementedWidget);
    notImplementedLayout->addWidget(nameLabel);
    notImplementedLayout->addWidget(notImplementedLabel);

    notImplementedWidget->setLayout(notImplementedLayout);
    return notImplementedWidget;
}

QWidget *mariongiciel::gui::SearchWidget::getAccesTravailleurHandicapeWidget(QWidget *mainWidget)// not implemented
{
    QWidget *notImplementedWidget = new QWidget(mainWidget);
    QHBoxLayout *notImplementedLayout = new QHBoxLayout();
    QLabel *nameLabel = new QLabel(QObject::tr("Acces Travailleur Handicape"), notImplementedWidget);
    QLabel *notImplementedLabel = new QLabel(QObject::tr("Cette fonctionnalité n'est pas implémentée"), notImplementedWidget);
    notImplementedLayout->addWidget(nameLabel);
    notImplementedLayout->addWidget(notImplementedLabel);

    notImplementedWidget->setLayout(notImplementedLayout);
    return notImplementedWidget;
}
QWidget *mariongiciel::gui::SearchWidget::getOffresMrsWidget(QWidget *mainWidget) // not implemented
{
    QWidget *notImplementedWidget = new QWidget(mainWidget);
    QHBoxLayout *notImplementedLayout = new QHBoxLayout();
    QLabel *nameLabel = new QLabel(QObject::tr("Offres MRS"), notImplementedWidget);
    QLabel *notImplementedLabel = new QLabel(QObject::tr("Cette fonctionnalité n'est pas implémentée"), notImplementedWidget);
    notImplementedLayout->addWidget(nameLabel);
    notImplementedLayout->addWidget(notImplementedLabel);

    notImplementedWidget->setLayout(notImplementedLayout);
    return notImplementedWidget;
}

QWidget *mariongiciel::gui::SearchWidget::getGrandDomaineWidget(QWidget *mainWidget) // not implemented
{
    QWidget *notImplementedWidget = new QWidget(mainWidget);
    QHBoxLayout *notImplementedLayout = new QHBoxLayout();
    QLabel *nameLabel = new QLabel(QObject::tr("Grand domaine"), notImplementedWidget);
    QLabel *notImplementedLabel = new QLabel(QObject::tr("Cette fonctionnalité n'est pas implémentée"), notImplementedWidget);
    notImplementedLayout->addWidget(nameLabel);
    notImplementedLayout->addWidget(notImplementedLabel);

    notImplementedWidget->setLayout(notImplementedLayout);
    return notImplementedWidget;
}
QWidget *mariongiciel::gui::SearchWidget::getExperienceExigenceWidget(QWidget *mainWidget) //not implemented
{
    QWidget *notImplementedWidget = new QWidget(mainWidget);
    QHBoxLayout *notImplementedLayout = new QHBoxLayout();
    QLabel *nameLabel = new QLabel(QObject::tr("Experience Exigence"), notImplementedWidget);
    QLabel *notImplementedLabel = new QLabel(QObject::tr("Cette fonctionnalité n'est pas implémentée"), notImplementedWidget);
    notImplementedLayout->addWidget(nameLabel);
    notImplementedLayout->addWidget(notImplementedLabel);

    notImplementedWidget->setLayout(notImplementedLayout);
    return notImplementedWidget;
}

QWidget *mariongiciel::gui::SearchWidget::getPublieeDepuisWidget(QWidget *mainWidget)//not implemented
{
    QWidget *notImplementedWidget = new QWidget(mainWidget);
    QHBoxLayout *notImplementedLayout = new QHBoxLayout();
    QLabel *nameLabel = new QLabel(QObject::tr("Publiee Depuis"), notImplementedWidget);
    QLabel *notImplementedLabel = new QLabel(QObject::tr("Cette fonctionnalité n'est pas implémentée"), notImplementedWidget);
    notImplementedLayout->addWidget(nameLabel);
    notImplementedLayout->addWidget(notImplementedLabel);

    notImplementedWidget->setLayout(notImplementedLayout);
    return notImplementedWidget;
}

QWidget *mariongiciel::gui::SearchWidget::getMinCreationDateWidget(QWidget *mainWidget) // not implemented Norme ISO-8601 (YYYY-MM-DDTHH:MM:SSZ)
{
    QGroupBox *minCreationDateWidget = new QGroupBox(mainWidget);
    QHBoxLayout *notImplementedLayout = new QHBoxLayout();
    QLabel *nameLabel = new QLabel(QObject::tr("Min Creation Date"), minCreationDateWidget);
    QLabel *notImplementedLabel = new QLabel(QObject::tr("Cette fonctionnalité n'est pas implémentée"), minCreationDateWidget);
    notImplementedLayout->addWidget(nameLabel);
    notImplementedLayout->addWidget(notImplementedLabel);

    minCreationDateWidget->setLayout(notImplementedLayout);
    return minCreationDateWidget;
}

QWidget *mariongiciel::gui::SearchWidget::getMaxCreationDateWidget(QWidget *mainWidget)// not implemented Norme ISO-8601 (YYYY-MM-DDTHH:MM:SSZ)
{
    QWidget *notImplementedWidget = new QWidget(mainWidget);
    QHBoxLayout *notImplementedLayout = new QHBoxLayout();
    QLabel *nameLabel = new QLabel(QObject::tr("Max Creation Date"), notImplementedWidget);
    QLabel *notImplementedLabel = new QLabel(QObject::tr("Cette fonctionnalité n'est pas implémentée"), notImplementedWidget);
    notImplementedLayout->addWidget(nameLabel);
    notImplementedLayout->addWidget(notImplementedLabel);

    notImplementedWidget->setLayout(notImplementedLayout);
    return notImplementedWidget;
}

QWidget *mariongiciel::gui::SearchWidget::getRunSearchWidget(QWidget *mainWidget)
{
    QWidget *runWidget = new QWidget(mainWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout();
    QPushButton *runButton = new QPushButton(QObject::tr("Executer"), this);
    runButton->setMaximumWidth(QFontMetrics(QFont("Times")).horizontalAdvance(runButton->text()));
    QObject::connect(runButton, &QPushButton::clicked, [this]()->void {
        if(this->searchMod_E == mariongiciel::core::SearchMod_E::_BY_COMMUNE_)
        {
            mariongiciel::core::Referencial ref;
            if(this->searchParam.departement.isEmpty() &&
            !ref.valuesIsValid(mariongiciel::core::Referencial_E::_DEPARTEMENTS_, {{"code", this->searchParam.departement}}))
            {
                QMessageBox::warning(nullptr,
                                    QObject::tr("ERREUR"),
                                    QObject::tr("Le département n'est pas valide")
                );
                return;
            }
        }
        QueryDialog queryDialog(this->currentFilterPath, this->searchParam, this->searchMod_E);
        queryDialog.exec();
    });

    mainLayout->addWidget(runButton, Qt::AlignHCenter);

    runWidget->setLayout(mainLayout);

    return runWidget;
}

