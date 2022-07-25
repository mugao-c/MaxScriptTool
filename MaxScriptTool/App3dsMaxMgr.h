#ifndef APP3DSMAXMGR_H
#define APP3DSMAXMGR_H

#include <QObject>
#include <QDir>

#define G3dsMgr App3dsMaxMgr::instance()

struct F3dsSupportLanguage
{
    QString dirName;
    QString displayName;
    QString dataDirName;
    F3dsSupportLanguage() {}
    F3dsSupportLanguage(QString dirName, QString displayName, QString dataDirName) {
        this->dirName = dirName;
        this->displayName = displayName;
        this->dataDirName = dataDirName;
    }
};

Q_DECLARE_METATYPE(F3dsSupportLanguage)

class App3dsMaxMgr : public QObject
{
    Q_OBJECT
public:
    explicit App3dsMaxMgr(QObject *parent = nullptr);

    static App3dsMaxMgr* instance();
    // 获取当前安装的3ds max版本
    QStringList get3dsVersions();
    // 或对应3ds max版本使用过的语言
    QList<F3dsSupportLanguage> getLanguageDirs(const QString& version);
    // 获取所有版本的工作空间
    QStringList get3dsWorkspaces(const QString& version, const F3dsSupportLanguage& language);

public:
    bool init();

private:
    bool is3dsVersionDirInfo(const QDir& versionDir);

signals:

private:
    QDir m3dsDir;
    static QList<F3dsSupportLanguage> mLanguages;
};

#endif // APP3DSMAXMGR_H
