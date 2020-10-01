#include "menutoolbar.h"

mariongiciel::gui::MenuToolBar::MenuToolBar(QWidget *parent)
    : QToolBar(parent)
{
    this->setObjectName("menu-tool-bar");

    this->setOrientation(Qt::Vertical);
    this->setMovable(false);
    this->setMinimumWidth(100);

    this->accountButton = new QToolButton(this);
    this->accountButton->setText(QObject::tr("Compte"));
    this->accountButton->setIcon(QIcon(global::rcs::icon::_ACCOUNT_));
    this->accountButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);


    this->searchButton = new QToolButton(this);
    this->searchButton->setText(QObject::tr("Recherche"));
    this->searchButton->setIcon(QIcon(global::rcs::icon::_SEARCH_));
    this->searchButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    this->referencialButton = new QToolButton(this);
    this->referencialButton->setText(QObject::tr("Référentiel"));
    this->referencialButton->setIcon(QIcon(global::rcs::icon::_DOWNLOAD_));
    this->referencialButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);


    this->addWidget(this->accountButton);
    this->addWidget(this->searchButton);
    this->addWidget(this->referencialButton);

    this->setObjectName("menutoolbar");

    // signals
    QObject::connect(this->accountButton, &QToolButton::clicked, [this]()->void {emit openWidget(widget_E::_ACCOUNT_);});
    QObject::connect(this->searchButton, &QToolButton::clicked, [this]()->void {emit openWidget(widget_E::_SEARCH_);});
    QObject::connect(this->referencialButton, &QToolButton::clicked, [this]()->void {emit openWidget(widget_E::_REFERENCIAL_);});
}

mariongiciel::gui::MenuToolBar::~MenuToolBar() noexcept
{

}
