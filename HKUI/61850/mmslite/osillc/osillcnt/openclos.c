/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,       */
/*              1996, All Rights Reserved                               */
/*                                                                      */
/* MODULE NAME : openclos.c                                             */
/* PRODUCT(S)  : OSI LLC NDIS 3.0 Device Driver for NT                  */
/*                                                                      */
/* MODULE DESCRIPTION :                                                 */
/*                                                                      */
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :                            */
/*                                                                      */
/* MODIFICATION LOG :                                                   */
/*  Date     Who   Rev                  Comments                        */
/* --------  ---  ------   -------------------------------------------  */
/* 08/21/00  DSF    09     Minor cleanup				*/
/* 04/01/99  DSF    08     Commonized Win98/WinNT include files		*/
/* 01/28/98  DSF    07     Medium parameters must be committed to	*/
/*			   memory - made them static			*/
/* 05/13/98  DSF    06     Added ReadPackets parameter			*/
/* 05/11/98  DSF    05     File reformatted				*/
/* 06/19/97  DSF    04     Added Stats                                  */
/* 07/16/96  DSF    02     Fixed DEBUGERROR1 Macros                     */
/* 05/22/96  DSF    01     Initial Release                              */
/*                                                                      */
/************************************************************************/

#include "ntddk.h"
#include "ntiologc.h"
#include "ndis.h"

#include "osillc.h"
#include "debug.h"
#include "frame.h"
#include "osillcnt.h"


/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  NTSTATUS OsillcOpen(PDEVICE_OBJECT DeviceObject, PIRP Irp)
 *
 *  PURPOSE:   Open an adapter object.
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

NTSTATUS OsillcOpen(PDEVICE_OBJECT DeviceObject, PIRP Irp)
  {
  PDEVICE_EXTENSION       DeviceExtension = DeviceObject->DeviceExtension;
  PIO_STACK_LOCATION      IrpSp = IoGetCurrentIrpStackLocation(Irp);
  POPEN_INSTANCE          Open;
  NDIS_STATUS                     Status;
  NDIS_STATUS                     ErrorStatus;
static  UINT                      Medium;
static  NDIS_MEDIUM               MediumArray = NdisMedium802_3;
  UINT                            i;

  DEBUGTRACE0("OpenAdapter");

  // allocate some memory for the open structure
  Open = ExAllocatePool(NonPagedPool, sizeof(OPEN_INSTANCE));

  if (Open == NULL) 
    {
    // no memory
    DEBUGERROR0("No Pool Memory");
    Irp->IoStatus.Status = STATUS_INSUFFICIENT_RESOURCES;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    return STATUS_INSUFFICIENT_RESOURCES;
    }

  RtlZeroMemory(Open, sizeof(OPEN_INSTANCE));

  // save our open context here
  IrpSp->FileObject->FsContext = Open;

  Open->DeviceExtension = DeviceExtension;

  // save the Irp here for the completion routine to retrieve
  Open->PendIrp = Irp;

  //  allocate a packet pool for our read packets
  NdisAllocatePacketPool(&Status, &Open->ReadPacketPool, 
                         OsillcReadPackets,
                         sizeof(OSILLC_RESERVED));

  if (Status != NDIS_STATUS_SUCCESS) 
    {
    NdisAllocError++;
    DEBUGERROR1("Could not allocate packet pool (%x)", Status);
    ExFreePool(Open);
    Irp->IoStatus.Status = STATUS_INSUFFICIENT_RESOURCES;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    return STATUS_INSUFFICIENT_RESOURCES;
    }

  // allocate a packet pool for our transmit packets
  NdisAllocatePacketPool(&Status, &Open->TxPacketPool, 
                         OsillcTransmitPackets,
                         sizeof(OSILLC_TX_RESERVED));

  if (Status != NDIS_STATUS_SUCCESS) 
    {
    NdisAllocError++;
    DEBUGERROR1("Could not allocate packet pool (%x)", Status);

    NdisFreePacketPool(Open->ReadPacketPool);
    ExFreePool(Open);
    Irp->IoStatus.Status = STATUS_INSUFFICIENT_RESOURCES;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    return STATUS_INSUFFICIENT_RESOURCES;
    }

  //  allocate a packet pool for our receive packets
  NdisAllocatePacketPool(&Status, &Open->RxPacketPool, 
                         OsillcReceivePackets,
                         sizeof(OSILLC_RESERVED));

  if (Status != NDIS_STATUS_SUCCESS) 
    {
    NdisAllocError++;
    DEBUGERROR1("Could not allocate packet pool (%x)", Status);

    NdisFreePacketPool(Open->TxPacketPool);
    ExFreePool(Open);
    Irp->IoStatus.Status = STATUS_INSUFFICIENT_RESOURCES;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    return STATUS_INSUFFICIENT_RESOURCES;
    }

  //  allocate a buffer pool for our receive packets
  NdisAllocateBufferPool(&Status, &Open->BufferPool, OsillcReceivePackets);

  if (Status != NDIS_STATUS_SUCCESS) 
    {
    NdisAllocError++;
    DEBUGERROR1 ("Could not allocate buffer pool (%x)", Status);

    NdisFreePacketPool(Open->TxPacketPool);
    NdisFreePacketPool(Open->RxPacketPool);
    ExFreePool(Open);

    Irp->IoStatus.Status = STATUS_INSUFFICIENT_RESOURCES;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    return STATUS_INSUFFICIENT_RESOURCES;
    }

  //  allocate a frame pool for our receive packets
  NdisAllocateFramePool(&Status, &Open->FramePool, 
                        OsillcReceivePackets,
                        ETH_LENGTH_OF_FRAME);

  if (Status != NDIS_STATUS_SUCCESS) 
    {
    NdisAllocError++;
    DEBUGERROR1 ("Could not allocate frame pool (%x)", Status);

    NdisFreePacketPool(Open->TxPacketPool);
    NdisFreePacketPool(Open->RxPacketPool);
    NdisFreeBufferPool(Open->BufferPool);
    ExFreePool(Open);

    Irp->IoStatus.Status = STATUS_INSUFFICIENT_RESOURCES;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    return STATUS_INSUFFICIENT_RESOURCES;
    }

  //  initialize list for holding received frames
  KeInitializeSpinLock(&Open->RcvQSpinLock);
  KeInitializeSpinLock(&Open->RcvListSpinLock);
  InitializeListHead(&Open->RcvList);

  //  initialize list for holding Read IRPs
  KeInitializeSpinLock(&Open->ReadQSpinLock);
  InitializeListHead(&Open->ReadIrpList);

  //  initialize list for holding Reset IRPs
  KeInitializeSpinLock(&Open->ResetQSpinLock);
  InitializeListHead(&Open->ResetIrpList);

  //  initialize list for holding empty Request blocks
  KeInitializeSpinLock(&Open->RequestQSpinLock);
  InitializeListHead(&Open->RequestList);

  //  link up the request stored in our open block
  for (i = 0; i < MAX_OSILLC_REQUESTS; i++)
    {
    ExInterlockedInsertTailList(&Open->RequestList, 
                                &Open->Requests[i].ListElement,
                                &Open->RequestQSpinLock);
    }

  // init the Notify event handle and pointer
  Open->hNotifyEvent = NULL;
  Open->pNotifyEvent = NULL;

  // mark the IRP pending
  IoMarkIrpPending(Irp);
  Irp->IoStatus.Status = STATUS_PENDING;

  //  try to open the MAC driver
  NdisOpenAdapter(&Status, &ErrorStatus, &Open->AdapterHandle,
                  &Medium, &MediumArray,
                  1, DeviceExtension->NdisProtocolHandle,
                  Open, &DeviceExtension->AdapterName,
                  0, NULL);

  if (Status != NDIS_STATUS_PENDING) 
    OsillcOpenAdapterComplete(Open, Status, NDIS_STATUS_SUCCESS);

  return STATUS_PENDING;
  //      return Status;
  }

/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  VOID OsillcOpenAdapterComplete(NDIS_HANDLE ProtocolBindingContext,
 *                                     NDIS_STATUS Status)
 *                                                                     NDIS_STATUS OpenErrorStatus)
 *
 *  PURPOSE:   Notification from the bound MAC driver that
 *             an adapter open request is complete.
 *
 *  PARMS:     NDIS_HANDLE ProtocolBindingContext - binding context
 *             NDIS_STATUS Status            - resulting status
 *             NDIS_STATUS OpenErrorStatus   - resulting open error status
 *
 *  RETURNS:   Nothing. 
 *
 *  NOTES:
 *
-*/
/* ---------------------------------------------------------------------*/

VOID OsillcOpenAdapterComplete(NDIS_HANDLE ProtocolBindingContext,
  NDIS_STATUS Status, NDIS_STATUS OpenErrorStatus)
  {
  POPEN_INSTANCE    Open = (POPEN_INSTANCE)ProtocolBindingContext;
  PIRP              Irp = Open->PendIrp;

  DEBUGTRACE0("OpenAdapterComplete");

  if (Status != NDIS_STATUS_SUCCESS) 
    {
    DEBUGERROR1("OpenAdapterComplete failed (%x)", Status);

    // free all buffer pools
    NdisFreePacketPool(Open->TxPacketPool);
    NdisFreePacketPool(Open->RxPacketPool);
    NdisFreeBufferPool(Open->BufferPool);
    NdisFreeFramePool(Open->FramePool);

    ExFreePool(Open);
    }

  Irp->IoStatus.Status = Status;
  IoCompleteRequest(Irp, IO_NO_INCREMENT);
  }

/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  NTSTATUS OsillcClose(PDEVICE_OBJECT DeviceObject, PIRP Irp)
 *
 *  PURPOSE:   Close an adapter object.
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

NTSTATUS OsillcClose(PDEVICE_OBJECT DeviceObject, PIRP Irp)
  {
  PIO_STACK_LOCATION      IrpSp = IoGetCurrentIrpStackLocation(Irp);
  POPEN_INSTANCE          Open = IrpSp->FileObject->FsContext;
  NDIS_STATUS     Status;

  DEBUGTRACE0("CloseAdapter");

  //  save the IRP
  Open->PendIrp = Irp;

  IoMarkIrpPending (Irp);
  Irp->IoStatus.Status = STATUS_PENDING;

  // dereference the Notify event
  if (Open->pNotifyEvent)
    {
    Open->hNotifyEvent = NULL;
    ObDereferenceObject((PVOID)Open->pNotifyEvent);
    Open->pNotifyEvent = NULL;
    }

  //  close the adapter
  NdisCloseAdapter(&Status, Open->AdapterHandle);

  if (Status != NDIS_STATUS_PENDING) 
    OsillcCloseAdapterComplete(Open, Status);

  return STATUS_PENDING;
  //      return Status;
  }

/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  VOID OsillcCloseAdapterComplete(NDIS_HANDLE ProtocolBindingContext,
 *                                             NDIS_STATUS Status)
 *
 *  PURPOSE:   Notification from the bound MAC driver that
 *             an adapter close request is complete.
 *
 *  PARMS:     NDIS_HANDLE ProtocolBindingContext - binding context
 *             NDIS_STATUS Status            - resulting status
 *
 *  RETURNS:   Nothing. 
 *
 *  NOTES:
 *
-*/
/* ---------------------------------------------------------------------*/

VOID OsillcCloseAdapterComplete(NDIS_HANDLE ProtocolBindingContext,
  NDIS_STATUS Status)
  {
  POPEN_INSTANCE    Open = (POPEN_INSTANCE)ProtocolBindingContext;
  PIRP              Irp = Open->PendIrp;

  DEBUGTRACE0("CloseAdapterComplete");

  // free all buffer pools
  NdisFreePacketPool(Open->ReadPacketPool);
  NdisFreePacketPool(Open->TxPacketPool);
  NdisFreePacketPool(Open->RxPacketPool);
  NdisFreeBufferPool(Open->BufferPool);
  NdisFreeFramePool(Open->FramePool);

  ExFreePool(Open);

  // zero out the stats
  NdisXmitOk = 0;
  NdisRcvOk = 0;
  NdisXmitError = 0;
  NdisRcvError = 0;
  NdisRcvUnknown = 0;
  NdisXmitInd = 0;
  NdisRcvInd = 0;
  NdisAllocError = 0;

  Irp->IoStatus.Status = STATUS_SUCCESS;
  IoCompleteRequest(Irp, IO_NO_INCREMENT);
  }

/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  NTSTATUS OsillcCleanup(PDEVICE_OBJECT DeviceObject, PIRP FlushIrp)
 *
 *  PURPOSE:   Clean up IRP on an adapter object.
 *
 *  PARMS:     PDEVICE_OBJECT DeviceObject - pointer to device object
 *             PIRP FlushIrp               - pointer to current IRP
 *
 *  RETURNS:   NTSTATUS. 
 *
 *  NOTES:
 *
-*/
/* ---------------------------------------------------------------------*/

NTSTATUS OsillcCleanup(PDEVICE_OBJECT DeviceObject, PIRP FlushIrp)
  {
  PIO_STACK_LOCATION  IrpSp = IoGetCurrentIrpStackLocation(FlushIrp);
  POPEN_INSTANCE      Open = IrpSp->FileObject->FsContext;
  PLIST_ENTRY         pListEntry;
  PNDIS_PACKET        pPacket;
  NDIS_STATUS         Status = STATUS_PENDING;

  DEBUGTRACE0("Cleanup");

  IoMarkIrpPending(FlushIrp);
  FlushIrp->IoStatus.Status = STATUS_PENDING;

  /*
  //
  //  The open instance of the device is about to close,
  //  we need to complete all pending Read Irp's
  //  First we complete any pending read requests
  //
  while ((pListEntry =
  		  ExInterlockedRemoveHeadList(&Open->ReadIrpList, 
		                              &Open->ReadQSpinLock)) != NULL)
    {
    DEBUGTRACE0("CleanUp - Completeing read");

    pPacket = CONTAINING_RECORD(pListEntry, NDIS_PACKET, ProtocolReserved);

    //  complete normally
    OsillcTransferDataComplete(Open, pPacket, NDIS_STATUS_SUCCESS, 0);
    }
  */

  //  now place the Irp on the Reset list
  ExInterlockedInsertTailList(&Open->ResetIrpList, 
                              &FlushIrp->Tail.Overlay.ListEntry,
                              &Open->ResetQSpinLock);

  //
  //  Now reset the adapter, the mac driver will complete any
  //  pending requests we have made to it.
  //

  // Don't reset for now
  Status = STATUS_SUCCESS;
  //      NdisReset(&Status, Open->AdapterHandle);

  if (Status != NDIS_STATUS_PENDING)
    OsillcResetComplete(Open, Status);

  return(STATUS_PENDING);
  //      return(Status);
  }

/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  VOID OsillcResetComplete(NDIS_HANDLE ProtocolBindingContext,
 *                                      NDIS_STATUS Status)
 *
 *  PURPOSE:   Notification from the bound MAC driver that
 *             a reset request is complete.
 *
 *  PARMS:     NDIS_HANDLE ProtocolBindingContext - binding context
 *             NDIS_STATUS Status            - resulting status
 *
 *  RETURNS:   Nothing. 
 *
 *  NOTES:
 *
-*/
/* ---------------------------------------------------------------------*/

VOID OsillcResetComplete(NDIS_HANDLE ProtocolBindingContext,
  NDIS_STATUS Status)
  {
  POPEN_INSTANCE  Open = (POPEN_INSTANCE) ProtocolBindingContext;
  PIRP                    Irp;
  PLIST_ENTRY         ResetListEntry;

  DEBUGTRACE0("ResetComplete");

  //  remove the reset IRP from the list
  ResetListEntry = ExInterlockedRemoveHeadList(&Open->ResetIrpList, &Open->ResetQSpinLock);

#if DBG
  ASSERT(ResetListEntry != NULL);

  if (ResetListEntry == NULL)
    {
    DbgBreakPoint();
    return;
    }
#endif

  Irp = CONTAINING_RECORD(ResetListEntry, IRP, Tail.Overlay.ListEntry);

  Irp->IoStatus.Status = STATUS_SUCCESS;
  IoCompleteRequest(Irp, IO_NO_INCREMENT);
  }
