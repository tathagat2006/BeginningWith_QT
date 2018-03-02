#include "calculator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    calculator calci;
    calci.show();

    return app.exec();
}
