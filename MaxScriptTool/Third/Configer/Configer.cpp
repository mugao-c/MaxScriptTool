#include "Configer.h"
#include <QSettings>
#include <QDebug>
#include <QDir>
#include <QStandardPaths>
#include <QGuiApplication>

Q_GLOBAL_STATIC(Configer, _Configer)

Configer::Configer(QObject *parent)
    : QObject{parent}
{
#ifndef LOG_NO_DEFAULT_CONFIGFILE
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation));
    setConfigFilePath(dir.absoluteFilePath("%1.conf").arg(qAppName()));
#endif
}

Configer* Configer::instance()
{
    return _Configer();
}

void Configer::setConfigFilePath(const QString &filepath)
{
    mConfigFilePath = filepath;
    qDebug() << filepath;
}

QVariant Configer::getValue(const QString &group, const QString &key, QVariant defaultValue)
{
    QSettings settings(mConfigFilePath, QSettings::IniFormat);
    settings.beginGroup(group);
    QVariant value = settings.value(key, defaultValue);
    settings.endGroup();
    return value;
}

void Configer::setValue(const QString &group, const QString &key, QVariant value)
{
    QSettings settings(mConfigFilePath, QSettings::IniFormat);
    settings.beginGroup(group);
    settings.setValue(key, value);
    settings.endGroup();
}
