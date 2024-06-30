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
#include <QLineSeries>
#include <QStringList>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QPen>
#include <QFrame>

#include "backend/man.h"

class Home : public QWidget
{
    Q_OBJECT
public:
    explicit Home(QWidget *parent = nullptr);
    QGridLayout* mainLayout = new QGridLayout(this);
    QHBoxLayout* helloLayout = new QHBoxLayout();
    QPixmap* photo = new QPixmap("../../data/photo.png");
    QLabel* helloLabel = new QLabel();
    QLabel* photoLabel = new QLabel();
    QFrame* foodFrame = new QFrame(this);
    QFrame* sportFrame = new QFrame(this);
    QVBoxLayout *foodPrefer = new QVBoxLayout();
    QVBoxLayout *sportPrefer = new QVBoxLayout();
    QLabel *fdPrfText = new QLabel();
    QLabel *sptPrfText = new QLabel();
    QStringList sportAxisText;
    void refresh();

    QCHART_H
public:
    Man* User = new Man;
    QChart* sportChart = new QChart;
    QChart* foodChart = new QChart;
    QChartView* sportView = new QChartView(sportChart, this);
    QChartView* foodView = new QChartView(foodChart, this);
    QBarSeries* sportSerie = new QBarSeries();
    QBarSeries* costSerie = new QBarSeries();
    QLineSeries* engLine = new QLineSeries();
    QLineSeries* protLine = new QLineSeries();
    QLineSeries* fatLine = new QLineSeries();
    QBarCategoryAxis* sportAxisX = new QBarCategoryAxis();
    QValueAxis* foodAxisX = new QValueAxis();
    QValueAxis* sportAxisY = new QValueAxis();
    QValueAxis* engAxisY = new QValueAxis();
    QValueAxis* otherAxisY = new QValueAxis();
    QValueAxis* costAxisY = new QValueAxis();
    QBarSet* sportTime = new QBarSet("运动时间");
    QBarSet* energyCost = new QBarSet("能量消耗");

    void sportTimeSet();
    void foodLineSet();
    void sportTimeRefresh();
    void foodKindRefresh();
    void setBestDish();

signals:
};

#endif // HOME_H
