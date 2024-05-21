#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>

class Menu : public QWidget
{
    Q_OBJECT
public:
    explicit Menu(QWidget *parent = nullptr);
    QVBoxLayout* finalLayout=new QVBoxLayout(this);
    void refresh();

signals:
};

#endif // MENU_H
