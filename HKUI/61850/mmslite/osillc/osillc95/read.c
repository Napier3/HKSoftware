//---------------------------------------------------------------------------
//
// File:         read.c
//
// Copyright (c) 1998 - 2002, SISCO Inc. All rights reserved.
//
// Description:  Packet receive management routines.
//
// Author:       A. Shajenko/Stratos Technology, Inc.
//
// History:
// 13-Sep-98     A. Shajenko     Implemented.
// 23-Mar-99     A. Shajenko     Save pointer to pPacket in pFrame 
//                               in OsillcReceiveIndicate().
// 28-Nov-01	JRB (SISCO)	Allow IEC GOOSE packets (LSAP = 0xF5)
// 01-Jan-02    SISCO (EJV)     Added support for cfg of LSAPs in registry
// 15-Nov-02    SISCO (EJV)     Added support for Ethertype filtering.
// 12-Dec-02    SISCO (EJV)     Pass all 8100 frames up if Ethertype filters
//				not configured.
// 12-Dec-02    SISCO (EJV)     Corrected OsillcReceiveIndicate
//
//---------------------------------------------------------------------------

#include "osillc95.h"

//---------------------------------------------------------------------------
// Function:    OsillcRead
//
// Parameters:  POPEN_INSTANCE pOpen -- pointer to open instance
//              PIOCTLPARAMS p       -- pointer to IOCTL request block
//
// Returns:     Return code.
//
// Description: Fetch one or more packets that have arrived from the MAC driver.
//
// Notes:
//
//---------------------------------------------------------------------------
DWORD OsillcRead(POPEN_INSTANCE pOpen, PIOCTLPARAMS p)
  {
PNDIS_PACKET pPacket;
PNDIS_BUFFER pBuffer;
NDIS_STATUS  Status;
PIRP pIrp;
POSILLC_PACKET_BLOCK pReadBlock;
POSILLC_PACKET_DATA  pPacketData;

THREADHANDLE hThread = Get_Cur_Thread_Handle();
DWORD	     dwPriority = Get_Thread_Win32_Pri(hThread, NULL, NULL, NULL);

  *p->dioc_bytesret = 0;

  // validate the output parameters
  if (p->dioc_OutBuf == NULL || p->dioc_cbOutBuf < sizeof(OSILLC_PACKET_BLOCK))
    {
    DEBUGERROR0("OsillcRead: ERROR: buffer too small"); 
    return ERROR_INSUFFICIENT_BUFFER;
    }

  // boost the thread priority to the max, so that the
  // OsillcReceiveIndicate thread doesn't get ahead here
  Set_Thread_Win32_Pri(hThread, 31);

  _disable();

  // if there are no ready packets just queue this read request
  if (IsListEmpty(&pOpen->RcvList))
    {
    _enable();

    // allocate an Irp for the request
    if ((pIrp = OsillcAllocateIrp(&pOpen->IrpPool, TRUE)) == NULL)
      { 
      // reset the thread priority
      Set_Thread_Win32_Pri(hThread, dwPriority);

      DEBUGERROR0("OsillcRead: ERROR: Irp Pool empty"); 
      return ERROR_NO_SYSTEM_RESOURCES;
      }

    // build the Irp -- copy the IOCTL params struct
    NdisMoveMemory(&pIrp->IoctlParms, p, sizeof(IOCTLPARAMS));

    //  try to get an NDIS packet from our list of free ones
    NdisAllocatePacket(&Status, &pPacket, pOpen->PacketPool);
    if (Status != NDIS_STATUS_SUCCESS)
      {
      // reset the thread priority
      Set_Thread_Win32_Pri(hThread, dwPriority);
      OsillcFreeIrp(pIrp, &pOpen->IrpPool, TRUE);

      DEBUGERROR0("OsillcRead: ERROR: no packet buffer");
      return ERROR_NO_SYSTEM_RESOURCES;
      }
    
    // save a pointer to the NDIS packet
    pIrp->pPacket = pPacket;

    // now save a pointer back to the Irp (needed by NdisTransferData)
    RESERVED(pPacket)->pIrp = pIrp;
    RESERVED(pPacket)->pFrame = NULL;

    // lock down the buffers
    pIrp->IoctlParms.dioc_OutBuf   = (PVOID)OsillcPageLock(p->dioc_OutBuf, p->dioc_cbOutBuf);
    pIrp->IoctlParms.dioc_bytesret = (PVOID)OsillcPageLock((PVOID)p->dioc_bytesret, sizeof(DWORD));
    pIrp->IoctlParms.dioc_ovrlp    = (PVOID)OsillcPageLock((PVOID)p->dioc_ovrlp, sizeof(OVERLAPPED));

    pReadBlock  = (POSILLC_PACKET_BLOCK)pIrp->IoctlParms.dioc_OutBuf;
    pPacketData = &pReadBlock->PacketData[0];

    // allocate an NDIS buffer to point to the payload
    NdisAllocateBuffer(&Status, &pBuffer, pOpen->BufferPool, 
		       (PVOID)(pPacketData->Data + ETHERNET_HEADER_LENGTH),
		       sizeof(pPacketData->Data) - ETHERNET_HEADER_LENGTH);

    if (Status != NDIS_STATUS_SUCCESS)
      {
      DEBUGERROR1("OsillcRead: ERROR: no buffer descriptor %x", Status);

      // reset the thread priority
      Set_Thread_Win32_Pri(hThread, dwPriority);

      // recycle the packet
      NdisReinitializePacket(pPacket);

      // put the packet on the free queue
      NdisFreePacket(pPacket);

      // unlock the buffers	
      OsillcPageUnlock(pIrp->IoctlParms.dioc_OutBuf, pIrp->IoctlParms.dioc_cbOutBuf);
      OsillcPageUnlock(pIrp->IoctlParms.dioc_bytesret, sizeof(DWORD));
      OsillcPageUnlock(pIrp->IoctlParms.dioc_ovrlp, sizeof(OVERLAPPED));

      OsillcFreeIrp(pIrp, &pOpen->IrpPool, TRUE);

      return ERROR_NO_SYSTEM_RESOURCES;
      }

    // attach the buffer to the NDIS packet
    NdisChainBufferAtFront(pPacket, pBuffer);

    //
    //  put this Irp in a list of pending reads; the receive indication handler
    //  will attempt to remove packets from this list for use in transfer data calls
    //

    _disable();
    InsertTailList(&pOpen->ReadIrpList, &pIrp->ListEntry);
    _enable();

    // reset the thread priority
    Set_Thread_Win32_Pri(hThread, dwPriority);

    // now return pending status
    return ERROR_IO_PENDING;
    }
  else
    {
    PLIST_ENTRY	pListEntry;
    PUCHAR	pVirtualMemory;
    POVERLAPPED	pOverlap = p->dioc_ovrlp;
    UINT	PhysBufferCount, BufferCount;
    UINT	PacketLength, BufferLength, TotalSize;
    PFRAME	pFrame;
    DWORD	i, dwMaxPackets;

    _enable();

    // reset the thread priority
    Set_Thread_Win32_Pri(hThread, dwPriority);

    pReadBlock = (POSILLC_PACKET_BLOCK)p->dioc_OutBuf;
    pPacketData = pReadBlock->PacketData;

    dwMaxPackets = pReadBlock->NumberOfPackets;
    pReadBlock->NumberOfPackets = 0;
    pReadBlock->SeqNumber = pOpen->SeqNumber++;

    for (i = 0; i < dwMaxPackets; i++, pPacketData++)
      {
      _disable();
      if (IsListEmpty(&pOpen->RcvList))
      	{
	_enable();
	break;
	}

      pListEntry = RemoveHeadList(&pOpen->RcvList);
      _enable();

      pFrame = CONTAINING_RECORD(pListEntry, FRAME, ListEntry);
      pPacket = pFrame->pPacket;

      // get packet payload size
      NdisQueryPacket(pPacket, &PhysBufferCount, &BufferCount,
                      &pBuffer, &PacketLength);
      NdisQueryBuffer(pBuffer, &pVirtualMemory, &BufferLength);
      pVirtualMemory -= pFrame->dwHeaderSize;
      TotalSize = pFrame->dwHeaderSize + pFrame->dwPacketSize;

      pPacketData->Length = pFrame->dwHeaderSize + pFrame->dwPacketSize;
      NdisMoveMappedMemory(pPacketData->Data, pVirtualMemory, pPacketData->Length);

      pReadBlock->NumberOfPackets++;

      // recycle the frame buffer
      OsillcFreeFrame(pFrame, &pOpen->FramePool, TRUE);

      // recycle the buffer descriptor
      NdisUnchainBufferAtFront(pPacket, &pBuffer);
      NdisFreeBuffer(pBuffer);

      // recycle the packet
      NdisReinitializePacket(pPacket);
      NdisFreePacket(pPacket);
      }

    *p->dioc_bytesret = sizeof(pReadBlock->NumberOfPackets) +
    		        (pReadBlock->NumberOfPackets * sizeof(pReadBlock->PacketData[0]));

    DEBUGTRACE1 ("OsillcRead: Complete Seq = %d", 
                 pReadBlock->SeqNumber);

#if 0
    pOverlap->O_InternalHigh = ERROR_SUCCESS;
    VWIN32_DIOCCompletionRoutine(pOverlap->O_Internal);
    return ERROR_IO_PENDING;
#else
    return ERROR_SUCCESS;
#endif
    }
  }

//---------------------------------------------------------------------------
// Function:    OsillcReceiveIndicate
//
// Parameters:  NDIS_HANDLE ProtocolBindingContext -- pointer to binding context
//              NDIS_HANDLE MacReceiveContext      -- MAC's receive context
//              PVOID HeaderBuffer                 -- pointer to header buffer
//              UINT HeaderBufferSize              -- header buffer size
//              PVOID LookaheadBuffer              -- pointer to lookahead buffer
//              INT LookaheadBufferSize            -- lookahead buffer size
//              UINT PacketSize                    -- packet size
//
// Returns:     NDIS_STATUS
//
// Description: Processes packet receive indication.
//
// Notes:
//  --------------
//  November, 2002
//  --------------
//  To implement the 802.1Q VLAN (Virtual LAN) tagging and the 802.1p
//  Priority tagging standards a new 802.3 Ethernet (2000 Edition) frame
//  format was defined.
//  The 'old' 802.3 frame fields (max length 14+1500=1514):
//    DA  SA  oL/T  Payload
//  New 802.3 (2000) frame fields (max length 18+1500=1518):
//    DA  SA  L/T TCI  oL/T  Payload
//  where
//    DA        Dest Address                    6 bytes		Destination MAC
//    SA        Src Address                     6 bytes		Source MAC
//    L/T       Len/802.1QTagType               2 bytes		Set to 8100 for tagged MAC frame (802.1Q)
//    TCI       Tag Control Info                2 bytes:
//        P       Priority                        3 bits	802.1p priority level 0-7
//        CFI     Canonical Format Indicator      1 bit		1 if MAC in canonical format (Ethernet uses 0)
//        VLAN    VLAN Identifier (VID)          12 bits	VLAN ID (0-4095)
//    oL/T      MAC Client Len/Type		2 bytes		Original 802.3 Len/Type (before insertion of QTag Prefix)
//    Payload   Payload                         <=1500 bytes	User date or higher protocol info
//
//---------------------------------------------------------------------------
NDIS_STATUS NDIS_API 
OsillcReceiveIndicate(NDIS_HANDLE ProtocolBindingContext, NDIS_HANDLE MacReceiveContext,
		      PVOID HeaderBuffer, UINT HeaderBufferSize,
		      PVOID LookaheadBuffer, UINT LookaheadBufferSize, 
		      UINT PacketSize)
  {
POPEN_INSTANCE	pOpen = (POPEN_INSTANCE)ProtocolBindingContext;
PNDIS_PACKET	pPacket;
PNDIS_BUFFER	pBuffer;
PUCHAR		pPayload = (PUCHAR)LookaheadBuffer;
PUCHAR		pFrameHdr = (PUCHAR)HeaderBuffer;
NDIS_STATUS	Status;
UINT		SizeToTransfer;
UINT		BytesTransfered = 0;
BOOL		bGoodFrame;
UINT            i;

  // if we're unbinding, don't accept any more packets
  if (pOpen->bUnbinding)
    {
    pOpen->Stats.RcvUnknown++;
    DEBUGTRACE0("OsillcReceiveIndicate: unbinding!");
    return NDIS_STATUS_NOT_ACCEPTED;
    }

  // make sure that the header size is for Ethernet
  if (HeaderBufferSize != ETHERNET_HEADER_LENGTH)
    {
    DEBUGERROR1("OsillcReceiveIndicate: ERROR: bad HeaderBufferSize %d", HeaderBufferSize);
    return NDIS_STATUS_NOT_ACCEPTED;
    }

  bGoodFrame = FALSE;

  // first filter 802.1Q Tagged MAC frames (see desc above)
  if (pFrameHdr[12] == 0x81 && pFrameHdr[13] == 0x00)	/* 0x8100 ? */
    {
    /* frame contains QTag Prefix, if no Ethertype filters configured pass all frames up */
    if  (g_DeviceExtension->EthertypeIdsCount == 0)
      bGoodFrame = TRUE;
    else
      {
      /* check for configured Ethertypes */
      for (i=0; i<g_DeviceExtension->EthertypeIdsCount*2; ++i, ++i)
        {
        // 2 & 3 byte in the pFrame is the oL/T (original Length/Ethertype) field
        if (pPayload[2] == g_DeviceExtension->EthertypeIdsTable[i] &&
            pPayload[3] == g_DeviceExtension->EthertypeIdsTable[i+1])
          {
          bGoodFrame = TRUE;
          break;
          }
        }
      }
#if 0
    // use if 'normal' OSI frames need to be 802.1Q Tagged MAC frames (VLAN stuff)
    // bGoodFrame=FALSE only if EthertypeIdsCount>0 (Ethertype filters configured)
    if (bGoodFrame == FALSE)
      {
      USHORT frameLen = (((USHORT)pPayload[2])<<8) + (USHORT)pPayload[3];
      // if valid length then check if OSI frames
      if (frameLen <= (USHORT) ETHERNET_DATA_LENGTH)
        {
        // accept only frames for the OSI, or other configured LSAPs
        for (i=0; i<g_DeviceExtension->LsapCount; ++i)
          {
          if (pPayload[4] == g_DeviceExtension->LsapTable[i] &&
              pPayload[5] == g_DeviceExtension->LsapTable[i])
            {
            bGoodFrame = TRUE;
            break;
            }
	  }
        }
      }
#endif /* 0 */
    }
  else
    {
    // Old type Ethernet frame
    // accept only frames for the OSI, or other configured LSAPs
    for (i=0; i<g_DeviceExtension->LsapCount; ++i)
      {
      if (pPayload[0] == g_DeviceExtension->LsapTable[i] &&
          pPayload[1] == g_DeviceExtension->LsapTable[i])
        {
        bGoodFrame = TRUE;
        break;
        }
      }
    }

  if (!bGoodFrame)
    {
    pOpen->Stats.RcvUnknown++;
    DEBUGTRACE2("OsillcReceiveIndicate: frame not recognized (%x %x)", pPayload[0], pPayload[1]);
    return NDIS_STATUS_NOT_ACCEPTED;
    }

  // see if there are any pending Read IRPs that we can satisfy
  _disable();
  if (!IsListEmpty(&pOpen->ReadIrpList))
    {
    PLIST_ENTRY		pListEntry;
    PIRP		pIrp;
    POSILLC_PACKET_BLOCK	pReadBlock;

    DEBUGTRACE0("OsillcReceiveIndicate: Read IRP List not empty");

    // get the next waiting read IRP
    pListEntry = RemoveHeadList(&pOpen->ReadIrpList);
    _enable();

    // reconstruct the IRP
    pIrp = CONTAINING_RECORD(pListEntry, IRP, ListEntry);
    pPacket = pIrp->pPacket;

    // get a pointer to the Read Block
    pReadBlock = (POSILLC_PACKET_BLOCK)pIrp->IoctlParms.dioc_OutBuf;
    pReadBlock->NumberOfPackets = 1;
    pReadBlock->PacketData[0].Length = HeaderBufferSize;

    // copy the Ethernet header into the first Read frame buffer
    NdisMoveMappedMemory(pReadBlock->PacketData[0].Data, HeaderBuffer,
		         HeaderBufferSize);

    // calculate out how much to transfer
    if (PacketSize <= (sizeof(pReadBlock->PacketData[0].Data) - HeaderBufferSize))
      SizeToTransfer = PacketSize;
    else
      SizeToTransfer = (sizeof(pReadBlock->PacketData[0].Data) - HeaderBufferSize);
    pReadBlock->PacketData[0].Length += SizeToTransfer;

#if 0
    // allocate an NDIS buffer to point to the payload
    NdisAllocateBuffer(&Status, &pBuffer, pOpen->BufferPool, 
                       (PCHAR) pReadBlock->PacketData[0].Data + HeaderBufferSize,
		       SizeToTransfer);

    if (Status != NDIS_STATUS_SUCCESS)
      {
      DEBUGERROR1("OsillcRead: ERROR: no buffer descriptor %x", Status);

      // recycle the packet
      NdisReinitializePacket(pPacket);

      // put the packet on the free queue
      NdisFreePacket(pPacket);

      // unlock the buffers	
      OsillcPageUnlock(pIrp->IoctlParms.dioc_OutBuf, pIrp->IoctlParms.dioc_cbOutBuf);
      OsillcPageUnlock(pIrp->IoctlParms.dioc_bytesret, sizeof(DWORD));
      OsillcPageUnlock(pIrp->IoctlParms.dioc_ovrlp, sizeof(OVERLAPPED));

      OsillcFreeIrp(pIrp, &pOpen->IrpPool, TRUE);

      return ERROR_NO_SYSTEM_RESOURCES;
      }

    // attach the buffer to the NDIS packet
    NdisChainBufferAtFront(pPacket, pBuffer);
#endif

    // call the Mac driver to transfer the rest of the packet
    NdisTransferData(&Status, pOpen->AdapterHandle, MacReceiveContext, 
                     0, SizeToTransfer, pPacket, 
		     &BytesTransfered);

    DEBUGTRACE1("OsillcReceiveIndicate: NdisTransferData status = %x", Status);

    //  if it didn't pend, call the completion routine now
    if (Status != NDIS_STATUS_PENDING)
      OsillcTransferDataComplete(pOpen, pPacket, Status, BytesTransfered);
    }
  else
    {
    PFRAME	pFrame;

    _enable();

    DEBUGTRACE0("OsillcReceiveIndicate: Read IRP List empty");

    // allocate a frame buffer
    pFrame = OsillcAllocateFrame(&pOpen->FramePool, TRUE);

    if (pFrame == NULL)
      {
      pOpen->Stats.AllocError++;
      DEBUGERROR0("AllocateMemory failed");
      return NDIS_STATUS_RESOURCES;
      }

    // calculate out how much to transfer
    if (PacketSize <= (pFrame->dwFrameSize - HeaderBufferSize))
      SizeToTransfer = PacketSize;
    else
      SizeToTransfer = (pFrame->dwFrameSize - HeaderBufferSize);

    // allocate an NDIS buffer descriptor
    NdisAllocateBuffer(&Status, &pBuffer, pOpen->BufferPool,
    		       pFrame->Data + HeaderBufferSize, SizeToTransfer);

    if (Status != NDIS_STATUS_SUCCESS)
      {
      pOpen->Stats.AllocError++;
      DEBUGERROR1("AllocateBuffer failed (%x)", Status);
      OsillcFreeFrame(pFrame, &pOpen->FramePool, TRUE);

      return NDIS_STATUS_RESOURCES;
      }

    // allocate an NDIS packet descriptor
    NdisAllocatePacket(&Status, &pPacket, pOpen->PacketPool);
    if (Status != NDIS_STATUS_SUCCESS)
      {
      pOpen->Stats.AllocError++;
      DEBUGERROR1("AllocatePacket failed (%x)", Status);
      OsillcFreeFrame(pFrame, &pOpen->FramePool, TRUE);
      NdisFreeBuffer(pBuffer);

      return NDIS_STATUS_RESOURCES;
      }
  
    // clear the pointer to an Irp because we don't
    // have an IRP associated with this NDIS packet
    RESERVED(pPacket)->pIrp = NULL;
    RESERVED(pPacket)->pFrame = pFrame;
    pFrame->pPacket = pPacket;

    // set up frame header fields as required
    pFrame->dwHeaderSize = HeaderBufferSize;
    pFrame->dwPacketSize = SizeToTransfer;

    // attach the buffer to the packet
    NdisChainBufferAtBack(pPacket, pBuffer);
 
    // copy the Ethernet header
    NdisMoveMappedMemory(pFrame->Data, HeaderBuffer, HeaderBufferSize);

    // call the Mac driver to transfer the rest of the packet
    NdisTransferData(&Status, pOpen->AdapterHandle, MacReceiveContext, 0,
		     SizeToTransfer, pPacket, &BytesTransfered);

    DEBUGTRACE1("OsillcReceiveIndicate: NdisTransferData status = %x", Status);

    // if it didn't pend, call the completion routine now
    if (Status != NDIS_STATUS_PENDING) 
      OsillcTransferDataComplete(pOpen, pPacket, Status, BytesTransfered);
    }

  // always return success since we accepted the packet
  return NDIS_STATUS_SUCCESS;
  }

//---------------------------------------------------------------------------
// Function:    OsillcTransferDataComplete
//
// Parameters:  NDIS_HANDLE ProtocolBindingContext -- pointer to binding context
//              PNDIS_PACKET pPacket               -- pointer to packet block
//              NDIS_STATUS Status                 -- status from NdisTransferData()
//              UINT BytesTransfered               -- number of bytes transfered
//
// Returns:     Return code.
//
// Description: Processes transfer data completion.
//
// Notes:
//
//---------------------------------------------------------------------------
VOID NDIS_API OsillcTransferDataComplete(NDIS_HANDLE ProtocolBindingContext,
					 PNDIS_PACKET pPacket, NDIS_STATUS Status,
					 UINT BytesTransfered)
  {
POPEN_INSTANCE	pOpen = (POPEN_INSTANCE)ProtocolBindingContext;
PIRP		pIrp = RESERVED(pPacket)->pIrp;
PFRAME		pFrame = RESERVED(pPacket)->pFrame;

  DEBUGTRACE1("OsillcTransferDataComplete: Status = %x", Status);

  // check if there is an IRP associated with the packet
  if (pIrp != NULL)
    {
    PIOCTLPARAMS		p = &pIrp->IoctlParms;
    POVERLAPPED			pOverlap = p->dioc_ovrlp;
    PNDIS_BUFFER		pBuffer;
    POSILLC_PACKET_BLOCK	pReadBlock = (POSILLC_PACKET_BLOCK)p->dioc_OutBuf;

    DEBUGTRACE0("OsillcTransferDataComplete: pIrp != NULL");

    // free the buffer descriptor
    NdisUnchainBufferAtFront(pPacket, &pBuffer);
		
    if (pBuffer)
      NdisFreeBuffer(pBuffer);

    // if we're closing, don't return any packet
    if (Status == NDIS_STATUS_CLOSING)
      {
      DEBUGTRACE0("OsillcTransferDataComplete: Closing");

      *p->dioc_bytesret = 0;
      pReadBlock->NumberOfPackets = 0;
      pOverlap->O_InternalHigh = ERROR_OPERATION_ABORTED;
      }
    else
      {
      // set total bytes returned
      BytesTransfered += ETHERNET_HEADER_LENGTH;
      *p->dioc_bytesret = 
      	sizeof(pReadBlock->NumberOfPackets) + sizeof(pReadBlock->PacketData[0]);

      pReadBlock->PacketData[0].Length = BytesTransfered;
      pOverlap->O_InternalHigh = ERROR_SUCCESS;
      }

    //
    // the internal member of overlapped structure contains a pointer to
    // the event structure that will be signalled, resuming the execution
    // of the waitng GetOverlappedResult call.
    //

    pReadBlock->SeqNumber = pOpen->SeqNumber++;
    DEBUGTRACE1 ("OsillcTransferDataComplete: Complete Seq = %d", 
                 pReadBlock->SeqNumber);
    VWIN32_DIOCCompletionRoutine(pOverlap->O_Internal);

    // unlock the buffers   
    OsillcPageUnlock(p->dioc_OutBuf, p->dioc_cbOutBuf);
    OsillcPageUnlock(p->dioc_bytesret, sizeof(DWORD));
    OsillcPageUnlock(p->dioc_ovrlp, sizeof(OVERLAPPED));

    // recycle the packet
    NdisReinitializePacket(pPacket);

    // put the packet back on the free list
    NdisFreePacket(pPacket);

    // return IRP item to the IRP pool
    OsillcFreeIrp(pIrp, &pOpen->IrpPool, TRUE);
    }
  else if (pFrame != NULL)	// otherwise just save the frame in the received list
    {
    DEBUGTRACE0("OsillcTransferDataComplete: pIrp = NULL");

    _disable();
    InsertTailList(&pOpen->RcvList, &pFrame->ListEntry);
    _enable();
    }

  // update our stats
  if (Status == NDIS_STATUS_SUCCESS)
    pOpen->Stats.RcvOk++;
  else
    pOpen->Stats.RcvError++;
  }

//---------------------------------------------------------------------------
// Function:    OsillcReceiveComplete
//
// Parameters:  NDIS_HANDLE ProtocolBindingContext -- pointer to binding context
//
// Returns:     Nothing.
//
// Description: Processes receive completion indication.
//
// Notes:
//
//---------------------------------------------------------------------------
VOID NDIS_API OsillcReceiveComplete(NDIS_HANDLE ProtocolBindingContext)
  {
  POPEN_INSTANCE pOpen = (POPEN_INSTANCE)ProtocolBindingContext;

  DEBUGTRACE0("OsillcReceiveComplete: entry...");
  }

