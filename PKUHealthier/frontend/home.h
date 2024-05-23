#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QtCharts/QtCharts>

class Home : public QWidget
{
    Q_OBJECT
public:
    explicit Home(QWidget *parent = nullptr);
    QVBoxLayout* finalLayout=new QVBoxLayout(this);
    QLabel* n = new QLabel("hh");
    void refresh();

signals:
};

#endif // HOME_H
