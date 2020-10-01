#ifndef DROPDOWN_H
#define DROPDOWN_H
#include <QWidget>
#include <QCompleter>
#include <QLineEdit>
#include <QStringList>
#include <QVBoxLayout>
#include <QAbstractItemView>
#include <QPainter>
#include <QStyleOption>
#include <QAction>
#include <QPushButton>

#ifdef QT_DEBUG
#include <QDebug>
#endif

namespace mariongiciel::gui {

class DropDown;

class MultiSelectDropDown : public QWidget
{
    Q_OBJECT

    private :
        const int maxSelect;
        const QIcon removeIcon;
        QVector<QPair<QString, QWidget*>> selection;
        QVBoxLayout *mainLayout;
        DropDown *dropDown;

    private :
        void addCustomWidget(const QString &text);

    public :
        explicit MultiSelectDropDown(const int maxSelect, const QIcon &removeIcon, DropDown *dropDown, QWidget *parent = nullptr);
        ~MultiSelectDropDown() noexcept;

    public :
         QStringList getSelection() const;

    private slots :
        void addSelection(const QString &text);
        void removeSelection();

    signals :
        void selectChanged(const QStringList &selectList);
};

class CustomLineEdit;

class DropDown : public QWidget
{
    Q_OBJECT

    private :
        CustomLineEdit *customLineEdit;

    public :
        explicit DropDown(const QIcon &actionIcon, const QStringList &list, QWidget *parent = nullptr);
        ~DropDown() noexcept override;

    signals :
        void textChanged(const QString &text);

};

class CustomLineEdit : public QLineEdit
{
    Q_OBJECT

    private :

    public :
        explicit CustomLineEdit(const QStringList &list, QWidget *parent = nullptr);
        void mousePressEvent(QMouseEvent *mouseEvent) override;
        ~CustomLineEdit() noexcept override;

     signals :
        void currentTextActivated(const QString &text);
};


} // END NAMESPACE mariongiciel::gui

#endif // DROPDOWN_H
