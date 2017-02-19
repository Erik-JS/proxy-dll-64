#include "PluginLoader.h"
#include "Logging.h"

void loadPlugins(const char *folder)
{
	DWORD typeMask = 0x6973612e; // '.asi'
	WIN32_FIND_DATA fd;
	char targetfilter[MAX_PATH];
	char currfile[MAX_PATH];
	strcpy (targetfilter, folder);
	strcat (targetfilter, "\\*.asi");

	HANDLE asiFile = FindFirstFile (targetfilter, &fd);
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
				strcpy (currfile, folder);
				strcat (currfile, "\\");
				strcat (currfile, fd.cFileName);
				LoadLibrary(currfile);
				if (LoadLibrary (currfile))
					logprintf(">>Plugin loaded: %s\n", currfile);
				else
					logprintf(">>Plugin error: %s\n", currfile);
			}
		}
	} while (FindNextFile (asiFile, &fd));
	FindClose (asiFile);
}
