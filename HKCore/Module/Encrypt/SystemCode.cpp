// SystemCode.cpp: implementation of the CSystemCode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SystemCode.h"

#include<atlbase.h>
#include<atlconv.h>
#include"iphlpapi.h"
#pragma comment(lib,"Iphlpapi.lib")

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSystemCode::CSystemCode()
{
	uSystemInfoLen = 0;
	m_nSysInfoCount = 0;
}

CSystemCode::~CSystemCode()
{

}

BOOL CSystemCode::WinNTHDSerialNumAsScsiRead( BYTE* dwSerial, UINT* puSerialLen, UINT uMaxSerialLen )
{
    BOOL bInfoLoaded = FALSE;
    
    for( int iController = 0; iController < 2; ++ iController )
    {
        HANDLE hScsiDriveIOCTL = 0;
        CString   szDriveName;
		szDriveName.Format(_T("\\\\.\\Scsi%d:"), iController );

// #ifdef _UNICODE
// 		wsprintf( szDriveName, L"\\\\.\\Scsi%d:", iController );
// #else
// 		sprintf( szDriveName, "\\\\.\\Scsi%d:", iController );
// #endif
        //  Try to get a handle to PhysicalDrive IOCTL, report failure
        //  and exit if can't.

        //  Windows NT, Windows 2000, any rights should do
#ifdef _PSX_IDE_QT_
		hScsiDriveIOCTL = CreateFile( (LPCWSTR)szDriveName.GetString(),
			GENERIC_READ | GENERIC_WRITE, 
			FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
			OPEN_EXISTING, 0, NULL);
#else
		hScsiDriveIOCTL = CreateFile( szDriveName,
			GENERIC_READ | GENERIC_WRITE, 
			FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
			OPEN_EXISTING, 0, NULL);
#endif
        
        // if (hScsiDriveIOCTL == INVALID_HANDLE_VALUE)
        //    printf ("Unable to open SCSI controller %d, error code: 0x%lX\n",
        //            controller, GetLastError ());
        
        if( hScsiDriveIOCTL != INVALID_HANDLE_VALUE )
        {
            int iDrive = 0;
            for( iDrive = 0; iDrive < 2; ++ iDrive )
            {
                char szBuffer[sizeof( SRB_IO_CONTROL ) + SENDIDLENGTH] = { 0 };

                SRB_IO_CONTROL* p = ( SRB_IO_CONTROL* )szBuffer;
                SENDCMDINPARAMS* pin = ( SENDCMDINPARAMS* )( szBuffer + sizeof( SRB_IO_CONTROL ) );
                DWORD dwResult;

                p->HeaderLength = sizeof( SRB_IO_CONTROL );
                p->Timeout = 10000;
                p->Length = SENDIDLENGTH;
                p->ControlCode = IOCTL_SCSI_MINIPORT_IDENTIFY;
                strncpy( ( char* )p->Signature, "SCSIDISK", 8 );

                pin->irDriveRegs.bCommandReg = IDE_ATA_IDENTIFY;
                pin->bDriveNumber = iDrive;
                
                if( DeviceIoControl( hScsiDriveIOCTL, IOCTL_SCSI_MINIPORT, 
                    szBuffer,
                    sizeof( SRB_IO_CONTROL ) + sizeof( SENDCMDINPARAMS ) - 1,
                    szBuffer,
                    sizeof( SRB_IO_CONTROL ) + SENDIDLENGTH,
                    &dwResult, NULL ) )
                {
                    SENDCMDOUTPARAMS* pOut = ( SENDCMDOUTPARAMS* )( szBuffer + sizeof( SRB_IO_CONTROL ) );
                    IDSECTOR* pId = ( IDSECTOR* )( pOut->bBuffer );
                    if( pId->sModelNumber[0] )
                    {
                        if( * puSerialLen + 20U <= uMaxSerialLen )
                        {
                            // 序列号
                            CopyMemory( dwSerial + * puSerialLen, ( ( USHORT* )pId ) + 10, 20 );

                            // Cut off the trailing blanks
							UINT i=0;
                            for( i = 20; i != 0U && ' ' == dwSerial[* puSerialLen + i - 1]; -- i )
                            {}
                            * puSerialLen += i;

                            // 型号
                            CopyMemory( dwSerial + * puSerialLen, ( ( USHORT* )pId ) + 27, 40 );
                            // Cut off the trailing blanks
                            for( i = 40; i != 0U && ' ' == dwSerial[* puSerialLen + i - 1]; -- i )
                            {}
                            * puSerialLen += i;

                            bInfoLoaded = TRUE;
                        }
                        else
                        {
                            ::CloseHandle( hScsiDriveIOCTL );
                            return bInfoLoaded;
                        }
                    }
                }
            }
            ::CloseHandle( hScsiDriveIOCTL );
        }
    }
    return bInfoLoaded;
}

BOOL CSystemCode::DoIdentify( HANDLE hPhysicalDriveIOCTL, PSENDCMDINPARAMS pSCIP,
                 PSENDCMDOUTPARAMS pSCOP, BYTE bIDCmd, BYTE bDriveNum,
                 PDWORD lpcbBytesReturned )
{
    // Set up data structures for IDENTIFY command.
    pSCIP->cBufferSize                  = IDENTIFY_BUFFER_SIZE;
    pSCIP->irDriveRegs.bFeaturesReg     = 0;
    pSCIP->irDriveRegs.bSectorCountReg  = 1;
    pSCIP->irDriveRegs.bSectorNumberReg = 1;
    pSCIP->irDriveRegs.bCylLowReg       = 0;
    pSCIP->irDriveRegs.bCylHighReg      = 0;
    
    // calc the drive number.
    pSCIP->irDriveRegs.bDriveHeadReg = 0xA0 | ( ( bDriveNum & 1 ) << 4 );

    // The command can either be IDE identify or ATAPI identify.
    pSCIP->irDriveRegs.bCommandReg = bIDCmd;
    pSCIP->bDriveNumber = bDriveNum;
    pSCIP->cBufferSize = IDENTIFY_BUFFER_SIZE;
    
    return DeviceIoControl( hPhysicalDriveIOCTL, DFP_RECEIVE_DRIVE_DATA,
        ( LPVOID ) pSCIP,
        sizeof( SENDCMDINPARAMS ) - 1,
        ( LPVOID ) pSCOP,
        sizeof( SENDCMDOUTPARAMS ) + IDENTIFY_BUFFER_SIZE - 1,
        lpcbBytesReturned, NULL );
}

BOOL CSystemCode::WinNTHDSerialNumAsPhysicalRead( BYTE* dwSerial, UINT* puSerialLen, UINT uMaxSerialLen )
{
#define  DFP_GET_VERSION          0x00074080
    BOOL bInfoLoaded = FALSE;

    for( UINT uDrive = 0; uDrive < 4; ++ uDrive )
    {
        HANDLE hPhysicalDriveIOCTL = 0;

        //  Try to get a handle to PhysicalDrive IOCTL, report failure
        //  and exit if can't.
        CString szDriveName;
		szDriveName.Format(_T("\\\\.\\PHYSICALDRIVE%d"), uDrive);
// #ifdef _UNICODE
// 		wsprintf( szDriveName, L"\\\\.\\PhysicalDrive%d", uDrive );
// #else
// 		sprintf( szDriveName, "\\\\.\\PhysicalDrive%d", uDrive );
// #endif
        
        //  Windows NT, Windows 2000, must have admin rights
#ifdef _PSX_IDE_QT_
		hPhysicalDriveIOCTL = ::CreateFile( (LPCWSTR)szDriveName.GetString(),
			GENERIC_READ | GENERIC_WRITE, 
			FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
			OPEN_EXISTING, 0, NULL);
#else
		hPhysicalDriveIOCTL = ::CreateFile( szDriveName,
			GENERIC_READ | GENERIC_WRITE, 
			FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
			OPEN_EXISTING, 0, NULL);
#endif

        if( hPhysicalDriveIOCTL != INVALID_HANDLE_VALUE )
        {
            GETVERSIONOUTPARAMS VersionParams = { 0 };
            DWORD               cbBytesReturned = 0;

            // Get the version, etc of PhysicalDrive IOCTL
            if( DeviceIoControl( hPhysicalDriveIOCTL, DFP_GET_VERSION,
                NULL, 
                0,
                &VersionParams,
                sizeof( GETVERSIONOUTPARAMS ),
                &cbBytesReturned, NULL ) )
            {
                // If there is a IDE device at number "i" issue commands
                // to the device
                if( VersionParams.bIDEDeviceMap != 0 )
                {
                    BYTE             bIDCmd = 0;   // IDE or ATAPI IDENTIFY cmd
                    SENDCMDINPARAMS  scip = { 0 };

                    // Now, get the ID sector for all IDE devices in the system.
                    // If the device is ATAPI use the IDE_ATAPI_IDENTIFY command,
                    // otherwise use the IDE_ATA_IDENTIFY command
                    bIDCmd = ( VersionParams.bIDEDeviceMap >> uDrive & 0x10 ) ? IDE_ATAPI_IDENTIFY : IDE_ATA_IDENTIFY;
                    BYTE IdOutCmd[sizeof( SENDCMDOUTPARAMS ) + IDENTIFY_BUFFER_SIZE - 1] = { 0 };

                    if( DoIdentify( hPhysicalDriveIOCTL, 
                        &scip, 
                        ( PSENDCMDOUTPARAMS )&IdOutCmd, 
                        ( BYTE )bIDCmd,
                        ( BYTE )uDrive,
                        &cbBytesReturned ) )
                    {
                        if( * puSerialLen + 20U <= uMaxSerialLen )
                        {
                            CopyMemory( dwSerial + * puSerialLen, ( ( USHORT* )( ( ( PSENDCMDOUTPARAMS )IdOutCmd )->bBuffer ) ) + 10, 20 );  // 序列号

                            // Cut off the trailing blanks
							UINT i=0;
                            for( i = 20; i != 0U && ' ' == dwSerial[* puSerialLen + i - 1]; -- i )  {}
                            * puSerialLen += i;

                            CopyMemory( dwSerial + * puSerialLen, ( ( USHORT* )( ( ( PSENDCMDOUTPARAMS )IdOutCmd )->bBuffer ) ) + 27, 40 ); // 型号

                            // Cut off the trailing blanks
                            for( i = 40; i != 0U && ' ' == dwSerial[* puSerialLen + i - 1]; -- i )  {}
                            * puSerialLen += i;

                            bInfoLoaded = TRUE;
                        }
                        else
                        {
                            ::CloseHandle( hPhysicalDriveIOCTL );
                            return bInfoLoaded;
                        }
                    }
                }
            }
            CloseHandle( hPhysicalDriveIOCTL );
        }
    }
    return bInfoLoaded;
}

// 硬盘序列号，注意：有的硬盘没有序列号
BOOL CSystemCode::GetHardDiscCode()
{
	OSVERSIONINFO ovi = { 0 };
	ovi.dwOSVersionInfoSize = sizeof( OSVERSIONINFO );
	GetVersionEx( &ovi );

	uSystemInfoLen = 0;
	m_nSysInfoCount = 0;
	
	if( ovi.dwPlatformId != VER_PLATFORM_WIN32_NT )
	{
		// Only Windows 2000, Windows XP, Windows Server 2003...
		return FALSE;
	}
	else
	{
		if( !WinNTHDSerialNumAsPhysicalRead( szSystemInfo, &uSystemInfoLen, 1024 ) )
		{
			WinNTHDSerialNumAsScsiRead( szSystemInfo, &uSystemInfoLen, 1024 );
		}
	}

	return TRUE;
}

    // CPU ID
void CSystemCode::GetCPUCode()
{
	BOOL bException = FALSE;
	BYTE szCpu[16]  = { 0 };
	UINT uCpuID     = 0U;

	uSystemInfoLen = 0;
	m_nSysInfoCount = 0;
	
	__try 
	{
		_asm 
		{
			mov eax, 0
                cpuid
                mov dword ptr szCpu[0], ebx
                mov dword ptr szCpu[4], edx
                mov dword ptr szCpu[8], ecx
                mov eax, 1
                cpuid
                mov uCpuID, edx
		}
	}
	__except( EXCEPTION_EXECUTE_HANDLER )
	{
		bException = TRUE;
	}
	
	if( !bException )
	{
		CopyMemory( szSystemInfo + uSystemInfoLen, &uCpuID, sizeof( UINT ) );
		uSystemInfoLen += sizeof( UINT );
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CpuID:%08X"), uCpuID);
		
		uCpuID = strlen( ( char* )szCpu );
		CopyMemory( szSystemInfo + uSystemInfoLen, szCpu, uCpuID );
		uSystemInfoLen += uCpuID;
		m_strCpu = ( char* )szCpu;
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CpuSN:%s"), m_strCpu);
	}
}

void CSystemCode::GetMacCode()
{
	uSystemInfoLen = 0;
	m_nSysInfoCount = 0;

	PIP_ADAPTER_INFO pAdapterInfo;
	PIP_ADAPTER_INFO pAdapter=NULL;
	DWORD dwRetVal=0;
	pAdapterInfo=(IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
	ULONG ulOutBufLen=sizeof(IP_ADAPTER_INFO);
	ZeroMemory(pAdapterInfo, ulOutBufLen);
	
	if(GetAdaptersInfo(pAdapterInfo,&ulOutBufLen)!=ERROR_SUCCESS)
	{
		free(pAdapterInfo);
		pAdapterInfo=(IP_ADAPTER_INFO*)malloc(ulOutBufLen);
	}

	if((dwRetVal=GetAdaptersInfo(pAdapterInfo,&ulOutBufLen))==NO_ERROR)
	{
		pAdapter=pAdapterInfo;
		while(pAdapter)
		{
			if(	pAdapter->Type == MIB_IF_TYPE_ETHERNET)
			{
				CopyMemory( szSystemInfo + uSystemInfoLen, pAdapter->Address, pAdapter->AddressLength );
				uSystemInfoLen += pAdapter->AddressLength;

				m_nSysInfoCount++;
				CString strMac;
				for (long nIndex=0; nIndex<pAdapter->AddressLength; nIndex++)
				{
					strMac.AppendFormat(_T("%02X-"), pAdapter->Address[nIndex]);
				}

				strMac = strMac.Left(strMac.GetLength()-1);
				//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("MAC:%s"), strMac);
			}

			pAdapter=pAdapter->Next;
		}
	}
	
	free(pAdapterInfo);
}

