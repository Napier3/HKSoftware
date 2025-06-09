/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,       */
/*              1996, All Rights Reserved                               */
/*                                                                      */
/* MODULE NAME : write.c                                                */
/* PRODUCT(S)  : OSI LLC NDIS 3.0 Device Driver for NT                  */
/*                                                                      */
/* MODULE DESCRIPTION :                                                 */
/*                                                                      */
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :                            */
/*                                                                      */
/* MODIFICATION LOG :                                                   */
/*  Date     Who   Rev                  Comments                        */
/* --------  ---  ------   -------------------------------------------  */
/* 08/21/00  DSF    08     Unchained send buffer before reinitializing	*/
/*			   packet in SendComplete			*/
/* 04/01/99  DSF    07     Commonized Win98/WinNT include files		*/
/* 05/11/98  DSF    06     File reformatted				*/
/* 05/08/98  DSF    05     In case of errors, return original status    */
/* 06/19/97  DSF    04     Added Stats                                  */
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

/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  NTSTATUS OsillcWrite(PDEVICE_OBJECT DeviceObject, PIRP Irp)
 *
 *  PURPOSE:   Send a packet to the bound MAC driver.
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

NTSTATUS OsillcWrite(PDEVICE_OBJECT DeviceObject, PIRP Irp)
  {
  PIO_STACK_LOCATION      IrpSp = IoGetCurrentIrpStackLocation(Irp);
  POPEN_INSTANCE          Open = IrpSp->FileObject->FsContext;
  PNDIS_PACKET            pPacket;
  NDIS_STATUS                     Status;

  DEBUGTRACE0("Write");

  //  get a packet from our list of free ones
  NdisAllocatePacket(&Status, &pPacket, Open->TxPacketPool);

  if (Status != NDIS_STATUS_SUCCESS) 
    {
    //  No free packets
    NdisAllocError++;
    DEBUGERROR1 ("AllocatePacket failed (%x)", Status);
    Irp->IoStatus.Status = Status;
    Irp->IoStatus.Information = 0;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    return Status;
    }

  // save a pointer to this Irp
  TX_RESERVED(pPacket)->Irp = Irp;

  // attach the write buffer to the packet
  NdisChainBufferAtFront(pPacket, Irp->MdlAddress);

  IoMarkIrpPending(Irp);
  Irp->IoStatus.Status = STATUS_PENDING;

  //  send the packet down to the MAC driver
  NdisSend(&Status, Open->AdapterHandle, pPacket);

  //  if the send didn't pend then call the completion handler now
  if (Status != NDIS_STATUS_PENDING) 
    OsillcSendComplete(Open, pPacket, Status);

  return STATUS_PENDING;
  //      return Status;
  }

/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  VOID OsillcSendComplete(NDIS_HANDLE ProtocolBindingContext,
 *                                              PNDIS_PACKET pPacket, NDIS_STATUS Status)
 *
 *  PURPOSE:   Notification from the bound MAC driver that send is complete.
 *
 *  PARMS:     NDIS_HANDLE ProtocolBindingContext - binding context
 *             PNDIS_PACKET pPacket          - pointer to packet
 *             NDIS_STATUS Status            - resulting status
 *
 *  RETURNS:   Nothing. 
 *
 *  NOTES:
 *
-*/
/* ---------------------------------------------------------------------*/

VOID OsillcSendComplete(NDIS_HANDLE ProtocolBindingContext,
  PNDIS_PACKET pPacket, NDIS_STATUS Status)
  {
  PIRP    Irp = TX_RESERVED(pPacket)->Irp;
  NDIS_BUFFER *pBuffer;

  DEBUGTRACE0("SendComplete");

  // remove buffer descriptor from packet
  NdisUnchainBufferAtBack(pPacket, &pBuffer);
  
  //  recycle the packet
  NdisReinitializePacket(pPacket);

  //  put the packet back on the free list
  NdisFreePacket(pPacket);

  if (Status != NDIS_STATUS_SUCCESS)
    {
    NdisXmitError++;
    DEBUGERROR1("Send failed (%x)", Status);
    }
  else
    NdisXmitOk++;

  Irp->IoStatus.Status = Status;
  Irp->IoStatus.Information = 0;
  IoCompleteRequest(Irp, IO_NO_INCREMENT);
  }
