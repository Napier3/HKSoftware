/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*	(c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*	1995-2005, All Rights Reserved					*/
/*									*/
/* MODULE NAME : acse2dec.c						*/
/* PRODUCT(S)  :							*/
/*									*/
/* MODULE DESCRIPTION :							*/
/*	ACSE Decode Functions.						*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev     Comments					*/
/* --------  ---  ------   -------------------------------------------  */
/* 02/26/09  JRB    12     Fix to handle PDV len=0 or user_info len=0.	*/
/* 04/28/08  GLB    59     Removed CALLED_ONLY and CALLING_ONLY         */
/* 01/30/06  GLB    58     Integrated porting changes for VMS           */
/* 07/06/05  EJV    57     Log "IP ADDR:" on the same line as the ip.	*/
/* 05/19/05  JRB    56     Chg "unrecognized tag" logs from ERR to DEC.	*/
/* 03/31/05  EJV    55     a_get_rem_ip_addr: added defined(linux)	*/
/* 09/20/04  JRB    54     u_copp_con_cnf: don't access acse_conn after	*/
/*			   copp_u_abort_req (it may have been freed).	*/
/* 08/06/04  EJV    53     _a_dec_authentication: chg param to ST_UCHAR.*/
/* 03/15/04  GLB    51     Delete "iso_mms_is_ASO_context_name"         */
/* 03/04/04  JRB    51     Use ASN1 decode log macros (ALOG_DEC*)	*/
/*			   Del logging of A-DATA.ind (use MVL or COPP)	*/
/* 02/06/04  EJV    50	   Use MACE_MECH_ID define.			*/
/* 01/08/04  EJV    49     Ported funcs to sun.				*/
/* 12/12/03  JRB    48     Fix asn1r_get_bitstr calls, init data=0 first*/
/* 10/24/03  JRB    47     Chg #if ..TP0.. to avoid compile errors.	*/
/* 07/08/03  EJV    46     Del old password auth (OBSOLETE_ACSE_AUTH);	*/
/*			   ACSE_AUTH_ENABLED code wo/define.		*/
/*			   Fix the ACSE Auth decode.			*/
/* 03/31/03  JRB    45     asn1r_get_bitstr: add max_bits arg.		*/
/* 11/08/02  JRB    44     asn1_skip_elmnt ret error if indef len.	*/
/* 10/29/02  JRB    43     Fix a_auth_password_dec ret if pwd too long.	*/
/* 10/22/02  ASK    42	   Wrap ifdef TP0_ENABLED around inet_ntoa calls*/
/* 10/14/02  ASK    41     Added decode of abort diagnostic.		*/
/* 10/03/02  ASK    40     Now send abort when AARQ fails to decode	*/
/* 09/27/02  ASK    39     Added ACSE auth decode to AARE, moved 	*/
/*			   bitstring defines into acse2.h		*/	
/* 06/26/02  JRB    38     con_ind: Log calling/called address.		*/
/* 06/20/02  JRB    37     con_ind: Copy calling/called PADDR to AARQ.	*/
/* 01/10/02  EJV    36     Converted to use ASN1R for TRIM7		*/
/* 01/02/02  JRB    35     Converted to use ASN1R (re-entrant ASN1)	*/
/* 10/09/01  JRB    34     Log if unrecognized tag received.		*/
/* 06/22/01  JRB    33     Fix u_copp_rel_cnf_pos & tp4_data_ind	*/
/*			   handling of STATE_RESP_COLL			*/
/*			   state per ISO 8650 (was kluged before).	*/
/* 03/15/01  JRB    32     Use new SMEM allocation functions.		*/
/* 01/02/01  EJV    31     Ported to _AIX				*/
/* 04/12/00  JRB    30     Lint cleanup.				*/
/* 09/13/99  MDE    29     Added SD_CONST modifiers			*/
/* 07/14/99  JRB    28     Add ACSE Password Authentication.		*/
/* 07/14/99  JRB    27     Add functions to get remote NSAP or IP Addr.	*/
/* 08/13/98  JRB    26     Lint cleanup.				*/
/* 08/11/98  JRB    25     BUG_FIX: MOSI: only save user_info if PCI=MMS*/
/* 03/18/98  JRB    24     Use defines (not variables) for ASN1 errors.	*/
/* 11/07/97  JRB    23     Can't use // for comments.			*/
/* 07/13/97  EJV    22     Commented out call to exit() in tp4_except.	*/
/* 05/27/97  JRB   7.00    MMSEASE 7.0 release.				*/
/* 03/19/97  JRB    21     Add MOSI "CALLING" support.			*/
/* 03/19/97  JRB    20     tp4_connect_cnf send AARQ (already encoded).	*/
/*			   Use acse_free_conn to free conn ctrl struct.	*/
/*			   Improve logging.				*/
/*			   Improve release collision handling.		*/
/* 03/07/97  JRB    19     Only pass abort to user if not in IDLE state.*/
/* 03/07/97  JRB    18     Don't call acse_decode unless class==APP.	*/
/* 03/07/97  JRB    17     Use new asn1_skip_elmnt funct instead of	*/
/*			   inline code and "parse_next" calls.		*/
/* 03/07/97  JRB    16     Added MOSI support.				*/
/* 08/12/96  JRB    15     Handle decode error gracefully in		*/
/*			   tp4_data_ind_aarqind & tp4_data_ind_aarqcnf.	*/
/* 07/15/96  JRB    14     Only free acse_conn->aarq_apdu.user_info.ptr	*/
/*			   if len != 0 (wasn't alloc'd otherwise).	*/
/* 07/08/96  JRB    13     Add tp4_except for LEAN_T.			*/
/* 06/25/96  JRB    12     Fix return codes for tp4_data_ind_aarq*	*/
/* 05/02/96  JRB    11     Add STATE_TP4CONN_WAIT.			*/
/* 04/25/96  JRB    10     Set acse_conn->initiator = SD_TRUE in		*/
/*			   tp4_data_ind_aarqcnf (for release collisions)*/
/* 04/18/96  JRB    09     if (acse_conn->state == STATE_AARE_ABANDON)	*/
/*			   in tp4_connect_cnf or tp4_data_ind, call	*/
/*			   tp4_disconnect and free acse_conn.		*/
/* 04/16/96  JRB    08     Copy rcv_data and rcv_data_len to local	*/
/*			   variables in tp4_data_ind for safe freeing.	*/
/* 03/26/96  MDE    07     Added REDUCED_STACK support			*/
/* 03/11/96  JRB    06     Move acse_msgsize to acse2enc.c		*/
/* 03/08/96  JRB    05     Define thisFileName even if !DEBUG_MMS.	*/
/* 03/07/96  JRB    04     Set default for acse_msgsize in case		*/
/*			   a_set_msgsize not called by user.		*/
/* 02/16/96  JRB    03     Clean up asn1_set_dec_err codes.			*/
/* 12/29/95  JRB    02     Broke up tp4_data_ind into subfunctions.	*/
/* 10/30/95  JRB    01     Created					*/
/************************************************************************/
static char *thisFileName = __FILE__;

#include "glbtypes.h"
#include "sysincs.h"
#include "mem_chk.h"
#include "asn1defs.h"
#include "asn1log.h"	/* for ASN.1 decode logging	*/
#include "acseauth.h"
#include "acse2.h"
#if defined (MOSI)
#include "copp_usr.h"
#endif	/* MOSI	*/
#include "tp4api.h"
#include "tp4.h"	/* need MIN_TP0_CONN_ID	definition	*/

/************************************************************************/
/************************************************************************/

static MMS_OBJ_ID *my_obj_id;
static ST_INT32 *my_i32;
static ST_INT16 *my_i16;

static AARQ_APDU aarq_apdu;
static AARE_APDU aare_apdu;
static RLRQ_APDU rlrq_apdu;
static RLRE_APDU rlre_apdu;
static ABRT_APDU abrt_apdu;

static ST_VOID decode_aarq (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_aarq_main (ASN1_DEC_CTXT *aCtx, ST_UINT16 id_code);
static ST_VOID decode_aarq_done (ASN1_DEC_CTXT *aCtx);

static ST_VOID decode_aare (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_aare_main (ASN1_DEC_CTXT *aCtx, ST_UINT16 id_code);
static ST_VOID decode_aare_done (ASN1_DEC_CTXT *aCtx);

static ST_VOID decode_rlrq (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_rlrq_main (ASN1_DEC_CTXT *aCtx, ST_UINT16 id_code);
static ST_VOID decode_rlrq_done (ASN1_DEC_CTXT *aCtx);

static ST_VOID decode_rlre (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_rlre_main (ASN1_DEC_CTXT *aCtx, ST_UINT16 id_code);
static ST_VOID decode_rlre_done (ASN1_DEC_CTXT *aCtx);

static ST_VOID decode_abrt (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_abrt_main (ASN1_DEC_CTXT *aCtx, ST_UINT16 id_code);
static ST_VOID decode_abrt_done (ASN1_DEC_CTXT *aCtx);

static ST_VOID decode_obj_id (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_i32 (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_i16 (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_result_source1 (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_result_source2 (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_acse_done (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_constr_done (ASN1_DEC_CTXT *aCtx);
/* DEBUG: all calls to tp4_reldata could be eliminated if tp4 quits	*/
/* allocating data buffers. This would save a malloc and a memcpy in tp4.*/

static ST_CHAR *a_auth_password_dec (ST_UCHAR *asn1_ptr);
static ST_RET _a_dec_authentication (ACSE_AUTH_INFO *authInfo,		/* out	*/
                                     ST_UCHAR       *auth_value,	/* in	*/
                                     ST_INT          auth_value_len);	/* in	*/


#if defined (MOSI)
ACSE_CONN *decode_acse_conn;	/* connection we're doing decode for.	*/

static ST_VOID END_user_info (ASN1_DEC_CTXT *aCtx);

/************************************************************************/
/*			u_copp_con_cnf					*/
/* P-CONNECT.cnf (Connect Confirm).					*/
/* Parameters:								*/
/*	acse_conn	Pointer to connection info			*/
/*	result		P_CON_RESULT_ACCEPT, P_CON_RESULT_USER_REJ or	*/
/*			P_CON_RESULT_PROVIDER_REJ			*/
/*	reason		Provider-reason (if result=P_CON_RESULT_PROVIDER_REJ)*/
/************************************************************************/
ST_VOID u_copp_con_cnf (ACSE_CONN *acse_conn, ST_INT result, ST_INT reason)
  {
ASN1_DEC_CTXT localDecCtx;	/* For readability, use "aCtx" to access this.*/
ASN1_DEC_CTXT *aCtx = &localDecCtx;

  memset (aCtx, 0, sizeof (ASN1_DEC_CTXT));	/* CRITICAL: start clean	*/

  if (acse_conn->state != STATE_AARE_WAIT)
    {
    ACSELOG_ERR0 ("ACSE-ERROR: Ignoring unexpected P-CONNECT.cnf");
    return;
    }
  if (result == P_CON_RESULT_PROVIDER_REJ)
    {	/* No AARE to decode.	*/
    ACSELOG_DEC2 ("A-ASSOCIATE.cnf-: acse_conn_id =0x%08X  user_conn_id =%4ld",
      acse_conn, acse_conn->user_conn_id);
    ACSELOG_DEC1C ("Rejected by PS-provider. Provider-reason = %d. No P-user-data.",
      reason);

    /* ACSE spec says to pass "A-ASSOCIATE.cnf-" primitive to		*/
    /* ACSE-user, but ACSE-user may not handle it with no AARE info, so	*/
    /* pass "A-P-ABORT.ind" primitive instead.  The result is the same.	*/
    abrt_apdu.source = ACSE_SERVICE_PROVIDER;
    abrt_apdu.user_info.len = 0;
    u_a_abort_ind (acse_conn->user_conn_id, &abrt_apdu);
    acse_conn->state = STATE_IDLE;
    /* DON'T free acse_conn. COSP will free it when T-DISCONNECT done.	*/
    return;
    }

  /* result != P_CON_RESULT_PROVIDER_REJ.  Decode AARE.			*/
  aCtx->asn1r_decode_method = ASN1_TAG_METHOD;			/* Use asn1_tag method for decoding. */
  aCtx->asn1r_decode_done_fun = asn1r_done_err;	/* done function = error fun 	*/
  aCtx->asn1r_err_fun = NULL;			/* set up error detected fun 	*/
  decode_acse_conn = acse_conn;	/* Save in global so asn1r_decode_asn1 (aCtx,	*/
				/* can fill it in.			*/
  
  /* CRITICAL: Init global PDV ptr & len. Changed only if PDV found in msg.*/
  pdv_data_ptr = NULL;
  pdv_data_len = 0;

  ASN1R_TAG_ADD (aCtx, APP|CONSTR,TAG_AARE,decode_aare);
  asn1r_decode_asn1 (aCtx, acse_conn->apdu_ptr,acse_conn->apdu_len); /* decode APDU	*/

  if (aCtx->asn1r_pdu_dec_err == NO_DECODE_ERR)
    {						/* Handle AARE.		*/
    if (aare_apdu.result == 0)
      {
      acse_conn->initiator = SD_TRUE;
      acse_conn->state = STATE_ASSOCIATED;
      ACSELOG_DEC2 ("A-ASSOCIATE.cnf+: acse_conn_id =0x%08X  user_conn_id =%4ld",
        acse_conn, acse_conn->user_conn_id);
      }
    else
      {
      acse_conn->state = STATE_IDLE;
      ACSELOG_DEC2 ("A-ASSOCIATE.cnf-: acse_conn_id =0x%08X  user_conn_id =%4ld",
        acse_conn, acse_conn->user_conn_id);
      }

    /* save partner's security info to the ACSE_CONN for user's anytime examination */
    acse_conn->part_auth_info = aare_apdu.auth_info;
    if (aare_apdu.auth_info.mech_type == ACSE_AUTH_MECH_OTHER)
      {
      /* allocate buffer for the Authentication Value */
      acse_conn->part_auth_info.u.other_auth.auth_value.buf = acse_conn->part_auth_info.u.other_auth.auth_value.ptr =
           (ST_UCHAR *) chk_calloc (aare_apdu.auth_info.u.other_auth.auth_value.len, sizeof(ST_CHAR));
      memcpy (acse_conn->part_auth_info.u.other_auth.auth_value.ptr, aare_apdu.auth_info.u.other_auth.auth_value.ptr,
              aare_apdu.auth_info.u.other_auth.auth_value.len);
      }
    aare_apdu.encrypt_ctrl = acse_conn->encrypt_ctrl;

    u_a_associate_cnf ((ST_LONG) acse_conn, (ST_LONG) acse_conn->user_conn_id,
             &aare_apdu);
    }
  else
    {					/* Handle ASN1 decode error.	*/
    ACSELOG_ERR0 ("ACSE-ERROR: AARE decode failed. Aborting.");
    /* Pass up A-P-ABORT.ind	*/
    abrt_apdu.source = ACSE_SERVICE_PROVIDER;
    abrt_apdu.user_info.len = 0;
    u_a_abort_ind (acse_conn->user_conn_id, &abrt_apdu);

    acse_conn->state = STATE_IDLE;

    /* NOTE: Send copp_u_abort_req ONLY IF COPP accepted conn.		*/
    if (result == P_CON_RESULT_ACCEPT)
      copp_u_abort_req (acse_conn);
    /* CRITICAL: DO NOT access acse_conn after abort. It may have been	*/
    /*     freed by cosp_u_abort_req (called from copp_u_abort_req).	*/
    }
  return;
  }

/************************************************************************/
/*			u_copp_rel_cnf_pos				*/
/* P-RELEASE.cnf+ (POSITIVE Release Confirm).				*/
/* Must be RLRE APDU.  Decode it and call u_a_release_cnf.		*/
/************************************************************************/
ST_VOID u_copp_rel_cnf_pos (ACSE_CONN *acse_conn)
  {
ASN1_DEC_CTXT localDecCtx;	/* For readability, use "aCtx" to access this.*/
ASN1_DEC_CTXT *aCtx = &localDecCtx;

  memset (aCtx, 0, sizeof (ASN1_DEC_CTXT));	/* CRITICAL: start clean	*/

  aCtx->asn1r_decode_method = ASN1_TAG_METHOD;			/* Use asn1_tag method for decoding. */
  aCtx->asn1r_decode_done_fun = asn1r_done_err;	/* done function = error fun 	*/
  aCtx->asn1r_err_fun = NULL;			/* set up error detected fun 	*/
  decode_acse_conn = acse_conn;	/* Save in global so asn1r_decode_asn1 (aCtx,	*/
				/* can fill it in.			*/

  /* CRITICAL: Init global PDV ptr & len. Changed only if PDV found in msg.*/
  pdv_data_ptr = NULL;
  pdv_data_len = 0;

  ASN1R_TAG_ADD (aCtx, APP|CONSTR,TAG_RLRE,decode_rlre);
  asn1r_decode_asn1 (aCtx, acse_conn->apdu_ptr,acse_conn->apdu_len); /* decode APDU	*/

  if (aCtx->asn1r_pdu_dec_err == NO_DECODE_ERR)
    {
    /* Handle RLRE.		*/
    switch (acse_conn->state)
      {
      case STATE_RLRE_WAIT:
      acse_conn->state = STATE_IDLE;
      ACSELOG_DEC2 ("A-RELEASE.cnf+:   acse_conn_id =0x%08X  user_conn_id =%4ld",
        acse_conn, acse_conn->user_conn_id);
      u_a_release_cnf (acse_conn->user_conn_id, &rlre_apdu);
      break;

      case STATE_RESP_COLL:
      acse_conn->state = STATE_ARLSRSP_WAIT;
      ACSELOG_DEC2 ("A-RELEASE.cnf+:   acse_conn_id =0x%08X  user_conn_id =%4ld",
        acse_conn, acse_conn->user_conn_id);
      u_a_release_cnf (acse_conn->user_conn_id, &rlre_apdu);
      break;

      default:
      u_a_except (acse_conn->user_conn_id, EX_ACSE_INVALID_STATE, 
              thisFileName, __LINE__);
      break;
      }	/* end "switch"	*/
    }
  else
    {
    /* Handle ASN1 decode error.	*/
    ACSELOG_ERR0 ("ACSE-ERROR: RLRE decode failed. Aborting.");
    /* Pass up A-P-ABORT.ind	*/
    abrt_apdu.source = ACSE_SERVICE_PROVIDER;
    abrt_apdu.user_info.len = 0;
    u_a_abort_ind (acse_conn->user_conn_id, &abrt_apdu);

    acse_conn->state = STATE_IDLE;
    }
  }


/************************************************************************/
/* u_copp_con_ind							*/
/* P-Connect Indication.						*/
/* Must be AARQ APDU.  Decode it and call u_a_associate_ind.		*/
/************************************************************************/
ST_VOID u_copp_con_ind (ST_LONG user_bind_id, ACSE_CONN *acse_conn)
  {
ASN1_DEC_CTXT localDecCtx;	/* For readability, use "aCtx" to access this.*/
ASN1_DEC_CTXT *aCtx = &localDecCtx;
ST_INT j;

  memset (aCtx, 0, sizeof (ASN1_DEC_CTXT));	/* CRITICAL: start clean	*/

  aCtx->asn1r_decode_method = ASN1_TAG_METHOD;			/* Use asn1_tag method for decoding. */
  aCtx->asn1r_decode_done_fun = asn1r_done_err;	/* done function = error fun 	*/
  aCtx->asn1r_err_fun = NULL;			/* set up error detected fun 	*/
  decode_acse_conn = acse_conn;	/* Save in global so asn1r_decode_asn1 (aCtx,	*/
				/* can fill it in.			*/
  
  /* CRITICAL: Init global PDV ptr & len. Changed only if PDV found in msg.*/
  pdv_data_ptr = NULL;
  pdv_data_len = 0;

  ASN1R_TAG_ADD (aCtx, APP|CONSTR,TAG_AARQ,decode_aarq);
  asn1r_decode_asn1 (aCtx, acse_conn->apdu_ptr,acse_conn->apdu_len); /* decode APDU	*/

  if (aCtx->asn1r_pdu_dec_err == NO_DECODE_ERR)
    {
    /* Handle AARQ.		*/
    acse_conn->state = STATE_AASCRSP_WAIT;

    /* Copy "calling" (remote) address to aarq_apdu.			*/
    if ((aarq_apdu.calling_paddr.psel_len = acse_conn->rem_psel[0])!=0)
      memcpy (aarq_apdu.calling_paddr.psel, &acse_conn->rem_psel[1],
              acse_conn->rem_psel[0]);
    if ((aarq_apdu.calling_paddr.ssel_len = acse_conn->rem_ssel[0])!=0)
      memcpy (aarq_apdu.calling_paddr.ssel, &acse_conn->rem_ssel[1],
              acse_conn->rem_ssel[0]);
    if ((aarq_apdu.calling_paddr.tsel_len = acse_conn->rem_tsel[0])!=0)
      memcpy (aarq_apdu.calling_paddr.tsel, &acse_conn->rem_tsel[1],
              acse_conn->rem_tsel[0]);

    if (acse_conn->tp4_conn_id >= MIN_TP0_CONN_ID)	/* This is TP0 conn. Save IP addr*/
      {
      aarq_apdu.calling_paddr.tp_type = TP_TYPE_TCP;
      aarq_apdu.calling_paddr.netAddr.ip = acse_conn->remNetAddr.ip;
      }
    else				/* This is TP4 conn. Save NSAP	*/
      {
      aarq_apdu.calling_paddr.tp_type = TP_TYPE_TP4;
      if ((aarq_apdu.calling_paddr.nsap_len = acse_conn->remNetAddr.nsap[0])!=0)
        memcpy (aarq_apdu.calling_paddr.netAddr.nsap, &acse_conn->remNetAddr.nsap[1],
                acse_conn->remNetAddr.nsap[0]);
      }

    /* Copy "called" (local) address (except NSAP) to aarq_apdu.	*/
    /* NOTE: "called" tp_type must be same as "calling".	*/
    aarq_apdu.called_paddr.tp_type = aarq_apdu.calling_paddr.tp_type;
    if ((aarq_apdu.called_paddr.psel_len = acse_conn->loc_psel[0])!=0)
      memcpy (aarq_apdu.called_paddr.psel, &acse_conn->loc_psel[1],
              acse_conn->loc_psel[0]);
    if ((aarq_apdu.called_paddr.ssel_len = acse_conn->loc_ssel[0])!=0)
      memcpy (aarq_apdu.called_paddr.ssel, &acse_conn->loc_ssel[1],
              acse_conn->loc_ssel[0]);
    if ((aarq_apdu.called_paddr.tsel_len = acse_conn->loc_tsel[0])!=0)
      memcpy (aarq_apdu.called_paddr.tsel, &acse_conn->loc_tsel[1],
              acse_conn->loc_tsel[0]);

    ACSELOG_DEC1 ("A-ASSOCIATE.ind:  acse_conn_id =0x%08X", acse_conn);
    ACSELOG_DEC0C ("DST (CALLED) ADDRESS:");
    if (aarq_apdu.called_ae_title.AP_title_pres)
      {
      for (j = 0; j < aarq_apdu.called_ae_title.AP_title.num_comps; ++j)
        {			/* Verbose but gets the job done.	*/
        ACSELOG_DEC2C ("  AP_title.comps[%d] = %d",
          j, aarq_apdu.called_ae_title.AP_title.comps[j]);
        }
      }
    if (aarq_apdu.called_ae_title.AE_qual_pres)
      {
      ACSELOG_DEC1C ("  AE_qual = %ld", aarq_apdu.called_ae_title.AE_qual);
      }
    ACSELOG_DEC0C ("  PSEL:");
    ACSELOG_DECH  (aarq_apdu.called_paddr.psel_len, aarq_apdu.called_paddr.psel);
    ACSELOG_DEC0C ("  SSEL:");
    ACSELOG_DECH  (aarq_apdu.called_paddr.ssel_len, aarq_apdu.called_paddr.ssel);
    ACSELOG_DEC0C ("  TSEL:");
    ACSELOG_DECH  (aarq_apdu.called_paddr.tsel_len, aarq_apdu.called_paddr.tsel);

    ACSELOG_DEC0C ("SRC (CALLING) ADDRESS:");
    if (aarq_apdu.calling_ae_title.AP_title_pres)
      {
      for (j = 0; j < aarq_apdu.calling_ae_title.AP_title.num_comps; ++j)
        {			/* Verbose but gets the job done.	*/
        ACSELOG_DEC2C ("  AP_title.comps[%d] = %d",
          j, aarq_apdu.calling_ae_title.AP_title.comps[j]);
        }
      }
    if (aarq_apdu.calling_ae_title.AE_qual_pres)
      {
      ACSELOG_DEC1C ("  AE_qual = %ld", aarq_apdu.calling_ae_title.AE_qual);
      }
    ACSELOG_DEC0C ("  PSEL:");
    ACSELOG_DECH  (aarq_apdu.calling_paddr.psel_len, aarq_apdu.calling_paddr.psel);
    ACSELOG_DEC0C ("  SSEL:");
    ACSELOG_DECH  (aarq_apdu.calling_paddr.ssel_len, aarq_apdu.calling_paddr.ssel);
    ACSELOG_DEC0C ("  TSEL:");
    ACSELOG_DECH  (aarq_apdu.calling_paddr.tsel_len, aarq_apdu.calling_paddr.tsel);
    if (aarq_apdu.calling_paddr.tp_type == TP_TYPE_TCP)
      {
#if defined(TP0_ENABLED)
      struct in_addr sin_addr;	/* inet_ntoa needs this addr format*/
      sin_addr.s_addr = aarq_apdu.calling_paddr.netAddr.ip;
      ACSELOG_DEC1C ("  IP ADDR:  %s", inet_ntoa (sin_addr));
#else
      ACSELOG_ERR0 ("Received TCP conn ind. TCP not supported");
#endif
      }
    else
      {
      ACSELOG_DEC0C ("  NSAP:");
      ACSELOG_DECH  (aarq_apdu.calling_paddr.nsap_len, aarq_apdu.calling_paddr.netAddr.nsap);
      }

    /* save partner's security info to the ACSE_CONN for user's anytime examination */
    acse_conn->part_auth_info = aarq_apdu.auth_info;
    if (aarq_apdu.auth_info.mech_type == ACSE_AUTH_MECH_OTHER)
      {
      /* allocate buffer for the Authentication Value */
      acse_conn->part_auth_info.u.other_auth.auth_value.buf = acse_conn->part_auth_info.u.other_auth.auth_value.ptr =
           (ST_UCHAR *) chk_calloc (aarq_apdu.auth_info.u.other_auth.auth_value.len, sizeof(ST_CHAR));
      memcpy (acse_conn->part_auth_info.u.other_auth.auth_value.ptr, aarq_apdu.auth_info.u.other_auth.auth_value.ptr,
              aarq_apdu.auth_info.u.other_auth.auth_value.len);
      }
    aarq_apdu.encrypt_ctrl = acse_conn->encrypt_ctrl;

    u_a_associate_ind (user_bind_id, (ST_LONG) acse_conn, &aarq_apdu);
    }
  else
    {
    /* Handle ASN1 decode error.  					*/
    /* According to the ACSE spec section 7.3.3.4 (pg 20) we should 	*/
    /* be sending an Abort PDU upon protocol error.			*/
    ACSELOG_ERR0 ("ACSE-ERROR: AARQ decode failed");
    copp_u_abort_req (acse_conn);
    acse_conn->state = STATE_IDLE;
    }
  }

/************************************************************************/
/* u_copp_rel_ind							*/
/* P-Release Indication.						*/
/* Must be RLRQ APDU.  Decode it and call u_a_release_ind.		*/
/************************************************************************/
ST_VOID u_copp_rel_ind (ACSE_CONN *acse_conn)
  {
ASN1_DEC_CTXT localDecCtx;	/* For readability, use "aCtx" to access this.*/
ASN1_DEC_CTXT *aCtx = &localDecCtx;

  memset (aCtx, 0, sizeof (ASN1_DEC_CTXT));	/* CRITICAL: start clean	*/

  aCtx->asn1r_decode_method = ASN1_TAG_METHOD;			/* Use asn1_tag method for decoding. */
  aCtx->asn1r_decode_done_fun = asn1r_done_err;	/* done function = error fun 	*/
  aCtx->asn1r_err_fun = NULL;			/* set up error detected fun 	*/
  decode_acse_conn = acse_conn;	/* Save in global so asn1r_decode_asn1 (aCtx,	*/
				/* can fill it in.			*/

  /* CRITICAL: Init global PDV ptr & len. Changed only if PDV found in msg.*/
  pdv_data_ptr = NULL;
  pdv_data_len = 0;

  ASN1R_TAG_ADD (aCtx, APP|CONSTR,TAG_RLRQ,decode_rlrq);
  asn1r_decode_asn1 (aCtx, acse_conn->apdu_ptr,acse_conn->apdu_len); /* decode APDU	*/

  if (aCtx->asn1r_pdu_dec_err == NO_DECODE_ERR)
    {
    /* Handle RLRQ.		*/
    switch (acse_conn->state)
      {
      case STATE_ASSOCIATED:
      acse_conn->state = STATE_ARLSRSP_WAIT;
      ACSELOG_DEC2 ("A-RELEASE.ind:    acse_conn_id =0x%08X  user_conn_id =%4ld",
        acse_conn, acse_conn->user_conn_id);
      u_a_release_ind (acse_conn->user_conn_id, &rlrq_apdu);
      break;

      case STATE_RLRE_WAIT:
      if (acse_conn->initiator)
        acse_conn->state = STATE_INIT_COLL;
      else
        acse_conn->state = STATE_RESP_COLL;
      ACSELOG_DEC2 ("A-RELEASE.ind:    acse_conn_id =0x%08X  user_conn_id =%4ld",
        acse_conn, acse_conn->user_conn_id);
      u_a_release_ind (acse_conn->user_conn_id, &rlrq_apdu);
      break;

      default:
      u_a_except (acse_conn->user_conn_id, EX_ACSE_INVALID_STATE, 
              thisFileName, __LINE__);
      break;
      }	/* end "switch"	*/
    }
  else
    {
    /* Handle ASN1 decode error.	*/
    ACSELOG_ERR0 ("ACSE-ERROR: RLRQ decode failed");
    }
  }

/************************************************************************/
/* u_copp_p_abort_ind							*/
/* P-P-Abort Indication.						*/
/* ACSE doesn't need to decode anything.  Just pass up A-P-ABORT.ind	*/
/************************************************************************/
ST_VOID u_copp_p_abort_ind (ACSE_CONN *acse_conn, ST_INT reason)
  {
  acse_conn->state = STATE_IDLE;
  ACSELOG_DEC2 ("A-P-ABORT.ind:    acse_conn_id =0x%08X  user_conn_id =%4ld",
    acse_conn, acse_conn->user_conn_id);
  ACSELOG_DEC1C ("Provider-reason = %d", reason);
  /* Pass up A-P-ABORT.ind	*/
  abrt_apdu.source = ACSE_SERVICE_PROVIDER;
  abrt_apdu.user_info.len = 0;
  u_a_abort_ind (acse_conn->user_conn_id, &abrt_apdu);
  }

/************************************************************************/
/* u_copp_u_abort_ind							*/
/* P-U-Abort Indication.						*/
/* Must be ABRT APDU.  Decode it and call u_a_abort_ind.		*/
/************************************************************************/
ST_VOID u_copp_u_abort_ind (ACSE_CONN *acse_conn)
  {
ASN1_DEC_CTXT localDecCtx;	/* For readability, use "aCtx" to access this.*/
ASN1_DEC_CTXT *aCtx = &localDecCtx;

  memset (aCtx, 0, sizeof (ASN1_DEC_CTXT));	/* CRITICAL: start clean	*/

  /* This must be ABRT. Perform ASN1 Decode of ABRT.			*/
  aCtx->asn1r_decode_method = ASN1_TAG_METHOD;			/* Use asn1_tag method for decoding. */
  aCtx->asn1r_decode_done_fun = asn1r_done_err;	/* done function = error fun 	*/
  aCtx->asn1r_err_fun = NULL;			/* set up error detected fun 	*/
  decode_acse_conn = acse_conn;	/* Save in global so asn1r_decode_asn1 (aCtx,	*/
				/* can fill it in.			*/

  /* CRITICAL: Init global PDV ptr & len. Changed only if PDV found in msg.*/
  pdv_data_ptr = NULL;
  pdv_data_len = 0;

  ASN1R_TAG_ADD (aCtx, APP|CONSTR,TAG_ABRT,decode_abrt);
  asn1r_decode_asn1 (aCtx, acse_conn->apdu_ptr,acse_conn->apdu_len); /* decode APDU	*/

  /* "asn1r_decode_asn1 (aCtx," has filled in Global "abrt_apdu" structure.		*/ 

  if (aCtx->asn1r_pdu_dec_err != NO_DECODE_ERR)
    {
    ACSELOG_ERR1 ("ACSE-ERROR: ABRT decode failed (code = %d). Call u_a_abort_ind anyway.",
                  aCtx->asn1r_pdu_dec_err);
    /* Fill "abrt_apdu" with defaults (possibly corrupted during decode).*/
    abrt_apdu.source = ACSE_SERVICE_USER;
    abrt_apdu.user_info.len = 0;
    }

  acse_conn->state = STATE_IDLE;
  ACSELOG_DEC2 ("A-ABORT.ind:      acse_conn_id =0x%08X  user_conn_id =%4ld",
    acse_conn, acse_conn->user_conn_id);
  u_a_abort_ind (acse_conn->user_conn_id, &abrt_apdu);
  }

/************************************************************************/
/* u_copp_data_ind							*/
/* P-Data Indication.							*/
/* ACSE doesn't need to decode anything.  Just call u_a_data_ind.	*/
/************************************************************************/
ST_VOID u_copp_data_ind (ACSE_CONN *acse_conn)
  {
  u_a_data_ind (acse_conn->user_conn_id, acse_conn->apdu_len, acse_conn->apdu_ptr);
  }

#else	/* !MOSI	*/

static ST_INT acse_tag;

static ST_BOOLEAN tp4_data_ind_aarqind (ACSE_CONN *acse_conn, ST_UINT len);
static ST_BOOLEAN tp4_data_ind_aarqcnf (ACSE_CONN *acse_conn, ST_UINT len);
static ST_RET acse_decode (ASN1_DEC_CTXT *aCtx, ST_UCHAR *msg_ptr, ST_UINT len);

/************************************************************************/
/*                      tp4_session_timer_expired			*/
/*----------------------------------------------------------------------*/
/* This function is called by TP4 when the session_timer expires.	*/
/* TRIM-7 does not use any Session timers, so this function will	*/
/* never be called. It's only purpose is to resolve link with LEAN_T.	*/
/* For MOSI, the "tp4_session_timer_expired" function is in COSP????.C	*/
/************************************************************************/
ST_VOID tp4_session_timer_expired (ST_LONG user_conn_id)
  {
  }

/************************************************************************/
/* tp4_bind_cnf								*/
/************************************************************************/
ST_VOID tp4_bind_cnf (ST_LONG user_bind_id, ST_LONG copp_bind_id, ST_RET result)
  {
  ACSELOG_DEC2 ("COPP-Bind   Cnf.  user_bind_id =%9ld copp_bind_id =%9ld",
          user_bind_id, copp_bind_id);
  u_copp_bind_cnf (user_bind_id, copp_bind_id, result);
  }

/************************************************************************/
/* tp4_unbind_cnf							*/
/************************************************************************/
ST_VOID tp4_unbind_cnf (ST_LONG user_bind_id)
  {
  ACSELOG_DEC1 ("COPP-Unbind Cnf.  user_bind_id =%9ld", user_bind_id);
  u_copp_unbind_cnf (user_bind_id);
  }

/************************************************************************/
/* tp4_connect_ind							*/
/* This function is called by the Transport provider when an ACSE	*/
/* Associate request is received.					*/
/************************************************************************/
ST_VOID tp4_connect_ind (
	ST_LONG user_bind_id,
	ST_LONG tp4_conn_id,	/* TP4's connection ID			*/
	TP4_ADDR *rem_tp4_addr,
	ST_INT data_len,
	char *data)
  {
  ACSE_CONN * acse_conn;
  /* This function uses global "aarq_apdu" - Decoded Associate Req Data.*/

  tp4_reldata (data);			/* I never use this.	*/

  acse_conn = (ACSE_CONN *) M_CALLOC (MSMEM_ACSE_CONN, 1, sizeof (ACSE_CONN));

  /* Save TP4's connection ID. Use it in calls to TP4 functions.	*/
  acse_conn->tp4_conn_id = tp4_conn_id;
  /* Save user_bind_id for later passing to u_a_associate_ind		*/
  acse_conn->user_bind_id = user_bind_id;

  tp4_accept (tp4_conn_id, (ST_LONG) acse_conn, 15, "SISCO Transport");
  return;
  }    

/************************************************************************/
/* tp4_connect_cnf							*/
/* This function is called by the Transport provider when a POSITIVE	*/
/* T-CONNECT confirm is received.					*/
/* Now send the AARQ APDU (save_buf) that was built by a_associate_req.	*/
/************************************************************************/
ST_VOID tp4_connect_cnf (
	ST_LONG acse_conn_id,
	ST_LONG tp4_conn_id,	/* TP4's connection ID			*/
	ST_INT data_len,
	char *data)
  {
  ACSE_CONN * acse_conn;
  /* This function uses global "aare_apdu" - Decoded Associate Rsp Data.	*/

  tp4_reldata (data);			/* I never use this.	*/

  acse_conn = (ACSE_CONN *) acse_conn_id;

  if (acse_conn->state == STATE_AARE_ABANDON)
    {
    /* User already aborted. Couldn't wait for cnf (impatient!!)	*/
    tp4_disconnect (tp4_conn_id, 0, NULL);
    acse_free_con (acse_conn);
    return;
    }

  if (acse_conn->state != STATE_TP4CONN_WAIT)
    {
    u_a_except (acse_conn->user_conn_id, EX_ACSE_INVALID_STATE,
                thisFileName, __LINE__);
    acse_free_con (acse_conn);	/* Dump conn tracking struct		*/
    return;
    }
    
  /* Save TP4's connection ID. Use it in calls to TP4 functions.	*/
  acse_conn->tp4_conn_id = tp4_conn_id;

  /* Send saved AARQ APDU (save_buf) via Transport Data request.	*/
  if (tp4_data (acse_conn->tp4_conn_id, 1, (ST_UINT) acse_conn->save_buf.len,
      (ST_CHAR *) acse_conn->save_buf.ptr) != SD_SUCCESS)
    {		/* This should never happen.	*/
    ACSELOG_ERR0 ("ACSE-ERROR: AARQ APDU could not be sent. Unrecoverable");
    }
  /* Free encoded AARQ buffer now. Reset len so know not to free later.	*/
  M_FREE (MSMEM_ACSE_DATA, acse_conn->save_buf.ptr);
  acse_conn->save_buf.len = 0;	/* This indicates "ptr" has been freed.	*/

  acse_conn->state = STATE_AARE_WAIT;	/* Waiting for AARE-apdu	*/
  }    

/************************************************************************/
/* tp4_disconnect_ind							*/
/************************************************************************/
ST_VOID tp4_disconnect_ind (
	ST_LONG acse_conn_id,
	ST_INT reason,
	ST_INT data_len,
	char *data)
  {
  ACSE_CONN * acse_conn;

  tp4_reldata (data);			/* I never use this.	*/

  acse_conn = (ACSE_CONN *) acse_conn_id;

  /* Only pass up abort to user if not already in idle state.	*/
  if (acse_conn->state != STATE_IDLE)
    {
    if (reason == 0)
      {
      ACSELOG_DEC2 ("A-ABORT.ind:      acse_conn_id =0x%08X  user_conn_id =%4ld",
        acse_conn, acse_conn->user_conn_id);
      abrt_apdu.source = ACSE_SERVICE_USER;
      }
    else	
      {
      ACSELOG_DEC2 ("A-P-ABORT.ind:    acse_conn_id =0x%08X  user_conn_id =%4ld",
        acse_conn, acse_conn->user_conn_id);
      abrt_apdu.source = ACSE_SERVICE_PROVIDER;
      }

    abrt_apdu.user_info.len = 0;
    u_a_abort_ind (acse_conn->user_conn_id, &abrt_apdu);
    }
  
  /* In any case, we're done with this connection.			*/
  acse_free_con (acse_conn);	/* Dump conn tracking struct	*/
  return;
  }    

/************************************************************************/
/* tp4_data_ind								*/
/* This function is called by the Transport provider when a data packet	*/
/* is received on a previously established connection.			*/
/* It could be one of the following PDUs:				*/
/*	A-RELEASE.ind							*/
/*	A-RELEASE.cnf							*/
/* DEBUG: MUST call tp4_reldata before returning from this function.	*/
/************************************************************************/
ST_VOID tp4_data_ind (
	ST_LONG acse_conn_id,
	ST_INT eot,
	ST_UINT data_len,
	char *data)
  {
  /* This function uses globals "rlrq_apdu", "rlre_apdu", etc.		*/
  ACSE_CONN * acse_conn;
  ST_BOOLEAN free_flag = SD_FALSE;	/* Flag: does acse_conn need to be freed?*/
  ST_UCHAR *rcv_data;		/* Local copy of data ptr.		*/
  ST_UINT rcv_data_len;		/* Local copy of data len.		*/
  ASN1_DEC_CTXT aLocalCtx;
  ASN1_DEC_CTXT *aCtx = &aLocalCtx;

  acse_conn = (ACSE_CONN *) acse_conn_id;

  if (acse_conn->state == STATE_AARE_ABANDON)
    {
    /* User already aborted. Couldn't wait for cnf (impatient!!)	*/
    tp4_disconnect (acse_conn->tp4_conn_id, 0, NULL);
    acse_free_con (acse_conn);
    return;
    }

  if (eot == 0)
    {	/* NOT complete PDU, so just save data and return.	*/
    if (acse_conn->rcv_data_len == 0)
      acse_conn->rcv_data = (ST_UCHAR *) M_CALLOC (MSMEM_ACSE_DATA, 1, acse_msgsize);
    if (acse_conn->rcv_data_len + data_len > acse_msgsize)
      {
      u_a_except (acse_conn->user_conn_id, EX_ACSE_DECODE, 
                  thisFileName, __LINE__);
      acse_free_con (acse_conn);	/* Dump conn tracking struct		*/
      tp4_reldata (data);
      return;
      }
    memcpy (acse_conn->rcv_data + acse_conn->rcv_data_len, data, data_len);
    acse_conn->rcv_data_len += data_len;
    tp4_reldata (data);
    return;
    }
  else
    {	/* eot != 0	*/
    /* Complete PDU or Last piece of assembled PDU.	*/
    if (acse_conn->rcv_data_len == 0)
      {				/* This is complete PDU		*/
      /* DO NOT ALLOCATE a rcv buffer & DO NOT COPY DATA.	*/
      /* Just set "acse_conn->rcv_data" to point to data.		*/
      /* At end of function, if (acse_conn->rcv_data_len == data_len),	*/
      /* DO NOT FREE "acse_conn->rcv_data".				*/
      acse_conn->rcv_data = (ST_UCHAR *) data;
      }
    else
      {				/* This is last piece of assembled PDU	*/
      memcpy (acse_conn->rcv_data + acse_conn->rcv_data_len, data, data_len);
      }
    acse_conn->rcv_data_len += data_len;	
    }

  /* Save ptr in local variable so it can be freed later.		*/
  rcv_data = acse_conn->rcv_data;

  /* Save len in local variable and reset it so ready for next indication.*/
  rcv_data_len = acse_conn->rcv_data_len;
  acse_conn->rcv_data_len = 0;
  /* WARNING: acse_conn->rcv_data_len must not be used by any functions	*/
  /*          called after this point because it's already been reset.	*/

  /******* HAVE A COMPLETE PDU NOW.  HANDLE ALL POSSIBLE PDUs.	*********/

  if (acse_conn->state == STATE_IDLE)
    {	/* Handle A-Associate indication.				*/
    free_flag = tp4_data_ind_aarqind (acse_conn, rcv_data_len);
    }
  else if (acse_conn->state == STATE_AARE_WAIT)
    {	/* Handle A-Associate confirm.					*/
    free_flag = tp4_data_ind_aarqcnf (acse_conn, rcv_data_len);
    }
  else if ((acse_conn->rcv_data[0] & 0xC0) != APP)	/* chk ASN.1 class*/
    {	/* Handle NON-ACSE PDU.						*/
    /* Pass up to user (i.e. MMS).	*/
    ACSELOG_DEC2 ("A-DATA.ind:       acse_conn_id =0x%08X  user_conn_id =%4ld",
      acse_conn, acse_conn->user_conn_id);
    ACSELOG_DEC1C ("User data length: %d", rcv_data_len);
    u_a_data_ind (acse_conn->user_conn_id, rcv_data_len, acse_conn->rcv_data);
    }
  else if (acse_decode (aCtx, acse_conn->rcv_data, rcv_data_len) == SD_SUCCESS)
    {	/* Handle all other ACSE PDUs.	*/
    switch (acse_tag)		/* acse_tag set by acse_decode above.	*/
      {
      case TAG_RLRQ:
      switch (acse_conn->state)
        {
        case STATE_ASSOCIATED:
        acse_conn->state = STATE_ARLSRSP_WAIT;
        ACSELOG_DEC2 ("A-RELEASE.ind:    acse_conn_id =0x%08X  user_conn_id =%4ld",
          acse_conn, acse_conn->user_conn_id);
        u_a_release_ind (acse_conn->user_conn_id, &rlrq_apdu);
        break;

        case STATE_RLRE_WAIT:
        if (acse_conn->initiator)
          acse_conn->state = STATE_INIT_COLL;
        else
          acse_conn->state = STATE_RESP_COLL;
        u_a_release_ind (acse_conn->user_conn_id, &rlrq_apdu);
        break;

        default:
        u_a_except (acse_conn->user_conn_id, EX_ACSE_INVALID_STATE, 
                thisFileName, __LINE__);
        break;
        }	/* end inner "switch"	*/
      break;

      case TAG_RLRE:
      switch (acse_conn->state)
        {
        case STATE_RLRE_WAIT:
        acse_conn->state = STATE_IDLE;
        ACSELOG_DEC2 ("A-RELEASE.cnf:    acse_conn_id =0x%08X  user_conn_id =%4ld",
          acse_conn, acse_conn->user_conn_id);
        u_a_release_cnf (acse_conn->user_conn_id, &rlre_apdu);
        tp4_disconnect (acse_conn->tp4_conn_id, 0, NULL);
        free_flag = SD_TRUE;	/* conn tracking struct must be freed	*/
        break;

        case STATE_RESP_COLL:
        acse_conn->state = STATE_ARLSRSP_WAIT;
        ACSELOG_DEC2 ("A-RELEASE.cnf:    acse_conn_id =0x%08X  user_conn_id =%4ld",
          acse_conn, acse_conn->user_conn_id);
        u_a_release_cnf (acse_conn->user_conn_id, &rlre_apdu);
        break;

        default:
        u_a_except (acse_conn->user_conn_id, EX_ACSE_INVALID_STATE, 
                 thisFileName, __LINE__);
        break;
        }	/* end inner "switch"	*/
      break;

      default:
      /* Illegal from this ACSE state.					*/
      u_a_except (acse_conn->user_conn_id, EX_ACSE_INVALID_STATE, 
               thisFileName, __LINE__);
      break;
      }	/* end outer "switch"	*/
    }	/* end big "else"	*/

  if (rcv_data_len != data_len)
    M_FREE (MSMEM_ACSE_DATA, rcv_data);
  if (free_flag)		/* Does acse_conn need to be freed ??	*/
    acse_free_con (acse_conn);
  tp4_reldata (data);
  return;
  }  

/************************************************************************/
/* tp4_data_ind_aarqind							*/
/* Subfunction for "tp4_data_ind" to handle AARQ.ind			*/
/* RETURNS:	SD_TRUE (means acse_conn needs to be freed)		*/
/*		SD_FALSE (means acse_conn does NOT need to be freed)	*/
/************************************************************************/
static ST_BOOLEAN tp4_data_ind_aarqind (ACSE_CONN *acse_conn,
	ST_UINT rcv_data_len)
  {
ST_UCHAR *msg_ptr;
ST_UINT len;
ASN1_DEC_CTXT aLocalCtx;
ASN1_DEC_CTXT *aCtx = &aLocalCtx;

  /* Strip off Fastbyte Session and Presentation bytes.			*/
#if !defined(REDUCED_STACK)
  if ((ST_UCHAR) acse_conn->rcv_data [0] == 0xE8  &&
      acse_conn->rcv_data [1] == 0x01)
    {
    msg_ptr = &acse_conn->rcv_data [2];
    len = rcv_data_len-2;
#else
    {
    msg_ptr = acse_conn->rcv_data;
    len = rcv_data_len;
#endif
    /* Decode the AARQ APDU and fill in the AARQ_APDU structure.	*/
    if (acse_decode (aCtx, msg_ptr, len) == SD_SUCCESS)
      {
      if (acse_tag == TAG_AARQ)
        {
        acse_conn->state = STATE_AASCRSP_WAIT;
        ACSELOG_DEC1 ("A-ASSOCIATE.ind:  acse_conn_id =0x%08X", acse_conn);
        u_a_associate_ind (acse_conn->user_bind_id, (ST_LONG) acse_conn, &aarq_apdu);
        return (SD_FALSE);
        }
      }
    }

  ACSELOG_ERR0 ("ACSE-ERROR: AARQ decode failed");
  tp4_disconnect (acse_conn->tp4_conn_id, 0, NULL);
  return (SD_TRUE);
  }

/************************************************************************/
/* tp4_data_ind_aarqcnf							*/
/* Subfunction for "tp4_data_ind" to handle AARQ.cnf			*/
/* RETURNS:	SD_TRUE (means acse_conn needs to be freed)		*/
/*		SD_FALSE (means acse_conn does NOT need to be freed)	*/
/************************************************************************/
static ST_BOOLEAN tp4_data_ind_aarqcnf (ACSE_CONN *acse_conn,
	ST_UINT rcv_data_len)
  {
ST_UCHAR *msg_ptr;
ST_UINT len;
ASN1_DEC_CTXT aLocalCtx;
ASN1_DEC_CTXT *aCtx = &aLocalCtx;

  /* Strip off Fastbyte Session byte.	*/
#if !defined(REDUCED_STACK)
  if ((ST_UCHAR) acse_conn->rcv_data [0] == 0xF0  ||	/* Short-SAC	*/
      (ST_UCHAR) acse_conn->rcv_data [0] == 0xE3  ||	/* Short-SRF, permanent	*/
      (ST_UCHAR) acse_conn->rcv_data [0] == 0xE2)	/* Short-SRF, transient	*/
    {
    /* Strip off Fastbyte Presentation byte.	*/
    if (acse_conn->rcv_data [1] == 0x01)	/* Short-CP	*/
      {
      msg_ptr = &acse_conn->rcv_data [2];
      len = rcv_data_len-2;
#else
    {
      {
      msg_ptr = acse_conn->rcv_data;
      len = rcv_data_len;
#endif
      /* Decode the AARE APDU and fill in the AARE_APDU structure.	*/
      if (acse_decode (aCtx, msg_ptr, len) == SD_SUCCESS)
        {
        if (acse_tag == TAG_AARE)
          {
          ACSELOG_DEC2 ("A-ASSOCIATE.cnf:  acse_conn_id =0x%08X  user_conn_id =%4ld",
            acse_conn, acse_conn->user_conn_id);
          u_a_associate_cnf ((ST_LONG) acse_conn, (ST_LONG) acse_conn->user_conn_id,
             &aare_apdu);
          if (aare_apdu.result == 0)
            {
            acse_conn->initiator = SD_TRUE;
            acse_conn->state = STATE_ASSOCIATED;
            return (SD_FALSE);
            }
          else
            {
            tp4_disconnect (acse_conn->tp4_conn_id, 0, NULL);
            return (SD_TRUE);	/* Only so don't call u_a_except.	*/
            }
          }
        }
      }
    }

  ACSELOG_ERR0 ("ACSE-ERROR: AARE decode failed");
  tp4_disconnect (acse_conn->tp4_conn_id, 0, NULL);
  /* Pass up a Provider Abort Ind.	*/
  abrt_apdu.source = ACSE_SERVICE_PROVIDER;
  abrt_apdu.user_info.len = 0;
  ACSELOG_DEC2 ("A-ABORT.ind:      acse_conn_id =0x%08X  user_conn_id =%4ld",
    acse_conn, acse_conn->user_conn_id);
  u_a_abort_ind (acse_conn->user_conn_id, &abrt_apdu);
  return (SD_TRUE);
  }

/************************************************************************/
/* tp4_expdata_ind								*/
/************************************************************************/
ST_VOID tp4_expdata_ind (
	ST_LONG acse_conn_id,
	ST_UINT data_len,
	char *data)
  {
  /* Treat like normal data.  Assume "eot" = 1.		*/
  tp4_data_ind (acse_conn_id, 1, data_len, data);
  }

/************************************************************************/
/*			acse_decode					*/
/* Function to setup and initiate MMS PDU decode			*/
/* Only fourteen context specific codes are legal at start		*/
/* Input parameters : pointer to message start, length of message,	*/
/* pointer to result buffer.						*/
/************************************************************************/

static ST_RET acse_decode (ASN1_DEC_CTXT *aCtx, ST_UCHAR *msg_ptr, ST_UINT len)
  {
  aCtx->asn1r_decode_method = ASN1_TAG_METHOD;		/* Use asn1_tag method for decoding. 	*/
  ASN1R_TAG_ADD (aCtx, APP|CONSTR,TAG_AARQ,decode_aarq);
  ASN1R_TAG_ADD (aCtx, APP|CONSTR,TAG_AARE,decode_aare);
  ASN1R_TAG_ADD (aCtx, APP|CONSTR,TAG_RLRQ,decode_rlrq);
  ASN1R_TAG_ADD (aCtx, APP|CONSTR,TAG_RLRE,decode_rlre);
  ASN1R_TAG_ADD (aCtx, APP|CONSTR,TAG_ABRT,decode_abrt);

  aCtx->asn1r_decode_done_fun = asn1r_done_err; /* done function = error fun 	*/
  aCtx->asn1r_err_fun = NULL;		   /* set up error detected fun 	*/

/* Call 'asn1r_decode_asn1 (aCtx,' to parse the message.                             */

  asn1r_decode_asn1 (aCtx, msg_ptr,len);		/* do message decode		*/
  if (aCtx->asn1r_pdu_dec_err == NO_DECODE_ERR)
    return (SD_SUCCESS);
  ACSELOG_ERR0 ("ACSE-ERROR: decode of APDU failed");
  return (SD_FAILURE);
  }

#endif	/* !MOSI	*/

/************************************************************************/
/* decode_aarq								*/
/************************************************************************/
static ST_VOID decode_aarq (ASN1_DEC_CTXT *aCtx)
  {
  aCtx->asn1r_decode_method = ASN1_CLASS_METHOD;	/* Use ASN1_CLASS_METHOD method to decode.		*/
  aCtx->asn1r_c_id_fun = decode_aarq_main;
  aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = decode_aarq_done;
  aCtx->asn1r_u_id_fun = asn1r_class_err; 	/* no universals to start		*/
  aCtx->asn1r_a_id_fun = asn1r_class_err; 	/* no applications to start		*/
  aCtx->asn1r_p_id_fun = asn1r_class_err; 	/* no privates to start 		*/

  /* Clean out old stuff from structure.				*/
  memset (&aarq_apdu, 0, sizeof (aarq_apdu));
  }

/************************************************************************/
/* decode_aarq_main								*/
/************************************************************************/
static ST_VOID decode_aarq_main (ASN1_DEC_CTXT *aCtx, ST_UINT16 id_code)
  {
ST_RET ret;
ST_UCHAR bit_str;
MMS_OBJ_ID mechanism_name;
MMS_OBJ_ID maceMechId = MACE_MECH_ID;

  switch (id_code)
    {
    case AARQ_protocol_version:
      if (aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* constructor not allowed	*/
        return;
        }
      /* CRITICAL: asn1r_get_bitstr doesn't set unused bits, so init all bits=0*/
      bit_str = 0;
      asn1r_get_bitstr (aCtx, &bit_str, 8);
      if ((bit_str & BIT_VERSION1) == 0)		/* NOT Version1	*/
        {
        asn1r_set_dec_err (aCtx, ASN1E_INVALID_BITSTR);	/* Illegal ACSE version		*/
        return;
        }
      break;

    case AARQ_ASO_context_name:
      if (!aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must be constructor	*/
        return;
        }
      aCtx->asn1r_decode_method = ASN1_TAG_METHOD;		/* Use asn1_tag method for decoding. */
      aarq_apdu.ASO_context_name_pres = SD_TRUE;
      my_obj_id = &aarq_apdu.ASO_context_name;
      ASN1R_TAG_ADD (aCtx, UNI,OBJ_ID_CODE,decode_obj_id);
      aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = decode_constr_done;
      break;

    case AARQ_CALLED_AP_title:
      if (!aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must be constructor	*/
        return;
        }
      aCtx->asn1r_decode_method = ASN1_TAG_METHOD;		/* Use asn1_tag method for decoding. */
      aarq_apdu.called_ae_title.AP_title_pres = SD_TRUE;
      my_obj_id = &aarq_apdu.called_ae_title.AP_title;
      ASN1R_TAG_ADD (aCtx, UNI,OBJ_ID_CODE,decode_obj_id);
      aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = decode_constr_done;
      break;

    case AARQ_CALLED_AE_qual:
      if (!aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must be constructor	*/
        return;
        }
      aCtx->asn1r_decode_method = ASN1_TAG_METHOD;		/* Use asn1_tag method for decoding. */
      aarq_apdu.called_ae_title.AE_qual_pres = SD_TRUE;
      my_i32 = &aarq_apdu.called_ae_title.AE_qual;
      ASN1R_TAG_ADD (aCtx, UNI,INT_CODE,decode_i32);
      aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = decode_constr_done;
      break;

    case AARQ_CALLED_AP_inv_id:
      if (!aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must be constructor	*/
        return;
        }
      aCtx->asn1r_decode_method = ASN1_TAG_METHOD;		/* Use asn1_tag method for decoding. */
      aarq_apdu.called_ae_title.AP_inv_id_pres = SD_TRUE;
      my_i32 = &aarq_apdu.called_ae_title.AP_inv_id;
      ASN1R_TAG_ADD (aCtx, UNI,INT_CODE,decode_i32);
      aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = decode_constr_done;
      break;

    case AARQ_CALLED_AE_inv_id:
      if (!aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must be constructor	*/
        return;
        }
      aCtx->asn1r_decode_method = ASN1_TAG_METHOD;		/* Use asn1_tag method for decoding. */
      aarq_apdu.called_ae_title.AE_inv_id_pres = SD_TRUE;
      my_i32 = &aarq_apdu.called_ae_title.AE_inv_id;
      ASN1R_TAG_ADD (aCtx, UNI,INT_CODE,decode_i32);
      aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = decode_constr_done;
      break;

    case AARQ_CALLING_AP_title:
      if (!aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must be constructor	*/
        return;
        }
      aCtx->asn1r_decode_method = ASN1_TAG_METHOD;		/* Use asn1_tag method for decoding. */
      aarq_apdu.calling_ae_title.AP_title_pres = SD_TRUE;
      my_obj_id = &aarq_apdu.calling_ae_title.AP_title;
      ASN1R_TAG_ADD (aCtx, UNI,OBJ_ID_CODE,decode_obj_id);
      aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = decode_constr_done;
      break;

    case AARQ_CALLING_AE_qual:
      if (!aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must be constructor	*/
        return;
        }
      aCtx->asn1r_decode_method = ASN1_TAG_METHOD;		/* Use asn1_tag method for decoding. */
      aarq_apdu.calling_ae_title.AE_qual_pres = SD_TRUE;
      my_i32 = &aarq_apdu.calling_ae_title.AE_qual;
      ASN1R_TAG_ADD (aCtx, UNI,INT_CODE,decode_i32);
      aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = decode_constr_done;
      break;

    case AARQ_CALLING_AP_inv_id:
      if (!aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must be constructor	*/
        return;
        }
      aCtx->asn1r_decode_method = ASN1_TAG_METHOD;		/* Use asn1_tag method for decoding. */
      aarq_apdu.calling_ae_title.AP_inv_id_pres = SD_TRUE;
      my_i32 = &aarq_apdu.calling_ae_title.AP_inv_id;
      ASN1R_TAG_ADD (aCtx, UNI,INT_CODE,decode_i32);
      aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = decode_constr_done;
      break;

    case AARQ_CALLING_AE_inv_id:
      if (!aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must be constructor	*/
        return;
        }
      aCtx->asn1r_decode_method = ASN1_TAG_METHOD;		/* Use asn1_tag method for decoding. */
      aarq_apdu.calling_ae_title.AE_inv_id_pres = SD_TRUE;
      my_i32 = &aarq_apdu.calling_ae_title.AE_inv_id;
      ASN1R_TAG_ADD (aCtx, UNI,INT_CODE,decode_i32);
      aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = decode_constr_done;
      break;

    case AARQ_acse_requirements:
      if (aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must NOT be constr*/
        return;
        }
      /* CRITICAL: asn1r_get_bitstr doesn't set unused bits, so init all bits=0*/
      bit_str = 0;
      asn1r_get_bitstr (aCtx, &bit_str, 8);
      /* DEBUG: some stacks incorrectly set the low bit (0x01) in the	*/
      /* bitstring. To be nice, we will let them get away with it.	*/
      if ((bit_str & BIT_AUTHENTICATION) || (bit_str & 0x01))
        aarq_apdu.auth_info.auth_pres = SD_TRUE;
      /* Don't support AP context negotiation, so ignore Bit 1.		*/
      /* We will never set Bit 1 in the response.			*/
      break;

      
    case AARQ_mechanism_name:
      if (aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must NOT be constr*/
        return;
        }
      if (asn1r_get_objid (aCtx, mechanism_name.comps,
                     &mechanism_name.num_comps))
        {
        asn1r_set_dec_err (aCtx, ASN1E_INVALID_BOOLEAN); 
        return;                          
        }
      
      /* Save the mechanism id for the user */
      if (asn1_objidcmp (&mechanism_name, &a_auth_password_obj_id) == 0)
        aarq_apdu.auth_info.mech_type = ACSE_AUTH_MECH_PASSWORD;
      else  
        {
        if (asn1_objidcmp (&mechanism_name, &maceMechId) == 0)
          aarq_apdu.auth_info.mech_type = ACSE_AUTH_MECH_MACE_CERT;
	else
          aarq_apdu.auth_info.mech_type = ACSE_AUTH_MECH_OTHER;
      	memcpy(&aarq_apdu.auth_info.u.other_auth.mech_id, &mechanism_name, sizeof(MMS_OBJ_ID));
      	}
      
      break;

    case AARQ_CALLING_auth_value:
      if (!aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must be constructor	*/
        return;
        }
      
      if (aarq_apdu.auth_info.mech_type == ACSE_AUTH_MECH_OTHER ||
          aarq_apdu.auth_info.mech_type == ACSE_AUTH_MECH_MACE_CERT)
	{
        ret = _a_dec_authentication (&aarq_apdu.auth_info,	/* out	*/
                                     aCtx->asn1r_field_ptr,	/* in	*/
                                     aCtx->asn1r_elmnt_len);	/* in	*/
        if (ret != SD_SUCCESS)
          return;
	}
      else
        strncpy(aarq_apdu.auth_info.u.pw_auth.password, 
        	a_auth_password_dec(aCtx->asn1r_field_ptr), ACSE_MAX_LEN_PASSWORD);
      
      asn1_skip_elmnt (aCtx);	/* Skip over this ASN.1 element.	*/
      break;

    case AARQ_user_info:
      if (!aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must be constructor	*/
        return;
        }
#if defined (MOSI)
      aCtx->asn1r_decode_method = ASN1_TAG_METHOD;		/* Use asn1_tag method for decoding. */
      /* Set the PCI to be expected in PDV-list decode.			*/
      expected_pdv_pci = decode_acse_conn->pcimms;
      ASN1R_TAG_ADD (aCtx, UNI|CONSTR,EXTERN_CODE,START_pdv_list);	/* see copp_dec.c*/
      aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = END_user_info;
#else	/* !MOSI	*/
      /* This is MMS user data. Just pass up for MMS user to decode.	*/
      aarq_apdu.user_info.ptr = aCtx->asn1r_field_ptr;
      aarq_apdu.user_info.len = aCtx->asn1r_elmnt_len;
      asn1_skip_elmnt (aCtx);	/* Skip over this ASN.1 element.	*/
#endif	/* !MOSI	*/
      break;
      
    default:				/* Don't know how to decode.	*/
      ACSELOG_DEC1 ("AARQ unrecognized tag %d. Ignored.", id_code);
      asn1_skip_elmnt (aCtx);	/* Skip over this ASN.1 element.	*/
      break;
    }	/* End "switch (id_code)"	*/
  }

/************************************************************************/
/* decode_aarq_done							*/
/************************************************************************/
static ST_VOID decode_aarq_done (ASN1_DEC_CTXT *aCtx)
  {
#if defined (MOSI)
  if (expected_pdv_pci == decode_acse_conn->pcimms)
    {		/* only set these if this is MMS (not ACSE) data	*/
    aarq_apdu.user_info.ptr = pdv_data_ptr;
    aarq_apdu.user_info.len = pdv_data_len;
    }
#else	/* !MOSI	*/
  acse_tag = TAG_AARQ;
#endif	/* !MOSI	*/
  aCtx->asn1r_decode_done_fun = decode_acse_done;
  }

/************************************************************************/
/* decode_aare								*/
/************************************************************************/
static ST_VOID decode_aare (ASN1_DEC_CTXT *aCtx)
  {
  aCtx->asn1r_decode_method = ASN1_CLASS_METHOD;	/* Use ASN1_CLASS_METHOD method to decode.		*/
  aCtx->asn1r_c_id_fun = decode_aare_main;
  aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = decode_aare_done;
  aCtx->asn1r_u_id_fun = asn1r_class_err; 	/* no universals to start		*/
  aCtx->asn1r_a_id_fun = asn1r_class_err; 	/* no applications to start		*/
  aCtx->asn1r_p_id_fun = asn1r_class_err; 	/* no privates to start 		*/

  /* Clean out old stuff from structure.				*/
  memset (&aare_apdu, 0, sizeof (aare_apdu));
  }

/************************************************************************/
/* decode_aare_main								*/
/************************************************************************/
static ST_VOID decode_aare_main (ASN1_DEC_CTXT *aCtx, ST_UINT16 id_code)
  {
ST_RET ret;
ST_UCHAR bit_str;
MMS_OBJ_ID mechanism_name;
MMS_OBJ_ID maceMechId = MACE_MECH_ID;

  switch (id_code)
    {
    case AARE_protocol_version:
      if (aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* constructor not allowed	*/
        return;
        }
      /* CRITICAL: asn1r_get_bitstr doesn't set unused bits, so init all bits=0*/
      bit_str = 0;
      asn1r_get_bitstr (aCtx, &bit_str, 8);
      if ((bit_str & BIT_VERSION1)==0)		/* NOT Version1	*/
        {
        asn1r_set_dec_err (aCtx, ASN1E_INVALID_BITSTR);	/* Illegal ACSE version		*/
        return;
        }
      break;

    case AARE_ASO_context_name:
      if (!aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must be constructor	*/
        return;
        }
      aCtx->asn1r_decode_method = ASN1_TAG_METHOD;		/* Use asn1_tag method for decoding. */
      aare_apdu.ASO_context_name_pres = SD_TRUE;
      my_obj_id = &aare_apdu.ASO_context_name;
      ASN1R_TAG_ADD (aCtx, UNI,OBJ_ID_CODE,decode_obj_id);
      aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = decode_constr_done;
      break;

    case AARE_result:
      if (!aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must be constructor	*/
        return;
        }
      aCtx->asn1r_decode_method = ASN1_TAG_METHOD;		/* Use asn1_tag method for decoding. */
      my_i16 = &aare_apdu.result;
      ASN1R_TAG_ADD (aCtx, UNI,INT_CODE,decode_i16);
      aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = decode_constr_done;
      break;

    case AARE_result_source_diagnostic:
      if (!aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must be constructor	*/
        return;
        }
      aCtx->asn1r_decode_method = ASN1_TAG_METHOD;		/* Use asn1_tag method for decoding. */
      aare_apdu.result_source_diag_pres = SD_TRUE;
      ASN1R_TAG_ADD (aCtx, CTX|CONSTR,1,decode_result_source1);
      ASN1R_TAG_ADD (aCtx, CTX|CONSTR,2,decode_result_source2);
      aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = decode_constr_done;
      break;

    case AARE_RESPONDING_AP_title:
      if (!aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must be constructor	*/
        return;
        }
      aCtx->asn1r_decode_method = ASN1_TAG_METHOD;		/* Use asn1_tag method for decoding. */
      aare_apdu.responding_ae_title.AP_title_pres = SD_TRUE;
      my_obj_id = &aare_apdu.responding_ae_title.AP_title;
      ASN1R_TAG_ADD (aCtx, UNI,OBJ_ID_CODE,decode_obj_id);
      aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = decode_constr_done;
      break;

    case AARE_RESPONDING_AE_qual:
      if (!aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must be constructor	*/
        return;
        }
      aCtx->asn1r_decode_method = ASN1_TAG_METHOD;		/* Use asn1_tag method for decoding. */
      aare_apdu.responding_ae_title.AE_qual_pres = SD_TRUE;
      my_i32 = &aare_apdu.responding_ae_title.AE_qual;
      ASN1R_TAG_ADD (aCtx, UNI,INT_CODE,decode_i32);
      aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = decode_constr_done;
      break;

    case AARE_RESPONDING_AP_inv_id:
      if (!aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must be constructor	*/
        return;
        }
      aCtx->asn1r_decode_method = ASN1_TAG_METHOD;		/* Use asn1_tag method for decoding. */
      aare_apdu.responding_ae_title.AP_inv_id_pres = SD_TRUE;
      my_i32 = &aare_apdu.responding_ae_title.AP_inv_id;
      ASN1R_TAG_ADD (aCtx, UNI,INT_CODE,decode_i32);
      aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = decode_constr_done;
      break;

    case AARE_RESPONDING_AE_inv_id:
      if (!aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must be constructor	*/
        return;
        }
      aCtx->asn1r_decode_method = ASN1_TAG_METHOD;		/* Use asn1_tag method for decoding. */
      aare_apdu.responding_ae_title.AE_inv_id_pres = SD_TRUE;
      my_i32 = &aare_apdu.responding_ae_title.AE_inv_id;
      ASN1R_TAG_ADD (aCtx, UNI,INT_CODE,decode_i32);
      aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = decode_constr_done;
      break;

    
    case AARE_RESPONDER_acse_requirements:
      if (aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must NOT be constr*/
        return;
        }
      /* CRITICAL: asn1r_get_bitstr doesn't set unused bits, so init all bits=0*/
      bit_str = 0;
      asn1r_get_bitstr (aCtx, &bit_str, 8);
      /* DEBUG: some stacks incorrectly set the low bit (0x01) in the	*/
      /* bitstring. To be nice, we will let them get away with it.	*/
      if ((bit_str & BIT_AUTHENTICATION) || (bit_str & 0x01))
        aare_apdu.auth_info.auth_pres = SD_TRUE;
      /* Don't support AP context negotiation, so ignore Bit 1.		*/
      /* We will never set Bit 1 in the response.			*/
      break;
    
    case AARE_mechanism_name:
      if (aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must NOT be constr*/
        return;
        }
      /* NOTE: this is IMPLICIT objid, so decoding simpler than normal.	*/
      if (asn1r_get_objid (aCtx, mechanism_name.comps, &mechanism_name.num_comps))
        {
        asn1r_set_dec_err (aCtx, ASN1E_INVALID_BOOLEAN); 
        return;                          
        }
      
      /* Save the mechanism id for the user */
      if (asn1_objidcmp (&mechanism_name, &a_auth_password_obj_id) == 0)
        aare_apdu.auth_info.mech_type = ACSE_AUTH_MECH_PASSWORD;
      else  
        {
        if (asn1_objidcmp (&mechanism_name, &maceMechId) == 0)
          aare_apdu.auth_info.mech_type = ACSE_AUTH_MECH_MACE_CERT;
	else
          aare_apdu.auth_info.mech_type = ACSE_AUTH_MECH_OTHER;
      	memcpy(&aare_apdu.auth_info.u.other_auth.mech_id, &mechanism_name, sizeof(MMS_OBJ_ID));
      	}
      
      break;

    case AARE_RESPONDING_auth_value:
      if (!aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must be constructor	*/
        return;
        }
      
      if (aare_apdu.auth_info.mech_type == ACSE_AUTH_MECH_OTHER ||
          aare_apdu.auth_info.mech_type == ACSE_AUTH_MECH_MACE_CERT)
	{
        ret = _a_dec_authentication (&aare_apdu.auth_info,	/* out	*/
                                     aCtx->asn1r_field_ptr,	/* in	*/
                                     aCtx->asn1r_elmnt_len);	/* in	*/
        if (ret != SD_SUCCESS)
          return;
	}
      else
        strncpy(aare_apdu.auth_info.u.pw_auth.password, 
               a_auth_password_dec(aCtx->asn1r_field_ptr), ACSE_MAX_LEN_PASSWORD);
      
      asn1_skip_elmnt (aCtx);	/* Skip over this ASN.1 element.	*/
      break;

    case AARE_user_info:
      if (!aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must be constructor	*/
        return;
        }
#if defined (MOSI)
      aCtx->asn1r_decode_method = ASN1_TAG_METHOD;		/* Use asn1_tag method for decoding. */
      /* Set the PCI to be expected in PDV-list decode.			*/
      expected_pdv_pci = decode_acse_conn->pcimms;
      ASN1R_TAG_ADD (aCtx, UNI|CONSTR,EXTERN_CODE,START_pdv_list);	/* see copp_dec.c*/
      aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = END_user_info;
#else	/* !MOSI	*/
      /* This is MMS user data. Just pass up for MMS user to decode.	*/
      aare_apdu.user_info.ptr = aCtx->asn1r_field_ptr;
      aare_apdu.user_info.len = aCtx->asn1r_elmnt_len;
      asn1_skip_elmnt (aCtx);	/* Skip over this ASN.1 element.	*/
#endif	/* !MOSI	*/
      break;
      
    default:				/* Don't know how to decode.	*/
      ACSELOG_DEC1 ("AARE unrecognized tag %d. Ignored.", id_code);
      asn1_skip_elmnt (aCtx);	/* Skip over this ASN.1 element.	*/
      break;
    }	/* End "switch (id_code)"	*/
  }

/************************************************************************/
/* decode_aare_done							*/
/************************************************************************/
static ST_VOID decode_aare_done (ASN1_DEC_CTXT *aCtx)
  {
#if defined (MOSI)
  if (expected_pdv_pci == decode_acse_conn->pcimms)
    {		/* only set these if this is MMS (not ACSE) data	*/
    aare_apdu.user_info.ptr = pdv_data_ptr;
    aare_apdu.user_info.len = pdv_data_len;
    }
#else	/* !MOSI	*/
  acse_tag = TAG_AARE;
#endif	/* !MOSI	*/
  aCtx->asn1r_decode_done_fun = decode_acse_done;
  }

/************************************************************************/
/* decode_rlrq								*/
/************************************************************************/
static ST_VOID decode_rlrq (ASN1_DEC_CTXT *aCtx)
  {
  aCtx->asn1r_decode_method = ASN1_CLASS_METHOD;	/* Use ASN1_CLASS_METHOD method to decode.		*/
  aCtx->asn1r_c_id_fun = decode_rlrq_main;
  aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = decode_rlrq_done;
  aCtx->asn1r_u_id_fun = asn1r_class_err; 	/* no universals to start		*/
  aCtx->asn1r_a_id_fun = asn1r_class_err; 	/* no applications to start		*/
  aCtx->asn1r_p_id_fun = asn1r_class_err; 	/* no privates to start 		*/

  /* Clean out old stuff from structure.				*/
  memset (&rlrq_apdu, 0, sizeof (rlrq_apdu));
  }

/************************************************************************/
/* decode_rlrq_main								*/
/************************************************************************/
static ST_VOID decode_rlrq_main (ASN1_DEC_CTXT *aCtx, ST_UINT16 id_code)
  {
  switch (id_code)
    {
    case RLRQ_reason:
      if (aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must be primitive	*/
        return;
        }
      rlrq_apdu.reason_pres = SD_TRUE;
      if (asn1r_get_i16 (aCtx, &rlrq_apdu.reason))
        {
        asn1r_set_dec_err (aCtx, ASN1E_INVALID_BOOLEAN); 
        return;                          
        }
      break;

    case RLRQ_user_info:
      if (!aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must be constructor	*/
        return;
        }
#if defined (MOSI)
      aCtx->asn1r_decode_method = ASN1_TAG_METHOD;		/* Use asn1_tag method for decoding. */
      /* Set the PCI to be expected in PDV-list decode.			*/
      expected_pdv_pci = decode_acse_conn->pcimms;
      ASN1R_TAG_ADD (aCtx, UNI|CONSTR,EXTERN_CODE,START_pdv_list);	/* see copp_dec.c*/
      aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = END_user_info;
#else	/* !MOSI	*/
      /* This is MMS user data. Just pass up for MMS user to decode.	*/
      rlrq_apdu.user_info.ptr = aCtx->asn1r_field_ptr;
      rlrq_apdu.user_info.len = aCtx->asn1r_elmnt_len;
      asn1_skip_elmnt (aCtx);	/* Skip over this ASN.1 element.	*/
#endif	/* !MOSI	*/
      break;
      
    default:				/* Don't know how to decode.	*/
      ACSELOG_DEC1 ("RLRQ unrecognized tag %d. Ignored.", id_code);
      asn1_skip_elmnt (aCtx);	/* Skip over this ASN.1 element.	*/
      break;
    }	/* End "switch (id_code)"	*/
  }

/************************************************************************/
/* decode_rlrq_done							*/
/************************************************************************/
static ST_VOID decode_rlrq_done (ASN1_DEC_CTXT *aCtx)
  {
#if defined (MOSI)
  if (expected_pdv_pci == decode_acse_conn->pcimms)
    {		/* only set these if this is MMS (not ACSE) data	*/
    rlrq_apdu.user_info.ptr = pdv_data_ptr;
    rlrq_apdu.user_info.len = pdv_data_len;
    }
#else	/* !MOSI	*/
  acse_tag = TAG_RLRQ;
#endif	/* !MOSI	*/
  aCtx->asn1r_decode_done_fun = decode_acse_done;
  }

/************************************************************************/
/* decode_rlre								*/
/************************************************************************/
static ST_VOID decode_rlre (ASN1_DEC_CTXT *aCtx)
  {
  aCtx->asn1r_decode_method = ASN1_CLASS_METHOD;	/* Use ASN1_CLASS_METHOD method to decode.		*/
  aCtx->asn1r_c_id_fun = decode_rlre_main;
  aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = decode_rlre_done;
  aCtx->asn1r_u_id_fun = asn1r_class_err; 	/* no universals to start		*/
  aCtx->asn1r_a_id_fun = asn1r_class_err; 	/* no applications to start		*/
  aCtx->asn1r_p_id_fun = asn1r_class_err; 	/* no privates to start 		*/

  /* Clean out old stuff from structure.				*/
  memset (&rlre_apdu, 0, sizeof (rlre_apdu));
  }

/************************************************************************/
/* decode_rlre_main								*/
/************************************************************************/
static ST_VOID decode_rlre_main (ASN1_DEC_CTXT *aCtx, ST_UINT16 id_code)
  {
  switch (id_code)
    {
    case RLRE_reason:
      if (aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must be primitive	*/
        return;
        }
      rlre_apdu.reason_pres = SD_TRUE;
      if (asn1r_get_i16 (aCtx, &rlre_apdu.reason))
        {
        asn1r_set_dec_err (aCtx, ASN1E_INVALID_BOOLEAN); 
        return;                          
        }
      break;

    case RLRE_user_info:
      if (!aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must be constructor	*/
        return;
        }
#if defined (MOSI)
      aCtx->asn1r_decode_method = ASN1_TAG_METHOD;		/* Use asn1_tag method for decoding. */
      /* Set the PCI to be expected in PDV-list decode.			*/
      expected_pdv_pci = decode_acse_conn->pcimms;
      ASN1R_TAG_ADD (aCtx, UNI|CONSTR,EXTERN_CODE,START_pdv_list);	/* see copp_dec.c*/
      aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = END_user_info;
#else	/* !MOSI	*/
      /* This is MMS user data. Just pass up for MMS user to decode.	*/
      rlre_apdu.user_info.ptr = aCtx->asn1r_field_ptr;
      rlre_apdu.user_info.len = aCtx->asn1r_elmnt_len;
      asn1_skip_elmnt (aCtx);	/* Skip over this ASN.1 element.	*/
#endif	/* !MOSI	*/
      break;
      
    default:				/* Don't know how to decode.	*/
      ACSELOG_DEC1 ("RLRE unrecognized tag %d. Ignored.", id_code);
      asn1_skip_elmnt (aCtx);	/* Skip over this ASN.1 element.	*/
      break;
    }	/* End "switch (id_code)"	*/
  }

/************************************************************************/
/* decode_rlre_done							*/
/************************************************************************/
static ST_VOID decode_rlre_done (ASN1_DEC_CTXT *aCtx)
  {
#if defined (MOSI)
  if (expected_pdv_pci == decode_acse_conn->pcimms)
    {		/* only set these if this is MMS (not ACSE) data	*/
    rlre_apdu.user_info.ptr = pdv_data_ptr;
    rlre_apdu.user_info.len = pdv_data_len;
    }
#else	/* !MOSI	*/
  acse_tag = TAG_RLRE;
#endif	/* !MOSI	*/
  aCtx->asn1r_decode_done_fun = decode_acse_done;
  }

/************************************************************************/
/* decode_abrt								*/
/************************************************************************/
static ST_VOID decode_abrt (ASN1_DEC_CTXT *aCtx)
  {
  aCtx->asn1r_decode_method = ASN1_CLASS_METHOD;	/* Use ASN1_CLASS_METHOD method to decode.		*/
  aCtx->asn1r_c_id_fun = decode_abrt_main;
  aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = decode_abrt_done;
  aCtx->asn1r_u_id_fun = asn1r_class_err; 	/* no universals to start		*/
  aCtx->asn1r_a_id_fun = asn1r_class_err; 	/* no applications to start		*/
  aCtx->asn1r_p_id_fun = asn1r_class_err; 	/* no privates to start 		*/

  /* Clean out old stuff from structure.				*/
  memset (&abrt_apdu, 0, sizeof (abrt_apdu));
  abrt_apdu.source = -1;	/* So can verify that gets set by decode*/
  }

/************************************************************************/
/* decode_abrt_main								*/
/************************************************************************/
static ST_VOID decode_abrt_main (ASN1_DEC_CTXT *aCtx, ST_UINT16 id_code)
  {
  switch (id_code)
    {
    case ABRT_source:
      if (aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must be primitive	*/
        return;
        }
      if (asn1r_get_i16 (aCtx, &abrt_apdu.source))
        {
        asn1r_set_dec_err (aCtx, ASN1E_INVALID_BOOLEAN); 
        return;                          
        }
      break;

    case ABRT_diagnostic:
      if (aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must be primitive	*/
        return;
        }
      if (asn1r_get_i16 (aCtx, &abrt_apdu.diagnostic))
        {
        asn1r_set_dec_err (aCtx, ASN1E_INVALID_BOOLEAN); 
        return;                          
        }
      else
        abrt_apdu.diagnostic_pres = SD_TRUE;
      break;

    case ABRT_user_info:
      if (!aCtx->asn1r_constr_elmnt)
        {
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM);	/* Must be constructor	*/
        return;
        }
#if defined (MOSI)
      aCtx->asn1r_decode_method = ASN1_TAG_METHOD;		/* Use asn1_tag method for decoding. */
      /* Set the PCI to be expected in PDV-list decode.			*/
      expected_pdv_pci = decode_acse_conn->pcimms;
      ASN1R_TAG_ADD (aCtx, UNI|CONSTR,EXTERN_CODE,START_pdv_list);	/* see copp_dec.c*/
      aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = END_user_info;
#else	/* !MOSI	*/
      /* This is MMS user data. Just pass up for MMS user to decode.	*/
      abrt_apdu.user_info.ptr = aCtx->asn1r_field_ptr;
      abrt_apdu.user_info.len = aCtx->asn1r_elmnt_len;
      asn1_skip_elmnt (aCtx);	/* Skip over this ASN.1 element.	*/
#endif	/* !MOSI	*/
      break;
      
    default:				/* Don't know how to decode.	*/
      ACSELOG_DEC1 ("ABRT unrecognized tag %d. Ignored.", id_code);
      asn1_skip_elmnt (aCtx);	/* Skip over this ASN.1 element.	*/
      break;
    }	/* End "switch (id_code)"	*/
  }

/************************************************************************/
/* decode_abrt_done							*/
/************************************************************************/
static ST_VOID decode_abrt_done (ASN1_DEC_CTXT *aCtx)
  {
  if (abrt_apdu.source == -1)
    {
    asn1r_set_dec_err (aCtx, ASN1E_END_OF_MESSAGE);	/* Did not contain MANDATORY "source".	*/
    return;
    }
#if defined (MOSI)
  if (expected_pdv_pci == decode_acse_conn->pcimms)
    {		/* only set these if this is MMS (not ACSE) data	*/
    abrt_apdu.user_info.ptr = pdv_data_ptr;
    abrt_apdu.user_info.len = pdv_data_len;
    }
#else	/* !MOSI	*/
  acse_tag = TAG_ABRT;
#endif	/* !MOSI	*/
  aCtx->asn1r_decode_done_fun = decode_acse_done;
  }

/************************************************************************/
/* decode_obj_id								*/
/************************************************************************/
static ST_VOID decode_obj_id (ASN1_DEC_CTXT *aCtx)
  {
  if (asn1r_get_objid (aCtx, my_obj_id->comps,&my_obj_id->num_comps))
    {
    asn1r_set_dec_err (aCtx, ASN1E_INVALID_BOOLEAN); 
    return;                          
    }
  /* Go back to ASN1_CLASS_METHOD mode. "aCtx->asn1r_c_id_fun" should still = "decode_????_main"*/
  aCtx->asn1r_decode_method = ASN1_CLASS_METHOD;
  return;
  }
  
/************************************************************************/
/* decode_i32								*/
/************************************************************************/
static ST_VOID decode_i32 (ASN1_DEC_CTXT *aCtx)
  {
  if (asn1r_get_i32 (aCtx, my_i32))
    {
    asn1r_set_dec_err (aCtx, ASN1E_INVALID_BOOLEAN); 
    return;                          
    }
  /* Go back to ASN1_CLASS_METHOD mode. "aCtx->asn1r_c_id_fun" should still = "decode_????_main"*/
  aCtx->asn1r_decode_method = ASN1_CLASS_METHOD;
  return;
  }
  
/************************************************************************/
/* decode_i16								*/
/************************************************************************/
static ST_VOID decode_i16 (ASN1_DEC_CTXT *aCtx)
  {
  if (asn1r_get_i16 (aCtx, my_i16))
    {
    asn1r_set_dec_err (aCtx, ASN1E_INVALID_BOOLEAN); 
    return;                          
    }
  /* Go back to ASN1_CLASS_METHOD mode. "aCtx->asn1r_c_id_fun" should still = "decode_????_main"*/
  aCtx->asn1r_decode_method = ASN1_CLASS_METHOD;
  return;
  }
  
/************************************************************************/
/* decode_result_source1						*/
/************************************************************************/
static ST_VOID decode_result_source1 (ASN1_DEC_CTXT *aCtx)
  {
  aare_apdu.result_source = 1;

  my_i16 = &aare_apdu.result_diag;
  ASN1R_TAG_ADD (aCtx, UNI,INT_CODE,decode_i16);
  aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = decode_constr_done;
  
  return;
  }
  
/************************************************************************/
/* decode_result_source2						*/
/************************************************************************/
static ST_VOID decode_result_source2 (ASN1_DEC_CTXT *aCtx)
  {
  aare_apdu.result_source = 2;

  my_i16 = &aare_apdu.result_diag;
  ASN1R_TAG_ADD (aCtx, UNI,INT_CODE,decode_i16);
  aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = decode_constr_done;
  
  return;
  }
  
/************************************************************************/
/* decode_acse_done							*/
/************************************************************************/
static ST_VOID decode_acse_done (ASN1_DEC_CTXT *aCtx)
  {
  return;
  }

/************************************************************************/
/* decode_constr_done							*/
/************************************************************************/
static ST_VOID decode_constr_done (ASN1_DEC_CTXT *aCtx)
  {
  return;
  }

/************************************************************************/
/*			asn1_skip_elmnt					*/
/* Skip over current ASN.1 element without decoding.			*/
/************************************************************************/
ST_VOID asn1_skip_elmnt (ASN1_DEC_CTXT *aCtx)
  {
  /* This function can't handle indefinite length encoding.		*/
  /* Only possible for constr, but let's chk here to be extra paranoid.	*/
  if (aCtx->asn1r_indef_flag)
    {
    /* NOTE: if this ever happens, chg code to use asn1r_parse_next.	*/
    ACSELOG_ERR0 ("asn1_skip_elmnt: indefinite length encoding not supported");
    asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_FORM); 
    return;                          
    }
  if (aCtx->asn1r_constr_elmnt)
    {
    aCtx->asn1r_constr_elmnt = 0;	/* Make ASN.1 treat it like primitive.	*/
    --aCtx->asn1r_msg_level;	/* Already incremented for constructor	*/
    }			/* so decrement to act like primitive.	*/
  aCtx->asn1r_field_ptr += aCtx->asn1r_elmnt_len;
  }

#if defined (MOSI)
/************************************************************************/
/* END_user_info						*/
/************************************************************************/
static ST_VOID END_user_info (ASN1_DEC_CTXT *aCtx)
  {
  }
#endif	/* MOSI	*/

#ifdef LEAN_T
/************************************************************************/
/* tp4_except								*/
/************************************************************************/
ST_VOID tp4_except (
	ST_CHAR *filename,		/* Source code file name		*/
	ST_INT line)		/* source code line number		*/
  {
  /* DEBUG: need better way to deal with all exceptions.		*/
  /* How about one exception function, pass component name and errcode	*/
  ACSELOG_ERR2 ("ERROR: TP4 exception:  File = %s, Line = %d", filename, line);
  /* DEBUG: create new errcode, or SKIP IT and use only filename/line??	*/
  u_a_except (-1L, EX_ACSE_DECODE, filename, line);
  }
#endif	/* LEAN_T	*/


/************************************************************************/
/*			a_auth_password_dec				*/
/* Authentication password decode function.				*/
/* RETURN: pointer to static NULL terminated string containing password.*/
/*         NULL if decode fails.					*/
/************************************************************************/
static ST_CHAR *a_auth_password_dec (ST_UCHAR *asn1_ptr)
  {
static ST_CHAR password [ACSE_MAX_LEN_PASSWORD + 1];
ST_UINT password_len;
ST_CHAR *ret_ptr = NULL;	/* assume error	*/

  if (asn1_ptr [0] == (CTX|0))	/* Tag 0 - GraphicString	*/
    {
    password_len = asn1_ptr[1];
    if (password_len <= ACSE_MAX_LEN_PASSWORD)
      {
      memcpy (password, &asn1_ptr [2], password_len);
      password [password_len] = 0;	/* NULL terminate	*/
      ret_ptr = password;	/* only valid return value	*/
      }
    }
  return (ret_ptr);
  }

#if defined (TP4_ENABLED)
/************************************************************************/
/*			a_get_rem_nsap					*/
/* RETURN: pointer to NSAP. First byte is length.			*/
/************************************************************************/
#include "tp4.h"			/* Need internal TP4 defines	*/
ST_UCHAR *a_get_rem_nsap (ST_LONG acse_conn_id)
  {
ACSE_CONN *acse_conn;
ST_LONG tp_conn_id;
TP_CONN *tp_conn;

  acse_conn = (ACSE_CONN *) acse_conn_id;
  tp_conn_id = acse_conn->tp4_conn_id;
  if (tp_conn_id < 0  ||  tp_conn_id >= tp_cfg.max_num_conns)
    return (NULL);	/* Invalid conn_id (could be TP0 conn id	*/
			/* which starts at MIN_TP0_CONN_ID).		*/
  tp_conn = &tp_conn_arr [tp_conn_id];
  return (tp_conn->rem_nsap);
  }
#endif	/* defined (TP4_ENABLED)	*/

#if defined (TP0_ENABLED)
/************************************************************************/
/*			a_get_rem_ip_addr				*/
/* This function returns the remote IP Address as an unsigned long in	*/
/* "network byte order", just like the "standard sockets" function	*/
/* "inet_addr" does. If there is an error, it returns			*/
/* "htonl (INADDR_NONE)", just like "inet_addr" does.			*/
/*   The return value can be stored in the appropriate union member	*/
/* in the structure "in_addr", which can be passed to "inet_ntoa".	*/
/************************************************************************/
#include "tp4.h"			/* Need internal TP4 defines	*/
#include "tp0_sock.h"			/* Need "sockets" defines	*/
ST_ULONG a_get_rem_ip_addr (ST_LONG acse_conn_id)
  {
ACSE_CONN *acse_conn;
ST_LONG tp_conn_id;
TP0_CONN *tp0_conn;
ST_INT ret;
SOCKADDR_IN sockaddr_in;
SOCK_ADDRLEN addr_len;

  acse_conn = (ACSE_CONN *) acse_conn_id;
  tp_conn_id = acse_conn->tp4_conn_id;
  if (tp_conn_id >= MIN_TP0_CONN_ID  &&
      tp_conn_id < tp0_cfg.max_num_conns + MIN_TP0_CONN_ID)
    {				/* Conn id is a legal TP0 conn id	*/
    tp0_conn = &tp0_conn_arr [tp_conn_id - MIN_TP0_CONN_ID];

    addr_len = sizeof (SOCKADDR_IN);	/* CRITICAL: set to expected len.*/
    ret = getpeername (tp0_conn->sock_info->hSock, (SOCKADDR *) &sockaddr_in, &addr_len); 
    if (ret == 0)
      return (sockaddr_in.sin_addr.s_addr);
    }
   
  return (htonl (INADDR_NONE));		/* something failed	*/
  }
#endif	/* defined (TP0_ENABLED)	*/


	/************************************************************************/
	/*	NOTE: Copied from marb_rx.c, if any changes are required	*/
	/*	      consider making them also in marb_rx.c file!		*/
	/************************************************************************/

static ST_VOID _a_dec_auth_value_external (ASN1_DEC_CTXT *aCtx);
static ST_VOID _a_dec_external_singleAsn1Type (ASN1_DEC_CTXT *aCtx);
static ST_VOID _a_dec_external_singleAsn1Type_done (ASN1_DEC_CTXT *aCtx);
static ST_VOID _a_dec_auth_value_external_done (ASN1_DEC_CTXT *aCtx);
static ST_VOID _a_dec_auth_value_graphicString (ASN1_DEC_CTXT *aCtx);
static ST_VOID _a_dec_auth_done (ASN1_DEC_CTXT *aCtx);

/********************************************************************************/
/*			_a_dec_authentication					*/
/*------------------------------------------------------------------------------*/
/* Decodes Authentication info. The buffer needed to hold authentication info	*/
/* is allocated in this	function and should be released after connection	*/
/* terminates.									*/
/* Parameters:									*/
/*   ACSE_AUTH_INFO    *authInfo	pointer to the decoded authInfo		*/
/*   ST_CHAR	       *auth_value	ptr to encoded authentication value	*/
/*   ST_INT             auth_value_len	length of the authentication encoding	*/
/* Return:									*/
/*   ST_RET		SD_SUCCESS or SD_FAILURE				*/
/********************************************************************************/

static ST_RET _a_dec_authentication (ACSE_AUTH_INFO *authInfo,		/* out	*/
                                     ST_UCHAR        *auth_value,	/* in	*/
                                     ST_INT          auth_value_len)	/* in	*/

{
ASN1_DEC_CTXT   localDecCtx;	/* For readability, use "aCtx" to access this.*/
ASN1_DEC_CTXT  *aCtx = &localDecCtx;

  ALOG_DEC0 ("Decoding Authentication");
  memset (aCtx, 0, sizeof (ASN1_DEC_CTXT));	/* CRITICAL: start clean*/

  /* Get ptr to association indication information.	     		*/
  authInfo->auth_pres = SD_FALSE;	/* set in case we fail		*/

  if (auth_value_len <= 0)
    {
    ACSELOG_ERR1 ("_a_dec_authentication: invalid authentication len=%d", auth_value_len);
    return (SD_FAILURE);
    }

  if (authInfo->mech_type == ACSE_AUTH_MECH_PASSWORD)
    ASN1R_TAG_ADD (aCtx, CTX, 0, _a_dec_auth_value_graphicString);
  else
    ASN1R_TAG_ADD (aCtx, CTX|CONSTR, 2, _a_dec_auth_value_external);

  /* decode the authentication value */
  aCtx->asn1r_decode_method = ASN1_TAG_METHOD;	/* Use asn1_tag method for decoding. 	*/

  aCtx->usr_info[0] = authInfo;		/* need to be set by dec funcs	*/

  aCtx->asn1r_decode_done_fun = asn1r_done_err; /* done function = error fun 	*/
  aCtx->asn1r_err_fun = NULL;		   /* set up error detected fun 	*/

  /* Call function to parse the message	*/
  asn1r_decode_asn1 (aCtx, auth_value, auth_value_len);

  if (aCtx->asn1r_pdu_dec_err == NO_DECODE_ERR)
    {
    /* decoding of authentication successful */
    authInfo->auth_pres = SD_TRUE;
    return (SD_SUCCESS);
    }
    
  return (SD_FAILURE);
  }

/************************************************************************/
/*		_a_dec_auth_value_external				*/
/************************************************************************/

static ST_VOID _a_dec_auth_value_external (ASN1_DEC_CTXT *aCtx)
  {
  ALOG_CDEC0 ("_a_dec_auth_value_external");

/* We need to see the Single Asn1 Type constructor */
  ASN1R_TAG_ADD (aCtx, CTX|CONSTR, 0, _a_dec_external_singleAsn1Type);
  }


/************************************************************************/
/*		_a_dec_external_singleAsn1Type				*/
/************************************************************************/

static ST_VOID _a_dec_external_singleAsn1Type (ASN1_DEC_CTXT *aCtx)
  {
  ALOG_CDEC0 ("_a_dec_external_singleAsn1Type");

/* OK, we are at the start of the data ... just record the position 	*/
  aCtx->usr_info[1] = ASN1_DEC_PTR(aCtx);

  asn1r_parse_next (aCtx, _a_dec_external_singleAsn1Type_done); /* parse entire element */
  }


/************************************************************************/
/* 		_a_dec_external_singleAsn1Type_done			*/
/************************************************************************/

static ST_VOID _a_dec_external_singleAsn1Type_done (ASN1_DEC_CTXT *aCtx)
  {
ACSE_AUTH_INFO *authInfo = (ACSE_AUTH_INFO *) aCtx->usr_info[0];
ST_UCHAR *data_start;
ST_INT data_len;

  ALOG_CDEC0 ("_a_dec_external_singleAsn1Type_done");

  data_start = (ST_UCHAR *) aCtx->usr_info[1];
  data_len = aCtx->asn1r_octetcount;

  authInfo->u.other_auth.auth_value.len = data_len;
  authInfo->u.other_auth.auth_value.buf = authInfo->u.other_auth.auth_value.ptr =
                 (ST_UCHAR *) chk_calloc (data_len, sizeof(ST_CHAR));
  memcpy (authInfo->u.other_auth.auth_value.ptr, data_start, data_len);

  aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = _a_dec_auth_value_external_done;
  }

/************************************************************************/
/* 		_a_dec_auth_value_external_done				*/
/************************************************************************/

static ST_VOID _a_dec_auth_value_external_done (ASN1_DEC_CTXT *aCtx)
  {
  ALOG_CDEC0 ("_a_dec_auth_value_external_done");
  aCtx->asn1r_decode_done_fun = _a_dec_auth_done;
  aCtx->asn1r_decode_done = SD_TRUE;
  }


/************************************************************************/
/* 		_a_dec_auth_value_graphicString				*/
/************************************************************************/

static ST_VOID _a_dec_auth_value_graphicString (ASN1_DEC_CTXT *aCtx)
  {
ACSE_AUTH_INFO *authInfo = (ACSE_AUTH_INFO *) aCtx->usr_info[0];
ST_INT          password_len;

  ALOG_CDEC0 ("_a_dec_auth_value_graphicString");

/* OK, here we have the data we need */
  password_len = ASN1_DEC_LEN(aCtx);
  if (password_len <= ACSE_MAX_LEN_PASSWORD)
    {
    memcpy (authInfo->u.pw_auth.password, ASN1_DEC_PTR(aCtx), password_len);
    authInfo->u.pw_auth.password[password_len] = 0; /* NULL terminate */
    aCtx->asn1r_decode_done_fun = _a_dec_auth_done;
    }
  else
    {
    ACSELOG_ERR1 ("_a_dec_auth_value: password too long (%d bytes)", password_len);
    authInfo->u.pw_auth.password[0] = 0;	/* NULL password	*/
    asn1r_set_dec_err (aCtx, ASN1E_INVALID_LENGTH);
    }
  aCtx->asn1r_decode_done = SD_TRUE;
  }

/************************************************************************/
/*			_a_dec_auth_done				*/
/************************************************************************/

static ST_VOID _a_dec_auth_done (ASN1_DEC_CTXT *aCtx)
  {
  ALOG_CDEC0 ("_a_dec_auth_done");
  }

