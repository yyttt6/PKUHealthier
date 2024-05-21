#include <QApplication>
#include <frontend/login.cpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login* loginpage=new Login;

    loginpage->show();
    return a.exec();
}
