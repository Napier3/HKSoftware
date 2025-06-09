//---------------------------------------------------------------------------
//
// File:         framepool.c
//
// Copyright (c) 1998 SISCO, Inc. All rights reserved.
//
// Description:  Frame pool management routines.
//
// Author:       A. Shajenko/Stratos Technology, Inc.
//
// History:
// 13-Sep-98     A. Shajenko     Implemented.
//
//---------------------------------------------------------------------------

#include "osillc95.h"

//-----------------------------------------------------------------------
// Function:    OsillcAllocateFramePool
//
// Parameters:  PFRAME_POOL pFramePool -- pointer to FRAME pool
//              DWORD dwNumberOfFrames -- number of frames in pool
//              DWORD dwFrameSize      -- frame size in bytes
//
// Returns:     TRUE if successful.
//
// Description: Allocates a FRAME pool.
//
// Note:        
//
//-----------------------------------------------------------------------
BOOL
OsillcAllocateFramePool(PFRAME_POOL pFramePool, DWORD dwNumberOfFrames,
                        DWORD dwFrameSize)
{
	NDIS_STATUS	Status;
	PFRAME		pFrame = NULL;
	DWORD		i;

	pFramePool->dwPoolItems = dwNumberOfFrames;
	pFramePool->dwItemSize  = sizeof(FRAME) + dwFrameSize;
	pFramePool->dwPoolSize  = dwNumberOfFrames * pFramePool->dwItemSize;
	pFramePool->dwPoolPages = (pFramePool->dwPoolSize + 4095) >> 12;
	pFramePool->dwFreeItems = 0;

	// allocate the frame pool
    Status = NdisAllocateMemory((PVOID *)&pFramePool->pPoolAddress, pFramePool->dwPoolSize, 0, -1);
	if (Status == NDIS_STATUS_SUCCESS)
	{
		InitializeListHead(&pFramePool->FreeList);
		pFrame = (PFRAME)pFramePool->pPoolAddress;
		for (i = 0; i < pFramePool->dwPoolItems; i++)
		{
			InsertTailList(&pFramePool->FreeList, &pFrame->ListEntry);
			pFramePool->dwFreeItems++;
			pFrame = (PFRAME)(((PBYTE)pFrame) + pFramePool->dwItemSize);
			pFrame->dwFrameSize = dwFrameSize;
		}

		DEBUGTRACE1("OsillcAllocateFramePool: allocated pool for %d items", pFramePool->dwFreeItems);
		return TRUE;
	}
	else
	{
		DEBUGERROR1("OsillcAllocateFramePool: NdisAllocateMemory failed: %x!", Status);
		return FALSE;
	}
}

//-----------------------------------------------------------------------
// Function:    OsillcFreeFramePool
//
// Parameters:  PFRAME_POOL pFramePool -- pointer to FRAME pool
//
// Returns:     Nothing
//
// Description: Deallocates the FRAME pool.
//
// Note:        
//
//-----------------------------------------------------------------------
VOID
OsillcFreeFramePool(PFRAME_POOL pFramePool)
{
    // free the Frame Pool arena
	if (pFramePool->pPoolAddress != NULL)
	{
		DEBUGTRACE1("OsillcFreeFramePool: freeing pool %08X", pFramePool);

		Assert(pFramePool->dwPoolItems == pFramePool->dwFreeItems);

		_disable();
		NdisFreeMemory((PVOID)pFramePool->pPoolAddress, pFramePool->dwPoolSize, 0);
		pFramePool->pPoolAddress = NULL;
		_enable();
	}
}

//-----------------------------------------------------------------------
// Function:    OsillcAllocateFrame
//
// Parameters:  PFRAME_POOL pFramePool -- pointer to FRAME pool
//              BOOL bProtect          -- if TRUE, protect critical section
//
// Returns:     Pointer to FRAME if successful.
//
// Description: Allocates a Frame from the Frame pool.
//
// Note:        
//
//-----------------------------------------------------------------------
PFRAME
OsillcAllocateFrame(PFRAME_POOL pFramePool, BOOL bProtect)
{
	PFRAME pFrame = NULL;

    // check if the Item pool is valid
	if (pFramePool->pPoolAddress == NULL)
        return (PFRAME)NULL;

	if (bProtect) _disable();

    // check if a Frame item is available
    if ( !IsListEmpty(&pFramePool->FreeList))
	{
		PLIST_ENTRY ListEntry;

		// remove a Frame item from the head of the free list and reconstruct it
		ListEntry = RemoveHeadList(&pFramePool->FreeList);
		pFrame = CONTAINING_RECORD(ListEntry, FRAME, ListEntry);
		pFramePool->dwFreeItems--;

		pFrame->pIrp = NULL;
		pFrame->pPacket = NULL;

		DEBUGTRACE1("OsillcAllocateFrame: allocated frame item %08X", pFrame);
    }
		
	if (bProtect) _enable();

    return pFrame;
}

//-----------------------------------------------------------------------
// Function:    OsillcFreeFrame
//
// Parameters:  PFRAME pFrame          -- pointer to FRAME
//              PFRAME_POOL pFramePool -- pointer to FRAME pool
//              BOOL bProtect          -- if TRUE, protect critical section
//
// Returns:     PBRI_ADAPTER Adapter - pointer to adapter object
//
// Description: Scans adapter list for a specific adapter.
//
// Note:        
//
//-----------------------------------------------------------------------
VOID
OsillcFreeFrame(PFRAME pFrame, PFRAME_POOL pFramePool, BOOL bProtect)
{
    // free the Frame item
	if (pFramePool->pPoolAddress != NULL)
    {
        DEBUGTRACE1("OsillcFreeFrame: freed frame item %08X", pFrame);

		if (bProtect) _disable();
		pFrame->pIrp = NULL;
		pFrame->pPacket = NULL;

		InsertTailList(&pFramePool->FreeList, &pFrame->ListEntry);
		pFramePool->dwFreeItems++;
		if (bProtect) _enable();
    }
}

//---------------------------------------------------------------------------
// end of framepool.c
