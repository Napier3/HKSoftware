//---------------------------------------------------------------------------
//
// File:         write.c
//
// Copyright (c) 1998 SISCO, Inc. All rights reserved.
//
// Description:  Packet send routines.
//
// Author:       A. Shajenko/Stratos Technology, Inc.
//
// History:
// 13-Sep-98     A. Shajenko     Implemented.
// 14-Feb-00     D. Farberov	 Don't set bytesret in OsillcSendComplete
//
//---------------------------------------------------------------------------

#include "osillc95.h"

//---------------------------------------------------------------------------
// Function:    OsillcWrite
//
// Parameters:  POPEN_INSTANCE pOpen -- pointer to open instance
//              PIOCTLPARAMS p       -- pointer to IOCTL request block
//
// Returns:     Return code.
//
// Description: Send packet down to MAC driver.
//
// Notes:
//
//---------------------------------------------------------------------------
DWORD OsillcWrite(POPEN_INSTANCE pOpen, PIOCTLPARAMS p)
{
	PNDIS_PACKET    pPacket;
	PNDIS_BUFFER    pBuffer;
	PIRP			pIrp = NULL;
	NDIS_STATUS     Status;

	*p->dioc_bytesret = 0;

	// validate the input and/or output parameters
	if (p->dioc_InBuf == NULL || p->dioc_cbInBuf < ETHERNET_HEADER_LENGTH)
	{
		DEBUGERROR0("OsillcWrite: ERROR: invalid buffer length"); 
		return ERROR_INSUFFICIENT_BUFFER;
	}
	
	// allocate an Irp for the request
	if ((pIrp = OsillcAllocateIrp(&pOpen->IrpPool, TRUE)) == NULL)
	{ 
		DEBUGERROR0("OsillcWrite: ERROR: Irp Pool empty"); 
		return ERROR_NO_SYSTEM_RESOURCES;
	}

	// build the Irp
	NdisMoveMemory(&pIrp->IoctlParms, p, sizeof(IOCTLPARAMS));

	//  try to get a packet from our list of free ones
    NdisAllocatePacket(&Status, &pPacket, pOpen->PacketPool);
    if (Status != NDIS_STATUS_SUCCESS)
	{
		DEBUGERROR0("OsillcWrite: ERROR: no packet buffer");
		OsillcFreeIrp(pIrp, &pOpen->IrpPool, TRUE);
		return ERROR_NO_SYSTEM_RESOURCES;
    }
    
	// save a pointer to the Irp; we'll let NDIS
	// and the MAC do the queueing of the IRP with the packet
	RESERVED(pPacket)->pIrp = pIrp;
//	*(PIRP *)(pPacket->ProtocolReserved) = pIrp;

	// lock down the buffers
	pIrp->IoctlParms.dioc_InBuf    = (PVOID)OsillcPageLock(p->dioc_InBuf, p->dioc_cbInBuf);
	pIrp->IoctlParms.dioc_bytesret = (PVOID)OsillcPageLock((PVOID)p->dioc_bytesret, sizeof(DWORD));
	pIrp->IoctlParms.dioc_ovrlp    = (PVOID)OsillcPageLock((PVOID)p->dioc_ovrlp, sizeof(OVERLAPPED));

    NdisAllocateBuffer(&Status, &pBuffer, pOpen->BufferPool, (PVOID)pIrp->IoctlParms.dioc_InBuf,
					   pIrp->IoctlParms.dioc_cbInBuf);

    if (Status != NDIS_STATUS_SUCCESS)
	{
		DEBUGERROR1("OsillcWrite: ERROR: no buffer descriptor %x", Status);

		// recycle the packet
		NdisReinitializePacket(pPacket);

		// put the packet on the free queue
		NdisFreePacket(pPacket);

		// unlock the buffers	
		OsillcPageUnlock(pIrp->IoctlParms.dioc_InBuf, pIrp->IoctlParms.dioc_cbInBuf);
		OsillcPageUnlock(pIrp->IoctlParms.dioc_bytesret, sizeof(DWORD));
		OsillcPageUnlock(pIrp->IoctlParms.dioc_ovrlp, sizeof(OVERLAPPED));

		OsillcFreeIrp(pIrp, &pOpen->IrpPool, TRUE);

		return ERROR_NO_SYSTEM_RESOURCES;
	}

	// attach the buffer to the NDIS packet
    NdisChainBufferAtFront(pPacket, pBuffer);

	// finally send the packet down
    NdisSend(&Status, pOpen->AdapterHandle, pPacket);
		
	DEBUGTRACE1("OsillcWrite: NdisSend status = %x", Status);

    if (Status != NDIS_STATUS_PENDING)
	{
        // send didn't pend so call the completion handler now
        OsillcSendComplete(pOpen, pPacket, Status);
	}

	// always return pending status
    return ERROR_IO_PENDING;
}

//---------------------------------------------------------------------------
// Function:    OsillcSendComplete
//
// Parameters:  NDIS_HANDLE ProtocolBindingContext -- binding context
//              PNDIS_PACKET pPacket -- pointer to packet
//              NDIS_STATUS Status   -- status
//
// Returns:     Nothing
//
// Description: Called to handle send completion.
//
// Notes:
//
//---------------------------------------------------------------------------
VOID NDIS_API OsillcSendComplete(NDIS_HANDLE ProtocolBindingContext,
                                 PNDIS_PACKET pPacket, NDIS_STATUS Status)
{
	POPEN_INSTANCE	pOpen = (POPEN_INSTANCE)ProtocolBindingContext;
//	PIRP			pIrp = *(PIRP *)pPacket->ProtocolReserved;
	PIRP			pIrp = RESERVED(pPacket)->pIrp;
	PIOCTLPARAMS	p = &pIrp->IoctlParms;
	POVERLAPPED		pOverlap = pIrp->IoctlParms.dioc_ovrlp;
    PNDIS_BUFFER	pBuffer;

	DEBUGTRACE1("OsillcSendComplete: Status = %x", Status);

	if (Status != NDIS_STATUS_SUCCESS)
	{
		pOpen->Stats.XmitError++;
		DEBUGERROR1("OsillcSendComplete: failed with Status = %x", Status);
	}
	else
		pOpen->Stats.XmitOk++;

	// free buffer descriptor
    NdisUnchainBufferAtFront(pPacket, &pBuffer);
	
    if (pBuffer)
        NdisFreeBuffer(pBuffer);

    // return status
    pOverlap->O_InternalHigh = Status;

	//
    // the internal member of overlapped structure contains a pointer 
    // to the event structure that will be signalled, resuming the 
    // execution of the waiting GetOverlappedResult call.
    //
	VWIN32_DIOCCompletionRoutine(pOverlap->O_Internal);

	// unlock the buffers	
	OsillcPageUnlock(p->dioc_InBuf, p->dioc_cbInBuf);
	OsillcPageUnlock(p->dioc_bytesret, sizeof(DWORD));
	OsillcPageUnlock(p->dioc_ovrlp, sizeof(OVERLAPPED));

	// recycle the packet
	NdisReinitializePacket(pPacket);

	// put the packet back on the free list
	NdisFreePacket(pPacket);

	// return IRP item to the IRP pool
	OsillcFreeIrp(pIrp, &pOpen->IrpPool, TRUE);
}
