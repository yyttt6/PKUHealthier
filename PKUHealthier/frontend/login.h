#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QMargins>
#include <QSize>
#include <QSizePolicy>

class Login : public QWidget
{
    Q_OBJECT
public:
    explicit Login(QWidget *parent = nullptr);
    QGridLayout* mainLayout = new QGridLayout(this);
    QVBoxLayout* editerLayout = new QVBoxLayout();
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* loginButton=new QPushButton("登录",this);
    QPushButton* signupButton = new QPushButton("注册", this);
    QLineEdit* usrNameEdit = new QLineEdit(this);
    QLineEdit* pswdEdit = new QLineEdit(this);

public slots:
    void loginsuccess();
    void signupPressed();

signals:
};

#endif // LOGIN_H
