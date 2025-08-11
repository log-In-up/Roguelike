#pragma once
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

enum class LogLevel { INFO, WARNING, ERROR };

class LogSink
{
public:
	virtual void Log(LogLevel level, const std::string& message) = 0;
	virtual ~LogSink() = default;
protected:
	std::string LogLevelToString(LogLevel level)
	{
		switch (level) {
		case LogLevel::INFO: return "[INFO]";
		case LogLevel::WARNING: return "[WARNING]";
		case LogLevel::ERROR: return "[ERROR]";
		default: return "[UNKNOWN]";
		}
	}
};

class ConsoleSink : public LogSink
{
public:
	void Log(LogLevel level, const std::string& message) override
	{
		std::cout << LogLevelToString(level) << " " << message << std::endl;
	}
};

class FileSink : public LogSink
{
private:
	std::ofstream logFile;

public:
	FileSink(const std::string& filename) {
		logFile.open(filename, std::ios::app);
	}

	void Log(LogLevel level, const std::string& message) override {
		if (logFile)
		{
			logFile << LogLevelToString(level) << " " << message << std::endl;
		}
	}

	~FileSink()
	{
		if (logFile.is_open())
		{
			logFile.close();
		}
	}
};

class Logger
{
private:
	std::vector<std::shared_ptr<LogSink>> sinks;
	std::mutex logMutex;
public:
	void AddSink(std::shared_ptr<LogSink> sink)
	{
		sinks.push_back(sink);
	}

	void Log(LogLevel level, const std::string& message)
	{
		std::lock_guard<std::mutex> lock(logMutex);
		for (auto& sink : sinks)
		{
			sink->Log(level, message);
		}
	}

	void Info(const std::string& message)
	{
		Log(LogLevel::INFO, message);
	}

	void Warning(const std::string& message)
	{
		Log(LogLevel::WARNING, message);
	}

	void Error(const std::string& message)
	{
		Log(LogLevel::ERROR, message);
	}
};

class LoggerRegistry
{
private:
	std::unordered_map<std::string, std::shared_ptr<Logger>> loggers;
	std::shared_ptr<Logger> defaultLogger;
	std::mutex registryMutex;
public:
	static LoggerRegistry& GetInstance()
	{
		static LoggerRegistry instance;
		return instance;
	}

	std::shared_ptr<Logger> GetLogger(const std::string& name)
	{
		std::lock_guard<std::mutex> lock(registryMutex);
		if (loggers.find(name) != loggers.end())
		{
			return loggers[name];
		}
		return defaultLogger;
	}

	void SetDefaultLogger(std::shared_ptr<Logger> logger)
	{
		defaultLogger = logger;
	}

	void RegisterLogger(const std::string& name, std::shared_ptr<Logger> logger)
	{
		std::lock_guard<std::mutex> lock(registryMutex);
		loggers[name] = logger;
	}
};

#define LOG_INFO(message) LoggerRegistry::GetInstance().GetLogger("global")->Info(message)
#define LOG_WARN(message) LoggerRegistry::GetInstance().GetLogger("global")->Warning(message)
#define LOG_ERROR(message) LoggerRegistry::GetInstance().GetLogger("global")->Error(message)
