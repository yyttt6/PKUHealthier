#ifndef RECOMMEND_H
#define RECOMMEND_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

class Recommend : public QWidget
{
    Q_OBJECT
public:
    explicit Recommend(QWidget *parent = nullptr);
    QVBoxLayout* finalLayout=new QVBoxLayout(this);
    QPushButton* temp=new QPushButton("test! recommend",this);
    void refresh();

signals:
};

#endif // RECOMMEND_H
