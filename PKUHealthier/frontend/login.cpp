#include "login.h"
#include "mainwindow.h"
#include "signup.h"

Login::Login(QWidget *parent)
    : QWidget{parent}
{
    resize(400,200);
    setMinimumSize(200,100);
    setStyleSheet("background:rgb(242,243,244);");

    editerLayout->setSpacing(20);
    usrNameEdit->setMaximumHeight(35);
    usrNameEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    usrNameEdit->setPlaceholderText("用户名");
    editerLayout->addWidget(usrNameEdit);
    pswdEdit->setMaximumHeight(35);
    pswdEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    pswdEdit->setPlaceholderText("密码");
    pswdEdit->setEchoMode(QLineEdit::Password);
    editerLayout->addWidget(pswdEdit);


    loginButton->setMaximumSize(QSize(100, 30));
    signupButton->setMaximumSize(QSize(100, 30));
    connect(loginButton,&QPushButton::clicked,this,&Login::loginsuccess);
    connect(signupButton, &QPushButton::clicked, this, &Login::signupPressed);
    buttonLayout->addWidget(loginButton);
    buttonLayout->addWidget(signupButton);

    mainLayout->addLayout(editerLayout, 0, 0);
    mainLayout->addLayout(buttonLayout, 1, 0);
    mainLayout->setContentsMargins(QMargins(50, 10, 50, 10));
    mainLayout->setSpacing(10);

    setLayout(mainLayout);
}

void Login::loginsuccess()
{
    this->close();
    MainWindow* mainwindow=new MainWindow;
    mainwindow->show();
}

void Login::signupPressed()
{
    this->close();
    Signup* signup = new Signup();
    signup->show();
}
