#ifndef REFERENCIALDIALOG_H
#define REFERENCIALDIALOG_H
#include <QDialog>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>


#include "../core/referencialdata.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

namespace mariongiciel::gui {

class ReferencialDialog : public QDialog
{
    Q_OBJECT

    private :
        mariongiciel::core::ReferencialInput *referencialInput;
        QProgressBar *progressBar;
        QLabel *information;
        QTimer *progressBarTimer;
        int currentValue;

    public :
        explicit ReferencialDialog(mariongiciel::core::network::Authentication *auth, QWidget *parent = nullptr);
        ~ReferencialDialog() noexcept;
};

} // END NAMESPACE mariongiciel::gui

#endif // REFERENCIALDIALOG_H
