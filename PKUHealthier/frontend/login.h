#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

class Login : public QWidget
{
    Q_OBJECT
public:
    explicit Login(QWidget *parent = nullptr);
    QVBoxLayout* finalLayout=new QVBoxLayout(this);
    QPushButton* button=new QPushButton("Click me!  sign up and log in",this);

public slots:
    void loginsuccess();

signals:
};

#endif // LOGIN_H
