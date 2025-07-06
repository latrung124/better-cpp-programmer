/**
* @file LogLevel.h
* @author trung.la
* @date 06-07-2025
* @brief This file defines the LogLevel enum class for logging
*/

#ifndef LOG_LEVEL_H
#define LOG_LEVEL_H

namespace logger {

enum class LogLevel {
    Debug,      // Detailed information, typically used for debugging
    Info,       // General information about the application's progress
    Warning,    // Indication of a potential issue that does not stop the application
    Error,      // An error occurred that may affect the application's functionality
    Critical,   // A serious error that may cause the application to terminate
    Fatal       // A severe error that will cause the application to stop immediately
};

inline std::string toString(LogLevel level) {
    switch (level) {
        case LogLevel::Debug: return "DEBUG";
        case LogLevel::Info: return "INFO";
        case LogLevel::Warning: return "WARNING";
        case LogLevel::Error: return "ERROR";
        case LogLevel::Critical: return "CRITICAL";
        case LogLevel::Fatal: return "FATAL";
        default: return "UNKNOWN";
    }
}

} // namespace logger

#endif // LOG_LEVEL_H