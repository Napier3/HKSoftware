//---------------------------------------------------------------------------
//
// File:         reset.c
//
// Copyright (c) 1998,1999 SISCO, Inc. All rights reserved.
//
// Description:  MAC reset routines.
//
// Author:       A. Shajenko/Stratos Technology, Inc.
//
// History:
// 13-Sep-98     A. Shajenko     Implemented.
//
//---------------------------------------------------------------------------

#include "osillc95.h"

//---------------------------------------------------------------------------
// Function:    OsillcReset
//
// Parameters:  PNDIS_STATUS pStatus -- pointer to Status
//              POPEN_INSTANCE pOpen -- pointer to open instance
//
// Returns:     Nothing.
//
// Description: Sends a reset request down to the MAC driver.
//
// Notes:       
//
//---------------------------------------------------------------------------
VOID OsillcReset(PNDIS_STATUS pStatus, POPEN_INSTANCE pOpen)
{
	PIRP		pIrp = NULL;

	// allocate an Irp for the reset request
	if ((pIrp = OsillcAllocateIrp(&pOpen->IrpPool, TRUE)) == NULL)
	{ 
		*pStatus = NDIS_STATUS_RESOURCES;
		DEBUGERROR0("OsillcReset: ERROR: IrpPool empty");
	}
    else
	{
		// insert Reset IRP into Request Queue
		_disable();
		InsertTailList(&pOpen->ResetIrpList, &pIrp->ListEntry);
		_enable();

		// reset the adapter
		NdisReset(pStatus, pOpen->AdapterHandle);

		DEBUGTRACE1("OsillcReset: NdisReset status = %x", *pStatus);

		if (*pStatus != NDIS_STATUS_PENDING)
			OsillcResetComplete(pOpen, *pStatus);
	}
}

//---------------------------------------------------------------------------
// Function:    OsillcResetComplete
//
// Parameters:  NDIS_HANDLE ProtocolBindingContext -- pointer to binding context
//              NDIS_STATUS Status                 -- status from NdisRequest()
//
// Returns:     Nothing.
//
// Description: Processes MAC reset completion.
//
// Notes:
//
//---------------------------------------------------------------------------
VOID NDIS_API OsillcResetComplete(NDIS_HANDLE ProtocolBindingContext, NDIS_STATUS Status)
{
	POPEN_INSTANCE   pOpen = (POPEN_INSTANCE)ProtocolBindingContext;

	DEBUGTRACE1("OsillcResetComplete: entry status = %x", Status);

	pOpen->ResetStatus = Status;

	_disable();

	//  remove the reset request from the list
    if (IsListEmpty(&pOpen->ResetIrpList))
	{ 
		DEBUGERROR0("OsillcResetComplete: ERROR: ResetIrpList empty");
	}
	else
	{
		PLIST_ENTRY	pListEntry = NULL;
		PIRP		pIrp = NULL;

		// acquire request element from list
		pListEntry = RemoveHeadList(&pOpen->ResetIrpList);
		pIrp = CONTAINING_RECORD(pListEntry, IRP, ListEntry);
		OsillcFreeIrp(pIrp, &pOpen->IrpPool, FALSE);
	}

	_enable();
}
