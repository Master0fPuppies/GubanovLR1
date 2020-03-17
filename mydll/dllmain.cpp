// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include <string>
#include <Windows.h>
#include <iostream>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
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
extern "C" __declspec(dllexport) bool isExist(char volumeNum)
{
    std::string exPath = "\\\\.\\";
    std::string path = exPath + volumeNum+':';
    HANDLE fileHandle = CreateFileA(path.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    
    if (fileHandle != INVALID_HANDLE_VALUE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
    CloseHandle(fileHandle);
}
extern "C" __declspec(dllexport) bool isNTFS(char volumeNum, dll_NTFSBootLoader* mainstruc)
{
    std::string exPath = "\\\\.\\";
    std::string path = exPath + volumeNum + ':';
    HANDLE fileHandle = CreateFileA(path.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    ULONGLONG startOffset = 0;
    BYTE buffer[512];
    memset(buffer, 0, 512);
    DWORD bytesToRead = 512;
    DWORD bytesRead;
    LARGE_INTEGER sectorOffset;
    sectorOffset.QuadPart = 0;
    unsigned long currentPosition = SetFilePointer(fileHandle, sectorOffset.LowPart, NULL, FILE_BEGIN);
    bool stopSpamTrash = ReadFile(fileHandle, buffer, bytesToRead, &bytesRead, NULL);
    *mainstruc = *reinterpret_cast<dll_NTFSBootLoader*>(buffer);
    CloseHandle(fileHandle);
    BYTE* gotByte = mainstruc->sysName;
    std::string resultSysName = std::string((char*)(gotByte), 4);
    if (resultSysName == "NTFS")
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
    CloseHandle(fileHandle);
}