#include "Logging.h"

FILE *LogFileHandle = NULL;

void logprintf(const char *format, ...)
{
	if (LogFileHandle == NULL)
		return;
	va_list arglist;
	va_start(arglist, format);
	vfprintf(LogFileHandle, format, arglist);
	va_end(arglist);
}

void logStart(const char *logFilename)
{
	PWSTR docfolder;
	char logfilepath[MAX_PATH];
    if (SHGetKnownFolderPath(FOLDERID_Documents, 0, 0, &docfolder) != S_OK)
        return;
	wcstombs(logfilepath, docfolder, MAX_PATH);
	strcat(logfilepath, "\\");
	strcat(logfilepath, logFilename);
	LogFileHandle = fopen(logfilepath, "a");
	CoTaskMemFree(docfolder);

	// Print time
	time_t currtime = time(NULL);
	struct tm * timeinfo;
	timeinfo = localtime(&currtime);
	logprintf("%s", asctime(timeinfo));

	// Print exe name
	char mfilename[MAX_PATH];
	char *filename;
	GetModuleFileName(NULL, mfilename, MAX_PATH);
	filename = PathFindFileName(mfilename);
	logprintf(">%s\n", filename);
}

void logEnd()
{
    if (LogFileHandle)
    {
        logprintf("\n");
        fclose(LogFileHandle);
    }
}
