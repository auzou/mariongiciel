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

#ifdef QT_DEBUG
#include <QDebug>
#endif

namespace mariongiciel::core {

#define MAX_LENGHT_ARRAY 6

class SearchResponse : public QObject
{
    Q_OBJECT

    private :
        int tag;
        QString path;
        const QString tagStr;

    public :
        explicit SearchResponse(QObject *parent = nullptr);

        void cutSearchResponse(const QString &data);
        void createDir();
        void createCompactFile(const QString &data);
        void createIndentedFile(const QString &data);
        void createFilterFile(const QString &data);

        void runConversionProcess();
        void appendToCSV(const QString &data);

        void setTag(const int tag);
        void setPath(const QString &path);
        int getTag() const;
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
        inline QString getCSVText(const QString &str);
        inline void addRow(const QString &keyRow, const QString &keyObject, const QJsonObject &currentObject);
        QString getCSVData(const QJsonObject &processObject);

        ~ConversionProcess() noexcept;
};

} // END NAMESPACE mariongiciel::core

#endif // RESPONSE_H
