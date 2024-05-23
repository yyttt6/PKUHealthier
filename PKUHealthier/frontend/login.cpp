#include "login.h"
#include "mainwindow.h"
#include "signup.h"
#include "backend/man.h"


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
    QString username = usrNameEdit->text();
    QString password = pswdEdit->text();

    Man* User = new Man;
    User->load();
    if (username != User->name) {
        QMessageBox::critical(this, tr("提示"), tr("用户不存在！"));
        delete User;
        return;
    }
    if (password != User->password) {
        QMessageBox::critical(this, tr("提示"), tr("密码错误！"));
        delete User;
        return;
    }
    delete User;

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
