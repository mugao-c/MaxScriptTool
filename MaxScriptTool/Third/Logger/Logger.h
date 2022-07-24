#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QThread>
#include "Logging.h"

class Logger : public QObject
{
    Q_OBJECT
public:

public:
    explicit Logger(QObject *parent = nullptr);

    ~Logger();

    static Logger* instance();


signals:
    void setLevel(const Logging::LogLevel& level);

    void setLogFilePath(const QString& filepath);

    void log(const Logging::LogInfo& info, const QString& msg);

private:
    Logging* mLogging = nullptr;
    QThread* mThread = nullptr;
};

#endif // LOGGER_H
