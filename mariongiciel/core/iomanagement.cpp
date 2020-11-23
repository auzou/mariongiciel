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

bool mariongiciel::core::FileManagement::isExist(const QString &path)
{
    return QFile::exists(path);
}


const QString mariongiciel::core::FileManagement::readFile(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return QString();
    }

    QString data = QString(QString::fromUtf8(file.readAll()));
    file.close();
    return data;
}

bool mariongiciel::core::FileManagement::write(const QString &path, const QString &data)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }

    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << data;
    file.close();
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
    out.setCodec("UTF-8");
    out << data;

    file.close();
    return true;
}

bool mariongiciel::core::FileManagement::remove(const QString &path)
{
    if(FileManagement::isExist(path))
    {
        if(QFile::remove(path))
        {
            return true;
        }
    }
    return false;
}

bool mariongiciel::core::FileManagement::moveToArchive(const QString &path, const QString &target, bool remove)
{
    Q_UNUSED(path)
    Q_UNUSED(target)
    Q_UNUSED(remove)
    return true;
}

const QString readLine(int line, const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return QString();
    }
    int i = 0;
    while (!file.atEnd()) {
        if(i == line)
        {
            return QString::fromUtf8(file.readLine());
        }
    }

    file.close();
    return QString();
}


const QString mariongiciel::core::LogManagement::head()
{
    return QString(
                   "\tMarionGiciel:" +
                   mariongiciel::global::info::_INFO_VERSION_ +
                   "/" +
                   mariongiciel::global::info::_INFO_VERSION_STATUS_ +
                   "\n\n"
                   );
}

QString mariongiciel::core::LogManagement::formate(const QString &message, const QString &localisation, const QString &level)
{
    return QString("[" + QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd_hh-mm-ss") + "] " +
                   "[" + localisation +"] " +
                   "[" + level + "]\t" +
                   message
    );
}

QString mariongiciel::core::LogManagement::getLevelStr(level_E level_e)
{
    switch (level_e)
    {
        case level_E::_INFO_ : return QString("INFO"); break;
        case level_E::_WARN_ : return QString("WARNING"); break;
        case level_E::_ALERT_ : return QString("ALERT"); break;
        case level_E::_ERROR_ : return QString("ERROR"); break;
        default : {
            LogManagement::log(QObject::tr("can't find log level"), "LogManagement", level_E::_ERROR_);
            return QString("");
        }
    }
}

void mariongiciel::core::LogManagement::clear(bool archive)
{
    for(auto &i : DirManagement::getFile(mariongiciel::global::rcs::log::_LOCATION_))
    {
        if(!archive)
        {
            FileManagement::remove(i.path());
        } else {
            DirManagement::isNotExistCreate(mariongiciel::global::rcs::_LOCATION_ + "archive");
            FileManagement::moveToArchive(i.path(), mariongiciel::global::rcs::_LOCATION_+"archive");
        }
    }
}

void mariongiciel::core::LogManagement::log(const QString &message, const QString &localisation, level_E level_e)
{

    QString level = LogManagement::getLevelStr(level_e);
    QString path = global::rcs::log::_LOCATION_ + level + ".txt";
    if(DirManagement::exist(path))
    {
        DirManagement::create(path);
    }

    if(!FileManagement::isExist(path))
    {
        FileManagement::write(path, LogManagement::head());
    }

    FileManagement::write(path, LogManagement::formate(message, localisation, level));
}

