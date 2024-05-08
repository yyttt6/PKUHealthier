#include "sport.h"
#include "ui_sport.h"

sport::sport(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::sport)
{
    ui->setupUi(this);
}

sport::~sport()
{
    delete ui;
}
