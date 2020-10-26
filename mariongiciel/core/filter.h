#ifndef FILTER_H
#define FILTER_H
#include <QObject>

#include "../global.h"
#include "iomanagement.h"
#include "response.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

namespace mariongiciel::core {

class Filter : public QObject
{
    private :
        QString path;
        QJsonObject filterObject;

    public :
        explicit Filter(const QString &path, QObject *parent = nullptr);
        ~Filter() noexcept;

    public :
        void addFilterReplace(const QString &columnName, QPair<QString, QString> replaceData);
        void removeFilter(const QString &columnName);
        QString getFilter(const QString &columnName, const QString &value);
};

} // END NAMESPACE mariongiciel::core

#endif // FILTER_H
