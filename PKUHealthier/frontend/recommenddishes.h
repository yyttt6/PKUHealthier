#ifndef RECOMMENDDISHES_H
#define RECOMMENDDISHES_H

#include <QWidget>

namespace Ui {
class RecommendDishes;
}

class RecommendDishes : public QWidget
{
    Q_OBJECT

public:
    explicit RecommendDishes(QWidget *parent = nullptr);
    ~RecommendDishes();

private:
    Ui::RecommendDishes *ui;
};

#endif // RECOMMENDDISHES_H
