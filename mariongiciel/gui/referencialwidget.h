#ifndef REFERENCIALWIDGET_H
#define REFERENCIALWIDGET_H
#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolButton>
#include <QPainter>
#include <QPushButton>

#include "../core/network/authentication.h"
#include "../core/iomanagement.h"
#include "referencialdialog.h"


#ifdef QT_DEBUG
#include <QDebug>
#endif

namespace mariongiciel::gui {


class ReferencialWidget : public QWidget
{
    Q_OBJECT

    private :
        QTableWidget *downloadList;
        const QVector<QString> fileInfoStr;

    public :
        explicit ReferencialWidget(QWidget *parent = nullptr);
        void paintEvent(QPaintEvent *event) override;
        void setDownloadList();
        ~ReferencialWidget() noexcept;

    private slots :
        void downloadSlot();

    signals :
        void referencialChanged();

};

} // END NAMESPACE mariongiciel::gui

#endif // REFERENCIALWIDGET_H
