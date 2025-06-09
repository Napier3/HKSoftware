/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*      	  1986 - 2001, All Rights Reserved.		        */
/*									*/
/*		    PROPRIETARY AND CONFIDENTIAL			*/
/*									*/
/* MODULE NAME : ard_bstr.c 						*/
/* PRODUCT(S)  : ASN1DE 						*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 04/21/08  JRB     09    Add cast to fix warning.			*/
/* 03/17/04  RKR     08    Changed thisFileName                         */
/* 03/11/04  GLB     07    Remove "thisFileName"                    	*/
/* 03/31/03  JRB     06	   asn1r_get_bitstr: add max_bits arg & truncate*/
/*			   bitstr if max_bits exceeded.			*/
/* 03/05/02  JRB     05    Eliminate warnings.				*/
/* 12/20/01  JRB     04    Chg ASN1_CTXT to ASN1_DEC_CTXT.		*/
/* 12/12/01  JRB     03    Changes to compile MMS-EASE			*/
/* 09/13/99  MDE     02    Added SD_CONST modifiers			*/
/* 07/26/99  MDE     01    New module, derived from ard_bstr.c		*/
/************************************************************************/

#include "glbtypes.h"
#include "sysincs.h"
#include "asn1r.h"
#include "asn1log.h"

/************************************************************************/
/* For debug version, use a static pointer to avoid duplication of 	*/
/* __FILE__ strings.							*/

#if defined(DEBUG_SISCO) && !defined(MMS_LITE)
SD_CONST static ST_CHAR *SD_CONST thisFileName = __FILE__;
#endif

/************************************************************************/
/************************************************************************/

#ifdef GET_CONSTRUCTED_BSTRINGS
static ST_VOID  _dec_bitstr_cstr (ASN1_DEC_CTXT *ac, ST_UINT16 id_code);
#endif

/************************************************************************/
/*			    get_bitstr					*/
/*  Function to read a primitive bitstring from an ASN.1 message.	*/
/*  Truncate bitstring if it exceeds "max_bits".			*/
/************************************************************************/

ST_RET asn1r_get_bitstr (ASN1_DEC_CTXT *ac, ST_UCHAR *bit_ptr, ST_INT max_bits)
 {
ST_INT i;
ST_INT accepted_bits;	/* # of bits accepted (may be truncated)	*/

#ifdef	DEBUG_ASN1_DECODE
  if (!bit_ptr)
    {
    slogCallStack (sLogCtrl,
                    "get_: attempt to reference through a NULL pointer");
    return(SD_FAILURE);
    }
#endif

  if (ac->asn1r_elmnt_len < 1)   /* For element length of 0, return error code.	*/
    return (SD_FAILURE);

  i = *(ac->asn1r_field_ptr++);
  if (i>7 || i<0)
    return (2);        /* Return error code for bad unused-bits value.	*/

  if (ac->asn1r_elmnt_len == 1)  /* When there is only the unused-bits octet,	*/
    {		       /* it must = 0, and there are no data bits.	*/
    if (i!=0)
      return (2);
    ac->asn1r_bitcount = 0;
    }

  else		       /* Treat normal case where there are data bits.	*/
    {
    ac->asn1r_bitcount = ((ac->asn1r_elmnt_len-1)*8 - i); /* Compute # data bits.	*/

    /* If caller imposed a limit, truncate. */
    if (max_bits != 0  &&  ac->asn1r_bitcount > max_bits)
      accepted_bits = max_bits;	/* truncated	*/
    else
      accepted_bits = ac->asn1r_bitcount;

    /* Copy bitstring to user buffer	*/
    bstrcpy (bit_ptr, ac->asn1r_field_ptr, accepted_bits);
    ac->asn1r_field_ptr += (ac->asn1r_elmnt_len - 1);	/* point to next*/
    }
  return (SD_SUCCESS);
  }

/************************************************************************/
/*			get_bitstr_cstr 				*/
/*  Function to setup to get a constructed bitstring.			*/
/************************************************************************/

ST_VOID asn1r_get_bitstr_cstr (ASN1_DEC_CTXT *ac, ST_INT bits, ST_UCHAR *ptr)
 {
#ifdef GET_CONSTRUCTED_BSTRINGS

#ifdef	DEBUG_ASN1_DECODE
  if (!ptr)
    {
    slogCallStack (sLogCtrl,
         "get_bitstr_cstr: attempt to reference through a NULL pointer");
    return;
    }
#endif

  ac->asn1r_max_bits = bits;	/* max allowed # bits				*/
  ac->_ad_bitptr = ptr; 	/* pointer to bit storage area			*/
  *ac->_ad_bitptr = 0;		/* zero first byte of user's storage area       */
  ac->asn1r_bitcount = 0; 	/* running bit count				*/

  ac->asn1r_u_id_fun = _dec_bitstr_cstr;		/* universal until bitstr done	*/
  ac->asn1r_c_id_fun = asn1r_class_err;		/* no more context		*/
  ac->asn1r_a_id_fun = asn1r_class_err;		/* or application		*/
  ac->asn1r_p_id_fun = asn1r_class_err;		/* or private			*/

  ac->asn1r_save_method = ac->asn1r_decode_method;
  ac->asn1r_decode_method = ASN1_CLASS_METHOD;
  ac->_asn1r_fun_save = ac->asn1r_decode_done_fun; /* save the previous done fun	*/
  ac->asn1r_decode_done_fun = asn1r_done_err;	/* can't be done for now        */
  ac->_asn1r_cstr_done_save = ac->asn1r_c_done_fun[ac->asn1r_msg_level];
  ac->asn1r_c_done_fun[ac->asn1r_msg_level] = asn1r_chk_getcstr_done;
#endif 	/* #ifdef GET_CONSTRUCTED_BSTRINGS */
  }

/************************************************************************/
/*			_dec_bitstr_cstr 				*/
/*	Function to decode asn.1 constructor bitstrings.		*/
/************************************************************************/

#ifdef GET_CONSTRUCTED_BSTRINGS

static ST_VOID _dec_bitstr_cstr (ASN1_DEC_CTXT *ac, ST_UINT16 id_code)
  {
ST_INT i;
ST_INT16 ub;
ST_INT16 phase;
ST_UINT16 imask;
ST_INT16 bitspill;
ST_INT numbytes;

  ALOG_DEC0 ("_dec_bitstr_cstr");

  if ((id_code & BITS_CODE) != BITS_CODE)
    {				/*  Protocol error - invalid ID Code.  */
    ALOG_NERR0 ("ASN.1 decode: unexpected tag");
    asn1r_set_dec_err(ac, ASN1E_UNEXPECTED_TAG);
    return;
    }

  if (ac->asn1r_constr_elmnt)		/* Don't do anything for constructors   */
    {
    ac->asn1r_c_done_fun[ac->asn1r_msg_level] = NULL;
    return;
    }
				    /* For primitive bitstrings,  */
  ub = *ac->asn1r_field_ptr++ & 0xff;	    /* read the unused-bits byte. */

  if (ac->asn1r_elmnt_len==1)		    /* For primitive bitstrings   */
    return;			    /* with no bits, just return. */

  else if (ac->asn1r_elmnt_len)		    /* Normal case: */
    {
    bitspill = (ST_INT16) (ac->asn1r_bitcount % 8);
    numbytes = (ST_INT16) (ac->asn1r_elmnt_len - 1); /* # of bytes of data does not  */
    ac->asn1r_bitcount += numbytes*8 - ub;    /* include the unused-bits byte */
    if (ac->asn1r_bitcount > ac->asn1r_max_bits)
      { 			    /*	bit storage area overflow. */
      ALOG_NERR0 ("ASN.1 decode: constructed bitstring too long");
      asn1r_set_dec_err(ac, ASN1E_BITCSTR_TOO_BIG);
      return;
      }
    phase = 8 - bitspill;
    for (i = numbytes; i; --i)	    /* Move bytes from ASN.1 message */
      { 			    /* through imask (where bits are */
      imask = *ac->asn1r_field_ptr++ & 0xff;  /* shifted) to final storage.    */
      imask <<= phase;
      *ac->_ad_bitptr++ |= (ST_CHAR) (imask>>8);	/* move left byte of imask   */
      *ac->_ad_bitptr = (ST_CHAR) imask;		/* move right byte of imask  */
      }
	 /* Now all bits have been moved to the user's storage area. */
    bitspill -= ub;		 /* Calculate new value of bitspill. */
    if (bitspill < 0)
      { 			    /* In this case, all bits in */
      bitspill += 8;		    /* last byte are unused, so  */
      ac->_ad_bitptr--; 		    /* decrement ac->_ad_bitptr.	 */
      }
				    /* Zero unused bits in last byte */
    *ac->_ad_bitptr &= (ST_UCHAR)~0 << (8-bitspill);
    }

  else
    {	     /*  Protocol error - zero length bitstring encountered. */
    ALOG_NERR0 ("ASN.1 decode: zero length bitstring");
    asn1r_set_dec_err(ac, ASN1E_INVALID_BITSTR);
    return;
    }
  }

#endif 	/* #ifdef GET_CONSTRUCTED_BSTRINGS */

