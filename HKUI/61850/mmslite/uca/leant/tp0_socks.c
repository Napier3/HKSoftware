/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*	(c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*	2003-2007, All Rights Reserved					*/
/*									*/
/* MODULE NAME : tp0_socks.c						*/
/* PRODUCT(S)  : Lean-T Stack						*/
/*									*/
/* MODULE DESCRIPTION :							*/
/*	TP0 functions for dealing with secured sockets interface (SSL).	*/
/*	Uses "gensock2" as intermediate interface to sockets.		*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev     Comments					*/
/* --------  ---  ------   -------------------------------------------  */
/* 02/16/07  JRB    35     Use new sockEventPut, sockEventGet functions	*/
/*			   and new "uSockConnectInd/Conf" funct ptrs.	*/
/* 01/30/07  JRB    34     readyToFree flag was deleted so don't use it.*/
/* 01/15/07  JRB    33     Del poll_mode arg to sockStart.		*/
/* 01/15/07  EJV    32	   Rpl TP0_SOCKS_MUTEX_* with S_LOCK_UTIL_RESOURCES */
/*			     due to mutex changes in gensock2.c.	*/
/*			   TP0_SOCK_CTX: rem listsMutex create/destroy.	*/
/* 12/11/06 EJV     31	   rfc1006_listener_connect: chg nonblock_on	*/
/*			     from ST_LONG to int.			*/
/*			     Needed on 64-bit UNIX, Linux systems.	*/
/* 11/29/06  EJV    30	   recvwait_fd: chg __hpux to use the SCM_RIGHTS*/
/* 11/17/06 EJV     29	   socket funs: added (int) cast, the HP-UX	*/
/*			     ssize_t is long.				*/
/*			   recvwait_fd: impl timeout for recvmsg loop	*/
/* 11/07/06  EJV    28     MMSEASE_MOSI:init tp0Ctx.tcpEventWakeupPort=0*/
/* 07/10/06  EJV    27     MMSEASE_MOSI: finished GEN_SOCK_CTXT work.	*/
/*			   Use sysincs.h for system includes.		*/
/*			     Changed sun to s_un (err on Sun Solaris)	*/
/* 01/30/06  GLB    26     Integrated porting changes for VMS           */
/* 12/15/05  EJV    24     _processDisconnectInd: call list_find_node	*/
/* 12/07/05  EJV    23     _processDisconnectInd: unlink if on the list	*/
/*			   _processConnectDone: moved secEnable code to	*/
/*			     case for SOCK_STATE_CONNECTED state.	*/
/* 10/04/05  EJV    22     Implemented GEN_SOCK_CTXT and other changes:	*/
/*			   Renamed orginal SOCK_CTX to TP0_SOCK_CTX,	*/
/*			     sockCtx to tp0Ctx.				*/
/*			   _uSockDisconnectInd: mk errptr more readable	*/
/*			   _addSockInd: chg to ST_RET from ST_VOID	*/
/*			   _sockClose: moved code to _sockCloseAllListen*/
/*			   np_end: added new call to _sockCloseAllListen*/
/*			   Rpl GSOCK_MUTEX_* with TP0_SOCKS_MUTEX_*.	*/
/*			   Folded some glb vars into the TP0_SOCK_CTX.	*/
/*			   Reversed Rev 21 change, not needed anymore.	*/
/* 08/03/05  EJV    20     Reworked rekeyTime to be per connection.	*/
/*			   Use sockCtx glb (instead saving it in usr1).	*/
/* 07/19/05  EJV    19     _processConnectInd: set usr2 back to NULL.	*/
/*			   _processConnectDone: if secEnable don't free	*/
/*			   sock_info. Check state.			*/
/* 			   np_disconnect_req:check other states, add log*/
/* 07/01/05  EJV    18     _uSockWritable CORR: removed state chg.	*/
/* 06/24/05  EJV    17     Added code to prevent queues buildup.	*/
/* 05/02/05  JRB    16     Add RFC1006_LISTENER task code (MMSEASE_MOSI)*/
/*           EJV           Added _sockSetDefaults.			*/
/* 05/05/05  EJV    15     Use rfc1006_listen_port if configured	*/
/* 04/21/05  JRB    14     Fix logging of sin_port (use ntohs).		*/
/*			   Del unused vars.				*/
/* 04/13/05  EJV    13     Corr EADDRINUSE to SOCK_EADDRINUSE		*/
/* 03/22/05  EJV    12     LINUX (MMSEASE_MOSI): implemented events.	*/
/*			   _sockInitListen: allow to SO_REUSEADDR.	*/
/*			   Added indTypeStr. Added/chg logging.		*/
/* 03/16/05  JRB    11     _uSockHunt: allow any val for 2nd byte &	*/
/*			   ret ..HUNT_DISCONNECT on err to cause disconn*/
/*			   For speed, set ptr to strings instead of strcpy.*/
/*			   Use RFC1006 defines from tp0_sock.h.		*/
/* 03/07/05  EJV    10     Fixed queuing bug where connectInd sometimes	*/
/*			   processed AFTER disconnectInd by moving	*/
/*			   sec cleanup from _uSockDisconnectInd to	*/
/*			   _processDisconnectInd.			*/
/*			   Moved sec code from _uSockConnectDone to 	*/
/*			   _processConnectDone,for consistency w/con ind*/
/*			   Use secEnable (in place of other sec fields)	*/
/* 02/19/04  EJV    09     np_end: chg sleep from 1000 to 100 ms	*/
/* 02/18/04  JRB    08     _uSockDisconnectInd: DON'T chk state, only	*/
/*			   safe from main thread (_processDisconnectInd)*/
/*			   np_end: allow disconnects to finish.		*/
/* 02/06/04  JRB    07     np_disconnect_req:Chg assert to log & ret err*/
/* 01/28/04  EJV    06     _handleRekeying:chk if connected before rekey*/
/* 01/23/04  EJV    05     np_data_req: sockTxMsg will free sockData.	*/
/* 01/21/04  JRB    04     Do most disconnect processing in callback	*/
/*			   _uSockDisconnectInd.				*/
/*	     EJV           Change test for rekey to '>='		*/
/* 01/14/04  EJV    03     np_data_req: added eot param.		*/
/*			     Free buff if sockTxMsg fails.		*/
/*			   Added np_get_tx_queue_cnt func.		*/
/* 10/16/03  JRB    02     Port to LINUX. Chg SOCKET to (GEN_SOCK *).	*/
/*			   Compare (GEN_SOCK *) to NULL, not INVALID_...*/
/* 07/29/03  EJV    01     New. Replacement for tp0_sock.c using	*/
/*			   gensock2 to interface to sockets.		*/
/*			   Used tp0_sock2.c and snapmain.c		*/
/************************************************************************/

#include "glbtypes.h"
#include "sysincs.h"

#include "mem_chk.h"
#include "ssec.h"
#include "ssec_int.h"
#include "tp4api.h"		/* User definitions for tp4	*/
#include "tp4.h"		/* Internal definitions for tp4	*/
#include "tp4_log.h"
#include "tp0_sock.h"
#include "sock_log.h"
#if defined(MMSEASE_MOSI)
#include "gensock2.h"
#endif

#ifdef MMS_LITE
#include "mvl_acse.h"		/* Need "mvl_num_called".	*/
#endif

#ifdef DEBUG_SISCO
SD_CONST static ST_CHAR *SD_CONST thisFileName = __FILE__;
#endif

/* This many messages can accumulate in the receiving ind queue 	*/
/* for given socket before we stop receiving, start receiving after	*/
/* we reach low mark.							*/
#define SOCK_RX_QUE_HIGH_MARK	10		/* >= stop  receiving	*/
#define SOCK_RX_QUE_LOW_MARK	 1		/* <= start receiving	*/

ST_CHAR *eventTypeStr[5] =
  {
  "UNKNOWN",
  "CONNECT_IND",
  "CONNECT_CONF",
  "DISCONNECT",
  "RXDATA"
  };

/* Similar to sock_info_alloc but uses GEN_SOCK.	*/
SOCK_INFO *sock_info_alloc2 (GEN_SOCK *genSock, ST_INT state, ST_LONG user_conn_id);

/* Functions to process indications/events.	*/
static ST_RET  _setSecInfo (GEN_SOCK *pSock, S_SEC_ENCRYPT_CTRL *encrypt_ctrl);
static ST_VOID _processConnectInd (GEN_SOCK *pSock);
static ST_VOID _processConnectDone (GEN_SOCK *pSock);
static ST_VOID _processDisconnectInd (GEN_SOCK *pSock);
static ST_VOID _processRxInd (GEN_SOCK *pSock, GEN_SOCK_DATA *sockData);

/* gensock2 callback functions	*/
static ST_RET  _uSockConnectDone (GEN_SOCK *pSock);
static ST_RET  _uSockConnectInd (GEN_SOCK *pSock);
static ST_VOID _uSockDisconnectInd (GEN_SOCK *pSock);
static ST_VOID _uSockRxInd (GEN_SOCK *pSock, GEN_SOCK_DATA *sockData);
static ST_VOID _uSockWritable (GEN_SOCK *pSock);
static ST_VOID _uSockHunt (GEN_SOCK *pSock, ST_INT *huntStateIo,
                     ST_CHAR *buf, ST_INT bufCount, ST_INT *lenOut);
static ST_VOID _uSockDataAlloc (GEN_SOCK *pSock, ST_INT dataLen,
			  GEN_SOCK_DATA **sockDataOut);
static ST_VOID _uSockDataFree (GEN_SOCK *pSock, GEN_SOCK_DATA *sockData);

/* misc functions */
static ST_RET  _addSockInd (GEN_SOCK *pSock, ST_INT indType,
			    GEN_SOCK_DATA *sockData);
static ST_RET  _handleRekeying (ST_VOID);

#define SOCK_REKEY_TIME		1000	/* check every 1000 ms if we need to rekey	*/


/************************************************************************/
/* Global variables.							*/
/************************************************************************/
int pipe_to_main;	/* Linker needs this, but it is never used.	*/

#if defined(_WIN32)
ST_EVENT_SEM        hTcpEvent;	/* to notify user about network events	*/
#endif

#if defined(MMSEASE_MOSI)
/*----------------------------------------------------------------------*/
/* NOTES:								*/
/* 1. We set SO_KEEPALIVE opt on TCP sockets (in/out connections).	*/
/* 2. We set SO_REUSEADDR on TCP sockets (in connections).		*/
/* 3. The domain socket and TCP sockets are all non-blocking.		*/
/* 4. How many fds we can FD_SET (for TCP connections in gensock2) ?	*/
/*      From the Linux: in the /usr/include/linux/posix_types.h the	*/
/*      __FD_SETSIZE is 1024  (FD_SETSIZE)				*/
/*    In gensock2.c there will be one service thread for every		*/
/*      GS_MAX_SOCK_PER_SERVICE defined to be (FD_SETSIZE - 1).		*/
/*----------------------------------------------------------------------*/

#if !defined(GENSOCK_THREAD_SUPPORT)
#error GENSOCK_THREAD_SUPPORT must be defined for MMSEASE_MOSI
#endif

/* NOTE:  These two sockets below need to be added to user's application	*/
/*        select() statement.							*/
/*        The mms_event_fd must always be added since it indicates events on	*/
/*        all the TCP connections.						*/
/*        The domsock_listener need to be added only if	the flag		*/
/*        use_rfc1006_listener_task=SD_TRUE.					*/
SOCKET    mms_event_fd = INVALID_SOCKET;	/* wakeup socket, indicating TCP Events	*/
SOCKET    domsock_listener = INVALID_SOCKET;	/* domain socket connected to the 	*/
						/* RFC1006_LISTENER task.		*/
ST_BOOLEAN use_rfc1006_listener_task = SD_TRUE;		/*DEBUG:: add to tp0_cfg struct? */
#else   /* !defined(MMSEASE_MOSI) */
ST_BOOLEAN use_rfc1006_listener_task = SD_FALSE;
#endif  /* !defined(MMSEASE_MOSI) */

/* use macro to simplify the code */
#define  CLOSE_THIS_SOCKET(hSock) \
  { \
  if (hSock != INVALID_SOCKET) \
    { \
    CLOSE_SOCKET (hSock); \
    hSock = INVALID_SOCKET; \
    } \
  }

/* listening socket types */
#define	SOCK_LISTEN_NON_SSL	1
#define	SOCK_LISTEN_SSL		2

/* Ctx state */
#define TP0_SOCK_CTX_STATE_IDLE			0
#define TP0_SOCK_CTX_STATE_ACTIVE		1
#define TP0_SOCK_CTX_STATE_TERMINATING		2

/* struct to hold configuration and communication info for secured and	*/
/* non-secured connections.						*/
typedef struct tag_tp0_sock_ctx
  {
  ST_UINT	 state;			/* TP0_SOCK_CTX_STATE_xxx				*/
  S_SEC_CONFIG  *secCfg;		/* ptr to global configuration				*/
  ST_UINT16      rfc1006Port;		/* save the listen port used for RFC1006 connections	*/
  GEN_SOCK      *remListenSock;		/* listen socket for non-secured cons from remotes  	*/
  GEN_SOCK      *remListenSockSSL[S_SSL_MAX_LISTEN_PORTS]; /* tbl of secure listen sockets for	*/
							   /* connections from remotes		*/
  SOCK_INFO          *secureSockList;	/* list of secured sockets			*/

  #if defined(MMSEASE_MOSI)
  ST_UINT16 tcpEventWakeupPortBase;	/* base listen port				*/
  ST_UINT   tcpEventWakeupPortRange;	/* range to search for free port		*/
  ST_UINT16 tcpEventWakeupPort;		/* actual wakeup port				*/
  SOCKET    hTcpEventSender;		/* signaled by gensock2 service thread		*/
  ST_CHAR   listenerIPCDir[256]; 	/* IPC directory (where to find domsock file);	*/
		   			/* set by calling setListenerIPCDir fun. If it	*/
		   			/* is not set by user appl the default dir	*/
		   			/* RFC1006_LISTENER_IPC_PATH will be used. 	*/
  #endif  /* defined(MMSEASE_MOSI) */


  GEN_SOCK_CTXT *sockCtx;		/* this is gensock2 context for tp0_socks.c	*/
  } TP0_SOCK_CTX;

TP0_SOCK_CTX	tp0Ctx;		/* must be global for !GENSOCK_THREAD_SUPPORT in event2.c	*/


static ST_RET _sockSetDefaults (GEN_SOCK_CONFIG *sockCfg);
static ST_RET _sockInitListen (ST_UINT type, ST_UINT idx, ST_INT max_num_conns);
static ST_RET _sockCloseAllListen (ST_VOID);
static ST_RET _sockClean (ST_VOID);

	/*----------------------------------------------*/
	/*	MMSEASE_MOSI - RFC1006 Listener funcs	*/
	/*----------------------------------------------*/

#if defined(MMSEASE_MOSI)

/************************************************************************/
/*			setListenerIPCDir				*/
/* This function would be called by user application to set the		*/
/* RFC1006_LISTENER daemon IPC directory where UNIX domain socket	*/
/* should be created. If this function is not called the default path	*/
/* RFC1006_LISTENER_IPC_PATH will be used.				*/
/************************************************************************/
ST_RET setListenerIPCDir (ST_CHAR *dirPath)
  {
ST_RET rtn = SD_FAILURE;

  if (dirPath && strlen (dirPath) > 0)
    {
    strcpy (tp0Ctx.listenerIPCDir, dirPath);		/* path to domsock file	*/
    rtn = SD_SUCCESS;
    }
  return (rtn);
  }


/* This section copied exactly from tp0_unix.c */

/************************************************************************/
/* This a special recv function only for receiving the socket handle	*/
/* from the "rfc1006_listener" task. It waits as long as the error is	*/
/* SOCK_WOULDBLOCK. On any other error, it stops waiting and returns.	*/
/* This function needs to take in account that the sender may fail in	*/
/* the sendmsg() by implementing timeout when waiting for the socket fd.*/
/************************************************************************/
ssize_t recvwait_fd (int fd, void *ptr, size_t nbytes, int *recvfd)
  {
struct msghdr msg;
struct iovec iov[1];
ssize_t ret;
int     err;
ST_DOUBLE recvmsg_start;

#define RECVMSG_TIMEOUT	10000		/* in milliseconds		*/

#if defined (OLD_WAY)
  /* NOTE: On HP-UX to use the msg_accrights fields compile without	*/
  /*       defining the -D_XOPEN_SOURCE_EXTENDED, -D_OPEN_SOURCE and	*/
  /*       without linking the -lxnet library).				*/
#else
  /* NOTE: On HP-UX to use the SCM_RIGHTS msg type compile with the	*/
  /*       -D_XOPEN_SOURCE_EXTENDED, -D_OPEN_SOURCE and link with the	*/
  /*       -lxnet library. Without linking the libxnet.* library the	*/
  /*       sendmsg() fails with EBADF error.				*/
  /*       See Richard Stevens "UNIX Network Programming" book.		*/

/* this just helps get alignment right	*/
union
  {
  struct cmsghdr cm;
  char control [CMSG_SPACE(sizeof(int))];
  } control_un;
struct cmsghdr *cmptr;
#endif

  SOCK_LOG_FLOW1 ("domsock %d: in recvwait_fd()", fd);

  *recvfd = -1;		/* init to invalid handle just in case the receive fails*/

#if defined (OLD_WAY)
  msg.msg_accrights = (caddr_t) recvfd;
  msg.msg_accrightslen = sizeof (int);		/* must be int			*/
#else
  msg.msg_control = control_un.control;
  msg.msg_controllen = sizeof (control_un.control);
#endif

  msg.msg_name = NULL;
  msg.msg_namelen = 0;

  iov[0].iov_base = ptr;
  iov[0].iov_len = nbytes;
  msg.msg_iov = iov;
  msg.msg_iovlen = 1;

  /* Wait for data as long as error is SOCK_WOULDBLOCK. Stop on any other error.*/
  /* NOTE: at this time there is only 1 byte of dummy data sent with this	*/
  /*       special message, but if this is changed to more bytes then the	*/
  /*       non-blocking recvmsg function may return with partial bytes.		*/
  recvmsg_start = sGetMsTime();
  while ((ret = recvmsg(fd, &msg, 0)) < 0)
    {
    err = SOCKET_ERRORNO;
    if (!(err == SOCK_WOULDBLOCK || err == SOCK_INTR ||
          err == SOCK_TIMEDOUT   || err == SOCK_INPROGRESS))
      break;	/* some non-recoverable socket error */

    /* check is we want to still wait longer for the msg			*/
    if ((sGetMsTime() - recvmsg_start) >= RECVMSG_TIMEOUT)
      {
      SOCK_LOG_NERR3 ("domsock %d: timed out in recvmsg(), errno = %d, timeout=%d", fd, err, RECVMSG_TIMEOUT);
      return (ret);	/* timeout, other side failed to send the socket handle	*/
      }
    sMsSleep(20);	/* sleep for a moment while waiting for the msg		*/
    }
  if (ret <= 0)
    {
    SOCK_LOG_NERR2 ("domsock %d: recvmsg() failed, errno = %d", fd, err);
    return (ret);	/* error we can't handle	*/
    }

#if defined (OLD_WAY)

#else
  if ((cmptr = CMSG_FIRSTHDR(&msg)) != NULL &&
      cmptr->cmsg_len == CMSG_LEN(sizeof(int)))
    {
    if (cmptr->cmsg_level != SOL_SOCKET)
      {
      SOCK_LOG_NERR1 ("domsock %d: cmsg_level != SOL_SOCKET", fd);
      *recvfd = -1; /* DEBUG: error. Book uses err_quit.*/
      }
    else if (cmptr->cmsg_type != SCM_RIGHTS)
      {
      SOCK_LOG_NERR1 ("domsock %d: cmsg_type != SCM_RIGHTS", fd);
      *recvfd = -1; /* DEBUG: error. Book uses err_quit. */
      }
    else
      *recvfd = *((int *) CMSG_DATA(cmptr));
    }
  else
    *recvfd = -1;	/* descriptor was not passed	*/
#endif

  if (*recvfd == -1)
    SOCK_LOG_NERR1 ("domsock %d: DID NOT receive socket handle from RFC1006_LISTENER task", fd);
  else
    SOCK_LOG_FLOW2 ("domsock %d: received socket handle = %d from RFC1006_LISTENER task",
                    fd, *recvfd);
  return (ret);
  }

/************************************************************************/
/*			check_domsock					*/
/* This function checks if the there are any events pending from	*/
/* RFC1006_LISTENER task.						*/
/* Note that this function does not non-blocking select.		*/
/************************************************************************/
ST_RET check_domsock (int domsock)
  {
fd_set rset, allset;
int nready;
int maxfd = 0;
struct timeval stTimeVal;

  if (domsock == INVALID_SOCKET)
    return (SD_FALSE);

  FD_ZERO (&allset);
  FD_SET (domsock, &allset);
  maxfd = max (maxfd, domsock);

  rset = allset;
  /* 0 timeout on select. Don't want to wait here.	*/
  stTimeVal.tv_sec  = 0;
  stTimeVal.tv_usec = 0;
  nready = select (maxfd + 1, &rset, NULL, NULL,  &stTimeVal);
  if (nready > 0 && FD_ISSET (domsock, &rset))
    return (SD_TRUE);
  return (SD_FALSE);
  }

/************************************************************************/
/*			rfc1006_listener_connect			*/
/* Connects to the UNIX domain socket of the RFC1006 Listener task.	*/
/* Stores the connected socket handle at the address pointed to by	*/
/* domsock.								*/
/************************************************************************/
ST_RET rfc1006_listener_connect (SOCKET *domsock)
  {
struct sockaddr_un s_un;
#if defined(__hpux) || defined(_AIX) || defined(sun) || defined(linux)
int nonblock_on=1;	/* CRITICAL: must be non-zero to enable non-blocking*/
#else
/* _WIN32 */
ST_ULONG nonblock_on=1;	/* CRITICAL: must be non-zero to enable non-blocking*/
#endif
int retcode;

  *domsock = socket (AF_LOCAL, SOCK_STREAM, 0);	/*DEBUG: why does some code use AF_UNIX */
  if (*domsock == INVALID_SOCKET)
    {
    SOCK_LOG_ERR1 ("Cannot create UNIX domain socket(), errno=%d", SOCKET_ERRORNO);
    return (SD_FAILURE);
    }

  s_un.sun_family = AF_LOCAL;
  if (strlen (tp0Ctx.listenerIPCDir) == 0)
    sprintf (s_un.sun_path, "%s/%s", RFC1006_LISTENER_IPC_PATH, RFC1006_LISTENER_DOMSOCK);
  else
    /* use the IPC directory that user set with call to setListenerIPCDir	*/
    sprintf (s_un.sun_path, "%s/%s", tp0Ctx.listenerIPCDir, RFC1006_LISTENER_DOMSOCK);
  retcode = connect (*domsock, (struct sockaddr *) &s_un, sizeof (s_un));
  if (retcode == 0)
    {
    SOCK_LOG_FLOW2 ("domsock %d: connected to RFC1006_LISTENER task (DomSockFile=%s)",
                    *domsock, s_un.sun_path);
    /* make the socket non-blocking */
    if (ioctlsocket (*domsock, FIONBIO, &nonblock_on) == -1)
      SOCK_LOG_ERR2 ("domsock %d: cannot set socket to non-blocking mode, errno = %d.",
                      *domsock, SOCKET_ERRORNO);
    }
  else
    {
    SOCK_LOG_ERR3 ("domsock %d: cannot connect() to RFC1006_LISTENER task (DomSockFile=%s), errno=%d, closing socket.",
                   *domsock, s_un.sun_path, SOCKET_ERRORNO);
    CLOSE_SOCKET (*domsock);
    *domsock = INVALID_SOCKET;
    }

  return (retcode);
  }

/************************************************************************/
/*			sockAcceptFromListenerTask			*/
/************************************************************************/
ST_RET sockAcceptFromListenerTask (SOCKET hNewSock,
	char *tpkt_buf,	/* ptr to TP0 connect.ind received from rfc1006_listener */
	int tpkt_len)
  {
ST_RET           rc;
GEN_SOCK_CONFIG  sockCfg;
GEN_SOCK        *pSock;

#if !defined(_WIN32)
  if (hNewSock >= FD_SETSIZE)
    {	/* Can't use this socket because illegal to use in "select" call*/
    SOCK_LOG_ERR1 ("sockAcceptFromListenerTask: socket num %d > FD_SETSIZE", hNewSock);
    CLOSE_SOCKET (hNewSock);
    return (SD_FAILURE);
    }
#endif

  /* Usually get sockCfg from pListenSock, but don't have that here, so just init local var*/
  rc = _sockSetDefaults (&sockCfg);

  /* OK, we have a go ... */
  pSock = _sockAllocSock (tp0Ctx.sockCtx, GS_ROLE_CALLED, GS_STATE_CONNECTED, hNewSock, &sockCfg);
  pSock->listenSocket = NULL;	/* "listenSocket" not used with rfc1006_listener task	*/

  SOCK_LOG_FLOW2 ("%s: new TCP connection passed from RFC1006_LISTENER, socket handle = %d",
                  pSock->sockIdStr, hNewSock);

  /* Set callingAddr and callingAddrLen.	*/
  pSock->callingAddrLen = sizeof (SOCKADDR_IN);
  if (sockGetRemAddrInfo (pSock, &pSock->callingAddr, NULL, NULL) != SD_SUCCESS)
    {
    SOCK_LOG_ERR1 ("%s: error getting remote address info", pSock->sockIdStr);
    }

  /* only non-secured TCP connections */
  rc = (*pSock->sockCfg.uSockConnectInd)(pSock);

  if (rc == SD_SUCCESS)
    _sockAddSock (pSock);       /* Add to a service list */
  else
    {
    CLOSE_SOCKET (hNewSock);
    chk_free (pSock);
    }

  SOCK_LOG_FLOW2 ("%s: first packet received len = %d", pSock->sockIdStr, tpkt_len);

  /* Allocate pSock->sockData and copy packet data to it.	*/
  (*pSock->sockCfg.uSockRxBufAlloc) (pSock, tpkt_len, &pSock->sockData);
  memcpy (pSock->sockData->data, tpkt_buf, tpkt_len);
  pSock->sockData->dataLen = tpkt_len;
  pSock->sockData->result = SD_SUCCESS;

  /* Pass packet up to user just like normal packet.	*/
  (*pSock->sockCfg.uSockRx)(pSock, pSock->sockData);

  return (SD_SUCCESS);
  }

/************************************************************************/
/*			rfc1006_listener_event				*/
/************************************************************************/
ST_BOOLEAN rfc1006_listener_event (ST_VOID)
  {
char tpkt_buf [1024];	/* this buffer is big enough for TP0 CR	(per JRB) */
int tpkt_len;
int recv_ret;
ST_RET retcode;
SOCKET hSockConnected;
RFC1006_IPC_MSG ipc_msg;
char dummy_byte;	/* one byte msg to read with recvwait_fd	*/

ST_BOOLEAN activityFlag = SD_FALSE;	/* assume no events processed	*/

  if (check_domsock (domsock_listener))
    {
    /* received msg on domain socket. Process it completely here.	*/
    /* receiwait & recvwait_fd read TP0 connect.ind pdu from the listener task.
     * It also gets the socket handle in hSockConnected.
     */
    SOCK_LOG_FLOW1 ("domsock %d: receiving msg from RFC1006_LISTENER...", domsock_listener);
    recv_ret = recvwait (domsock_listener, &ipc_msg, sizeof (RFC1006_IPC_MSG), 0);
    if (recv_ret == sizeof (RFC1006_IPC_MSG))
      {			/* NOTE: other opcodes maybe implemeted later	*/
      if (ipc_msg.opcode != RFC1006_IPC_OP_CONNECT)
        {
        SOCK_LOG_ERR2  ("domsock %d: received invalid opcode=%u",
                        domsock_listener, (ST_UINT) ipc_msg.opcode);
        return (activityFlag);
        }
      /* recvwait_fd waits for the socket handle in hSockConnected.	*/
      recv_ret = (int) recvwait_fd (domsock_listener, &dummy_byte, 1, &hSockConnected);
      if (recv_ret > 0)
        {
        assert (recv_ret == 1);	/* must ALWAYS be this size	*/
        /* This recvwait reads TP0 connect.ind pdu from the listener task.*/
        /* NOTE: read (data_len-1) because 1 byte already read with recvwait_fd.*/
        assert (ipc_msg.data_len-1 <= sizeof (tpkt_buf));
        tpkt_len = recv_ret = recvwait (domsock_listener, tpkt_buf, ipc_msg.data_len-1, 0);
        if (tpkt_len > 0 && hSockConnected >= 0)
          {
          /* rfc1006_listener task already did the "accept".	*/
          /* This funct should get the whole machine running.	*/
          retcode = sockAcceptFromListenerTask (hSockConnected, tpkt_buf, tpkt_len);
          activityFlag = SD_TRUE;
          }
        }
      }

/* DEBUG: In the future we could add code to reconnect to the RFC1006_LISTENER task	*/
/*         and bind our selectors. For now just let the application to continue working.*/
    if (recv_ret == 0)
      {
      SOCK_LOG_ERR1 ("domsock %d: recvwait() detected RFC1006_LISTENER socket disconnect", domsock_listener);
      CLOSE_THIS_SOCKET(domsock_listener);
      }
    else if (recv_ret < 0)
      {
      SOCK_LOG_ERR2 ("domsock %d: recvwait() detected error (errno=%d), closing RFC1006_LISTENER socket",
                     domsock_listener, SOCKET_ERRORNO);
      CLOSE_THIS_SOCKET(domsock_listener);
      }
    }
  return (activityFlag);
  }
#endif  /* defined(MMSEASE_MOSI) */

	/*----------------------------------------------*/
	/*	Initialization / Cleanup		*/
	/*----------------------------------------------*/

/************************************************************************/
/*			np_init						*/
/* NOTE: max_num_conns arg used only by listen sockets.			*/
/************************************************************************/
ST_RET np_init (ST_INT max_num_conns)
  {
ST_RET rc;
ST_INT i;

#if defined(MMSEASE_MOSI)
  tp0Ctx.tcpEventWakeupPortBase  = 55051;	/* base listen port		*/
  tp0Ctx.tcpEventWakeupPortRange = 100;		/* range to search for free port*/
  tp0Ctx.tcpEventWakeupPort = 0;		/* actual wakeup port		*/
  tp0Ctx.hTcpEventSender = INVALID_SOCKET;	/* set by gensock2 service thread*/
#endif

  if (tp0Ctx.state != TP0_SOCK_CTX_STATE_IDLE)
    {
    SOCK_LOG_NERR0 ("np_init: TP0 Context State not IDLE.");
    return (SD_FAILURE);
    }

  SOCK_LOG_FLOW1 ("np_init: initializing Network layer ... TCP max_num_conns = %d.", max_num_conns);

  /* Create "TCP" Event Semaphore.	*/
#if defined(_WIN32)
  if (!(hTcpEvent = gs_get_event_sem (SD_FALSE)))
    {
    SOCK_LOG_ERR0 ("np_init: error creating TCP Event Semaphore.");
    return (SD_FAILURE);
    }
#endif

  /* initialize gensock2 before calling any of the socket functions */
  rc = sockStart ("TP0_SOCKS", &tp0Ctx.sockCtx);
  if (rc != SD_SUCCESS)
    {
    SOCK_LOG_ERR1 ("np_init: sockStart() failed, rc=%d", rc);
#if defined(_WIN32)
    gs_free_event_sem (hTcpEvent);
#endif
    return (rc);
    }

#if defined(MMSEASE_MOSI)
  if ((rc = sockCreateWakeupSockets ( tp0Ctx.sockCtx,
                                  tp0Ctx.tcpEventWakeupPortBase, tp0Ctx.tcpEventWakeupPortRange,
                                  &tp0Ctx.tcpEventWakeupPort,
                                  &tp0Ctx.hTcpEventSender, &mms_event_fd)) != SD_SUCCESS)
    {
    sockEnd (tp0Ctx.sockCtx);
    tp0Ctx.sockCtx = NULL;
    return (rc);
    }
#endif /* defined(MMSEASE_MOSI) */

  /* start the security components */
  rc = sSecStart (&tp0Ctx.secCfg);
  if (rc != SD_SUCCESS)
    {
    SOCK_LOG_ERR1 ("np_init: sSecStart() failed, rc=%d", rc);
    _sockClean ();
    return (rc);
    }

#if defined(MMSEASE_MOSI)
  /* MMSEASE_MOSI uses the RFC1006_LISTENER task to listen for TCP connections,	*/
  /* but it is not required to do so. Instead the application could listen for	*/
  /* TCP connections itself if it is the only RFC1006 port listener in the system.*/
  /* This is an undocumented option that maybe exposed in the future to		*/
  /* selected customers when need arises.					*/
  if (use_rfc1006_listener_task)
    {
    /* NOTE: if RFC1006_LITENER task is used then the UNIX domain socket will	*/
    /*       handle only non-secure connections.				*/
    rc = rfc1006_listener_connect (&domsock_listener);
    if (rc != SD_SUCCESS)
      _sockClean ();
    return (rc);
    }
#endif /* defined(MMSEASE_MOSI) */
  /* If !use_rfc1006_listener_task, continue with default code.			*/
#if !defined(MMSEASE_MOSI)
  /* only MMS_LITE configures num_called */
  if (mvl_cfg_info->num_called)
#endif
    {
    /* start listening for non-secured connections from remotes		*/
    if (!tp0Ctx.secCfg->secureModeEnabled || tp0Ctx.secCfg->encryptReqCalled == SD_FALSE)
      {
      rc = _sockInitListen (SOCK_LISTEN_NON_SSL, 0, max_num_conns);
      if (rc != SD_SUCCESS)
        {
        _sockClean ();
        return (rc);
        }
      }

    /* start listening for secured connections from remotes (multiple ports maybe configured)	*/
    if (tp0Ctx.secCfg->secureModeEnabled)
      {
      for (i=0; i<tp0Ctx.secCfg->numSslListenPorts; ++i)
        {
        rc = _sockInitListen (SOCK_LISTEN_SSL, i, max_num_conns);
        if (rc != SD_SUCCESS)
          {
          rc = _sockClean ();
          return (SD_FAILURE);
          }
        }
      }
    }

  if (rc == SD_SUCCESS)
    {
    tp0Ctx.state = TP0_SOCK_CTX_STATE_ACTIVE;
    SOCK_LOG_FLOW0 ("np_init: initialization successful.");
    }

  return (rc);
  }

/************************************************************************/
/*			_sockSetDefaults				*/
/*----------------------------------------------------------------------*/
/* Initialize socket cfg params (used for secure/non-secure connections)*/
/************************************************************************/
static ST_RET _sockSetDefaults (GEN_SOCK_CONFIG *sockCfg)

{
ST_RET rc = SD_SUCCESS;

  SOCK_LOG_FLOW0 ("in _sockSetDefaults()");

  memset (sockCfg, 0, sizeof (GEN_SOCK_CONFIG));	/* start clean	*/

  /* set socket parameters */

  sockCfg->hdrSize     = RFC1006_HEAD_LEN;	/* RFC1006 header len	*/

  /* set sockopt parameters */
  sockCfg->setSockOpts = SD_TRUE;
  sockCfg->noDelay     = SD_TRUE;
  sockCfg->keepAlive   = SD_TRUE;
  sockCfg->reuseAddr   = SD_TRUE;  	/* SO_REUSEADDR for quick restart */
  sockCfg->rcvBufSize  = 0;		/* use default socket buffer size */
  sockCfg->sndBufSize  = 0;		/* use default socket buffer size */

  sockCfg->pauseRecv   = SD_FALSE;	/* used to apply back pressure	  */
  sockCfg->listenBacklog = 0;		/* if 0,  SOMAXCONN used	  */

  /* set callback funcs for non-secured connections from remotes	*/

  sockCfg->uSockConnectInd = &_uSockConnectInd;
  sockCfg->uSockConnectConf= &_uSockConnectDone;
  sockCfg->uSockDisconnect = &_uSockDisconnectInd;
  sockCfg->uSockRx         = &_uSockRxInd;
  sockCfg->uSockWritable   = &_uSockWritable;
  sockCfg->uSockHunt       = &_uSockHunt;
  sockCfg->uSockRxBufAlloc = &_uSockDataAlloc;
  sockCfg->uSockTxBufFree  = &_uSockDataFree;

  /*  sockCfg->recvEvent    = not used				*/
  /*  sockCfg->usr1         = not used				*/

  return (rc);
}

/************************************************************************/
/*			_sockInitListen					*/
/*----------------------------------------------------------------------*/
/* Initialize listen socket. 						*/
/************************************************************************/
static ST_RET _sockInitListen (ST_UINT    type,
			       ST_UINT    idx,
			       ST_INT     max_num_conns)

{
ST_RET          rc;
GEN_SOCK_CONFIG sockCfg;
ST_UINT16       listenPort;
ST_UINT         maxActive;
GEN_SOCK      **pListenSock;

  SOCK_LOG_FLOW1 ("%s: in _sockInitListen()", tp0Ctx.sockCtx->ctxName);

  /* set socket parameters */

  rc = _sockSetDefaults (&sockCfg);

  if (type == SOCK_LISTEN_SSL)
    {
    /* set callback functions for secure connections from remotes */
    setGenSockSSL (&sockCfg); /* sets sockCfg.secEnable=SD_TRUE & secure fun ptrs */
    listenPort  =  tp0Ctx.secCfg->sslListenPorts[idx];
    maxActive   =  max_num_conns;
    pListenSock = &tp0Ctx.remListenSockSSL[idx];
    }
  else
    {
    /* SOCK_LISTEN_NON_SSL */
    if (tp0_cfg.rfc1006_listen_port)
      listenPort  =  tp0_cfg.rfc1006_listen_port;
    else
      listenPort  =  IPPORT_RFC1006;		/* use the default port */
    tp0Ctx.rfc1006Port = listenPort;	/* save the port used	*/
    maxActive   =  max_num_conns;
    pListenSock = &tp0Ctx.remListenSock;
    }

  /* init the listening socket */
  rc = sockInitListen (tp0Ctx.sockCtx, &sockCfg, listenPort, maxActive, pListenSock);
  if (rc != SD_SUCCESS)
    {
    SOCK_LOG_ERR4 ("%s: sockInitListen() failed for port=%u, rc=%d %s",
                   tp0Ctx.sockCtx->ctxName, (ST_UINT) listenPort, rc,
                   (rc== SOCK_EADDRINUSE) ? "(port already used)" : "");
    *pListenSock = NULL;	/* need to be set if bind fails	*/
    return (SD_FAILURE);
    }

  SOCK_LOG_FLOW2 ("%s: listening on port=%u", (*pListenSock)->sockIdStr, (ST_UINT) listenPort);

  return (SD_SUCCESS);
}

/************************************************************************/
/*			_sockCloseAllListen				*/
/* Closes all listen sockets. Currently the only return is SD_SUCCESS.	*/
/************************************************************************/
static ST_RET _sockCloseAllListen (ST_VOID)
{
ST_INT i;

#if defined(MMSEASE_MOSI)
  /* disconnect domain socket to avoid incoming connections	*/
  if (use_rfc1006_listener_task)
    CLOSE_THIS_SOCKET(domsock_listener);
#endif

  /* Close all listen sockets to avoid handling incoming connections */
  if (tp0Ctx.secCfg)
    for (i=0; i<tp0Ctx.secCfg->numSslListenPorts; ++i)
      if (tp0Ctx.remListenSockSSL[i])
        {
        SOCK_LOG_FLOW2 ("%s: closing secure listening port=%d",
          tp0Ctx.remListenSockSSL[i]->sockIdStr, tp0Ctx.secCfg->sslListenPorts[i]);
        sockClose (tp0Ctx.remListenSockSSL[i]);
	}

  if (tp0Ctx.remListenSock)
    {
    SOCK_LOG_FLOW2 ("%s: closing listening port=%d",
                    tp0Ctx.remListenSock->sockIdStr, tp0Ctx.rfc1006Port);
    sockClose (tp0Ctx.remListenSock);
    }

  return SD_SUCCESS;
}

/************************************************************************/
/*			_sockClean					*/
/************************************************************************/
static ST_RET _sockClean (ST_VOID)
{
ST_RET rc;

  SOCK_LOG_FLOW1 ("%s: in _sockClean()", tp0Ctx.sockCtx->ctxName);

  /* CRITICAL: release resources in reverse order.	*/

  /* close all listen sockets to avoid handling incoming connections */
  _sockCloseAllListen ();

  /* terminate Security Manager  */
  rc = sSecEnd ();

  /* cleanup gensock2 resources, terminate threads,... */
  rc = sockEnd (tp0Ctx.sockCtx);
  tp0Ctx.sockCtx = NULL;

  /* free events and mutexes */
#if defined(_WIN32)
  gs_free_event_sem (hTcpEvent);
#endif
#if defined(MMSEASE_MOSI)
  CLOSE_THIS_SOCKET(domsock_listener);
  CLOSE_THIS_SOCKET(tp0Ctx.hTcpEventSender);
  CLOSE_THIS_SOCKET(mms_event_fd);
#endif

  return (SD_SUCCESS);
}

/************************************************************************/
/*			np_end						*/
/* This function will terminate the operation of the Network layer	*/
/*									*/
/* Parameters:								*/
/*	ST_VOID			none					*/
/*									*/
/* Return:								*/
/*	SD_SUCCESS (0)		if termination successful		*/
/*	error code		otherwise				*/
/************************************************************************/
ST_RET np_end (ST_VOID)
  {
ST_RET rc;
GEN_SOCK_EVENT *sdi;

  SOCK_LOG_FLOW1 ("%s: in np_end()", tp0Ctx.sockCtx->ctxName);

  tp0Ctx.state = TP0_SOCK_CTX_STATE_TERMINATING;

  /* close all listen sockets to avoid handling incoming connections */
  _sockCloseAllListen ();

  /* Finish processing of disconnect events. Ignore all other events.	*/
  sMsSleep (100);	/* let other threads finish disconnects		*/

  /* Get all events off list and process them.	*/
  while ((sdi = sockEventGet (tp0Ctx.sockCtx)) != NULL)
    {
    if (sdi->eventType == GS_EVENT_DISCONNECT)
      {
      SOCK_LOG_FLOW1 ("%s: np_end: processing Event Indication IndType=DISCONNECT.",
                      sdi->pSock->sockIdStr);
      _processDisconnectInd (sdi->pSock);
      }
    else if (sdi->eventType == GS_EVENT_CONNECT_IND)
      {
      SOCK_LOG_FLOW1 ("%s: np_end: IGNORING Event Indication IndType=CONNECT (closing socket).",
                      sdi->pSock->sockIdStr);
      sockClose (sdi->pSock);
      }
    else if (sdi->eventType == GS_EVENT_DATA_IND)
      {
      SOCK_LOG_FLOW1 ("%s: np_end: IGNORING Event Indication IndType=RXDATA (closing socket).",
                      sdi->pSock->sockIdStr);
      _uSockDataFree (sdi->pSock, sdi->sockData);
       }
    else
      SOCK_LOG_FLOW3 ("%s: np_end: IGNORING Event Indication IndType=%d (%s).",
                      sdi->pSock->sockIdStr, sdi->eventType,
      (sdi->eventType < sizeof(eventTypeStr)) ? eventTypeStr[sdi->eventType] : "UNKNOWN");

    chk_free (sdi);
    }	/* end loop processing all events	*/

  rc = _sockClean ();

  tp0Ctx.state = TP0_SOCK_CTX_STATE_IDLE;
  return (rc);
  }

	/*----------------------------------------------*/
	/*	Event/Indication Handling		*/
	/*----------------------------------------------*/

#if defined(MMSEASE_MOSI)
ST_VOID drain_wakeup_sock (ST_VOID)
  {
ST_CHAR dataBucket[256];
ST_INT  recvRet;
ST_INT  err;

  /* Non-blocking receive, dump wakeup data */
  if (mms_event_fd != INVALID_SOCKET)
    {
    recvRet = (ST_INT) recv (mms_event_fd, dataBucket, sizeof (dataBucket), 0);
    if (recvRet > 0)
      {
      SOCK_LOG_FLOW3 ("%s: XSocket received %d wakeup bytes, byte[0]=%d",
                     tp0Ctx.sockCtx->ctxName, recvRet, (ST_UINT) ((ST_UCHAR) dataBucket[0]));
      }
    else  if (recvRet == 0)
      {
      SOCK_LOG_ERR1 ("%s: XSocket disconnected", tp0Ctx.sockCtx->ctxName);
      CLOSE_THIS_SOCKET(mms_event_fd);
      }
    else
      {
      err = SOCKET_ERRORNO;
      if (err == SOCK_WOULDBLOCK || err == SOCK_INTR ||
          err == SOCK_TIMEDOUT   || err == SOCK_INPROGRESS)
        {
        /* recoverable error or nothing received */
        }
      else
        {
        SOCK_LOG_ERR3 ("%s: XSocket error, recv() returned %d, errno = %d",
                       tp0Ctx.sockCtx->ctxName, recvRet, err);
        CLOSE_THIS_SOCKET(mms_event_fd);
        }
      }
    }
  }
#endif /* defined(MMSEASE_MOSI) */

/************************************************************************/
/*			np_event					*/
/* This function is called to process network events.			*/
/************************************************************************/
ST_BOOLEAN np_event (ST_VOID)
  {
GEN_SOCK_EVENT *sdi;
ST_BOOLEAN activityFlag = SD_FALSE;	/* assume no events processed	*/

#if defined(MMSEASE_MOSI)
  if (use_rfc1006_listener_task)
    rfc1006_listener_event ();
#endif	/* defined(MMSEASE_MOSI) */

#if !defined(GENSOCK_THREAD_SUPPORT)
  /* Service all sockets.						*/
  /* NOTE: this may add "many" entries to the linked list.		*/
  /* User should have already waited for event, so use timeout=0 here.	*/
  sockServiceAll (tp0Ctx.sockCtx, 0);	/* arg is timeout in milliseconds*/
#endif	/* !GENSOCK_THREAD_SUPPORT	*/

#if defined(MMSEASE_MOSI)
  drain_wakeup_sock ();
#endif

  /* CRITICAL: Get one and only one entry off linked list. If we get more,*/
  /* MVL queue fills up, and user can't process other events, including TP4.*/
  if ((sdi = sockEventGet (tp0Ctx.sockCtx)) != NULL)
    {
    activityFlag = SD_TRUE;		/* 1 event processed	*/
    S_LOCK_UTIL_RESOURCES ();
    /* check if we need to enable reception of data (we have flow control to	*/
    /* prevent excessive memory allocations when data messages are received	*/
    /* faster than the application can process)					*/
    if (sdi->eventType == GS_EVENT_DATA_IND)
      {
      SOCK_INFO *sock_info = (SOCK_INFO *) sdi->pSock->sockCfg.usr2; /* get (SOCK_INFO *) from GEN_SOCK	*/
      if (sock_info->recvCnt > 0)
        --sock_info->recvCnt;
      if (sock_info->recvCnt <= SOCK_RX_QUE_LOW_MARK && sdi->pSock->sockCfg.pauseRecv == SD_TRUE)
        {
        sdi->pSock->sockCfg.pauseRecv = SD_FALSE;
        SOCK_LOG_FLOW2 ("%s: recvCnt=%u setting pauseRecv=SD_FALSE", sdi->pSock->sockIdStr, sock_info->recvCnt);
        sockServiceWakeAll (tp0Ctx.sockCtx);
	}
      }
    S_UNLOCK_UTIL_RESOURCES ();
    SOCK_LOG_FLOW3 ("%s: processing Event Indication IndType=%d (%s).",
                    sdi->pSock->sockIdStr, sdi->eventType,
                    (sdi->eventType < sizeof(eventTypeStr)) ? eventTypeStr[sdi->eventType] : "UNKNOWN");

    switch (sdi->eventType)
      {
      case GS_EVENT_CONNECT_IND:
        _processConnectInd (sdi->pSock);
      break;

      case GS_EVENT_CONNECT_CONF:
        _processConnectDone (sdi->pSock);
      break;

      case GS_EVENT_DISCONNECT:
        _processDisconnectInd (sdi->pSock);
      break;

      case GS_EVENT_DATA_IND:
        _processRxInd (sdi->pSock, sdi->sockData);
      break;

      default:
        assert (0);	/* Unknown eventType	*/
      }
    chk_free (sdi);
    }

  /* we have to take care of rekeying every once a while, since this	*/
  /* function is called periodically (at least once every 1 sec) we	*/
  /* use it to do the job						*/
  _handleRekeying ();

  return (activityFlag);
  }

/************************************************************************/
/*			_setSecInfo					*/
/************************************************************************/
static ST_RET _setSecInfo (GEN_SOCK *pSock, S_SEC_ENCRYPT_CTRL *encrypt_ctrl)
{
ST_RET  rc;

  rc = sSecGetCipherSuite (pSock, &encrypt_ctrl->u.ssl.cipherSuite);
  if (rc != SD_SUCCESS)
    {
    SOCK_LOG_NERR2 ("%s: failed to obtain Cipher Suite (rc=%d)", pSock->sockIdStr, rc);
    return (rc);
    }

  rc = sSecGetCertCtrl (pSock, &encrypt_ctrl->u.ssl.sslCert);
  if (rc == SD_SUCCESS)
    {
    /* SD_SUCCESS means that this is a secured connection	*/
    encrypt_ctrl->encryptMode = S_SEC_ENCRYPT_SSL;

    /* if the remote certificate is not config the function above may return	*/
    /* NULL for the sslCert pointer						*/
    if (encrypt_ctrl->u.ssl.sslCert)
      encrypt_ctrl->u.ssl.sslCertMatched = SD_TRUE;
    else
      encrypt_ctrl->u.ssl.sslCertMatched = SD_FALSE;
    }
  else
    SOCK_LOG_NERR2 ("%s: failed to obtain Certificate Ctrl (rtn=%d)", pSock->sockIdStr, rc);

  return (rc);
}

/************************************************************************/
/*			_processConnectInd				*/
/* Accepted new socket connection, let user know.			*/
/************************************************************************/
static ST_VOID _processConnectInd (GEN_SOCK *pSock)
  {
ST_RET              rc;
SOCK_INFO          *sock_info;
S_SEC_ENCRYPT_CTRL *encrypt_ctrl;

  /* For a listening socket we will attach the GEN_SOCK to our user ctrl*/
  /* Pass (GEN_SOCK *) instead of SOCKET as first arg.			*/
  /* This saves (GEN_SOCK *) in SOCK_INFO.				*/
  sock_info = sock_info_alloc2 (pSock, SOCK_STATE_ACCEPTED,
                               INVALID_CONN_ID);
  sock_info->ip_addr = pSock->callingAddr.sin_addr.s_addr; /* Save remote IP addr	*/
  pSock->sockCfg.usr2 = sock_info;			   /* Save (SOCK_INFO *) in GEN_SOCK*/
  encrypt_ctrl = &sock_info->encrypt_ctrl;

  /* if secured connection extract encryption info */
  if (pSock->sockCfg.secEnable)
    {
    rc = _setSecInfo (pSock, encrypt_ctrl);
    if (rc != SD_SUCCESS)
      {
      pSock->sockCfg.usr2 = NULL;	/* to prevent use of invalid sock_info	*/
      sock_info_free (sock_info);
      sockClose (pSock);
      return;
      }
    sock_info->rekeyTime = sGetMsTime() + SOCK_REKEY_TIME;
    /* add sock_info to list of secured sockets */
    S_LOCK_UTIL_RESOURCES ();
    list_add_last (&tp0Ctx.secureSockList, sock_info);
    S_UNLOCK_UTIL_RESOURCES ();
    }

  handle_accepted_conn (sock_info);
  }

/************************************************************************/
/*			handle_accepted_conn				*/
/************************************************************************/
ST_VOID handle_accepted_conn (SOCK_INFO *sock_info)
  {
  /* User only cares about T-CONNECT.ind.  Just log this.		*/
  SOCK_LOG_RX1 ("N-CONNECT.ind:  sock_info = 0x%X", sock_info);
  sock_info->state = SOCK_STATE_CONNECTED;
  }

/************************************************************************/
/*			_processConnectDone				*/
/* Socket connection established, let user know.			*/
/************************************************************************/
static ST_VOID _processConnectDone (GEN_SOCK *pSock)
  {
ST_RET              rc;
SOCK_INFO          *sock_info = (SOCK_INFO *) pSock->sockCfg.usr2; /* get (SOCK_INFO *) from GEN_SOCK	*/
S_SEC_ENCRYPT_CTRL *encrypt_ctrl;

  assert (sock_info);
  sock_info->genSock = pSock;	/* CRITICAL: save pSock now	*/

  /* it is possible that if the connection took long time then the application 	*/
  /* called already np_disconnect_req						*/
  if (sock_info->state == SOCK_STATE_CONNECT_CANCELLED)
    sockClose (pSock);	/* couldn't call this function from np_disconnect_req	*/
  else if (sock_info->state == SOCK_STATE_CONNECTING)
    {
    /* if secured connection extract encryption info */
    if (pSock->sockCfg.secEnable)
      {
      encrypt_ctrl = &sock_info->encrypt_ctrl;
      rc = _setSecInfo (pSock, encrypt_ctrl);
      if (rc != SD_SUCCESS)
        {
        sockClose (pSock);
        return;
        }
      sock_info->rekeyTime = sGetMsTime() + SOCK_REKEY_TIME;
      /* add sock_info to list of secured sockets */
      S_LOCK_UTIL_RESOURCES ();
      list_add_last (&tp0Ctx.secureSockList, sock_info);
      S_UNLOCK_UTIL_RESOURCES ();
      }

    handle_connect_success (sock_info);
    }
  else
    SOCK_LOG_ERR2 ("%s: _processConnectDone invalid state=%d", pSock->sockIdStr, sock_info->state);
  }

/************************************************************************/
/*			handle_connect_success				*/
/************************************************************************/
ST_VOID handle_connect_success (SOCK_INFO *sock_info)
  {
  /* Pass up N-CONNECT.cnf+ to user.	*/
  SOCK_LOG_RX1 ("N-CONNECT.cnf+ (pos): user_conn=%d", sock_info->user_conn_id);
  np_connect_cnf_pos (sock_info, sock_info->user_conn_id);
  sock_info->state = SOCK_STATE_CONNECTED;
  }

/************************************************************************/
/*			_processDisconnectInd				*/
/************************************************************************/
static ST_VOID _processDisconnectInd (GEN_SOCK *pSock)
  {
SOCK_INFO *sock_info = (SOCK_INFO *) pSock->sockCfg.usr2;

  if (pSock->sockCfg.secEnable)
    {
    if (sock_info)
      {
      S_LOCK_UTIL_RESOURCES ();
      if (list_find_node (tp0Ctx.secureSockList, sock_info) == SD_SUCCESS)
        /* del sock_info from list of secured sockets */
        list_unlink (&tp0Ctx.secureSockList, sock_info);
      S_UNLOCK_UTIL_RESOURCES ();
      }
    else
      {
      /* in this case a remote node attempted to connect on a secured port	*/
      /* but for some SSL reason the socket connection need to be terminated	*/
      sockClose (pSock);
      sockFree (pSock);
      return;	/* can't do anything else	*/
      }
    }

  if (sock_info)
    {
    /* If we disconnected, don't call handle_disconnect.	*/
    if (!(sock_info->state == SOCK_STATE_DISCONNECTING ||
          sock_info->state == SOCK_STATE_CONNECT_CANCELLED))
      handle_disconnect (sock_info);

    sock_info_free (sock_info);
    }
  else
    SOCK_LOG_ERR1 ("%s: _processDisconnectInd sock_info=NULL", pSock->sockIdStr);

  sockFree (pSock);	/* Totally done with this socket now.	*/
  }

/************************************************************************/
/*			handle_disconnect				*/
/************************************************************************/
ST_VOID handle_disconnect (SOCK_INFO *sock_info)
  {
  SOCK_LOG_RX2 ("N-DISCONNECT.ind:  sock_info = 0x%X, user_conn = %d",
          sock_info, sock_info->user_conn_id);
  np_disconnect_ind (sock_info);
  }

/************************************************************************/
/*			_processRxInd					*/
/************************************************************************/
static ST_VOID _processRxInd (GEN_SOCK *pSock, GEN_SOCK_DATA *sockData)
  {
  /* data is only valid if result==SD_SUCCESS	*/
  if (sockData->result == SD_SUCCESS)
    {
    /* rxData->data includes 4-byte RFC-1006 header. That's what handle_data wants.*/
    assert (sockData->dataLen <= 65535);	/* RFC-1006 limit	*/
    handle_data ((SOCK_INFO *)pSock->sockCfg.usr2, sockData->data,
                 (ST_UINT16)sockData->dataLen);
    }
  _uSockDataFree (pSock, sockData);
  }

/************************************************************************/
/*			handle_data					*/
/* Parameters:								*/
/* 	sock_info	ptr to socket tracking struct			*/
/*	tpkt_ptr	ptr to RFC1006 TPKT.				*/
/*	tpkt_len	len of RFC1006 TPKT.				*/
/************************************************************************/
ST_VOID handle_data (SOCK_INFO *sock_info, ST_UCHAR *tpkt_ptr, ST_UINT16 tpkt_len)
  {
  SOCK_LOG_RX3 ("N-DATA.ind:  sock_info = 0x%X, user_conn = %d tpkt_len = %d",
     sock_info, sock_info->user_conn_id, tpkt_len);
  SOCK_LOG_RXH (tpkt_len, tpkt_ptr);
  np_data_ind (sock_info, tpkt_ptr, tpkt_len);
  }

	/*----------------------------------------------*/
	/*	Connection Request / Indication		*/
	/*----------------------------------------------*/

/************************************************************************/
/*			np_connect_req					*/
/* RETURNS:								*/
/*	SOCK_INFO *	ptr to socket info for new socket,  OR		*/
/*			NULL if connect fails immediately.		*/
/************************************************************************/
SOCK_INFO *np_connect_req (ST_LONG user_conn_id, ST_ULONG ipAddr, ST_UINT16 rem_port,
                           S_SEC_ENCRYPT_CTRL *encrypt_ctrl)
  {
ST_RET          rc;
SOCK_INFO      *sock_info;	/* new tracking struct for this conn.	*/
struct in_addr  sin_addr;	/* inet_ntoa needs this addr format	*/
ST_CHAR        *tmp_ptr;
ST_CHAR         addr_string [32];		/* local copy of addr	*/
GEN_SOCK_CONFIG sockCfg = {0};
ST_UINT16       port;
GEN_SOCK       *pGenSock;

  SOCK_LOG_TX1 ("N-CONNECT.req:        user_conn=%d", user_conn_id);

  /* MMS Lite stores IP Addr as ULONG. Must convert back to string.	*/
  sin_addr.s_addr = ipAddr;
  tmp_ptr = inet_ntoa (sin_addr);
  assert (strlen (tmp_ptr) < sizeof (addr_string));
  strcpy (addr_string, tmp_ptr);

  /* Must do this first, because connect ind callback may be called
   * before returning from sockInitCalling!
   */
  sock_info = sock_info_alloc2 (NULL, SOCK_STATE_CONNECTING, user_conn_id);


  /* setup rem socket params and connect to the rem IP Addr, Port	*/
  _sockSetDefaults (&sockCfg);
  sockCfg.reuseAddr = SD_FALSE;	/* Override setting from _sockSetDefaults.*/

  /* save our control ptr (used in callback functions) */
  sockCfg.usr2 = (ST_VOID *) sock_info;

  if (encrypt_ctrl->encryptMode == S_SEC_ENCRYPT_SSL)
    {
    /* secure connection requested, set the security functions hooks	*/
    setGenSockSSL (&sockCfg); /* sets sockCfg.secEnable=SD_TRUE & secure fun ptrs */
    port = encrypt_ctrl->u.ssl.port;
    }
  else
    {
    /* non-secured connection */
    if (rem_port)
      port = rem_port;			/* use configured remote port	*/
    else
      port = IPPORT_RFC1006;
    }

  /* connect to Remote */
  /* NOTE: The callback may be called before
   * sockInitCalling returns, so just save the (GEN_SOCK *) to "sock_info->genSock"
   * in the callback function (_uSockConnectInd).
   */
  SOCK_LOG_TX4 ("N-CONNECT.req:        sock_info=0x%X, connection pending to IP Address='%s' Port=%u %s",
                  sock_info, addr_string, port,
                  (encrypt_ctrl->encryptMode==S_SEC_ENCRYPT_SSL) ? "(SSL)" : "");

  rc = sockInitCalling (tp0Ctx.sockCtx, &sockCfg, port, addr_string, &pGenSock);
  /* DEBUG Note: the pGenSock may need to be in the SOCK_INFO struct */

  if (rc != SD_SUCCESS)
    {		/* failed, clean up	*/
    sock_info_free (sock_info);
    sock_info = NULL;
    }

  return (sock_info);
  }

/************************************************************************/
/*                      _uSockConnectDone                               */
/* This is gensock2 callback function called when socket connection	*/
/* to the remote has been established.					*/
/************************************************************************/

static ST_RET _uSockConnectDone (GEN_SOCK *pSock)
  {
ST_RET rtn;

  SOCK_LOG_FLOW1 ("%s: in _uSockConnectDone()", pSock->sockIdStr);

  rtn = _addSockInd (pSock, GS_EVENT_CONNECT_CONF, NULL);
  return (rtn);
  }

/************************************************************************/
/*                      _uSockConnectInd                                */
/* This is gensock2 callback function when a socket connection has been	*/
/* accepted from remote.						*/
/************************************************************************/

static ST_RET _uSockConnectInd (GEN_SOCK *pSock)
  {
ST_RET rtn;
ST_CHAR *SSLstr;

  if (pSock->sockCfg.secEnable)
    SSLstr = "SSL";
  else
    SSLstr = "";
  SOCK_LOG_FLOW4 ("%s: in _uSockConnectInd(), received %s connection from"
                  " IP Address=%s Port=%u", pSock->sockIdStr, SSLstr,
    inet_ntoa (pSock->callingAddr.sin_addr), (ST_UINT) ntohs (pSock->callingAddr.sin_port));

  rtn = _addSockInd (pSock, GS_EVENT_CONNECT_IND, NULL);
  return (rtn);
  }

	/*----------------------------------------------*/
	/*	Disconnection Request / Indication	*/
	/*----------------------------------------------*/

/************************************************************************/
/*			np_disconnect_req				*/
/* This function is called by the user to break connection		*/
/************************************************************************/

ST_RET np_disconnect_req (SOCK_INFO *sock_info)
  {
ST_RET retCode;
  SOCK_LOG_TX2 ("N-DISCONNECT.req:  sock_info = 0x%X, user_conn = %d",
     sock_info, sock_info->user_conn_id);


  if (sock_info->genSock == NULL)
    {
    /* this is the case when application issues connect request but calls disconnect	*/
    /* before the socket connection gets established (for example because of timeout).	*/
    SOCK_LOG_NERR3 ("N-DISCONNECT.req:  disconnect delayed (connect pending), \n"
                    "                     sock_info = 0x%X, user_conn = %d, state = %d",
        sock_info, sock_info->user_conn_id, sock_info->state);
     /* change the state to avoid calling any transport functions from this point on 	*/
    sock_info->state = SOCK_STATE_CONNECT_CANCELLED;
    retCode = SD_FAILURE;
    }
  else
    {
    /* change the state to avoid calling any transport functions from this point on 	*/
    sock_info->state = SOCK_STATE_DISCONNECTING;
    retCode = sockClose (sock_info->genSock);
    }

  return (retCode);
  /* sock_info is not freed until _processDisconnectInd.	*/
  }

/************************************************************************/
/*                      _uSockDisconnectInd                             */
/* This is gensock2 callback function when socket gets disconnected or	*/
/* we call sockClose.							*/
/************************************************************************/
static ST_VOID _uSockDisconnectInd (GEN_SOCK *pSock)
  {
ST_RET     rtn;
ST_CHAR   *errptr;
ST_INT     i;

  switch (pSock->disconnectReason)
    {
    case GS_DISCONNECT_CONNECT_FAILED:	errptr= "CONNECT_FAILED"; break;
    case GS_DISCONNECT_USR_REFUSED:	errptr= "USER_REFUSED"; break;
    case GS_DISCONNECT_SEND_FAILURE:	errptr= "SEND_FAILURE"; break;
    case GS_DISCONNECT_RECV_FAILED:	errptr= "RECEIVE_FAILED"; break;
    case GS_DISCONNECT_ACCEPT_FAILED:	errptr= "ACCEPT_FAILED"; break;
    case GS_DISCONNECT_CLOSED:		errptr= "SOCKET_CLOSED"; break;
    case GS_DISCONNECT_TERMINATING:	errptr= "TERMINATING"; break;
    case GS_DISCONNECT_RESOURCES_ERROR:	errptr= "RESOURCES_ERROR"; break;
    case GS_DISCONNECT_INTERNAL_ERROR:	errptr= "INTERNAL_ERROR"; break;

    case GS_DISCONNECT_UNKNOWN:
    default:				errptr= "UNKNOWN"; break;
    }
  SOCK_LOG_FLOW2 ("%s: in _uSockDisconnectInd() reason=%s", pSock->sockIdStr, errptr);

  /* CRITICAL: deal with GS_ROLE_LISTENING now. This happens when server is
   * exiting. _processDisconnectInd may not be called again.
   */
  if (pSock->role == GS_ROLE_LISTENING)
    {
    if (pSock == tp0Ctx.remListenSock)
      {
      SOCK_LOG_FLOWC1 (" for non-secured listening port=%d", tp0Ctx.rfc1006Port);
      tp0Ctx.remListenSock = NULL;
      }
    else
      {
      for (i=0; i<S_SSL_MAX_LISTEN_PORTS; ++i)
        {
        if (pSock == tp0Ctx.remListenSockSSL[i])
	  {
          SOCK_LOG_FLOWC1 (" for secured listening port=%d", tp0Ctx.secCfg->sslListenPorts[i]);
          tp0Ctx.remListenSockSSL[i] = NULL;
	  break;
	  }
        }
      }
    sockFree (pSock);
    return;
    }

  rtn = _addSockInd (pSock, GS_EVENT_DISCONNECT, NULL);
  if (rtn != SD_SUCCESS && tp0Ctx.state == TP0_SOCK_CTX_STATE_TERMINATING)
    {
    SOCK_INFO *sock_info = pSock->sockCfg.usr2;
    /* since we will not pass the disconnect ind to the main thread clean the	*/
    /* sock_info here 								*/
    if (sock_info)
      sock_info_free (sock_info);

    sockFree (pSock);
    }
  }

	/*----------------------------------------------*/
	/*	Data Request / Indication		*/
	/*----------------------------------------------*/

/************************************************************************/
/* np_data_req								*/
/* Parameters:								*/
/*  eot			SD_TRUE if last TPDU msg in a SPDU.		*/
/* RETURN CODES:							*/
/*	SD_SUCCESS or SD_FAILURE					*/
/************************************************************************/
ST_RET np_data_req (SOCK_INFO *sock_info, ST_INT tpkt_len, ST_UCHAR *tpkt_ptr,
                    ST_BOOLEAN eot)
  {
GEN_SOCK_DATA *sockData;
ST_RET rc;

  assert (sock_info->genSock != NULL);

  /* check if queueing limit has been reached to prevent the excessive	*/
  /* growth of the outbound queue in gensock2.c				*/
  if (sockTxQueueGroupCntGet (sock_info->genSock) >= tp0_cfg.max_spdu_outst)
    {
    SOCK_LOG_ERR2 ("N-DATA.req:  sock_info = 0x%X, error sending (queue limit = %u reached)",
                   sock_info, tp0_cfg.max_spdu_outst);
    return (SD_FAILURE);
    }

  /* _uSockDataAlloc allocs "sockData" (plus space for data) and initializes it.*/
  _uSockDataAlloc (sock_info->genSock, tpkt_len, &sockData);
  memcpy (sockData->data, tpkt_ptr, tpkt_len);	/* copy the data	*/
  sockData->eot = eot;

  rc = sockTxMsg (sock_info->genSock, sockData);

  if (rc == SD_SUCCESS)
    {
    SOCK_LOG_TX3 ("N-DATA.req:  sock_info = 0x%X, user_conn = %d tpkt_len = %d",
       sock_info, sock_info->user_conn_id, tpkt_len);
    SOCK_LOG_TXH (tpkt_len, tpkt_ptr);
    }
  else
    SOCK_LOG_ERR1 ("N-DATA.req:  sock_info = 0x%X, error sending", sock_info);

  return (rc);
  }

/************************************************************************/
/*			np_get_tx_queue_cnt				*/
/* Returns number of queued SPDUs. 					*/
/************************************************************************/
ST_UINT np_get_tx_queue_cnt (SOCK_INFO *sock_info)
  {
  assert (sock_info->genSock != NULL);
  return (sockTxQueueGroupCntGet (sock_info->genSock));
  }

/************************************************************************/
/*                      _uSockWritable                                  */
/* This function is called by gensock2 when the socket becomes writable.*/
/************************************************************************/
static ST_VOID _uSockWritable (GEN_SOCK *pSock)
  {
ST_RET     rc;

  SOCK_LOG_FLOW1 ("%s: in _uSockWritable()", pSock->sockIdStr);

  /* the socket is writable, so send something from the transmit queue.	*/
  rc = sockTxQueueProc (pSock);
  if (rc != SD_SUCCESS)
    {
    SOCK_LOG_ERR1 ("%s: sockTxQueueProc failed, closing socket", pSock->sockIdStr);
    /* DEBUG: this change of state will cause problem,	*/
    /*        app will not be notified about disconnect */
    /*    sock_info->state = SOCK_STATE_DISCONNECTING; 	*/
    sockClose (pSock);
    }
  }

/************************************************************************/
/*                      _uSockRxInd                                     */
/************************************************************************/
static ST_VOID _uSockRxInd (GEN_SOCK *pSock, GEN_SOCK_DATA *sockData)
  {
ST_RET rtn;

  if (pSock && sockData)
    SOCK_LOG_FLOW3 ("%s: in _uSockRxInd() result=%s, bytes=%d", pSock->sockIdStr,
      (sockData->result == SD_SUCCESS) ? "SD_SUCCESS" : "SD_FAILURE", sockData->dataLen);
  else
    {
    SOCK_LOG_ERR2 ("%s: in _uSockRxInd() sockData=%08lx", pSock->sockIdStr, sockData);
    if (sockData)
      _uSockDataFree (pSock, sockData);
    return;
    }

  if (sockData->result != SD_SUCCESS)
    {
    /* socket is disconnecting, any received data buffers need to be free */
    _uSockDataFree (pSock, sockData);
    return;
    }

  /* received data on the socket, queue indication for user */
  rtn = _addSockInd (pSock, GS_EVENT_DATA_IND, sockData);
  if (rtn != SD_SUCCESS)
    _uSockDataFree (pSock, sockData);
  }

/************************************************************************/
/*                      	uSockHunt				*/
/* This function will get the length of received message on a socket.	*/
/* We expect the size field to be RFC1006_HEAD_LEN bytes.		*/
/************************************************************************/

static ST_VOID _uSockHunt (GEN_SOCK *pSock, ST_INT *huntStateIo,
                     ST_CHAR *buf, ST_INT bufCount, ST_INT *lenOut)
  {
ST_INT16 *pInt;

  /* Better get our 4 byte RFC-1006 header ... */
  if (bufCount != RFC1006_HEAD_LEN)
    {
    SOCK_LOG_ERR1 ("%s: Socket Hunt for start of message failed.\n"
                   " Error could be unrecoverable.", pSock->sockIdStr);
    *huntStateIo = GENSOCK_HUNT_DISCONNECT;
    return;
    }

  if (buf[0] != RFC1006_VERSION)
    {
    SOCK_LOG_NERR1 ("%s: Received message with invalid RFC1006 version (first byte). Header:",
                    pSock->sockIdStr);
    SOCK_LOG_NERRH (4, buf);
    *huntStateIo = GENSOCK_HUNT_DISCONNECT;
    return;
    }

  /* len is in 3rd/4th bytes, in network byte order, and includes len of header.
   * Convert to host byte order, & subtract header len.
   */
  pInt = (ST_INT16 *) (buf+2);
  *lenOut = ntohs (*pInt) - RFC1006_HEAD_LEN;	/* convert from network byte order	*/
  *huntStateIo = GENSOCK_HUNT_DONE;
  }

	/*----------------------------------------------*/
	/*		Alloc / Free			*/
	/*----------------------------------------------*/

/************************************************************************/
/*			sock_info_alloc2				*/
/* Allocate a SOCK_INFO struct and fill it in.				*/
/************************************************************************/
SOCK_INFO *sock_info_alloc2 (GEN_SOCK *genSock, ST_INT state, ST_LONG user_conn_id)
  {
SOCK_INFO *sock_info;

  /* Allocate SOCK_INFO struct.						*/
  sock_info = (SOCK_INFO *) M_CALLOC (MSMEM_SOCK_INFO, 1, sizeof (SOCK_INFO));
  /* Fill in SOCK_INFO struct.						*/
  /* NOTE: sock_info->hSock is NOT used. sock_info->genSock is used instead.*/
  sock_info->genSock = genSock;
  sock_info->state = state;
  sock_info->user_conn_id = user_conn_id;
  sock_info->encrypt_ctrl.encryptMode = S_SEC_ENCRYPT_NONE;
  sock_info->recvCnt = 0;
  return (sock_info);
  }

/************************************************************************/
/*			sock_info_free					*/
/* Free a SOCK_INFO struct.						*/
/************************************************************************/
ST_VOID sock_info_free (SOCK_INFO *sock_info)
  {
  /* NOTE: gensock2 handles closing of the socket.	*/
  M_FREE (MSMEM_SOCK_INFO, sock_info);
  }

/************************************************************************/
/*			_uSockDataAlloc					*/
/************************************************************************/
static ST_VOID _uSockDataAlloc (GEN_SOCK *pSock, ST_INT dataLen, 
			         GEN_SOCK_DATA **sockDataOut)
  {
GEN_SOCK_DATA *sockData;

  sockData = (GEN_SOCK_DATA *) chk_malloc (sizeof (GEN_SOCK_DATA) + dataLen);
  sockData->data = (ST_UCHAR *) (sockData + 1);
  sockData->dataLen = dataLen;
  /* We don't use sockData->usrBufBase, sockData->usrBufLen */

  *sockDataOut = sockData;
  }
/************************************************************************/
/*			_uSockDataFree					*/
/************************************************************************/
static ST_VOID _uSockDataFree (GEN_SOCK *pSock, GEN_SOCK_DATA *sockData)
  {
  /* Allocated in _uSockDataAlloc using "chk_malloc", so use "chk_free".*/
  chk_free (sockData);
  }

	/*----------------------------------------------*/
	/*			Misc			*/
	/*----------------------------------------------*/

/************************************************************************/
/*			_addSockInd					*/
/************************************************************************/
static ST_RET _addSockInd (GEN_SOCK *pSock, ST_INT eventType, GEN_SOCK_DATA *sockData)
  {
GEN_SOCK_EVENT *sdi;
#if defined(MMSEASE_MOSI)
static ST_UCHAR tcpEventWakeupData = 1;
ST_INT          numSent = 0;
#endif

  if (tp0Ctx.state == TP0_SOCK_CTX_STATE_TERMINATING)
    {
    SOCK_LOG_FLOW1 ("%s: in _addSockInd failed - context terminating", pSock->sockIdStr);
    return (SD_FAILURE);
    }
  else
    SOCK_LOG_FLOW1 ("%s: in _addSockInd", pSock->sockIdStr);

  sdi = (GEN_SOCK_EVENT *) chk_calloc (1, sizeof (GEN_SOCK_EVENT));
  sdi->eventType = eventType;
  sdi->pSock = pSock;

  sdi->sockData = sockData;
  sockEventPut (tp0Ctx.sockCtx, sdi);	/* let gensock save on list*/
  S_LOCK_UTIL_RESOURCES ();
  /* if application can't process incoming data msgs as fast as they are*/
  /* received by the socket then the best way to prevent uncontrolled	*/
  /* growth of the receiving queue is to apply back pressure to the	*/
  /* sending socket.							*/
  if (eventType == GS_EVENT_DATA_IND)
    {
SOCK_INFO *sock_info = (SOCK_INFO *) pSock->sockCfg.usr2;
    /* this is a bit tricky, if we accept connection from rfc1006listener	*/
    /* then the first packet will be queued before the sock_info is allocated	*/
    /* so we must check here if the ptr is NULL					*/
    if (sock_info)
      {
      ++sock_info->recvCnt;		
      if (sock_info->recvCnt >= SOCK_RX_QUE_HIGH_MARK && pSock->sockCfg.pauseRecv == SD_FALSE)
        {
        pSock->sockCfg.pauseRecv = SD_TRUE;
        SOCK_LOG_FLOWC2 ("%s: recvCnt=%u, setting pauseRecv=SD_TRUE",
                         pSock->sockIdStr, sock_info->recvCnt);
        }
      }
    }
  S_UNLOCK_UTIL_RESOURCES ();

  /* wake up main thread	*/
#if defined(_WIN32)
  gs_signal_event_sem (hTcpEvent);	/* wake up main thread	*/
  SOCK_LOG_FLOW2 ("%s: in _addSockInd() signaled hTcpEvent=%lu", pSock->sockIdStr, (ST_ULONG) hTcpEvent);
#endif

#if defined(MMSEASE_MOSI)
  if (tp0Ctx.hTcpEventSender != INVALID_SOCKET)
    {
    numSent = (ST_INT) send (tp0Ctx.hTcpEventSender, &tcpEventWakeupData, sizeof(tcpEventWakeupData), 0);
    if (numSent == sizeof (tcpEventWakeupData))
      {
      SOCK_LOG_FLOW3 ("%s: XSocket sent %d Wakeup data (value=%u)",
                     tp0Ctx.sockCtx->ctxName, numSent, (ST_UINT) tcpEventWakeupData);
      }
    else
      {
      /* when a lot of indications are received in short time, EWOULDBLOCK and EAGAIN	*/
      /* errors could happen often with this 1-byte packets				*/
      SOCK_LOG_FLOW3 ("%s: XSocket Wakeup data send() error (numSent=%d), errno=%d",
                      tp0Ctx.sockCtx->ctxName, numSent, SOCKET_ERRORNO);
      /* ignore any errors */
      }
    ++tcpEventWakeupData;
    }
#endif /* defined(MMSEASE_MOSI) */

  return (SD_SUCCESS);
  }

/************************************************************************/
/*			_handleRekeying					*/
/* Call function driving security rekeying on every secured socket.	*/
/************************************************************************/
static ST_RET _handleRekeying (ST_VOID)
{
ST_RET         rc;
S_SEC_CONFIG  *pSecCfg;

  rc = secManAccessCfg (&pSecCfg);
  if (rc != SD_SUCCESS)
    return (rc);
  
  /* we have to drive the checking for periodic rekeying, to do that call	*/
  /* the TX func with no data to send						*/
  if (pSecCfg->secureModeEnabled)
    {
    SOCK_INFO     *sock_info;

    S_LOCK_UTIL_RESOURCES ();
    sock_info = tp0Ctx.secureSockList;
    while (sock_info)
      {
      if (sGetMsTime () >= sock_info->rekeyTime &&
          sock_info->genSock != NULL && sock_info->genSock->sockState == GS_STATE_CONNECTED)
        {
        GEN_SOCK_DATA  sockData={{0}};	/* first in struct is struct, so need double braces	*/
        ST_INT         numSent;
        sockTx (sock_info->genSock, &sockData, &numSent);
        /* set the time for next check	*/
        sock_info->rekeyTime = sGetMsTime() + SOCK_REKEY_TIME;
	}
      sock_info = list_get_next (tp0Ctx.secureSockList, sock_info);
      }
    S_UNLOCK_UTIL_RESOURCES ();
    }

  secManReleaseCfg();
  return (rc);
}

