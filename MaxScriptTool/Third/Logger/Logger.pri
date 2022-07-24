HEADERS += \
    $$PWD/LogMacro.h \
    $$PWD/Logger.h \
    $$PWD/Logging.h

SOURCES += \
    $$PWD/Logger.cpp \
    $$PWD/Logging.cpp

INCLUDEPATH += $$PWD

# 不自动生成Log文件
# DEFINES += LOG_NO_DEFAULT_LOGFILE

# 不输出日志到控制台
# DEFINES += NO_LOG_TERMINAL

# 非DEBUG运行
# DEFINES += QT_NO_DEBUG
