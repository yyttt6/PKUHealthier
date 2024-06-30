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

    QPixmap* photo = new QPixmap("../../data/photo.png");
    QLabel* helloLabel = new QLabel;
    QLabel* photoLabel = new QLabel;
    QHBoxLayout* helloLayout = new QHBoxLayout;

    QLabel *fdPrfText1 = new QLabel;
    QLabel *fdPrfText2 = new QLabel;
    QLabel *cafePrfText1 = new QLabel;
    QLabel *cafePrfText2 = new QLabel;
    QVBoxLayout *foodPrefer = new QVBoxLayout;
    QFrame* foodFrame = new QFrame;
    QVBoxLayout* foodLayout = new QVBoxLayout;

    QLabel *sptPrfText1 = new QLabel;
    QLabel *sptPrfText2 = new QLabel;
    QLabel *sptPrfText3 = new QLabel;
    QLabel *sptPrfText4 = new QLabel;
    QVBoxLayout *sportPrefer = new QVBoxLayout;
    QFrame* sportFrame = new QFrame;
    QVBoxLayout* sportLayout = new QVBoxLayout;

    QLabel *achText = new QLabel;
    QVBoxLayout *achLayout = new QVBoxLayout;
    QFrame* achFrame = new QFrame;
    QVBoxLayout* achLayout2 = new QVBoxLayout;

    QStringList sportAxisText;

    QHBoxLayout* hLayout1=new QHBoxLayout;
    QHBoxLayout* hLayout2=new QHBoxLayout;
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

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
    void setBestDish();

};

#endif // HOME_H
