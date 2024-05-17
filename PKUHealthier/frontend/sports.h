#ifndef SPORTS_H
#define SPORTS_H

#include <QWidget>
#include <QVBoxLayout>

class Sports : public QWidget
{
    Q_OBJECT
public:
    explicit Sports(QWidget *parent = nullptr);
    QVBoxLayout* finalLayout=new QVBoxLayout(this);
    void refresh();

signals:
};

#endif // SPORTS_H
