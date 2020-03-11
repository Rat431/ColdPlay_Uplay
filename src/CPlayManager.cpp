#include "CPlayManager.h"

char UplayDllPath[MAX_PATH] = { 0 };

namespace Uplay_Configuration
{
	char UserName[0x200] = { "CPlay" };
	char UserEmail[0x200] = { "UplayEmu@cplay42.com" };
	char password[0x200] = { "UplayPassword74" };
	char GameLanguage[0x200] = { "en-US" };
	char SaveDir[0x400] = { "Auto" };
	char UserId[1024] = { "c91c91c9-1c91-c91c-91c9-1c91c91c91c9" };
	char CdKey[1024] = { "1111-2222-3333-4444" };
	char TickedId[1024] = { "noT456umPqRt" };
	bool Offline = false;
	bool appowned = true;

	int cdkey1 = 0;
	int cdkey2 = 0;
	uint32_t gameAppId = 0;
}
namespace CPlay
{
	const char* FormatTheString(const char* Format, const char* ValueS, uint64_t ValueU)
	{
		char TheString[300] = { 0 };
		if (std::strcmp(ValueS, EMPTY) == 0) {
			std::sprintf(TheString, Format, ValueU);
			return TheString;
		}
		std::sprintf(TheString, Format, ValueS);
		return TheString;
	}
	char* ConnectDirectoryToFile(const char* FileName)
	{
		// Variables 
		char* tempbuffer = nullptr;
		char* FileAndDir = nullptr;
		int ConstantDirLength = std::strlen(Uplay_Configuration::SaveDir);
		int ProvidedStringLength = std::strlen(FileName);
		int CalcSize = ConstantDirLength + ProvidedStringLength;

		FileAndDir = (char*)VirtualAlloc(nullptr, CalcSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		if (FileAndDir)
		{
			tempbuffer = (char*)VirtualAlloc(nullptr, CalcSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

			if (tempbuffer)
			{
				std::strcpy(FileAndDir, Uplay_Configuration::SaveDir);
				std::strcpy(&FileAndDir[ConstantDirLength], FileName);

				for (int i = 0; i < ProvidedStringLength; i++, ConstantDirLength++)
				{
					if (FileAndDir[ConstantDirLength] == '\\' || FileAndDir[ConstantDirLength] == '/')
					{
						std::memcpy(tempbuffer, FileAndDir, ConstantDirLength);
						DWORD ftyp = GetFileAttributesA(tempbuffer);
						if (ftyp == INVALID_FILE_ATTRIBUTES) {
							CreateDirectoryA(tempbuffer, NULL);
						}
					}
				}
				VirtualFree(tempbuffer, NULL, MEM_RELEASE);
				return FileAndDir;
			}
			VirtualFree(FileAndDir, NULL, MEM_RELEASE);
		}
		return nullptr;
	}
	static bool Ready = false;
	const char* GetStorageDirectory()
	{
		if (!Ready)
		{
			if (std::strcmp(Uplay_Configuration::SaveDir, "Auto") == 0)
			{
				// directory in roaming by default
				char SavingDir[MAX_PATH] = { 0 };
				bool SetSlash = true;
				if (!SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA | CSIDL_FLAG_CREATE, NULL, 0, SavingDir))) {
					std::strcpy(SavingDir, UplayDllPath);
					SetSlash = false;
				}

				std::memset(Uplay_Configuration::SaveDir, 0, sizeof(Uplay_Configuration::SaveDir));
				std::strcpy(Uplay_Configuration::SaveDir, SavingDir);

				if (SetSlash) {
					std::strcat(Uplay_Configuration::SaveDir, "\\");
				}

				std::strcat(Uplay_Configuration::SaveDir, "UbiStorage\\");
				std::strcat(Uplay_Configuration::SaveDir, Uplay_Configuration::UserName);
				std::strcat(Uplay_Configuration::SaveDir, "\\");
				std::strcat(Uplay_Configuration::SaveDir, FormatTheString("%lu", EMPTY, Uplay_Configuration::gameAppId));
				std::strcat(Uplay_Configuration::SaveDir, "\\");
				std::strcat(Uplay_Configuration::SaveDir, "LocalSaves\\");
			}
			else
			{
				int SlashP = std::strlen(Uplay_Configuration::SaveDir) - 1;

				// Search if the last byte was a "\".
				if (Uplay_Configuration::SaveDir[SlashP] != '\\') {
					std::strcat(Uplay_Configuration::SaveDir, "\\");
				}

				std::strcat(Uplay_Configuration::SaveDir, "UbiStorage\\");
				std::strcat(Uplay_Configuration::SaveDir, Uplay_Configuration::UserName);
				std::strcat(Uplay_Configuration::SaveDir, "\\");
				std::strcat(Uplay_Configuration::SaveDir, FormatTheString("%lu", EMPTY, Uplay_Configuration::gameAppId));
				std::strcat(Uplay_Configuration::SaveDir, "\\");
				std::strcat(Uplay_Configuration::SaveDir, "LocalSaves\\");
			}
			Ready = true;
		}
		return Uplay_Configuration::SaveDir;
	}
	void Storage_Initializzation()
	{
		GetStorageDirectory();

		// Check if the directory exist
		int Arr = 0;
		char TempDir[0x400] = { 0 };

		for (;;)
		{
			if (Uplay_Configuration::SaveDir[Arr] == NULL)
				break;
			TempDir[Arr] = Uplay_Configuration::SaveDir[Arr];
			if (Uplay_Configuration::SaveDir[Arr] == '\\' || Uplay_Configuration::SaveDir[Arr] == '/') {
				DWORD ftyp = GetFileAttributesA(TempDir);
				if (ftyp != INVALID_FILE_ATTRIBUTES && ftyp & FILE_ATTRIBUTE_DIRECTORY) {
					Arr++;
					continue;
				}
				CreateDirectoryA(TempDir, NULL);
			}
			Arr++;
		}
	}
	bool IsTargetExist(LPCSTR path)
	{
		if (GetFileAttributesA(path) == INVALID_FILE_ATTRIBUTES)
			return false;
		return true;
	}
	void InitEmu(HMODULE MainModule)
	{
		char INI[MAX_PATH] = { 0 };					// Get ini directory
		GetModuleFileNameA(MainModule, INI, MAX_PATH);
		lstrcpyA(UplayDllPath, INI);

		int Size = lstrlenA(INI);
		for (int i = Size; i > 0; i--) {
			if (INI[i] == '\\') {
				ZeroMemory(&UplayDllPath[i + 1], (Size - i) + 1);
				lstrcpyA(&INI[i], "\\CPlay.ini");
				break;
			}
		}
		if (!IsTargetExist(INI)) {
			MessageBoxA(0, "Couldn't find CPlay.ini.", "CPlay", MB_ICONERROR);
			ExitProcess(0);
		}

		Uplay_Configuration::appowned = GetPrivateProfileIntA("Uplay", "IsAppOwned", 0, INI) == TRUE;		// Read ini informations
		Uplay_Configuration::Offline = GetPrivateProfileIntA("Uplay", "UplayConnection", 0, INI) != TRUE;
		Uplay_Configuration::gameAppId = GetPrivateProfileIntA("Uplay", "AppId", 0, INI);
		GetPrivateProfileStringA("Uplay", "Username", "CPlay", Uplay_Configuration::UserName, 0x200, INI);
		GetPrivateProfileStringA("Uplay", "Email", "UplayEmu@cplay42.com", Uplay_Configuration::UserEmail, 0x200, INI);
		GetPrivateProfileStringA("Uplay", "Password", "UplayPassword74", Uplay_Configuration::password, 0x200, INI);
		GetPrivateProfileStringA("Uplay", "SavePath", "Auto", Uplay_Configuration::SaveDir, MAX_PATH, INI);
		GetPrivateProfileStringA("Uplay", "Language", "en-US", Uplay_Configuration::GameLanguage, 0x200, INI);
		GetPrivateProfileStringA("Uplay", "CdKey", "1111-2222-3333-4444", Uplay_Configuration::CdKey, 0x200, INI);
		GetPrivateProfileStringA("Uplay", "UserId", "c91c91c9-1c91-c91c-91c9-1c91c91c91c9", Uplay_Configuration::UserId, 0x200, INI);
		GetPrivateProfileStringA("Uplay", "TickedId", "noT456umPqRt", Uplay_Configuration::TickedId, 0x200, INI);

		CPlay::Storage_Initializzation();
	}
}