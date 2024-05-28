#include "menu.h"


Menu::Menu(QWidget *parent)
    : QWidget{parent}
{
    for (int i=0;i<1;i++){  //应为12
        cafe[i]=new Cafeteria();
        cafe[i]->load(i);
    }

    typelabel1->setFixedWidth(40);
    typelabel2->setFixedWidth(40);
    typelabel3->setFixedWidth(40);
    typelabel4->setFixedWidth(40);

    line1->setFrameShape(QFrame::HLine);
    line2->setFrameShape(QFrame::HLine);
    line3->setFrameShape(QFrame::HLine);
    line4->setFrameShape(QFrame::HLine);

    typeLayout1->addWidget(typelabel1);
    typeLayout1->addWidget(line1);
    typeLayout2->addWidget(typelabel2);
    typeLayout2->addWidget(line2);
    typeLayout3->addWidget(typelabel3);
    typeLayout3->addWidget(line3);
    typeLayout4->addWidget(typelabel4);
    typeLayout4->addWidget(line4);

    showpage(0);

}

void Menu::showpage(int idx){
    staple.clear();
    recipe.clear();
    dessert.clear();
    setmeal.clear();
    for (int i=0;i<cafe[idx]->dishes.size();i++){
        Dish *pdish = &(cafe[idx]->dishes[i]);
        switch(pdish->type){
        case 0: staple.append(pdish);break;
        case 1: recipe.append(pdish);break;
        case 2: dessert.append(pdish);break;
        case 3: setmeal.append(pdish);break;
        default: break;
        }
    }
    gLayout1=new QGridLayout;
    gLayout2=new QGridLayout;
    gLayout3=new QGridLayout;
    gLayout4=new QGridLayout;

    for (int i=0;i<staple.size();i++)
        gLayout1->addWidget((new SingleDish(this,staple[i]))->frame,i/3,i%3);
    for (int i=0;i<recipe.size();i++)
        gLayout2->addWidget((new SingleDish(this,recipe[i]))->frame,i/3,i%3);
    for (int i=0;i<setmeal.size();i++)
        gLayout3->addWidget((new SingleDish(this,setmeal[i]))->frame,i/3,i%3);
    for (int i=0;i<dessert.size();i++)
        gLayout4->addWidget((new SingleDish(this,dessert[i]))->frame,i/3,i%3);

    gLayout1->setVerticalSpacing(30);
    gLayout2->setVerticalSpacing(30);
    gLayout3->setVerticalSpacing(30);
    gLayout4->setVerticalSpacing(30);


    scrollWidget=new QWidget;
    vLayout=new QVBoxLayout(scrollWidget);

    vLayout->addLayout(typeLayout1);
    vLayout->addSpacing(30);
    vLayout->addLayout(gLayout1);
    vLayout->addSpacing(50);
    vLayout->addLayout(typeLayout2);
    vLayout->addSpacing(30);
    vLayout->addLayout(gLayout2);
    vLayout->addSpacing(50);
    vLayout->addLayout(typeLayout3);
    vLayout->addSpacing(30);
    vLayout->addLayout(gLayout3);
    vLayout->addSpacing(50);
    vLayout->addLayout(typeLayout4);
    vLayout->addSpacing(30);
    vLayout->addLayout(gLayout4);
    vLayout->setContentsMargins(30,50,30,50);

    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);
    finalLayout=new QVBoxLayout;
    finalLayout->addWidget(scrollArea);
    setLayout(finalLayout);

}

void Menu::refresh(){

}
