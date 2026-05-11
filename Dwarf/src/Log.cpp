#include "Log.hpp"
#include <iostream>

namespace Dwarf {

    void Logger::log(LogLevel level, const char* file, int line, const std::string& msg) {
        if (static_cast<int>(level) < static_cast<int>(m_MinLevel))
            return;
        std::cout << "[" << getLogLevel(level) << "]" << " (" << file << ":" << line << ") " << msg
                  << "\n";
    }
} // namespace Dwarf
