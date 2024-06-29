#include "achievementwall.h"
#include <QScrollBar>

AchievementWall::SingleAchievement::SingleAchievement(QWidget* parent, QString _name)
    : QWidget{parent}, name(_name)
{
    picLabel->setFixedHeight(120);
    picLabel->setScaledContents(true);
    nameLabel->setAlignment(Qt::AlignHCenter);
    textLabel->setAlignment(Qt::AlignHCenter);

    rightLayout->addStretch(1);
    rightLayout->addWidget(nameLabel);
    rightLayout->addSpacing(15);
    rightLayout->addWidget(textLabel);
    rightLayout->addStretch(1);

    tempLayout->addWidget(picLabel);
    tempLayout->addLayout(rightLayout);
    tempLayout->setContentsMargins(60,0,20,0);
    tempLayout->setStretch(0,3);
    tempLayout->setStretch(1,5);

    frame->setLayout(tempLayout);
    frame->setFixedSize(QSize(700,160));

    finalLayout->addStretch(1);
    finalLayout->addWidget(frame);
    finalLayout->addStretch(1);

    setLayout(finalLayout);

}

void AchievementWall::SingleAchievement::draw(Man* User){

    switch(User->achRec.achievement_map[name]){
    case 0: //黑铁
        frame->setObjectName("frameframe");
        frame->setStyleSheet("QFrame#frameframe{border:3px solid #545454;background-color:#909090;border-radius:10px;}");
        nameLabel->setStyleSheet("font-size:24px;font-weight:bold;color:#404040;");
        textLabel->setStyleSheet("font-size:20px;color:#404040;");
        break;
    case 1: //青铜
        frame->setObjectName("frameframe");
        frame->setStyleSheet("QFrame#frameframe{border:3px solid #7D4820;background-color:#d28247;border-radius:10px;}");
        nameLabel->setStyleSheet("font-size:24px;font-weight:bold;color:#633A19;");
        textLabel->setStyleSheet("font-size:20px;color:#633A19;");
        break;
    case 2: //白银
        frame->setObjectName("frameframe");
        frame->setStyleSheet("QFrame#frameframe{border:3px solid #5F627D;background-color:#a5a7bc;border-radius:10px;}");
        nameLabel->setStyleSheet("font-size:24px;font-weight:bold;color:#474A5E;");
        textLabel->setStyleSheet("font-size:20px;color:#474A5E;");
        break;
    case 3: //黄金
        frame->setObjectName("frameframe");
        frame->setStyleSheet("QFrame#frameframe{border:3px solid #8A8045;background-color:#E3D74A;border-radius:10px;}");
        nameLabel->setStyleSheet("font-size:24px;font-weight:bold;color:#696135;");
        textLabel->setStyleSheet("font-size:20px;color:#696135;");
        break;
    }

    if (User->achRec.achievement_map[name]==0) {
        picLabel->setStyleSheet("image:url(:/achievement/close.png);"); nameLabel->setText("成就尚未解锁"); textLabel->setText("锟斤拷烫烫烫");
    }
    else if (name == "干饭") {
        switch(User->achRec.achievement_map[name]) {
        case 1: picLabel->setStyleSheet("image:url(:/achievement/eat1.png);"); nameLabel->setText("干饭小将"); textLabel->setText("记录10顿饭"); break;
        case 2: picLabel->setStyleSheet("image:url(:/achievement/eat2.png);"); nameLabel->setText("干饭大师"); textLabel->setText("记录100顿饭"); break;
        case 3: picLabel->setStyleSheet("image:url(:/achievement/eat3.png);"); nameLabel->setText("古希腊掌管干饭的神"); textLabel->setText("记录1000顿饭");
        }
    }
    else if (name == "素食") {
        switch (User->achRec.achievement_map[name]) {
        case 1: picLabel->setStyleSheet("image:url(:/achievement/veg1.png);"); nameLabel->setText("素食主义者"); textLabel->setText("吃20道素菜"); break;
        case 2: picLabel->setStyleSheet("image:url(:/achievement/veg2.png);"); nameLabel->setText("极端素食主义者"); textLabel->setText("吃50道素菜"); break;
        case 3: picLabel->setStyleSheet("image:url(:/achievement/veg3.png);"); nameLabel->setText("牛马"); textLabel->setText("吃100道素菜");
        }
    }
    else if (name == "吃辣") {
        switch(User->achRec.achievement_map[name]) {
        case 1: picLabel->setStyleSheet("image:url(:/achievement/pepper1.png);"); nameLabel->setText("吃辣小将"); textLabel->setText("吃20道辣菜"); break;
        case 3: picLabel->setStyleSheet("image:url(:/achievement/pepper2.png);"); nameLabel->setText("吃辣大师"); textLabel->setText("吃50道辣菜");
        }
    }
    else if (name == "挑选") {
        picLabel->setStyleSheet("image:url(:/achievement/selct1.png);"); nameLabel->setText("精挑细选"); textLabel->setText("要求重新推荐食谱20次");
    }
    else if (name == "评论") {
        picLabel->setStyleSheet("image:url(:/achievement/cmt1.png);"); nameLabel->setText("美食评论家"); textLabel->setText("对菜品评分20次");
    }
    else if (name == "羽毛球") {
        switch(User->achRec.achievement_map[name]) {
        case 1: picLabel->setStyleSheet("image:url(:/achievement/bad1.png);"); nameLabel->setText("羽坛小将"); textLabel->setText("打羽毛球180分钟"); break;
        case 3: picLabel->setStyleSheet("image:url(:/achievement/bad2.png);"); nameLabel->setText("羽神"); textLabel->setText("打羽毛球600分钟");
        }
    }
    else if (name == "乒乓球") {
        switch(User->achRec.achievement_map[name]) {
        case 1: picLabel->setStyleSheet("image:url(:/achievement/pin1.png);"); nameLabel->setText("乒坛小将"); textLabel->setText("打乒乓球180分钟"); break;
        case 3: picLabel->setStyleSheet("image:url(:/achievement/pin2.png);"); nameLabel->setText("乒神"); textLabel->setText("打乒乓球600分钟");
        }
    }
    else if (name == "网球") {
        switch(User->achRec.achievement_map[name]) {
        case 1: picLabel->setStyleSheet("image:url(:/achievement/ten1.png);"); nameLabel->setText("网球小将"); textLabel->setText("打网球180分钟"); break;
        case 3: picLabel->setStyleSheet("image:url(:/achievement/ten2.png);"); nameLabel->setText("网球大师"); textLabel->setText("打网球600分钟");
        }
    }
    else if (name == "篮球") {
        switch(User->achRec.achievement_map[name]) {
        case 1: picLabel->setStyleSheet("image:url(:/achievement/NBA1.png);"); nameLabel->setText("篮球新秀"); textLabel->setText("打篮球180分钟"); break;
        case 3: picLabel->setStyleSheet("image:url(:/achievement/NBA2.png);"); nameLabel->setText("想你了，牢大！"); textLabel->setText("打篮球600分钟");
        }
    }
    else if (name == "排球") {
        switch(User->achRec.achievement_map[name]) {
        case 1: picLabel->setStyleSheet("image:url(:/achievement/vol1.png);"); nameLabel->setText("排球新秀"); textLabel->setText("打排球180分钟"); break;
        case 3: picLabel->setStyleSheet("image:url(:/achievement/vol2.png);"); nameLabel->setText("排球大师"); textLabel->setText("打排球600分钟");
        }
    }
    else if (name == "足球") {
        switch(User->achRec.achievement_map[name]) {
        case 1: picLabel->setStyleSheet("image:url(:/achievement/fot1.png);"); nameLabel->setText("足球新秀"); textLabel->setText("踢足球180分钟"); break;
        case 3: picLabel->setStyleSheet("image:url(:/achievement/fot2.png);"); nameLabel->setText("足球大师"); textLabel->setText("踢足球600分钟");
        }
    }
    else if (name == "跑步") {
        switch(User->achRec.achievement_map[name]) {
        case 1: picLabel->setStyleSheet("image:url(:/achievement/run1.png);"); nameLabel->setText("初级跑者"); textLabel->setText("跑步180分钟"); break;
        case 3: picLabel->setStyleSheet("image:url(:/achievement/run2.png);"); nameLabel->setText("人生是一场马拉松~"); textLabel->setText("跑步600分钟");
        }
    }
    else if (name == "骑行") {
        switch(User->achRec.achievement_map[name]) {
        case 1: picLabel->setStyleSheet("image:url(:/achievement/ride1.png);"); nameLabel->setText("初级骑手"); textLabel->setText("骑行180分钟"); break;
        case 3: picLabel->setStyleSheet("image:url(:/achievement/ride2.png);"); nameLabel->setText("人车合一！"); textLabel->setText("骑行600分钟");
        }
    }
    else if (name == "登山") {
        switch(User->achRec.achievement_map[name]) {
        case 1: picLabel->setStyleSheet("image:url(:/achievement/mountain1.png);"); nameLabel->setText("驴友"); textLabel->setText("登山180分钟"); break;
        case 3: picLabel->setStyleSheet("image:url(:/achievement/mountain2.png);"); nameLabel->setText("山顶洞人"); textLabel->setText("登山600分钟");
        }
    }
    else if (name == "游泳") {
        switch(User->achRec.achievement_map[name]) {
        case 1: picLabel->setStyleSheet("image:url(:/achievement/swim1.png);"); nameLabel->setText("狗刨式"); textLabel->setText("游泳180分钟"); break;
        case 3: picLabel->setStyleSheet("image:url(:/achievement/swim2.png);"); nameLabel->setText("弄潮儿"); textLabel->setText("游泳600分钟");
        }
    }
    else if (name == "六边形") {
        switch(User->achRec.achievement_map[name]) {
        case 2: picLabel->setStyleSheet("image:url(:/achievement/cool1.png);"); nameLabel->setText("六边形战士"); textLabel->setText("获得所有初级运动成就"); break;
        case 3: picLabel->setStyleSheet("image:url(:/achievement/cool2.png);"); nameLabel->setText("古希腊无所不能的神"); textLabel->setText("获得所有高级运动成就");
        }
    }

}

AchievementWall::AchievementWall(QWidget *parent)
    : QWidget{parent}
{
    QString achlist[16]={"干饭","素食","吃辣","挑选","评论","跑步","骑行","游泳","登山","篮球","足球","排球","乒乓球","羽毛球","网球","六边形"};

    man->load();
    *fakeman=*man;
    for (int i=0;i<16;i++)
        fakeman->achRec.achievement_map[achlist[i]]=3;

    headlabel->setFixedSize(QSize(155,55));
    headlabel->setStyleSheet("QLabel{font-family:华文楷体;font-size:28px;font-weight:bold;color:#664C34;letter-spacing:1px;"
                             "background:transparent;border-image:url(:/achievement/board.png) 4 4 4 4 stretch stretch;}");
    headlabel->setAlignment(Qt::AlignCenter);

    button->setFixedSize(QSize(40,40));
    button->setIconSize(QSize(34,34));
    button->setStyleSheet("QPushButton{border:3px solid #545454;background:#909090;border-radius:10px;}"
                          "QPushButton:hover{border:3px solid #545454;background:#757575;border-radius:10px;}");
    button->setContentsMargins(0,0,0,0);

    hLayout->addStretch(1);
    hLayout->addSpacing(75);
    hLayout->addWidget(headlabel);
    hLayout->addSpacing(20);
    hLayout->addWidget(button);
    hLayout->addStretch(1);

    connect(button,&QPushButton::clicked,this,&AchievementWall::change);

    for (int i=0;i<16;i++){
        single[i]=new SingleAchievement(this, achlist[i]);
        itemLayout->addWidget(single[i]);
    }

    itemLayout->setSpacing(20);
    itemLayout->setContentsMargins(0,0,5,5);
    itemLayout->setAlignment(Qt::AlignHCenter);

    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);

    scrollArea->verticalScrollBar()->setStyleSheet(
        "QScrollBar:vertical{width:14px;background:rgba(242,243,244,80%);padding-top:3px;padding-bottom:3px;padding-left:3px;padding-right:3px;border-radius:7px;}"
        "QScrollBar::handle:vertical{background:#A69278;border-radius:4px;}"
        "QScrollBar::handle:vertical:hover{background:#7A6C58;border-radius:4px;}"
        "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{background:transparent;}"
        "QScrollBar::add-line:vertical,QScrollBar::sub-line:vertical{height:0px;width:0px;}");

    scrollArea->setStyleSheet("background-color:transparent;border:none;");

    frameLayout->addLayout(hLayout);
    frameLayout->addSpacing(10);
    frameLayout->addWidget(scrollArea);
    frameLayout->setContentsMargins(15,15,15,15);

    frame->setLayout(frameLayout);
    frame->setObjectName("ff");
    frame->setStyleSheet("QFrame#ff{background-image:url(:/achievement/wall.jpg);border-radius:10px;}");

    finalLayout->addWidget(frame);
    finalLayout->setContentsMargins(20,10,15,15);

    setLayout(finalLayout);

    change();

}

void AchievementWall::change(){
    if(fake){
        button->setIcon(QIcon(":/achievement/hint.png"));
        for (int i=0;i<16;i++)
            single[i]->draw(man);
    }
    else{
        button->setIcon(QIcon(":/achievement/nohint.png"));
        for (int i=0;i<16;i++)
            single[i]->draw(fakeman);
    }
    fake=!fake;
}

void AchievementWall::refresh(){
    fake=true;
    man->load();
    change();
}
