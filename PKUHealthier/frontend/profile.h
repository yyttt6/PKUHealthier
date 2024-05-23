#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>
#include <QVBoxLayout>

class Profile : public QWidget
{
    Q_OBJECT
public:
    explicit Profile(QWidget *parent = nullptr);
    QVBoxLayout* finalLayout=new QVBoxLayout(this);
    void refresh();

signals:
};

#endif // PROFILE_H
