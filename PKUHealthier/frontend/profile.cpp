#include "profile.h"
#include "backend/man.h"

Profile::Profile(QWidget *parent)
    : QWidget{parent}
{
    Man* preUser = new Man;
    preUser->load();

    usrPhoto->setFrameStyle(QFrame::Box|QFrame::Sunken);
    usrPhoto->setPixmap(*photo);
    usrPhoto->setFixedSize(QSize(100, 100));
    usrPhoto->setScaledContents(true);
    usrPhoto->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    changePhotoButton->setMaximumSize(QSize(100, 30));
    connect(changePhotoButton, &QPushButton::clicked, this, &Profile::changePhoto);

    photoLayout->setSpacing(20);
    photoLayout->addWidget(usrPhoto);
    photoLayout->addWidget(changePhotoButton);

    usrNameEdit->setMinimumHeight(35);
    usrNameEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    usrNameEdit->setText(preUser->name);

    pswdEdit->setMinimumHeight(35);
    pswdEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    pswdEdit->setText(preUser->password);
    pswdEdit->setEchoMode(QLineEdit::Password);

    correctPswdEdit->setMinimumHeight(35);
    correctPswdEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    correctPswdEdit->setText(preUser->password);
    correctPswdEdit->setEchoMode(QLineEdit::Password);

    infoText->setMinimumSize(QSize(100, 20));
    infoText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    infoLayout->setSpacing(20);
    infoLayout->addWidget(infoText);
    infoLayout->addWidget(usrNameEdit);
    infoLayout->addWidget(pswdEdit);
    infoLayout->addWidget(correctPswdEdit);

    correctButton->setMaximumSize(QSize(100, 30));
    connect(correctButton, &QPushButton::clicked, this, &Profile::corrected);

    buttonLayout->addWidget(correctButton);

    weightEdit->setDecimals(2);
    weightEdit->setRange(1.0, 300.0);
    weightEdit->setValue(preUser->weight);
    weightEdit->setMinimumSize(QSize(100, 30));
    weightEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    heightEdit->setDecimals(2);
    heightEdit->setRange(1.0, 300.0);
    heightEdit->setValue(preUser->height);
    heightEdit->setMinimumSize(QSize(100, 30));
    heightEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ageEdit->setRange(1, 200);
    ageEdit->setValue(preUser->age);
    ageEdit->setMinimumSize(QSize(100, 30));
    ageEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    genderEdit->addItem(tr("女"));
    genderEdit->addItem(tr("男"));
    genderEdit->addItem(tr("其他"));
    genderEdit->setCurrentIndex(preUser->gender);
    genderEdit->setMinimumSize(QSize(100, 30));
    genderEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    goalEdit->addItem(tr("减重"));
    goalEdit->addItem(tr("平衡膳食"));
    goalEdit->addItem(tr("适度健身"));
    goalEdit->addItem(tr("增肌"));
    goalEdit->addItem(tr("高强度增肌"));
    goalEdit->setCurrentIndex(preUser->target);
    goalEdit->setMinimumSize(QSize(100, 30));
    goalEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    sugarEdit->addItem(tr("适中"));
    sugarEdit->addItem(tr("少糖"));
    sugarEdit->addItem(tr("多糖"));
    sugarEdit->setCurrentIndex(preUser->preference[0]);
    sugarEdit->setMinimumSize(QSize(100, 30));
    sugarEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    pepperEdit->addItem(tr("适中"));
    pepperEdit->addItem(tr("少辣"));
    pepperEdit->addItem(tr("多辣"));
    pepperEdit->setCurrentIndex(preUser->preference[1]);
    pepperEdit->setMinimumSize(QSize(100, 30));
    pepperEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    exploreEdit->addItem(tr("适中"));
    exploreEdit->addItem(tr("忠于热爱"));
    exploreEdit->addItem(tr("乐于尝试"));
    exploreEdit->setCurrentIndex(preUser->preference[2]);
    exploreEdit->setMinimumSize(QSize(100, 30));
    exploreEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    moneyEdit->addItem(tr("适中"));
    moneyEdit->addItem(tr("减少消费"));
    moneyEdit->setCurrentIndex(preUser->preference[3]);
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

void Profile::refresh(){
    Man* preUser = new Man;
    preUser->load();
    usrNameEdit->setText(preUser->name);
    pswdEdit->setText(preUser->password);
    correctPswdEdit->setText(preUser->password);
    weightEdit->setValue(preUser->weight);
    heightEdit->setValue(preUser->height);
    ageEdit->setValue(preUser->age);
    genderEdit->setCurrentIndex(preUser->gender);
    goalEdit->setCurrentIndex(preUser->target);
    sugarEdit->setCurrentIndex(preUser->preference[0]);
    pepperEdit->setCurrentIndex(preUser->preference[1]);
    exploreEdit->setCurrentIndex(preUser->preference[2]);
    moneyEdit->setCurrentIndex(preUser->preference[3]);
}

void Profile::corrected()
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

    if (photoFile != "../../data/photo.png") {
        QFile savePhoto(photoFile), targetFile("../../data/photo.png");
        QFile::setPermissions("../../data/photo.png", QFile::ReadOther | QFile::WriteOther);
        if (targetFile.exists()) targetFile.remove();
        bool photoCheck = savePhoto.copy("../../data/photo.png");
        if (!photoCheck) {
            QMessageBox::critical(this, tr("提示"), tr("头像保存失败，请重试！"));
            return;
        }
    }

    Man* User = new Man;
    User->load();
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
    delete User;
    if (!saveCheck) {
        QMessageBox::information(this, tr("提示"), tr("用户信息保存失败，请重试！"));
        return;
    }
    QMessageBox::information(this, tr("提示"), tr("用户信息修改成功！"));
    refresh();
}

void Profile::changePhoto()
{
    QString fileName =
        QFileDialog::getOpenFileName(this, tr("选择头像文件"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));
    bool changeSuccess = photo->load(fileName);
    if (!changeSuccess) {
        QMessageBox::information(this, tr("提示"), tr("头像上传失败或未选择文件"));
        return;
    }
    usrPhoto->setPixmap(*photo);
    photoFile = fileName;
}

