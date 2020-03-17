// pch.h: это предварительно скомпилированный заголовочный файл.
// Перечисленные ниже файлы компилируются только один раз, что ускоряет последующие сборки.
// Это также влияет на работу IntelliSense, включая многие функции просмотра и завершения кода.
// Однако изменение любого из приведенных здесь файлов между операциями сборки приведет к повторной компиляции всех(!) этих файлов.
// Не добавляйте сюда файлы, которые планируете часто изменять, так как в этом случае выигрыша в производительности не будет.

#ifndef PCH_H
#define PCH_H
// Добавьте сюда заголовочные файлы для предварительной компиляции
#include "framework.h"

#endif //PCH_H
#pragma pack(push,1)
typedef struct
{
	BYTE jumpCode[3];//0x0000
	BYTE sysName[8];//0x0003
	WORD bytesPerSector;//0x000B
	BYTE sectorPerCluster;//0x000D
	WORD reservedSectors;//0x000E
	BYTE notInteresting[3];
	WORD notInteresting2;
	BYTE mediaDescriptor;//0x0015
	WORD notInteresting3;
	WORD sectorPerTrack;//0x0018
	WORD numOfHeaders;//0x001A
	DWORD hiddenSectors;
	DWORD notInteresting4;
	DWORD notInteresting5;
	ULONGLONG sectorsInTheVolume;//0x0028
	ULONGLONG lcnOfMFT;//0x0030
	ULONGLONG lcnOfSMFTMirr;//0x0038
	DWORD clusterPerMftRecord;//0x0040
	BYTE clusterPerIndexRecord;//0x0044
	BYTE  notInteresting6[3];
	ULONGLONG volumeID;//0x0048
	DWORD  notInteresting7;
	BYTE  notInteresting8[426];
	WORD markerOfTheEnd;
} dll_NTFSBootLoader;
#pragma pack(pop)