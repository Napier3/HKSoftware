/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*      	  1986 - 2005, All Rights Reserved.		        */
/*									*/
/*		    PROPRIETARY AND CONFIDENTIAL			*/
/*									*/
/* MODULE NAME : ard_int.c 						*/
/* PRODUCT(S)  : ASN1DE 						*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 10/03/08  JRB     08    Fix crash by testing for asn1r_elmnt_len < 1.*/
/* 06/10/05  JRB     07    Use i64 suffix on WIN32, default to LL suffix*/
/* 03/03/05  EJV     06    Use LL suffix also on linux.			*/
/* 03/16/04  EJV     05    Added ST_(U)LONG typecast to logs,on some sys*/
/*			     ST_(U)INT32 can be (unsigned) long or int.	*/
/*			   asn1r_get_u8 (_u16): fixed potential problem.*/
/* 01/08/04  EJV     04    asn1r_get_int64: added define for sun.	*/
/* 12/20/01  JRB     03    Chg ASN1_CTXT to ASN1_DEC_CTXT.		*/
/* 09/13/99  MDE     02    Added SD_CONST modifiers			*/
/* 07/26/99  MDE     01    New module, derived from ad_int.c		*/
/************************************************************************/

#include "glbtypes.h"
#include "sysincs.h"
#include "asn1r.h"
#include "asn1log.h"

/************************************************************************/
/* For debug version, use a static pointer to avoid duplication of 	*/
/* __FILE__ strings.							*/

#ifdef DEBUG_SISCO
SD_CONST static ST_CHAR *SD_CONST thisFileName = __FILE__;
#endif

/************************************************************************/
/************************************************************************/

ST_RET asn1r_get_int32 (ASN1_DEC_CTXT *ac, ST_INT32 *ptr, ST_BOOLEAN signedInt);
#ifdef INT64_SUPPORT
ST_RET asn1r_get_int64 (ASN1_DEC_CTXT *ac, ST_INT64 *ptr, ST_BOOLEAN signedInt);
#endif

/************************************************************************/
/*			     get_i8					*/
/* Function to read a short integer from a message being decoded.	*/
/* Assumes asn1_field_ptr points to data (content field), and asn1_elmnt_len	*/
/* equals exactly one byte.  Leaves pointer set to next data element.	*/
/* Returns 0 if OK, non-zero if error.					*/
/************************************************************************/

ST_RET asn1r_get_i8 (ASN1_DEC_CTXT *ac, ST_INT8 *ptr)
  {
ST_INT32 value;
ST_RET ret;

  ret = asn1r_get_int32 (ac, &value, SD_TRUE);
  if (ret == SD_SUCCESS && (value > 127 || value < -128))
    {
    ALOG_NERR1 ("ASN.1 decode: Signed8 out of range (%ld)", (ST_LONG) value);
    return (SD_FAILURE);
    }

  *ptr = (ST_CHAR) value;
  return (ret);
  }

/************************************************************************/
/*			      get_i16					*/
/* Function to read an integer from a message being decoded.		*/
/* Assume asn1_field_ptr points to data, and asn1_elmnt_len		*/
/* equals one or two bytes.  Leaves pointer set to next data element.	*/
/* Returns 0 if OK, non-zero if error.					*/
/************************************************************************/

ST_RET asn1r_get_i16 (ASN1_DEC_CTXT *ac, ST_INT16 *ptr)
  {
ST_INT32 value;
ST_RET ret;

  ret = asn1r_get_int32 (ac, &value, SD_TRUE);
  if (ret == SD_SUCCESS && (value > 32767 || value < -32768))
    {
    ALOG_NERR1 ("ASN.1 decode: Signed16 out of range (%ld)", (ST_LONG) value);
    return (SD_FAILURE);
    }

  *ptr = (ST_INT16) value;
  return (ret);
  }

/************************************************************************/
/*			      get_i32					*/
/* Function to read a long integer from a message being decoded.	*/
/* Assumes asn1_field_ptr points to data, and asn1_elmnt_len		*/
/* equals one to four bytes.  Leaves pointer set to next data element.	*/
/* Returns 0 if OK, non-zero if error.					*/
/************************************************************************/

ST_RET asn1r_get_i32 (ASN1_DEC_CTXT *ac, ST_INT32 *ptr)
  {
ST_INT32 value;
ST_RET ret;

  ret = asn1r_get_int32 (ac, &value, SD_TRUE);
  *ptr = value;
  return (ret);  
  }

/************************************************************************/
/*				get_u8					*/
/* Function to read an ASN.1 INTEGER from a message being decoded	*/
/* into a 1-byte unsigned char.  Assumes asn1_field_ptr points to data	*/
/* field and asn1_elmnt_len has 1 or 2 bytes.  Leaves asn1_field_ptr pointing to	*/
/* next data element.  Returns 0 if OK, non-zero if error.		*/
/************************************************************************/

ST_RET asn1r_get_u8 (ASN1_DEC_CTXT *ac, ST_UCHAR *ptr)
  {
ST_UINT32 value;
ST_RET ret;

  ret = asn1r_get_int32 (ac, (ST_INT32 *) &value, SD_FALSE);
  if (ret == SD_SUCCESS && value > 0xFF)
    {
    ALOG_NERR1 ("ASN.1 decode: Unsigned16 out of range (%lu)", (ST_ULONG) value);
    return (SD_FAILURE);
    }

  *ptr = (ST_UCHAR) value;
  return (ret);
  }

/************************************************************************/
/*			    get_u16					*/
/* Function to read an ASN.1 INTEGER from a message being decoded	*/
/* into a 2-byte unsigned integer.  Assumes asn1_field_ptr points to data	*/
/* field and asn1_elmnt_len has 1 to 3 bytes.  Leaves asn1_field_ptr pointing to	*/
/* next data element.  Returns 0 if OK, non-zero if error.		*/
/************************************************************************/

ST_RET asn1r_get_u16 (ASN1_DEC_CTXT *ac, ST_UINT16 *ptr)
  {
ST_UINT32 value;
ST_RET ret;

  ret = asn1r_get_int32 (ac, (ST_INT32 *) &value, SD_FALSE);
  if (ret == SD_SUCCESS && value > 0xFFFF)
    {
    ALOG_NERR1 ("ASN.1 decode: Unsigned16 out of range (%lu)", (ST_ULONG) value);
    return (SD_FAILURE);
    }

  *ptr = (ST_UINT16) value;
  return (ret);  
  }

/************************************************************************/
/*			    get_u32					*/
/* Function to read an ASN.1 INTEGER from a message being decoded	*/
/* into a 4-byte unsigned ST_INT32.  Assumes asn1_field_ptr points to data	*/
/* field and asn1_elmnt_len has 1 to 5 bytes.  Leaves asn1_field_ptr pointing	*/
/* to next data element.  Returns 0 if OK, non-zero if error.		*/
/************************************************************************/

ST_RET asn1r_get_u32 (ASN1_DEC_CTXT *ac, ST_UINT32 *ptr)
  {
ST_INT32 value;
ST_RET ret;

  ret = asn1r_get_int32 (ac, &value, SD_FALSE);
  *ptr = value;
  return (ret);  
  }

/************************************************************************/
/************************************************************************/

ST_RET asn1r_get_int32 (ASN1_DEC_CTXT *ac, ST_INT32 *ptr, ST_BOOLEAN signedInt)
  {
ST_INT32 value;
ST_INT32 oVal;
ST_INT32 negMask;
ST_BOOLEAN positive;
ST_INT i;

#ifdef	DEBUG_ASN1_DECODE
  if (!ptr)
    {
    slogCallStack (sLogCtrl,
                    "get_i32: attempt to reference through a NULL pointer");
    return(SD_FAILURE);
    }
#endif

/* ASN.1 spec says 'integer' must be at least 1 octet	*/
  if (ac->asn1r_elmnt_len < 1)
    {
    ALOG_ERR0 ("ASN.1 decode: length < 1 not allowed for integer");
    return (SD_FAILURE);
    }

/* Check to see if the ASN.1 data value is posative or negative		*/
  if (*ac->asn1r_field_ptr & 0x80)
    {
    positive = SD_FALSE;
    if (signedInt == SD_FALSE)	/* The caller must want a signed int	*/
      {
      ALOG_NERR0 ("ASN.1 decode: Negative number received for unsigned integer");
      return (SD_FAILURE);
      }
    }
  else
    positive = SD_TRUE;

/* Large unsigned value's may be 5 bytes, with a leading 0. If so,	*/
/* we will strip it here.						*/
  i = ac->asn1r_elmnt_len; 
  if (i >= 5)			/* Large positive number, skip leading 0 */
    {
    if (*ac->asn1r_field_ptr != 0 || positive == SD_FALSE)
      {
      ALOG_NERR0 ("ASN.1 decode: invalid 5 byte (or larger) integer");
      return (SD_FAILURE);
      }
    ++ac->asn1r_field_ptr;
    --i;
    }

/* Go ahead and read the value into A 4 byte integer, shifting as we go	*/
  value = 0;
  while (SD_TRUE)
    {
    oVal = (ST_INT32) *(ac->asn1r_field_ptr++);
    oVal &= 0xFF;
    value |= oVal;
    if (--i == 0)
      break;

  /* More bytes of data, need to make room for next one */
    value = (value << 8) & 0xffffff00;
    }

/* We may need to sign extend if negative 				*/
  if (!positive && ac->asn1r_elmnt_len < 4)
    {
    negMask = 0xff000000L;
    i = 4 - ac->asn1r_elmnt_len;
    while (i-- > 0)
      {
      value |= negMask;
      negMask = negMask >> 8; 
      }
    }

  *ptr = value;
  return (SD_SUCCESS);
  }

/************************************************************************/
#ifdef INT64_SUPPORT
/************************************************************************/
/************************************************************************/

ST_RET asn1r_get_u64 (ASN1_DEC_CTXT *ac, ST_UINT64 *ptr)
  {
ST_INT64 value;
ST_RET ret;

  ret = asn1r_get_int64 (ac, &value, SD_FALSE);
  *ptr = value;
  return (ret);  
  }

/************************************************************************/

ST_RET asn1r_get_i64 (ASN1_DEC_CTXT *ac, ST_INT64 *ptr)
  {
ST_INT64 value;
ST_RET ret;

  ret = asn1r_get_int64 (ac, &value, SD_TRUE);
  *ptr = value;
  return (ret);  
  }

/************************************************************************/

ST_RET asn1r_get_int64 (ASN1_DEC_CTXT *ac, ST_INT64 *ptr, ST_BOOLEAN signedInt)
  {
ST_INT64 value;
ST_INT64 oVal;
ST_INT64 negMask;
ST_BOOLEAN positive;
ST_INT i;

/* Check to see if the ASN.1 data value is posative or negative		*/
  if (*ac->asn1r_field_ptr & 0x80)
    {
    positive = SD_FALSE;
    if (signedInt == SD_FALSE)	/* The caller must want a signed int	*/
      {
      ALOG_NERR0 ("ASN.1 decode: Negative number received for unsigned integer");
      return (SD_FAILURE);
      }
    }
  else
    positive = SD_TRUE;

/* Large unsigned value's may be 9 bytes, with a leading 0. If so,	*/
/* we will strip it here.						*/
  i = ac->asn1r_elmnt_len; 
  if (i >= 9)			/* Large positive number, skip leading 0 */
    {
    if (*ac->asn1r_field_ptr != 0 || positive == SD_FALSE)
      {
      ALOG_NERR0 ("ASN.1 decode: invalid 9 byte (or larger) integer");
      return (SD_FAILURE);
      }
    ++ac->asn1r_field_ptr;
    --i;
    }

/* Go ahead and read the value into a 8 byte integer, shifting as we go	*/
  value = 0;
  while (SD_TRUE)
    {
    oVal = (ST_INT64) *(ac->asn1r_field_ptr++);
    oVal &= 0xFF;
    value |= oVal;
    if (--i == 0)
      break;

  /* More bytes of data, need to make room for next one */
#if defined(_WIN32)
    value = (value << 8) & 0xffffffffffffff00i64;
#else
    value = (value << 8) & 0xffffffffffffff00LL;
#endif
    }

/* We may need to sign extend if negative 				*/
  if (!positive && ac->asn1r_elmnt_len < 8)
    {
#if defined(_WIN32)
    negMask = 0xff00000000000000i64;
#else
    negMask = 0xff00000000000000LL;
#endif
    i = 8 - ac->asn1r_elmnt_len;
    while (i-- > 0)
      {
      value |= negMask;
      negMask = negMask >> 8; 
      }
    }

  *ptr = value;
  return (SD_SUCCESS);
  }


/************************************************************************/
#endif /* #ifdef INT64_SUPPORT */
/************************************************************************/
