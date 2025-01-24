#include "avp_ui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    std::cout<<"0"<<std::endl;
    QApplication a(argc, argv);
    std::cout<<"1"<<std::endl;
    avp_ui w;
    std::cout<<"2"<<std::endl;
    w.show();
    std::cout<<"3"<<std::endl;

    return a.exec();
}
