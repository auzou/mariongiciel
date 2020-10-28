#ifndef FILTERWIDGET_H
#define FILTERWIDGET_H
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QComboBox>

#include "listview/customitem.h"

#include "../core/filter.h"
#include "../core/response.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

namespace mariongiciel::gui {

class FilterViewDialog : public QDialog
{
    private :
        QStringList oldData;
        QComboBox *filterNameList;
        QLineEdit *filterData;
        QLineEdit *filterBy;
        QPushButton *saveButton;
        mariongiciel::core::Filter *filter;

    public :
        explicit FilterViewDialog(mariongiciel::core::Filter *filter, QWidget *parent = nullptr);
        explicit FilterViewDialog(const QString &name, const QString &data, const QString &by, mariongiciel::core::Filter *filter, QWidget *parent = nullptr);
        ~FilterViewDialog() noexcept;
};

class FilterDialog : public QDialog
{
    Q_OBJECT

    private :
        QListWidget *filterSaveList;
        QListWidget  *columnList;
        mariongiciel::core::Filter *filter;
        QLabel *filterSelected;

    public :
        explicit FilterDialog(QString filterSelected = "", QWidget *parent = nullptr);
        ~FilterDialog() noexcept;

    public :
        void setColumnList();
        QString getFilterName() const;

    private slots :
        void addItem(const QString &itemName);
        void addFilter();
};

}// END NAMESPACE mariongiciel::gui

#endif // FILTERWIDGET_H
