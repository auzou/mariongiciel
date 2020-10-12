#ifndef ACCOUNTWIDGET_H
#define ACCOUNTWIDGET_H
#include <QWidget>
#include <QTabWidget>
#include <QTabBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QMessageBox>
#include <QPainter>
#include <QStyleOption>

#include "../global.h"
#include "../core/account.h"
#include "../core/network/authentication.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

namespace mariongiciel::gui {

class AccountWidget : public QWidget
{
    Q_OBJECT

    private :
        QTabWidget *tabWidget;
        mariongiciel::core::network::Authentication *auth;

    private :
        QWidget *poleWidget;
        QVBoxLayout *poleMainLayout;
        QLineEdit *poleId;
        QLineEdit *poleKey;
        QTextEdit *poleTextEdit;
        QPushButton *poleSaveButton;
        QPushButton *poleTestButton;

    // futur widget
    private :
        QWidget *mapsWidget;
        QLineEdit *mapsId;
        QTextEdit *mapsTextEdit;
        QPushButton *mapsSaveButton;
        QPushButton *mapsTestButton;


    public :
        explicit AccountWidget(mariongiciel::core::network::Authentication *auth, QWidget *parent = nullptr);
        void ongletPole();
        void ongletMaps();
        void sessionBox();
        ~AccountWidget() noexcept;

   public slots :
        void poleTestSlot();
};

} // END NAMESPACE mariongiciel::gui

#endif // ACCOUNTWIDGET_H
