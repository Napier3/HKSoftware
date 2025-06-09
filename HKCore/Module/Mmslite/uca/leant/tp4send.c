/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*	(c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*	1996 All Rights Reserved					*/
/*									*/
/* MODULE NAME : tp4send.c						*/
/* PRODUCT(S)  : Lean-T Stack						*/
/*									*/
/* MODULE DESCRIPTION :							*/
/*	TP4 functions for sending TPDUs.				*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*	tp_send_dt							*/
/*	tp_send_ak							*/
/*	tp_send_cr							*/
/*	tp_send_cc							*/
/*	tp_send_dr							*/
/*	tp_send_dc							*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev     Comments					*/
/* --------  ---  ------   -------------------------------------------  */
/* 08/13/98  JRB    05     Lint cleanup.				*/
/* 08/26/97  JRB    04     Use TP_PDU_TYPE_* as arg to tp_log_tsdu.	*/
/* 05/27/97  JRB   7.00    MMSEASE 7.0 release.				*/
/* 09/09/96  JRB    03     Added tp_send_dt_and_ak function.		*/
/* 09/03/96  JRB    02     Added code to tp_send_cr.			*/
/* 07/17/96  JRB    01     Created					*/
/************************************************************************/
static char *thisFileName = __FILE__;	/* For TP4_EXCEPT and slog macros*/

#include "glbtypes.h"
#include "sysincs.h"
#include "mem_chk.h"
#include "tp4_log.h"
#include "tp4api.h"		/* User definitions for tp4	*/
#include "tp4.h"		/* Internal definitions for tp4	*/
#include "tp4_encd.h"		/* encoding/decoding definitions*/

/************************************************************************/
/* tp_send_dt								*/
/* Send a DT (Data) TPDU.						*/
/************************************************************************/
ST_VOID tp_send_dt (TPDU_DT *tpdu_dt)
  {
N_UNITDATA *n_unitdata;

  tp_log_tsdu ((ST_VOID *) tpdu_dt, TP_PDU_TYPE_DT, TP_REQ);

  if ((n_unitdata = clnp_alloc (tpdu_dt->udata_len + TP_HEAD_LEN_DT)) == NULL)
    {
    /* We're probably dead, but maybe we'll recover. This would look	*/
    /* like a TPDU that gets lost on the network.			*/
    TP4_EXCEPT ();
    return;		/* Make sure "retrans_time" already set.		*/
    }

  /* Fill in n_unitdata with TPDU (in data_buf) and remote address info	*/

  /* Encode DT TPDU in n_unitdata->data_buf */
  n_unitdata->data_len = tp_encode_dt (n_unitdata->data_buf, tpdu_dt);

  if (n_unitdata->data_len > 0)
    {
    memcpy (n_unitdata->rem_nsap, tpdu_dt->rem_nsap,
          tpdu_dt->rem_nsap[0]+1);	/* First byte is len.	*/
    memcpy (n_unitdata->rem_mac, tpdu_dt->rem_mac, CLNP_MAX_LEN_MAC);
    n_unitdata->rem_mac_valid = SD_TRUE;	/* Always SD_TRUE when conn made	*/
    clnp_write (n_unitdata);
    }
  }

/************************************************************************/
/* tp_send_ak								*/
/* Send AK TPDU								*/
/************************************************************************/
ST_VOID tp_send_ak (TPDU_AK *tpdu_ak)
  {
N_UNITDATA *n_unitdata;

  tp_log_tsdu ((ST_VOID *) tpdu_ak, TP_PDU_TYPE_AK, TP_REQ);

  if ((n_unitdata = clnp_alloc (TP_MAX_LEN_AK)) == NULL)
    {
    /* We're probably dead, but maybe we'll recover. This would look	*/
    /* like a TPDU that gets lost on the network.			*/
    TP4_EXCEPT ();
    return;		/* Make sure "retrans_time" already set.		*/
    }

  /* Fill in n_unitdata with TPDU (in data_buf) and remote address info	*/

  /* Encode TPDU in n_unitdata->data_buf */
  n_unitdata->data_len = tp_encode_ak (n_unitdata->data_buf, tpdu_ak);

  if (n_unitdata->data_len > 0)
    {
    memcpy (n_unitdata->rem_nsap, tpdu_ak->rem_nsap,
          tpdu_ak->rem_nsap[0]+1);	/* First byte is len.	*/
    memcpy (n_unitdata->rem_mac, tpdu_ak->rem_mac, CLNP_MAX_LEN_MAC);
    n_unitdata->rem_mac_valid = SD_TRUE;	/* Always SD_TRUE when conn made	*/
    clnp_write (n_unitdata);
    }
  }

/************************************************************************/
/* tp_send_cr								*/
/* Send a CR (Connect Request) TPDU.					*/
/************************************************************************/
ST_VOID tp_send_cr (TPDU_CX *tpdu_cr)
  {
N_UNITDATA *n_unitdata;

  tp_log_tsdu ((ST_VOID *) tpdu_cr, TP_PDU_TYPE_CR, TP_REQ);

  if ((n_unitdata = clnp_alloc (TP_MAX_LEN_CX)) == NULL)
    {
    /* We're probably dead, but maybe we'll recover. This would look	*/
    /* like a TPDU that gets lost on the network.			*/
    TP4_EXCEPT ();
    return;		/* Make sure "retrans_time" already set.		*/
    }

  /* Fill in n_unitdata with TPDU (in data_buf) and remote address info	*/

  /* Encode TPDU in n_unitdata->data_buf */
  n_unitdata->data_len = tp_encode_cx (n_unitdata->data_buf, tpdu_cr,
  				       TP_PDU_TYPE_CR);

  if (n_unitdata->data_len > 0)
    {
    memcpy (n_unitdata->rem_nsap, tpdu_cr->rem_nsap,
          tpdu_cr->rem_nsap[0]+1);	/* First byte is len.	*/
    n_unitdata->rem_mac_valid = SD_FALSE;	/* Always SD_FALSE when connecting	*/
    clnp_write (n_unitdata);
    }
  }

/************************************************************************/
/* tp_send_cc								*/
/* Send a CC (Connect Confirm) TPDU.					*/
/************************************************************************/
ST_VOID tp_send_cc (TPDU_CX *tpdu_cc)
  {
N_UNITDATA *n_unitdata;

  tp_log_tsdu ((ST_VOID *) tpdu_cc, TP_PDU_TYPE_CC, TP_REQ);

  if ((n_unitdata = clnp_alloc (TP_MAX_LEN_CX)) == NULL)
    {
    /* We're probably dead, but maybe we'll recover. This would look	*/
    /* like a TPDU that gets lost on the network.			*/
    TP4_EXCEPT ();
    return;		/* Make sure "retrans_time" already set.		*/
    }

  /* Fill in n_unitdata with TPDU (in data_buf) and remote address info	*/

  /* Encode TPDU in n_unitdata->data_buf */
  n_unitdata->data_len = tp_encode_cx (n_unitdata->data_buf, tpdu_cc,
  				       TP_PDU_TYPE_CC);

  if (n_unitdata->data_len > 0)
    {
    memcpy (n_unitdata->rem_nsap, tpdu_cc->rem_nsap,
          tpdu_cc->rem_nsap[0]+1);	/* First byte is len.	*/
    memcpy (n_unitdata->rem_mac, tpdu_cc->rem_mac, CLNP_MAX_LEN_MAC);
    n_unitdata->rem_mac_valid = SD_TRUE;	/* Always SD_TRUE when conn made	*/
    clnp_write (n_unitdata);
    }
  }

/************************************************************************/
/* tp_send_dr								*/
/* Send a DR (Disconnect Request) TPDU.					*/
/************************************************************************/
ST_VOID tp_send_dr (TPDU_DR *tpdu_dr)
  {
N_UNITDATA *n_unitdata;

  tp_log_tsdu ((ST_VOID *) tpdu_dr, TP_PDU_TYPE_DR, TP_REQ);

  if ((n_unitdata = clnp_alloc (TP_MAX_LEN_DR)) == NULL)
    {
    /* We're probably dead, but maybe we'll recover. This would look	*/
    /* like a TPDU that gets lost on the network.			*/
    TP4_EXCEPT ();
    return;
    }

  /* Fill in n_unitdata with TPDU (in data_buf) and remote address info	*/

  /* Encode TPDU in n_unitdata->data_buf */
  n_unitdata->data_len = tp_encode_dr (n_unitdata->data_buf, tpdu_dr);

  if (n_unitdata->data_len > 0)
    {
    memcpy (n_unitdata->rem_nsap, tpdu_dr->rem_nsap,
          tpdu_dr->rem_nsap[0]+1);	/* First byte is len.	*/
    memcpy (n_unitdata->rem_mac, tpdu_dr->rem_mac, CLNP_MAX_LEN_MAC);
    n_unitdata->rem_mac_valid = SD_TRUE;	/* Always SD_TRUE when conn made	*/
    clnp_write (n_unitdata);
    }
  }

/************************************************************************/
/* tp_send_dc								*/
/* Send a DC (Disconnect Confirm) TPDU.					*/
/************************************************************************/
ST_VOID tp_send_dc (TPDU_DC *tpdu_dc)
  {
N_UNITDATA *n_unitdata;

  tp_log_tsdu ((ST_VOID *) tpdu_dc, TP_PDU_TYPE_DC, TP_REQ);

  if ((n_unitdata = clnp_alloc (TP_MAX_LEN_DC)) == NULL)
    {
    /* We're probably dead, but maybe we'll recover. This would look	*/
    /* like a TPDU that gets lost on the network.			*/
    TP4_EXCEPT ();
    return;
    }

  /* Fill in n_unitdata with TPDU (in data_buf) and remote address info	*/

  /* Encode TPDU in n_unitdata->data_buf */
  n_unitdata->data_len = tp_encode_dc (n_unitdata->data_buf, tpdu_dc);

  if (n_unitdata->data_len > 0)
    {
    memcpy (n_unitdata->rem_nsap, tpdu_dc->rem_nsap,
          tpdu_dc->rem_nsap[0]+1);	/* First byte is len.	*/
    memcpy (n_unitdata->rem_mac, tpdu_dc->rem_mac, CLNP_MAX_LEN_MAC);
    n_unitdata->rem_mac_valid = SD_TRUE;	/* Always SD_TRUE when conn made	*/
    clnp_write (n_unitdata);
    }
  }

/************************************************************************/
/* tp_send_dt_and_ak							*/
/* Send an AK and a DT (Data) TPDU.					*/
/************************************************************************/
ST_VOID tp_send_dt_and_ak (TPDU_DT *tpdu_dt, TPDU_AK *tpdu_ak)
  {
N_UNITDATA *n_unitdata;
ST_UINT16  ak_len;
ST_UINT16  dt_len;

  tp_log_tsdu ((ST_VOID *) tpdu_ak, TP_PDU_TYPE_AK, TP_REQ);
  tp_log_tsdu ((ST_VOID *) tpdu_dt, TP_PDU_TYPE_DT, TP_REQ);

  if ((n_unitdata = clnp_alloc (tpdu_dt->udata_len + TP_HEAD_LEN_DT +
  				TP_MAX_LEN_AK)) == NULL)
    {
    /* We're probably dead, but maybe we'll recover. This would look	*/
    /* like a TPDU that gets lost on the network.			*/
    TP4_EXCEPT ();
    return;		/* Make sure "retrans_time" already set.		*/
    }

  /* Fill in n_unitdata with TPDU (in data_buf) and remote address info	*/

  /* Encode AK TPDU in n_unitdata->data_buf */
  ak_len = tp_encode_ak (n_unitdata->data_buf, tpdu_ak);

  if (ak_len > 0)
    {
    /* Encode DT TPDU in n_unitdata->data_buf */
    dt_len = tp_encode_dt (n_unitdata->data_buf + ak_len, tpdu_dt);

    if (dt_len > 0)
      {
      n_unitdata->data_len = ak_len + dt_len;
      memcpy (n_unitdata->rem_nsap, tpdu_dt->rem_nsap,
            tpdu_dt->rem_nsap[0]+1);	/* First byte is len.	*/
      memcpy (n_unitdata->rem_mac, tpdu_dt->rem_mac, CLNP_MAX_LEN_MAC);
      n_unitdata->rem_mac_valid = SD_TRUE;	/* Always SD_TRUE when conn made	*/
      clnp_write (n_unitdata);
      }
    }
  }

