#include "dialog.h"
#include <QApplication>

using namespace std;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Dialog dialog;
    Qt::WindowFlags flags = dialog.windowFlags();
    Qt::WindowFlags helpFlag = Qt::WindowContextHelpButtonHint;
    flags = flags & (~helpFlag);
    dialog.setWindowFlags(flags);
    dialog.setWindowTitle("LandmassDetector application developed by Mathias Assmann");
    dialog.show();
    return a.exec();
}
