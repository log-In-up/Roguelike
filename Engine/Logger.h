#pragma once
#include <fstream>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

namespace GameEngine
{
enum LogLevel
{
    NONE = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 4,
    ALL = INFO | WARNING | ERROR
};

class LogSink
{
  public:
    virtual ~LogSink() = default;

    virtual void Log(LogLevel logLevel, const std::string &message) = 0;

    void SetLoggedLevels(LogLevel newLoggingLevels);

  protected:
    static std::string LogLevelToString(LogLevel logLevel);
    LogLevel loggingLevels = LogLevel::ALL;
};

class ConsoleSink : public LogSink
{
  public:
    virtual void Log(LogLevel logLevel, const std::string &message) override;
};

class FileSink : public LogSink
{
  public:
    explicit FileSink(const std::string &fileName);
    ~FileSink();
    virtual void Log(LogLevel logLevel, const std::string &message) override;

  private:
    std::ofstream logFile;
};

class Logger
{
  public:
    void AddSink(std::shared_ptr<LogSink> sink);
    void Error(const std::string &message);
    void Info(const std::string &message);
    void Log(LogLevel logLevel, const std::string &message);
    void SetLoggedLevels(LogLevel newLoggingLevels);
    void Warn(const std::string &message);

  private:
    std::vector<std::shared_ptr<LogSink>> sinks;
    LogLevel loggingLevels = LogLevel::ALL;
    std::mutex mutex;
};

class LoggerRegister
{
  public:
    static LoggerRegister &GetInstance()
    {
        static LoggerRegister instance;
        return instance;
    }

    std::shared_ptr<Logger> GetLogger(const std::string &name);
    void RegisterLogger(const std::string &name, std::shared_ptr<Logger> logger);
    void SetDefaultLogger(std::shared_ptr<Logger> logger);
    void UnregisterLogger(const std::string &name);

  private:
    LoggerRegister() = default;
    LoggerRegister(const LoggerRegister &) = delete;
    LoggerRegister &operator=(const LoggerRegister &) = delete;
    std::unordered_map<std::string, std::shared_ptr<Logger>> loggers;
    std::shared_ptr<Logger> defaultLogger = std::make_shared<Logger>();
    std::mutex mutex;
};
} // namespace GameEngine

#define LOG_INFO(message) GameEngine::LoggerRegister::GetInstance().GetLogger("Global")->Info(message);
#define LOG_WARN(message) GameEngine::LoggerRegister::GetInstance().GetLogger("Global")->Warn(message);
#define LOG_ERROR(message) GameEngine::LoggerRegister::GetInstance().GetLogger("Global")->Error(message);