#pragma once

#include <string>

namespace Dwarf {
    class Logger {
      public:
        enum class LogLevel { DEBUG, INFO, WARN, ERR };

      public:
        static Logger& get() {
            static Logger instance;
            return instance;
        }

        void log(LogLevel level, const char* file, int line, const std::string& msg);
        void setLevel(LogLevel level) { m_MinLevel = level; }

        Logger(const Logger&)            = delete;
        Logger& operator=(const Logger&) = delete;

      private:
        Logger() {}
        std::string getLogLevel(LogLevel level) const {
            switch (level) {
            case LogLevel::DEBUG:
                return "DEBUG";
                break;
            case LogLevel::INFO:
                return "INFO";
                break;
            case LogLevel::WARN:
                return "WARN";
                break;
            case LogLevel::ERR:
                return "ERR";
                break;
            default:
                return "LL NOT FOUND";
                break;
            };
        }

      private:
        LogLevel m_MinLevel = LogLevel::DEBUG;
    };

#define LOG_DEBUG(msg)                                                                             \
    Dwarf::Logger::get().log(Dwarf::Logger::LogLevel::DEBUG, __FILE__, __LINE__, msg)
#define LOG_INFO(msg)                                                                              \
    Dwarf::Logger::get().log(Dwarf::Logger::LogLevel::INFO, __FILE__, __LINE__, msg)
#define LOG_WARN(msg)                                                                              \
    Dwarf::Logger::get().log(Dwarf::Logger::LogLevel::WARN, __FILE__, __LINE__, msg)
#define LOG_ERR(msg) Dwarf::Logger::get().log(Dwarf::Logger::LogLevel::ERR, __FILE__, __LINE__, msg)
} // namespace Dwarf
