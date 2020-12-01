#include "querydialog.h"

mariongiciel::gui::QueryDialog::QueryDialog(const QString &filterName,
                                            mariongiciel::core::network::SearchParam searchParam,
                                            mariongiciel::core::SearchMod_E searchMod_e,
                                            QWidget *parent)
    : QDialog(parent),
      filterName(filterName),
      searchMod_e(searchMod_e),
      searchParam(searchParam)
{
    this->searchQuery = new mariongiciel::core::SearchQuery(this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    //this->progressBar = new QProgressBar(this);
    //this->progressBar->setRange(0, 100);


    //mainLayout->addWidget(this->progressBar);

    this->info = new QTextEdit(
    QObject::tr("<center>En attente de la fin du traitement, cette fenêtre se fermera automatiquement à la fin du traitement<center>"), this);
    this->info->setEnabled(false);
    mainLayout->addWidget(info);

    this->setLayout(mainLayout);
}

mariongiciel::gui::QueryDialog::~QueryDialog() noexcept
{

}

void mariongiciel::gui::QueryDialog::showEvent(QShowEvent *)
{
    this->runSearch();
}

void mariongiciel::gui::QueryDialog::runSearch()
{
    this->searchQuery->setMod(this->searchMod_e);
    this->searchQuery->runSearchQuery(filterName, this->searchParam);



    QObject::connect(this->searchQuery, &mariongiciel::core::SearchQuery::searchQueryStepFinished, [this]()->void {
        this->close();
    });

    QObject::connect(this->searchQuery, &mariongiciel::core::SearchQuery::searchQueryFinished, [this]()->void {
        QDesktopServices::openUrl(
                         QUrl::fromLocalFile(
                         QDir(global::rcs::data::_LOCATION_+this->searchQuery->getCurrentDir()).absolutePath()
                         ));
        this->close();
    });
}
