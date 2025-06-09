/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,       */
/*		1996 - 2002, All Rights Reserved                        */
/*                                                                      */
/* MODULE NAME : osillcnt.h                                             */
/* PRODUCT(S)  : OSI LLC NDIS 3.0 Device Driver for NT                  */
/*	                                                                */
/* MODULE DESCRIPTION :                                                 */
/*                                                                      */
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :                            */
/*				                                        */
/* MODIFICATION LOG :                                                   */
/*  Date     Who   Rev			Comments                        */
/* --------  ---  ------   -------------------------------------------	*/
/* 11/15/02  EJV    08     Added support for Ethertype filtering.	*/
/* 01/15/02  EJV    07     Added support to cfg LSAPs in registry:	*/
/*			     globals OsillcLsapTable, OsillcLsapCount.	*/
/* 05/18/98  DSF    06     Added ReceptionMode				*/
/* 05/13/98  DSF    05     Added SeqNumber field to OPEN_INSTANCE	*/
/* 05/13/98  DSF    04     Added ReadPackets parameter			*/
/*			   Changed DEFAULT_PRIORITY_BOOST to		*/
/*			   NETWORK_INCREMENT				*/
/* 05/07/98  DSF    03     Added RcvListSpinLock			*/
/* 06/19/97  DSF    02     Added Stats                                  */
/* 05/22/96  DSF    01     Initial Release                              */
/*                                                                      */
/************************************************************************/

//
// Device extension.
//
typedef struct _DEVICE_EXTENSION 
{
	PDEVICE_OBJECT	DeviceObject;
	NDIS_HANDLE		NdisProtocolHandle;
	NDIS_STRING		AdapterName;
	NDIS_STRING		MacName;
	PWSTR			BindString;
	PWSTR			ExportString;
	ULONG			DevicesCreated;
} DEVICE_EXTENSION, *PDEVICE_EXTENSION;


#define MAX_OSILLC_REQUESTS	6		// max simultaneous NDIS requests

//
// NDIS Request packet context
//
typedef struct _INTERNAL_REQUEST
{
	LIST_ENTRY     ListElement;
	PIRP           Irp;
	NDIS_REQUEST   Request;
} INTERNAL_REQUEST, *PINTERNAL_REQUEST;


//
// Open context structure
//
typedef struct _OPEN_INSTANCE 
{
	PDEVICE_EXTENSION   DeviceExtension;
	NDIS_HANDLE         AdapterHandle;

    HANDLE				hNotifyEvent;       // Event Handle - Ring 3
    PKEVENT				pNotifyEvent;       // pointer to Event object

	NDIS_HANDLE         ReadPacketPool;
	NDIS_HANDLE         TxPacketPool;
	NDIS_HANDLE         RxPacketPool;
	NDIS_HANDLE         BufferPool;
	NDIS_HANDLE         FramePool;

	KSPIN_LOCK          RcvQSpinLock;
	KSPIN_LOCK          RcvListSpinLock;
	LIST_ENTRY          RcvList;

	KSPIN_LOCK          ReadQSpinLock;
	LIST_ENTRY          ReadIrpList;		// Read IRP pending queue

	KSPIN_LOCK          ResetQSpinLock;
	LIST_ENTRY          ResetIrpList;

	KSPIN_LOCK          RequestQSpinLock;
	LIST_ENTRY          RequestList;		// empty request block list

	PIRP                PendIrp;
	PIRP                SignalIrp;

	INTERNAL_REQUEST	Requests[MAX_OSILLC_REQUESTS];

	ULONG		    SeqNumber;
} OPEN_INSTANCE, *POPEN_INSTANCE;


#define ETHERNET_HEADER_LENGTH	14

typedef struct _OSILLC_RESERVED 
{
	LIST_ENTRY	ListElement;
	PIRP		Irp;
	UINT		HeaderSize;
	UINT		PacketSize;
}  OSILLC_RESERVED, *POSILLC_RESERVED;


#define RESERVED(_p) ((POSILLC_RESERVED)((_p)->ProtocolReserved))

typedef struct _OSILLC_TX_RESERVED 
{
	LIST_ENTRY	ListElement;
	PIRP		Irp;
}  OSILLC_TX_RESERVED, *POSILLC_TX_RESERVED;


#define TX_RESERVED(_p) ((POSILLC_TX_RESERVED)((_p)->ProtocolReserved))


//
// default parameter values
//
#define DEFAULT_PRIORITY_BOOST		IO_NETWORK_INCREMENT
#define DEFAULT_READ_PACKETS		10
#define DEFAULT_TRANSMIT_PACKETS	128
#define DEFAULT_RECEIVE_PACKETS		128

#define RECEPTION_MODE_FAST		0
#define RECEPTION_MODE_SAFE		1

#define MAX_LSAPS			20
#define MAX_ETHERTYPE_IDS		32

extern ULONG OsillcDebugFlag;
extern CCHAR OsillcPriorityBoost;
extern ULONG OsillcReadPackets;
extern ULONG OsillcTransmitPackets;
extern ULONG OsillcReceivePackets;
extern ULONG OsillcReceptionMode;
extern UCHAR OsillcLsapTable[MAX_LSAPS];	// table of LSAPs to filter on
extern UINT  OsillcLsapCount;			// num of LSAPs in table
                                                                // must be one more than max number of entries
extern UCHAR OsillcEthertypeIdsTable[2*(MAX_ETHERTYPE_IDS+1)];	// table of Ethertype IDs to filter on
extern UINT  OsillcEthertypeIdsCount;				// num of Ethertype 2-byte IDs in table

//
// Protocol driver statistics
//
extern ULONG NdisXmitOk;
extern ULONG NdisRcvOk;
extern ULONG NdisXmitError;
extern ULONG NdisRcvError;
extern ULONG NdisRcvUnknown;
extern ULONG NdisXmitInd;
extern ULONG NdisRcvInd;
extern ULONG NdisAllocError;

//
// function prototypes
//

VOID OsillcOpenAdapterComplete
  (
   IN NDIS_HANDLE  ProtocolBindingContext,
   IN NDIS_STATUS  Status,
   IN NDIS_STATUS  OpenErrorStatus
  );

VOID OsillcCloseAdapterComplete
  (
   IN NDIS_HANDLE  ProtocolBindingContext,
   IN NDIS_STATUS  Status
  );

NDIS_STATUS OsillcReceiveIndicate
  (
   IN NDIS_HANDLE ProtocolBindingContext,
   IN NDIS_HANDLE MacReceiveContext,
   IN PVOID HeaderBuffer,
   IN UINT HeaderBufferSize,
   IN PVOID LookAheadBuffer,
   IN UINT LookaheadBufferSize,
   IN UINT PacketSize
  );

VOID OsillcReceiveComplete 
  (
   IN NDIS_HANDLE  ProtocolBindingContext
  );

VOID OsillcRequestComplete
  (
   IN NDIS_HANDLE   ProtocolBindingContext,
   IN PNDIS_REQUEST pRequest,
   IN NDIS_STATUS   Status
  );

VOID OsillcSendComplete 
  (
   IN NDIS_HANDLE   ProtocolBindingContext,
   IN PNDIS_PACKET  pPacket,
   IN NDIS_STATUS   Status
  );

VOID OsillcResetComplete
  (
   IN NDIS_HANDLE  ProtocolBindingContext,
   IN NDIS_STATUS  Status
  );

VOID OsillcStatus
  (
   IN NDIS_HANDLE   ProtocolBindingContext,
   IN NDIS_STATUS   Status,
   IN PVOID         StatusBuffer,
   IN UINT          StatusBufferSize
  );

VOID OsillcStatusComplete
  (
   IN NDIS_HANDLE  ProtocolBindingContext
  );

VOID OsillcTransferDataComplete
  (
   IN NDIS_HANDLE ProtocolBindingContext,
   IN PNDIS_PACKET Packet,
   IN NDIS_STATUS Status,
   IN UINT BytesTransferred
  );

VOID OsillcRemoveReference
  (
   IN PDEVICE_EXTENSION DeviceExtension
  );

NTSTATUS OsillcCleanup
  (
   IN PDEVICE_OBJECT DeviceObject,
   IN PIRP FlushIrp
  );

NTSTATUS OsillcShutdown
  (
   IN PDEVICE_OBJECT DeviceObject,
   IN PIRP Irp
  );

VOID OsillcUnload
  (
   IN PDRIVER_OBJECT DriverObject
  );

NTSTATUS OsillcOpen
  (
   IN PDEVICE_OBJECT DeviceObject,
   IN PIRP Irp
  );

NTSTATUS OsillcClose
  (
   IN PDEVICE_OBJECT DeviceObject,
   IN PIRP Irp
  );

NTSTATUS OsillcWrite 
  (
   IN PDEVICE_OBJECT DeviceObject,
   IN PIRP Irp
  );

NTSTATUS OsillcRead
  (
   IN PDEVICE_OBJECT DeviceObject,
   IN PIRP Irp
  );

NTSTATUS OsillcIoControl 
  (
   IN PDEVICE_OBJECT DeviceObject,
   IN PIRP Irp
  );
