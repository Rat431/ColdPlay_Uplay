#pragma once
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <mutex>
#include <map>
#include <vector>
#include <shellapi.h>
#include <shlobj_core.h>

#define EMPTY "Nothing"
extern char UplayDllPath[MAX_PATH];
namespace Uplay_Configuration
{
	extern char UserName[0x200];
	extern char UserEmail[0x200];
	extern char password[0x200];
	extern char GameLanguage[0x200];
	extern char SaveDir[0x400];
	extern char UserId[1024];
	extern char CdKey[1024];
	extern char TickedId[1024];
	extern bool Offline;
	extern bool appowned;

	extern int cdkey1;
	extern int cdkey2;
	extern uint32_t gameAppId;
}
namespace CPlay
{
	const char* FormatTheString(const char* Format, const char* ValueS, uint64_t ValueU);
	char* ConnectDirectoryToFile(const char* FileName);
	const char* GetStorageDirectory();
	void Storage_Initializzation();

	bool IsTargetExist(LPCSTR path);
	void InitEmu(HMODULE MainModule);
}