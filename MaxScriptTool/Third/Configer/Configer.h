#ifndef CONFIGER_H
#define CONFIGER_H

#include <QObject>

#ifndef GConfig
#define GConfig Configer::instance()
#endif

class Configer : public QObject
{
    Q_OBJECT
public:
    explicit Configer(QObject *parent = nullptr);
    static Configer* instance();

public:
    // 设置配置文件路径
    void setConfigFilePath(const QString& filepath);

    QVariant getValue(const QString& group, const QString& key, QVariant defaultValue);

    void setValue(const QString& group, const QString& key, QVariant value);

signals:

private:
    QString mConfigFilePath;

public:

};

#endif // CONFIGER_H
