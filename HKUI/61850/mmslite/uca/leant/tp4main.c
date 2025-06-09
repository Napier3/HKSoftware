#if defined (TP4_ENABLED)
/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*	(c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*	1996-2005 All Rights Reserved					*/
/*									*/
/* MODULE NAME : tp4main.c						*/
/* PRODUCT(S)  : Lean-T Stack						*/
/*									*/
/* MODULE DESCRIPTION :							*/
/*	Main processsing functions for TP4.				*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*	tp4_initialize ()						*/
/*	tp4_terminate ()						*/
/*	tp4_bind ()							*/
/*	tp4_unbind ()							*/
/*	tp4_timer_tick ()						*/
/*	tp4_buffers_avail ()						*/
/*	tp4_data ()							*/
/*	tp4_event ()							*/
/*	tp_process_dt ()						*/
/*	tp_process_ak ()						*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev     Comments					*/
/* --------  ---  ------   -------------------------------------------  */
/* 03/16/07  JRB    33     Add more retransmit logging.			*/
/* 05/23/05  EJV    32     Add sockLogMaskMapCtrl for parsing logcfg.xml*/
/* 01/24/05  JRB    31     Move tp4_debug_sel & "*_logstr" to lean_var.c*/
/* 09/17/04  JRB    30     tp4_session_timer: chk state only if starting*/
/* 10/21/03  JRB    29     Lint.					*/
/* 04/07/03  JRB    28     Add SPDU_RX_NO_PREALLOCATE option.		*/
/* 06/26/02  JRB    27     If max_spdu_outst exceeded, do delayed abort	*/
/*			   (use new tp_dr_reason in TP_CONN).		*/
/* 06/20/02  JRB    26     Allow max_spdu_outst as high as 128.		*/
/* 01/22/02  JRB    25     Add max_conns arg to tp4_initialize.		*/
/* 05/21/01  JRB    24     #ifdef out tp4_session_timer function for	*/
/*			   Reduced Stack or Trim-7 (not used).		*/
/* 03/14/01  JRB    23     Use new SMEM allocation functions.		*/
/* 03/14/01  JRB    22	   Use new session_cfg.disconnect_timeout.	*/
/* 11/13/00  JRB    21     Alloc tp_conn->spdu_rx.spdu_ptr once at	*/
/*			   startup for each conn. Free before exit.	*/
/* 11/13/00  JRB    20     If spdu_rx exceeds max, disconnect.		*/
/* 03/14/00  JRB    19     tp4_terminate: fake DR.ind so stack cleans up*/
/* 09/13/99  MDE    18     Added SD_CONST modifiers			*/
/* 08/05/99  JRB    17     Support "multithreading" by using		*/
/*			   "clnp_read_fun_co" function pointer.		*/
/* 06/08/99  JRB    16     Chg to support 1024 connections.		*/
/* 01/21/99  JRB    15     BUG FIX: Eliminate retransmit delays caused	*/
/*			   by mishandling reduction of cdt by peer.	*/
/* 10/27/98  JRB    14     Enable error logging before tp0_initialize.	*/
/* 10/16/98  JRB    13     BUG FIX: tp_setup_and_send_dr call		*/
/*			   tp_free_spdu_all to free SPDU buffers.	*/
/* 10/08/98  MDE    12     Migrated to updated SLOG interface		*/
/* 08/13/98  JRB    11     Lint cleanup.				*/
/* 08/04/98  JRB    10     BUG FIX: Only increment "num_trans" for	*/
/*			   first DT in window.				*/
/* 06/04/98  JRB    09     Move "Max retrans" log so state doesn't matter.*/
/* 02/20/98  JRB    08     Del log of OBSOLETE param.			*/
/* 02/16/98  JRB    07     Cast args.					*/
/* 12/29/97  JRB    06     tp4_terminate: disconnect all TP4 conns.	*/
/*			   Don't check for chk_calloc return value=NULL.*/
/* 09/25/97  JRB    05     Don't generate exception for invalid state.	*/
/* 09/04/97  JRB    04     Add max_spdu_len arg to tp4_initialize.	*/
/* 09/04/97  JRB    03     BUG FIX: sending data, set eot in TPDU_DT	*/
/*			   if SPDU fits "exactly" in max size TPDU.	*/
/* 08/26/97  JRB    02     RFC1006 changes:				*/
/*			   tp4_* functs call tp0_* if RFC1006 conn.	*/
/*			   If !TP4_ENABLED, disable whole module.	*/
/*			   tp4_data: pass len as ST_UINT like tp0_data.	*/
/*			   tp4_bind: only set tp4_bind_called if success*/
/* 07/31/97  JRB    01     BUG FIX: Use negotiated TPDU len instead of	*/
/*			   configured (i.e. use tp_conn->max_tpdu_len).	*/
/* 05/27/97  JRB   7.00    MMSEASE 7.0 release.				*/
/* 05/07/97  JRB    25     Improve tp4_bind error codes & logging.	*/
/* 03/26/97  JRB    24     tp4_bind compare arg to tp_cfg.max_num_conns.*/
/* 03/21/97  JRB    23     Add tp_free_spdu_all function.		*/
/* 02/20/97  EJV    22     Added MOSI support: tp4_session_timer func.	*/
/*			   and call to tp4_session_timer_expired.	*/
/* 01/24/97  JRB    21     Just log if in illegal state to receive AK.	*/
/* 01/23/97  JRB    20     Init tp4_debug_sel in tp4_initialize.	*/
/* 11/18/96  JRB    19     Set ak_delay to default if not set.		*/
/* 11/13/96  JRB    18     Don't init globals unless they are constant.	*/
/* 10/31/96  MDE    17     Added Retransmit count			*/
/* 10/16/96  JRB    16     Retransmit all TPDUs in the transmit window.	*/
/* 10/04/96  JRB    15     Move static protos & fix chk_free for OS/2.	*/
/* 10/04/96  JRB    14     Use max_tpdu_len_enc (binary encoded value).	*/
/* 10/04/96  JRB    13     Chg send_ak_flag to ak_delay so can		*/
/*			   configure # of loops to delay sending AK.	*/
/* 09/09/96  JRB    12     Use new send_ak_flag in TP_CONN for		*/
/*			   concatentating AK TPDU with DT TPDU.		*/
/* 09/03/96  JRB    11     Chg local "conn_id" to ST_UINT.		*/
/* 09/03/96  JRB    10     Make "tp_setup_and_send_??" non-static.	*/
/* 09/03/96  JRB    09     Handle retransmissions for TP_STATE_WFCC.	*/
/* 09/03/96  JRB    08     Add tp_conn_clean function.			*/
/* 08/14/96  JRB    07     Add tp4_buffers_avail function.		*/
/* 08/14/96  JRB    06     Increment num_trans before tp_send_dt.	*/
/* 08/12/96  JRB    05     Set retrans_time before tp_send_dt.		*/
/* 08/06/96  JRB    04     Fix ack_sn_in_window & log if fails.		*/
/* 07/26/96  JRB    03     Use new error codes in tp4_init.		*/
/* 07/25/96  JRB    02     Delete tp4_config call. User must call it.	*/
/*			   Define tp4_debug_sel always.			*/
/* 07/17/96  JRB    01     Created					*/
/************************************************************************/
static char *thisFileName = __FILE__;	/* For TP4_EXCEPT and slog macros*/

#include "glbtypes.h"
#include "sysincs.h"
#include "mem_chk.h"
#include "tp4api.h"		/* User definitions for tp4	*/
#include "tp4.h"		/* Internal definitions for tp4	*/
#include "tp4_encd.h"
#include "tp4_log.h"

#if defined(DEBUG_SISCO) && !defined(TP0_ENABLED)
/* NOTE: variables to satisfy link when using the logcfg.xml	*/
LOGCFG_VALUE_GROUP sockLogMaskMapCtrl =
  {
  {NULL,NULL},
  "FOR LINK",
  0,
  NULL
  };
#endif /* defined(DEBUG_SISCO) && !defined(TP0_ENABLED) */

/************************************************************************/
/* Local function Prototypes						*/
/************************************************************************/
static ST_VOID tp_retransmit (TP_CONN *tp_conn);
static ST_VOID tp_retransmit_done (TP_CONN *tp_conn);
static ST_VOID inc_sn (ST_UCHAR *sn);
static ST_BOOLEAN ack_sn_in_window (ST_UCHAR lower_tx_sn, ST_UCHAR ack_sn, ST_UCHAR rem_cdt);
static ST_VOID tp_send_dt_all (TP_CONN *tp_conn);
static ST_VOID tp_setup_ak (TP_CONN *tp_conn, TPDU_AK *tpdu_ak);

/************************************************************************/
/* Global Configuration Structure					*/
/* This structure must be filled in by user BEFORE tp4_initialize ().	*/
/* It MUST NOT change after tp4_initialize ().				*/
/* DEBUG: should tp4_initialize make it's own copy of this struct	*/
/*        so that the user CAN NOT screw it up?????			*/
/************************************************************************/
TP_CFG tp_cfg;

/************************************************************************/
/* Global Variables initialized by tp4_initialize ().			*/
/* Not accessible to user.						*/
/************************************************************************/
TP_CONN *tp_conn_arr;	/* ptr to array of "max_num_conns" structs	*/
static ST_UINT g_tp4_max_spdu_len;	/* Max SPDU size to send or receive	*/

/************************************************************************/
/* Global Variables initialized by tp4_bind ().				*/
/* Not accessible to user.						*/
/************************************************************************/
/* DEBUG: should we check tp4_bind_called before any calls to user?	*/
static ST_INT tp4_bind_called;	/* Flag to prevent multiple bind calls.	*/
ST_LONG only_tp4_bind_id = 99;	/* Only one tp4_bind_id.		*/
ST_LONG only_user_bind_id;		/* Only one user_bind_id.		*/
ST_UCHAR only_loc_tsap [1+MAX_TSEL_LEN];	/* Local len & TSAP addr	*/

/*======================================================================*/
/*======================================================================*/
/* INITIALIZATION AND TERMINATION FUNCTIONS				*/
/*======================================================================*/
/*======================================================================*/

/************************************************************************/
/* tp4_initialize							*/
/* Initialize the TP4 service provider.					*/
/* NOTE:  the configuration parameters in the "tp_cfg" struct must be	*/
/*        set BEFORE calling this function.				*/
/* WARNING: tp_cfg MUST NOT be modified after this function called.	*/
/* NOTE:  the value of tp_cfg.max_num_conns is overwritten with the	*/
/* 	  value passed in the argument max_conns.			*/
/* Return:								*/
/*	SD_SUCCESS or							*/
/*	error code (TP4E_* or error code returned from clnp_init)	*/
/************************************************************************/
ST_RET tp4_initialize (ST_UINT max_conns, ST_UINT max_spdu_len)
  {
ST_RET errcode;
ST_UINT j;

  if (max_conns > TP_MAX_NUM_CONNS)
    {
    TP_LOG_ERR1 ("TP-ERROR: number of requested TP4 connections (%d) exceeds max",
                 max_conns);
    return (TP4E_INVAL_NUM_CONNS);
    }
  tp_cfg.max_num_conns = max_conns;	/* overwrite configured value	*/

#if defined(DEBUG_SISCO)
  tp4_debug_sel |= TP4_LOG_ERR;		/* Always enable error logging.	*/
#endif

#if defined (TP0_ENABLED)
  if ((errcode = tp0_initialize (max_conns, max_spdu_len)) != SD_SUCCESS)
    {
    TP_LOG_ERR0 ("TP-ERROR: TP0/RFC1006 initialization failed.");
    return (errcode);
    }
#endif	/* defined (TP0_ENABLED)	*/

  tp4_init_timer ();

  /* Save arg in global for later use.		*/
  g_tp4_max_spdu_len = max_spdu_len;

  /* Check that all configured parameter values are legal.		*/

  /* Check max_tpdu_len. If legal, save binary encoding in global NOW.	*/
  switch (tp_cfg.max_tpdu_len)
    {					/* code for PDU size	*/
    case  128:	tp_cfg.max_tpdu_len_enc = TP_PDU_MAX_SIZE_128;  break;
    case  256:	tp_cfg.max_tpdu_len_enc = TP_PDU_MAX_SIZE_256;  break;
    case  512:	tp_cfg.max_tpdu_len_enc = TP_PDU_MAX_SIZE_512;  break;
    case 1024:	tp_cfg.max_tpdu_len_enc = TP_PDU_MAX_SIZE_1024; break;
    case 2048:	tp_cfg.max_tpdu_len_enc = TP_PDU_MAX_SIZE_2048; break;
    case 4096:	tp_cfg.max_tpdu_len_enc = TP_PDU_MAX_SIZE_4096; break;
    case 8192:	tp_cfg.max_tpdu_len_enc = TP_PDU_MAX_SIZE_8192; break;
    default:
      TP_LOG_ERR1 ("TP-ERROR: configured max_tpdu_len (%d) illegal",
                 tp_cfg.max_tpdu_len);
      return (TP4E_INVAL_TPDU_LEN);
    }

  if (tp_cfg.max_rem_cdt != 2  &&
      tp_cfg.max_rem_cdt != 4  &&
      tp_cfg.max_rem_cdt != 8  &&
      tp_cfg.max_rem_cdt != 16)
    {
    TP_LOG_ERR1 ("TP-ERROR: configured max_rem_cdt (%d) illegal",
                 tp_cfg.max_rem_cdt);
    return (TP4E_INVAL_REM_CDT);
    }

  if (tp_cfg.loc_cdt > 15)
    {
    TP_LOG_ERR1 ("TP-ERROR: configured loc_cdt (%d) illegal",
                 tp_cfg.loc_cdt);
    return (TP4E_INVAL_LOC_CDT);
    }
  
  if (tp_cfg.max_spdu_outst != 2  &&
      tp_cfg.max_spdu_outst != 4  &&
      tp_cfg.max_spdu_outst != 8  &&
      tp_cfg.max_spdu_outst != 16  &&
      tp_cfg.max_spdu_outst != 32  &&
      tp_cfg.max_spdu_outst != 64  &&
      tp_cfg.max_spdu_outst != 128)
    {
    TP_LOG_ERR1 ("TP-ERROR: configured max_spdu_outst (%d) illegal",
                 tp_cfg.max_spdu_outst);
    return (TP4E_INVAL_SPDU_OUTST);
    }

  if (tp_cfg.window_time == 0)
    {
    TP_LOG_ERR1 ("TP-ERROR: configured window_time (%d) illegal",
                 tp_cfg.window_time);
    return (TP4E_INVAL_WINDOW_TIME);
    }

  if (tp_cfg.inact_time == 0)
    {
    TP_LOG_ERR1 ("TP-ERROR: configured inact_time (%d) illegal",
                 tp_cfg.inact_time);
    return (TP4E_INVAL_INACT_TIME);
    }

  if (tp_cfg.retrans_time == 0)
    {
    TP_LOG_ERR1 ("TP-ERROR: configured retrans_time (%d) illegal",
                 tp_cfg.retrans_time);
    return (TP4E_INVAL_RETRANS_TIME);
    }

  if (tp_cfg.max_trans == 0)
    {
    TP_LOG_ERR1 ("TP-ERROR: configured max_trans (%d) illegal",
                 tp_cfg.max_trans);
    return (TP4E_INVAL_MAX_TRANS);
    }

  if (tp_cfg.ak_delay == 0)
    {
    TP_LOG_ERR1 ("TP-ERROR: configured ak_delay (%d) illegal. Setting to default.",
                 tp_cfg.ak_delay);
    tp_cfg.ak_delay = 2;
    }
  
  /* Initialize the CLNP component.				*/
  /* Set the CLNP NSDU User Data size = TPDU size.		*/
  if ((errcode = clnp_init (tp_cfg.max_tpdu_len)) != SD_SUCCESS)
    return (errcode);

  tp_conn_arr = (TP_CONN *) M_CALLOC (MSMEM_STARTUP, max_conns, sizeof (TP_CONN));
  for (j=0; j<max_conns; j++)
    {
    tp_conn_arr [j].tpdu_dt_tx =
            (TPDU_DT *) M_CALLOC (MSMEM_STARTUP, tp_cfg.max_rem_cdt, sizeof (TPDU_DT));
    tp_conn_arr [j].spdu_tx =
            (SPDU_INFO *) M_CALLOC (MSMEM_STARTUP, tp_cfg.max_spdu_outst, sizeof (SPDU_INFO));
#if !defined(SPDU_RX_NO_PREALLOCATE)
    tp_conn_arr [j].spdu_rx.spdu_ptr = (ST_CHAR *) M_MALLOC (MSMEM_STARTUP, g_tp4_max_spdu_len);
#endif
    }
  return (SD_SUCCESS);
  }

/************************************************************************/
/* tp4_terminate							*/
/************************************************************************/
ST_RET tp4_terminate (ST_VOID)
  {
ST_UINT j;
ST_RET ret = SD_SUCCESS;

#if defined (TP0_ENABLED)
  tp0_terminate ();
#endif

  /* Disconnect all connections.	*/
  for (j = 0;  j < tp_cfg.max_num_conns;  j++)
    {
    /* If already closed or closing, do nothing.	*/
    if (tp_conn_arr [j].state != TP_STATE_CLOSED &&
        tp_conn_arr [j].state != TP_STATE_CLOSING)
      {
      /* Fake disconnect indication so Upper Layers can clean up.	*/
      tp4_disconnect_ind (tp_conn_arr[j].user_conn_id, TP_DR_NO_REASON,
                          0, NULL);
      /* Send disconnect request.					*/
      tp4_disconnect (j, 0, NULL);
      }
    }
  for (j=0; j<tp_cfg.max_num_conns; j++)
    {
    M_FREE (MSMEM_STARTUP, tp_conn_arr [j].tpdu_dt_tx);
    M_FREE (MSMEM_STARTUP, tp_conn_arr [j].spdu_tx);
#if !defined(SPDU_RX_NO_PREALLOCATE)
    M_FREE (MSMEM_STARTUP, tp_conn_arr [j].spdu_rx.spdu_ptr);
#endif
    }
  M_FREE (MSMEM_STARTUP, tp_conn_arr);
  tp_conn_arr = NULL;

  ret = clnp_end ();

  return (ret);
  }
  
/************************************************************************/
/*			tp4_bind					*/
/* This function is called by the user to bind to local TSAP.		*/
/* This is done by passing to the stack local transport address --	*/
/* transport selector + network address (NSAP).				*/
/* WARNING: unlike the other SISCO TP4 interface, this interface	*/
/*          ignores the NSAP of the tp4_addr, and the sharable arg.	*/
/*          The NSAP used is stored only in the CLNP layer.		*/
/************************************************************************/

ST_RET tp4_bind (ST_LONG user_bind_id, 
		  TP4_ADDR *tp4_addr, 
		  ST_INT sharable,
		  ST_INT max_conns)
  {
  if (tp4_addr->tp_type != TP_TYPE_TP4)
    {						/* Not for TP4	*/
#if defined (TP0_ENABLED)
    /* Pass on to TP0		*/
    return (tp0_bind (user_bind_id, tp4_addr, sharable, max_conns));
#else
    TP_LOG_ERR0 ("TP-ERROR: tp4_bind: invalid transport type");
    return (SD_FAILURE);
#endif
    }

  if (tp4_bind_called)
    {
    TP_LOG_ERR0 ("TP-ERROR: too many binds");
    return (TP4E_TOO_MANY_BINDS);
    }

  if (max_conns > tp_cfg.max_num_conns)
    {
    TP_LOG_ERR2 ("TP-ERROR: requested TP conns (%d) greater than number configured (%d)",
                 max_conns, tp_cfg.max_num_conns);
    return (TP4E_INVAL_NUM_CONNS);
    }

  /* Save user_bind_id in Global. Use in all calls to user functions.	*/
  only_user_bind_id = user_bind_id;

  /* Make sure Local TSAP len is legal before copying.			*/
  if (tp4_addr->tp4_sel_len > MAX_TSEL_LEN)
    {
    TP_LOG_ERR0 ("TP-ERROR: TSEL too long");
    return (TP4E_INVAL_TSEL);
    }

  /* Save Local TSAP (only do memcpy if len != 0).			*/
  if ((only_loc_tsap [0] = (ST_UCHAR) tp4_addr->tp4_sel_len) != 0)
    memcpy (&only_loc_tsap [1], tp4_addr->tp4_sel, tp4_addr->tp4_sel_len);
  tp4_bind_cnf (user_bind_id, only_tp4_bind_id, SD_SUCCESS);
  tp4_bind_called = SD_TRUE;	/* Only set if successful.		*/
  return (SD_SUCCESS);
  }
  
/************************************************************************/
/* tp4_unbind								*/
/************************************************************************/
ST_RET tp4_unbind (ST_LONG tp4_bind_id)
  {
#if defined (TP0_ENABLED)
  /* If it's not for TP4, maybe it's for TP0.  Pass it on down.		*/
  if (tp4_bind_id != only_tp4_bind_id)
    return (tp0_unbind (tp4_bind_id));
#endif
  if (tp4_bind_called == SD_FALSE)
    return (SD_FAILURE);		/* Bind never made. Cannot unbind.	*/
  tp4_bind_called = SD_FALSE;	/* Clear flag so user can bind again.	*/
  tp4_unbind_cnf (only_user_bind_id);
  return (SD_SUCCESS);
  }

/*======================================================================*/
/*======================================================================*/
/* TIMER FUNCTIONS							*/
/*======================================================================*/
/*======================================================================*/

/************************************************************************/
/*                      tp4_session_timer				*/
/*----------------------------------------------------------------------*/
/* This function starts the session timer (for MOSI implementation).	*/
/* The user function tp4_session_timer_expired will be called if the	*/
/* timer expires.							*/
/*									*/
/* Parameters:								*/
/*  ST_LONG	tp_conn_id	TP4 connection id for this connect.	*/
/*  ST_BOOLEAN	start		SD_TRUE if timer should be started,	*/
/*				SD_FALSE if timer should be stopped.	*/
/*									*/
/* Return:								*/
/*	SD_SUCCESS (0)		if successful				*/
/*	error code		if not successful			*/
/************************************************************************/
#if !(defined(ADLC_SLAVE) || defined (ADLC_MASTER))	/* NOT Reduced Stack or Trim-7*/
/* Reduced Stack & Trim-7 DO NOT use session timer.			*/

ST_RET tp4_session_timer (ST_LONG tp_conn_id, ST_BOOLEAN start)
{
TP_CONN *tp_conn = &tp_conn_arr [tp_conn_id];

#if defined (TP0_ENABLED)
  if (tp_conn_id >= MIN_TP0_CONN_ID)
    return (tp0_session_timer (tp_conn_id, start));
#endif

  if (start)
    {
    if (tp_conn->state != TP_STATE_OPEN)
      {
      TP_LOG_ERR1 ("TP-ERROR: illegal connection state = %d", tp_conn->state);
      return (TP4E_CONN_STATE);
      }

    /* If configured, use configured val. It not, compute sensible timeout.*/
    if (session_cfg.disconnect_timeout)
      tp_conn->session_timer = session_cfg.disconnect_timeout;
    else
      tp_conn->session_timer = tp_cfg.retrans_time * tp_cfg.max_trans;
    }
  else
    tp_conn->session_timer = 0;		/* stopping the session timer	*/

  return (SD_SUCCESS);
}
#endif	/* !(defined(ADLC_SLAVE) || defined (ADLC_MASTER))	*/

/*======================================================================*/
/*======================================================================*/
/* DATA TRANSFER FUNCTIONS						*/
/*======================================================================*/
/*======================================================================*/

/************************************************************************/
/*			tp4_timer_tick					*/
/*----------------------------------------------------------------------*/
/* This function is called on 1 second intervals by the TP4-user	*/
/* When this function is called, TP4 decrements all of the timers	*/
/* for all outstanding transport connections.				*/
/*									*/
/* Parameters:								*/
/*	ST_VOID			none				       	*/
/*									*/
/* Return:								*/
/*	ST_VOID			none					*/
/************************************************************************/
ST_VOID tp4_timer_tick ()
  {
ST_UINT conn_id;
TP_CONN *tp_conn;
ST_INT reason;		/* Disconnect reason	*/

  clnp_timer_tick ();	/* Let CLNP process it's timers too.		*/

#if defined (TP0_ENABLED)
  tp0_timer_tick ();	/* Let TP0 process it's timers too.		*/
#endif

  /* Because this function is called often and the entire tp_conn_arr	*/
  /* must be checked, it must be very efficient.  Therefore, tp_conn	*/
  /* is used to point to each element of array (instead of		*/
  /* tp_conn_arr[conn_id]).						*/
  for (conn_id = 0, tp_conn = &tp_conn_arr[0];
       conn_id < tp_cfg.max_num_conns;
       conn_id++, tp_conn++)
    {
    /* Handle "retransmission timer".				*/
    /* Only decrement it if it's not 0 and state is legal.	*/
    if (tp_conn->state != TP_STATE_CLOSED &&
        tp_conn->state != TP_STATE_WFTRESP &&
        tp_conn->retrans_time)
      {
      if (--tp_conn->retrans_time == 0)
        {	/* Timer expired	*/
        if (tp_conn->num_trans >= tp_cfg.max_trans)
          {		/* Don't retransmit	*/
          tp_retransmit_done (tp_conn);
          }
        else
          {		/* OK to retransmit	*/
          tp_retransmit (tp_conn);	/* Retransmit one TPDU	*/
          tp_conn->num_trans++;		/* Inc # of transmissions	*/
          tp_conn->retrans_time = tp_cfg.retrans_time;	/* Reset timer	*/
          }
        }	/* End "if timer expired"	*/
      }		/* End "retransmission timer" handling	*/

    /* Handle "window timer".					*/
    /* Only decrement it if it's not 0 and state is legal.	*/
    if (tp_conn->state == TP_STATE_OPEN &&
        tp_conn->window_time)
      {
      if (--tp_conn->window_time == 0)
        {	/* Timer expired	*/
        tp_setup_and_send_ak (tp_conn);	/* send AK & reset window_time	*/
        }	/* End "if timer expired"	*/
      }		/* End "window timer" handling	*/

    /* Handle "inactivity timer".					*/
    /* Only decrement it if it's not 0 and state is legal.	*/
    if (tp_conn->state == TP_STATE_OPEN &&
        tp_conn->inact_time)
      {
      if (--tp_conn->inact_time == 0)
        {	/* Timer expired	*/
        TP_LOG_ERR1 ("TP-ERROR: Inactivity timer expired on conn %d", conn_id);
        /* Pass up disconnect indication to user.		*/
        /* DEBUG: "reason" passed to tp4_disconnect_ind not same as	*/
        /*        tpdu_dr->reason. Should this be changed?		*/
        reason = 0xff;			/* Local user error	*/
        tp4_disconnect_ind (tp_conn->user_conn_id, reason,
                            0, NULL);	/* No user data passed up.	*/
        tp_conn->state = TP_STATE_CLOSED;	/* Skip REFWAIT state.		*/
        }	/* End "if timer expired"	*/
      }		/* End "inactivity timer" handling	*/

    /* Handle "session timer" (MOSI implementation only)	*/
    /* Only decrement it if it's not 0 and state is legal.	*/
    if (tp_conn->state == TP_STATE_OPEN &&
        tp_conn->session_timer)
      {
      if (--tp_conn->session_timer == 0)
        tp4_session_timer_expired (tp_conn->user_conn_id);
      }		/* End "session timer" handling	*/

    }		/* End "for" loop	*/
  }

/************************************************************************/
/* tp_retransmit							*/
/* Retransmit whatever is needed for this connection			*/
/************************************************************************/

ST_LONG tp4RetransCount;

static ST_VOID tp_retransmit (TP_CONN *tp_conn)
  {
TPDU_DT *tpdu_dt_tx;		/* ptr to TPDU of interest.	*/
ST_UCHAR tx_sn;

  TP_LOG_REQ3 ("Retransmission on conn %d, dst_ref=0x%04X, state=%d",
               tp_conn - tp_conn_arr, tp_conn->rem_ref, tp_conn->state);

  ++tp4RetransCount;

  switch (tp_conn->state)
    {
    case TP_STATE_WFCC:
      tp_send_cr (&tp_conn->tpdu_cx);		/* Retransmit CR.	*/
      break;
    /*   TP_STATE_WBCL state is never entered, so it is NOT handled.	*/
    case TP_STATE_OPEN:
      /* Retransmit all TPDUs in the transmit window.			*/
      for (tx_sn = tp_conn->lower_tx_sn; tx_sn != tp_conn->next_tx_sn;
           inc_sn (&tx_sn))	/* Must increment with wrap around	*/
        {
        tpdu_dt_tx = &tp_conn->tpdu_dt_tx [tx_sn & (tp_cfg.max_rem_cdt-1)];
        tp_send_dt (tpdu_dt_tx);
        }
      break;
    case TP_STATE_AKWAIT:
      tp_send_cc (&tp_conn->tpdu_cx);		/* Retransmit CC.	*/
      break;
    case TP_STATE_CLOSING:
      tp_setup_and_send_dr (tp_conn);
      break;
    default:
      TP4_EXCEPT ();		/* Illegal state.		*/
      break;
    }	/* end "switch"	*/
  }

/************************************************************************/
/* tp_retransmit_done							*/
/* Give up on Retransmission on this connection				*/
/************************************************************************/
static ST_VOID tp_retransmit_done (TP_CONN *tp_conn)
  {
ST_INT reason;		/* Disconnect reason	*/

  TP_LOG_ERR3 ("TP-ERROR: Max retransmissions exceeded on conn %d, dst_ref=0x%04X, state=%d",
               tp_conn - tp_conn_arr, tp_conn->rem_ref, tp_conn->state);
  
  switch (tp_conn->state)
    {
    case TP_STATE_WFCC:
      reason = 0xff;			/* Local user error	*/
      tp4_disconnect_ind (tp_conn->user_conn_id, reason,
                          0, NULL);	/* No user data passed up.	*/
      tp_conn->state = TP_STATE_CLOSED;	/* Skip REFWAIT state.		*/
      break;
    /*   TP_STATE_WBCL state is never entered, so it is NOT handled.	*/
    case TP_STATE_OPEN:
      tp_conn->window_time = 0;		/* Stop window timer.		*/
      tp_conn->inact_time = 0;		/* Stop inactivity timer	*/
      /* CRITICAL: do not "break". Do same as for AKWAIT state now.	*/
    case TP_STATE_AKWAIT:
      tp_conn->retrans_time = tp_cfg.retrans_time;
      tp_conn->num_trans = 1;		/* Set to 0 and increment	*/

      /* Fill in TPDU_DR struct and send DR.		*/
      tp_setup_and_send_dr (tp_conn);
      /* DEBUG: "reason" passed to tp4_disconnect_ind not same as	*/
      /*        tpdu_dr->reason. Should this be changed?		*/
      reason = 0xff;			/* Local user error	*/
      tp4_disconnect_ind (tp_conn->user_conn_id, reason,
                          0, NULL);	/* No user data passed up.	*/
      tp_conn->state = TP_STATE_CLOSING;
      break;
    case TP_STATE_CLOSING:
      tp_conn->state = TP_STATE_CLOSED;
      break;
    default:
      TP4_EXCEPT ();		/* Illegal state.		*/
      break;
    }	/* end "switch"	*/
  }

/************************************************************************/
/* tp4_buffers_avail							*/
/*----------------------------------------------------------------------*/
/* This function returns the number of buffers available for sending	*/
/* SPDUs.  This may be used, for example, when sending Information	*/
/* Reports, to make sure there are always enough buffers for sending	*/
/* responses to incoming requests.					*/
/*									*/
/* Parameters:								*/
/*	ST_LONG tp_conn_id		Transport Connection ID			*/
/*									*/
/* Return:								*/
/*	ST_INT			# of SPDU transmit buffers available	*/
/************************************************************************/
ST_INT tp4_buffers_avail (ST_LONG tp_conn_id)
  {
TP_CONN *tp_conn = &tp_conn_arr [tp_conn_id];

#if defined (TP0_ENABLED)
  if (tp_conn_id >= MIN_TP0_CONN_ID)
    return (tp0_buffers_avail (tp_conn_id));
#endif
  
  return (tp_cfg.max_spdu_outst - tp_conn->num_spdu_outst);
  }
  

/************************************************************************/
/* inc_sn								*/
/* Increment sequence # with wrap around at MODULUS_SN.			*/
/************************************************************************/
static ST_VOID inc_sn (ST_UCHAR *sn)
  {
  if (++(*sn) >= MODULUS_SN)
    *sn = 0;
  }

/************************************************************************/
/* ack_sn_in_window							*/
/* Check that ack_sn is in window.					*/
/* RETURN CODE:		SD_FALSE	(NOT in window)				*/
/*			SD_TRUE	(IS in window)				*/
/************************************************************************/
static ST_BOOLEAN ack_sn_in_window (ST_UCHAR lower_tx_sn, ST_UCHAR ack_sn, ST_UCHAR rem_cdt)
  {
ST_UCHAR j;
  for (j = 0; j <= rem_cdt; j++)
    {
    if (lower_tx_sn == ack_sn)
      break;
    inc_sn (&lower_tx_sn);	/* increment sequence # with wrap around	*/
    }
  if (j > rem_cdt)
    {
    TP_LOG_ERR1 ("TP-ERROR: AK SN = %d not within window", ack_sn);
    return (SD_FALSE);	/* ack_sn WAS NOT within window	*/
    }
  return (SD_TRUE);	/* ack_sn WAS within window	*/
  }
  
/************************************************************************/
/* tp4_data								*/
/* RETURN CODES:							*/
/*	SD_SUCCESS		(if SPDU successfully queued for sending)	*/
/*	TP4E_QUEUE_FULL	(if queue is full)				*/
/*      TP4E_CONN_STATE (connection not in proper state for this)	*/
/************************************************************************/
ST_RET tp4_data (ST_LONG tp_conn_id, ST_INT eot, ST_UINT spdu_len, ST_CHAR *spdu_ptr)
  {
SPDU_INFO *spdu_tx;
TP_CONN *tp_conn = &tp_conn_arr [tp_conn_id];

#if defined (TP0_ENABLED)
  if (tp_conn_id >= MIN_TP0_CONN_ID)
    return (tp0_data (tp_conn_id, eot, spdu_len, spdu_ptr));
#endif

  if (tp_conn->state != TP_STATE_OPEN)
    {
    TP_LOG_ERR1 ("TP-ERROR: illegal connection state = %d", tp_conn->state);
    return (TP4E_CONN_STATE);
    }

  if (tp_conn->num_spdu_outst >= tp_cfg.max_spdu_outst)
    {
    TP_LOG_ERR1 ("TP-ERROR: SPDU queue full (num = %d)", tp_conn->num_spdu_outst);

    /* NOTE: we should abort now, but user code might not handle well	*/
    /* an abort while sending req or resp, so we just set error flag.	*/
    /* An abort/disconnect MUST be generated on next call to "tp4_event".*/
    tp_conn->tp_dr_reason = TP_DR_CONGESTION;
    return (TP4E_QUEUE_FULL);
    }
  
  /* Set spdu_tx pointing to right struct in array of structs,	*/
  /* and fill it in.							*/
  /* If max_spdu_outst = 2, the following storage results:		*/
  /* If "spdu_cnt_qued" is EVEN, SPDU is stored at array index 0	*/
  /* If "spdu_cnt_qued" is ODD, SPDU is stored at array index 1		*/
  /* This algorithm will work if max_spdu_outst is any power of 2	*/
  /* (i.e. 2,4,8,16).							*/
  /* What's nice is we don't have to keep track if struct is in use.	*/
  /* If "num_spdu_outst" and "spdu_cnt_qued" are accurate,		*/
  /* "spdu_cnt_qued & (max_spdu_outst-1)" is always an unused position in array*/
  
  spdu_tx = &tp_conn->spdu_tx [tp_conn->spdu_cnt_qued & (tp_cfg.max_spdu_outst-1)];

  /* Allocate buffer for SPDU and copy data at "spdu_ptr" to it.	*/
  spdu_tx->spdu_len = spdu_len;
  spdu_tx->spdu_ptr = (ST_CHAR *) M_MALLOC (MSMEM_SPDU_TX, spdu_len);
  memcpy (spdu_tx->spdu_ptr, spdu_ptr, spdu_len);
  spdu_tx->offset = 0;

  tp_conn->num_spdu_outst++;	/* This decremented when SPDU ACKed	*/
  tp_conn->spdu_cnt_qued++;		/* counter loops around		*/

  tp_send_dt_all (tp_conn);	/* Send as many TPDUs as you can.	*/
  return (SD_SUCCESS);
  }
    
/************************************************************************/
/* tp_send_dt_all							*/
/************************************************************************/
static ST_VOID tp_send_dt_all (TP_CONN *tp_conn)
  {
ST_UCHAR lower;
ST_UCHAR next;
ST_UCHAR upper;
TPDU_DT *tpdu_dt_tx;		/* ptr to TPDU of interest.	*/
SPDU_INFO *spdu_tx;		/* ptr to SPDU of interest	*/
TPDU_AK tpdu_ak;		/* AK TPDU to concatentate with DT.	*/

  if (tp_conn->spdu_cnt_sent != tp_conn->spdu_cnt_qued && tp_conn->adj_rem_cdt)
    {	/* Num sent not equal to num queued, AND we have credits.	*/
    lower = tp_conn->lower_tx_sn;
    next = tp_conn->next_tx_sn;
    if ((upper = lower + tp_conn->adj_rem_cdt) >= MODULUS_SN)
      upper -= MODULUS_SN;	/* Adjust for wrapping if necessary.	*/
  
    if (
        ( upper < lower  &&  (next >= lower || next < upper) )	/* Wrapped*/
        ||
        ( next >= lower  &&  next < upper)			/* Normal*/
       )
      {
      /* Send at least part of the next SPDU.  May have already sent	*/
      /* part of it, in which case the "offset" will not be 0.		*/
      spdu_tx = &tp_conn->spdu_tx [tp_conn->spdu_cnt_sent & (tp_cfg.max_spdu_outst-1)];
      tpdu_dt_tx = &tp_conn->tpdu_dt_tx [next & (tp_cfg.max_rem_cdt-1)];
      tpdu_dt_tx->dst_ref = tp_conn->rem_ref;
      tpdu_dt_tx->sn = tp_conn->next_tx_sn;
      inc_sn (&tp_conn->next_tx_sn);	/* increment send SN now	*/
      tpdu_dt_tx->rem_mac = tp_conn->rem_mac;
      tpdu_dt_tx->rem_nsap = tp_conn->rem_nsap;
      tpdu_dt_tx->udata_ptr = spdu_tx->spdu_ptr + spdu_tx->offset;
      if (spdu_tx->spdu_len - spdu_tx->offset <= (ST_UINT)(tp_conn->max_tpdu_len - TP_HEAD_LEN_DT))
        {
        tpdu_dt_tx->udata_len = spdu_tx->spdu_len - spdu_tx->offset;
        tpdu_dt_tx->eot = SD_TRUE;
        tp_conn->spdu_cnt_sent++;
        }
      else
        {
        /* Send largest allowed TPDU, taking header size into account.	*/
        tpdu_dt_tx->udata_len = tp_conn->max_tpdu_len - TP_HEAD_LEN_DT;
        tpdu_dt_tx->eot = SD_FALSE;
        spdu_tx->offset += tpdu_dt_tx->udata_len;
        }

      /* CRITICAL: only increment num_trans if this is first TPDU in	*/
      /* window. We only count the # of transmissions of the first TPDU	*/
      /* in the window. When the retrans timer goes off, we resend	*/
      /* all TPDUs in the window.					*/
      if (next == lower)
        tp_conn->num_trans++;

      tp_conn->retrans_time = tp_cfg.retrans_time;
      if (tp_conn->ak_delay)	/* If not 0, there is AK to send.	*/
        {
        tp_setup_ak (tp_conn, &tpdu_ak);	/* This clears ak_delay.*/
        tp_send_dt_and_ak (tpdu_dt_tx, &tpdu_ak);
        }
      else
        tp_send_dt (tpdu_dt_tx);
      }
    }	/* End "if (tp_conn->spdu_cnt_sent != tp_conn->spdu_cnt_qued)"	*/
  }

/************************************************************************/
/* tp4_event								*/
/* Receive a n_unitdata NSDU, decode it, process it, and free it.	*/
/************************************************************************/
ST_BOOLEAN tp4_event ()
  {
N_UNITDATA *n_unitdata;
ST_UINT conn_id;
TP_CONN *tp_conn;
ST_BOOLEAN retcode = SD_FALSE;	/* Default to FALSE (no event received)	*/

#if defined (TP0_ENABLED)
  if (tp0_event ())
    retcode = SD_TRUE;			/* TP0 TPDU received.	*/
#endif

  tp4_check_timer ();

  /* For all active connections, get DT TPDUs from queue and send.	*/
  for (conn_id = 0, tp_conn = &tp_conn_arr[0];
       conn_id < tp_cfg.max_num_conns;
       conn_id++, tp_conn++)
    {
    if (tp_conn->state == TP_STATE_OPEN)
      {
      if (tp_conn->tp_dr_reason)		/* Error on this conn?	*/
        {
        TP_LOG_ERR2 ("Unrecoverable error 0x%X on tp conn %d, aborting",
                     tp_conn->tp_dr_reason, conn_id);
        /* Pass up disconnect indication.	*/
        tp4_disconnect_ind (tp_conn->user_conn_id, tp_conn->tp_dr_reason, 0, NULL);
        /* Send disconnect request.		*/
        tp4_disconnect (conn_id, 0, NULL);
        continue;				/* skip to next conn	*/
        }
      tp_send_dt_all (tp_conn);
      }
    /* If ak_delay gets decremented to 0, it means there was no DT for	*/
    /* an AK to be concatenated to, so the AK must be sent by itself.	*/
    if (tp_conn->ak_delay  &&  (--tp_conn->ak_delay == 0))
      tp_setup_and_send_ak (tp_conn);
    }

  n_unitdata = (*clnp_read_fun_co) ();	/* Read NSDU from CLNP	*/

  if (n_unitdata)
    {
    /* n_unitdata NSDU data part should be one or more TPDUs. Decode it.*/
    /* During decode, one or more of the "tp_process_*" functions below	*/
    /* will be called.							*/
    tp_decode_nsdu (n_unitdata);		/* Decode it.	*/
    clnp_free (n_unitdata);			/* Free it.	*/
    retcode = SD_TRUE;			/* TP4 TPDU received.	*/
    }
  return (retcode);	/* SD_TRUE if TP0 and/or TP4 TPDU received	*/
  }
  
/************************************************************************/
/* tp_process_dt							*/
/* Only one SPDU per connection is ever being processed.  As soon as	*/
/* the EOT is received, the SPDU is passed up to the Transport-user.	*/
/************************************************************************/
ST_VOID tp_process_dt (TPDU_DT *tpdu_dt_rx)
  {
ST_UINT conn_id;
TP_CONN *tp_conn;

  if ((conn_id = calc_conn_id (tpdu_dt_rx->dst_ref)) >= tp_cfg.max_num_conns)
    return;	/* Loc ref is invalid.  Ignore this TPDU.			*/
  
  tp_conn = &tp_conn_arr [conn_id];

  if (tp_conn->tpdu_cx.loc_ref != tpdu_dt_rx->dst_ref)
    return;	/* Loc ref is invalid.  Ignore this TPDU.			*/

  switch (tp_conn->state)
    {
    case TP_STATE_CLOSED:
      return;			/* Ignore this DT.			*/
    case TP_STATE_OPEN:
      tp_conn->inact_time = tp_cfg.inact_time;
      break;			/* Continue				*/
    case TP_STATE_AKWAIT:
      tp_conn->inact_time = tp_cfg.inact_time;
      tp_conn->state = TP_STATE_OPEN;
      break;			/* Continue				*/
    case TP_STATE_CLOSING:
      /* Do nothing. If we sent a DR, it will be resent based on retrans_time.*/
      return;			/* Don't bother with ack_sn_in_window check.*/
    default:
      TP_LOG_ERR1 ("TP-ERROR: invalid state (%d) for received DT. Ignored.",
        tp_conn->state);
      return;
    }
    
  /* Check Sequence # (this takes care of retransmissions too).		*/
  if (tpdu_dt_rx->sn != tp_conn->next_rx_sn)
    {
    tp_setup_and_send_ak (tp_conn);	/* send AK & reset window_time	*/
    return;	/* Out of sequence. Throw out TPDU.  ACK already sent	*/
    		/* with correct SN.					*/
    }

  inc_sn (&tp_conn->next_rx_sn);
  tp_conn->ak_delay = tp_cfg.ak_delay;	/* Set # loops delay before AK.	*/ 

  /* If this is beginning of SPDU, initialize buffer for it.		*/
  if (tp_conn->spdu_rx_start)	/* init when CR rcvd or CR sent 	*/
    {		/* Last TPDU contained EOT. This TPDU starts new SPDU.	*/
    /* We can freely overwrite "spdu_rx.spdu_ptr" because the user	*/
    /* is now responsible for the last one.				*/
    tp_conn->spdu_rx.spdu_len = 0;
    }

  if ((ST_UINT) (tp_conn->spdu_rx.spdu_len + tpdu_dt_rx->udata_len)
      > g_tp4_max_spdu_len)
    {
    /* Would exceed max SPDU size. CAN'T DO memcpy. WON'T FIT IN BUFFER.*/
    /* No good recovery, so just disconnect.				*/
    /* NOTE: This is really a Session problem, but we handle it here.	*/

    TP_LOG_ERR1 ("Received msg exceeds max_spdu_len (%d)", g_tp4_max_spdu_len);

    /* Pass up disconnect indication.	*/
    tp4_disconnect_ind (tp_conn->user_conn_id, TP_DR_PROT_ERROR,
                        0, NULL);
    /* Send disconnect request.		*/
    tp4_disconnect (conn_id, 0, NULL);
    return;					/* DO NOT CONTINUE	*/
    }

  memcpy (tp_conn->spdu_rx.spdu_ptr + tp_conn->spdu_rx.spdu_len, tpdu_dt_rx->udata_ptr,
          tpdu_dt_rx->udata_len);
  tp_conn->spdu_rx.spdu_len += tpdu_dt_rx->udata_len;

  if (tpdu_dt_rx->eot)
    {		/* This TPDU contains EOT. This TPDU ends SPDU.		*/
    tp_conn->spdu_rx_start = SD_TRUE;		/* Next TPDU will begin a SPDU.	*/

    /* Pass up SPDU to user. Note that we always pass up complete SPDU	*/
    /* so eot is always SD_TRUE.						*/
    /* "tp4_data_ind" must completely process the data at spdu_ptr.	*/
    /* When it returns, the buffer may be reused.			*/

    tp4_data_ind (tp_conn->user_conn_id, tpdu_dt_rx->eot, tp_conn->spdu_rx.spdu_len,
                  tp_conn->spdu_rx.spdu_ptr);
    }
  else
    tp_conn->spdu_rx_start = SD_FALSE;	/* Next TPDU is part of this SPDU*/
  }

/************************************************************************/
/* tp_process_ak							*/
/* Don't change "adj_rem_cdt" until end of this function.		*/
/************************************************************************/

ST_VOID tp_process_ak (TPDU_AK *tpdu_ak)
  {
ST_UINT conn_id;
TP_CONN *tp_conn;
TPDU_DT *tpdu_dt_tx;		/* ptr to TPDU of interest.		*/
ST_UCHAR spdu_tx_index;		/* index into array of SPDUs.		*/

  if ((conn_id = calc_conn_id (tpdu_ak->dst_ref)) >= tp_cfg.max_num_conns)
    return;	/* Loc ref is invalid.  Ignore this AK.			*/
  
  tp_conn = &tp_conn_arr [conn_id];

  if (tpdu_ak->dst_ref != tp_conn->tpdu_cx.loc_ref)
    return;	/* Loc ref is invalid.  Ignore this AK.			*/

  switch (tp_conn->state)
    {
    case TP_STATE_CLOSED:
      return;			/* Ignore this AK.			*/
    case TP_STATE_OPEN:
      tp_conn->inact_time = tp_cfg.inact_time;
      break;			/* See ack_sn_in_window call below	*/
    case TP_STATE_AKWAIT:
      tp_conn->inact_time = tp_cfg.inact_time;
      tp_conn->state = TP_STATE_OPEN;
      break;			/* See ack_sn_in_window call below	*/
    case TP_STATE_CLOSING:
      /* Do nothing. If we sent a DR, it will be resent based on retrans_time.*/
      return;			/* Don't bother with ack_sn_in_window check.*/
    default:
      TP_LOG_ERR1 ("TP-ERROR: Illegal state to receive AK on conn %d. Ignored.",
                   conn_id);
      return;
    }
    
  /* Is this ACK within the window. If not, we ignore it.		*/
  /* NOTE: we use the adjusted cdt (adj_rem_cdt) for the window because	*/
  /*       this is what we use to send, even though the CDT granted	*/
  /*       by the peer may be bigger.					*/
  if (ack_sn_in_window (tp_conn->lower_tx_sn, tpdu_ak->sn, tp_conn->adj_rem_cdt))
    {
    /* This is a legal ACK for one or more outstanding TPDUs.		*/
    /* Clear them out of outstanding TPDU list.				*/
    while (tp_conn->lower_tx_sn != tpdu_ak->sn)
      {
      tpdu_dt_tx = &tp_conn->tpdu_dt_tx [tp_conn->lower_tx_sn & (tp_cfg.max_rem_cdt-1)];
      if (tpdu_dt_tx->eot)
        {
        /* Done with this SPDU.  Free the buffer.		*/
        spdu_tx_index = tp_conn->spdu_cnt_done & (tp_cfg.max_spdu_outst-(ST_UCHAR)1);
        tp_conn->spdu_cnt_done++;	/* Increment SPDU "done" count.	*/
        M_FREE (MSMEM_SPDU_TX, tp_conn->spdu_tx [spdu_tx_index].spdu_ptr);
        /* Decrement num SPDUs outstanding. Should never go below 0.	*/
        if (tp_conn->num_spdu_outst-- == 0)
          TP4_EXCEPT ();	/* This better not happen.		*/
        }
      /* increment sequence # with wrap around	*/
      inc_sn (&tp_conn->lower_tx_sn);
      /* Clear the "# of transmissions".	*/
      tp_conn->num_trans = 0;
      }

    /* If this is AK for last TPDU sent, stop retransmission timer.	*/
    if (tp_conn->lower_tx_sn == tp_conn->next_tx_sn)
      tp_conn->retrans_time = 0;

    /* Set adj_rem_cdt = tpdu_ak->cdt OR max_rem_cdt, whichever is smaller.*/
    tp_conn->adj_rem_cdt = min (tpdu_ak->cdt, tp_cfg.max_rem_cdt);
    }	/* end "if (ack_sn_in_window (...)"	*/
  }

/************************************************************************/
/* tp_setup_and_send_ak							*/
/************************************************************************/
ST_VOID tp_setup_and_send_ak (TP_CONN *tp_conn)
  {
TPDU_AK tpdu_ak;

  tp_setup_ak (tp_conn, &tpdu_ak);
  tp_send_ak (&tpdu_ak);
  }

/************************************************************************/
/* tp_setup_ak - setup AK TPDU.						*/
/* NOTE: tp_setup_ak call should always be followed by tp_send_ak or	*/
/*       tp_send_dt_and_ak because "window_time" is set here.		*/
/************************************************************************/
static ST_VOID tp_setup_ak (TP_CONN *tp_conn, TPDU_AK *tpdu_ak)
  {
  tpdu_ak->dst_ref = tp_conn->rem_ref;		/* Fill in AK TPDU.	*/
  tpdu_ak->sn = tp_conn->next_rx_sn;
  tpdu_ak->cdt = tp_cfg.loc_cdt;
  tpdu_ak->rem_mac = tp_conn->rem_mac;
  tpdu_ak->rem_nsap = tp_conn->rem_nsap;

  tp_conn->window_time = tp_cfg.window_time;	/* Re-init timer.	*/
  tp_conn->ak_delay = 0;			/* Reset AK delay.	*/
  }

/************************************************************************/
/* tp_setup_and_send_dr							*/
/************************************************************************/
ST_VOID tp_setup_and_send_dr (TP_CONN *tp_conn)
  {
TPDU_DR tpdu_dr;
ST_UINT16 conn_id;

  tp_free_spdu_all (tp_conn);	/* Free all SPDUs allocated for this conn*/

  conn_id = tp_conn - tp_conn_arr;	/* Compute array index.	*/
  tpdu_dr.loc_ref = calc_loc_ref (conn_id, tp_conn->loc_ref_offset);
  tpdu_dr.rem_ref = tp_conn->rem_ref;
  tpdu_dr.rem_nsap = tp_conn->rem_nsap;
  tpdu_dr.rem_mac = tp_conn->rem_mac;
  tpdu_dr.reason = TP_DR_NORMAL;
  tp_send_dr (&tpdu_dr);
  }

/************************************************************************/
/* tp_conn_clean							*/
/* Initialize connection struct for a new connection.			*/
/************************************************************************/
ST_VOID tp_conn_clean (TP_CONN *tp_conn)
  {
#if defined(SPDU_RX_NO_PREALLOCATE)
  tp_conn->spdu_rx.spdu_ptr = (ST_CHAR *) M_MALLOC (MSMEM_STARTUP, g_tp4_max_spdu_len);
#endif
  tp_conn->spdu_rx_start = SD_TRUE;	/* CRITICAL: Initialize flag.	*/
  tp_conn->window_time = 0;
  tp_conn->inact_time = 0;
  tp_conn->retrans_time = 0;
  tp_conn->lower_tx_sn = 0;
  /* tp_conn->adj_rem_cdt set when conn established. Not used before then.*/
  tp_conn->next_tx_sn = 0;
  tp_conn->next_rx_sn = 0;
  tp_conn->num_spdu_outst = 0;
  tp_conn->spdu_cnt_qued = 0;
  tp_conn->spdu_cnt_sent = 0;
  tp_conn->spdu_cnt_done = 0;
  tp_conn->num_trans = 0;
  tp_conn->tp_dr_reason = 0;
  return;
  }

/************************************************************************/
/*			tp_free_spdu_all				*/
/* Free all SPDUs that have been allocated, but not sent yet.		*/
/************************************************************************/
ST_VOID tp_free_spdu_all (TP_CONN *tp_conn)
  {
ST_UCHAR spdu_tx_index;		/* index into array of SPDUs.		*/

  while (tp_conn->spdu_cnt_done != tp_conn->spdu_cnt_qued)
    {	/* Num done not equal to num queued.		*/
    spdu_tx_index = tp_conn->spdu_cnt_done & (tp_cfg.max_spdu_outst-1);
    M_FREE (MSMEM_SPDU_TX, tp_conn->spdu_tx [spdu_tx_index].spdu_ptr);
    tp_conn->spdu_cnt_done++;
    }
#if defined(SPDU_RX_NO_PREALLOCATE)
  M_FREE (MSMEM_STARTUP, tp_conn->spdu_rx.spdu_ptr);
#endif
  }
#endif	/* defined (TP4_ENABLED)	*/
