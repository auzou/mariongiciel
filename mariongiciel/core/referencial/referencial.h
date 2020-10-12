#ifndef REFERENCIAL_H
#define REFERENCIAL_H

#include "../iomanagement.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

namespace mariongiciel::core::referencial {

struct Communes final {
    QString code;
    QString codeDepartement;
    QString codePostal;
    QString libelle;
};

struct Departements final {
    QString code;
    QString libelle;
    QString regionCode;
    QString regionLibelle;
};


} // END NAMESPACE mariongiciel::core::referencial

#endif // REFERENCIAL_H
