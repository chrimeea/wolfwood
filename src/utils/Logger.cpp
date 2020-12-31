#include <time.h>
#include <windows.h>
#include <string.h>
#include "utils\Logger.h"
#include "utils\Config.h"

char *Logger::logFile = NULL;
unsigned char Logger::logLevel = 0;
double Logger::lastTime = 0.0;

void Logger::Init() {
	char *lf = Config::GetValue("config/logger/logfile");
	if (lf) {
		logFile = (char *) malloc(strlen(lf) + 1);
		strcpy(logFile, lf);
	} else {
		logFile = (char *) malloc(13);
		strcpy(logFile, LOG_DEFAULT_FILE);
	}
	lf = Config::GetValue("config/logger/level");
	if (lf) {
		logLevel = atoi(lf);
	} else {
		logLevel = LOG_DEFAULT_LEVEL;
	}
	FILE *f = fopen(logFile, "wt");
	fclose(f);
	LARGE_INTEGER ticks, ticks_freq;
	QueryPerformanceFrequency(&ticks_freq);
	QueryPerformanceCounter(&ticks);
	lastTime = (double) ticks.QuadPart / (double) ticks_freq.QuadPart;
}

void Logger::Log(unsigned char level, const char *message)
{
	if (level <= logLevel)
	{
		LARGE_INTEGER ticks, ticks_freq;
		QueryPerformanceFrequency(&ticks_freq);
		QueryPerformanceCounter(&ticks);
		double newTime = (double) ticks.QuadPart / (double) ticks_freq.QuadPart;
		time_t ltime;
		struct tm *today;
		time(&ltime);
		today = localtime(&ltime);
		char *t = asctime(today);
		t[24] = 0;
		FILE *f = fopen(logFile, "at");
		fprintf(f, "[%d] %s (%lf) : %s\n", level, t, newTime - lastTime, message);
		fclose(f);
		lastTime = newTime;
	}
}

void Logger::Close()
{
	if (logFile) {
		free(logFile);
	}
}

void Logger::Log(unsigned message)
{
	char m[10];
	sprintf(m, "%u", message);
	Log(LOG_DEFAULT_LEVEL, m);
}
