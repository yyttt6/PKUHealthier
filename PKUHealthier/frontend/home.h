#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QChart>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QStringList>
#include <QBarCategoryAxis>
#include <QValueAxis>

#include "backend/man.h"

class Home : public QWidget
{
    Q_OBJECT
public:
    explicit Home(QWidget *parent = nullptr);
    QGridLayout* mainLayout = new QGridLayout(this);
    QVBoxLayout* chartsLayout=new QVBoxLayout();
    QHBoxLayout* helloLayout = new QHBoxLayout();
    QPixmap* photo = new QPixmap("../../data/photo.png");
    QLabel* helloLabel = new QLabel();
    QLabel* photoLabel = new QLabel();
    void refresh();

    QCHART_H
public:
    Man* User = new Man;
    QChart* sportChart = new QChart;
    QChart* foodChart = new QChart;
    QChartView* sportView = new QChartView(sportChart, this);
    QChartView* foodView = new QChartView(foodChart, this);
    QBarSeries* sportSerie = new QBarSeries();
    QBarSeries* foodKindSerie = new QBarSeries();
    QBarCategoryAxis* sportAxisX = new QBarCategoryAxis();
    QBarCategoryAxis* foodKindAxisX = new QBarCategoryAxis();
    QValueAxis* sportAxisY = new QValueAxis();
    QValueAxis* foodAxisY = new QValueAxis();
    QBarSet* sportTime = new QBarSet("运动时间");
    QBarSet* foodSet = new QBarSet("数量");

    void sportTimeSet();
    void foodKindSet();
    void sportTimeRefresh();
    void foodKindRefresh();

signals:
};

#endif // HOME_H
