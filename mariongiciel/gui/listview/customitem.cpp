#include "customitem.h"



mariongiciel::gui::CustomAddItem::CustomAddItem(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    this->exitButton = new QPushButton(QIcon(global::rcs::icon::_LEFT_ARROW_), QObject::tr("Retour"), this);
    this->exitButton->setStyleSheet("QPushButton{background:transparent;}");
    mainLayout->addWidget(this->exitButton);
    mainLayout->setAlignment(this->exitButton, Qt::AlignLeft);
    QObject::connect(this->exitButton, &QPushButton::clicked, [this]()->void {emit exitFilter();});

    this->addItemEdit = new QLineEdit(this);
    this->addItemEdit->setPlaceholderText(QObject::tr("Nom de la sauvegarde"));
    mainLayout->addWidget(this->addItemEdit);
    mainLayout->setAlignment(this->addItemEdit, Qt::AlignLeft);

    this->addItemButton = new QPushButton(QIcon(global::rcs::icon::_DOWN_ARROW_), QObject::tr("Ajouter"), this);
    this->addItemButton->setStyleSheet("background:transparent;");
    mainLayout->addWidget(this->addItemButton);
    mainLayout->setAlignment(this->addItemButton, Qt::AlignLeft);
    QObject::connect(this->addItemButton, &QPushButton::clicked, [this]()->void {
        QString text = this->addItemEdit->text();
        if(!text.isEmpty())
        {
            this->addItemEdit->clear();
            emit addItem(text);
        }
    });

    this->createFilter = new QPushButton(QObject::tr("Créer un filtre"), this);
    mainLayout->addWidget(this->createFilter);
    mainLayout->setAlignment(this->createFilter, Qt::AlignRight);
    QObject::connect(this->createFilter, &QPushButton::clicked, [this]()->void {
        emit addFilter();
    });


    this->setLayout(mainLayout);
}

mariongiciel::gui::CustomAddItem::~CustomAddItem() noexcept
{

}



mariongiciel::gui::CustomItem::CustomItem(const QString &itemName, QWidget *parent)
    : QWidget(parent), itemName(itemName)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignLeft);

    this->itemNameEdit = new QLineEdit(itemName, this);
    mainLayout->addWidget(this->itemNameEdit);
    mainLayout->setAlignment(this->itemNameEdit, Qt::AlignLeft);

    this->removeButton = new QPushButton(this);
    this->removeButton->setIcon(QIcon(mariongiciel::global::rcs::icon::_REMOVE_));
    this->removeButton->setStyleSheet("background:transparent;");
    mainLayout->addWidget(this->removeButton);
    mainLayout->setAlignment(this->removeButton, Qt::AlignLeft);
    QObject::connect(this->removeButton, &QPushButton::clicked, [this]()->void {emit removeItem(this->itemName);});

    this->setLayout(mainLayout);
}

mariongiciel::gui::CustomItem::~CustomItem() noexcept
{

}

QString mariongiciel::gui::CustomItem::getItemName() const
{
    return this->itemName;
}

mariongiciel::gui::CustomItemFilter::CustomItemFilter(const QString &itemName, const QString &dataName, const QString &byName, QWidget *parent)
    : QWidget(parent), itemName(itemName), itemData(dataName), itemBy(byName)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignLeft);

    QLabel *nameLabel = new QLabel(this->itemName, this);
    mainLayout->addWidget(nameLabel);
    mainLayout->setAlignment(nameLabel, Qt::AlignLeft);

    QLabel *dataLabel = new QLabel(this->itemData, this);
    mainLayout->addWidget(dataLabel);
    mainLayout->setAlignment(dataLabel, Qt::AlignLeft);

    QLabel *wordLabel = new QLabel(QObject::tr("REMPLACER PAR"), this);
    wordLabel->setStyleSheet("color:red");
    mainLayout->addWidget(wordLabel);
    mainLayout->setAlignment(wordLabel, Qt::AlignLeft);

    QLabel *byLabel = new QLabel(this->itemBy, this);
    mainLayout->addWidget(byLabel);
    mainLayout->setAlignment(byLabel, Qt::AlignLeft);

    this->removeButton = new QPushButton(this);
    this->removeButton->setIcon(QIcon(mariongiciel::global::rcs::icon::_REMOVE_));
    this->removeButton->setStyleSheet("background:transparent;");
    mainLayout->addWidget(this->removeButton);
    mainLayout->setAlignment(this->removeButton, Qt::AlignLeft);
    QObject::connect(this->removeButton, &QPushButton::clicked, [this]()->void {emit removeItem(this->itemName, this->itemData, this->itemBy);});

    this->setLayout(mainLayout);
}

mariongiciel::gui::CustomItemFilter::~CustomItemFilter() noexcept
{

}

QString mariongiciel::gui::CustomItemFilter::getItemName() const
{
    return this->itemName;
}

QString mariongiciel::gui::CustomItemFilter::getItemData() const
{
    return this->itemData;
}

QString mariongiciel::gui::CustomItemFilter::getItemBy() const
{
    return this->itemBy;
}
