/**
* @file LoggerStream.h
* @author trung.la
* @date 06-07-2025
* @brief This file defines the Logger class for logging messages
*/

#ifndef LOGGER_STREAM_H
#define LOGGER_STREAM_H

#include <iostream>
#include <sstream>
#include <string>

#include "LogLevel.h"

namespace logger {

class LoggerStream {
public:
    // Constructor
    LoggerStream(LogLevel level, const char* func, int line) :
        mLevel(level), mFunc(func), mLine(line) {
    }

    // Destructor
    ~LoggersStream() {
        std::ostringstream stream;
        stream << "[" << LogLevel::toString(mLevel) << "] "
        << "[" << mFunc << ":" << mLine << "] " << mStream.str();
        std::cout << stream.str() << std::endl; // Output to console, can
    }

    template <typename T>
    LoggerStream& operator<<(const T& message) {
        stream << message;
        return *this;
    }

    
private:
    LoggerStream() = delete; // Disable default constructor
    LoggerStream(const LoggerStream&) = delete; // Disable copy constructor
    LoggerStream& operator=(const LoggerStream&) = delete; // Disable assignment operator
    LoggerStream(LoggerStream&&) = delete; // Disable move constructor
    LoggerStream& operator=(LoggerStream&&) = delete; // Disable move assignment operator

    LogLevel mLevel; // Log level of the message
    const char* mFunc; // Function name where the log is generated
    int mLine; // Line number where the log is generated
    std::ostringstream mStream; // Stream to hold the log message
};

inline LoggerStream print(LogLevel level, const char* func, int line) {
    return LoggerStream(level, func, line);
}

} // logger

#define LOG(LEVEL) logger::print(LEVEL, __func__, __LINE__)

#endif // LOGGER_STREAM_H