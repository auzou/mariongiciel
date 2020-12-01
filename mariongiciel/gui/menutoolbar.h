#ifndef MENUTOOLBAR_H
#define MENUTOOLBAR_H
#include <QToolBar>
#include <QToolButton>
#include <QMessageBox>

#include "global.h"
#include "core/referencialdata.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

namespace mariongiciel::gui {

enum widget_E
{
    _ACCOUNT_ = 0,
    _SEARCH_ = 1,
    _REFERENCIAL_ = 2,
};


class MenuToolBar : public QToolBar
{
    Q_OBJECT

    private :
        QToolButton *accountButton;
        QToolButton *searchButton;
        QToolButton *referencialButton;

    public :
        explicit MenuToolBar(QWidget *parent = nullptr);
        ~MenuToolBar() noexcept;

    signals :
        void openWidget(widget_E);
};

} // END NAMESPACE mariongiciel::gui

#endif // MENUTOOLBAR_H
