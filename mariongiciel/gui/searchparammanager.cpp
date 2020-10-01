#include "searchparammanager.h"

mariongiciel::gui::SearchParamManager::SearchParamManager(QWidget *parent)
    : QWidget(parent)
{
    this->setObjectName("search-param-manager");

    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    this->clearAllParam = new QPushButton(QObject::tr("Tout effacer"), this);
    this->clearAllParam->setIcon(QIcon());


    this->searchList = new QComboBox(this);

    this->loadSearch = new QPushButton(QObject::tr("Charger"), this);
    QObject::connect(this->loadSearch, &QPushButton::clicked, this, &SearchParamManager::loadSearchSlot);

    this->removeSearch = new QPushButton(QObject::tr("Supprimer"), this);
    QObject::connect(this->removeSearch, &QPushButton::clicked, this, &SearchParamManager::removeSearchSlot);

    mainLayout->addWidget(this->clearAllParam);
    mainLayout->addWidget(this->searchList);
    mainLayout->addWidget(this->loadSearch);
    mainLayout->addWidget(this->removeSearch);

    this->setLayout(mainLayout);
}

mariongiciel::gui::SearchParamManager::~SearchParamManager() noexcept
{

}


// private slots :
void mariongiciel::gui::SearchParamManager::loadSearchSlot()
{
#ifdef QT_DEBUG
    qDebug()<<"load search";
#endif
}

void mariongiciel::gui::SearchParamManager::removeSearchSlot()
{
#ifdef QT_DEBUG
    qDebug()<<"remove search";
#endif
}

void mariongiciel::gui::SearchParamManager::clearAllSlot()
{
#ifdef QT_DEBUG
    qDebug()<<"clear all";
#endif
}
