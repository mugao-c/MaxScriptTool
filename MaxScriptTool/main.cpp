#include "MainWindow.h"

#include <QApplication>

#include "LogMacro.h"
#include "App3dsMaxMgr.h"

DECLARE_LOG_CATEGORY(LogMaxScriptTool)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LOG_INFO(LogMaxScriptTool, "Start application");
    if (!G3dsMgr->init())
    {
        return 0;
    }
    MainWindow w;
    w.show();
    return a.exec();
}
