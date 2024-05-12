#include "dish.h"
#include <QtCore/qmath.h>
#include <QStringList>
Dish::Dish() {}
double Dish::get_value(int preference)
{

    double* sc = new double[DIM];
    sc[0] = qExp((double)energy*weight[0]);
    sc[1] = qExp((double)protein*weight[1]);
    sc[2] = qExp((double)fat*weight[2]);
    sc[3] = qExp((double)sugar*weight[3]);
    sc[4] = qExp((double)pepper*weight[4]);
    sc[5] = qExp((double)all_veg*weight[5]);
    sc[6] = qExp(money*weight[6]);
    sc[7] = qExp((double)scores*weight[7]);

    delete[] sc;
    return 0;
}

Dish::Dish(QStringList infos){
    id = infos[0].toInt();
    name = infos[1];
    type = infos[2].toInt();
    energy = infos[3].toInt();
    protein = infos[4].toInt();
    fat = infos[5].toInt();
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
    encodedInfo += QString::number(energy) + ",";
    encodedInfo += QString::number(protein) + ",";
    encodedInfo += QString::number(fat) + ",";
    encodedInfo += QString::number(sugar) + ",";
    encodedInfo += QString::number(pepper) + ",";
    encodedInfo += QString::number(all_veg) + ",";
    encodedInfo += QString::number(money,'f',2) + ",";
    encodedInfo += QString::number(scores)+"\n";

    return encodedInfo;
}
