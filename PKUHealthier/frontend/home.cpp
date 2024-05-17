#include "home.h"

Home::Home(QWidget *parent)
    : QWidget{parent}
{
    finalLayout->addWidget(temp);
    setLayout(finalLayout);
}

void Home::refresh(){

}
