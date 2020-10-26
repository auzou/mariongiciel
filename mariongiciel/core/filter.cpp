#include "filter.h"


mariongiciel::core::Filter::Filter(const QString &path, QObject *parent)
    : QObject(parent), path(path)
{
    if(mariongiciel::core::FileManagement::isExist(this->path))
    {
        QJsonDocument doc = QJsonDocument::fromJson(mariongiciel::core::FileManagement::readFile(this->path).toUtf8());
        this->filterObject= doc.object();
    } else {
        this->filterObject = {
            {"add", QJsonArray()},
            {"delete", QJsonArray()},
            {"replace", QJsonArray()},
        };

        QJsonDocument doc(this->filterObject);

        mariongiciel::core::FileManagement::write(this->path, QString(doc.toJson()).toUtf8());
    }
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
    mariongiciel::core::FileManagement::write(this->path, QString(doc.toJson()).toUtf8());
}

void mariongiciel::core::Filter::removeFilter(const QString &columnName)
{
    QJsonArray removeArray = this->filterObject["replace"].toArray();

    for(int i =0; i<removeArray.size(); i++)
    {
        if(removeArray[i].toObject()["name"] == columnName)
        {
            removeArray.removeAt(i);
            break;
        }
    }
    this->filterObject["replace"] = removeArray;

    QJsonDocument doc(this->filterObject);
    mariongiciel::core::FileManagement::write(this->path, QString(doc.toJson()).toUtf8());
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
