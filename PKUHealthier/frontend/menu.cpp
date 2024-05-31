#include "menu.h"
#include <string>
#include <iostream>

Menu::SingleDish::SingleDish(QWidget *parent, Dish* d, SinglePage* pp)
    : QWidget{parent}, dish(d), parentPage(pp)
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
        parentPage->selected_count++;
        chooseButton->setText("取消");
        frame->setStyleSheet("QFrame#frameframe{border-style:solid;border-width:2px;border-color:blue;border-radius:10px;}");
    }
    else{
        parentPage->selected_count--;
        chooseButton->setText("选择");
        frame->setStyleSheet("QFrame#frameframe{border-style:solid;border-width:2px;border-color:gray;border-radius:10px;}");
    }
}

void Menu::SingleDish::selected_change(){
    selected_change_only();
    parentPage->checkRecordButton();
}

Menu::SinglePage::SinglePage(QWidget *parent, int index)
    : QWidget{parent}
{
    cafe->load(index);

    switch(index){
    case 0:imagePixmap=new QPixmap(":/menu/jia1.png");break;
    case 1:imagePixmap=new QPixmap(":/menu/jia2.png");break;
    case 2:imagePixmap=new QPixmap(":/menu/jia3.png");break;
    case 3:imagePixmap=new QPixmap(":/menu/xue1.png");break;
    case 4:imagePixmap=new QPixmap(":/menu/yan.png");break;
    case 5:imagePixmap=new QPixmap(":/menu/song.png");break;
    case 6:imagePixmap=new QPixmap(":/menu/shao1.png");break;
    case 7:imagePixmap=new QPixmap(":/menu/shao2.png");break;
    case 8:imagePixmap=new QPixmap(":/menu/xue5.png");break;
    case 9:imagePixmap=new QPixmap(":/menu/nong1.png");break;
    case 10:imagePixmap=new QPixmap(":/menu/nong2.png");break;
    case 11:imagePixmap=new QPixmap(":/menu/tong.png");break;
    default:break;
    }

    imageLabel->setScaledContents(true);
    imageLabel->setPixmap(*imagePixmap);

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

    for (int i=0;i<cafe->dishes.size();i++){
        Dish *pdish = &(cafe->dishes[i]);
        switch(pdish->type){
        case 0:stapleDishes.append(new SingleDish(this,pdish,this));break;
        case 1:recipeDishes.append(new SingleDish(this,pdish,this));break;
        case 2:dessertDishes.append(new SingleDish(this,pdish,this));break;
        case 3:setmealDishes.append(new SingleDish(this,pdish,this));break;
        default:break;
        }
    }

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

    vLayout->addWidget(imageLabel);
    vLayout->addSpacing(30);
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

    recordLayout->addStretch(1);
    recordLayout->addWidget(cancelButton);
    cancelButton->setVisible(false);
    recordLayout->addSpacing(20);
    recordLayout->addWidget(recordButton);
    recordButton->setEnabled(false);
    recordButton->setStyleSheet("color:gray;");

    connect(cancelButton,&QPushButton::clicked,this,&SinglePage::cancelAll);
    connect(recordButton,&QPushButton::clicked,this,&SinglePage::save);

    selectLayout->addWidget(scrollArea);
    selectLayout->addSpacing(20);
    selectLayout->addLayout(recordLayout);
    selectLayout->addSpacing(10);
    setLayout(selectLayout);
}

void Menu::SinglePage::checkRecordButton(){
    if (selected_count==0){
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

void Menu::SinglePage::cancelAll(){
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

QString getTimeString(){
    std::time_t now = std::time(nullptr);
    std::tm* tm = std::localtime(&now);
    std::string str(ctime(&now));
    QString timestr= QString::number(1900+tm->tm_year)+"年"
                      +QString::number(1+tm->tm_mon)+"月"
                      +QString::number(tm->tm_mday)+"日 "
                      +QString::fromStdString(str.substr(11,19));
    return timestr;
}

void Menu::SinglePage::save(){

    Meal* meal=new Meal;

    for (int i=0;i<stapleDishes.size();i++)
        if (stapleDishes[i]->selected==1)
            meal->elements.append(stapleDishes[i]->dish);
    for (int i=0;i<recipeDishes.size();i++)
        if (recipeDishes[i]->selected==1)
            meal->elements.append(recipeDishes[i]->dish);
    for (int i=0;i<dessertDishes.size();i++)
        if (dessertDishes[i]->selected==1)
            meal->elements.append(dessertDishes[i]->dish);
    for (int i=0;i<setmealDishes.size();i++)
        if (setmealDishes[i]->selected==1)
            meal->elements.append(setmealDishes[i]->dish);

    cancelAll();

    meal->init();

    Man* man=new Man;
    man->load();
    std::cout<<man->foodRec.week_record.size()<<std::endl;
    std::cout<<"success"<<std::endl;
    man->foodRec.week_record.append(qMakePair(getTimeString(),*meal));
    std::cout<<"success"<<std::endl;
    man->foodRec.number++;
    for (int i=0;i<meal->elements.size();i++){
        man->foodRec.veg_number += meal->elements[i]->all_veg;
        man->foodRec.hot_number += meal->elements[i]->pepper;
    }
    std::cout<<"success"<<std::endl;
    man->save();



}

Menu::Menu(QWidget *parent)
    : QWidget{parent}
{
    Cafeteria* tmpCafe=new Cafeteria;
    /*
    for (int i=0;i<12;i++){
        cafeBox->addItem(tmpCafe->names[i]);
        stackedPage->addWidget(new SinglePage(this,i));
    }
    */

    cafeBox->setFixedWidth(150);

    cafeBox->addItem(tmpCafe->names[0]);
    stackedPage->addWidget(new SinglePage(this,0));
    for (int i=1;i<=10;i++){
        cafeBox->addItem("null");
        stackedPage->addWidget(new SinglePage(this,0));
    }
    cafeBox->addItem(tmpCafe->names[11]);
    stackedPage->addWidget(new SinglePage(this,11));

    connect(cafeBox,&QComboBox::currentIndexChanged,stackedPage,&QStackedWidget::setCurrentIndex);

    cafeLayout->addSpacing(10);
    cafeLayout->addWidget(cafeBox);
    cafeLayout->addStretch(1);

    finalLayout->addLayout(cafeLayout);
    finalLayout->addWidget(stackedPage);
    setLayout(finalLayout);

}

void Menu::refresh(){

}

