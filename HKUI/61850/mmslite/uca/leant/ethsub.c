/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,       */
/*              1996 - 2006 All Rights Reserved                         */
/*									*/
/* PRODUCT(S)  : Lean-T Stack						*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*	NONE								*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 01/19/07  JRB    39     Del assert on rx_queue_count (not always 0).	*/
/* 08/03/06  JRB    38     If RX queue full, discard received packets.	*/
/* 07/24/06  JRB    37     Add OsiReadThreadNT so users don't need to	*/
/*			   call "*Ex" functs to allow completion routines.*/
/* 07/21/06  JRB    36     Delete all code NOT used for MMS-Lite.	*/
/*			   Chg to use SISCO naming conventions.		*/
/*			   Use CLNP_LOG_ERR to log errors.		*/
/* 11/08/04  EJV    35     ProcessReadBlock: log error and continue if	*/
/*			     incorrect frame len received.		*/
/* 11/04/04  EJV    34     ethsapon: add more info in log - open osillc	*/
/* 06/10/04  EJV    33     Corr log to catch ReadPackets != MaxReadOut	*/
/* 02/13/04  EJV    32     Chg log to catch ReadPackets != MaxReadOut	*/
/*			     OSILLC & OSILL2 registry parameters.	*/
/* 11/18/03  JRB    31     Pass NULL as 7th arg to DeviceIoControl,	*/
/*			   avoids risks of data corruption on Win 98	*/
/*			   if data written AFTER DeviceIo.. returns.	*/
/* 08/12/02  DSF    30	   Changed the criteria for out of sequence 	*/
/*			   frames					*/
/* 01/17/02  DSF    29     Added QueryMediumType ()			*/
/* 01/16/02  JRB    28     Add "driver not found" MessageBox.		*/
/* 12/10/01  EJV    27     llcsetup: Added some more info to MessageBox.*/
/* 11/08/01  DSF    26     Free pWriteEvents only if it's been allocated*/
/* 03/27/01  DSF    25     For NT/2000, build a list of useable drivers	*/
/*			   and use those instead of the names passed to	*/
/*			   ethsapon					*/
/* 10/26/00  JRB    24     Free pWriteEvents in ethsapoff		*/
/* 07/25/00  JRB    23     Lint cleanup & fix slog macro.		*/ 
/* 05/01/00  JRB    22     Use macros for slog; disable if Lite & !DEBUG*/
/* 04/05/00  JRB    21     Added #ifdef MMS_LITE for MMS-EASE Lite.	*/
/*			   Removed unused code.				*/
/* 09/10/99  DSF    20     Don't put up Message Boxes if bOsiRequired 	*/
/*			   is false					*/
/* 04/01/99  DSF    19     Win98 port					*/
/* 09/13/98  DSF    18     Driver events are now manual reset		*/
/* 06/02/98  DSF    17     Provide for blocking receive mode		*/
/* 05/19/98  DSF    16     Check for bogus frame length			*/
/* 05/01/98  DSF    15     Use Completion Routines for NT		*/
/* 04/21/98  DSF    14     Discard non-OSI frames			*/
/* 04/13/98  DSF    13     Added support for pacing			*/
/* 01/26/98  DSF    12     Old NT Driver no longer supported		*/
/* 11/19/97  DSF    11     Better messages in Message Boxes		*/
/* 06/12/97  DSF    10     Added Slogging				*/
/*			   Added stats					*/
/* 02/05/97  DSF    09     Added a check for valid LLC frame length in	*/
/*			   ethin ()					*/
/* 09/17/96  DSF    08     Allow for up to 4 Physical Addresses		*/
/* 09/10/96  DSF    07     Allow passing ESH's up			*/
/* 09/09/96  DSF    06     Handle multiple subnets			*/
/* 09/05/96  DSF    05     Handle STATUS_PENDING for Win95		*/
/* 08/14/96  DSF    04     Added Completion Event for 95		*/
/* 08/06/96  DSF    03     Added handling of ERROR_IO_PENDING		*/
/* 07/22/96  DSF    02     Better logging				*/
/* 04/04/96  DSF    01     Initial Release				*/
/*									*/
/************************************************************************/
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif

#include "glbtypes.h"
#include "sysincs.h"
#include "ethsub.h"	/* definitions modified for Lite	*/

#ifdef DEBUG_SISCO
SD_CONST static ST_CHAR *SD_CONST thisFileName = __FILE__;  /* Define for SLOG mechanism    */
#endif

/****************************************************************/
/*              Global variables	                    	*/
/****************************************************************/
int NumWriteOut;
HANDLE 		hIoEvent;

static unsigned long msgXmitOk = 0;
static unsigned long msgRcvOk = 0;
static unsigned long msgXmitError = 0;
static unsigned long msgRcvError = 0;
static unsigned long msgRcvUnknown = 0;

static ST_UCHAR aes[7] = {0x06, 0x09, 0x00, 0x2b, 0x00, 0x00, 0x04};
static ST_UCHAR ais[7] = {0x06, 0x09, 0x00, 0x2b, 0x00, 0x00, 0x05};


CRITICAL_SECTION csOsiList;   /* Critical Section object for OSI Event List */

SN_EVENT *osiEvtListHead = NULL;
SN_EVENT *osiEvtListTail = NULL;	/* list pointers	*/

/* Use these global variables to limit the number of received packets	*/
/* queued up. If limit exceeded, discard packets. Protect access to	*/
/* these using CriticalSection.						*/
static ST_INT rx_queue_limit = 20000;	/* DEBUG: add funct to change limit?*/
static ST_INT rx_queue_count;
static ST_INT rx_lost_count;

DWORD QueryPacket(HANDLE hDriver, ULONG ioctl, BYTE* inBuffer, DWORD cbIn, 
				  BYTE* outBuffer, DWORD cbOut);
BOOL QueryOid(HANDLE hDriver, ULONG ulOid, PBYTE pBuffer, ULONG ulLength);
BOOL SetOid(HANDLE hDriver, ULONG ulOid, PBYTE pBuffer, ULONG ulLength);
void QueryMacName(HANDLE hDriver, PBYTE pMacName, DWORD dwLength);
BOOL QueryMediaType(HANDLE hDriver);
BOOL IoctlRequest (HANDLE hDriver, ULONG ioctl, BYTE* inBuffer, DWORD cbIn, 
		   BYTE* outBuffer, DWORD cbOut, DWORD* pcbRet);
int GetBindInfo(int binding);

void PostReads ();
void WriteMonitorThread (LPDWORD lpdwParam);


/************************************************************************/
/*			WriteCompletion					*/
/* This function gets called when a write operation completes		*/
/************************************************************************/
void CALLBACK WriteCompletion (DWORD error, DWORD length, OVERLAPPED *ovlp)
  {

  NumWriteOut--;
  if (error)
    {
    CLNP_LOG_ERR1 ( 
             "WriteCompletion: WriteFileEx () failed, error = %d", error);
    }

  free (ovlp->hEvent);	/* Frame buffer */
  free (ovlp);
  }

/************************************************************************/
/*			ethsapoff					*/
/************************************************************************/
void ethsapoff (void)
{
DWORD cbRet;
int j;

  if (GCCP->hFile != INVALID_HANDLE_VALUE)
    {
    if (!bNT)
      {
      // Unbind from the MAC Driver first
      IoctlRequest (GCCP->hFile, (ULONG)IOCTL_OSILLC_UNBIND,
	            "0000", 5,
		    NULL, 0, &cbRet);
      }
    CloseHandle (GCCP->hFile);  
    }

  GCCP->hFile = INVALID_HANDLE_VALUE;
  Sleep (2000);	/* wait for OsiReadThreadNT to exit	*/
  if (!bNT && GCCP->pWriteEvents)
    {
    for (j = 0; j < MaxWriteOut; j++)
      {
      free (GCCP->pWriteEvents[j].ovlp);
      free (GCCP->pWriteEvents[j].framep);
      }
    free (GCCP->pWriteEvents);
    }
}

/************************************************************************/
/*			ethsapon					*/
/************************************************************************/
static int timesCalled;
static char drvList[16][32];
static int numDrivers;
extern int nSubnets;

void ethsapon (ST_CHAR *drvname)
{
char name[100];
UINT mb_opts;
DWORD cbRet;
int binding;
char bindname[128];
HANDLE handle;
int i;

 timesCalled++;
 if (timesCalled > nSubnets)
   return;

 if (timesCalled == 1)
   {
   hIoEvent = CreateEvent (NULL, TRUE, FALSE, NULL);

   InitializeCriticalSection (&csOsiList);
   
   if (bNT)
     {
     /* Build a list of useable drivers */
     for (i = 0; i < 64; i++)
       {
       sprintf (name, "\\\\.\\osillc%d", i + 1);
       handle = CreateFile (name,
  		            GENERIC_READ | GENERIC_WRITE,
		            FILE_SHARE_READ | FILE_SHARE_WRITE,
		            NULL,
		            OPEN_EXISTING,
		            FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
		            NULL);
       if (handle != INVALID_HANDLE_VALUE)
         {
	 /* Now check to see which media the driver supports */
	 if (QueryMediaType (handle))
	   strcpy (drvList[numDrivers++], name);
	 CloseHandle (handle);
	 if (numDrivers == 16)
	   break;
	 }
       }
     }
   }

 if (bNT)
   {
   if (bServiceControl)
     mb_opts = MB_OK | MB_ICONEXCLAMATION | MB_SERVICE_NOTIFICATION;
   else
     mb_opts = MB_OK | MB_ICONEXCLAMATION;

   if (numDrivers == 0  &&  bOsiRequired)
     {
     MessageBox (NULL, 
                 "OSILLC driver not found.\nOSI support disabled.",
                 "OSI Stack Initialization Error", 
                 mb_opts);
     return;		/* something is seriously messed up */
     }

   /* Get the name of the appropriate driver */

   i = drvname[6] - '1';
   strcpy (name, drvList[i]);
   
   /* open Driver, initialize it, and prepare it for operations */
   GCCP->hFile = CreateFile (name,
  		             GENERIC_READ | GENERIC_WRITE,
		             FILE_SHARE_READ | FILE_SHARE_WRITE,
		             NULL,
		             OPEN_EXISTING,
		             FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
		             NULL);
   if (GCCP->hFile == INVALID_HANDLE_VALUE)
     {
     char errmsg[200];
     sprintf (errmsg,"drvname='%s' mapped to '%s', driver open failed (errno=%d)", drvname, name, GetLastError());
     CLNP_LOG_ERR0 (errmsg);
     /* Check to see if OSI support is required */
     if (bOsiRequired)
       {
       MessageBox (NULL, 
                   "Could not open OSILLC Driver.\n"
                   "OSI support disabled.", 
                   "OSI Stack Initialization Error", 
                    mb_opts);
       }

     return;		/* something is seriously messed up */
     }
   }
 else
   {
   /* open VxD, initialize it, and prepare it for operations */
   GCCP->hFile = CreateFile ("\\\\.\\osillc98.vxd",
 			     0, 0,
		             NULL,
		             CREATE_NEW,
 		             FILE_FLAG_DELETE_ON_CLOSE | FILE_FLAG_OVERLAPPED,
		             NULL);
   if (GCCP->hFile == INVALID_HANDLE_VALUE)
     {
     CLNP_LOG_ERR0 ("VxD Open failed");
     /* Check to see if OSI support is required */
     if (bOsiRequired)
       {
       MessageBox (NULL, 
                   "Could not open OSILLC VxD.\n"
                   "OSI support disabled.", 
                   "OSILL2 Initialization Error", 
                   MB_OK | MB_ICONEXCLAMATION);
       }

     return;		/* something is seriously messed up */
     }

   // Attempt to bind to the appropriate MAC driver
   if (DriverID == -1)
     {
     binding = GetBindInfo (timesCalled);
     if (binding == -1)
       {
       CLNP_LOG_ERR0 ("VxD Bind failed");
       /* Check to see if OSI support is required */
       if (bOsiRequired)
         {
         MessageBox (NULL, 
                     "Could not find appropriate binding.\n",
                     "OSILL2 Initialization Error", 
                     MB_OK | MB_ICONEXCLAMATION);
         }

       CloseHandle (GCCP->hFile);  
       GCCP->hFile = INVALID_HANDLE_VALUE;

       return;
       }
     }
   else
     binding = DriverID;

   sprintf (bindname, "000%d", binding);
   if (!IoctlRequest(GCCP->hFile, (ULONG)IOCTL_OSILLC_BIND,
   	             bindname, 5, NULL, 0, &cbRet))
     {
     CLNP_LOG_ERR0 ("VxD Bind failed");
     /* Check to see if OSI support is required */
     if (bOsiRequired)
       {
       MessageBox (NULL, 
                   "Could not bind to MAC Driver.\n"
                   "OSI support disabled.", 
                   "OSILL2 Initialization Error", 
                   MB_OK | MB_ICONEXCLAMATION);
       }

     CloseHandle (GCCP->hFile);  
     GCCP->hFile = INVALID_HANDLE_VALUE;

     return;
     }
   }

 GCCP->pWriteEvents = NULL;
 llcsetup ();
}


/************************************************************************/
/************************************************************************/
/* Special support functions that handle Ethernet Driver management	*/
/************************************************************************/
/************************************************************************/

/************************************************************************/
/* llcsetup								*/
/************************************************************************/

llcsetup ()
 {
UINT mb_opts;
char macaddr[ETHE_MAC_LEN];
char multilist[2 * ETHE_MAC_LEN];
LONG filter;
HANDLE hThread;
DWORD dwThreadId;
int i;

  if (bServiceControl)
    mb_opts = MB_OK | MB_ICONEXCLAMATION | MB_SERVICE_NOTIFICATION;
  else
    mb_opts = MB_OK | MB_ICONEXCLAMATION;

 /* Discover the hardware address */
 if (QueryOid (GCCP->hFile, OID_802_3_CURRENT_ADDRESS, 
               macaddr, ETHE_MAC_LEN) == FALSE)
   {
   /* Check to see if OSI support is required */
   if (bOsiRequired)
     {
     MessageBox (NULL, 
                 "GetCurrentAddress failed.\n"
	         "Make sure OSI LLC Protocol Driver V2.00 or later is installed.\n"
		 "For multiple adapters in the system you may need to configure specific adapter to be used.",
                 "OSI Stack Initialization Error", 
                 mb_opts);
     }
   CLNP_LOG_ERR0 ("GetCurrentAddress failed");
   ethsapoff ();
   return (-1);
   }

 /* Save the local address for future use */
 memcpy (clnp_param.loc_mac, macaddr, ETHE_MAC_LEN);

 /* Add ES and IS Multicast */
 multilist[0] = 0x09;
 multilist[1] = 0x00;
 multilist[2] = 0x2B;
 multilist[3] = 0x00;
 multilist[4] = 0x00;
 multilist[5] = 0x04;
 multilist[6] = 0x09;
 multilist[7] = 0x00;
 multilist[8] = 0x2B;
 multilist[9] = 0x00;
 multilist[10] = 0x00;
 multilist[11] = 0x05;

 if (SetOid (GCCP->hFile, OID_802_3_MULTICAST_LIST,
             multilist, 2 * ETHE_MAC_LEN) == FALSE)
   {
   /* Check to see if OSI support is required */
   if (bOsiRequired)
     {
     MessageBox (NULL, 
                 "SetMulticast failed.\n"
	         "Make sure OSI LLC Protocol Driver V2.00 or later "
	         "is installed.", 
                 "OSI Stack Initialization Error", 
                 mb_opts);
     }
   CLNP_LOG_ERR0 ("SetMulticast failed");
   ethsapoff ();
   return (-1);
   }

 filter = NDIS_PACKET_TYPE_DIRECTED | NDIS_PACKET_TYPE_MULTICAST;
 if (SetOid (GCCP->hFile, OID_GEN_CURRENT_PACKET_FILTER, 
            (PBYTE)&filter, sizeof(DWORD)) == FALSE)
   {
   /* Check to see if OSI support is required */
   if (bOsiRequired)
     {
     MessageBox (NULL, 
                 "SetFilter () failed"
	         "Make sure OSI LLC Protocol Driver V2.00 or later "
	         "is installed.", 
                 "OSI Stack Initialization Error", 
                 mb_opts);
     }
   CLNP_LOG_ERR0 ("SetFilter failed");
   CloseHandle (GCCP->hFile);
   GCCP->hFile = INVALID_HANDLE_VALUE;
   return (-1);
   }

 // For 95/98, create write event objects and spawn a thread
 // to monitor them
 if (!bNT)
   {
   // Restrict number of oustanding write reqs to max.
   // number of objects you can wait on
   if (MaxWriteOut > MAXIMUM_WAIT_OBJECTS)
     MaxWriteOut = MAXIMUM_WAIT_OBJECTS;

   GCCP->pWriteEvents = calloc (MaxWriteOut, sizeof (RD_WR_BLOCK));
   for (i = 0; i < MaxWriteOut; i++)
     {
     GCCP->pWriteEvents[i].inuse = 0;
     GCCP->pWriteEvents[i].hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);
     GCCP->pWriteEvents[i].ovlp = malloc (sizeof (OVERLAPPED));
     GCCP->pWriteEvents[i].framep = malloc (ETHE_MAX_LEN_LSDU);
     GCCP->pWriteEvents[i].gccp = GCCP;
     }

   hThread = CreateThread (NULL, 0, 
 			   (LPTHREAD_START_ROUTINE) WriteMonitorThread,
			   GCCP, 0, &dwThreadId) ;
   }

 if (bNT && ReceptionMode == 0)
   {
   hThread = CreateThread (NULL, 0, 
 			   (LPTHREAD_START_ROUTINE) OsiReadThreadNT,
			   GCCP, 0, &dwThreadId) ;
   }
 else
   {
   hThread = CreateThread (NULL, 0, 
 			   (LPTHREAD_START_ROUTINE) OsiReadThread,
			   GCCP, 0, &dwThreadId) ;
   }

 return (0);
 }   
   

/************************************************************************/
/* PostReads								*/
/************************************************************************/

void PostReads ()
  {
OVERLAPPED *ovlp;
int result;
DWORD dwErrorCode;
RD_WR_BLOCK	*readBlock;
OSILLC_PACKET_BLOCK	*PacketBlock;
int i;

  for (i = 0; i < MaxReadOut; i++)
    {
    if (bNT)
      {
      PacketBlock = (OSILLC_PACKET_BLOCK *) calloc (FramesPerBlock, 
    					      sizeof (OSILLC_PACKET_BLOCK));
      PacketBlock->NumberOfPackets = FramesPerBlock;

      readBlock = (RD_WR_BLOCK *) calloc (1, sizeof (RD_WR_BLOCK));
      readBlock->pb = PacketBlock;
      readBlock->gccp = GCCP;

      ovlp = (OVERLAPPED *) calloc (1, sizeof (OVERLAPPED));
      ovlp->hEvent = (HANDLE) readBlock;

      result = ReadFileEx (GCCP->hFile, PacketBlock, 
    		           FramesPerBlock * sizeof (OSILLC_PACKET_BLOCK), 
                           ovlp,
		           (LPOVERLAPPED_COMPLETION_ROUTINE) ReadCompletion);
      if (!result)
        {
        dwErrorCode = GetLastError();

        CLNP_LOG_ERR3 ( 
              "ReadFileEx () failed, error = %d (MaxReadOut=%d, i=%d) \n"
              "\\My Computer\\HKEY_LOCAL_MACHINE\\System\\CurrentControlSet\\Services\\OSILLC\\Parameters\\ReadPackets and \n"
              "\\My Computer\\HKEY_LOCAL_MACHINE\\Software\\SISCO\\Osill2\\CurrentVersion\\Parameters\\MaxReadOut \n"
              "parameters should be the same.",
                 dwErrorCode, MaxReadOut, i);

        free (PacketBlock);
        free (ovlp);
        break;
	}
      }
    else
      {
      memset (GCCP->pReadEvents[i].ovlp, 0, sizeof (OVERLAPPED));
      GCCP->pReadEvents[i].ovlp->hEvent = GCCP->pReadEvents[i].hEvent;
      result = DeviceIoControl (GCCP->hFile, 
                                IOCTL_OSILLC_READ, 
				GCCP->pReadEvents[i].pb, 
    		                sizeof (OSILLC_PACKET_BLOCK),
				GCCP->pReadEvents[i].pb, 
    		                sizeof (OSILLC_PACKET_BLOCK),
				NULL, 
				GCCP->pReadEvents[i].ovlp);
      if (!result)
        {
        dwErrorCode = GetLastError();

	if (dwErrorCode != ERROR_IO_PENDING)
	  {
          CLNP_LOG_ERR1 ( 
                "DeviceIoControl () failed, error = %d", dwErrorCode);
	  }
	}
      }
    }
  }


/************************************************************************/
/* ReadCompletion							*/
/************************************************************************/

void CALLBACK ReadCompletion (DWORD error, DWORD length, OVERLAPPED *ovlp)
  {
int i;
RD_WR_BLOCK *readBlock;
OSILLC_PACKET_BLOCK *PacketBlock;
LLC_CONTEXT *gccp;
int result;

  readBlock = (RD_WR_BLOCK *) ovlp->hEvent;
  PacketBlock = (OSILLC_PACKET_BLOCK *) readBlock->pb;
  gccp = readBlock->gccp;

  if (error)
    {
    CLNP_LOG_ERR1 ( 
          "ReadFileEx () failed, error = %d", error);
    msgRcvError++;

    if (gccp->hFile != INVALID_HANDLE_VALUE)
      {
      result = ReadFileEx (gccp->hFile, PacketBlock, 
    		           FramesPerBlock * sizeof (OSILLC_PACKET_BLOCK), 
                           ovlp,
		           (LPOVERLAPPED_COMPLETION_ROUTINE) ReadCompletion);
      if (!result)
        {
        error = GetLastError();

        CLNP_LOG_ERR1 ( 
              "ReadFileEx () failed, error = %d", error);

        free (PacketBlock);
        free (readBlock);
        free (ovlp);
        }
      }
    }
  else    
    {
    /* Check to see if this is the sequence number we expect */
    if (PacketBlock->SeqNumber > gccp->seq)
      {
      CLNP_LOG_ERR2 ( 
            "Frame received out of sequence (E=%d R=%d)", 
            gccp->seq, PacketBlock->SeqNumber);
      /* got one out of sequence, set it aside */
      /* and deal with it later */
      for (i = 0; i < 10; i++)
        {
	if (gccp->readlst[i] == NULL)
	  break;
	}

      if (i < 10)
	gccp->readlst[i] = ovlp;
      else
        {
        CLNP_LOG_ERR2 ( 
              "Received 10 frames out of sequence (E=%d R=%d)", 
	      gccp->seq, PacketBlock->SeqNumber);
	}

      return;
      }

    ProcessReadBlock (ovlp);

    /* Check to see if we previously got a block out of sequence */
    for (i = 0; i < 10; i++)
      {
      if (gccp->readlst[i] == NULL)
        break;

      ProcessReadBlock ((OVERLAPPED *) gccp->readlst[i]);
      gccp->readlst[i] = NULL;
      }
    }
  }

/************************************************************************/
/* WriteMonirorThread							*/
/************************************************************************/

void WriteMonitorThread (LPDWORD lpdwParam)
  {
LLC_CONTEXT *gccp = (LLC_CONTEXT *) lpdwParam;
HANDLE *phWriteEvents;
DWORD result;
DWORD dwErrorCode;
int i;

  SetThreadPriority (GetCurrentThread (), Priority);

  phWriteEvents = (HANDLE *) calloc (MaxWriteOut, sizeof (HANDLE));
  for (i = 0; i < MaxWriteOut; i++)
    phWriteEvents[i] = gccp->pWriteEvents[i].hEvent;

  while (1)
    {
    result = WaitForMultipleObjects (MaxWriteOut, phWriteEvents, 
    				     FALSE, INFINITE);
    if (result == WAIT_FAILED)
      {
      dwErrorCode = GetLastError ();

      CLNP_LOG_ERR1 ( 
            "WaitForMultipleObjects () failed, error = %d", dwErrorCode);

      continue;
      }

    i = result - WAIT_OBJECT_0;
    ResetEvent (phWriteEvents[i]);
    EnterCriticalSection (&csOsiList);
    gccp->pWriteEvents[i].inuse = 0;
    NumWriteOut--;
    LeaveCriticalSection (&csOsiList);
    }
  }

/************************************************************************/
/*			OsiReadThreadNT					*/
/* Read from the driver asynchronously using ReadFileEx (called by	*/
/* PostReads and by the completion routine). The completion routine is	*/
/* always "ReadCompletion". SleepEx is called in loop to allow		*/
/* "ReadCompletion" to be called. "ReadCompletion" processes the data &	*/
/* calls ReadFileEx again.						*/
/* NOTE: ReadFileEx & SleepEx called in the same thread, so completion	*/
/*   routines always allowed to run. User does NOT need to call SleepEx,*/
/*   WaitForSingleObjectEx, or any other "*Ex" function.		*/
/* NOTE: don't need similar WriteThread because WriteCompletion doesn't	*/
/*   do much, and SleepEx in clnp_snet_write_raw makes sure completion	*/
/*   routines called at least when next write occurs.			*/
/************************************************************************/

void OsiReadThreadNT (LPDWORD lpdwParam)
  {
LLC_CONTEXT *gccp = (LLC_CONTEXT *) lpdwParam;

  PostReads ();	/* Post several async read requests using ReadFileEx	*/
  /* Main thread sets hFile invalid when it is time to exit.	*/
  while (gccp->hFile != INVALID_HANDLE_VALUE)
    {
    /* Should wake up on every ReadCompletion event, but wake up	*/
    /* periodically just to check if it is time to exit.		*/
    SleepEx (1000, TRUE);
    }
  ExitThread (1);
  }

/************************************************************************/
/* QueryPacket								*/
/************************************************************************/

DWORD QueryPacket (HANDLE hDriver, ULONG ioctl, BYTE* inBuffer, DWORD cbIn, 
		   BYTE* outBuffer, DWORD cbOut)
  {
DWORD cbRet;
OVERLAPPED ovlp = {0,0,0,0,0};
   
  ovlp.hEvent = hIoEvent;
  
  if (!DeviceIoControl (hDriver, ioctl, inBuffer, cbIn, outBuffer, cbOut, NULL, &ovlp))
    {
    if (GetLastError() == ERROR_IO_PENDING)                         
      {
      //
      // DeviceIoControl call will have returned without completing
      // requested function. GetOverlappedResult at this point
      // should return ERROR_IO_INCOMPLETE if called w/ fWait=FALSE.
      //
      if ( !GetOverlappedResult(hDriver, &ovlp, &cbRet, FALSE))
        {
      	if (GetLastError() != ERROR_IO_INCOMPLETE)
	  return (FALSE);
        }

      // suspend this thread until the operation is completed by the driver
      GetOverlappedResult (hDriver, &ovlp, &cbRet, TRUE);
      }
    }

  return cbRet;
  }


/************************************************************************/
/* QueryOid								*/
/************************************************************************/

BOOL QueryOid(HANDLE hDriver, ULONG ulOid, PBYTE pBuffer, ULONG ulLength)
  {
DWORD cbIn = sizeof(OSILLC_OID_DATA) + ulLength;
DWORD cbRet, dwErrorCode;
BYTE QueryBuffer[100];
POSILLC_OID_DATA pOidData = (POSILLC_OID_DATA)QueryBuffer;
OVERLAPPED ovlp = {0,0,0,0,0};

  memset (pBuffer, 0, ulLength);

  pOidData->Oid    = ulOid;
  pOidData->Length = ulLength;

  ovlp.hEvent = hIoEvent;
  
  if (!DeviceIoControl (hDriver, (ULONG)IOCTL_OSILLC_QUERY_OID, pOidData, cbIn,
  			pOidData, cbIn, NULL, &ovlp))
    {
    dwErrorCode = GetLastError();
    if (dwErrorCode == ERROR_IO_PENDING)                         
      {
      //
      // DeviceIoControl call will have returned without completing
      // requested function. GetOverlappedResult at this point
      // should return ERROR_IO_INCOMPLETE if called w/ fWait=FALSE.
      //
      if ( !GetOverlappedResult(hDriver, &ovlp, &cbRet, FALSE))
        {
        dwErrorCode = GetLastError();
      	if (dwErrorCode != ERROR_IO_INCOMPLETE)
	  return (FALSE);
        }

      // suspend this thread until the operation is completed by the driver
      if (GetOverlappedResult (hDriver, &ovlp, &cbRet, TRUE))
      	memcpy (pBuffer, pOidData->Data, ulLength);
      }
    }

  return (cbRet > 0) ? TRUE : FALSE;
  }


/************************************************************************/
/* SetOid								*/
/************************************************************************/

BOOL SetOid(HANDLE hDriver, ULONG ulOid, PBYTE pBuffer, ULONG ulLength)
  {
DWORD cbIn = sizeof(OSILLC_OID_DATA) + ulLength;
DWORD cbRet, dwErrorCode;
BYTE SetBuffer[100];
POSILLC_OID_DATA pOidData = (POSILLC_OID_DATA)SetBuffer;
OVERLAPPED ovlp = {0,0,0,0,0};
   

  pOidData->Oid    = ulOid;
  pOidData->Length = ulLength;
  memcpy (pOidData->Data, pBuffer, ulLength);
  
  ovlp.hEvent = hIoEvent;
    
  if (!DeviceIoControl (hDriver, (ULONG)IOCTL_OSILLC_SET_OID, pOidData, cbIn,
			pOidData, cbIn, NULL, &ovlp))
    {
    dwErrorCode = GetLastError();
    if (dwErrorCode == ERROR_IO_PENDING)                         
      {
      //
      // DeviceIoControl call will have returned without completing
      // requested function. GetOverlappedResult at this point
      // should return ERROR_IO_INCOMPLETE if called w/ fWait=FALSE.
      //
      if (!GetOverlappedResult (hDriver, &ovlp, &cbRet, FALSE))
        {
        dwErrorCode = GetLastError();
      	if (dwErrorCode != ERROR_IO_INCOMPLETE)
	  return (FALSE);
        }

      // suspend this thread until the operation is completed by the driver
      GetOverlappedResult(hDriver, &ovlp, &cbRet, TRUE);
      }
    }


  return (cbRet > 0) ? TRUE : FALSE;
  }

/************************************************************************/
/* QueryMacName								*/
/************************************************************************/

void QueryMacName(HANDLE hDriver, PBYTE pMacName, DWORD dwLength)
  {
DWORD cbRet;

  memset(pMacName, 0, dwLength);

  cbRet = QueryPacket (hDriver, (ULONG)IOCTL_OSILLC_GET_MACNAME,
		       pMacName, dwLength, pMacName, dwLength);
  }


/************************************************************************/
/* QueryMediaType							*/
/************************************************************************/

typedef enum _NDIS_MEDIUM {
    NdisMedium802_3,
    NdisMedium802_5,
    NdisMediumFddi,
    NdisMediumWan,
    NdisMediumLocalTalk,
    NdisMediumDix,
    NdisMediumArcnetRaw,
    NdisMediumArcnet878_2,
    NdisMediumAtm,
    NdisMediumWirelessWan,
    NdisMediumIrda,
    NdisMediumMax
} NDIS_MEDIUM, *PNDIS_MEDIUM;


BOOL QueryMediaType(HANDLE hDriver)
  {
BYTE QueryBuffer[128 + sizeof (OSILLC_OID_DATA)];
DWORD cbIn = sizeof(QueryBuffer);
DWORD cbRet, dwErrorCode, dwMediumType;
BOOL ret = FALSE;
POSILLC_OID_DATA pOidData = (POSILLC_OID_DATA)QueryBuffer;
OVERLAPPED ovlp = {0,0,0,0,0};
int i;

  memset (QueryBuffer, 0, cbIn);

  pOidData->Oid    = OID_GEN_MEDIA_IN_USE;
  pOidData->Length = 128;

  ovlp.hEvent = hIoEvent;
  
  if (!DeviceIoControl (hDriver, (ULONG)IOCTL_OSILLC_QUERY_OID, pOidData, cbIn,
  			pOidData, cbIn, NULL, &ovlp))
    {
    dwErrorCode = GetLastError();
    if (dwErrorCode == ERROR_IO_PENDING)                         
      {
      //
      // DeviceIoControl call will have returned without completing
      // requested function. GetOverlappedResult at this point
      // should return ERROR_IO_INCOMPLETE if called w/ fWait=FALSE.
      //
      if ( !GetOverlappedResult(hDriver, &ovlp, &cbRet, FALSE))
        {
        dwErrorCode = GetLastError();
      	if (dwErrorCode != ERROR_IO_INCOMPLETE)
	  return (FALSE);
        }

      // suspend this thread until the operation is completed by the driver
      if (GetOverlappedResult (hDriver, &ovlp, &cbRet, TRUE))
        {
	if (pOidData->Length > 0)
	  {
	  i = 0;
	  while (cbRet)
	    {
	    dwMediumType = * ((DWORD *) &pOidData->Data[i]);
	    switch (dwMediumType)
	      {
	      case NdisMedium802_3:
	      case NdisMedium802_5:
	      case NdisMediumWan:
	      case NdisMediumDix:
	      case NdisMediumWirelessWan:
	        ret = TRUE;
	      break;
	      
	      default:
	      break;
	      }
	    
	    if (ret == TRUE)
	      break;
	      
	    pOidData->Length -= 4;
	    i += 4;
	    }
	  }
	else
	  ret = TRUE;
	}
      }
    }

  return ret;
  }


/************************************************************************/
/* IoctlRequest								*/
/************************************************************************/

BOOL IoctlRequest (HANDLE hDriver, ULONG ioctl, BYTE* inBuffer, DWORD cbIn, 
		   BYTE* outBuffer, DWORD cbOut, DWORD* pcbRet)
  {
HANDLE      hEvent = 0;
OVERLAPPED  ovlp = {0,0,0,0,0};

  *pcbRet = 0;
   
  if (!(hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)))
    {
    return FALSE;
    }

  if (!ResetEvent(hEvent)) 
    {
    return FALSE;
    }

  ovlp.hEvent = hEvent;
    
  if (!DeviceIoControl(hDriver, ioctl, inBuffer, cbIn, outBuffer, cbOut, NULL, &ovlp))
    {
    DWORD dwErrorCode;

    if ((dwErrorCode = GetLastError()) == ERROR_IO_PENDING)                         
      {
      // suspend this thread until the operation is completed by the driver
      if (!GetOverlappedResult(hDriver, &ovlp, pcbRet, TRUE))
        {
        dwErrorCode = GetLastError();
        return FALSE;
        }
      }
    else
      return FALSE;
    }

  CloseHandle(hEvent);

  return TRUE;
  }

/************************************************************************/
/* GetBindInfo								*/
/************************************************************************/

int GetBindInfo(int binding)
  {
HKEY	hKey, hSubKey;
DWORD	i, j;
DWORD	retCode;
char	szNetKey[] = "System\\CurrentControlSet\\Services\\Class\\Net";
char	szSubKey[MAX_PATH];
int		dwBindingsFound = 0;
DWORD   dwIndex;

  retCode = RegOpenKeyEx(HKEY_LOCAL_MACHINE, szNetKey,
			0, KEY_ENUMERATE_SUB_KEYS | KEY_EXECUTE, &hKey);

  if (retCode != ERROR_SUCCESS)
    return -1;

  for (i = 0; dwBindingsFound < binding; i++)
    {
    DWORD retValue;
    char  strKeyName[MAX_PATH];
    DWORD dwcKeyName = MAX_PATH;
    FILETIME ftLastWritten;

    retValue = RegEnumKeyEx(hKey, i, strKeyName, &dwcKeyName, NULL, NULL, NULL, &ftLastWritten);
    if (retValue != ERROR_SUCCESS || retValue == ERROR_NO_MORE_ITEMS)
    	break;

    strKeyName[dwcKeyName] = '\0';
    dwIndex = atoi(strKeyName);
    sprintf(szSubKey, "%s\\%s", szNetKey, strKeyName);

    retCode = RegOpenKeyEx(HKEY_LOCAL_MACHINE, szSubKey, 0,
    			   KEY_EXECUTE | KEY_QUERY_VALUE, &hSubKey);

    if (retCode != ERROR_SUCCESS)
      continue;

    for (j = 0; ; j++)
      {
      DWORD	retValue;
      char	ValueName[MAX_PATH];
      DWORD	dwcValueName = MAX_PATH;
      BYTE	lpData[MAX_PATH];
      DWORD	cbData = MAX_PATH;

      ValueName[0] = '\0';

      retValue = RegEnumValue(hSubKey, j, ValueName, &dwcValueName,
      			      NULL, NULL, lpData, &cbData);

      if (retValue == ERROR_NO_MORE_ITEMS || retValue != ERROR_SUCCESS)
      	break;

      if (lstrcmpi (ValueName, "DeviceVxDs") == 0)
        {
	if (lstrcmpi ("pppmac.vxd", (LPCTSTR)lpData) == 0)
          break;
	if (lstrcmpi ("netpptp.sys", (LPCTSTR)lpData) == 0)
          break;

        dwBindingsFound++;
        }
      }

    RegCloseKey(hSubKey);
    }

  // Close the key handle.
  RegCloseKey(hKey);   

  if (dwBindingsFound < binding)
    return -1;

  return dwIndex;
  }

/****************************************************************/
/*			osiallocevt				*/
/* This function is used to create (alloc) an event structure	*/
/* and return a pointer to it to caller				*/
/****************************************************************/

SN_EVENT *osiallocevt ()
  {
ST_RET queue_full = SD_FALSE;
SN_EVENT *sn_event;

  EnterCriticalSection (&csOsiList);
  if (rx_queue_count < rx_queue_limit)
    rx_queue_count++;
  else
    {
    rx_lost_count++;
    queue_full = SD_TRUE;
    }
  LeaveCriticalSection (&csOsiList);

  if (queue_full)
    sn_event = NULL;
  else
    sn_event = (SN_EVENT *) calloc (1, sizeof (SN_EVENT));
  return (sn_event);
  }

/****************************************************************/
/*			osifreeevt				*/
/* This function is used to release (free) an event structure	*/
/****************************************************************/

void osifreeevt (SN_EVENT *evt)
  {
  free (evt);
  EnterCriticalSection (&csOsiList);
  rx_queue_count--;
  LeaveCriticalSection (&csOsiList);
  }

/****************************************************************/
/*			osiputevt				*/
/* This function is used to put an event structure on user	*/
/* event list and signal the event object attached to the list	*/
/****************************************************************/

void osiputevt (SN_EVENT *evt)
  {
  evt->nxevt = NULL;	/* should be NULL already, but just in case... */
  EnterCriticalSection (&csOsiList);

  if (osiEvtListHead == NULL)
    {					/* Empty list.	*/
    osiEvtListHead = osiEvtListTail = evt;
    }
  else
    {
    osiEvtListTail->nxevt = evt;
    osiEvtListTail = evt;
    }

  LeaveCriticalSection (&csOsiList);

  SetEvent (hMMSEvent);
  }



/****************************************************************/
/*			osigetevt				*/
/* This function is used to get an event structure from upbound	*/
/* event list							*/
/****************************************************************/

SN_EVENT *osigetevt ()
  {
SN_EVENT *evt;
ST_INT rx_lost_count_save;

  EnterCriticalSection (&csOsiList);

  if (osiEvtListHead)
    {
    assert (rx_queue_count > 0);	/* list NOT empty. count should be > 0.*/
    evt = osiEvtListHead;
    osiEvtListHead = osiEvtListHead->nxevt;
    }
  else
    {
    evt = NULL;
    }

  rx_lost_count_save = rx_lost_count;	/* save count to use outside CriticalSection*/
  rx_lost_count = 0;			/* reset lost count	*/
  LeaveCriticalSection (&csOsiList);

  /* This is a very bad error. Received packets have been lost.	*/
  if (rx_lost_count_save)
    CLNP_LOG_ERR1 ("CRITICAL ERROR: Lost Ethernet packets (count=%d)", rx_lost_count_save);

  return (evt);
  }
