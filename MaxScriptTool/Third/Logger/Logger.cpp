#include "Logger.h"
#include <QDebug>

Q_GLOBAL_STATIC(Logger, _Logger)

Logger::Logger(QObject *parent)
    : QObject{parent}
{
    mLogging = new Logging;
    mThread = new QThread;
    mLogging->moveToThread(mThread);
    connect(mThread, &QThread::finished, mLogging, &QObject::deleteLater);
    connect(this, &Logger::setLevel, mLogging, &Logging::setLevel);
    connect(this, &Logger::log, mLogging, &Logging::log);
    connect(this, &Logger::setLogFilePath, mLogging, &Logging::setLogFilePath);
    mThread->start();


}

Logger::~Logger()
{
    mThread->quit();
    mThread->wait();
    mThread->deleteLater();
}

Logger* Logger::instance()
{
    return _Logger();
}
