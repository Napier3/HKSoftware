//---------------------------------------------------------------------------
//
// File:         request.c
//
// Copyright (c) 1998,1999 SISCO, Inc. All rights reserved.
//
// Description:  OID query & set routines.
//
// Author:       A. Shajenko/Stratos Technology, Inc.
//
// History:
// 13-Sep-98     A. Shajenko     Implemented.
//
//---------------------------------------------------------------------------

#include "osillc95.h"

// Original code by William Ingle (address unknown)
// debugged and extended by Chris Chlap (chrisc@fir.canberra.edu.au)


//---------------------------------------------------------------------------
// Function:    OsillcRequest
//
// Parameters:  POPEN_INSTANCE pOpen -- pointer to open instance
//              PIOCTLPARAMS p       -- pointer to IOCTL request block
//
// Returns:     Return code.
//
// Description: Send an OID request down to the MAC driver.
//
// Notes:
//
//---------------------------------------------------------------------------
DWORD OsillcRequest(POPEN_INSTANCE pOpen, PIOCTLPARAMS p)
{
//	PLIST_ENTRY			pListEntry;
	PIRP				pIrp = NULL;
	POSILLC_OID_DATA	pOidData = p->dioc_InBuf;
	NDIS_STATUS			Status;

	// set the number of bytes returned
	*p->dioc_bytesret = 0;

	// we only accept Query and Set OID types
	if (p->dioc_IOCtlCode != IOCTL_OSILLC_SET_OID &&
		p->dioc_IOCtlCode != IOCTL_OSILLC_QUERY_OID)
	{
		return ERROR_INVALID_PARAMETER;
	}

	// make sure that the input and output buffer are the same buffer
	// and the sizes are the same since we treat them as the same buffer
	if (p->dioc_InBuf != p->dioc_OutBuf ||
		p->dioc_cbInBuf != p->dioc_cbOutBuf)
	{
		DEBUGERROR0("OsillcRequest: ERROR: invalid request"); 
		return ERROR_INVALID_PARAMETER;
	}
		
	// validate the input and/or output parameters
	if (p->dioc_InBuf == NULL || p->dioc_cbInBuf < sizeof(OSILLC_OID_DATA) ||
		p->dioc_cbInBuf < sizeof(OSILLC_OID_DATA) + pOidData->Length - 1)
	{
		DEBUGERROR0("OsillcRequest: ERROR: invalid request"); 
		return ERROR_INSUFFICIENT_BUFFER;
	}
	
	// allocate an Irp for the request
	if ((pIrp = OsillcAllocateIrp(&pOpen->IrpPool, TRUE)) == NULL)
	{ 
		DEBUGERROR0("OsillcRequest: ERROR: Irp Pool empty"); 
		return ERROR_NO_SYSTEM_RESOURCES;
	}

	// build the Irp
	NdisMoveMemory(&pIrp->IoctlParms, p, sizeof(IOCTLPARAMS));

	// lock down the buffers
	pIrp->IoctlParms.dioc_InBuf    = (PVOID)OsillcPageLock(p->dioc_InBuf, p->dioc_cbInBuf);
	pIrp->IoctlParms.dioc_bytesret = (PVOID)OsillcPageLock((PVOID)p->dioc_bytesret, sizeof(DWORD));
	pIrp->IoctlParms.dioc_ovrlp    = (PVOID)OsillcPageLock((PVOID)p->dioc_ovrlp, sizeof(OVERLAPPED));

	pOidData = (POSILLC_OID_DATA)pIrp->IoctlParms.dioc_InBuf;

	// build the NDIS request
	if (p->dioc_IOCtlCode == IOCTL_OSILLC_SET_OID)
	{
		pIrp->Request.RequestType = NdisRequestSetInformation;
		pIrp->Request.DATA.SET_INFORMATION.Oid                     = pOidData->Oid;
		pIrp->Request.DATA.SET_INFORMATION.InformationBufferLength = pOidData->Length;
		pIrp->Request.DATA.SET_INFORMATION.InformationBuffer       = pOidData->Data;
		pIrp->Request.DATA.SET_INFORMATION.BytesNeeded             = 0;
	}
	else
	{
		pIrp->Request.RequestType = NdisRequestQueryInformation;
		pIrp->Request.DATA.QUERY_INFORMATION.Oid                     = pOidData->Oid;
		pIrp->Request.DATA.QUERY_INFORMATION.InformationBufferLength = pOidData->Length;
		pIrp->Request.DATA.QUERY_INFORMATION.InformationBuffer       = pOidData->Data;
		pIrp->Request.DATA.QUERY_INFORMATION.BytesNeeded             = 0;
	}

    // submit the OID request to the MAC
    NdisRequest(&Status, pOpen->AdapterHandle, &pIrp->Request);

	DEBUGTRACE1("OsillcRequest: NdisRequest status = %x", Status);

    if (Status != NDIS_STATUS_PENDING)
        OsillcRequestComplete(pOpen, &pIrp->Request, Status);

	// always return pending
    return ERROR_IO_PENDING;
}

//---------------------------------------------------------------------------
// Function:    OsillcRequestComplete
//
// Parameters:  NDIS_HANDLE ProtocolBindingContext -- pointer to binding context
//              PNDIS_REQUEST NdisRequest          -- pointer to request block
//              NDIS_STATUS Status                 -- status from NdisRequest()
//
// Returns:     Return code.
//
// Description: Processes OID request completion.
//
// Notes:
//
//---------------------------------------------------------------------------
VOID NDIS_API OsillcRequestComplete(NDIS_HANDLE ProtocolBindingContext,
                                    PNDIS_REQUEST pRequest,
                                    NDIS_STATUS   Status)
{
	POPEN_INSTANCE    pOpen     = (POPEN_INSTANCE)ProtocolBindingContext;
	PIRP			  pIrp      = CONTAINING_RECORD(pRequest, IRP, Request);
	PIOCTLPARAMS	  p         = &pIrp->IoctlParms;
	POVERLAPPED		  pOverlap  = pIrp->IoctlParms.dioc_ovrlp;
	POSILLC_OID_DATA  pOidData  = (POSILLC_OID_DATA)pIrp->IoctlParms.dioc_InBuf;

	DEBUGTRACE1("OsillcRequestComplete: entry status = %x", Status);

	// return the Request results in the user's OID struct
	if (pRequest->RequestType == IOCTL_OSILLC_SET_OID)
	{
		pOidData->BytesProcessed = pRequest->DATA.SET_INFORMATION.BytesRead;
		pOidData->BytesNeeded = pRequest->DATA.SET_INFORMATION.BytesNeeded;
	}
	else
	{
		pOidData->BytesProcessed = pRequest->DATA.QUERY_INFORMATION.BytesWritten;
		pOidData->BytesNeeded = pRequest->DATA.QUERY_INFORMATION.BytesNeeded;
	}
	pOidData->Status = Status;

    if (Status == NDIS_STATUS_SUCCESS)
	{
		// set total bytes returned
		*p->dioc_bytesret        = sizeof(OSILLC_OID_DATA) + pOidData->Length - 1;
		pOverlap->O_InternalHigh = *p->dioc_bytesret;
	}
    else
	{
		// set total bytes returned
		*p->dioc_bytesret        = 0;
		pOverlap->O_InternalHigh = Status;
	}

	//
	// the internal member of overlapped structure contains a pointer 
	// to the event structure that will be signalled, resuming the execution
	// of the waitng GetOverlappedResult call.
	//
	VWIN32_DIOCCompletionRoutine(pOverlap->O_Internal);

	// unlock the buffers	
	OsillcPageUnlock(p->dioc_InBuf, p->dioc_cbInBuf);
	OsillcPageUnlock(p->dioc_bytesret, sizeof(DWORD));
	OsillcPageUnlock(p->dioc_ovrlp, sizeof(OVERLAPPED));

	// return IRP item to the IRP pool
	OsillcFreeIrp(pIrp, &pOpen->IrpPool, TRUE);
}
