#ifndef RECORDS_H
#define RECORDS_H

#include <QWidget>
#include <QVBoxLayout>

class Records : public QWidget
{
    Q_OBJECT
public:
    explicit Records(QWidget *parent = nullptr);
    QVBoxLayout* finalLayout=new QVBoxLayout(this);
    void refresh();

signals:
};

#endif // RECORDS_H
