#ifndef LOGGER
#define LOGGER

#include <stdio.h>

#define LOG_DEBUG_LEVEL 3
#define LOG_INFO_LEVEL 2
#define LOG_ERROR_LEVEL 1

#define LOG_DEFAULT_LEVEL 2
#define LOG_MAX_LEVEL 3

#define LOG_DEFAULT_FILE "wolfwood.log"

class Logger
{
private:
	static unsigned char logLevel;
	static char *logFile;
	static double lastTime;
	Logger() {}
	~Logger() {}
public:
	static void Log(unsigned char, const char *);
	static void Log(const char *message) { Log(LOG_DEFAULT_LEVEL, message); }
	static void Log(unsigned);
	static void Close();
	static void Init();
	static void SetLogLevel(unsigned char level) { logLevel = level; }
};

#endif