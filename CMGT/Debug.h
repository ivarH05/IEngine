#pragma once
#include <string>

using string = std::string;


class Debug
{
public:
	static void Log(string message);
	static void LogError(string message);
	static void LogWarning(string message);

	static void Log(string message, string colorCode);
};