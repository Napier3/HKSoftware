/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,       */
/*              1996 - 2002, All Rights Reserved                        */
/*                                                                      */
/* MODULE NAME : osillc.c                                               */
/* PRODUCT(S)  : OSI LLC NDIS 3.0 Device Driver for NT                  */
/*                                                                      */
/* MODULE DESCRIPTION :                                                 */
/*                                                                      */
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :                            */
/*                                                                      */
/* MODIFICATION LOG :                                                   */
/*  Date     Who   Rev                  Comments                        */
/* --------  ---  ------   -------------------------------------------  */
/* 01/28/05  JRB    16     Del default 0xFE entry from OsillcLsapTable.	*/
/*			   Must have Registry entry to filter on LSAPs.	*/
/* 11/15/02  EJV    15     Added support for Ethertype filtering.	*/
/* 10/21/02  EJV    14     Use NDIS50 - port for XP,should be OK on 2000*/
/* 01/15/02  EJV    13     Added support to cfg LSAPs in registry:	*/
/*			      See OsillcLsapTable, OsillcLsapCount.	*/
/* 08/21/00  DSF    12     Minor cleanup				*/
/* 04/01/99  DSF    11     Commonized Win98/WinNT include files		*/
/* 01/28/99  DSF    10     Spelling					*/
/* 05/18/98  DSF    09     Added ReceptionMode				*/
/* 05/13/98  DSF    08     Added ReadPackets parameter			*/
/* 05/11/98  DSF    07     File reformatted				*/
/* 06/19/97  DSF    05     Added Stats                                  */
/* 09/10/96  DSF    04     Allowed to set a multicast list              */
/* 08/06/96  DSF    03     Added WriteErrorLogEntry support             */
/* 07/16/96  DSF    02     Fixed DEBUGERROR1 Macros                     */
/* 05/22/96  DSF    01     Initial Release                              */
/*                                                                      */
/************************************************************************/

#include "stdarg.h"
#include "ntddk.h"
#include "ntiologc.h"
#include "ndis.h"

#include "debug.h"
#include "osillcnt.h"

#include "osillc.h"

ULONG NdisXmitOk;
ULONG NdisRcvOk;
ULONG NdisXmitError;
ULONG NdisRcvError;
ULONG NdisRcvUnknown;
ULONG NdisXmitInd;
ULONG NdisRcvInd;
ULONG NdisAllocError;

static UINT bGetStatsInProg;

NTSTATUS DriverEntry(
  IN PDRIVER_OBJECT DriverObject,
  IN PUNICODE_STRING RegistryPath
  );

#if defined(NDIS50)
VOID OsillcBindAdapter(
    OUT PNDIS_STATUS Status,
    IN NDIS_HANDLE  BindContext,
    IN PNDIS_STRING  DeviceName,
    IN PVOID  SystemSpecific1,
    IN PVOID  SystemSpecific2
    );

VOID OsillcUnbindAdapter(
    OUT PNDIS_STATUS  Status,
    IN NDIS_HANDLE  ProtocolBindingContext,
    IN NDIS_HANDLE  UnbindContext
    );
#endif /* defined(NDIS50) */

VOID OsillcCancel(
  IN PDEVICE_OBJECT DeviceObject, 
  IN PIRP Irp
  );

VOID IoctlGetPhysAddr(PIRP              Irp,
  PNDIS_REQUEST    pRequest
  );

VOID IoctlSetMulti(
  PIRP                Irp,
  PNDIS_REQUEST       pRequest
  );

VOID IoctlSetFilter(
  PIRP               Irp,
  PNDIS_REQUEST      pRequest
  );

VOID IoctlGetStats(PIRP Irp);

NTSTATUS OsillcReadRegistry(
  IN  PWSTR              *MacDriverName,
  IN  PWSTR              *OsillcDriverName,
  IN  PUNICODE_STRING     RegistryPath
  );


NTSTATUS OsillcCreateSymbolicLink(
  IN  PUNICODE_STRING  DeviceName,
  IN  UINT             DeviceNumber,
  IN  BOOLEAN          Create
  );

NTSTATUS OsillcQueryRegistryRoutine(
  IN PWSTR     ValueName,
  IN ULONG     ValueType,
  IN PVOID     ValueData,
  IN ULONG     ValueLength,
  IN PVOID     Context,
  IN PVOID     EntryContext
  );


ULONG OsillcDebugFlag = 1;
CCHAR OsillcPriorityBoost = DEFAULT_PRIORITY_BOOST;
ULONG OsillcReceptionMode = RECEPTION_MODE_SAFE;
ULONG OsillcReadPackets = DEFAULT_READ_PACKETS;
ULONG OsillcTransmitPackets = DEFAULT_TRANSMIT_PACKETS;
ULONG OsillcReceivePackets = DEFAULT_RECEIVE_PACKETS;
UCHAR OsillcLsapTable[MAX_LSAPS];	// table of LSAPs to filter on
UINT  OsillcLsapCount=0;		// num of LSAPs in table
                                                        // must be one more than max number of entries
UCHAR OsillcEthertypeIdsTable[2*(MAX_ETHERTYPE_IDS+1)];	// table of Ethertype IDs to filter on
UINT  OsillcEthertypeIdsCount=0;			// num of Ethertype 2-byte IDs in table
ULONG ErrorCodes[10];

/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject,
 *                                  PUNICODE_STRING RegistryPath)
 *
 *  PURPOSE:   This function is called by OS to initialize the driver.
 *
 *  PARMS:     PDRIVER_OBJECT DriverObject - pointer to driver object
 *             PUNICODE_STRING RegistryPath - driver's Registry path & subkey
 *
 *  RETURNS:   NTSTATUS. 
 *
 *  NOTES:
 *
-*/
/* ---------------------------------------------------------------------*/

NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
  {
  UNICODE_STRING                          ParsedRegPath;
  RTL_QUERY_REGISTRY_TABLE        paramTable[10];  // must be one more than number of entries
  UNICODE_STRING                          ParamString;

  NDIS_PROTOCOL_CHARACTERISTICS  ProtocolChar;

  UNICODE_STRING MacDriverName;
  UNICODE_STRING UnicodeDeviceName;

  PDEVICE_OBJECT DeviceObject = NULL;
  PDEVICE_EXTENSION DeviceExtension = NULL;

  NTSTATUS Status = STATUS_SUCCESS;
  NTSTATUS ErrorCode = STATUS_SUCCESS;
#if defined(NDIS50)
  NDIS_STRING ProtoName = NDIS_STRING_CONST("OSILLC");
  /* DEBUG Note: If the ProtoName does not matches the driver's name	*/
  /* installed through the Network Control Panel Applet (NCPA) then the	*/
  /* bind function is not called on Win XP. On Win 2000 this rule is	*/
  /* not enforced too strictly. So to make the behavior the same on 	*/
  /* Win 2000 and XP we make the names the same!.			*/
#else
  NDIS_STRING ProtoName = NDIS_STRING_CONST("OsillcDriver");
#endif

  ULONG          DevicesCreated = 0;

  PWSTR          BindString;
  PWSTR          BindStringSave;
  PWSTR          ExportString;
  PWSTR          ExportStringSave;

  NDIS_HANDLE    NdisProtocolHandle;
  ULONG          dwPriorityBoost;
  UINT		 i;

  RtlInitUnicodeString(&ParamString, L"\\Parameters");
  ParsedRegPath.MaximumLength = RegistryPath->Length + ParamString.Length + sizeof(WCHAR);
  ParsedRegPath.Length = 0;

  // Now that we have the lengths set correctly, allocate a buffer for
  // the string from pageable pool.
  ParsedRegPath.Buffer = ExAllocatePool(PagedPool, ParsedRegPath.MaximumLength);

  // Check to make sure we could get the memory.
  if ( !ParsedRegPath.Buffer) 
    {
    // We failed, return with an appropriate status code.
    KdPrint(("OSILLC: FAILED! Returning INSUFFICIENT_RESOURCES.\n"));
    return (STATUS_INSUFFICIENT_RESOURCES);
    }

  // That worked. Zero out the memory and then parse the strings together.
  RtlZeroMemory(ParsedRegPath.Buffer, ParsedRegPath.MaximumLength);
  RtlAppendUnicodeStringToString(&ParsedRegPath, RegistryPath);
  RtlAppendUnicodeStringToString(&ParsedRegPath, &ParamString);

  // We have our path. Now zero out the memory for the paramTable for
  // RtlQueryRegistryValues.
  RtlZeroMemory(paramTable, sizeof(paramTable));


  //--------------------------------------------
  // Get the LSAPs from registry or use defaults
  i=0;
  paramTable[i].Flags = RTL_QUERY_REGISTRY_DIRECT;
  paramTable[i].Name = L"LSAPs";
  paramTable[i].EntryContext = &OsillcLsapTable;
  paramTable[i].DefaultType = REG_BINARY;
  paramTable[i].DefaultData = &OsillcLsapTable;
  paramTable[i].DefaultLength = sizeof(OsillcLsapTable);
  // Note: if the "LSAPs" field is empty then the function below will return error

  // Now let us try and query the registry for our information.
  Status = RtlQueryRegistryValues(RTL_REGISTRY_ABSOLUTE | RTL_REGISTRY_OPTIONAL,
    ParsedRegPath.Buffer, &paramTable[0],
    NULL, NULL);
  // We will not check the Status, if error we use defaults.

  // Since NT doesn't return the length of the REG_BINARY value we need to
  // find the length of the LSAP table
  OsillcLsapCount = 0;
  for (i=0; i<sizeof(OsillcLsapTable); ++i)
    {
    if (OsillcLsapTable[i] == 0)
      break;
    ++OsillcLsapCount;
    }

#if DBG
  if (OsillcDebugFlag > 1)
    {
    DEBUGTRACE1("OsillcGetConfiguration: Filtering on %d LSAPs: ", OsillcLsapCount);
    for (i=0; i<OsillcLsapCount; ++i)
      {
      DEBUGTRACE1(" %2.2X ", (UINT) OsillcLsapTable[i]);
      }
    DEBUGTRACE0("OsillcGetConfiguration: End of LSAP Table");
    }
#endif  // DBG

  //--------------------------------------------------------
  // Get the Ethertype IDs from registry (no defaults used)
  i=0;
  paramTable[i].Flags = RTL_QUERY_REGISTRY_DIRECT;
  paramTable[i].Name = L"EthertypeIDs";
  paramTable[i].EntryContext = &OsillcEthertypeIdsTable;
  paramTable[i].DefaultType = REG_BINARY;
  paramTable[i].DefaultData = &OsillcEthertypeIdsTable;
  paramTable[i].DefaultLength = sizeof(OsillcEthertypeIdsTable)-2; // last 2 bytes need to be 00 00
  // Note: if the "EthertypeIDs" field is empty then the function below will return error

  // Now let us try and query the registry for our information.
  Status = RtlQueryRegistryValues(RTL_REGISTRY_ABSOLUTE | RTL_REGISTRY_OPTIONAL,
    ParsedRegPath.Buffer, &paramTable[0],
    NULL, NULL);
  // We will not check the Status, if error we don't filter on any Ethertype IDs.

  // Since NT doesn't return the length of the REG_BINARY value we need to
  // find the length of the Ethertype IDs table
  OsillcEthertypeIdsCount = 0;
  for (i=0; i<sizeof(OsillcEthertypeIdsTable)-1; ++i,++i)
    {
    // since Ethertype could have only the second byte 00 (e.g. 80 00) then
    // 2 bytes with "00 00" will indicate the end of Ethertype IDs
    if (OsillcEthertypeIdsTable[i] == 0 && OsillcEthertypeIdsTable[i+1] == 0)
      break;
    ++OsillcEthertypeIdsCount;		
    }

  //---------------------------------------------------------------
  // Now set up the paramTable entries to query our registry values.
  i = 0;
  paramTable[i].Flags = RTL_QUERY_REGISTRY_DIRECT;
  paramTable[i].Name  = L"DebugLevel";
  paramTable[i].EntryContext = &OsillcDebugFlag;
  paramTable[i].DefaultType = REG_DWORD;
  paramTable[i].DefaultData = &OsillcDebugFlag;
  paramTable[i].DefaultLength = sizeof(ULONG);

  i++;
  paramTable[i].Flags = RTL_QUERY_REGISTRY_DIRECT;
  paramTable[i].Name  = L"PriorityBoost";
  paramTable[i].EntryContext = &dwPriorityBoost;
  paramTable[i].DefaultType = REG_DWORD;
  paramTable[i].DefaultData = &dwPriorityBoost;
  paramTable[i].DefaultLength = sizeof(ULONG);

  i++;
  paramTable[i].Flags = RTL_QUERY_REGISTRY_DIRECT;
  paramTable[i].Name = L"ReceptionMode";
  paramTable[i].EntryContext = &OsillcReceptionMode;
  paramTable[i].DefaultType = REG_DWORD;
  paramTable[i].DefaultData = &OsillcReceptionMode;
  paramTable[i].DefaultLength = sizeof(ULONG);

  i++;
  paramTable[i].Flags = RTL_QUERY_REGISTRY_DIRECT;
  paramTable[i].Name = L"ReadPackets";
  paramTable[i].EntryContext = &OsillcReadPackets;
  paramTable[i].DefaultType = REG_DWORD;
  paramTable[i].DefaultData = &OsillcReadPackets;
  paramTable[i].DefaultLength = sizeof(ULONG);

  i++;
  paramTable[i].Flags = RTL_QUERY_REGISTRY_DIRECT;
  paramTable[i].Name = L"TransmitPackets";
  paramTable[i].EntryContext = &OsillcTransmitPackets;
  paramTable[i].DefaultType = REG_DWORD;
  paramTable[i].DefaultData = &OsillcTransmitPackets;
  paramTable[i].DefaultLength = sizeof(ULONG);

  i++;
  paramTable[i].Flags = RTL_QUERY_REGISTRY_DIRECT;
  paramTable[i].Name = L"ReceivePackets";
  paramTable[i].EntryContext = &OsillcReceivePackets;
  paramTable[i].DefaultType = REG_DWORD;
  paramTable[i].DefaultData = &OsillcReceivePackets;
  paramTable[i].DefaultLength = sizeof(ULONG);

  // Now let us try and query the registry for our information.
  Status = RtlQueryRegistryValues(RTL_REGISTRY_ABSOLUTE | RTL_REGISTRY_OPTIONAL,
    ParsedRegPath.Buffer, &paramTable[0],
    NULL, NULL);

  // Check to see if we were successful.
  if ( !NT_SUCCESS(Status)) 
    {
    // Something bad happened. We will return a failure. We musn't
    // forget to free the pool we allocated for the Registry buffer.
    KdPrint(("OSILLC: FAILURE! RtlQueryRegistryValues.\n"));
    ExFreePool(ParsedRegPath.Buffer);
    return (STATUS_DRIVER_INTERNAL_ERROR);
    }

  // free the buffer for the Parsed registry path.
  ExFreePool(ParsedRegPath.Buffer);

  // adjust the priority boost if too high
  OsillcPriorityBoost =
    (dwPriorityBoost > IO_NETWORK_INCREMENT) ? (CCHAR)dwPriorityBoost : IO_NETWORK_INCREMENT;

  DEBUGTRACE0("DriverEntry");

  RtlZeroMemory(&ProtocolChar, sizeof(NDIS_PROTOCOL_CHARACTERISTICS));

#if defined(NDIS50)
  ProtocolChar.MajorNdisVersion            = 5;
  ProtocolChar.MinorNdisVersion            = 0;
  ProtocolChar.BindAdapterHandler          = OsillcBindAdapter;
  ProtocolChar.UnbindAdapterHandler        = OsillcUnbindAdapter;
#else
  ProtocolChar.MajorNdisVersion            = 3;
  ProtocolChar.MinorNdisVersion            = 0;
#endif
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
  ProtocolChar.Name                        = ProtoName;

  NdisRegisterProtocol(&Status, &NdisProtocolHandle, &ProtocolChar,
    sizeof(NDIS_PROTOCOL_CHARACTERISTICS));

  if (Status != NDIS_STATUS_SUCCESS) 
    {
    DEBUGERROR1("RegisterProtocol failed: (%x)", Status);
    return Status;
    }


  // set up the device driver entry points.
  DriverObject->MajorFunction[IRP_MJ_CREATE]          = OsillcOpen;
  DriverObject->MajorFunction[IRP_MJ_CLOSE]           = OsillcClose;
  DriverObject->MajorFunction[IRP_MJ_READ]            = OsillcRead;
  DriverObject->MajorFunction[IRP_MJ_WRITE]           = OsillcWrite;
  DriverObject->MajorFunction[IRP_MJ_CLEANUP]         = OsillcCleanup;
  DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]  = OsillcIoControl;
  DriverObject->DriverUnload                          = OsillcUnload;

  //
  //  Get the name of the OSILLC driver and the name of the MAC driver
  //  to bind to from the registry
  //
  Status = OsillcReadRegistry(&BindString, &ExportString, RegistryPath);

  if (Status != STATUS_SUCCESS) 
    {
    DEBUGERROR1("ReadRegistry failed: (%x)", Status);
    goto RegistryError;
    }

  BindStringSave   = BindString;
  ExportStringSave = ExportString;

  //  create a device object for each entry
  while (*BindString!= UNICODE_NULL && *ExportString!= UNICODE_NULL) 
    {
    //  Create a counted unicode string for both null terminated strings
    RtlInitUnicodeString(&MacDriverName, BindString);
    RtlInitUnicodeString(&UnicodeDeviceName, ExportString);

    //  advance to the next string of the MULTI_SZ string
    BindString   += (MacDriverName.Length + sizeof(UNICODE_NULL))/sizeof(WCHAR);
    ExportString += (UnicodeDeviceName.Length + sizeof(UNICODE_NULL))/sizeof(WCHAR);

    DEBUGTRACE2("DeviceName=%ws  MacName=%ws", 
      UnicodeDeviceName.Buffer, MacDriverName.Buffer);

    //  create the device object
    Status = IoCreateDevice(DriverObject, sizeof(DEVICE_EXTENSION),
                            &UnicodeDeviceName, FILE_DEVICE_PROTOCOL,
                            0, FALSE, &DeviceObject);

    if (Status != STATUS_SUCCESS) 
      {
      DEBUGERROR1("IoCreateDevice failed: (%x)", Status);
      break;
      }

    Status = OsillcCreateSymbolicLink(&UnicodeDeviceName, 
                                      DevicesCreated, TRUE);

    if (Status != STATUS_SUCCESS) 
      {
      DEBUGERROR1("IoCreateSymbolicLink failed: (%x)", Status);
      break;
      }

    DevicesCreated++;

    DeviceObject->Flags |= DO_DIRECT_IO;
    DeviceExtension = (PDEVICE_EXTENSION)DeviceObject->DeviceExtension;
    DeviceExtension->DeviceObject = DeviceObject;
    DeviceExtension->DevicesCreated = DevicesCreated;

    //  save the the name of the MAC driver to open
    //      and the Mac name in the Device Extension
    DeviceExtension->AdapterName = MacDriverName;

      {
      WCHAR   szDevice[] = L"\\Device\\";
      ULONG   Size = sizeof(L"\\Device\\")/2 - 1;
      PWCHAR p;

      //              p = DeviceExtension->AdapterName.Buffer + (sizeof(szDevice)/2) - 1;
      p = DeviceExtension->AdapterName.Buffer + (sizeof(L"\\Device\\")/2) - 1;

      RtlInitUnicodeString(&DeviceExtension->MacName, p);
      }

    DEBUGTRACE1("MacName: %ws", DeviceExtension->MacName.Buffer);

    if (DevicesCreated == 1) 
      {
      DeviceExtension->BindString   = BindStringSave;
      DeviceExtension->ExportString = ExportStringSave;
      }

    DeviceExtension->NdisProtocolHandle = NdisProtocolHandle;
    }

  // check if we managed to create at least on device.
  if (DevicesCreated > 0) 
    return STATUS_SUCCESS;

  ExFreePool(BindStringSave);
  ExFreePool(ExportStringSave);

RegistryError:
  NdisDeregisterProtocol(&Status, NdisProtocolHandle);

  Status = STATUS_UNSUCCESSFUL;

  return Status;
  }


/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  VOID OsillcBindAdapter
 *
 *  PURPOSE:   Function for dynamic binding to an underlying NIC
 *
 *  PARMS:	OUT PNDIS_STATUS	Status
 *		IN NDIS_HANDLE		BindContext
 *		IN PNDIS_STRING		DeviceName
 *		IN PVOID		SystemSpecific1
 *		IN PVOID		SystemSpecific2
 *
 *  RETURNS:   Nothing. 
 *
 *  NOTES:  	Required for NDIS 5.0 on Win XP. According to MS design this
 *		function suppose to call the NdisOpenAdapter function but in our
 *		case it is done from the osill2d stack. We could move portion of
 *		the code from DriverEntry function here, but there maybe be risk
 *		that this OsillcBindAdapter function may not be called by NDIS
 *		(as indicated in the Note for ProtoName in the DriverEntry).
 *		This code should work OK on Win 2000 also.
-*/
/* ---------------------------------------------------------------------*/

#if defined(NDIS50)
VOID OsillcBindAdapter(
		OUT PNDIS_STATUS Status,
		IN NDIS_HANDLE  BindContext,
		IN PNDIS_STRING  DeviceName,
		IN PVOID  SystemSpecific1,
		IN PVOID  SystemSpecific2)
{
  DEBUGTRACE1("BindAdapterHandler - DeviceName=%ws.\n", DeviceName);
  *Status = NDIS_STATUS_SUCCESS;
}
#endif /* defined(NDIS50) */

/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  VOID OsillcUnbindAdapter
 *
 *  PURPOSE:   Function for unbinding from an underlying NIC
 *
 *  PARMS:	OUT PNDIS_STATUS	Status
 *		IN NDIS_HANDLE		ProtocolBindingContext
 *		IN NDIS_HANDLE		UnbindContext
 *
 *  RETURNS:   Nothing. 
 *
 *  NOTES:  Required for NDIS 5.0 on Win XP
 *
-*/
/* ---------------------------------------------------------------------*/

#if defined(NDIS50)
VOID OsillcUnbindAdapter(
		OUT PNDIS_STATUS  Status,
		IN NDIS_HANDLE  ProtocolBindingContext,
		IN NDIS_HANDLE  UnbindContext)
{
  DEBUGTRACE0("UnbindAdapterHandler.\n");
  *Status = NDIS_STATUS_SUCCESS;
}
#endif /* defined(NDIS50) */

/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  VOID OsillcUnload(PDRIVER_OBJECT DriverObject)
 *
 *  PURPOSE:   Unload the driver.
 *
 *  PARMS:     PDEVICE_OBJECT DeviceObject - pointer to device object
 *
 *  RETURNS:   Nothing. 
 *
 *  NOTES:
 *
-*/
/* ---------------------------------------------------------------------*/

VOID OsillcUnload(PDRIVER_OBJECT DriverObject)
  {
  PDEVICE_OBJECT     DeviceObject = DriverObject->DeviceObject;
  PDEVICE_OBJECT     OldDeviceObject;
  PDEVICE_EXTENSION  DeviceExtension = DeviceObject->DeviceExtension;
  NDIS_HANDLE        NdisProtocolHandle;
  NDIS_STATUS        Status;
  ULONG   i;

  DEBUGTRACE0("Unload");

  // delete the symbolic links
  for (i = 0; i < DeviceExtension->DevicesCreated; i++)
    {
    Status = OsillcCreateSymbolicLink(UNICODE_NULL, i, FALSE);

    if (Status != STATUS_SUCCESS) 
      DEBUGERROR1("IoDeleteSymbolicLink failed: (%x)", Status);
    }

  // now delete all device objects
  while (DeviceObject != NULL) 
    {
    DeviceExtension = DeviceObject->DeviceExtension;

    NdisProtocolHandle=DeviceExtension->NdisProtocolHandle;

    if (DeviceExtension->BindString != NULL) 
      ExFreePool(DeviceExtension->BindString);

    if (DeviceExtension->ExportString != NULL) 
      ExFreePool(DeviceExtension->ExportString);

    OldDeviceObject = DeviceObject;
    DeviceObject = DeviceObject->NextDevice;

    IoDeleteDevice(OldDeviceObject);
    }

  // finally deregister our protocol driver
  NdisDeregisterProtocol(&Status, NdisProtocolHandle);
  }

/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  VOID OsillcCancel(PDRIVER_OBJECT DriverObject, PIRP Irp)
 *
 *  PURPOSE:   Cancels a pending IRP.
 *
 *  PARMS:     PDEVICE_OBJECT DeviceObject - pointer to device object
 *             PIRP Irp                    - pointer to cancel IRP
 *
 *  RETURNS:   Nothing. 
 *
 *  NOTES:
 *
-*/
/* ---------------------------------------------------------------------*/

VOID OsillcCancel(PDEVICE_OBJECT DeviceObject, PIRP Irp)
  {
  PIO_STACK_LOCATION  IrpSp = IoGetCurrentIrpStackLocation(Irp);
  POPEN_INSTANCE      Open = IrpSp->FileObject->FsContext;

  DEBUGTRACE0("Cancel");

  Open->SignalIrp = NULL;

  // Release the cancel spin lock.
  IoReleaseCancelSpinLock(Irp->CancelIrql);

  Irp->IoStatus.Status = STATUS_CANCELLED;
  Irp->IoStatus.Information = 0;
  IoCompleteRequest(Irp, IO_NO_INCREMENT);
  }

/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  NTSTATUS OsillcIoControl(PDEVICE_OBJECT DeviceObject, PIRP Irp)
 *
 *  PURPOSE:   Dispatch routine to process IOCTL requests.
 *
 *  PARMS:     PDEVICE_OBJECT DeviceObject - pointer to device object
 *             PIRP Irp                    - pointer to current IRP
 *
 *  RETURNS:   NTSTATUS. 
 *
 *  NOTES:
 *
-*/
/* ---------------------------------------------------------------------*/

NTSTATUS OsillcIoControl(PDEVICE_OBJECT DeviceObject, PIRP Irp)
  {
  PIO_STACK_LOCATION  IrpSp = IoGetCurrentIrpStackLocation(Irp);
  POPEN_INSTANCE      Open = IrpSp->FileObject->FsContext;
  ULONG               FunctionCode;
  NDIS_STATUS         Status;

  DEBUGTRACE0("IoControl");

  FunctionCode = IrpSp->Parameters.DeviceIoControl.IoControlCode;

  // mark this IRP as pending
  IoMarkIrpPending(Irp);
  Irp->IoStatus.Status = STATUS_PENDING;
  Irp->IoStatus.Information = 0;


  DEBUGTRACE1("Function code is %08lx", FunctionCode);

  switch (FunctionCode)
    {
    case IOCTL_OSILLC_GET_MACNAME:
      {
      ULONG   OutputBufferLength = IrpSp->Parameters.DeviceIoControl.OutputBufferLength;

      // validate the output parameter
      if (OutputBufferLength <= Open->DeviceExtension->MacName.Length)
	{
	//  buffer too small
	Status = STATUS_BUFFER_TOO_SMALL;
	Irp->IoStatus.Information = 0;
	}
      else
	{
	ANSI_STRING asString;

	// copy the MAC name to string
	asString.MaximumLength = (USHORT)OutputBufferLength;
	asString.Buffer = (PCHAR)Irp->AssociatedIrp.SystemBuffer;
	Status = RtlUnicodeStringToAnsiString(&asString,
	  &Open->DeviceExtension->MacName, FALSE);
	Irp->IoStatus.Information =
	  (Status == STATUS_SUCCESS) ? asString.Length + 1 : 0;
	}
      }
    Irp->IoStatus.Status = Status;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    break;

    case IOCTL_OSILLC_GET_STATS:
      {
      OSILLC_GET_STATS       *pGetStats = (OSILLC_GET_STATS *)Irp->AssociatedIrp.SystemBuffer;

      // validate the output parameter
      if (IrpSp->Parameters.DeviceIoControl.OutputBufferLength < sizeof(OSILLC_GET_STATS))
	{
	//  buffer too small
	Status = STATUS_BUFFER_TOO_SMALL;
	Irp->IoStatus.Information = 0;
	}
      else
	{
	pGetStats->XmitOk = NdisXmitOk;
	pGetStats->RcvOk = NdisRcvOk;
	pGetStats->XmitError = NdisXmitError;
	pGetStats->RcvError = NdisRcvError;
	pGetStats->RcvUnknown = NdisRcvUnknown;
	pGetStats->XmitInd = NdisXmitInd;
	pGetStats->RcvInd = NdisRcvInd;
	pGetStats->AllocError = NdisAllocError;

	Status = NDIS_STATUS_SUCCESS;
	Irp->IoStatus.Information = sizeof(OSILLC_GET_STATS);
	}
      Irp->IoStatus.Status = Status;
      IoCompleteRequest(Irp, IO_NO_INCREMENT);
      }
    break;

    case IOCTL_OSILLC_SET_OID:
    case IOCTL_OSILLC_QUERY_OID:
      {
      POSILLC_OID_DATA OidData = (POSILLC_OID_DATA)Irp->AssociatedIrp.SystemBuffer;
      ULONG   InputBufferLength = IrpSp->Parameters.DeviceIoControl.InputBufferLength;
      PLIST_ENTRY                     RequestListEntry;
      PINTERNAL_REQUEST       pRequest;

      // get an empty request block
      RequestListEntry =
	ExInterlockedRemoveHeadList(&Open->RequestList, &Open->RequestQSpinLock);

      // check if we got a block
      if (RequestListEntry == NULL)
	{
	Status = STATUS_UNSUCCESSFUL;
	Irp->IoStatus.Status = Status;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	break;
	}

      // save a pointer to our IRP
      pRequest = CONTAINING_RECORD(RequestListEntry, INTERNAL_REQUEST, ListElement);
      pRequest->Irp = Irp;

      // mark the IRP as pending
      IoMarkIrpPending(Irp);
      Irp->IoStatus.Status = STATUS_PENDING;

      // validate the input and output parameters
      if ((InputBufferLength == IrpSp->Parameters.DeviceIoControl.OutputBufferLength) &&
	(InputBufferLength >= sizeof(OSILLC_OID_DATA)) &&
	(InputBufferLength >= sizeof(OSILLC_OID_DATA) - 1 + OidData->Length))
	{

	DEBUGTRACE1("IoControl: Request: Oid=%08lx", OidData->Oid);
	DEBUGTRACE1("           Length=%08lx", OidData->Length);

	// set up the request
	if (FunctionCode == IOCTL_OSILLC_SET_OID)
	  {
	  pRequest->Request.RequestType = NdisRequestSetInformation;
	  pRequest->Request.DATA.SET_INFORMATION.Oid = OidData->Oid;
	  pRequest->Request.DATA.SET_INFORMATION.InformationBuffer = OidData->Data;
	  pRequest->Request.DATA.SET_INFORMATION.InformationBufferLength = OidData->Length;
	  }
	else
	  {
	  pRequest->Request.RequestType = NdisRequestQueryInformation;
	  pRequest->Request.DATA.QUERY_INFORMATION.Oid = OidData->Oid;
	  pRequest->Request.DATA.QUERY_INFORMATION.InformationBuffer = OidData->Data;
	  pRequest->Request.DATA.QUERY_INFORMATION.InformationBufferLength = OidData->Length;
	  }

	//  submit the request
	NdisRequest(&Status, Open->AdapterHandle, &pRequest->Request);
	}
      else
	{
	//  buffer too small
	Status = NDIS_STATUS_FAILURE;
	pRequest->Request.DATA.SET_INFORMATION.BytesRead = 0;
	pRequest->Request.DATA.QUERY_INFORMATION.BytesWritten = 0;
	}

      if (Status != NDIS_STATUS_PENDING)
	{
	DEBUGTRACE0("Calling RequestCompleteHandler");
	OsillcRequestComplete(Open, &pRequest->Request, Status);
	}
      }
    break;

    default:
    Status = STATUS_UNSUCCESSFUL;
    Irp->IoStatus.Status = Status;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    break;
    }

  return STATUS_PENDING;
  //      return Status;
  }


/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  VOID OsillcRequestComplete(NDIS_HANDLE ProtocolBindingContext,
 *                                                 PNDIS_REQUEST NdisRequest, NDIS_STATUS Status)
 *
 *  PURPOSE:   Completes NDIS OID requests.
 *
 *  PARMS:     NDIS_HANDLE ProtocolBindingContext - pointer to binding context
 *             PNDIS_REQUEST NdisRequest - pointer to NDIS request
 *             NDIS_STATUS Status - resulting status
 *
 *  RETURNS:   NTSTATUS. 
 *
 *  NOTES:
 *
-*/
/* ---------------------------------------------------------------------*/

VOID OsillcRequestComplete(NDIS_HANDLE ProtocolBindingContext,
  PNDIS_REQUEST NdisRequest, NDIS_STATUS Status)
  {
  POPEN_INSTANCE          Open = (POPEN_INSTANCE)ProtocolBindingContext;
  PIO_STACK_LOCATION      IrpSp;
  PIRP                    Irp;
  UINT                FunctionCode;
  PINTERNAL_REQUEST   pRequest;
  POSILLC_OID_DATA    OidData;
  KIRQL                           oldIrql;
  PLIST_ENTRY                     pListEntry;

  DEBUGTRACE0("RequestCompleteHandler");

  // get our pending request IRP
  pRequest = CONTAINING_RECORD(NdisRequest, INTERNAL_REQUEST, Request);
  Irp = pRequest->Irp;
  IrpSp = IoGetCurrentIrpStackLocation(Irp);
  FunctionCode = IrpSp->Parameters.DeviceIoControl.IoControlCode;

  OidData = Irp->AssociatedIrp.SystemBuffer;

  if (FunctionCode == IOCTL_OSILLC_SET_OID)
    {
    OidData->Length = pRequest->Request.DATA.SET_INFORMATION.BytesRead;
    }
  else if (FunctionCode == IOCTL_OSILLC_QUERY_OID)
    {
    OidData->Length = pRequest->Request.DATA.QUERY_INFORMATION.BytesWritten;
    }

  if (Status == NDIS_STATUS_SUCCESS)
    Irp->IoStatus.Information = IrpSp->Parameters.DeviceIoControl.InputBufferLength;
  else
    {
    DEBUGERROR1("Request failed (%x)", Status);
    Irp->IoStatus.Information = 0;
    }

  // put the request block back on the free list
  ExInterlockedInsertTailList(&Open->RequestList, &pRequest->ListElement,
    &Open->RequestQSpinLock);

  // complete the IRP
  //      Irp->IoStatus.Status = NDIS_STATUS_SUCCESS;
  Irp->IoStatus.Status = Status;
  IoCompleteRequest(Irp, IO_NO_INCREMENT);
  }

/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  VOID OsillcStatus(NDIS_HANDLE ProtocolBindingContext,
 *                                                NDIS_STATUS Status,
 *                                                PVOID StatusBuffer, UINT StatusBufferSize)
 *
 *  PURPOSE:   Status change notification from miniport.
 *
 *  PARMS:     NDIS_HANDLE ProtocolBindingContext - pointer to binding context
 *             NDIS_STATUS Status - resulting status
 *             PVOID StatusBuffer - pointer to miniport status
 *             UINT StatusBufferSize - size of miniport status buffer
 *
 *  RETURNS:   Nothing. 
 *
 *  NOTES:
 *
-*/
/* ---------------------------------------------------------------------*/

VOID OsillcStatus(NDIS_HANDLE ProtocolBindingContext, NDIS_STATUS Status,
  PVOID StatusBuffer, UINT StatusBufferSize)
  {
  DEBUGTRACE0("StatusIndication");
  return;
  }

/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  VOID OsillcStatusComplete(NDIS_HANDLE ProtocolBindingContext,
 *
 *  PURPOSE:   Completes a miniport status change requests.
 *
 *  PARMS:     NDIS_HANDLE ProtocolBindingContext - pointer to binding context
 *
 *  RETURNS:   Nothing. 
 *
 *  NOTES:
 *
-*/
/* ---------------------------------------------------------------------*/

VOID OsillcStatusComplete(NDIS_HANDLE ProtocolBindingContext)
  {
  DEBUGTRACE0("StatusIndicationComplete");
  return;
  }

/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  NTSTATUS OsillcCreateSymbolicLink(PUNICODE_STRING DeviceName,
 *                                UINT DeviceNumber,
 *                                                                BOOLEAN Create)
 *
 *  PURPOSE:   Create a SymbolicLink for device.
 *
 *  PARMS:     PUNICODE_STRING DeviceName - pointer to device name
 *             UINT DeviceNumber - link suffix number
 *             BOOLEAN Create - if TRUE then create link, otherwise delete it
 *
 *  RETURNS:   NTSTATUS. 
 *
 *  NOTES:
 *
-*/
/* ---------------------------------------------------------------------*/

NTSTATUS OsillcCreateSymbolicLink(PUNICODE_STRING DeviceName, UINT DeviceNumber,
  BOOLEAN Create)
  {
  UNICODE_STRING  usDosDeviceName;
  NTSTATUS                Status;
  WCHAR                   szDosDeviceName[] = L"\\DosDevices\\Osillc0";

  // create a Dos device name
  szDosDeviceName[(sizeof(szDosDeviceName)/2) - 2] = L'0' + (WCHAR)(DeviceNumber+1);
  RtlInitUnicodeString(&usDosDeviceName, szDosDeviceName);

  DEBUGTRACE1("DosDeviceName is %ws", usDosDeviceName.Buffer);

  // create or delete the symbolic link
  if (Create) 
    Status = IoCreateSymbolicLink(&usDosDeviceName, DeviceName);
  else 
    Status = IoDeleteSymbolicLink(&usDosDeviceName);

  return Status;
  }

/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  NTSTATUS OsillcReadRegistry(PWSTR *MacDriverName,
 *                                                                PWSTR *OsillcDriverName,
 *                                PUNICODE_STRING RegistryPath)
 *
 *  PURPOSE:   Reads Registry parameters for this driver.
 *
 *  PARMS:     PWSTR *MacDriverName, - pointer to miniport driver name
 *             PWSTR *OsillcDriverName - name of this driver
 *             PUNICODE_STRING RegistryPath - registry path for this driver
 *
 *  RETURNS:   NTSTATUS. 
 *
 *  NOTES:
 *
-*/
/* ---------------------------------------------------------------------*/

NTSTATUS OsillcReadRegistry(PWSTR *MacDriverName, PWSTR *OsillcDriverName,
  PUNICODE_STRING RegistryPath)
  {
  RTL_QUERY_REGISTRY_TABLE ParamTable[5];
  NTSTATUS   Status;
  PWSTR      Bind       = L"Bind";
  PWSTR      Export     = L"Export";
  PWSTR      Parameters = L"Parameters";
  PWSTR      Linkage    = L"Linkage";
  PWCHAR     Path;

  Path = ExAllocatePool(PagedPool, RegistryPath->Length + sizeof(WCHAR));
  if (Path == NULL) 
    return STATUS_INSUFFICIENT_RESOURCES;

  RtlZeroMemory(Path, RegistryPath->Length+sizeof(WCHAR));
  RtlCopyMemory(Path, RegistryPath->Buffer, RegistryPath->Length);

  DEBUGTRACE1("OSILLC: Reg path is %ws\n", RegistryPath->Buffer);

  RtlZeroMemory(ParamTable, sizeof(ParamTable));

  //
  //  change to the parmeters key
  //
  ParamTable[0].QueryRoutine = NULL;
  ParamTable[0].Flags = RTL_QUERY_REGISTRY_SUBKEY;
  ParamTable[0].Name = Parameters;

  //
  //  change to the linkage key
  //
  ParamTable[1].QueryRoutine = NULL;
  ParamTable[1].Flags = RTL_QUERY_REGISTRY_SUBKEY;
  ParamTable[1].Name = Linkage;

  //
  //  Get the name of the mac driver we should bind to
  //
  ParamTable[2].QueryRoutine = OsillcQueryRegistryRoutine;
  ParamTable[2].Flags = RTL_QUERY_REGISTRY_REQUIRED |
    RTL_QUERY_REGISTRY_NOEXPAND;

  ParamTable[2].Name = Bind;
  ParamTable[2].EntryContext = (PVOID)MacDriverName;
  ParamTable[2].DefaultType = REG_MULTI_SZ;

  //
  //  Get the name that we should use for the driver object
  //
  ParamTable[3].QueryRoutine = OsillcQueryRegistryRoutine;
  ParamTable[3].Flags = RTL_QUERY_REGISTRY_REQUIRED |
    RTL_QUERY_REGISTRY_NOEXPAND;

  ParamTable[3].Name = Export;
  ParamTable[3].EntryContext = (PVOID) OsillcDriverName;
  ParamTable[3].DefaultType = REG_MULTI_SZ;

  Status = RtlQueryRegistryValues(RTL_REGISTRY_ABSOLUTE, Path, ParamTable, NULL, NULL);

  ExFreePool(Path);

  return Status;
  }

/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  NTSTATUS OsillcQueryRegistryRoutine(PWSTR ValueName, ULONG ValueType,
 *                                                                      PVOID ValueData, ULONG ValueLength,
									PVOID Context, PVOID EntryContext)
 *
 *  PURPOSE:   This is the QueryRegistry callback.
 *
 *  PARMS:     PWSTR ValueName - name of value
 *             ULONG ValueType - value type
 *             PVOID ValueData - pointer to value data buffer
 *             ULONG ValueLength - size of data buffer
 *             PVOID Context
 *             PPVOID EntryContext
 *
 *  RETURNS:   NTSTATUS. 
 *
 *  NOTES:
 *
-*/
/* ---------------------------------------------------------------------*/

NTSTATUS OsillcQueryRegistryRoutine(PWSTR ValueName, ULONG ValueType,
  PVOID ValueData, ULONG ValueLength,
  PVOID Context, PVOID EntryContext)
  {
  PUCHAR  Buffer;

  DEBUGTRACE0("QueryRegistryRoutine");

  if (ValueType != REG_MULTI_SZ) 
    return STATUS_OBJECT_NAME_NOT_FOUND;

  Buffer = ExAllocatePool(NonPagedPool, ValueLength);

  if (Buffer == NULL) 
    return STATUS_INSUFFICIENT_RESOURCES;

  RtlCopyMemory(Buffer, ValueData, ValueLength);

  * ((PUCHAR *)EntryContext) = Buffer;

  return STATUS_SUCCESS;
  }
