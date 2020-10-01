#include "iomanagement.h"


/********************DirManagement********************/
void mariongiciel::core::DirManagement::initDirsEnv()
{
    // check if env exist run QMESSAGEBOX ERROR
    QVector<QString> dirs {
        mariongiciel::global::rcs::_LOCATION_,
        mariongiciel::global::rcs::css::_LOCATION_,
        mariongiciel::global::rcs::icon::_LOCATION_,
    };

    for(auto &i : dirs)
    {
        if(!DirManagement::exist(i))
        {
            //error
            if(DirManagement::create(i))
            {
                // succes
            } else {
                // error
            }
        }
    }
}
bool mariongiciel::core::DirManagement::exist(const QString &path)
{
    if(QDir(path).exists())
    {
        return true;
    }
    return false;
}

bool mariongiciel::core::DirManagement::create(const QString &path)
{
    if(QDir().mkdir(path))
    {
        return true;
    }
    return false;
}


bool mariongiciel::core::DirManagement::isNotExistCreate(const QString &path)
{
    if(!DirManagement::exist(path))
    {
        if(DirManagement::create(path))
        {
            return true;
        }
    }
    return false;
}

QVector<QFileInfo> mariongiciel::core::DirManagement::getFile(const QString &path)
{
    QDirIterator it(path, QDir::Files, QDirIterator::Subdirectories);
    QVector<QFileInfo>fileInfoList;
    while (it.hasNext()) {
        fileInfoList.push_back(QFileInfo(QFile(it.next())));
    }

    return fileInfoList;
}

/********************FileManagement********************/

const QString mariongiciel::core::FileManagement::readFile(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return QString();
    }

    return QString(file.readAll());
}

bool mariongiciel::core::FileManagement::write(const QString &path, const QString &data)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }
    QTextStream out(&file);
    out << data;

    return true;
}

bool mariongiciel::core::FileManagement::writeAppend(const QString &path, const QString &data)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        return false;
    }
    QTextStream out(&file);
    out << data;

    return true;
}
