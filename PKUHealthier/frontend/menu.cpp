#include "menu.h"
#include <string>

Menu::SingleDish::SingleDish(QWidget *parent, Dish* d, SinglePage* pp)
    : QWidget{parent}, dish(d), parentPage(pp)
{
    label1->setText(dish->name);
    label1->setStyleSheet("QLabel{font-size:15px;font-family:微软雅黑;font-weight:bold;letter-spacing:1px;}");

    label2->setText("热量："+QString::number(dish->energy)+" 千卡");
    label3->setText("蛋白质："+QString::number(dish->protein)+" 克");
    label4->setText("脂肪："+QString::number(dish->fat)+" 克");

    label5->setText("¥ "+QString::number(dish->money));
    label5->setStyleSheet("QLabel{font-size:13px;}");

    label6->setStyleSheet("QLabel{border-style:solid;border-width:1px;border-radius:4px;border-color:rgb(183,149,11);background:rgb(249,231,159);}");
    label6->setFixedHeight(22);

    label7->setStyleSheet("QLabel{border-style:solid;border-width:1px;border-radius:4px;border-color:rgb(203,67,53);background:rgb(245,183,177);}");
    label7->setScaledContents(true);
    label7->setPixmap(QPixmap(":/menu/pepper.png"));
    label7->setFixedSize(QSize(22,22));
    label7->setMargin(2);

    label8->setStyleSheet("QLabel{border-style:solid;border-width:1px;border-radius:4px;border-color:rgb(34,153,84);background:rgb(171,235,198);}");
    label8->setFixedHeight(22);

    scoreButton->setStyleSheet("QPushButton{font-size:13px;}");
    scoreButton->setFixedWidth(55);

    chooseButton->setStyleSheet("QPushButton{font-size:13px;}");
    chooseButton->setFixedWidth(55);

    hLayout1->addWidget(label1);
    hLayout1->addStretch(1);
    hLayout1->addWidget(scoreButton);

    if(dish->sugar>0)
        hLayout2->addWidget(label6);
    if(dish->pepper>0)
        hLayout2->addWidget(label7);
    if(dish->all_veg>0)
        hLayout2->addWidget(label8);
    hLayout2->addStretch(1);

    hLayout3->addStretch(1);
    hLayout3->addWidget(label5);
    hLayout3->addSpacing(10);
    hLayout3->addWidget(chooseButton);

    vLayout->addLayout(hLayout1);
    vLayout->addWidget(label2);
    vLayout->addWidget(label3);
    vLayout->addWidget(label4);
    vLayout->addLayout(hLayout2);
    vLayout->addStretch(1);
    vLayout->addLayout(hLayout3);
    vLayout->setSpacing(8);
    vLayout->setContentsMargins(12,12,12,12);

    frame->setLayout(vLayout);
    frame->setFixedSize(QSize(240,180));
    frame->setObjectName("frameframe");
    frame->setStyleSheet("QFrame#frameframe{border-style:dashed;border-width:2px;border-color:gray;border-radius:10px;}");

    finalLayout->addStretch(1);
    finalLayout->addWidget(frame);
    finalLayout->addStretch(1);

    setLayout(finalLayout);

    connect(scoreButton,&QPushButton::clicked,this,&SingleDish::score_update);
    connect(chooseButton,&QPushButton::clicked,this,&SingleDish::selected_change);
}

void Menu::SingleDish::selected_change_only(){
    selected=1-selected;
    if(selected==1){
        parentPage->selected_count++;
        chooseButton->setText("取消");
        frame->setStyleSheet("QFrame{background-color:rgb(232,241,247);}"
                             "QFrame#frameframe{border-style:solid;border-width:2px;border-color:rgb(52,152,219);border-radius:10px;}");
    }
    else{
        parentPage->selected_count--;
        chooseButton->setText("选择");
        frame->setStyleSheet("QFrame#frameframe{border-style:dashed;border-width:2px;border-color:gray;border-radius:10px;}");
    }
}

void Menu::SingleDish::selected_change(){
    selected_change_only();
    parentPage->checkRecordButton();
}

void Menu::SingleDish::score_update(){
    ((new ScoreDialog(this,this))->dialog)->exec();  //阻塞调用
}

Menu::SingleDish::ScoreDialog::ScoreDialog(QWidget *parent, SingleDish* sd)
    : QWidget{parent}, parentDish(sd)
{
    dialog->setWindowTitle("请为这道菜品评分~");
    dialog->setStyleSheet("background:rgb(242,243,244);");

    dishName->setText(sd->parentPage->cafe->names[sd->parentPage->idx]+" "+sd->dish->name+"：");
    dishName->setStyleSheet("QLabel{font-size:18px;font-family:微软雅黑;font-weight:bold;letter-spacing:1px;}");

    currentLove->setText("当前您对这道菜品的好感度为"+QString::number(sd->parentPage->cafe->dishes[sd->dish->id-1].scores)+"~");
    currentLove->setStyleSheet("QLabel{font-size:15px;font-weight:bold;letter-spacing:1px;}");

    loveText1->setText("注：好感度影响菜品推荐，最低为0，最高为10；");
    loveText1->setStyleSheet("QLabel{font-size:14px;}");

    loveText2->setText("吃一次该菜品自动增加好感度，也可以通过评分改变好感度。");
    loveText2->setStyleSheet("QLabel{font-size:14px;padding-left:25px;}");

    buttonLayout->addStretch(1);
    for (int i=0;i<5;i++){
        scoreButton[i]=new QPushButton;
        scoreButton[i]->setFixedSize(QSize(50,50));
        scoreButton[i]->setIconSize(QSize(45,45));
        scoreButton[i]->setStyleSheet("QPushButton{border:none;}");
        buttonLayout->addWidget(scoreButton[i]);
    }
    buttonLayout->addStretch(1);

    printStar2();

    connect(scoreButton[0],&QPushButton::clicked,this,&ScoreDialog::printStar0);
    connect(scoreButton[1],&QPushButton::clicked,this,&ScoreDialog::printStar1);
    connect(scoreButton[2],&QPushButton::clicked,this,&ScoreDialog::printStar2);
    connect(scoreButton[3],&QPushButton::clicked,this,&ScoreDialog::printStar3);
    connect(scoreButton[4],&QPushButton::clicked,this,&ScoreDialog::printStar4);

    CancelButton->setStyleSheet("QPushButton{font-size:13px;}");
    ConfirmButton->setStyleSheet("QPushButton{font-size:13px;}");

    resultLayout->addSpacing(300);
    resultLayout->addWidget(CancelButton);
    resultLayout->addSpacing(10);
    resultLayout->addWidget(ConfirmButton);
    connect(CancelButton,&QPushButton::clicked,dialog,&QDialog::close);
    connect(ConfirmButton,&QPushButton::clicked,dialog,&QDialog::close);
    connect(ConfirmButton,&QPushButton::clicked,this,&ScoreDialog::save);


    layout->addWidget(dishName);
    layout->addLayout(buttonLayout);
    layout->addWidget(currentLove);
    layout->addWidget(loveText1);
    layout->addWidget(loveText2);
    layout->addSpacing(20);
    layout->addLayout(resultLayout);
    layout->setSpacing(20);
    layout->setContentsMargins(30,30,30,30);

}

void Menu::SingleDish::ScoreDialog::printStar0(){
    score=1;
    scoreButton[0]->setIcon(*shixinStar);
    scoreButton[1]->setIcon(*kongxinStar);
    scoreButton[2]->setIcon(*kongxinStar);
    scoreButton[3]->setIcon(*kongxinStar);
    scoreButton[4]->setIcon(*kongxinStar);
}

void Menu::SingleDish::ScoreDialog::printStar1(){
    score=2;
    scoreButton[0]->setIcon(*shixinStar);
    scoreButton[1]->setIcon(*shixinStar);
    scoreButton[2]->setIcon(*kongxinStar);
    scoreButton[3]->setIcon(*kongxinStar);
    scoreButton[4]->setIcon(*kongxinStar);
}

void Menu::SingleDish::ScoreDialog::printStar2(){
    score=3;
    scoreButton[0]->setIcon(*shixinStar);
    scoreButton[1]->setIcon(*shixinStar);
    scoreButton[2]->setIcon(*shixinStar);
    scoreButton[3]->setIcon(*kongxinStar);
    scoreButton[4]->setIcon(*kongxinStar);
}

void Menu::SingleDish::ScoreDialog::printStar3(){
    score=4;
    scoreButton[0]->setIcon(*shixinStar);
    scoreButton[1]->setIcon(*shixinStar);
    scoreButton[2]->setIcon(*shixinStar);
    scoreButton[3]->setIcon(*shixinStar);
    scoreButton[4]->setIcon(*kongxinStar);
}

void Menu::SingleDish::ScoreDialog::printStar4(){
    score=5;
    scoreButton[0]->setIcon(*shixinStar);
    scoreButton[1]->setIcon(*shixinStar);
    scoreButton[2]->setIcon(*shixinStar);
    scoreButton[3]->setIcon(*shixinStar);
    scoreButton[4]->setIcon(*shixinStar);
}

void Menu::SingleDish::ScoreDialog::save(){
    parentDish->parentPage->cafe->dishes[parentDish->dish->id-1].update(score);
    parentDish->parentPage->cafe->save(parentDish->parentPage->idx);
    Man* man=new Man;
    man->load();
    man->foodRec.comment_number++;
    QVector<QString> newach=man->check_achievement();
    man->save();
    if(!newach.empty())
        emit parentDish->parentPage->parentMenu->hasnewach(newach);
}

Menu::SinglePage::SinglePage(QWidget *parent, int index, Menu* pm)
    : QWidget{parent}, parentMenu(pm), idx(index)
{
    cafe->load(index);

    typelabel1->setStyleSheet("QLabel{font-size:20px;font-family:华文中宋;font-weight:bold;}");
    typelabel2->setStyleSheet("QLabel{font-size:20px;font-family:华文中宋;font-weight:bold;}");
    typelabel3->setStyleSheet("QLabel{font-size:20px;font-family:华文中宋;font-weight:bold;}");
    typelabel4->setStyleSheet("QLabel{font-size:20px;font-family:华文中宋;font-weight:bold;}");

    line1->setFrameShape(QFrame::HLine);
    line1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    line2->setFrameShape(QFrame::HLine);
    line2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    line3->setFrameShape(QFrame::HLine);
    line3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    line4->setFrameShape(QFrame::HLine);
    line4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    typeLayout1->addWidget(typelabel1);
    typeLayout1->addSpacing(15);
    typeLayout1->addWidget(line1);
    typeLayout2->addWidget(typelabel2);
    typeLayout2->addSpacing(15);
    typeLayout2->addWidget(line2);
    typeLayout3->addWidget(typelabel3);
    typeLayout3->addSpacing(15);
    typeLayout3->addWidget(line3);
    typeLayout4->addWidget(typelabel4);
    typeLayout4->addSpacing(15);
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

    gLayout1->setVerticalSpacing(15);
    gLayout2->setVerticalSpacing(15);
    gLayout3->setVerticalSpacing(15);
    gLayout4->setVerticalSpacing(15);

    vLayout->addSpacing(10);
    vLayout->addLayout(typeLayout1);
    vLayout->addSpacing(20);
    vLayout->addLayout(gLayout1);
    vLayout->addSpacing(50);
    vLayout->addLayout(typeLayout2);
    vLayout->addSpacing(20);
    vLayout->addLayout(gLayout2);
    vLayout->addSpacing(50);
    vLayout->addLayout(typeLayout3);
    vLayout->addSpacing(20);
    vLayout->addLayout(gLayout3);
    vLayout->addSpacing(50);
    vLayout->addLayout(typeLayout4);
    vLayout->addSpacing(20);
    vLayout->addLayout(gLayout4);
    vLayout->setContentsMargins(20,0,30,20);

    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);

    recordLayout->addStretch(1);
    recordLayout->addWidget(cancelButton);
    cancelButton->setVisible(false);
    cancelButton->setStyleSheet("QPushButton{font-size:14px;}");

    recordLayout->addSpacing(20);
    recordLayout->addWidget(recordButton);
    recordButton->setEnabled(false);
    recordButton->setStyleSheet("QPushButton{font-size:14px;color:gray;}");

    connect(cancelButton,&QPushButton::clicked,this,&SinglePage::cancelAll);
    connect(recordButton,&QPushButton::clicked,this,&SinglePage::save);

    selectLayout->addWidget(scrollArea);
    selectLayout->addSpacing(20);
    selectLayout->addLayout(recordLayout);
    selectLayout->addSpacing(5);
    setLayout(selectLayout);
}

void Menu::SinglePage::checkRecordButton(){
    if (selected_count==0){
        cancelButton->setVisible(false);
        recordButton->setEnabled(false);
        recordButton->setStyleSheet("QPushButton{font-size:14px;color:gray;}");
    }
    else{
        cancelButton->setVisible(true);
        recordButton->setEnabled(true);
        recordButton->setStyleSheet("QPushButton{font-size:14px;color:black;}");
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
                      +QString::number(tm->tm_mday)+"日"
                      +QString::fromStdString(str.substr(11,8));
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

    Meal fakeMeal=*meal;
    fakeMeal.elements[0]->sugar=idx; //暗度陈仓，这样record里可以知道是哪个食堂

    Man* man=new Man;
    man->load();
    man->foodRec.week_record.append(qMakePair(getTimeString(),fakeMeal));
    man->foodRec.number++;
    for (int i=0;i<meal->elements.size();i++){
        man->foodRec.veg_number += meal->elements[i]->all_veg;
        man->foodRec.hot_number += meal->elements[i]->pepper;
    }
    QVector<QString> newach=man->check_achievement();
    man->save();

    for (int i=0;i<meal->elements.size();i++){
        cafe->dishes[meal->elements[i]->id-1].scores
            =std::min(cafe->dishes[meal->elements[i]->id-1].scores+1,10);
    }
    cafe->save(idx);

    QDialog* dialog=new QDialog;
    QVBoxLayout* layout = new QVBoxLayout(dialog);
    dialog->setWindowTitle("吃饭记录成功！");
    dialog->setStyleSheet("background:rgb(242,243,244);");

    layout->addWidget(new QLabel("吃饭记录成功！"));
    layout->addWidget(new QLabel("本次您在"+cafe->names[idx]+"吃了："));
    for (int i=0;i<meal->elements.size();i++)
        layout->addWidget(new QLabel("        "+meal->elements[i]->name));
    layout->addWidget(new QLabel("共计摄入："));
    layout->addWidget(new QLabel("        热量 "+QString::number(meal->energy)+" 千卡"));
    layout->addWidget(new QLabel("        蛋白质 "+QString::number(meal->protein)+" 克"));
    layout->addWidget(new QLabel("        脂肪 "+QString::number(meal->fat)+" 克"));
    layout->addWidget(new QLabel("总共消费 "+QString::number(meal->money)+" 元"));

    for (int i=0;i<layout->count();i++) {
        QLayoutItem* item=layout->itemAt(i);
        if(auto label = qobject_cast<QLabel*>(item->widget()))
            label->setStyleSheet("QLabel{font-size:13px;}");
    }

    QPushButton* Button=new QPushButton("确认");
    Button->setStyleSheet("QPushButton{font-size:13px;}");
    connect(Button,&QPushButton::clicked,dialog,&QDialog::close);

    QHBoxLayout* hhLayout=new QHBoxLayout;
    hhLayout->addStretch(1);
    hhLayout->addSpacing(300);
    hhLayout->addWidget(Button);

    layout->addSpacing(50);
    layout->addStretch(1);
    layout->addLayout(hhLayout);

    layout->setSpacing(10);
    layout->setContentsMargins(20,20,20,20);

    dialog->exec();

    if(!newach.empty())
        emit parentMenu->hasnewach(newach);
}

Menu::Menu(QWidget *parent)
    : QWidget{parent}
{
    cafeLabel->setStyleSheet("QLabel{font-size:14px;}");
    cafeBox->setStyleSheet("QComboBox{font-size:14px;}");
    cafeBox->setFixedSize(QSize(150,25));
    cafeBox->setFocusPolicy(Qt::NoFocus);

    Cafeteria* tmpCafe=new Cafeteria;

    for (int i=0;i<=11;i++){
        cafeBox->addItem(tmpCafe->names[i]);
        page[i]=new SinglePage(this,i,this);
        stackedPage->addWidget(page[i]);
    }

    connect(cafeBox,&QComboBox::currentIndexChanged,stackedPage,&QStackedWidget::setCurrentIndex);

    cafeLayout->addSpacing(20);
    cafeLayout->addWidget(cafeLabel);
    cafeLayout->addWidget(cafeBox);
    cafeLayout->addStretch(1);

    finalLayout->addSpacing(5);
    finalLayout->addLayout(cafeLayout);
    finalLayout->addSpacing(5);
    finalLayout->addWidget(stackedPage);
    setLayout(finalLayout);

}
