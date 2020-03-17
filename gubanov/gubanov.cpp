#include <iostream>
#include <Windows.h>
#include "gubanov_main.h"

using namespace std;
int main()
{
    HMODULE hLib = LoadLibrary(L"mydll.dll");
    if (hLib == NULL)
    {
        cout << "No able to attach dll !" << endl;
    }
    else
    {
        cout << "Please, insert disk you are interested in name (like C)" << endl;
        char disk;
        cin >> disk;
        IfDiskExistType isDiskExist = (IfDiskExistType)GetProcAddress(hLib, "isExist");
        if (!isDiskExist)
        {
            cout << " Problems with dll function, exiting" << endl;
        }
        else
        {
            bool diskExistResult = isDiskExist(disk);
            if (diskExistResult == TRUE)
            {
                IfDiskNTFSType isDiskNTFS = (IfDiskNTFSType)GetProcAddress(hLib, "isNTFS");
                if (!isDiskNTFS)
                {
                    cout << " Problems with dll function, exiting " << endl;
                }
                else
                {
                    m_NTFSBootLoader mystruc;
                    bool isNTFSresult= isDiskNTFS(disk, mystruc);
                    if (isNTFSresult == TRUE)
                    {
                        std::cout << "~ File system name: " << mystruc.sysName << " ~"<< std::endl;
                        std::cout << "~ Sectors per track: " << mystruc.sectorPerTrack << " ~" << std::endl;
                        std::cout << "~ Sectors per cluster: " << WORD(mystruc.sectorPerCluster) << " ~" << std::endl;
                        std::cout << "~ Bytes per sector: " << mystruc.bytesPerSector << " ~" << std::endl;
                        std::cout << "~ Number of heads: " << mystruc.numOfHeaders << " ~" << std::endl;
                        std::cout << "~ Number of sectors in the volume: " << mystruc.sectorsInTheVolume << " ~" << std::endl;
                        std::cout << "~ LCN of VCN 0 of the MFT: " << mystruc.lcnOfMFT << " ~" << std::endl;
                        std::cout << "~ LCN of VCN 0 of the MFTMirr: " << mystruc.lcnOfSMFTMirr << " ~" << std::endl;
                        std::cout << "~ Clusters per MFT Record: " << mystruc.clusterPerMftRecord << " ~" << std::endl;
                        std::cout << "~ Clusters per Index Record: " << WORD(mystruc.clusterPerIndexRecord) << " ~" << std::endl;
                        std::cout << "~ Volume serial number: " << mystruc.volumeID << " ~" << std::endl;
                    }
                    else
                    {
                        cout << "This disk is not NTFS, stopping" << endl;
                    }
                }
            }
            else
            {
                cout << "This disk not found, exiting" << endl;
            }
        }
    FreeLibrary(hLib);
    };
}