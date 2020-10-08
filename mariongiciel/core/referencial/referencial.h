#ifndef REFERENCIAL_H
#define REFERENCIAL_H

#include "../iomanagement.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

namespace mariongiciel::core::referencial {

struct Commune final {
    QString code;
    QString codeDepartement;
    QString codePostal;
    QString libelle;
};

/*
class ReferencialBase : public QObject
{
    Q_OBJECT

    private :
    public :
        explicit Referencial(QObject *parent = nullptr);
        ~Referencial();

    private :
        inline Commune getCommune();
};
*/


} // END NAMESPACE mariongiciel::core::referencial

#endif // REFERENCIAL_H
