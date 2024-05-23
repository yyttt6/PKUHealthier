#include <QApplication>
#include <frontend/login.cpp>
#include "./backend/cafeteria.h""
int main(int argc, char *argv[])
{
    // QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    // QTextCodec::setCodecForLocale(codec);
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
    // pm->target=2;
    // pm->init();
    // pm->save();
    // int temp_id = -1;
    // int *pint = &temp_id;
    // QVector<Meal> ans;
    // ans = pc->recommend(*pm,100,pint);
    // qDebug()<<*pint<<'\n';
    // for(int i=0;i<3;i++)
    // {
    //     for(auto pd:ans[i].elements)
    //     {
    //         pd->update(5);
    //     }
    // }
    // pc->save(*pint);
    // return 0;
}
