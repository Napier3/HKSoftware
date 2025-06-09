//
// frame pool definition
//
typedef PVOID NDIS_FRAME, *PNDIS_FRAME;

#pragma pack(1)

//
// Frame pool header - this struct MUST start on 8-byte boundary
//
typedef struct _NDIS_FRAME_POOL
{
	ZONE_HEADER			Zone;
	NDIS_SPIN_LOCK		SpinLock;
	ZONE_SEGMENT_HEADER	ZoneSegmentHeader;	// this MUST start on 8-byte boundary
} NDIS_FRAME_POOL, * PNDIS_FRAME_POOL;

#pragma pack()

VOID
NdisAllocateFramePool(
	OUT PNDIS_STATUS			Status,
	OUT PNDIS_HANDLE			PoolHandle,
	IN	UINT					NumberOfFrames,
	IN	UINT					FrameLength
	);

VOID
NdisFreeFramePool(
	IN	NDIS_HANDLE		PoolHandle
	);

VOID
NdisAllocateFrame(
	OUT PNDIS_STATUS	Status,
	OUT NDIS_FRAME	*	Frame,
	IN	NDIS_HANDLE		PoolHandle
	);

VOID
NdisFreeFrame(
	IN  NDIS_FRAME		Frame,
	IN	NDIS_HANDLE		PoolHandle
	);

VOID
NdisDprAllocateFrame(
	OUT PNDIS_STATUS	Status,
	OUT NDIS_FRAME	*	Frame,
	IN	NDIS_HANDLE		PoolHandle
	);

VOID
NdisDprFreeFrame(
	IN  NDIS_FRAME		Frame,
	IN	NDIS_HANDLE		PoolHandle
	);

