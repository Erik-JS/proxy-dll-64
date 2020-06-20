#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include <windows.h>
#include <shlwapi.h>

int GetPluginLoadCount();
void loadPlugins(LPCSTR subfolder);

#endif
