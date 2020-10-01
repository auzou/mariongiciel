#include "accountwidget.h"

mariongiciel::gui::AccountWidget::AccountWidget(mariongiciel::core::network::Authentication *auth, QWidget *parent)
    : QWidget(parent), auth(auth)
{
    this->setObjectName("account-widget");

    this->tabWidget = new QTabWidget(this);

    this->ongletPole();
    this->ongletMaps();

    // change
    this->tabWidget->setStyleSheet("QTabBar::tab { min-height: 50px; }");

    this->tabWidget->addTab(this->poleWidget, QObject::tr("API Pôle emploi"));
    this->tabWidget->setTabIcon(0, QIcon(global::rcs::icon::_POLE_));

    this->tabWidget->addTab(this->mapsWidget, QObject::tr("API Google Maps"));
    this->tabWidget->setTabIcon(1, QIcon(global::rcs::icon::_MAPS_));

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(this->tabWidget);

    this->setLayout(mainLayout);

    // move (better error handling and expected -> error code)
    /*
    QObject::connect(this->auth, &mariongiciel::core::network::Authentication::authenticationFinished,
                     [this](mariongiciel::core::network::Session session)->void {
        if(session.token.isEmpty())
        {
            QMessageBox::warning(this, "ERREUR", "<h1 color=\"red\">ERREUR d'authentification !</h1>");
        } else {
            QMessageBox::information(this, "Informations", "<center><h2>Votre compte est valide</h2></center>"
                                                           "<strong>Scope : </strong>" +  session.scope +
                                                           "<br><strong>Token : </strong>" + session.token +
                                                           "<br><strong>Token type : </strong>" + session.tokenType +
                                                           "<br><strong>Expire : </strong>" + QString::number(session.expire));
        }
    });
    */
}

void mariongiciel::gui::AccountWidget::ongletPole()
{
    this->poleWidget = new QWidget(this->tabWidget);
    this->poleMainLayout = new QVBoxLayout(this->poleWidget);
    this->poleMainLayout->setAlignment(Qt::AlignHCenter);

    // id
    QHBoxLayout *poleIdLayout = new QHBoxLayout();
    QLabel *poleIdLabel = new QLabel("Client ID : ", this->poleWidget);
    poleIdLabel->setFixedSize(100, 10);
    this->poleId = new QLineEdit(this->poleWidget);
    this->poleId->setMaximumWidth(300);
    poleIdLayout->addWidget(poleIdLabel);
    poleIdLayout->addWidget(this->poleId);
    this->poleMainLayout->addLayout(poleIdLayout);

    // key
    QHBoxLayout *poleKeyLayout = new QHBoxLayout();
    QLabel *poleKeyLabel = new QLabel("Client clef : ", this->poleWidget);
    poleKeyLabel->setFixedSize(100, 10);
    this->poleKey = new QLineEdit(this->poleWidget);
    this->poleKey->setMaximumWidth(300);
    poleKeyLayout->addWidget(poleKeyLabel);
    poleKeyLayout->addWidget(this->poleKey);
    this->poleMainLayout->addLayout(poleKeyLayout);

    // text edit
    this->poleTextEdit = new QTextEdit(this->poleWidget);
    this->poleTextEdit->setMaximumWidth(300);
    this->poleTextEdit->setEnabled(false);
    this->poleTextEdit->setFrameStyle(QFrame::NoFrame);
    this->poleTextEdit->setHtml(QObject::tr("<strong>Informations</strong><br>"
                                            "<em>- Les identifiants ne sont pas visible</em></center><br>"
                                            "<em>- Le boutton \"Sauvegarde\" écrase les identifiants</em>"));
    this->poleTextEdit->setStyleSheet("QTextEdit{background-color: transparent;color:black;max-height:100px;}");
    this->poleMainLayout->addWidget(this->poleTextEdit);

    // button
    QHBoxLayout *poleButtonLayout = new QHBoxLayout();
    this->poleSaveButton = new QPushButton(QObject::tr("Sauvegarder"), this->poleWidget);
    this->poleSaveButton->setMaximumWidth(200);
    poleButtonLayout->addWidget(this->poleSaveButton);
    this->poleTestButton = new QPushButton(QObject::tr("Tester le compte"), this->poleWidget);
    this->poleTestButton->setMaximumWidth(200);
    poleButtonLayout->addWidget(this->poleTestButton);
    this->poleMainLayout->addLayout(poleButtonLayout);

    this->poleWidget->setLayout(this->poleMainLayout);

    QObject::connect(this->poleTestButton, &QPushButton::clicked, this, &AccountWidget::poleTestSlot);
}

void mariongiciel::gui::AccountWidget::ongletMaps()
{
    this->mapsWidget = new QWidget(this->tabWidget);
}

mariongiciel::gui::AccountWidget::~AccountWidget() noexcept
{

}

// SLOTS
void mariongiciel::gui::AccountWidget::poleTestSlot()
{

}
