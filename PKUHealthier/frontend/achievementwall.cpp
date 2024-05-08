#include "achievementwall.h"
#include "ui_achievementwall.h"

AchievementWall::AchievementWall(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AchievementWall)
{
    ui->setupUi(this);
}

AchievementWall::~AchievementWall()
{
    delete ui;
}
