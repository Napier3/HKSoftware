/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*	(c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*	1997-2002, All Rights Reserved					*/
/*									*/
/*			PROPRIETARY AND CONFIDENTIAL			*/
/*									*/
/* MODULE NAME : copp_dec.c						*/
/* PRODUCT(S)  : MOSI Stack (over TP4)					*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/*		This file implements decoding of most confirm/indication*/
/*		functions.						*/
/*									*/
/*  For information see the:						*/
/*	ISO 8822 "Information processing systems - Open Systems		*/
/*	  Interconnection - Connection oriented presentation service	*/
/*	  definition.							*/
/*	ISO 8823 "Information processing systems - Open Systems		*/
/*	  Interconnection - Connection oriented presentation protocol	*/
/*	  specification.						*/
/*									*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*									*/
/*			u_cosp_bind_cnf					*/
/*			u_cosp_unbind_cnf				*/
/*									*/
/*			u_cosp_rel_cnf_pos				*/
/*			u_cosp_rel_ind					*/
/*			u_cosp_p_abort_ind 				*/
/*			u_cosp_data_ind 				*/
/*									*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 01/02/02  JRB    10     Converted to use ASN1R (re-entrant ASN1)	*/
/* 04/24/01  JRB    09     Allow octet-aligned PDV. Don't think it's	*/
/*			   legal but some stacks (ONE?) may use it.	*/
/* 02/21/01  JRB    08     Fix previous change. Was checking wrong byte	*/
/*			   in PDU for Indef Len. Use global flag instead*/  
/* 12/20/00  JRB    07     asn1_skip_elmnt doesn't work for indef len	*/
/*			   encoding. Use "parse_next" instead.		*/
/* 08/13/98  JRB    06     Lint cleanup.				*/
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

/*          START_p_user_data	used by everyone, so proto in include	*/
/*          START_pdv_list	used by everyone, so proto in include	*/
static ST_VOID decode_pdv_tsn (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_pdv_pci (ASN1_DEC_CTXT *aCtx);
static ST_VOID START_pdv (ASN1_DEC_CTXT *aCtx);
static ST_VOID parse_next_done (ASN1_DEC_CTXT *aCtx);
static ST_VOID END_pdv (ASN1_DEC_CTXT *aCtx);
static ST_VOID END_pdv_list (ASN1_DEC_CTXT *aCtx);
static ST_VOID END_p_user_data (ASN1_DEC_CTXT *aCtx);

/************************************************************************/
/* Global Variables							*/
/************************************************************************/
ST_CHAR expected_pdv_pci;
ST_UCHAR *pdv_data_ptr;
ST_INT pdv_data_len;

ST_BOOLEAN p_user_data_is_outer;	/* Is P-User-data outermost constr?*/
				/* SD_TRUE or SD_FALSE		*/

/************************************************************************/
/*			u_cosp_bind_cnf					*/
/************************************************************************/
ST_VOID u_cosp_bind_cnf (ST_LONG user_bind_id, ST_LONG cosp_bind_id, ST_RET result)
  {
  COPP_LOG_DEC3 ("P-BIND.cnf:    copp_user_bind_id =0x%08X  copp_bind_id =%9ld  result =%d",
    user_bind_id, cosp_bind_id, result);

  u_copp_bind_cnf (user_bind_id, cosp_bind_id, result);
  }

/************************************************************************/
/*			u_cosp_unbind_cnf				*/
/************************************************************************/
ST_VOID u_cosp_unbind_cnf (ST_LONG user_bind_id)
  {
  COPP_LOG_DEC1 ("P-UNBIND.cnf:  copp_user_bind_id =0x%08X", user_bind_id);

  u_copp_unbind_cnf (user_bind_id);
  }

#if !defined (CALLED_ONLY)
/* See "coppdcp.c" for "u_cosp_con_cnf_pos" function.			*/
/* See "coppdcpr.c" for "u_cosp_con_cnf_neg" function.			*/

/************************************************************************/
/*			u_cosp_rel_cnf_pos				*/
/*----------------------------------------------------------------------*/
/* This USER function is called by the SS-Provider to indicate positive	*/
/* result of the release operation.					*/
/* 									*/
/* Parameters:								*/
/*	acse_conn		Pointer to connection info		*/
/*	  								*/
/* Return:								*/
/*	ST_VOID								*/
/************************************************************************/
ST_VOID u_cosp_rel_cnf_pos (ACSE_CONN *acse_conn)
  {
ST_INT8 abort_reason;
ASN1_DEC_CTXT localDecCtx;	/* For readability, use "aCtx" to access this.*/
ASN1_DEC_CTXT *aCtx = &localDecCtx;

  memset (aCtx, 0, sizeof (ASN1_DEC_CTXT));	/* CRITICAL: start clean	*/

  if (acse_conn->copp_state != COPP_STATE_CONNECTED)
    {
    COPP_LOG_ERR1 ("COPP-ERROR: Cannot process S-RELEASE.cnf+ (Illegal state=%d)",
      acse_conn->copp_state);
    return;
    }

  aCtx->asn1r_decode_method = ASN1_TAG_METHOD;			/* Use asn1_tag method for decoding. */
  aCtx->asn1r_decode_done_fun = asn1r_done_err;	/* done function = error fun 	*/
  aCtx->asn1r_err_fun = NULL;			/* set up error detected fun 	*/

  /* Clean out old stuff from structure.				*/
  decode_acse_conn = acse_conn;	/* Save in global so asn1r_decode_asn1 (aCtx,	*/
				/* can fill it in.			*/

  /* Set the PCI to be used during P-User-Data decode.			*/
  expected_pdv_pci = decode_acse_conn->pciacse;

  p_user_data_is_outer = SD_TRUE;	/* P-User-data IS outermost constr.	*/

/* Call 'asn1r_decode_asn1 (aCtx,' to parse the message.                             */
  ASN1R_TAG_ADD (aCtx, APP|CONSTR,1,START_p_user_data);
  asn1r_decode_asn1 (aCtx, acse_conn->ppdu_ptr,acse_conn->ppdu_len);
  if (aCtx->asn1r_pdu_dec_err != NO_DECODE_ERR)
    {
    COPP_LOG_ERR1 ("COPP-ERROR: ASN.1 decode of S-Release.cnf failed, err=%d", aCtx->asn1r_pdu_dec_err);
    abort_reason = 1;			/* unrecognized-ppdu	*/
    /* Don't send ARP PPDU.  COSP already thinks we're released.	*/
    /* Pass P-P-Abort.ind to COPP-user.					*/
    u_copp_p_abort_ind (acse_conn, abort_reason);
    }
  else
    {
    COPP_LOG_DEC2 ("P-RELEASE.cnf+:  acse_conn_id =0x%08X  user_conn_id =%4ld",
      acse_conn, acse_conn->user_conn_id);
    COPP_LOG_DECC1 ("User data length: %d", acse_conn->apdu_len);
    COPP_LOG_DECH (acse_conn->apdu_len, acse_conn->apdu_ptr);

    if (acse_conn->cr)
      {
      acse_conn->cr = SD_FALSE;
      acse_conn->rl = SD_FALSE;	/* and stay in COPP_STATE_CONNECTED	*/
      }
    else
      acse_conn->copp_state = COPP_STATE_IDLE;

    u_copp_rel_cnf_pos (acse_conn);
    }
  }
#endif	/* !defined (CALLED_ONLY)	*/


#if !defined (CALLING_ONLY)
/* See "coppdcp.c" for "u_cosp_con_ind" function.			*/

/************************************************************************/
/*			u_cosp_rel_ind					*/
/*----------------------------------------------------------------------*/
/* This USER function is called by the SS-Provider to indicate that a	*/
/* remote node wishes to release a connection.				*/
/* 									*/
/* Parameters:								*/
/*  ACSE_CONN	*acse_conn		Pointer to connection info	*/
/*	  								*/
/* Return:								*/
/*	ST_VOID								*/
/************************************************************************/
ST_VOID u_cosp_rel_ind (ACSE_CONN *acse_conn)
  {
ST_INT8 abort_reason;
ST_INT8 event_id;
ASN1_DEC_CTXT localDecCtx;	/* For readability, use "aCtx" to access this.*/
ASN1_DEC_CTXT *aCtx = &localDecCtx;

  memset (aCtx, 0, sizeof (ASN1_DEC_CTXT));	/* CRITICAL: start clean	*/

  if (acse_conn->copp_state != COPP_STATE_CONNECTED)
    {
    COPP_LOG_ERR1 ("COPP-ERROR: Cannot process S-RELEASE.ind (Illegal state=%d)",
      acse_conn->copp_state);
    return;
    }
  /* Set release collision flags.	*/
  if (acse_conn->rl)
    acse_conn->cr = SD_TRUE;
  acse_conn->rl = SD_TRUE;

  aCtx->asn1r_decode_method = ASN1_TAG_METHOD;			/* Use asn1_tag method for decoding. */
  aCtx->asn1r_decode_done_fun = asn1r_done_err;	/* done function = error fun 	*/
  aCtx->asn1r_err_fun = NULL;			/* set up error detected fun 	*/

  /* Clean out old stuff from structure.				*/
  decode_acse_conn = acse_conn;	/* Save in global so asn1r_decode_asn1 (aCtx,	*/
				/* can fill it in.			*/

  /* Set the PCI to be used during P-User-Data decode.			*/
  expected_pdv_pci = decode_acse_conn->pciacse;

  p_user_data_is_outer = SD_TRUE;	/* P-User-data IS outermost constr.	*/

/* Call 'asn1r_decode_asn1 (aCtx,' to parse the message.                             */
  ASN1R_TAG_ADD (aCtx, APP|CONSTR,1,START_p_user_data);
  asn1r_decode_asn1 (aCtx, acse_conn->ppdu_ptr,acse_conn->ppdu_len);
  if (aCtx->asn1r_pdu_dec_err != NO_DECODE_ERR)
    {
    COPP_LOG_ERR1 ("COPP-ERROR: ASN.1 decode of S-Release.ind failed, err=%d", aCtx->asn1r_pdu_dec_err);
    acse_conn->copp_state = COPP_STATE_IDLE;
    abort_reason = 1;			/* unrecognized-ppdu	*/
    event_id = 14;			/* s-release-indication	*/
    /* Encode and send ARP PPDU.					*/
    copp_p_abort_req (acse_conn, abort_reason, event_id);
    /* Pass P-P-Abort.ind to COPP-user.					*/
    u_copp_p_abort_ind (acse_conn, abort_reason);
    }
  else
    {
    COPP_LOG_DEC2 ("P-RELEASE.ind:   acse_conn_id =0x%08X  user_conn_id =%4ld",
      acse_conn, acse_conn->user_conn_id);
    COPP_LOG_DECC1 ("User data length: %d", acse_conn->apdu_len);
    COPP_LOG_DECH (acse_conn->apdu_len, acse_conn->apdu_ptr);

    u_copp_rel_ind (acse_conn);
    }
  }

#endif	/* !defined (CALLING_ONLY)	*/

/************************************************************************/
/*			u_cosp_p_abort_ind 				*/
/*----------------------------------------------------------------------*/
/* This USER function is called by the SS-Provider to indicate that a	*/
/* connection has been aborted by SS-provider (local or remote).	*/
/* 									*/
/* Parameters:								*/
/*  ACSE_CONN	*acse_con	Pointer to connection info		*/
/*  ST_INT	reason		see def reasons COSP_P_AB_IND_... above	*/
/*	  								*/
/* Return:								*/
/*	ST_VOID								*/
/************************************************************************/
ST_VOID u_cosp_p_abort_ind (ACSE_CONN *acse_conn, ST_INT reason)
  {
  if (acse_conn->copp_state == COPP_STATE_IDLE)
    {
    COPP_LOG_ERR1 ("COPP-ERROR: Cannot process S-P-ABORT.ind (Illegal state=%d)",
      acse_conn->copp_state);
    return;
    }

  COPP_LOG_DEC3 ("P-P-ABORT.ind:   acse_conn_id =0x%08X  user_conn_id =%4ld  reason =%d",
    acse_conn, acse_conn->user_conn_id, reason + 0x100);

  acse_conn->copp_state = COPP_STATE_IDLE;
  u_copp_p_abort_ind (acse_conn, reason + 0x100);
  }

/************************************************************************/
/*			u_cosp_data_ind 				*/
/*----------------------------------------------------------------------*/
/* This USER function is called by the SS-Provider to indicate that a	*/
/* data SPDU has been received.						*/
/* 									*/
/* Parameters:								*/
/*  ACSE_CONN	*acse_conn		Pointer to connection info	*/
/*	  								*/
/* Return:								*/
/*	ST_VOID								*/
/************************************************************************/
ST_VOID u_cosp_data_ind (ACSE_CONN *acse_conn)
  {
ST_INT8 abort_reason;
ST_INT8 event_id;
ASN1_DEC_CTXT localDecCtx;	/* For readability, use "aCtx" to access this.*/
ASN1_DEC_CTXT *aCtx = &localDecCtx;

  memset (aCtx, 0, sizeof (ASN1_DEC_CTXT));	/* CRITICAL: start clean	*/

  if (acse_conn->copp_state != COPP_STATE_CONNECTED)
    {
    COPP_LOG_ERR1 ("COPP-ERROR: Cannot process S-DATA.ind (Illegal state=%d)",
      acse_conn->copp_state);
    return;
    }

  aCtx->asn1r_decode_method = ASN1_TAG_METHOD;			/* Use asn1_tag method for decoding. */
  aCtx->asn1r_decode_done_fun = asn1r_done_err;	/* done function = error fun 	*/
  aCtx->asn1r_err_fun = NULL;			/* set up error detected fun 	*/

  /* Clean out old stuff from structure.				*/
  decode_acse_conn = acse_conn;	/* Save in global so asn1r_decode_asn1 (aCtx,	*/
				/* can fill it in.			*/

  /* Set the PCI to be used during P-User-Data decode.			*/
  expected_pdv_pci = decode_acse_conn->pcimms;

  p_user_data_is_outer = SD_TRUE;	/* P-User-data IS outermost constr.	*/

/* Call 'asn1r_decode_asn1 (aCtx,' to parse the message.                             */
  ASN1R_TAG_ADD (aCtx, APP|CONSTR,1,START_p_user_data);
  asn1r_decode_asn1 (aCtx, acse_conn->ppdu_ptr,acse_conn->ppdu_len);
  if (aCtx->asn1r_pdu_dec_err != NO_DECODE_ERR)
    {
    COPP_LOG_ERR1 ("COPP-ERROR: ASN.1 decode of S-Data.ind failed, err=%d", aCtx->asn1r_pdu_dec_err);
    abort_reason = 1;			/* unrecognized-ppdu	*/
    event_id = -1;			/* Unlisted	*/
    /* Encode and send ARP PPDU.					*/
    copp_p_abort_req (acse_conn, abort_reason, event_id);
    /* Pass P-P-Abort.ind to COPP-user.					*/
    u_copp_p_abort_ind (acse_conn, abort_reason);
    }
  else
    {
    COPP_LOG_DEC2 ("P-DATA.ind:      acse_conn_id =0x%08X  user_conn_id =%4ld",
      acse_conn, acse_conn->user_conn_id);
    COPP_LOG_DECC1 ("User data length: %d", acse_conn->apdu_len);
    COPP_LOG_DECH (acse_conn->apdu_len, acse_conn->apdu_ptr);

    u_copp_data_ind (acse_conn);
    }
  }

	/*======================================================*/
	/*	ASN.1 DECODE FUNCTIONS FOR P-USER-DATA		*/
	/*							*/
	/*	Used for CP, CPA, CPR, ARU, DT, or REL decode.	*/
	/*======================================================*/

/************************************************************************/
/*			START_p_user_data				*/
/************************************************************************/
ST_VOID START_p_user_data (ASN1_DEC_CTXT *aCtx)
  {
  ASN1R_TAG_ADD (aCtx, UNI|CONSTR,SEQ_CODE,START_pdv_list);
  aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = END_p_user_data;
  }
/************************************************************************/
/*			START_pdv_list					*/
/* ACSE also uses this function to decode "EXTERNAL".  Although defined	*/
/* independently, it's encoding is same as "PDV-list".			*/
/************************************************************************/
ST_VOID START_pdv_list (ASN1_DEC_CTXT *aCtx)
  {
  ASN1R_TAG_ADD (aCtx, UNI,OBJ_ID_CODE,decode_pdv_tsn);
  ASN1R_TAG_ADD (aCtx, UNI,INT_CODE,decode_pdv_pci);
  aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = END_pdv_list;
  }
/************************************************************************/
/*			decode_pdv_tsn					*/
/************************************************************************/
static ST_VOID decode_pdv_tsn (ASN1_DEC_CTXT *aCtx)
  {
MMS_OBJ_ID tsn;

  if (asn1r_get_objid (aCtx, tsn.comps,&tsn.num_comps))
    {
    asn1r_set_dec_err (aCtx, ASN1E_INVALID_BOOLEAN);
    return;
    }
  if (asn1_objidcmp (&tsn, &asn1_obj_id) != 0)
    {					/* TSN better be ASN1		*/
    asn1r_set_dec_err (aCtx, ASN1E_INVALID_BITSTR);
    return;
    }
  ASN1R_TAG_ADD (aCtx, UNI,INT_CODE,decode_pdv_pci);
  }
/************************************************************************/
/*			decode_pdv_pci					*/
/************************************************************************/
static ST_VOID decode_pdv_pci (ASN1_DEC_CTXT *aCtx)
  {
ST_INT8 pci;

  if (asn1r_get_i8 (aCtx, &pci))
    {
    asn1r_set_dec_err (aCtx, ASN1E_INVALID_BOOLEAN); 
    return;                          
    }
  if (pci != expected_pdv_pci)
    {		/* Not the pci we're expecting.		*/
    asn1r_set_dec_err (aCtx, ASN1E_INVALID_BITSTR); 
    return;                          
    }
  ASN1R_TAG_ADD (aCtx, CTX|CONSTR,0,START_pdv);	/* Must be single-ASN1-type	*/
  /* Octet-aligned doesn't appear to be legal, but some stacks (ONE?)	*/
  /* may use it. To be friendly, let's accept it.			*/
  ASN1R_TAG_ADD (aCtx, CTX,1,START_pdv);		/* Allow octet-aligned	*/
  }
/************************************************************************/
/*			START_pdv					*/
/************************************************************************/
static ST_VOID START_pdv (ASN1_DEC_CTXT *aCtx)
  {
  /* Should now point to PDV data. Save until decode done.		*/
  pdv_data_ptr = aCtx->asn1r_field_ptr;

  /* If this is indefinite length encoding, use "asn1r_parse_next (aCtx,".		*/
  /* If "normal" encoding, use "asn1_skip_elmnt" (faster).		*/
  if (aCtx->asn1r_indef_flag)
    {				/* indefinite length encoding	*/
    aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = END_pdv;
    asn1r_parse_next (aCtx, parse_next_done);
    }
  else
    {				/* "normal" encoding		*/
    pdv_data_len = aCtx->asn1r_elmnt_len;
    asn1_skip_elmnt (aCtx);	/* Done decoding PPDU. Let ACSE decode rest.	*/
    }
  }
/************************************************************************/
/*			parse_next_done					*/
/* Only used for indefinite length encoding.				*/
/************************************************************************/
static ST_VOID parse_next_done (ASN1_DEC_CTXT *aCtx)
  {	/* called when "asn1r_parse_next (aCtx," is done	*/
  }
/************************************************************************/
/*			END_pdv						*/
/* Only used for indefinite length encoding.				*/
/************************************************************************/
static ST_VOID END_pdv (ASN1_DEC_CTXT *aCtx)
  {
  pdv_data_len = aCtx->asn1r_field_ptr - pdv_data_ptr - 2;	/* -2 strips 00 00*/
  }
/************************************************************************/
/*			END_pdv_list					*/
/************************************************************************/
static ST_VOID END_pdv_list (ASN1_DEC_CTXT *aCtx)
  {
  }
/************************************************************************/
/*			END_p_user_data					*/
/************************************************************************/
static ST_VOID END_p_user_data (ASN1_DEC_CTXT *aCtx)
  {
  decode_acse_conn->apdu_ptr = pdv_data_ptr;
  decode_acse_conn->apdu_len = pdv_data_len;
  if (p_user_data_is_outer)	/* Is P-User-data outermost constr?	*/
    aCtx->asn1r_decode_done_fun = NULL;		/* done decoding		*/
  }

