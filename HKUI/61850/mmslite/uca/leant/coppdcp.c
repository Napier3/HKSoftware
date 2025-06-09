/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*	(c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*	1997-2002, All Rights Reserved					*/
/*									*/
/*			PROPRIETARY AND CONFIDENTIAL			*/
/*									*/
/* MODULE NAME : coppdcp.c						*/
/* PRODUCT(S)  : MOSI Stack (over TP4)					*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/*		This file implements decoding of CP and CPA PPDUs.	*/
/*									*/
/*  For information see the:						*/
/*	ISO 8822 "Information processing systems - Open Systems		*/
/*	  Interconnection - Connection oriented presentation service	*/
/*	  definition.							*/
/*	ISO 8823 "Information processing systems - Open Systems		*/
/*	  Interconnection - Connection oriented presentation protocol	*/
/*	  specification.						*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*									*/
/*			u_cosp_con_ind 					*/
/*			u_cosp_con_cnf_pos				*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 01/30/06  GLB    13     Integrated porting changes for VMS           */
/* 08/01/03  JRB    12     Elim compiler warning.			*/
/* 06/24/03  JRB    11     Init psels before decode to avoid crash	*/
/*			   when sender does not send psels.		*/
/* 03/31/03  JRB    10     asn1r_get_bitstr: add max_bits arg.		*/
/* 01/02/02  JRB    09     Converted to use ASN1R (re-entrant ASN1)	*/
/* 10/10/01  JRB    08     asn1_skip_elmnt doesn't work for indef len	*/
/*			   encoding. Use "parse_next" instead.		*/
/* 05/09/01  JRB    07     On P-CONNECT.ind, save PSELs in ACSE_CONN.	*/
/* 02/02/99  JRB    06     BUG FIX: Decode "prov_reas" in "Result-list"	*/
/*			   even if no TSN (see decode_result).		*/
/* 03/18/98  JRB    05     Use defines (not variables) for ASN1 errors.	*/
/* 02/20/98  JRB    04     Chg abort_reason & event_id to ST_INT8.	*/
/* 12/22/97  JRB    03     Use ST_INT8.					*/
/* 05/27/97  JRB   7.00    MMSEASE 7.0 release.				*/
/* 03/19/97  JRB    02     Add "CALLING" support.  General cleanup.	*/
/* 02/27/97  JRB    01     Created					*/
/************************************************************************/
#ifdef DEBUG_SISCO
static char *thisFileName = __FILE__;
#endif

#include "glbtypes.h"
#include "sysincs.h"
#include "mem_chk.h"
#include "asn1defs.h"
#include "acse2.h"

#include "copp.h"
#include "cosp_usr.h"

/************************************************************************/
/* Global Variables							*/
/************************************************************************/
/* Structure for tracking this decode.		*/
typedef struct
  {
#define PPDU_TYPE_CP	0	/* This is a CP  PPDU.			*/
#define PPDU_TYPE_CPA	1	/* This is a CPA PPDU.			*/
  ST_INT ppdu_type;		/* PPDU_TYPE_CP or PPDU_TYPE_CPA	*/
  ST_UCHAR version_bit_str;
  ST_UCHAR *calling_psel;
  ST_UCHAR *called_psel;
  ST_UCHAR *responding_psel;
  ST_INT num_ctxt;
  ST_BOOLEAN bad_pc_deflist;	/* SD_TRUE if anything we don't like in pc_deflist*/
  ST_BOOLEAN def_ctxt_proposed;
  ST_INT8 mode;
  ST_BOOLEAN pres_req_present;
  ST_UCHAR pres_req [1];
  ST_BOOLEAN user_ses_req_present;
  ST_UCHAR user_sess_req [2];
  } DECODE_CP;
static DECODE_CP decode_cp;
static ST_INT8 pci;		/* PCI rcvd in P-context-def-list	*/  
static ST_UCHAR empty_psel [1] = {0};	/* first byte (len) = 0	*/

static ST_VOID START_p_cp (ASN1_DEC_CTXT *aCtx);
static ST_VOID START_mode (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_mode2 (ASN1_DEC_CTXT *aCtx);
static ST_VOID END_mode (ASN1_DEC_CTXT *aCtx);
static ST_VOID START_p_cp_sequence (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_version (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_calling_psel (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_called_psel (ASN1_DEC_CTXT *aCtx);
static ST_VOID START_pc_deflist (ASN1_DEC_CTXT *aCtx);
static ST_VOID START_context (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_pci (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_asn (ASN1_DEC_CTXT *aCtx);
static ST_VOID START_tsn_list (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_tsn (ASN1_DEC_CTXT *aCtx);
static ST_VOID END_tsn_list (ASN1_DEC_CTXT *aCtx);
static ST_VOID END_context (ASN1_DEC_CTXT *aCtx);
static ST_VOID END_pc_deflist (ASN1_DEC_CTXT *aCtx);
static ST_VOID START_def_ctxt_name (ASN1_DEC_CTXT *aCtx);
static ST_VOID parse_next_done (ASN1_DEC_CTXT *aCtx);
static ST_VOID END_def_ctxt_name (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_pres_req (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_user_sess_req (ASN1_DEC_CTXT *aCtx);
static ST_VOID END_p_cp_sequence (ASN1_DEC_CTXT *aCtx);
static ST_VOID END_p_cp (ASN1_DEC_CTXT *aCtx);

/* Functions used only for CPA decode		*/
static ST_VOID decode_responding_psel (ASN1_DEC_CTXT *aCtx);
static ST_VOID START_pc_def_result_list (ASN1_DEC_CTXT *aCtx);
static ST_VOID START_result_seq (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_result (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_tsn2 (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_result_list_prov_reas (ASN1_DEC_CTXT *aCtx);
static ST_VOID END_result_seq (ASN1_DEC_CTXT *aCtx);
static ST_VOID END_pc_def_result_list (ASN1_DEC_CTXT *aCtx);

#if !defined (CALLING_ONLY)
/************************************************************************/
/*			u_cosp_con_ind					*/
/*----------------------------------------------------------------------*/
/* This USER function is called by the SS-Provider to indicate that a	*/
/* remote node wishes to establish a connection.			*/
/* 									*/
/* Parameters:								*/
/*  ST_LONG	 user_bind_id		SS-User's id for this binding.	*/
/*  ACSE_CONN	*con			Pointer to connection info	*/
/*	  								*/
/* Return:								*/
/*	ST_VOID								*/
/************************************************************************/
ST_VOID u_cosp_con_ind (ST_LONG user_bind_id, ACSE_CONN *acse_conn)
  {
ST_INT8 abort_reason;
ST_INT8 event_id;
ASN1_DEC_CTXT localDecCtx;	/* For readability, use "aCtx" to access this.*/
ASN1_DEC_CTXT *aCtx = &localDecCtx;

  memset (aCtx, 0, sizeof (ASN1_DEC_CTXT));	/* CRITICAL: start clean	*/

  if (acse_conn->copp_state != COPP_STATE_IDLE)
    {
    COPP_LOG_ERR1 ("COPP-ERROR: Cannot process S-CONNECT.ind (Illegal state=%d)",
      acse_conn->copp_state);
    return;
    }

  aCtx->asn1r_decode_method = ASN1_TAG_METHOD;			/* Use asn1_tag method for decoding. */
  aCtx->asn1r_decode_done_fun = asn1r_done_err;	/* done function = error fun 	*/
  aCtx->asn1r_err_fun = NULL;			/* set up error detected fun 	*/

  /* Clean out old stuff from structure.				*/
  memset (&decode_cp, 0, sizeof (decode_cp));
  decode_cp.ppdu_type = PPDU_TYPE_CP;
  decode_cp.version_bit_str = 0x80;	/* Default to "version1".	*/

  /* CRITICAL: Initialize psels in case they are NOT received in CP.	*/
  decode_cp.calling_psel = empty_psel;
  decode_cp.called_psel = empty_psel;
  decode_cp.responding_psel = empty_psel;

  decode_acse_conn = acse_conn;	/* Save in global so asn1r_decode_asn1 (aCtx,	*/
				/* can fill it in.			*/

  /* WARNING: expected_pdv_pci MUST BE SET before START_p_user_data	*/
  /* is called (by asn1r_decode_asn1 (aCtx,).  Don't know it yet, so don't set here.	*/

  p_user_data_is_outer = SD_FALSE;	/* P-User-data IS NOT outermost constr.	*/

/* Call 'asn1r_decode_asn1 (aCtx,' to parse the message.                             */
  ASN1R_TAG_ADD (aCtx, UNI|CONSTR,SET_CODE,START_p_cp);
  asn1r_decode_asn1 (aCtx, acse_conn->ppdu_ptr,acse_conn->ppdu_len);
  if (aCtx->asn1r_pdu_dec_err != NO_DECODE_ERR)
    {
    COPP_LOG_ERR1 ("COPP-ERROR: ASN.1 decode of S-Connect.ind failed, err=%d", aCtx->asn1r_pdu_dec_err);
    abort_reason = 1;			/* unrecognized-ppdu	*/
    event_id = -1;			/* Unlisted	*/
    /* Encode and send ARP PPDU.					*/
    copp_p_abort_req (acse_conn, abort_reason, event_id);
    /* DON'T pass P-P-Abort.ind to COPP-user. User doesn't know about conn.*/
    }
  else if (decode_cp.version_bit_str != 0x80)
    {		/* Must be version1:  Bit 0 of bitstr (high bit) set	*/
    COPP_LOG_ERR0 ("COPP-ERROR: P-CONNECT.ind contains illegal P-version.");
    copp_con_rsp_neg (acse_conn, PROV_REASON_VERSION);
    }
  else if (decode_cp.def_ctxt_proposed)
    {
    COPP_LOG_ERR0 ("COPP-ERROR: P-CONNECT.ind contains unsupported P-default-context.");
    copp_con_rsp_neg (acse_conn, PROV_REASON_DEFAULT_CONTEXT);
    }
  else if (memcmp (decode_cp.called_psel, only_loc_psel, only_loc_psel [0]+1))
    {		/* Called PSEL must be one that is bound.		*/
    COPP_LOG_ERR0 ("COPP-ERROR: P-CONNECT.ind contains invalid Called-P-address.");
    copp_con_rsp_neg (acse_conn, PROV_REASON_CALLED_PRES_ADDR);
    }
  else if (decode_cp.bad_pc_deflist)
    {    /* Something we can't handle in pc_deflist.		*/
    COPP_LOG_ERR0 ("COPP-ERROR: P-CONNECT.ind contains illegal PC-deflist.");
    copp_con_rsp_neg (acse_conn, PROV_REASON_LOCAL_LIMIT);
    }
  else if (decode_cp.calling_psel[0] > MAX_PSEL_LEN)
    {    /* Calling PSEL too long (Called PSEL len checked by memcmp above).*/
    COPP_LOG_ERR2 ("COPP-ERROR: P-CONNECT.ind: Calling PSEL len=%u (should be len<=%u).",
              decode_cp.calling_psel[0], MAX_PSEL_LEN);
    copp_con_rsp_neg (acse_conn, PROV_REASON_LOCAL_LIMIT);
    }
  else
    {
    COPP_LOG_DEC1 ("P-CONNECT.ind:   acse_conn_id =0x%08X", acse_conn);
    COPP_LOG_DECC1 ("User data length: %d", acse_conn->apdu_len);
    COPP_LOG_DECH (acse_conn->apdu_len, acse_conn->apdu_ptr);

    acse_conn->copp_state = COPP_STATE_AWAIT_CON_RSP;

    /* Save called_psel, calling_psel in acse_conn.			*/
    /* Will NEVER be too long, because len checked above.		*/
    memcpy (acse_conn->loc_psel, decode_cp.called_psel, decode_cp.called_psel [0]+1);
    memcpy (acse_conn->rem_psel, decode_cp.calling_psel, decode_cp.calling_psel [0]+1);
    
    u_copp_con_ind (user_bind_id, acse_conn);
    }
  }
#endif	/* !defined (CALLING_ONLY)	*/

#if !defined (CALLED_ONLY)
/************************************************************************/
/*			u_cosp_con_cnf_pos				*/
/*----------------------------------------------------------------------*/
/* This USER function is called by the SS-Provider to indicate that	*/
/* the connection has been established.					*/
/* 									*/
/* Parameters:								*/
/*  acse_conn			Pointer to connection info		*/
/*	  								*/
/* Return:								*/
/*	ST_VOID								*/
/************************************************************************/
ST_VOID u_cosp_con_cnf_pos (ACSE_CONN *acse_conn)
  {
ST_INT8 abort_reason;
ST_INT8 event_id;
ASN1_DEC_CTXT localDecCtx;	/* For readability, use "aCtx" to access this.*/
ASN1_DEC_CTXT *aCtx = &localDecCtx;

  memset (aCtx, 0, sizeof (ASN1_DEC_CTXT));	/* CRITICAL: start clean	*/

  if (acse_conn->copp_state != COPP_STATE_AWAIT_CPA)
    {
    COPP_LOG_ERR1 ("COPP-ERROR: Cannot process S-CONNECT.cnf+ (Illegal state=%d)",
      acse_conn->copp_state);
    return;
    }

  aCtx->asn1r_decode_method = ASN1_TAG_METHOD;			/* Use asn1_tag method for decoding. */
  aCtx->asn1r_decode_done_fun = asn1r_done_err;	/* done function = error fun 	*/
  aCtx->asn1r_err_fun = NULL;			/* set up error detected fun 	*/

  /* Clean out old stuff from structure.				*/
  memset (&decode_cp, 0, sizeof (decode_cp));
  decode_cp.ppdu_type = PPDU_TYPE_CPA;
  decode_cp.version_bit_str = 0x80;	/* Default to "version1".	*/

  /* CRITICAL: Initialize psels in case they are NOT received in CP.	*/
  decode_cp.calling_psel = empty_psel;
  decode_cp.called_psel = empty_psel;
  decode_cp.responding_psel = empty_psel;

  decode_acse_conn = acse_conn;	/* Save in global so asn1r_decode_asn1 (aCtx,	*/
				/* can fill it in.			*/

  /* WARNING: expected_pdv_pci MUST BE SET before START_p_user_data	*/
  /* is called (by asn1r_decode_asn1 (aCtx,).  SET IT NOW.				*/
  expected_pdv_pci = acse_conn->pciacse;

  p_user_data_is_outer = SD_FALSE;	/* P-User-data IS NOT outermost constr.	*/

/* Call 'asn1r_decode_asn1 (aCtx,' to parse the message.                             */
  ASN1R_TAG_ADD (aCtx, UNI|CONSTR,SET_CODE,START_p_cp);
  asn1r_decode_asn1 (aCtx, acse_conn->ppdu_ptr,acse_conn->ppdu_len);
  if (aCtx->asn1r_pdu_dec_err != NO_DECODE_ERR)
    {
    COPP_LOG_ERR1 ("COPP-ERROR: ASN.1 decode of S-Connect.cnf+ failed, err=%d", aCtx->asn1r_pdu_dec_err);
    acse_conn->copp_state = COPP_STATE_IDLE;
    abort_reason = 1;			/* unrecognized-ppdu	*/
    event_id = -1;			/* Unlisted	*/
    /* Encode and send ARP PPDU.					*/
    copp_p_abort_req (acse_conn, abort_reason, event_id);
    /* Pass P-P-Abort.ind to COPP-user.					*/
    u_copp_p_abort_ind (acse_conn, abort_reason);
    }
  else if (decode_cp.version_bit_str != 0x80  ||  decode_cp.bad_pc_deflist)
    {		/* Must be version1:  Bit 0 of bitstr (high bit) set	*/
    COPP_LOG_ERR1 ("COPP-ERROR: Unsupported version in CPA received for conn %d",
      acse_conn->user_conn_id);
    acse_conn->copp_state = COPP_STATE_IDLE;
    abort_reason = 6;			/* invalid-ppdu-parameter-value	*/
    event_id = 1;			/* cpa-PPDU	*/
    /* Encode and send ARP PPDU.					*/
    copp_p_abort_req (acse_conn, abort_reason, event_id);
    /* Pass P-P-Abort.ind to COPP-user.					*/
    u_copp_p_abort_ind (acse_conn, abort_reason);
    }
  else
    {
    COPP_LOG_DEC2 ("P-CONNECT.cnf+:  acse_conn_id =0x%08X  user_conn_id =%4ld",
      acse_conn, acse_conn->user_conn_id);
    COPP_LOG_DECC1 ("User data length: %d", acse_conn->apdu_len);
    COPP_LOG_DECH (acse_conn->apdu_len, acse_conn->apdu_ptr);

    acse_conn->copp_state = COPP_STATE_CONNECTED;
    u_copp_con_cnf (acse_conn, P_CON_RESULT_ACCEPT, 0);
    }
  }
#endif	/* !defined (CALLED_ONLY)	*/

	/*======================================================*/
	/*	FUNCTIONS BELOW USED FOR BOTH			*/
	/*	"CP" AND "CPA" DECODE				*/
	/*======================================================*/

/************************************************************************/
/*			START_p_cp					*/
/************************************************************************/
static ST_VOID START_p_cp (ASN1_DEC_CTXT *aCtx)
  {
  ASN1R_TAG_ADD (aCtx, CTX|CONSTR,0,START_mode);
  ASN1R_TAG_ADD (aCtx, CTX|CONSTR,2,START_p_cp_sequence);
  aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = END_p_cp;
  }
/************************************************************************/
/*			START_mode					*/
/************************************************************************/
static ST_VOID START_mode (ASN1_DEC_CTXT *aCtx)
  {
  ASN1R_TAG_ADD (aCtx, CTX,0,decode_mode2);
  aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = END_mode;
  }
/************************************************************************/
/*			decode_mode2					*/
/************************************************************************/
static ST_VOID decode_mode2 (ASN1_DEC_CTXT *aCtx)
  {
  if (asn1r_get_i8 (aCtx, &decode_cp.mode) || decode_cp.mode != 1)	/* Not "normal" mode. Give up.	*/
    {
    asn1r_set_dec_err (aCtx, ASN1E_INVALID_BOOLEAN); 
    return;                          
    }
  }
/************************************************************************/
/*			END_mode					*/
/************************************************************************/
static ST_VOID END_mode (ASN1_DEC_CTXT *aCtx)
  {
  ASN1R_TAG_ADD (aCtx, CTX|CONSTR,2,START_p_cp_sequence);
  }
/************************************************************************/
/*			START_p_cp_sequence				*/
/************************************************************************/
static ST_VOID START_p_cp_sequence (ASN1_DEC_CTXT *aCtx)
  {
  ASN1R_TAG_ADD (aCtx, CTX,0,decode_version);
  if (decode_cp.ppdu_type == PPDU_TYPE_CP)
    {					/* This is CP PPDU	*/
    ASN1R_TAG_ADD (aCtx, CTX,1,decode_calling_psel);
    ASN1R_TAG_ADD (aCtx, CTX,2,decode_called_psel);
    ASN1R_TAG_ADD (aCtx, CTX|CONSTR,4,START_pc_deflist);
    ASN1R_TAG_ADD (aCtx, CTX|CONSTR,6,START_def_ctxt_name);
    }
  else
    {					/* This is CPA PPDU	*/
    ASN1R_TAG_ADD (aCtx, CTX,3,decode_responding_psel);
    ASN1R_TAG_ADD (aCtx, CTX|CONSTR,5,START_pc_def_result_list);
    }
  ASN1R_TAG_ADD (aCtx, CTX,8,decode_pres_req);
  ASN1R_TAG_ADD (aCtx, CTX,9,decode_user_sess_req);
  ASN1R_TAG_ADD (aCtx, APP|CONSTR,1,START_p_user_data);
  aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = END_p_cp_sequence;
  }
/************************************************************************/
/*			decode_version					*/
/************************************************************************/
static ST_VOID decode_version (ASN1_DEC_CTXT *aCtx)
  {
  asn1r_get_bitstr (aCtx, &decode_cp.version_bit_str, 8);
  if (decode_cp.ppdu_type == PPDU_TYPE_CP)
    {					/* This is CP PPDU	*/
    ASN1R_TAG_ADD (aCtx, CTX,1,decode_calling_psel);
    ASN1R_TAG_ADD (aCtx, CTX,2,decode_called_psel);
    ASN1R_TAG_ADD (aCtx, CTX|CONSTR,4,START_pc_deflist);
    ASN1R_TAG_ADD (aCtx, CTX|CONSTR,6,START_def_ctxt_name);
    }
  else
    {					/* This is CPA PPDU	*/
    ASN1R_TAG_ADD (aCtx, CTX,3,decode_responding_psel);
    ASN1R_TAG_ADD (aCtx, CTX|CONSTR,5,START_pc_def_result_list);
    }
  ASN1R_TAG_ADD (aCtx, CTX,8,decode_pres_req);
  ASN1R_TAG_ADD (aCtx, CTX,9,decode_user_sess_req);
  ASN1R_TAG_ADD (aCtx, APP|CONSTR,1,START_p_user_data);
  }
/************************************************************************/
/*			decode_calling_psel				*/
/************************************************************************/
static ST_VOID decode_calling_psel (ASN1_DEC_CTXT *aCtx)
  {
  decode_cp.calling_psel = aCtx->asn1r_field_ptr-1;
  /* Primitive CAN'T be indef len, so asn1_skip_elmnt is safe here.	*/
  asn1_skip_elmnt (aCtx);		/* Don't bother decoding it.		*/
  ASN1R_TAG_ADD (aCtx, CTX,2,decode_called_psel);
  ASN1R_TAG_ADD (aCtx, CTX|CONSTR,4,START_pc_deflist);
  ASN1R_TAG_ADD (aCtx, CTX|CONSTR,6,START_def_ctxt_name);
  ASN1R_TAG_ADD (aCtx, CTX,8,decode_pres_req);
  ASN1R_TAG_ADD (aCtx, CTX,9,decode_user_sess_req);
  ASN1R_TAG_ADD (aCtx, APP|CONSTR,1,START_p_user_data);
  }
/************************************************************************/
/*			decode_called_psel				*/
/************************************************************************/
static ST_VOID decode_called_psel (ASN1_DEC_CTXT *aCtx)
  {
  decode_cp.called_psel = aCtx->asn1r_field_ptr-1;
  /* Primitive CAN'T be indef len, so asn1_skip_elmnt is safe here.	*/
  asn1_skip_elmnt (aCtx);		/* Don't bother decoding it.		*/
  ASN1R_TAG_ADD (aCtx, CTX|CONSTR,4,START_pc_deflist);
  ASN1R_TAG_ADD (aCtx, CTX|CONSTR,6,START_def_ctxt_name);
  ASN1R_TAG_ADD (aCtx, CTX,8,decode_pres_req);
  ASN1R_TAG_ADD (aCtx, CTX,9,decode_user_sess_req);
  ASN1R_TAG_ADD (aCtx, APP|CONSTR,1,START_p_user_data);
  }
/************************************************************************/
/*			START_pc_deflist				*/
/************************************************************************/
static ST_VOID START_pc_deflist (ASN1_DEC_CTXT *aCtx)
  {
  ASN1R_TAG_ADD (aCtx, UNI|CONSTR,SEQ_CODE,START_context);
  aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = END_pc_deflist;
  }
/************************************************************************/
/*			START_context					*/
/************************************************************************/
static ST_VOID START_context (ASN1_DEC_CTXT *aCtx)
  {
  ASN1R_TAG_ADD (aCtx, UNI,INT_CODE,decode_pci);
  aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = END_context;
  }
/************************************************************************/
/*			decode_pci					*/
/************************************************************************/
static ST_VOID decode_pci (ASN1_DEC_CTXT *aCtx)
  {
  if (asn1r_get_i8 (aCtx, &pci))
    {
    asn1r_set_dec_err (aCtx, ASN1E_INVALID_BOOLEAN); 
    return;                          
    }
  ASN1R_TAG_ADD (aCtx, UNI,OBJ_ID_CODE,decode_asn);
  }
/************************************************************************/
/*			decode_asn					*/
/************************************************************************/
static ST_VOID decode_asn (ASN1_DEC_CTXT *aCtx)
  {
MMS_OBJ_ID asn;
  if (asn1r_get_objid (aCtx, asn.comps,&asn.num_comps))
    {
    asn1r_set_dec_err (aCtx, ASN1E_INVALID_BOOLEAN);
    return;
    }
  if (asn1_objidcmp (&asn, (MMS_OBJ_ID *) &mms_obj_id) == 0)
    decode_acse_conn->pcimms = pci;
  else if (asn1_objidcmp (&asn, (MMS_OBJ_ID *) &acse_obj_id) == 0)
    decode_acse_conn->pciacse = pci;
  else
    {	/* Unrecognized Abstract Syntax.  Must be "ACSE" or "ISO MMS".	*/
    decode_cp.bad_pc_deflist = SD_TRUE;
    }

  ASN1R_TAG_ADD (aCtx, UNI|CONSTR,SEQ_CODE,START_tsn_list);
  }
/************************************************************************/
/*			START_tsn_list					*/
/************************************************************************/
static ST_VOID START_tsn_list (ASN1_DEC_CTXT *aCtx)
  {
  ASN1R_TAG_ADD (aCtx, UNI,OBJ_ID_CODE,decode_tsn);
  aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = END_tsn_list;
  }
/************************************************************************/
/*			decode_tsn					*/
/************************************************************************/
static ST_VOID decode_tsn (ASN1_DEC_CTXT *aCtx)
  {
MMS_OBJ_ID tsn;

  if (asn1r_get_objid (aCtx, tsn.comps,&tsn.num_comps))
    {
    asn1r_set_dec_err (aCtx, ASN1E_INVALID_BOOLEAN);
    return;
    }
  if (asn1_objidcmp (&tsn, (MMS_OBJ_ID *) &asn1_obj_id) != 0)
    {					/* TSN better be ASN1		*/
    decode_cp.bad_pc_deflist = SD_TRUE;
    }
  /* DEBUG: we don't support multiple TSN so no ASN1R_TAG_ADD (aCtx, here.	*/
  /* Should end up in END_tsn_list after this.		*/
  }
/************************************************************************/
/*			END_tsn_list					*/
/************************************************************************/
static ST_VOID END_tsn_list (ASN1_DEC_CTXT *aCtx)
  {
  return;
  }
/************************************************************************/
/*			END_context					*/
/************************************************************************/
static ST_VOID END_context (ASN1_DEC_CTXT *aCtx)
  {
  decode_acse_conn->num_ctxt++;
  /* May be another context.	*/
  ASN1R_TAG_ADD (aCtx, UNI|CONSTR,SEQ_CODE,START_context);
  }
/************************************************************************/
/*			END_pc_deflist					*/
/************************************************************************/
static ST_VOID END_pc_deflist (ASN1_DEC_CTXT *aCtx)
  {
  /* Set the PCI to be used during P-User-Data decode.			*/
  /* WARNING: this must be done here because we don't know what it is	*/
  /* beforehand.							*/
  expected_pdv_pci = decode_acse_conn->pciacse;

  ASN1R_TAG_ADD (aCtx, CTX|CONSTR,6,START_def_ctxt_name);
  ASN1R_TAG_ADD (aCtx, CTX,8,decode_pres_req);
  ASN1R_TAG_ADD (aCtx, CTX,9,decode_user_sess_req);
  ASN1R_TAG_ADD (aCtx, APP|CONSTR,1,START_p_user_data);
  }
/************************************************************************/
/*			START_def_ctxt_name				*/
/* Default-context-name.  If this is present, we will refuse this	*/
/* connection so don't bother decoding it.				*/
/************************************************************************/
static ST_VOID START_def_ctxt_name (ASN1_DEC_CTXT *aCtx)
  {
  decode_cp.def_ctxt_proposed = SD_TRUE;
  /* Don't bother decoding it. Use asn1r_parse_next (aCtx, to skip over it.	*/
  aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = END_def_ctxt_name;
  asn1r_parse_next (aCtx, parse_next_done);
  }
/************************************************************************/
/*			parse_next_done					*/
/************************************************************************/
static ST_VOID parse_next_done (ASN1_DEC_CTXT *aCtx)
  {	/* called when "asn1r_parse_next (aCtx," is done	*/
  }
/************************************************************************/
/*			END_def_ctxt_name				*/
/************************************************************************/
static ST_VOID END_def_ctxt_name (ASN1_DEC_CTXT *aCtx)
  {
  ASN1R_TAG_ADD (aCtx, CTX,8,decode_pres_req);
  ASN1R_TAG_ADD (aCtx, CTX,9,decode_user_sess_req);
  ASN1R_TAG_ADD (aCtx, APP|CONSTR,1,START_p_user_data);
  }
/************************************************************************/
/*			decode_pres_req					*/
/************************************************************************/
static ST_VOID decode_pres_req (ASN1_DEC_CTXT *aCtx)
  {
  decode_cp.pres_req_present = SD_TRUE;
  asn1r_get_bitstr (aCtx, decode_cp.pres_req, 8);
  ASN1R_TAG_ADD (aCtx, CTX,9,decode_user_sess_req);
  ASN1R_TAG_ADD (aCtx, APP|CONSTR,1,START_p_user_data);
  }
/************************************************************************/
/*			decode_user_sess_req				*/
/************************************************************************/
static ST_VOID decode_user_sess_req (ASN1_DEC_CTXT *aCtx)
  {
  decode_cp.user_ses_req_present = SD_TRUE;
  asn1r_get_bitstr (aCtx, decode_cp.user_sess_req, 16);
  ASN1R_TAG_ADD (aCtx, APP|CONSTR,1,START_p_user_data);
  }
/************************************************************************/
/*			END_p_cp_sequence				*/
/************************************************************************/
static ST_VOID END_p_cp_sequence (ASN1_DEC_CTXT *aCtx)
  {	/* Somebody might encode "mode" after "p_cp_sequence".	*/
  ASN1R_TAG_ADD (aCtx, CTX|CONSTR,0,START_mode);
  }
/************************************************************************/
/*			END_p_cp					*/
/************************************************************************/
static ST_VOID END_p_cp (ASN1_DEC_CTXT *aCtx)
  {
  aCtx->asn1r_decode_done_fun = NULL;		/* done decoding		*/
  }

	/*======================================================*/
	/*	FUNCTIONS BELOW USED ONLY FOR "CPA" DECODE	*/
	/*							*/
	/*======================================================*/

/************************************************************************/
/*			decode_responding_psel				*/
/************************************************************************/
static ST_VOID decode_responding_psel (ASN1_DEC_CTXT *aCtx)
  {
  decode_cp.responding_psel = aCtx->asn1r_field_ptr-1;
  /* Primitive CAN'T be indef len, so asn1_skip_elmnt is safe here.	*/
  asn1_skip_elmnt (aCtx);		/* Don't bother decoding it.		*/
  ASN1R_TAG_ADD (aCtx, CTX|CONSTR,5,START_pc_def_result_list);
  ASN1R_TAG_ADD (aCtx, CTX,8,decode_pres_req);
  ASN1R_TAG_ADD (aCtx, CTX,9,decode_user_sess_req);
  ASN1R_TAG_ADD (aCtx, APP|CONSTR,1,START_p_user_data);
  }
/************************************************************************/
/*			START_pc_def_result_list			*/
/************************************************************************/
static ST_VOID START_pc_def_result_list (ASN1_DEC_CTXT *aCtx)
  {
  ASN1R_TAG_ADD (aCtx, UNI|CONSTR,SEQ_CODE,START_result_seq);
  aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = END_pc_def_result_list;
  }
/************************************************************************/
/*			START_result_seq				*/
/************************************************************************/
static ST_VOID START_result_seq (ASN1_DEC_CTXT *aCtx)
  {
  ASN1R_TAG_ADD (aCtx, CTX,0,decode_result);
  aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = END_result_seq;
  }
/************************************************************************/
/*			decode_result					*/
/************************************************************************/
static ST_VOID decode_result (ASN1_DEC_CTXT *aCtx)
  {
ST_INT8 result;
  if (asn1r_get_i8 (aCtx, &result))
    {
    asn1r_set_dec_err (aCtx, ASN1E_INVALID_BOOLEAN);
    return;
    }
  if (result != 0)
    {	/* P-Context rejected. We can't handle any rejection so set flag.*/ 
    decode_cp.bad_pc_deflist = SD_TRUE;
    }
  ASN1R_TAG_ADD (aCtx, CTX,1,decode_tsn2);
  ASN1R_TAG_ADD (aCtx, CTX,2,decode_result_list_prov_reas);
  }
/************************************************************************/
/*			decode_tsn2					*/
/* NOTE: This is essentially same as decode_tsn used in the CP decode	*/
/* except for the different ASN1R_TAG_ADD (aCtx, at the end.  In either case		*/
/* if we receive any TSN that is not ASN.1 (this is the only		*/
/* TSN we will ever accept or propose) we set the flag			*/
/*       decode_cp.bad_pc_deflist = SD_TRUE				*/
/************************************************************************/
static ST_VOID decode_tsn2 (ASN1_DEC_CTXT *aCtx)
  {
MMS_OBJ_ID tsn;

  if (asn1r_get_objid (aCtx, tsn.comps,&tsn.num_comps))
    {
    asn1r_set_dec_err (aCtx, ASN1E_INVALID_BOOLEAN);
    return;
    }
  if (asn1_objidcmp (&tsn, (MMS_OBJ_ID *) &asn1_obj_id) != 0)
    {					/* TSN better be ASN1		*/
    decode_cp.bad_pc_deflist = SD_TRUE;
    }
  ASN1R_TAG_ADD (aCtx, CTX,2,decode_result_list_prov_reas);
  }
/************************************************************************/
/*			decode_result_list_prov_reas			*/
/* NOTE: Decode but don't save value, because no real use for it.	*/
/************************************************************************/
static ST_VOID decode_result_list_prov_reas (ASN1_DEC_CTXT *aCtx)
  {
ST_INT8 result_list_prov_reas;
  if (asn1r_get_i8 (aCtx, &result_list_prov_reas))
    {
    asn1r_set_dec_err (aCtx, ASN1E_INVALID_BOOLEAN); 
    return;                          
    }
  }
/************************************************************************/
/*			END_result_seq					*/
/************************************************************************/
static ST_VOID END_result_seq (ASN1_DEC_CTXT *aCtx)
  {
  decode_acse_conn->num_ctxt++;
  /* May be another "result sequence".	*/
  ASN1R_TAG_ADD (aCtx, UNI|CONSTR,SEQ_CODE,START_result_seq);
  }
/************************************************************************/
/*			END_pc_def_result_list				*/
/************************************************************************/
static ST_VOID END_pc_def_result_list (ASN1_DEC_CTXT *aCtx)
  {
  ASN1R_TAG_ADD (aCtx, CTX,8,decode_pres_req);
  ASN1R_TAG_ADD (aCtx, CTX,9,decode_user_sess_req);
  ASN1R_TAG_ADD (aCtx, APP|CONSTR,1,START_p_user_data);
  }

