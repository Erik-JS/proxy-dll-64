# Proxy DLL 64

Proxy DLL's with ASI loader for 64-bit games. For 32-bit games, [click here](https://github.com/Erik-JS/proxy-dll-32).

**See [Releases](https://github.com/Erik-JS/proxy-dll-64/releases) for binaries.**

## About this repository

A DLL proxy acts like a "middle man" between the game and the original Windows DLL. The goal is to be able to load custom code into a game's memory by loading additional DLL files renamed as *.asi (dubbed as 'ASI plugin').<br />

## A little backstory about "ASI"

[Grand Theft Auto III](https://en.wikipedia.org/wiki/Grand_Theft_Auto_III) was released for PC in 2002.<br />
[GTAForums](https://gtaforums.com/) (one of the biggest GTA communities at the time, and probably the biggest today) hosts discussions about GTA hacking and modding, and back then people found an exploit which allowed custom user-made DLL's to be loaded by the game without the use of injectors if they were named with ASI extension.<br />
It turned out that this was due to how the Miles Sound System middleware (Mss32.dll) attempts to load "ASI codecs" by looking for files ending with .asi in the game's executable folder.<br />
For the sequels, I reckon that Vice City retained the exploit, but not San Andreas. For GTASA, dedicated ASI loaders were made in form of proxy DLL's.<br />
Believe it or not, I contacted the creator of Miles Sound System, John Miles, via e-mail only to ask him what "ASI" stood for, which he politely replied that it's supposed to be "Audio Stream Interface".

## The ASI loader

I implemented here the same scheme I used with the [Binkw32 proxy DLL's for Mass Effect 1, 2 and 3](https://github.com/Erik-JS/masseffect-binkw32).<br />
The proxy DLL will attempt to load ASI plugins from a subfolder "ASI", and if it doesn't find anything there, then it'll load from the current folder.<br />
The ASI loading function in this repo and on Binkw32's is based on [XLiveless](https://gtaforums.com/topic/388658-relgtaiv-xliveless/) made by Stanislav "listener" Golovin. There's no secret: it performs a file search for "*.asi" and attempts to load what it founds.<br />
The loading function has been tweaked by me so it looks for plugins in a given folder while counting what has been already loaded. This is intentionally done to avoid loading plugins with the same name from different places. See Erik-JS/masseffect-binkw32#12.

## How things work

* Place fake DLL in the game's exe folder;
* Game loads fake DLL;
* Fake DLL loads real DLL from System folder;
* Fake DLL writes a log to fakedll_proxy64.log to current user's Documents folder;
* Fake DLL loads ASI files from ASI subfolder (or the game's executable folder).

## Games with Denuvo

As far as I can tell, Denuvo doesn't prevent hacking and modding. Game devs may employ anti-cheat and/or anti-modding measures which aren't related to Denuvo.<br />
In any event, I cannot guarantee that these proxy DLL's will work with every game you own, regardless of having Denuvo or not.

-----------------------------------------------------------

Software used for writing and compiling:<br />
[Code::Blocks](http://www.codeblocks.org/)<br />
[TDM-GCC](https://jmeubank.github.io/tdm-gcc/)