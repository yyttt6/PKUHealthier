#include "man.h"
#include <assert.h>
Man::Man() {}

double exercise_level[5] = {1.0,1.2,1.375,1.55,1.725};
double protein_rate[5] = {0.9,0.9,1.1,1.4,1.6};

void Man::init()
{
    assert(weight>0&&height>0);
    basic_energy = 10*weight + 6.25*height -5*age -161 + 166*gender;
    energy_need = basic_energy * exercise_level[target] *2/5;
    protein_need = weight * protein_rate[target] *2/5;
    if(gender==0) protein_need /= 0.85;
    fat_need = (energy_need/45)*2/5;
    if(target<=1) weight_vector[5]+=10;
    if(target<=1) weight_vector[0]+=0.5;
    if(target>=3) weight_vector[1]+=1;
    if(preference[0]==0) weight_vector[3]-=5;
    if(preference[0]==2) weight_vector[3]+=5;
    if(preference[1]==0) weight_vector[4]-=5;
    if(preference[1]==2) weight_vector[4]+=5;
    if(preference[3]==0) weight_vector[6]-=0.5;
    if(preference[2]==0) weight_vector[7]=0;
    if(preference[2]==2) weight_vector[7]+=10;
}
