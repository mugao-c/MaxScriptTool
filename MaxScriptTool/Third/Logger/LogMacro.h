#ifndef LOGMACRO_H
#define LOGMACRO_H

#include "Logger.h"

inline void code_noop(void) {}

template<typename ... Args>
QString makeString(const char* format, Args ...args)
{
    const size_t size = 1 + snprintf(nullptr, 0, format, args ...);

    static char bytes[1024];

    memset(bytes, 0, 1024 * sizeof(char));

    snprintf(bytes, size, format, args ...);

    std::string str(bytes);

    return QString::fromStdString(str);
}

// Declare a log category
#define DECLARE_LOG_CATEGORY(LogCategory) struct LogStruct##LogCategory {\
    inline void log_noop(void) {}\
} LogCategory;

//
#define GLogger Logger::instance()

// 配置日志输出文件
#define SET_LOG_FILE_PATH(FilePath) emit GLogger->setLogFilePath(FilePath)

#define QStringParam(str) (str).toStdString().c_str()
//
#define LOG_DEBUG(LogCategory, format, ...) LogCategory.log_noop();\
    emit GLogger->log(Logging::LogInfo(Logging::LL_Debug, #LogCategory, __FILE__, __FUNCTION__, __LINE__), makeString(format, ##__VA_ARGS__));

#define LOG_INFO(LogCategory, format, ...) LogCategory.log_noop();\
    emit GLogger->log(Logging::LogInfo(Logging::LL_Info, #LogCategory, __FILE__, __FUNCTION__, __LINE__), makeString(format, ##__VA_ARGS__));

#define LOG_WARN(LogCategory, format, ...) LogCategory.log_noop();\
    emit GLogger->log(Logging::LogInfo(Logging::LL_Warning, #LogCategory, __FILE__, __FUNCTION__, __LINE__), makeString(format, ##__VA_ARGS__));

#define LOG_ERROR(LogCategory, format, ...) LogCategory.log_noop();\
    emit GLogger->log(Logging::LogInfo(Logging::LL_Error, #LogCategory, __FILE__, __FUNCTION__, __LINE__), makeString(format, ##__VA_ARGS__));

#define LOG_CRITICAL(LogCategory, format, ...) LogCategory.log_noop();\
    emit GLogger->log(Logging::LogInfo(Logging::LL_Critical, #LogCategory, __FILE__, __FUNCTION__, __LINE__), makeString(format, ##__VA_ARGS__));

#ifndef checkd
#   ifndef QT_NO_DEBUG
#       define checkd(e) if (!(e)) __debugbreak();
#   else
#       define checkd(e) code_noop();
#   endif
#endif

#ifndef check
#define check(e) Q_ASSERT(e)
#endif

#endif // LOGMACRO_H
