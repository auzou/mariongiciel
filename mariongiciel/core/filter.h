#ifndef FILTER_H
#define FILTER_H
#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "../global.h"
#include "iomanagement.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

namespace mariongiciel::core {

class Filter : public QObject
{
    Q_OBJECT

    private :
        QString fileName;
        QJsonObject filterObject;

    public :
        explicit Filter(QObject *parent = nullptr);
        explicit Filter(const QString &path, QObject *parent = nullptr);
        ~Filter() noexcept;

    public :
        void addFilterReplace(const QString &columnName, QPair<QString, QString> replaceData);
        void removeFilter(const QString &columnName, const QString &data, const QString &by);
        QString getFilter(const QString &columnName, const QString &value);
        QVector<QMap<QString, QString>> getFilterList() const;

    public :
        void setFilter(const QString &fileName);
};

} // END NAMESPACE mariongiciel::core

#endif // FILTER_H
