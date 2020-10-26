#ifndef RESPONSE_H
#define RESPONSE_H
#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFileInfo>
#include <QTextStream>
#include <QTextDecoder>

#include "../global.h"
#include "utility.h"
#include "iomanagement.h"
#include "filter.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

namespace mariongiciel::core {

#define MAX_LENGHT_ARRAY 6

class SearchResponse : public QObject
{
    Q_OBJECT

    private :
        QString path;

    public :
        explicit SearchResponse(QObject *parent = nullptr);

        void cutSearchResponse(const QString &data);
        void runConversionProcess(const QJsonArray &mainArray);
        void appendToCSV(const QString &data);

        void setPath(const QString &path);
        QString getPath() const;

        virtual ~SearchResponse() noexcept;

     signals :
        void noTagError();
};


class ConversionProcess : public QObject
{
    Q_OBJECT

    private :
        QMap<QString, QString> columnAndRow;
        void clearColumnRow();

    public :
        explicit ConversionProcess(QObject *parent = nullptr);
        QString getColumnName();
        QMap<QString, QString> getColumnAndRow();
        inline QString getCSVText(const QString &str);
        inline void addRow(const QString &keyRow, const QString &keyObject, const QJsonObject &currentObject);
        QString getCSVData(const QJsonObject &processObject);

        ~ConversionProcess() noexcept;
};

} // END NAMESPACE mariongiciel::core

#endif // RESPONSE_H
