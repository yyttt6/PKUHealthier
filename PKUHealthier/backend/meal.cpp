#include <assert.h>
#include <QtGlobal>
#include <QRandomGenerator>
#include "meal.h"

Meal::Meal() {}

void Meal::init()
{
    assert(elements.size()>0);
    for(auto p : elements)
    {
        energy+=p->energy;
        protein+=p->protein;
        fat+=p->fat;
        sugar=sugar|(p->sugar);
        pepper=pepper|(p->pepper);
        all_veg=all_veg&(p->all_veg);
        money+=p->money;
        if(p->scores==0) scores=-100;
        else scores+=p->scores;
    }
    scores /= elements.size();
    if(scores<0) scores=-100;
}

void Meal::get_value(const Man &man,int seed)
{
    value = 0;
    QRandomGenerator radg(seed);
    int item[9]={0};
    item[0]=qAbs(energy-man.energy_need);
    item[1]=qAbs(protein-man.protein_need);
    item[2]=qAbs(fat-man.fat_need);
    item[3]=sugar;
    item[4]=pepper;
    item[5]=all_veg;
    item[6]=money;
    item[7]=scores;
    item[8]=radg.generate()%10;
    for(int i=0;i<8;i++)
    {
        value += item[i]*man.weight_vector[i];
    }
}
