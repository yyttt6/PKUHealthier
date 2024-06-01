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
            case 1: pic->load(":/achievement/eat1.png"); nameLabel->setText("干饭小将\n\n（记录10顿饭）"); break;
            case 2: pic->load(":/achievement/eat2.png"); nameLabel->setText("干饭大师\n\n（记录100顿饭）"); break;
            case 3: pic->load(":/achievement/eat3.png"); nameLabel->setText("古希腊掌管干饭的神\n\n（记录1000顿饭）");
        }
    }
    if (name == "素食") {
        switch (User->achRec.achievement_map[name]) {
            case 1: pic->load(":/achievement/veg1.png"); nameLabel->setText("素食主义者\n\n（素食数>=20）"); break;
            case 2: pic->load(":/achievement/veg2.png"); nameLabel->setText("极端素食主义者\n\n（素食数>=50）"); break;
            case 3: pic->load(":/achievement/veg3.png"); nameLabel->setText("牛马\n\n（素食数>=100）");
        }
    }
    if (name == "吃辣") {
        switch(User->achRec.achievement_map[name]) {
        case 1: pic->load(":/achievement/pepper1.png"); nameLabel->setText("吃辣小将\n\n（辣菜数>=20）"); break;
        case 2: pic->load(":/achievement/pepper2.png"); nameLabel->setText("吃辣大师\n\n（辣菜数>=50）");
        }
    }
    if (name == "挑选") {
        pic->load(":/achievement/selct1.png"); nameLabel->setText("精挑细选\n\n（要求重新推荐20次）");
    }
    if (name == "评论") {
        pic->load(":/achievement/cmt1.png"); nameLabel->setText("美食评论家\n\n（对20道菜评分）");
    }
    if (name == "羽毛球") {
        switch(User->achRec.achievement_map[name]) {
        case 1: pic->load(":/achievement/bad1.png"); nameLabel->setText("羽坛小将\n\n（羽毛球时间>=180分钟）"); break;
        case 2: pic->load(":/achievement/bad2.png"); nameLabel->setText("羽神\n\n（羽毛球时间>=600分钟)");
        }
    }
    if (name == "乒乓球") {
        switch(User->achRec.achievement_map[name]) {
        case 1: pic->load(":/achievement/pin1.png"); nameLabel->setText("乒坛小将\n\n（乒乓球时间>=180分钟）"); break;
        case 2: pic->load(":/achievement/bad2.png"); nameLabel->setText("乒神\n\n（乒乓球时间>=600分钟）");
        }
    }
    if (name == "网球") {
        switch(User->achRec.achievement_map[name]) {
        case 1: pic->load(":/achievement/ten1.png"); nameLabel->setText("网球小将\n\n（网球时间>=180分钟）"); break;
        case 2: pic->load(":/achievement/ten2.png"); nameLabel->setText("网球大师\n\n（网球时间>=600分钟）");
        }
    }
    if (name == "篮球") {
        switch(User->achRec.achievement_map[name]) {
        case 1: pic->load(":/achievement/NBA1.png"); nameLabel->setText("篮球新秀\n\n（篮球时间>=180分钟）"); break;
        case 2: pic->load(":/achievement/NBA2.png"); nameLabel->setText("想你了，牢大！\n\n（篮球时间>=600分钟）");
        }
    }
    if (name == "排球") {
        switch(User->achRec.achievement_map[name]) {
        case 1: pic->load(":/achievement/vol1.png"); nameLabel->setText("排球新秀\n\n（排球时间>=180分钟）"); break;
        case 2: pic->load(":/achievement/vol2.png"); nameLabel->setText("排球大师\n\n（排球时间>=600分钟）");
        }
    }
    if (name == "足球") {
        switch(User->achRec.achievement_map[name]) {
        case 1: pic->load(":/achievement/fot1.png"); nameLabel->setText("足球新秀\n\n（足球时间>=180分钟）"); break;
        case 2: pic->load(":/achievement/fot2.png"); nameLabel->setText("足球大师\n\n（足球时间>=600分钟）");
        }
    }
    if (name == "跑步") {
        switch(User->achRec.achievement_map[name]) {
        case 1: pic->load(":/achievement/run1.png"); nameLabel->setText("初级跑者\n\n（跑步时间>=180分钟）"); break;
        case 2: pic->load(":/achievement/run2.png"); nameLabel->setText("人生是一场马拉松~\n\n（跑步时间>=600分钟）");
        }
    }
    if (name == "骑行") {
        switch(User->achRec.achievement_map[name]) {
        case 1: pic->load(":/achievement/ride1.png"); nameLabel->setText("初级骑手\n\n（骑行时间>=180分钟）"); break;
        case 2: pic->load(":/achievement/ride2.png"); nameLabel->setText("人车合一！\n\n（骑行时间>=600分钟）");
        }
    }
    if (name == "登山") {
        switch(User->achRec.achievement_map[name]) {
        case 1: pic->load(":/achievement/mountain1.png"); nameLabel->setText("驴友\n\n（登山时间>=180分钟）"); break;
        case 2: pic->load(":/achievement/mountain2.png"); nameLabel->setText("山顶洞人\n\n（登山时间>=600分钟）");
        }
    }
    if (name == "游泳") {
        switch(User->achRec.achievement_map[name]) {
        case 1: pic->load(":/achievement/swim1.png"); nameLabel->setText("狗刨式\n\n（游泳时间>=180分钟）"); break;
        case 2: pic->load(":/achievement/swim2.png"); nameLabel->setText("弄潮儿\n\n（游泳时间>=600分钟）");
        }
    }
    if (name == "六边形") {
        switch(User->achRec.achievement_map[name]) {
        case 1: pic->load(":/achievement/cool1.png"); nameLabel->setText("六边形战士\n\n（获得所有初级运动成就）"); break;
        case 2: pic->load(":/achievement/cool2.png"); nameLabel->setText("古希腊无所不能的神\n\n（获得所有高级运动成就）");
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
