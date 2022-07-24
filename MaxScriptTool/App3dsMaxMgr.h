#ifndef APP3DSMAXMGR_H
#define APP3DSMAXMGR_H

#include <QObject>
#include <QDir>

#define G3dsMgr App3dsMaxMgr::instance()

class App3dsMaxMgr : public QObject
{
    Q_OBJECT
public:
    explicit App3dsMaxMgr(QObject *parent = nullptr);

    static App3dsMaxMgr* instance();

    QStringList get3dsVersions();

public:
    bool init();

private:
    bool is3dsVersionDirInfo(const QFileInfo& info);

signals:

private:
    QDir m3dsDir;
};

#endif // APP3DSMAXMGR_H
