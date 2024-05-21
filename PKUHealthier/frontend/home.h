#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

class Home : public QWidget
{
    Q_OBJECT
public:
    explicit Home(QWidget *parent = nullptr);
    QVBoxLayout* finalLayout=new QVBoxLayout(this);
    QPushButton* temp=new QPushButton("test! home",this);
    void refresh();

signals:
};

#endif // HOME_H
