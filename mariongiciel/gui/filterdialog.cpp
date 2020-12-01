#include "filterdialog.h"


mariongiciel::gui::FilterViewDialog::FilterViewDialog(mariongiciel::core::Filter *filter, QWidget *parent)
    : QDialog(parent), filter(filter)
{
    QVBoxLayout * mainLayout = new QVBoxLayout(this);

    this->filterNameList = new QComboBox(this);
    this->filterNameList->addItems(mariongiciel::core::ConversionProcess(this).getColumnName().split(","));
    mainLayout->addWidget(this->filterNameList);

    this->filterData = new QLineEdit(this);
    this->filterData->setPlaceholderText(QObject::tr("Donnée de base"));
    mainLayout->addWidget(this->filterData);

    this->filterBy = new QLineEdit(this);
    this->filterBy->setPlaceholderText(QObject::tr("Remplacer par"));
    mainLayout->addWidget(this->filterBy);

    this->saveButton = new QPushButton(QObject::tr("Sauvegarde"), this);
    mainLayout->addWidget(this->saveButton);
    QObject::connect(this->saveButton, &QPushButton::clicked, [this]()->void {
        if(!this->filterData->text().isEmpty())
        {
            this->filter->addFilterReplace(this->filterNameList->currentText(), {this->filterData->text(), this->filterBy->text()});
        }
        this->close();
    });

    this->setLayout(mainLayout);
}

mariongiciel::gui::FilterViewDialog::FilterViewDialog(const QString &name, const QString &data, const QString &by, mariongiciel::core::Filter *filter, QWidget *parent)
    : QDialog(parent), filter(filter)
{
    this->oldData << name << data << by ;
    QVBoxLayout * mainLayout = new QVBoxLayout(this);

    this->filterNameList = new QComboBox(this);
    this->filterNameList->addItems(mariongiciel::core::ConversionProcess(this).getColumnName().split(","));
    this->filterNameList->setCurrentText(name);
    mainLayout->addWidget(this->filterNameList);

    this->filterData = new QLineEdit(this);
    this->filterData->setText(data);
    mainLayout->addWidget(this->filterData);

    this->filterBy = new QLineEdit(this);
    this->filterBy->setText(by);
    mainLayout->addWidget(this->filterBy);

    this->saveButton = new QPushButton(QObject::tr("Sauvegarde"), this);
    mainLayout->addWidget(this->saveButton);
    QObject::connect(this->saveButton, &QPushButton::clicked, [this]()->void {
        if(!this->filterData->text().isEmpty() && !this->filterBy->text().isEmpty())
        {
            if(!this->oldData.isEmpty())
            {
                this->filter->removeFilter(this->oldData[0], this->oldData[1], this->oldData[2]);
            }
            this->filter->addFilterReplace(this->filterNameList->currentText(), {this->filterData->text(), this->filterBy->text()});
        }
        this->close();
    });

    this->setLayout(mainLayout);
}

mariongiciel::gui::FilterViewDialog::~FilterViewDialog() noexcept
{

}


mariongiciel::gui::FilterDialog::FilterDialog(QString filterSelected, QWidget *parent)
    : QDialog(parent)
{
    this->setFixedSize(800, 400);
    this->filter = new mariongiciel::core::Filter(this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *filterSelectedLayout = new QHBoxLayout();
    if(filterSelected.isEmpty())
    {
        this->filterSelected = new QLabel(QObject::tr("aucun filtre"), this);
    } else {
        this->filterSelected = new QLabel(filterSelected, this);
    }
    filterSelectedLayout->addWidget(this->filterSelected);
    filterSelectedLayout->setAlignment(this->filterSelected, Qt::AlignRight);

    QPushButton *removeFilterSelected = new QPushButton(this);
    removeFilterSelected->setIcon(QIcon(global::rcs::icon::_REMOVE_));
    removeFilterSelected->setStyleSheet("background:transparent;");
    QObject::connect(removeFilterSelected, &QPushButton::clicked, [this]()->void {
        this->filterSelected->setText(QObject::tr("aucun filtre"));
    });
    filterSelectedLayout->addWidget(removeFilterSelected);
    filterSelectedLayout->setAlignment(removeFilterSelected, Qt::AlignLeft);

    mainLayout->addLayout(filterSelectedLayout);



    this->filterSaveList = new QListWidget(this);
    this->filterSaveList->setMinimumSize(300, 300);

    CustomAddItem *customAddItem = new CustomAddItem(this);
    mainLayout->addWidget(customAddItem);
    mainLayout->setAlignment(customAddItem, Qt::AlignLeft);

    QObject::connect(customAddItem, &CustomAddItem::addItem, this, &FilterDialog::addItem);
    QObject::connect(customAddItem, &CustomAddItem::exitFilter, this, &FilterDialog::close);
    QObject::connect(customAddItem, &CustomAddItem::addFilter, this, &FilterDialog::addFilter);

    QWidget *container = new QWidget(this);
    QHBoxLayout *containerMainLayout = new QHBoxLayout(container);
    container->setLayout(containerMainLayout);

    for(auto &i : mariongiciel::core::DirManagement::getFile(global::rcs::filter::_LOCATION_))
    {
        CustomItem *customItem = new CustomItem(i.baseName(), this->filterSaveList);
        QListWidgetItem *item = new QListWidgetItem(this->filterSaveList);
        item->setSizeHint(customItem->sizeHint());
        this->filterSaveList->addItem(item);
        this->filterSaveList->setItemWidget(item, customItem);
        QObject::connect(customItem, &CustomItem::removeItem, [this, item](const QString &itemName)->void{
            this->filterSaveList->removeItemWidget(item);
            delete item;
            mariongiciel::core::FileManagement::remove(QString(global::rcs::filter::_LOCATION_+itemName+".json"));
        });
    }

    QObject::connect(this->filterSaveList, &QListWidget::itemClicked, [this](QListWidgetItem *item)->void {
        CustomItem *customWidget = dynamic_cast<CustomItem*>(this->filterSaveList->itemWidget(item));
        this->filterSelected->setText(customWidget->getItemName());
        this->filter->setFilter(customWidget->getItemName());
        this->setColumnList();
    });

    containerMainLayout->addWidget(this->filterSaveList);
    containerMainLayout->setAlignment(this->filterSaveList, Qt::AlignCenter);

    // right view
    this->columnList = new QListWidget(this);
    this->columnList->setMinimumSize(500, 300);


    containerMainLayout->addWidget(this->columnList);
    containerMainLayout->setAlignment(this->columnList, Qt::AlignCenter);

    QObject::connect(this->columnList, &QListWidget::itemClicked, [this](QListWidgetItem *item)->void {
        CustomItemFilter *customWidget = dynamic_cast<CustomItemFilter*>(this->columnList->itemWidget(item));
        FilterViewDialog filverViewDialog(customWidget->getItemName(), customWidget->getItemData(), customWidget->getItemBy(), this->filter);
        filverViewDialog.exec();
        this->setColumnList();
    });

    mainLayout->addWidget(container);

    this->setLayout(mainLayout);
}

mariongiciel::gui::FilterDialog::~FilterDialog() noexcept
{

}

void mariongiciel::gui::FilterDialog::setColumnList()
{
    this->columnList->clear();
    QVector<QMap<QString,QString>> filterData = this->filter->getFilterList();
    if(filterData.isEmpty())
    {
        QListWidgetItem *item = new QListWidgetItem(QObject::tr("Aucun filtre"), this->columnList);
        this->columnList->addItem(item);
    } else {
        for(auto &i : filterData)
        {
            CustomItemFilter *itemFilter = new CustomItemFilter(i["name"], i["data"], i["by"], this->columnList);
            QListWidgetItem *item = new QListWidgetItem(this->columnList);
            item->setSizeHint(itemFilter->sizeHint());
            this->columnList->setItemWidget(item, itemFilter);
            this->columnList->addItem(item);
            QObject::connect(itemFilter, &CustomItemFilter::removeItem, [this, item]
                             (const QString &itemName, const QString &itemData, const QString &itemBy)->void{
                this->filterSaveList->removeItemWidget(item);
                delete item;
                this->filter->removeFilter(itemName, itemData, itemBy);
                this->setColumnList();
            });
        }
    }
}

void mariongiciel::gui::FilterDialog::addItem(const QString &itemName)
{
    mariongiciel::core::Filter filter(itemName);
    CustomItem *customItem = new CustomItem(itemName, this->filterSaveList);
    QListWidgetItem *item = new QListWidgetItem(this->filterSaveList);
    item->setSizeHint(customItem->sizeHint());
    this->filterSaveList->addItem(item);
    this->filterSaveList->setItemWidget(item, customItem);
}
void mariongiciel::gui::FilterDialog::addFilter()
{
    FilterViewDialog filverViewDialog(this->filter);
    filverViewDialog.exec();
    this->setColumnList();
}

QString mariongiciel::gui::FilterDialog::getFilterName() const
{
    return this->filterSelected->text();
}
