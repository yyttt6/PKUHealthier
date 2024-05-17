#include "login.h"
#include "mainwindow.h"

Login::Login(QWidget *parent)
    : QWidget{parent}
{
    resize(400,200);
    setMinimumSize(200,100);
    setStyleSheet("background:rgb(242,243,244);");

    finalLayout->addWidget(button);
    connect(button,&QPushButton::clicked,this,&Login::loginsuccess);
    setLayout(finalLayout);
}

void Login::loginsuccess()
{
    this->close();
    MainWindow* mainwindow=new MainWindow;
    mainwindow->show();
}
