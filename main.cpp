#include "mainwindow.h"
#include <QApplication>
#include "grid.h"
#include <QStringList>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QStringList items;
    items << "480x480" << "720x480" << "1280x720" << "1920x1080";

    bool ok;
    QString item = QInputDialog::getItem(nullptr, "Screen resolution", "Resolution: ", items, 0, false, &ok);

    int width = 480;
    int height = 480;

    if (ok && !item.isEmpty())
    {
        if (item == "720x480")
        {
            width = 720;
        }
        else if (item == "1280x720")
        {
            width = 1280;
            height = 720;
        }
        else if (item == "1920x1080")
        {
            width = 1920;
            height = 1080;
        }
    }

    MainWindow window(width, height);

    window.show();
    return a.exec();
}
