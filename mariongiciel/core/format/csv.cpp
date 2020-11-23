#include "csv.h"





CSVParser::CSVParser(QObject *parent)
    : QObject(parent)
{

}

CSVParser::CSVParser(const QString &data, QObject *parent)
    : QObject(parent)
{
    Q_UNUSED(data)
   // this->parse(data);
}

CSVParser::CSVParser(const QJsonDocument &doc, QObject *parent)
    : QObject(parent)
{
    Q_UNUSED(doc)
}

CSVParser::~CSVParser() noexcept
{

}

void CSVParser::appendColumn(const QString &data)
{
    QString word;
    this->csvHeader.rawHeader.clear();

    for(auto &i : data)
    {
        if(i!=this->separator)
        {
            word+=i;
        } else {
            this->csvHeader.rawHeader.push_back(word);
            word.clear();
        }
        if(i == this->CRLF)
        {
            return;
        }
    }
    //qDebug()<< this->csvHeader.rawHeader;
}

void CSVParser::appendLine(const QString &data)
{
    QString word;
    CSVData csvData;

    for(auto &i : data)
    {
        if(i!=this->separator)
        {
            word+=i;
        } else {
            CSVData csvData;
            csvData.rawData.push_back(word);
            word.clear();
        }
        if(i == this->CRLF)
        {
            //this->csvData.push_back(word)
            word.clear();
        }
    }
    //qDebug()<< this->csvHeader.rawHeader;
}



