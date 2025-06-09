/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*	(c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*	1996 All Rights Reserved					*/
/*									*/
/* MODULE NAME : tp4_hc.c						*/
/* PRODUCT(S)  : Lean-T Stack						*/
/*									*/
/* MODULE DESCRIPTION :							*/
/*	Functions for Hard Coding TP4 configuration parameters.		*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*	tp4_config ()							*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev     Comments					*/
/* --------  ---  ------   -------------------------------------------  */
/* 01/10/00  RKR    04     Changed max_spdu_outst & credits from 2 to 4	*/
/* 02/20/98  JRB    03     Don't set tp4_debug_sel. Set tp_cfg.ak_delay	*/
/*			   Don't set max_spdu_len (OBSOLETE).		*/
/* 11/10/97  JRB    02     Added TP0.					*/
/* 05/27/97  JRB   7.00    MMSEASE 7.0 release.				*/
/* 07/17/96  JRB    01     Created					*/
/************************************************************************/

#include "glbtypes.h"
#include "sysincs.h"
#include "tp4api.h"		/* User definitions for tp4	*/

/************************************************************************/
/* tp4_config								*/
/* This function fills in the "tp_cfg" structure and sets		*/
/* "tp4_debug_sel".							*/
/* Parameters:								*/
/*	ST_VOID			none				       	*/
/* Return:								*/
/*	ST_INT			SD_SUCCESS or				*/
/*				errcode					*/
/************************************************************************/
ST_RET tp4_config (ST_VOID)
  {
#ifdef TP4_ENABLED
  tp_cfg.max_tpdu_len = 1024;	/* max len of TPDU.  Base on SNPDU size.*/
				/* Use to allocate TPDU buffers.	*/
  tp_cfg.max_rem_cdt = 4;	/* Max credits we can handle.		*/
				/* Will allocate this many TPDU_DT	*/
				/* structs.				*/
				/* CRITICAL: MUST BE POWER OF 2.	*/
  tp_cfg.loc_cdt = 4;		/* CDT value we will ALWAYS send in ACK	*/
				/* We only accept in-sequence TPDUs so	*/
				/* only purpose of this is to		*/
				/* allow peer to send ahead.		*/
  tp_cfg.max_spdu_outst = 4;	/* Max # of SPDUs outstanding per conn.	*/
				/* Will allocate this many SPDU_INFO	*/
				/* structs for transmit queue.		*/
				/* CRITICAL: MUST BE POWER OF 2.	*/
  tp_cfg.max_num_conns = 4;	/* Max # Connections			*/
  tp_cfg.window_time = 10;	/* Window Time				*/
  tp_cfg.inact_time = 120;	/* Inactivity Time			*/
  tp_cfg.retrans_time = 10;	/* Retransmission Time			*/
  tp_cfg.max_trans = 2;		/* Max # of transmissions of a TPDU	*/
  tp_cfg.ak_delay = 2;		/* # of loops to delay sending AK.	*/
#endif	/* TP4_ENABLED	*/

#ifdef TP0_ENABLED
  tp0_cfg.max_tpdu_len = 8192;
  tp0_cfg.max_num_conns = 4;
#endif	/* TP0_ENABLED	*/
  return (SD_SUCCESS);
  }
