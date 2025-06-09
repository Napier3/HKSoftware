/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*	(c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*	1997-2002, All Rights Reserved					*/
/*									*/
/*			PROPRIETARY AND CONFIDENTIAL			*/
/*									*/
/* MODULE NAME : coppdaru.c						*/
/* PRODUCT(S)  : MOSI Stack (over TP4)					*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/*		This file implements decoding of U-ABORT indication.	*/
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
/*			u_cosp_u_abort_ind 				*/
/*									*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 02/26/09  JRB    07     Fix to handle PDV len=0 or User-data len=0.	*/
/* 01/30/06  GLB    06     Integrated porting changes for VMS           */
/* 01/02/02  JRB    05     Converted to use ASN1R (re-entrant ASN1)	*/
/* 03/18/98  JRB    04     Use defines (not variables) for ASN1 errors.	*/
/* 12/22/97  JRB    03     Use ST_INT8.					*/
/* 05/27/97  JRB   7.00    MMSEASE 7.0 release.				*/
/* 03/19/97  JRB    02     General cleanup.				*/
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
/* Structure for tracking ARP/ARU decode.		*/
typedef struct
  {
#define COPP_U_ABORT	0	/* Use to set "abort_type"	*/
#define COPP_P_ABORT	1	/* Use to set "abort_type"	*/
  ST_INT8 abort_type;
  ST_INT8 abort_reason;
  ST_INT8 event_id;
  } DECODE_ARX;
static DECODE_ARX decode_arx;

static ST_VOID START_aru (ASN1_DEC_CTXT *aCtx);
static ST_VOID START_pc_identifier_list (ASN1_DEC_CTXT *aCtx);
static ST_VOID START_sequence (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_pci (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_tsn (ASN1_DEC_CTXT *aCtx);
static ST_VOID END_sequence (ASN1_DEC_CTXT *aCtx);
static ST_VOID END_pc_identifier_list (ASN1_DEC_CTXT *aCtx);
static ST_VOID END_aru (ASN1_DEC_CTXT *aCtx);

static ST_VOID START_arp (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_abort_reason (ASN1_DEC_CTXT *aCtx);
static ST_VOID decode_event_id (ASN1_DEC_CTXT *aCtx);
static ST_VOID END_arp (ASN1_DEC_CTXT *aCtx);

/************************************************************************/
/*			u_cosp_u_abort_ind 				*/
/*----------------------------------------------------------------------*/
/* This USER function is called by the SS-Provider to indicate that a	*/
/* connection has been aborted by remote SS-user.			*/
/* 									*/
/* Parameters:								*/
/*  ACSE_CONN	*acse_conn		Pointer to connection info	*/
/*	  								*/
/* Return:								*/
/*	ST_VOID								*/
/************************************************************************/
ST_VOID u_cosp_u_abort_ind (ACSE_CONN *acse_conn)
  {
ASN1_DEC_CTXT localDecCtx;	/* For readability, use "aCtx" to access this.*/
ASN1_DEC_CTXT *aCtx = &localDecCtx;

  memset (aCtx, 0, sizeof (ASN1_DEC_CTXT));	/* CRITICAL: start clean	*/

  if (acse_conn->copp_state == COPP_STATE_IDLE)
    {
    COPP_LOG_ERR1 ("COPP-ERROR: Cannot process S-U-ABORT.ind (Illegal state=%d)",
      acse_conn->copp_state);
    return;
    }

  aCtx->asn1r_decode_method = ASN1_TAG_METHOD;			/* Use asn1_tag method for decoding. */
  aCtx->asn1r_decode_done_fun = asn1r_done_err;	/* done function = error fun 	*/
  aCtx->asn1r_err_fun = NULL;			/* set up error detected fun 	*/

  decode_acse_conn = acse_conn;	/* Save in global so asn1r_decode_asn1 (aCtx,	*/
				/* can fill it in.			*/

  /* Set the PCI to be used during P-User-Data decode.			*/
  expected_pdv_pci = decode_acse_conn->pciacse;

  p_user_data_is_outer = SD_FALSE;	/* P-User-data IS NOT outermost constr.	*/

  /* CRITICAL: Init APDU ptr & len. Changed only if APDU found in msg.	*/
  acse_conn->apdu_ptr = NULL;
  acse_conn->apdu_len = 0;
  /* CRITICAL: Init global PDV ptr & len. Changed only if PDV found in msg.*/
  pdv_data_ptr = NULL;
  pdv_data_len = 0;

  ASN1R_TAG_ADD (aCtx, CTX|CONSTR,0,START_aru);
  ASN1R_TAG_ADD (aCtx, UNI|CONSTR,SEQ_CODE,START_arp);
  asn1r_decode_asn1 (aCtx, acse_conn->ppdu_ptr,acse_conn->ppdu_len);
  if (aCtx->asn1r_pdu_dec_err != NO_DECODE_ERR)
    {		/* DECODE FAILED	*/
    /* Couldn't decode ARP or ARU, so pass up as P-P-Abort.ind with	*/
    /* reason = unrecognized-ppdu					*/
    decode_arx.abort_reason = 1;	/* unrecognized-ppdu.		*/
    COPP_LOG_ERR1 ("COPP-ERROR: ASN.1 decode of S-U-Abort.ind failed, err=%d", aCtx->asn1r_pdu_dec_err);
    COPP_LOG_DEC3 ("P-P-ABORT.ind:   acse_conn_id =0x%08X  user_conn_id =%4ld  reason =%d",
        acse_conn, acse_conn->user_conn_id, decode_arx.abort_reason);
    u_copp_p_abort_ind (acse_conn, decode_arx.abort_reason);
    }
  else
    {		/* DECODE SUCCESSFUL	*/
    if (decode_arx.abort_type == COPP_U_ABORT)
      {		/* This is P-U-Abort	*/
      COPP_LOG_DEC2 ("P-U-ABORT.ind:   acse_conn_id =0x%08X  user_conn_id =%4ld",
        acse_conn, acse_conn->user_conn_id);
      COPP_LOG_DECC1 ("User data length: %d", acse_conn->apdu_len);
      COPP_LOG_DECH (acse_conn->apdu_len, acse_conn->apdu_ptr);
      u_copp_u_abort_ind (acse_conn);
      }
    else
      {		/* This is P-P-Abort	*/
      COPP_LOG_DEC4 ("P-P-ABORT.ind:   acse_conn_id =0x%08X  user_conn_id =%4ld  reason =%d, event_id =%d",
        acse_conn, acse_conn->user_conn_id, decode_arx.abort_reason, decode_arx.event_id);
      u_copp_p_abort_ind (acse_conn, decode_arx.abort_reason);
      }
    }
  acse_conn->copp_state = COPP_STATE_IDLE;	/* No matter what.	*/
  }

/************************************************************************/
/* START_aru								*/
/************************************************************************/
static ST_VOID START_aru (ASN1_DEC_CTXT *aCtx)
  {
  decode_arx.abort_type = COPP_U_ABORT;		/* Set type to U-Abort	*/
  ASN1R_TAG_ADD (aCtx, CTX|CONSTR,0,START_pc_identifier_list);
  ASN1R_TAG_ADD (aCtx, APP|CONSTR,1,START_p_user_data);
  aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = END_aru;
  }
/************************************************************************/
/* START_pc_identifier_list							*/
/************************************************************************/
static ST_VOID START_pc_identifier_list (ASN1_DEC_CTXT *aCtx)
  {
  ASN1R_TAG_ADD (aCtx, UNI|CONSTR,SEQ_CODE,START_sequence);
  aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = END_pc_identifier_list;
  }
/************************************************************************/
/* START_sequence							*/
/************************************************************************/
static ST_VOID START_sequence (ASN1_DEC_CTXT *aCtx)
  {
  ASN1R_TAG_ADD (aCtx, UNI,INT_CODE,decode_pci);
  aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = END_sequence;
  }
/************************************************************************/
/* decode_pci								*/
/************************************************************************/
static ST_VOID decode_pci (ASN1_DEC_CTXT *aCtx)
  {
ST_INT8 pci;
  if (asn1r_get_i8 (aCtx, &pci))
    {
    asn1r_set_dec_err (aCtx, ASN1E_INVALID_BOOLEAN); 
    return;                          
    }
  ASN1R_TAG_ADD (aCtx, UNI,OBJ_ID_CODE,decode_tsn);
  }
/************************************************************************/
/* decode_tsn								*/
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
    asn1r_set_dec_err (aCtx, ASN1E_INVALID_BITSTR);
    return;
    }
  }
/************************************************************************/
/* END_sequence								*/
/************************************************************************/
static ST_VOID END_sequence (ASN1_DEC_CTXT *aCtx)
  {
  /* May be another context.	*/
  ASN1R_TAG_ADD (aCtx, UNI|CONSTR,SEQ_CODE,START_sequence);
  }
/************************************************************************/
/* END_pc_identifier_list						*/
/************************************************************************/
static ST_VOID END_pc_identifier_list (ASN1_DEC_CTXT *aCtx)
  {
  ASN1R_TAG_ADD (aCtx, APP|CONSTR,1,START_p_user_data);
  }
/************************************************************************/
/* END_aru								*/
/************************************************************************/
static ST_VOID END_aru (ASN1_DEC_CTXT *aCtx)
  {
  aCtx->asn1r_decode_done_fun = NULL;		/* done decoding		*/
  }


/************************************************************************/
/* START_arp								*/
/************************************************************************/
static ST_VOID START_arp (ASN1_DEC_CTXT *aCtx)
  {
  decode_arx.abort_type = COPP_P_ABORT;		/* Set type to P-Abort	*/
  ASN1R_TAG_ADD (aCtx, CTX,0,decode_abort_reason);
  ASN1R_TAG_ADD (aCtx, CTX,1,decode_event_id);
  aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = END_arp;
  }
/************************************************************************/
/* decode_abort_reason							*/
/************************************************************************/
static ST_VOID decode_abort_reason (ASN1_DEC_CTXT *aCtx)
  {
  if (asn1r_get_i8 (aCtx, &decode_arx.abort_reason))
    {
    asn1r_set_dec_err (aCtx, ASN1E_INVALID_BOOLEAN); 
    return;                          
    }
  ASN1R_TAG_ADD (aCtx, CTX,1,decode_event_id);
  }
/************************************************************************/
/* decode_event_id							*/
/************************************************************************/
static ST_VOID decode_event_id (ASN1_DEC_CTXT *aCtx)
  {
  if (asn1r_get_i8 (aCtx, &decode_arx.event_id))
    {
    asn1r_set_dec_err (aCtx, ASN1E_INVALID_BOOLEAN); 
    return;                          
    }
  }
/************************************************************************/
/* END_arp								*/
/************************************************************************/
static ST_VOID END_arp (ASN1_DEC_CTXT *aCtx)
  {
  aCtx->asn1r_decode_done_fun = NULL;		/* done decoding		*/
  }
