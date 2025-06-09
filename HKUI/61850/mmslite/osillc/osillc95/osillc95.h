//---------------------------------------------------------------------------
//
// File:         osillc95.h
//
// Copyright (c) 1998 - 2002 SISCO, Inc. All rights reserved.
//
// Description:  Driver internal definitions.
//
// Author:       A. Shajenko/Stratos Technology, Inc.
//
// History:
// 13-Sep-98     A. Shajenko     Implemented.
// 01-Jan-02     SISCO (EJV)     Added support for cfg of LSAPs in registry
//				 in DEVICE_EXTENSION struct.
// 18-Nov-02     SISCO (EJV)     Added support for Ethertype filtering.
//
//---------------------------------------------------------------------------

#ifndef _OSILLC95_H
#define _OSILLC95_H

#define  USE_NDIS

#define  DEVICE_MAIN
#include <vtoolsc.h>
#undef   DEVICE_MAIN

#include "osillc.h"

#pragma pack(1)

//---------------------------------------------------------------------------
//
// OSILLC95 VxD Definitions.
//
#define OSILLC98_Major		2
#define OSILLC98_Minor		0
#define OSILLC98_DeviceID	UNDEFINED_DEVICE_ID
#define OSILLC98_Init_Order	UNDEFINED_INIT_ORDER


#define TRANSPORT_NAME "OSILLC98"

#define OSILLC98_NDIS_MAJOR_VERSION	0x03
#define OSILLC98_NDIS_MINOR_VERSION	0x0A

#define OSILLC_MAX_OPENS	10				// max number of open instances
#define OSILLC_MAX_IRPS		100				// max number of IRPS to allocate

//
// Default values for Registry parameters
//
#define OSILLC_DEFAULT_MAX_BUFFERS	200
#define OSILLC_DEFAULT_MAX_FRAMES	200
#define OSILLC_DEFAULT_DEBUG_LEVEL	1

//
// Ethernet 802.3 frame definitions
//
#define  ETHERNET_HEADER_LENGTH   14
#define  ETHERNET_DATA_LENGTH     1500
#define  ETHERNET_PACKET_LENGTH   1514

//
// Pending status that is required by the Win9X kernel (do not change!)
//
#ifdef	ERROR_IO_PENDING
#undef	ERROR_IO_PENDING
#endif
#define	ERROR_IO_PENDING	(DWORD)-1

typedef OVERLAPPED *POVERLAPPED;

//---------------------------------------------------------------------------
//
// Reserved Packet.
//
typedef struct _IRP *PIRP;
typedef struct _FRAME *PFRAME;
typedef struct _PACKET_RESERVED
{
//	NDIS_PACKET	Packet;
	PFRAME		pFrame;
	PIRP		pIrp;
} PACKET_RESERVED, * PPACKET_RESERVED;

#define RESERVED(_p)	((PPACKET_RESERVED)((_p)->ProtocolReserved))

//---------------------------------------------------------------------------
//
// Frame Item.
//
typedef struct _IRP *PIRP;
typedef struct _FRAME
{
	LIST_ENTRY		ListEntry;
	PIRP			pIrp;
	PNDIS_PACKET	pPacket;
	DWORD			dwFrameSize;	// frame data buffer size in bytes
	DWORD			dwHeaderSize;
	DWORD			dwPacketSize;
	UCHAR			Data[];
} FRAME, * PFRAME;

//---------------------------------------------------------------------------
//
// Frame Pool
//
typedef struct _FRAME_POOL
{
	DWORD		dwPoolItems;		// number of items in pool
	DWORD		dwItemSize;			// item size in bytes
	DWORD		dwPoolSize;			// total pool buffer size in bytes
	DWORD		dwPoolPages;		// number of 4K pages spanned by the pool
	PVOID		pPoolAddress;		// pointer to pool array
	LIST_ENTRY	FreeList;			// list of empty frames
	DWORD		dwFreeItems;		// number of free items in pool
} FRAME_POOL, * PFRAME_POOL;

//---------------------------------------------------------------------------
//
// IRP Item
//
typedef struct _OPEN_INSTANCE *POPEN_INSTANCE;
typedef struct _IRP 
{
	LIST_ENTRY		ListEntry;
	IOCTLPARAMS		IoctlParms;
//	POPEN_INSTANCE	OpenInstance;
	PNDIS_PACKET	pPacket;		// pointer to associated NDIS packet
	NDIS_REQUEST	Request;		// used for calls to NdisRequest
} IRP, * PIRP;

//---------------------------------------------------------------------------
//
// IRP Pool
//
typedef struct _IRP_POOL
{
	DWORD		dwPoolItems;		// number of items in pool
	DWORD		dwItemSize;			// item size in bytes
	DWORD		dwPoolSize;			// total pool buffer size in bytes
	DWORD		dwPoolPages;		// number of 4K pages spanned by the pool
	PVOID		pPoolAddress;		// pointer to pool array
	LIST_ENTRY	FreeList;			// list of empty frames
	DWORD		dwFreeItems;		// number of free items in pool
} IRP_POOL, * PIRP_POOL;

//---------------------------------------------------------------------------
//
// Open Instance object
//
typedef struct _OPEN_INSTANCE 
{
    LIST_ENTRY		ListEntry;

    NDIS_HANDLE     AdapterHandle;
    NDIS_HANDLE     BindAdapterContext;

	BOOL			bBound;				// if TRUE we're bound to a MAC
	BOOL			bUnbinding;			// if TRUE we're unbinding from a MAC
	BOOL			bClosing;			// if TRUE we're closing

	NDIS_STATUS		Status;
	NDIS_STATUS		ResetStatus;

    UINT			Medium;				// medium supported by MAC driver
	UINT			MediumArraySize;	// number of media in MediumArray
	NDIS_MEDIUM		MediumArray[10];	// MAC will pick a medium from this array

    DWORD           hDevice;			// device handle
	DWORD			dwProcessId;		// process id of calling process

    NDIS_HANDLE     PacketPool;
    NDIS_HANDLE     BufferPool;

	FRAME_POOL		FramePool;
	IRP_POOL		IrpPool;

	PIRP			pPendingIrp;

    LIST_ENTRY      RcvList;

    LIST_ENTRY      ReadIrpList;
    LIST_ENTRY      RequestIrpList;
    LIST_ENTRY      ResetIrpList;

	OSILLC_GET_STATS	Stats;

	ULONG		    	SeqNumber;
} OPEN_INSTANCE;

//---------------------------------------------------------------------------
//
// Global device extension
//

#define MAX_LSAPS	20
#define MAX_ETHERTYPE_IDS	32

typedef struct _DEVICE_EXTENSION 
{
	PDRIVER_OBJECT	DriverObject;
	NDIS_HANDLE		NdisProtocolHandle;

//	DWORD			DebugLevel;
	DWORD			dwNumberBuffers;	// number of NDIS_BUFFER structs to allocate
	DWORD			dwNumberFrames;		// number of FRAME structs to allocate

	DWORD			LsapCount;		// Num of LSAPs
	UCHAR			LsapTable[MAX_LSAPS];	// table of LSAPs to filter on

        UCHAR  EthertypeIdsTable[2*MAX_ETHERTYPE_IDS]; // table of Ethertype IDs to filter on
        DWORD  EthertypeIdsCount;		       // num of Ethertype 2-byte IDs in table

	DWORD			dwOpenCount;
	LIST_ENTRY		OpenList;
} DEVICE_EXTENSION, *PDEVICE_EXTENSION;

extern PDEVICE_EXTENSION g_DeviceExtension;

#pragma pack()


//
// Osillc Function prototypes
//
DWORD OsillcOpenAdapter(POPEN_INSTANCE pOpen, PIOCTLPARAMS p);
VOID NDIS_API OsillcOpenAdapterComplete(NDIS_HANDLE ProtocolBindingContext,
										NDIS_STATUS Status, NDIS_STATUS OpenErrorStatus);
DWORD OsillcCloseAdapter(POPEN_INSTANCE pOpen, PIOCTLPARAMS p);
VOID NDIS_API OsillcCloseAdapterComplete(NDIS_HANDLE ProtocolBindingContext, NDIS_STATUS Status);
DWORD OsillcRead(POPEN_INSTANCE pOpen, PIOCTLPARAMS p);
DWORD OsillcWrite(POPEN_INSTANCE pOpen, PIOCTLPARAMS p);

NDIS_STATUS NDIS_API OsillcReceiveIndicate(NDIS_HANDLE ProtocolBindingContext,
										   NDIS_HANDLE MacReceiveContext,
										   PVOID HeaderBuffer, UINT HeaderBufferSize,
										   PVOID LookAheadBuffer, UINT LookaheadBufferSize,
										   UINT PacketSize);
VOID NDIS_API OsillcReceiveComplete(NDIS_HANDLE ProtocolBindingContext);
DWORD OsillcRequest(POPEN_INSTANCE pOpen, PIOCTLPARAMS p);
VOID NDIS_API OsillcRequestComplete(NDIS_HANDLE ProtocolBindingContext, PNDIS_REQUEST pRequest, 
									NDIS_STATUS Status);
VOID NDIS_API OsillcSendComplete(NDIS_HANDLE ProtocolBindingContext, PNDIS_PACKET pPacket, 
								 NDIS_STATUS Status);
VOID OsillcReset(PNDIS_STATUS pStatus, POPEN_INSTANCE pOpen);
VOID NDIS_API OsillcResetComplete(NDIS_HANDLE ProtocolBindingContext, NDIS_STATUS Status);
VOID NDIS_API OsillcStatus(NDIS_HANDLE ProtocolBindingContext, NDIS_STATUS Status,
						   PVOID StatusBuffer, UINT StatusBufferSize);
VOID NDIS_API OsillcStatusComplete(NDIS_HANDLE ProtocolBindingContext);
VOID OsillcAllocatePacketBuffer(PNDIS_STATUS pStatus, POPEN_INSTANCE pOpen,
                                     PNDIS_PACKET *pPacket, // 17.2.97
									 PDIOCPARAMETERS  pDiocParms,
									 DWORD				FunctionCode );

VOID NDIS_API OsillcTransferDataComplete(NDIS_HANDLE ProtocolBindingContext, PNDIS_PACKET Packet,
										 NDIS_STATUS Status, UINT BytesTransferred);


VOID OsillcRemoveReference(PDEVICE_EXTENSION DeviceExtension);
VOID OsillcCleanUp(PNDIS_STATUS Status, POPEN_INSTANCE Open);
NTSTATUS NDIS_API OsillcShutdown(PDEVICE_OBJECT DeviceObject);
VOID NDIS_API OsillcUnload();


VOID NDIS_API OsillcBindAdapter(PNDIS_STATUS Status, NDIS_HANDLE BindAdapterContext,
								PNDIS_STRING AdapterName, PVOID SystemSpecific1,
								PVOID SystemSpecific2);
VOID NDIS_API OsillcUnbindAdapter(PNDIS_STATUS Status, NDIS_HANDLE, NDIS_HANDLE);


//DWORD _stdcall OsillcIOControl(DWORD dwService, PDIOCPARAMETERS lpDIOCParms);

// framepool.c
BOOL OsillcAllocateFramePool(PFRAME_POOL pFramePool, DWORD dwNumberOfFrames,
							 DWORD dwFrameSize);
VOID OsillcFreeFramePool(PFRAME_POOL pFramePool);
PFRAME OsillcAllocateFrame(PFRAME_POOL pFramePool, BOOL bProtect);
VOID OsillcFreeFrame(PFRAME pFrame, PFRAME_POOL pFramePool, BOOL bProtect);

// irppool.c
BOOL OsillcAllocateIrpPool(PIRP_POOL pIrpPool, DWORD dwNumberOfIrps);
VOID OsillcFreeIrpPool(PIRP_POOL pIrpPool);
PIRP OsillcAllocateIrp(PIRP_POOL pIrpPool, BOOL bProtect);
VOID OsillcFreeIrp(PIRP pIrp, PIRP_POOL pIrpPool, BOOL bProtect);


//ULONG strlen( BYTE *s );

//#define strcat(d, s)  NdisMoveMemory(d+strlen(d), s, strlen(s) )
//#define strcpy(d, s)  NdisMoveMemory(d, s, strlen(s))

//
// where is memset defined?  okay, let's make one!
//
/*
#define memset( _S, _C, _N )\
{\
	UCHAR* _pS = _S;\
	ULONG  _I  = _N;\
	while ( _I-- )\
	{\
		*_pS++ = _C;\
	}\
}
*/
/////////////////////////////////////////////////////////////////////////////
//// Debug Macros

extern DWORD g_DebugLevel;

#if DEBUG

#define DEBUGERROR0(a)       \
	{if (g_DebugLevel > 0) dprintf("Osillc95: %s %d " a "\n",__FILE__,__LINE__);}
#define DEBUGERROR1(a,b) 	 \
	{if (g_DebugLevel > 0) dprintf("Osillc95: %s %d " a "\n",__FILE__,__LINE__,b);}
#define DEBUGERROR2(a,b,c) 	 \
	{if (g_DebugLevel > 0) dprintf("Osillc95: %s %d " a "\n",__FILE__,__LINE__,b,c);}
#define DEBUGERROR3(a,b,c,d) \
	{if (g_DebugLevel > 0) dprintf("Osillc95: %s %d " a "\n",__FILE__,__LINE__,b,c,d);}
#define DEBUGTRACE0(a)		 \
	{if (g_DebugLevel > 1) dprintf("Osillc95: %s %d " a "\n",__FILE__,__LINE__);}
#define DEBUGTRACE1(a,b) 	 \
	{if (g_DebugLevel > 1) dprintf("Osillc95: %s %d " a "\n",__FILE__,__LINE__,b);}
#define DEBUGTRACE2(a,b,c)	 \
	{if (g_DebugLevel > 1) dprintf("Osillc95: %s %d " a "\n",__FILE__,__LINE__,b,c);}
#define DEBUGTRACE3(a,b,c,d) \
	{if (g_DebugLevel > 1) dprintf("Osillc95: %s %d " a "\n",__FILE__,__LINE__,b,c,d);}

#else

#define DEBUGERROR0(a)	
#define DEBUGERROR1(a,b)	
#define DEBUGERROR2(a,b,c)	
#define DEBUGERROR3(a,b,c)	
#define DEBUGTRACE0(a)	
#define DEBUGTRACE1(a,b)	
#define DEBUGTRACE2(a,b,c)	
#define DEBUGTRACE3(a,b,c)	

#endif

#endif _OSILLC95_H

// end of osillc95.h
