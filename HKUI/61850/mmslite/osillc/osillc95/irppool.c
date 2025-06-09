//---------------------------------------------------------------------------
//
// File:         irppool.c
//
// Copyright (c) 1998 SISCO, Inc. All rights reserved.
//
// Description:  IRP pool management routines.
//
// Author:       A. Shajenko/Stratos Technology, Inc.
//
// History:
// 13-Sep-98     A. Shajenko     Implemented.
//
//---------------------------------------------------------------------------

#include "osillc95.h"

//-----------------------------------------------------------------------
// Function:    OsillcAllocateIrpPool
//
// Parameters:  PIRP_POOL pIrpPool -- pointer to IRP pool
//              DWORD dwNumberOfIrps -- number of frames in pool
//
// Returns:     TRUE if successful.
//
// Description: Allocates a IRP pool.
//
// Note:        
//
//-----------------------------------------------------------------------
BOOL
OsillcAllocateIrpPool(PIRP_POOL pIrpPool, DWORD dwNumberOfIrps)
{
	PIRP		pIrp = NULL;
	DWORD		i;
	NDIS_STATUS	Status;

	pIrpPool->dwPoolItems = dwNumberOfIrps;
	pIrpPool->dwItemSize  = sizeof(IRP);
	pIrpPool->dwPoolSize  = dwNumberOfIrps * pIrpPool->dwItemSize;
	pIrpPool->dwPoolPages = (pIrpPool->dwPoolSize + 4095) >> 12;
	pIrpPool->dwFreeItems = 0;

	// allocate the frame pool
    Status = NdisAllocateMemory((PVOID *)&pIrpPool->pPoolAddress, pIrpPool->dwPoolSize, 0, -1);
	if (Status == NDIS_STATUS_SUCCESS)
	{
		InitializeListHead(&pIrpPool->FreeList);
		pIrp = (PIRP)pIrpPool->pPoolAddress;
		for (i = 0; i < pIrpPool->dwPoolItems; i++)
		{
			InsertTailList(&pIrpPool->FreeList, &pIrp->ListEntry);
			pIrpPool->dwFreeItems++;
			pIrp++;
		}

		DEBUGTRACE1("OsillcAllocateIrpPool: allocated pool for %d items", pIrpPool->dwFreeItems);
		return TRUE;
	}
	else
	{
		DEBUGERROR1("OsillcAllocateIrpPool: NdisAllocateMemory failed: %x!", Status);
		return FALSE;
	}
}

//-----------------------------------------------------------------------
// Function:    OsillcFreeIrpPool
//
// Parameters:  PIRP_POOL pIrpPool -- pointer to IRP pool
//
// Returns:     Nothing
//
// Description: Deallocates the IRP pool.
//
// Note:        
//
//-----------------------------------------------------------------------
VOID
OsillcFreeIrpPool(PIRP_POOL pIrpPool)
{
    // free the Irp pool arena
	if (pIrpPool->pPoolAddress != NULL)
	{
		DEBUGTRACE1("OsillcFreeIrpPool: freeing pool %08X", pIrpPool);

		Assert(pIrpPool->dwPoolItems == pIrpPool->dwFreeItems);

		_disable();
		NdisFreeMemory((PVOID)pIrpPool->pPoolAddress, pIrpPool->dwPoolSize, 0);
		pIrpPool->pPoolAddress = NULL;
		_enable();
	}
}

//-----------------------------------------------------------------------
// Function:    OsillcAllocateIrp
//
// Parameters:  PIRP_POOL pIrpPool -- pointer to IRP pool
//              BOOL bProtect -- if TRUE, protect critical section
//
// Returns:     Pointer to IRP if successful.
//
// Description: Allocates a Irp from the Irp pool.
//
// Note:        
//
//-----------------------------------------------------------------------
PIRP
OsillcAllocateIrp(PIRP_POOL pIrpPool, BOOL bProtect)
{
	PIRP pIrp = NULL;

    // check if the Item pool is valid
	if (pIrpPool->pPoolAddress == NULL)
        return (PIRP)NULL;

	if (bProtect) _disable();

    // check if a Irp item is available
    if ( !IsListEmpty(&pIrpPool->FreeList))
	{
		PLIST_ENTRY ListEntry;

		// remove a Irp item from the head of the free list and reconstruct it
		ListEntry = RemoveHeadList(&pIrpPool->FreeList);
		pIrp = CONTAINING_RECORD(ListEntry, IRP, ListEntry);
		pIrpPool->dwFreeItems--;

		DEBUGTRACE1("OsillcAllocateIrp: allocated IRP %08X", pIrp);
    }
		
	if (bProtect) _enable();

    return pIrp;
}

//-----------------------------------------------------------------------
// Function:    OsillcFreeIrp
//
// Parameters:  PIRP pIrp  -- pointer to IRP
//              PIRP_POOL pIrpPool -- pointer to IRP pool
//              BOOL bProtect -- if TRUE, protect critical section
//
// Returns:     PBRI_ADAPTER Adapter - pointer to adapter object
//
// Description: Scans adapter list for a specific adapter.
//
// Note:        
//
//-----------------------------------------------------------------------
VOID
OsillcFreeIrp(PIRP pIrp, PIRP_POOL pIrpPool, BOOL bProtect)
{
    // free the Irp item
	if (pIrpPool->pPoolAddress != NULL)
    {
        DEBUGTRACE1("OsillcFreeIrp: freed IRP %08X", pIrp);

		if (bProtect) _disable();
		InsertTailList(&pIrpPool->FreeList, &pIrp->ListEntry);
		pIrpPool->dwFreeItems++;
		if (bProtect) _enable();
    }
}

//---------------------------------------------------------------------------
// end of irppool.c
