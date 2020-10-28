#include "filter.h"

mariongiciel::core::Filter::Filter(QObject *parent)
    : QObject(parent)
{

}


mariongiciel::core::Filter::Filter(const QString &fileName, QObject *parent)
    : QObject(parent)
{
    this->setFilter(fileName);
}

mariongiciel::core::Filter::~Filter() noexcept
{

}

void mariongiciel::core::Filter::addFilterReplace(const QString &columnName, QPair<QString, QString> replaceData)
{
    QJsonArray replaceArray = this->filterObject["replace"].toArray();
    QJsonObject replaceObject = {
        {"name", columnName},
        {"data", replaceData.first},
        {"by", replaceData.second},
    };

    for(auto i : replaceArray)
    {
        if(replaceObject == i.toObject())
        {
            return;
        }
    }

    replaceArray.append(replaceObject);
    this->filterObject["replace"] = replaceArray;

    QJsonDocument doc(this->filterObject);
    mariongiciel::core::FileManagement::write(mariongiciel::global::rcs::filter::_LOCATION_ + this->fileName, QString(doc.toJson()).toUtf8());
}

void mariongiciel::core::Filter::removeFilter(const QString &columnName, const QString &data, const QString &by)
{
    QJsonArray removeArray = this->filterObject["replace"].toArray();

    for(int i =0; i<removeArray.size(); i++)
    {
        if(removeArray[i].toObject()["name"] == columnName
                && removeArray[i].toObject()["data"] == data
                && removeArray[i].toObject()["by"] == by)
        {
            removeArray.removeAt(i);
            break;
        }
    }
    this->filterObject["replace"] = removeArray;

    QJsonDocument doc(this->filterObject);
    mariongiciel::core::FileManagement::write(mariongiciel::global::rcs::filter::_LOCATION_ + this->fileName, QString(doc.toJson()).toUtf8());
}

QString mariongiciel::core::Filter::getFilter(const QString &columnName, const QString &value)
{
    QString response = value;
    QJsonArray mainArray = this->filterObject["replace"].toArray();
    if(!mainArray.isEmpty())
    {
        for(auto j : mainArray)
        {
            if(j.toObject()["name"] == columnName)
            {
                if(value.contains(j.toObject()["data"].toString()))
                {
                    response.replace(j.toObject()["data"].toString(), j.toObject()["by"].toString());
                }
            }
         }
    }

    return response;
}

QVector<QMap<QString, QString>> mariongiciel::core::Filter::getFilterList() const
{
    QVector<QMap<QString, QString>> filterList;
    if(this->filterObject.isEmpty() && this->filterObject["replace"].toArray().isEmpty())
    {
        return filterList;
    }

    for(auto i : this->filterObject["replace"].toArray())
    {
        QMap<QString, QString> currentData;
        for(auto &y : i.toObject().keys())
        {
            currentData.insert(y, i.toObject().value(y).toString());
        }
        filterList.push_back(currentData);
    }

    return filterList;
}

void mariongiciel::core::Filter::setFilter(const QString &fileName)
{
    if(fileName.isEmpty()){
        return;
    }

    this->fileName = fileName + ".json";
    if(mariongiciel::core::FileManagement::isExist(mariongiciel::global::rcs::filter::_LOCATION_+this->fileName))
    {
        QJsonDocument doc = QJsonDocument::fromJson(
                    mariongiciel::core::FileManagement::readFile(mariongiciel::global::rcs::filter::_LOCATION_ + this->fileName).toUtf8()
        );
        this->filterObject= doc.object();
    } else {
        this->filterObject = {
            {"replace", QJsonArray()}
        };

        QJsonDocument doc(this->filterObject);

        mariongiciel::core::FileManagement::write(mariongiciel::global::rcs::filter::_LOCATION_+this->fileName, QString(doc.toJson()).toUtf8());
    }
}
