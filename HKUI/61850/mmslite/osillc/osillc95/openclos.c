//---------------------------------------------------------------------------
//
// File:         openclos.c
//
// Copyright (c) 1998 SISCO, Inc. All rights reserved.
//
// Description:  MAC bind & unbind routines.
//
// Author:       A. Shajenko/Stratos Technology, Inc.
//
// History:
// 13-Sep-98     A. Shajenko     Implemented.
//
//---------------------------------------------------------------------------

#include "osillc95.h"

//---------------------------------------------------------------------------
// Function:    OsillcOpenAdapter
//
// Parameters:  POPEN_INSTANCE pOpen -- pointer to open instance
//              PIOCTLPARAMS p       -- pointer to IOCTL request block
//
// Returns:     Return code.
//
// Description: Binds this driver to a MAC driver.
//
// Notes:
//
//---------------------------------------------------------------------------
DWORD OsillcOpenAdapter(POPEN_INSTANCE pOpen, PIOCTLPARAMS p)
{
	NDIS_STATUS	OpenStatus, ErrorStatus, AllocStatus;
	PIRP		pIrp;
	NDIS_STRING	AdapterName = NDIS_STRING_CONST("0000");
    UINT		i;

    PWRAPPER_PROTOCOL_BLOCK         pWPBlock;
    PNDIS_PROTOCOL_CHARACTERISTICS  pNPChar;

	// validate input parameters
	if (p->dioc_InBuf == NULL || p->dioc_cbInBuf < 5)
	{
		DEBUGERROR0("OsillcOpenAdapter: input buffer too small.");
		return ERROR_INSUFFICIENT_BUFFER;
	}

	// allocate an open instance object
	AllocStatus = NdisAllocateMemory((PVOID *)&pOpen, sizeof(OPEN_INSTANCE), 0, -1);
	if (pOpen == NULL)
	{
		// not enough memory
		DEBUGERROR0("OsillcOpenAdapter: error: no memory for Open"); 
		return ERROR_NO_SYSTEM_RESOURCES;
	}

	NdisZeroMemory((PUCHAR)pOpen, sizeof(OPEN_INSTANCE));
	pOpen->hDevice = p->dioc_hDevice;
	pOpen->dwProcessId = p->dioc_ppdb;

	DEBUGTRACE2("OsillcOpenAdapter: hDevice=0x%08X, dwProcessId=0x%08X.", 
				pOpen->hDevice, pOpen->dwProcessId);

	if ( !OsillcAllocateIrpPool(&pOpen->IrpPool, OSILLC_MAX_IRPS))
	{
		// not enough memory
		DEBUGERROR0("OsillcOpenAdapter: error: no memory for Open"); 
		NdisFreeMemory((PVOID)pOpen, sizeof(OPEN_INSTANCE), 0);
		return ERROR_NO_SYSTEM_RESOURCES;
	}

	pOpen->bBound = FALSE;
	pOpen->bUnbinding = FALSE;
	pOpen->bClosing = FALSE;

	// now try to bind with the specified MAC (four char string) 
    strncpy(AdapterName.Buffer, (PUCHAR)p->dioc_InBuf, 5);

	// allocate a frame pool
	if ( !OsillcAllocateFramePool(&pOpen->FramePool, g_DeviceExtension->dwNumberFrames,
								  ETHERNET_PACKET_LENGTH))
	{
		DEBUGERROR0("OsillcOpenAdapter: can't allocate frame pool.");
		OsillcFreeIrpPool(&pOpen->IrpPool);
		NdisFreeMemory((PVOID)pOpen, sizeof(OPEN_INSTANCE), 0);
        return ERROR_NO_SYSTEM_RESOURCES;
	}

	pOpen->MediumArray[0] = NdisMedium802_3;
	pOpen->MediumArraySize = 1;

	// save Binding Context
	pOpen->BindAdapterContext = g_DeviceExtension->NdisProtocolHandle;

    // allocate a packet pool for receive packets
    NdisAllocatePacketPool(&AllocStatus,  &pOpen->PacketPool, g_DeviceExtension->dwNumberBuffers,
                           sizeof(PACKET_RESERVED));

    if (AllocStatus != NDIS_STATUS_SUCCESS)
	{
        // not enough memory
        DEBUGERROR0("OsillcOpenAdapter: ERROR: no memory for Packet Pool."); 
		OsillcFreeFramePool(&pOpen->FramePool);
		OsillcFreeIrpPool(&pOpen->IrpPool);
		NdisFreeMemory((PVOID)pOpen, sizeof(OPEN_INSTANCE), 0);
        return ERROR_NO_SYSTEM_RESOURCES;
    }

	// Allocate a buffer pool for our xmit and receive buffers
    NdisAllocateBufferPool(&AllocStatus, &pOpen->BufferPool, g_DeviceExtension->dwNumberBuffers);

    if (AllocStatus != NDIS_STATUS_SUCCESS)
	{
        // not enough memory
        DEBUGERROR0("OsillcOpenAdapter: ERROR: no memory for Buffer Pool."); 
		NdisFreePacketPool(pOpen->PacketPool);
		OsillcFreeFramePool(&pOpen->FramePool);
		OsillcFreeIrpPool(&pOpen->IrpPool);
		NdisFreeMemory((PVOID)pOpen, sizeof(OPEN_INSTANCE), 0);
        return ERROR_NO_SYSTEM_RESOURCES;
    }

    //  list to hold irp's that want to reset the adapter
    InitializeListHead(&pOpen->ResetIrpList);

    //  Initialize list for holding pending read requests
    InitializeListHead(&pOpen->ReadIrpList);

    //  Initialize list for holding received packets
    InitializeListHead(&pOpen->RcvList);

    //  Initialize the request list
    InitializeListHead(&pOpen->RequestIrpList);

	// clear the stats
	NdisZeroMemory(&pOpen->Stats, sizeof(pOpen->Stats));

	// allocate an Irp for the request
	if ((pIrp = OsillcAllocateIrp(&pOpen->IrpPool, TRUE)) == NULL)
	{ 
        // not enough memory
		DEBUGERROR0("OsillcOpenAdapter: ERROR: Irp Pool empty"); 
		NdisFreeBufferPool(pOpen->BufferPool);
		NdisFreePacketPool(pOpen->PacketPool);
		OsillcFreeFramePool(&pOpen->FramePool);
		OsillcFreeIrpPool(&pOpen->IrpPool);
		NdisFreeMemory((PVOID)pOpen, sizeof(OPEN_INSTANCE), 0);
		return ERROR_NO_SYSTEM_RESOURCES;
	}

	// build the Irp
	pOpen->pPendingIrp = pIrp;
	NdisMoveMemory(&pIrp->IoctlParms, p, sizeof(IOCTLPARAMS));

	// lock down the necessary buffers
	pIrp->IoctlParms.dioc_bytesret = (PVOID)OsillcPageLock((PVOID)p->dioc_bytesret, sizeof(DWORD));
	pIrp->IoctlParms.dioc_ovrlp    = (PVOID)OsillcPageLock((PVOID)p->dioc_ovrlp, sizeof(OVERLAPPED));

    // open and bind to the MAC
    NdisOpenAdapter(&OpenStatus, &ErrorStatus, &pOpen->AdapterHandle, &pOpen->Medium,
                    pOpen->MediumArray, pOpen->MediumArraySize, pOpen->BindAdapterContext,
					pOpen, &AdapterName, 0, NULL);

	DEBUGTRACE2("OsillcOpenAdapter: NdisOpenAdapter open=%x, error=%x", OpenStatus, ErrorStatus);

	//  test for protocol name and adapter name
	pWPBlock = ((PWRAPPER_OPEN_BLOCK)(pOpen->AdapterHandle))->ProtocolHandle;
	pNPChar  = &pWPBlock->ProtocolCharacteristics;

//	DEBUGTRACE1("Protocol                      : %s",  pNPChar->Name.Buffer);
	DEBUGTRACE1("Protocol Handle               : %lx", g_DeviceExtension->NdisProtocolHandle);
	DEBUGTRACE1("PWRAPPER_OPEN_BLOCK           : %lx", pOpen->AdapterHandle);
	DEBUGTRACE1("PWRAPPER_PROTOCOL_BLOCK       : %lx", pWPBlock);
	DEBUGTRACE1("NDIS_PROTOCOL_CHARACTERISTICS : %lx", pNPChar);
//	DEBUGTRACE1("Name                          : %lx", &pNPChar->Name);
	DEBUGTRACE1("Adapter Name                  : %s",  AdapterName.Buffer);

    if (OpenStatus == NDIS_STATUS_SUCCESS)
        ErrorStatus = NDIS_STATUS_SUCCESS;

    if (OpenStatus != NDIS_STATUS_PENDING)
        OsillcOpenAdapterComplete(pOpen, OpenStatus, ErrorStatus);
		
	// always return pending status
	return ERROR_IO_PENDING;
}

//---------------------------------------------------------------------------
// Function:    OsillcOpenAdapterComplete
//
// Parameters:  NDIS_HANDLE ProtocolBindingContext -- pointer to binding context
//              NDIS_STATUS OpenStatus             -- status from NdisOpenAdapter()
//              NDIS_STATUS ErrorStatus            -- status after NdisOpenAdapter()
//
// Returns:     Nothing.
//
// Description: Processes a bind completion.
//
// Notes:
//
//---------------------------------------------------------------------------
VOID NDIS_API OsillcOpenAdapterComplete(NDIS_HANDLE ProtocolBindingContext,
										NDIS_STATUS OpenStatus, NDIS_STATUS ErrorStatus)
{
    POPEN_INSTANCE	pOpen = (POPEN_INSTANCE)ProtocolBindingContext;
	PIRP			pIrp = pOpen->pPendingIrp;
	PIOCTLPARAMS	p = &pIrp->IoctlParms;
	POVERLAPPED		pOverlap = pIrp->IoctlParms.dioc_ovrlp;

	DEBUGTRACE1("OsillcOpenAdapterComplete: entry status = %x", OpenStatus);

	// save the completion status
	pOpen->Status = OpenStatus;

	//
    // If the binding is unsuccessful then we deallocate data structures in 
    // preparation for unloading
	//
    if (OpenStatus != NDIS_STATUS_SUCCESS)
	{
		DEBUGERROR0("OsillcOpenAdapterComplete: ERROR: could not bind");

		NdisFreeBufferPool(pOpen->BufferPool);
		NdisFreePacketPool(pOpen->PacketPool);
		OsillcFreeFramePool(&pOpen->FramePool);
		OsillcFreeIrpPool(&pOpen->IrpPool);
		NdisFreeMemory((PVOID)pOpen, sizeof(OPEN_INSTANCE), 0);
	}
	else
	{
		pOpen->bBound = TRUE;

		// now put the open item onto the global open list
		_disable();
		InsertTailList(&g_DeviceExtension->OpenList, &pOpen->ListEntry);
		_enable();

		DEBUGTRACE1("OsillcOpenAdapterComplete: queued open item 0x%08X", pOpen);

		++g_DeviceExtension->dwOpenCount;
	}

	// return the resulting status
	*p->dioc_bytesret = 5;
	pOverlap->O_InternalHigh = 
		(OpenStatus == NDIS_STATUS_SUCCESS) ? ERROR_SUCCESS : ERROR_CONNECTION_REFUSED;

	//
    // the internal member of overlapped structure contains a pointer 
    // to the event structure that will be signalled, resuming the 
    // execution of the waiting GetOverlappedResult call.
    //
	VWIN32_DIOCCompletionRoutine(pOverlap->O_Internal);

	// unlock the buffers	
	OsillcPageUnlock(p->dioc_bytesret, sizeof(DWORD));
	OsillcPageUnlock(p->dioc_ovrlp, sizeof(OVERLAPPED));

	// return IRP item to the IRP pool
	OsillcFreeIrp(pIrp, &pOpen->IrpPool, TRUE);
}

//---------------------------------------------------------------------------
// Function:    OsillcCloseAdapter
//
// Parameters:  POPEN_INSTANCE pOpen -- pointer to binding context
//              PIOCTLPARAMS p       -- pointer to IOCTL request
//
// Returns:     Return code.
//
// Description: Unbinds this driver from a bound MAC driver.
//
// Notes:       This does IOCTL_OSILLC_UNBIND processing only!.
//
//---------------------------------------------------------------------------
DWORD OsillcCloseAdapter(POPEN_INSTANCE pOpen, PIOCTLPARAMS p)
{
	PIRP			pIrp;
	NDIS_STATUS		Status;

	DEBUGTRACE0("OsillcCloseAdapter: entry...");

	// allocate an Irp for the request
	if ((pIrp = OsillcAllocateIrp(&pOpen->IrpPool, TRUE)) == NULL)
	{ 
		DEBUGERROR0("OsillcCloseAdapter: ERROR: Irp Pool empty"); 
		_disable();
		pOpen->bUnbinding = FALSE;
		_enable();
		return ERROR_NO_SYSTEM_RESOURCES;
	}

	pOpen->bUnbinding = TRUE;

	// build the Irp
	pOpen->pPendingIrp = pIrp;
	NdisMoveMemory(&pIrp->IoctlParms, p, sizeof(IOCTLPARAMS));

	// lock down the necessary buffers
	pIrp->IoctlParms.dioc_bytesret = (PVOID)OsillcPageLock((PVOID)p->dioc_bytesret, sizeof(DWORD));
	pIrp->IoctlParms.dioc_ovrlp    = (PVOID)OsillcPageLock((PVOID)p->dioc_ovrlp, sizeof(OVERLAPPED));

	// close the adapter
	NdisCloseAdapter(&Status, pOpen->AdapterHandle);

	DEBUGTRACE1("OsillcCloseAdapter: NdisCloseAdapter status = %x", Status);

	// save status returned from NdisCloseAdapter for completion routine
	pOpen->Status = Status;

	if (Status != NDIS_STATUS_PENDING)
		OsillcCloseAdapterComplete(pOpen, Status);

	DEBUGTRACE0("OsillcCloseAdapter: exit.");

	// always return pending status
	return ERROR_IO_PENDING;
}

//---------------------------------------------------------------------------
// Function:    OsillcCloseAdapterComplete
//
// Parameters:  NDIS_HANDLE ProtocolBindingContext -- pointer to binding context
//              NDIS_STATUS Status                 -- status from NdisCloseAdapter()
//
// Returns:     Nothing.
//
// Description: Processes MAC close completion.
//
// Notes:
//
//---------------------------------------------------------------------------
VOID NDIS_API OsillcCloseAdapterComplete(NDIS_HANDLE ProtocolBindingContext, 
										 NDIS_STATUS Status)
{
	POPEN_INSTANCE	pOpen = (POPEN_INSTANCE)ProtocolBindingContext;
	PIRP			pIrp = pOpen->pPendingIrp;
	PIOCTLPARAMS	p = &pIrp->IoctlParms;
	POVERLAPPED		pOverlap = pIrp->IoctlParms.dioc_ovrlp;

	DEBUGTRACE1("OsillcCloseAdapterComplete: entry status = %x", Status);

	// save the completion status
	pOpen->Status = Status;

	//
    // if Status is NDIS_STATUS_PENDING   
    // then we must complete the pended unbinding
	//
    if (pOpen->Status == NDIS_STATUS_PENDING)
	{
//		NdisCompleteUnbindAdapter(pOpen->BindAdapterContext, Status);
		pOpen->Status = NDIS_STATUS_SUCCESS;
	}

    if (Status == NDIS_STATUS_SUCCESS)
	{
		// clean up any pending I/O requests
		OsillcCleanUp(&Status, pOpen);

		pOpen->bBound = FALSE;

		// free Memory
        NdisFreeBufferPool(pOpen->BufferPool);
        NdisFreePacketPool(pOpen->PacketPool);
		OsillcFreeFramePool(&pOpen->FramePool);
	}

	// return the resulting status
	*p->dioc_bytesret = 0;
	pOverlap->O_InternalHigh = 
		(Status == NDIS_STATUS_SUCCESS) ? ERROR_SUCCESS : ERROR_CONNECTION_ACTIVE;

	//
    // the internal member of overlapped structure contains a pointer 
    // to the event structure that will be signalled, resuming the 
    // execution of the waiting GetOverlappedResult call.
    //
	VWIN32_DIOCCompletionRoutine(pOverlap->O_Internal);

	// unlock the buffers	
	OsillcPageUnlock(p->dioc_bytesret, sizeof(DWORD));
	OsillcPageUnlock(p->dioc_ovrlp, sizeof(OVERLAPPED));

	// return IRP item to the IRP pool
	OsillcFreeIrp(pIrp, &pOpen->IrpPool, TRUE);

	// if we're closing, destroy the open object
	if (Status == NDIS_STATUS_SUCCESS && pOpen->bClosing)
	{
		OsillcFreeIrpPool(&pOpen->IrpPool);

		// remove the open object from global list
		_disable();
		RemoveEntryList(&pOpen->ListEntry);
		_enable();

		// delete it
		NdisFreeMemory(pOpen, sizeof(OPEN_INSTANCE), 0);
	}
}

//-----------------------------------------------------------------------
// Function:    OsillcCleanUp
//
// Parameters:  PFRAME_POOL pFramePool -- pointer to FRAME pool
//
// Returns:     Nothing
//
// Description: Performs cleanup before unbinding from MAC.
//
// Note:        
//
//-----------------------------------------------------------------------
VOID OsillcCleanUp(PNDIS_STATUS pStatus, POPEN_INSTANCE pOpen)
{
    //
    //  the open instance of the device is about to close,
    //  we need to complete all pending I/O requests
    //
    for (;;)
	{
		PLIST_ENTRY     pListEntry;
		PIRP			pIrp;
		PNDIS_PACKET    pPacket;

		_disable();
		if (IsListEmpty(&pOpen->ReadIrpList))
		{
			_enable();
			break;
		}

		pListEntry = RemoveHeadList(&pOpen->ReadIrpList);
		pIrp = CONTAINING_RECORD(pListEntry, IRP, ListEntry);
		pPacket = pIrp->pPacket;
		_enable();

		//  complete normally
		OsillcTransferDataComplete(pOpen, pPacket, NDIS_STATUS_CLOSING, 0);
    }

	// delete all received packets
    for (;;)
	{
		PLIST_ENTRY     pListEntry;
		PFRAME			pFrame;
		PNDIS_PACKET    pPacket;
		PNDIS_BUFFER	pBuffer;
		UINT			PhysBufferCount, BufferCount, PacketLength;

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

		// get packet descriptor details
		NdisQueryPacket(pPacket, &PhysBufferCount, &BufferCount,
						&pBuffer, &PacketLength);

		// recycle the frame buffer
		OsillcFreeFrame(pFrame, &pOpen->FramePool, TRUE);

		// recycle the buffer descriptor
		NdisUnchainBufferAtFront(pPacket, &pBuffer);
		NdisFreeBuffer(pBuffer);

		// recycle the packet
		NdisReinitializePacket(pPacket);
		NdisFreePacket(pPacket);
    }

	// complete all reset requests
    for (;;)
	{
		_disable();
		if (IsListEmpty(&pOpen->ResetIrpList))
		{
			_enable();
			break;
		}
		_enable();

		//  complete normally
		OsillcResetComplete(pOpen, NDIS_STATUS_SUCCESS);
    }

	*pStatus = NDIS_STATUS_SUCCESS;

//	OsillcReset(pStatus, pOpen);

}

VOID OsillcYieldExecution(void)
{
	Release_Time_Slice();
	Begin_Nest_Exec();
	Resume_Exec();
	End_Nest_Exec();
}
