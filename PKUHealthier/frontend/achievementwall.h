#ifndef ACHIEVEMENTWALL_H
#define ACHIEVEMENTWALL_H

#include <QWidget>

namespace Ui {
class AchievementWall;
}

class AchievementWall : public QWidget
{
    Q_OBJECT

public:
    explicit AchievementWall(QWidget *parent = nullptr);
    ~AchievementWall();

private:
    Ui::AchievementWall *ui;
};

#endif // ACHIEVEMENTWALL_H
