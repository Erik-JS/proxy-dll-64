#include "PluginLoader.h"
#include "Logging.h"

int plugincount = 0;

int GetPluginLoadCount()
{
    return plugincount;
}

void loadPlugins(LPCSTR subfolder)
{
	DWORD typeMask = 0x6973612e; // '.asi'
	WIN32_FIND_DATA fd;
    char exebasefolder[MAX_PATH];
    GetModuleFileName(NULL, exebasefolder, sizeof(exebasefolder));
    PathRemoveFileSpec(exebasefolder);
	char targetfilter[MAX_PATH];
	strcpy(targetfilter, exebasefolder);
	PathAppend(targetfilter, subfolder);
	PathAppend(targetfilter, "*.asi");
	char currfile[MAX_PATH];
	HANDLE asiFile = FindFirstFile(targetfilter, &fd);
	if (asiFile == INVALID_HANDLE_VALUE)
        return;
	do
	{
		if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			int pos = 0;
			while (fd.cFileName[pos])
				pos++;
			DWORD type = *(DWORD *)(fd.cFileName+pos-4);
			type |= 0x20202020; // convert letter to lowercase, "\0" to space
			if (type == typeMask)
			{
				strcpy (currfile, targetfilter);
				PathRemoveFileSpec(currfile);
				PathAppend(currfile, fd.cFileName);
				if (LoadLibrary (currfile))
                {
                    logprintf(">>Plugin loaded: %s\n", currfile);
					plugincount++;
                }
				else
					logprintf(">>Plugin error: %s\n", currfile);
			}
		}
	} while (FindNextFile (asiFile, &fd));
	FindClose (asiFile);
}
