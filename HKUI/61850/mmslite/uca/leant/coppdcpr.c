/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*	(c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*	1997-2002, All Rights Reserved					*/
/*									*/
/*			PROPRIETARY AND CONFIDENTIAL			*/
/*									*/
/* MODULE NAME : coppdcpr.c						*/
/* PRODUCT(S)  : MOSI Stack (over TP4)					*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/*		This file implements decoding of CPR PPDU.		*/
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
/*			u_cosp_con_cnf_neg				*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 03/31/03  JRB    08     asn1r_get_bitstr: add max_bits arg.		*/
/* 01/02/02  JRB    07     Converted to use ASN1R (re-entrant ASN1)	*/
/* 10/09/01  JRB    06     asn1_skip_elmnt doesn't work for indef len	*/
/*			   encoding. Use "parse_next" instead.		*/
/* 02/02/99  JRB    05     BUG FIX: Decode "prov_reas" in "Result-list"	*/
/*			   even if no TSN (see decode_result).		*/
/* 02/02/99  JRB    04	   Allow User-data with Prov-reason but ignore.	*/
/* 03/18/98  JRB    03     Use defines (not variables) for ASN1 errors.	*/
/* 12/22/97  JRB    02     Use ST_INT8.					*/
/* 05/27/97  JRB   7.00    MMSEASE 7.0 release.				*/
/* 03/19/97  JRB    01     Created					*/
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

/* Define illegal value for "provider_reason".  Init to this before	*/
/* decode. If still equals this after decode, it was not encoded in PDU.*/ 
#define CPR_PROVIDER_REASON_NOT_ENCODED		-1

/************************************************************************/
/* Global Variables							*/
/************************************************************************/
/* Structure for tracking this decode.		*/
typedef struct
  {
  ST_UCHAR version_bit_str;
  ST_UCHAR *responding_psel;
  ST_INT num_ctxt;
  ST_BOOLEAN bad_pc_deflist;	/* SD_TRUE if anything we don't like in pc_deflist*/
  ST_INT8 default_context_result;
  ST_INT8 provider_reason;
  } CPR_INFO;
static CPR_INFO cpr_info;

static ST_VOID START_p_cpr (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_version (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_responding_psel (ASN1_DEC_CTXT *aCtx);
static ST_VOID START_pc_def_result_list (ASN1_DEC_CTXT *aCtx);
static ST_VOID START_result_seq (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_result (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_tsn2 (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_result_list_prov_reas (ASN1_DEC_CTXT *aCtx);
static ST_VOID END_result_seq (ASN1_DEC_CTXT *aCtx);
static ST_VOID END_pc_def_result_list (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_default_context_result (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_provider_reason (ASN1_DEC_CTXT *aCtx);
static ST_VOID SKIP_p_user_data (ASN1_DEC_CTXT *aCtx);
static ST_VOID parse_next_done (ASN1_DEC_CTXT *aCtx);
static ST_VOID END_skip_p_user_data (ASN1_DEC_CTXT *aCtx);
static ST_VOID END_p_cpr (ASN1_DEC_CTXT *aCtx);


#if !defined (CALLED_ONLY)
/************************************************************************/
/*			u_cosp_con_cnf_neg				*/
/*----------------------------------------------------------------------*/
/* This USER function is called by the SS-Provider to indicate the	*/
/* connection has been rejected by remote.				*/
/* 									*/
/* Parameters:								*/
/*	acse_conn		Pointer to connection info		*/
/*	result			see def results COSP_CON_CNF_... above	*/
/*	reason			see def reasons COSP_CON_CNF_... above	*/
/*	  								*/
/* Return:								*/
/*	ST_VOID								*/
/************************************************************************/
ST_VOID u_cosp_con_cnf_neg (ACSE_CONN *acse_conn, ST_INT result, ST_INT reason)
  {
ST_INT8 abort_reason;
ASN1_DEC_CTXT localDecCtx;	/* For readability, use "aCtx" to access this.*/
ASN1_DEC_CTXT *aCtx = &localDecCtx;

  memset (aCtx, 0, sizeof (ASN1_DEC_CTXT));	/* CRITICAL: start clean	*/

  if (acse_conn->copp_state != COPP_STATE_AWAIT_CPA)
    {
    COPP_LOG_ERR1 ("COPP-ERROR: Cannot process S-CONNECT.cnf- (Illegal state=%d)",
      acse_conn->copp_state);
    return;
    }

  aCtx->asn1r_decode_method = ASN1_TAG_METHOD;			/* Use asn1_tag method for decoding. */
  aCtx->asn1r_decode_done_fun = asn1r_done_err;	/* done function = error fun 	*/
  aCtx->asn1r_err_fun = NULL;			/* set up error detected fun 	*/

  /* Clean out old stuff from structure.				*/
  memset (&cpr_info, 0, sizeof (cpr_info));
  cpr_info.version_bit_str = 0x80;	/* Default to "version1".	*/
  cpr_info.provider_reason = CPR_PROVIDER_REASON_NOT_ENCODED;
  decode_acse_conn = acse_conn;	/* Save in global so asn1r_decode_asn1 (aCtx,	*/
				/* can fill it in.			*/

  /* WARNING: expected_pdv_pci MUST BE SET before START_p_user_data	*/
  /* is called (by asn1r_decode_asn1 (aCtx,).  SET IT NOW.				*/
  expected_pdv_pci = acse_conn->pciacse;

  p_user_data_is_outer = SD_FALSE;	/* P-User-data IS NOT outermost constr.	*/

/* Call 'asn1r_decode_asn1 (aCtx,' to parse the message.                             */
  ASN1R_TAG_ADD (aCtx, UNI|CONSTR,SEQ_CODE,START_p_cpr);
  asn1r_decode_asn1 (aCtx, acse_conn->ppdu_ptr,acse_conn->ppdu_len);
  if (aCtx->asn1r_pdu_dec_err != NO_DECODE_ERR)
    {
    COPP_LOG_ERR1 ("COPP-ERROR: ASN.1 decode of S-Connect.cnf- failed, err=%d", aCtx->asn1r_pdu_dec_err);
    abort_reason = 1;			/* unrecognized-ppdu	*/
    /* Don't send ARP PPDU.  Remote node is already rejecting connect.	*/
    /* Pass P-P-Abort.ind to COPP-user.					*/
    u_copp_p_abort_ind (acse_conn, abort_reason);
    }
  else if (cpr_info.version_bit_str != 0x80)
    {		/* Must be version1:  Bit 0 of bitstr (high bit) set	*/
    COPP_LOG_ERR1 ("COPP-ERROR: Unsupported version in CPR received for conn %d",
      acse_conn->user_conn_id);
    abort_reason = 6;			/* invalid-ppdu-parameter-value	*/
    /* Don't send ARP PPDU.  Remote node is already rejecting connect.	*/
    /* Pass P-P-Abort.ind to COPP-user.					*/
    u_copp_p_abort_ind (acse_conn, abort_reason);
    }
  else if (cpr_info.provider_reason != CPR_PROVIDER_REASON_NOT_ENCODED)
    {		/* Provider reject	*/
    COPP_LOG_DEC2 ("P-CONNECT.cnf-:  acse_conn_id =0x%08X  user_conn_id =%4ld",
      acse_conn, acse_conn->user_conn_id);
    COPP_LOG_DECC1 ("Provider-reason = %d. No P-user-data.",
      cpr_info.provider_reason);
    /* NOTE: there is no User-data with this one.			*/
    u_copp_con_cnf (acse_conn, P_CON_RESULT_PROVIDER_REJ,
      cpr_info.provider_reason);
    }
  else if (cpr_info.bad_pc_deflist)
    {
    COPP_LOG_ERR1 ("COPP-ERROR: Unsupported P-context in CPR received for conn %d",
      acse_conn->user_conn_id);
    abort_reason = 6;			/* invalid-ppdu-parameter-value	*/
    /* Don't send ARP PPDU.  Remote node is already rejecting connect.	*/
    /* Pass P-P-Abort.ind to COPP-user.					*/
    u_copp_p_abort_ind (acse_conn, abort_reason);
    }
  else
    {		/* User reject		*/
    COPP_LOG_DEC2 ("P-CONNECT.cnf-:  acse_conn_id =0x%08X  user_conn_id =%4ld",
      acse_conn, acse_conn->user_conn_id);
    COPP_LOG_DECC1 ("User data length: %d", acse_conn->apdu_len);
    COPP_LOG_DECH (acse_conn->apdu_len, acse_conn->apdu_ptr);

    u_copp_con_cnf (acse_conn, P_CON_RESULT_USER_REJ, 0);
    }
  acse_conn->copp_state = COPP_STATE_IDLE;	/* No matter what	*/
  }
#endif	/* !defined (CALLED_ONLY)	*/

	/*======================================================*/
	/*	FUNCTIONS BELOW USED FOR "CPR" DECODE		*/
	/*							*/
	/*======================================================*/

/************************************************************************/
/*			START_p_cpr					*/
/************************************************************************/
static ST_VOID START_p_cpr (ASN1_DEC_CTXT *aCtx)
  {
  ASN1R_TAG_ADD (aCtx, CTX,0,decode_version);
  ASN1R_TAG_ADD (aCtx, CTX,3,decode_responding_psel);
  ASN1R_TAG_ADD (aCtx, CTX|CONSTR,5,START_pc_def_result_list);
  ASN1R_TAG_ADD (aCtx, CTX,7,decode_default_context_result);
  ASN1R_TAG_ADD (aCtx, CTX,10,decode_provider_reason);
  ASN1R_TAG_ADD (aCtx, APP|CONSTR,1,START_p_user_data);
  aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = END_p_cpr;
  }
/************************************************************************/
/*			decode_version					*/
/************************************************************************/
static ST_VOID decode_version (ASN1_DEC_CTXT *aCtx)
  {
  asn1r_get_bitstr (aCtx, &cpr_info.version_bit_str, 8);
  ASN1R_TAG_ADD (aCtx, CTX,3,decode_responding_psel);
  ASN1R_TAG_ADD (aCtx, CTX|CONSTR,5,START_pc_def_result_list);
  ASN1R_TAG_ADD (aCtx, CTX,7,decode_default_context_result);
  ASN1R_TAG_ADD (aCtx, CTX,10,decode_provider_reason);
  ASN1R_TAG_ADD (aCtx, APP|CONSTR,1,START_p_user_data);
  }
/************************************************************************/
/*			decode_responding_psel				*/
/************************************************************************/
static ST_VOID decode_responding_psel (ASN1_DEC_CTXT *aCtx)
  {
  cpr_info.responding_psel = aCtx->asn1r_field_ptr-1;
  /* Primitive CAN'T be indef len, so asn1_skip_elmnt is safe here.	*/
  asn1_skip_elmnt (aCtx);		/* Don't bother decoding it.		*/
  ASN1R_TAG_ADD (aCtx, CTX|CONSTR,5,START_pc_def_result_list);
  ASN1R_TAG_ADD (aCtx, CTX,7,decode_default_context_result);
  ASN1R_TAG_ADD (aCtx, CTX,10,decode_provider_reason);
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
    cpr_info.bad_pc_deflist = SD_TRUE;
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
/*       cpr_info.bad_pc_deflist = SD_TRUE					*/
/************************************************************************/
static ST_VOID decode_tsn2 (ASN1_DEC_CTXT *aCtx)
  {
MMS_OBJ_ID tsn;

  if (asn1r_get_objid (aCtx, tsn.comps,&tsn.num_comps))
    {
    asn1r_set_dec_err (aCtx, ASN1E_INVALID_BOOLEAN);
    return;
    }
  if (asn1_objidcmp (&tsn, &asn1_obj_id) != 0)
    {					/* TSN better be ASN1		*/
    cpr_info.bad_pc_deflist = SD_TRUE;
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
  ASN1R_TAG_ADD (aCtx, CTX,7,decode_default_context_result);
  ASN1R_TAG_ADD (aCtx, CTX,10,decode_provider_reason);
  ASN1R_TAG_ADD (aCtx, APP|CONSTR,1,START_p_user_data);
  }
/************************************************************************/
/*			decode_default_context_result			*/
/************************************************************************/
static ST_VOID decode_default_context_result (ASN1_DEC_CTXT *aCtx)
  {	/* Ignore value, because we never proposed Default-context-name.*/
  if (asn1r_get_i8 (aCtx, &cpr_info.default_context_result))
    {
    asn1r_set_dec_err (aCtx, ASN1E_INVALID_BOOLEAN); 
    return;                          
    }
  ASN1R_TAG_ADD (aCtx, CTX,10,decode_provider_reason);
  ASN1R_TAG_ADD (aCtx, APP|CONSTR,1,START_p_user_data);
  }
/************************************************************************/
/*			decode_provider_reason				*/
/************************************************************************/
static ST_VOID decode_provider_reason (ASN1_DEC_CTXT *aCtx)
  {
  if (asn1r_get_i8 (aCtx, &cpr_info.provider_reason))
    {
    asn1r_set_dec_err (aCtx, ASN1E_INVALID_BOOLEAN); 
    return;                          
    }
  /* Marben sends bad p_user_data in this case. Skip over it.		*/
  COPP_LOG_DEC0 ("WARNING: Ignoring P-user-data received on CPR.");
  ASN1R_TAG_ADD (aCtx, APP|CONSTR,1,SKIP_p_user_data);
  }

/************************************************************************/
/*			SKIP_p_user_data				*/
/************************************************************************/
ST_VOID SKIP_p_user_data (ASN1_DEC_CTXT *aCtx)
  {
  aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = END_skip_p_user_data;
  asn1r_parse_next (aCtx, parse_next_done);
  }
/************************************************************************/
/*			parse_next_done					*/
/************************************************************************/
static ST_VOID parse_next_done (ASN1_DEC_CTXT *aCtx)
  {	/* called when "asn1r_parse_next (aCtx," is done	*/
  }
/************************************************************************/
/*			END_skip_p_user_data				*/
/************************************************************************/
static ST_VOID END_skip_p_user_data (ASN1_DEC_CTXT *aCtx)
  {
  }
/************************************************************************/
/*			END_p_cpr					*/
/************************************************************************/
static ST_VOID END_p_cpr (ASN1_DEC_CTXT *aCtx)
  {
  aCtx->asn1r_decode_done_fun = NULL;		/* done decoding		*/
  }


