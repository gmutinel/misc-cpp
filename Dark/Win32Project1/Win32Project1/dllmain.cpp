// dllmain.cpp: definisce il punto di ingresso per l'applicazione DLL.
#include "stdafx.h"
#include <stdio.h>
#include <windows.h>
#include <shlobj.h>

extern "C"
{
 BOOL __stdcall APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
 {
  switch (ul_reason_for_call)
  {
   case DLL_PROCESS_ATTACH:
   case DLL_THREAD_ATTACH:
   case DLL_THREAD_DETACH:
   case DLL_PROCESS_DETACH:
   break;
  }
  return TRUE;
 }

 char* appID;
 char* lang;
 char* playerName;
 const char* eu="EU";
 char* saveDir;
 int userVals[2]={0x04100000,0x04100000};
 int* userValsPtr;

 // funzioni SteamApps
 bool __stdcall apps0()
 {
  return (true);
 }
 bool __stdcall apps4()
 {
  return (true);
 }
 bool __stdcall apps8()
 {
  return (false);
 }
 bool __stdcall appsC()
 {
  return (false);
 }
 char* __stdcall apps10()
 {
  return lang;
 }
 bool __stdcall apps18(int a)
 {
  return (true);
 }
 bool __stdcall apps1C(int a)
 {
  return (true);
 }
 bool __stdcall apps28()
 {
  return (false);
 }
 bool __stdcall apps2C(int a, int b, int c, int d, int e)
 {
  return (false);
 }
 bool __stdcall apps38(int a)
 {
  return (false);
 }

 // funzioni SteamUtils
 int __stdcall utils8()
 {
  return 1;
 }
 int __stdcall utilsC()
 {
  return 1;
 }
 const char* __stdcall utils10()
 {
  return eu;
 }
 bool __stdcall utils14(int a, int b, int c)
 {
  return false;
 }
 bool __stdcall utils18(int a, int b, int c)
 {
  return false;
 }
 int __stdcall utils24()
 {
  return 0xC184;
 }
 bool __stdcall utils28(int a)
 {
  return (true);
 }
 bool __stdcall utils2C(int a, int b, int c)
 {
  return (true);
 }
 bool __stdcall utils34(int a, int b, int c, int d, int e, int f)
 {
  return (true);
 }
 bool __stdcall utils3C()
 {
  return (true);
 }
 bool __stdcall utils40(int a)
 {
  return (true);
 }
 bool __stdcall utils44()
 {
  return (true);
 }
 bool __stdcall utils48()
 {
  return (true);
 }

//virtual bool ShowGamepadTextInput( EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eInputLineMode, const char *szText, uint32 uMaxLength, const char * pUnk ) = 0;
 bool __stdcall utils50(int a, int b, int c, int d, int e)
 {
  return (false);
 }
//virtual uint32 GetEnteredGamepadTextLength() = 0;
 int __stdcall utils54()
 {
  return 0;
 }
//virtual bool GetEnteredGamepadTextInput( char *pchValue, uint32 cchValueMax ) = 0;
 bool __stdcall utils58()
 {
  return (false);
 }

 // funzioni SteamUser
 bool __stdcall user4()
 {
  return (false);
 }
 int* __stdcall user8(int a)
 {
  userValsPtr=userVals;
  return (userValsPtr);
 }
 bool __stdcall user10(int a, int b)
 {
  return (true);
 }
 bool __stdcall user18(int a, int b)
 {
  return (true);
 }
 bool __stdcall user1C()
 {
  return (true);
 }
 bool __stdcall user20()
 {
  return (true);
 }
 bool __stdcall user24(int a, int b, int c)
 {
  return (true);
 }
 bool __stdcall user28(int a, int b, int c, int d, int e, int f, int g, int h, int i)
 {
  return (true);
 }
 bool __stdcall user2C(int a, int b, int c, int d, int e, int f)
 {
  return (true);
 }
 bool __stdcall user30()
 {
  return (true);
 }
 bool __stdcall user34(int a, int b, int c)
 {
  return (true);
 }
 bool __stdcall user38(int a, int b, int c, int d)
 {
  return (true);
 }
 bool __stdcall user3C(int a, int b)
 {
  return (true);
 }
 bool __stdcall user40(int a)
 {
  return (true);
 }
 //virtual EUserHasLicenseForAppResult UserHasLicenseForApp( CSteamID steamID, AppId_t appID ) = 0;
 int __stdcall user44(int a)
 {
  return (0);
 }
 
 bool __stdcall user48()
 {
  return (true);
 }
 bool __stdcall user4C(int a, int b, int c, int d)
 {
  return (true);
 }
 bool __stdcall user50(int a, int b)
 {
  return (true);
 }

 // funzioni SteamRemoteStorage
 bool __stdcall remStor0(char *pchFile, char *buffer, unsigned long int size) //WriteFile
 {
  int len = lstrlen((LPCWSTR)saveDir)+lstrlen((LPCWSTR)pchFile)+1;
  HANDLE hHeap = GetProcessHeap();
  char* fname = (char*)HeapAlloc(hHeap,HEAP_ZERO_MEMORY,len);
  lstrcpy((LPWSTR)fname, (LPCWSTR)saveDir);
  lstrcat((LPWSTR)fname, (LPCWSTR)pchFile);
  HANDLE hfile = CreateFileA(fname,GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
  HeapFree(hHeap,0,fname);
  if (hfile == INVALID_HANDLE_VALUE)
  {
   return 0;
  }
  else
  {
   DWORD byteWritten = 0;
   bool res = WriteFile(hfile, buffer, size, &byteWritten, NULL);
   CloseHandle(hfile);
   return res;
  }
 }

 DWORD __stdcall remStor4(const char *pchFile, void *buffer, int byteToRead) //ReadFile
 {
  int len = lstrlen((LPCWSTR)saveDir)+lstrlen((LPCWSTR)pchFile)+1;
  HANDLE hHeap = GetProcessHeap();
  char* fname = (char*)HeapAlloc(hHeap,HEAP_ZERO_MEMORY,len);
  lstrcpy((LPWSTR)fname, (LPCWSTR)saveDir);
  lstrcat((LPWSTR)fname, (LPCWSTR)pchFile);
  HANDLE hfile = CreateFileA(fname, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  HeapFree(hHeap,0,fname);
  if (hfile == INVALID_HANDLE_VALUE)
  {
   return 0;
  }
  else
  {
   DWORD byteRead = 0;
   ReadFile(hfile, buffer, byteToRead, &byteRead, NULL);
   CloseHandle(hfile);
   return byteRead;
  }
 }

 bool __stdcall remStor8(const char *pchFile )  //FileForget
 {
  return (true);
 }

 bool __stdcall remStorC(const char *pchFile )  //FileDelete
 {
  bool del;
  int len = lstrlen((LPCWSTR)saveDir)+lstrlen((LPCWSTR)pchFile)+1;
  HANDLE hHeap = GetProcessHeap();
  char* fname = (char*)HeapAlloc(hHeap,HEAP_ZERO_MEMORY,len);
  lstrcpy((LPWSTR)fname, (LPCWSTR)saveDir);
  lstrcat((LPWSTR)fname, (LPCWSTR)pchFile);
  del = DeleteFile((LPCWSTR)fname);
  HeapFree(hHeap,0,fname);
  return del;
 }

 bool __stdcall remStor28(const char *pchFile )  //FileExists
 {
  int len = lstrlen((LPCWSTR)saveDir)+lstrlen((LPCWSTR)pchFile)+1;
  HANDLE hHeap = GetProcessHeap();
  char* fname = (char*)HeapAlloc(hHeap,HEAP_ZERO_MEMORY,len);
  lstrcpy((LPWSTR)fname, (LPCWSTR)saveDir);
  lstrcat((LPWSTR)fname, (LPCWSTR)pchFile);
  HANDLE hfile = CreateFileA(fname, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  HeapFree(hHeap,0,fname);
  if (hfile == INVALID_HANDLE_VALUE)
  {
   return false;
  }
  else
  {
   CloseHandle(hfile);
   return true;
  }
 }

 bool __stdcall remStor2C(const char *pchFile )  //FilePersisted
 {
  return true;
 }

 DWORD __stdcall remStor30(const char *pchFile) //GetFileSize
 {
  int len = lstrlen((LPCWSTR)saveDir)+lstrlen((LPCWSTR)pchFile)+1;
  HANDLE hHeap = GetProcessHeap();
  char* fname = (char*)HeapAlloc(hHeap,HEAP_ZERO_MEMORY,len);
  lstrcpy((LPWSTR)fname, (LPCWSTR)saveDir);
  lstrcat((LPWSTR)fname, (LPCWSTR)pchFile);
  HANDLE hfile = CreateFileA(fname,GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  HeapFree(hHeap,0,fname);
  if (hfile == INVALID_HANDLE_VALUE)
  {
    return 0;
  }
  else
  {
   DWORD fSize = GetFileSize(hfile, NULL);
   CloseHandle(hfile);
   return fSize;
  }
 }

 DWORD64 __stdcall remStor34(const char *pchFile) //GetFileTimestamp
 {
  DWORD64 epoch_diff = 0x019DB1DED53E8000LL;
  int len = lstrlen((LPCWSTR)saveDir)+lstrlen((LPCWSTR)pchFile)+1;
  HANDLE hHeap = GetProcessHeap();
  char* fname = (char*)HeapAlloc(hHeap,HEAP_ZERO_MEMORY,len);
  lstrcpy((LPWSTR)fname, (LPCWSTR)saveDir);
  lstrcat((LPWSTR)fname, (LPCWSTR)pchFile);
  HANDLE hfile = CreateFileA(fname, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  HeapFree(hHeap,0,fname);
  if (hfile == INVALID_HANDLE_VALUE)
  {
   return 0;
  }
  else
  {
   DWORD64 t;
   FILETIME ftime;
   GetFileTime(hfile, NULL, NULL, &ftime);
   CloseHandle(hfile);
   t = (DWORD64)ftime.dwHighDateTime << 32 | ftime.dwLowDateTime;
   t = t - epoch_diff;
   return t;
  }
 }
 
 int __stdcall remStor38(const char *pchFile) //GetSyncPlatforms
 {
  return 1;
 }

 int __stdcall remStor3C()     //GetFileCount
 {
  int count = 0;
  HANDLE hFind;
  WIN32_FIND_DATA wfd;
  int len = lstrlen((LPCWSTR)saveDir)+4;
  HANDLE hHeap = GetProcessHeap();
  char* fname = (char*)HeapAlloc(hHeap,HEAP_ZERO_MEMORY,len);
  lstrcpy((LPWSTR)fname, (LPCWSTR)saveDir);
  lstrcat((LPWSTR)fname, (LPCWSTR)"*.*");
  hFind = FindFirstFile((LPWSTR)fname, &wfd);
  do
  {
   if (wfd.dwFileAttributes == FILE_ATTRIBUTE_ARCHIVE)
   {
    count++;
   }
  }
  while (FindNextFile(hFind,&wfd));
  FindClose(hFind);
  HeapFree(hHeap,0,fname);
  return count;
 }

 char* __stdcall remStor40(int numFile, DWORD* size)      //GetFileNameAndSize
 {
  int count = 0;
  HANDLE hFind;
  WIN32_FIND_DATA wfd;
  int len = lstrlen((LPCWSTR)saveDir)+4;
  HANDLE hHeap = GetProcessHeap();
  char* fname = (char*)HeapAlloc(hHeap,HEAP_ZERO_MEMORY,len);
  lstrcpy((LPWSTR)fname, (LPCWSTR)saveDir);
  lstrcat((LPWSTR)fname, (LPCWSTR)"*.*");
  hFind = FindFirstFile((LPWSTR)fname, &wfd);
  do
  {
   if (wfd.dwFileAttributes == FILE_ATTRIBUTE_ARCHIVE)
   {
    if (count != numFile)
    {
     count++;
    }
    else if (count == numFile)
    {
     *size = wfd.nFileSizeLow;
     FindClose(hFind);
     HeapFree(hHeap,0,fname);
     int nameLen = lstrlen(wfd.cFileName)+1;
     char* name = (char*)HeapAlloc(hHeap,HEAP_ZERO_MEMORY,nameLen);
     lstrcpy((LPWSTR)name, wfd.cFileName);
     return name;
    }
   }
  }
  while (FindNextFile(hFind,&wfd));
  FindClose(hFind);
  HeapFree(hHeap,0,fname);
  return 0;
 }

 bool __stdcall remStor44(int *pnTotalBytes, int *puAvailableBytes)      //GetQuota
 {
  *pnTotalBytes = 0x10000000;
  *puAvailableBytes = 0x10000000;
  return true;
 }

 bool __stdcall remStor48()      //IsCloudEnabledForAccount
 {
  return false;
 }

 bool __stdcall remStor4C()      //SetCloudEnabledForApp
 {
  return false;
 }
 
 bool __stdcall remStorA0(int a) //UpdatingCloudFiles
 {
  return false;
 }

 // funzioni SteamFriends
 char* __stdcall friends0()
 {
  return playerName;
 }
 bool __stdcall friends8()
 {
  return (false);
 }
 bool __stdcall friendsC(int a)
 {
  return (false);
 }
 bool __stdcall friends10(int a, int b, int c)
 {
  return (false);
 }
 bool __stdcall friends1C(int a, int b)
 {
  return playerName;
 }
 bool __stdcall friends20(int a, int b, int c)
 {
  return (false);
 }
 
 /*bool __stdcall friends28(int a, int b)
 {
  return (false);
 }*/
 //virtual const char *GetPlayerNickname( CSteamID steamIDPlayer ) = 0;
 char* __stdcall friends28(int steamIDPlayer)
 {
  return (playerName);
 }
 
 bool __stdcall friends4C()
 {
  return (false);
 }
 bool __stdcall friends50(int a, int b, int c)
 {
  return (false);
 }
 bool __stdcall friends54(int a)
 {
  return (false);
 }
 bool __stdcall friends58(int a)
 {
  return (false);
 }
 
 //virtual void ActivateGameOverlayToUser( const char *pchDialog, CSteamID steamID ) = 0;
// bool __stdcall friends5C(int a)
 void __stdcall friends5C(const char *pchDialog, int steamID, int sticazzi)
 {
  //return ();
 }
 
 bool __stdcall friends60(int a)
 {
  return (false);
 }
 bool __stdcall friends64(int a, int b)
 {
  return (false);
 }
 bool __stdcall friends6C(int a, int b)
 {
  return (false);
 }
 bool __stdcall friends70(int a, int b)
 {
  return (false);
 }
 bool __stdcall friends74(int a, int b)
 {
  return (false);
 }
 bool __stdcall friends7C(int a, int b, int c)
 {
  return (false);
 }
 bool __stdcall friends90(int a, int b)
 {
  return (false);
 }
 bool __stdcall friends94(int a, int b)
 {
  return (false);
 }
 
 //funzioni SteamUserStats
 bool __stdcall userStats0()
 {
  return (true);
 }
 bool __stdcall userStats4()
 {
  return (true);
 }
 bool __stdcall userStats8(int a, int b)
 {
  return (true);
 }
 bool __stdcall userStats10(int a, int b)
 {
  return (true);
 }
 bool __stdcall userStats18(int a, int b)
 {
  return (true);
 }
 bool __stdcall userStats1C(int a)
 {
  return (true);
 }
 bool __stdcall userStats20(int a)
 {
  return (true);
 }
 bool __stdcall userStats24(int a, int b, int c)
 {
  return (true);
 }
 bool __stdcall userStats28()
 {
  return (true);
 }
 bool __stdcall userStats30(int a, int b)
 {
  return (true);
 }
 bool __stdcall userStats34(int a, int b, int c)
 {
  return (true);
 }
// virtual uint32 GetNumAchievements( CGameID nGameID ) = 0;
 int __stdcall userStats38(int nGameID)
 {
  return (0);
 }
 
 bool __stdcall userStats40(int a, int b)
 {
  return (true);
 }
 bool __stdcall userStats50(int a, int b, int c)
 {
  return (true);
 }
 bool __stdcall userStats54(int a)
 {
  return (true);
 }
 bool __stdcall userStats58(int a, int b, int c)
 {
  return (true);
 }
 bool __stdcall userStats5C(int a)
 {
  return (true);
 }
 bool __stdcall userStats60(int a, int b)
 {
  return (true);
 }
 bool __stdcall userStats64(int a, int b)
 {
  return (true);
 }
 bool __stdcall userStats68(int a, int b, int c, int d, int e)
 {
  return (true);
 }
 bool __stdcall userStats70(int a, int b, int c, int d, int e)
 {
  return (true);
 }
 bool __stdcall userStats74(int a, int b, int c, int d)
 {
  return (true);
 }
 bool __stdcall userStats78(int a, int b, int c, int d, int e, int f)
 {
  return (true);
 }
 bool __stdcall userStats7C(int a, int b, int c, int d, int e, int f)
 {
  return (true);
 }

 //funzioni SteamClient
 bool __stdcall client54(int a)
 {
  return (true);
 }

 //funzioni SteamMatchmaking
 bool __stdcall matchmaking10()
 {
  return (true);
 }
 bool __stdcall matchmaking14(int a, int b, int c)
 {
  return (true);
 }
 bool __stdcall matchmaking18(int a, int b, int c)
 {
  return (true);
 }
 bool __stdcall matchmaking1C(int a, int b)
 {
  return (true);
 }
 bool __stdcall matchmaking20(int a)
 {
  return (true);
 }
 bool __stdcall matchmaking24(int a)
 {
  return (true);
 }
 bool __stdcall matchmaking28(int a)
 {
  return (true);
 } 
 bool __stdcall matchmaking30(int a, int b)
 {
  return (true);
 }
 bool __stdcall matchmaking34(int a, int b)
 {
  return (true);
 }
 bool __stdcall matchmaking38(int a, int b)
 {
  return (true);
 }
 bool __stdcall matchmaking3C(int a, int b)
 {
  return (true);
 }
 bool __stdcall matchmaking44(int a, int b)
 {
  return (true);
 }
 bool __stdcall matchmaking48(int a, int b, int c, int d)
 {
  return (true);
 }
 bool __stdcall matchmaking4C(int a, int b, int c)
 {
  return (true);
 }
 bool __stdcall matchmaking50(int a, int b, int c, int d)
 {
  return (true);
 }
 bool __stdcall matchmaking54(int a, int b)
 {
  return (true);
 }
 bool __stdcall matchmaking58(int a, int b, int c, int d, int e, int f, int g)
 {
  return (true);
 }
 bool __stdcall matchmaking64(int a, int b, int c, int d)
 {
  return (true);
 }
 bool __stdcall matchmaking6C(int a, int b, int c, int d, int e)
 {
  return (true);
 }
 bool __stdcall matchmaking70(int a, int b)
 {
  return (true);
 }
 bool __stdcall matchmaking78(int a, int b, int c, int d, int e)
 {
  return (true);
 }
 bool __stdcall matchmaking80(int a, int b)
 {
  return (true);
 }
 bool __stdcall matchmaking8C(int a, int b, int c)
 {
  return (true);
 }

 //funzioni SteamNetworking
 bool __stdcall networking0()
 {
  return (true);
 }
 bool __stdcall networking4(int a, int b)
 {
  return (false);
 }
 bool __stdcall networking8(int a, int b, int c, int d, int e)
 {
  return (false);
 }
 bool __stdcall networking1C(int a)
 {
  return (true);
 }

 //funzioni SteamGameServerNetworking
 bool __stdcall gameServerNetworking8(int a, int b, int c, int d, int e)
 {
  return (false);
 }
 
 //funzioni SteamGameServerStats
 bool __stdcall gameServerStats0()
 {
  return (false);
 }
 
 //funzioni SteamGameServerUtils
 bool __stdcall gameServerUtils0()
 {
  return (false);
 }
 
 //funzioni SteamScreenshots
 void __stdcall screenshotsC(bool a) { }

 __declspec(dllexport) bool SteamController()
 {
  return (false);
 }
 
//funzioni SteamUGC
//virtual UGCQueryHandle_t CreateQueryUserUGCRequest( AccountID_t unAccountID, EUserUGCList eListType, EUGCMatchingUGCType eMatchingUGCType, EUserUGCListSortOrder eSortOrder, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32 unPage ) = 0;
 bool __stdcall UGC0(int unAccountID, int eListType, int eMatchingUGCType, int eSortOrder, int nCreatorAppID, int nConsumerAppID, int unPage)
 {
 	return false;
 }
//virtual UGCQueryHandle_t CreateQueryAllUGCRequest( EUGCQuery eQueryType, EUGCMatchingUGCType eMatchingeMatchingUGCTypeFileType, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32 unPage ) = 0;
 bool __stdcall UGC4(int eQueryType, int eMatchingeMatchingUGCTypeFileType, int nCreatorAppID, int nConsumerAppID, int unPage)
 {
 	return false;
 }
//virtual SteamAPICall_t SendQueryUGCRequest( UGCQueryHandle_t handle ) = 0;
 bool __stdcall UGC8(long int handle )
 {
 	return 0;
 }
//virtual bool GetQueryUGCResult( UGCQueryHandle_t handle, uint32 index, SteamUGCDetails_t *pDetails ) = 0;

 bool __stdcall UGCC(int handle, int index, char *pDetails)
 {
 	return false;
 }
//virtual bool ReleaseQueryUGCRequest( UGCQueryHandle_t handle ) = 0;
 bool __stdcall UGC10(int handle)
 {
 	return true;
 }
//virtual bool AddRequiredTag( UGCQueryHandle_t handle, const char *pTagName ) = 0;
 bool __stdcall UGC14(int handle, const char *pTagName)
 {
 	return false;
 }
//virtual bool AddExcludedTag( UGCQueryHandle_t handle, const char *pTagName ) = 0;
 bool __stdcall UGC18(int handle, const char *pTagName)
 {
 	return false;
 }
//virtual bool SetReturnLongDescription( UGCQueryHandle_t handle, bool bReturnLongDescription ) = 0;
 bool __stdcall UGC1C(int handle, bool bReturnLongDescription)
 {
 	return false;
 }
//virtual bool SetReturnTotalOnly( UGCQueryHandle_t handle, bool bReturnTotalOnly ) = 0;
 bool __stdcall UGC20(int handle, bool bReturnTotalOnly)
 {
 	return false;
 }
//virtual bool SetAllowCachedResponse( UGCQueryHandle_t handle, uint32 uUnk ) = 0;
 bool __stdcall UGC24(int handle, int uUnk)
 {
 	return false;
 }
//virtual bool SetCloudFileNameFilter( UGCQueryHandle_t handle, const char *pMatchCloudFileName ) = 0;
 bool __stdcall UGC28(int handle, const char *pMatchCloudFileName)
 {
 	return false;
 }
//virtual bool SetMatchAnyTag( UGCQueryHandle_t handle, bool bMatchAnyTag ) = 0;
 bool __stdcall UGC2C(int handle, bool bMatchAnyTag)
 {
 	return false;
 }
//virtual bool SetSearchText( UGCQueryHandle_t handle, const char *pSearchText ) = 0;
 bool __stdcall UGC30(int handle, const char *pSearchText)
 {
 	return false;
 }
//virtual bool SetRankedByTrendDays( UGCQueryHandle_t handle, uint32 unDays ) = 0;
 bool __stdcall UGC34(int handle, int unDays)
 {
 	return false;
 }
//virtual SteamAPICall_t RequestUGCDetails( PublishedFileId_t nPublishedFileID, uint32 uUnk ) = 0;
  bool __stdcall UGC38(int nPublishedFileID, int uUnk)
 {
 	return false;
 }
 
 typedef void (*funcPtr)(void);

 funcPtr arrayApps[15];
 funcPtr **ptrPtrApps;
 funcPtr *ptrApps;

 funcPtr arrayUtils[50];
 funcPtr **ptrPtrUtils;
 funcPtr *ptrUtils;

 funcPtr arrayUser[24];
 funcPtr **ptrPtrUser;
 funcPtr *ptrUser;

 funcPtr arrayRemStor[41];
 funcPtr **ptrPtrRemStor;
 funcPtr *ptrRemStor;

 funcPtr arrayFriends[38];
 funcPtr **ptrPtrFriends;
 funcPtr *ptrFriends;

 funcPtr arrayUserStats[32];
 funcPtr **ptrPtrUserStats;
 funcPtr *ptrUserStats;

 funcPtr arrayClient[24];
 funcPtr **ptrPtrClient;
 funcPtr *ptrClient;

 funcPtr arrayMatchmaking[36];
 funcPtr **ptrPtrMatchmaking;
 funcPtr *ptrMatchmaking;

 funcPtr arrayNetworking[8];
 funcPtr **ptrPtrNetworking;
 funcPtr *ptrNetworking;

 funcPtr arrayGameServerNetworking[3];
 funcPtr **ptrPtrGameServerNetworking;
 funcPtr *ptrGameServerNetworking;
 
 funcPtr arrayGameServerStats[1];
 funcPtr **ptrPtrGameServerStats;
 funcPtr *ptrGameServerStats;
 
 funcPtr arrayGameServerUtils[1];
 funcPtr **ptrPtrGameServerUtils;
 funcPtr *ptrGameServerUtils;
 
 funcPtr arrayScreenshots[4];
 funcPtr **ptrPtrScreenshots;
 funcPtr *ptrScreenshots;

 funcPtr arrayUGC[15];
 funcPtr **ptrPtrUGC;
 funcPtr *ptrUGC;

 int regCallback = 0;
 int matrixCallback[1000][2];

 __declspec(dllexport) bool SteamAPI_Init()
 {
  HANDLE hHeap = GetProcessHeap();
  lang = (char*)HeapAlloc(hHeap,HEAP_ZERO_MEMORY,1024);
  appID = (char*)HeapAlloc(hHeap,HEAP_ZERO_MEMORY,1024);
  playerName = (char*)HeapAlloc(hHeap,HEAP_ZERO_MEMORY,1024);

  GetPrivateProfileString((LPCWSTR)"Settings",(LPCWSTR)"Language",(LPCWSTR)"english",(LPWSTR)lang,1024,(LPCWSTR)".\\CPY.ini");
  GetPrivateProfileString((LPCWSTR)"Settings",(LPCWSTR)"AppID",(LPCWSTR)"",(LPWSTR)appID,1024,(LPCWSTR)".\\CPY.ini");
  GetPrivateProfileString((LPCWSTR)"Settings",(LPCWSTR)"PlayerName",(LPCWSTR)"",(LPWSTR)playerName,1024,(LPCWSTR)".\\CPY.ini");

  saveDir = (char*)HeapAlloc(hHeap,HEAP_ZERO_MEMORY,1024);
  GetPrivateProfileString((LPCWSTR)"Settings",(LPCWSTR)"SavePath",(LPCWSTR)"",(LPWSTR)saveDir,1024,(LPCWSTR)".\\CPY.ini");
  if (lstrcmp((LPCWSTR)saveDir,(LPCWSTR)"%DEFAULT_CPY_DIR%") == 0)
  {
   SHGetFolderPath(NULL,CSIDL_PERSONAL,NULL,0,(LPWSTR)saveDir);
  }
  wsprintf((LPWSTR)saveDir,(LPCWSTR)"%s\\CPY_SAVES",saveDir);
  CreateDirectory((LPCWSTR)saveDir, NULL);
  wsprintf((LPWSTR)saveDir,(LPCWSTR)"%s\\%s",saveDir,playerName);
  CreateDirectory((LPCWSTR)saveDir, NULL);
  wsprintf((LPWSTR)saveDir,(LPCWSTR)"%s\\%s",saveDir,appID);
  CreateDirectory((LPCWSTR)saveDir, NULL);
  wsprintf((LPWSTR)saveDir,(LPCWSTR)"%s\\",saveDir);
  
  arrayApps[0]=(funcPtr)apps0;
  arrayApps[1]=(funcPtr)apps4;
  arrayApps[2]=(funcPtr)apps8;
  arrayApps[3]=(funcPtr)appsC;
  arrayApps[4]=(funcPtr)apps10;
  arrayApps[6]=(funcPtr)apps18;
  arrayApps[7]=(funcPtr)apps1C;
  arrayApps[10]=(funcPtr)apps28;
  arrayApps[11]=(funcPtr)apps2C;
  arrayApps[14]=(funcPtr)apps38;
  ptrApps=arrayApps;
  ptrPtrApps=&ptrApps;

  arrayUtils[2]=(funcPtr)utils8;
  arrayUtils[3]=(funcPtr)utilsC;
  arrayUtils[4]=(funcPtr)utils10;
  arrayUtils[5]=(funcPtr)utils14;
  arrayUtils[6]=(funcPtr)utils18;
  arrayUtils[9]=(funcPtr)utils24;
  arrayUtils[10]=(funcPtr)utils28;
  arrayUtils[11]=(funcPtr)utils2C;
  arrayUtils[13]=(funcPtr)utils34;
  arrayUtils[15]=(funcPtr)utils3C;
  arrayUtils[16]=(funcPtr)utils40;
  arrayUtils[17]=(funcPtr)utils44;
  arrayUtils[18]=(funcPtr)utils48;
  
  arrayUtils[20]=(funcPtr)utils50;
  arrayUtils[21]=(funcPtr)utils54;
  arrayUtils[22]=(funcPtr)utils58;
    
  ptrUtils=arrayUtils;
  ptrPtrUtils=&ptrUtils;

  arrayUser[1]=(funcPtr)user4;
  arrayUser[2]=(funcPtr)user8;
  arrayUser[4]=(funcPtr)user10;
  arrayUser[6]=(funcPtr)user18;
  arrayUser[7]=(funcPtr)user1C;
  arrayUser[8]=(funcPtr)user20;
  arrayUser[9]=(funcPtr)user24;
  arrayUser[10]=(funcPtr)user28;
  arrayUser[11]=(funcPtr)user2C;
  arrayUser[12]=(funcPtr)user30;
  arrayUser[13]=(funcPtr)user34;
  arrayUser[14]=(funcPtr)user38;
  arrayUser[15]=(funcPtr)user3C;
  arrayUser[16]=(funcPtr)user40;
  arrayUser[17]=(funcPtr)user44;
  arrayUser[18]=(funcPtr)user48;
  arrayUser[19]=(funcPtr)user4C;
  arrayUser[20]=(funcPtr)user50;
  ptrUser=arrayUser;
  ptrPtrUser=&ptrUser;

  arrayRemStor[0]=(funcPtr)remStor0;
  arrayRemStor[1]=(funcPtr)remStor4;
  arrayRemStor[2]=(funcPtr)remStor8;
  arrayRemStor[3]=(funcPtr)remStorC;
  arrayRemStor[10]=(funcPtr)remStor28;
  arrayRemStor[11]=(funcPtr)remStor2C;
  arrayRemStor[12]=(funcPtr)remStor30;
  arrayRemStor[13]=(funcPtr)remStor34;
  arrayRemStor[14]=(funcPtr)remStor38;
  arrayRemStor[15]=(funcPtr)remStor3C;
  arrayRemStor[16]=(funcPtr)remStor40;
  arrayRemStor[17]=(funcPtr)remStor44;
  arrayRemStor[18]=(funcPtr)remStor48;
  arrayRemStor[19]=(funcPtr)remStor4C;
  arrayRemStor[40]=(funcPtr)remStorA0;
  
  ptrRemStor=arrayRemStor;
  ptrPtrRemStor=&ptrRemStor;

  arrayFriends[0]=(funcPtr)friends0;
  arrayFriends[2]=(funcPtr)friends8;
  arrayFriends[3]=(funcPtr)friendsC;
  arrayFriends[4]=(funcPtr)friends10;
  arrayFriends[7]=(funcPtr)friends1C;
  arrayFriends[8]=(funcPtr)friends20;
  arrayFriends[10]=(funcPtr)friends28;
  arrayFriends[19]=(funcPtr)friends4C;
  arrayFriends[20]=(funcPtr)friends50;
  arrayFriends[21]=(funcPtr)friends54;
  arrayFriends[22]=(funcPtr)friends58;
  arrayFriends[23]=(funcPtr)friends5C;
  arrayFriends[24]=(funcPtr)friends60;
  arrayFriends[25]=(funcPtr)friends64;
  arrayFriends[27]=(funcPtr)friends6C;
  arrayFriends[28]=(funcPtr)friends70;
  arrayFriends[29]=(funcPtr)friends74;
  arrayFriends[31]=(funcPtr)friends7C;
  arrayFriends[36]=(funcPtr)friends90;
  arrayFriends[37]=(funcPtr)friends94; 
  ptrFriends=arrayFriends;
  ptrPtrFriends=&ptrFriends;

  arrayUserStats[0]=(funcPtr)userStats0;
  arrayUserStats[1]=(funcPtr)userStats4;
  arrayUserStats[2]=(funcPtr)userStats8;
  arrayUserStats[4]=(funcPtr)userStats10;
  arrayUserStats[6]=(funcPtr)userStats18;
  arrayUserStats[7]=(funcPtr)userStats1C;
  arrayUserStats[8]=(funcPtr)userStats20;
  arrayUserStats[9]=(funcPtr)userStats24;
  arrayUserStats[10]=(funcPtr)userStats28;
  arrayUserStats[12]=(funcPtr)userStats30;
  arrayUserStats[13]=(funcPtr)userStats34;
  arrayUserStats[14]=(funcPtr)userStats38;
  arrayUserStats[16]=(funcPtr)userStats40;
  arrayUserStats[20]=(funcPtr)userStats50;
  arrayUserStats[21]=(funcPtr)userStats54;
  arrayUserStats[22]=(funcPtr)userStats58;
  arrayUserStats[23]=(funcPtr)userStats5C;
  arrayUserStats[24]=(funcPtr)userStats60;
  arrayUserStats[25]=(funcPtr)userStats64;
  arrayUserStats[26]=(funcPtr)userStats68;
  arrayUserStats[28]=(funcPtr)userStats70;
  arrayUserStats[29]=(funcPtr)userStats74;
  arrayUserStats[30]=(funcPtr)userStats78;
  arrayUserStats[31]=(funcPtr)userStats7C;
  ptrUserStats=arrayUserStats;
  ptrPtrUserStats=&ptrUserStats;

  arrayClient[21]=(funcPtr)client54;
  ptrClient=arrayClient;
  ptrPtrClient=&ptrClient;

  arrayMatchmaking[4]=(funcPtr)matchmaking10;
  arrayMatchmaking[5]=(funcPtr)matchmaking14;
  arrayMatchmaking[6]=(funcPtr)matchmaking18;
  arrayMatchmaking[7]=(funcPtr)matchmaking1C;
  arrayMatchmaking[8]=(funcPtr)matchmaking20;
  arrayMatchmaking[9]=(funcPtr)matchmaking24;
  arrayMatchmaking[10]=(funcPtr)matchmaking28; 
  arrayMatchmaking[12]=(funcPtr)matchmaking30;
  arrayMatchmaking[13]=(funcPtr)matchmaking34;
  arrayMatchmaking[14]=(funcPtr)matchmaking38;
  arrayMatchmaking[15]=(funcPtr)matchmaking3C;
  arrayMatchmaking[17]=(funcPtr)matchmaking44;
  arrayMatchmaking[18]=(funcPtr)matchmaking48;
  arrayMatchmaking[19]=(funcPtr)matchmaking4C;
  arrayMatchmaking[20]=(funcPtr)matchmaking50;
  arrayMatchmaking[21]=(funcPtr)matchmaking54;
  arrayMatchmaking[22]=(funcPtr)matchmaking58;
  arrayMatchmaking[25]=(funcPtr)matchmaking64;
  arrayMatchmaking[27]=(funcPtr)matchmaking6C;
  arrayMatchmaking[28]=(funcPtr)matchmaking70;
  arrayMatchmaking[30]=(funcPtr)matchmaking78;
  arrayMatchmaking[32]=(funcPtr)matchmaking80;
  arrayMatchmaking[35]=(funcPtr)matchmaking8C;
  ptrMatchmaking=arrayMatchmaking;
  ptrPtrMatchmaking=&ptrMatchmaking;

  arrayNetworking[0]=(funcPtr)networking0;
  arrayNetworking[1]=(funcPtr)networking4;
  arrayNetworking[2]=(funcPtr)networking8;
  arrayNetworking[7]=(funcPtr)networking1C;
  ptrNetworking=arrayNetworking;
  ptrPtrNetworking=&ptrNetworking;

  arrayGameServerNetworking[2]=(funcPtr)gameServerNetworking8;
  ptrGameServerNetworking=arrayGameServerNetworking;
  ptrPtrGameServerNetworking=&ptrGameServerNetworking;
  
  arrayGameServerStats[0]=(funcPtr)gameServerStats0;
  ptrGameServerStats=arrayGameServerStats;
  ptrPtrGameServerStats=&ptrGameServerStats;

  arrayGameServerUtils[0]=(funcPtr)gameServerUtils0;
  ptrGameServerUtils=arrayGameServerUtils;
  ptrPtrGameServerUtils=&ptrGameServerUtils;
  
  arrayScreenshots[3]=(funcPtr)screenshotsC;
  ptrScreenshots=arrayScreenshots;
  ptrPtrScreenshots=&ptrScreenshots;

 arrayUGC[0]=(funcPtr)UGC0;
 arrayUGC[1]=(funcPtr)UGC4;
 arrayUGC[2]=(funcPtr)UGC8;
 arrayUGC[3]=(funcPtr)UGCC;
 arrayUGC[4]=(funcPtr)UGC10;
 arrayUGC[5]=(funcPtr)UGC14;
 arrayUGC[6]=(funcPtr)UGC18;
 arrayUGC[7]=(funcPtr)UGC1C;
 arrayUGC[8]=(funcPtr)UGC20;
 arrayUGC[9]=(funcPtr)UGC24;
 arrayUGC[10]=(funcPtr)UGC28;
 arrayUGC[11]=(funcPtr)UGC2C;
 arrayUGC[12]=(funcPtr)UGC30;
 arrayUGC[13]=(funcPtr)UGC34;
 arrayUGC[14]=(funcPtr)UGC38;
 ptrUGC=arrayUGC;
 ptrPtrUGC=&ptrUGC;
  
  return (true);
 }

 __declspec(dllexport) bool SteamAPI_RestartAppIfNecessary()
 {
  return (false);
 }

 __declspec(dllexport) bool SteamAPI_Shutdown()
 {
  return (true);
 }

 __declspec(dllexport) bool SteamAPI_InitSafe()
 {
  return (false);
 }

 __declspec(dllexport) bool SteamAPI_IsSteamRunning()
 {
  return (true);
 }

 __declspec(dllexport) funcPtr** SteamApps()
 {
  return ptrPtrApps;
 }

 __declspec(dllexport) funcPtr** SteamRemoteStorage()
 {
  return ptrPtrRemStor;
 }

 __declspec(dllexport) funcPtr** SteamUser()
 {
  return ptrPtrUser;
 }

 __declspec(dllexport) funcPtr** SteamUtils()
 {
  return ptrPtrUtils;
 }

 __declspec(dllexport) funcPtr** SteamFriends()
 {
  return ptrPtrFriends;
 }

 __declspec(dllexport) funcPtr** SteamClient()
 {
  return ptrPtrClient;
 }

 __declspec(dllexport) funcPtr** SteamNetworking()
 {
  return ptrPtrNetworking;
 }

 __declspec(dllexport) funcPtr** SteamMatchmaking()
 {
  return ptrPtrMatchmaking;
 }

 __declspec(dllexport) funcPtr** SteamUserStats()
 {
  return ptrPtrUserStats;
 }

 __declspec(dllexport) bool SteamAPI_UnregisterCallback()
 {
  return true;
 }

 __declspec(dllexport) bool SteamAPI_RegisterCallback(int ptr, int id)
 {
  if (regCallback < 1000)
  {
   matrixCallback[regCallback][0] = ptr;
   matrixCallback[regCallback][1] = id;
   regCallback++;
  }
  return true;
 }

 __declspec(dllexport) bool SteamAPI_RunCallbacks()
 {
  return true;
 }

 __declspec(dllexport) bool SteamAPI_SetMiniDumpComment()
 {
  return true;
 }

 __declspec(dllexport) bool SteamAPI_WriteMiniDump()
 {
  return true;
 }

 __declspec(dllexport) bool SteamAPI_UnregisterCallResult()
 {
  return true;
 }

 __declspec(dllexport) bool SteamAPI_RegisterCallResult()
 {
  return true;
 }

 __declspec(dllexport) bool SteamMatchmakingServers()
 {
  return true;
 }

 __declspec(dllexport) bool SteamGameServer_Init()
 {
  return false;
 }

 __declspec(dllexport) bool SteamGameServer()
 {
  return false;
 }
 
 __declspec(dllexport) bool SteamGameServer_BSecure()
 {
  return true;
 }

 __declspec(dllexport) funcPtr** SteamGameServerNetworking()
 {
  return ptrPtrGameServerNetworking;
 }
 
 __declspec(dllexport) funcPtr** SteamGameServerStats()
 {
  return ptrPtrGameServerStats;
 }
 
 __declspec(dllexport) funcPtr** SteamGameServerUtils()
 {
  return ptrPtrGameServerUtils;
 }

 __declspec(dllexport) bool SteamGameServer_Shutdown()
 {
  return true;
 }

 __declspec(dllexport) bool SteamGameServer_RunCallbacks()
 {
  return true;
 }
 
 __declspec(dllexport) DWORD64 SteamGameServer_GetSteamID()
 {
  return 1234;
 }
 
 __declspec(dllexport) bool SteamHTTP()
 {
  return false;
 }
 
 __declspec(dllexport) funcPtr** SteamScreenshots()
 {
  return ptrPtrScreenshots;
 }
 
  __declspec(dllexport) funcPtr** SteamUGC()
 {
  return ptrPtrUGC;
 }

 
}
