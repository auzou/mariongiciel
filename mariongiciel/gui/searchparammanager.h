#ifndef SEARCHPARAMMANAGER_H
#define SEARCHPARAMMANAGER_H
#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>

#include "../global.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

namespace mariongiciel::gui {

class SearchParamManager : public QWidget
{
    Q_OBJECT

    private :
        QPushButton *clearAllParam;
        QComboBox *searchList;
        QPushButton *loadSearch;
        QPushButton *removeSearch;

    public :
        explicit SearchParamManager(QWidget *parent = nullptr);
        ~SearchParamManager() noexcept;

    private slots :
        void loadSearchSlot();
        void removeSearchSlot();
        void clearAllSlot();

    signals :
        void loadParam(QString);
        void clearAll();
};

} // END NAMESPACE mariongiciel::gui

#endif // SEARCHPARAMMANAGER_H
