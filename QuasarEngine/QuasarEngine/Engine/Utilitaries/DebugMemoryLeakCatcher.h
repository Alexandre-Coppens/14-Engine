#pragma once
#include <map>
#include <string>

#include "Log.h"

inline std::map<std::string, int> debugMap;

//Add only on an Engine class
static void DEBUGAddClass(const std::string& className)
{
    debugMap[className]++;
}

//Add only on an Engine class
static void DEBUGRemoveClass(const std::string& className)
{
    debugMap[className]--;
    if (debugMap[className] == 0)
        debugMap.erase(className);
}

static void DEBUGPrintList()
{
    for (auto const &pair : debugMap)
    {
        Log::Error(LogType::System, "Forgot to DELETE -> " + pair.first + " : " + std::to_string(pair.second));
    }
}
