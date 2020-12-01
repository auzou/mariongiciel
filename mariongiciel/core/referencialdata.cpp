#include "referencialdata.h"



mariongiciel::core::Referencial::Referencial(QObject *parent)
    : QObject(parent),
      referancialName({
                        "domaines",
                        "appellations",
                        "metiers",
                        "themes",
                        "continents",
                        "pays",
                        "regions",
                        "departements",
                        "communes",
                        "secteursActivites",
                        "naturesContrats",
                        "typesContrats",
                        "niveauxFormations",
                        "permis",
                        "langues",
      })
{
}

mariongiciel::core::Referencial::~Referencial() noexcept
{

}

const QVector<QString> mariongiciel::core::Referencial::getReferancialName() const
{
    return this->referancialName;
}

const QString mariongiciel::core::Referencial::getName(Referencial_E referencial_e) const
{
    return QString(referancialName[referencial_e]);
}

const QString mariongiciel::core::Referencial::getFileName(Referencial_E referencial_e) const
{
    return QString(global::rcs::referencial::_LOCATION_ + referancialName[referencial_e] + ".json");
}

QVector<QMap<QString, QString>> mariongiciel::core::Referencial::getReferancial(Referencial_E referencial_e) const
{
    QVector<QMap<QString, QString>> dataOut;
    if(this->referancialName.size() < referencial_e)
    {
        return dataOut;
    }

    QString fileData = mariongiciel::core::FileManagement::readFile(this->getFileName(referencial_e));
    if(fileData.isEmpty())
    {
        return dataOut;
    }

    QJsonDocument doc = QJsonDocument::fromJson(fileData.toUtf8());

    QJsonArray mainArray = doc.array();
    if(mainArray.isEmpty())
    {
        return dataOut;
    }


    for(auto i : mainArray)
    {
        QMap<QString, QString> currentData;
        for(auto y : i.toObject().keys())
        {
            if(!i.toObject().value(y).isObject())
            {
                currentData.insert(y, i.toObject().value(y).toString());
            } else {
                QJsonObject nextObject = i.toObject().value(y).toObject();
                for(auto z : nextObject.keys())
                {
                    currentData.insert(y + "-" + z, nextObject.value(z).toString());
                }
            }
        }
        dataOut.push_back(currentData);
    }
    return dataOut;
}

bool mariongiciel::core::Referencial::valuesIsValid(Referencial_E referencial_e, const QMap<QString, QString> &values)
{

    for(auto &i : this->getReferancial(referencial_e))
    {
        if(values == i)
        {
            return true;
        }
    }
    return false;
}

bool mariongiciel::core::Referencial::isExist(Referencial_E referencial_e)
{
    if(DirManagement::exist(this->getFileName(referencial_e)))
    {
        return true;
    }

    return false;
}

bool mariongiciel::core::Referencial::isValidDir()
{
   if(DirManagement::getFile(global::rcs::referencial::_LOCATION_).isEmpty())
   {
       return false;
   }

   for(auto &i : this->getReferancialName())
   {
       if(!FileManagement::isExist(global::rcs::referencial::_LOCATION_ + i + ".json"))
       {
            return false;
       }
   }

   return true;
}




// **

void mariongiciel::core::ReferencialInput::write(const QString &data)
{
    if(!QDir(global::rcs::referencial::_LOCATION_).exists())
    {
        QDir().mkdir(global::rcs::referencial::_LOCATION_);
    }

    QFile file(global::rcs::referencial::_LOCATION_+ this->ReferencialName[this->cursor] +".json");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream outStream(&file);
    outStream << QJsonDocument::fromJson(data.toUtf8()).toJson(QJsonDocument::Indented);
    file.close();

}

mariongiciel::core::ReferencialInput::ReferencialInput(mariongiciel::core::network::Authentication *auth, QObject *parent)
    : QObject(parent),
      ReferencialName({
                        "domaines",
                        "appellations",
                        "metiers",
                        "themes",
                        "continents",
                        "pays",
                        "regions",
                        "departements",
                        "communes",
                        "secteursActivites",
                        "naturesContrats",
                        "typesContrats",
                        "niveauxFormations",
                        "permis",
                        "langues",
      }),
      waitingTime(int(1000))
{
    this->cursor = 0;

    this->resquestTimer = new QTimer(this);

    this->referencial = new mariongiciel::core::network::Referencial(auth, this);

    QObject::connect(this->referencial, &mariongiciel::core::network::Referencial::referencialFinished,
                     [this](QString data)->void {
        this->write(data);
        this->cursor++;
        this->resquestTimer->start(this->waitingTime);
    });

    QObject::connect(this->referencial, &mariongiciel::core::network::Referencial::referencialError,
                     [this](QString errorMsg)->void {
        emit referencialInProgressError(this->cursor, errorMsg, this->ReferencialName[this->cursor]);
        this->resquestTimer->start(3000);
    });

    QObject::connect(this->resquestTimer, &QTimer::timeout, [this]()->void {
        this->resquestTimer->stop();
        this->refreshReferencial();
    });
}

void mariongiciel::core::ReferencialInput::refreshReferencial()
{
    if(this->cursor < this->ReferencialName.size())
    {
       emit referencialInProgress(this->cursor, this->ReferencialName[this->cursor]);
       this->referencial->runReferencial(this->ReferencialName[this->cursor]);
    } else {
        this->cursor = 0;
        this->resquestTimer->stop();
        emit referencialFinished();
    }
}

mariongiciel::core::ReferencialInput::~ReferencialInput() noexcept
{

}

inline QJsonArray mariongiciel::core::ReferencialOutput::readReferencial(const QString &refName)
{
    QFile file(global::rcs::referencial::_LOCATION_+ refName +".json");

    if (!file.open(QIODevice::ReadOnly| QIODevice::Text))
    {
        return QJsonArray();
    }

    QTextStream out(&file);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QJsonDocument doc = QJsonDocument::fromJson(QString(out.readAll()).toUtf8());
    file.close();

    return QJsonArray(doc.array());
}

mariongiciel::core::ReferencialOutput::ReferencialOutput(QObject *parent)
    : QObject(parent),
    domaines("domaines"),
    appellations("appellations"),
    metiers("metiers"),
    themes("themes"),
    continents("continents"),
    pays("pays"),
    regions("regions"),
    departements("departements"),
    communes("communes"),
    secteursActivites("secteursActivites"),
    naturesContrats("naturesContrats"),
    typesContrats("typesContrats"),
    niveauxFormations("niveauxFormations"),
    permis("permis"),
    langues("langues")
{

}

QStringList mariongiciel::core::ReferencialOutput::getDomaine()
{
    QJsonArray mainArray = this->readReferencial(this->domaines);
    QStringList domaineList("...");

    for(auto &&i : mainArray)
    {
        QJsonObject obj = i.toObject();
        domaineList.push_back(obj.value("code").toString() + ":" + obj.value("libelle").toString());
    }
    return domaineList;
}

QStringList mariongiciel::core::ReferencialOutput::getAppellations()
{
    QJsonArray mainArray = this->readReferencial(this->appellations);
    QStringList domaineList("...");

    for(auto &&i : mainArray)
    {
        QJsonObject obj = i.toObject();
        domaineList.push_back(obj.value("code").toString() + ":" + obj.value("libelle").toString());
    }
    return domaineList;
}

QStringList mariongiciel::core::ReferencialOutput::getMetiers()
{
    QJsonArray mainArray = this->readReferencial(this->metiers);
    QStringList domaineList("...");

    for(auto &&i : mainArray)
    {
        QJsonObject obj = i.toObject();
        domaineList.push_back(obj.value("code").toString() + ":" + obj.value("libelle").toString());
    }
    return domaineList;
}

QStringList mariongiciel::core::ReferencialOutput::getThemes()
{
    QJsonArray mainArray = this->readReferencial(this->themes);
    QStringList domaineList("...");

    for(auto &&i : mainArray)
    {
        QJsonObject obj = i.toObject();
        domaineList.push_back(obj.value("code").toString() + ":" + obj.value("libelle").toString());
    }
    return domaineList;
}

QStringList mariongiciel::core::ReferencialOutput::getContinents()
{
    QJsonArray mainArray = this->readReferencial(this->continents);
    QStringList domaineList("...");

    for(auto &&i : mainArray)
    {
        QJsonObject obj = i.toObject();
        domaineList.push_back(obj.value("code").toString() + ":" + obj.value("libelle").toString());
    }
    return domaineList;
}

QStringList mariongiciel::core::ReferencialOutput::getPays()
{
    QJsonArray mainArray = this->readReferencial(this->pays);
    QStringList domaineList("...");

    for(auto &&i : mainArray)
    {
        QJsonObject obj = i.toObject();
        domaineList.push_back(obj.value("code").toString() + ":" + obj.value("libelle").toString());
    }
    return domaineList;
}

QStringList mariongiciel::core::ReferencialOutput::getRegions()
{
    QJsonArray mainArray = this->readReferencial(this->regions);
    QStringList domaineList("...");

    for(auto &&i : mainArray)
    {
        QJsonObject obj = i.toObject();
        domaineList.push_back(obj.value("code").toString() + ":" + obj.value("libelle").toString());
    }
    return domaineList;
}

QStringList mariongiciel::core::ReferencialOutput::getDepartements()
{
    QJsonArray mainArray = this->readReferencial(this->departements);
    QStringList domaineList("...");

    for(auto &&i : mainArray)
    {
        QJsonObject obj = i.toObject();
        domaineList.push_back(obj.value("code").toString() + ":" + obj.value("libelle").toString());
    }
    return domaineList;
}

QStringList mariongiciel::core::ReferencialOutput::getCommunes()
{
    QJsonArray mainArray = this->readReferencial(this->communes);
    QStringList domaineList("...");

    for(auto &&i : mainArray)
    {
        QJsonObject obj = i.toObject();
        domaineList.push_back(obj.value("code").toString() + ":" + obj.value("libelle").toString());
    }
    return domaineList;
}

QStringList mariongiciel::core::ReferencialOutput::getSecteursActivites()
{
    QJsonArray mainArray = this->readReferencial(this->secteursActivites);
    QStringList domaineList("...");

    for(auto &&i : mainArray)
    {
        QJsonObject obj = i.toObject();
        domaineList.push_back(obj.value("code").toString() + ":" + obj.value("libelle").toString());
    }
    return domaineList;
}

QStringList mariongiciel::core::ReferencialOutput::getNaturesContrats()
{
    QJsonArray mainArray = this->readReferencial(this->naturesContrats);
    QStringList domaineList("...");

    for(auto &&i : mainArray)
    {
        QJsonObject obj = i.toObject();
        domaineList.push_back(obj.value("code").toString() + ":" + obj.value("libelle").toString());
    }
    return domaineList;
}

QStringList mariongiciel::core::ReferencialOutput::getTypesContrats()
{
    QJsonArray mainArray = this->readReferencial(this->typesContrats);
    QStringList domaineList("...");

    for(auto &&i : mainArray)
    {
        QJsonObject obj = i.toObject();
        domaineList.push_back(obj.value("code").toString() + ":" + obj.value("libelle").toString());
    }
    return domaineList;
}

QStringList mariongiciel::core::ReferencialOutput::getNiveauxFormations()
{
    QJsonArray mainArray = this->readReferencial(this->niveauxFormations);
    QStringList domaineList("...");

    for(auto &&i : mainArray)
    {
        QJsonObject obj = i.toObject();
        domaineList.push_back(obj.value("code").toString() + ":" + obj.value("libelle").toString());
    }
    return domaineList;
}

QStringList mariongiciel::core::ReferencialOutput::getPermis()
{
    QJsonArray mainArray = this->readReferencial(this->permis);
    QStringList domaineList("...");

    for(auto &&i : mainArray)
    {
        QJsonObject obj = i.toObject();
        domaineList.push_back(obj.value("code").toString() + ":" + obj.value("libelle").toString());
    }
    return domaineList;
}

QStringList mariongiciel::core::ReferencialOutput::getLangues()
{
    QJsonArray mainArray = this->readReferencial(this->langues);
    QStringList domaineList("...");

    for(auto &&i : mainArray)
    {
        QJsonObject obj = i.toObject();
        domaineList.push_back(obj.value("code").toString() + ":" + obj.value("libelle").toString());
    }
    return domaineList;
}

mariongiciel::core::ReferencialOutput::~ReferencialOutput() noexcept
{

}
