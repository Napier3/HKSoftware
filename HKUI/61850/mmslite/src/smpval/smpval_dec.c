/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*	(c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*	2006-2006, All Rights Reserved.					*/
/*									*/
/*			PROPRIETARY AND CONFIDENTIAL			*/
/*									*/
/* MODULE NAME : smpval_dec.c						*/
/* PRODUCT(S)  : MMS-EASE Lite						*/
/*									*/
/* MODULE DESCRIPTION : IEC 61850-9-2 SMPVAL decode functions.		*/
/*	This module uses the new ASN.1 decode method			*/
/*      ASN1_ANYTAG_METHOD. The decoder calls the same callback		*/
/*	function (aCtx->asn1r_anytag_fun) for a any tag of any class.	*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev     Comments					*/
/* --------  ---  ------   -------------------------------------------  */
/* 12/01/06  JRB     02    Fix warnings.				*/
/* 03/20/06  JRB     01    Created					*/
/************************************************************************/
#include "glbtypes.h"
#include "sysincs.h"
#include "asn1r.h"
#include "mem_chk.h"
#include "asn1log.h"
#include "clnp_sne.h"
#include "smpval.h"
#include "clnp_log.h"

#ifdef DEBUG_SISCO
SD_CONST static ST_CHAR *SD_CONST thisFileName = __FILE__;
#endif

static ST_VOID decode_tag_asdu (ASN1_DEC_CTXT *aCtx, ST_UINT16 tagnum);

/* ASN.1 tags at top level (APPLICATION)	*/
/* Processed in "decode_tag_apdu"		*/
#define TAG_SAVPDU	(ASN1MASK_APP | ASN1MASK_CONSTR | 0)

/* ASN.1 tags at top level inside SAVPDU 	*/
/* Also processed in "decode_tag_apdu"		*/
#define TAG_NOASDU	(ASN1MASK_CTX | 0)
#define TAG_SECURITY	(ASN1MASK_CTX | 1)
#define TAG_ASDU	(ASN1MASK_CTX | ASN1MASK_CONSTR | 2)

/* ASN.1 tags inside ASDU			*/
/* Processed in "decode_tag_asdu"		*/
#define TAG_ASDU_SEQ	(ASN1MASK_UNI | ASN1MASK_CONSTR | SEQ_CODE)
#define TAG_SVID	(ASN1MASK_CTX |0)
#define TAG_DATSET	(ASN1MASK_CTX |1)
#define TAG_SMPCNT	(ASN1MASK_CTX |2)
#define TAG_CONFREV	(ASN1MASK_CTX |3)
#define TAG_REFRTM	(ASN1MASK_CTX |4)
#define TAG_SMPSYNCH	(ASN1MASK_CTX |5)
#define TAG_SMPRATE	(ASN1MASK_CTX |6)
#define TAG_SAMPLE	(ASN1MASK_CTX |7)

/* Decode state defines (i.e. what are we waiting for next)	*/
/* CRITICAL: must be in this sequence.				*/
#define STATE_WAIT_SAVPDU	0	/* initial state	*/
#define STATE_WAIT_NOASDU	1
#define STATE_WAIT_SECURITY	2
#define STATE_WAIT_ASDU		3
#define STATE_WAIT_ASDU_SEQ	4
#define STATE_WAIT_SVID		5
#define STATE_WAIT_DATSET	6
#define STATE_WAIT_SMPCNT	7
#define STATE_WAIT_CONFREV	8
#define STATE_WAIT_REFRTM	9
#define STATE_WAIT_SMPSYNCH	10
#define STATE_WAIT_SMPRATE	11
#define STATE_WAIT_SAMPLE	12

typedef struct
  {
  ST_INT state;		/* one of above defines (STATE_WAIT_*)	*/
  ST_INT asduIdx;
  } SMPVAL_DEC_CTXT;

/************************************************************************/
/* END_smpval								*/
/* Done with parse. Clear asn1r_decode_done_fun function pointer.	*/
/************************************************************************/
static ST_VOID END_smpval (ASN1_DEC_CTXT *aCtx)
  {
  aCtx->asn1r_decode_done_fun = NULL;	/* replaces error funct		*/
  }

/************************************************************************/
/* decode_tag_apdu							*/
/* Called for all 'context-specific' class tags at APDU (top) level.	*/
/************************************************************************/
static ST_VOID decode_tag_apdu (ASN1_DEC_CTXT *aCtx, ST_UINT16 tagnum)
  {
SMPVAL_MSG *smpvalMsg = (SMPVAL_MSG *) aCtx->usr_info[0];
SMPVAL_DEC_CTXT *smpvalCtx = (SMPVAL_DEC_CTXT *) aCtx->usr_info[1];

  /* This whole function is just one big switch to handle each possible id*/
  switch (tagnum)
    {
    case TAG_SAVPDU:
      if (smpvalCtx->state == STATE_WAIT_SAVPDU)
        {
        aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = END_smpval;
        smpvalCtx->state++;
        }
      else
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_TAG);	/* out of sequence	*/
      break;

    case TAG_NOASDU:
      if (smpvalCtx->state == STATE_WAIT_NOASDU)
        {
        if (asn1r_get_u16 (aCtx, &smpvalMsg->numASDU) == SD_SUCCESS)
          {
          /* CRITICAL: allocate asduArray now.	*/
          smpvalMsg->asduArray = chk_calloc (smpvalMsg->numASDU, sizeof(SMPVAL_ASDU));
          /* NOTE: because of calloc, "SmpSynch" is correctly	*/
          /*   set to default value. No need to change it if not present in PDU.*/ 
          smpvalCtx->state = STATE_WAIT_SECURITY;
          }
        else
          asn1r_set_dec_err (aCtx, ASN1E_DECODE_OTHER);
        }
      else
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_TAG);	/* out of sequence	*/
      break;

    case TAG_SECURITY:
      /* Just copy encoded "security" into smpvalMsg->securityBuf.	*/
      if (smpvalCtx->state == STATE_WAIT_SECURITY)
        {
        if (asn1r_get_octstr_varlen (aCtx, smpvalMsg->securityBuf, MAX_SMPVAL_SECURITY_LEN, &smpvalMsg->securityLen) == SD_SUCCESS)
          smpvalCtx->state = STATE_WAIT_ASDU;
        else
          asn1r_set_dec_err (aCtx, ASN1E_DECODE_OTHER);
        }
      else
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_TAG);	/* out of sequence	*/
      break;

    case TAG_ASDU:
      /* OPTIONAL "security" may not be present, so state may be either of these.*/
      if (smpvalCtx->state == STATE_WAIT_SECURITY || smpvalCtx->state == STATE_WAIT_ASDU)
        {
        aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = NULL;	/* do nothing when constr done*/
        smpvalCtx->state = STATE_WAIT_ASDU_SEQ;
        /* CRITICAL: This is start of ASDU so change callback funct.*/
        aCtx->asn1r_anytag_fun = decode_tag_asdu;	/* decode any tag	*/
        }
      else
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_TAG);	/* out of sequence	*/
      break;

    default:				/* Don't know how to decode.	*/
      CLNP_LOG_ERR1 ("Decode error: unexpected tag 0x%X.", tagnum);
      asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_TAG);
      break;
    }	/* End "switch (tagnum)"	*/
  }
/************************************************************************/
/* decode_tag_asdu							*/
/* Called for all 'context-specific' class tags at ASDU (lower) level.	*/
/************************************************************************/
static ST_VOID decode_tag_asdu (ASN1_DEC_CTXT *aCtx, ST_UINT16 tagnum)
  {
SMPVAL_ASDU *asdu;
SMPVAL_MSG *smpvalMsg = (SMPVAL_MSG *) aCtx->usr_info[0];
SMPVAL_DEC_CTXT *smpvalCtx = (SMPVAL_DEC_CTXT *) aCtx->usr_info[1];
ST_UINT8 tmp_ostr [4];

  /* NOTE: asduIdx starts at 0, and is incremented after each ASDU decoded.*/
  asdu = &smpvalMsg->asduArray[smpvalCtx->asduIdx];

  /* This whole function is just one big switch to handle each possible id*/
  switch (tagnum)
    {
    case TAG_ASDU_SEQ:
      if (smpvalCtx->state == STATE_WAIT_ASDU_SEQ)
        {
        aCtx->asn1r_c_done_fun [aCtx->asn1r_msg_level] = NULL;	/* do nothing when constr done*/
        smpvalCtx->state++;
        }
      else
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_TAG);	/* out of sequence	*/
      break;

    case TAG_SVID:					/* svID	*/
      if (smpvalCtx->state == STATE_WAIT_SVID)
        {
        if (asn1r_get_vstr_maxlen (aCtx, asdu->svID, sizeof(asdu->svID)-1) == SD_SUCCESS)
          smpvalCtx->state++;
        else
          asn1r_set_dec_err (aCtx, ASN1E_DECODE_OTHER);
        }
      else
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_TAG);	/* out of sequence	*/
      break;

    case TAG_DATSET:					/* DatSet (Optional)	*/
      if (smpvalCtx->state == STATE_WAIT_DATSET)
        {
        asdu->DatSetPres = SD_TRUE;
        if (asn1r_get_vstr_maxlen (aCtx, asdu->DatSet, sizeof(asdu->DatSet)-1) == SD_SUCCESS)
          smpvalCtx->state++;
        else
          asn1r_set_dec_err (aCtx, ASN1E_DECODE_OTHER);
        }
      else
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_TAG);	/* out of sequence	*/
      break;

    case TAG_SMPCNT:					/* SmpCnt	*/
      /* OPTIONAL DatSet may not be present, so state may be either of these.*/
      if (smpvalCtx->state == STATE_WAIT_DATSET || smpvalCtx->state == STATE_WAIT_SMPCNT)
        {
        if (asn1r_get_octstr_fixlen (aCtx, tmp_ostr, 2) == SD_SUCCESS)
          {
#if (SD_BYTE_ORDER==SD_LITTLE_ENDIAN)
          reverse_bytes ((ST_UINT8 *) &asdu->SmpCnt, tmp_ostr, 2);
#else
          asdu->SmpCnt = *(ST_UINT16 *) tmp_ostr;
#endif
          /* Don't know current state, so must set next state directly.*/
          smpvalCtx->state = STATE_WAIT_CONFREV;
          }
        else
          asn1r_set_dec_err (aCtx, ASN1E_DECODE_OTHER);
        }
      else
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_TAG);	/* out of sequence	*/
      break;

    case TAG_CONFREV:					/* ConfRev	*/
      if (smpvalCtx->state == STATE_WAIT_CONFREV)
        {
        if (asn1r_get_octstr_fixlen (aCtx, tmp_ostr, 4) == SD_SUCCESS)
          {
#if (SD_BYTE_ORDER==SD_LITTLE_ENDIAN)
          reverse_bytes ((ST_UINT8 *) &asdu->ConfRev, tmp_ostr, 4);
#else
          asdu->ConfRev = *(ST_UINT32 *) tmp_ostr;
#endif
          smpvalCtx->state++;
          }
        else
          asn1r_set_dec_err (aCtx, ASN1E_DECODE_OTHER);
        }
      else
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_TAG);	/* out of sequence	*/
      break;

    case TAG_REFRTM:					/* RefrTm (optional)	*/
      if (smpvalCtx->state == STATE_WAIT_REFRTM)
        {
        asdu->RefrTmPres = SD_TRUE;
        if (asn1r_get_utc_time (aCtx, &asdu->RefrTm) == SD_SUCCESS)
          smpvalCtx->state++;
        else
          asn1r_set_dec_err (aCtx, ASN1E_DECODE_OTHER);
        }
      else
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_TAG);	/* out of sequence	*/
      break;

    case TAG_SMPSYNCH:					/* SmpSynch (optional)	*/
      /* OPTIONAL RefrTm may not be present, so state may be either of these.*/
      if (smpvalCtx->state == STATE_WAIT_REFRTM || smpvalCtx->state == STATE_WAIT_SMPSYNCH)
        {
        if (asn1r_get_bool (aCtx, &asdu->SmpSynch) == SD_SUCCESS)
          /* Don't know current state, so must set next state directly.*/
          smpvalCtx->state = STATE_WAIT_SMPRATE;
        else
          asn1r_set_dec_err (aCtx, ASN1E_DECODE_OTHER);
        }
      else
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_TAG);	/* out of sequence	*/
      break;

    case TAG_SMPRATE:					/* SmpRate (optional)	*/
      /* OPTIONAL RefrTm, SmpSynch may not be present, so any state in this range is OK.*/
      if (smpvalCtx->state >= STATE_WAIT_REFRTM && smpvalCtx->state <= STATE_WAIT_SMPRATE) 
        {
        if (asn1r_get_octstr_fixlen (aCtx, tmp_ostr, 2) == SD_SUCCESS)
          {
          asdu->SmpRatePres = SD_TRUE;
#if (SD_BYTE_ORDER==SD_LITTLE_ENDIAN)
          reverse_bytes ((ST_UINT8 *) &asdu->SmpRate, tmp_ostr, 2);
#else
          asdu->SmpRate = *(ST_UINT16 *) tmp_ostr;
#endif
          /* Don't know current state, so must set next state directly.*/
          smpvalCtx->state = STATE_WAIT_SAMPLE;
          }
        else
          asn1r_set_dec_err (aCtx, ASN1E_DECODE_OTHER);
        }
      else
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_TAG);	/* out of sequence	*/
      break;

    case TAG_SAMPLE:					/* sample	*/
      /* OPTIONAL RefrTm, SmpSynch & SmpRate may not be present, so any state >= STATE_WAIT_REFRTM is OK.*/
      /* State can't be > STATE_WAIT_SAMPLE, so don't have to chk for state too high.*/
      if (smpvalCtx->state >= STATE_WAIT_REFRTM)
        {
        /* Set SampleLen and SamplePtr (points within ASN1 decode buffer).*/
        asdu->SampleLen = ASN1_DEC_LEN(aCtx);
        asdu->SamplePtr = ASN1_DEC_PTR(aCtx);
        if (asn1r_skip_elmnt (aCtx) == SD_SUCCESS)	/* Skip over this ASN.1 element.*/
          {
          smpvalCtx->state = STATE_WAIT_ASDU_SEQ;	/* CRITICAL: get ready for new sequence*/
          smpvalCtx->asduIdx++;
          }
        /* NOTE: if asn1r_skip_elmnt fails, ASN1 err is already set.	*/
        }
      else
        asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_TAG);	/* out of sequence	*/
      break;

    default:				/* Don't know how to decode.	*/
      CLNP_LOG_ERR1 ("Decode error: unexpected tag 0x%X.", tagnum);
      asn1r_set_dec_err (aCtx, ASN1E_UNEXPECTED_TAG);
      break;
    }	/* End "switch (tagnum)"	*/
  }

/************************************************************************/
/*			smpval_error					*/
/************************************************************************/

static ST_VOID smpval_error (ASN1_DEC_CTXT *aCtx, ST_RET err)
  {
  CLNP_LOG_ERR1 ("SMPVAL decode error = 0x%X", err);
  }
/************************************************************************/
/*			smpval_msg_decode_asn1				*/
/* Decode the ASN.1 part of a SMPVAL message.				*/
/************************************************************************/
static ST_RET smpval_msg_decode_asn1 (SMPVAL_MSG *smpvalMsg, ST_UCHAR *apdu, ST_INT apdu_len)
  {
ASN1_DEC_CTXT aCtx;
SMPVAL_DEC_CTXT smpvalCtx;
ST_RET retcode = SD_SUCCESS;

  memset (&aCtx, 0, sizeof(ASN1_DEC_CTXT));		/* start clean	*/
  memset (&smpvalCtx, 0, sizeof(SMPVAL_DEC_CTXT));	/* start clean	*/

  /* Save smpvalMsg and smpvalCtx in ASN1 Decode Context*/
  aCtx.usr_info[0] = smpvalMsg;
  aCtx.usr_info[1] = &smpvalCtx;

  /* ASN1_ANYTAG_METHOD decode method is much simpler and uses fewer callback functions.*/
  aCtx.asn1r_decode_method = ASN1_ANYTAG_METHOD;
  aCtx.asn1r_anytag_fun = decode_tag_apdu;	/* decode any tag	*/

  /* If parse finishes before expected, this error funct is called.	*/
  /* When parse is done, this funct ptr is set to NULL.			*/
  aCtx.asn1r_decode_done_fun = asn1r_done_err; /* done function = error fun*/

  /* this function called if any error detected during parse.		*/
  aCtx.asn1r_err_fun = smpval_error;

  /* Parse the ASN.1 msg. */
  asn1r_decode_asn1 (&aCtx, apdu, apdu_len);

  if (aCtx.asn1r_pdu_dec_err != NO_DECODE_ERR)
    retcode = SD_FAILURE;
  return (retcode);
  }

/************************************************************************/
/*			smpval_msg_decode					*/
/* Completely decode SMPVAL message (including Ethertype header).		*/
/* This function allocates the SMPVAL_MSG structure, fills it in, and	*/
/* returns a pointer to it. It also fills in the ETYPE_INFO struct	*/
/* referenced by the "etypeInfo" argument.				*/
/* CRITICAL: The SMPVAL_MSG struct contains pointers to data in the 	*/
/*   SN_UNITDATA struct. Therefore, the SN_UNITDATA struct must not be	*/
/*   freed until after the SMPVAL_MSG struct is freed.			*/
/* NOTE: The Ethertype ID should be checked before calling this funct,	*/
/*   but it is checked again here to be sure this is SMPVAL message.	*/
/************************************************************************/
SMPVAL_MSG *smpval_msg_decode (
	SN_UNITDATA *sn_req,	/* message to decode			*/
	ETYPE_INFO *etypeInfo)	/* where to store decoded Ethertype info*/
  {
  SMPVAL_MSG *smpvalMsg = NULL;
  ST_UCHAR *apdu;
  ST_INT apdu_len;

  /* Decode the Ethertype header.	*/
  /* Returns a ptr to the data. Fills in etypeInfo struct. */
  apdu = etype_hdr_decode(sn_req, etypeInfo, &apdu_len);
  if (apdu != NULL && etypeInfo->etypeID == ETYPE_TYPE_SV)
    {
    /* Decode complete SMPVAL message	*/
    /* Use calloc to allocate "clean" SMPVAL_MSG struct	*/
    smpvalMsg = (SMPVAL_MSG *) chk_calloc (1, sizeof (SMPVAL_MSG));
    if (smpval_msg_decode_asn1 (smpvalMsg, apdu, apdu_len) != SD_SUCCESS)
      {
      chk_free (smpvalMsg);	/* free struct just allocated.	*/
      smpvalMsg = NULL;		/* error return	*/
      }
    }

  return (smpvalMsg);
  }
/************************************************************************/
/*			smpval_msg_free					*/
/* Free resources for allocated for recieved SMPVAL message.		*/
/************************************************************************/
ST_VOID smpval_msg_free (SMPVAL_MSG *smpvalMsg)
  {
  if (smpvalMsg->asduArray)
    chk_free (smpvalMsg->asduArray);
  chk_free (smpvalMsg);
  }


