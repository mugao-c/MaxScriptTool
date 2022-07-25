#include "App3dsMaxMgr.h"
#include <QStandardPaths>
#include <QDir>
#include "LogMacro.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QSettings>

// 3DS的配置文件名称
#define CONFIG_FILE_NAME "3dsMax.ini"

// 3DS存储workspace的位置
#define WorkSpaceDirName "UI/Workspaces"

// 存储的Goup
#define GroupDirecties "Directories"

// usermacros的key
#define KeyUserMacros "Additional Macros"

Q_GLOBAL_STATIC(App3dsMaxMgr, _App3dsMaxMgr)

DECLARE_LOG_CATEGORY(Log3dsMaxMgr)

QList<F3dsSupportLanguage> App3dsMaxMgr::mLanguages = {
        F3dsSupportLanguage("ENU", "English", "en-US"),
        F3dsSupportLanguage("CHS", "简体中文", "zh-CN")
};

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
        box.setText("自动获取3dsMax配置失败，可能是由于尚未安装3dsMax或者未在此用户下运行过3dsmax，即将退出管理程序!");
        box.exec();
        return false;
    }

    return true;
}

QStringList App3dsMaxMgr::get3dsVersions()
{
    QStringList appVersions;
    QFileInfoList entries = m3dsDir.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot);
    foreach (auto info, entries) {
        if (is3dsVersionDirInfo(QDir(info.filePath()))) {
            appVersions.append(info.fileName());
        }
    }
    return appVersions;
}

QList<F3dsSupportLanguage> App3dsMaxMgr::getLanguageDirs(const QString &version)
{
    QList<F3dsSupportLanguage> lDirs;
    QDir dir = m3dsDir;
    dir.cd(version);
    foreach (auto& language, mLanguages) {
        if (dir.cd(language.dirName)) {
            lDirs.append(language);
            dir.cdUp();
        }
    }
    return lDirs;
}

QStringList App3dsMaxMgr::get3dsWorkspaces(const QString& version, const F3dsSupportLanguage &language)
{
    QDir dir = m3dsDir;
    dir.cd(version);
    dir.cd(language.dirName);
    dir.cd(language.dataDirName);

    LOG_DEBUG(Log3dsMaxMgr, "???%s", QStringParam(language.dirName));

    QStringList workspaces;
    if (dir.cd(WorkSpaceDirName)) {
        QFileInfoList workspaceLst = dir.entryInfoList(QStringList("*.mnux"),QDir::Files);
        foreach (auto workspaceFileInfo, workspaceLst) {
            LOG_DEBUG(Log3dsMaxMgr, "find work space config file: %s", QStringParam(workspaceFileInfo.filePath()));
            workspaces.append(workspaceFileInfo.baseName());
        }
    } else {
        LOG_ERROR(Log3dsMaxMgr, "Cd to 3dsmax dir: %s failed! from %s",
                  WorkSpaceDirName, QStringParam(dir.absolutePath()));
    }
    return workspaces;
}

bool App3dsMaxMgr::is3dsVersionDirInfo(const QDir &versionDir)
{
    return !getLanguageDirs(versionDir.dirName()).isEmpty();
}
