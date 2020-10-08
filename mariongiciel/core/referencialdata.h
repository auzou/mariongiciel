#ifndef REFERENCIAL_DATA_H
#define REFERENCIAL_DATA_H
#include <QFile>
#include <QDir>
#include <QTimer>
#include <QVector>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextCodec>

#include "network/authentication.h"
#include "network/referencial.h"
#include "../global.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

namespace mariongiciel::core {

class ReferencialInput : public QObject
{
    Q_OBJECT

    private :
        const QVector<QString> ReferencialName;
        QTimer *resquestTimer;
        const int waitingTime;
        mariongiciel::core::network::Referencial *referencial;
        int cursor;

    private :
        void write(const QString &data);

    public :
        explicit ReferencialInput(mariongiciel::core::network::Authentication *auth, QObject *parent = nullptr);
        void refreshReferencial();
        ~ReferencialInput() noexcept;

    signals :
        void referencialInProgress(int cursor, QString refName);
        void referencialInProgressError(int cursor, QString errorMsg, QString refName);
        void referencialFinished();
};

// delete
class ReferencialOutput : public QObject
{
    Q_OBJECT

    private :
        inline QJsonArray readReferencial(const QString &refName); 
        const QString domaines;
        const QString appellations;
        const QString metiers;
        const QString themes;
        const QString continents;
        const QString pays;
        const QString regions;
        const QString departements;
        const QString communes;
        const QString secteursActivites;
        const QString naturesContrats;
        const QString typesContrats;
        const QString niveauxFormations;
        const QString permis;
        const QString langues;

    public :
        explicit ReferencialOutput(QObject *parent = nullptr);
        QStringList getDomaine();

        QStringList getAppellations();
        QStringList getMetiers();
        QStringList getThemes();
        QStringList getContinents();
        QStringList getPays();
        QStringList getRegions();
        QStringList getDepartements();
        QStringList getCommunes();
        QStringList getSecteursActivites();
        QStringList getNaturesContrats();
        QStringList getTypesContrats();
        QStringList getNiveauxFormations();
        QStringList getPermis();
        QStringList getLangues();

        ~ReferencialOutput() noexcept;
};

} // END NAMESPACE mariongiciel::core

#endif // REFERENCIAL_DATA_H
