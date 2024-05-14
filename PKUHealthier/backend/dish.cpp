#include "dish.h"
#include <QtCore/qmath.h>
#include <QStringList>
#include <QtGlobal>
Dish::Dish() {}

Dish::Dish(QStringList infos){
    id = infos[0].toInt();
    name = infos[1];
    type = infos[2].toInt();
    energy = infos[3].toDouble();
    protein = infos[4].toDouble();
    fat = infos[5].toDouble();
    sugar = infos[6].toInt();
    pepper = infos[7].toInt();
    all_veg = infos[8].toInt();
    money = infos[9].toDouble();
    scores = infos[10].toInt();
    assert(energy>0);
}

QString Dish::save() const{
    QString encodedInfo;
    encodedInfo += QString::number(id) + ",";
    encodedInfo += name + ",";
    encodedInfo += QString::number(type) + ",";
    encodedInfo += QString::number(energy,'f',2) + ",";
    encodedInfo += QString::number(protein,'f',2) + ",";
    encodedInfo += QString::number(fat,'f',2) + ",";
    encodedInfo += QString::number(sugar) + ",";
    encodedInfo += QString::number(pepper) + ",";
    encodedInfo += QString::number(all_veg) + ",";
    encodedInfo += QString::number(money,'f',2) + ",";
    encodedInfo += QString::number(scores)+"\n";
    return encodedInfo;
}
