//---------------------------------------------------------------------------
//
// File:         osillc95.c
//
// Copyright (c) 1998 - 2002, SISCO, Inc. All rights reserved.
//
// Description:  Driver entry routines.
//
// Author:       A. Shajenko/Stratos Technology, Inc.
//
// History:
// 13-Sep-98     A. Shajenko     Implemented.
// 01-Jan-02     SISCO (EJV)     Added support for cfg of LSAPs in registry
// 18-Nov-02     SISCO (EJV)     Added support for Ethertype filtering.
//
//---------------------------------------------------------------------------

#include "osillc95.h"

//
// Global Data	
//
PDEVICE_EXTENSION	g_DeviceExtension = NULL;
BOOL				g_fInitialized = FALSE;
HANDLE				g_hSystemVM = NULL;
DWORD				g_DebugLevel = OSILLC_DEFAULT_DEBUG_LEVEL;

//
// Local functions
//
BOOL OsillcGetConfiguration(void);
VOID NDIS_API OsillcUnload();
POPEN_INSTANCE OsillcGetOpenInstance(DWORD hDevice, DWORD dwProcessId);
DWORD OsillcGetMacName(POPEN_INSTANCE pOpen, PIOCTLPARAMS p);
DWORD OsillcGetStats(POPEN_INSTANCE pOpen, PIOCTLPARAMS p);


//
// Standard VxD Declarations
//

Declare_Virtual_Device(OSILLC98)

DefineControlHandler(DEVICE_INIT, OnDeviceInit);
DefineControlHandler(SYS_DYNAMIC_DEVICE_INIT, OnSysDynamicDeviceInit);
DefineControlHandler(SYS_DYNAMIC_DEVICE_EXIT, OnSysDynamicDeviceExit);
DefineControlHandler(W32_DEVICEIOCONTROL, OnW32Deviceiocontrol);


//---------------------------------------------------------------------------
// Function:    ControlDispatcher
//
// Parameters:  DWORD dwControlMessage -- control messade id
//              DWORD EBX
//              DWORD EDX
//              DWORD ESI
//              DWORD EDI
//              DWORD ECX
//
// Returns:     TRUE if successful.
//
// Description: Main VxD Control Message Dispatcher.
//
// Notes:       
//
//---------------------------------------------------------------------------
BOOL __cdecl ControlDispatcher(DWORD dwControlMessage, DWORD EBX, DWORD EDX,
							   DWORD ESI, DWORD EDI, DWORD ECX)
{
	START_CONTROL_DISPATCH

		ON_DEVICE_INIT(OnDeviceInit);
		ON_SYS_DYNAMIC_DEVICE_INIT(OnSysDynamicDeviceInit);
		ON_SYS_DYNAMIC_DEVICE_EXIT(OnSysDynamicDeviceExit);
		ON_W32_DEVICEIOCONTROL(OnW32Deviceiocontrol);

	END_CONTROL_DISPATCH

	return TRUE;
}

//---------------------------------------------------------------------------
// Function:    OnSysDynamicDeviceInit
//
// Parameters:  None
//
// Returns:     TRUE if successful.
//
// Description: Called when VxD is first loaded.
//
// Notes:       
//
//---------------------------------------------------------------------------
BOOL OnSysDynamicDeviceInit(void)
{
	DWORD dwVMM_Version, dwDebugRev;

	SETDEBUGLEVEL(DBG_NONE, DBG_ERROR);
	DEBUGTRACE0("OnSysDynamicDeviceInit Entry...");

	// get the version of the Win9X OS
	dwVMM_Version = Get_VMM_Version(&dwDebugRev);

	// get the System VM handle
	g_hSystemVM = Get_Sys_VM_Handle();

	return (DriverEntry(NULL, NULL) == NDIS_STATUS_SUCCESS);
}

//---------------------------------------------------------------------------
// Function:    OnSysDynamicDeviceExit
//
// Parameters:  None
//
// Returns:     TRUE if successful.
//
// Description: Called when the VxD is being unloaded.
//
// Notes:       
//
//---------------------------------------------------------------------------
BOOL OnSysDynamicDeviceExit(void)
{
	DEBUGTRACE0("OnSysDynamicDeviceExit Entry...");

	if (g_DeviceExtension)
	{
		NDIS_STATUS Status;

		// unregister our protocol driver
		NdisDeregisterProtocol(&Status, g_DeviceExtension->NdisProtocolHandle);

		DEBUGTRACE1("OnSysDynamicDeviceExit: NdisDeregisterProtocol: status %x", Status);

        if (Status == NDIS_STATUS_SUCCESS)
		{
            NdisFreeMemory(g_DeviceExtension, sizeof(DEVICE_EXTENSION), 0);
			g_DeviceExtension = NULL;
		}
        g_fInitialized = FALSE;
    }

	return TRUE;
}

//---------------------------------------------------------------------------
// Function:    OsillcUnload
//
// Parameters:  None
//
// Returns:     Nothing
//
// Description: Called when driver unbinds from the last MAC.
//
// Notes:       We should not do anything special here.
//
//---------------------------------------------------------------------------
VOID NDIS_API OsillcUnload()
{
	DEBUGTRACE0("OsillcUnload: entry...");

}

//---------------------------------------------------------------------------
// Function:    DriverEntry
//
// Parameters:  PDRIVER_OBJECT DriverObject  -- pointer to driver object
//              PUNICODE_STRING RegistryPath -- pointer to Registry path
//
// Returns:     NTSTATUS
//
// Description: Initializes the OISLLC95 driver.
//
// Notes:       Both paramters are NULL in Win9X.
//
//---------------------------------------------------------------------------
NTSTATUS NDIS_API
DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
    NDIS_PROTOCOL_CHARACTERISTICS ProtocolChar;
    NDIS_STRING ProtoName = NDIS_STRING_CONST("OSILLC98");
    NDIS_STATUS Status;

	// we must ensure that initialization is performed only once.
    if (g_fInitialized)
        return NDIS_STATUS_SUCCESS;
        
    NdisAllocateMemory((PVOID *)&g_DeviceExtension, sizeof(DEVICE_EXTENSION), 0, -1 );
    if (g_DeviceExtension == NULL)
	{
		DEBUGERROR0("DriverEntry: ERROR: no resources");
		return NDIS_STATUS_RESOURCES;
    }

	NdisZeroMemory((PUCHAR)g_DeviceExtension, sizeof(DEVICE_EXTENSION));
	NdisZeroMemory((PUCHAR)&ProtocolChar, sizeof(NDIS_PROTOCOL_CHARACTERISTICS));

	ProtocolChar.MajorNdisVersion            = OSILLC98_NDIS_MAJOR_VERSION;
	ProtocolChar.MinorNdisVersion            = OSILLC98_NDIS_MINOR_VERSION;
	ProtocolChar.Reserved                    = 0;
	ProtocolChar.OpenAdapterCompleteHandler  = OsillcOpenAdapterComplete;
	ProtocolChar.CloseAdapterCompleteHandler = OsillcCloseAdapterComplete;
	ProtocolChar.SendCompleteHandler         = OsillcSendComplete;
	ProtocolChar.TransferDataCompleteHandler = OsillcTransferDataComplete;
	ProtocolChar.ResetCompleteHandler        = OsillcResetComplete;
	ProtocolChar.RequestCompleteHandler      = OsillcRequestComplete;
	ProtocolChar.ReceiveHandler              = OsillcReceiveIndicate;
	ProtocolChar.ReceiveCompleteHandler      = OsillcReceiveComplete;
	ProtocolChar.StatusHandler               = OsillcStatus;
	ProtocolChar.StatusCompleteHandler       = OsillcStatusComplete;
	ProtocolChar.BindAdapterHandler          = NULL;
	ProtocolChar.UnbindAdapterHandler        = NULL;
	ProtocolChar.UnloadProtocolHandler       = OsillcUnload;
	ProtocolChar.Name                        = ProtoName;

	NdisRegisterProtocol(&Status, &g_DeviceExtension->NdisProtocolHandle,
						 &ProtocolChar, sizeof(NDIS_PROTOCOL_CHARACTERISTICS));

    if (Status != NDIS_STATUS_SUCCESS)
	{
        NdisFreeMemory(g_DeviceExtension, sizeof(DEVICE_EXTENSION), 0);
		DEBUGERROR1("NdisRegisterProtocol failed with code 0x%X", Status);
        return Status;
    }

	DEBUGTRACE0("NdisRegisterProtocol succeeded");

	// initialize global device extension
	g_DeviceExtension->DriverObject = DriverObject;
	g_DeviceExtension->dwNumberBuffers = OSILLC_DEFAULT_MAX_BUFFERS;
	g_DeviceExtension->dwNumberFrames = OSILLC_DEFAULT_MAX_FRAMES;

	// initialize open list
	InitializeListHead(&g_DeviceExtension->OpenList);

	// get the configuration from the Registry
	OsillcGetConfiguration();

	g_fInitialized = TRUE;

	return Status;
}

//#include PAGEABLE_CODE_SEGMENT

//---------------------------------------------------------------------------
// Function:    OsillcGetConfiguration
//
// Parameters:  None
//
// Returns:     TRUE if it could open the Registry key.
//
// Description: Gets the configuration for this driver from the Registry.
//
// Notes:       
//
//---------------------------------------------------------------------------
BOOL OsillcGetConfiguration(void)
{
	PBYTE	RegistryKeyPath = "Software\\SISCO\\Osillc";
	DWORD	dwResult, dwValueType, dwValueSize, dwValue;
	CHAR	szEntryName[128];
	HKEY	hKey;

	DEBUGTRACE0("OsillcGetConfiguration:  entry...");

	// open the Registry key
	dwResult = RegOpenKey(HKEY_LOCAL_MACHINE, RegistryKeyPath, &hKey);
	if (dwResult != ERROR_SUCCESS)
	{
		DEBUGERROR2("OsillcGetConfiguration: RegOpenKey failed for \"%s\": %x", 
					RegistryKeyPath, dwResult);
		return FALSE;
	}

	// all values are REG_DWORD
	dwValueType = REG_DWORD;
	dwValueSize = sizeof(DWORD);

	strcpy(szEntryName, "NumBufferDesc");
	dwResult = RegQueryValueEx(hKey, szEntryName, NULL, &dwValueType, (PBYTE)&dwValue, &dwValueSize);
	if (dwResult == ERROR_SUCCESS)
	{
		g_DeviceExtension->dwNumberBuffers = dwValue;
	}
	else
	{
		DEBUGERROR2("OsillcGetConfiguration: RegQueryValueEx failed for \"%s\": %x", 
					szEntryName, dwResult);
	}

	strcpy(szEntryName, "NumFrames");
	dwResult = RegQueryValueEx(hKey, szEntryName, NULL, &dwValueType, (PBYTE)&dwValue, &dwValueSize);
	if (dwResult == ERROR_SUCCESS)
	{
		g_DeviceExtension->dwNumberFrames = dwValue;
	}
	else
	{
		DEBUGERROR2("OsillcGetConfiguration: RegQueryValueEx failed for \"%s\": %x", 
					szEntryName, dwResult);
	}

	g_DebugLevel = OSILLC_DEFAULT_DEBUG_LEVEL;
	strcpy(szEntryName, "DebugLevel");
	dwResult = RegQueryValueEx(hKey, szEntryName, NULL, &dwValueType, (PBYTE)&dwValue, &dwValueSize);
	if (dwResult == ERROR_SUCCESS)
	{
		g_DebugLevel = dwValue;
	}
	else
	{
		DEBUGERROR2("OsillcGetConfiguration: RegQueryValueEx failed for \"%s\": %x", 
					szEntryName, dwResult);
	}

	strcpy(szEntryName, "LSAPs");
        dwValueSize = sizeof (g_DeviceExtension->LsapTable);
	dwResult = RegQueryValueEx(hKey, szEntryName, NULL, &dwValueType, (PBYTE)&g_DeviceExtension->LsapTable, &dwValueSize);
	if (dwResult == ERROR_SUCCESS)
        {
		g_DeviceExtension->LsapCount = dwValueSize;	// num of LSAPs
        }
        else
        {
         	if (dwResult == ERROR_MORE_DATA)
                {
		DEBUGERROR2("OsillcGetConfiguration: RegQueryValueEx failed for \"%s\": %x (buffer too small)", 
					szEntryName, dwResult);
                }
                else
                {
		DEBUGERROR2("OsillcGetConfiguration: RegQueryValueEx failed for \"%s\": %x", 
					szEntryName, dwResult);
                }
	}
        // if LSAPs table empty default to filter OSI frames
	if (g_DeviceExtension->LsapCount == 0)
	{
		g_DeviceExtension->LsapTable[0] = 0xFE;	/* OSI frames */
		g_DeviceExtension->LsapCount = 1;
	}
#if DEBUG
	if (g_DebugLevel > 1)
	  {
	  UINT	i;
	  CHAR	lsapBuf[3*MAX_LSAPS+1];
	  CHAR	lsapTmp[4];
		
	  lsapBuf[0] = 0;                
	  for (i=0; i<g_DeviceExtension->LsapCount; ++i)
	    {
	    sprintf (lsapTmp,"%2.2X ", g_DeviceExtension->LsapTable[i]);
	    strcat (lsapBuf, lsapTmp);
	    }
	  DEBUGTRACE2("OsillcGetConfiguration: Filtering on %d LSAPs: %s",
                      g_DeviceExtension->LsapCount, lsapBuf);
	  }
#endif  // DEBUG

        strcpy(szEntryName, "EthertypeIDs");
        dwValueSize = sizeof (g_DeviceExtension->EthertypeIdsTable);
        dwResult = RegQueryValueEx(hKey, szEntryName, NULL, &dwValueType, (PBYTE)&g_DeviceExtension->EthertypeIdsTable, &dwValueSize);
        if (dwResult == ERROR_SUCCESS)
        {
		g_DeviceExtension->EthertypeIdsCount = dwValueSize/2;	// num of Ethertype IDs
        }
        else
        {
		g_DeviceExtension->EthertypeIdsCount = 0;	// num of Ethertype IDs
         	if (dwResult == ERROR_MORE_DATA)
                {
		DEBUGERROR2("OsillcGetConfiguration: RegQueryValueEx failed for \"%s\": %x (buffer too small)", 
					szEntryName, dwResult);
                }
                else
                {
		DEBUGERROR2("OsillcGetConfiguration: RegQueryValueEx failed for \"%s\": %x", 
					szEntryName, dwResult);
                }
	}

	RegCloseKey(hKey);

	switch (g_DebugLevel)
	{
	case 0:
		SETDEBUGLEVEL(DBG_NONE, DBG_NONE);
		break;

	case 1:
		SETDEBUGLEVEL(DBG_NONE, DBG_ERROR);
		break;

	case 2:
		SETDEBUGLEVEL(DBG_NONE, DBG_TRACE);
		break;

	default:
		SETDEBUGLEVEL(DBG_NONE, DBG_ERROR);
		break;
	}

	return TRUE;
}

//---------------------------------------------------------------------------
// Function:    OsillcGetOpenInstance
//
// Parameters:  DWORD hDevice     -- deive open handle (specific to process)
//              DWORD dwProcessId -- Win32 process id
//
// Returns:     POPEN_INSTANCE pOpen -- pointer to open object if found,
//                                      NULL if not found
//
// Description: Finds a specified Open Instance object from list.
//
// Notes:       
//
//---------------------------------------------------------------------------
POPEN_INSTANCE OsillcGetOpenInstance(DWORD hDevice, DWORD dwProcessId)
{
	PLIST_ENTRY     pHead = &(g_DeviceExtension->OpenList);
	PLIST_ENTRY     pListEntry;
	POPEN_INSTANCE  pOpen;

	if ( !g_DeviceExtension)
	{
        DEBUGERROR0("OsillcGetOpenInstance: g_DeviceExtension is NULL");
        return (POPEN_INSTANCE)NULL;
    }
    
    // search the list for the Open Instance containing the specified handle
	_disable();
    for (pListEntry = pHead->Flink; pListEntry != pHead; pListEntry = pListEntry->Flink)
	{
        pOpen = CONTAINING_RECORD(pListEntry, OPEN_INSTANCE, ListEntry);        
        if (pOpen) 
		{
            if (pOpen->hDevice == hDevice && pOpen->dwProcessId == dwProcessId)
			{
				_enable();
				DEBUGTRACE1("OsillcGetOpenInstance: open instance found: %x", pOpen);
                return pOpen;
			}
		}
    }
	_enable();

	DEBUGERROR0("OsillcGetOpenInstance: returning NULL");

	return (POPEN_INSTANCE)NULL;
}

//---------------------------------------------------------------------------
// Function:    OsillcGetMacName
//
// Parameters:  POPEN_INSTANCE pOpen -- pointer to open instance
//              PIOCTLPARAMS p       -- pointer to IOCTL request block
//
// Returns:     Return code.
//
// Description: Returns MAC name.
//
// Notes:
//
//---------------------------------------------------------------------------
DWORD OsillcGetMacName(POPEN_INSTANCE pOpen, PIOCTLPARAMS p) 
{
    PWRAPPER_MAC_BLOCK	pWMBlock;
    DWORD   dwBytes = 0;
    BYTE    *lpzName;
    ULONG   uLength;

	if (p->dioc_OutBuf == NULL)
	{
        *p->dioc_bytesret = 0;
		return ERROR_INSUFFICIENT_BUFFER;
	}

	pWMBlock = ((PWRAPPER_OPEN_BLOCK)(pOpen->AdapterHandle))->MacHandle;
	lpzName  = pWMBlock->AdapterQueue->nsMacName.Buffer;
	uLength  = strlen(lpzName);
    
	// check that the ouput buffer is big enough
    if (uLength < p->dioc_cbOutBuf - 1)
	{
        strcpy((BYTE *)p->dioc_OutBuf, lpzName);
        *p->dioc_bytesret = uLength + 1;
		return ERROR_SUCCESS;
    }
	else
	{
        *p->dioc_bytesret = 0;
		return ERROR_INSUFFICIENT_BUFFER;
	}
}

//---------------------------------------------------------------------------
// Function:    OsillcGetStats
//
// Parameters:  POPEN_INSTANCE pOpen -- pointer to open instance
//              PIOCTLPARAMS p       -- pointer to IOCTL request block
//
// Returns:     Return code.
//
// Description: Returns binding statistics.
//
// Notes:
//
//---------------------------------------------------------------------------
DWORD OsillcGetStats(POPEN_INSTANCE pOpen, PIOCTLPARAMS p) 
{
	if (p->dioc_OutBuf == NULL || p->dioc_cbOutBuf < sizeof(OSILLC_GET_STATS))
	{
        *p->dioc_bytesret = 0;
		return ERROR_INSUFFICIENT_BUFFER;
	}

	NdisMoveMemory(p->dioc_OutBuf, &pOpen->Stats, sizeof(OSILLC_GET_STATS));
	*p->dioc_bytesret = sizeof(OSILLC_GET_STATS);

	return ERROR_SUCCESS;
}

//---------------------------------------------------------------------------
// Function:    OnW32Deviceiocontrol
//
// Parameters:  PIOCTLPARAMS p -- pointer to IOCTL request block
//
// Returns:     Return code.
//
// Description: Process Win32 IOCTL requests.
//
// Notes:
//
//---------------------------------------------------------------------------
DWORD OnW32Deviceiocontrol(PIOCTLPARAMS p) 
{
	POPEN_INSTANCE  pOpen;
	NDIS_STATUS     Status;
	DWORD			dwErrorCode = ERROR_CONNECTION_INVALID;

    // set the number of return bytes.
    *p->dioc_bytesret = 0;

	switch (p->dioc_IOCtlCode)
    {
    case DIOC_OPEN:
		dwErrorCode = DEVIOCTL_NOERROR;
        break;

	case DIOC_CLOSEHANDLE:
		// get the open instance object
		pOpen = OsillcGetOpenInstance(p->dioc_hDevice, p->dioc_ppdb);
		if (pOpen)
		{
			// if we're still bound to a MAC, unbind from it
			if (pOpen->bBound)
			{
				pOpen->bClosing = TRUE;
				dwErrorCode = OsillcCloseAdapter(pOpen, p);
			}
			else
			{
				// free the IRP pool
				OsillcFreeIrpPool(&pOpen->IrpPool);

				// now remove it from the global open list and delete it
				_disable();
				RemoveEntryList(&pOpen->ListEntry);
				_enable();
				NdisFreeMemory((PVOID)pOpen, sizeof(OPEN_INSTANCE), 0);
			}
		
			--g_DeviceExtension->dwOpenCount;
		}
		dwErrorCode = DEVIOCTL_NOERROR;
		break;

    case IOCTL_OSILLC_BIND:
		// get the open instance object
		pOpen = OsillcGetOpenInstance(p->dioc_hDevice, p->dioc_ppdb);
		if (pOpen && pOpen->bBound)
		{
			dwErrorCode = ERROR_CONNECTION_ACTIVE;
		}
		else
		{
			dwErrorCode = OsillcOpenAdapter(pOpen, p);
		}
		break;

    case IOCTL_OSILLC_UNBIND:
		pOpen = OsillcGetOpenInstance(p->dioc_hDevice, p->dioc_ppdb);
        if (pOpen && pOpen->bBound)
		{
			pOpen->bClosing = FALSE;
			dwErrorCode = OsillcCloseAdapter(pOpen, p);
		}
		else
		{
			dwErrorCode = ERROR_CONNECTION_INVALID;
		}
        break;
    
    case IOCTL_OSILLC_RESET:
		pOpen = OsillcGetOpenInstance(p->dioc_hDevice, p->dioc_ppdb);
        if (pOpen && pOpen->bBound)
		{
            OsillcReset(&Status, pOpen);
			dwErrorCode = Status;
		}
		else
		{
			dwErrorCode = ERROR_CONNECTION_INVALID;
		}
        break;

    case IOCTL_OSILLC_SET_OID:
    case IOCTL_OSILLC_QUERY_OID:
		pOpen = OsillcGetOpenInstance(p->dioc_hDevice, p->dioc_ppdb);
        if (pOpen && pOpen->bBound)
		{
			dwErrorCode = OsillcRequest(pOpen, p);
		}
		else
		{
			dwErrorCode = ERROR_CONNECTION_INVALID;
		}
        break;

    case IOCTL_OSILLC_READ:
		pOpen = OsillcGetOpenInstance(p->dioc_hDevice, p->dioc_ppdb);
        if (pOpen && pOpen->bBound)
		{
			dwErrorCode = OsillcRead(pOpen, p);
		}
		else
		{
			dwErrorCode = ERROR_CONNECTION_INVALID;
		}
        break;

    case IOCTL_OSILLC_WRITE:
		pOpen = OsillcGetOpenInstance(p->dioc_hDevice, p->dioc_ppdb);
        if (pOpen && pOpen->bBound)
		{
			dwErrorCode = OsillcWrite(pOpen, p);
		}
		else
		{
			dwErrorCode = ERROR_CONNECTION_INVALID;
		}
        break;

    case IOCTL_OSILLC_GET_MACNAME:
		pOpen = OsillcGetOpenInstance(p->dioc_hDevice, p->dioc_ppdb);
        if (pOpen && pOpen->bBound)
		{
			dwErrorCode = OsillcGetMacName(pOpen, p);
		}
		else
		{
			dwErrorCode = ERROR_CONNECTION_INVALID;
		}
        break;
  
    case IOCTL_OSILLC_GET_STATS:
		pOpen = OsillcGetOpenInstance(p->dioc_hDevice, p->dioc_ppdb);
        if (pOpen)
            dwErrorCode = OsillcGetStats(pOpen, p);
		else
		{
			dwErrorCode = ERROR_CONNECTION_INVALID;
		}
		break;

    default: 
		DEBUGERROR1("OsillcIoControl: ERROR: unknown DIOC %x", p->dioc_IOCtlCode); 
		dwErrorCode = ERROR_INVALID_FUNCTION;
		break;
	}

    return dwErrorCode;
}

//---------------------------------------------------------------------------
// Function:    OsillcStatus
//
// Parameters:  NDIS_HANDLE ProtocolBindingContext -- pointer to binding context
//              NDIS_STATUS Status                 -- status from MAC
//              PVOID StatusBuffer                 -- status data from MAC
//              UINT StatusBufferSize              -- size of status data
//
// Returns:     Nothing.
//
// Description: Processes MAC status indications.
//
// Notes:
//
//---------------------------------------------------------------------------
VOID NDIS_API OsillcStatus(NDIS_HANDLE ProtocolBindingContext, NDIS_STATUS Status,
						   PVOID StatusBuffer, UINT StatusBufferSize)
{
	POPEN_INSTANCE   pOpen = (POPEN_INSTANCE)ProtocolBindingContext;

	DEBUGTRACE1("OsillcStatus: %x", Status);
}

//---------------------------------------------------------------------------
// Function:    OsillcStatusComplete
//
// Parameters:  NDIS_HANDLE ProtocolBindingContext -- pointer to binding context
//
// Returns:     Nothing.
//
// Description: Processes MAC status indication completion.
//
// Notes:
//
//---------------------------------------------------------------------------
VOID NDIS_API OsillcStatusComplete(NDIS_HANDLE ProtocolBindingContext)
{
	POPEN_INSTANCE   pOpen = (POPEN_INSTANCE)ProtocolBindingContext;
	return;
}

//---------------------------------------------------------------------------
// Function:    OsillcTimeoutHandler
//
// Parameters:  PVOID Context -- context used as unique id
//              DWORD dwExtra -- ignored
//
// Returns:     Nothing
//
// Description: Unblocks a Ring3 caller thread.
//
// Notes:       
//
//---------------------------------------------------------------------------
VOID __stdcall OsillcTimeoutHandler(PVOID Context, DWORD dwExtra)
{
	SignalID((DWORD)Context);
}

//---------------------------------------------------------------------------
// Function:    OsillcDelay
//
// Parameters:  POPEN_INSTANCE pOpen -- pointer to open object
//              DWORD dwMillisecs    -- number of milliseconds to delay
//
// Returns:     Nothing
//
// Description: Delay for a number of milliseconds.
//
// Notes:       This is accurate only to +/- 15msecs at best.
//
//              This functions cannot be called from interrupt processing.
//
//---------------------------------------------------------------------------
VOID OsillcDelay(POPEN_INSTANCE pOpen, DWORD dwMillisecs)
{
    ASYNCTIMEOUT_THUNK TimeoutThunk;

	//now wait for the requested time.(alertable)
	if (Set_Async_Time_Out(dwMillisecs, (PVOID)pOpen, OsillcTimeoutHandler, &TimeoutThunk))
	{
		BlockOnID((DWORD)pOpen, BLOCK_ENABLE_INTS | BLOCK_SVC_INTS | BLOCK_THREAD_IDLE);
	}
}

#include INIT_CODE_SEGMENT

//---------------------------------------------------------------------------
// Function:    OnDeviceInit
//
// Parameters:  None
//
// Returns:     TRUE if successful.
//
// Description: This function is called when VxD is statically loaded.
//
// Notes:       This function should not be called in Win9X!
//
//---------------------------------------------------------------------------
BOOL OnDeviceInit(VMHANDLE hVM, PCHAR CommandTail)
{
	SETDEBUGLEVEL( DBG_NONE, DBG_ERROR );

	DEBUGTRACE0("OnDeviceInit Entry...");

	return (DriverEntry(NULL, NULL) == NDIS_STATUS_SUCCESS);
}

