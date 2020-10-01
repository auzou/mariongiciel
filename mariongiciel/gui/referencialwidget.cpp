#include "referencialwidget.h"


mariongiciel::gui::ReferencialWidget::ReferencialWidget(QWidget *parent)
    : QWidget(parent),
      fileInfoStr({
                  QObject::tr("Nom"),
                  QObject::tr("Taille"),
                  QObject::tr("Date"),
                  QObject::tr("Chemin"),
                  })
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QToolButton *downloadButton = new QToolButton(this);
    downloadButton->setText(QObject::tr("Téléchargement"));
    downloadButton->setIcon(QIcon(global::rcs::icon::_DOWNLOAD_));
    downloadButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    QObject::connect(downloadButton, &QToolButton::clicked, this, &ReferencialWidget::downloadSlot);

    this->downloadList = new QTableWidget(this);
    this->setDownloadList();

    mainLayout->addWidget(downloadButton);
    mainLayout->setAlignment(downloadButton, Qt::AlignHCenter);
    mainLayout->addWidget(this->downloadList);

    this->setLayout(mainLayout);
}

void mariongiciel::gui::ReferencialWidget::setDownloadList()
{
    this->downloadList->clear();
    QVector<QFileInfo> fileInfoList = mariongiciel::core::DirManagement::getFile(mariongiciel::global::rcs::referencial::_LOCATION_);

    if(fileInfoList.isEmpty())
    {
        return;
    }
    this->downloadList->setRowCount(fileInfoList.size());
    this->downloadList->setColumnCount(fileInfoStr.size());

    for(int i = 0; i < this->fileInfoStr.size(); i++)
    {
        this->downloadList->setHorizontalHeaderItem(i, new QTableWidgetItem(this->fileInfoStr[i]));
    }

    for(int i = 0; i < fileInfoList.size(); i++)
    {
        for(int j = 0; j < this->fileInfoStr.size(); j++)
        {
            switch(j)
            {
                case 0 :
                    this->downloadList->setItem(i, j, new QTableWidgetItem(fileInfoList[i].baseName()));
                break;
                case 1 :
                    this->downloadList->setItem(i, j, new QTableWidgetItem(QString::number(fileInfoList[i].size())+" Octets"));
                break;
                case 2 :
                    this->downloadList->setItem(i, j, new QTableWidgetItem(fileInfoList[i].lastModified().toString("yyyy-MM-dd_hh-mm-ss")));
                break;
                case 3 :
                    this->downloadList->setItem(i, j, new QTableWidgetItem(fileInfoList[i].path()));
                break;
            }
            this->downloadList->item(i, j)->setFlags(Qt::ItemIsEnabled);
        }
    }
}

mariongiciel::gui::ReferencialWidget::~ReferencialWidget() noexcept
{

}

void mariongiciel::gui::ReferencialWidget::downloadSlot()
{
    ReferencialDialog ref(mariongiciel::core::network::AuthSingleton::GetInstance());
    ref.exec();
    this->setDownloadList();
    emit referencialChanged();
}
