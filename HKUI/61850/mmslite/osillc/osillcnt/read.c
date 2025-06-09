/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,       */
/*              1996 - 2005, All Rights Reserved                        */
/*                                                                      */
/* MODULE NAME : read.c                                                 */
/* PRODUCT(S)  : OSI LLC NDIS 3.0 Device Driver for NT                  */
/*                                                                      */
/* MODULE DESCRIPTION :                                                 */
/*                                                                      */
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :                            */
/*                                                                      */
/* MODIFICATION LOG :                                                   */
/*  Date     Who   Rev                  Comments                        */
/* --------  ---  ------   -------------------------------------------  */
/* 01/27/05  JRB    19     OsillcReceiveIndicate: make filtering work with or*/
/*			   without QTag Prefix for OSI & Ethertype frames.*/
/*			   If no filters, accept ALL incoming frames.	*/
/* 12/12/02  EJV    18     Pass all 8100 frames up if Ethertype filters	*/
/*			     not configured.				*/
/* 11/15/02  EJV    17     Added support for Ethertype filtering.	*/
/* 01/15/02  EJV    16     Added support to cfg LSAPs in registry:	*/
/*			     globals OsillcLsapTable, OsillcLsapCount.	*/
/* 11/28/01  JRB    15     Allow IEC GOOSE packets (LSAP = 0xF5)	*/
/* 08/21/00  DSF    14     Minor cleanup				*/
/* 04/01/99  DSF    13     Commonized Win98/WinNT include files		*/
/* 06/02/98  DSF    12     When processing a read, allocate packets	*/
/*			   out of Read Packet pool			*/
/* 05/28/98  DSF    11     A bug bix					*/
/* 05/18/98  DSF    10     Added ReceptionMode				*/
/* 05/13/98  DSF    09     Set SeqNumber in PACKET_BLOCK so the user	*/
/*			   can order packets which may come up out of	*/
/*			   sequence					*/
/* 05/07/98  DSF    08     The size of PACKET_BLOCK is now user-settable*/
/* 05/05/98  DSF    07     Corrected several problems related to 	*/
/*			   receiving frames out of order		*/
/* 04/21/98  DSF    06     Added Time Sync support                      */
/* 08/19/97  APS    05     Added queueing of read IRPs                  */
/* 06/19/97  DSF    04     Added Stats                                  */
/* 07/16/96  DSF    03     Fixed DEBUGERROR1 Macros                     */
/* 07/15/96  DSF    02     Allocate memory from nonpaged system memory  */
/* 05/22/96  DSF    01     Initial Release                              */
/*                                                                      */
/************************************************************************/

#include "ntddk.h"
#include "ntiologc.h"
#include "ndis.h"

#include "debug.h"
#include "frame.h"
#include "osillcnt.h"
#include "osillc.h"

static LONG NdisBuffersInUse;

VOID OsillcCancelRead(PDEVICE_OBJECT DeviceObject, PIRP Irp);

/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  NTSTATUS OsillcRead(PDEVICE_OBJECT DeviceObject, PIRP Irp)
 *
 *  PURPOSE:   Get a packet.
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

NTSTATUS OsillcRead(PDEVICE_OBJECT DeviceObject, PIRP Irp)
  {
  PIO_STACK_LOCATION  IrpSp = IoGetCurrentIrpStackLocation(Irp);
  POPEN_INSTANCE      Open = IrpSp->FileObject->FsContext;
  PNDIS_PACKET        pPacket;
  PNDIS_BUFFER        pBuffer;
  PMDL                pMdl;
  KIRQL   	      cancelIrql;
  KIRQL   	      oldIrql;
  NDIS_STATUS         Status;
  PLIST_ENTRY         pListEntry;
  POSILLC_RESERVED    Reserved;
  PUCHAR              pVirtualMemory;
  UINT                PhysBufferCount, BufferCount;
  UINT                PacketLength, BufferLength, TotalSize;
  ULONG		      NumberOfPackets;


  DEBUGTRACE0("Read");

  Irp->IoStatus.Information = 0;

  //  check if the buffer is big enough
  if (IrpSp->Parameters.Read.Length < sizeof(OSILLC_PACKET_BLOCK))
    {
    Status = STATUS_BUFFER_TOO_SMALL;

    Irp->IoStatus.Status = Status;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    return Status;
    }

  // check if there are any packets already queued
  // if not, just queue this read request
  if ((OsillcReceptionMode != RECEPTION_MODE_FAST) || 
      IsListEmpty (&Open->RcvList))
    {
    // try to get a packet from our list of free ones
    NdisAllocatePacket(&Status, &pPacket, Open->ReadPacketPool);

    if (Status != NDIS_STATUS_SUCCESS)
      {
      DEBUGTRACE0("Read: No free packets");

      Irp->IoStatus.Status = Status;
      IoCompleteRequest(Irp, IO_NO_INCREMENT);

      return Status;
      }

    // save a pointer to the packet itself
    RESERVED(pPacket)->Irp = Irp;

    // mark the IRP as pending
    Status = STATUS_PENDING;
    IoMarkIrpPending(Irp);
    Irp->IoStatus.Status = Status;

    // set the cancel routine
    IoAcquireCancelSpinLock(&cancelIrql);
    IoSetCancelRoutine(Irp, OsillcCancelRead);

    // release the cancel spinlock
    IoReleaseCancelSpinLock(cancelIrql);

    //
    //  put this packet in a list of pending reads;
    //  the receive indication handler will attemp to remove packets
    //  from this list for use in transfer data calls
    //
    ExInterlockedInsertTailList (&Open->ReadIrpList, 
                                 &RESERVED(pPacket)->ListElement,
                                 &Open->ReadQSpinLock);
    }
  else
    {
    POSILLC_PACKET_BLOCK        ReadBlock = MmGetSystemAddressForMdl(Irp->MdlAddress);
    POSILLC_PACKET_DATA         PacketData = ReadBlock->PacketData;
    ULONG   i;


#if JUNK
    KeAcquireSpinLock (&Open->RcvListSpinLock, &oldIrql);
#endif
    NumberOfPackets = 0;

    // otherwise get packets waiting for us
    for (i = 0; i < ReadBlock->NumberOfPackets; i++, PacketData++)
      {
      pListEntry = ExInterlockedRemoveHeadList (&Open->RcvList,
      					        &Open->RcvQSpinLock);

      // if no more packets, just finish up here
      if (pListEntry == NULL)
	break;

      Reserved = CONTAINING_RECORD(pListEntry, OSILLC_RESERVED, ListElement);
      pPacket  = CONTAINING_RECORD(Reserved, NDIS_PACKET, ProtocolReserved);

      // get packet payload size
      NdisQueryPacket (pPacket, &PhysBufferCount, &BufferCount,
	               &pBuffer, &PacketLength);
      NdisQueryBuffer (pBuffer, &pVirtualMemory, &BufferLength);
      pVirtualMemory -= Reserved->HeaderSize;
      TotalSize = Reserved->HeaderSize + Reserved->PacketSize;

      PacketData->Length = TotalSize;
      NdisMoveMappedMemory (PacketData->Data, pVirtualMemory, TotalSize);

      NumberOfPackets++;

      // recycle the frame buffer
      NdisFreeFrame (pVirtualMemory, Open->FramePool);

      // recycle the buffer descriptor
      NdisUnchainBufferAtFront(pPacket, &pBuffer);
      NdisFreeBuffer (pBuffer);

      // recycle the packet
      NdisReinitializePacket (pPacket);
      NdisFreePacket (pPacket);

      NdisBuffersInUse--;
      }

#if JUNK
    KeReleaseSpinLock (&Open->RcvListSpinLock, oldIrql);
#endif

    ReadBlock->NumberOfPackets = NumberOfPackets;
    ReadBlock->SeqNumber = Open->SeqNumber++;

    Status = STATUS_SUCCESS;
    Irp->IoStatus.Status = Status;
    Irp->IoStatus.Information = sizeof(ULONG) +
                                ReadBlock->NumberOfPackets * sizeof(OSILLC_PACKET_DATA);
    IoCompleteRequest (Irp, IO_NO_INCREMENT);
    }

  return Status;
  }

/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  VOID OsillcCancelRead(PDEVICE_OBJECT DeviceObject, PIRP pIrp)
 *
 *  PURPOSE:   Cancels a pending Read Request IPR.
 *
 *  PARMS:     PDEVICE_OBJECT DeviceObject - pointer to device object
 *             PIRP Irp                    - pointer to IRP to be cancelled
 *
 *  RETURNS:   Nothing
 *
 *  NOTES:     The IO Manager calls this function with the Cancel spinlock held.
 *             We must release it!
-*/
/* ---------------------------------------------------------------------*/

VOID OsillcCancelRead (PDEVICE_OBJECT DeviceObject, PIRP Irp)
  {
  PIO_STACK_LOCATION  IrpSp = IoGetCurrentIrpStackLocation(Irp);
  POPEN_INSTANCE      Open = IrpSp->FileObject->FsContext;
  POSILLC_RESERVED    Reserved;
  PNDIS_PACKET        pPacket;
  PLIST_ENTRY         pListEntry;
  KIRQL               oldIrql;
  PIRP                QueuedIrp = NULL;

  DEBUGTRACE0("OsillcCancelRead");

  // if IRP is a pending request, cancel it
  if ( !IsListEmpty(&Open->ReadIrpList))
    {
    // get the queue's spin lock
    KeAcquireSpinLock (&Open->ReadQSpinLock, &oldIrql);

    // pick thru the queue looking for our IRP
    for (pListEntry = Open->ReadIrpList.Flink;
         pListEntry != &Open->ReadIrpList;
         pListEntry = pListEntry->Flink)
      {
      // reconstruct a pointer to the IRP
      Reserved = CONTAINING_RECORD(pListEntry, OSILLC_RESERVED, ListElement);
      pPacket = CONTAINING_RECORD(Reserved, NDIS_PACKET, ProtocolReserved);

      QueuedIrp = RESERVED(pPacket)->Irp;

      // check if we've found our IRP
      if (QueuedIrp == Irp)
	{
	// yes, remove it for our queue
	RemoveEntryList(pListEntry);
	break;
	}
      }

    // release the queue's spin lock
    KeReleaseSpinLock(&Open->ReadQSpinLock, oldIrql);

    // if the IRP is found, cancel it
    if (QueuedIrp)
      {
      // make sure that the cancel routine doesn't get called again for this IRP
      //                      IoSetCancelRoutine(Irp, NULL);

      // release the cancel spinlock before completing the request
      IoReleaseCancelSpinLock (Irp->CancelIrql);

      // complete the request as cancelled
      Irp->IoStatus.Status = STATUS_CANCELLED;
      Irp->IoStatus.Information = 0;
      IoCompleteRequest (Irp, OsillcPriorityBoost);
      }
    }
  }

/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  NDIS_STATUS OsillcReceiveIndicate(NDIS_HANDLE ProtocolBindingContext,
 *                                                                NDIS_HANDLE MacReceiveContext,
 *                                                                PVOID HeaderBuffer,
 *                                                                UINT HeaderBufferSize,
 *                                                                PVOID LookAheadBuffer,
 *                                                                UINT LookaheadBufferSize,
 *                                                                UINT PacketSize)
 *
 *  PURPOSE:   Notification from the bound MAC driver that
 *             a packet data transfer is complete.
 *
 *  PARMS:     NDIS_HANDLE ProtocolBindingContext - binding context
 *             NDIS_HANDLE MacReceiveContext - receive context
 *             PVOID HeaderBuffer            - pointer to header
 *             UINT HeaderBufferSize         - header size in bytes
 *                 PVOID LookAheadBuffer         - pointer to lookahead buffer
 *             UINT LookaheadBufferSize      - lookahead buffer size
 *             UINT PacketSize               - packet size in bytes
 *
 *  RETURNS:   NDIS_STATUS. 
 *
 *  NOTES:
 *  --------------
 *  November, 2002
 *  --------------
 *  To implement the 802.1Q VLAN (Virtual LAN) tagging and the 802.1p
 *  Priority tagging standards a new 802.3 Ethernet (2000 Edition) frame
 *  format was defined.
 *  The 'old' 802.3 frame fields (max length 14+1500=1514):
 *    DA  SA  oL/T  Payload
 *  New 802.3 (2000) frame fields (max length 18+1500=1518):
 *    DA  SA  L/T TCI  oL/T  Payload
 *  where
 *    DA        Dest Address                    6 bytes		Destination MAC
 *    SA        Src Address                     6 bytes		Source MAC
 *    L/T       Len/802.1QTagType               2 bytes		Set to 8100 for tagged MAC frame (802.1Q)
 *    TCI       Tag Control Info                2 bytes:
 *        P       Priority                        3 bits	802.1p priority level 0-7
 *        CFI     Canonical Format Indicator      1 bit		1 if MAC in canonical format (Ethernet uses 0)
 *        VLAN    VLAN Identifier (VID)          12 bits	VLAN ID (0-4095)
 *    oL/T      MAC Client Len/Type		2 bytes		Original 802.3 Len/Type (before insertion of QTag Prefix)
 *    Payload   Payload                         <=1500 bytes	User date or higher protocol info
 *
-*/
/* ---------------------------------------------------------------------*/

NDIS_STATUS OsillcReceiveIndicate (NDIS_HANDLE ProtocolBindingContext,
  NDIS_HANDLE MacReceiveContext,
  PVOID HeaderBuffer,
  UINT HeaderBufferSize,
  PVOID LookAheadBuffer,
  UINT LookaheadBufferSize,
  UINT PacketSize)
  {
  POPEN_INSTANCE  Open = (POPEN_INSTANCE)ProtocolBindingContext;
  PLIST_ENTRY     OsillcListEntry;
  KIRQL           cancelIrql;
  PLIST_ENTRY     pListEntry;
  PNDIS_PACKET    pPacket;
  PNDIS_BUFFER    pBuffer;
  PUCHAR          pFrame = (PUCHAR) LookAheadBuffer;
  PUCHAR          pFrameHdr = (PUCHAR) HeaderBuffer;
  PUCHAR          pVirtualMemory;
  NDIS_STATUS     Status;
  UINT            BytesTransfered;
  UINT            TotalSize;
  BOOLEAN         bGoodFrame;
  LARGE_INTEGER   LargeInteger;
  UINT            i;
  PUCHAR          pLenType;	/* ptr to Len/Type field	*/
  PUCHAR          pLsap;	/* ptr to the LSAPs (DST/SRC)	*/


  DEBUGTRACE0("ReceiveIndicate");

  // check that the header is an Ethernet header size
  if (HeaderBufferSize != ETHERNET_HEADER_LENGTH) 
    {
    DEBUGTRACE0("ReceiveIndicate: NOT_ACCEPTED");
    return NDIS_STATUS_NOT_ACCEPTED;
    }

  // Check for 802.1Q Tagged MAC frames (see desc above)
  // This API makes it tricky to handle 802.1Q tagged frames, because the API
  // stores the Header (pFrameHdr) separately from the Frame (pFrame).
  if (pFrameHdr[12] == 0x81 && pFrameHdr[13] == 0x00)	/* 0x8100 ? */
    {
    pLenType = &pFrame[2];	/* 802.1Q Tagged. Len/Type is 4 bytes later*/
    pLsap = &pFrame[4];
    }
  else
    {
    pLenType = &pFrameHdr[12];	/* not Tagged. Len/Type is here in header*/
    pLsap = &pFrame[0];
    }
  
  bGoodFrame = FALSE;	/* assume packet is bad	*/

  // If Length/Type >= 0x0600, it indicates "type", not "length"
  // (i.e. this is an Ethertype frame).
  if (*pLenType >= 0x06)
    {			/* Ethertype frame. Check EthertypeId filters	*/
    /* If no Ethertype filters configured, pass all frames up */
    if  (OsillcEthertypeIdsCount == 0)
      bGoodFrame = TRUE;
    else
      {
      /* Check all configured Ethertype filters */
      for (i=0; i<OsillcEthertypeIdsCount*2; i+=2)
        {
        /* Compare the Length/Type field of the frame to this EthertypeId filter.*/
        if (pLenType[0] == OsillcEthertypeIdsTable[i] &&
            pLenType[1] == OsillcEthertypeIdsTable[i+1])
          {
          bGoodFrame = TRUE;
          break;
          }
        }
      }
    }			/* end checking EthertypeId filters	*/
  else
    {			/* OSI frame. Check LSAP filters	*/
    /* If no LSAP filters configured, pass all frames up */
    if  (OsillcLsapCount == 0)
      bGoodFrame = TRUE;
    else
      {
      /* Check all configured LSAP filters */
      for (i=0; i<OsillcLsapCount; ++i)
        {
        /* Compare the DST/SRC LSAPs of the frame to this LSAP filter.	*/
        if (pLsap[0] == OsillcLsapTable[i] && pLsap[1] == OsillcLsapTable[i])
          {
          bGoodFrame = TRUE;
          break;
          }
        }
      }
    }			/* end checking LSAP filters	*/

  if (bGoodFrame == FALSE)
    {
    NdisRcvUnknown++;
    DEBUGTRACE0("ReceiveIndicate: NOT_ACCEPTED");
    return NDIS_STATUS_NOT_ACCEPTED;
    }

  // allocate a frame buffer of appropriate size
  TotalSize = HeaderBufferSize + PacketSize;
  NdisAllocateFrame (&Status, &pVirtualMemory, Open->FramePool);

  if (Status != NDIS_STATUS_SUCCESS)
    {
    NdisAllocError++;
    DEBUGERROR0("AllocateMemory failed");
    return (NDIS_STATUS_RESOURCES);
    }

  // allocate a buffer descriptor
  NdisAllocateBuffer (&Status, &pBuffer, Open->BufferPool,
                      pVirtualMemory + HeaderBufferSize, PacketSize);

  if (Status != NDIS_STATUS_SUCCESS)
    {
    NdisAllocError++;
    DEBUGERROR1("AllocateBuffer failed (%x)", Status);
    NdisFreeFrame(pVirtualMemory, Open->FramePool);

    return (NDIS_STATUS_RESOURCES);
    }

  NdisBuffersInUse++;

  // allocate a packet descriptor
  NdisAllocatePacket(&Status, &pPacket, Open->RxPacketPool);
  if (Status != NDIS_STATUS_SUCCESS)
    {
    NdisAllocError++;
    DEBUGERROR1("AllocatePacket failed (%x)", Status);
    NdisFreeFrame(pVirtualMemory, Open->FramePool);
    NdisFreeBuffer(pBuffer);

    return (NDIS_STATUS_RESOURCES);
    }

  // attach the buffer to the packet
  NdisChainBufferAtBack(pPacket, pBuffer);

  // set up reserved fields as required
  RESERVED(pPacket)->HeaderSize = HeaderBufferSize;
  RESERVED(pPacket)->PacketSize = PacketSize;

  // copy the Ethernet header
  NdisMoveMappedMemory (pVirtualMemory, HeaderBuffer, HeaderBufferSize);

  // call the Mac driver to transfer the packet
  NdisTransferData (&Status, Open->AdapterHandle, MacReceiveContext, 0,
                    PacketSize, pPacket, &BytesTransfered);

  // if it didn't pend, call the completion routine now
  if (Status != NDIS_STATUS_PENDING) 
    OsillcTransferDataComplete (Open, pPacket, Status, BytesTransfered);

  return NDIS_STATUS_SUCCESS;
  }

/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  VOID OsillcTransferDataComplete(NDIS_HANDLE ProtocolBindingContext,
 *                                                                     PNDIS_PACKET pPacket,
 *                                             NDIS_STATUS Status)
 *                                                                             UINT BytesTransfered)
 *
 *  PURPOSE:   Notification from the bound MAC driver that
 *             a packet data transfer is complete.
 *
 *  PARMS:     NDIS_HANDLE ProtocolBindingContext - binding context
 *             PNDIS_PACKET pPacket          - pointer to packet
 *             NDIS_STATUS Status            - resulting status
 *             UINT BytesTransfered          - number of bytes transferred
 *
 *  RETURNS:   Nothing. 
 *
 *  NOTES:
 *
-*/
/* ---------------------------------------------------------------------*/

VOID OsillcTransferDataComplete(NDIS_HANDLE ProtocolBindingContext,
  PNDIS_PACKET pPacket, NDIS_STATUS Status,
  UINT BytesTransfered)
  {
  POPEN_INSTANCE      Open = (POPEN_INSTANCE)ProtocolBindingContext;
  PIRP                Irp;
  KIRQL               cancelIrql;
  KIRQL               oldIrql;
  PNDIS_BUFFER        pBuffer;
  PLIST_ENTRY         pListEntry;
  PLIST_ENTRY         pRcvEntry;
  POSILLC_RESERVED    Reserved;
  PIO_STACK_LOCATION  IrpSp;
  POSILLC_PACKET_BLOCK    ReadBlock;
  POSILLC_PACKET_DATA     PacketData;
  PUCHAR              pVirtualMemory;
  UINT                PhysBufferCount, BufferCount;
  UINT                PacketLength, BufferLength, TotalSize;
  ULONG   	      NumberOfPackets;
  ULONG   	      i;


  DEBUGTRACE0("TransferDataComplete");

#if JUNK
  if (OsillcReceptionMode == RECEPTION_MODE_FAST)
    KeAcquireSpinLock (&Open->RcvListSpinLock, &oldIrql);
#endif    

  // put this packet in the back of the list for future user retrieval
  ExInterlockedInsertTailList (&Open->RcvList, 
                               &RESERVED(pPacket)->ListElement,
 	                       &Open->RcvQSpinLock);

  // see if there are any pending Read IRPs that we can satisfy
  while (TRUE)
    {
    pListEntry = ExInterlockedRemoveHeadList (&Open->ReadIrpList, 
                                              &Open->ReadQSpinLock);
    if (pListEntry == NULL)
      break;

    Reserved = CONTAINING_RECORD(pListEntry, OSILLC_RESERVED, ListElement);
    pPacket = CONTAINING_RECORD(Reserved, NDIS_PACKET, ProtocolReserved);

    Irp = RESERVED(pPacket)->Irp;
    IrpSp = IoGetCurrentIrpStackLocation (Irp);

    // acquire the cancel spinlock
    IoAcquireCancelSpinLock(&cancelIrql);

    // clear the cancel routine so that it is not called during completion
    IoSetCancelRoutine (Irp, NULL);

    // release the cancel spinlock
    IoReleaseCancelSpinLock (cancelIrql);

    // get a pointer to the Read Block
    ReadBlock = MmGetSystemAddressForMdl (Irp->MdlAddress);

    RESERVED(pPacket)->Irp = NULL;

    // recycle the packet
    NdisReinitializePacket(pPacket);

    // put the packet on the free queue
    NdisFreePacket(pPacket);

    NdisBuffersInUse--;

    NumberOfPackets = 0;
    PacketData = ReadBlock->PacketData;

    // get packets waiting for us
    for (i = 0; i < ReadBlock->NumberOfPackets; i++, PacketData++)
      {
      pRcvEntry = ExInterlockedRemoveHeadList (&Open->RcvList,
  					       &Open->RcvQSpinLock);

      // if no more packets, just finish up here
      if (pRcvEntry == NULL)
        break;

      Reserved = CONTAINING_RECORD(pRcvEntry, OSILLC_RESERVED, ListElement);
      pPacket  = CONTAINING_RECORD(Reserved, NDIS_PACKET, ProtocolReserved);

      // get packet payload size
      NdisQueryPacket (pPacket, &PhysBufferCount, &BufferCount,
                       &pBuffer, &PacketLength);
      NdisQueryBuffer (pBuffer, &pVirtualMemory, &BufferLength);
      pVirtualMemory -= Reserved->HeaderSize;
      TotalSize = Reserved->HeaderSize + Reserved->PacketSize;

      PacketData->Length = TotalSize;
      NdisMoveMappedMemory (PacketData->Data, pVirtualMemory, TotalSize);

      NumberOfPackets++;

      // recycle the frame buffer
      NdisFreeFrame (pVirtualMemory, Open->FramePool);

      // recycle the buffer descriptor
      NdisUnchainBufferAtFront(pPacket, &pBuffer);
      NdisFreeBuffer (pBuffer);

      // recycle the packet
      NdisReinitializePacket (pPacket);
      NdisFreePacket (pPacket);

      NdisBuffersInUse--;
      }

    ReadBlock->NumberOfPackets = NumberOfPackets;
    ReadBlock->SeqNumber = Open->SeqNumber++;

    Status = STATUS_SUCCESS;
    Irp->IoStatus.Status = Status;
    Irp->IoStatus.Information = sizeof(ULONG) +
                              ReadBlock->NumberOfPackets * sizeof(OSILLC_PACKET_DATA);
    IoCompleteRequest (Irp, OsillcPriorityBoost);

    if (pRcvEntry == NULL)
      break;
    }

  // release receive list spin lock
#if JUNK
  if (OsillcReceptionMode == RECEPTION_MODE_FAST)
    KeReleaseSpinLock (&Open->RcvListSpinLock, oldIrql);
#endif    

  // notify the user of a saved packet (only if using events)
  //
  // Note: we have atleast a header
  //
  if (Open->hNotifyEvent)
    KeSetEvent(Open->pNotifyEvent, (KPRIORITY)1, FALSE);

  // update our counters according to Status
  if (Status != NDIS_STATUS_SUCCESS)
    {
    NdisRcvError++;
    DEBUGERROR1("TransferData failed (%x)", Status);
    }
  else
    NdisRcvOk++;
  }

/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  VOID OsillcReceiveComplete(NDIS_HANDLE ProtocolBindingContext)
 *
 *  PURPOSE:   Notification from the bound MAC driver that receive
 *             is complete.
 *
 *  PARMS:     NDIS_HANDLE ProtocolBindingContext - binding context
 *
 *  RETURNS:   Nothing. 
 *
 *  NOTES:     This is called when one or more packets have been
 *             indicated by the MAC driver.
 *
-*/
/* ---------------------------------------------------------------------*/

VOID OsillcReceiveComplete(NDIS_HANDLE ProtocolBindingContext)
  {
  POPEN_INSTANCE  Open = (POPEN_INSTANCE)ProtocolBindingContext;
  PIRP                    Irp;

  DEBUGTRACE0("ReceiveComplete");

  Irp = Open->SignalIrp;
  Open->SignalIrp = NULL;

  if (Irp)
    {
    NdisRcvInd++;
    Irp->IoStatus.Status = NDIS_STATUS_SUCCESS;
    Irp->IoStatus.Information = 0;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    }
  }
