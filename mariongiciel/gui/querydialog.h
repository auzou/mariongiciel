#ifndef QUERYDIALOG_H
#define QUERYDIALOG_H
#include <QDialog>
#include <QProgressBar>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QDesktopServices>
#include <QApplication>

#include "core/searchquery.h"

namespace mariongiciel::gui {

class QueryDialog : public QDialog
{
    private :
        mariongiciel::core::SearchQuery *searchQuery;
        QString filterName;
        mariongiciel::core::SearchMod_E searchMod_e;
        mariongiciel::core::network::SearchParam searchParam;

    private :
        //QProgressBar *progressBar;
        QTextEdit *info;
        int currentValue;

    public :
        explicit QueryDialog(const QString &filterName,
                             mariongiciel::core::network::SearchParam searchParam,
                             mariongiciel::core::SearchMod_E searchMod_e,
                             QWidget *parent = nullptr);

        ~QueryDialog() noexcept;

     public :
        void showEvent(QShowEvent *) override;
        void runSearch();
};

} // END NAMESPACE mariongiciel::gui

#endif // QUERYDIALOG_H
