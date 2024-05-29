#include "menu.h"

Menu::SingleDish::SingleDish(QWidget *parent,Dish* d,Menu* mm)
    : QWidget{parent}, dish(d), parentMenu(mm)
{
    /*
    int id;         //也许会需要把每道菜编号
    QString name;
    int type;       //0主食，1菜品，2点心，3套餐
                    //如果是套餐，数值是内部所有饭菜的加和
    double energy;  //卡路里/份     //热量：千卡 蛋白质：克
    double protein; //蛋白质/份
    double fat;     //脂肪/份
    int sugar;      //0-1是否高糖
    int pepper;     //0-1是否狠辣（微辣0）
    int all_veg;    //是不是全素
    double money;   //价格
    int scores;
    */

    selected=0;

    label1->setText(dish->name);
    label2->setText("热量："+QString::number(dish->energy)+"千卡");
    label3->setText("蛋白质："+QString::number(dish->protein)+"克");
    label4->setText("脂肪："+QString::number(dish->fat)+"克");
    label5->setText("¥"+QString::number(dish->money));

    hLayout1->addWidget(label1);
    hLayout1->addStretch(1);
    hLayout1->addWidget(likeButton);
    hLayout1->addWidget(blockButton);
    if(dish->sugar>0)
        hLayout2->addWidget(label6);
    if(dish->pepper>0)
        hLayout2->addWidget(label7);
    if(dish->all_veg>0)
        hLayout2->addWidget(label8);
    hLayout2->addStretch(1);
    hLayout3->addStretch(1);
    hLayout3->addWidget(label5);
    hLayout3->addWidget(chooseButton);

    vLayout->addLayout(hLayout1);
    vLayout->addWidget(label2);
    vLayout->addWidget(label3);
    vLayout->addWidget(label4);
    vLayout->addLayout(hLayout2);
    vLayout->addLayout(hLayout3);


    frame->setLayout(vLayout);
    frame->setFixedSize(QSize(220,160));
    frame->setObjectName("frameframe");
    frame->setStyleSheet("QFrame#frameframe{border-style:solid;border-width:2px;border-color:gray;border-radius:10px;}");

    finalLayout->addWidget(frame);
    setLayout(finalLayout);
    connect(chooseButton,&QPushButton::clicked,this,&SingleDish::selected_change);

}


void Menu::SingleDish::selected_change_only(){
    selected=1-selected;
    if(selected==1){
        chooseButton->setText("取消");
        frame->setStyleSheet("QFrame#frameframe{border-style:solid;border-width:2px;border-color:blue;border-radius:10px;}");
    }
    else{
        chooseButton->setText("选择");
        frame->setStyleSheet("QFrame#frameframe{border-style:solid;border-width:2px;border-color:gray;border-radius:10px;}");
    }

}

void Menu::SingleDish::selected_change(){
    selected_change_only();
    parentMenu->checkRecordButton();
}


void Menu::SingleDish::refresh(){

}


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

    stapleDishes.clear();
    recipeDishes.clear();
    dessertDishes.clear();
    setmealDishes.clear();

    for (int i=0;i<cafe[idx]->dishes.size();i++){
        Dish *pdish = &(cafe[idx]->dishes[i]);
        switch(pdish->type){
        case 0:stapleDishes.append(new SingleDish(this,pdish,this));break;
        case 1:recipeDishes.append(new SingleDish(this,pdish,this));break;
        case 2:dessertDishes.append(new SingleDish(this,pdish,this));break;
        case 3:setmealDishes.append(new SingleDish(this,pdish,this));break;
        default:break;
        }
    }

    gLayout1=new QGridLayout;
    gLayout2=new QGridLayout;
    gLayout3=new QGridLayout;
    gLayout4=new QGridLayout;

    for (int i=0;i<stapleDishes.size();i++)
        gLayout1->addWidget(stapleDishes[i],i/3,i%3);
    for (int i=0;i<recipeDishes.size();i++)
        gLayout2->addWidget(recipeDishes[i],i/3,i%3);
    for (int i=0;i<setmealDishes.size();i++)
        gLayout3->addWidget(setmealDishes[i],i/3,i%3);
    for (int i=0;i<dessertDishes.size();i++)
        gLayout4->addWidget(dessertDishes[i],i/3,i%3);

    gLayout1->setVerticalSpacing(10);
    gLayout2->setVerticalSpacing(10);
    gLayout3->setVerticalSpacing(10);
    gLayout4->setVerticalSpacing(10);


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

    recordLayout=new QHBoxLayout;
    recordLayout->addStretch(1);
    recordLayout->addWidget(cancelButton);
    cancelButton->setVisible(false);
    recordLayout->addSpacing(20);
    recordLayout->addWidget(recordButton);
    recordButton->setEnabled(false);
    recordButton->setStyleSheet("color:gray;");
    connect(cancelButton,&QPushButton::clicked,this,&Menu::cancelAll);
    connect(recordButton,&QPushButton::clicked,this,&Menu::save);

    finalLayout=new QVBoxLayout;
    finalLayout->addWidget(scrollArea);
    finalLayout->addSpacing(20);
    finalLayout->addLayout(recordLayout);
    finalLayout->addSpacing(10);
    setLayout(finalLayout);

    selectedDishes.clear();
}

void Menu::refresh(){

}

void Menu::checkRecordButton(){
    bool hasSelected=0;
    if (hasSelected==0)
        for (int i=0;i<stapleDishes.size();i++)
            if (stapleDishes[i]->selected==1){
                hasSelected=1;
                break;
            }
    if (hasSelected==0)
        for (int i=0;i<recipeDishes.size();i++)
            if (recipeDishes[i]->selected==1){
                hasSelected=1;
                break;
            }
    if (hasSelected==0)
        for (int i=0;i<dessertDishes.size();i++)
            if (dessertDishes[i]->selected==1){
                hasSelected=1;
                break;
            }
    if (hasSelected==0)
        for (int i=0;i<setmealDishes.size();i++)
            if (setmealDishes[i]->selected==1){
                hasSelected=1;
                break;
            }
    if (hasSelected==0){
        cancelButton->setVisible(false);
        recordButton->setEnabled(false);
        recordButton->setStyleSheet("color:gray;");
    }
    else{
        cancelButton->setVisible(true);
        recordButton->setEnabled(true);
        recordButton->setStyleSheet("color:black;");
    }

}

void Menu::cancelAll(){
    for (int i=0;i<stapleDishes.size();i++)
        if (stapleDishes[i]->selected==1)
            stapleDishes[i]->selected_change_only();
    for (int i=0;i<recipeDishes.size();i++)
        if (recipeDishes[i]->selected==1)
            recipeDishes[i]->selected_change_only();
    for (int i=0;i<dessertDishes.size();i++)
        if (dessertDishes[i]->selected==1)
            dessertDishes[i]->selected_change_only();
    for (int i=0;i<setmealDishes.size();i++)
        if (setmealDishes[i]->selected==1)
            setmealDishes[i]->selected_change_only();

    cancelButton->setVisible(false);
    recordButton->setEnabled(false);
    recordButton->setStyleSheet("color:gray;");
}

void Menu::save(){
    cancelAll();


}
