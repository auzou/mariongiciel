#ifndef UTILITY_H
#define UTILITY_H
#include <QVector>
#include <QString>

namespace mariongiciel::core {

inline QString boolToQString(bool b)
{
    return b ? QString("true") : QString("false");
}

static inline QVector<QPair<QString, QString>> specialCharacter = {
    {"\n", "\\n"},
    {"\t", "\\t"},
    {"\"", "\"\""},
};

inline QString escapeQString(QString str)
{
    for(auto &i : specialCharacter)
    {
        str.replace(i.first, i.second);
    }
    return str;
}

} // END NAMESPACE mariongiciel::core

#endif // UTILITY_H
