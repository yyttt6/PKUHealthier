#include "recommenddishes.h"
#include "ui_recommenddishes.h"

RecommendDishes::RecommendDishes(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RecommendDishes)
{
    ui->setupUi(this);
}

RecommendDishes::~RecommendDishes()
{
    delete ui;
}
