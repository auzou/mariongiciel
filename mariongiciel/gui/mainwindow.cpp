#include "mainwindow.h"

mariongiciel::gui::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setObjectName("main-window");

    this->setWindowTitle(QObject::tr(
                                     "MarionGiciel Version : " +
                                     mariongiciel::global::info::_INFO_VERSION_.toUtf8() +
                                     ":" +
                                     mariongiciel::global::info::_INFO_VERSION_STATUS_.toUtf8()
                                     )
                         );

    this->setWindowIcon(QIcon(global::rcs::icon::_API_));

    this->loadCss();

    mariongiciel::core::network::AuthSingleton::initInstance(this);

    this->menuToolBar = new MenuToolBar(this);
    this->addToolBar(Qt::LeftToolBarArea,this->menuToolBar);

    this->stackedWidget = new QStackedWidget(this);

    this->accountWidget = new AccountWidget(mariongiciel::core::network::AuthSingleton::GetInstance(), this->stackedWidget);

    this->searchWidget = new SearchWidget(this->stackedWidget);

    this->referencialWidget = new ReferencialWidget(this->stackedWidget);

    this->stackedWidget->addWidget(this->accountWidget);
    this->stackedWidget->addWidget(this->searchWidget);
    this->stackedWidget->addWidget(this->referencialWidget);

    this->setCentralWidget(this->stackedWidget);

    QObject::connect(this->menuToolBar, &MenuToolBar::openWidget, [this](widget_E widget_e)->void {
        this->stackedWidget->setCurrentIndex(widget_e);
    });

    QObject::connect(this->referencialWidget, &ReferencialWidget::referencialChanged, [this]()->void {
        this->searchWidget->refreshMainWidget();
    });
}

void mariongiciel::gui::MainWindow::loadCss()
{
    QFile file(global::rcs::css::_STYLE_);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QString styleSheet = QLatin1String(file.readAll());
    this->setStyleSheet(styleSheet);
    file.close();
}

mariongiciel::gui::MainWindow::~MainWindow() noexcept
{

}
