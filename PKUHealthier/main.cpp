#include <QApplication>
#include <frontend/login.cpp>
#include "./backend/cafeteria.h""
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login* loginpage=new Login;

    loginpage->show();
    return a.exec();
    // Cafeteria *pc = new Cafeteria();
    // Man * pm = new Man();
    // pm->weight=70;
    // pm->height=184;
    // pm->age=20;
    // pm->gender=1;
    // pm->name="God";
    // pm->target=4;
    // pm->init();
    // pm->save();
    // QString *pqs;
    // pc->recommend(*pm,100,pqs);
    return 0;
}
