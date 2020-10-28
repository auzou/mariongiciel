#ifndef CUSTOMITEM_H
#define CUSTOMITEM_H
#include <QWidget>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

#include "../../global.h"

namespace mariongiciel::gui {

class CustomAddItem : public QWidget
{
    Q_OBJECT

    private :
        QPushButton *exitButton;
        QLineEdit *addItemEdit;
        QPushButton *addItemButton;
        QPushButton *createFilter;

    public :
        explicit CustomAddItem(QWidget *parent = nullptr);
        ~CustomAddItem() noexcept;

     signals :
        void addItem(const QString &itemName);
        void exitFilter();
        void addFilter();
};


class CustomItem : public QWidget
{
    Q_OBJECT

    private :
        QString itemName;
        QLineEdit *itemNameEdit;
        QPushButton *removeButton;


    public :
        explicit CustomItem(const QString &itemName, QWidget *parent = nullptr);
        ~CustomItem() noexcept;

    public :
        QString getItemName() const;

    signals :
        void removeItem(const QString &itemName);
};

class CustomItemFilter : public QWidget
{
    Q_OBJECT

    private :
        QString itemName;
        QString itemData;
        QString itemBy;
        QPushButton *removeButton;


    public :
        explicit CustomItemFilter(const QString &itemName, const QString &dataName, const QString &byName, QWidget *parent = nullptr);
        ~CustomItemFilter() noexcept;

    public :
        QString getItemName() const;
        QString getItemData() const;
        QString getItemBy() const;

    signals :
        void removeItem(const QString &itemName, const QString &itemData, const QString &itemBy);
};

} // END NAMESPACE mariongiciel::gui

#endif // CUSTOMITEM_H
