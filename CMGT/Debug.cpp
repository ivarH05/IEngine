#pragma once
#include "Debug.h"
#include <iostream>

#define WHITE   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"


void Debug::Log(string message)			{ Log(" > " + message, WHITE); }
void Debug::LogError(string message)	{ Log("[ERROR] " + message, RED); }
void Debug::LogWarning(string message)	{ Log("[WARNING] " + message, YELLOW); }

void Debug::Log(string message, string colorCode)
{
	std::cout << colorCode << message << "\n";
}