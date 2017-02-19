#ifndef LOGGING_H
#define LOGGING_H

#define WINVER 0x0601
#define _WIN32_WINNT 0x0601
#include <windows.h>
#include <shlobj.h>
#include <stdio.h>
#include <time.h>
#include <shlwapi.h>

void logprintf(const char *format, ...);
void logStart(const char *logFilename);
void logEnd();

#endif
