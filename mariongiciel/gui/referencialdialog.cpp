#include "referencialdialog.h"

mariongiciel::gui::ReferencialDialog::ReferencialDialog(mariongiciel::core::network::Authentication *auth, QWidget *parent)
    : QDialog(parent), currentValue(0)
{
    this->setObjectName("referencial-dialog");

    this->setFixedWidth(600);

    this->progressBarTimer = new QTimer(this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    this->progressBar = new QProgressBar(this);
    this->progressBar->setRange(0, 100);

    mainLayout->addWidget(progressBar);

    this->information = new QLabel(QObject::tr("<strong>Téléchargement des référentiel</strong>"), this);

    mainLayout->addWidget(this->information);

    this->setLayout(mainLayout);

    this->referencialInput = new mariongiciel::core::ReferencialInput(auth, this);

    QObject::connect(this->referencialInput, &mariongiciel::core::ReferencialInput::referencialInProgress,
                     [this](int cursor, QString refNam)->void {
        QString label = QObject::tr("<strong>Téléchargement du référentiel : ") + refNam +
                "  "+
                QString::number(cursor+1)+
                "/15"
                "</strong>";
        this->information->setText(label);
        this->currentValue = (cursor+1) * 6;
    });

    QObject::connect(this->referencialInput, &mariongiciel::core::ReferencialInput::referencialInProgressError,
                     [this](int cursor, QString errorMsg, QString refNam)->void {
        QString label = QObject::tr("<strong>Téléchargement du référentiel : ") + refNam +
                "  "+
                QString::number(cursor+1)+
                "/15"+
                "<br>Code erreur :<br>"+
                errorMsg +
                "<br>Nouvelle tentative en cours" +
                "</strong>";
        this->information->setText(label);
    });

    QObject::connect(this->referencialInput, &mariongiciel::core::ReferencialInput::referencialFinished,
                     [this]()->void {
        this->currentValue = 100;
    });

    QObject::connect(this->progressBarTimer, &QTimer::timeout, [this]()->void {
        if(this->progressBar->value() >= 100)
        {
            this->progressBarTimer->stop();
            this->close();
        }

        if(this->currentValue > this->progressBar->value())
        {
            this->progressBar->setValue(this->progressBar->value()+1);
        }
    });

    this->progressBarTimer->start(100);
    this->referencialInput->refreshReferencial();
}

mariongiciel::gui::ReferencialDialog::~ReferencialDialog() noexcept
{

}
