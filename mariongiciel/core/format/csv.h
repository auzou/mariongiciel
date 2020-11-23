#ifndef CSV_H
#define CSV_H
#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QTextStream>

#ifdef QT_DEBUG
#include <QDebug>
#endif

struct CSVHeader {
    QVector<QString> rawHeader;
};

struct CSVData {
    CSVHeader csvHeader;
    QVector<QString> rawData;
};

class CSVParser : public QObject
{
    private :
        const QString separator = QStringLiteral(",");
        CSVHeader csvHeader;
        QVector<CSVData> csvData;

#ifdef linux
    QString CRLF = "\n";
#endif
#ifdef WIN32
    QString CRLF = "\n\r";
#endif
#ifdef __APPLE__
    QString CRLF = "\n";
#endif

    public :
        explicit CSVParser(QObject *parent= nullptr);
        explicit CSVParser(const QString &data, QObject *parent = nullptr);
        explicit CSVParser(const QJsonDocument &doc, QObject *parent = nullptr);
        ~CSVParser() noexcept;


    public :
        void appendColumn(const QString &data);
        void appendLine(const QString &data);

};

#endif // CSV_H
