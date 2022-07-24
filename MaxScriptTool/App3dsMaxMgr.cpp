#include "App3dsMaxMgr.h"
#include <QStandardPaths>
#include <QDir>
#include "LogMacro.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>

Q_GLOBAL_STATIC(App3dsMaxMgr, _App3dsMaxMgr)

DECLARE_LOG_CATEGORY(Log3dsMaxMgr)

App3dsMaxMgr::App3dsMaxMgr(QObject *parent)
    : QObject{parent}
{

}

App3dsMaxMgr* App3dsMaxMgr::instance()
{
    return _App3dsMaxMgr();
}

bool App3dsMaxMgr::init()
{
    m3dsDir = QDir(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation));
    m3dsDir.cdUp();
    if (!m3dsDir.cd("Autodesk/3dsMax")) {
        LOG_ERROR(Log3dsMaxMgr, "Do not installed 3ds max!");
        QMessageBox box(nullptr);
        box.setWindowTitle("错误");
        box.setText("自动获取3dsMax配置失败，可能是由于尚未安装3dsMax，如果已经安装，请手动指定配置文件目录");
        box.exec();
        QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation));
        dir.cdUp();
        QString appConfigPath = QFileDialog::getOpenFileName(nullptr,
                                                             "选择3dsmax配置文件",
                                                             dir.absolutePath(),"*.ini");
        // todo: 判断ini文件是否正确
        if (appConfigPath.isEmpty())
        {
            box.setWindowTitle("信息");
            box.setText("即将退出程序");
            box.exec();
            return false;
        }
    }

    return true;
}

QStringList App3dsMaxMgr::get3dsVersions()
{
    QStringList appVersions;
    QFileInfoList entries = m3dsDir.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot);
    foreach (auto info, entries) {
        if (is3dsVersionDirInfo(info)) {
            appVersions.append(info.fileName());
        }
    }
    return appVersions;
}

bool App3dsMaxMgr::is3dsVersionDirInfo(const QFileInfo &info)
{
    if (info.isDir())
    {
        QDir versionDir = QDir(info.filePath());
        QFileInfoList languageDirInfos = versionDir.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot);
        foreach (auto languageDirInfo, languageDirInfos)
        {
            QDir dir = QDir(languageDirInfo.filePath());
            QFileInfoList entries = dir.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot);
            QString iniFilePath = dir.absoluteFilePath("3dsMax.ini");
            if (QFileInfo(iniFilePath).isFile())
            {
                return true;
            }
        }
    }
    return false;
}
