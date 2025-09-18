#include "pch.h"

#include "Logger.h"

#include <exception>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>

namespace GameEngine
{
void ConsoleSink::Log(LogLevel logLevel, const std::string &message)
{
    if ((logLevel & loggingLevels) != LogLevel::NONE)
    {
        std::cout << LogLevelToString(logLevel) << message << std::endl;
    }
}

void LogSink::SetLoggedLevels(LogLevel newLoggingLevels)
{
    loggingLevels = newLoggingLevels;
}

std::string LogSink::LogLevelToString(LogLevel logLevel)
{
    switch (logLevel)
    {
    case LogLevel::INFO:
        return "[INFO]";
    case LogLevel::WARNING:
        return "[WARNING]";
    case LogLevel::ERROR:
        return "[ERROR]";
    default:
        return "[UNKNOWN]";
    }
}

FileSink::FileSink(const std::string &fileName)
{
    logFile.open(fileName, std::ios::app);
}

FileSink::~FileSink()
{
    if (logFile.is_open())
    {
        try
        {
            logFile.close();
        }
        catch (const std::exception &exception)
        {
            std::cerr << "File closing failed: " << exception.what() << std::endl;
        }
    }
}

void FileSink::Log(LogLevel logLevel, const std::string &message)
{
    if ((logLevel & loggingLevels) != LogLevel::NONE)
    {
        if (logFile.is_open())
        {
            logFile << LogLevelToString(logLevel) << message << std::endl;
        }
    }
}

void Logger::AddSink(std::shared_ptr<LogSink> sink)
{
    sinks.push_back(sink);
}

void Logger::Error(const std::string &message)
{
    Log(LogLevel::ERROR, message);
}

void Logger::Info(const std::string &message)
{
    Log(LogLevel::INFO, message);
}

void Logger::Log(LogLevel logLevel, const std::string &message)
{
    if ((logLevel & loggingLevels) != LogLevel::NONE)
    {
        const std::lock_guard<std::mutex> lock(mutex);
        for (auto &sink : sinks)
        {
            sink->Log(logLevel, message);
        }
    }
}

void Logger::SetLoggedLevels(LogLevel newLoggingLevels)
{
    loggingLevels = newLoggingLevels;
}

void Logger::Warn(const std::string &message)
{
    Log(LogLevel::WARNING, message);
}

std::shared_ptr<Logger> LoggerRegister::GetLogger(const std::string &name)
{
    auto foundIt = loggers.find(name);
    if (foundIt != loggers.end())
    {
        return foundIt->second;
    }
    return defaultLogger;
}

void LoggerRegister::RegisterLogger(const std::string &name, std::shared_ptr<Logger> logger)
{
    const std::lock_guard<std::mutex> lock(mutex);
    loggers[name] = logger;
}

void LoggerRegister::SetDefaultLogger(std::shared_ptr<Logger> logger)
{
    const std::lock_guard<std::mutex> lock(mutex);
    defaultLogger = logger;
    bool registered = false;
    for (const auto &loggerIt : loggers)
    {
        if (logger == loggerIt.second)
        {
            registered = true;
            break;
        }
    }
    if (!registered)
    {
        loggers["Default"] = logger;
    }
}

void LoggerRegister::UnregisterLogger(const std::string &name)
{
    const std::lock_guard<std::mutex> lock(mutex);
    auto foundIt = loggers.find(name);
    if (foundIt != loggers.end())
    {
        loggers.erase(foundIt);
    }
}
} // namespace GameEngine