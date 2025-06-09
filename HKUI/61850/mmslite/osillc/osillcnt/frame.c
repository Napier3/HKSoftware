/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,       */
/*              199, 1997, All Rights Reserved                          */
/*                                                                      */
/* MODULE NAME : frame.c                                                */
/* PRODUCT(S)  : OSI LLC NDIS 3.0 Device Driver for NT                  */
/*                                                                      */
/* MODULE DESCRIPTION :                                                 */
/*                                                                      */
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :                            */
/*                                                                      */
/* MODIFICATION LOG :                                                   */
/*  Date     Who   Rev                  Comments                        */
/* --------  ---  ------   -------------------------------------------  */
/* 05/11/98  DSF    06     File reformatted				*/
/* 05/06/98  DSF    02     Must initialize pool spinlock                */
/* 08/19/97  APS    01     Initial Release                              */
/*                                                                      */
/************************************************************************/

#include "ntddk.h"
#include "ntiologc.h"
#include "ndis.h"

#include "debug.h"
#include "frame.h"

/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  VOID NdisAllocateFramePool(
 *                                              OUT PNDIS_STATUS                        Status,
 *                                              OUT PNDIS_HANDLE                        PoolHandle,
 *                                              IN      UINT                                    NumberOfFrames,
 *                                              IN      UINT                                    FrameLength
 *                                              )
 *
 *  PURPOSE:   Allocates a pool of frame data buffers.
 *
 *  PARMS:     PNDIS_STATUS Status - resulting status
 *             PNDIS_HANDLE PoolHandle - pointer to pool handle
 *             UINT     NumberOfFrames - number of frames in pool
 *             UINT FrameLength - size of frame
 *
 *  RETURNS:   Nothing. 
 *
 *  NOTES:
 *
-*/
/* ---------------------------------------------------------------------*/

VOID
  NdisAllocateFramePool(
  OUT PNDIS_STATUS                        Status,
  OUT PNDIS_HANDLE                        PoolHandle,
  IN      UINT                                    NumberOfFrames,
  IN      UINT                                    FrameLength
  )
  {
  PNDIS_FRAME_POOL        FramePool;
  NTSTATUS        NtStatus;
  PVOID           Arena;
  ULONG           BlockSize = FrameLength + 8 - (FrameLength % 8);
  ULONG           SegmentSize = NumberOfFrames * BlockSize;
  ULONG           PoolSize = sizeof(NDIS_FRAME_POOL) + SegmentSize;
  ULONG           FramePoolSize = sizeof(NDIS_FRAME_POOL);

  // allocate the frame pool arena
  Arena = ExAllocatePool(NonPagedPool, PoolSize);
  if (Arena == NULL)
    *Status = NDIS_STATUS_FAILURE;
  else
    {
    // set up the frame pool
    FramePool = (PNDIS_FRAME_POOL)Arena;
    NtStatus = ExInitializeZone(&FramePool->Zone, BlockSize,
                                &FramePool->ZoneSegmentHeader,
                                SegmentSize);

    if (NtStatus == STATUS_SUCCESS)
      {
      *PoolHandle = (NDIS_HANDLE)FramePool;
      NdisAllocateSpinLock (&FramePool->SpinLock);
      *Status = NDIS_STATUS_SUCCESS;
      }
    else
      {
      *PoolHandle = NULL;
      ExFreePool(Arena);
      *Status = NDIS_STATUS_FAILURE;
      }
    }
  }

/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  VOID NdisFreeFramePool(
 *                                              OUT PNDIS_HANDLE                        PoolHandle,
 *                                              )
 *
 *  PURPOSE:   Deallocates a pool of frame data buffers.
 *
 *  PARMS:     PNDIS_HANDLE PoolHandle - pointer to pool handle
 *
 *  RETURNS:   Nothing. 
 *
 *  NOTES:
 *
-*/
/* ---------------------------------------------------------------------*/

VOID
  NdisFreeFramePool(
  IN      NDIS_HANDLE             PoolHandle
  )
  {
  PNDIS_FRAME_POOL        FramePool = (PNDIS_FRAME_POOL)PoolHandle;

  // free the frame pool arena
  ExFreePool(FramePool);
  }

/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  VOID NdisAllocateFrame(
 *                                              OUT PNDIS_STATUS        Status,
 *                                              OUT NDIS_FRAME  *       Frame,
 *                                              OUT PNDIS_HANDLE        PoolHandle,
 *                                              )
 *
 *  PURPOSE:   Allocates a frame from the frame buffer pool.
 *
 *  PARMS:     PNDIS_STATUS Status - resulting status
 *                         NDIS_FRAME Frame - pointer to a frame buffer pointer
 *             PNDIS_HANDLE PoolHandle - pointer to pool handle
 *
 *  RETURNS:   Nothing. 
 *
 *  NOTES:     This function is to called from PASSIVE_LEVEL.
 *
-*/
/* ---------------------------------------------------------------------*/

VOID
  NdisAllocateFrame(
  OUT PNDIS_STATUS        Status,
  OUT NDIS_FRAME  *       Frame,
  IN      NDIS_HANDLE             PoolHandle
  )
  {
  PNDIS_FRAME_POOL        FramePool = (PNDIS_FRAME_POOL)PoolHandle;
  KIRQL                           Irql = KeGetCurrentIrql();

  // get the frame pool spinlock (backets need due to macro invocation)
  if (Irql == DISPATCH_LEVEL)
    {
    NdisDprAcquireSpinLock(&FramePool->SpinLock);
    }
  else
    NdisAcquireSpinLock(&FramePool->SpinLock);

  // check if a frame is available
  if (ExIsFullZone(&FramePool->Zone))
    *Status = NDIS_STATUS_FAILURE;
  else
    {
    // try to allocate a frame
    *Frame = ExAllocateFromZone(&FramePool->Zone);
    *Status = (*Frame) ? NDIS_STATUS_SUCCESS : NDIS_STATUS_FAILURE;
    }

  if (Irql == DISPATCH_LEVEL)
    NdisDprReleaseSpinLock(&FramePool->SpinLock);
  else
    NdisReleaseSpinLock(&FramePool->SpinLock);
  }

/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  VOID NdisFreeFrame(
 *                                              OUT NDIS_FRAME          Frame,
 *                                              OUT PNDIS_HANDLE        PoolHandle,
 *                                              )
 *
 *  PURPOSE:   Allocates a frame from the frame buffer pool.
 *
 *  PARMS:     NDIS_FRAME Frame - pointer to a frame buffer
 *             PNDIS_HANDLE PoolHandle - pointer to pool handle
 *
 *  RETURNS:   Nothing. 
 *
 *  NOTES:     This function is to called from PASSIVE_LEVEL.
 *
-*/
/* ---------------------------------------------------------------------*/

VOID
  NdisFreeFrame(
  IN  NDIS_FRAME          Frame,
  IN      NDIS_HANDLE             PoolHandle
  )
  {
  PNDIS_FRAME_POOL        FramePool = (PNDIS_FRAME_POOL)PoolHandle;
  KIRQL                           Irql = KeGetCurrentIrql();

  // get the frame pool spinlock (backets need due to macro invocation)
  if (Irql == DISPATCH_LEVEL)
    {
    NdisDprAcquireSpinLock(&FramePool->SpinLock);
    }
  else
    NdisAcquireSpinLock(&FramePool->SpinLock);

  // free the frame
  ExFreeToZone(&FramePool->Zone, (PVOID)Frame);

  if (Irql == DISPATCH_LEVEL)
    NdisDprReleaseSpinLock(&FramePool->SpinLock);
  else
    NdisReleaseSpinLock(&FramePool->SpinLock);
  }

/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  VOID NdisDprAllocateFrame(
 *                                              OUT PNDIS_STATUS        Status,
 *                                              OUT NDIS_FRAME  *       Frame,
 *                                              OUT PNDIS_HANDLE        PoolHandle,
 *                                              )
 *
 *  PURPOSE:   Allocates a frame from the frame buffer pool.
 *
 *  PARMS:     PNDIS_STATUS Status - resulting status
 *                         NDIS_FRAME Frame - pointer to a frame buffer pointer
 *             PNDIS_HANDLE PoolHandle - pointer to pool handle
 *
 *  RETURNS:   Nothing. 
 *
 *  NOTES:     This function is to called from DISPATCH_LEVEL.
 *
-*/
/* ---------------------------------------------------------------------*/

VOID
  NdisDprAllocateFrame(
  OUT PNDIS_STATUS        Status,
  OUT NDIS_FRAME  *       Frame,
  IN      NDIS_HANDLE             PoolHandle
  )
  {
  PNDIS_FRAME_POOL        FramePool = (PNDIS_FRAME_POOL)PoolHandle;

  // check if a frame is available
  if (ExIsFullZone(&FramePool->Zone))
    *Status = NDIS_STATUS_FAILURE;
  else
    {
    // try to allocate a frame
    NdisDprAcquireSpinLock(&FramePool->SpinLock);
    *Frame = ExAllocateFromZone(&FramePool->Zone);
    NdisDprReleaseSpinLock(&FramePool->SpinLock);

    *Status = (*Frame) ? NDIS_STATUS_SUCCESS : NDIS_STATUS_FAILURE;
    }
  }

/* -------------------------------------------------------------------- */
/*+
 *  FUNCTION:  VOID NdisDprFreeFrame(
 *                                              OUT NDIS_FRAME          Frame,
 *                                              OUT PNDIS_HANDLE        PoolHandle,
 *                                              )
 *
 *  PURPOSE:   Allocates a frame from the frame buffer pool.
 *
 *  PARMS:     NDIS_FRAME Frame - pointer to a frame buffer
 *             PNDIS_HANDLE PoolHandle - pointer to pool handle
 *
 *  RETURNS:   Nothing. 
 *
 *  NOTES:     This function is to called from DISPATCH_LEVEL.
 *
-*/
/* ---------------------------------------------------------------------*/

VOID
  NdisDprFreeFrame(
  IN  NDIS_FRAME          Frame,
  IN      NDIS_HANDLE             PoolHandle
  )
  {
  PNDIS_FRAME_POOL        FramePool = (PNDIS_FRAME_POOL)PoolHandle;

  // free the frame
  NdisDprAcquireSpinLock(&FramePool->SpinLock);
  ExFreeToZone(&FramePool->Zone, (PVOID)Frame);
  NdisDprReleaseSpinLock(&FramePool->SpinLock);
  }

