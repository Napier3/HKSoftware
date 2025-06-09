/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*      	  1996, All Rights Reserved.		        	*/
/*									*/
/*		    PROPRIETARY AND CONFIDENTIAL			*/
/*									*/
/* MODULE NAME : tp4_dec.c						*/
/* PRODUCT(S)  : Lean-T Stack						*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/*		This module implements the decoding of the TPDUs.	*/
/*									*/
/*  For information see the:						*/
/*	ISO 8073 "Information processing systems - Open Systems		*/
/*	Interconnections - Connection oriented transport protocol	*/
/*	specification.							*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*									*/
/*			tp_decode_nsdu					*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 04/13/00  JRB    11     Lint cleanup.				*/
/* 12/27/99  EJV    10     Changed _ERR0 to _IND0 logging for decoding	*/
/*			   connectionless PDU (see case TP_PDU_TYPE_UD)	*/
/* 01/28/99  JRB    09     Use funct ptr "cltp_decode_nsdu_fun" to	*/
/*			   control if CLTP decoding allowed.		*/
/* 08/13/98  JRB    08     Lint cleanup.				*/
/* 08/26/97  JRB    07     tp_decode_* functs moved to "tpx_dec.c" &	*/
/*			   args changed so TP0 can use them too.	*/
/* 05/27/97  JRB   7.00    MMSEASE 7.0 release.				*/
/* 05/07/97  JRB    06     Changed non-ANSI "%hu" to "%u".		*/
/* 11/22/96  JRB    05     Add CLCOTP code to handle CLTP decoding	*/
/*			   from tp_decode_nsdu.				*/
/* 10/04/96  JRB    04     Use max_tpdu_len_enc (binary encoded value).	*/
/* 09/09/96  JRB    03     Fix comments.				*/
/* 07/24/96  EJV    02     Changed ST_UCHAR buf to char buf in tp_log_tsdu	*/
/* 06/20/96  EJV    01     Created					*/
/************************************************************************/
#include "glbtypes.h"
#include "sysincs.h"
#include "tp4_log.h"
#include "checksum.h"
#include "tp4.h"
#include "tp4_encd.h"

#ifdef DEBUG_SISCO
SD_CONST static ST_CHAR *SD_CONST thisFileName = __FILE__;
#endif

/************************************************************************/
/* Global Variables							*/
/************************************************************************/
ST_VOID (*cltp_decode_nsdu_fun) (N_UNITDATA *n_unitdata);

/************************************************************************/
/*			tp_decode_nsdu					*/
/*----------------------------------------------------------------------*/
/* Function used to decode a received TPDU. The n_unitdata may contain	*/
/* few TPDUs.  We will try to decode all of them in this function.	*/
/* Note that there can be only one CR,DR,CC,DT,or ED TPDU concatinated	*/
/* with other TPDUs (this TPDU should be the last in NSDU).		*/
/*									*/
/* Parameters:								*/
/*	N_UNITDATA *n_unitdata	Pointer to data struct from network.	*/
/*									*/
/* Return:								*/
/*	SD_SUCCESS (0)		If decoding successful			*/
/*	SD_FAILURE			otherwise				*/
/************************************************************************/
ST_RET tp_decode_nsdu (N_UNITDATA *n_unitdata)
{
ST_RET ret;
ST_UCHAR	type;  
ST_UCHAR  *buf;			/* pointer to current TPDU in data_buf	*/
ST_UINT16  len_proc; 		/* len of processed TPDUs from data_buf	*/
ST_UINT16	len;		/* len of processed TPDU by a dec func	*/
ST_BOOLEAN	done;		/* flag set if a TPDU with user data has*/
				/* been decoded, or error occurred so	*/
				/* we don't continue while loop forever	*/
ST_UCHAR *pdu_ptr;
ST_UINT16 pdu_len;
TPDU_CX  tpdu_cx_rx;	/* tpdu_cr_rx or tpdu_cc_rx		*/
TPDU_DR	 tpdu_dr_rx;
TPDU_DC	 tpdu_dc_rx;
TPDU_DT	 tpdu_dt_rx;
TPDU_AK	 tpdu_ak_rx;

  ret = SD_SUCCESS;
  len_proc = 0;

  buf = n_unitdata->data_buf;	/* start from first TPDU in data_buf	*/

  done = SD_FALSE;
  while (!done && len_proc < n_unitdata->data_len)
    {
    /* get the TPDU type (from the second octet, bits 4-7) */

    type = (ST_UCHAR) (buf [len_proc+1] & TP_PDU_MASK_CDT);

    /* Based on type of TPDU (CR, CC, DT, etc.) call appropriate decode	*/
    /* subfunction.							*/

    pdu_ptr = &n_unitdata->data_buf [len_proc];
    pdu_len = n_unitdata->data_len - len_proc;
    switch (type)
      {
      case TP_PDU_TYPE_CR:
      case TP_PDU_TYPE_CC:
        if ((len = tp_decode_cx (&tpdu_cx_rx, pdu_ptr, pdu_len, type,
                  TP_PDU_MAX_SIZE_128)) != 0)	/* Default TPDU size=128*/
          {
          len_proc += len;
          /* set the rem_mac and rem_nsap pointers */
          tpdu_cx_rx.rem_mac = n_unitdata->rem_mac;
          tpdu_cx_rx.rem_nsap = n_unitdata->rem_nsap;

          tp_log_tsdu ((ST_VOID *) &tpdu_cx_rx, type, TP_IND);
          /* This is the only step different in processing CR or CC.	*/
          if (type == TP_PDU_TYPE_CR)
            tp_process_cr (&tpdu_cx_rx);
          else
            tp_process_cc (&tpdu_cx_rx);
          }
        done = SD_TRUE;	/* TPDU with user data, do not continue loop	*/
      break;

      case TP_PDU_TYPE_DR:
        if ((len = tp_decode_dr (&tpdu_dr_rx, pdu_ptr, pdu_len)) != 0)
          {
          len_proc += len;
          /* set the rem_mac and rem_nsap pointers */
          tpdu_dr_rx.rem_mac = n_unitdata->rem_mac;
          tpdu_dr_rx.rem_nsap = n_unitdata->rem_nsap;

          tp_log_tsdu ((ST_VOID *) &tpdu_dr_rx, TP_PDU_TYPE_DR, TP_IND);
          tp_process_dr (&tpdu_dr_rx);
          }
        done = SD_TRUE;	/* TPDU with user data, do not continue loop	*/
      break;

      case TP_PDU_TYPE_DC:
        if ((len = tp_decode_dc (&tpdu_dc_rx, pdu_ptr)) > 0)
          {
          len_proc += len;
          /* set the rem_mac and rem_nsap pointers */
          tpdu_dc_rx.rem_mac = n_unitdata->rem_mac;
          tpdu_dc_rx.rem_nsap = n_unitdata->rem_nsap;

          tp_log_tsdu ((ST_VOID *) &tpdu_dc_rx, TP_PDU_TYPE_DC, TP_IND);
          tp_process_dc (&tpdu_dc_rx);
          }
        else
          /* 0 bytes has been processed we should exit, otherwise we	*/
          /* will loop forever.						*/
          done = SD_TRUE;
      break;

      case TP_PDU_TYPE_DT:
        if ((len = tp_decode_dt (&tpdu_dt_rx, pdu_ptr, pdu_len)) != 0)
          {
          len_proc += len;
          /* set the rem_mac and rem_nsap pointers */
          tpdu_dt_rx.rem_mac = n_unitdata->rem_mac;
          tpdu_dt_rx.rem_nsap = n_unitdata->rem_nsap;

          tp_log_tsdu ((ST_VOID *) &tpdu_dt_rx, TP_PDU_TYPE_DT, TP_IND);
          tp_process_dt (&tpdu_dt_rx);
          }
        done = SD_TRUE;	/* TPDU with user data, do not continue loop	*/
      break;

      case TP_PDU_TYPE_AK:
        if ((len = tp_decode_ak (&tpdu_ak_rx, pdu_ptr)) > 0)
          {
          len_proc += len;
          /* set the rem_mac and rem_nsap pointers */
          tpdu_ak_rx.rem_mac = n_unitdata->rem_mac;
          tpdu_ak_rx.rem_nsap = n_unitdata->rem_nsap;

          tp_log_tsdu ((ST_VOID *) &tpdu_ak_rx, TP_PDU_TYPE_AK, TP_IND);
          tp_process_ak (&tpdu_ak_rx);
          }
        else
          /* 0 bytes has been processed we should exit, otherwise we	*/
          /* will loop forever.						*/
          done = SD_TRUE;
      break;

      case TP_PDU_TYPE_RJ:
        if ((len = tp_decode_rj (pdu_ptr)) > 0)
          len_proc += len;
        else
          /* 0 bytes has been processed we should exit, otherwise we	*/
          /* will loop forever.						*/
          done = SD_TRUE;
      break;

      case TP_PDU_TYPE_ER:
        /* we need the length of the ER TPDU, so we call the decoding	*/
        if ((len = tp_decode_er (pdu_ptr)) > 0)
          len_proc += len;
        else
          /* 0 bytes has been processed we should exit, otherwise we	*/
          /* will loop forever.						*/
          done = SD_TRUE;
      break;

      case TP_PDU_TYPE_ED:	/* we do not support expedited data	*/
      case TP_PDU_TYPE_EA:
        TP_LOG_ERR0 ("TP-ERROR: decode ED or EA TPDU failed (not supported)");
        done = SD_TRUE;	/* TPDU with user data, do not continue loop	*/
      break;		/* Do nothing					*/

      case TP_PDU_TYPE_UD:
        if (cltp_decode_nsdu_fun)
          (*cltp_decode_nsdu_fun) (n_unitdata);	/* Handle CLTP event.	*/
        else
          {
          /* Just notify No error logging required if function no provided */
          TP_LOG_IND0 ("decode UD TPDU failed (not supported)");
          }
        len_proc = n_unitdata->data_len;	/* Make len check happy	*/
        done = SD_TRUE;	/* Only one UD allowed.  Do not continue loop	*/
      break;
        
      default:		/* type unknown, we should exit	decoding	*/
        TP_LOG_ERR1 ("TP-ERROR: decode TPDU failed (invalid type %2.2X)",
	  (unsigned) type);
        done = SD_TRUE;
      break;
      }	/* end "switch"	*/
    } /* end "while" */

  if (len_proc < n_unitdata->data_len)
    {
    /* some TPDUs from n_unitdata have not been	processed */

    TP_LOG_ERR2 ("TP-ERROR: decoding NSDU problem (not all TPDUs have been decoded, NSDU length = %u, length processed = %u)",
      n_unitdata->data_len, len_proc);
    ret = SD_FAILURE;
    }

  return (ret);
}


