#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QApplication>
#include <QScreen>

#include "../global.h"
#include "menutoolbar.h"
#include "accountwidget.h"
#include "searchwidget.h"
#include "referencialwidget.h"
#include "../core/response.h"
#include "../core/network/authentication.h"
#include "../core/network/search.h"


#ifdef QT_DEBUG
#include <QDebug>
#endif

namespace mariongiciel::gui {

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private :
         MenuToolBar *menuToolBar;
         QStackedWidget *stackedWidget;
         // stacked
         AccountWidget *accountWidget;
         SearchWidget *searchWidget;
         ReferencialWidget *referencialWidget;

    public :
        explicit MainWindow(QWidget *parent = nullptr);
        void loadCss();
        ~MainWindow() noexcept;
};

} // END NAMESPACE mariongiciel::gui

#endif // MAINWINDOW_H
