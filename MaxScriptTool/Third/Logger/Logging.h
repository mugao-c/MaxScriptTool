#ifndef LOGGING_H
#define LOGGING_H

#include <QObject>

#include <QFile>

class Logging : public QObject
{
    Q_OBJECT
public:
    enum LogLevel {
        LL_Debug = 0,
        LL_Info,
        LL_Warning,
        LL_Error,
        LL_Critical,
    };

    struct LogInfo
    {
        LogLevel level;
        QString category;
        QString file;
        QString function;
        int line;

        LogInfo() {}

        LogInfo(const LogLevel& level, const QString& category,
                const QString& file = "", const QString& function = "", const int& line = 0)
        {
            this->level = level;
            this->category = category;
            this->file = file;
            this->function = function;
            this->line = line;
        }

    };

public:
    explicit Logging(QObject *parent = nullptr);

public slots:
    void setLevel(const Logging::LogLevel& level);
    void setLogFilePath(const QString& filepath);
    void log(const Logging::LogInfo& info, const QString& msg);

private:
    QString getLogMsg(const Logging::LogInfo& info, const QString& msg);

    void logToTerminal(const QString& logmsg);

    void logToFile(const QString& logmsg);

private:
    LogLevel mLevel = LL_Debug;
    QString mLogFilePath;
    QFile* mLogFile = nullptr;
};

#endif // LOGGING_H
