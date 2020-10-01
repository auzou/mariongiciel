#include <QApplication>

#include "dropdown.h"

//test
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTextDecoder>

#include <QMap>


using namespace mariongiciel::gui;

const QString PATH = "D:/Qt programmation/mariongiciel/rcs/referencial/communes.json";

QStringList getQStringList()
{
    QFile file(PATH);

    if (!file.open(QIODevice::ReadOnly| QIODevice::Text))
    {
        return QStringList();
    }

    QTextStream out(&file);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QJsonDocument doc = QJsonDocument::fromJson(QString(out.readAll()).toUtf8());
    file.close();

    QStringList communeList("...");

    for(auto &&i : doc.array())
    {
        QJsonObject obj = i.toObject();
        communeList.push_back(obj.value("code").toString() + ":" + obj.value("libelle").toString());
    }
    return communeList;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    DropDown *dropDown = new DropDown(QIcon("D:/Qt programmation/mariongiciel/rcs/icon/remove_512.png"), getQStringList());
    MultiSelectDropDown multiDropDown(5, QIcon("D:/Qt programmation/mariongiciel/rcs/icon/remove_512.png"), dropDown);
    multiDropDown.showMaximized();
    return app.exec();
}
