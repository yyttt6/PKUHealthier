#include <QApplication>
#include "frontend/login.cpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont font;
    font.setStyleStrategy(QFont::PreferAntialias);
    font.setHintingPreference(QFont::HintingPreference::PreferFullHinting);
    a.setFont(font); //抗锯齿 加强渲染

    Login* loginpage=new Login;
    loginpage->show();
    return a.exec();
}
