#include "achievementwall.h"

AchievementWall::SingleAchievement::SingleAchievement(QWidget* parent, QString name)
    : QWidget{parent}
{
    picLabel->setFixedSize(QSize(160, 120));
    picLabel->setScaledContents(true);
    nameLabel->setStyleSheet("QLabel{font-size:15px;font-family:楷体;font-weight:bold;}");
    nameLabel->setAlignment(Qt::AlignCenter);

    User->load();
    User->achRec.check_achievement(User->sptRec, User->foodRec);
    if (!User->achRec.achievement_map[name]) {
        pic->load(":/achievement/close.png");
        picLabel->setPixmap(*pic);
        nameLabel->setText("成就尚未解锁");
        tempLayout->addWidget(picLabel);
        tempLayout->addWidget(nameLabel);

        frame->setLayout(tempLayout);
        frame->setFixedSize(QSize(400,160));
        frame->setObjectName("frameframe");
        frame->setStyleSheet("QFrame#frameframe{border-style:dotted;border-width:2px;border-color:rgb(0, 0, 0);border-radius:10px;}");

        finalLayout->addWidget(frame);
        setLayout(finalLayout);

        return;
    }
    if (name == "干饭") {
        switch(User->achRec.achievement_map[name]) {
            case 1: pic->load(":/achievement/eat1.png"); nameLabel->setText("干饭小将"); break;
            case 2: pic->load(":/achievement/eat2.png"); nameLabel->setText("干饭大师"); break;
            case 3: pic->load(":/achievement/eat3.png"); nameLabel->setText("古希腊掌管干饭的神");
        }
    }
    if (name == "素食") {
        switch (User->achRec.achievement_map[name]) {
            case 1: pic->load(":/achievement/veg1.png"); nameLabel->setText("素食主义者"); break;
            case 2: pic->load(":/achievement/veg2.png"); nameLabel->setText("极端素食主义者"); break;
            case 3: pic->load(":/achievement/veg3.png"); nameLabel->setText("牛马");
        }
    }
    if (name == "吃辣") {
        switch(User->achRec.achievement_map[name]) {
        case 1: pic->load(":/achievement/pepper1.png"); nameLabel->setText("吃辣小将"); break;
        case 2: pic->load(":/achievement/pepper2.png"); nameLabel->setText("吃辣大师");
        }
    }
    if (name == "挑选") {
        pic->load(":/achievement/selct1.png"); nameLabel->setText("精挑细选");
    }
    if (name == "评论") {
        pic->load(":/achievement/cmt1.png"); nameLabel->setText("美食评论家");
    }
    if (name == "羽毛球") {
        switch(User->achRec.achievement_map[name]) {
        case 1: pic->load(":/achievement/bad1.png"); nameLabel->setText("羽坛小将"); break;
        case 2: pic->load(":/achievement/bad2.png"); nameLabel->setText("羽神");
        }
    }
    if (name == "乒乓球") {
        switch(User->achRec.achievement_map[name]) {
        case 1: pic->load(":/achievement/pin1.png"); nameLabel->setText("乒坛小将"); break;
        case 2: pic->load(":/achievement/bad2.png"); nameLabel->setText("乒神");
        }
    }
    if (name == "网球") {
        switch(User->achRec.achievement_map[name]) {
        case 1: pic->load(":/achievement/ten1.png"); nameLabel->setText("网球小将"); break;
        case 2: pic->load(":/achievement/ten2.png"); nameLabel->setText("网球大师");
        }
    }
    if (name == "篮球") {
        switch(User->achRec.achievement_map[name]) {
        case 1: pic->load(":/achievement/NBA1.png"); nameLabel->setText("篮球新秀"); break;
        case 2: pic->load(":/achievement/NBA2.png"); nameLabel->setText("想你了，牢大！");
        }
    }
    if (name == "排球") {
        switch(User->achRec.achievement_map[name]) {
        case 1: pic->load(":/achievement/vol1.png"); nameLabel->setText("排球新秀"); break;
        case 2: pic->load(":/achievement/vol2.png"); nameLabel->setText("排球大师");
        }
    }
    if (name == "足球") {
        switch(User->achRec.achievement_map[name]) {
        case 1: pic->load(":/achievement/fot1.png"); nameLabel->setText("足球新秀"); break;
        case 2: pic->load(":/achievement/fot2.png"); nameLabel->setText("足球大师");
        }
    }
    if (name == "跑步") {
        switch(User->achRec.achievement_map[name]) {
        case 1: pic->load(":/achievement/run1.png"); nameLabel->setText("初级跑者"); break;
        case 2: pic->load(":/achievement/run2.png"); nameLabel->setText("人生是一场马拉松");
        }
    }
    if (name == "骑行") {
        switch(User->achRec.achievement_map[name]) {
        case 1: pic->load(":/achievement/ride1.png"); nameLabel->setText("初级骑手"); break;
        case 2: pic->load(":/achievement/ride2.png"); nameLabel->setText("人车合一");
        }
    }
    if (name == "登山") {
        switch(User->achRec.achievement_map[name]) {
        case 1: pic->load(":/achievement/mountain1.png"); nameLabel->setText("驴友"); break;
        case 2: pic->load(":/achievement/mountain2.png"); nameLabel->setText("登山大师");
        }
    }
    if (name == "游泳") {
        switch(User->achRec.achievement_map[name]) {
        case 1: pic->load(":/achievement/swim1.png"); nameLabel->setText("狗刨式"); break;
        case 2: pic->load(":/achievement/swim2.png"); nameLabel->setText("弄潮儿");
        }
    }
    if (name == "六边形") {
        switch(User->achRec.achievement_map[name]) {
        case 1: pic->load(":/achievement/cool1.png"); nameLabel->setText("六边形战士"); break;
        case 2: pic->load(":/achievement/cool2.png"); nameLabel->setText("古希腊无所不能的神");
        }
    }

    picLabel->setPixmap(*pic);
    tempLayout->addWidget(picLabel);
    tempLayout->addWidget(nameLabel);

    frame->setLayout(tempLayout);
    frame->setFixedSize(QSize(400,160));
    frame->setObjectName("frameframe");
    frame->setStyleSheet("QFrame#frameframe{border-style:dotted;border-width:2px;border-color:rgb(0, 0, 0);border-radius:10px;}");

    finalLayout->addWidget(frame);
    setLayout(finalLayout);
}

AchievementWall::AchievementWall(QWidget *parent)
    : QWidget{parent}
{
    itemLayout->addWidget(new SingleAchievement(this, "干饭"), 0, 0);
    itemLayout->addWidget(new SingleAchievement(this, "素食"), 0, 1);
    itemLayout->addWidget(new SingleAchievement(this, "吃辣"), 1, 0);
    itemLayout->addWidget(new SingleAchievement(this, "挑选"), 1, 1);
    itemLayout->addWidget(new SingleAchievement(this, "评论"), 2, 0);
    itemLayout->addWidget(new SingleAchievement(this, "羽毛球"), 2, 1);
    itemLayout->addWidget(new SingleAchievement(this, "乒乓球"), 3, 0);
    itemLayout->addWidget(new SingleAchievement(this, "网球"), 3, 1);
    itemLayout->addWidget(new SingleAchievement(this, "篮球"), 4, 0);
    itemLayout->addWidget(new SingleAchievement(this, "排球"), 4, 1);
    itemLayout->addWidget(new SingleAchievement(this, "足球"), 5, 0);
    itemLayout->addWidget(new SingleAchievement(this, "跑步"), 5, 1);
    itemLayout->addWidget(new SingleAchievement(this, "骑行"), 6, 0);
    itemLayout->addWidget(new SingleAchievement(this, "登山"), 6, 1);
    itemLayout->addWidget(new SingleAchievement(this, "游泳"), 7, 0);
    itemLayout->addWidget(new SingleAchievement(this, "六边形"), 7, 1);

    itemLayout->setSpacing(20);
    itemLayout->setContentsMargins(0,0,10,20);
    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);
    finalLayout->addWidget(scrollArea);
    finalLayout->setContentsMargins(25,20,15,20);

    setLayout(finalLayout);
}

void AchievementWall::refresh(){

}
