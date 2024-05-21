#include "recommend.h"

Recommend::Recommend(QWidget *parent)
    : QWidget{parent}
{
    finalLayout->addWidget(temp);
    setLayout(finalLayout);
}

void Recommend::refresh(){

}
