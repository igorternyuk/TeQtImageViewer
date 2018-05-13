#include "mainwindow.hpp"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyle("fusion");
    MainWindow w;
    auto screenRect = QApplication::desktop()->rect();
    auto dx = (screenRect.width() - w.width()) / 2;
    auto dy = (screenRect.height() - w.height()) / 2;
    w.move(dx, dy);
    w.show();

    return app.exec();
}
