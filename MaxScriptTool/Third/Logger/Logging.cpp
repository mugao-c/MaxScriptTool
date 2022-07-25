#include "Logging.h"
#include <QDebug>
#include <QThread>
#include <QDateTime>

#include <QStandardPaths>
#include <QGuiApplication>
#include <QDir>

#define LogCategory "LogLogging"

#define LoggerStartMsg "Logger Created"

Logging::Logging(QObject *parent)
    : QObject{parent}
{
#ifndef LOG_NO_DEFAULT_LOGFILE
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation));
    setLogFilePath(dir.absoluteFilePath("%1.log").arg(qAppName()));
#endif
    log(LogInfo(LL_Info, LogCategory), LoggerStartMsg);
}

void Logging::setLevel(const LogLevel &level)
{
    mLevel = level;
}

void Logging::setLogFilePath(const QString &filepath)
{
    mLogFilePath = filepath;
    QDir dir = QFileInfo(filepath).absoluteDir();
    if (!dir.exists()) {
        dir.mkpath(dir.absolutePath());
    }
    QFile* file = new QFile(filepath);
    if (file->open(QIODevice::Append))
    {
        if (mLogFile) {
            delete mLogFile;
        }
        mLogFile = file;
    }
    else
    {
        log(LogInfo(LL_Error, LogCategory), QString("set log file failed! path: %1").arg(filepath));
    }
}

void Logging::log(const LogInfo &info, const QString &msg)
{
    if (info.level >= mLevel)
    {
        QString logmsg = getLogMsg(info, msg);
#ifndef NO_LOG_TERMINAL
        logToTerminal(logmsg);
#endif
        logToFile(logmsg);
    }
}

QString Logging::getLogMsg(const LogInfo &info, const QString &msg)
{
    QString levelName;
    switch (info.level) {
    case LL_Debug:
        levelName = "DEBUG";
        break;
    case LL_Info:
        levelName = "INFO";
        break;
    case LL_Warning:
        levelName = "WARN";
        break;
    case LL_Error:
        levelName = "ERROR";
        break;
    case LL_Critical:
        levelName = "CRITICAL";
        break;
    default:
        break;
    }
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

#ifndef QT_NO_DEBUG
    QString logMsg = QString("%1 [%2] [%3] [%4 %5 %6]: %7").arg(time, levelName, info.category,
                                                     info.file, info.function,
                                                     QString::number(info.line), msg);
#else
    QString logMsg = QString("%1 [%2] [%3]: %4").arg(time, levelName, info.category, msg);
#endif
    return logMsg;
}

void Logging::logToTerminal(const QString &logmsg)
{
    qInfo() << logmsg;
}

void Logging::logToFile(const QString &logmsg)
{
    if (mLogFile) {
        QString msg = logmsg + "\n";
        mLogFile->write(msg.toUtf8());
        mLogFile->flush();
    }
}
