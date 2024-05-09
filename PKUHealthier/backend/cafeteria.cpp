#include <QRandomGenerator>
#include "cafeteria.h"
#include "dish.h"
#include "man.h"
Cafeteria::Cafeteria() {}
Dish * Cafeteria::recommend(const Man &m,int seed,QString *pname)
{
    bool flag = 0;
    QRandomGenerator prng(seed);
    do{
        int idx = prng.generate()%12;
        Dish * dishes = load(filenames[idx]);

        QString cafe_name = names[idx];
    }while(flag==0)

}
