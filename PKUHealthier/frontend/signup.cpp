#include "login.h"
#include "signup.h"
#include "backend/man.h"

Signup::Signup(QWidget *parent)
    : QWidget{parent}
{
    resize(800,600);
    setMinimumSize(500,300);
    setStyleSheet("background:rgb(242,243,244);");

    usrPhoto->setFrameStyle(QFrame::Box|QFrame::Sunken);
    usrPhoto->setPixmap(*photo);
    usrPhoto->setFixedSize(QSize(100, 100));
    usrPhoto->setScaledContents(true);
    usrPhoto->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    changePhotoButton->setMaximumSize(QSize(100, 30));
    connect(changePhotoButton, &QPushButton::clicked, this, &Signup::changePhoto);

    photoLayout->setSpacing(20);
    photoLayout->addWidget(usrPhoto);
    photoLayout->addWidget(changePhotoButton);

    usrNameEdit->setMinimumHeight(35);
    usrNameEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    usrNameEdit->setPlaceholderText("用户名");

    pswdEdit->setMinimumHeight(35);
    pswdEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    pswdEdit->setPlaceholderText("密码");
    pswdEdit->setEchoMode(QLineEdit::Password);

    correctPswdEdit->setMinimumHeight(35);
    correctPswdEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    correctPswdEdit->setPlaceholderText("确认密码");
    correctPswdEdit->setEchoMode(QLineEdit::Password);

    infoText->setMinimumSize(QSize(100, 20));
    infoText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    infoLayout->setSpacing(20);
    infoLayout->addWidget(infoText);
    infoLayout->addWidget(usrNameEdit);
    infoLayout->addWidget(pswdEdit);
    infoLayout->addWidget(correctPswdEdit);

    correctButton->setMaximumSize(QSize(100, 30));
    cancelButton->setMaximumSize(QSize(100, 30));
    connect(correctButton, &QPushButton::clicked, this, &Signup::corrected);
    connect(cancelButton, &QPushButton::clicked, this, &Signup::cancelled);

    buttonLayout->addWidget(correctButton);
    buttonLayout->addWidget(cancelButton);

    weightEdit->setDecimals(2);
    weightEdit->setRange(0.0, 300.0);
    weightEdit->setMinimumSize(QSize(100, 30));
    weightEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    heightEdit->setDecimals(2);
    heightEdit->setRange(0.0, 300.0);
    heightEdit->setMinimumSize(QSize(100, 30));
    heightEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ageEdit->setRange(0, 200);
    ageEdit->setMinimumSize(QSize(100, 30));
    ageEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    genderEdit->addItem(tr("女"));
    genderEdit->addItem(tr("男"));
    genderEdit->addItem(tr("其他"));
    genderEdit->setMinimumSize(QSize(100, 30));
    genderEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    goalEdit->addItem(tr("减重"));
    goalEdit->addItem(tr("仅平衡膳食"));
    goalEdit->addItem(tr("适度健身"));
    goalEdit->addItem(tr("增肌"));
    goalEdit->addItem(tr("高强度增肌"));
    goalEdit->setMinimumSize(QSize(100, 30));
    goalEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    sugarEdit->addItem(tr("适中"));
    sugarEdit->addItem(tr("少糖"));
    sugarEdit->addItem(tr("多糖"));
    sugarEdit->setMinimumSize(QSize(100, 30));
    sugarEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    pepperEdit->addItem(tr("适中"));
    pepperEdit->addItem(tr("少辣"));
    pepperEdit->addItem(tr("多辣"));
    pepperEdit->setMinimumSize(QSize(100, 30));
    pepperEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    exploreEdit->addItem(tr("默认"));
    exploreEdit->addItem(tr("保守"));
    exploreEdit->addItem(tr("探索"));
    exploreEdit->setMinimumSize(QSize(100, 30));
    exploreEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    moneyEdit->addItem(tr("正常"));
    moneyEdit->addItem(tr("经济"));
    moneyEdit->setMinimumSize(QSize(100, 30));
    moneyEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    dataText->setMinimumSize(QSize(100, 20));
    dataText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    dataLayout->setSpacing(20);
    dataLayout->addWidget(dataText, 0, 0, 1, 2);
    dataLayout->addWidget(ageText, 1, 0);
    dataLayout->addWidget(ageEdit, 1, 1);
    dataLayout->addWidget(heightText, 2, 0);
    dataLayout->addWidget(heightEdit, 2, 1);
    dataLayout->addWidget(weightText, 3, 0);
    dataLayout->addWidget(weightEdit, 3, 1);
    dataLayout->addWidget(genderText, 4, 0);
    dataLayout->addWidget(genderEdit, 4, 1);
    dataLayout->addWidget(goalText, 5, 0);
    dataLayout->addWidget(goalEdit, 5, 1);

    preferText->setMinimumSize(QSize(100, 20));
    preferText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    preferLayout->setSpacing(20);
    preferLayout->addWidget(preferText, 0, 0, 1, 2);
    preferLayout->addWidget(sugarText, 1, 0);
    preferLayout->addWidget(sugarEdit, 1, 1);
    preferLayout->addWidget(pepperText, 2, 0);
    preferLayout->addWidget(pepperEdit, 2, 1);
    preferLayout->addWidget(exploreText, 3, 0);
    preferLayout->addWidget(exploreEdit, 3, 1);
    preferLayout->addWidget(moneyText, 4, 0);
    preferLayout->addWidget(moneyEdit, 4, 1);

    mainLayout->setContentsMargins(QMargins(50, 10, 50, 10));
    mainLayout->setSpacing(20);
    mainLayout->addLayout(photoLayout, 0, 0);
    mainLayout->addLayout(infoLayout, 1, 0);
    mainLayout->addLayout(dataLayout, 0, 1);
    mainLayout->addLayout(preferLayout, 1, 1);
    mainLayout->addLayout(buttonLayout, 2, 0, 1, 2);

    setLayout(mainLayout);
}

void Signup::corrected()
{
    QString usrname = usrNameEdit->text();
    QString password = pswdEdit->text();
    if (usrname == "" || password == "") {
        QMessageBox::critical(this, tr("提示"), tr("用户名或密码不能为空！"));
        return;
    }
    QString crctpswd = correctPswdEdit->text();
    if (password != crctpswd) {
        QMessageBox::critical(this, tr("提示"), tr("密码与确认密码不一致！"));
        return;
    }
    if (password.size() < 6) {
        QMessageBox::critical(this, tr("提示"), tr("密码不能少于6位！"));
        return;
    }

    Man* User = new Man;
    User->name = usrname;
    User->password = password;
    User->weight = weightEdit->value();
    User->height = heightEdit->value();
    User->age = ageEdit->value();
    User->gender = genderEdit->currentIndex();
    User->target = goalEdit->currentIndex();
    User->preference[0] = sugarEdit->currentIndex();
    User->preference[1] = pepperEdit->currentIndex();
    User->preference[2] = exploreEdit->currentIndex();
    User->preference[3] = moneyEdit->currentIndex();

    User->init();
    bool saveCheck = User->save();
    if (!saveCheck) {
        QMessageBox::information(this, tr("提示"), tr("用户信息保存失败，请重试！"));
        return;
    }
    this->close();
    QMessageBox::information(this, tr("提示"), tr("注册成功！即将返回登录界面"));
    Login* login = new Login;
    login->show();
}

void Signup::cancelled()
{
    this->close();
    Login* login = new Login;
    login->show();
}

void Signup::changePhoto()
{
    QString fileName =
        QFileDialog::getOpenFileName(this, tr("选择头像文件"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));
    bool changeSuccess = photo->load(fileName);
    if (!changeSuccess) {
        QMessageBox::information(this, tr("提示"), tr("头像上传失败"));
        return;
    }
    usrPhoto->setPixmap(*photo);
}
