#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <Psapi.h> //Windows API Header

void PrintProcessNameandID( DWORD processID )
{
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown"); 
    //Default process name is "unknown"

    //Initializes a Process Handle
    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
    //A process handle is an integer value that identifies a process to windows. The handlers desired access is "PROCESS_QUERY_INFORMATION | PROCESS_VM_READ" and is not an inherited handler.


    //Process Names
    if (NULL != hProcess)
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), &cbNeeded))
        {
            GetModuleBaseName( hProcess, hMod, szProcessName, sizeof(szProcessName)/sizeof(TCHAR) );
        }
    }

    //Printing Process Name and ID
    _tprintf( TEXT("%s  (PID: %u)\n"), szProcessName, processID );

    //Handle Release
    CloseHandle( hProcess );
}

int main( void )
{
    //Listing process IDs
    DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;

    if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
    {
        return 1;
    }

    //Number of process IDs returned
    cProcesses = cbNeeded / sizeof(DWORD);

    //Print Process name and ID

    for ( i = 0; i < cProcesses; i++ )
    {
        if ( aProcesses[i] != 0 )
        {
            PrintProcessNameandID( aProcesses[i] );
        }
    }

    return 0;
}
