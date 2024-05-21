#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSize>
#include <QSizePolicy>
#include <QMargins>
#include <QString>
#include <QFileDialog>
#include <Qpixmap>
#include <QMessageBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>

class Signup : public QWidget
{
    Q_OBJECT
public:
    explicit Signup(QWidget *parent = nullptr);

    QPixmap* photo = new QPixmap(":/signup/default_photo.png"); // 用户头像
    QLabel* usrPhoto = new QLabel;
    QHBoxLayout* photoLayout = new QHBoxLayout(); // 头像和修改按钮

    QLabel* infoText = new QLabel(tr("账号信息"));
    QVBoxLayout* infoLayout = new QVBoxLayout(); // 账号信息
    QGridLayout* dataLayout = new QGridLayout(); // 健康数据
    QGridLayout* preferLayout = new QGridLayout(); // 饮食偏好
    QHBoxLayout* buttonLayout = new QHBoxLayout(); // 按钮
    QGridLayout* mainLayout = new QGridLayout(this);

    QLineEdit* usrNameEdit = new QLineEdit(this);
    QLineEdit* pswdEdit = new QLineEdit(this);
    QLineEdit* correctPswdEdit = new QLineEdit(this);

    QLabel* dataText = new QLabel(tr("健康数据"));
    QLabel* weightText = new QLabel(tr("体重"));
    QDoubleSpinBox* weightEdit = new QDoubleSpinBox(this);
    QLabel* heightText = new QLabel(tr("身高"));
    QDoubleSpinBox* heightEdit = new QDoubleSpinBox(this);
    QLabel* ageText = new QLabel(tr("年龄"));
    QSpinBox* ageEdit = new QSpinBox(this);
    QComboBox* genderEdit = new QComboBox(this);
    QLabel* genderText = new QLabel(tr("性别"));
    QComboBox* goalEdit = new QComboBox(this);
    QLabel* goalText = new QLabel(tr("健康目标"));

    QLabel* preferText = new QLabel(tr("饮食偏好"));
    QComboBox* sugarEdit = new QComboBox(this);
    QLabel* sugarText = new QLabel(tr("甜度"));
    QComboBox* pepperEdit = new QComboBox(this);
    QLabel* pepperText = new QLabel(tr("辣度"));
    QComboBox* exploreEdit = new QComboBox(this);
    QLabel* exploreText = new QLabel(tr("新鲜感"));
    QComboBox* moneyEdit = new QComboBox(this);
    QLabel* moneyText = new QLabel(tr("经济性"));

    QPushButton* correctButton = new QPushButton("确定", this);
    QPushButton* cancelButton = new QPushButton("取消", this);
    QPushButton* changePhotoButton = new QPushButton("更换头像", this);

public slots:
    void corrected();
    void cancelled();
    void changePhoto();
};

#endif // SIGNUP_H
