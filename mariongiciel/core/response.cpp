#include "response.h"


mariongiciel::core::SearchResponse::SearchResponse(QObject *parent)
    : QObject(parent), tagStr(QStringLiteral("-part_"))
{
    this->tag = 1;
}

void mariongiciel::core::SearchResponse::cutSearchResponse(const QString &data)
{
    this->createDir();

    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject mainObject = doc.object();

    this->createFilterFile(QJsonDocument(mainObject["filtresPossibles"].toArray()).toJson());
    this->createCompactFile(QJsonDocument(mainObject["resultats"].toArray()).toJson());
    this->createIndentedFile(QJsonDocument(mainObject["resultats"].toArray()).toJson());

    this->runConversionProcess();
}

void mariongiciel::core::SearchResponse::createDir()
{
    if(!QDir(global::rcs::data::_LOCATION_).exists())
    {
        QDir().mkdir(global::rcs::data::_LOCATION_);
    }

    if(!QDir(global::rcs::data::_LOCATION_+this->path).exists())
    {
        QDir().mkdir(global::rcs::data::_LOCATION_+this->path);
    }

}

void mariongiciel::core::SearchResponse::createCompactFile(const QString &data)
{
    QFile file(global::rcs::data::_LOCATION_+ this->path
                        + "/compact_data" + this->tagStr
                 + QString::number(this->tag) + ".json");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream outStream(&file);
    outStream << QJsonDocument::fromJson(data.toUtf8()).toJson(QJsonDocument::Compact);
    file.close();
}

void mariongiciel::core::SearchResponse::createIndentedFile(const QString &data)
{
    QFile file(global::rcs::data::_LOCATION_+ this->path
                       + "/indented_data" + this->tagStr
                + QString::number(this->tag) + ".json");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream outStream(&file);
    outStream << QJsonDocument::fromJson(data.toUtf8()).toJson(QJsonDocument::Indented);
    file.close();
}

void mariongiciel::core::SearchResponse::createFilterFile(const QString &data)
{
    QFile file(global::rcs::data::_LOCATION_+ this->path + "/filter.json");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream outStream(&file);
    outStream << QJsonDocument::fromJson(data.toUtf8()).toJson(QJsonDocument::Indented);
    file.close();
}

void mariongiciel::core::SearchResponse::runConversionProcess()
{
    QFile file(global::rcs::data::_LOCATION_+ this->path
                       + "/compact_data" + this->tagStr
                + QString::number(this->tag) + ".json");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream out(&file);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QJsonDocument doc = QJsonDocument::fromJson(QString(out.readAll()).toUtf8());

    file.close();
    QJsonArray mainArray = doc.array();
    ConversionProcess conversionProcess;

    this->appendToCSV(conversionProcess.getColumnName());
    for(int i =0; i < mainArray.count(); i++)
    {
        this->appendToCSV(conversionProcess.getCSVData(mainArray[i].toObject()));
    }
}

void mariongiciel::core::SearchResponse::appendToCSV(const QString &data)
{
    QFile file(global::rcs::data::_LOCATION_+ this->path + "/final.csv");
    if (!file.open(QFile::Text | QIODevice::Append))
    {
        return;
    }

    QTextStream outStream(&file);
    outStream << data.toUtf8();
    file.close();
}

void mariongiciel::core::SearchResponse::setTag(const int tag)
{
    this->tag = tag;
}

void mariongiciel::core::SearchResponse::setPath(const QString &path)
{
    this->path = path;
}

int mariongiciel::core::SearchResponse::getTag() const
{
    return this->tag;
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
        this->columnAndRow[keyRow] = this->getCSVText(currentObject.value(keyObject).toString());
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

