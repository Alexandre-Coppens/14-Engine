#include "Log.h"
#include <SDL_error.h>

void Log::Info(const std::string& message, const LogLevel _level = LogLevel::Normal)
{
	std::string infoLevel;
	switch (_level)
	{
	case LogLevel::Normal:
		infoLevel = "\033[37m[INFO] %s\033[0m\n";
		break;
	case LogLevel::Good:
		infoLevel = "\033[32m[INFO] %s\033[0m\n";
		break;
	case LogLevel::Warning:
		infoLevel = "\033[33m[INFO] %s\033[0m\n";
		break;
	case LogLevel::Error:
		infoLevel = "\033[31m[INFO] %s\033[0m\n";
		break;
	}
	printf(infoLevel.c_str(), message.c_str());
}

void Log::Error(LogType category, const std::string& message)
{
	SDL_Log(message.c_str(), LogLevel::Error);
	SDL_LogError(static_cast<int>(category), "%s | SDL : %s", message.c_str(), SDL_GetError());
}
