#include "startpage.h"

#include <QApplication>

// 主应用程序由此进入
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartPage w;
    w.show();
    return a.exec();
}
