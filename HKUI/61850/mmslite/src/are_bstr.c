/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*      	  1986 - 2002, All Rights Reserved.		        */
/*									*/
/*		    PROPRIETARY AND CONFIDENTIAL			*/
/*									*/
/* MODULE NAME : are_bstr.c 						*/
/* PRODUCT(S)  : ASN1DE 						*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 03/11/04  GLB     07    Remove "thisFileName"                    	*/
/* 01/14/03  JRB     06    Avoid redundant logging of encode overrun.	*/
/* 03/05/02  JRB     05    Eliminate warnings.				*/
/* 01/22/02  JRB     04    Chg asn1r_end_of_buffer to asn1r_buf_start.	*/
/* 12/20/01  JRB     03    Chg ASN1_CTXT to ASN1_ENC_CTXT.		*/
/* 09/13/99  MDE     02    Added SD_CONST modifiers			*/
/* 07/26/99  MDE     01    New module, derived from ae_bstr.c		*/
/************************************************************************/

#include "glbtypes.h"
#include "sysincs.h"
#include "asn1r.h"
#include "asn1log.h"


/************************************************************************/
/*			     wr_bitstr					*/
/************************************************************************/

ST_VOID asn1r_wr_bitstr (ASN1_ENC_CTXT *ac, ST_UCHAR *bitPtr, ST_INT numBits)
  {
ST_INT bitsLeft;
ST_INT numBytes;

  numBytes = numBits/8; 	/* calculate the total # bytes req'd    */
  if ((bitsLeft = numBits % 8)!=0)	/* get remainder		*/
    numBytes++;

  if (ac->asn1r_field_ptr - numBytes < ac->asn1r_buf_start)
    {
    ac->asn1r_encode_overrun = SD_TRUE;
    return;
    }

  ac->asn1r_field_ptr -= numBytes;
  memcpy (ac->asn1r_field_ptr+1, bitPtr, numBytes);

  if (bitsLeft) 		/* write the unused-bits octet		*/
    *(ac->asn1r_field_ptr--) = (ST_UCHAR) (8 - bitsLeft);
  else
    *(ac->asn1r_field_ptr--) =  0;
  }

