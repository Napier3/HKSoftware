/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*	1996-2006, All Rights Reserved.					*/
/*									*/
/*		    PROPRIETARY AND CONFIDENTIAL			*/
/*									*/
/* MODULE NAME : clnp_w32.c						*/
/* PRODUCT(S)  : MOSI Stack						*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/*		This module provides the interface between the		*/
/*		Connectionless-mode Network Protocol (CLNP) and the	*/
/*		Ethernet Windows 95/98/NT driver.			*/
/*									*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*									*/
/*			clnp_snet_init					*/
/*			clnp_snet_term					*/
/*			clnp_snet_read					*/
/*			clnp_snet_write_raw				*/
/*			clnp_snet_add_multicast_mac			*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 12/01/06  JRB    27     ..write_raw: log frame being sent.		*/
/* 08/17/06  NAV    26     Reduce MAX_MULTICAST_FILTER for AXS4GOOSE    */
/* 08/10/06  NAV    25     Conditionally set MAX_MULTICAST_FILTER	*/
/* 08/03/06  JRB    24     Chk osiallocevt return (it might fail).	*/
/* 07/24/06  JRB    23     clnp_snet_read: del SleepEx call, not needed	*/
/*			   with new OsiReadThreadNT.			*/
/* 07/21/06  JRB    22	   Chg to use SISCO naming conventions.		*/
/* 03/20/06  JRB    21     Del clnp_snet_write, clnp_etype_write.	*/
/*			   Add clnp_snet_write_raw.			*/
/*			   Functions return error if CLNP not initialized.*/
/* 09/09/05  JRB    20     Del unneeded includes.			*/
/* 02/08/05  JRB    19     Fix 802.1Q decoding by chging QueueRxPacket	*/
/*			    to call new clnp_snet_frame_to_udt		*/
/* 11/18/03  JRB    18     Pass NULL as 7th arg to DeviceIoControl,	*/
/*			   avoids risks of data corruption on Win 98	*/
/*			   if data written AFTER DeviceIo.. returns.	*/
/* 12/03/02  ASK    17     Added clnp_etype_write, ethdown_etype.       */
/*			   Changed QueueRxPacket to handle Ethertype	*/
/*			   frames. Include ethertyp.h. 			*/
/* 10/24/02  NAV    16     Add clnp_snet_rx_multicast_stop fun          */
/* 12/07/01  JRB    15     Add more "multicast" functions.		*/
/* 10/08/01  JRB    14     Log if write to OSI LLC driver fails.	*/
/* 05/01/00  JRB    13     Chg "slog" calls to "CLNP_LOG_ERR*" macros.	*/
/* 04/27/00  MDE    12     Lint cleanup					*/
/* 04/06/00  JRB    11     Overhauled to use new Ethernet driver.	*/
/* 04/06/00  JRB    10     Use new subnet function "clnp_snet_free"	*/
/*			   instead of "free_lpdu" flag. More flexible.	*/
/* 09/13/99  MDE    09     Added SD_CONST modifiers			*/
/* 08/05/99  JRB    08     Create hMMSEvent for NT too.			*/
/* 12/02/98  JRB    07     Added clnp_snet_add_multicast_mac function.	*/
/* 12/02/98  JRB    06     Del common functs. Instead use "clnp_eth.c".	*/
/* 11/10/98  JRB    05     Use global hMMSEvent for WIN95.		*/
/*			   Call SetEvent from list_put for WINNT.	*/
/* 08/13/98  JRB    04     Lint cleanup.				*/
/* 06/19/98  JRB    03     Update NT code to work with V2.10 driver.	*/
/* 02/16/98  EJV    02     Use func _beginthread instead of CreateThread*/
/*                         Use func   _endthread instead of   ExitThread*/
/*                         Eliminated warning for var ArmComplete.	*/
/* 12/01/97  EJV    01     Created from clnp_e95.c and ethsub.c		*/
/************************************************************************/
#include "glbtypes.h"
#include "sysincs.h"

#ifdef DEBUG_SISCO
SD_CONST static ST_CHAR *SD_CONST thisFileName = __FILE__;  /* Define for SLOG mechanism    */
#endif
#include "clnp_log.h"

#include "clnp_usr.h"
#include "clnp_sne.h"
#include "clnp_llc.h"

#include "ethsub.h"
#include "ethertyp.h"

/*----------------------------------------------------------------------*/
/* NOTE: This module interfaces to the Ethernet driver for Win95/98/NT.	*/
/*       It calls functions in the "marben26\osiam\l95\src\ethsub.c"	*/
/*       which was modified for MMS_LITE.				*/
/*       MMS_LITE must be defined when "ethsub.c" is compiled.		*/
/*----------------------------------------------------------------------*/

/*----------------------------------------------------------------------*/
/* Global variables needed by ethsub.c					*/
/*----------------------------------------------------------------------*/
LLC_CONTEXT GCC;		/* General Current Context */
LLC_CONTEXT *GCCP;		/* General Current Context Pointer */

DWORD Priority = THREAD_PRIORITY_NORMAL;
int MaxWriteOut = 5;
int MaxReadOut = 5;
int FramesPerBlock = 5;
int DriverID = -1;
int ReceptionMode = 0;		/* Fast mode				*/

int nSubnets = 1;		/* Don't allow multiple subnets.	*/
BOOL bOsiRequired = TRUE;	/* This code called only if OSI needed	*/
BOOL bServiceControl = FALSE;
int llc_trace_level;

/*----------------------------------------------------------------------*/
/* defines and variables local to this module				*/
/*----------------------------------------------------------------------*/
HANDLE hMMSEvent;	/* Event Object to be triggered */

BOOL   bNT;

/************************************************************************/
/*			clnp_snet_init					*/
/*----------------------------------------------------------------------*/
/* This function will initialize the interface between the CLNP and	*/
/* underlying sub-network.						*/
/*									*/
/* Parameters:								*/
/*	CLNP_PARAM	*clnp_param	POinter to CLNP parameters.	*/
/*									*/
/* Return:								*/
/*	SD_SUCCESS (0)		if initialization successful		*/
/*	error code		otherwise				*/
/************************************************************************/
ST_RET clnp_snet_init (CLNP_PARAM *param)
{
OSVERSIONINFO OsVersion;

  /* Create Event Semaphore.  Use for Win95 OR for NT.			*/
  if (hMMSEvent == NULL)
    hMMSEvent = CreateEvent (NULL,	// No Security
                          FALSE,	// Automatic reset.
                          FALSE,	// Initially non-signaled.
                          NULL);

  /*----------------------------*/
  /* Determine OS Version	*/
  /*----------------------------*/
  OsVersion.dwOSVersionInfoSize = sizeof (OsVersion);
  GetVersionEx (&OsVersion);
  if (OsVersion.dwPlatformId == VER_PLATFORM_WIN32_NT)
    bNT = SD_TRUE;
  else
    bNT = SD_FALSE;

  GCCP = &GCC;		/* Init global pointer used by ethsapon.	*/
  GCCP->hFile = INVALID_HANDLE_VALUE;
  ethsapon ("osillc1");
  if (GCCP->hFile == INVALID_HANDLE_VALUE)
    {
    CLNP_LOG_ERR0 ("Error starting OSI LLC driver. OSI support disabled.");
    return (SNET_ERR_DRV_OPEN);
    }
  return (SD_SUCCESS);
}

/************************************************************************/
/*			clnp_snet_term					*/
/*----------------------------------------------------------------------*/
/* This function will terminate the interface between the CLNP and	*/
/* undelying sub-network.						*/
/*									*/
/* Parameters:								*/
/*	ST_VOID			none					*/
/*									*/
/* Return:								*/
/*	SD_SUCCESS (0)		if termination successful		*/
/*	error code		otherwise				*/
/************************************************************************/
ST_RET clnp_snet_term (ST_VOID)
{
ST_RET ret;

  ethsapoff ();
  ret = SD_SUCCESS;		/* assume termination successful	*/
  return (ret);
}


/************************************************************************/
/*			clnp_snet_read					*/
/*----------------------------------------------------------------------*/
/* This function will receive a LPDU from a sub-network.		*/
/* NOTE: it depends on QueueRxPacket to do most decoding and put packets*/
/*       on a queue. This function just gets them off the queue and	*/
/*       passes them up.						*/
/*									*/
/* Parameters:								*/
/*	SN_UNITDATA *sn_req	Pointer to Sub-network Unit Data request*/
/*				to be received.				*/
/*									*/
/* Return:								*/
/*	SD_SUCCESS (0)		if read successful			*/
/*	error code		otherwise				*/
/************************************************************************/
ST_RET clnp_snet_read (SN_UNITDATA *sn_req)
{
ST_RET     ret= SNET_ERR_READ;	/* assume read failed (nothing arrived)	*/
SN_EVENT *evt;

  evt = osigetevt ();
  if (evt)
    {		/* Got a packet		*/
    memcpy (sn_req, &evt->sn_req, sizeof (SN_UNITDATA));
    osifreeevt (evt);
    ret = SD_SUCCESS;
    }

  return (ret);
}

/************************************************************************/
/*			clnp_snet_add_multicast_mac			*/
/*----------------------------------------------------------------------*/
/* This function will add the MAC to the set of multicast addresses	*/
/* on which to accept incoming packets.					*/
/*									*/
/* Parameters:								*/
/*	ST_UCHAR  *mac_buf	Pointer to buffer for MAC address.	*/
/*									*/
/* Return:								*/
/*	SD_SUCCESS (0)		if successfully added			*/
/*	error code		otherwise				*/
/************************************************************************/
ST_RET clnp_snet_add_multicast_mac (ST_UCHAR *mac_buf)
{
DWORD filter;

  if (GCCP==NULL)
    {
    CLNP_LOG_ERR0 ("clnp_snet_add_multicast_mac: CLNP not initialized.");
    return (SNET_ERR_DRV_ADD_ES_ADDR);
    }
     
  /* Using the OID_802_3_MULTICAST_LIST command to add a multicast,	*/
  /* disables previous multicasts (like ALL-ES, ALL-IS). NOT GOOD.	*/
  /* So, instead, just enable ALL multicasts here.			*/
  filter = NDIS_PACKET_TYPE_DIRECTED | NDIS_PACKET_TYPE_ALL_MULTICAST;
  if (SetOid (GCCP->hFile, OID_GEN_CURRENT_PACKET_FILTER, 
            (ST_UCHAR *)&filter, sizeof(DWORD)) == FALSE)
    return (SNET_ERR_DRV_ADD_ES_ADDR);

  return (SD_SUCCESS);
}

/************************************************************************/
/*			clnp_snet_free					*/
/* Upper (CLNP) layer calls this function to free anything allocated	*/
/* for the SN-UNITDATA PDU.						*/
/************************************************************************/
ST_VOID clnp_snet_free (SN_UNITDATA *sn_req)
  {
  /* Free the lpdu which was allocated by QueueRxPacket.		*/
  /* NOTE: Free must be thread-safe because lpdu was "allocated" from	*/
  /*       another thread (see QueueRxPacket).				*/
  free (sn_req->lpdu);
  }

/************************************************************************/
/* ProcessReadBlock							*/
/* Based on function in "ethsub.c" used by MMS-EASE.			*/
/* Only used for NT (i.e. bNT = TRUE).					*/
/************************************************************************/

void ProcessReadBlock (OVERLAPPED *ovlp)
  {
DWORD i;
OSILLC_PACKET_BLOCK *PacketBlock;
LLC_CONTEXT *gccp;
int result;
DWORD error;
RD_WR_BLOCK *readBlock;

  readBlock = (RD_WR_BLOCK *) ovlp->hEvent;
  PacketBlock = (OSILLC_PACKET_BLOCK *) readBlock->pb;
  gccp = readBlock->gccp;

  /* Calculate next expected sequence number */
  gccp->seq = PacketBlock->SeqNumber + 1;

  for (i = 0; i < PacketBlock->NumberOfPackets; i++)
    {
    QueueRxPacket (PacketBlock->PacketData[i].Data);
    }

  if (gccp->hFile != INVALID_HANDLE_VALUE)
    {
    PacketBlock->NumberOfPackets = FramesPerBlock;
    result = ReadFileEx (gccp->hFile, PacketBlock, 
                 FramesPerBlock * sizeof (OSILLC_PACKET_BLOCK), 
                 ovlp,
                 (LPOVERLAPPED_COMPLETION_ROUTINE) ReadCompletion);
    if (!result)
      {
      error = GetLastError();
      CLNP_LOG_ERR1 ("ReadFileEx () failed, error = %d", error);
      free (PacketBlock);
      free (readBlock);
      free (ovlp);
      }
    }
  }

/************************************************************************/
/* OsiReadThread							*/
/* Based on function in "ethsub.c" used by MMS-EASE.			*/
/* Only used for 95/98 (i.e. bNT = FALSE).				*/
/************************************************************************/

void OsiReadThread (LPDWORD lpdwParam)
  {
LLC_CONTEXT *gccp = (LLC_CONTEXT *) lpdwParam;
OVERLAPPED ovlp;
HANDLE hEvent;
int result;
DWORD cbRet;
DWORD dwErrorCode;
OSILLC_PACKET_BLOCK	*PacketBlock;
DWORD i;

  hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);

  PacketBlock = (OSILLC_PACKET_BLOCK *) calloc (FramesPerBlock, 
  					    sizeof (OSILLC_PACKET_BLOCK));

  while (gccp->hFile != INVALID_HANDLE_VALUE)
    {
    memset (&ovlp, '\0', sizeof (OVERLAPPED));
    ovlp.hEvent = hEvent;

    PacketBlock->NumberOfPackets = FramesPerBlock;
    result = DeviceIoControl (gccp->hFile, 
                                IOCTL_OSILLC_READ, 
				PacketBlock, 
    		                sizeof (OSILLC_PACKET_BLOCK),
				PacketBlock, 
    		                sizeof (OSILLC_PACKET_BLOCK),
				NULL, 
				&ovlp);

    if (!result)
      {
      dwErrorCode = GetLastError();

      if (dwErrorCode == ERROR_IO_PENDING)
        result = GetOverlappedResult (gccp->hFile, &ovlp, &cbRet, TRUE);
      }
  
    if (result == TRUE)
      {
      if (PacketBlock->SeqNumber != gccp->seq)
        {
        CLNP_LOG_ERR2 ("Frame received out of sequence (E=%d R=%d)", 
              gccp->seq, PacketBlock->SeqNumber);
	}
      gccp->seq = PacketBlock->SeqNumber + 1;

      for (i = 0; i < PacketBlock->NumberOfPackets; i++)
        {
        QueueRxPacket (PacketBlock->PacketData[i].Data);
        }
      }
    else
      {
      dwErrorCode = GetLastError();
      }
    }

  ExitThread (1);
  }

/************************************************************************/
/*			QueueRxPacket					*/
/* This is called from ProcessReadBlock or OsiReadThread		*/
/* to queue up a received packet.					*/
/************************************************************************/
void QueueRxPacket (ST_UCHAR *framep)
  {
SN_EVENT *evt;
ST_RET retcode;

  /* The driver is not supposed to pass up packets that we sent,	*/
  /* but the WIN32 driver does. THROW THEM AWAY NOW.			*/
  /* NOTE: SRC MAC starts in 6th byte in raw frame (framep).		*/
  if (memcmp (clnp_param.loc_mac, &framep[CLNP_MAX_LEN_MAC], CLNP_MAX_LEN_MAC) == 0)
    return;	/* This is echo of packet we sent. Throw it away.	*/
    
  /* Allocate event struct.	*/
  evt = osiallocevt ();

  /* If alloc failed, this packet is lost. Don't log here because	*/
  /* we are in completion routine. See error logging in "ethsub.c".	*/
  if (evt != NULL)
    {
    /* Allocate LPDU. Must be "thread-safe" because freed from another thread.*/
    /* CLNP layer calls "clnp_snet_free" to free it.			*/
    /* Allocate max to avoid fragmenting memory.				*/
    evt->sn_req.lpdu = malloc (ETHE_MAX_LEN_UDATA);

    /* Fill in "evt->sn_req".	*/
    /* Can't access len of raw frame, so just assume max ETHE_MAX_LEN_LSDU.*/
    retcode = clnp_snet_frame_to_udt ((ST_UINT8 *)framep, ETHE_MAX_LEN_LSDU, &evt->sn_req, ETHE_MAX_LEN_UDATA);
    if (retcode == SD_SUCCESS)
      osiputevt (evt);	/* Put event on queue.	*/
    else
      {	/* bad frame. Free event struct now.	*/
      free (evt->sn_req.lpdu);
      osifreeevt (evt);
      }
    }	/* if (evt != NULL)	*/
  }
/************************************************************************/
/*			clnp_snet_set_multicast_filter			*/
/*----------------------------------------------------------------------*/
/* This function sets the multicast MAC addresses on which to accept	*/
/* incoming packets.							*/
/* IMPORTANT: If the ES-IS protocol is needed (e.g. for 7-Layer OSI	*/
/*	stack), the ALL-ES & ALL-IS MACs must be included in the list	*/
/*	of MAC addresses.						*/
/*									*/
/* Parameters:								*/
/*	ST_UCHAR  *mac_list	Pointer to list of MAC addresses.	*/
/*	ST_INT     num_macs	Number of MAC addresses in list.	*/
/*									*/
/* Return:								*/
/*	SD_SUCCESS (0)		if successfully set			*/
/*	error code		otherwise				*/
/************************************************************************/
#ifdef AXS4GOOSE
#define MAX_MULTICAST_FILTER	14	
#else
#define MAX_MULTICAST_FILTER	6	//DEBUG: what can Win handle??
#endif
ST_RET clnp_snet_set_multicast_filter (ST_UCHAR *mac_list,
				ST_INT num_macs)
  {
DWORD filter;

  if (GCCP==NULL)
    {
    CLNP_LOG_ERR0 ("clnp_snet_set_multicast_filter: CLNP not initialized.");
    return (SNET_ERR_DRV_ADD_ES_ADDR);
    }
     
  if (num_macs > MAX_MULTICAST_FILTER)	/* don't exceed max*/
    return (SNET_ERR_DRV_ADD_ES_ADDR);

  if (SetOid (GCCP->hFile, OID_802_3_MULTICAST_LIST,
             mac_list, num_macs * 6) == FALSE)
    return (SNET_ERR_DRV_ADD_ES_ADDR);

  filter = NDIS_PACKET_TYPE_DIRECTED | NDIS_PACKET_TYPE_MULTICAST;
  if (SetOid (GCCP->hFile, OID_GEN_CURRENT_PACKET_FILTER, 
            (PBYTE)&filter, sizeof(DWORD)) == FALSE)
    return (SNET_ERR_DRV_ADD_ES_ADDR);

  return (SD_SUCCESS);
  }

/************************************************************************/
/*			clnp_snet_rx_all_multicast_start		*/
/*----------------------------------------------------------------------*/
/* This function tells the driver to BEGIN accepting ALL incoming	*/
/* multicast packets.							*/
/*									*/
/* Parameters:								*/
/*	NONE								*/
/*									*/
/* Return:								*/
/*	SD_SUCCESS (0)		if successfully STARTED discovery mode	*/
/*	error code		otherwise				*/
/************************************************************************/
ST_RET clnp_snet_rx_all_multicast_start (ST_VOID)
  {
DWORD filter;

  if (GCCP==NULL)
    {
    CLNP_LOG_ERR0 ("clnp_snet_rx_all_multicast_start: CLNP not initialized.");
    return (SNET_ERR_DRV_ADD_ES_ADDR);
    }
     
  filter = NDIS_PACKET_TYPE_DIRECTED | NDIS_PACKET_TYPE_ALL_MULTICAST;
  if (SetOid (GCCP->hFile, OID_GEN_CURRENT_PACKET_FILTER, 
            (ST_UCHAR *)&filter, sizeof(DWORD)) == FALSE)
    return (SNET_ERR_DRV_ADD_ES_ADDR);

  return (SD_SUCCESS);
  }
/************************************************************************/
/*			clnp_snet_rx_all_multicast_stop			*/
/*----------------------------------------------------------------------*/
/* This function tells the driver to STOP accepting ALL incoming	*/
/* multicast packets.							*/
/* NOTE: If multicast filters were previously set up by calling		*/
/*	gse_set_multicast_filter, they will automatically be active	*/
/*	again when this function returns.				*/
/*									*/
/* Parameters:								*/
/*	NONE								*/
/*									*/
/* Return:								*/
/*	SD_SUCCESS (0)		if successfully STOPPED discovery mode	*/
/*	error code		otherwise				*/
/************************************************************************/
ST_RET clnp_snet_rx_all_multicast_stop (ST_VOID)
  {
DWORD filter;

  if (GCCP==NULL)
    {
    CLNP_LOG_ERR0 ("clnp_snet_rx_all_multicast_stop: CLNP not initialized.");
    return (SNET_ERR_DRV_ADD_ES_ADDR);
    }
     
  filter = NDIS_PACKET_TYPE_DIRECTED | NDIS_PACKET_TYPE_MULTICAST;
  if (SetOid (GCCP->hFile, OID_GEN_CURRENT_PACKET_FILTER, 
            (PBYTE)&filter, sizeof(DWORD)) == FALSE)
    return (SNET_ERR_DRV_ADD_ES_ADDR);

  return (SD_SUCCESS);
  }

/************************************************************************/
/*			clnp_snet_rx_multicast_stop			*/
/*----------------------------------------------------------------------*/
/* This function tells the driver to STOP accepting incoming	        */
/* multicast packets.							*/
/*									*/
/* Parameters:								*/
/*	NONE								*/
/*									*/
/* Return:								*/
/*	SD_SUCCESS (0)		if successfully STOPPED filter mode	*/
/*	error code		otherwise				*/
/************************************************************************/

ST_RET clnp_snet_rx_multicast_stop (ST_VOID)
  {
DWORD filter;

  if (GCCP==NULL)
    {
    CLNP_LOG_ERR0 ("clnp_snet_rx_multicast_stop: CLNP not initialized.");
    return (SNET_ERR_DRV_ADD_ES_ADDR);
    }
     
  filter = NDIS_PACKET_TYPE_DIRECTED;
  if (SetOid (GCCP->hFile, OID_GEN_CURRENT_PACKET_FILTER, 
            (PBYTE)&filter, sizeof(DWORD)) == FALSE)
    return (SNET_ERR_DRV_ADD_ES_ADDR);

  return (SD_SUCCESS);
  }

/************************************************************************/
/*			clnp_snet_write_raw				*/
/*----------------------------------------------------------------------*/
/* This function will send a LPDU to a sub-network.			*/
/*									*/
/* Return:								*/
/*	SD_SUCCESS (0)		if write successful			*/
/*	error code		otherwise				*/
/************************************************************************/
ST_RET clnp_snet_write_raw (
	ST_UCHAR *framePtr,	/* Pointer to complete frame including MACs*/
	size_t    frameLen)	/* Length of complete frame		*/
  {
int lg;
OVERLAPPED *ovlp;
ST_UCHAR *framep;	/* pointer to raw frame	*/
int status;
int i;
ST_RET retcode = SD_SUCCESS;	/* assume success	*/

  CLSNS_LOG_REQ1 ("Sending Raw Ethernet frame (len = %d)", frameLen);
  CLSNS_LOGH_REQ (frameLen, framePtr);

  /* CRITICAL: Call SleepEx now to enter "alertable" state, just in 	*/
  /* case user never did. This allows completion routines to be called.	*/
  SleepEx (0, TRUE);		/* alertable	*/

  /* Block until there's room in the pipe */
  while (NumWriteOut >= MaxWriteOut)
    SleepEx (100, TRUE);

  // For NT, allocate required structures dynamically
  // For 95/98, find available structures
  if (bNT)
    {
    framep = (ST_UCHAR *) calloc (1, ETHE_MAX_LEN_LSDU);
    ovlp = (OVERLAPPED *) calloc (1, sizeof (OVERLAPPED));
    }
  else
    {
    for (i = 0; i < MaxWriteOut; i++)
      {
      if (!GCCP->pWriteEvents[i].inuse)
        break;
      }

    if (i == MaxWriteOut)
      {
      CLNP_LOG_ERR0 ("No write buffers available");
      return (SNET_ERR_WRITE);	/* write failed. Can't continue so return now.*/
      }

    // This block is available - use it
    GCCP->pWriteEvents[i].inuse = 1;

    framep = GCCP->pWriteEvents[i].framep;
    ovlp = GCCP->pWriteEvents[i].ovlp;
    memset (ovlp, 0, sizeof (OVERLAPPED));
    ovlp->hEvent = GCCP->pWriteEvents[i].hEvent;
    }

  /* Use args to fill in "framep" struct, and set the frame length "lg".	*/
  memcpy (framep, framePtr, frameLen);
  /* Set lg (total frame length)	*/
  lg = frameLen < 60 ? 60 : frameLen;	/* minumum len = 60	*/

  if (bNT)
    {
    NumWriteOut++;
    ovlp->hEvent = (HANDLE) framep;
    if (WriteFileEx (GCCP->hFile, 
                     framep, lg, 
                     ovlp,
                     (LPOVERLAPPED_COMPLETION_ROUTINE) WriteCompletion) == FALSE)
      {
      CLNP_LOG_ERR0 ("Error writing to OSI LLC driver.");
      NumWriteOut--;
      free (framep);
      free (ovlp);
      retcode = SNET_ERR_WRITE;	/* write failed */
      }
    }
  else
    {
    EnterCriticalSection (&csOsiList);
    NumWriteOut++;
    LeaveCriticalSection (&csOsiList);
    if (DeviceIoControl (GCCP->hFile, 
		  IOCTL_OSILLC_WRITE, 
                         framep, lg, NULL, 0, NULL, ovlp) == FALSE)
      {
      // Make sure return code is IO_PENDING
      status = GetLastError ();
      if (status != ERROR_IO_PENDING)
        {
        CLNP_LOG_ERR1 ("Error %d writing to OSI LLC driver.", status);
        EnterCriticalSection (&csOsiList);
        NumWriteOut--;
        LeaveCriticalSection (&csOsiList);
        retcode = SNET_ERR_WRITE;	/* write failed */
        }
      }
    }
  return (retcode);
  }
