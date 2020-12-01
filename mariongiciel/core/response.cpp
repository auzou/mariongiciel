#include "response.h"


mariongiciel::core::SearchResponse::SearchResponse(Filter *filter, QObject *parent)
    : QObject(parent), filter(filter)
{

}

void mariongiciel::core::SearchResponse::cutSearchResponse(const QString &data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject mainObject = doc.object();
    QJsonArray mainArray = mainObject["resultats"].toArray();
    //this->createFilterFile(QJsonDocument(mainObject["filtresPossibles"].toArray()).toJson());
    this->runConversionProcess(mainArray);
}

void mariongiciel::core::SearchResponse::runConversionProcess(const QJsonArray &mainArray)
{
    ConversionProcess conversionProcess(this->filter);
    if(!FileManagement::isExist(global::rcs::data::_LOCATION_+ this->path + "/final.csv"))
    {
        this->appendToCSV(conversionProcess.getColumnName());
    }
    for(int i =0; i < mainArray.count(); i++)
    {
        this->appendToCSV(conversionProcess.getCSVData(mainArray[i].toObject()));
    }
}

void mariongiciel::core::SearchResponse::appendToCSV(const QString &data)
{
    mariongiciel::core::DirManagement::isNotExistCreate(global::rcs::data::_LOCATION_+ this->path);
    mariongiciel::core::FileManagement::writeAppend(global::rcs::data::_LOCATION_+ this->path + "/final.csv", data.toUtf8());
}

void mariongiciel::core::SearchResponse::setPath(const QString &path)
{
    this->path = path;
}

QString mariongiciel::core::SearchResponse::getPath() const
{
    return this->path;
}

mariongiciel::core::SearchResponse::~SearchResponse() noexcept
{

}

mariongiciel::core::ConversionProcess::ConversionProcess(QObject *parent)
    : QObject(parent)
{
    this->clearColumnRow();
}

mariongiciel::core::ConversionProcess::ConversionProcess(Filter *filter, QObject *parent)
    : QObject(parent), filter(filter)
{
    this->clearColumnRow();
}

void mariongiciel::core::ConversionProcess::clearColumnRow()
{
    this->columnAndRow = {
        // string
        {"id", ""},
        {"intitule", ""},
        {"description", ""},
        {"dateCreation", ""},
        {"dateActualisation", ""},

        // object
        {"lieuTravail-libelle", ""},
        {"lieuTravail-latitude", ""},
        {"lieuTravail-longitude", ""},
        {"lieuTravail-codepostal", ""},
        {"lieuTravail-commune", ""},

        // string
        {"romeCode", ""},
        {"romeLibelle", ""},
        {"appellationlibelle", ""},

        // object
        {"entreprise-nom", ""},
        {"entreprise-description", ""},
        {"entreprise-logo", ""},
        {"entreprise-url", ""},

        // string
        {"typeContrat", ""},
        {"typeContratLibelle", ""},
        {"natureContrat", ""},

        // array 0 -> N
        {"origineOffre-origine", ""},
        {"origineOffre-urlOrigine", ""},
        {"origineOffre-partenaires-nom", ""},
        {"origineOffre-partenaires-logo", ""},
        {"origineOffre-partenaires-url", ""},

        {"experienceExige", ""},
        {"experienceLibelle", ""},
        {"experienceCommentaire", ""},

        // array 0 -> N
        {"formations-domaineLibelle-1", ""},
        {"formations-niveauLibelle-1", ""},
        {"formations-commentaire-1", ""},
        {"formations-exigence-1", ""},
        {"formations-domaineLibelle-2", ""},
        {"formations-niveauLibelle-2", ""},
        {"formations-commentaire-2", ""},
        {"formations-exigence-2", ""},
        {"formations-domaineLibelle-3", ""},
        {"formations-niveauLibelle-3", ""},
        {"formations-commentaire-3", ""},
        {"formations-exigence-3", ""},

        // array 0 -> N
        {"langues-libelle-1", ""},
        {"langues-exigence-1", ""},
        {"langues-libelle-2", ""},
        {"langues-exigence-2", ""},
        {"langues-libelle-3", ""},
        {"langues-exigence-3", ""},

        // array 0 -> N
        {"langues-libelle-1", ""},
        {"langues-exigence-1", ""},
        {"langues-libelle-2", ""},
        {"langues-exigence-2", ""},
        {"langues-libelle-3", ""},
        {"langues-exigence-3", ""},

        // array 0 -> N
        {"permis-libelle-1", ""},
        {"permis-exigence-1", ""},
        {"permis-libelle-2", ""},
        {"permis-exigence-2", ""},
        {"permis-libelle-3", ""},
        {"permis-exigence-3", ""},

        // string
        {"outilsBureautiques", ""},

        // array 0 -> N
        {"competences-code-1", ""},
        {"competences-exigence-1", ""},
        {"competences-libelle-1", ""},
        {"competences-code-2", ""},
        {"competences-exigence-2", ""},
        {"competences-libelle-2", ""},
        {"competences-code-3", ""},
        {"competences-exigence-3", ""},
        {"competences-libelle-3", ""},
        {"competences-code-4", ""},
        {"competences-exigence-4", ""},
        {"competences-libelle-4", ""},
        {"competences-code-5", ""},
        {"competences-exigence-5", ""},
        {"competences-libelle-5", ""},
        {"competences-code-6", ""},
        {"competences-exigence-6", ""},
        {"competences-libelle-6", ""},
        {"competences-code-7", ""},
        {"competences-exigence-7", ""},
        {"competences-libelle-7", ""},

        // object
        {"salaire-libelle", ""},
        {"salaire-commentaire", ""},
        {"salaire-complement1", ""},
        {"salaire-complement2", ""},

        // string
        {"dureeTravailLibelle", ""},
        {"complementExercice", ""},
        {"conditionExercice", ""},
        {"alternance", ""},

        // object
        {"contact-nom", ""},
        {"contact-coordonnees1", ""},
        {"contact-coordonnees2", ""},
        {"contact-coordonnees3", ""},
        {"contact-telephone", ""},
        {"contact-courriel", ""},
        {"contact-urlRecruteur", ""},
        {"contact-urlPostulation", ""},

        // object
        {"agence-telephone", ""},
        {"agence-courriel", ""},

        // string
        {"nombrePostes", ""},
        {"accessibleTH", ""},
        {"deplacementCode", ""},
        {"deplacementLibelle", ""},
        {"qualificationCode", ""},
        {"qualificationLibelle", ""},
        {"secteurActivite", ""},
        {"secteurActiviteLibelle", ""},

        // array 0 -> N
        {"qualitesProfessionnelles-libelle", ""},
        {"qualitesProfessionnelles-description", ""},

        // string
        {"trancheEffectifEtab", ""},

    };
}

QMap<QString, QString> mariongiciel::core::ConversionProcess::getColumnAndRow()
{
    return this->columnAndRow;
}

QString mariongiciel::core::ConversionProcess::getColumnName()
{
    QString column = "";

    for(auto &i : this->columnAndRow.keys())
    {
        column += i + ",";
    }

    return column;
}

inline QString mariongiciel::core::ConversionProcess::getCSVText(const QString &str)
{
    return QString("\""+escapeQString(str)+"\"");
}

inline void  mariongiciel::core::ConversionProcess::addRow(const QString &keyRow, const QString &keyObject, const QJsonObject &currentObject)
{
    if(currentObject.value(keyObject).isString())
    {
        this->columnAndRow[keyRow] = this->getCSVText(this->filter->getFilter(keyRow, currentObject.value(keyObject).toString()));
    }

    if(currentObject.value(keyObject).isDouble())
    {
        this->columnAndRow[keyRow] = QString::number(currentObject.value(keyObject).toDouble());
    }

    if(currentObject.value(keyObject).isBool())
    {
        this->columnAndRow[keyRow] = boolToQString(currentObject.value(keyObject).toBool());
    }
}

QString mariongiciel::core::ConversionProcess::getCSVData(const QJsonObject &processObject)
{
    QString line = "\n";
    this->clearColumnRow();


    for(auto &i : processObject.keys())
    {
        if(!processObject.value(i).isUndefined() && this->columnAndRow.contains(i))
        {
            this->addRow(i, i, processObject);
        }
        if(processObject.value(i).isObject())
        {
            QJsonObject currentObject = processObject.value(i).toObject();
            for(auto &j : currentObject.keys())
            {
                if(this->columnAndRow.contains(QString(i + "-" + j)))
                {
                    this->addRow(QString(i + "-" + j), j, currentObject);
                }
            }
        }

        if(processObject.value(i).isArray())
        {
            QJsonArray array = processObject.value(i).toArray();
            for(int j = 0; j < MAX_LENGHT_ARRAY; j++)
            {
                if(j < array.count())
                {
                    QJsonObject currentObject = array[j].toObject();
                    for(auto &jj : currentObject.keys())
                    {
                        if(this->columnAndRow.contains(QString(i + "-" + jj + "-" +QString::number(j+1))))
                        {
                            this->addRow(QString(i + "-" + jj + "-" +QString::number(j+1)), jj ,currentObject);
                        }
                    }
                } else {
                    break;
                }
            }
        }
    }

    for(auto &i : this->columnAndRow.keys())
    {
        line += this->columnAndRow.value(i) + ",";
    }

    return line;
}

mariongiciel::core::ConversionProcess::~ConversionProcess() noexcept
{

}

