#include "pch.h"
#include "CPlayManager.h"


#define UPLAY_EXPORT extern "C" _declspec(dllexport)

HANDLE fileuplay = 0;
void* DirectoryBuffer = 0;
bool created = false;
int val = 0;

struct Chunks
{
	ULONG_PTR d1;
	void* d2;
};
struct Overmapped
{
	signed char pd[4];
	int32_t f4;
	int32_t f8;
};
struct FileOverlap
{
	DWORD addr1;
	DWORD addr2;
	DWORD addr3;
};
struct FileList
{
	DWORD num;
	void* bufferstring;
	DWORD pointer;
};
struct MyFileRef
{
	bool Write;
	HANDLE hFile;
	char* nameoffile;
};
std::mutex ThreadSafe;
std::multimap<DWORD, MyFileRef> FileStream;

// Exports implementations
UPLAY_EXPORT int UPLAY_ACH_EarnAchievement()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_ACH_GetAchievementImage()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_ACH_GetAchievements()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_ACH_ReleaseAchievementImage()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_ACH_ReleaseAchievementList()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_ACH_Write()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_AVATAR_Get(void* buf1)
{
	return 1;
}
UPLAY_EXPORT int UPLAY_AVATAR_GetAvatarIdForCurrentUser()
{
	return 1;
}
UPLAY_EXPORT int UPLAY_AVATAR_GetBitmap()
{
	return 1;
}
UPLAY_EXPORT int UPLAY_AVATAR_Release()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_ClearGameSession()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_FRIENDS_AddPlayedWith()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_FRIENDS_AddToBlackList()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_FRIENDS_DisableFriendMenuItem()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_FRIENDS_EnableFriendMenuItem()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_FRIENDS_GetFriendList()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_FRIENDS_Init()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_FRIENDS_InviteToGame()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_FRIENDS_IsBlackListed()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_FRIENDS_IsFriend()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_FRIENDS_RemoveFriendship()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_FRIENDS_RemoveFromBlackList()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_FRIENDS_RequestFriendship()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_FRIENDS_RespondToGameInvite()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_FRIENDS_ShowFriendSelectionUI()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_FRIENDS_ShowInviteFriendsToGameUI()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_GetLastError()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_GetNextEvent()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_GetOverlappedOperationResult(void* buf1, int* buf2)
{
	Overmapped* ovr = (Overmapped*)buf1;
	if (ovr->f4 == 0) {
		return 0;
	}
	else {
		*buf2 = ovr->f8;
		return 1;
	}
}
UPLAY_EXPORT int UPLAY_HasOverlappedOperationCompleted(void* buf1)
{
	Overmapped* ovr = (Overmapped*)buf1;
	return ovr->f4;
}
UPLAY_EXPORT int UPLAY_INSTALLER_AreChunksInstalled()
{
	return 1;
}
UPLAY_EXPORT int UPLAY_INSTALLER_GetChunkIdsFromTag()
{
	return 0;
}
Chunks* chunks = nullptr;
UPLAY_EXPORT int UPLAY_INSTALLER_GetChunks(void** buf1)
{
	ThreadSafe.lock();

	chunks = (Chunks*)VirtualAlloc(0, 10, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	chunks->d1 = 1;
	chunks->d2 = VirtualAlloc(0, 1000, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (buf1)
		*buf1 = (void*)chunks;

	ThreadSafe.unlock();
	return 1;

}
UPLAY_EXPORT const char* UPLAY_INSTALLER_GetLanguageUtf8()
{
	return Uplay_Configuration::GameLanguage;
}
UPLAY_EXPORT int UPLAY_INSTALLER_Init()
{
	return 1;
}
UPLAY_EXPORT int UPLAY_INSTALLER_ReleaseChunkIdList()
{
	ThreadSafe.lock();

	VirtualFree((void*)chunks, 0, MEM_RELEASE);

	ThreadSafe.unlock();
	return 1;
}
UPLAY_EXPORT int UPLAY_INSTALLER_UpdateInstallOrder()
{
	return 1;
}
UPLAY_EXPORT int UPLAY_Init()
{
	return 1;
}
UPLAY_EXPORT int UPLAY_METADATA_ClearContinuousTag()
{
	return 1;
}
UPLAY_EXPORT int UPLAY_METADATA_SetContinuousTag()
{
	return 1;
}
UPLAY_EXPORT int UPLAY_METADATA_SetSingleEventTag()
{
	return 1;
}
UPLAY_EXPORT int UPLAY_OPTIONS_Apply()
{
	return 1;
}
UPLAY_EXPORT int UPLAY_OPTIONS_Close()
{
	return 1;
}
UPLAY_EXPORT int UPLAY_OPTIONS_Enumerate()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_OPTIONS_Get()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_OPTIONS_Open()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_OPTIONS_ReleaseKeyValueList()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_OPTIONS_Set()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_OPTIONS_SetInGameState()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_OVERLAY_SetShopUrl()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_OVERLAY_Show()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_OVERLAY_ShowBrowserUrl()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_OVERLAY_ShowFacebookAuthentication()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_OVERLAY_ShowNotification()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_OVERLAY_ShowShopUrl()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_PARTY_DisablePartyMemberMenuItem()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_PARTY_EnablePartyMemberMenuItem()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_PARTY_GetFullMemberList()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_PARTY_GetId()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_PARTY_GetInGameMemberList()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_PARTY_Init()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_PARTY_InvitePartyToGame()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_PARTY_InviteToParty()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_PARTY_IsInParty()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_PARTY_IsPartyLeader()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_PARTY_PromoteToLeader()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_PARTY_RespondToGameInvite()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_PARTY_SetGuest()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_PARTY_SetUserData()
{
	return 1;
}
UPLAY_EXPORT int UPLAY_PARTY_ShowGameInviteOverlayUI()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_PRESENCE_SetPresence()
{
	return 1;
}
UPLAY_EXPORT int UPLAY_PeekNextEvent()
{
	return 1;
}
UPLAY_EXPORT int UPLAY_Quit()
{
	return 1;
}
UPLAY_EXPORT int UPLAY_Release()
{
	return 1;
}
UPLAY_EXPORT int UPLAY_SAVE_Close(DWORD hFileStream)
{
	// Stream close
	if (hFileStream) {
		ThreadSafe.lock();
		auto StreamBufferPosition = FileStream.find(hFileStream);
		if (StreamBufferPosition != FileStream.end()) {
			SetFilePointer(StreamBufferPosition->second.hFile, 0, 0, 0);
			if (StreamBufferPosition->second.Write) {
				int NameL = std::strlen(StreamBufferPosition->second.nameoffile);
				DWORD WRITTEN;
				WriteFile(StreamBufferPosition->second.hFile, StreamBufferPosition->second.nameoffile, NameL, &WRITTEN, 0);
				VirtualFree(StreamBufferPosition->second.nameoffile, 0, MEM_RELEASE);
			}
			CloseHandle(StreamBufferPosition->second.hFile);
			FileStream.erase(StreamBufferPosition);

			ThreadSafe.unlock();
			return 1;
		}
		ThreadSafe.unlock();
	}
	return 0;
}
UPLAY_EXPORT int UPLAY_SAVE_GetSavegames(void** listpointer, FileOverlap* mystruct)
{
	if (!listpointer)
		return 0;

	ThreadSafe.lock();

	void* FirstPointer = VirtualAlloc(NULL, 0x80000, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	DWORD_PTR FileCounter = 0;
	WIN32_FIND_DATAA fd = { 0 };
	if (FirstPointer)
	{
		void** SecondPointer = (void**)VirtualAlloc(NULL, 0x80000, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		if (SecondPointer)
		{
			void** SecPAddr = SecondPointer;
			char* CListInfo = CPlay::ConnectDirectoryToFile("*.save");

			HANDLE hFirstFile = FindFirstFileA(CListInfo, &fd);
			VirtualFree(CListInfo, 0, MEM_RELEASE);

			if (hFirstFile != INVALID_HANDLE_VALUE)
			{
				do
				{
					if (fd.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)
					{
						void* ThirdPointer = VirtualAlloc(NULL, sizeof(FileList), MEM_COMMIT, PAGE_READWRITE);
						if (ThirdPointer)
						{
							int FileNumber = 0;
							int FileNameSL = std::strlen((char*)fd.cFileName);

							char* TempString = (char*)VirtualAlloc(NULL, FileNameSL, MEM_COMMIT, PAGE_READWRITE);
							if (TempString)
							{
								std::strcpy(TempString, (char*)fd.cFileName);

								for (int i = FileNameSL; i > 0; i--) {
									if (TempString[i] == '.') {
										std::memset(&TempString[i], 0, FileNameSL - i);
										FileNumber = std::strtoull(TempString, NULL, 16);
										break;
									}
								}

								VirtualFree(TempString, FileNameSL, MEM_DECOMMIT);

								char* ConnectedD = CPlay::ConnectDirectoryToFile((char*)fd.cFileName);

								HANDLE hFileD = CreateFileA(ConnectedD, GENERIC_READ, 1, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
								VirtualFree(ConnectedD, 0, MEM_RELEASE);

								if (hFileD != INVALID_HANDLE_VALUE) {
									// Structure and read internal file name
									SetFilePointer(hFileD, 0, 0, 0);
									char* FileRealName = (char*)VirtualAlloc(NULL, 0x1000, MEM_COMMIT, PAGE_READWRITE);
									if (FileRealName) {
										DWORD bytesreaded;
										ReadFile(hFileD, FileRealName, 0x1000, &bytesreaded, 0);

										char* RealString = (char*)VirtualAlloc(0, std::strlen(FileRealName), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
										if (RealString)
										{
											std::strcpy(RealString, FileRealName);
											VirtualFree(FileRealName, 0x1000, MEM_DECOMMIT);

											FileList* flst = (FileList*)ThirdPointer;
											flst->bufferstring = RealString;
											flst->num = FileNumber;
											flst->pointer = GetFileSize(hFileD, NULL) - 0x1000;

											*SecPAddr = ThirdPointer;
											SecPAddr++;

											FileCounter++;
										}
										else {
											VirtualFree(ThirdPointer, sizeof(FileList), MEM_DECOMMIT);
											VirtualFree(FileRealName, 0x1000, MEM_DECOMMIT);
										}
									}
									else {
										VirtualFree(ThirdPointer, sizeof(FileList), MEM_DECOMMIT);
									}
									CloseHandle(hFileD);
								}
								else {
									VirtualFree(ThirdPointer, sizeof(FileList), MEM_DECOMMIT);
									VirtualFree(TempString, FileNameSL, MEM_DECOMMIT);
								}
							}
							else {
								VirtualFree(ThirdPointer, sizeof(FileList), MEM_DECOMMIT);
							}
						}
					}
				} while (FindNextFileA(hFirstFile, &fd));
				FindClose(hFirstFile);
			}
			std::memcpy(FirstPointer, &FileCounter, sizeof(DWORD_PTR));
			*(void**)((DWORD_PTR)FirstPointer + sizeof(DWORD_PTR)) = SecondPointer;
		}
		else {
			VirtualFree(FirstPointer, 0, MEM_RELEASE);
		}
	}

	*listpointer = FirstPointer;

	if (mystruct) {
		mystruct->addr1++;
		mystruct->addr2 = 1;
		mystruct->addr3 = 0;
	}

	ThreadSafe.unlock();
	return 1;
}
static int FileStreamID = 0;
UPLAY_EXPORT int UPLAY_SAVE_Open(int dp1, int dp2, DWORD* buf1, FileOverlap* buf2)		// Init UPLAY SAVES
{
	if (!buf1)
		return 0;

	// Vars
	char CurrentFName[MAX_PATH] = { 0 };
	bool WriteMode = dp2 != 0;
	char* fullDir = nullptr;

	ThreadSafe.lock();

	std::sprintf(CurrentFName, "0x%x.save", dp1);
	if (!WriteMode) {
		fullDir = CPlay::ConnectDirectoryToFile(CurrentFName);

		HANDLE fileuplayt = CreateFileA(fullDir, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		VirtualFree(fullDir, 0, MEM_RELEASE);
		if (fileuplayt == INVALID_HANDLE_VALUE)
		{
			if (buf2) {
				buf2->addr1++;
				buf2->addr2 = 1;
				buf2->addr3 = 0;
			}
			ThreadSafe.unlock();
			return 0;
		}
		FileStreamID++;

		MyFileRef MyFile;
		MyFile.Write = WriteMode;
		MyFile.hFile = fileuplayt;
		MyFile.nameoffile = nullptr;

		FileStream.insert(std::make_pair(FileStreamID, MyFile));

		*buf1 = FileStreamID;

		if (buf2) {
			buf2->addr1++;
			buf2->addr2 = 1;
			buf2->addr3 = 0;
		}
		ThreadSafe.unlock();
		return 1;
	}
	else {
		fullDir = CPlay::ConnectDirectoryToFile(CurrentFName);
		HANDLE fileuplayt = CreateFileA(fullDir, SE_GROUP_LOGON_ID, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		VirtualFree(fullDir, 0, MEM_RELEASE);

		if (fileuplayt == INVALID_HANDLE_VALUE)
		{
			if (buf2) {
				buf2->addr1++;
				buf2->addr2 = 1;
				buf2->addr3 = 0;
			}
			ThreadSafe.unlock();
			return 0;
		}
		FileStreamID++;

		MyFileRef MyFile;
		MyFile.Write = WriteMode;
		MyFile.hFile = fileuplayt;
		MyFile.nameoffile = nullptr;
		
		FileStream.insert(std::make_pair(FileStreamID, MyFile));

		*buf1 = FileStreamID;

		if (buf2) {
			buf2->addr1++;
			buf2->addr2 = 1;
			buf2->addr3 = 0;
		}
		ThreadSafe.unlock();
		return 1;
	}
}
UPLAY_EXPORT int UPLAY_SAVE_Read(DWORD hFileStreamID, SIZE_T datatoread, long offset, void** dt1, DWORD *bytesreaded, FileOverlap* mystruct)
{
	ThreadSafe.lock();

	if (hFileStreamID && dt1 && bytesreaded)
	{
		auto StreamBufferPosition = FileStream.find(hFileStreamID);
		if (StreamBufferPosition != FileStream.end()) {
			SetFilePointer(StreamBufferPosition->second.hFile, 0x1000 + offset, 0, 0);
			if (!ReadFile(StreamBufferPosition->second.hFile, *dt1, datatoread, bytesreaded, 0))
			{
				if (mystruct) {
					mystruct->addr1++;
					mystruct->addr2 = 1;
					mystruct->addr3 = 0;
				}
				ThreadSafe.unlock();
				return 0;
			}
			if (mystruct) {
				mystruct->addr1++;
				mystruct->addr2 = 1;
				mystruct->addr3 = 0;
			}
			ThreadSafe.unlock();
			return 1;
		}
	}
	if (mystruct) {
		mystruct->addr1++;
		mystruct->addr2 = 1;
		mystruct->addr3 = 0;
	}
	ThreadSafe.unlock();
	return 0;
}
UPLAY_EXPORT int UPLAY_SAVE_ReleaseGameList(void* listpointer)
{
	VirtualFree(listpointer, NULL, MEM_RELEASE);
	return 1;
}
UPLAY_EXPORT int UPLAY_SAVE_Remove(int fileindex, FileOverlap* filestruct)
{
	char CurrentFName[MAX_PATH] = { 0 };
	char* fullDir = nullptr;

	ThreadSafe.lock();

	std::sprintf(CurrentFName, "0x%x.save", fileindex);
	fullDir = CPlay::ConnectDirectoryToFile(CurrentFName);

	if (!DeleteFileA(fullDir))
	{
		VirtualFree(fullDir, 0, MEM_RELEASE);
		if (filestruct) {
			filestruct->addr1++;
			filestruct->addr2 = 1;
			filestruct->addr3 = 0;
		}
		ThreadSafe.unlock();
		return 0;
	}
	VirtualFree(fullDir, 0, MEM_RELEASE);
	if (filestruct) {
		filestruct->addr1++;
		filestruct->addr2 = 1;
		filestruct->addr3 = 0;
	}
	ThreadSafe.unlock();
	return 1;
}
UPLAY_EXPORT int UPLAY_SAVE_SetName(DWORD hFileData, const char* namefile)
{
	ThreadSafe.lock();
	if (hFileData) {
		auto StreamBufferPosition = FileStream.find(hFileData);
		if (StreamBufferPosition != FileStream.end()) {
			StreamBufferPosition->second.nameoffile = (char*)VirtualAlloc(0, std::strlen(namefile), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			if (StreamBufferPosition->second.nameoffile) {
				std::strcpy(StreamBufferPosition->second.nameoffile, namefile);
				ThreadSafe.unlock();
				return 1;
			}
		}
	}
	ThreadSafe.unlock();
	return 0;
}
UPLAY_EXPORT int UPLAY_SAVE_Write(DWORD hFileStreamID, SIZE_T datatowrite, void** buf1, FileOverlap* buf2)
{
	ThreadSafe.lock();

	if (hFileStreamID && buf1)
	{
		auto StreamBufferPosition = FileStream.find(hFileStreamID);
		if (StreamBufferPosition != FileStream.end()) {
			SetFilePointer(StreamBufferPosition->second.hFile, 0x1000, 0, 0);
			DWORD bytesWritten;
			if (!WriteFile(StreamBufferPosition->second.hFile, *buf1, datatowrite, &bytesWritten, 0))
			{
				if (buf2) {
					buf2->addr1++;
					buf2->addr2 = 1;
					buf2->addr3 = 0;
				}
				ThreadSafe.unlock();
				return 0;
			}
			if (buf2) {
				buf2->addr1++;
				buf2->addr2 = 1;
				buf2->addr3 = 0;
			}
			ThreadSafe.unlock();
			return 1;
		}
	}
	if (buf2) {
		buf2->addr1++;
		buf2->addr2 = 1;
		buf2->addr3 = 0;
	}
	ThreadSafe.unlock();
	return 0;
}
UPLAY_EXPORT int UPLAY_STORE_Checkout()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_STORE_GetPartner()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_STORE_GetProducts()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_STORE_ReleaseProductsList()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_STORE_ShowProductDetails()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_STORE_ShowProducts()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_SetGameSession()
{
	return 1;
}
UPLAY_EXPORT int UPLAY_SetLanguage(const char* language)
{
	std::strcpy(Uplay_Configuration::GameLanguage, language);
	return 1;
}
UPLAY_EXPORT int UPLAY_Start()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_StartCN()
{
	return UPLAY_Start();
}
UPLAY_EXPORT int UPLAY_Startup()
{
	return UPLAY_Start();
}
UPLAY_EXPORT int UPLAY_USER_ClearGameSession()
{
	return 1;
}
UPLAY_EXPORT int UPLAY_USER_ConsumeItem()
{
	return 1;
}
UPLAY_EXPORT int UPLAY_USER_GetAccountId()
{
	return 0;
}
UPLAY_EXPORT const char* UPLAY_USER_GetAccountIdUtf8()
{
	return Uplay_Configuration::UserId;
}
UPLAY_EXPORT int UPLAY_USER_GetCPUScore()
{
	return 0;
}
UPLAY_EXPORT const char* UPLAY_USER_GetCdKeyUtf8()
{
	return Uplay_Configuration::CdKey;
}
UPLAY_EXPORT int UPLAY_USER_GetCdKeys()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_USER_GetConsumableItems(void* buf1)
{
#ifdef _WIN64
	memset(buf1, 0, 8);
#else
	memset(buf1, 0, 4);
#endif
	return 1;
}
UPLAY_EXPORT int UPLAY_USER_GetCredentials()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_USER_GetEmail()
{
	return 0;
}
UPLAY_EXPORT const char* UPLAY_USER_GetEmailUtf8()
{
	return Uplay_Configuration::UserEmail;
}
UPLAY_EXPORT int UPLAY_USER_GetGPUScore()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_USER_GetGPUScoreConfidenceLevel()
{
	return 0;
}
UPLAY_EXPORT const char* UPLAY_USER_GetNameUtf8()
{
	return Uplay_Configuration::UserName;
}
UPLAY_EXPORT int UPLAY_USER_GetPassword()
{
	return 0;
}
UPLAY_EXPORT const char* UPLAY_USER_GetPasswordUtf8()
{
	return Uplay_Configuration::password;
}
UPLAY_EXPORT int UPLAY_USER_GetProfile()
{
	return 0;
}
UPLAY_EXPORT const char* UPLAY_USER_GetTicketUtf8()
{
	return Uplay_Configuration::TickedId;
}
UPLAY_EXPORT int UPLAY_USER_GetUsername()
{
	return 0;
}
UPLAY_EXPORT const char* UPLAY_USER_GetUsernameUtf8()
{
	return Uplay_Configuration::UserName;
}
UPLAY_EXPORT int UPLAY_USER_IsConnected()
{
	return 1;
}
UPLAY_EXPORT int UPLAY_USER_IsInOfflineMode()
{
	return Uplay_Configuration::Offline;
}
UPLAY_EXPORT int UPLAY_USER_IsOwned(int data)
{
	return Uplay_Configuration::appowned;
}
UPLAY_EXPORT int UPLAY_USER_ReleaseCdKeyList()
{
	return 1;
}
UPLAY_EXPORT int UPLAY_USER_ReleaseConsumeItemResult()
{
	return 1;
}
UPLAY_EXPORT int UPLAY_USER_ReleaseProfile()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_USER_SetGameSession()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_Update()
{
	return 1;
}
UPLAY_EXPORT int UPLAY_WIN_GetActions()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_WIN_GetRewards()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_WIN_GetUnitBalance()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_WIN_RefreshActions()
{
	return 1;
}
UPLAY_EXPORT int UPLAY_WIN_ReleaseActionList()
{
	return 1;
}
UPLAY_EXPORT int UPLAY_WIN_ReleaseRewardList()
{
	return 1;
}
UPLAY_EXPORT int UPLAY_WIN_SetActionsCompleted()
{
	return 1;
}
UPLAY_EXPORT int UPLAY_CHAT_GetHistory()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_CHAT_Init()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_CHAT_ReleaseHistoryList()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_CHAT_SendMessage()
{
	return 0;
}
UPLAY_EXPORT int UPLAY_CHAT_SentMessagesRead()
{
	return 0;
}