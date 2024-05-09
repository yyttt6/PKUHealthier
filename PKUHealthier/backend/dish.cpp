#include "dish.h"
#include <QtCore/qmath.h>
Dish::Dish() {}
double* Dish::get_value()
{
    assert(energy>0);
    double* ans = new double[DIM];
    ans[0] = qExp((double)energy*weight[0]);
    ans[1] = qExp((double)protein*weight[1]);
    ans[2] = qExp((double)fat*weight[2]);
    ans[3] = qExp((double)sugar*weight[3]);
    ans[4] = qExp((double)pepper*weight[4]);
    ans[5] = qExp((double)all_veg*weight[5]);
    ans[6] = qExp(money*weight[6]);
    ans[7] = qExp((double)scores*weight[7]);
    return ans;
}
