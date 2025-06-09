/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*      	  1986 - 2002, All Rights Reserved.		        */
/*									*/
/*		    PROPRIETARY AND CONFIDENTIAL			*/
/*									*/
/* MODULE NAME : are_ostr.c						*/
/* PRODUCT(S)  : ASN1DE 						*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 08/01/05  JRB     07    Add const on asn1_wr_octstr args.		*/
/* 03/11/04  GLB     06    Remove "thisFileName"                    	*/
/* 01/14/03  JRB     05    Avoid redundant logging of encode overrun.	*/
/* 01/22/02  JRB     04    Chg asn1r_end_of_buffer to asn1r_buf_start.	*/
/* 12/20/01  JRB     03    Chg ASN1_CTXT to ASN1_ENC_CTXT.		*/
/* 09/13/99  MDE     02    Added SD_CONST modifiers			*/
/* 07/26/99  MDE     01    New module, derived from ae_ostr.c		*/
/************************************************************************/

#include "glbtypes.h"
#include "sysincs.h"
#include "asn1r.h"
#include "asn1log.h"

/************************************************************************/
/*			    wr_octstr					*/
/* Function to write a primitive octet string to a message being built. */
/************************************************************************/

ST_VOID asn1r_wr_octstr (ASN1_ENC_CTXT *ac, const ST_UCHAR *octPtr, ST_INT numOctets)
  {
  if (ac->asn1r_field_ptr - numOctets < ac->asn1r_buf_start)
    {
    ac->asn1r_encode_overrun = SD_TRUE;
    return;
    }

  ac->asn1r_field_ptr -= numOctets;
  memcpy (ac->asn1r_field_ptr+1, octPtr, numOctets);
  }

