#include "graphmainwindow.h"
#include <QApplication>
#include "CriticalPath.h"
#include "graphAdjList.h"
#include "TopologicalSort.h"
#include "inputgraphdialog.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GraphMainWindow w;
    InputGraphDialog i;
    w.show();

    return a.exec();
}


