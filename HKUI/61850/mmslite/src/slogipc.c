/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*		2004 - 2007, All Rights Reserved 			*/
/*									*/
/* MODULE NAME : slogipc.c						*/
/* PRODUCT(S)  : SLOG							*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/*		This module implements code to slog through sockets.	*/
/*		The gensock2 is used to access socket functionality.	*/
/*		The socket logging subsystem accepts connections from	*/
/*		number of clients and sends any slog messages to them	*/
/*		once available.						*/
/*		No connections are made from this module.		*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 03/12/07  JRB    29     Add cast.					*/
/* 03/01/07  MDE    28     Added SLOGIPC options, missed message 	*/
/* 02/21/07  RKR    27     Added a cast to slog_ipc_std_cmd_fun         */
/* 01/22/07  MDE    26     Cleaned up command handling			*/
/* 01/15/07  JRB    25     Del poll_mode arg to sockStart.		*/
/* 01/15/07  EJV    24     Chg S_LOCK_RESOURCES to S_LOCK_UTIL_RESOURCES*/
/* 01/08/07  EJV    23     Chg SV* globals to local var in functions	*/
/*			     (see new struct SLOGIPC_SV_SLOG).		*/
/*			   slogIpcSaveLoggingParams: chg args.		*/
/*			   slogIpcStop: added lc param.			*/
/* 10/05/05  EJV    22     Implemented GEN_SOCK_CTXT.			*/
/*			   slogIpc: ! application MUST call slogIpcInit	*/
/*			   slogIpc: do not log if not in ACTIVE state.	*/
/*			   slogIpcInit: use memset (not secCfg={0});	*/
/*			     cleanup if sockInitListen fails.		*/
/*			   slogIpcStop: return rtn from sockEnd.	*/
/*			   slogIpc_uSockConnectInd: tx CRNLs with appId.*/
/*			   Added slogIpcEvent for non-threaded mode.	*/
/*			   Chg connection state names to SLOGIPC_CON*.	*/
/* 08/10/05  MDE    21     Retry listen periodically			*/
/* 08/02/05  MDE    20     slogIpcInit: set reuseAddr to SD_FALSE	*/
/* 07/06/05  EJV    19     slogIpcInit: set reuseAddr to SD_TRUE.	*/
/* 04/06/05  EJV    18     Elim Linux warnings (added typecasting)	*/
/* 02/23/05  JRB    17     slogIpc: add SD_CONST to some args.		*/
/*           EJV           slogIpc: init vars on stack to avoid warnings*/
/*           EJV	   Del unused vars.				*/
/* 02/02/05  MDE    16     Smart mode work				*/
/* 01/24/05  EJV    15     slogIpcInit: limited SLOGALWAYS		*/
/* 12/15/04  ASK    14     Fix buffering when sending Ipc Cmd Responses	*/
/* 12/08/04  ASK    13     Added 'smart mode' for Ipc Cmd clients.	*/
/*			   Use strncat_safe when filling IPC Buffer.	*/
/* 11/22/04  EJV    12     Move buf size computation to slogIpc, do not	*/
/*			     use sl_max_msg_size, may change dynamically*/
/* 09/22/04  EJV    11     Eliminated more sun warnings.		*/
/* 09/13/04  EJV    10     Eliminated sun warnings.			*/
/* 07/22/04  EJV    09     slogIpc_uSockWritable:don't slog in this fun	*/
/* 07/09/04  EJV    08     slogIpcSendQueued: init ret.			*/
/* 07/02/04  DSF    07     Always link in ws2_32.lib			*/
/* 06/24/04  EJV    06     slogIpcInit: set portUsed.			*/
/* 06/23/04  EJV    05     Init range of ports for multiple instances.	*/
/*			   Send Application ID after conn if configured.*/
/* 05/27/04 ASK/EJV 04     Fix S_LOCK_RESOURCES deadlock in slogIpcStop.*/
/*			   Rework slogIpc to prevent gensock logs.	*/
/* 05/20/04  EJV    03     Limited log message queue.			*/
/* 05/18/04  MDE    02     Removed LOG_IPC_SUPPORT #ifdef's		*/
/* 05/11/04  EJV    01     Initial Release				*/
/************************************************************************/

#include "glbtypes.h"
#include "sysincs.h"
#include "stime.h"
#include "slog.h"
#include "gensock2.h"
#include "str_util.h"

#if defined (_WIN32)
#pragma comment(linker, "/defaultlib:ws2_32.lib")
#endif

/* For debug version, use a static pointer to avoid duplication of 	*/
/* __FILE__ strings.							*/
#ifdef DEBUG_SISCO
SD_CONST static ST_CHAR *SD_CONST thisFileName = __FILE__;
#endif

/************************************************************************/

#define _SLOGIPC_MAX_OPTIONS_LEN	1000

/************************************************************************/

/* connection states */
#define SLOGIPC_CON_IDLE	0
#define SLOGIPC_CONNECTED	1
#define SLOGIPC_CON_CLOSING	2

/* Remote connection info */
typedef struct slogipc_con_ctrl_tag
  {
  DBL_LNK	 link;			/* link list 				*/

  GEN_SOCK      *conSock;		/* pointer to socket info		*/
  ST_UINT        conState;		/* connection state			*/
  ST_BOOLEAN	 txEnable;		/* Used in smart mode			*/
  GEN_SOCK_DATA *sendQue;		/* Pending send queue to the Remote	*/
  ST_UINT        sendQueCnt;		/* number of messages to send in queue	*/
  GEN_SOCK_DATA *rcvBuf;		/* alloc buf to drain any rcvd bytes	*/
  } SLOGIPC_CON_CTRL;


/* SLOGIPC context states */
#define	SLOGIPC_CTX_IDLE		0
#define	SLOGIPC_CTX_INITIALIZING	1
#define	SLOGIPC_CTX_ACTIVE		2
#define	SLOGIPC_CTX_TERMINATING		3

/* This structure holds core parameters */
typedef struct slogipc_ctx_tag
  {
  ST_UINT           state;		/* SLOGIPC_CTX_*					*/
  ST_BOOLEAN	    smartMode;		/* SD_TRUE if smart mode enabled, SD_FALSE otherwise	*/
  SLOGIPC_CON_CTRL *conCtrlList;	/* list of connect CTRLs				*/
  GEN_SOCK         *listenSock;		/* listen socket for conns from remote slog Clients	*/
  LOG_CTRL         *lc;			/* save to access appId when connected			*/
  GEN_SOCK_CTXT    *sockCtx;		/* this is gensock2 context for slogipc.c		*/
  } SLOGIPC_CTX;

/* static vars */
static SLOGIPC_CTX	slogIpcCtx;


/* struct used to save slog log masks and dynamic slogging function pointers	*/
typedef struct slogipc_sv_slog_tag
  {
  ST_UINT32 logCtrl;

  ST_VOID (*slog_dyn_log_fun)  (LOG_CTRL *lc, 
			        SD_CONST ST_INT logType, 
                                SD_CONST ST_CHAR *SD_CONST sourceFile, 
			        SD_CONST ST_INT lineNum,
                                SD_CONST ST_INT bufLen, 
			        SD_CONST ST_CHAR *buf);

  ST_VOID (*_slog_dyn_log_fun) (LOG_CTRL *lc, 
			        SD_CONST ST_CHAR *timeStr, 
			        SD_CONST ST_INT logType, 
			        SD_CONST ST_CHAR *SD_CONST logTypeStr,
                                SD_CONST ST_CHAR *SD_CONST sourceFile, 
			        SD_CONST ST_INT lineNum,
                                SD_CONST ST_INT bufLen, 
			        SD_CONST ST_CHAR *buf);

  ST_VOID (*slog_remote_fun)   (ST_UINT32 slog_remote_flags,
			        LOG_CTRL *lc, 
			        SD_CONST ST_INT logType, 
                                SD_CONST ST_CHAR *SD_CONST sourceFile, 
			        SD_CONST ST_INT lineNum,
                                SD_CONST ST_INT bufLen, 
			        SD_CONST ST_CHAR *buf);

  ST_VOID (*_slog_remote_fun)  (ST_UINT32 slog_remote_flags,
			        LOG_CTRL *lc, 
			        SD_CONST ST_INT logType, 
                                SD_CONST ST_CHAR *SD_CONST logTypeStr, 
                                SD_CONST ST_CHAR *SD_CONST sourceFile, 
			        SD_CONST ST_INT lineNum,
                                SD_CONST ST_INT bufLen, 
			        SD_CONST ST_CHAR *buf);
  } SLOGIPC_SV_SLOG;


typedef struct
  {
  ST_BOOLEAN logMsg;
  } SLOGIPC_MSG_INFO;

/************************************************************************/
#if defined(GENSOCK_THREAD_SUPPORT)
#define	SLOGIPC_WAIT(ctx, ms)	sMsSleep (ms);
#else
#define	SLOGIPC_WAIT(ctx, ms)	sockServiceAll (ctx, ms);
#endif


/************************************************************************/

static ST_VOID slogIpcAddSendQue (LOG_CTRL *lc, SLOGIPC_CTX *ctx, 
				  SLOGIPC_CON_CTRL *conCtrl,
				  GEN_SOCK_DATA    *sockData);

/************************************************************************/

	/*----------------------------------------------*/	
	/*	gensock2 callback functions		*/
	/*----------------------------------------------*/

/************************************************************************/
/*			slogIpc_DataBufAlloc				*/
/************************************************************************/

/* Used for both transmit and receive buffers */

static ST_VOID slogIpc_DataBufAlloc (GEN_SOCK *pSock, ST_INT dataLen,
                                      GEN_SOCK_DATA **sockDataOut)
  {
GEN_SOCK_DATA    *sockData;

  sockData = (GEN_SOCK_DATA *) chk_malloc (sizeof (GEN_SOCK_DATA) + dataLen + sizeof (SLOGIPC_MSG_INFO));
  sockData->data = (ST_UCHAR *)(sockData + 1);
  sockData->dataLen = 0;			/* curr length to send			*/
  sockData->usr1 = (sockData->data + dataLen);

/* These parameters are used for Transmit only */
  sockData->usrBufBase = sockData->data;	/* ptr to buffer base		*/
  sockData->usrBufLen = dataLen;		/* len of alloc buf, could be more than actual len */

  *sockDataOut = sockData;
  }

/************************************************************************/
/*			slogIpc_uDataBufFree				*/
/************************************************************************/

static ST_VOID slogIpc_uDataBufFree (GEN_SOCK *pSock, GEN_SOCK_DATA *sockData)
  {
  chk_free (sockData);
  }

/************************************************************************/
/*			slogIpc_uSockHunt				*/
/*----------------------------------------------------------------------*/
/* This function will get the length of received message on a socket.	*/
/************************************************************************/

static ST_VOID slogIpc_uSockHunt (GEN_SOCK *pSock, ST_INT *huntStateIo,
                                  ST_CHAR *buf, ST_INT bufCount, ST_INT *lenOut)
  {
SLOGIPC_CTX *ctx  = (SLOGIPC_CTX *) pSock->sockCfg.usr1;
ST_UINT32 magic;
ST_UINT32 *pHdr;
  
  /* Make sure we have our header bytes */
  if(ctx->smartMode == SD_TRUE)
    {
    if (bufCount != SLOGIPC_SMRT_HDR_SIZE)
      {
      *huntStateIo = GENSOCK_HUNT_RESET;
      return;
      }

    pHdr = (ST_UINT32 *) buf;
    magic = ntohl (*pHdr);
    if (magic != SLOGIPC_MAGIC_NUMBER)
      {
      *huntStateIo = GENSOCK_HUNT_RESET;
      return;
      }
    ++pHdr;
    ++pHdr;
    *lenOut = ntohl (*pHdr);
    *huntStateIo = GENSOCK_HUNT_DONE;
    }
  else	/* Just discard data if not in smart mode */
    *huntStateIo = GENSOCK_HUNT_RESET;
  }

/************************************************************************/
/*			slogIpc_uSockConnectInd				*/
/*----------------------------------------------------------------------*/
/* This is gensock2 callback function when a socket connection has been	*/
/* accepted on listen socket.						*/
/************************************************************************/
static ST_RET slogIpc_uSockConnectInd (struct tag_GEN_SOCK *pSock)
  {
SLOGIPC_CTX      *ctx  = (SLOGIPC_CTX *) pSock->sockCfg.usr1;
SLOGIPC_CON_CTRL *conCtrl = NULL;
ST_CHAR          *appId = NULL;
ST_UINT32	 *pHdr;
ST_CHAR          *p;
GEN_SOCK_DATA    *sockData;
ST_INT            appIdLen;
ST_INT            optionsLen;
ST_UINT32         options;

  S_LOCK_UTIL_RESOURCES ();

  /* do not accept connections if state other than active	*/
  if (ctx->state != SLOGIPC_CTX_ACTIVE)
    {
    S_UNLOCK_UTIL_RESOURCES ();
    return (SD_FAILURE);
    }

  conCtrl = (SLOGIPC_CON_CTRL *) chk_calloc (1, sizeof(SLOGIPC_CON_CTRL));
  conCtrl->conSock  = pSock;
  conCtrl->conState = SLOGIPC_CONNECTED;

/* Don't need because of calloc 
  if (ctx->smartMode == SD_TRUE)
    conCtrl->txEnable = SD_FALSE;
*/

  /* save the our ptr (used in other callback functions) */
  pSock->sockCfg.usr2 = (ST_VOID *) conCtrl;

  /* add to list of connections */
  list_add_last (&ctx->conCtrlList, conCtrl);

  /* queue the application identification to send to the connecting client	*/
  appId = ctx->lc->ipc.appId;
  if (appId)
    {
    appIdLen = strlen (appId);
    if (ctx->smartMode != SD_TRUE)
      {	
      #define APPID_PAD_STR		"\r\n\r\n"
      #define APPID_PAD_STR_LEN		(2 * strlen (APPID_PAD_STR))
      slogIpc_DataBufAlloc (pSock, appIdLen + APPID_PAD_STR_LEN + 1, &sockData);
      /* transmit CR NL to separate AppIdfrom other messages on the screen */
      sprintf ((ST_CHAR *)sockData->data, "%s%s%s", APPID_PAD_STR, (ST_CHAR *)appId, APPID_PAD_STR);
      sockData->dataLen = appIdLen + APPID_PAD_STR_LEN;
      slogIpcAddSendQue (NULL, ctx, conCtrl, sockData);
      }
    else /* Smart mode */
      { 
      slogIpc_DataBufAlloc (pSock, 
                             SLOGIPC_SMRT_HDR_SIZE + (appIdLen + 1), 
                             &sockData);
  
      sockData->dataLen = SLOGIPC_SMRT_HDR_SIZE + appIdLen;
  
      /* Setup our 12 byte header */
      pHdr = (ST_UINT32 *) sockData->data;
      *(pHdr++) = htonl (SLOGIPC_MAGIC_NUMBER);
      *(pHdr++) = htonl (SLOGIPC_MSG_TYPE_APPID);
      *pHdr     = htonl ((ST_UINT32) appIdLen);
  
      p = (ST_CHAR *)sockData->data + SLOGIPC_SMRT_HDR_SIZE;
      strcpy (p, appId);
      slogIpcAddSendQue (NULL, ctx, conCtrl, sockData);

      /* See if we need to send options */
      options = ctx->lc->ipc.options;
      if (options != 0)
        {
        slogIpc_DataBufAlloc (pSock, 
                              SLOGIPC_SMRT_HDR_SIZE + _SLOGIPC_MAX_OPTIONS_LEN + 1, 
                              &sockData);
    
      /* Setup our 12 byte header */
        pHdr = (ST_UINT32 *) sockData->data;
        *(pHdr++) = htonl (SLOGIPC_MAGIC_NUMBER);
        *(pHdr++) = htonl (SLOGIPC_MSG_TYPE_OPTIONS);

      /* Go ahead and create the options string */
        p = (ST_CHAR *) sockData->data + SLOGIPC_SMRT_HDR_SIZE;
        p[0] = 0;
        if (options & LOG_IPC_EDIT_LOGCFG)
          strncat_safe (p, "|EDIT_LOGCFG|", _SLOGIPC_MAX_OPTIONS_LEN);
  
      /* OK, finish the len and send it */
        optionsLen = strlen (p);
        *pHdr     = htonl ((ST_UINT32) optionsLen);
        sockData->dataLen = SLOGIPC_SMRT_HDR_SIZE + optionsLen;
  
        slogIpcAddSendQue (NULL, ctx, conCtrl, sockData);
        }
      } /* Smart mode */

    /* can't send from here because socket is not ready for send until we ret	*/
    /* from this function, but to drive the sending we can set the writable	*/
    /* flag and gensock2 service thread should soon call slogIpc_uSockWritable*/
    pSock->sockCfg.chkWritable = SD_TRUE;
    }

  S_UNLOCK_UTIL_RESOURCES ();

  /* connection accepted */
  return (SD_SUCCESS);
  }

/************************************************************************/
/*			slogIpc_uSockDisconnectInd			*/
/*----------------------------------------------------------------------*/
/* This is gensock2 callback function when socket gets disconnected or	*/
/* we call sockClose.							*/
/************************************************************************/
static ST_VOID slogIpc_uSockDisconnectInd (struct tag_GEN_SOCK *pSock)
{
ST_RET            rtn;
SLOGIPC_CTX      *ctx = (SLOGIPC_CTX *) pSock->sockCfg.usr1;
SLOGIPC_CON_CTRL *conCtrl = (SLOGIPC_CON_CTRL *) pSock->sockCfg.usr2;
GEN_SOCK_DATA    *sockData;

  if (pSock->role == GS_ROLE_LISTENING)
    {
    ctx->listenSock = NULL;
    sockFree (pSock);
    return;
    }

  S_LOCK_UTIL_RESOURCES ();

  sockFree (pSock);

  /* free buffers in send que */
  while (conCtrl->sendQue != NULL)
    {
    sockData = conCtrl->sendQue;
    list_unlink (&conCtrl->sendQue, sockData);
    slogIpc_uDataBufFree (NULL, sockData);
    }

  /* remove the connection control from list */
  rtn = list_unlink (&ctx->conCtrlList, conCtrl);
  if (rtn == SD_SUCCESS)
    chk_free (conCtrl);

  S_UNLOCK_UTIL_RESOURCES ();
}

/************************************************************************/
/*			slogIpc_uSockRxInd				*/
/*----------------------------------------------------------------------*/
/* This is gensock2 callback function when socket receives a msg.	*/
/* NOTE that we do not expect to receive anything on that socket, any	*/
/* bytes received will be ignored if not in smartMode.			*/
/************************************************************************/

static ST_VOID slogIpc_uSockRxInd (struct tag_GEN_SOCK *pSock, GEN_SOCK_DATA *sockData)
{
SLOGIPC_CON_CTRL *conCtrl;
SLOGIPC_CTX 	 *ctx;
ST_UINT32 	 *pUl;
ST_UINT32  	  magicNum;
ST_UINT32  	  msgType;
ST_UINT32  	  msgDataLen;
ST_CHAR 	 *msgData;

  conCtrl =  (SLOGIPC_CON_CTRL *) pSock->sockCfg.usr2;
  ctx = (SLOGIPC_CTX *) pSock->sockCfg.usr1;
  if (ctx->smartMode == SD_TRUE)
    {
    pUl = (ST_UINT32 *) (sockData->data);	/* point to magic number */
    magicNum = ntohl(*pUl);
    if (magicNum != SLOGIPC_MAGIC_NUMBER)
      {
      chk_free (sockData);
      return;
      }  

    ++pUl;					/* point to message type */
    msgType = ntohl(*pUl);

    ++pUl;					/* point to message type */
    msgDataLen = ntohl(*pUl);

    ++pUl;					/* point to message data start */
    msgData = (ST_CHAR *) (pUl);

    switch (msgType)
      {
      case SLOGIPC_MSG_TYPE_START:
        conCtrl->txEnable = SD_TRUE;
        chk_free (sockData);
      break;

      case SLOGIPC_MSG_TYPE_STOP:
        conCtrl->txEnable = SD_FALSE;
        chk_free (sockData);
      break;

    /* All others can get passed to the application */
      default:
        if (ctx->lc->ipc.slog_ipc_cmd_fun != NULL)
          {
          (*ctx->lc->ipc.slog_ipc_cmd_fun) (pSock, sockData, msgType, msgDataLen, msgData);
          }
	else
          slogIpcSendData (pSock, SLOGIPC_MSG_TYPE_RESP_FAILURE, 0, NULL);
      break;
      }
    }
  }

/************************************************************************/
/*			slogIpcSaveLoggingParams   			*/
/************************************************************************/

static ST_VOID slogIpcSaveLoggingParams(LOG_CTRL *lc, SLOGIPC_SV_SLOG *svSlog)
  {
  /* prevent any logging from code handling IPC slogging */
  /* NOTE: we may still have problems if program changes some of the	*/
  /* slog params that we saved and reset them while we exec this fun!	*/
  svSlog->logCtrl = lc->logCtrl;

  svSlog->slog_dyn_log_fun  = slog_dyn_log_fun;
  svSlog->_slog_dyn_log_fun = _slog_dyn_log_fun;
  svSlog->slog_remote_fun   =  slog_remote_fun;
  svSlog->_slog_remote_fun  = _slog_remote_fun;
  slog_dyn_log_fun  = NULL;
  _slog_dyn_log_fun = NULL;
  slog_remote_fun   = NULL;
  _slog_remote_fun  = NULL;

  lc->logCtrl &= ~LOG_FILE_EN;
  lc->logCtrl &= ~LOG_MEM_EN;
  lc->logCtrl &= ~LOG_IPC_EN;
  }

/************************************************************************/
/*			slogIpcRestoreLoggingParams   			*/
/************************************************************************/

static ST_VOID slogIpcRestoreLoggingParams(LOG_CTRL *lc, SLOGIPC_SV_SLOG *svSlog)
  {
  lc->logCtrl = svSlog->logCtrl;	/* restore the slogging control		*/
  slog_dyn_log_fun  = svSlog->slog_dyn_log_fun;
  _slog_dyn_log_fun = svSlog->_slog_dyn_log_fun;
  slog_remote_fun   = svSlog->slog_remote_fun;
  _slog_remote_fun  = svSlog->_slog_remote_fun;
  }

/************************************************************************/
/*			slogIpcSendQueued				*/
/*----------------------------------------------------------------------*/
/* Send all queued log messages on a socket.				*/
/************************************************************************/

static ST_RET slogIpcSendQueued (struct tag_GEN_SOCK *pSock)
{
ST_RET            rtn = SD_SUCCESS;
SLOGIPC_CON_CTRL *conCtrl = (SLOGIPC_CON_CTRL *) pSock->sockCfg.usr2;
GEN_SOCK_DATA    *sockData;
ST_INT            numSent;

  S_LOCK_UTIL_RESOURCES ();

  /* send as many queued messages as possible */
  while (conCtrl->sendQue != NULL)
    {
    sockData = conCtrl->sendQue;
    rtn = sockTx (pSock, sockData, &numSent);

    if (rtn == SD_SUCCESS)
      {
      if (numSent == sockData->dataLen)
        {
        /* the whole message has been sent, unlink the buffer */
        ++pSock->sockStats.numSend;		/* num of msgs sent	*/

        if ( conCtrl->sendQueCnt > 0)
	  --conCtrl->sendQueCnt;
        list_unlink (&conCtrl->sendQue, sockData);
        slogIpc_uDataBufFree (NULL, sockData);	/* pSock=NULL will free the buff */
        }
      else
        {
        /* data sent partially, adjust for next send attempt */
        sockData->data += numSent;
        sockData->dataLen -= numSent;
        break;	/* Stop trying to send */
        }
      }
    else
      {
      /* problem sending, free buffers in send que */
      while (conCtrl->sendQue != NULL)
        {
        sockData = conCtrl->sendQue;
        list_unlink (&conCtrl->sendQue, sockData);
        slogIpc_uDataBufFree (NULL, sockData);
        }
      }
    }

  S_UNLOCK_UTIL_RESOURCES ();

  return (rtn);
}

/************************************************************************/
/*			slogIpc_uSockWritable				*/
/*----------------------------------------------------------------------*/
/* This function is called by gensock2 when the socket becomes writable.*/
/************************************************************************/
static ST_VOID slogIpc_uSockWritable (struct tag_GEN_SOCK *pSock)
{
SLOGIPC_CTX      *ctx = (SLOGIPC_CTX *) pSock->sockCfg.usr1;
SLOGIPC_CON_CTRL *conCtrl = (SLOGIPC_CON_CTRL *) pSock->sockCfg.usr2;
LOG_CTRL          *lc = ctx->lc;
SLOGIPC_SV_SLOG   svSlog;

  S_LOCK_UTIL_RESOURCES ();
  if (conCtrl->conState != SLOGIPC_CONNECTED || ctx->state != SLOGIPC_CTX_ACTIVE)
    {
    S_UNLOCK_UTIL_RESOURCES ();
    return;
    }

  slogIpcSaveLoggingParams(lc, &svSlog);
  slogIpcSendQueued (pSock);
  slogIpcRestoreLoggingParams(lc, &svSlog);

  S_UNLOCK_UTIL_RESOURCES ();

}

/************************************************************************/
/*                              slogIpcInit				*/
/*----------------------------------------------------------------------*/
/* Initialize the socket logging subsystem.				*/
/* Parameters:								*/
/*	lc		Pointer to LOG_CTRL that is used for logging.	*/
/* Return values:							*/
/*	SD_SUCCESS	if functions successful				*/
/*	SD_FAILURE	or other error otherwise.			*/
/************************************************************************/

ST_RET slogIpcInit (LOG_CTRL *lc)
{
ST_RET          rtn = SD_SUCCESS;
SLOGIPC_CTX    *ctx = &slogIpcCtx;
GEN_SOCK_CONFIG sockCfg;
ST_UINT16	portNum;

  S_LOCK_UTIL_RESOURCES ();

  if (ctx->state != SLOGIPC_CTX_IDLE)
    {
    S_UNLOCK_UTIL_RESOURCES ();
    return (SD_FAILURE);
    }

  /* Remove when SLOG IPC Calling is implemented */
  if((lc->logCtrl & LOG_IPC_CALL_EN) &&
    !(lc->logCtrl & LOG_IPC_LISTEN_EN))
    {
    SLOGALWAYS0("SLOG IPC Calling mode not implemented in slogipc.c at this time");
    }

  /* Can't do IPC logging if we can't listen */
  if(!(lc->logCtrl & LOG_IPC_LISTEN_EN))
    {
    S_UNLOCK_UTIL_RESOURCES ();
    return (SD_FAILURE);
    }
  
  ctx->state = SLOGIPC_CTX_INITIALIZING;

  /* are we running in smart mode? */
  if(lc->logCtrl & LOG_IPC_SMART)
    ctx->smartMode = SD_TRUE;
  else
    ctx->smartMode = SD_FALSE;

   /* make sure port and maxConns are set to some good values */
  if (!lc->ipc.port)
    lc->ipc.port = IPC_LOG_BASE_PORT;
  if (!lc->ipc.portCnt)
    lc->ipc.portCnt = 1;
  if (!lc->ipc.maxConns)
    lc->ipc.maxConns = IPC_LOG_MAX_CONNECTIONS;
  if (!lc->ipc.maxQueCnt)
    lc->ipc.maxQueCnt = IPC_LOG_MAX_QUEUE_CNT;
  
  /* initialize gensock2 before calling any of the socket functions	*/
  rtn = sockStart (SLOGIPC_NAME, &slogIpcCtx.sockCtx);
  if (rtn != SD_SUCCESS)
    {
    ctx->state = SLOGIPC_CTX_IDLE;
    S_UNLOCK_UTIL_RESOURCES ();
    return (rtn);
    }

  memset (&sockCfg, 0, sizeof (GEN_SOCK_CONFIG));
  /* set listen socket parameters */
  if(ctx->smartMode == SD_TRUE)
    sockCfg.hdrSize     = SLOGIPC_SMRT_HDR_SIZE; /* our header size in smart mode */
  else
    sockCfg.hdrSize	= 1;			 /* set to 1 to drain the socket rcv buf */
  /* set sockopt parameters */
  sockCfg.setSockOpts = SD_TRUE;
  sockCfg.noDelay     = SD_TRUE;
  sockCfg.keepAlive   = SD_TRUE;
  sockCfg.reuseAddr   = SD_FALSE;
  sockCfg.rcvBufSize  = 0;		/* use default socket buffer size	*/
  sockCfg.sndBufSize  = 0;		/* use default socket buffer size	*/
  sockCfg.listenBacklog = 0;		/* if 0,  SOMAXCONN used 		*/
  /* set user callback functions */
  sockCfg.uSockConnectInd   = &slogIpc_uSockConnectInd;
  sockCfg.uSockConnectConf  = &slogIpc_uSockConnectInd;
  sockCfg.uSockDisconnect = &slogIpc_uSockDisconnectInd;
  sockCfg.uSockRx         = &slogIpc_uSockRxInd;
  sockCfg.uSockWritable   = &slogIpc_uSockWritable;
  sockCfg.uSockHunt       = &slogIpc_uSockHunt;
  sockCfg.uSockRxBufAlloc = &slogIpc_DataBufAlloc;
  sockCfg.uSockTxBufFree  = &slogIpc_uDataBufFree;
  /*  sockCfg.recvEvent     = not used */
  sockCfg.usr1 = (ST_VOID *) ctx;

  /* init the listening socket */
  /* for multiple instances of an application try range of ports 	*/
  portNum = lc->ipc.port;
  while (portNum < lc->ipc.port + lc->ipc.portCnt)
    {
    rtn = sockInitListen (slogIpcCtx.sockCtx, &sockCfg, portNum, lc->ipc.maxConns, &ctx->listenSock);
    if (rtn == SD_SUCCESS)
      {
      lc->ipc.portUsed = portNum;
      ctx->state = SLOGIPC_CTX_ACTIVE;
      ctx->lc = lc;	/* save LOG_CTRL ptr for later params access	*/
      break;
      }
    else
      {
      ctx->listenSock = NULL;	       	/* need to be set if bind fails	*/
      if (rtn == SOCK_EADDRINUSE)
        ++portNum;			/* try next port		*/
      else
        break;				/* other error			*/
      }
    }
  
  S_UNLOCK_UTIL_RESOURCES ();

  /* sockInitListen failed, cleanup */
  if (rtn != SD_SUCCESS)
    {
    /* sockEnd should not be in a S_LOCK_RESORCES because gensock2	*/
    /* threads need to call callback functions that use locks		*/
    sockEnd (slogIpcCtx.sockCtx);
    S_LOCK_UTIL_RESOURCES ();
    slogIpcCtx.sockCtx = NULL;
    ctx->state = SLOGIPC_CTX_IDLE;
    S_UNLOCK_UTIL_RESOURCES ();
    }

  return (rtn);
}

/************************************************************************/
/*                              slogIpcStop				*/
/*----------------------------------------------------------------------*/
/* Call this function to close all sockets and release resources used 	*/
/* socket logging subsystem.						*/
/* Parameters:								*/
/*	none								*/
/* Return values:							*/
/*	SD_SUCCESS	if functions successful				*/
/*	SD_FAILURE	or other error otherwise.			*/
/************************************************************************/
ST_RET slogIpcStop (LOG_CTRL *lc)
{
ST_RET            rtn = SD_SUCCESS;
SLOGIPC_CTX      *ctx = &slogIpcCtx;
SLOGIPC_CON_CTRL *conCtrl;

  /* Note: the S_LOCK_UTIL_RESOURCES must lock only portions of the code*/
  /*       since we will wait on work performed by gensock2 threads.	*/

  S_LOCK_UTIL_RESOURCES ();
  if (ctx->state != SLOGIPC_CTX_ACTIVE || ctx->lc != lc)
    {
    S_UNLOCK_UTIL_RESOURCES ();
    return (SD_FAILURE);
    }
  ctx->state = SLOGIPC_CTX_TERMINATING;
  S_UNLOCK_UTIL_RESOURCES ();

  /* close listen socket */
  if (ctx->listenSock)
    {
    sockClose (ctx->listenSock);
    while (ctx->listenSock != NULL)
      SLOGIPC_WAIT(ctx->sockCtx, 20);		/* wait until listen socket closes	*/
    }

  /* disconnect all connected sockets */
  S_LOCK_UTIL_RESOURCES ();
  conCtrl = ctx->conCtrlList;
  while (conCtrl)
    {
    conCtrl->conState = SLOGIPC_CON_CLOSING;
    sockClose (conCtrl->conSock);
    conCtrl = (SLOGIPC_CON_CTRL *) list_get_next (ctx->conCtrlList, conCtrl);
    }
  S_UNLOCK_UTIL_RESOURCES ();
  
  /* wait until all socket connections terminate */
  while (ctx->conCtrlList)
    SLOGIPC_WAIT(ctx->sockCtx, 20);

  /* cleanup gensock2 resources, terminate threads,... */
  rtn = sockEnd (slogIpcCtx.sockCtx);

  S_LOCK_UTIL_RESOURCES ();
  if (rtn == SD_SUCCESS)
    slogIpcCtx.sockCtx = NULL;
  ctx->state = SLOGIPC_CTX_IDLE;
  S_UNLOCK_UTIL_RESOURCES ();

  return (rtn);
}

/************************************************************************/
/*                              slogIpcEvent				*/
/*----------------------------------------------------------------------*/
/* Call this function to process slogIpc events. This function needs	*/
/* to be called only if the gensock2 is compiled without		*/
/* GENSOCK_THREAD_SUPPORT defined.					*/
/* Parameters:								*/
/*	none								*/
/* Return values:							*/
/*	SD_SUCCESS	if functions successful				*/
/*	SD_FAILURE	or other error otherwise.			*/
/************************************************************************/
ST_RET slogIpcEvent (ST_VOID)
{
#if !defined(GENSOCK_THREAD_SUPPORT)
SLOGIPC_CTX      *ctx = &slogIpcCtx;

  if (ctx->state == SLOGIPC_CTX_ACTIVE)
    sockServiceAll (ctx->sockCtx, 0);	/* arg is timeout in milliseconds*/
#endif /* !defined(GENSOCK_THREAD_SUPPORT) */

  return (SD_SUCCESS);
}

/************************************************************************/
/*                              slogIpc					*/
/*----------------------------------------------------------------------*/
/* This function will send the log message to all connected clients.	*/
/* If this is first log message this function will initialize the	*/
/* socket slogging subsystem.						*/
/* Parameters:								*/
/*	see slog() parameters						*/
/* Return values:							*/
/*	none								*/
/************************************************************************/

ST_VOID slogIpc (LOG_CTRL *lc, ST_INT logType,
		 SD_CONST ST_CHAR *SD_CONST logTypeStr, 
		 SD_CONST ST_CHAR *SD_CONST sourceFile,
		 ST_INT lineNum, ST_INT bufLen, 
                 ST_CHAR *buf)
  {
SLOGIPC_CTX      *ctx = &slogIpcCtx;
SLOGIPC_CON_CTRL *conCtrl;
GEN_SOCK_DATA    *sockData;
ST_UINT		  slogIpcMaxBufLen = 0;	/* max len of log message	*/
ST_UINT32 	 *pHdr;
ST_CHAR          *p;
ST_CHAR          *logMsg = NULL;
ST_INT            logMsgLen = 0;
ST_BOOLEAN        firstConn;
SLOGIPC_SV_SLOG   svSlog;

  S_LOCK_UTIL_RESOURCES ();
  if (ctx->state != SLOGIPC_CTX_ACTIVE || ctx->lc != lc)
    {
    S_UNLOCK_UTIL_RESOURCES ();
    return;	/* Application needs to call slogIpcInit function	*/
    }

  /* prevent any logging from code handling IPC slogging */
  /* NOTE: we may still have problems if program changes some of the	*/
  /* slog params that we saved and reset them while we exec this fun!	*/
  slogIpcSaveLoggingParams(lc, &svSlog);

  /* first queue message to all clients */
  conCtrl = ctx->conCtrlList;
  firstConn = SD_TRUE;
  while (conCtrl)
    {
    if (conCtrl->conState == SLOGIPC_CONNECTED)
      {
      /* setup the smart mode header */
      if (ctx->smartMode == SD_TRUE)
        {
        if (conCtrl->txEnable == SD_TRUE)
	  {
          if (firstConn == SD_TRUE)
	    {
          /* compute the max log buffer size needed for this app logging to	*/
          /* avoid memory fragmentation						*/
            slogIpcMaxBufLen = SLOGIPC_SMRT_HDR_SIZE +	/* IPC CMD Headers	*/ 
        		       SLOG_MAX_HDR +		/* log header		*/
        		       2 +			/* CR NL		*/
        		       bufLen+1 + 		/* msg in buf, +1 for NULL */
        		       1;	  		/* CR			*/

            slogIpc_DataBufAlloc (conCtrl->conSock, slogIpcMaxBufLen, &sockData);
	  
            p = (ST_CHAR *) sockData->data + SLOGIPC_SMRT_HDR_SIZE;
            slogSetHdr (lc, logType, logTypeStr, sourceFile, lineNum,  p, "\r\n");

            /* Now put the message to buffer */
            strncat_safe (p, (ST_CHAR *) buf, slogIpcMaxBufLen - SLOGIPC_SMRT_HDR_SIZE-1);
	    logMsgLen = strlen (p);

            /* Save for next socket */
            logMsg = p;
            firstConn = SD_FALSE;
	    }
	  else /* Not first time, just send duplicate */
	    {
            slogIpc_DataBufAlloc (conCtrl->conSock, slogIpcMaxBufLen, &sockData);
            p = (ST_CHAR *) sockData->data + SLOGIPC_SMRT_HDR_SIZE;
	    *p = 0;
            strncat_safe (p, logMsg, slogIpcMaxBufLen - SLOGIPC_SMRT_HDR_SIZE-1);
	    }

          /* Setup our 12 byte header */
          pHdr = (ST_UINT32 *) sockData->data;
          *(pHdr++) = htonl (SLOGIPC_MAGIC_NUMBER);
          *(pHdr++) = htonl (SLOGIPC_MSG_TYPE_LOG);
          *(pHdr++) = htonl ((ST_UINT32) logMsgLen);

	  sockData->dataLen = SLOGIPC_SMRT_HDR_SIZE + logMsgLen;
          slogIpcAddSendQue (lc, ctx, conCtrl, sockData);
	  }
        }
      else /* not smart mode */
        {
        /* compute the max log buffer size needed for this app logging to	*/
        /* avoid memory fragmentation						*/
        slogIpcMaxBufLen = SLOG_MAX_HDR +		/* log header		*/
        		   2 +				/* CR NL		*/
        		   bufLen+1 +			/* msg in buf, +1 for NULL */
        		   1;				/* CR			*/

        slogIpc_DataBufAlloc (conCtrl->conSock, slogIpcMaxBufLen , &sockData);

        slogSetHdr (lc, logType, logTypeStr, sourceFile, lineNum, (ST_CHAR *)sockData->data, "\r\n");
        /* Now put the message to buffer	*/
        strncat_safe ((ST_CHAR *) sockData->data, (ST_CHAR *) buf, slogIpcMaxBufLen-1);
        sockData->dataLen = strlen ((ST_CHAR *)sockData->data);
        slogIpcAddSendQue (lc, ctx, conCtrl, sockData);
	}
      }
    conCtrl = (SLOGIPC_CON_CTRL *) list_get_next (ctx->conCtrlList, conCtrl);
    }

  /* now try to send all the messages */
  conCtrl = ctx->conCtrlList;
  while (conCtrl)
    {
    if (conCtrl->conState == SLOGIPC_CONNECTED)
      {
      if (ctx->smartMode == SD_FALSE || conCtrl->txEnable == SD_TRUE)
        slogIpcSendQueued (conCtrl->conSock);
      }
    conCtrl = (SLOGIPC_CON_CTRL *) list_get_next (ctx->conCtrlList, conCtrl);
    }

  slogIpcRestoreLoggingParams(lc, &svSlog);
  S_UNLOCK_UTIL_RESOURCES ();
  }


/************************************************************************/
/*                       slogIpcSendData	                        */
/************************************************************************/

ST_VOID slogIpcSendData (GEN_SOCK *pSock, ST_UINT32 msgType, ST_INT dataLen, ST_UCHAR *data)
  {
GEN_SOCK_DATA 	 *sockData;
SLOGIPC_CON_CTRL *conCtrl;
SLOGIPC_CTX      *ctx;
LOG_CTRL         *lc;
ST_UINT32 	 *pHdr;
SLOGIPC_SV_SLOG   svSlog;

  ctx     = (SLOGIPC_CTX *)      pSock->sockCfg.usr1;
  lc      = ctx->lc;
  conCtrl = (SLOGIPC_CON_CTRL *) pSock->sockCfg.usr2;

  S_LOCK_UTIL_RESOURCES();
  slogIpcSaveLoggingParams(lc, &svSlog);
  
  slogIpc_DataBufAlloc (pSock, (SLOGIPC_SMRT_HDR_SIZE + dataLen), &sockData);

  /* Setup our 12 byte header */
  pHdr = (ST_UINT32 *) sockData->data;
  *(pHdr++) = htonl (SLOGIPC_MAGIC_NUMBER);
  *(pHdr++) = htonl (msgType);
  *(pHdr++) = htonl ((ST_UINT32) dataLen);

  /* Add the data */
  memcpy ((ST_CHAR *) pHdr, data, dataLen);
  sockData->dataLen = SLOGIPC_SMRT_HDR_SIZE + dataLen;

  /* Add to the queue */
  slogIpcAddSendQue (NULL, ctx, conCtrl, sockData);

  /* Service the queue */
  slogIpcSendQueued (pSock);

  /* Restore log parameters */
  slogIpcRestoreLoggingParams(lc, &svSlog);
  S_UNLOCK_UTIL_RESOURCES();
  }


/************************************************************************/
/************************************************************************/
ST_VOID slogIpcSendRawData (LOG_CTRL *lc, ST_INT bufLen, ST_CHAR *buf)

  {
SLOGIPC_CTX      *ctx = &slogIpcCtx;
SLOGIPC_CON_CTRL *conCtrl;
GEN_SOCK_DATA    *sockData;
ST_BOOLEAN        firstConn;
SLOGIPC_SV_SLOG   svSlog;

  S_LOCK_UTIL_RESOURCES ();
  if (ctx->state != SLOGIPC_CTX_ACTIVE || ctx->lc != lc)
    {
    S_UNLOCK_UTIL_RESOURCES ();
    return;	/* Application needs to call slogIpcInit function	*/
    }

  /* prevent any logging from code handling IPC slogging */
  /* NOTE: we may still have problems if program changes some of the	*/
  /* slog params that we saved and reset them while we exec this fun!	*/
  slogIpcSaveLoggingParams(lc, &svSlog);

  /* first queue message to all clients */
  conCtrl = ctx->conCtrlList;
  firstConn = SD_TRUE;
  while (conCtrl)
    {
    if (conCtrl->conState == SLOGIPC_CONNECTED)
      {
      slogIpc_DataBufAlloc (conCtrl->conSock, bufLen , &sockData);

      /* Now put the message to buffer	*/
      memcpy (sockData->data, buf, bufLen);
      sockData->dataLen = bufLen;
      slogIpcAddSendQue (lc, ctx, conCtrl, sockData);
      }
    conCtrl = (SLOGIPC_CON_CTRL *) list_get_next (ctx->conCtrlList, conCtrl);
    }

  /* now try to send all the messages */
  conCtrl = ctx->conCtrlList;
  while (conCtrl)
    {
    if (conCtrl->conState == SLOGIPC_CONNECTED)
      {
      if (ctx->smartMode == SD_FALSE || conCtrl->txEnable == SD_TRUE)
        slogIpcSendQueued (conCtrl->conSock);
      }
    conCtrl = (SLOGIPC_CON_CTRL *) list_get_next (ctx->conCtrlList, conCtrl);
    }

  slogIpcRestoreLoggingParams(lc, &svSlog);
  S_UNLOCK_UTIL_RESOURCES ();
  }



/************************************************************************/
/*			slogIpcAddSendQue				*/
/************************************************************************/

static ST_VOID slogIpcAddSendQue (LOG_CTRL *lc, SLOGIPC_CTX *ctx, 
				  SLOGIPC_CON_CTRL *conCtrl,
				  GEN_SOCK_DATA    *sockData)
  {
GEN_SOCK_DATA *sd;
GEN_SOCK_DATA *lastCtrlMsg;
SLOGIPC_MSG_INFO *ipcMsgInfo;
ST_UINT32 msgType;
ST_UINT32 *pUl;
ST_UINT32 missedMsgCount;

  ipcMsgInfo = (SLOGIPC_MSG_INFO *) sockData->usr1;

  if (lc)	/* If this is a log message */
    {
    ipcMsgInfo->logMsg = SD_TRUE;

  /* See if there is room at in the queue */
    if (conCtrl->sendQueCnt < lc->ipc.maxQueCnt)
      {
      ++conCtrl->sendQueCnt;
      list_add_last (&conCtrl->sendQue, sockData);
      }
    else
      { 
    /* Overflow .... This one is lost */
      slogIpc_uDataBufFree (NULL, sockData);

    /* Take a look at the last one, see if it is a 'missed' message */
      sockData = (GEN_SOCK_DATA *) list_find_last ((DBL_LNK *) conCtrl->sendQue);


      pUl = (ST_UINT32 *) (sockData->data);	/* point to magic number */
      ++pUl;					/* point to message type */
      msgType = ntohl(*pUl);
      if (msgType == SLOGIPC_MSG_TYPE_LOG_MISSED)
        {
        ++pUl;		 /* point to message len 			*/
        ++pUl;		 /* point to message data start 		*/
        missedMsgCount = ntohl(*pUl);
        ++missedMsgCount;
        *pUl = htonl (missedMsgCount);
        }
      else	/* We need to queue up a 'LOG MISSED' message */
        {
        slogIpc_DataBufAlloc (conCtrl->conSock, (SLOGIPC_SMRT_HDR_SIZE + sizeof (ST_UINT32)), &sockData);
        sockData->dataLen = SLOGIPC_SMRT_HDR_SIZE + sizeof (ST_UINT32);

       /* Setup our 12 byte header */
        pUl = (ST_UINT32 *) sockData->data;
        *(pUl++) = htonl (SLOGIPC_MAGIC_NUMBER);
        *(pUl++) = htonl (SLOGIPC_MSG_TYPE_LOG_MISSED);
        *(pUl++) = htonl (sizeof (ST_UINT32));
        *(pUl++) = htonl (1);
        ++conCtrl->sendQueCnt;
        list_add_last (&conCtrl->sendQue, sockData);
	}
      }
    }
  else 	/* Not a log message, put after the last control message */
    {
    ipcMsgInfo->logMsg = SD_FALSE;
    ++conCtrl->sendQueCnt;

    lastCtrlMsg = NULL;
    sd = conCtrl->sendQue;
    while (sd != NULL)
      {
      ipcMsgInfo = (SLOGIPC_MSG_INFO *) sd->usr1;
      if (ipcMsgInfo->logMsg == SD_FALSE)
        lastCtrlMsg = sd;
      else
        break;

      sd = (GEN_SOCK_DATA *) list_get_next (conCtrl->sendQue, sd);
      }

    if (lastCtrlMsg == NULL)
      list_add_first (&conCtrl->sendQue, sockData);
    else
      list_add_node_after (lastCtrlMsg, sockData);
    
    sd = conCtrl->sendQue;
    }
  }

/************************************************************************/
/************************************************************************/
/* Standard IPC Command Processing Framework				*/
/************************************************************************/

SLOGIPC_CMD *slogIpcCmdList;
ST_INT 	    slogIpcMaxCmdPend = 1;

/************************************************************************/
/*			slog_ipc_std_cmd_fun				*/
/************************************************************************/

ST_VOID slog_ipc_std_cmd_fun (GEN_SOCK *pSock, GEN_SOCK_DATA *sockData,
			             ST_UINT32 msgType, ST_UINT32 msgDataLen, 
                                     ST_CHAR *msgData) 
  {
SLOGIPC_CMD *slogIpcCmd;

/* If we have room on the que, alloc a ctrl struct for this command */
  if (list_get_sizeof (slogIpcCmdList) < slogIpcMaxCmdPend)
    {
    slogIpcCmd = (SLOGIPC_CMD *)chk_calloc (1, sizeof (SLOGIPC_CMD) + msgDataLen);
    slogIpcCmd->pSock = pSock;
    slogIpcCmd->sockData = sockData;
    slogIpcCmd->msgType = msgType;
    slogIpcCmd->msgDataLen = msgDataLen;
    slogIpcCmd->msgData = (ST_CHAR *) (slogIpcCmd + 1);
    memcpy (slogIpcCmd->msgData, msgData, msgDataLen);
    S_LOCK_UTIL_RESOURCES ();
    list_add_last (&slogIpcCmdList, slogIpcCmd);
    S_UNLOCK_UTIL_RESOURCES ();
    }
  else	/* No room ... */
    slogIpcSendData (pSock, SLOGIPC_MSG_TYPE_RESP_FAILURE, 0, NULL);
  }


