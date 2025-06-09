/*+***************************************************************************/
/* SISCO SOFTWARE MODULE HEADER **********************************************/
/* ***************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,            */
/*            2005 All Rights Reserved                                       */
/*                                                                           */
/* MODULE NAME : stdtime.c                                                   */
/* PRODUCT(S)  : Standard Time Management Library                            */
/*                                                                           */
/* MODULE DESCRIPTION:                                                       */
/*   Implementation of Standard Time Management Library Functions            */
/*                                                                           */
/*   Note: Most functions a produce a return-code value STDTIME_RC.          */
/*   The return code is zero if successful, otherwise it is a structured     */
/*   value in which the low-order 10 bits enumerates an error reason,        */
/*   and the upper 20 bits enumerates the high-level and low-level           */
/*   functions where the error was detected.                                 */
/*                                                                           */
/* MODIFICATION LOG:                                                         */
/*   Date    Who  Rev  Comments                                              */
/* --------  ---  ---  ----------------------------------------------------- */
/* 03/18/07  RLH   12  Correct bug in new normalization code.                */
/* 03/16/07  RLH   11  Normalize struct tm, SYSTEMTIME, and STDTIME_FIELDS   */
/*                     after rounding is applied; no rounding for formatting */
/*                     functions.                                            */
/* 02/16/07  RLH   10  Clean up minor warnings under Linux                   */
/* 01/11/07  RLH   09  Perform generalized rounding when creating outside    */
/*                     data types and extra (Ex) fields are not written.     */
/*                     This supersedes the Rev 08 changes.                   */
/*                     Also, add TruncStdTimeString functions.               */
/* 01/10/07  RLH   08  Perform rounding at msec level when creating HpDate   */
/* 11/22/06  RLH   07  Ensure DelimitStdTimeString does not pad a trimmed    */
/*                     string value with trailing blanks.                    */
/* 11/21/06  RLH   06  Remove unused variable to silence a warning msg       */
/* 10/27/06  RLH   05  Correct rounding in Rc_ArgDateExToStdTime             */
/* 10/18/06  RLH   04  Enhanced capabilities for timezone rules              */
/* 09/13/06  RLH   03  Ensure local time conversions work when TZ not set    */
/* 06/07/06  RLH   02  Numerous features added, see stdtime.doc              */
/* 01/18/06  RLH   01  Created                                               */
/*+***************************************************************************/

/* define list of error-code descriptions */
/* this is done by temporary macro and include file */

#define STDTIME_ENUM_ERR(x) #x ,

static char *               enum_stdtime_err_text[] =
  {
  "",                       /* dummy 0 entry */
#include "stdtime_enum_err.h"
  ""
  };

/* temporary macro has served its purpose, so undefine it */
#undef  STDTIME_ENUM_ERR


/* create function name table from enum_stdtime_func.h */
/* this is done by temporary macro and include file */

#define STDTIME_ENUM_FUNC(x) #x ,

static char *               enum_stdtime_func_text[] =
  {
  "",                       /* dummy 0 entry */
#include "stdtime_enum_func.h"
  ""
  };

/* temporary macro has served its purpose, so undefine it */
#undef  STDTIME_ENUM_FUNC


#include "stdtime.h"
#include <math.h>


/*** private (helper) macros and static areas ********************************/

#define STDTIME_IF(x)       ((rc=(x)) == STDTIME_OK)
#define STDTIME_IFNOT(x)    ((rc=(x)) != STDTIME_OK)

#define PVT_STDTIME_ROUND(ptr,curr,next)                                      \
  if ((ptr) == NULL)                                                          \
    {                                                                         \
    if ((curr) >= 500)                                                        \
      {                                                                       \
      (next) += (((curr) + 500) / 1000);                                      \
      (curr) = 0;                                                             \
      }                                                                       \
    }                                                                         \
  else                                                                        \
    {                                                                         \
    *ptr = (curr);                                                            \
    }

#define STDTIME_IN_RANGE(x,lo,hi)   (((x) >= (lo)) && ((x) <= (hi)))

#define PVT_STDTIME_FORMAT_BUFSIZE  256
#define PVT_STDTIME_FORMAT_DEFAULT  "%a %b %d %H:%M:%S %Y"

/* standard delimiters for ISO 8601-formatted time strings */
/* allow for user to redefine the standard delimiter string */
/* this change must be done carefully */

#ifndef STDTIME_ISO_DLM_STR
#define STDTIME_ISO_DLM_STR         "-T:."
#endif

  static char             Pvt_StdTime_UserDelimString[5] = STDTIME_ISO_DLM_STR;

#define PVT_STDTIME_ISO_DLM_DATE    (STDTIME_ISO_DLM_STR[0])
#define PVT_STDTIME_ISO_DLM_SEP     (STDTIME_ISO_DLM_STR[1])
#define PVT_STDTIME_ISO_DLM_TIME    (STDTIME_ISO_DLM_STR[2])
#define PVT_STDTIME_ISO_DLM_FRAC    (STDTIME_ISO_DLM_STR[3])

#define PVT_STDTIME_USR_DLM_DATE    (Pvt_StdTime_UserDelimString[0])
#define PVT_STDTIME_USR_DLM_SEP     (Pvt_StdTime_UserDelimString[1])
#define PVT_STDTIME_USR_DLM_TIME    (Pvt_StdTime_UserDelimString[2])
#define PVT_STDTIME_USR_DLM_FRAC    (Pvt_StdTime_UserDelimString[3])

#define PVT_STDTIME_SCALE_FILETIME  10000000

/* value of 11644473600000000 in hex, split into high/low 32-bit values */
#define PVT_STDTIME_U32_TIMET_BASE_HI 0x019DB1DE
#define PVT_STDTIME_U32_TIMET_BASE_LO 0xD53E8000

/* value of 2650467743999999999 in hex, split into high/low 32-bit values */
#define PVT_STDTIME_MAX_FILETIME_HI 0x24C85A5E
#define PVT_STDTIME_MAX_FILETIME_LO 0xD1C03FFF

/* value of 864000000000 in hex, split into high/low 32-bit values */
#define PVT_STDTIME_100NS_PERDAY_HI 0x000000C9
#define PVT_STDTIME_100NS_PERDAY_LO 0x2A69C000


/* form value of 1899-12-30 00:00:00.0000000 as a FILETIME equivalent */
/* value of 94353120000000000 in hex, split into high/low 32-bit values */
#define PVT_STDTIME_U32_COMDATE_BASE_HI 0x014F35A9
#define PVT_STDTIME_U32_COMDATE_BASE_LO 0xA90CC000


#define PVT_STDTIME_COMPARE(x)                                                \
  if (pOne->x < pTwo->x) return STDTIME_LT;                                   \
  if (pOne->x > pTwo->x) return STDTIME_GT                                 /**/


#define PVT_STDTIME_EXPORT_TZOA(x)                                            \
  {                                                                           \
  if ((x)->embTzo[0] != 0)                                                    \
    {                                                                         \
    strncpy ((x)->extTzo.str, (x)->embTzo, STDTIME_TZO_LEN);                  \
    (x)->extTzo.str[STDTIME_TZO_LEN] = 0;                                     \
    (x)->embTzo[0] = 0;                                                       \
    }                                                                         \
  }                                                                        /**/


#define PVT_STDTIME_EXPORT_TZOW(x)                                            \
  {                                                                           \
  if ((x)->embTzo[0] != 0)                                                    \
    {                                                                         \
    Wchar_StdTime_StrncpyWW ((x)->extTzo.str, (x)->embTzo, STDTIME_TZO_LEN);  \
    (x)->extTzo.str[STDTIME_TZO_LEN] = 0;                                     \
    (x)->embTzo[0] = 0;                                                       \
    }                                                                         \
  }                                                                        /**/


#define PVT_STDTIME_IMPORT_TZOA(x)                                            \
  {                                                                           \
  if ((x)->extTzo.str[0] != 0)                                                \
    {                                                                         \
    strncpy ((x)->embTzo, (x)->extTzo.str, STDTIME_TZO_LEN);                  \
    (x)->embTzo[STDTIME_TZO_LEN] = 0;                                         \
    (x)->extTzo.str[0] = 0;                                                   \
    }                                                                         \
  }                                                                        /**/


#define PVT_STDTIME_IMPORT_TZOW(x)                                            \
  {                                                                           \
  if ((x)->extTzo.str[0] != 0)                                                \
    {                                                                         \
    Wchar_StdTime_StrncpyWW ((x)->embTzo, (x)->extTzo.str, STDTIME_TZO_LEN);  \
    (x)->embTzo[STDTIME_TZO_LEN] = 0;                                         \
    (x)->extTzo.str[0] = 0;                                                   \
    }                                                                         \
  }                                                                        /**/


/*** private (helper) functions **********************************************/


/* NOTE: function names beginning with Rc_, Int_, Char_, Wchar_ and Bool_    */
/* are private functions; the prefix identifies the return type.             */


/*-***************************************************************************/
/*            StdTimeRet                                                     */
/*  assemble a STDTIME return code                                           */
/*  when basic error code is 0, always return 0                              */
/*  (used to be static, but was needed in multiple modules)                  */
/*****************************************************************************/


STDTIME_RC                  StdTimeRet (
  const STDTIME_RC          /*I*/ func,
  const STDTIME_RC          /*I*/ ec)
  {
  if (ec == 0) return 0;
  return ((func & STDTIME_10_BITS) << 20) | (ec & STDTIME_20_BITS);
  }


/*-***************************************************************************/
/*            Rc_StdTimeToQuadLibI64 - PRIVATE FUNCTION                      */
/*  convert: StdTime structure to QUADLIB I64 value                          */
/*  like StdTimeToFileTime without range checking                            */
/*****************************************************************************/

static STDTIME_RC           Rc_StdTimeToQuadLibI64 (
  const STDTIME *           /*I*/ pStdTime,
  QUADLIB_I64 *             /*O*/ pNumber)
  {
  STDTIME_ENUM_FUNC (Rc_StdTimeToQuadLibI64)

  if ((pStdTime == NULL) || (pNumber == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  /* StdTime and FILETIME have the following structure */

  /*  StdTime:   7FFFFFFF 7FFFFFFF  */
  /*  FILETIME:  3FFFFFFF FFFFFFFF  */

  QUADLIB_U64_LO (*pNumber) = pStdTime->lo & 0x7FFFFFFF;

  if (pStdTime->hi & 1)
    {
    QUADLIB_U64_LO (*pNumber) |= 0x80000000;
    }

  QUADLIB_U64_HI (*pNumber) = ((pStdTime->hi) >> 1) & 0x3FFFFFFF;

  STDTIME_RET_OK;

  } /* Rc_StdTimeToQuadLibI64 */


/*-***************************************************************************/
/*            Rc_QuadLibI64ToStdTime - PRIVATE FUNCTION                      */
/*  convert: QUADLIB I64 value to StdTime structure                          */
/*  like FileTimeToStdTime without range checking                            */
/*****************************************************************************/


static STDTIME_RC           Rc_QuadLibI64ToStdTime (
  const QUADLIB_I64 *       /*I*/ pNumber,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_ENUM_FUNC (Rc_QuadLibI64ToStdTime)

  if ((pStdTime == NULL) || (pNumber == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  /*  StdTime and FILETIME have the following structure */

  /*  StdTime:   7FFFFFFF 7FFFFFFF  */
  /*  FILETIME:  3FFFFFFF FFFFFFFF  */

  pStdTime->lo = QUADLIB_U64_LO (*pNumber) & 0x7FFFFFFF;

  pStdTime->hi = ((QUADLIB_U64_HI (*pNumber)) << 1) & 0x7FFFFFFF;

  if (QUADLIB_U64_LO (*pNumber) & 0x80000000)
    {
    pStdTime->hi |= 1;
    }

  STDTIME_RET_OK;

  } /* Rc_QuadLibI64ToStdTime */


/*-***************************************************************************/
/*            Bool_StdTime_IsBlankA - PRIVATE FUNCTION                       */
/*  Return STDTIME_TRUE if string is nul or whitespace only                  */
/*****************************************************************************/

static STDTIME_BOOL         Bool_StdTime_IsBlankA (
  const char *              /*I*/ str)
  {
  if (str == NULL)
    {
    return STDTIME_FALSE;
    }

  for (; *str; str++)
    {
    if (*str == 0)
      {
      break;
      }

    if (*str > (char) ' ')
      {
      return STDTIME_FALSE;
      }
    }

  return STDTIME_TRUE;

  } /* Bool_StdTime_IsBlankA */


#if 0   /* Bool_StdTime_IsBlankW not presently needed */

/*-***************************************************************************/
/*            Bool_StdTime_IsBlankW - PRIVATE FUNCTION                       */
/*  Return STDTIME_TRUE if string is nul or whitespace only                  */
/*****************************************************************************/

static STDTIME_BOOL         Bool_StdTime_IsBlankW (
  const STDTIME_WCHAR *     /*I*/ str)
  {
  if (str == NULL)
    {
    return STDTIME_FALSE;
    }

  for (; *str; str++)
    {
    if (*str == 0)
      {
      break;
      }

    if (*str > (STDTIME_WCHAR) ' ')
      {
      return STDTIME_FALSE;
      }
    }

  return STDTIME_TRUE;

  } /* Bool_StdTime_IsBlankW */

#endif  /* Bool_StdTime_IsBlankW not presently needed */


/*-***************************************************************************/
/*            Char_StdTime_StrcpyAW - PRIVATE FUNCTION                       */
/*  copy WCHAR to CHAR string until nul reached                              */
/*****************************************************************************/

#if 0   /* Char_StdTime_StrcpyAW not presently needed */

static char *               Char_StdTime_StrcpyAW (
  char *                    /*O*/ pTarget,
  const STDTIME_WCHAR *     /*I*/ pSource)
  {
  /* copy from WCHAR to CHAR, stopping at nul */
  /* Return ptr to terminator, useful for doing strcat operations */

  if (pTarget == NULL)
    {
    return NULL;
    }

  if (pSource == NULL)
    {
    pTarget [0] = 0;
    return pTarget;
    }

  for (;;)
    {
    if (*pSource > (STDTIME_WCHAR) 0xFF)
      {
      /* non-Ansi Unicode characters are converted to 0xFF */
      *pTarget = (char) STDTIME_UNICODE_SUBSTITUTE_CHAR;
      }

    else
      {
      *pTarget = (char) *pSource;
      }

    if (*pTarget == 0)
      {
      break;
      }

    pSource++;
    pTarget++;

    } /* for */

  return pTarget;

  } /* Char_StdTime_StrcpyAW */

#endif  /* Char_StdTime_StrcpyAW not presently needed */


/*-***************************************************************************/
/*            Wchar_StdTime_StrcpyWA - PRIVATE FUNCTION                      */
/*  copy CHAR to WCHAR string until nul reached                              */
/*****************************************************************************/

static STDTIME_WCHAR *      Wchar_StdTime_StrcpyWA (
  STDTIME_WCHAR *           /*O*/ pTarget,
  const char *              /*I*/ pSource)
  {
  /* copy from CHAR to WCHAR, stopping at nul */
  /* Return ptr to terminator, useful for doing strcat operations */

  if (pTarget == NULL)
    {
    return NULL;
    }

  if (pSource == NULL)
    {
    pTarget [0] = 0;
    return pTarget;
    }

  for (;;)
    {
    *pTarget = (unsigned char) *pSource;

    if (*pTarget == 0)
      {
      break;
      }

    pSource++;
    pTarget++;

    } /* for */

  return pTarget;

  } /* Wchar_StdTime_StrcpyWA */


/*-***************************************************************************/
/*            Char_StdTime_StrncpyAW - PRIVATE FUNCTION                      */
/*  copy WCHAR to CHAR string until nul reached or 'n' chars copied          */
/*****************************************************************************/

static char *               Char_StdTime_StrncpyAW (
  char *                    /*O*/ pTarget,
  const STDTIME_WCHAR *     /*I*/ pSource,
  size_t                    /*I*/ nLength)
  {
  /* copy from WCHAR to CHAR, stopping at nul */
  /* copy at most nLength characters, even if terminator not copied */
  /* Return ptr to terminator, useful for doing strcat operations */

  if (pTarget == NULL)
    {
    return NULL;
    }

  if (nLength < 1)
    {
    /* if no characters are copied, no terminator is set, either */
    return pTarget;
    }

  if (pSource == NULL)
    {
    pTarget [0] = 0;
    return pTarget;
    }

  for (;;)
    {
    if (*pSource > 0xFF)
      {
      /* non-Ansi Unicode characters are converted to 0xFF */
      *pTarget = (char) STDTIME_UNICODE_SUBSTITUTE_CHAR;
      }

    else
      {
      *pTarget = (char) *pSource;
      }

    if (*pTarget == 0)
      {
      break;
      }

    pSource++;
    pTarget++;
    nLength--;

    if (nLength == 0)
      {
      /* if copy halted by length, leave pointer after end of */
      /* copied string, so returned ptr can be used for strcat */
      break;
      }

    } /* for */

  return pTarget;

  } /* Char_StdTime_StrncpyAW */


/*-***************************************************************************/
/*            Wchar_StdTime_StrncpyWA - PRIVATE FUNCTION                     */
/*  copy CHAR to WCHAR string until nul reached or 'n' chars copied          */
/*****************************************************************************/

static STDTIME_WCHAR *      Wchar_StdTime_StrncpyWA (
  STDTIME_WCHAR *           /*O*/ pTarget,
  const char *              /*I*/ pSource,
  size_t                    /*I*/ nLength)
  {
  /* copy from CHAR to WCHAR, stopping at nul */
  /* copy at most nLength characters, even if terminator not copied */
  /* Return ptr to terminator, useful for doing strcat operations */

  if (pTarget == NULL)
    {
    return NULL;
    }

  if (nLength < 1)
    {
    /* if no characters are copied, no terminator is set, either */
    return pTarget;
    }

  if (pSource == NULL)
    {
    pTarget [0] = 0;
    return pTarget;
    }

  for (;;)
    {
    *pTarget = (unsigned char) *pSource;

    if (*pTarget == 0)
      {
      break;
      }

    pSource++;
    pTarget++;
    nLength--;

    if (nLength == 0)
      {
      /* if copy halted by length, leave pointer after end of */
      /* copied string, so returned ptr can be used for strcat */
      break;
      }

    } /* for */

  return pTarget;

  } /* Wchar_StdTime_StrncpyWA */


/*-***************************************************************************/
/*            Wchar_StdTime_StrncpyWA_Sub - PRIVATE FUNCTION                 */
/*  copy CHAR to WCHAR string until nul reached or 'n' chars copied          */
/*  use original WCHAR string as a reference, retaining any Unicode chars    */
/*  in the 'basis' string that had been translated to a "substitute" char.   */
/*****************************************************************************/

static STDTIME_WCHAR *      Wchar_StdTime_StrncpyWA_Sub (
  STDTIME_WCHAR *           /*O*/ pTarget,
  const char *              /*I*/ pSource,
  size_t                    /*I*/ nLength,
  const STDTIME_WCHAR *     /*O*/ pBasis)
  {
  unsigned char             aChar;
  STDTIME_WCHAR             wChar;

  /* copy from CHAR to WCHAR, stopping at nul */
  /* copy at most nLength characters, even if terminator not copied */
  /* Return ptr to terminator, useful for doing strcat operations */

  if (pBasis == NULL)
    {
    return Wchar_StdTime_StrncpyWA (pTarget, pSource, nLength);
    }

  if (pTarget == NULL)
    {
    return NULL;
    }

  if (nLength < 1)
    {
    /* if no characters are copied, no terminator is set, either */
    return pTarget;
    }

  if (pSource == NULL)
    {
    pTarget [0] = 0;
    return pTarget;
    }

  for (;;)
    {
    aChar = (unsigned char) *pSource;
    wChar = 0;

    if (aChar == (unsigned char) STDTIME_UNICODE_SUBSTITUTE_CHAR)
      {
      /* use next available unicode char in the basis string */
      for (; *pBasis; pBasis++)
        {
        if ((*pBasis == (STDTIME_WCHAR) STDTIME_UNICODE_SUBSTITUTE_CHAR)
        ||  (*pBasis > (STDTIME_WCHAR) 0xFF))
          {
          wChar = *pBasis++;
          break;
          }
        }
      }

    if (wChar)  /* replacement unicode char found in basis string */
      {
      *pTarget = wChar;
      }

    else
      {
      *pTarget = (STDTIME_WCHAR) aChar;  /* use source char as is */
      }

    if (*pTarget == 0)
      {
      break;
      }

    pSource++;
    pTarget++;
    nLength--;

    if (nLength == 0)
      {
      /* if copy halted by length, leave pointer after end of */
      /* copied string, so returned ptr can be used for strcat */
      break;
      }

    } /* for */

  return pTarget;

  } /* Wchar_StdTime_StrncpyWA_Sub */


/*-***************************************************************************/
/*            Int_StdTime_StrlenW - PRIVATE FUNCTION                         */
/*  portable Unicode strlen function                                         */
/*****************************************************************************/

static int32_t              Int_StdTime_StrlenW (
  const STDTIME_WCHAR *     /*I*/ pSource)
  {
  int32_t                   len = 0;

  if (pSource == NULL) return 0;

  while (pSource [len] != (STDTIME_WCHAR) 0)
    {
    len++;
    }

  return len;

  } /* Int_StdTime_StrlenW */


/*-***************************************************************************/
/*            Wchar_StdTime_StrcpyWW                                         */
/*  copy WCHAR to WCHAR string until nul reached or 'n' chars copied         */
/*****************************************************************************/

STDTIME_WCHAR *             Wchar_StdTime_StrcpyWW (
  STDTIME_WCHAR *           /*O*/ pTarget,
  const STDTIME_WCHAR *     /*I*/ pSource)
  {
  /* copy from WCHAR to WCHAR, stopping at nul */
  /* copy at most nLength characters, even if terminator not copied */
  /* Return ptr to terminator, useful for doing strcat operations */

  if (pTarget == NULL)
    {
    return NULL;
    }

  if (pSource == NULL)
    {
    pTarget [0] = 0;
    return pTarget;
    }

  for (;;)
    {
    *pTarget = *pSource;

    if (*pTarget == 0)
      {
      break;
      }

    pSource++;
    pTarget++;

    } /* for */

  return pTarget;

  } /* Wchar_StdTime_StrcpyWW */


/*-***************************************************************************/
/*            Wchar_StdTime_StrncpyWW                                        */
/*  copy WCHAR to WCHAR string until nul reached or 'n' chars copied         */
/*****************************************************************************/

STDTIME_WCHAR *             Wchar_StdTime_StrncpyWW (
  STDTIME_WCHAR *           /*O*/ pTarget,
  const STDTIME_WCHAR *     /*I*/ pSource,
  size_t                    /*I*/ nLength)
  {
  /* copy from WCHAR to WCHAR, stopping at nul */
  /* copy at most nLength characters, even if terminator not copied */
  /* Return ptr to terminator, useful for doing strcat operations */

  if (pTarget == NULL)
    {
    return NULL;
    }

  if (nLength < 1)
    {
    /* if no characters are copied, no terminator is set, either */
    return pTarget;
    }

  if (pSource == NULL)
    {
    pTarget [0] = 0;
    return pTarget;
    }

  for (;;)
    {
    *pTarget = *pSource;

    if (*pTarget == 0)
      {
      break;
      }

    pSource++;
    pTarget++;
    nLength--;

    if (nLength == 0)
      {
      /* if copy halted by length, leave pointer after end of */
      /* copied string, so returned ptr can be used for strcat */
      break;
      }

    } /* for */

  return pTarget;

  } /* Wchar_StdTime_StrncpyWW */


/*-***************************************************************************/
/*            Rc_StdTime_TimeTBase - PRIVATE FUNCTION                        */
/*  form FILETIME equal to Jan 1, 1970, the base of time_t                   */
/*****************************************************************************/

static STDTIME_RC           Rc_StdTime_TimeTBase (
  STDTIME_WIN_FILETIME *    /*O*/ pFileTime)
  {
  /* form FILETIME equal to Jan 1, 1970, the base of time_t */
  /* this is a constant value 116444736000000000 */

  STDTIME_ENUM_FUNC (Rc_StdTime_TimeTBase)

  if (pFileTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  pFileTime->dwHighDateTime = PVT_STDTIME_U32_TIMET_BASE_HI;
  pFileTime->dwLowDateTime  = PVT_STDTIME_U32_TIMET_BASE_LO;

  STDTIME_RET_OK;

  } /* Rc_StdTime_TimeTBase */


/*-***************************************************************************/
/*            Rc_NormalizeStdTimeFields                                      */
/*  ensure a STDTIME_FIELDS value is normalized, adjusting fields as needed. */
/*****************************************************************************/


#define PVT_STDTIME_NORMALIZE_FIELD(curr,num,next)                            \
  while ((curr) < 0)                                                          \
    {                                                                         \
    (curr) += num;                                                            \
    (next)--;                                                                 \
    }                                                                         \
  if ((curr) >= num)                                                          \
    {                                                                         \
    (next) += (curr) / num;                                                   \
    (curr) =  (curr) % num;                                                   \
    }


STDTIME_RC                  Rc_NormalizeStdTimeFields (
  STDTIME_FIELDS *          pFields)
  {
  STDTIME_DELTA             delta = {0};
  int32_t                   new_day = 0;
  int32_t                   max_day;

  STDTIME_ENUM_FUNC (Rc_NormalizeStdTimeFields)

  if (pFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  PVT_STDTIME_NORMALIZE_FIELD (pFields->nsec, 1000, pFields->usec)
  PVT_STDTIME_NORMALIZE_FIELD (pFields->usec, 1000, pFields->msec)
  PVT_STDTIME_NORMALIZE_FIELD (pFields->msec, 1000, pFields->sec )
  PVT_STDTIME_NORMALIZE_FIELD (pFields->sec,    60, pFields->min )
  PVT_STDTIME_NORMALIZE_FIELD (pFields->min,    60, pFields->hour)
  PVT_STDTIME_NORMALIZE_FIELD (pFields->hour,   24, delta.day)

  if (delta.day == 0)
    {
    /* did not change the day, so no calendar normalization needed */
    STDTIME_RET_OK;
    }

  /* easy normalization: just day, within current month */

  max_day = StdTimeDaysInYearMon (pFields->year, pFields->mon);
  new_day = pFields->day + delta.day;

  if ((new_day >= 1)
  &&  (new_day <= max_day)
  &&  (pFields->mon >= 1)
  &&  (pFields->mon <= 12))
    {
    /* month was good, and day did not overflow the month */
    pFields->day = new_day;
    STDTIME_RET_OK;
    }

  /* hard normalization: do full AddDelta processing */

  STDTIME_RET (StdTimeFields_AddDelta (pFields, &delta));

  } /* Rc_NormalizeStdTimeFields */

#undef PVT_STDTIME_NORMALIZE_FIELD


/*-***************************************************************************/
/*            Rc_StdTime_NormalizeSystemTimeEx                               */
/*  ensure a SYSTEMTIME value is normalized, adjusting fields as needed.     */
/*  method: convert to STDTIME_FIELDS, normalize that, and convert back.     */
/*****************************************************************************/

STDTIME_RC                  Rc_StdTime_NormalizeSystemTimeEx (
  STDTIME_WIN_SYSTEMTIME *  /*IO*/ pSystemTime,
  int32_t *                 /*IO*/ pUsec,
  int32_t *                 /*IO*/ pNsec)
  {
  STDTIME_FIELDS            fields = {0};
  STDTIME_ENUM_FUNC (Rc_StdTime_NormalizeSystemTimeEx)

  if (pSystemTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  fields.year = (int32_t) pSystemTime->wYear;
  fields.mon  = (int32_t) pSystemTime->wMonth;
  fields.day  = (int32_t) pSystemTime->wDay;

  fields.hour = (int32_t) pSystemTime->wHour;
  fields.min  = (int32_t) pSystemTime->wMinute;
  fields.sec  = (int32_t) pSystemTime->wSecond;

  fields.msec = (int32_t) pSystemTime->wMilliseconds;

  if (pUsec != NULL)
    {
    fields.usec = *pUsec;
    }

  if (pNsec != NULL)
    {
    fields.nsec = *pNsec;
    }

  rc = Rc_NormalizeStdTimeFields (&fields);

  pSystemTime->wYear         = (STDTIME_WIN_WORD) fields.year;
  pSystemTime->wMonth        = (STDTIME_WIN_WORD) fields.mon ;
  pSystemTime->wDay          = (STDTIME_WIN_WORD) fields.day ;

  pSystemTime->wHour         = (STDTIME_WIN_WORD) fields.hour;
  pSystemTime->wMinute       = (STDTIME_WIN_WORD) fields.min ;
  pSystemTime->wSecond       = (STDTIME_WIN_WORD) fields.sec ;

  pSystemTime->wMilliseconds = (STDTIME_WIN_WORD) fields.msec;

  if (pUsec != NULL)
    {
    *pUsec = fields.usec;
    }

  if (pNsec != NULL)
    {
    *pNsec = fields.nsec;
    }

  return rc;

  } /* Rc_StdTime_NormalizeSystemTimeEx */


/*-***************************************************************************/
/*            Rc_StdTime_NormalizeStructTmEx                                 */
/*  ensure a struct tm value is normalized, adjusting fields as needed.      */
/*  method: convert to STDTIME_FIELDS, normalize that, and convert back.     */
/*****************************************************************************/

STDTIME_RC                  Rc_StdTime_NormalizeStructTmEx (
  struct tm *               /*IO*/ pStructTm,
  int32_t *                 /*IO*/ pMsec,
  int32_t *                 /*IO*/ pUsec,
  int32_t *                 /*IO*/ pNsec)
  {
  STDTIME_FIELDS            fields = {0};

  STDTIME_ENUM_FUNC (Rc_StdTime_NormalizeStructTmEx)

  if (pStructTm == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }


  fields.year = (int32_t) pStructTm->tm_year + 1900;
  fields.mon  = (int32_t) pStructTm->tm_mon + 1;
  fields.day  = (int32_t) pStructTm->tm_mday;

  fields.hour = (int32_t) pStructTm->tm_hour;
  fields.min  = (int32_t) pStructTm->tm_min;
  fields.sec  = (int32_t) pStructTm->tm_sec;

  if (pMsec != NULL)
    {
    fields.msec = *pMsec;
    }

  if (pUsec != NULL)
    {
    fields.usec = *pUsec;
    }

  if (pNsec != NULL)
    {
    fields.nsec = *pNsec;
    }

  rc = Rc_NormalizeStdTimeFields (&fields);

  pStructTm->tm_year = (int) fields.year - 1900;
  pStructTm->tm_mon  = (int) fields.mon - 1;
  pStructTm->tm_mday = (int) fields.day;

  pStructTm->tm_hour = (int) fields.hour;
  pStructTm->tm_min  = (int) fields.min;
  pStructTm->tm_sec  = (int) fields.sec;

  if (pMsec != NULL)
    {
    *pMsec = fields.msec;
    }

  if (pUsec != NULL)
    {
    *pUsec = fields.usec;
    }

  if (pNsec != NULL)
    {
    *pNsec = fields.nsec;
    }

  return rc;

  } /* Rc_StdTime_NormalizeStructTmEx */


/*-***************************************************************************/
/*            Rc_StdTime_FileTimeToSystemTimeEx - PRIVATE FUNCTION           */
/*  convert FILETIME to SYSTEMTIME, extracting and storing fractional        */
/*  seconds not available in a SYSTEMTIME structure, if pointers provided.   */
/*****************************************************************************/

static STDTIME_RC           Rc_StdTime_FileTimeToSystemTimeEx (
  const STDTIME_WIN_FILETIME * /*I*/ pFileTime,
  STDTIME_WIN_SYSTEMTIME *     /*O*/ pSystemTime,
  int32_t *                    /*O*/ pUsec,
  int32_t *                    /*O*/ pNsec)
  {
  /* helper function to convert FILETIME to SYSTEMTIME and capture */
  /* fractional milliseconds */

  QUADLIB_I64               qFileTime;
  QUADLIB_I64               work;
  int32_t                   frac;
  int32_t                   msec;
  int32_t                   usec;
  int32_t                   nsec;

  STDTIME_ENUM_FUNC (Rc_StdTime_FileTimeToSystemTimeEx)

  if (pSystemTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pSystemTime = StdTimeApiZeroSystemTime();

  if (pFileTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  /* extract fractional seconds (units of 100 nanoseconds) */

  QUADLIB_U64_HI(qFileTime) = pFileTime->dwHighDateTime;
  QUADLIB_U64_LO(qFileTime) = pFileTime->dwLowDateTime;

  work = QUADLIB_U64_MOD (
    qFileTime, QUADLIB_U64_CASTU32 (PVT_STDTIME_SCALE_FILETIME));

  frac = QUADLIB_U64_LO(work);

  if (! STDTIME_API_FILETIMETOSYSTEMTIME (pFileTime, pSystemTime))
    {
    STDTIME_RET_EC (failure_in_api_FileTimeToSystemTime);
    }

  /* extract 1 digit of nanoseconds, but make it a 3-digit value */

  nsec = (frac % STDTIME_PREC_NSEC) * STDTIME_SCALE_NSEC;
  frac /= STDTIME_PREC_NSEC;
  usec = frac % 1000;
  frac /= 1000;
  msec = (frac % 1000);

  /* if output field ptrs are NULL, round up */

  PVT_STDTIME_ROUND (pNsec, nsec, usec)
  PVT_STDTIME_ROUND (pUsec, usec, msec)

  pSystemTime->wMilliseconds = (STDTIME_WIN_WORD) msec;

  STDTIME_RET (Rc_StdTime_NormalizeSystemTimeEx (pSystemTime, pNsec, pUsec));

  } /* Rc_StdTime_FileTimeToSystemTimeEx */


/*-***************************************************************************/
/*            Rc_StdTime_SystemTimeExToFileTime - PRIVATE FUNCTION           */
/*  convert SYSTEMTIME to FILETIME, incorporating additional parameters      */
/*  to account for fractional seconds not available in a SYSTEMTIME.         */
/*****************************************************************************/

static STDTIME_RC           Rc_StdTime_SystemTimeExToFileTime (
  const STDTIME_WIN_SYSTEMTIME *    /*I*/ pSystemTime,
  int32_t                           /*I*/ nUsec,
  int32_t                           /*I*/ nNsec,
  STDTIME_WIN_FILETIME *            /*O*/ pFileTime)
  {
  STDTIME_ENUM_FUNC (Rc_StdTime_SystemTimeExToFileTime)

  /* helper function to convert SYSTEMTIME to FILETIME and add in */
  /* fractional milliseconds */

  if (pFileTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pFileTime = StdTimeApiZeroFileTime();

  if (pSystemTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if (! STDTIME_API_SYSTEMTIMETOFILETIME (pSystemTime, pFileTime))
    {
    STDTIME_RET_EC (failure_in_api_SystemTimeToFileTime);
    }

  if ((nUsec != 0) || (nNsec != 0))
    {
    /* add in fractional seconds */
    STDTIME_DELTA           delta = {0};
    STDTIME_SPAN            span;
    QUADLIB_I64             qFileTime;

    FILETIME_TO_QUADLIB_I64 (pFileTime, &qFileTime);
    delta.usec = nUsec;
    delta.nsec = nNsec;
    StdTimeDeltaToStdTimeSpan (&delta, &span);
    QUADLIB_I64_ADD_EQ (qFileTime, span.value);
    QUADLIB_I64_TO_FILETIME (&qFileTime, pFileTime);
    }

  STDTIME_RET_OK;

  } /* Rc_StdTime_SystemTimeExToFileTime */


/*-***************************************************************************/
/*            Int_StdTime_GetNumField - PRIVATE FUNCTION                     */
/*  extract a fixed-length decimal string and Return int32_t value or -1     */
/*****************************************************************************/

static int32_t              Int_StdTime_GetNumField (
  const char *              /*I*/ str,
  int32_t                   /*I*/ len)
  {
  /* extract a decimal string and Return int32_t value */
  /* an exact number of digits must be present */
  /* string is delimited by length, not by null terminator */
  /* on error, Return -1 */

  int32_t                   result = 0;
  int32_t                   i;
  int32_t                   c;

  if ((str == NULL) || (len < 1))
    {
    return -1;
    }

  for (i=0; i < len; i++)
    {
    c = str[i];

    if ((c < '0') || (c > '9'))
      {
      return -1;
      }

    result = (result * 10) + (c - '0');
    }

  return result;

  } /* Int_StdTime_GetNumField */


/*-***************************************************************************/
/*            Int_StdTime_GetHexField - PRIVATE FUNCTION                     */
/*  extract a fixed-length hex string and Return int32_t value or -1         */
/*****************************************************************************/

static int32_t              Int_StdTime_GetHexField (
  const char *              /*I*/ str,
  int32_t                   /*I*/ len)
  {
  /* extract a hex string and Return int32_t value */
  /* an exact number of digits must be present */
  /* string is delimited by length, not by null terminator */
  /* on error, Return -1 */

  int32_t                   result = 0;
  int32_t                   i;
  int32_t                   c;

  if ((str == NULL) || (len < 1))
    {
    return -1;
    }

  for (i=0; i < len; i++)
    {
    c = str[i];

    if ((c >= '0') && (c <= '9'))
      {
      result = (result * 16) + (c - '0');
      }

    else if ((c >= 'A') && (c <= 'F'))
      {
      result = (result * 16) + (c - 'A' + 10);
      }

    else if ((c >= 'a') && (c <= 'f'))
      {
      result = (result * 16) + (c - 'a' + 10);
      }

    else
      {
      return -1;
      }

    }

  return result;

  } /* Int_StdTime_GetHexField */


/*-***************************************************************************/
/*            StdTimeYearIsLeap                                              */
/*  Return 1 if year is leapyear, else Return 0                              */
/*****************************************************************************/

int32_t                     StdTimeYearIsLeap (
  int32_t                   /*I*/ year)
  {
  /* no assertions made about invalid years */

  if ((year < STDTIME_YEAR_MIN) || (year > STDTIME_YEAR_MAX))
    {
    return 0;
    }

  if ((year % 4000) == 0)
    {
    return 0;               /* multiples of 4000 are not leap years */
    }

  if ((year % 400) == 0)
    {
    return 1;               /* multiples of 400 are leap years */
    }

  if ((year % 100) == 0)
    {
    return 0;               /* multiples of 100 are not leap years */
    }

  if ((year % 4) == 0)
    {
    return 1;               /* multiples of 4 are leap years */
    }

  return 0;                 /* all others are not leap years */

  } /* StdTimeYearIsLeap */


/*-***************************************************************************/
/*            StdTimeDaysInYearMon                                           */
/*  calendar function: get maximum number of days in month for a given year  */
/*****************************************************************************/

static int32_t              StdTimeDaysPerMonTab [13] =
  { 00,
    31,   /* JAN */
    28,   /* FEB */
    31,   /* MAR */
    30,   /* APR */
    31,   /* MAY */
    30,   /* JUN */
    31,   /* JUL */
    31,   /* AUG */
    30,   /* SEP */
    31,   /* OCT */
    30,   /* NOV */
    31    /* DEC */
  };

static int32_t              StdTimeDaysPerMonLeapTab [13] =
  { 00,
    31,   /* JAN */
    29,   /* FEB */
    31,   /* MAR */
    30,   /* APR */
    31,   /* MAY */
    30,   /* JUN */
    31,   /* JUL */
    31,   /* AUG */
    30,   /* SEP */
    31,   /* OCT */
    30,   /* NOV */
    31    /* DEC */
  };

int32_t                     StdTimeDaysInYearMon (
  int32_t                   /*I*/ year,
  int32_t                   /*I*/ mon)
  {
  int32_t                   leap = 0;

  if ((year < STDTIME_YEAR_MIN)
  ||  (year > STDTIME_YEAR_MAX)
  ||  (mon  < 1)
  ||  (mon  > 12))
    {
    return 0;       /* argument error */
    }

  if (mon == 2)
    {
    leap = StdTimeYearIsLeap (year);
    }

  return leap + StdTimeDaysPerMonTab [mon];

  } /* StdTimeDaysInYearMon */


/*-***************************************************************************/
/*            Rc_StdTime_ValidFileTime - PRIVATE FUNCTION                    */
/*  Return STDTIME_OK if FILETIME value is within range of STDTIME           */
/*****************************************************************************/

static STDTIME_RC           Rc_StdTime_ValidFileTime (
  const STDTIME_WIN_FILETIME * /*I*/ pFileTime)
  {
  QUADLIB_I64               qFileTime;
  QUADLIB_I64               qMaxFileTime;

  STDTIME_ENUM_FUNC (Rc_StdTime_ValidFileTime)

  if (pFileTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  FILETIME_TO_QUADLIB_I64 (pFileTime, &qFileTime);

  /* filetime cannot be < 0 */

  if (QUADLIB_I64_LT_0 (qFileTime))
    {
    STDTIME_RET_EC (invalid_FileTime);
    }

  QUADLIB_U64_HI (qMaxFileTime) = PVT_STDTIME_MAX_FILETIME_HI;
  QUADLIB_U64_LO (qMaxFileTime) = PVT_STDTIME_MAX_FILETIME_LO;

  /* filetime cannot be > 9999-12-31 23:59:59.9999999 */

  if (QUADLIB_I64_GT (qFileTime, qMaxFileTime))
    {
    STDTIME_RET_EC (invalid_FileTime);
    }

  STDTIME_RET_OK;

  } /* Rc_StdTime_ValidFileTime */


/*-***************************************************************************/
/*            Rc_StdTime_FileTimeSplit - PRIVATE FUNCTION                    */
/*  split FILETIME into FILETIME, usec and nsec.                             */
/*****************************************************************************/

static STDTIME_RC           Rc_StdTime_FileTimeSplit (
  STDTIME_WIN_FILETIME *    /*IO*/ pFileTime,
  int32_t *                 /*IO*/ pUsec,
  int32_t *                 /*IO*/ pNsec)
  {
  QUADLIB_I64               qFileTime;
  QUADLIB_I64               qFactor;
  QUADLIB_I64               qResult;
  QUADLIB_I64               qRemainder;

  STDTIME_ENUM_FUNC (Rc_StdTime_FileTimeSplit)

  if ((pFileTime == NULL) || (pUsec == NULL) || (pNsec == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  /* divide 64-bit filetime by 10000 to extract usec,nsec */
  /* then Return these values */

  FILETIME_TO_QUADLIB_I64 (pFileTime, &qFileTime);
  QUADLIB_U64_HI (qFactor) = 0;
  QUADLIB_U64_LO (qFactor) = 10000;

  qResult = QuadLibI64DivMod (qFileTime, qFactor, &qRemainder);
  qFileTime = QUADLIB_I64_MUL (qResult, qFactor);
  QUADLIB_I64_TO_FILETIME (&qFileTime, pFileTime);

  *pUsec = QUADLIB_I64_LO (qRemainder) / 10;
  *pNsec = (QUADLIB_I64_LO (qRemainder) % 10) * 100;

  STDTIME_RET_OK;

  } /* Rc_StdTime_FileTimeSplit */


/*-***************************************************************************/
/*            Int_StdTime_GmtYear - PRIVATE FUNCTION                         */
/*  get the current GMT year for timezone processing reasons                 */
/*  the function is system-specific to be as fast as possible                */
/*****************************************************************************/

int32_t                     Int_StdTime_GmtYear ()
  {
  int32_t                   year;

#ifdef _WIN32

  SYSTEMTIME                currSystemTime;

  GetSystemTime (&currSystemTime);
  year = (int32_t) currSystemTime.wYear;

#else

  struct tm *               currStructTm;
  time_t                    currTimeT;

  currTimeT = time (NULL);
  currStructTm = gmtime (&currTimeT);

  if (currStructTm == NULL)
    {
    year = 0;
    }

  else
    {
    year = (int32_t) (currStructTm->tm_year + 1900);
    }

#endif

  return year;

  } /* Int_StdTime_GmtYear */


/*-***************************************************************************/
/*            Int_StdTime_LocYear - PRIVATE FUNCTION                         */
/*  get the current local year for timezone processing reasons               */
/*  the function is system-specific to be as fast as possible                */
/*****************************************************************************/

int32_t                     Int_StdTime_LocYear ()
  {
  int32_t                   year;

#ifdef _WIN32

  SYSTEMTIME                currSystemTime;

  GetLocalTime (&currSystemTime);
  year = (int32_t) currSystemTime.wYear;

#else

  struct tm *               currStructTm;
  time_t                    currTimeT;

  currTimeT = time (NULL);
  currStructTm = localtime (&currTimeT);

  if (currStructTm == NULL)
    {
    year = 0;
    }

  else
    {
    year = (int32_t) (currStructTm->tm_year + 1900);
    }

#endif

  return year;

  } /* Int_StdTime_LocYear */


/*** StdTime/StdTimeFields conversions ***************************************/

/*-***************************************************************************/
/*            StdTimeToStdTimeFields                                         */
/*  convert: StdTime structure to StdTimeFields structure                    */
/*  method: StdTime -> FILETIME -> SYSTEMTIME -> StdTimeFields               */
/*****************************************************************************/

STDTIME_RC                  StdTimeToStdTimeFields (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_WIN_FILETIME      ft;
  STDTIME_WIN_SYSTEMTIME    st;
  int32_t                   usec;
  int32_t                   nsec;

  STDTIME_ENUM_FUNC (StdTimeToStdTimeField)

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeFields = ZeroStdTimeFields ();

  if (pStdTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeToFileTime (pStdTime, &ft))
    {
    if STDTIME_IF (Rc_StdTime_FileTimeSplit (&ft, &usec, &nsec))
      {
      if (STDTIME_API_FILETIMETOSYSTEMTIME (&ft, &st))
        {
        STDTIME_RET (SystemTimeExToStdTimeFields (
          &st, usec, nsec, pStdTimeFields));
        }
      else
        {
        STDTIME_RET_EC (failure_in_api_FileTimeToSystemTime);
        }
      }
    }

  STDTIME_RET_RC;

  } /* StdTimeToStdTimeFields */


/*-***************************************************************************/
/*            StdTimeFieldsToStdTime                                         */
/*  convert: StdTimeFields structure to StdTime structure                    */
/*  method:  StdTimeFields -> SYSTEMTIME -> FILETIME -> StdTime              */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToStdTime (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_WIN_FILETIME      ft;
  STDTIME_WIN_SYSTEMTIME    st;
  int32_t                   usec;
  int32_t                   nsec;

  STDTIME_ENUM_FUNC (StdTimeFieldsToStdTime)

  if (pStdTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTime = ZeroStdTime ();

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeFieldsToSystemTimeEx (
       pStdTimeFields, &st, &usec, &nsec))
    {
    if STDTIME_IF (Rc_StdTime_SystemTimeExToFileTime (&st, usec, nsec, &ft))
      {
      if STDTIME_IF (FileTimeToStdTime (&ft, pStdTime))
        {
        STDTIME_RET (ValidStdTime (pStdTime));
        }
      else
        {
        STDTIME_RET_EC (failure_in_api_FileTimeToSystemTime);
        }
      }
    }

  STDTIME_RET_RC;

  } /* StdTimeFieldsToStdTime */


/*** StdTime/external conversions ********************************************/

/*-***************************************************************************/
/*            StdTimeToStdTimeStringA                                        */
/*  convert: StdTime structure to StdTimeToStdTimeStringA structure          */
/*****************************************************************************/

STDTIME_RC                  StdTimeToStdTimeStringA (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_STRINGA *         /*O*/ pStdTimeString)
  {
  STDTIME_FIELDS            f;

  STDTIME_ENUM_FUNC (StdTimeToStdTimeStringA)

  if (pStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeString = ZeroStdTimeStringA ();

  if (pStdTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeToStdTimeFields (pStdTime, &f))
    {
    STDTIME_RET (StdTimeFieldsToStdTimeStringA (&f, pStdTimeString));
    }

  STDTIME_RET_RC;

  }  /* StdTimeToStdTimeStringA */

/*-***************************************************************************/
/*            StdTimeToStdTimeStringW                                        */
/*  convert: StdTime structure to StdTimeToStdTimeStringW structure          */
/*****************************************************************************/

STDTIME_RC                  StdTimeToStdTimeStringW (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_STRINGW *         /*O*/ pStdTimeString)
  {
  STDTIME_FIELDS            f;

  STDTIME_ENUM_FUNC (StdTimeToStdTimeStringW)

  if (pStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeString = ZeroStdTimeStringW ();

  if (pStdTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeToStdTimeFields (pStdTime, &f))
    {
    STDTIME_RET (StdTimeFieldsToStdTimeStringW (&f, pStdTimeString));
    }

  STDTIME_RET_RC;

  }  /* StdTimeToStdTimeStringA */

/*-***************************************************************************/
/*            StdTimeToStdTimeHexStrA                                        */
/*  convert: StdTime structure to StdTimeToStdTimeHexStrA structure          */
/*****************************************************************************/

STDTIME_RC                  StdTimeToStdTimeHexStrA (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_HEXSTRA *         /*O*/ pStdTimeHexStr)
  {
  STDTIME_ENUM_FUNC (StdTimeToStdTimeHexStrA)

  if (pStdTimeHexStr == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeHexStr = ZeroStdTimeHexStrA ();

  if (pStdTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IFNOT (ValidStdTime (pStdTime))
    {
    STDTIME_RET_RC;
    }

  sprintf (pStdTimeHexStr->str, "%08X%08X", pStdTime->hi, pStdTime->lo);

  STDTIME_RET_OK;

  } /* StdTimeToStdTimeHexStrA */

/*-***************************************************************************/
/*            StdTimeToStdTimeHexStrW                                        */
/*  convert: StdTime structure to StdTimeToStdTimeHexStrW structure          */
/*****************************************************************************/

STDTIME_RC                  StdTimeToStdTimeHexStrW (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_HEXSTRW *         /*O*/ pStdTimeHexStr)
  {
  STDTIME_HEXSTRA           as;

  STDTIME_ENUM_FUNC (StdTimeToStdTimeHexStrW)

  if (pStdTimeHexStr == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeHexStr = ZeroStdTimeHexStrW ();

  if (pStdTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeToStdTimeHexStrA (pStdTime, &as))
    {
    Wchar_StdTime_StrncpyWA (pStdTimeHexStr->str, as.str, STDTIME_HEXSTR_LEN+1);
    STDTIME_RET_OK;
    }

  STDTIME_RET_RC;

  } /* StdTimeToStdTimeHexStrW */


/*** external/StdTime conversions ********************************************/

/*-***************************************************************************/
/*            StdTimeStringAToStdTime                                        */
/*  convert: StdTimeStringA structure to StdTime structure                   */
/*****************************************************************************/

STDTIME_RC                  StdTimeStringAToStdTime (
  const STDTIME_STRINGA *   /*I*/ pStdTimeString,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_FIELDS            f;

  STDTIME_ENUM_FUNC (StdTimeStringAToStdTime)

  if (pStdTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTime = ZeroStdTime ();

  if STDTIME_IF (StdTimeStringAToStdTimeFields (pStdTimeString, &f))
    {
    /* StdTimeStringAToStdTimeFields will apply embTzo to form GMT */

    STDTIME_RET (StdTimeFieldsToStdTime (&f, pStdTime));
    }

  STDTIME_RET_RC;

  } /* StdTimeStringAToStdTime */

/*-***************************************************************************/
/*            StdTimeStringWToStdTime                                        */
/*  convert: StdTimeStringW structure to StdTime structure                   */
/*****************************************************************************/

STDTIME_RC                  StdTimeStringWToStdTime (
  const STDTIME_STRINGW *   /*I*/ pStdTimeString,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_FIELDS            f;

  STDTIME_ENUM_FUNC (StdTimeStringWToStdTime)

  if (pStdTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTime = ZeroStdTime ();

  if STDTIME_IF (StdTimeStringWToStdTimeFields (pStdTimeString, &f))
    {
    /* StdTimeStringWToStdTimeFields will apply embTzo to form GMT */

    STDTIME_RET (StdTimeFieldsToStdTime (&f, pStdTime));
    }

  STDTIME_RET_RC;

  } /* StdTimeStringWToStdTime */

/*-***************************************************************************/
/*            StdTimeHexStrAToStdTime                                        */
/*  convert: StdTimeHexStrA structure to StdTime structure                   */
/*****************************************************************************/

STDTIME_RC                  StdTimeHexStrAToStdTime (
  const STDTIME_HEXSTRA *   /*I*/ pStdTimeHexStr,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_ENUM_FUNC (StdTimeHexStrAToStdTime)

  if (pStdTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTime = ZeroStdTime ();

  if (pStdTimeHexStr == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if (! ((pStdTimeHexStr->str[STDTIME_HEXSTR_LEN] == ' ')
      || (pStdTimeHexStr->str[STDTIME_HEXSTR_LEN] ==  0 )) )
    {
    /* not a good delimiter */
    STDTIME_RET_EC (invalid_delimiter);
    }

  pStdTime->hi = Int_StdTime_GetHexField (pStdTimeHexStr->str+0, 8);
  pStdTime->lo = Int_StdTime_GetHexField (pStdTimeHexStr->str+8, 8);

  STDTIME_RET (ValidStdTime (pStdTime));

  } /* StdTimeHexStrAToStdTime */

/*-***************************************************************************/
/*            StdTimeHexStrWToStdTime                                        */
/*  convert: StdTimeHexStrW structure to StdTime structure                   */
/*****************************************************************************/

STDTIME_RC                  StdTimeHexStrWToStdTime (
  const STDTIME_HEXSTRW *   /*I*/ pStdTimeHexStr,
  STDTIME *                 /*O*/ pStdTime)
  {
  /* copy Unicode string to Ansi string, then convert to StdTime */
  STDTIME_HEXSTRA           as;

  STDTIME_ENUM_FUNC (StdTimeHexStrWToStdTime)

  if (pStdTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTime = ZeroStdTime ();

  if (pStdTimeHexStr == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  Char_StdTime_StrncpyAW (as.str, pStdTimeHexStr->str, STDTIME_HEXSTR_LEN+1);

  STDTIME_RET (StdTimeHexStrAToStdTime (&as, pStdTime));

  } /* StdTimeHexStrWToStdTime */


/*** StdTimeFields/external conversions **************************************/

/*-***************************************************************************/
/*            StdTimeFieldsToStdTimeStringA                                  */
/*  convert: StdTimeFields structure to StdTimeStringA structure             */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToStdTimeStringA (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_STRINGA *         /*O*/ pStdTimeString)
  {
  int32_t                   nsec;
  STDTIME_FIELDS            f;          /* local copy of time fields */

  STDTIME_ENUM_FUNC (StdTimeFieldsToStdTimeStringA)

  if (pStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  /* there is no context to decide on a timezone offset, so it is cleared */
  /* with the rest of the output string */

  *pStdTimeString = ZeroStdTimeStringA ();

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  f = *pStdTimeFields;

  /* normalize values in case invalid */
  /* they shouldn't be invalid, but we must ensure that the string */
  /* value does not get corrupted with '-' signs or field-length overflow */

  f.year = abs(f.year) % 10000;
  f.mon  = abs(f.mon)  % 100;
  f.day  = abs(f.day)  % 100;
  f.hour = abs(f.hour) % 100;
  f.min  = abs(f.min)  % 100;
  f.sec  = abs(f.sec)  % 100;
  f.msec = abs(f.msec) % 1000;
  f.usec = abs(f.usec) % 1000;
  f.nsec = abs(f.nsec) % 1000;

  /* cannot use actual nanoseconds, just 1 digit due to limited precision */
  nsec = f.nsec / STDTIME_SCALE_NSEC;

  if STDTIME_IFNOT (ValidStdTimeFields (&f))
    {
    STDTIME_RET_RC;
    }

  sprintf (pStdTimeString->str,

    "%04d"  "%c"
    "%02d"  "%c"
    "%02d"  "%c"
    "%02d"  "%c"
    "%02d"  "%c"
    "%02d"  "%c"
    "%03d%03d%d",

    /* string format:   yyyy-mm  -dd  Thh  :mi  :ss  .ttt ttt t   */
    /* string position: 0123456  789  012  345  678  9012 345 6 7 */
    /* delimiters are taken from user-defined values, or default  */

    f.year,         PVT_STDTIME_USR_DLM_DATE,
    f.mon,          PVT_STDTIME_USR_DLM_DATE,
    f.day,          PVT_STDTIME_USR_DLM_SEP,
    f.hour,         PVT_STDTIME_USR_DLM_TIME,
    f.min,          PVT_STDTIME_USR_DLM_TIME,
    f.sec,          PVT_STDTIME_USR_DLM_FRAC,

    f.msec, f.usec, nsec);

  STDTIME_RET_OK;

  } /* StdTimeFieldsToStdTimeStringA */

/*-***************************************************************************/
/*            StdTimeFieldsToStdTimeStringW                                  */
/*  convert: StdTimeFields structure to StdTimeStringW structure             */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToStdTimeStringW (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_STRINGW *         /*O*/ pStdTimeString)
  {
  STDTIME_STRINGA           as;

  STDTIME_ENUM_FUNC (StdTimeFieldsToStdTimeStringW)

  if (pStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeString = ZeroStdTimeStringW ();

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  /* perform an Ansi string conversion, then copy to Unicode string */

  if STDTIME_IF (StdTimeFieldsToStdTimeStringA (pStdTimeFields, &as))
    {
    Wchar_StdTime_StrcpyWA (pStdTimeString->str, as.str);
    STDTIME_RET_OK;
    }

  STDTIME_RET_RC;

  } /* StdTimeFieldsToStdTimeStringW */

/*-***************************************************************************/
/*            StdTimeFieldsToStdTimeHexStrA                                  */
/*  convert: StdTimeFields structure to StdTimeHexStrA structure             */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToStdTimeHexStrA (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_HEXSTRA *         /*O*/ pStdTimeHexStr)
  {
  STDTIME                   t;

  STDTIME_ENUM_FUNC (StdTimeFieldsToStdTimeHexStrA)

  if (pStdTimeHexStr == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeHexStr = ZeroStdTimeHexStrA ();

  if STDTIME_IF (StdTimeFieldsToStdTime (pStdTimeFields, &t))
    {
    STDTIME_RET (StdTimeToStdTimeHexStrA (&t, pStdTimeHexStr));
    }

  STDTIME_RET_RC;

  } /* StdTimeFieldsToStdTimeHexStrA */

/*-***************************************************************************/
/*            StdTimeFieldsToStdTimeHexStrW                                  */
/*  convert: StdTimeFields structure to StdTimeHexStrW structure             */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToStdTimeHexStrW (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_HEXSTRW *         /*O*/ pStdTimeHexStr)
  {
  STDTIME                   t;

  STDTIME_ENUM_FUNC (StdTimeFieldsToStdTimeHexStrW)

  if (pStdTimeHexStr == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeHexStr = ZeroStdTimeHexStrW ();

  if STDTIME_IF (StdTimeFieldsToStdTime (pStdTimeFields, &t))
    {
    STDTIME_RET (StdTimeToStdTimeHexStrW (&t, pStdTimeHexStr));
    }

  STDTIME_RET_RC;

  } /* StdTimeFieldsToStdTimeHexStrW */


/*** external/StdTimeFields conversions **************************************/

/*-***************************************************************************/
/*            StdTimeStringAToStdTimeFields                                  */
/*  convert: StdTimeStringA structure to StdTimeFields structure             */
/*****************************************************************************/

/* string format:           yyyy-mm-ddThh:mi:ss.fffffff     */
/*                          0123456789012345678901234567    */

STDTIME_RC                  StdTimeStringAToStdTimeFields (
  const STDTIME_STRINGA *   /*I*/ pStdTimeString,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  /* method: validate delimiters, then extract numeric values */
  /* into a STDTIME_FIELDS structure.  if a timezone offset is present */
  /* then validate it, and apply its value to the time fields */

  STDTIME_STRINGA           s;
  STDTIME_TZOA              tzo;
  char                      c;

  STDTIME_ENUM_FUNC (StdTimeStringAToStdTimeFields)

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeFields = ZeroStdTimeFields ();

  if (pStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  s = *pStdTimeString;

  /* check for some reasonable delimiters */

  c = s.str[STDTIME_STRING_DLM_D1];     /* date delim between yyyy and mm */

  if ( (c != PVT_STDTIME_ISO_DLM_DATE)  /* normally '-' */
  &&   (c != PVT_STDTIME_USR_DLM_DATE)
  &&   (c != '/')                       /* common but nonstandard delimiter */
  &&   (c != ' ')
  &&   (c !=  0 ) )
    {
    STDTIME_RET_EC (invalid_delimiter);
    }

  c = s.str[STDTIME_STRING_DLM_D2];     /* date delim between mo and dd */

  if ( (c != PVT_STDTIME_ISO_DLM_DATE)  /* normally '-' */
  &&   (c != PVT_STDTIME_USR_DLM_DATE)
  &&   (c != '/')                       /* common but nonstandard delimiter */
  &&   (c != ' ')
  &&   (c !=  0 ) )
    {
    STDTIME_RET_EC (invalid_delimiter);
    }

  c = s.str[STDTIME_STRING_DLM_S1];     /* separator between dd and hh */

  if ( (c != PVT_STDTIME_ISO_DLM_SEP)   /* normally 'T' */
  &&   (c != PVT_STDTIME_USR_DLM_SEP)
  &&   (c != ' ')
  &&   (c !=  0 ) )
    {
    STDTIME_RET_EC (invalid_delimiter);
    }

  c = s.str[STDTIME_STRING_DLM_T1];     /* time delim between hh and mi */

  if ( (c != PVT_STDTIME_ISO_DLM_TIME)  /* normally ':' */
  &&   (c != PVT_STDTIME_USR_DLM_TIME)
  &&   (c != ' ')
  &&   (c !=  0 ) )
    {
    STDTIME_RET_EC (invalid_delimiter);
    }

  c = s.str[STDTIME_STRING_DLM_T2];     /* time delim between mi and ss */

  if ( (c != PVT_STDTIME_ISO_DLM_TIME)  /* normally ':' */
  &&   (c != PVT_STDTIME_USR_DLM_TIME)
  &&   (c != ' ')
  &&   (c !=  0 ) )
    {
    STDTIME_RET_EC (invalid_delimiter);
    }

  c = s.str[STDTIME_STRING_DLM_F1]; /* fraction delim between ss and fffffff */

  if ( (c != PVT_STDTIME_ISO_DLM_FRAC)  /* normally '.' */
  &&   (c != PVT_STDTIME_USR_DLM_FRAC)
  &&   (c != ' ')
  &&   (c != ',')                   /* iso 8601 also allows comma here */
  &&   (c !=  0 ) )
    {
    STDTIME_RET_EC (invalid_delimiter);
    }

  /* string may be followed by optional embTzo field */
  /* if so, we need to extract its value and adjust the time accordingly */
  /* it is valid for an embTzo to be empty (null string) */

  strncpy (tzo.str, s.embTzo, STDTIME_TZO_LEN);

  if STDTIME_IFNOT (NormalizeStdTimeTzoA (&tzo)) /* normalize also validates */
    {
    STDTIME_RET_RC;
    }

  /* Int_StdTime_GetNumField Returns -1 on error */
  /* this will be detected via ValidStdTimeFields */

  pStdTimeFields->year = Int_StdTime_GetNumField (s.str+0, 4);
  pStdTimeFields->mon  = Int_StdTime_GetNumField (s.str+5, 2);
  pStdTimeFields->day  = Int_StdTime_GetNumField (s.str+8, 2);
  pStdTimeFields->hour = Int_StdTime_GetNumField (s.str+11, 2);
  pStdTimeFields->min  = Int_StdTime_GetNumField (s.str+14, 2);
  pStdTimeFields->sec  = Int_StdTime_GetNumField (s.str+17, 2);
  pStdTimeFields->msec = Int_StdTime_GetNumField (s.str+20, 3);
  pStdTimeFields->usec = Int_StdTime_GetNumField (s.str+23, 3);

  pStdTimeFields->nsec = Int_StdTime_GetNumField (s.str+26, 1)
                       * STDTIME_SCALE_NSEC;

  if STDTIME_IFNOT (ValidStdTimeFields (pStdTimeFields))
    {
    STDTIME_RET_RC;
    }

  if ((tzo.str[0] == '+') || (tzo.str[0] == '-'))
    {
    /* a valid, non-null, non-Z timezone offset exists */
    /* extract the timezone offset fields and adjust the stdtime fields */
    /* +hh:mm:ss# */
    /* 0123456789 */

    STDTIME_DELTA           delta = {0};

    delta.hour = atoi (tzo.str+1);
    delta.min  = atoi (tzo.str+4);

    if (tzo.str[6] == ':')  /* seconds field is present */
      {
      delta.sec = atoi (tzo.str+7);
      }

    /* an offset like -05:00 means that 5 hours is subtracted from GMT to   */
    /* get local time.  however, the -05:00 appears next to the local time, */
    /* not the GMT time.  so, to get back to GMT, 5 hours would have to be  */
    /* added.  thus, '-' means "add offset to get GMT", and '+' means       */
    /* "subtract offset to get GMT".  we could use the normal meaning of    */
    /* '+' and '-' and use a SubDelta call, but there is overhead to negate */
    /* the delta.  instead, we negate only when '+' is used, and then call  */
    /* AddDelta.  it's counter-intuitive, but more efficient.               */

    if (tzo.str[0] == '+')  /* yes, '+' */
      {
      delta.hour = -(delta.hour);
      delta.min  = -(delta.min);
      delta.sec  = -(delta.sec);
      }

    STDTIME_RET (StdTimeFields_AddDelta (pStdTimeFields, &delta));
    }

  STDTIME_RET_OK;

  } /* StdTimeStringAToStdTimeFields */

/*-***************************************************************************/
/*            StdTimeStringWToStdTimeFields                                  */
/*  convert: StdTimeStringW structure to StdTimeFields structure             */
/*****************************************************************************/

STDTIME_RC                  StdTimeStringWToStdTimeFields (
  const STDTIME_STRINGW *   /*I*/ pStdTimeString,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  /* copy Unicode string to Ansi string */
  /* then call Ansi version of function */

  STDTIME_STRINGA           as;

  STDTIME_ENUM_FUNC (StdTimeStringWToStdTimeFields)

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeFields = ZeroStdTimeFields ();

  if (pStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  Char_StdTime_StrncpyAW (as.str, pStdTimeString->str, STDTIME_STRING_LEN+1);

  /* StdTimeStringAToStdTimeFields will apply embTzo to form GMT */

  STDTIME_RET (StdTimeStringAToStdTimeFields (&as, pStdTimeFields));

  } /* StdTimeStringWToStdTimeFields */

/*-***************************************************************************/
/*            StdTimeHexStrAToStdTimeFields                                  */
/*  convert: StdTimeHexStrA structure to StdTimeFields structure             */
/*****************************************************************************/

STDTIME_RC                  StdTimeHexStrAToStdTimeFields (
  const STDTIME_HEXSTRA *   /*I*/ pStdTimeHexStr,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME                   t;

  STDTIME_ENUM_FUNC (StdTimeHexStrAToStdTimeFields)

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeFields = ZeroStdTimeFields ();

  if (pStdTimeHexStr == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeHexStrAToStdTime (pStdTimeHexStr, &t))
    {
    STDTIME_RET (StdTimeToStdTimeFields (&t, pStdTimeFields));
    }

  STDTIME_RET_RC;

  } /* StdTimeHexStrAToStdTimeFields */

/*-***************************************************************************/
/*            StdTimeHexStrWToStdTimeFields                                  */
/*  convert: StdTimeHexStrW structure to StdTimeFields structure             */
/*****************************************************************************/

STDTIME_RC                  StdTimeHexStrWToStdTimeFields (
  const STDTIME_HEXSTRW *   /*I*/ pStdTimeHexStr,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME                   t;

  STDTIME_ENUM_FUNC (StdTimeHexStrWToStdTimeFields)

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeFields = ZeroStdTimeFields ();

  if (pStdTimeHexStr == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeHexStrWToStdTime (pStdTimeHexStr, &t))
    {
    STDTIME_RET (StdTimeToStdTimeFields (&t, pStdTimeFields));
    }

  STDTIME_RET_RC;

  } /* StdTimeHexStrWToStdTimeFields */


/*** StdTimeString/StdTimeHexStr conversions *********************************/

/*-***************************************************************************/
/*            StdTimeStringAToStdTimeHexStrA                                 */
/*  convert: StdTimeStringA structure to StdTimeHexStrA structure            */
/*****************************************************************************/

STDTIME_RC                  StdTimeStringAToStdTimeHexStrA (
  const STDTIME_STRINGA *   /*I*/ pStdTimeString,
  STDTIME_HEXSTRA *         /*O*/ pStdTimeHexStr)
  {
  STDTIME_FIELDS            f;

  STDTIME_ENUM_FUNC (StdTimeStringAToStdTimeHexStrA)

  if (pStdTimeHexStr == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeHexStr = ZeroStdTimeHexStrA ();

  if STDTIME_IF (StdTimeStringAToStdTimeFields (pStdTimeString, &f))
    {
    /* StdTimeStringAToStdTimeFields will apply embTzo if present */

    STDTIME_RET (StdTimeFieldsToStdTimeHexStrA (&f, pStdTimeHexStr));
    }

  STDTIME_RET_RC;

  } /* StdTimeStringAToStdTimeHexStrA */

/*-***************************************************************************/
/*            StdTimeStringWToStdTimeHexStrW                                 */
/*  convert: StdTimeStringW structure to StdTimeHexStrW structure            */
/*****************************************************************************/

STDTIME_RC                  StdTimeStringWToStdTimeHexStrW (
  const STDTIME_STRINGW *   /*I*/ pStdTimeString,
  STDTIME_HEXSTRW *         /*O*/ pStdTimeHexStr)
  {
  STDTIME_FIELDS            f;

  STDTIME_ENUM_FUNC (StdTimeStringWToStdTimeHexStrW)

  if (pStdTimeHexStr == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeHexStr = ZeroStdTimeHexStrW ();

  if STDTIME_IF (StdTimeStringWToStdTimeFields (pStdTimeString, &f))
    {
    STDTIME_RET (StdTimeFieldsToStdTimeHexStrW (&f, pStdTimeHexStr));
    }

  STDTIME_RET_RC;

  } /* StdTimeStringWToStdTimeHexStrW */

/*-***************************************************************************/
/*            StdTimeHexStrAToStdTimeStringA                                 */
/*  convert: StdTimeHexStrA structure to StdTimeStringA structure            */
/*****************************************************************************/

STDTIME_RC                  StdTimeHexStrAToStdTimeStringA (
  const STDTIME_HEXSTRA *   /*I*/ pStdTimeHexStr,
  STDTIME_STRINGA *         /*O*/ pStdTimeString)
  {
  STDTIME                   t;

  STDTIME_ENUM_FUNC (StdTimeHexStrAToStdTimeStringA)

  if (pStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeString = ZeroStdTimeStringA ();

  if STDTIME_IF (StdTimeHexStrAToStdTime (pStdTimeHexStr, &t))
    {
    STDTIME_RET (StdTimeToStdTimeStringA (&t, pStdTimeString));
    }

  STDTIME_RET_RC;

  } /* StdTimeHexStrAToStdTimeStringA */

/*-***************************************************************************/
/*            StdTimeHexStrWToStdTimeStringW                                 */
/*  convert: StdTimeHexStrW structure to StdTimeStringW structure            */
/*****************************************************************************/

STDTIME_RC                  StdTimeHexStrWToStdTimeStringW (
  const STDTIME_HEXSTRW *   /*I*/ pStdTimeHexStr,
  STDTIME_STRINGW *         /*O*/ pStdTimeString)
  {
  STDTIME                   t;

  STDTIME_ENUM_FUNC (StdTimeHexStrWToStdTimeStringW)

  if (pStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeString = ZeroStdTimeStringW ();

  if STDTIME_IF (StdTimeHexStrWToStdTime (pStdTimeHexStr, &t))
    {
    STDTIME_RET (StdTimeToStdTimeStringW (&t, pStdTimeString));
    }

  STDTIME_RET_RC;

  } /* StdTimeHexStrWToStdTimeStringW */


/*** Get (current UTC/GMT time) functions ************************************/

/*-***************************************************************************/
/*            GetStdTime                                                     */
/*  get current UTC time and store in StdTime structure                      */
/*  method: get current UTC time as a FILETIME, then convert to StdTime      */
/*****************************************************************************/

STDTIME_RC                  GetStdTime (
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_WIN_FILETIME      gmtFileTime;

  STDTIME_ENUM_FUNC (GetStdTime)

  if (pStdTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  STDTIME_API_GETSYSTEMTIMEASFILETIME (&gmtFileTime);

  STDTIME_RET (FileTimeToStdTime (&gmtFileTime, pStdTime));

  } /* GetStdTime */

/*-***************************************************************************/
/*            GetStdTimeFields                                               */
/*  get current UTC time and store in StdTimeFields structure                */
/*****************************************************************************/

STDTIME_RC                  GetStdTimeFields (
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME                   t;

  STDTIME_ENUM_FUNC (GetStdTimeFields)

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeFields = ZeroStdTimeFields ();

  if STDTIME_IF (GetStdTime (&t))
    {
    STDTIME_RET (StdTimeToStdTimeFields (&t, pStdTimeFields));
    }

  STDTIME_RET_RC;

  } /* GetStdTimeFields */

/*-***************************************************************************/
/*            GetStdTimeStringA                                              */
/*  get current UTC time and store as StdTimeStringA formatted string        */
/*****************************************************************************/

STDTIME_RC                  GetStdTimeStringA (
  STDTIME_STRINGA *         /*O*/ pStdTimeString)
  {
  STDTIME_FIELDS            f;

  STDTIME_ENUM_FUNC (GetStdTimeStringA)

  /* get current StdTime by getting the system time as StdTimeFields */
  /* and then converting that to a StdTimeStringA */

  if (pStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeString = ZeroStdTimeStringA ();

  if STDTIME_IFNOT (GetStdTimeFields (&f))
    {
    STDTIME_RET_RC;
    }

  /* StdTimeFieldsToStdTimeStringA will set extTzo to null string */
  /* because we know we are getting GMT/UTC time, the extTzo field */
  /* is then changed to Z, since that is what zone it is. */

  if STDTIME_IF (StdTimeFieldsToStdTimeStringA (&f, pStdTimeString))
    {
    pStdTimeString->extTzo.str[0] = 'Z';
    STDTIME_RET_OK;
    }

  STDTIME_RET_RC;

  } /* GetStdTimeStringA */

/*-***************************************************************************/
/*            GetStdTimeStringW                                              */
/*  get current UTC time and store as StdTimeStringW formatted string        */
/*****************************************************************************/

STDTIME_RC                  GetStdTimeStringW (
  STDTIME_STRINGW *         /*O*/ pStdTimeString)
  {
  STDTIME_FIELDS            f;

  STDTIME_ENUM_FUNC (GetStdTimeStringW)

  /* get current StdTime by getting the system time as StdTimeFields */
  /* and then converting that to a StdTimeStringW */

  if (pStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeString = ZeroStdTimeStringW ();

  if STDTIME_IFNOT (GetStdTimeFields (&f))
    {
    STDTIME_RET_RC;
    }

  /* StdTimeFieldsToStdTimeStringA will set extTzo to null string */
  /* because we know we are getting GMT/UTC time, the extTzo field */
  /* is then changed to Z, since that is what zone it is. */

  if STDTIME_IF (StdTimeFieldsToStdTimeStringW (&f, pStdTimeString))
    {
    pStdTimeString->extTzo.str[0] = (STDTIME_WCHAR) 'Z';
    STDTIME_RET_OK;
    }

  STDTIME_RET_RC;

  } /* GetStdTimeStringW */

/*-***************************************************************************/
/*            GetStdTimeHexStrA                                              */
/*  get current UTC time and store as StdTimeHexStrA formatted string        */
/*****************************************************************************/

STDTIME_RC                  GetStdTimeHexStrA (
  STDTIME_HEXSTRA *         /*O*/ pStdTimeHexStr)
  {
  STDTIME                   t;

  STDTIME_ENUM_FUNC (GetStdTimeHexStrA)

  if (pStdTimeHexStr == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeHexStr = ZeroStdTimeHexStrA ();

  if STDTIME_IF (GetStdTime (&t))
    {
    STDTIME_RET (StdTimeToStdTimeHexStrA (&t, pStdTimeHexStr));
    }

  STDTIME_RET_RC;

  } /* GetStdTimeHexStrA */

/*-***************************************************************************/
/*            GetStdTimeHexStrW                                              */
/*  get current UTC time and store as StdTimeHexStrW formatted string        */
/*****************************************************************************/

STDTIME_RC                  GetStdTimeHexStrW (
  STDTIME_HEXSTRW *         /*O*/ pStdTimeHexStr)
  {
  STDTIME                   t;

  STDTIME_ENUM_FUNC (GetStdTimeHexStrW)

  if (pStdTimeHexStr == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeHexStr = ZeroStdTimeHexStrW ();

  if STDTIME_IF (GetStdTime (&t))
    {
    STDTIME_RET (StdTimeToStdTimeHexStrW (&t, pStdTimeHexStr));
    }

  STDTIME_RET_RC;

  } /* GetStdTimeHexStrW */


/*** GetLocal (current time) functions ***************************************/

/*-***************************************************************************/
/*            GetLocalStdTime                                                */
/*  get current local time and store in StdTime structure                    */
/*  method: get current UTC time as a FILETIME, then convert to StdTime      */
/*****************************************************************************/

STDTIME_RC                  GetLocalStdTime (
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_WIN_FILETIME      gmtFileTime;
  STDTIME_WIN_FILETIME      locFileTime;

  STDTIME_ENUM_FUNC (GetLocalStdTime)

  if (pStdTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTime = ZeroStdTime ();

  STDTIME_API_GETSYSTEMTIMEASFILETIME (&gmtFileTime);

#ifdef STDTIME_LOCAL_USES_TZDB

  if STDTIME_IFNOT (StdTimeApiFileTimeToZonedFileTime (
       NULL, &gmtFileTime, &locFileTime))
    {
    STDTIME_RET_RC;
    }

#else

  if (! STDTIME_API_FILETIMETOLOCALFILETIME (&gmtFileTime, &locFileTime))
    {
    STDTIME_RET_EC (failure_in_api_FileTimeToLocalFileTime);
    }

#endif

    STDTIME_RET (FileTimeToStdTime (&locFileTime, pStdTime));

  } /* GetLocalStdTime */

/*-***************************************************************************/
/*            GetLocalStdTimeFields                                          */
/*  get current local time and store in StdTimeFields structure              */
/*****************************************************************************/

STDTIME_RC                  GetLocalStdTimeFields (
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_WIN_FILETIME      gmtFileTime;
  STDTIME_WIN_FILETIME      locFileTime;

  STDTIME_ENUM_FUNC (GetLocalStdTimeFields)

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeFields = ZeroStdTimeFields ();

  STDTIME_API_GETSYSTEMTIMEASFILETIME (&gmtFileTime);

#ifdef STDTIME_LOCAL_USES_TZDB

  if STDTIME_IFNOT (StdTimeApiFileTimeToZonedFileTime (
       NULL, &gmtFileTime, &locFileTime))
    {
    STDTIME_RET_RC;
    }

#else

  if (! STDTIME_API_FILETIMETOLOCALFILETIME (&gmtFileTime, &locFileTime))
    {
    STDTIME_RET_EC (failure_in_api_FileTimeToLocalFileTime);
    }

#endif

  STDTIME_RET (FileTimeToStdTimeFields (&locFileTime, pStdTimeFields));

  } /* GetLocalStdTimeFields */

/*-***************************************************************************/
/*            GetLocalStdTimeStringA                                         */
/*  get current local time and store in StdTimeStringA formatted string      */
/*  then, determine the current local timezone offset and save in extTzo.    */
/*****************************************************************************/

STDTIME_RC                  GetLocalStdTimeStringA (
  STDTIME_STRINGA *         /*O*/ pStdTimeString)
  {
  STDTIME_FIELDS            f;

  STDTIME_ENUM_FUNC (GetLocalStdTimeStringA)

  /* get current StdTime by getting the system time as StdTimeFields */
  /* and then converting that to a StdTimeStringA */

  if (pStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeString = ZeroStdTimeStringA ();

  if STDTIME_IFNOT (GetLocalStdTimeFields (&f))
    {
    STDTIME_RET_RC;
    }

  if STDTIME_IF (StdTimeFieldsToStdTimeStringA (&f, pStdTimeString))
    {
    /* store local timezone offset string */
    STDTIME_RET (GetLocalStdTimeTzoA (&(pStdTimeString->extTzo)));
    }

  STDTIME_RET_RC;

  } /* GetLocalStdTimeStringA */

/*-***************************************************************************/
/*            GetLocalStdTimeStringW                                         */
/*  get current local time and store in StdTimeStringW formatted string      */
/*  then, determine the current local timezone offset and save in extTzo.    */
/*****************************************************************************/

STDTIME_RC                  GetLocalStdTimeStringW (
  STDTIME_STRINGW *         /*O*/ pStdTimeString)
  {
  STDTIME_FIELDS            f;

  STDTIME_ENUM_FUNC (GetLocalStdTimeStringW)

  /* get current StdTime by getting the system time as StdTimeFields */
  /* and then converting that to a StdTimeStringW */

  if (pStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeString = ZeroStdTimeStringW ();

  if STDTIME_IFNOT (GetLocalStdTimeFields (&f))
    {
    STDTIME_RET_RC;
    }

  if STDTIME_IF (StdTimeFieldsToStdTimeStringW (&f, pStdTimeString))
    {
    /* store local timezone offset string */
    STDTIME_RET (GetLocalStdTimeTzoW (&(pStdTimeString->extTzo)));
    }

  STDTIME_RET_RC;

  } /* GetLocalStdTimeStringW */

/*-***************************************************************************/
/*            GetLocalStdTimeHexStrA                                         */
/*  get current local time and store as StdTimeHexStrA formatted string      */
/*****************************************************************************/

STDTIME_RC                  GetLocalStdTimeHexStrA (
  STDTIME_HEXSTRA *         /*O*/ pStdTimeHexStr)
  {
  STDTIME                   t;

  STDTIME_ENUM_FUNC (GetLocalStdTimeHexStrA)

  if (pStdTimeHexStr == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeHexStr = ZeroStdTimeHexStrA ();

  if STDTIME_IF (GetLocalStdTime (&t))
    {
    STDTIME_RET (StdTimeToStdTimeHexStrA (&t, pStdTimeHexStr));
    }

  STDTIME_RET_RC;

  } /* GetLocalStdTimeHexStrA */

/*-***************************************************************************/
/*            GetLocalStdTimeHexStrW                                         */
/*  get current local time and store as StdTimeHexStrW formatted string      */
/*****************************************************************************/

STDTIME_RC                  GetLocalStdTimeHexStrW (
  STDTIME_HEXSTRW *         /*O*/ pStdTimeHexStr)
  {
  STDTIME                   t;

  STDTIME_ENUM_FUNC (GetLocalStdTimeHexStrW)

  if (pStdTimeHexStr == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeHexStr = ZeroStdTimeHexStrW ();

  if STDTIME_IF (GetLocalStdTime (&t))
    {
    STDTIME_RET (StdTimeToStdTimeHexStrW (&t, pStdTimeHexStr));
    }

  STDTIME_RET_RC;

  } /* GetLocalStdTimeHexStrW */


/*** validation functions ****************************************************/

/*-***************************************************************************/
/*            ValidStdTime                                                   */
/*  return STDTIME_OK if StdTime is valid, else STDTIME_FALSE                */
/*****************************************************************************/

STDTIME_RC                  ValidStdTime (
  const STDTIME *           /*I*/ pStdTime)
  {
  STDTIME_ENUM_FUNC (ValidStdTime)

  /* validate a StdTime field */
  /* the only check here is that individual fields must not be negative */

  if (pStdTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if ((pStdTime->hi < 0) || (pStdTime->lo < 0))
    {
    STDTIME_RET_EC (invalid_StdTime);
    }

  STDTIME_RET_OK;

  } /* ValidStdTime */

/*-***************************************************************************/
/*            ValidStdTimeFields                                             */
/*  return STDTIME_OK if StdTimeFields is valid, else STDTIME_FALSE          */
/*****************************************************************************/

STDTIME_RC                  ValidStdTimeFields (
  const STDTIME_FIELDS *    /*I*/ pFields)
  {
  STDTIME_ENUM_FUNC (ValidStdTimeFields)

  if (pFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if (! STDTIME_IN_RANGE (pFields->year, STDTIME_YEAR_MIN, STDTIME_YEAR_MAX))
    {
    STDTIME_RET_EC (invalid_year);
    }

  if (! STDTIME_IN_RANGE (pFields->mon,  1, 12))
    {
    STDTIME_RET_EC (invalid_mon);
    }

  if (! STDTIME_IN_RANGE (pFields->day,  1, 31))
    {
    STDTIME_RET_EC (invalid_day);
    }

  if (! STDTIME_IN_RANGE (pFields->hour, 0, 23))
    {
    STDTIME_RET_EC (invalid_hour);
    }

  if (! STDTIME_IN_RANGE (pFields->min,  0, 59))
    {
    STDTIME_RET_EC (invalid_min);
    }

  if (! STDTIME_IN_RANGE (pFields->sec,  0, 59))
    {
    STDTIME_RET_EC (invalid_sec);
    }

  if (! STDTIME_IN_RANGE (pFields->msec, 0, 999))
    {
    STDTIME_RET_EC (invalid_msec);
    }

  if (! STDTIME_IN_RANGE (pFields->usec, 0, 999))
    {
    STDTIME_RET_EC (invalid_usec);
    }

  if (! STDTIME_IN_RANGE (pFields->nsec, 0, 999))
    {
    STDTIME_RET_EC (invalid_nsec);
    }

  /* already checked that day is 0-31, now validate per month */

  if (pFields->day >
        StdTimeDaysInYearMon (pFields->year, pFields->mon))
    {
    STDTIME_RET_EC (invalid_mon);
    }

#if 0
  /* already checked that nsec is 0-999, now ensure precision not exceeded */
  /* ISSUE: this could be a problem. suppose nsec contains 123. */

  /* FOR NOW, LOSS OF LOW-ORDER NANOSECOND PRECISION IS NOT AN ERROR */

  if ( ((pFields->nsec) % STDTIME_SCALE_NSEC) != 0)
    {
    STDTIME_RET_EC (invalid_nsec);
    }
#endif

  STDTIME_RET_OK;

  } /* ValidStdTimeFields */

/*-***************************************************************************/
/*            ValidStdTimeStringA                                            */
/*  return STDTIME_OK if StdTimeStringA is valid, else STDTIME_FALSE         */
/*****************************************************************************/

STDTIME_RC                  ValidStdTimeStringA (
  const STDTIME_STRINGA *   /*I*/ pStdTimeString)
  {
  /* validate string by converting to temporary time fields */
  /* and return validation status from the conversion */

  STDTIME_FIELDS            f;

  STDTIME_ENUM_FUNC (ValidStdTimeStringA)

  STDTIME_RET (StdTimeStringAToStdTimeFields (pStdTimeString, &f));

  } /* ValidStdTimeStringA */

/*-***************************************************************************/
/*            ValidStdTimeStringW                                            */
/*  return STDTIME_OK if StdTimeStringW is valid, else STDTIME_FALSE         */
/*****************************************************************************/

STDTIME_RC                  ValidStdTimeStringW (
  const STDTIME_STRINGW *   /*I*/ pStdTimeString)
  {
  /* validate string by converting to temporary time fields */
  /* and return validation status from the conversion */

  STDTIME_FIELDS            f;

  STDTIME_ENUM_FUNC (ValidStdTimeStringW)

  STDTIME_RET (StdTimeStringWToStdTimeFields (pStdTimeString, &f));

  } /* ValidStdTimeStringW */

/*-***************************************************************************/
/*            ValidStdTimeHexStrA                                            */
/*  return STDTIME_OK if StdTimeHexStrA is valid, else STDTIME_FALSE         */
/*****************************************************************************/

STDTIME_RC                  ValidStdTimeHexStrA (
  const STDTIME_HEXSTRA *   /*I*/ pStdTimeHexStr)
  {
  STDTIME                   t;

  STDTIME_ENUM_FUNC (ValidStdTimeHexStrA)

  STDTIME_RET (StdTimeHexStrAToStdTime (pStdTimeHexStr, &t));

  } /* ValidStdTimeHexStrA */

/*-***************************************************************************/
/*            ValidStdTimeHexStrW                                            */
/*  return STDTIME_OK if StdTimeHexStrW is valid, else STDTIME_FALSE         */
/*****************************************************************************/

STDTIME_RC                  ValidStdTimeHexStrW (
  const STDTIME_HEXSTRW *   /*I*/ pStdTimeHexStr)
  {
  STDTIME                   t;

  STDTIME_ENUM_FUNC (ValidStdTimeHexStrW)

  STDTIME_RET (StdTimeHexStrWToStdTime (pStdTimeHexStr, &t));

  } /* ValidStdTimeHexStrW */


/*** Format functions ********************************************************/

/*-***************************************************************************/
/*            Rc_StdTime_Formatter - PRIVATE FUNCTION                        */
/*  helper function for formatting support                                   */
/*****************************************************************************/

static STDTIME_RC           Rc_StdTime_Formatter (
  char *                    /*O*/ pTarget,
  size_t                    /*I*/ nMaxsize,
  const char *              /*I*/ pFormat,
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  const STDTIME_STRINGA *   /*I*/ pStdTimeString)
  {
  struct tm                 structTmValue;
  char                      fmt [PVT_STDTIME_FORMAT_BUFSIZE+32];
  char                      buf [PVT_STDTIME_FORMAT_BUFSIZE+1];
  char *                    scan;
  char                      fmt_len;
  char                      fmt_type;
  char                      dlm = 0;

  STDTIME_TZOA              tzo;

  int32_t                   msec = 0;   /* dummy value to avoid rounding */
  int32_t                   usec = 0;   /* dummy value to avoid rounding */
  int32_t                   nsec = 0;   /* dummy value to avoid rounding */

  int32_t                   len = 0;
  int32_t                   default_len;

  STDTIME_ENUM_FUNC (Rc_StdTime_Formatter)

  if ( (pTarget        == NULL)
  ||   (pStdTimeFields == NULL)
  ||   (pFormat        == NULL)
  ||   (pStdTimeString == NULL) )
    {
    STDTIME_RET_EC (null_argument);
    }

  if ((nMaxsize < 1) || (nMaxsize > PVT_STDTIME_FORMAT_BUFSIZE))
    {
    pTarget [0] = 0;
    STDTIME_RET_EC (argument_out_of_range);
    }

  StdTimeStringAToTzoA (pStdTimeString, &tzo);

  strncpy (fmt, pFormat, PVT_STDTIME_FORMAT_BUFSIZE);
  fmt [PVT_STDTIME_FORMAT_BUFSIZE] = 0;

  /* scan for extended formatting codes \1m \2u \3n .. \4s etc. */
  /* replace these codes with actual values prior to calling strftime */
  /* the 1 thru 7 are the number of digits to be stored. */

  /* if \v is found, we take the default number of digits, which is */
  /* 3 for m and u, 1 for n, and 7 for s */

  /* if \t is found, we take the default number of digits, as a maximum */
  /* length, which may be shortened to only significant digits */

  /* if \r is found, we take the default number of digits, as a maximum */
  /* length, which may be shortened to zero digits */

  /* codes 's' and 'm' will generate the current fraction delimiter */
  /* for \rs and \rm, if there are no significant digits, the delimiter */
  /* is omitted from the string. */

  /* codes 'S' and 'M' are like 's' and 'm', except that the fraction */
  /* delimiter is never stored */

  /* \fd inserts a STDTIME_STRING-formatted date string */
  /* \ft inserts a STDTIME_STRING-formatted time string */
  /* \fs inserts the date/time field separator (default 'T') */
  /* \fp inserts the time/fraction field separator (default '.') */

  scan = fmt;
  while (*scan)
    {
    /* if a user (for some reason) wants to embed one of our codes */
    /* in their formatting string, they can escape it with % */
    /* no matter what follows %, it is not one of our codes */

    /* however, the Ansi standard for strftime() does not specify */
    /* what is done with a non-standard format code. */

    /* in such cases, we delete the % and pass the code to strftime() */
    /* without the % to be sure it does not handle it improperly */

    if (*scan == '%')
      {
      if ((scan[1]) && (scan[1] <= ' '))
        {
        /* % is followed by whitespace or unprintable char */
        /* delete the % from the format string */
        /* two-step copy is done in order to avoid overlap in portable way */

        strcpy (buf, scan+1);
        strcpy (scan, buf);
        continue;
        }

      scan++;   /* skip the % */

      if (*scan)
        {
        scan++;     /* skip over escaped char, unless it's nul */
        }

      continue;
      }


    /* handle \tz code: insert timezone offset string, if present */
    /* the code may be a zero-length string, a Z, or an offset like */
    /* -05:00 or +01:00:00 */

    /* note that this is an alternate use of the usual \t1 to \t7 */
    /* format code, which is handled below. */

    if ((scan[0] == '\t') && (scan[1] == 'z'))
      {
      strcpy (buf, scan+2);                              /* save tail of fmt */
      strcpy (scan, tzo.str);                             /* copy TZO string */
      scan += strlen (tzo.str);                      /* skip over TZO string */
      strcpy (scan, buf);                                     /* rebuilt fmt */
      continue;
      }


    /* handle \fs code: insert date/time separator char */

    if ((scan[0] == '\f') && (scan[1] == 's'))
      {
      *scan = PVT_STDTIME_USR_DLM_SEP;               /* wipe out the \f code */
      strcpy (buf, scan+2);                              /* copy tail of fmt */
      scan++;                                     /* skip over the delimiter */
      strcpy (scan, buf);                                     /* rebuilt fmt */
      continue;
      }


    /* handle \fp code: insert time/fraction separator char */

    if ((scan[0] == '\f') && (scan[1] == 'p'))
      {
      *scan = PVT_STDTIME_USR_DLM_FRAC;              /* wipe out the \f code */
      strcpy (buf, scan+2);                              /* copy tail of fmt */
      scan++;                                     /* skip over the delimiter */
      strcpy (scan, buf);                                     /* rebuilt fmt */
      continue;
      }


    /* handle \fd code: stored formatted date in pStdTimeString */

    if ((scan[0] == '\f') && (scan[1] == 'd'))
      {
      strncpy (buf, pStdTimeString->str + STDTIME_STRING_DATE_POS,
               STDTIME_STRING_DATE_LEN);

      strcpy (buf + STDTIME_STRING_DATE_LEN, scan+2);    /* copy tail of fmt */
      strcpy (scan, buf);                                     /* rebuilt fmt */
      scan += STDTIME_STRING_DATE_LEN;          /* skip over the date string */

      /* verify that the new string is not too long */
      /* we allowed some extra room so overflowing once is OK */

      if (strlen (fmt) > PVT_STDTIME_FORMAT_BUFSIZE)
        {
        STDTIME_RET_EC (buffer_size_exceeded);
        }

      continue;

      } /* if \fd */


    /* handle \ft code: stored formatted time in pStdTimeString */

    if ((scan[0] == '\f') && (scan[1] == 't'))
      {
      strncpy (buf, pStdTimeString->str + STDTIME_STRING_TIME_POS,
               STDTIME_STRING_TIME_LEN);

      strcpy (buf + STDTIME_STRING_TIME_LEN, scan+2);    /* copy tail of fmt */
      strcpy (scan, buf);                                     /* rebuilt fmt */
      scan += STDTIME_STRING_TIME_LEN;          /* skip over the time string */

      /* verify that the new string is not too long */
      /* we allowed some extra room so overflowing once is OK */

      if (strlen (fmt) > PVT_STDTIME_FORMAT_BUFSIZE)
        {
        STDTIME_RET_EC (buffer_size_exceeded);
        }

      continue;

      } /* if \fd */


    /* look for \1 thru \7, \t, \r or \v length code */

    fmt_len = scan[0];

    if ((fmt_len >= '\1') && (fmt_len <= '\7'))
      {
      len = (int32_t) fmt_len;
      }

    else if ((fmt_len != '\t') && (fmt_len != '\r') && (fmt_len != '\v'))
      {
      scan++;       /* first char is not \1 thru \7, \t, \r or \v */
      continue;
      }

    /* look for 'm', 'u', 'n' or 's' type codes */

    fmt_type = scan[1];
    dlm = 0;

    if ((fmt_type == 'm') || (fmt_type == 'M'))
      {
      default_len = 3;

      if (fmt_type == 'm')
        {
        dlm = PVT_STDTIME_USR_DLM_FRAC;
        }

      sprintf (buf, "%03d000000",
        abs (pStdTimeFields->msec) % 1000);
      }

    else if ((fmt_type == 'u') || (fmt_type == 'U'))
      {
      default_len = 3;

      sprintf (buf, "%03d000000",
        abs (pStdTimeFields->usec) % 1000);
      }

    else if ((fmt_type == 'n') || (fmt_type == 'N'))
      {
      default_len = 1;

      sprintf (buf, "%03d000000",
        abs (pStdTimeFields->nsec) % 1000);
      }

    else if ((fmt_type == 's') || (fmt_type == 'S'))
      {
      default_len = 7;

      if (fmt_type == 's')
        {
        dlm = PVT_STDTIME_USR_DLM_FRAC;
        }

      sprintf (buf, "%03d%03d%03d",
        abs (pStdTimeFields->msec) % 1000,
        abs (pStdTimeFields->usec) % 1000,
        abs (pStdTimeFields->nsec) % 1000);
      }

    else
      {
      scan += 2;        /* not a valid two-char formatting code */
      continue;
      }

    if (fmt_len == '\v')
      {
      len = default_len;
      }

    else if (fmt_len == '\t')
      {
      len = default_len;

      /* trim off non-significant digits, but no shorter than 1 digit */

      while ((len > 1) && (buf[len-1] == '0'))
        {
        len--;
        }
      }

    else if (fmt_len == '\r')
      {
      len = default_len;

      /* trim off non-significant digits, possibly all of them */

      while ((len > 0) && (buf[len-1] == '0'))
        {
        len--;
        }

      if (len == 0)                 /* no significant digits */
        {
        dlm = 0;                    /* omit delimiter */
        }
      }

    strcpy (buf+len, scan+2);       /* copy in tail of fmt string */

    if (dlm)                        /* need to insert fraction delimiter */
    {
        *scan++ = dlm;
    }

    strcpy (scan, buf);             /* rebuilt fmt */
    scan += len;                    /* skip over the resultant digits */

    /* verify that the new string is not too long */
    /* we allowed some extra room so overflowing once is OK */

    if (strlen (fmt) > PVT_STDTIME_FORMAT_BUFSIZE)
      {
      STDTIME_RET_EC (buffer_size_exceeded);
      }

    continue;

    } /* while */


  if STDTIME_IF (StdTimeFieldsToStructTmEx
       (pStdTimeFields, &structTmValue, &msec, &usec, &nsec))
    {
    if (strftime (buf, PVT_STDTIME_FORMAT_BUFSIZE, fmt, &structTmValue))
      {
      /* string did not overrun temp buffer, so copy back to user */
      strncpy (pTarget, buf, nMaxsize);
      pTarget [nMaxsize-1] = 0;
      STDTIME_RET_OK;
      }

    else
      {
      /* string overran temp buffer, so strftime did not initialize it */
      STDTIME_RET_EC (failure_in_api_strftime);
      }
    }

  STDTIME_RET_RC;  /* from StdTimeFieldsToStructTmEx call */

  } /* Rc_StdTime_Formatter */

/*-***************************************************************************/
/*            FormatStdTimeA - Ansi output                                   */
/*  format StdTime structure using extended strftime() functionality         */
/*****************************************************************************/

STDTIME_RC                  FormatStdTimeA (
  char *                    /*O*/ pTarget,
  size_t                    /*I*/ nMaxsize,
  const char *              /*I*/ pFormat,
  const STDTIME *           /*I*/ pStdTime)
  {
  STDTIME_FIELDS            f;

  STDTIME_ENUM_FUNC (FormatStdTimeA)

  if STDTIME_IF (StdTimeToStdTimeFields (pStdTime, &f))
    {
    STDTIME_RET (FormatStdTimeFieldsA (pTarget, nMaxsize, pFormat, &f));
    }

  STDTIME_RET_RC;

  } /* FormatStdTimeA */

/*-***************************************************************************/
/*            FormatStdTimeW - Unicode output                                */
/*  format StdTime structure using extended strftime() functionality         */
/*****************************************************************************/

STDTIME_RC                  FormatStdTimeW (
  STDTIME_WCHAR *           /*O*/ pTarget,
  size_t                    /*I*/ nMaxsize,
  const STDTIME_WCHAR *     /*I*/ pFormat,
  const STDTIME *           /*I*/ pStdTime)
  {
  STDTIME_FIELDS            f;

  STDTIME_ENUM_FUNC (FormatStdTimeW)

  if STDTIME_IF (StdTimeToStdTimeFields (pStdTime, &f))
    {
    STDTIME_RET (FormatStdTimeFieldsW (pTarget, nMaxsize, pFormat, &f));
    }

  STDTIME_RET_RC;

  } /* FormatStdTimeW */

/*-***************************************************************************/
/*            FormatStdTimeFieldsA - Ansi output                             */
/*  format StdTimeFields structure using extended strftime() functionality   */
/*****************************************************************************/

STDTIME_RC                  FormatStdTimeFieldsA (
  char *                    /*O*/ pTarget,
  size_t                    /*I*/ nMaxsize,
  const char *              /*I*/ pFormat,
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields)
  {
  char                      aFmt [PVT_STDTIME_FORMAT_BUFSIZE+1];
  STDTIME_STRINGA           stdTimeString;

  STDTIME_ENUM_FUNC (FormatStdTimeFieldsA)

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if (pFormat == NULL)
    {
    strncpy (aFmt, PVT_STDTIME_FORMAT_DEFAULT, PVT_STDTIME_FORMAT_BUFSIZE);
    }

  else
    {
    strncpy (aFmt, pFormat, PVT_STDTIME_FORMAT_BUFSIZE);
    }

  if STDTIME_IFNOT (StdTimeFieldsToStdTimeStringA (
       pStdTimeFields, &stdTimeString))
    {
    STDTIME_RET_RC;
    }

  aFmt [PVT_STDTIME_FORMAT_BUFSIZE] = 0;

  STDTIME_RET (Rc_StdTime_Formatter (
            pTarget,
            nMaxsize,
            aFmt,
            pStdTimeFields,
            &stdTimeString));

  } /* FormatStdTimeFieldsW */

/*-***************************************************************************/
/*            FormatStdTimeFieldsW - Unicode output                          */
/*  format StdTimeFields structure using extended strftime() functionality   */
/*****************************************************************************/

STDTIME_RC                  FormatStdTimeFieldsW (
  STDTIME_WCHAR *           /*O*/ pTarget,
  size_t                    /*I*/ nMaxsize,
  const STDTIME_WCHAR *     /*I*/ pFormat,
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields)
  {
  char                      aBuf [PVT_STDTIME_FORMAT_BUFSIZE+1];
  char                      aFmt [PVT_STDTIME_FORMAT_BUFSIZE+1];
  STDTIME_STRINGA           stdTimeString;

  STDTIME_ENUM_FUNC (FormatStdTimeFieldsW)

  /* copy Unicode format string to temp Ansi string first */
  /* format time as Ansi, then copy back as Unicode */

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if (pFormat == NULL)
    {
    strcpy (aFmt, PVT_STDTIME_FORMAT_DEFAULT);
    }

  else
    {
    Char_StdTime_StrncpyAW (aFmt, pFormat, PVT_STDTIME_FORMAT_BUFSIZE);
    }

  aFmt [PVT_STDTIME_FORMAT_BUFSIZE] = 0;

  if STDTIME_IFNOT (StdTimeFieldsToStdTimeStringA (
       pStdTimeFields, &stdTimeString))
    {
    STDTIME_RET_RC;
    }

  if STDTIME_IF (Rc_StdTime_Formatter (
        aBuf,
        nMaxsize,
        aFmt,
        pStdTimeFields,
        &stdTimeString))

    {
    Wchar_StdTime_StrncpyWA_Sub (pTarget, aBuf, nMaxsize, pFormat);
    STDTIME_RET_OK;
    }

  STDTIME_RET_RC;

  } /* FormatStdTimeFieldsW */

/*-***************************************************************************/
/*            FormatStdTimeStringA - Ansi output                             */
/*  format StdTimeStringA structure using extended strftime() functionality  */
/*****************************************************************************/

STDTIME_RC                  FormatStdTimeStringA (
  char *                    /*O*/ pTarget,
  size_t                    /*I*/ nMaxsize,
  const char *              /*I*/ pFormat,
  const STDTIME_STRINGA *   /*I*/ pStdTimeString)
  {
  char                      aFmt [PVT_STDTIME_FORMAT_BUFSIZE+1];
  STDTIME_FIELDS            stdTimeFields;
  STDTIME_STRINGA           stdTimeString;

  STDTIME_ENUM_FUNC (FormatStdTimeStringA)

  if (pStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if (pFormat == NULL)
    {
    strncpy (aFmt, PVT_STDTIME_FORMAT_DEFAULT, PVT_STDTIME_FORMAT_BUFSIZE);
    }

  else
    {
    strncpy (aFmt, pFormat, PVT_STDTIME_FORMAT_BUFSIZE);
    }

  /* when formating StdTimeString, we must retain the existing embTzo */
  /* and not allow it to influence the str to fld conversion */
  /* otherwise the string value and the fields values will not agree */
  /* we copy the string to a local variable and chop off the embTzo */

  stdTimeString = *pStdTimeString;
  stdTimeString.embTzo[0] = 0;

  if STDTIME_IFNOT (StdTimeStringAToStdTimeFields (
       &stdTimeString, &stdTimeFields))
    {
    STDTIME_RET_RC;
    }

  aFmt [PVT_STDTIME_FORMAT_BUFSIZE] = 0;

  STDTIME_RET (Rc_StdTime_Formatter (
            pTarget,
            nMaxsize,
            aFmt,
            &stdTimeFields,
            pStdTimeString));

  } /* FormatStdTimeStringA */

/*-***************************************************************************/
/*            FormatStdTimeStringW - Unicode output                          */
/*  format StdTimeStringW structure into ISO 8601 formatted WCHAR string     */
/*****************************************************************************/

STDTIME_RC                  FormatStdTimeStringW (
  STDTIME_WCHAR *           /*O*/ pTarget,
  size_t                    /*I*/ nMaxsize,
  const STDTIME_WCHAR *     /*I*/ pFormat,
  const STDTIME_STRINGW *   /*I*/ pStdTimeString)
  {
  char                      aFmt [PVT_STDTIME_FORMAT_BUFSIZE+1];
  char                      aBuf [PVT_STDTIME_FORMAT_BUFSIZE+1];
  STDTIME_FIELDS            stdTimeFields;
  STDTIME_STRINGA           stdTimeStringA = {{0}};

  STDTIME_ENUM_FUNC (FormatStdTimeStringW)

  if (pStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if (pFormat == NULL)
    {
    strncpy (aFmt, PVT_STDTIME_FORMAT_DEFAULT, PVT_STDTIME_FORMAT_BUFSIZE);
    }

  else
    {
    Char_StdTime_StrncpyAW (aFmt, pFormat, PVT_STDTIME_FORMAT_BUFSIZE);
    }

  aFmt [PVT_STDTIME_FORMAT_BUFSIZE] = 0;

  /* the formatter takes an Ansi STDTIME_STRING, so we must copy the */
  /* unicode string fields to Ansi mode first */

  /* when formating StdTimeString, we must retain the existing embTzo */
  /* and not allow it to influence the str to fld conversion */
  /* otherwise the string value and the fields values will not agree */
  /* we copy the string to a local variable and chop off the embTzo */

  Char_StdTime_StrncpyAW (
    stdTimeStringA.str, pStdTimeString->str, STDTIME_STRING_LEN);

  stdTimeStringA.embTzo[0] = 0;

  /* convert Ansi version from string to fields before copying embTzo */

  if STDTIME_IFNOT (StdTimeStringWToStdTimeFields (
       pStdTimeString, &stdTimeFields))
    {
    STDTIME_RET_RC;
    }

  Char_StdTime_StrncpyAW (
    stdTimeStringA.embTzo, pStdTimeString->embTzo, STDTIME_TZO_LEN);

  stdTimeStringA.embTzo [STDTIME_TZO_LEN] = 0;

  if STDTIME_IF (Rc_StdTime_Formatter (
            aBuf,
            nMaxsize,
            aFmt,
            &stdTimeFields,
            &stdTimeStringA))
    {
    Wchar_StdTime_StrncpyWA_Sub (pTarget, aBuf, nMaxsize, pFormat);
    STDTIME_RET_OK;
    }

  STDTIME_RET_RC;

  } /* FormatStdTimeStringW */

/*-***************************************************************************/
/*            FormatStdTimeHexStrA - Ansi output                             */
/*  format StdTimeHexStrA structure using extended strftime() functionality  */
/*****************************************************************************/

STDTIME_RC                  FormatStdTimeHexStrA (
  char *                    /*O*/ pTarget,
  size_t                    /*I*/ nMaxsize,
  const char *              /*I*/ pFormat,
  const STDTIME_HEXSTRA *   /*I*/ pStdTimeHexStr)
  {
  STDTIME_FIELDS            f;

  STDTIME_ENUM_FUNC (FormatStdTimeHexStrA)

  if STDTIME_IF (StdTimeHexStrAToStdTimeFields (pStdTimeHexStr, &f))
    {
    STDTIME_RET (FormatStdTimeFieldsA (pTarget, nMaxsize, pFormat, &f));
    }

  STDTIME_RET_RC;

  } /* FormatStdTimeHexStrA */

/*-***************************************************************************/
/*            FormatStdTimeHexStrW - Unicode output                          */
/*  format StdTimeHexStrW structure using extended strftime() functionality  */
/*****************************************************************************/

STDTIME_RC                  FormatStdTimeHexStrW (
  STDTIME_WCHAR *           /*O*/ pTarget,
  size_t                    /*I*/ nMaxsize,
  const STDTIME_WCHAR *     /*I*/ pFormat,
  const STDTIME_HEXSTRW *   /*I*/ pStdTimeHexStr)
  {
  STDTIME_FIELDS            f;

  STDTIME_ENUM_FUNC (FormatStdTimeHexStrW)

  if STDTIME_IF (StdTimeHexStrWToStdTimeFields (pStdTimeHexStr, &f))
    {
    STDTIME_RET (FormatStdTimeFieldsW (pTarget, nMaxsize, pFormat, &f));
    }

  STDTIME_RET_RC;

  } /* FormatStdTimeHexStrW */


/*-***************************************************************************/
/*            TrimStdTimeStringA                                             */
/*  adjust number of trailing digits of fractional seconds by truncating     */
/*  trailing zero digits, up to nSize number of digits.                      */
/*  when nSize is -1 and all digits are 0, the delimiter is also removed.    */
/*  the fractional field is first restored, so Trim also adds back digits.   */
/*                                                                           */
/*  if an embTzo field is present, it is exported to extTzo, overwriting it. */
/*****************************************************************************/

STDTIME_RC                  TrimStdTimeStringA (
  STDTIME_STRINGA *         /*IO*/ pStdTimeString,
  int32_t                   /*I*/ nSize)
  {
  int32_t                   i;
  int32_t                   pos;
  int32_t                   lastNonZero;
  int32_t                   truncPos;

  STDTIME_ENUM_FUNC (TrimStdTimeStringA)

  if (pStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  pStdTimeString->embTzo[STDTIME_TZO_LEN] = 0;
  pStdTimeString->extTzo.str[STDTIME_TZO_LEN] = 0;

  PVT_STDTIME_EXPORT_TZOA (pStdTimeString);

  if (nSize < -1)
    {
    nSize = -1;
    }

  else if (nSize > STDTIME_STRING_FRAC_LEN)
    {
    nSize = STDTIME_STRING_FRAC_LEN;
    }

  /* first, restore fractional part of StdTimeString */
  pStdTimeString->str [STDTIME_STRING_DLM_F1] = PVT_STDTIME_USR_DLM_FRAC;

  lastNonZero = 0;  /* relative pos where last non '0' fractional digit is */

  for (pos = 1; pos <= STDTIME_STRING_FRAC_LEN; pos++)
    {
    i = STDTIME_STRING_DLM_F1 + pos;

    if ((pStdTimeString->str [i] < '0')
    ||  (pStdTimeString->str [i] > '9'))
      {
      pStdTimeString->str [i] = '0';
      }

    if (pStdTimeString->str [i] != '0')
      {
      lastNonZero = pos;
      }
    }

  if ((lastNonZero == 0) && (nSize == -1))
    {
    /* there are no significant digits and nSize == -1 */
    /* this means the fractional delimiter is chopped off */
    truncPos = 0;
    }

  else if (lastNonZero >= nSize)
    {
    /* there are as many, or more, significant digits than the minimum */
    /* all the significant digits are retained */
    truncPos = lastNonZero + 1;
    }

  else
    {
    /* the minimum number of digits requested is longer than the number */
    /* of significant digits, so keep the number requested */
    truncPos = nSize + 1;
    }

  /* replace truncated character to end of string with nuls */

  for (i = STDTIME_STRING_DLM_F1 + truncPos; i <= STDTIME_STRING_LEN; i++)
    {
    pStdTimeString->str [i] = 0;
    }

  STDTIME_RET_OK;

  } /* TrimStdTimeStringA */


/*-***************************************************************************/
/*            TrimStdTimeStringW                                             */
/*  adjust number of trailing digits of fractional seconds                   */
/*****************************************************************************/


STDTIME_RC                  TrimStdTimeStringW (
  STDTIME_STRINGW *         /*I*/ pStdTimeString,
  int32_t                   /*I*/ nSize)
  {
  STDTIME_STRINGA           as;

  STDTIME_ENUM_FUNC (TrimStdTimeStringW)

  if (pStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  pStdTimeString->embTzo[STDTIME_TZO_LEN] = 0;
  pStdTimeString->extTzo.str[STDTIME_TZO_LEN] = 0;

  PVT_STDTIME_EXPORT_TZOW (pStdTimeString);

  Char_StdTime_StrncpyAW (as.str, pStdTimeString->str, STDTIME_STRING_LEN+1);

  if STDTIME_IF (TrimStdTimeStringA (&as, nSize))
    {
    Wchar_StdTime_StrncpyWA (pStdTimeString->str, as.str, STDTIME_STRING_LEN+1);
    STDTIME_RET_OK;
    }

  STDTIME_RET_RC;

  } /* TrimStdTimeStringW */


/*-***************************************************************************/
/*            TruncStdTimeStringA                                            */
/*  adjust number of trailing digits of fractional seconds by truncating     */
/*  trailing digits (whether significant or not) up to nSize num of digits.  */
/*  when nSize is -1 and all digits are 0, the delimiter is also removed.    */
/*  the fractional field is first restored, so Trunc also adds back digits.  */
/*                                                                           */
/*  if an embTzo field is present, it is exported to extTzo, overwriting it. */
/*****************************************************************************/

STDTIME_RC                  TruncStdTimeStringA (
  STDTIME_STRINGA *         /*IO*/ pStdTimeString,
  int32_t                   /*I*/ nSize)
  {
  int32_t                   i;
  int32_t                   pos;
  int32_t                   truncPos;

  STDTIME_ENUM_FUNC (TruncStdTimeStringA)

  if (pStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  pStdTimeString->embTzo[STDTIME_TZO_LEN] = 0;
  pStdTimeString->extTzo.str[STDTIME_TZO_LEN] = 0;

  PVT_STDTIME_EXPORT_TZOA (pStdTimeString);

  if (nSize < -1)
    {
    nSize = -1;
    }

  else if (nSize > STDTIME_STRING_FRAC_LEN)
    {
    nSize = STDTIME_STRING_FRAC_LEN;
    }

  /* first, restore fractional part of StdTimeString */
  pStdTimeString->str [STDTIME_STRING_DLM_F1] = PVT_STDTIME_USR_DLM_FRAC;

  for (pos = 1; pos <= STDTIME_STRING_FRAC_LEN; pos++)
    {
    i = STDTIME_STRING_DLM_F1 + pos;

    if ((pStdTimeString->str [i] < '0')
    ||  (pStdTimeString->str [i] > '9'))
      {
      pStdTimeString->str [i] = '0';
      }
    }

  truncPos = nSize + 1;

  /* replace truncated character to end of string with nuls */

  for (i = STDTIME_STRING_DLM_F1 + truncPos; i <= STDTIME_STRING_LEN; i++)
    {
    pStdTimeString->str [i] = 0;
    }

  STDTIME_RET_OK;

  } /* TruncStdTimeStringA */


/*-***************************************************************************/
/*            TruncStdTimeStringW                                            */
/*  adjust number of trailing digits of fractional seconds                   */
/*****************************************************************************/


STDTIME_RC                  TruncStdTimeStringW (
  STDTIME_STRINGW *         /*I*/ pStdTimeString,
  int32_t                   /*I*/ nSize)
  {
  STDTIME_STRINGA           as;

  STDTIME_ENUM_FUNC (TruncStdTimeStringW)

  if (pStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  pStdTimeString->embTzo[STDTIME_TZO_LEN] = 0;
  pStdTimeString->extTzo.str[STDTIME_TZO_LEN] = 0;

  PVT_STDTIME_EXPORT_TZOW (pStdTimeString);

  Char_StdTime_StrncpyAW (as.str, pStdTimeString->str, STDTIME_STRING_LEN+1);

  if STDTIME_IF (TruncStdTimeStringA (&as, nSize))
    {
    Wchar_StdTime_StrncpyWA (pStdTimeString->str, as.str, STDTIME_STRING_LEN+1);
    STDTIME_RET_OK;
    }

  STDTIME_RET_RC;

  } /* TruncStdTimeStringW */


/*++ delimiter functions ++***************************************************/
/*                                                                           */
/* bcd time string delimiters are a 4-character string of the form "abcd"    */
/* where 'a' is the separator between (year,month) and (month,day)           */
/*   'b' is the separator between (day,hour)                                 */
/*   'c' is the separator between (hour,minute) and (minute,second)          */
/*   'd' is the separator between (second,fractional)                        */
/*                                                                           */
/* the default value is "-T:.", which is the standard ISO 8601 values        */
/* for the international representation of date and time.                    */
/*                                                                           */
/* this results in a StdTimeString value of yyyy-mm-ddThh:mm:ss.fffffff      */
/*                                                                           */
/* the default value is set when a delimiter argument of NULL is passed.     */
/* passed strings must be exactly 4 characters with a valid nul terminator   */
/* otherwise, the delimiters are not used, and the function fails.           */
/* individual delimiter characters may not be nul, but may contain blanks    */
/*                                                                           */
/*++**************************************************************************/


/*-***************************************************************************/
/*            Bool_StdTime_DefaultDelimiters - PRIVATE FUNCTION              */
/*  initializes string delimiters to their ISO 8601 default values           */
/*****************************************************************************/

STDTIME_BOOL                Bool_StdTime_DefaultDelimiters ()
  {
  strcpy (Pvt_StdTime_UserDelimString, STDTIME_ISO_DLM_STR);
  return STDTIME_TRUE;

  } /* Bool_StdTime_DefaultDelimiters */

/*-***************************************************************************/
/*            Bool_StdTime_SetDelimiters - PRIVATE FUNCTION                  */
/*  initializes string delimiters to user-supplied values                    */
/*****************************************************************************/

static STDTIME_BOOL         Bool_StdTime_SetDelimiters (
  const char *              /*I*/ pDelimiters)
  {
  int32_t                         i;
  char                      buf [5];

  if (pDelimiters == NULL)
    {
    return STDTIME_FALSE;
    }

  if (pDelimiters[4] != 0)
    {
    return STDTIME_FALSE;
    }

  strcpy (buf, pDelimiters);

  /* verify correct delimiter string format */
  for (i=0; i < 4; i++)
    {
    if (buf[i] == '0')
      {
      /* '0' means change to default; copy default char for this position */
      buf[i] = STDTIME_ISO_DLM_STR[i];
      continue;
      }

    if (buf[i] == '1')
      {
      /* '1' means do not change, copy in old value to avoid changing it */
      buf[i] = Pvt_StdTime_UserDelimString[i];
      continue;
      }

    /* delimiters 2 to 9 are illegal */
    if ((buf[i] >= '2') && (buf[i] <= '9'))
      {
      return STDTIME_FALSE;
      }

    if ((buf[i] < ' ') || (buf[i] > 0x7E))
      {
      return STDTIME_FALSE;
      }
    }

  strcpy (Pvt_StdTime_UserDelimString, buf);

  return STDTIME_TRUE;

  } /* Bool_StdTime_SetDelimiters */

/*-***************************************************************************/
/*            SetStdTimeStringDelimitersA                                    */
/*  initializes string delimiters to user-supplied CHAR string               */
/*****************************************************************************/

STDTIME_RC                  SetStdTimeStringDelimitersA (
  const char *              /*I*/ pDelimiters)
  {
  STDTIME_BOOL              success;

  STDTIME_ENUM_FUNC (SetStdTimeStringDelimitersA)

  if (pDelimiters == NULL)
    {
    success = Bool_StdTime_DefaultDelimiters ();
    }

  else
    {
    success = Bool_StdTime_SetDelimiters (pDelimiters);
    }

  if (success)
    {
    STDTIME_RET_OK;
    }

  STDTIME_RET_EC (failure_in_api_SetStdTimeStringDelimitersA);

  } /* SetStdTimeStringDelimitersA */

/*-***************************************************************************/
/*            SetStdTimeStringDelimitersW                                    */
/*  initializes string delimiters to user-supplied WCHAR string              */
/*****************************************************************************/

STDTIME_RC                  SetStdTimeStringDelimitersW (
  const STDTIME_WCHAR *     /*I*/ pDelimiters)
  {
  char                      buf [5];
  STDTIME_BOOL              success;

  STDTIME_ENUM_FUNC (SetStdTimeStringDelimitersW)

  if (pDelimiters == NULL)
    {
    success = Bool_StdTime_DefaultDelimiters ();
    }

  else
    {
    buf[0] = (char) pDelimiters[0];
    buf[1] = (char) pDelimiters[1];
    buf[2] = (char) pDelimiters[2];
    buf[3] = (char) pDelimiters[3];
    buf[4] = (char) pDelimiters[4];

    success = Bool_StdTime_SetDelimiters (buf);
    }

  if (success)
    {
    STDTIME_RET_OK;
    }

  STDTIME_RET_EC (failure_in_api_SetStdTimeStringDelimitersW);

  } /* SetStdTimeStringDelimitersW */


/*-***************************************************************************/
/*            RepairStdTimeStringA                                           */
/*  set delimiters in StdTimeStringA to currently defined delimiter values   */
/*  any nul CHAR's in StdTimeStringA are set to blank (except terminator)    */
/*****************************************************************************/

STDTIME_RC                  RepairStdTimeStringA (
  STDTIME_STRINGA *         /*O*/ pStdTimeString)
  {
  /* repair delimiters in a StdTime string (Ansi) */

  int32_t                         i;
  char *                    str;

  STDTIME_ENUM_FUNC (RepairStdTimeStringA)

  if (pStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  pStdTimeString->embTzo[STDTIME_TZO_LEN] = 0;
  pStdTimeString->extTzo.str[STDTIME_TZO_LEN] = 0;

  str = &(pStdTimeString->str[0]);

  for (i = 0; i < STDTIME_STRING_LEN; i++)
    {
    /* ensure there are no embedded nuls or blanks */
    if ((str [i] == 0)
    ||  (str [i] == ' '))
      {
      str [i] = '0';
      }
    }

  str [STDTIME_STRING_DLM_D1] = PVT_STDTIME_USR_DLM_DATE;
  str [STDTIME_STRING_DLM_D2] = PVT_STDTIME_USR_DLM_DATE;
  str [STDTIME_STRING_DLM_S1] = PVT_STDTIME_USR_DLM_SEP;
  str [STDTIME_STRING_DLM_T1] = PVT_STDTIME_USR_DLM_TIME;
  str [STDTIME_STRING_DLM_T2] = PVT_STDTIME_USR_DLM_TIME;
  str [STDTIME_STRING_DLM_F1] = PVT_STDTIME_USR_DLM_FRAC;

  /* only repair delimiter at embTzo if an offset is not present */

  if (str[STDTIME_STRING_LEN] == 'z')
    {
    str[STDTIME_STRING_LEN] = 'Z';
    }

  else if ( (str[STDTIME_STRING_LEN] != '+')
       &&   (str[STDTIME_STRING_LEN] != '-')
       &&   (str[STDTIME_STRING_LEN] != 'Z') )
    {
    str[STDTIME_STRING_LEN] = 0;
    }

  if (str[STDTIME_STRING_LEN] == 'Z')
    {
    str[STDTIME_STRING_LEN+1] = 0;
    }

  STDTIME_RET_OK;

  } /* RepairStdTimeStringA */


/*-***************************************************************************/
/*            RepairStdTimeStringW                                           */
/*  set delimiters in StdTimeStringW to currently defined delimiter values   */
/*  any nul WCHAR's in StdTimeStringW are set to blank (except terminator)   */
/*****************************************************************************/

STDTIME_RC                  RepairStdTimeStringW (
  STDTIME_STRINGW *         /*O*/ pStdTimeString)
  {
  /* repair delimiters in a StdTime string (Unicode) */

  int32_t                         i;
  STDTIME_WCHAR *           str;

  STDTIME_ENUM_FUNC (RepairStdTimeStringW)

  if (pStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  pStdTimeString->embTzo[STDTIME_TZO_LEN] = 0;
  pStdTimeString->extTzo.str[STDTIME_TZO_LEN] = 0;

  str = &(pStdTimeString->str[0]);

  for (i = 0; i < STDTIME_STRING_LEN; i++)
    {
    /* ensure there are no embedded nuls or blanks */
    if ((str [i] == (STDTIME_WCHAR) 0)
    ||  (str [i] == (STDTIME_WCHAR) ' '))
      {
      str [i] = (STDTIME_WCHAR) '0';
      }
    }

  str [STDTIME_STRING_DLM_D1] = (STDTIME_WCHAR) PVT_STDTIME_USR_DLM_DATE;
  str [STDTIME_STRING_DLM_D2] = (STDTIME_WCHAR) PVT_STDTIME_USR_DLM_DATE;
  str [STDTIME_STRING_DLM_S1] = (STDTIME_WCHAR) PVT_STDTIME_USR_DLM_SEP;
  str [STDTIME_STRING_DLM_T1] = (STDTIME_WCHAR) PVT_STDTIME_USR_DLM_TIME;
  str [STDTIME_STRING_DLM_T2] = (STDTIME_WCHAR) PVT_STDTIME_USR_DLM_TIME;
  str [STDTIME_STRING_DLM_F1] = (STDTIME_WCHAR) PVT_STDTIME_USR_DLM_FRAC;

  /* only repair delimiter at embTzo if an offset is not present */

  if (str[STDTIME_STRING_LEN] == (STDTIME_WCHAR) 'z')
    {
    str[STDTIME_STRING_LEN] = (STDTIME_WCHAR) 'Z';
    }

  else if ( (str[STDTIME_STRING_LEN] != (STDTIME_WCHAR) '+')
       &&   (str[STDTIME_STRING_LEN] != (STDTIME_WCHAR) '-')
       &&   (str[STDTIME_STRING_LEN] != (STDTIME_WCHAR) 'Z') )
    {
    str [STDTIME_STRING_LEN] = (STDTIME_WCHAR) 0;
    }

  if (str[STDTIME_STRING_LEN] == (STDTIME_WCHAR) 'Z')
    {
    str[STDTIME_STRING_LEN+1] = 0;
    }

  STDTIME_RET_OK;

  } /* RepairStdTimeStringW */


/*-***************************************************************************/
/*            DelimitStdTimeStringA                                          */
/*  set delimiters in StdTimeStringA to user-provided delimiter values.      */
/*  any nul CHAR's in StdTimeStringA are set to blank (except terminator)    */
/*  prior to the fractional-second delimiter position.                       */
/*****************************************************************************/

STDTIME_RC                  DelimitStdTimeStringA (
  STDTIME_STRINGA *         /*O*/ pStdTimeString,
  const char *              /*I*/ pDelim)
  {
  /* insert user-provided delimiters into a StdTime string (Ansi) */

  int32_t                   i;
  char *                    str;
  static char               defaultDelim[4] = {0,0,0,0};

  STDTIME_ENUM_FUNC (DelimitStdTimeStringA)

  if (pStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  pStdTimeString->embTzo[STDTIME_TZO_LEN] = 0;
  pStdTimeString->extTzo.str[STDTIME_TZO_LEN] = 0;

  if (pDelim == NULL)
    {
    pDelim = defaultDelim;
    }

  /* there are no restrictions on the contents of pDelim */
  /* it is possible to insert nul characters by passing */
  /* a string of "\0\0\0\0" */

  str = &(pStdTimeString->str[0]);

  for (i = 0; i < STDTIME_STRING_DLM_F1; i++)
    {
    /* ensure there are no embedded nuls prior to fractional-second delim */
    if (str [i] == (char) 0)
      {
      str [i] = (char) ' ';
      }
    }

  str [STDTIME_STRING_DLM_D1] = pDelim[0];
  str [STDTIME_STRING_DLM_D2] = pDelim[0];
  str [STDTIME_STRING_DLM_S1] = pDelim[1];
  str [STDTIME_STRING_DLM_T1] = pDelim[2];
  str [STDTIME_STRING_DLM_T2] = pDelim[2];
  str [STDTIME_STRING_DLM_F1] = pDelim[3];

  /* only repair delimiter at embTzo if an offset is not present */

  if (str[STDTIME_STRING_LEN] == 'z')
    {
    str[STDTIME_STRING_LEN] = 'Z';
    }

  else if ( (str[STDTIME_STRING_LEN] != '+')
       &&   (str[STDTIME_STRING_LEN] != '-')
       &&   (str[STDTIME_STRING_LEN] != 'Z') )
    {
    str[STDTIME_STRING_LEN] = 0;
    }

  if (str[STDTIME_STRING_LEN] == 'Z')
    {
    str[STDTIME_STRING_LEN+1] = 0;
    }

  STDTIME_RET_OK;

  } /* DelimitStdTimeStringA */


/*-***************************************************************************/
/*            DelimitStdTimeStringW                                          */
/*  set delimiters in StdTimeStringW to user-provided delimiter values.      */
/*  any nul WCHAR's in StdTimeStringW are set to blank (except terminator)   */
/*  prior to the fractional-second delimiter position.                       */
/*****************************************************************************/

STDTIME_RC                  DelimitStdTimeStringW (
  STDTIME_STRINGW *         /*IO*/ pStdTimeString,
  const STDTIME_WCHAR *     /*I*/ pDelim)
  {
  /* insert user-provided delimiters into a StdTime string (Unicode) */

  int32_t                   i;
  STDTIME_WCHAR *           str;
  static STDTIME_WCHAR      defaultDelim[4] = {0,0,0,0};

  STDTIME_ENUM_FUNC (DelimitStdTimeStringW)

  if (pStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  pStdTimeString->embTzo[STDTIME_TZO_LEN] = 0;
  pStdTimeString->extTzo.str[STDTIME_TZO_LEN] = 0;

  if (pDelim == NULL)
    {
    pDelim = defaultDelim;
    }

  /* there are no restrictions on the contents of pDelim */
  /* it is possible to insert nul characters by passing */
  /* a string of L"\0\0\0\0" */

  str = &(pStdTimeString->str[0]);

  for (i = 0; i < STDTIME_STRING_DLM_F1; i++)
    {
    /* ensure there are no embedded nuls prior to fractional-second delim */
    if (str [i] == (STDTIME_WCHAR) 0)
      {
      str [i] = (STDTIME_WCHAR) ' ';
      }
    }

  str [STDTIME_STRING_DLM_D1] = pDelim[0];
  str [STDTIME_STRING_DLM_D2] = pDelim[0];
  str [STDTIME_STRING_DLM_S1] = pDelim[1];
  str [STDTIME_STRING_DLM_T1] = pDelim[2];
  str [STDTIME_STRING_DLM_T2] = pDelim[2];
  str [STDTIME_STRING_DLM_F1] = pDelim[3];

  /* only repair delimiter at embTzo if an offset is not present */

  if (str[STDTIME_STRING_LEN] == (STDTIME_WCHAR) 'z')
    {
    str[STDTIME_STRING_LEN] = (STDTIME_WCHAR) 'Z';
    }

  else if ( (str[STDTIME_STRING_LEN] != (STDTIME_WCHAR) '+')
       &&   (str[STDTIME_STRING_LEN] != (STDTIME_WCHAR) '-')
       &&   (str[STDTIME_STRING_LEN] != (STDTIME_WCHAR) 'Z') )
    {
    str [STDTIME_STRING_LEN] = (STDTIME_WCHAR) 0;
    }

  if (str[STDTIME_STRING_LEN] == (STDTIME_WCHAR) 'Z')
    {
    str[STDTIME_STRING_LEN+1] = 0;
    }

  STDTIME_RET_OK;

  } /* DelimitStdTimeStringW */


/*** AddFraction adjustment function *****************************************/

/*-***************************************************************************/
/*            StdTimeFields_AddFraction                                      */
/*  a low-overhead StdTimeFields adjustment without using a delta            */
/*  nMsec, nUsec and nNsec must be positive                                  */
/*****************************************************************************/

STDTIME_RC                  StdTimeFields_AddFraction (
  STDTIME_FIELDS *          /*IO*/ pStdTimeFields,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec)
  {
  STDTIME_FIELDS            f;
  int32_t                   maxday;

  STDTIME_ENUM_FUNC (StdTimeFields_AddFraction)

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if ((nMsec < 0) || (nUsec < 0) || (nNsec < 0))
    {
    STDTIME_RET_EC (argument_out_of_range);
    }

  if STDTIME_IFNOT (ValidStdTimeFields (pStdTimeFields))
    {
    STDTIME_RET_RC;
    }

  if ((nMsec == 0) && (nUsec == 0) && (nNsec == 0))
    {
    STDTIME_RET_OK;         /* nothing to do */
    }

  f.nsec = pStdTimeFields->nsec + nNsec;
  pStdTimeFields->nsec = ((f.nsec / 100) * 100) % 1000;

  f.usec = pStdTimeFields->usec + (f.nsec / 1000) + nUsec;
  pStdTimeFields->usec          = (f.usec % 1000);

  f.msec = pStdTimeFields->msec + (f.usec / 1000) + nMsec;
  pStdTimeFields->msec          = (f.msec % 1000);

  f.sec  = pStdTimeFields->sec  + (f.msec / 1000);
  pStdTimeFields->sec           = (f.sec  % 60);

  f.min  = pStdTimeFields->min  + (f.sec  / 60);
  pStdTimeFields->min           = (f.min  % 60);

  f.hour = pStdTimeFields->hour + (f.min  / 60);
  pStdTimeFields->hour          = (f.hour % 24);

  f.day  = pStdTimeFields->day  + (f.hour / 24);
  f.mon  = pStdTimeFields->mon;
  f.year = pStdTimeFields->year;

  /* adjust days using calander logic */

  for (;;)
    {
    maxday = StdTimeDaysInYearMon (f.year, f.mon);

    if (f.day <= maxday)    /* no (further) calendar adj needed */
      {
      pStdTimeFields->mon  = f.mon;
      pStdTimeFields->year = f.year;
      break;                /* and return true */
      }

    f.day -= maxday;
    f.mon++;

    if (f.mon > 12)
      {
      f.mon = 1;
      f.year++;

      if (f.year > STDTIME_YEAR_MAX)
        {
        STDTIME_RET_EC (year_out_of_range);
        }
      }
    } /* for */

  STDTIME_RET_OK;

  } /* StdTimeFields_AddFraction */


/*** AddSpan functions *******************************************************/


/*-***************************************************************************/
/*            StdTime_AddSpan                                                */
/*  use STDTIME_SPAN parm to increment value in StdTime structure            */
/*****************************************************************************/

STDTIME_RC                  StdTime_AddSpan (
  STDTIME *                 /*IO*/ pStdTime,
  const STDTIME_SPAN *      /*I*/  pSpan)
  {
  QUADLIB_I64               qStdTime;

  STDTIME_ENUM_FUNC (StdTime_AddSpan)

  if STDTIME_IFNOT (Rc_StdTimeToQuadLibI64 (pStdTime, &qStdTime))
    {
    STDTIME_RET_RC;
    }

  QUADLIB_I64_ADD_EQ (qStdTime, pSpan->value);

  if STDTIME_IFNOT (Rc_QuadLibI64ToStdTime (&qStdTime, pStdTime))
    {
    STDTIME_RET_RC;
    }

  STDTIME_RET (ValidStdTime (pStdTime));

  } /* StdTime_AddSpan */


/*-***************************************************************************/
/*            StdTimeFields_AddSpan                                          */
/*  use STDTIME_SPAN parm to increment value in StdTimeFields structure      */
/*****************************************************************************/

STDTIME_RC                  StdTimeFields_AddSpan (
  STDTIME_FIELDS *          /*IO*/ pStdTimeFields,
  const STDTIME_SPAN *      /*I*/  pSpan)
  {
  STDTIME                   stdTime;

  STDTIME_ENUM_FUNC (StdTimeFields_AddSpan)

  if STDTIME_IF (StdTimeFieldsToStdTime (pStdTimeFields, &stdTime))
    {
    if STDTIME_IF (StdTime_AddSpan (&stdTime, pSpan))
      {
      STDTIME_RET (StdTimeToStdTimeFields (&stdTime, pStdTimeFields));
      }
    }

  STDTIME_RET_RC;

  } /* StdTimeFields_AddSpan */


/*-***************************************************************************/
/*            StdTimeStringA_AddSpan                                         */
/*  use STDTIME_SPAN parm to increment value in StdTimeStringA structure     */
/*****************************************************************************/

STDTIME_RC                  StdTimeStringA_AddSpan (
  STDTIME_STRINGA *         /*IO*/ pStdTimeString,
  const STDTIME_SPAN *      /*I*/  pSpan)
  {
  STDTIME                   stdTime;
  STDTIME_STRINGA           s = {{0}};
  char                      c;

  STDTIME_ENUM_FUNC (StdTimeStringA_AddSpan)

  if ((pStdTimeString == NULL) || (pSpan == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  /* copy StdTimeString to temporary, truncating embTzo and extTzo */

  strncpy (s.str, pStdTimeString->str, STDTIME_STRING_LEN);
  s.str [STDTIME_STRING_LEN] = 0;

  if STDTIME_IF (StdTimeStringAToStdTime (&s, &stdTime))
    {
    if STDTIME_IF (StdTime_AddSpan (&stdTime, pSpan))
      {
      if STDTIME_IF (StdTimeToStdTimeStringA (&stdTime, &s))
        {
        /* copy value back, preserving any embTzo in result */

        c = pStdTimeString->str [STDTIME_STRING_LEN];
        strncpy (pStdTimeString->str, s.str, STDTIME_STRING_LEN);
        pStdTimeString->str [STDTIME_STRING_LEN] = c;
        }
      }
    }

  STDTIME_RET_RC;

  } /* StdTimeStringA_AddSpan */


/*-***************************************************************************/
/*            StdTimeStringW_AddSpan                                         */
/*  use STDTIME_SPAN parm to increment value in StdTimeStringW structure     */
/*****************************************************************************/

STDTIME_RC                  StdTimeStringW_AddSpan (
  STDTIME_STRINGW *         /*IO*/ pStdTimeString,
  const STDTIME_SPAN *      /*I*/  pSpan)
  {
  STDTIME                   stdTime;
  STDTIME_STRINGW           s = {{0}};
  STDTIME_WCHAR             c;

  STDTIME_ENUM_FUNC (StdTimeStringW_AddSpan)

  if ((pStdTimeString == NULL) || (pSpan == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  /* copy StdTimeString to temporary, truncating embTzo and extTzo */

  Wchar_StdTime_StrncpyWW (s.str, pStdTimeString->str, STDTIME_STRING_LEN);
  s.str [STDTIME_STRING_LEN] = 0;

  if STDTIME_IF (StdTimeStringWToStdTime (&s, &stdTime))
    {
    if STDTIME_IF (StdTime_AddSpan (&stdTime, pSpan))
      {
      if STDTIME_IF (StdTimeToStdTimeStringW (&stdTime, &s))
        {
        /* copy value back, preserving any embTzo in result */

        c = pStdTimeString->str [STDTIME_STRING_LEN];

        Wchar_StdTime_StrncpyWW (
          pStdTimeString->str, s.str, STDTIME_STRING_LEN);

        pStdTimeString->str [STDTIME_STRING_LEN] = c;
        }
      }
    }

  STDTIME_RET_RC;

  } /* StdTimeStringW_AddSpan */


/*-***************************************************************************/
/*            StdTimeHexStrA_AddSpan                                         */
/*  use STDTIME_SPAN parm to increment value in StdTimeHexStrA structure     */
/*****************************************************************************/

STDTIME_RC                  StdTimeHexStrA_AddSpan (
  STDTIME_HEXSTRA *         /*IO*/ pStdTimeHexStr,
  const STDTIME_SPAN *      /*I*/  pSpan)
  {
  STDTIME                   stdTime;

  STDTIME_ENUM_FUNC (StdTimeHexStrA_AddSpan)

  if STDTIME_IF (StdTimeHexStrAToStdTime (pStdTimeHexStr, &stdTime))
    {
    if STDTIME_IF (StdTime_AddSpan (&stdTime, pSpan))
      {
      STDTIME_RET (StdTimeToStdTimeHexStrA (&stdTime, pStdTimeHexStr));
      }
    }

  STDTIME_RET_RC;

  } /* StdTimeHexStrA_AddSpan */


/*-***************************************************************************/
/*            StdTimeHexStrW_AddSpan                                         */
/*  use STDTIME_SPAN parm to increment value in StdTimeHexStrW structure     */
/*****************************************************************************/

STDTIME_RC                  StdTimeHexStrW_AddSpan (
  STDTIME_HEXSTRW *         /*IO*/ pStdTimeHexStr,
  const STDTIME_SPAN *      /*I*/  pSpan)
  {
  STDTIME                   stdTime;

  STDTIME_ENUM_FUNC (StdTimeHexStrW_AddSpan)

  if STDTIME_IF (StdTimeHexStrWToStdTime (pStdTimeHexStr, &stdTime))
    {
    if STDTIME_IF (StdTime_AddSpan (&stdTime, pSpan))
      {
      STDTIME_RET (StdTimeToStdTimeHexStrW (&stdTime, pStdTimeHexStr));
      }
    }

  STDTIME_RET_RC;

  } /* StdTimeHexStrW_AddSpan */


/*** SubSpan functions *******************************************************/


/*-***************************************************************************/
/*            StdTime_SubSpan                                                */
/*  use STDTIME_SPAN parm to decrement value in StdTime structure            */
/*****************************************************************************/

STDTIME_RC                  StdTime_SubSpan (
  STDTIME *                 /*IO*/ pStdTime,
  const STDTIME_SPAN *      /*I*/  pSpan)
  {
  QUADLIB_I64               qStdTime;

  STDTIME_ENUM_FUNC (StdTime_SubSpan)

  if STDTIME_IFNOT (Rc_StdTimeToQuadLibI64 (pStdTime, &qStdTime))
    {
    STDTIME_RET_RC;
    }

  QUADLIB_I64_SUB_EQ (qStdTime, pSpan->value);

  if STDTIME_IFNOT (Rc_QuadLibI64ToStdTime (&qStdTime, pStdTime))
    {
    STDTIME_RET_RC;
    }

  STDTIME_RET (ValidStdTime (pStdTime));

  } /* StdTime_SubSpan */


/*-***************************************************************************/
/*            StdTimeFields_SubSpan                                          */
/*  use STDTIME_SPAN parm to decrement value in StdTimeFields structure      */
/*****************************************************************************/

STDTIME_RC                  StdTimeFields_SubSpan (
  STDTIME_FIELDS *          /*IO*/ pStdTimeFields,
  const STDTIME_SPAN *      /*I*/  pSpan)
  {
  STDTIME                   stdTime;

  STDTIME_ENUM_FUNC (StdTimeFields_SubSpan)

  if STDTIME_IF (StdTimeFieldsToStdTime (pStdTimeFields, &stdTime))
    {
    if STDTIME_IF (StdTime_SubSpan (&stdTime, pSpan))
      {
      STDTIME_RET (StdTimeToStdTimeFields (&stdTime, pStdTimeFields));
      }
    }

  STDTIME_RET_RC;

  } /* StdTimeFields_SubSpan */


/*-***************************************************************************/
/*            StdTimeStringA_SubSpan                                         */
/*  use STDTIME_SPAN parm to decrement value in StdTimeStringA structure     */
/*****************************************************************************/

STDTIME_RC                  StdTimeStringA_SubSpan (
  STDTIME_STRINGA *         /*IO*/ pStdTimeString,
  const STDTIME_SPAN *      /*I*/  pSpan)
  {
  STDTIME                   stdTime;
  STDTIME_STRINGA           s = {{0}};
  char                      c;

  STDTIME_ENUM_FUNC (StdTimeStringA_SubSpan)

  if ((pStdTimeString == NULL) || (pSpan == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  /* copy StdTimeString to temporary, truncating embTzo and extTzo */

  strncpy (s.str, pStdTimeString->str, STDTIME_STRING_LEN);
  s.str [STDTIME_STRING_LEN] = 0;

  if STDTIME_IF (StdTimeStringAToStdTime (&s, &stdTime))
    {
    if STDTIME_IF (StdTime_SubSpan (&stdTime, pSpan))
      {
      if STDTIME_IF (StdTimeToStdTimeStringA (&stdTime, &s))
        {
        /* copy value back, preserving any embTzo in result */

        c = pStdTimeString->str [STDTIME_STRING_LEN];
        strncpy (pStdTimeString->str, s.str, STDTIME_STRING_LEN);
        pStdTimeString->str [STDTIME_STRING_LEN] = c;
        }
      }
    }

  STDTIME_RET_RC;

  } /* StdTimeStringA_SubSpan */


/*-***************************************************************************/
/*            StdTimeStringW_SubSpan                                         */
/*  use STDTIME_SPAN parm to decrement value in StdTimeStringW structure     */
/*****************************************************************************/

STDTIME_RC                  StdTimeStringW_SubSpan (
  STDTIME_STRINGW *         /*IO*/ pStdTimeString,
  const STDTIME_SPAN *      /*I*/  pSpan)
  {
  STDTIME                   stdTime;
  STDTIME_STRINGW           s = {{0}};
  STDTIME_WCHAR             c;

  STDTIME_ENUM_FUNC (StdTimeStringW_SubSpan)

  if ((pStdTimeString == NULL) || (pSpan == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  /* copy StdTimeString to temporary, truncating embTzo and extTzo */

  Wchar_StdTime_StrncpyWW (s.str, pStdTimeString->str, STDTIME_STRING_LEN);
  s.str [STDTIME_STRING_LEN] = 0;

  if STDTIME_IF (StdTimeStringWToStdTime (&s, &stdTime))
    {
    if STDTIME_IF (StdTime_SubSpan (&stdTime, pSpan))
      {
      if STDTIME_IF (StdTimeToStdTimeStringW (&stdTime, &s))
        {
        /* copy value back, preserving any embTzo in result */

        c = pStdTimeString->str [STDTIME_STRING_LEN];

        Wchar_StdTime_StrncpyWW (
          pStdTimeString->str, s.str, STDTIME_STRING_LEN);

        pStdTimeString->str [STDTIME_STRING_LEN] = c;
        }
      }
    }

  STDTIME_RET_RC;

  } /* StdTimeStringW_SubSpan */


/*-***************************************************************************/
/*            StdTimeHexStrA_SubSpan                                         */
/*  use STDTIME_SPAN parm to decrement value in StdTimeHexStrA structure     */
/*****************************************************************************/

STDTIME_RC                  StdTimeHexStrA_SubSpan (
  STDTIME_HEXSTRA *         /*IO*/ pStdTimeHexStr,
  const STDTIME_SPAN *      /*I*/  pSpan)
  {
  STDTIME                   stdTime;

  STDTIME_ENUM_FUNC (StdTimeHexStrA_SubSpan)

  if STDTIME_IF (StdTimeHexStrAToStdTime (pStdTimeHexStr, &stdTime))
    {
    if STDTIME_IF (StdTime_SubSpan (&stdTime, pSpan))
      {
      STDTIME_RET (StdTimeToStdTimeHexStrA (&stdTime, pStdTimeHexStr));
      }
    }

  STDTIME_RET_RC;

  } /* StdTimeHexStrA_SubSpan */


/*-***************************************************************************/
/*            StdTimeHexStrW_SubSpan                                         */
/*  use STDTIME_SPAN parm to decrement value in StdTimeHexStrW structure     */
/*****************************************************************************/

STDTIME_RC                  StdTimeHexStrW_SubSpan (
  STDTIME_HEXSTRW *         /*IO*/ pStdTimeHexStr,
  const STDTIME_SPAN *      /*I*/  pSpan)
  {
  STDTIME                   stdTime;

  STDTIME_ENUM_FUNC (StdTimeHexStrW_SubSpan)

  if STDTIME_IF (StdTimeHexStrWToStdTime (pStdTimeHexStr, &stdTime))
    {
    if STDTIME_IF (StdTime_SubSpan (&stdTime, pSpan))
      {
      STDTIME_RET (StdTimeToStdTimeHexStrW (&stdTime, pStdTimeHexStr));
      }
    }

  STDTIME_RET_RC;

  } /* StdTimeHexStrW_SubSpan */


/*** AddDelta functions ******************************************************/


/*-***************************************************************************/
/*            StdTime_AddDelta                                               */
/*  use STDTIME_DELTA parm to increment value in StdTime structure           */
/*****************************************************************************/

STDTIME_RC                  StdTime_AddDelta (
  STDTIME *                 /*IO*/ pStdTime,
  const STDTIME_DELTA *     /*I*/  pDelta)
  {
  STDTIME_SPAN              span;

  STDTIME_ENUM_FUNC (StdTime_AddDelta)

  if STDTIME_IF (StdTimeDeltaToStdTimeSpan (pDelta, &span))
    {
    STDTIME_RET (StdTime_AddSpan (pStdTime, &span));
    }

  STDTIME_RET_RC;

  } /* StdTime_AddDelta */

/*-***************************************************************************/
/*            StdTimeFields_AddDelta                                         */
/*  use STDTIME_DELTA parm to increment value in StdTimeFields structure     */
/*****************************************************************************/

STDTIME_RC                  StdTimeFields_AddDelta (
  STDTIME_FIELDS *          /*IO*/ pStdTimeFields,
  const STDTIME_DELTA *     /*I*/  pDelta)
  {
  STDTIME_SPAN              span;

  STDTIME_ENUM_FUNC (StdTimeFields_AddDelta)

  if STDTIME_IF (StdTimeDeltaToStdTimeSpan (pDelta, &span))
    {
    STDTIME_RET (StdTimeFields_AddSpan (pStdTimeFields, &span));
    }

  STDTIME_RET_RC;

  } /* StdTimeFields_AddDelta */


/*-***************************************************************************/
/*            StdTimeStringA_AddDelta                                        */
/*  use STDTIME_DELTA parm to increment value in StdTimeStringA structure    */
/*****************************************************************************/

STDTIME_RC                  StdTimeStringA_AddDelta (
  STDTIME_STRINGA *         /*IO*/ pStdTimeString,
  const STDTIME_DELTA *     /*I*/  pDelta)
  {
  STDTIME_SPAN              span;

  STDTIME_ENUM_FUNC (StdTimeStringA_AddDelta)

  if STDTIME_IF (StdTimeDeltaToStdTimeSpan (pDelta, &span))
    {
    STDTIME_RET (StdTimeStringA_AddSpan (pStdTimeString, &span));
    }

  STDTIME_RET_RC;

  } /* StdTimeStringA_AddDelta */

/*-***************************************************************************/
/*            StdTimeStringW_AddDelta                                        */
/*  use STDTIME_DELTA parm to increment value in StdTimeStringW structure    */
/*****************************************************************************/

STDTIME_RC                  StdTimeStringW_AddDelta (
  STDTIME_STRINGW *         /*IO*/ pStdTimeString,
  const STDTIME_DELTA *     /*I*/  pDelta)
  {
  STDTIME_SPAN              span;

  STDTIME_ENUM_FUNC (StdTimeStringW_AddDelta)

  if STDTIME_IF (StdTimeDeltaToStdTimeSpan (pDelta, &span))
    {
    STDTIME_RET (StdTimeStringW_AddSpan (pStdTimeString, &span));
    }

  STDTIME_RET_RC;

  } /* StdTimeStringW_AddDelta */

/*-***************************************************************************/
/*            StdTimeHexStrA_AddDelta                                        */
/*  use STDTIME_DELTA parm to increment value in StdTimeHexStrA structure    */
/*****************************************************************************/

STDTIME_RC                  StdTimeHexStrA_AddDelta (
  STDTIME_HEXSTRA *         /*IO*/ pStdTimeHexStr,
  const STDTIME_DELTA *     /*I*/  pDelta)
  {
  STDTIME_SPAN              span;

  STDTIME_ENUM_FUNC (StdTimeHexStrA_AddDelta)

  if STDTIME_IF (StdTimeDeltaToStdTimeSpan (pDelta, &span))
    {
    STDTIME_RET (StdTimeHexStrA_AddSpan (pStdTimeHexStr, &span));
    }

  STDTIME_RET_RC;

  } /* StdTimeHexStrA_AddDelta */

/*-***************************************************************************/
/*            StdTimeHexStrW_AddDelta                                        */
/*  use STDTIME_DELTA parm to increment value in StdTimeHexStrW structure    */
/*****************************************************************************/

STDTIME_RC                  StdTimeHexStrW_AddDelta (
  STDTIME_HEXSTRW *         /*IO*/ pStdTimeHexStr,
  const STDTIME_DELTA *     /*I*/  pDelta)
  {
  STDTIME_SPAN              span;

  STDTIME_ENUM_FUNC (StdTimeHexStrW_AddDelta)

  if STDTIME_IF (StdTimeDeltaToStdTimeSpan (pDelta, &span))
    {
    STDTIME_RET (StdTimeHexStrW_AddSpan (pStdTimeHexStr, &span));
    }

  STDTIME_RET_RC;

  } /* StdTimeHexStrW_AddDelta */


/*** SubDelta functions ******************************************************/


/*-***************************************************************************/
/*            StdTime_SubDelta                                               */
/*  use STDTIME_DELTA parm to decrement value in StdTime structure           */
/*****************************************************************************/

STDTIME_RC                  StdTime_SubDelta (
  STDTIME *                 /*IO*/ pStdTime,
  const STDTIME_DELTA *     /*I*/  pDelta)
  {
  STDTIME_SPAN              span;

  STDTIME_ENUM_FUNC (StdTime_SubDelta)

  if STDTIME_IF (StdTimeDeltaToStdTimeSpan (pDelta, &span))
    {
    STDTIME_RET (StdTime_SubSpan (pStdTime, &span));
    }

  STDTIME_RET_RC;

  } /* StdTime_SubDelta */

/*-***************************************************************************/
/*            StdTimeFields_SubDelta                                         */
/*  use STDTIME_DELTA parm to decrement value in StdTimeFields structure     */
/*****************************************************************************/

STDTIME_RC                  StdTimeFields_SubDelta (
  STDTIME_FIELDS *          /*IO*/ pStdTimeFields,
  const STDTIME_DELTA *     /*I*/  pDelta)
  {
  STDTIME_SPAN              span;

  STDTIME_ENUM_FUNC (StdTimeFields_SubDelta)

  if STDTIME_IF (StdTimeDeltaToStdTimeSpan (pDelta, &span))
    {
    STDTIME_RET (StdTimeFields_SubSpan (pStdTimeFields, &span));
    }

  STDTIME_RET_RC;

  } /* StdTimeFields_SubDelta */


/*-***************************************************************************/
/*            StdTimeStringA_SubDelta                                        */
/*  use STDTIME_DELTA parm to decrement value in StdTimeStringA structure    */
/*****************************************************************************/

STDTIME_RC                  StdTimeStringA_SubDelta (
  STDTIME_STRINGA *         /*IO*/ pStdTimeString,
  const STDTIME_DELTA *     /*I*/  pDelta)
  {
  STDTIME_SPAN              span;

  STDTIME_ENUM_FUNC (StdTimeStringA_SubDelta)

  if STDTIME_IF (StdTimeDeltaToStdTimeSpan (pDelta, &span))
    {
    STDTIME_RET (StdTimeStringA_SubSpan (pStdTimeString, &span));
    }

  STDTIME_RET_RC;

  } /* StdTimeStringA_SubDelta */

/*-***************************************************************************/
/*            StdTimeStringW_SubDelta                                        */
/*  use STDTIME_DELTA parm to decrement value in StdTimeStringW structure    */
/*****************************************************************************/

STDTIME_RC                  StdTimeStringW_SubDelta (
  STDTIME_STRINGW *         /*IO*/ pStdTimeString,
  const STDTIME_DELTA *     /*I*/  pDelta)
  {
  STDTIME_SPAN              span;

  STDTIME_ENUM_FUNC (StdTimeStringW_SubDelta)

  if STDTIME_IF (StdTimeDeltaToStdTimeSpan (pDelta, &span))
    {
    STDTIME_RET (StdTimeStringW_SubSpan (pStdTimeString, &span));
    }

  STDTIME_RET_RC;

  } /* StdTimeStringW_SubDelta */

/*-***************************************************************************/
/*            StdTimeHexStrA_SubDelta                                        */
/*  use STDTIME_DELTA parm to decrement value in StdTimeHexStrA structure    */
/*****************************************************************************/

STDTIME_RC                  StdTimeHexStrA_SubDelta (
  STDTIME_HEXSTRA *         /*IO*/ pStdTimeHexStr,
  const STDTIME_DELTA *     /*I*/  pDelta)
  {
  STDTIME_SPAN              span;

  STDTIME_ENUM_FUNC (StdTimeHexStrA_SubDelta)

  if STDTIME_IF (StdTimeDeltaToStdTimeSpan (pDelta, &span))
    {
    STDTIME_RET (StdTimeHexStrA_SubSpan (pStdTimeHexStr, &span));
    }

  STDTIME_RET_RC;

  } /* StdTimeHexStrA_SubDelta */

/*-***************************************************************************/
/*            StdTimeHexStrW_SubDelta                                        */
/*  use STDTIME_DELTA parm to decrement value in StdTimeHexStrW structure    */
/*****************************************************************************/

STDTIME_RC                  StdTimeHexStrW_SubDelta (
  STDTIME_HEXSTRW *         /*IO*/ pStdTimeHexStr,
  const STDTIME_DELTA *     /*I*/  pDelta)
  {
  STDTIME_SPAN              span;

  STDTIME_ENUM_FUNC (StdTimeHexStrW_SubDelta)

  if STDTIME_IF (StdTimeDeltaToStdTimeSpan (pDelta, &span))
    {
    STDTIME_RET (StdTimeHexStrW_SubSpan (pStdTimeHexStr, &span));
    }

  STDTIME_RET_RC;

  } /* StdTimeHexStrW_SubDelta */


/*** GetSpan functions *******************************************************/


/*-***************************************************************************/
/*            StdTime_GetSpan                                                */
/*  produce a STDTIME_SPAN value as the delta-t of two STDTIME values        */
/*****************************************************************************/


STDTIME_RC                  StdTime_GetSpan (
  const STDTIME *           /*I*/ pStdTimeOne,
  const STDTIME *           /*I*/ pStdTimeTwo,
  STDTIME_SPAN *            /*O*/ pSpan)
  {
  QUADLIB_I64               qOne;
  QUADLIB_I64               qTwo;

  STDTIME_ENUM_FUNC (StdTime_GetSpan)

  if STDTIME_IFNOT (Rc_StdTimeToQuadLibI64 (pStdTimeOne, &qOne))
    {
    STDTIME_RET_RC;
    }

  if STDTIME_IFNOT (Rc_StdTimeToQuadLibI64 (pStdTimeTwo, &qTwo))
    {
    STDTIME_RET_RC;
    }

  pSpan->value = QUADLIB_I64_SUB (qOne, qTwo);

  STDTIME_RET (ValidStdTimeSpan (pSpan));

  } /* StdTime_GetSpan */


/*-***************************************************************************/
/*            StdTimeFields_GetSpan                                          */
/*  form STDTIME_SPAN value as a delta-t of two STDTIME_FIELDS values        */
/*****************************************************************************/

STDTIME_RC                  StdTimeFields_GetSpan (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFieldsOne,
  const STDTIME_FIELDS *    /*I*/ pStdTimeFieldsTwo,
  STDTIME_SPAN *            /*O*/ pSpan)
  {
  STDTIME                   one;
  STDTIME                   two;

  STDTIME_ENUM_FUNC (StdTimeFields_GetSpan)

  if STDTIME_IF (StdTimeFieldsToStdTime (pStdTimeFieldsOne, &one))
    {
    if STDTIME_IF (StdTimeFieldsToStdTime (pStdTimeFieldsTwo, &two))
      {
      STDTIME_RET (StdTime_GetSpan (&one, &two, pSpan));
      }
    }

  STDTIME_RET_RC;

  } /* StdTimeFields_GetSpan */

/*-***************************************************************************/
/*            StdTimeStringA_GetSpan                                         */
/*  form STDTIME_SPAN value as a delta-t of two STDTIME_STRINGA values       */
/*****************************************************************************/

STDTIME_RC                  StdTimeStringA_GetSpan (
  const STDTIME_STRINGA *   /*I*/ pStdTimeStringOne,
  const STDTIME_STRINGA *   /*I*/ pStdTimeStringTwo,
  STDTIME_SPAN *            /*I*/ pSpan)
  {
  STDTIME                   one;
  STDTIME                   two;

  STDTIME_ENUM_FUNC (StdTimeStringA_GetSpan)

  if STDTIME_IF (StdTimeStringAToStdTime (pStdTimeStringOne, &one))
    {
    if STDTIME_IF (StdTimeStringAToStdTime (pStdTimeStringTwo, &two))
      {
      STDTIME_RET (StdTime_GetSpan (&one, &two, pSpan));
      }
    }

  STDTIME_RET_RC;

  } /* StdTimeStringA_GetSpan */

/*-***************************************************************************/
/*            StdTimeStringW_GetSpan                                         */
/*  form STDTIME_SPAN value as a delta-t of two STDTIME_STRINGW values       */
/*****************************************************************************/

STDTIME_RC                  StdTimeStringW_GetSpan (
  const STDTIME_STRINGW *   /*I*/ pStdTimeStringOne,
  const STDTIME_STRINGW *   /*I*/ pStdTimeStringTwo,
  STDTIME_SPAN *            /*I*/ pSpan)
  {
  STDTIME                   one;
  STDTIME                   two;

  STDTIME_ENUM_FUNC (StdTimeStringW_GetSpan)

  if STDTIME_IF (StdTimeStringWToStdTime (pStdTimeStringOne, &one))
    {
    if STDTIME_IF (StdTimeStringWToStdTime (pStdTimeStringTwo, &two))
      {
      STDTIME_RET (StdTime_GetSpan (&one, &two, pSpan));
      }
    }

  STDTIME_RET_RC;

  } /* StdTimeStringW_GetSpan */

/*-***************************************************************************/
/*            StdTimeHexStrA_GetSpan                                         */
/*  form STDTIME_SPAN value as a delta-t of two STDTIME_HEXSTRA values       */
/*****************************************************************************/

STDTIME_RC                  StdTimeHexStrA_GetSpan (
  const STDTIME_HEXSTRA *   /*I*/ pStdTimeHexStrOne,
  const STDTIME_HEXSTRA *   /*I*/ pStdTimeHexStrTwo,
  STDTIME_SPAN *            /*I*/ pSpan)
  {
  STDTIME                   one;
  STDTIME                   two;

  STDTIME_ENUM_FUNC (StdTimeHexStrA_GetSpan)

  if STDTIME_IF (StdTimeHexStrAToStdTime (pStdTimeHexStrOne, &one))
    {
    if STDTIME_IF (StdTimeHexStrAToStdTime (pStdTimeHexStrTwo, &two))
      {
      STDTIME_RET (StdTime_GetSpan (&one, &two, pSpan));
      }
    }

  STDTIME_RET_RC;

  } /* StdTimeHexStrA_GetSpan */

/*-***************************************************************************/
/*            StdTimeHexStrW_GetSpan                                         */
/*  form STDTIME_SPAN value as a delta-t of two STDTIME_HEXSTRW values       */
/*****************************************************************************/

STDTIME_RC                  StdTimeHexStrW_GetSpan (
  const STDTIME_HEXSTRW *   /*I*/ pStdTimeHexStrOne,
  const STDTIME_HEXSTRW *   /*I*/ pStdTimeHexStrTwo,
  STDTIME_SPAN *            /*I*/ pSpan)
  {
  STDTIME                   one;
  STDTIME                   two;

  STDTIME_ENUM_FUNC (StdTimeHexStrW_GetSpan)

  if STDTIME_IF (StdTimeHexStrWToStdTime (pStdTimeHexStrOne, &one))
    {
    if STDTIME_IF (StdTimeHexStrWToStdTime (pStdTimeHexStrTwo, &two))
      {
      STDTIME_RET (StdTime_GetSpan (&one, &two, pSpan));
      }
    }

  STDTIME_RET_RC;

  } /* StdTimeHexStrW_GetSpan */


/*** GetDelta functions ******************************************************/


/*-***************************************************************************/
/*            StdTime_GetDelta                                               */
/*  produce a STDTIME_DELTA value as the delta-t of two STDTIME values       */
/*****************************************************************************/

STDTIME_RC                  StdTime_GetDelta (
  const STDTIME *           /*I*/ pStdTimeOne,
  const STDTIME *           /*I*/ pStdTimeTwo,
  STDTIME_DELTA *           /*O*/ pDelta)
  {
  STDTIME_SPAN              span;

  STDTIME_ENUM_FUNC (StdTime_GetDelta)

  if STDTIME_IF (StdTime_GetSpan (pStdTimeOne, pStdTimeTwo, &span))
    {
    STDTIME_RET (StdTimeSpanToStdTimeDelta (&span, pDelta));
    }

  STDTIME_RET_RC;

  } /* StdTime_GetDelta */


/*-***************************************************************************/
/*            StdTimeFields_GetDelta                                         */
/*  form STDTIME_DELTA value as a delta-t of two STDTIME values              */
/*****************************************************************************/

STDTIME_RC                  StdTimeFields_GetDelta (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFieldsOne,
  const STDTIME_FIELDS *    /*I*/ pStdTimeFieldsTwo,
  STDTIME_DELTA *           /*O*/ pDelta)
  {
  STDTIME_SPAN              span;

  STDTIME_ENUM_FUNC (StdTimeFields_GetDelta)

  if STDTIME_IF (StdTimeFields_GetSpan (
       pStdTimeFieldsOne, pStdTimeFieldsTwo, &span))
    {
    STDTIME_RET (StdTimeSpanToStdTimeDelta (&span, pDelta));
    }

  STDTIME_RET_RC;

  } /* StdTimeFields_GetDelta */


/*-***************************************************************************/
/*            StdTimeStringA_GetDelta                                        */
/*  form STDTIME_DELTA value as a delta-t of two STDTIME_STRINGA values      */
/*****************************************************************************/

STDTIME_RC                  StdTimeStringA_GetDelta (
  const STDTIME_STRINGA *   /*I*/ pStdTimeStringOne,
  const STDTIME_STRINGA *   /*I*/ pStdTimeStringTwo,
  STDTIME_DELTA *           /*I*/ pDelta)
  {
  STDTIME_SPAN              span;

  STDTIME_ENUM_FUNC (StdTimeStringA_GetDelta)

  if STDTIME_IF (StdTimeStringA_GetSpan (
       pStdTimeStringOne, pStdTimeStringTwo, &span))
    {
    STDTIME_RET (StdTimeSpanToStdTimeDelta (&span, pDelta));
    }

  STDTIME_RET_RC;

  } /* StdTimeStringA_GetDelta */


/*-***************************************************************************/
/*            StdTimeStringW_GetDelta                                        */
/*  form STDTIME_DELTA value as a delta-t of two STDTIME_STRINGW values      */
/*****************************************************************************/

STDTIME_RC                  StdTimeStringW_GetDelta (
  const STDTIME_STRINGW *   /*I*/ pStdTimeStringOne,
  const STDTIME_STRINGW *   /*I*/ pStdTimeStringTwo,
  STDTIME_DELTA *           /*I*/ pDelta)
  {
  STDTIME_SPAN              span;

  STDTIME_ENUM_FUNC (StdTimeStringW_GetDelta)

  if STDTIME_IF (StdTimeStringW_GetSpan (
       pStdTimeStringOne, pStdTimeStringTwo, &span))
    {
    STDTIME_RET (StdTimeSpanToStdTimeDelta (&span, pDelta));
    }

  STDTIME_RET_RC;

  } /* StdTimeStringW_GetDelta */


/*-***************************************************************************/
/*            StdTimeHexStrA_GetDelta                                        */
/*  form STDTIME_DELTA value as a delta-t of two STDTIME_HEXSTRA values      */
/*****************************************************************************/

STDTIME_RC                  StdTimeHexStrA_GetDelta (
  const STDTIME_HEXSTRA *   /*I*/ pStdTimeHexStrOne,
  const STDTIME_HEXSTRA *   /*I*/ pStdTimeHexStrTwo,
  STDTIME_DELTA *           /*I*/ pDelta)
  {
  STDTIME_SPAN              span;

  STDTIME_ENUM_FUNC (StdTimeHexStrA_GetDelta)

  if STDTIME_IF (StdTimeHexStrA_GetSpan (
       pStdTimeHexStrOne, pStdTimeHexStrTwo, &span))
    {
    STDTIME_RET (StdTimeSpanToStdTimeDelta (&span, pDelta));
    }

  STDTIME_RET_RC;

  } /* StdTimeHexStrA_GetDelta */


/*-***************************************************************************/
/*            StdTimeHexStrW_GetDelta                                        */
/*  form STDTIME_DELTA value as a delta-t of two STDTIME_HEXSTRW values      */
/*****************************************************************************/

STDTIME_RC                  StdTimeHexStrW_GetDelta (
  const STDTIME_HEXSTRW *   /*I*/ pStdTimeHexStrOne,
  const STDTIME_HEXSTRW *   /*I*/ pStdTimeHexStrTwo,
  STDTIME_DELTA *           /*I*/ pDelta)
  {
  STDTIME_SPAN              span;

  STDTIME_ENUM_FUNC (StdTimeHexStrW_GetDelta)

  if STDTIME_IF (StdTimeHexStrW_GetSpan (
       pStdTimeHexStrOne, pStdTimeHexStrTwo, &span))
    {
    STDTIME_RET (StdTimeSpanToStdTimeDelta (&span, pDelta));
    }

  STDTIME_RET_RC;

  } /* StdTimeHexStrW_GetDelta */


/*-***************************************************************************/
/*            NormalizeStdTimeDelta                                          */
/*  normalize a delta value to the nearest number of days                    */
/*  this is the same as truncating its value to the nearest day              */
/*****************************************************************************/


STDTIME_RC                  NormalizeStdTimeDelta (
  STDTIME_DELTA *           /*IO*/ pDelta)
  {
  STDTIME_ENUM_FUNC (NormalizeStdTimeDelta)

  STDTIME_RET (TruncStdTimeDelta (pDelta, STDTIME_FIELD_DAY));

  } /* NormalizeStdTimeDelta */


/*-***************************************************************************/
/*            TruncStdTimeDelta                                              */
/*  form normalized value of delta, such that there are non-zero difference  */
/*  values only as large as the selected units of the specified field.       */
/*  for example, to truncate to 'hour' means that the delta value is         */
/*  expressed in units no larger than hours.  thus, an 'hour' value of 25    */
/*  is truncated to hours because it does not get changed to 1 day and 1     */
/*  'hour'.  fields of smaller units do not exceed the normal maximum value  */
/*  for that field.  for example, a value may be truncated to 25 hours, but  */
/*  the 'min' field will be within the absolute value of 0 to 59, etc.       */
/*                                                                           */
/*  all non-zero values in a truncated delta will have the same sign, plus   */
/*  or minus, regardless of how they were originally defined.                */
/*****************************************************************************/

STDTIME_RC                  TruncStdTimeDelta (
  STDTIME_DELTA *           /*IO*/ pDelta,
  int32_t                   /*I*/  field)
  {
  QUADLIB_I64               qVal;
  int32_t                   sign = 1;
  STDTIME_SPAN              span;
  STDTIME_DELTA             result = {0};

  STDTIME_ENUM_FUNC (TruncStdTimeDelta)

  if (pDelta == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if ((field < STDTIME_FIELD_DAY) || (field > STDTIME_FIELD_NSEC))
    {
    /* field selector is invalid */
    STDTIME_RET_EC (field_selector_out_of_range);
    }

  if STDTIME_IFNOT (StdTimeDeltaToStdTimeSpan (pDelta, &span))
    {
    STDTIME_RET_RC;
    }

  qVal = span.value;

  /* at this point, qVal has a count of 100-nanosecond intervals */
  /* and may be positive or negative */
  /* now, rebuilt the delta value with normalized quantities */

  /***************************************************************************/
  /* nsecs - only 1 digit available, but we store as 3 digit nsec            */
  /***************************************************************************/

  if (QUADLIB_I64_LT_0 (qVal))
    {
    qVal = QUADLIB_I64_NEG (qVal);
    sign = -1;
    }

  /* if truncating to nsec we are done */

  if (field == STDTIME_FIELD_NSEC)
    {
    /* since the 100-nanosecond count must be multiplied by 100 to */
    /* get actual nanoseconds, just checking for overflow is not   */
    /* enough.  we must check to see if overflow WILL occur when   */
    /* the multiply is done, but we have to check before we do it  */

    if ((QUADLIB_I64_HI(qVal) != 0)
    ||  (QUADLIB_U64_LO(qVal) > (0x7FFFFFFF / STDTIME_SCALE_NSEC) ))
      {
      STDTIME_RET_EC (overflow_in_delta_nsec);
      /* cannot hold nsec value in I32 field */
      }

    result.nsec = sign * STDTIME_SCALE_NSEC * QUADLIB_I64_LO(qVal);
    *pDelta = result;

    STDTIME_RET_OK;
    }

  result.nsec =
    sign * STDTIME_SCALE_NSEC * QUADLIB_I32_CASTI64 (
      QUADLIB_I64_MOD (qVal, QUADLIB_I64_CASTI32 (STDTIME_PREC_NSEC)) );

  QUADLIB_I64_DIV_EQ (qVal, QUADLIB_I64_CASTI32 (STDTIME_PREC_NSEC));

  /***************************************************************************/
  /*  qVal now has usecs                                                     */
  /***************************************************************************/

  /* if truncating to usec we are done */

  if (field == STDTIME_FIELD_USEC)
    {
    if (QUADLIB_I64_OVERFLOW_I32 (qVal))
      {
      STDTIME_RET_EC (overflow_in_delta_usec);
      /* cannot hold usec value in I32 field */
      }

    result.usec = sign * QUADLIB_I64_LO(qVal);
    *pDelta = result;
    STDTIME_RET_OK;
    }

  result.usec =
    sign * QUADLIB_I32_CASTI64 (
      QUADLIB_I64_MOD (qVal, QUADLIB_I64_CASTI32 (1000)) );

  QUADLIB_I64_DIV_EQ (qVal, QUADLIB_I64_CASTI32 (1000));    /* qVal / 1000 */


  /***************************************************************************/
  /*  qVal now has msecs                                                     */
  /***************************************************************************/

  /* if truncating to msec we are done */

  if (field == STDTIME_FIELD_MSEC)
    {
    if (QUADLIB_I64_OVERFLOW_I32 (qVal))
      {
      STDTIME_RET_EC (overflow_in_delta_msec);
      /* cannot hold msec value in I32 field */
      }

    result.msec = sign * QUADLIB_I64_LO(qVal);
    *pDelta = result;
    STDTIME_RET_OK;
    }

  result.msec =
    sign * QUADLIB_I32_CASTI64 (
      QUADLIB_I64_MOD (qVal, QUADLIB_I64_CASTI32 (1000)) );

  QUADLIB_I64_DIV_EQ (qVal, QUADLIB_I64_CASTI32 (1000));    /* qVal / 1000 */


  /***************************************************************************/
  /*  qVal now has secs                                                      */
  /***************************************************************************/

  /* if truncating to sec we are done */

  if (field == STDTIME_FIELD_SEC)
    {
    if (QUADLIB_I64_OVERFLOW_I32 (qVal))
      {
      STDTIME_RET_EC (overflow_in_delta_sec);
      /* cannot hold sec value in I32 field */
      }

    result.sec = sign * QUADLIB_I64_LO(qVal);
    *pDelta = result;
    STDTIME_RET_OK;
    }

  result.sec =
    sign * QUADLIB_I32_CASTI64 (
      QUADLIB_I64_MOD (qVal, QUADLIB_I64_CASTI32 (60)) );

  QUADLIB_I64_DIV_EQ (qVal, QUADLIB_I64_CASTI32 (60));      /* qVal / 60 */


  /***************************************************************************/
  /*  qVal now has mins                                                      */
  /***************************************************************************/

  /* if truncating to min we are done */

  if (field == STDTIME_FIELD_MIN)
    {
    if (QUADLIB_I64_OVERFLOW_I32 (qVal))
      {
      STDTIME_RET_EC (overflow_in_delta_min);
      /* cannot hold min value in I32 field */
      }

    result.min = sign * QUADLIB_I64_LO(qVal);
    *pDelta = result;
    STDTIME_RET_OK;
    }

  result.min =
    sign * QUADLIB_I32_CASTI64 (
      QUADLIB_I64_MOD (qVal, QUADLIB_I64_CASTI32 (60)) );

  QUADLIB_I64_DIV_EQ (qVal, QUADLIB_I64_CASTI32 (60));      /* qVal / 60 */


  /***************************************************************************/
  /*  qVal now has hours                                                     */
  /***************************************************************************/

  /* if truncating to hour we are done */

  if (field == STDTIME_FIELD_HOUR)
    {
    if (QUADLIB_I64_OVERFLOW_I32 (qVal))
      {
      STDTIME_RET_EC (overflow_in_delta_hour);
      /* cannot hold hour value in I32 field */
      }

    result.hour = sign * QUADLIB_I64_LO(qVal);
    *pDelta = result;
    STDTIME_RET_OK;
    }

  result.hour =
    sign * QUADLIB_I32_CASTI64 (
      QUADLIB_I64_MOD (qVal, QUADLIB_I64_CASTI32 (24)) );

  QUADLIB_I64_DIV_EQ (qVal, QUADLIB_I64_CASTI32 (24));      /* qVal / 24 */


  /***************************************************************************/
  /*  qVal now has days                                                      */
  /***************************************************************************/

  /* months and years are not linear, so they are left as zero */
  /* field == STDTIME_FIELD_DAY must be true because of prior check */

  if (QUADLIB_I64_OVERFLOW_I32 (qVal))
    {
    STDTIME_RET_EC (overflow_in_delta_day);
    /* cannot hold day value in I32 field */
    }

  result.day = sign * QUADLIB_I64_LO(qVal);
  *pDelta = result;
  STDTIME_RET_OK;

  } /* TruncStdTimeDelta */


/*-***************************************************************************/
/*            RoundStdTimeDelta                                              */
/*  change a delta value to a rounded form.  first, truncate the delta value */
/*  using TruncStdTimeDelta above.  then, based on the field, if the field   */
/*  to its 'right' is greater than or equal to its maximum, the 'round'      */
/*  field is incremented.                                                    */
/*                                                                           */
/*  'greater than' and 'increment' are relative terms, because the delta     */
/*  could be positive or negative; the magnitudes and signs are taken into   */
/*  account.                                                                 */
/*                                                                           */
/*  once the rounding occurs, the fields to the right of the rounded field   */
/*  are zeroed out.  in case the selected field the one to its right are     */
/*  both zero, no increment occurs, but zeroing-out is still done.           */
/*                                                                           */
/*  if the delta is considered invalid by TruncStdTimeDelta, no further      */
/*  processing is done.                                                      */
/*                                                                           */
/*  since nanoseconds (nsec) is the right-most field, a request to round to  */
/*  the nsec level is simply ignored; in effect, it is already rounded to    */
/*  that level, and TruncStdTimeDelta would already have dropped digits of   */
/*  nsec smaller than the 100-nanosecond precision limit anyway.             */
/*                                                                           */
/*  the helper function Bool_StdTime_AbsDelta forms the absolute value of a  */
/*  delta field, and returns STDTIME_TRUE if a sign conflict is found, else  */
/*  STDTIME_FALSE;                                                           */
/*                                                                           */
/*****************************************************************************/

static STDTIME_BOOL         Bool_StdTime_AbsDelta (
  int32_t                   *sign,
  int32_t                   *value)
  {
  int32_t                   newsign = 0;

  if (*value > 0)
    {
    newsign = 1;
    }

  else if (*value < 0)
    {
    newsign = -1;
    *value = -(*value);
    }

  if ((newsign == 0) || (*sign == newsign))
    {
    /* *value is zero, or its sign is the same as the 'old' sign */
    return STDTIME_FALSE;   /* no sign conflict detected */
    }

  if (*sign == 0)           /* sign not defined yet */
    {
    *sign = newsign;
    return STDTIME_FALSE;   /* no sign conflict detected */
    }

  return STDTIME_TRUE;      /* error: delta has conflicting signs */

  } /* Bool_StdTime_AbsDelta */


/*-***************************************************************************/
/*            RoundStdTimeDelta                                              */
/*****************************************************************************/

STDTIME_RC                  RoundStdTimeDelta (
  STDTIME_DELTA *           /*IO*/ pDelta,
  int32_t                   /*I*/  field)
  {
  int32_t                   sign = 0;
  STDTIME_DELTA             f;

  STDTIME_ENUM_FUNC (RoundStdTimeDelta)

  if STDTIME_IFNOT (TruncStdTimeDelta (pDelta, field))
    {
    STDTIME_RET_RC;
    }

  if (field == STDTIME_FIELD_NSEC)
    {
    /* nothing to round - OK - leave value as is */

    STDTIME_RET_OK;
    }

  /* analyze sign of delta fields, and form absolute value of delta */

  f = *pDelta;          /* local copy */

  if ( (Bool_StdTime_AbsDelta (&sign, &f.day ))
  ||   (Bool_StdTime_AbsDelta (&sign, &f.hour))
  ||   (Bool_StdTime_AbsDelta (&sign, &f.min ))
  ||   (Bool_StdTime_AbsDelta (&sign, &f.sec ))
  ||   (Bool_StdTime_AbsDelta (&sign, &f.msec))
  ||   (Bool_StdTime_AbsDelta (&sign, &f.usec))
  ||   (Bool_StdTime_AbsDelta (&sign, &f.nsec)) )
    {
    STDTIME_RET_EC (conflicting_sign_delta);
    }

  /* rounding a field means to increment it if the field to its */
  /* 'right' is >= half the (max+1) value for it */

  /* whether rounds occurs or not, the fields to the right are */
  /* zeroed out to maintain a numerically valid delta value */
  /* to the requested precision of the field being rounded */

  switch (field)
    {
    case STDTIME_FIELD_DAY:
      if (f.hour >= 12)
        {
        f.day++;
        }

      f.hour = f.min = f.sec = f.msec = f.usec = f.nsec = 0;
      break;

    case STDTIME_FIELD_HOUR:
      if (f.min >= 30)
        {
        f.hour++;
        }

      f.min = f.sec = f.msec = f.usec = f.nsec = 0;
      break;

    case STDTIME_FIELD_MIN:
      if (f.sec >= 30)
        {
        f.min++;
        }

      f.sec = f.msec = f.usec = f.nsec = 0;
      break;

    case STDTIME_FIELD_SEC:
      if (f.msec >= 500)
        {
        f.sec++;
        }

      f.msec = f.usec = f.nsec = 0;
      break;

    case STDTIME_FIELD_MSEC:
      if (f.usec >= 500)
        {
        f.msec++;
        }

      f.usec = f.nsec = 0;
      break;

    case STDTIME_FIELD_USEC:
      if (f.nsec >= 500)
        {
        f.usec++;
        }

      f.nsec = 0;
      break;

    default:
     STDTIME_RET_EC (unexpected_condition); /* should not occur */

    } /* switch (field) */

  /* copy back to pDelta parameter, with correct sign */

  pDelta->day  = sign * f.day;
  pDelta->hour = sign * f.hour;
  pDelta->min  = sign * f.min;
  pDelta->sec  = sign * f.sec;
  pDelta->msec = sign * f.msec;
  pDelta->usec = sign * f.usec;
  pDelta->nsec = sign * f.nsec;

  STDTIME_RET_OK;

  } /* RoundStdTimeDelta */


/*** Delta/Span conversion functions *****************************************/


/*-***************************************************************************/
/*            StdTimeDeltaToStdTimeSpan                                      */
/*  convert a StdTimeDelta to a StdTimeSPan value                            */
/*  if the resultant value exceeds the maximum range for a span, return      */
/*  STDTIME_FALSE.  the value range is about +/- 8400 years, in terms of     */
/*  100-nanosecond intervals.                                                */
/*****************************************************************************/


STDTIME_RC                  StdTimeDeltaToStdTimeSpan (
  const STDTIME_DELTA *     /*I*/ pDelta,
  STDTIME_SPAN *            /*O*/ pSpan)
  {
  QUADLIB_I64               qSum;
  QUADLIB_I64               qTest;

  STDTIME_ENUM_FUNC (StdTimeDeltaToStdTimeSpan)

  if ((pDelta == NULL) || (pSpan == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  /* accumulate field values, and convert to nanoseconds */

  /* qSum = day */
  qSum = QUADLIB_I64_CASTI32 (pDelta->day);

  /* qSum (day) *= 24 -> (hour)_*/
  QUADLIB_I64_MUL_EQ (qSum, QUADLIB_I64_CASTI32 (24));

  /* qSum += hour */
  QUADLIB_I64_ADD_EQ (qSum, QUADLIB_I64_CASTI32 (pDelta->hour));

  /* qSum (hour) *= 60 -> (min) */
  QUADLIB_I64_MUL_EQ (qSum, QUADLIB_I64_CASTI32 (60));

  /* qSum += min */
  QUADLIB_I64_ADD_EQ (qSum, QUADLIB_I64_CASTI32 (pDelta->min));

  /* qSum (min) *= 60 -> (sec) */
  QUADLIB_I64_MUL_EQ (qSum, QUADLIB_I64_CASTI32 (60));

  /* qSum += sec */
  QUADLIB_I64_ADD_EQ (qSum, QUADLIB_I64_CASTI32 (pDelta->sec));

  /* qSum (sec) *= 1000 -> (msec) */
  QUADLIB_I64_MUL_EQ (qSum, QUADLIB_I64_CASTI32 (1000));

  /* qSum += msec */
  QUADLIB_I64_ADD_EQ (qSum, QUADLIB_I64_CASTI32 (pDelta->msec));

  /* qSum (msec) *= 1000 -> (usec) */
  QUADLIB_I64_MUL_EQ (qSum, QUADLIB_I64_CASTI32 (1000));

  /* qSum += usec */
  QUADLIB_I64_ADD_EQ (qSum, QUADLIB_I64_CASTI32 (pDelta->usec));

  /* qSum (usec) *= 10 -> (nsec/100) */
  QUADLIB_I64_MUL10_EQ (qSum);

  /* qSum += nsec/100 */
  QUADLIB_I64_ADD_EQ (qSum, QUADLIB_I64_CASTI32 ((pDelta->nsec) / 100));

  pSpan->value = qSum;

  if (QUADLIB_I64_LT_0 (qSum))
    {
    /* create negative test value and see if value is less than it */
    QUADLIB_U64_HI (qTest) = STDTIME_SPAN_MIN_HI;
    QUADLIB_U64_LO (qTest) = STDTIME_SPAN_MIN_LO;

    if (QUADLIB_I64_LT (qSum, qTest))   /* qSum < qTest */
      {
      STDTIME_RET_EC (span_out_of_range);
      }
    }

  else  /* qSum >= 0 */
    {
    /* create positive test value and see if value is less than it */
    QUADLIB_U64_HI (qTest) = STDTIME_SPAN_MAX_HI;
    QUADLIB_U64_LO (qTest) = STDTIME_SPAN_MAX_LO;

    if (QUADLIB_I64_GT (qSum, qTest))   /* qSum > qTest */
      {
      STDTIME_RET_EC (span_out_of_range);
      }
    }

  STDTIME_RET_OK;

  } /* StdTimeDeltaToStdTimeSpan */


/*-***************************************************************************/
/*            StdTimeSpanToStdTimeDelta                                      */
/*  convert a StdTimeSpan to a StdTimeDelta value                            */
/*  if the resultant day value exceeds the maximum range for a day, return   */
/*  STDTIME_FALSE.  the value range 8400 years * 366 days, just to keep      */
/*  the definition simple.                                                   */
/*****************************************************************************/

STDTIME_RC                  StdTimeSpanToStdTimeDelta (
  const STDTIME_SPAN *      /*I*/ pSpan,
  STDTIME_DELTA *           /*O*/ pDelta)
  {
  QUADLIB_U64                       uVal;
  QUADLIB_U64                       uMod;
  QUADLIB_U64                       uDiv;

  int32_t                           sign = 1;

  STDTIME_ENUM_FUNC (StdTimeSpanToStdTimeDelta)

  if ((pSpan == NULL) || (pDelta == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  if (QUADLIB_I64_LT_0 (pSpan->value))
    {
    uVal = QUADLIB_I64_NEG (pSpan->value);
    sign = -1;
    }

  else
    {
    uVal = pSpan->value;
    }

  /* uVal has count of 100 nsecs intervals */
  /* calculate: nsec = (uVal % 10) * 100; */

  QUADLIB_U64_HI (uDiv) = 0;
  QUADLIB_U64_LO (uDiv) = 10;
  uVal = QuadLibU64DivMod (uVal, uDiv, &uMod);
  pDelta->nsec = sign * QUADLIB_I64_LO (uMod) * 100;

  /* uVal has usecs */
  /* calculate: usec = uVal % 1000; */

  QUADLIB_U64_LO (uDiv) = 1000;
  uVal = QuadLibU64DivMod (uVal, uDiv, &uMod);
  pDelta->usec = sign * QUADLIB_I64_LO (uMod);

  /* uVal has msecs */
  /* calculate: wMilliseconds = uVal % 1000; */
  /* QUADLIB_U64_LO (uDiv) = 1000; ==> still in effect */

  uVal = QuadLibU64DivMod (uVal, uDiv, &uMod);
  pDelta->msec = sign * QUADLIB_U64_LO (uMod);

  /* uVal has secs */
  /* calculate: wSecond = uVal % 60; */

  QUADLIB_U64_LO (uDiv) = 60;
  uVal = QuadLibU64DivMod (uVal, uDiv, &uMod);
  pDelta->sec = sign * QUADLIB_U64_LO (uMod);

  /* uVal has mins */
  /* calculate: wMinute = uVal % 60; */
  /* QUADLIB_U64_LO (uDiv) = 60; ==> still in effect */

  uVal = QuadLibU64DivMod (uVal, uDiv, &uMod);
  pDelta->min = sign * QUADLIB_U64_LO(uMod);

  /* uVal has hours */
  /* calculate: wHour = uVal % 24; */

  QUADLIB_U64_LO (uDiv) = 24;
  uVal = QuadLibU64DivMod (uVal, uDiv, &uMod);

  pDelta->hour = sign * QUADLIB_U64_LO (uMod);

  /* uVal has days */

  pDelta->day = sign * QUADLIB_I64_LO (uVal);

  if (QUADLIB_I64_OVERFLOW_I32 (uVal))
    {
    STDTIME_RET_EC (overflow_in_delta_day);
    }

  /* we check the positive value for valid range, so that +/- cases */
  /* are both covered in one test */

  if (QUADLIB_I64_LO (uVal) > STDTIME_DELTA_DAY_MAX)
    {
    STDTIME_RET_EC (overflow_in_delta_day);
    }

  STDTIME_RET_OK;

  } /* StdTimeSpanToStdTimeDelta */


/*** validation of delta and span ********************************************/


/*-***************************************************************************/
/*            ValidStdTimeDelta                                              */
/*  validate delta by converting to a span and discard the result            */
/*****************************************************************************/

STDTIME_RC                  ValidStdTimeDelta (
  const STDTIME_DELTA *     /*I*/ pDelta)
  {
  STDTIME_SPAN              span;

  STDTIME_ENUM_FUNC (ValidStdTimeDelta)

  STDTIME_RET (StdTimeDeltaToStdTimeSpan (pDelta, &span));

  } /* ValidStdTimeDelta */


/*-***************************************************************************/
/*            ValidStdTimeSpan                                               */
/*  validate span by converting to a delta and discard the result            */
/*****************************************************************************/

STDTIME_RC                  ValidStdTimeSpan (
  const STDTIME_SPAN *      /*I*/ pSpan)
  {
  STDTIME_DELTA             delta;

  STDTIME_ENUM_FUNC (ValidStdTimeSpan)

  STDTIME_RET (StdTimeSpanToStdTimeDelta (pSpan, &delta));

  } /* ValidStdTimeSpan */


/*** Delta/Span sign-related functions ***************************************/


/*-***************************************************************************/
/*            SgnStdTimeDelta                                                */
/*  characterize the sign of a delta as -1, 0 or +1                          */
/*****************************************************************************/

int32_t                     SgnStdTimeDelta (
  const STDTIME_DELTA *     /*I*/ pDelta)
  {
  STDTIME_SPAN              span;

  if (pDelta == NULL)
    {
    return STDTIME_ERR;
    }

  /* test for a normal sign first */

  if ((pDelta->day  == 0)
  &&  (pDelta->hour == 0)
  &&  (pDelta->min  == 0)
  &&  (pDelta->sec  == 0)
  &&  (pDelta->msec == 0)
  &&  (pDelta->usec == 0)
  &&  (pDelta->nsec == 0))
    {
    return STDTIME_EQ;  /* == 0 */
    }

  if ((pDelta->day  >= 0)
  &&  (pDelta->hour >= 0)
  &&  (pDelta->min  >= 0)
  &&  (pDelta->sec  >= 0)
  &&  (pDelta->msec >= 0)
  &&  (pDelta->usec >= 0)
  &&  (pDelta->nsec >= 0))
    {
    return STDTIME_GT;  /* > 0 (not >= 0, because 0 already checked for) */
    }

  if ((pDelta->day  <= 0)
  &&  (pDelta->hour <= 0)
  &&  (pDelta->min  <= 0)
  &&  (pDelta->sec  <= 0)
  &&  (pDelta->msec <= 0)
  &&  (pDelta->usec <= 0)
  &&  (pDelta->nsec <= 0))
    {
    return STDTIME_LT;  /* < 0 (not <= 0, because 0 already checked for) */
    }

  /* delta has a complex sign. convert to a span, and report its sign */

  if (StdTimeDeltaToStdTimeSpan (pDelta, &span) == STDTIME_OK)
    {
    return SgnStdTimeSpan (&span);
    }

  return STDTIME_ERR;

  } /* SgnStdTimeDelta */


/*-***************************************************************************/
/*            AbsStdTimeDelta                                                */
/*  form absolute value of a delta; depends on its sign                      */
/*****************************************************************************/

STDTIME_RC                  AbsStdTimeDelta (
  STDTIME_DELTA *           /*IO*/ pDelta)
  {
  int32_t                   sign;

  STDTIME_ENUM_FUNC (AbsStdTimeDelta)

  sign = SgnStdTimeDelta (pDelta);  /* handles NULL argument */

  if (sign == STDTIME_ERR)
    {
    STDTIME_RET_EC (failure_in_api_SgnStdTimeDelta);
    }

  if (sign == STDTIME_LT)
    {
    STDTIME_RET (NegStdTimeDelta (pDelta));
    }

  STDTIME_RET_OK;

  } /* AbsStdTimeDelta */


/*-***************************************************************************/
/*            NegStdTimeDelta                                                */
/*  form negative value of a delta; negates each element                     */
/*****************************************************************************/

STDTIME_RC                  NegStdTimeDelta (
  STDTIME_DELTA *           /*IO*/ pDelta)
  {
  STDTIME_ENUM_FUNC (NegStdTimeDelta)

  if (pDelta == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  pDelta->day  = -(pDelta->day);
  pDelta->hour = -(pDelta->hour);
  pDelta->min  = -(pDelta->min);
  pDelta->sec  = -(pDelta->sec);
  pDelta->msec = -(pDelta->msec);
  pDelta->usec = -(pDelta->usec);
  pDelta->nsec = -(pDelta->nsec);

  STDTIME_RET_OK;

  } /* NegStdTimeDelta */


/*-***************************************************************************/
/*            SgnStdTimeSpan                                                 */
/*  characterize the sign of a span as -1, 0 or +1                           */
/*****************************************************************************/

int32_t                     SgnStdTimeSpan (
  const STDTIME_SPAN *      /*I*/ pSpan)
  {
  if (pSpan == NULL)
    {
    return STDTIME_ERR;
    }

  if (QUADLIB_I64_LT_0 (pSpan->value))
    {
    return STDTIME_LT;
    }

  if (QUADLIB_I64_EQ_0 (pSpan->value))
    {
    return STDTIME_EQ;
    }

  return STDTIME_GT;
  } /* SgnStdTimeSpan */


/*-***************************************************************************/
/*            AbsStdTimeSpan                                                 */
/*  form absolute value of a span, via call to QUADLIB function              */
/*****************************************************************************/

STDTIME_RC                  AbsStdTimeSpan (
  STDTIME_SPAN *            /*IO*/ pSpan)
  {
  STDTIME_ENUM_FUNC (AbsStdTimeSpan)

  if (pSpan == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  pSpan->value = QUADLIB_I64_ABS (pSpan->value);

  STDTIME_RET_OK;

  } /* AbsStdTimeSpan */


/*-***************************************************************************/
/*            NegStdTimeSpan                                                 */
/*  form negative value of a span, via call to QUADLIB function              */
/*****************************************************************************/

STDTIME_RC                  NegStdTimeSpan (
  STDTIME_SPAN *            /*IO*/ pSpan)
  {
  STDTIME_ENUM_FUNC (NegStdTimeSpan)

  if (pSpan == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  pSpan->value = QUADLIB_I64_NEG (pSpan->value);

  STDTIME_RET_OK;

  } /* NegStdTimeSpan */


/*** Compare functions *******************************************************/


/*-***************************************************************************/
/*            CompareStdTime                                                 */
/*  compare two STDTIME values and return a strcmp-like result               */
/*****************************************************************************/

int32_t                     CompareStdTime (
  const STDTIME *           /*I*/ pOne,
  const STDTIME *           /*I*/ pTwo)
  {
  if ((pOne == NULL) || (pTwo == NULL))
    {
    return STDTIME_ERR;
    }

  PVT_STDTIME_COMPARE(hi);
  PVT_STDTIME_COMPARE(lo);

  return STDTIME_EQ;

  } /* CompareStdTime */

/*-***************************************************************************/
/*            CompareStdTimeFields                                           */
/*  compare two STDTIME_FIELDS values and return a strcmp-like result        */
/*****************************************************************************/

int32_t                     CompareStdTimeFields (
  const STDTIME_FIELDS *    /*I*/ pOne,
  const STDTIME_FIELDS *    /*I*/ pTwo)
  {
  if ((pOne == NULL) || (pTwo == NULL))
    {
    return STDTIME_ERR;
    }

  PVT_STDTIME_COMPARE(year);
  PVT_STDTIME_COMPARE(mon );
  PVT_STDTIME_COMPARE(day );
  PVT_STDTIME_COMPARE(hour);
  PVT_STDTIME_COMPARE(min );
  PVT_STDTIME_COMPARE(sec );
  PVT_STDTIME_COMPARE(msec);
  PVT_STDTIME_COMPARE(usec);
  PVT_STDTIME_COMPARE(nsec);

  return STDTIME_EQ;

  } /* CompareStdTimeFields */

/*-***************************************************************************/
/*            CompareStdTimeStringA                                          */
/*  compare two STDTIME_STRINGA values and return a strcmp-like result       */
/*****************************************************************************/

int32_t                     CompareStdTimeStringA (
  const STDTIME_STRINGA *   /*I*/ pOne,
  const STDTIME_STRINGA *   /*I*/ pTwo)
  {
  STDTIME_FIELDS            oneFields;
  STDTIME_FIELDS            twoFields;

  if (StdTimeStringAToStdTimeFields (pOne, &oneFields) == STDTIME_OK)
    {
    if (StdTimeStringAToStdTimeFields (pTwo, &twoFields) == STDTIME_OK)
      {
      return CompareStdTimeFields (&oneFields, &twoFields);
      }
    }

  return STDTIME_ERR;

  } /* CompareStdTimeStringA */

/*-***************************************************************************/
/*            CompareStdTimeStringW                                          */
/*  compare two STDTIME_STRINGW values and return a strcmp-like result       */
/*****************************************************************************/

int32_t                     CompareStdTimeStringW (
  const STDTIME_STRINGW *   /*I*/ pOne,
  const STDTIME_STRINGW *   /*I*/ pTwo)
  {
  STDTIME_FIELDS            oneFields;
  STDTIME_FIELDS            twoFields;

  if (StdTimeStringWToStdTimeFields (pOne, &oneFields) == STDTIME_OK)
    {
    if (StdTimeStringWToStdTimeFields (pTwo, &twoFields) == STDTIME_OK)
      {
      return CompareStdTimeFields (&oneFields, &twoFields);
      }
    }

  return STDTIME_ERR;

  } /* CompareStdTimeStringW */

/*-***************************************************************************/
/*            CompareStdTimeHexStrA                                          */
/*  compare two STDTIME_HEXSTRA values and return a strcmp-like result       */
/*****************************************************************************/

int32_t                     CompareStdTimeHexStrA (
  const STDTIME_HEXSTRA *   /*I*/ pStdTimeHexStrOne,
  const STDTIME_HEXSTRA *   /*I*/ pStdTimeHexStrTwo)
  {
  STDTIME                   oneStdTime;
  STDTIME                   twoStdTime;

  if (StdTimeHexStrAToStdTime (pStdTimeHexStrOne, &oneStdTime) == STDTIME_OK)
    {
    if (StdTimeHexStrAToStdTime (pStdTimeHexStrTwo, &twoStdTime) == STDTIME_OK)
      {
      return CompareStdTime (&oneStdTime, &twoStdTime);
      }
    }

  return STDTIME_ERR;

  } /* CompareStdTimeHexStrA */

/*-***************************************************************************/
/*            CompareStdTimeHexStrW                                          */
/*  compare two STDTIME_HEXSTRW values and return a strcmp-like result       */
/*****************************************************************************/

int32_t                     CompareStdTimeHexStrW (
  const STDTIME_HEXSTRW *   /*I*/ pStdTimeHexStrOne,
  const STDTIME_HEXSTRW *   /*I*/ pStdTimeHexStrTwo)
  {
  STDTIME                   oneStdTime;
  STDTIME                   twoStdTime;

  if (StdTimeHexStrWToStdTime (pStdTimeHexStrOne, &oneStdTime) == STDTIME_OK)
    {
    if (StdTimeHexStrWToStdTime (pStdTimeHexStrTwo, &twoStdTime) == STDTIME_OK)
      {
      return CompareStdTime (&oneStdTime, &twoStdTime);
      }
    }

  return STDTIME_ERR;

  } /* CompareStdTimeHexStrW */


/*** FileTime functions ******************************************************/


/*-***************************************************************************/
/*            StdTimeToFileTime                                              */
/*  convert: StdTime structure to FILETIME structure                         */
/*****************************************************************************/

STDTIME_RC                  StdTimeToFileTime (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_FILETIME *    /*O*/ pFileTime)
  {
  STDTIME_ENUM_FUNC (StdTimeToFileTime)

  if (pFileTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pFileTime = StdTimeApiZeroFileTime();

  if (pStdTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IFNOT (ValidStdTime (pStdTime))
    {
    STDTIME_RET_RC;
    }

  /* StdTime and FILETIME have the following structure */

  /*  StdTime:   7FFFFFFF 7FFFFFFF  */
  /*  FILETIME:  3FFFFFFF FFFFFFFF  */

  pFileTime->dwLowDateTime = pStdTime->lo & 0x7FFFFFFF;

  if (pStdTime->hi & 1)
    {
    pFileTime->dwLowDateTime |= 0x80000000;
    }

  pFileTime->dwHighDateTime = ((pStdTime->hi) >> 1) & 0x3FFFFFFF;

  STDTIME_RET_OK;

  } /* StdTimeToFileTime */


/*-***************************************************************************/
/*            FileTimeToStdTime                                              */
/*  convert: FILETIME structure to StdTime structure                         */
/*****************************************************************************/

STDTIME_RC                  FileTimeToStdTime (
  const STDTIME_WIN_FILETIME * /*I*/ pFileTime,
  STDTIME *                    /*O*/ pStdTime)
  {
  STDTIME_ENUM_FUNC (FileTimeToStdTime)

  if (pStdTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTime = ZeroStdTime ();

  if (pFileTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if (pFileTime->dwHighDateTime > 0x3FFFFFFF)
    {
    STDTIME_RET_EC (invalid_FileTime);
    }

  /* StdTime and FILETIME have the following structure */

  /*  StdTime:   7FFFFFFF 7FFFFFFF  */
  /*  FILETIME:  3FFFFFFF FFFFFFFF  */

  pStdTime->lo = (pFileTime->dwLowDateTime) & 0x7FFFFFFF;
  pStdTime->hi = ((pFileTime->dwHighDateTime) << 1) & 0x7FFFFFFF;

  if ((pFileTime->dwLowDateTime) & 0x80000000)
    {
    pStdTime->hi |= 1;
    }

  STDTIME_RET_OK;

  } /* FileTimeToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToFileTime                                        */
/*  convert: StdTimeFields structure to FILETIME structure                   */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToFileTime (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_FILETIME *    /*O*/ pFileTime)
  {
  STDTIME_WIN_SYSTEMTIME        st;
  STDTIME_WIN_FILETIME          ft;
  QUADLIB_U64                   qFileTime;
  int32_t                       omit = 0;
  uint32_t                      incr32;

  STDTIME_ENUM_FUNC (StdTimeFieldsToFileTime)

  if (pFileTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pFileTime = StdTimeApiZeroFileTime();

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  /* the 'omit' argument is like NULL, but suppressing rounding */

  if STDTIME_IFNOT (StdTimeFieldsToSystemTimeEx (
       pStdTimeFields, &st, &omit, &omit))
    {
    STDTIME_RET_RC;
    }

  if (! STDTIME_API_SYSTEMTIMETOFILETIME (&st, &ft))
    {
    STDTIME_RET_EC (failure_in_api_SystemTimeToSystemTime);
    }

  /* SYSTEMTIME does not have usec and nsec, so add them to FILETIME */

  QUADLIB_U64_HI (qFileTime) = ft.dwHighDateTime;
  QUADLIB_U64_LO (qFileTime) = ft.dwLowDateTime;

  incr32 = (uint32_t) (pStdTimeFields->usec * STDTIME_PREC_NSEC)
         + (uint32_t) (pStdTimeFields->nsec / STDTIME_SCALE_NSEC);

  QUADLIB_U64_ADD_EQ (qFileTime, QUADLIB_U64_CASTU32 (incr32));

  pFileTime->dwHighDateTime = QUADLIB_U64_HI (qFileTime);
  pFileTime->dwLowDateTime  = QUADLIB_U64_LO (qFileTime);

  STDTIME_RET_OK;

  } /* StdTimeFieldsToFileTime */

/*-***************************************************************************/
/*            FileTimeToStdTimeFields                                        */
/*  convert: FILETIME structure to StdTimeFields structure                   */
/*****************************************************************************/

STDTIME_RC                  FileTimeToStdTimeFields (
  const STDTIME_WIN_FILETIME *  /*I*/ pFileTime,
  STDTIME_FIELDS *              /*O*/ pStdTimeFields)
  {
  STDTIME_WIN_SYSTEMTIME    st;
  int32_t                   usec;
  int32_t                   nsec;

  STDTIME_ENUM_FUNC (FileTimeToStdTimeFields)

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeFields = ZeroStdTimeFields ();

  if (pFileTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IFNOT (Rc_StdTime_FileTimeToSystemTimeEx (
       pFileTime, &st, &usec, &nsec))
    {
    STDTIME_RET_RC;
    }

  STDTIME_RET (SystemTimeExToStdTimeFields (&st, usec, nsec, pStdTimeFields));

  } /* FileTimeToStdTimeFields */


/*-***************************************************************************/
/*            StdTimeHexStrAToFileTime                                       */
/*****************************************************************************/

STDTIME_RC                  StdTimeHexStrAToFileTime (
  const STDTIME_HEXSTRA *   /*I*/ pStdTimeHexStr,
  STDTIME_WIN_FILETIME *    /*O*/ pFileTime)
  {
  STDTIME                   t;

  STDTIME_ENUM_FUNC (StdTimeHexStrAToFileTime)

  if (pFileTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pFileTime = StdTimeApiZeroFileTime();

  if (pStdTimeHexStr == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeHexStrAToStdTime (pStdTimeHexStr, &t))
    {
    STDTIME_RET (StdTimeToFileTime (&t, pFileTime));
    }

  STDTIME_RET_RC;

  } /* StdTimeHexStrAToFileTime */


/*-***************************************************************************/
/*            StdTimeHexStrWToFileTime                                       */
/*****************************************************************************/

STDTIME_RC                  StdTimeHexStrWToFileTime (
  const STDTIME_HEXSTRW *   /*I*/ pStdTimeHexStr,
  STDTIME_WIN_FILETIME *    /*O*/ pFileTime)
  {
  STDTIME                   t;

  STDTIME_ENUM_FUNC (StdTimeHexStrWToFileTime)

  if (pFileTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pFileTime = StdTimeApiZeroFileTime();

  if (pStdTimeHexStr == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeHexStrWToStdTime (pStdTimeHexStr, &t))
    {
    STDTIME_RET (StdTimeToFileTime (&t, pFileTime));
    }

  STDTIME_RET_RC;

  } /* StdTimeHexStrWToFileTime */


/*-***************************************************************************/
/*            FileTimeToStdTimeHexStrA                                       */
/*****************************************************************************/

STDTIME_RC                  FileTimeToStdTimeHexStrA (
  const STDTIME_WIN_FILETIME *  /*I*/ pFileTime,
  STDTIME_HEXSTRA *             /*O*/ pStdTimeHexStr)
  {
  STDTIME                   t;

  STDTIME_ENUM_FUNC (FileTimeToStdTimeHexStrA)

  if (pStdTimeHexStr == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeHexStr = ZeroStdTimeHexStrA ();

  if (pFileTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (FileTimeToStdTime (pFileTime, &t))
    {
    STDTIME_RET (StdTimeToStdTimeHexStrA (&t, pStdTimeHexStr));
    }

  STDTIME_RET_RC;

  } /* FileTimeToStdTimeHexStrA */


/*-***************************************************************************/
/*            FileTimeToStdTimeHexStrW                                       */
/*****************************************************************************/

STDTIME_RC                  FileTimeToStdTimeHexStrW (
  const STDTIME_WIN_FILETIME *  /*I*/ pFileTime,
  STDTIME_HEXSTRW *             /*O*/ pStdTimeHexStr)
  {
  STDTIME                   t;

  STDTIME_ENUM_FUNC (FileTimeToStdTimeHexStrW)

  if (pStdTimeHexStr == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeHexStr = ZeroStdTimeHexStrW ();

  if (pFileTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (FileTimeToStdTime (pFileTime, &t))
    {
    STDTIME_RET (StdTimeToStdTimeHexStrW (&t, pStdTimeHexStr));
    }

  STDTIME_RET_RC;

  } /* FileTimeToStdTimeHexStrW */


/*** SystemTimeEx functions **************************************************/

/*-***************************************************************************/
/*            StdTimeToSystemTimeEx                                          */
/*  convert: StdTime structure to SYSTEMTIME and extra fields                */
/*  method: StdTime -> FILETIME -> StdTimeFields                             */
/*****************************************************************************/

STDTIME_RC                  StdTimeToSystemTimeEx (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_SYSTEMTIME *  /*O*/ pSystemTime,
  int32_t *                 /*O*/ pUsec,
  int32_t *                 /*O*/ pNsec)
  {
  STDTIME_WIN_FILETIME      ft;

  STDTIME_ENUM_FUNC (StdTimeToSystemTimeEx)

  if (pSystemTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pSystemTime = StdTimeApiZeroSystemTime();

  if STDTIME_IF (StdTimeToFileTime (pStdTime, &ft))
    {
    STDTIME_RET (Rc_StdTime_FileTimeToSystemTimeEx (
      &ft, pSystemTime, pUsec, pNsec));
    }

  STDTIME_RET_RC;

  } /* StdTimeToSystemTimeEx */

/*-***************************************************************************/
/*            SystemTimeExToStdTime                                          */
/*  convert: SYSTEMTIME and extra fields to StdTime structure                */
/*  method:  SYSTEMTIME, fields -> FILETIME -> StdTime                       */
/*****************************************************************************/

STDTIME_RC                  SystemTimeExToStdTime (
  const STDTIME_WIN_SYSTEMTIME * /*I*/ pSystemTime,
  int32_t                        /*I*/ nUsec,
  int32_t                        /*I*/ nNsec,
  STDTIME *                      /*O*/ pStdTime)
  {
  STDTIME_WIN_FILETIME      ft;

  STDTIME_ENUM_FUNC (SystemTimeExToStdTime)

  if (pStdTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTime = ZeroStdTime ();

  if STDTIME_IF (Rc_StdTime_SystemTimeExToFileTime (
       pSystemTime, nUsec, nNsec, &ft))
    {
    STDTIME_RET (FileTimeToStdTime (&ft, pStdTime));
    }

  STDTIME_RET_RC;

  } /* SystemTimeExToStdTime */

/*-***************************************************************************/
/*            StdTimeFieldsToSystemTimeEx                                    */
/*  convert: StdTimeFields structure to SYSTEMTIME and extra fields          */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToSystemTimeEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_SYSTEMTIME *  /*O*/ pSystemTime,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  int32_t                   wday;
  int32_t                   msec;
  int32_t                   usec;
  int32_t                   nsec;

  STDTIME_ENUM_FUNC (StdTimeFieldsToSystemTimeEx)

  if (pSystemTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pSystemTime = StdTimeApiZeroSystemTime();

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IFNOT (ValidStdTimeFields (pStdTimeFields))
    {
    STDTIME_RET_RC;
    }

  pSystemTime->wYear         = (STDTIME_WIN_WORD) pStdTimeFields->year;
  pSystemTime->wMonth        = (STDTIME_WIN_WORD) pStdTimeFields->mon;
  pSystemTime->wDay          = (STDTIME_WIN_WORD) pStdTimeFields->day;
  pSystemTime->wHour         = (STDTIME_WIN_WORD) pStdTimeFields->hour;
  pSystemTime->wMinute       = (STDTIME_WIN_WORD) pStdTimeFields->min;
  pSystemTime->wSecond       = (STDTIME_WIN_WORD) pStdTimeFields->sec;

  nsec = pStdTimeFields->nsec;
  usec = pStdTimeFields->usec;
  msec = pStdTimeFields->msec;

  PVT_STDTIME_ROUND (pNsec, nsec, usec)
  PVT_STDTIME_ROUND (pUsec, usec, msec)

  pSystemTime->wMilliseconds = (STDTIME_WIN_WORD) msec;

  Rc_StdTime_NormalizeSystemTimeEx (pSystemTime, pNsec, pUsec);

  /* generate wDayOfWeek value */

  /* a conversion to FILETIME and back to SYSTEM could do this */
  /* but that is a lot of overhead for one field */
  /* the 'yday' value, stored in a struct tm, is not contained in */
  /* a SYSTEMTIME struct, so we discard its value with the NULL parm */

  if STDTIME_IFNOT (StdTimeW32GetDayofWeekAndYear (
       pStdTimeFields->year,
       pStdTimeFields->mon,
       pStdTimeFields->day,
       &wday, NULL))
    {
    STDTIME_RET_EC (failure_in_api_StdTimeW32GetDayofWeekAndYear);
    }

  pSystemTime->wDayOfWeek = (STDTIME_WIN_WORD) wday;

  STDTIME_RET_OK;

  } /* StdTimeFieldsToSystemTimeEx */

/*-***************************************************************************/
/*            SystemTimeExToStdTimeFields                                    */
/*  convert: SYSTEMTIME and extra fields to StdTimeFields structure          */
/*****************************************************************************/

STDTIME_RC                  SystemTimeExToStdTimeFields (
  const STDTIME_WIN_SYSTEMTIME * /*I*/ pSystemTime,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_ENUM_FUNC (SystemTimeExToStdTimeFields)

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeFields = ZeroStdTimeFields ();

  if (pSystemTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  pStdTimeFields->year = pSystemTime->wYear;
  pStdTimeFields->mon  = pSystemTime->wMonth;
  pStdTimeFields->day  = pSystemTime->wDay;

  pStdTimeFields->hour = pSystemTime->wHour;
  pStdTimeFields->min  = pSystemTime->wMinute;
  pStdTimeFields->sec  = pSystemTime->wSecond;

  pStdTimeFields->msec = pSystemTime->wMilliseconds;
  pStdTimeFields->usec = 0;
  pStdTimeFields->nsec = 0;

  STDTIME_RET (StdTimeFields_AddFraction (pStdTimeFields, 0, nUsec, nNsec));

  } /* SystemTimeExToStdTimeFields */


/*** SystemTime functions ****************************************************/

/*-***************************************************************************/
/*            StdTimeToSystemTime                                            */
/*  convert: StdTime structure to SYSTEMTIME (without extra fields)          */
/*****************************************************************************/

STDTIME_RC                  StdTimeToSystemTime (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_SYSTEMTIME *  /*O*/ pSystemTime)
  {
  STDTIME_ENUM_FUNC (StdTimeToSystemTime)

  STDTIME_RET (StdTimeToSystemTimeEx (pStdTime, pSystemTime, NULL, NULL));

  } /* StdTimeToSystemTime */

/*-***************************************************************************/
/*            SystemTimeToStdTime                                            */
/*  convert: SYSTEMTIME (without extra fields) to StdTime structure          */
/*****************************************************************************/

STDTIME_RC                  SystemTimeToStdTime (
  const STDTIME_WIN_SYSTEMTIME * /*I*/ pSystemTime,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_ENUM_FUNC (SystemTimeToStdTime)

  STDTIME_RET (SystemTimeExToStdTime (pSystemTime, 0, 0, pStdTime));

  } /* SystemTimeToStdTime */

/*-***************************************************************************/
/*            StdTimeFieldsToSystemTime                                      */
/*  convert: StdTimeFields structure to SYSTEMTIME (without extra fields)    */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToSystemTime (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_SYSTEMTIME *  /*O*/ pSystemTime)
  {
  STDTIME_ENUM_FUNC (StdTimeFieldsToSystemTime)

  STDTIME_RET (StdTimeFieldsToSystemTimeEx (
    pStdTimeFields, pSystemTime, NULL, NULL));

  } /* StdTimeFieldsToSystemTime */

/*-***************************************************************************/
/*            SystemTimeToStdTimeFields                                      */
/*  convert: SYSTEMTIME (without extra fields) to StdTimeFields structure    */
/*****************************************************************************/

STDTIME_RC                  SystemTimeToStdTimeFields (
  const STDTIME_WIN_SYSTEMTIME * /*I*/ pSystemTime,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_ENUM_FUNC (SystemTimeToStdTimeFields)

  STDTIME_RET (SystemTimeExToStdTimeFields (pSystemTime, 0, 0, pStdTimeFields));

  } /* SystemTimeToStdTimeFields */


/*** UdateEx functions *******************************************************/

/*-***************************************************************************/
/*            StdTimeToUdateEx                                               */
/*  convert: StdTime structure to UDATE and extra fields                     */
/*****************************************************************************/

STDTIME_RC                  StdTimeToUdateEx (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_UDATE *       /*O*/ pUdate,
  int32_t *                 /*O*/ pUsec,
  int32_t *                 /*O*/ pNsec)
  {
  STDTIME_FIELDS            stdTimeFields;

  STDTIME_ENUM_FUNC (StdTimeToUdateEx)

  if (pUdate == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pUdate = StdTimeApiZeroUdate();

  if STDTIME_IF (StdTimeToStdTimeFields (pStdTime, &stdTimeFields))
    {
    STDTIME_RET (StdTimeFieldsToUdateEx (
      &stdTimeFields, pUdate, pUsec, pNsec));
    }

  STDTIME_RET_RC;

  } /* StdTimeToUdateEx */


/*-***************************************************************************/
/*            UdateExToStdTime                                               */
/*  convert: UDATE and extra fields to StdTime structure                     */
/*****************************************************************************/

STDTIME_RC                  UdateExToStdTime (
  const STDTIME_WIN_UDATE *      /*I*/ pUdate,
  int32_t                        /*I*/ nUsec,
  int32_t                        /*I*/ nNsec,
  STDTIME *                      /*O*/ pStdTime)
  {
  STDTIME_ENUM_FUNC (UdateExToStdTime)

  if (pStdTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  /* convert SYSTEMTIME portion of UDATE, ignoring wDayOfYear field */

  STDTIME_RET (SystemTimeExToStdTime (&(pUdate->st), nUsec, nNsec, pStdTime));

  } /* UdateExToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToUdateEx                                         */
/*  convert: StdTimeFields structure to UDATE and extra fields               */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToUdateEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_UDATE *       /*O*/ pUdate,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  int32_t                   wday;
  int32_t                   yday;
  int32_t                   msec;
  int32_t                   usec;
  int32_t                   nsec;

  STDTIME_ENUM_FUNC (StdTimeFieldsToUdateEx)

  if (pUdate == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pUdate = StdTimeApiZeroUdate();

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IFNOT (ValidStdTimeFields (pStdTimeFields))
    {
    STDTIME_RET_RC;
    }

  pUdate->st.wYear         = (STDTIME_WIN_WORD) pStdTimeFields->year;
  pUdate->st.wMonth        = (STDTIME_WIN_WORD) pStdTimeFields->mon;
  pUdate->st.wDay          = (STDTIME_WIN_WORD) pStdTimeFields->day;
  pUdate->st.wHour         = (STDTIME_WIN_WORD) pStdTimeFields->hour;
  pUdate->st.wMinute       = (STDTIME_WIN_WORD) pStdTimeFields->min;
  pUdate->st.wSecond       = (STDTIME_WIN_WORD) pStdTimeFields->sec;

  nsec = pStdTimeFields->nsec;
  usec = pStdTimeFields->usec;
  msec = pStdTimeFields->msec;

  PVT_STDTIME_ROUND (pNsec, nsec, usec)
  PVT_STDTIME_ROUND (pUsec, usec, msec)

  pUdate->st.wMilliseconds = (STDTIME_WIN_WORD) msec;

  Rc_StdTime_NormalizeSystemTimeEx (&(pUdate->st), pUsec, pNsec);

  /* generate st.wDayOfWeek and wDayOfYear values */

  if STDTIME_IFNOT (StdTimeW32GetDayofWeekAndYear (
       pStdTimeFields->year,
       pStdTimeFields->mon,
       pStdTimeFields->day,
       &wday, &yday))
    {
    STDTIME_RET_EC (failure_in_api_StdTimeW32GetDayofWeekAndYear);
    }

  pUdate->st.wDayOfWeek = (STDTIME_WIN_WORD)   wday;
  pUdate->wDayOfYear    = (STDTIME_WIN_USHORT) yday;

  STDTIME_RET_OK;

  } /* StdTimeFieldsToUdateEx */


/*-***************************************************************************/
/*            UdateExToStdTimeFields                                         */
/*  convert: UDATE and extra fields to StdTimeFields structure               */
/*****************************************************************************/

STDTIME_RC                  UdateExToStdTimeFields (
  const STDTIME_WIN_UDATE * /*I*/ pUdate,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_ENUM_FUNC (UdateExToStdTimeFields)

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  /* convert SYSTEMTIME portion of UDATE, ignoring wDayOfYear field */

  STDTIME_RET (SystemTimeExToStdTimeFields (
    &(pUdate->st), nUsec, nNsec, pStdTimeFields));

  } /* UdateExToStdTimeFields */


/*** Udate functions *********************************************************/


/*-***************************************************************************/
/*            StdTimeToUdate                                                 */
/*  convert: StdTime structure to UDATE (without extra fields)               */
/*****************************************************************************/

STDTIME_RC                  StdTimeToUdate (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_UDATE *       /*O*/ pUdate)
  {
  STDTIME_ENUM_FUNC (StdTimeToUdate)

  STDTIME_RET (StdTimeToUdateEx (pStdTime, pUdate, NULL, NULL));

  } /* StdTimeToUdate */

/*-***************************************************************************/
/*            UdateToStdTime                                                 */
/*  convert: UDATE (without extra fields) to StdTime structure               */
/*****************************************************************************/

STDTIME_RC                  UdateToStdTime (
  const STDTIME_WIN_UDATE * /*I*/ pUdate,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_ENUM_FUNC (UdateToStdTime)

  STDTIME_RET (UdateExToStdTime (pUdate, 0, 0, pStdTime));

  } /* UdateToStdTime */

/*-***************************************************************************/
/*            StdTimeFieldsToUdate                                           */
/*  convert: StdTimeFields structure to UDATE (without extra fields)         */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToUdate (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_UDATE *       /*O*/ pUdate)
  {
  STDTIME_ENUM_FUNC (StdTimeFieldsToUdate)

  STDTIME_RET (StdTimeFieldsToUdateEx (
    pStdTimeFields, pUdate, NULL, NULL));

  } /* StdTimeFieldsToUdate */

/*-***************************************************************************/
/*            UdateToStdTimeFields                                           */
/*  convert: UDATE (without extra fields) to StdTimeFields structure         */
/*****************************************************************************/

STDTIME_RC                  UdateToStdTimeFields (
  const STDTIME_WIN_UDATE * /*I*/ pUdate,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_ENUM_FUNC (UdateToStdTimeFields)

  STDTIME_RET (UdateExToStdTimeFields (pUdate, 0, 0, pStdTimeFields));

  } /* UdateToStdTimeFields */




/*** DbTimeStamp functions ***************************************************/

/*-***************************************************************************/
/*            StdTimeToDbTimeStamp                                           */
/*  convert: StdTime structure to DBTIMESTAMP                                */
/*****************************************************************************/

STDTIME_RC                  StdTimeToDbTimeStamp (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_DBTIMESTAMP * /*O*/ pDbTimeStamp)
  {
  STDTIME_FIELDS            stdTimeFields;

  STDTIME_ENUM_FUNC (StdTimeToDbTimeStamp)

  if (pDbTimeStamp == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pDbTimeStamp = StdTimeApiZeroDbTimeStamp();

  if STDTIME_IF (StdTimeToStdTimeFields (pStdTime, &stdTimeFields))
    {
    STDTIME_RET (StdTimeFieldsToDbTimeStamp (&stdTimeFields, pDbTimeStamp));
    }

  STDTIME_RET_RC;

  } /* StdTimeToDbTimeStamp */


/*-***************************************************************************/
/*            DbTimeStampToStdTime                                           */
/*  convert: DBTIMESTAMP to StdTime structure                                */
/*****************************************************************************/

STDTIME_RC                  DbTimeStampToStdTime (
  const STDTIME_WIN_DBTIMESTAMP * /*I*/ pDbTimeStamp,
  STDTIME *                      /*O*/ pStdTime)
  {
  STDTIME_FIELDS            stdTimeFields;

  STDTIME_ENUM_FUNC (DbTimeStampToStdTime)

  if (pStdTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTime = ZeroStdTime ();

  if STDTIME_IF (DbTimeStampToStdTimeFields (pDbTimeStamp, &stdTimeFields))
    {
    STDTIME_RET (StdTimeFieldsToStdTime (&stdTimeFields, pStdTime));
    }

  STDTIME_RET_RC;

  } /* DbTimeStampToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToDbTimeStamp                                     */
/*  convert: StdTimeFields structure to DBTIMESTAMP                          */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToDbTimeStamp (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_DBTIMESTAMP * /*O*/ pDbTimeStamp)
  {
  STDTIME_ENUM_FUNC (StdTimeFieldsToDbTimeStamp)

  if (pDbTimeStamp == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pDbTimeStamp = StdTimeApiZeroDbTimeStamp();

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IFNOT (ValidStdTimeFields (pStdTimeFields))
    {
    STDTIME_RET_RC;
    }

  pDbTimeStamp->year   = (STDTIME_WIN_SHORT)  pStdTimeFields->year;
  pDbTimeStamp->month  = (STDTIME_WIN_USHORT) pStdTimeFields->mon;
  pDbTimeStamp->day    = (STDTIME_WIN_USHORT) pStdTimeFields->day;
  pDbTimeStamp->hour   = (STDTIME_WIN_USHORT) pStdTimeFields->hour;
  pDbTimeStamp->minute = (STDTIME_WIN_USHORT) pStdTimeFields->min;
  pDbTimeStamp->second = (STDTIME_WIN_USHORT) pStdTimeFields->sec;

  /* a DBTIMESTAMP fraction is a number of nanoseconds, 0 to 999,999,999 */

  pDbTimeStamp->fraction     = (STDTIME_WIN_ULONG)
    (pStdTimeFields->msec * 1000000) +
    (pStdTimeFields->usec * 1000) +
    (pStdTimeFields->nsec);

  STDTIME_RET_OK;

  } /* StdTimeFieldsToDbTimeStamp */


/*-***************************************************************************/
/*            DbTimeStampToStdTimeFields                                     */
/*  convert: DBTIMESTAMP to StdTimeFields structure                          */
/*****************************************************************************/

STDTIME_RC                  DbTimeStampToStdTimeFields (
  const STDTIME_WIN_DBTIMESTAMP * /*I*/ pDbTimeStamp,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  int32_t                   fraction;

  STDTIME_ENUM_FUNC (DbTimeStampToStdTimeFields)

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeFields = ZeroStdTimeFields ();

  if (pDbTimeStamp == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  pStdTimeFields->year = (int32_t) pDbTimeStamp->year;
  pStdTimeFields->mon  = (int32_t) pDbTimeStamp->month;
  pStdTimeFields->day  = (int32_t) pDbTimeStamp->day;

  pStdTimeFields->hour = (int32_t) pDbTimeStamp->hour;
  pStdTimeFields->min  = (int32_t) pDbTimeStamp->minute;
  pStdTimeFields->sec  = (int32_t) pDbTimeStamp->second;

  fraction = (int32_t) pDbTimeStamp->fraction;

  /* limit fraction to valid range */

  if (fraction < 0)
    {
    fraction = 0;
    }

  else if (fraction > 999999999)
    {
    fraction = 999999999;
    }

  pStdTimeFields->msec = (fraction / 1000000) % 1000;
  pStdTimeFields->usec = (fraction / 1000) % 1000;
  pStdTimeFields->nsec = (fraction % 1000);

  STDTIME_RET_OK;

  } /* DbTimeStampToStdTimeFields */


/*** StructTmEx functions ****************************************************/

/*-***************************************************************************/
/*            StdTimeToStructTmEx                                            */
/*  convert: StdTime structure to 'struct tm' and extra fields               */
/*****************************************************************************/

STDTIME_RC                  StdTimeToStructTmEx (
  const STDTIME *           /*I*/ pStdTime,
  struct tm *               /*O*/ pStructTm,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME_FIELDS            f;

  STDTIME_ENUM_FUNC (StdTimeToStructTmEx)

  /* convert StdTime to StdTimeFields, then convert fields to struct tm */

  if STDTIME_IF (StdTimeToStdTimeFields (pStdTime, &f))
    {
    STDTIME_RET (StdTimeFieldsToStructTmEx (
      &f, pStructTm, pMsec, pUsec, pNsec));
    }

  STDTIME_RET_RC;

  } /* StdTimeToStructTmEx */

/*-***************************************************************************/
/*            StructTmExToStdTime                                            */
/*  convert: 'struct tm' and extra fields to StdTime structure               */
/*****************************************************************************/

STDTIME_RC                  StructTmExToStdTime (
  const struct tm *         /*I*/ pStructTm,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_FIELDS            f;

  STDTIME_ENUM_FUNC (StructTmExToStdTime)

  /* convert struct tm to time fields, then convert fields to StdTime */

  if STDTIME_IF (StructTmExToStdTimeFields (pStructTm, nMsec, nUsec, nNsec, &f))
    {
    STDTIME_RET (StdTimeFieldsToStdTime (&f, pStdTime));
    }

  STDTIME_RET_RC;

  } /* StructTmExToStdTime */

/*-***************************************************************************/
/*            StdTimeFieldsToStructTmEx                                      */
/*  convert: StdTimeFields structure to 'struct tm' and extra fields         */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToStructTmEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  struct tm *               /*O*/ pStructTm,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  int32_t                   wday = 0;
  int32_t                   yday = 0;
  int32_t                   sec;
  int32_t                   msec;
  int32_t                   usec;
  int32_t                   nsec;

  STDTIME_ENUM_FUNC (StdTimeFieldsToStructTmEx)

  if (pStructTm == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStructTm = StdTimeApiZeroStructTm();

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IFNOT (ValidStdTimeFields (pStdTimeFields))
    {
    STDTIME_RET_RC;
    }

  /* the base value of tm_year is defined as an offset from 1900 */
  /* however, there is no restriction on having negative tm_year */
  /* values.  so, no further range limits are applied here */

  pStructTm->tm_year  = pStdTimeFields->year - 1900;
  pStructTm->tm_mon   = pStdTimeFields->mon - 1;
  pStructTm->tm_mday  = pStdTimeFields->day;
  pStructTm->tm_hour  = pStdTimeFields->hour;
  pStructTm->tm_min   = pStdTimeFields->min;

  nsec = pStdTimeFields->nsec;
  usec = pStdTimeFields->usec;
  msec = pStdTimeFields->msec;
  sec =  pStdTimeFields->sec;

  PVT_STDTIME_ROUND (pNsec, nsec, usec)
  PVT_STDTIME_ROUND (pUsec, usec, msec)
  PVT_STDTIME_ROUND (pMsec, msec, sec)

  pStructTm->tm_sec = sec;

  Rc_StdTime_NormalizeStructTmEx (pStructTm, pMsec, pUsec, pNsec);

  /* set tm_isdst to default value, which should be 0, 1 or -1 */

#ifdef STDTIME_TM_ISDST_DEFAULT
  pStructTm->tm_isdst = (STDTIME_TM_ISDST_DEFAULT);
#else
  pStructTm->tm_isdst = 0;
#endif

  /* tm_wday and tm_yday values are generated */
  /* an API like mktime() could do this, but it has the Y2K38 bug */

  if STDTIME_IFNOT (StdTimeW32GetDayofWeekAndYear (
       pStdTimeFields->year,
       pStdTimeFields->mon,
       pStdTimeFields->day,
       &wday, &yday))
    {
    STDTIME_RET_EC (failure_in_api_StdTimeW32GetDayofWeekAndYear);
    }

  pStructTm->tm_wday  = wday;
  pStructTm->tm_yday  = yday;

  STDTIME_RET_OK;

  } /* StdTimeFieldsToStructTmEx */

/*-***************************************************************************/
/*            StructTmExToStdTimeFields                                      */
/*  convert: 'struct tm' and extra fields to StdTimeFields structure         */
/*****************************************************************************/

STDTIME_RC                  StructTmExToStdTimeFields (
  const struct tm *         /*I*/ pStructTm,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_DELTA             delta = {0};

  STDTIME_ENUM_FUNC (StructTmExToStdTimeFields)

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeFields = ZeroStdTimeFields ();

  if (pStructTm == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  /* create a DELTA from the 'extra' fields */

  delta.msec = nMsec;
  delta.usec = nUsec;
  delta.nsec = nNsec;

  /* pStructTm->tm_isdst unused */
  /* pStructTm->tm_wday  unused */
  /* pStructTm->tm_yday  unused */

  pStdTimeFields->year = pStructTm->tm_year + 1900;
  pStdTimeFields->mon  = pStructTm->tm_mon  + 1;
  pStdTimeFields->day  = pStructTm->tm_mday;
  pStdTimeFields->hour = pStructTm->tm_hour;
  pStdTimeFields->min  = pStructTm->tm_min;
  pStdTimeFields->sec  = pStructTm->tm_sec;

  pStdTimeFields->msec = 0;
  pStdTimeFields->usec = 0;
  pStdTimeFields->nsec = 0;

  STDTIME_RET (StdTimeFields_AddDelta (pStdTimeFields, &delta));

  } /* StructTmExToStdTimeFields */


/*** StructTm functions ******************************************************/

/*-***************************************************************************/
/*            StdTimeToStructTm                                              */
/*  convert: StdTime structure to 'struct tm' (without extra fields)         */
/*****************************************************************************/

STDTIME_RC                  StdTimeToStructTm (
  const STDTIME *           /*I*/ pStdTime,
  struct tm *               /*O*/ pStructTm)
  {
  STDTIME_ENUM_FUNC (StdTimeToStructTm)

  STDTIME_RET (StdTimeToStructTmEx (pStdTime, pStructTm, NULL, NULL, NULL));

  } /* StdTimeToStructTm */

/*-***************************************************************************/
/*            StructTmToStdTime                                              */
/*  convert: 'struct tm' (without extra fields) to StdTime structure         */
/*****************************************************************************/

STDTIME_RC                  StructTmToStdTime (
  const struct tm *         /*I*/ pStructTm,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_ENUM_FUNC (StructTmToStdTime)

  STDTIME_RET (StructTmExToStdTime (pStructTm, 0, 0, 0, pStdTime));

  } /* StructTmToStdTime */

/*-***************************************************************************/
/*            StdTimeFieldsToStructTm                                        */
/*  convert: StdTimeFields structure to 'struct tm' (without extra fields)   */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToStructTm (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  struct tm *               /*O*/ pStructTm)
  {
  STDTIME_ENUM_FUNC (StdTimeFieldsToStructTm)

  STDTIME_RET (StdTimeFieldsToStructTmEx (
    pStdTimeFields, pStructTm, NULL, NULL, NULL));

  } /* StdTimeFieldsToStructTm */

/*-***************************************************************************/
/*            StructTmToStdTimeFields                                        */
/*  convert: 'struct tm' (without extra fields) to StdTimeFields structure   */
/*****************************************************************************/

STDTIME_RC                  StructTmToStdTimeFields (
  const struct tm *         /*I*/ pStructTm,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_ENUM_FUNC (StructTmToStdTimeFields)

  STDTIME_RET (StructTmExToStdTimeFields (pStructTm, 0, 0, 0, pStdTimeFields));

  } /* StructTmToStdTimeFields */


/*** TimeTypeEx functions ************************************************   */

/*-***************************************************************************/
/*            Rc_StdTime_TimeTypeToFileTime - PRIVATE FUNCTION               */
/*  convert: STDTIME_TIMETYPE structure to FILETIME, arithmetically          */
/*****************************************************************************/

static STDTIME_RC           Rc_StdTime_TimeTypeToFileTime (
  const STDTIME_TIMETYPE *  /*I*/ pTimeType,
  STDTIME_WIN_FILETIME *    /*O*/ pFileTime)
  {
  /* code adapted from MSDN KB Q167296 */

  QUADLIB_I64                qFileTime;
  QUADLIB_I64                qBase;
  QUADLIB_I64                qTimeType;

  STDTIME_ENUM_FUNC (Rc_StdTime_TimeTypeToFileTime)

  if (pFileTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pFileTime = StdTimeApiZeroFileTime();

  if (pTimeType == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

#ifdef STDTIME_TIME_T64_ENABLED
    QUADLIB_U64_HI(qTimeType) = QUADLIB_U64_HI(pTimeType->t);
    QUADLIB_U64_LO(qTimeType) = QUADLIB_U64_LO(pTimeType->t);
#else
    QUADLIB_U64_HI(qTimeType) = 0;
    QUADLIB_U64_LO(qTimeType) = (*(uint32_t *) (&(pTimeType->t)));
#endif

  qFileTime = QUADLIB_I64_MUL (
    qTimeType, QUADLIB_I64_CASTI32 (PVT_STDTIME_SCALE_FILETIME) );


  QUADLIB_I64_HI(qBase) = PVT_STDTIME_U32_TIMET_BASE_HI;
  QUADLIB_I64_LO(qBase) = PVT_STDTIME_U32_TIMET_BASE_LO;

  QUADLIB_I64_ADD_EQ (qFileTime, qBase);

  pFileTime->dwHighDateTime = QUADLIB_U64_HI(qFileTime);
  pFileTime->dwLowDateTime  = QUADLIB_U64_LO(qFileTime);

  STDTIME_RET_OK;

  } /* Rc_StdTime_TimeTypeToFileTime */

/*-***************************************************************************/
/*            StdTimeToTimeTypeEx                                            */
/*  convert: StdTime structure to STDTIME_TIMETYPE and extra fields          */
/*****************************************************************************/

STDTIME_RC                  StdTimeToTimeTypeEx (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_TIMETYPE *        /*O*/ pTimeType,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME_FIELDS            f;

  STDTIME_ENUM_FUNC (StdTimeToTimeTypeEx)

  /* convert StdTime to StdTimeFields, then convert to STDTIME_TIMETYPE */

  if STDTIME_IF (StdTimeToStdTimeFields (pStdTime, &f))
    {
    STDTIME_RET (StdTimeFieldsToTimeTypeEx (
      &f, pTimeType, pMsec, pUsec, pNsec));
    }

  STDTIME_RET_RC;

  } /* StdTimeToTimeTypeEx */


/*-***************************************************************************/
/*            StdTimeFieldsToTimeTypeEx                                      */
/*  convert: StdTimeFields structure to STDTIME_TIMETYPE and extra fields    */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToTimeTypeEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_TIMETYPE *        /*O*/ pTimeType,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME_WIN_FILETIME      ftUser;
  STDTIME_WIN_FILETIME      ftBase;
  QUADLIB_U64               qFileTime;
  STDTIME_WIN_TIME_T        baseTimeT;
  STDTIME_WIN_TIME_T        userTimeT;

  int32_t                   msec;
  int32_t                   usec;
  int32_t                   nsec;

#ifdef STDTIME_TIME_T64_ENABLED
  QUADLIB_U64               qValue;
#endif

  STDTIME_ENUM_FUNC (StdTimeFieldsToTimeTypeEx)

  /* it would be nice to have a mkgmtime(), but this is not portable */
  /* so, the STDTIME_FIELDS are converted to FILETIME, and then a */
  /* STDTIME_WIN_TIME_T is synthesized from FILETIME, based on the */
  /* epoch STDTIME_WIN_TIME_T value of January 1, 1970. */

  if (pTimeType == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pTimeType = StdTimeApiZeroTimeType();

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if (pStdTimeFields->year < STDTIME_UNIX_EPOCH_YEAR)
    {
    /* year is out of range */
    STDTIME_RET_EC (year_out_of_range);
    }

  if STDTIME_IFNOT (Rc_StdTime_TimeTBase (&ftBase))
    {
    STDTIME_RET_RC;
    }

  if STDTIME_IFNOT (StdTimeFieldsToFileTime (pStdTimeFields, &ftUser))
    {
    STDTIME_RET_RC;
    }

  QUADLIB_U64_HI(qFileTime) = ftUser.dwHighDateTime;
  QUADLIB_U64_LO(qFileTime) = ftUser.dwLowDateTime;

#ifdef STDTIME_TIME_T64_ENABLED
  qValue = QUADLIB_I64_DIV (
    qFileTime,
    QUADLIB_I64_CASTI32 (PVT_STDTIME_SCALE_FILETIME) );
  userTimeT = QUADLIB_I64N_CASTI64(qValue);

#else
  userTimeT = QUADLIB_I32_CASTI64 (
    QUADLIB_I64_DIV (
      qFileTime,
      QUADLIB_I64_CASTI32 (PVT_STDTIME_SCALE_FILETIME) ));
#endif


  QUADLIB_U64_HI(qFileTime) = ftBase.dwHighDateTime;
  QUADLIB_U64_LO(qFileTime) = ftBase.dwLowDateTime;


#ifdef STDTIME_TIME_T64_ENABLED
  qValue = QUADLIB_I64_DIV (
    qFileTime,
    QUADLIB_I64_CASTI32 (PVT_STDTIME_SCALE_FILETIME) );
  baseTimeT = QUADLIB_I64N_CASTI64(qValue);

#else
  baseTimeT = QUADLIB_I32_CASTI64 (
    QUADLIB_I64_DIV (
      qFileTime,
      QUADLIB_I64_CASTI32 (PVT_STDTIME_SCALE_FILETIME) ));
#endif

  pTimeType->t = (userTimeT - baseTimeT);

  nsec = pStdTimeFields->nsec;
  usec = pStdTimeFields->usec;
  msec = pStdTimeFields->msec;

  PVT_STDTIME_ROUND (pNsec, nsec, usec)
  PVT_STDTIME_ROUND (pUsec, usec, msec)

  /* if msec rounding is done, increment time_t value directly */
  /* since it is in units of seconds */

  PVT_STDTIME_ROUND (pMsec, msec, pTimeType->t)

  STDTIME_RET_OK;

  } /* StdTimeFieldsToTimeTypeEx */


/*-***************************************************************************/
/*            TimeTypeExToStdTime                                            */
/*  convert: STDTIME_TIMETYPE and extra fields to StdTime structure          */
/*****************************************************************************/

STDTIME_RC                  TimeTypeExToStdTime (
  const STDTIME_TIMETYPE *  /*I*/ pTimeType,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_WIN_FILETIME      ft;
  STDTIME_DELTA             delta = {0};

  STDTIME_ENUM_FUNC (TimeTypeExToStdTime)

  if (pStdTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTime = ZeroStdTime ();

  if (pTimeType == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  delta.msec = nMsec;
  delta.usec = nUsec;
  delta.nsec = nNsec;

  if STDTIME_IFNOT (Rc_StdTime_TimeTypeToFileTime (pTimeType, &ft))
    {
    STDTIME_RET_RC;
    }

  /* a time_t only has time down to seconds, so when it is converted */
  /* to FILETIME, the fractional seconds are all zero */

  if STDTIME_IFNOT (FileTimeToStdTime (&ft, pStdTime))
    {
    STDTIME_RET_RC;
    }

  STDTIME_RET (StdTime_AddDelta (pStdTime, &delta));

  } /* TimeTypeExToStdTime */


/*-***************************************************************************/
/*            TimeTypeExToStdTimeFields                                      */
/*  convert: STDTIME_TIMETYPE and extra fields to StdTimeFields structure    */
/*****************************************************************************/

STDTIME_RC                  TimeTypeExToStdTimeFields (
  const STDTIME_TIMETYPE *  /*I*/ pTimeType,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME                   stdTime;

  STDTIME_ENUM_FUNC (TimeTypeExToStdTimeFields)

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeFields = ZeroStdTimeFields ();

  if (pTimeType == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IFNOT (TimeTypeExToStdTime (
       pTimeType, nMsec, nUsec, nNsec, &stdTime))
    {
    STDTIME_RET_RC;
    }

  STDTIME_RET (StdTimeToStdTimeFields (&stdTime, pStdTimeFields));

  } /* TimeTypeExToStdTimeFields */


/*** TimeType functions **************************************************   */

/*-***************************************************************************/
/*            StdTimeToTimeType                                              */
/*  convert: StdTime struct to STDTIME_TIMETYPE (without extra fields)       */
/*****************************************************************************/

STDTIME_RC                  StdTimeToTimeType (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_TIMETYPE *        /*O*/ pTimeType)
  {
  STDTIME_ENUM_FUNC (StdTimeToTimeType)

  STDTIME_RET (StdTimeToTimeTypeEx (pStdTime, pTimeType, NULL, NULL, NULL));

  } /* StdTimeToTimeType */

/*-***************************************************************************/
/*            TimeTypeToStdTime                                              */
/*  convert: STDTIME_TIMETYPE (without extra fields) to StdTime struct       */
/*****************************************************************************/

STDTIME_RC                  TimeTypeToStdTime (
  const STDTIME_TIMETYPE *  /*I*/ pTimeType,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_ENUM_FUNC (TimeTypeToStdTime)

  STDTIME_RET (TimeTypeExToStdTime (pTimeType, 0, 0, 0, pStdTime));

  } /* TimeTypeToStdTime */

/*-***************************************************************************/
/*            StdTimeFieldsToTimeType                                        */
/*  convert: StdTimeFields struct to STDTIME_TIMETYPE (without extra fields) */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToTimeType (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_TIMETYPE *        /*O*/ pTimeType)
  {
  STDTIME_ENUM_FUNC (StdTimeFieldsToTimeType)

  STDTIME_RET (StdTimeFieldsToTimeTypeEx (
    pStdTimeFields, pTimeType, NULL, NULL, NULL));

  } /* StdTimeFieldsToTimeType */

/*-***************************************************************************/
/*            TimeTypeToStdTimeFields                                        */
/*  convert: STDTIME_TIMETYPE (without extra fields) to StdTimeFields struct */
/*****************************************************************************/

STDTIME_RC                  TimeTypeToStdTimeFields (
  const STDTIME_TIMETYPE *  /*I*/ pTimeType,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_ENUM_FUNC (TimeTypeToStdTimeFields)

  STDTIME_RET (TimeTypeExToStdTimeFields (pTimeType, 0, 0, 0, pStdTimeFields));

  } /* TimeTypeToStdTimeFields */


/*** Constructor-like functions **********************************************/


/*-***************************************************************************/
/*            StdTime                                                        */
/*  construct a STDTIME structure from parameters                            */
/*****************************************************************************/


STDTIME                     StdTime (
  int32_t                   /*I*/ hi,
  int32_t                   /*I*/ lo)
  {
  STDTIME                   x;

  x.hi = hi;
  x.lo = lo;

  return x;

  } /* StdTime */


/*-***************************************************************************/
/*            StdTimeFields                                                  */
/*  construct a STDTIME_FIELDS structure from parameters                     */
/*****************************************************************************/


STDTIME_FIELDS              StdTimeFields (
  int32_t                   /*I*/ year,
  int32_t                   /*I*/ mon,
  int32_t                   /*I*/ day,
  int32_t                   /*I*/ hour,
  int32_t                   /*I*/ min,
  int32_t                   /*I*/ sec,
  int32_t                   /*I*/ msec,
  int32_t                   /*I*/ usec,
  int32_t                   /*I*/ nsec)
  {
  STDTIME_FIELDS            x;

  x.year = year;
  x.mon  = mon;
  x.day  = day;
  x.hour = hour;
  x.min  = min;
  x.sec  = sec;
  x.msec = msec;
  x.usec = usec;
  x.nsec = nsec;

  return x;

  } /* StdTimeFields */


/*-***************************************************************************/
/*            StdTimeStringA                                                 */
/*  construct a STDTIME_STRINGA structure from parameters                    */
/*****************************************************************************/

STDTIME_STRINGA             StdTimeStringA (
  const char *              /*I*/ str)
  {
  STDTIME_STRINGA           x = {{0}};
  int32_t                   i;
  int32_t                   len;

  if (str == NULL)
    {
    len = 0;
    }

  else
    {
    len = (int32_t) strlen (str);
    }

  for (i=0; i < STDTIME_STRING_LEN; i++)
    {
    if (str == NULL)
      {
      x.str[i] = '0';
      }

    else
      {
      if (str[i] == 0)
        {
        x.str[i] = '0';
        str = NULL;         /* ignore remainder of string */
        }

      else
        {
        x.str[i] = str[i];
        }
      }
    } /* for */

  if (len > STDTIME_STRING_LEN)
    {
    strncpy (x.embTzo, str+STDTIME_STRING_LEN, STDTIME_TZO_LEN);
    x.embTzo[STDTIME_TZO_LEN] = 0;
    }

  else
    {
    x.embTzo[0] = 0;
    }

  RepairStdTimeStringA (&x);

  return x;

  } /* StdTimeStringA */


/*-***************************************************************************/
/*            StdTimeStringW                                                 */
/*  construct a STDTIME_STRINGW structure from parameters                    */
/*****************************************************************************/

STDTIME_STRINGW             StdTimeStringW (
  const STDTIME_WCHAR *     /*I*/ str)
  {
  STDTIME_STRINGW           x = {{0}};
  int32_t                   i;
  int32_t                   len;

  if (str == NULL)
    {
    len = 0;
    }

  else
    {
    len = Int_StdTime_StrlenW (str);
    }

  for (i=0; i < STDTIME_STRING_LEN; i++)
    {
    if (str == NULL)
      {
      x.str[i] = (STDTIME_WCHAR) '0';
      }

    else
      {
      if (str[i] == 0)
        {
        x.str[i] = (STDTIME_WCHAR) '0';
        str = NULL;         /* ignore remainder of string */
        }

      else
        {
        x.str[i] = str[i];
        }
      }
    } /* for */

  if (len > STDTIME_STRING_LEN)
    {
    Wchar_StdTime_StrncpyWW (x.embTzo, str+STDTIME_STRING_LEN, STDTIME_TZO_LEN);
    x.embTzo[STDTIME_TZO_LEN] = 0;
    }

  else
    {
    x.embTzo[0] = 0;
    }

  RepairStdTimeStringW (&x);

  return x;

  } /* StdTimeStringW */


/*-***************************************************************************/
/*            StdTimeHexStrA                                                 */
/*  construct a STDTIME_HEXSTRA structure from parameters                    */
/*****************************************************************************/


STDTIME_HEXSTRA             StdTimeHexStrA (
  const char *              /*I*/ str)
  {
  STDTIME_HEXSTRA           x;
  int32_t                   i;

  for (i=0; i < STDTIME_HEXSTR_LEN; i++)
    {
    if (str == NULL)
      {
      x.str[i] = '0';
      }

    else
      {
      if (str[i] == 0)
        {
        x.str[i] = '0';
        str = NULL;         /* ignore remainder of string */
        }

      else
        {
        x.str[i] = str[i];
        }
      }
    } /* for */

  x.str [STDTIME_HEXSTR_LEN] = 0;
  return x;

  } /* StdTimeHexStrA */


/*-***************************************************************************/
/*            StdTimeHexStrW                                                 */
/*  construct a STDTIME_HEXSTRW structure from parameters                    */
/*****************************************************************************/


STDTIME_HEXSTRW             StdTimeHexStrW (
  const STDTIME_WCHAR *     /*I*/ str)
  {
  STDTIME_HEXSTRW           x;
  int32_t                   i;

  for (i=0; i < STDTIME_HEXSTR_LEN; i++)
    {
    if (str == NULL)
      {
      x.str[i] = (STDTIME_WCHAR) '0';
      }

    else
      {
      if (str[i] == (STDTIME_WCHAR) 0)
        {
        x.str[i] = (STDTIME_WCHAR) '0';
        str = NULL;         /* ignore remainder of string */
        }

      else
        {
        x.str[i] = str[i];
        }
      }
    } /* for */

  x.str [STDTIME_HEXSTR_LEN] = (STDTIME_WCHAR) 0;
  return x;

  } /* StdTimeHexStrW */


/*-***************************************************************************/
/*            StdTimeDelta                                                   */
/*  construct a STDTIME_DELTA structure from parameters                      */
/*****************************************************************************/


STDTIME_DELTA               StdTimeDelta (
  int32_t                   /*I*/ day,
  int32_t                   /*I*/ hour,
  int32_t                   /*I*/ min,
  int32_t                   /*I*/ sec,
  int32_t                   /*I*/ msec,
  int32_t                   /*I*/ usec,
  int32_t                   /*I*/ nsec)
  {
  STDTIME_DELTA             x;

  x.day  = day;
  x.hour = hour;
  x.min  = min;
  x.sec  = sec;
  x.msec = msec;
  x.usec = usec;
  x.nsec = nsec;

  return x;

  } /* StdTimeDelta */


/*-***************************************************************************/
/*            StdTimeSpan                                                    */
/*  construct a STDTIME structure from parameters                            */
/*****************************************************************************/


STDTIME_SPAN                StdTimeSpan (
  QUADLIB_I64               /*I*/ value)
  {
  STDTIME_SPAN              x;

  x.value = value;

  return x;

  } /* StdTimeSpan */


/*** Initializer functions ***************************************************/


/*-***************************************************************************/
/*            ZeroStdTime                                                    */
/*  return a zero value of type STDTIME                                      */
/*****************************************************************************/

STDTIME                     ZeroStdTime ()
  {
  STDTIME                   zero = {0};

  return zero;

  } /* ZeroStdTime */


/*-***************************************************************************/
/*            ZeroStdTimeFields                                              */
/*  return a zero value of type STDTIME_FIELDS                               */
/*****************************************************************************/

STDTIME_FIELDS              ZeroStdTimeFields ()
  {
  STDTIME_FIELDS            zero = {0};

  return zero;

  } /* ZeroStdTimeFields */


/*-***************************************************************************/
/*            ZeroStdTimeStringA                                             */
/*  return a zero value of type STDTIME_STRINGA                              */
/*****************************************************************************/

STDTIME_STRINGA             ZeroStdTimeStringA ()
  {
  STDTIME_STRINGA           zero = {{0}};

  return zero;

  } /* ZeroStdTimeStringA */


/*-***************************************************************************/
/*            ZeroStdTimeStringW                                             */
/*  return a zero value of type STDTIME_STRINGW                              */
/*****************************************************************************/

STDTIME_STRINGW             ZeroStdTimeStringW ()
  {
  STDTIME_STRINGW           zero = {{0}};

  return zero;

  } /* ZeroStdTimeStringW */


/*-***************************************************************************/
/*            ZeroStdTimeHexStrA                                             */
/*  return a zero value of type STDTIME_HEXSTRA                              */
/*****************************************************************************/

STDTIME_HEXSTRA             ZeroStdTimeHexStrA ()
  {
  STDTIME_HEXSTRA           zero = {{0}};

  return zero;

  } /* ZeroStdTimeHexStrA */


/*-***************************************************************************/
/*            ZeroStdTimeHexStrW                                             */
/*  return a zero value of type STDTIME_HEXSTRW                              */
/*****************************************************************************/

STDTIME_HEXSTRW             ZeroStdTimeHexStrW ()
  {
  STDTIME_HEXSTRW           zero = {{0}};

  return zero;

  } /* ZeroStdTimeHexStrW */


/*-***************************************************************************/
/*            ZeroStdTimeDelta                                               */
/*  return a zero value of type STDTIME_DELTA                                */
/*****************************************************************************/

STDTIME_DELTA               ZeroStdTimeDelta ()
  {
  STDTIME_DELTA             zero = {0};

  return zero;

  } /* ZeroStdTimeDelta */


/*-***************************************************************************/
/*            ZeroStdTimeSpan                                                */
/*  return a zero value of type STDTIME_SPAN                                 */
/*****************************************************************************/

STDTIME_SPAN                ZeroStdTimeSpan ()
  {
  STDTIME_SPAN              zero = {0};

  return zero;

  } /* ZeroStdTimeSpan */


/*-***************************************************************************/
/*            ZeroStdTimeTzoA                                                */
/*  return a zero value of type STDTIME_TZOA                                 */
/*****************************************************************************/

STDTIME_TZOA                ZeroStdTimeTzoA ()
  {
  STDTIME_TZOA              zero = {{0}};

  return zero;

  } /* ZeroStdTimeTzoA */


/*-***************************************************************************/
/*            ZeroStdTimeTzoW                                                */
/*  return a zero value of type STDTIME_TZOW                                 */
/*****************************************************************************/

STDTIME_TZOW                ZeroStdTimeTzoW ()
  {
  STDTIME_TZOW              zero = {{0}};

  return zero;

  } /* ZeroStdTimeTzoW */


/*-***************************************************************************/
/*            ZeroStdTimeErrMsgA                                             */
/*  return a zero value of type STDTIME_ERRMSGA                              */
/*****************************************************************************/

STDTIME_ERRMSGA             ZeroStdTimeErrMsgA ()
  {
  STDTIME_ERRMSGA           zero = {{0}};

  return zero;

  } /* ZeroStdTimeErrMsgA */


/*-***************************************************************************/
/*            ZeroStdTimeErrMsgW                                             */
/*  return a zero value of type STDTIME_ERRMSGW                              */
/*****************************************************************************/

STDTIME_ERRMSGW             ZeroStdTimeErrMsgW ()
  {
  STDTIME_ERRMSGW           zero = {{0}};

  return zero;

  } /* ZeroStdTimeErrMsgW */


/*** Initializer functions for 'outside' types *******************************/
/*** names prefixed with 'StdTimeApi' because they are non-STDTIME structs ***/


/*-***************************************************************************/
/*            StdTimeApiZeroTimeType                                         */
/*  return a zero value of type STDTIME_TIMETYPE                             */
/*****************************************************************************/

STDTIME_TIMETYPE            StdTimeApiZeroTimeType ()
  {
  STDTIME_TIMETYPE          zero = {0};

  return zero;

  } /* StdTimeApiZeroTimeType */


/*-***************************************************************************/
/*            StdTimeApiZeroFileTime                                         */
/*  return a zero value of type STDTIME_WIN_FILETIME                         */
/*****************************************************************************/

STDTIME_WIN_FILETIME        StdTimeApiZeroFileTime ()
  {
  STDTIME_WIN_FILETIME      zero = {0};

  return zero;

  } /* StdTimeApiZeroFileTime */


/*-***************************************************************************/
/*            StdTimeApiZeroSystemTime                                       */
/*  return a zero value of type STDTIME_WIN_SYSTEMTIME                       */
/*****************************************************************************/

STDTIME_WIN_SYSTEMTIME      StdTimeApiZeroSystemTime ()
  {
  STDTIME_WIN_SYSTEMTIME    zero = {0};

  return zero;

  } /* StdTimeApiZeroSystemTime */


/*-***************************************************************************/
/*            StdTimeApiZeroDbTimeStamp                                      */
/*  return a zero value of type STDTIME_WIN_DBTIMESTAMP                      */
/*****************************************************************************/

STDTIME_WIN_DBTIMESTAMP     StdTimeApiZeroDbTimeStamp ()
  {
  STDTIME_WIN_DBTIMESTAMP   zero = {0};

  return zero;

  } /* StdTimeApiZeroDbTimeStamp */


/*-***************************************************************************/
/*            StdTimeApiZeroUdate                                            */
/*  return a zero value of type STDTIME_WIN_UDATE                            */
/*****************************************************************************/

STDTIME_WIN_UDATE           StdTimeApiZeroUdate ()
  {
  STDTIME_WIN_UDATE         zero = {{0}};

  return zero;

  } /* StdTimeApiZeroUdate */


/*-***************************************************************************/
/*            StdTimeApiZeroStructTm                                         */
/*  return a zero value of type struct tm                                    */
/*****************************************************************************/

struct tm                   StdTimeApiZeroStructTm ()
  {
  struct tm                 zero = {0};

  return zero;

  } /* StdTimeApiZeroStructTm */


/*** calandar function interface *********************************************/


/*-***************************************************************************/
/*  OBTAIN DAY OF WEEK AND DAY OF WEEK                                       */
/*  This provides an interface to the W32 layer, which we do not want to     */
/*  expose to the user.                                                      */
/*****************************************************************************/

STDTIME_RC                  StdTimeGetDayofWeekAndYear (
  int32_t                   /*I*/ nYear,
  int32_t                   /*I*/ nMon,
  int32_t                   /*I*/ nDayofMon,
  int32_t *                 /*O*/ pDayofWeek,
  int32_t *                 /*O*/ pDayofYear)
  {
  STDTIME_ENUM_FUNC (StdTimeGetDayofWeekAndYear)

  STDTIME_RET (StdTimeW32GetDayofWeekAndYear (
    nYear, nMon, nDayofMon, pDayofWeek, pDayofYear));
  }


/*** private ArgDateEx functions *********************************************/


/* an "ArgDate" is either a Date or an HpDate,                      */
/* depending on the hpDate boolean argument to these functions.     */

/* we need a common routine to handle the two forms.  admittedly,   */
/* ArgDate isn't an ideal function name for this, but there         */
/* were no obvious alternatives that seemed better, so here it is.  */


/*-***************************************************************************/
/*            Rc_StdTimeToArgDateEx - PRIVATE FUNCTION                       */
/*  convert: StdTime structure to DATE time value and extra fields           */
/*  with optional millisecond precision.                                     */
/*                                                                           */
/*  this private function takes a boolean parameter that distinguishes       */
/*  between Windows DATE and our High Precision DATE.                        */
/*  for HpDate, the library ensures that milliseconds are not lost.          */
/*****************************************************************************/

static STDTIME_RC           Rc_StdTimeToArgDateEx (
  STDTIME_BOOL              /*I*/ hpDate,
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_DATE *        /*O*/ pDate,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME_WIN_FILETIME      ft;
  QUADLIB_I64               qDateBase;
  QUADLIB_I64               qWork;
  QUADLIB_I64               qDivisor;
  QUADLIB_I64               qRemainder;
  QUADLIB_I64               qResult;
  STDTIME_WIN_DATE          dFraction;
  STDTIME_WIN_DATE          dDate = 1.0; /* the initial sign */
  int32_t                   sign = 1;

  int32_t                   sec;
  int32_t                   msec;
  int32_t                   usec;
  int32_t                   nsec;
  int32_t                   temp;

  STDTIME_ENUM_FUNC (Rc_StdTimeToArgDateEx)

  if ((pStdTime == NULL) || (pDate == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IFNOT (StdTimeToFileTime (pStdTime, &ft))
    {
    STDTIME_RET_RC;
    }

  if STDTIME_IFNOT (Rc_StdTime_ValidFileTime (&ft))
    {
    STDTIME_RET_RC;
    }

  FILETIME_TO_QUADLIB_I64 (&ft, &qWork);

  /* split off msec, usec and nsec from filetime before proceeding */

  QUADLIB_U64_HI (qDivisor) = 0;
  QUADLIB_U64_LO (qDivisor) = 10000000;  /* msec * usec * nsec */

  qResult = QuadLibI64DivMod (qWork, qDivisor, &qRemainder);
  /* qResult contains the number of seconds */

  /* capture fractional seconds values */
  msec = QUADLIB_I64_LO (qRemainder) / 10000;
  temp = QUADLIB_I64_LO (qRemainder) % 10000;   /* usec and nsec value */

  usec = temp / 10;
  nsec = (temp % 10) * 100;
  sec = 0;

  PVT_STDTIME_ROUND (pNsec, nsec, usec)
  PVT_STDTIME_ROUND (pUsec, usec, msec)

  /* if not hpDate, round up msec to sec */
  /* hpDate incorporates msec so rounding to sec is not needed */

  if (! hpDate)
    {
    PVT_STDTIME_ROUND (pMsec, msec, sec)
    QUADLIB_U64_ADD_EQ (qResult, QUADLIB_I64_CASTI32 (sec));
    }

  /* form filetime value with resolution only to seconds */
  qWork = QUADLIB_U64_MUL (qResult, qDivisor);

  /* form value of 1899-12-30 00:00:00.0000000 as a FILETIME equivalent */
  QUADLIB_U64_HI (qDateBase) = PVT_STDTIME_U32_COMDATE_BASE_HI;
  QUADLIB_U64_LO (qDateBase) = PVT_STDTIME_U32_COMDATE_BASE_LO;


  /* form number of 100-nanosecond intervals relative to 1899-12-30 00:00:00 */
  QUADLIB_I64_SUB_EQ (qWork, qDateBase);

  if (QUADLIB_I64_LT_0 (qWork))
    {
    /* time before 1899-12-30 00:00:00 is a negative DATE */
    dDate = -1.0;
    sign = -1;
    qWork = QUADLIB_I64_NEG (qWork);
    }

  /* number of 100-ns intervals in 1 day = */
  /* 24 hour * 60 min * 60 sec * 1000 msec * 1000 usec * 10 (nsec/100) */
  /* = 864,000,000,000 = 0x0000_00C9_2A69_C000 */

  QUADLIB_U64_HI (qDivisor) = PVT_STDTIME_100NS_PERDAY_HI;
  QUADLIB_U64_LO (qDivisor) = PVT_STDTIME_100NS_PERDAY_LO;

  /* the result will fit in an int32_t */

  qResult = QuadLibI64DivMod (qWork, qDivisor, &qRemainder);

  /* form whole number of days in double format */
  dDate *= (double) QUADLIB_I64_LO (qResult);

  /* qRemainder contains a partial day value in 100-ns intervals */
  /* qRemainder is a number < 864,000,000,000 and does not contain */
  /* msec precision.  convert qRemainder to msec units. */

  QUADLIB_U64_HI (qDivisor) = 0;
  QUADLIB_U64_LO (qDivisor) = 10000;
  qWork = qRemainder;

  qResult = QUADLIB_I64_DIV (qWork, qDivisor);
  /* qResult now contains a count of msec < 86,400,000 for < one day */

  if (hpDate)
    {
    /* HpDate keeps fractional seconds */
    temp = QUADLIB_I64_LO (qResult) + msec;  /* use sec and msec resolution */
    }

  else
    {
    /* standard Date drops fractional seconds */
    temp = QUADLIB_I64_LO (qResult);    /* just use sec resolution */
    }

  if (temp != 0)
    {
    /* dFraction is number of msec in one day */
    dFraction = (double) temp;

    if (sign == -1)
    {
      /* handle DATE fractional part as absolute value */
      /* example: real value of -1.25 must become negative integral */
      /* plus positive fractional. -1.25 is the same as -2 (left) */
      /* plus 0.75 right.  since we have to express this as an absolute */
      /* value, the value must become -3 plus 0.25 -> -2.75 */
      /* so, decrement integral by -2, then always add the fraction */

      dDate -= 2.0;
    }

    dDate += (dFraction / 86400000.0);
   }

  /* pass back msec if user asked for it */
  /* for hpDate, pass back zero because DATE includes msec value */

  if (pMsec != NULL)
    {
    if (hpDate)
      {
      *pMsec = 0;
      }

    else
      {
      *pMsec = msec;
      }
    }

  *pDate = dDate;

  STDTIME_RET_OK;

  } /* Rc_StdTimeToArgDateEx */


/*-***************************************************************************/
/*            Rc_ArgDateExToStdTime - PRIVATE FUNCTION                       */
/*  convert: DATE time value and extra fields to StdTime structure           */
/*  with optional microsecond precision.                                     */
/*                                                                           */
/*  this private function takes a boolean parameter that distinguishes       */
/*  between Windows DATE and our High Precision DATE.                        */
/*  for HpDate, the library ensures that milliseconds are not lost.          */
/*****************************************************************************/

static STDTIME_RC           Rc_ArgDateExToStdTime (
  STDTIME_BOOL              /*I*/ hpDate,
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime)
  {
  QUADLIB_I64               qDateBase;
  QUADLIB_I64               qWork;
  double                    dIntegral;
  double                    dFractional;
  double                    dWork;
  int32_t                   iIntegral;
  STDTIME_WIN_FILETIME      ft;

  STDTIME_ENUM_FUNC (Rc_ArgDateExToStdTime)

  if (pStdTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTime = ZeroStdTime ();

  if (pDate == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }


#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4244)
/* silence the VC compiler warning message: */
/* "conversion from 'double' to 'int', possible loss of data" */
#endif


  /* form value of 1899-12-30 00:00:00.0000000 as a FILETIME equivalent */
  QUADLIB_U64_HI (qDateBase) = PVT_STDTIME_U32_COMDATE_BASE_HI;
  QUADLIB_U64_LO (qDateBase) = PVT_STDTIME_U32_COMDATE_BASE_LO;

  dFractional = modf (*pDate, &dIntegral);

  if (dFractional < 0.0)
    {
    /* DATE fractions are processed as absolute values */
    dFractional = -dFractional;
    }

    /* start with number of whole days */
  iIntegral   = dIntegral;
  qWork       = QUADLIB_I64_CASTI32 (iIntegral);

  /* convert whole days to seconds */
  QUADLIB_I64_MUL_EQ (qWork, QUADLIB_I64_CASTI32 (24*60*60));

  /* convert fractional days to seconds */
  dWork       = dFractional * 24.0 * 60.0 * 60.0;

  dFractional = modf (dWork, &dIntegral);

  if (! hpDate)
    {
    /* perform simple rounding to avoid floating-point roundoff problems */
    /* this is NOT a rounding up operation */
    if (dFractional > 0.990)
      {
      dIntegral += 1.0;
      }
    }

  iIntegral   = dIntegral;
  QUADLIB_I64_ADD_EQ (qWork, QUADLIB_I64_CASTI32 (iIntegral));

  /* msec */
  QUADLIB_I64_MUL_EQ (qWork, QUADLIB_I64_CASTI32 (1000));

  /* only add in DATE msec if this is a high precision DATE */
  /* otherwise, the msec value may not be meaningful */

  if (hpDate)
    {
    dWork = dFractional * 1000.0;
    dFractional = modf (dWork, &dIntegral);

    if (dFractional > 0.990)
      {
      dIntegral += 1.0;
      }

    iIntegral = dIntegral;

    if (iIntegral != 0)
      {
      QUADLIB_I64_ADD_EQ (qWork, QUADLIB_I64_CASTI32 (iIntegral));
      }
    }

  /* add in supplied msec if any */

  if (nMsec != 0)
    {
    QUADLIB_I64_ADD_EQ (qWork, QUADLIB_I64_CASTI32 (nMsec));
    }

  /* add in supplied usec if any */
  QUADLIB_I64_MUL_EQ (qWork, QUADLIB_I64_CASTI32 (1000));

  if (nUsec != 0)
    {
    QUADLIB_I64_ADD_EQ (qWork, QUADLIB_I64_CASTI32 (nUsec));
    }

  /* add in supplied nsec if any */
  /* nsec value is actual nanoseconds, but FILETIME is in 100-nanosecond */
  /* intervals, so divide by 100 to add in proper precision */

  QUADLIB_I64_MUL10_EQ (qWork);

  if (nNsec != 0)
    {
    QUADLIB_I64_ADD_EQ (qWork, QUADLIB_I64_CASTI32 (nNsec / 100));
    }

  /* add DATE base epoch of 1899-12-30 */
  QUADLIB_I64_ADD_EQ (qWork, qDateBase);

  /* qWork now contains the FILETIME equivalent of the DATE time */
  QUADLIB_I64_TO_FILETIME (&qWork, &ft);

  if STDTIME_IF (Rc_StdTime_ValidFileTime (&ft))
    {
    STDTIME_RET (FileTimeToStdTime (&ft, pStdTime));
    }

  STDTIME_RET_RC;


#ifdef _MSC_VER
#pragma warning(pop)
#endif


  } /* Rc_ArgDateExToStdTime */


/*-***************************************************************************/
/*            Rc_StdTimeFieldsToArgDateEx - PRIVATE FUNCTION                 */
/*  convert: StdTime structure to DATE time value                            */
/*  with optional microsecond precision.                                     */
/*                                                                           */
/*  this private function takes a boolean parameter that distinguishes       */
/*  between Windows DATE and our High Precision DATE.                        */
/*  for HpDate, the library ensures that milliseconds are not lost.          */
/*****************************************************************************/

static STDTIME_RC           Rc_StdTimeFieldsToArgDateEx (
  STDTIME_BOOL              /*I*/ hpDate,
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_DATE *        /*O*/ pDate,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME                   stdTime;

  STDTIME_ENUM_FUNC (Rc_StdTimeFieldsToArgDateEx)

  if STDTIME_IF (StdTimeFieldsToStdTime (pStdTimeFields, &stdTime))
    {
    STDTIME_RET (Rc_StdTimeToArgDateEx (
      hpDate,
      &stdTime,
      pDate,
      pMsec,
      pUsec,
      pNsec));
    }

  STDTIME_RET_RC;

  } /* Rc_StdTimeFieldsToArgDateEx */


/*-***************************************************************************/
/*            Rc_ArgDateExToStdTimeFields - PRIVATE FUNCTION                 */
/*  convert: DATE time value to StdTimeFields structure                      */
/*  with optional microsecond precision.                                     */
/*                                                                           */
/*  this private function takes a boolean parameter that distinguishes       */
/*  between Windows DATE and our High Precision DATE.                        */
/*  for HpDate, the library ensures that milliseconds are not lost.          */
/*****************************************************************************/

static STDTIME_RC           Rc_ArgDateExToStdTimeFields (
  STDTIME_BOOL              /*I*/ hpDate,
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME                   stdTime;

  STDTIME_ENUM_FUNC (Rc_ArgDateExToStdTimeFields)

  if STDTIME_IF (Rc_ArgDateExToStdTime (
        hpDate,
        pDate,
        nMsec,
        nUsec,
        nNsec,
        &stdTime))
    {
    STDTIME_RET (StdTimeToStdTimeFields (&stdTime, pStdTimeFields));
    }

  STDTIME_RET_RC;

  } /* Rc_ArgDateExToStdTimeFields */


/*** DateEx functions (COM DATE) *********************************************/


/*-***************************************************************************/
/*            StdTimeToDateEx                                                */
/*  convert: StdTime structure to DATE time value and extra fields           */
/*****************************************************************************/

STDTIME_RC                  StdTimeToDateEx (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_DATE *        /*O*/ pDate,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME_ENUM_FUNC (StdTimeToDateEx)

  STDTIME_RET (Rc_StdTimeToArgDateEx (
    STDTIME_FALSE,          /* not High Precision DATE */
    pStdTime,
    pDate,
    pMsec,
    pUsec,
    pNsec));

  } /* StdTimeToDateEx */


/*-***************************************************************************/
/*            DateExToStdTime                                                */
/*  convert: DATE time value and extra fields to StdTime structure           */
/*****************************************************************************/

STDTIME_RC                  DateExToStdTime (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_ENUM_FUNC (DateExToStdTime)

  STDTIME_RET (Rc_ArgDateExToStdTime (
    STDTIME_FALSE,          /* not High Precision DATE */
    pDate,
    nMsec,
    nUsec,
    nNsec,
    pStdTime));

  } /* DateExToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToDateEx                                          */
/*  convert: StdTime structure to DATE time value                            */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToDateEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_DATE *        /*O*/ pDate,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME_ENUM_FUNC (StdTimeFieldsToDateEx)

  STDTIME_RET (Rc_StdTimeFieldsToArgDateEx (
    STDTIME_FALSE,          /* not High Precision DATE */
    pStdTimeFields,
    pDate,
    pMsec,
    pUsec,
    pNsec));

  } /* StdTimeFieldsToDateEx */


/*-***************************************************************************/
/*            DateExToStdTimeFields                                          */
/*  convert: DATE time value to StdTimeFields structure                      */
/*****************************************************************************/

STDTIME_RC                  DateExToStdTimeFields (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_ENUM_FUNC (DateExToStdTimeFields)

  STDTIME_RET (Rc_ArgDateExToStdTimeFields (
    STDTIME_FALSE,         /* not High Precision DATE */
    pDate,
    nMsec,
    nUsec,
    nNsec,
    pStdTimeFields));

  } /* DateExToStdTimeFields */


/*** Date functions (COM DATE) ***********************************************/


/*-***************************************************************************/
/*            StdTimeToDate                                                  */
/*  convert: StdTime structure to DATE time value                            */
/*****************************************************************************/

STDTIME_RC                  StdTimeToDate (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_DATE *        /*O*/ pDate)
  {
  STDTIME_ENUM_FUNC (StdTimeToDate)

  STDTIME_RET (Rc_StdTimeToArgDateEx (
    STDTIME_FALSE,      /* not High Precision DATE */
    pStdTime,
    pDate,
    NULL,
    NULL,
    NULL));

  } /* StdTimeToDate */


/*-***************************************************************************/
/*            DateToStdTime                                                  */
/*  convert: DATE time value to StdTime structure                            */
/*****************************************************************************/

STDTIME_RC                  DateToStdTime (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_ENUM_FUNC (DateToStdTime)

  STDTIME_RET (Rc_ArgDateExToStdTime (
    STDTIME_FALSE,          /* not High Precision DATE */
    pDate,
    0,
    0,
    0,
    pStdTime));

  } /* DateToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToDate                                            */
/*  convert: StdTime structure to DATE time value                            */
/*****************************************************************************/


STDTIME_RC                  StdTimeFieldsToDate (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_DATE *        /*O*/ pDate)
  {
  STDTIME_ENUM_FUNC (StdTimeFieldsToDate)

  STDTIME_RET (Rc_StdTimeFieldsToArgDateEx (
    STDTIME_FALSE,          /* not High Precision DATE */
    pStdTimeFields,
    pDate,
    NULL,
    NULL,
    NULL));

  } /* StdTimeFieldsToDate */


/*-***************************************************************************/
/*            DateToStdTimeFields                                            */
/*  convert: DATE time value to StdTimeFields structure                      */
/*****************************************************************************/

STDTIME_RC                  DateToStdTimeFields (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_ENUM_FUNC (DateToStdTimeFields)

  STDTIME_RET (Rc_ArgDateExToStdTimeFields (
    STDTIME_FALSE,          /* not High Precision DATE */
    pDate,
    0,
    0,
    0,
    pStdTimeFields));

  } /* DateToStdTimeFields */


/*** HpDateEx functions (COM DATE) *******************************************/


/*-***************************************************************************/
/*            StdTimeToHpDateEx                                              */
/*  convert: StdTime structure to DATE time value and extra fields           */
/*****************************************************************************/

STDTIME_RC                  StdTimeToHpDateEx (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_DATE *        /*O*/ pDate,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME_ENUM_FUNC (StdTimeToHpDateEx)

  STDTIME_RET (Rc_StdTimeToArgDateEx (
    STDTIME_TRUE,           /* is High Precision DATE */
    pStdTime,
    pDate,
    NULL,                   /* dummy msec */
    pUsec,
    pNsec));

  } /* StdTimeToHpDateEx */


/*-***************************************************************************/
/*            HpDateExToStdTime                                              */
/*  convert: DATE time value and extra fields to StdTime structure           */
/*****************************************************************************/

STDTIME_RC                  HpDateExToStdTime (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_ENUM_FUNC (HpDateExToStdTime)

  STDTIME_RET (Rc_ArgDateExToStdTime (
    STDTIME_TRUE,           /* is High Precision DATE */
    pDate,
    0,                      /* dummy msec */
    nUsec,
    nNsec,
    pStdTime));

  } /* HpDateExToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToHpDateEx                                        */
/*  convert: StdTime structure to DATE time value                            */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToHpDateEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_DATE *        /*O*/ pDate,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME_ENUM_FUNC (StdTimeFieldsToHpDateEx)

  STDTIME_RET (Rc_StdTimeFieldsToArgDateEx (
    STDTIME_TRUE,           /* is High Precision DATE */
    pStdTimeFields,
    pDate,
    NULL,                   /* dummy msec */
    pUsec,
    pNsec));

  } /* StdTimeFieldsToHpDateEx */


/*-***************************************************************************/
/*            HpDateExToStdTimeFields                                        */
/*  convert: DATE time value to StdTimeFields structure                      */
/*****************************************************************************/

STDTIME_RC                  HpDateExToStdTimeFields (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_ENUM_FUNC (HpDateExToStdTimeFields)

  STDTIME_RET (Rc_ArgDateExToStdTimeFields (
    STDTIME_TRUE,           /* is High Precision DATE */
    pDate,
    0,                      /* dummy msec */
    nUsec,
    nNsec,
    pStdTimeFields));

  } /* HpDateExToStdTimeFields */


/*** HpDate functions (COM DATE) *********************************************/


/*-***************************************************************************/
/*            StdTimeToHpDate                                                */
/*  convert: StdTime structure to DATE time value                            */
/*****************************************************************************/

STDTIME_RC                  StdTimeToHpDate (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_DATE *        /*O*/ pDate)
  {
  STDTIME_ENUM_FUNC (StdTimeToHpDate)

  STDTIME_RET (Rc_StdTimeToArgDateEx (
    STDTIME_TRUE,           /* is High Precision DATE */
    pStdTime,
    pDate,
    NULL,
    NULL,
    NULL));

  } /* StdTimeToHpDate */


/*-***************************************************************************/
/*            HpDateToStdTime                                                */
/*  convert: DATE time value to StdTime structure                            */
/*****************************************************************************/

STDTIME_RC                  HpDateToStdTime (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_ENUM_FUNC (HpDateToStdTime)

  STDTIME_RET (Rc_ArgDateExToStdTime (
    STDTIME_TRUE,           /* is High Precision DATE */
    pDate,
    0,
    0,
    0,
    pStdTime));

  } /* HpDateToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToHpDate                                          */
/*  convert: StdTime structure to DATE time value                            */
/*****************************************************************************/


STDTIME_RC                  StdTimeFieldsToHpDate (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_DATE *        /*O*/ pDate)
  {
  STDTIME_ENUM_FUNC (StdTimeFieldsToHpDate)

  STDTIME_RET (Rc_StdTimeFieldsToArgDateEx (
    STDTIME_TRUE,           /* is High Precision DATE */
    pStdTimeFields,
    pDate,
    NULL,
    NULL,
    NULL));

  } /* StdTimeFieldsToHpDate */

/*-***************************************************************************/
/*            HpDateToStdTimeFields                                          */
/*  convert: DATE time value to StdTimeFields structure                      */
/*****************************************************************************/


STDTIME_RC                  HpDateToStdTimeFields (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_ENUM_FUNC (HpDateToStdTimeFields)

  STDTIME_RET (Rc_ArgDateExToStdTimeFields (
    STDTIME_TRUE,           /* is High Precision DATE */
    pDate,
    0,
    0,
    0,
    pStdTimeFields));

  } /* HpDateToStdTimeFields */


/*** VariantEx functions *************************************************/


/*-***************************************************************************/
/*            Rc_StdTime_DateToVariant - PRIVATE FUNCTION                    */
/*  store a DATE value into a VARIANT structure                              */
/*****************************************************************************/

static STDTIME_RC           Rc_StdTime_DateToVariant (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  STDTIME_WIN_VARIANT *     /*O*/ pVariant)
  {
  STDTIME_ENUM_FUNC (Rc_StdTime_DateToVariant)

  if ((pDate == NULL) || (pVariant == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  if (pVariant->vt == (STDTIME_WIN_VT_DATE|STDTIME_WIN_VT_BYREF))
    {
    /* target is a pointer to a DATE value; ensure ptr is valid */

    if (pVariant->STDTIME_UDOT pdate == NULL)
      {
      STDTIME_RET_EC (null_VARIANT_pdate);
      }

    /* copy value into memory location pointed by BYREF argument */
    *(pVariant->STDTIME_UDOT pdate) = *pDate;

    pVariant->wReserved1 = 0;
    pVariant->wReserved2 = 0;
    pVariant->wReserved3 = 0;

    STDTIME_RET_OK;
    }

  /* BYREF type cannot be any other type than DATE */

  if ((pVariant->vt) | STDTIME_WIN_VT_BYREF)
    {
    STDTIME_RET_EC (VARIANT_BYREF_type_not_DATE);
    }

  /* copy value into VARIANT structure itself, and set vt */

  pVariant->vt = STDTIME_WIN_VT_DATE;
  pVariant->STDTIME_UDOT date = *pDate;

  pVariant->wReserved1 = 0;
  pVariant->wReserved2 = 0;
  pVariant->wReserved3 = 0;

  STDTIME_RET_OK;

  } /* Rc_StdTime_DateToVariant */


/*-***************************************************************************/
/*            Rc_StdTime_VariantToDate - PRIVATE FUNCTION                    */
/*  store a VARIANT value into a DATE structure                              */
/*****************************************************************************/

static STDTIME_RC           Rc_StdTime_VariantToDate (
  const STDTIME_WIN_VARIANT * /*I*/ pVariant,
  STDTIME_WIN_DATE *        /*O*/ pDate)
  {
  STDTIME_ENUM_FUNC (Rc_StdTime_VariantToDate)

  if ((pVariant == NULL) || (pDate == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  if (pVariant->vt == (STDTIME_WIN_VT_DATE|STDTIME_WIN_VT_BYREF))
    {
    /* source is a pointer to a DATE value; ensure ptr is valid */

    if (pVariant->STDTIME_UDOT pdate == NULL)
      {
      STDTIME_RET_EC (null_VARIANT_pdate);
      }

    /* copy value from memory location pointed by BYREF argument */
    *pDate = *(pVariant->STDTIME_UDOT pdate);

    STDTIME_RET_OK;
    }

  /* source VARIANT cannot be any other type than DATE */

  if ((pVariant->vt) != STDTIME_WIN_VT_DATE)
    {
    STDTIME_RET_EC (VARIANT_type_not_DATE);
    }

  /* copy value from VARIANT structure */

  *pDate = pVariant->STDTIME_UDOT date;

  STDTIME_RET_OK;

  } /* Rc_StdTime_VariantToDate */


/*-***************************************************************************/
/*            StdTimeToVariantEx                                             */
/*  convert: StdTime structure to VARIANT time value and extra fields        */
/*****************************************************************************/

STDTIME_RC                  StdTimeToVariantEx (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_VARIANT *     /*O*/ pVariant,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME_WIN_DATE          comDate;

  STDTIME_ENUM_FUNC (StdTimeToVariantEx)

  if STDTIME_IF (StdTimeToDateEx (
       pStdTime, &comDate, pMsec, pUsec, pNsec))
    {
    STDTIME_RET (Rc_StdTime_DateToVariant (&comDate, pVariant));
    }

  STDTIME_RET_RC;

  } /* StdTimeToVariantEx */


/*-***************************************************************************/
/*            VariantExToStdTime                                             */
/*  convert: VARIANT time value and extra fields to StdTime structure        */
/*****************************************************************************/

STDTIME_RC                  VariantExToStdTime (
  const STDTIME_WIN_VARIANT * /*I*/ pVariant,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_WIN_DATE          comDate;

  STDTIME_ENUM_FUNC (VariantExToStdTime)

  if STDTIME_IF (Rc_StdTime_VariantToDate (pVariant, &comDate))
    {
    STDTIME_RET (DateExToStdTime (
      &comDate, nMsec, nUsec, nNsec, pStdTime));
    }

  STDTIME_RET_RC;

  } /* VariantExToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToVariantEx                                       */
/*  convert: StdTime structure to VARIANT time value                         */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToVariantEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_VARIANT *     /*O*/ pVariant,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME_WIN_DATE          comDate;

  STDTIME_ENUM_FUNC (StdTimeFieldsToVariantEx)

  if STDTIME_IF (StdTimeFieldsToDateEx (
       pStdTimeFields, &comDate, pMsec, pUsec, pNsec))
    {
    STDTIME_RET (Rc_StdTime_DateToVariant (&comDate, pVariant));
    }

  STDTIME_RET_RC;

  } /* StdTimeFieldsToVariantEx */


/*-***************************************************************************/
/*            VariantExToStdTimeFields                                       */
/*  convert: VARIANT time value to StdTimeFields structure                   */
/*****************************************************************************/

STDTIME_RC                  VariantExToStdTimeFields (
  const STDTIME_WIN_VARIANT * /*I*/ pVariant,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_WIN_DATE          comDate;

  STDTIME_ENUM_FUNC (VariantExToStdTimeFields)

  if STDTIME_IF (Rc_StdTime_VariantToDate (pVariant, &comDate))
    {
    STDTIME_RET (DateExToStdTimeFields (
      &comDate, nMsec, nUsec, nNsec, pStdTimeFields));
    }

  STDTIME_RET_RC;

  } /* VariantExToStdTimeFields */


/*** Variant functions *******************************************************/


/*-***************************************************************************/
/*            StdTimeToVariant                                               */
/*  convert: StdTime structure to VARIANT time value                         */
/*****************************************************************************/

STDTIME_RC                  StdTimeToVariant (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_VARIANT *     /*O*/ pVariant)
  {
  STDTIME_ENUM_FUNC (StdTimeToVariant)

  STDTIME_RET (StdTimeToVariantEx (
    pStdTime,
    pVariant,
    NULL,
    NULL,
    NULL));

  } /* StdTimeToVariant */


/*-***************************************************************************/
/*            VariantToStdTime                                               */
/*  convert: VARIANT time value to StdTime structure                         */
/*****************************************************************************/

STDTIME_RC                  VariantToStdTime (
  const STDTIME_WIN_VARIANT * /*I*/ pVariant,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_ENUM_FUNC (VariantToStdTime)

  STDTIME_RET (VariantExToStdTime (
    pVariant,
    0,
    0,
    0,
    pStdTime));

  } /* VariantToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToVariant                                         */
/*  convert: StdTime structure to VARIANT time value                         */
/*****************************************************************************/


STDTIME_RC                  StdTimeFieldsToVariant (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_VARIANT *     /*O*/ pVariant)
  {
  STDTIME_ENUM_FUNC (StdTimeFieldsToVariant)

  STDTIME_RET (StdTimeFieldsToVariantEx (
    pStdTimeFields,
    pVariant,
    NULL,
    NULL,
    NULL));

  } /* StdTimeFieldsToVariant */


/*-***************************************************************************/
/*            VariantToStdTimeFields                                         */
/*  convert: VARIANT time value to StdTimeFields structure                   */
/*****************************************************************************/

STDTIME_RC                  VariantToStdTimeFields (
  const STDTIME_WIN_VARIANT * /*I*/ pVariant,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_ENUM_FUNC (VariantToStdTimeFields)

  STDTIME_RET (VariantExToStdTimeFields (
    pVariant,
    0,
    0,
    0,
    pStdTimeFields));

  } /* VariantToStdTimeFields */


/*** timezone-related functions **********************************************/


/*-***************************************************************************/
/*            Rc_StdTimeTz_GetRule - PRIVATE FUNCTION                        */
/*  interpret start/stop rule string from Boost timezone database file       */
/*****************************************************************************/

static STDTIME_RC           Rc_StdTimeTz_GetRule (
  const char *              pString,
  STDTIME_TZ_RULE *         pRule)
  {
  /***************************************************************************/
  /*                                                                         */
  /* interpret start/stop rule string.  according to Boost.org doc:          */
  /*-------------------------------------------------------------------------*/
  /* This is a specially formatted string that describes the day of year     */
  /* in which the transition take place. It holds three fields of its        */
  /* own, separated by semicolons.                                           */
  /*                                                                         */
  /* * The first field indicates the "nth" weekday of the month. The         */
  /*         possible values are: 1 (first), 2 (second), 3 (third),          */
  /*         4 (fourth), 5 (fifth), and -1 (last).                           */
  /*                                                                         */
  /* * The second field indicates the day-of-week from 0-6 (Sun=0).          */
  /*                                                                         */
  /* * The third field indicates the month from 1-12 (Jan=1).                */
  /*                                                                         */
  /* Examples are: "-1;5;9"="Last Friday of September",                      */
  /* "2;1;3"="Second Monday of March"                                        */
  /*-------------------------------------------------------------------------*/
  /* however, since no month has more than 5 of any particular day (like     */
  /* Monday), there is no need to distinguish 5th from last.  we treat -1    */
  /* the same as 5, doing a conversion; this is how most Unix systems do it. */
  /*-------------------------------------------------------------------------*/
  /* 10/18/06: new capabilities added for timezone rules:                    */
  /*    when day of week == 9, the day ordinal is an exact date              */
  /*        example: 7;9;2 ==> Feb 7                                         */
  /*                                                                         */
  /*    when day ordinal has a + sign, it means a lower bound for the date.  */
  /*    that is, the date to be determined is >= value of day ordinal.       */
  /*        example: +9;0;10 ==> lowest Sun of Oct where date is >= 9        */
  /*                                                                         */
  /*    the >= relationship is being used in more current zoneinfo/ts        */
  /*    databases, so it's important to support it here.                     */
  /*                                                                         */
  /***************************************************************************/

  const char *              scan;

  int32_t                   n;

  STDTIME_ENUM_FUNC (Rc_StdTimeTz_GetRule)

  if ((pString == NULL) || (pRule == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  /* zero-out rule if missing */

  pRule->dayOrdinal = 0;
  pRule->dayOfWeek  = 0;
  pRule->dayOfMonth = 0;
  pRule->mon = 0;

  if (pString[0] == 0)
    {
    STDTIME_RET_OK;             /* string has no rule - OK */
    }

  /*  1;0;4#    = first SUN in APR */
  /* -1;0;10#   = last  SUN in OCT */
  /* +7;0;10#   = first SUN in OCT that is >= 7 */
  /* +21;0;10#  = first SUN in OCT that is >= 21 */

  scan = pString;

  /* for first field: */
  /* unsigned value must be 1 digit */
  /* - signed value must be 1 digit */
  /* + signed value may be 1 or 2 digits */


  /************************************/
  /* extract dayOrdinal or dayOfMonth */
  /************************************/

  if (*scan == '+')
    {
    /* first field is for exact-date mode, or lower-bound mode */

    /* +7;0... */
    /* +21;0... */
    /* 01234   */

    if (scan[2] == ';')                         /* 1 digit value */
      {
      if ((scan[1] < '1') || (scan[1] > '9'))
        {
        STDTIME_RET_EC (data_out_of_range);     /* bad day ordinal */
        }
      }

    else if (scan[3] == ';')                    /* 2 digit value */
      {
      if ((scan[1] < '1') || (scan[1] > '3'))
        {
        STDTIME_RET_EC (data_out_of_range);     /* bad day ordinal */
        }

      if ((scan[2] < '0') || (scan[2] > '9'))
        {
        STDTIME_RET_EC (data_out_of_range);     /* bad day ordinal */
        }
      }

    else
      {
      STDTIME_RET_EC (invalid_delimiter);
      }

    n = atoi (scan+1);      /* grab dayOfMonth value */

    if ((n < 1) || (n > 31))
      {
      STDTIME_RET_EC (data_out_of_range);     /* bad day ordinal */
      }

    pRule->dayOfMonth = n;

    /* assume that the +n or +nn value is a lower bound, unless the */
    /* second field is '9' to indicate an exact date */
    pRule->dayOrdinal = STDTIME_TZ_RULE_LBOUND;
    }

  else if (*scan == '-')
    {
    /* -1;0... */
    /* 0123    */

    if (scan[2] != ';')
      {
      STDTIME_RET_EC (invalid_delimiter);
      }

    if (scan[1] != '1')
      {
      STDTIME_RET_EC (data_out_of_range);       /* bad day ordinal */
      }

    pRule->dayOrdinal = STDTIME_TZ_RULE_LAST;
    /* -1 same as 5, both mean 'last' */
    }

  else  /* s/b digit 1 to 5 */
    {
    /* 1;0... */
    /* 012    */

    if (scan[1] != ';')
      {
      STDTIME_RET_EC (invalid_delimiter);
      }

    if ((scan[0] < '1') || (scan[0] > '5'))
      {
      STDTIME_RET_EC (data_out_of_range);   /* bad day ordinal */
      }

    if (scan[0] == '5')
      {
      pRule->dayOrdinal = STDTIME_TZ_RULE_LAST;      /* 5 stored */
      }

    else
      {
      pRule->dayOrdinal = scan[0] - '0';      /* 1 thru 4 stored */
      }
    }

  while (*scan != ';') scan++;      /* skip upto ';' */
  scan++;                           /* skip over ';' */


  /*********************************************************************/
  /* extract dayOfWeek: range 0 to 6 == SUN to SAT, or 9 == exact date */
  /*********************************************************************/

  /* 0;3#       SUN in MAR */
  /* 6;10#      SAT in OCT */
  /* 01234                 */

  if (scan[1] != ';')
    {
    STDTIME_RET_EC (invalid_delimiter);
    }

  if (scan[0] == '9')               /* exact-date mode */
    {
    if (pRule->dayOfMonth == 0)
      {
      /* there was no exact date (+n or +nn) value as field 1 */
      STDTIME_RET_EC (data_out_of_range);
      }

    pRule->dayOrdinal = STDTIME_TZ_RULE_EXACT;
    pRule->dayOfWeek = 0;                   /* a default value, not used */
    }

  else if ((scan[0] < '0') || (scan[0] > '6'))
    {
    STDTIME_RET_EC (data_out_of_range);     /* bad dayOfWeek */
    }

  else
    {
    pRule->dayOfWeek = scan[0] - '0';       /* 0 thru 6 stored */
    }

  scan += 2;        /* skip over 1 digit and ';' */


  /**************************************************/
  /* extract mon value: range 1 to 12 == JAN to DEC */
  /**************************************************/

  /* 3#       MAR */
  /* 10#      OCT */
  /* 012          */

  if ((scan[0] < '0') || (scan[0] > '9'))
    {
    STDTIME_RET_EC (data_out_of_range);     /* bad mon value */
    }

  if (scan[1] == 0)                         /* 1 digit month */
    {
    n = scan[0] - '0';                      /* grab mon value */
    }

  else if (scan[2] == 0)                    /* 2 digit month */
    {
    if ((scan[1] < '0') || (scan[1] > '9'))
      {
      STDTIME_RET_EC (data_out_of_range);   /* bad mon value */
      }

    n = atoi (scan);                        /* grab mon value */
    }

  else
    {
    STDTIME_RET_EC (invalid_delimiter);
    }

  if ((n < 1) || (n > 12))
    {
    STDTIME_RET_EC (data_out_of_range);     /* bad mon value */
    }

  pRule->mon = n;                           /* 1 thru 12 stored */

  /* if there a dayOfMonth value (+n or +nn) was specified, validate it. */
  /* this test will allow for Feb 29, even though that would be a little */
  /* strange to use.  further validation will be handled elsewhere.      */
  /* the dayOfMonth has already been validated to be in range 1 to 31.   */

  if (pRule->dayOfMonth > StdTimeDaysPerMonLeapTab [n])
    {
    STDTIME_RET_EC (data_out_of_range);
    }

  STDTIME_RET_OK;

  } /* Rc_StdTimeTz_GetRule */


/*-***************************************************************************/
/*            Rc_StdTimeTz_GetTime - PRIVATE FUNCTION                        */
/*  interpret start/stop time string from Boost timezone database file       */
/*****************************************************************************/

static STDTIME_RC           Rc_StdTimeTz_GetTime (
  const char *              pString,
  STDTIME_TZ_TIME *         pTime)
  {
  /***************************************************************************/
  /*                                                                         */
  /* interpret start/stop time string.  according to Boost.org doc:          */
  /*-------------------------------------------------------------------------*/
  /* Some fields represent a length of time. The format of these fields      */
  /* must be: "{+|-}hh:mm[:ss]" <- length-of-time format, where the plus     */
  /* or minus is mandatory and the seconds are optional.                     */
  /*-------------------------------------------------------------------------*/
  /* so we can have the following strings, of length 6 or 9:                 */
  /*    +hh:mm#                                                              */
  /*    -hh:mm#                                                              */
  /*    +hh:mm:ss#                                                           */
  /*    -hh:mm:ss#                                                           */
  /*    0123456789                                                           */
  /*                                                                         */
  /***************************************************************************/

  int32_t                   len;
  int32_t                   hour;
  int32_t                   min;
  int32_t                   sec;

  STDTIME_ENUM_FUNC (Rc_StdTimeTz_GetTime)

  if ((pString == NULL) || (pTime == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  pTime->sign = 0;
  pTime->hour = 0;
  pTime->min  = 0;
  pTime->sec  = 0;

  len = (int32_t) strlen (pString);

  if (len == 0)
    {
    STDTIME_RET_OK;             /* no time - same as time of +00:00:00 */
    }

  if ((len != 6) && (len != 9))
    {
    STDTIME_RET_EC (length_out_of_range);
    }

  if ((pString[0] != '+') && (pString[0] != '-'))
    {
    STDTIME_RET_EC (invalid_sign);
    }

  if ( (pString[3] != ':')
  ||   (! isdigit (pString[1]))
  ||   (! isdigit (pString[2]))
  ||   (! isdigit (pString[4]))
  ||   (! isdigit (pString[5])) )
    {
    STDTIME_RET_EC (invalid_hh_mm);      /* bad hh:mm */
    }

  hour = atoi (pString+1);
  min  = atoi (pString+4);

  if (len == 9)
    {
    if ( (pString[6] != ':')
    ||   (! isdigit (pString[7]))
    ||   (! isdigit (pString[8])) )
      {
      STDTIME_RET_EC (invalid_ss);      /* bad :ss */
      }

    sec = atoi (pString+7);
    }

  else
    {
    sec = 0;
    }

  if ((hour < 0) || (hour > 23)
  ||  (min  < 0) || (min  > 59)
  ||  (sec  < 0) || (sec  > 59))
    {
    STDTIME_RET_EC (data_out_of_range);     /* bad hh:mm:ss numeric values */
    }

  pTime->hour = hour;
  pTime->min  = min;
  pTime->sec  = sec;

  if ((hour == 0) && (min == 0) && (sec == 0))
    {
    pTime->sign = 0;            /* [+] or [-] doesn't matter if value is 0 */
    }

  else if (pString[0] == '-')
    {
    pTime->sign = -1;
    }

  else
    {
    pTime->sign = 1;
    }

  STDTIME_RET_OK;

  } /* Rc_StdTimeTz_GetTime */


/*-***************************************************************************/
/*            Bool_StdTimeTz_ChrEq - PRIVATE FUNCTION                        */
/*  special-purpose character compare function.                              */
/*  the timezone database file uses underscore like a blank, so we treat     */
/*  those two characters as equivalent; other chars are case insensitive.    */
/*****************************************************************************/

static STDTIME_BOOL         Bool_StdTimeTz_ChrEq (
  char                      /*I*/ a,
  char                      /*I*/ b)
  {
  if (a == b)                   return STDTIME_TRUE;
  if ((a == ' ') && (b == '_')) return STDTIME_TRUE;
  if ((a == '_') && (b == ' ')) return STDTIME_TRUE;
  if (toupper(a) == toupper(b)) return STDTIME_TRUE;

  return STDTIME_FALSE;

  } /* Bool_StdTimeTz_ChrEq */


/*-***************************************************************************/
/*            Bool_StdTimeTz_StrEq - PRIVATE FUNCTION                        */
/*  special-purpose string compare function for timezone database IDs.       */
/*  the comparison stops at the first ';' in case there is a group/region    */
/*  code embedded in the table; that is used later to look up year-specific  */
/*  day-transition rules.                                                    */
/*  example: "America/Detroit;US" matches "America/Detroit".                 */
/*****************************************************************************/

static STDTIME_BOOL         Bool_StdTimeTz_StrEq (
  const char *              a,
  const char *              b)
  {
  if ((a == NULL) || (b == NULL)) return STDTIME_FALSE;

  for (;; a++, b++)
    {
    if ((*a == ';') && (*b == 0))       return STDTIME_TRUE;
    if ((*b == ';') && (*a == 0))       return STDTIME_TRUE;
    if (!Bool_StdTimeTz_ChrEq (*a, *b)) return STDTIME_FALSE;
    if (*a == 0) break;
    }

  return STDTIME_TRUE;

  } /* Bool_StdTimeTz_StrEq */


/*-***************************************************************************/
/*            Bool_StdTimeTz_SimpleTZ - PRIVATE FUNCTION                     */
/*  determine if string is a simple timezone string like EST or EST5EDT      */
/*****************************************************************************/

static STDTIME_BOOL         Bool_StdTimeTz_SimpleTZ (
  char *                    /*I*/ pEnvStr,
  char *                    /*O*/ pZoneName)
  {
  /* if TZ env var is a simple timezone string like EST5EDT, truncate it */
  /* at the STD zone name abbreviation */

  int32_t                   len = 0;
  char                      work[8];


  /* count leading letters; only 3 to 5 char names are valid */
  /* most codes are 3 letters, like EST.  a few are 4 letters, like WEST. */
  /* a very few are 5 letters, like  MAGST, AZOST, YEKST, and VLAST */

  /* there may be an optionally signed zone offset following the name */

  if ((pEnvStr == NULL) || (pZoneName == NULL))
    {
    return STDTIME_FALSE;
    }

  /* establish a default in case we cannot truncate the name */

  strcpy (pZoneName, pEnvStr);

  while (isalpha (pEnvStr[len]))
    {
    work[len] = (char) toupper (pEnvStr[len]);
    len++;
    work[len] = 0;
    if (len > 5) break;
    }

  if ((len < 3) || (len > 5)) return STDTIME_FALSE;

  if ( (pEnvStr[len] == 0)            /* form like EST found */
  ||   (isdigit (pEnvStr[len])) )     /* form like EST5... found */
    {
    strcpy (pZoneName, work);
    return STDTIME_TRUE;
    }

  if ((pEnvStr[len] == '+') || (pEnvStr[len] == '-'))
    {
    if (isdigit (pEnvStr[len+1]))   /* form like EST+5... found */
      {
      strcpy (pZoneName, work);
      return STDTIME_TRUE;
      }
    }

  return STDTIME_FALSE;

  } /* Bool_StdTimeTz_SimpleTZ */


/*-***************************************************************************/
/*            Bool_StdTimeTz_HasTimePhrase - PRIVATE FUNCTION                */
/*  determine if time zone name is a phrase like "Eastern Standard Time"     */
/*  if it is, we later compress it to a string like "EST".                   */
/*****************************************************************************/

static STDTIME_BOOL         Bool_StdTimeTz_HasTimePhrase (
  char *                    /*O*/ pZoneName)
  {
  int32_t                   len;
  char                      work[8];

  /* determine if time zone name is a phrase like "Eastern Standard Time" */

  if (pZoneName == NULL) return STDTIME_FALSE;

  /* make sure string looks reasonable */

  if (! isalpha (pZoneName[0])) return STDTIME_FALSE;

  len = (int32_t) strlen (pZoneName);
  if (len < 10) return STDTIME_FALSE;

  /* example:  abc Time# len = 8 */
  /*           012345678         */
  /*  + len -     543210         */
  /*    work +    012345         */

  strcpy (work, pZoneName + len - 5);
  work[1] = (char) toupper(work[1]);
  work[2] = (char) toupper(work[2]);
  work[3] = (char) toupper(work[3]);
  work[4] = (char) toupper(work[4]);

  if (strcmp (work, " TIME") == 0) return STDTIME_TRUE;

  /* string did not end in " Time" */
  return STDTIME_FALSE;

  } /* Bool_StdTimeTz_HasTimePhrase */


/*-***************************************************************************/
/*            Bool_StdTimeTz_GetName - PRIVATE FUNCTION                      */
/*  attempt to obtain the local time zone name from the environment, by      */
/*  retrieving STDTIMEZONE, TZ, or requesting the information from an API.   */
/*****************************************************************************/

static STDTIME_BOOL         Bool_StdTimeTz_GetName (
  char *                    /*O*/ pZoneName)
  {
  char *                    envName;
  char                      wZoneName [STDTIME_TZ_FLD_SIZE] = "";
  char                      winZoneName [STDTIME_TZ_FLD_SIZE] = "";
  int32_t                   i;
  int32_t                   j;
  STDTIME_BOOL              has_TZ_id;

  if (pZoneName == NULL)
    {
    return STDTIME_FALSE;
    }

  pZoneName[0] = 0;

  envName = getenv ("STDTIMEZONE");

  if (envName == NULL)
    {
    envName = getenv ("TZ");
    }

  /* on some platforms, the env variable TZ may be set for the timezone   */
  /* database ID, rather than a value like "EST5EDT".  If so, use it.     */
  /* the name must start with a letter, have at least one '/', and must   */
  /* contain only alpha, slash and underscore characters, or ';'.         */
  /*                                                                      */
  /* a few IDs have multiple slashes, like "America/Kentucky/Louisville"  */
  /* so we can't look for just one slash, even though most entries only   */
  /* have one. the Boost.org rules do not specify an upper bound on this. */

  /* support for ';' in the ID was added to support group and region      */
  /* codes.  for US and Canada, the group is US or CA, and region is the  */
  /* state or province.  For European Union countries, the group is EU    */
  /* and the region is the country code.                                  */

  has_TZ_id = STDTIME_FALSE;

  if (envName != NULL)
    {
    int32_t                 slash_count = 0;
    int32_t                 alpha_count = 0;
    int32_t                 semi_count = 0;

    if (isalpha (envName[0]))
      {
      char *                scan;

      has_TZ_id = STDTIME_TRUE;

      for (scan = envName; *scan; scan++)
        {
        if (isalpha (*scan))
          {
          alpha_count++;
          }

        else if (*scan == '/')
          {
          slash_count++;
          }

        else if (*scan == ';')
          {
          semi_count++;
          }

        else if (*scan != '_')
          {
          has_TZ_id = STDTIME_FALSE;
          break;
          }
        } /* for */

      } /* if (isalpha (envName[0])) */

    if ((has_TZ_id)
    &&  (slash_count > 0)
    &&  (slash_count < 4)
    &&  (semi_count  < 2)
    &&  (alpha_count > 5))
      {
      /* the TZ env var apparently has a timezone database ID */

      strncpy (pZoneName, envName, STDTIME_TZ_FLD_MAX);
      pZoneName[STDTIME_TZ_FLD_MAX] = 0;
      return STDTIME_TRUE;
      }
    } /* if (envName != NULL) */


  if (envName != NULL)
    {
    if (Bool_StdTimeTz_SimpleTZ (envName, wZoneName))
      {
      /* TZ had a simple tz string like EST, or EST5EDT which was truncated */
      /* to EST by the Bool_StdTimeTz_SimpleTZ just called. */

      /* if so, return this string as is without searching further. the */
      /* simple string returned is only 3 to 5 chars, so plain strcpy is OK */

      strcpy (pZoneName, wZoneName);
      return STDTIME_TRUE;
      }
    }


  /* at this point, neither STDTIMEZONE nor TZ env vars were found */
  /* ask the OS directly what the zone is. for Windows, this is normal */
  /* since the time zone is set by a control panel app rather than the */
  /* TZ variable. */

#ifdef _WIN32
  _tzset();
#else
  tzset();
#endif

#ifdef STDTIME_MSVC8
  /* MSVC 2005 has a more secure function to access tzname */
    {
    errno_t                   rc;
    size_t                    iNameLen = 0;

    /* get tzname[0] */
    rc = _get_tzname (&iNameLen, winZoneName, STDTIME_TZ_FLD_MAX, 0);

    if (rc != 0)
      {
      /* Windows failed to return the name of the current timezone */
      /* this *really* shouldn't happen, but ... */
      return STDTIME_FALSE;
      }
    }

#else
  /* go after plain old global var */
  #ifdef _WIN32
    strncpy (winZoneName, _tzname[0], STDTIME_TZ_FLD_MAX);
  #else
    strncpy (winZoneName, tzname[0], STDTIME_TZ_FLD_MAX);
  #endif

#endif

  winZoneName[STDTIME_TZ_FLD_MAX] = 0;

  /* some systems use long names like "Eastern Standard Time" */

  /* see if a standard Windows timezone name is present */
  /* if so, convert it to its timezone database ID */

  if (TranslateStdTimeWinZoneName (winZoneName, wZoneName) == STDTIME_OK)
    {
    if (strcmp (winZoneName, wZoneName) != 0)  /* name was converted */
      {
      strcpy (pZoneName, wZoneName);
      return STDTIME_TRUE;
      }
    }

  /* if not a standard Windows time zone, another phrase might be present */

  /* if so, copy only initial letters of winZoneName */
  /* we look for the string " Time" (case insensitive) */
  /* at the end of the name */

  if (Bool_StdTimeTz_HasTimePhrase (winZoneName))
    {
    /* flag set on so initial letter always copied */
    STDTIME_BOOL            copyNeeded = STDTIME_TRUE;

    j = 0;

    for (i=0; winZoneName[i]; i++)
      {
      if (j == STDTIME_TZ_FLD_MAX) break;

      if (isalpha (winZoneName[i]))
        {
        if (copyNeeded)
          {
          pZoneName[j++] = (char) toupper (winZoneName[i]);
          copyNeeded = STDTIME_FALSE;
          }
        }

      else
        {
        /* a copy is needed after a blank, but we allow for the */
        /* possibility of punctuation, though this is unlikely. */
        /* so, the trigger condition is non-alpha rather than blank. */

        copyNeeded = STDTIME_TRUE;
        }

      } /* for */

    pZoneName[j] = 0;
    }

  else
    {
    strcpy (pZoneName, winZoneName);
    }

  return STDTIME_TRUE;

  } /* Bool_StdTimeTz_GetName */


/*-***************************************************************************/
/*            Bool_StdTimeTz_GetFieldValue - PRIVATE FUNCTION                */
/*  fetch a field value from the timezone database file.  if the requested   */
/*  field is the first or last, it got "merged" by the C compiler, since the */
/*  csv file does not end each line with a trailing comma. we scan these     */
/*  fields and split them apart.  other fields are returned as is.           */
/*****************************************************************************/

static STDTIME_BOOL         Bool_StdTimeTz_GetFieldValue (
  char *                    /*O*/ pValue,
  int32_t                   /*I*/ field,
  int32_t                   /*I*/ line)
  {
  /***************************************************************************/
  /*                                                                         */
  /*  Access the timezone database file from Boost.org as a C table.         */
  /*  The Boost file is a comma-separated-value (csv) file.  This is similar */
  /*  to a list of strings in an array of char pointers.  However, the last  */
  /*  value on each line has no trailing comma.  This makes the C compiler   */
  /*  concatenate the last value of one line with the first value of the     */
  /*  next line.  This reduces the number of values per line by one, and     */
  /*  merges together two unrelated field values.  However, it is desirable  */
  /*  to use the Boost file unmodified, so we have to account for this.      */
  /*                                                                         */
  /*  Each line in the Boost timezone file has 11 fields. Since field 11 has */
  /*  no trailing comma, when used as a C string-array initializer, field 11 */
  /*  of one line is concatenated with field 1 of the next line.             */
  /*                                                                         */
  /*  To undo this, the following steps are taken:                           */
  /*                                                                         */
  /*  1.  The first 10 fields (column headings) of the table are ignored.    */
  /*                                                                         */
  /*  2.  Field 1 is a timezone ID such as "America/Chicago". The beginning  */
  /*      of a timezone ID may be found by finding the first '/' of a field, */
  /*      then the last uppercase letter that preceded the '/' is the start  */
  /*      of the ID field.                                                   */
  /*                                                                         */
  /*  3.  Field 11 is the DST end time, normally of the format "+00:00:00".  */
  /*      If the field starts with '+', '-' or digit, the end of the field   */
  /*      is found by scanning forward until a character that is neither a   */
  /*      digit nor ':' is found.                                            */
  /*                                                                         */
  /*  4.  In terms of C string values, the timezone database file appears as */
  /*      follows, where the notation '10:' means 10 string values:          */
  /*                                                                         */
  /*      10: [ column-heading 1 thru column-heading 10 of data line 1 ]     */
  /*                                                                         */
  /*      1: [ column-heading 11 + field 1       of data line 2 ]            */
  /*      9: [ field 2 thru field 10             of data line 2 ]            */
  /*                                                                         */
  /*      1: [ field 11 of data line 2 + field 1 of data line 3 ]            */
  /*      9: [ field 2 thru field 10             of data line 3 ]            */
  /*                                                                         */
  /*      ...                                                                */
  /*                                                                         */
  /*      1: [ field 11 of data line 378 + field 1 of data line 379 ]        */
  /*      9: [ field 2 thru field 10               of data line 379 ]        */
  /*                                                                         */
  /*      1: [ field 11                            of data line 379 ]        */
  /*      9: [ dummy field 2 thru dummy field 10   of data line 380 ]        */
  /*                                                                         */
  /*      It may be seen that the first 10 fields are skipped, and the       */
  /*      repeating values are grouped by 10, plus one at the end.           */
  /*                                                                         */
  /*  5.  By padding the initialization with 9 null strings, a structure     */
  /*      containing 10 char pointers can be defined, to make references     */
  /*      to to individual fields easier.  The actual number of data lines   */
  /*      is 2 less than the apparent number.  Example:                      */
  /*                                                                         */
  /*          380 - (column-heading line) - (dummy last line) = 378          */
  /*                                                                         */
  /*  6.  The usable array ranges from [1] to [378].  Entry 0 is not used,   */
  /*      and entry 379 is only used to get the DST END TIME for entry 378.  */
  /*                                                                         */
  /*  6.  The field that has the combined value of field 11 + field 1 is     */
  /*      called the 'merged' field, and must be split to get 1 and 11.      */
  /*                                                                         */
  /*  7.  Field 1 would have been the ID, and field 11 would have been the   */
  /*      DST END TIME if the merging had not taken place.                   */
  /*                                                                         */
  /*  8.  The numbers 378, 379, 380 above are only example values in effect  */
  /*      when this code was written, and are subject to change.             */
  /*                                                                         */
  /*  9.  The above considerations apply only if the file is merged, as      */
  /*      indicated by the STDTIME_MERGED_CSV define.  if it is unmerged,    */
  /*      the file looks like a simple list of strings and is accessed       */
  /*      accordingly, without having to parse and unmerge any fields.       */
  /*                                                                         */
  /***************************************************************************/

  static STDTIME_TZ_DEF       Pvt_StdTimeTz_Def[] =
    {
#include "stdtime_timezone_csv.h"

  /* dummy fields are added if csv is merged */

#ifdef STDTIME_MERGED_CSV
    , "" , "" , "" , "" , "" , "" , "" , "" , ""
#endif /* STDTIME_MERGED_CSV */

    };


  if (pValue == NULL)
    {
    return STDTIME_FALSE;
    }

  if ((field < STDTIME_TZ_ID          )
  ||  (field > STDTIME_TZ_DST_END_TIME)
  ||  (line  < 1                      )
  ||  (line  > STDTIME_TZ_LINE_MAX    ))
    {
    pValue[0] = 0;          /* illegal field or line number */
    return STDTIME_FALSE;
    }

#ifdef STDTIME_MERGED_CSV

  if (field == STDTIME_TZ_ID)
    {
    /* ID field starts at last upper case letter before first '/' */
    /* within the merged field of the current line */

    /* in case user defines an ID like US/Michigan or USA/Michigan */
    /* we start the field there. method: if there is a span of upper-case */
    /* letters preceding the first '/', the first upper-case letter is the */
    /* start of the field.  otherwise, if the first upper-case letter is */
    /* preceded by a digit, that is where the field starts. */

    char *                  scan;
    char *                  first_uc = NULL;
    char *                  last_uc = NULL;

    for (scan = Pvt_StdTimeTz_Def[line].pField[STDTIME_TZ_MERGED];
         *scan;
         scan++)
      {
      if ((scan[0] >= '0') && (scan[0] <= '9')
      &&  (scan[1] >= 'A') && (scan[1] <= 'Z'))
        {
        /* a time-to-name transition has been found, such as: */
        /* "+02:00:00" followed by "America/New_York".        */
        /* note use of 'scan+1' for the start of the field.   */

        strncpy (pValue, scan+1, STDTIME_TZ_FLD_MAX);
        pValue [STDTIME_TZ_FLD_MAX] = 0;
        return STDTIME_TRUE;
        }

      if ((*scan >= 'A') && (*scan <= 'Z'))
        {
        last_uc = scan;

        if (first_uc == NULL)
          {
          first_uc = scan;
          }
        }

      else if (*scan == '/')
        {
        if (last_uc == NULL)
          {
          strcpy (pValue, "*** missing ID");
          pValue[0] = 0;        /* missing ID */
          return STDTIME_FALSE;
          }

        else
          {
          /* if there was a span of uc letters, field starts at first one */

          if (first_uc != NULL)
            {
            strncpy (pValue, first_uc, STDTIME_TZ_FLD_MAX);
            }

          else
            {
            strncpy (pValue, last_uc, STDTIME_TZ_FLD_MAX);
            }

          pValue [STDTIME_TZ_FLD_MAX] = 0;
          return STDTIME_TRUE;
          }
        }

      else
        {
        /* current char at *scan is neither uc letter nor '/' */
        first_uc = NULL;
        }

      } /* for */

      /* at this point, we reached end of string but '/' was not found */

      strcpy (pValue, "*** malformed");
      pValue[0] = 0;        /* missing '/' */
      return STDTIME_FALSE;

    } /* if (field == STDTIME_TZ_ID) */


  else if (field == STDTIME_TZ_DST_END_TIME)
    {
    /* END TIME field starts at the beginning of the merged field */
    /* the next line.  END TIME looks like +00:00:00 */

    char *                  scan;
    int32_t                 len;

    pValue[0] = 0;          /* END TIME field may be omitted */

    scan = Pvt_StdTimeTz_Def[line+1].pField[STDTIME_TZ_MERGED];

    if ( (scan[0] == '+')
    ||   (scan[0] == '-')
    ||   (isdigit (scan[0])) )
      {
      for (len=0; len < STDTIME_TZ_FLD_MAX; len++)
        {
        if ( (scan[len] == '+')
        ||   (scan[len] == '-')
        ||   (scan[len] == ':')
        ||   (isdigit (scan[len])) )
          {
          pValue[len] = scan[len];
          }

        else
          {
          break;            /* reached end of END TIME field */
          }

        } /* for */

      pValue[len] = 0;

      } /* if */

    } /* if (field == STDTIME_TZ_DST_END_TIME) */

  else

#endif /* STDTIME_MERGED_CSV */

    /* copy normal (non-merged) field */
    {
    strncpy (pValue, Pvt_StdTimeTz_Def[line].pField[field],
      STDTIME_TZ_FLD_MAX);
    pValue [STDTIME_TZ_FLD_MAX] = 0;
    }

  return STDTIME_TRUE;

  } /* Bool_StdTimeTz_GetFieldValue */


/*-***************************************************************************/
/*            TranslateStdTimeZoneName                                       */
/*  see if a time zone name like EST is a nonunique name with a preferred    */
/*  zone ID.  if so, translate the name to a preferred ID.                   */
/*  return STDTIME_TRUE if translation is successful, even if not changed.   */
/*****************************************************************************/

STDTIME_RC                  TranslateStdTimeZoneName (
  const char *              /*I*/ pZoneName,
  char *                    /*O*/ pZoneID)
  {
  int32_t                   i;

  /***************************************************************************/
  /*  Pvt_StdTimeTz_TranTable - used to translate non-unique timezone        */
  /*  abbreviations like EST into unique timezone database IDs like          */
  /*  "America/New_York".                                                    */
  /*                                                                         */
  /*  note that both standard and DST get mapped the same way, so that       */
  /*  either EST or EDT will convert to the same ID, "America/New_York".     */
  /*                                                                         */
  /*  translation assumes the most common, most likely definition. Where a   */
  /*  timezone abbreviation involves US timezones, common high-population    */
  /*  areas are picked: New York, Chicago, Denver, Los Angeles.  For other   */
  /*  zones, similar large, high-population areas are picked. These choices  */
  /*  are somewhat arbitrary, of course, but will suffice for most purposes. */
  /***************************************************************************/

  static STDTIME_TZTRAN       Pvt_StdTimeTz_TranTable[] =
    {
      { "ADT" , "America/Halifax"      },
      { "AKDT", "America/Anchorage"    },
      { "AKST", "America/Anchorage"    },
      { "AMT" , "America/Cuiaba"       },
      { "ART" , "America/Buenos_Aires" },
      { "AST" , "America/Halifax"      },
      { "BRST", "America/Sao_Paulo"    },
      { "BRT" , "America/Sao_Paulo"    },
      { "CAT" , "Africa/Lusaka"        },
      { "CDT" , "America/Chicago"      },
      { "CEST", "Europe/Paris"         },
      { "CET" , "Europe/Paris"         },
      { "CST" , "America/Chicago"      },
      { "EAT" , "Africa/Nairobi"       },
      { "EDT" , "America/New_York"     },
      { "EEST", "Europe/Helsinki"      },
      { "EET" , "Europe/Helsinki"      },
      { "EST" , "America/New_York"     },
      { "GMT" , "Europe/London"        },
      { "GST" , "Asia/Dubai"           },
      { "ICT" , "Asia/Bangkok"         },
      { "MDT" , "America/Denver"       },
      { "MST" , "America/Denver"       },
      { "NZDT", "Pacific/Auckland"     },
      { "NZST", "Pacific/Auckland"     },
      { "PDT" , "America/Los_Angeles"  },
      { "PST" , "America/Los_Angeles"  },
      { "SAST", "Africa/Johannesburg"  },
      { "WAT" , "Africa/Lagos"         },
      { "WEST", "Europe/Lisbon"        },
      { "WET" , "Europe/Lisbon"        },
      { "WST" , "Australia/Perth"      },
      { NULL,   NULL                   }
    };

  STDTIME_ENUM_FUNC (TranslateStdTimeZoneName)


  if ((pZoneName == NULL) || (pZoneID == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  /* copy name to result field in case not found */
  strncpy (pZoneID, pZoneName, STDTIME_TZ_FLD_MAX);

  for (i=0; Pvt_StdTimeTz_TranTable[i].pZoneAlias != NULL; i++)
    {
    if (Bool_StdTimeTz_StrEq (
          pZoneName, Pvt_StdTimeTz_TranTable[i].pZoneAlias))
      {
      strncpy (pZoneID, Pvt_StdTimeTz_TranTable[i].pZoneID,
        STDTIME_TZ_FLD_MAX);
      break;
      }
    }

  pZoneID[STDTIME_TZ_FLD_MAX] = 0;
  STDTIME_RET_OK;

  } /* TranslateStdTimeZoneName */


/*-***************************************************************************/
/*            TranslateStdTimeWinZoneName                                    */
/*  convert a Windows-specific timezone string to a TimeZone ID.             */
/*  for example, "Eastern Standard Time" is converted to "America/New_York". */
/*  return STDTIME_TRUE if translation is successful, even if not changed.   */
/*****************************************************************************/

STDTIME_RC                  TranslateStdTimeWinZoneName (
  const char *              /*I*/ pZoneName,
  char *                    /*O*/ pZoneID)
  {
  int32_t                   i;

  /***************************************************************************/
  /*  Pvt_StdTimeTz_WinZoneTable - used to translate Windows-specific        */
  /*  timezone abbreviations like "Eastern Standard Time" into unique        */
  /*  timezone database IDs like "America/New_York".                         */
  /*                                                                         */
  /*  this translation only works if the standard names provided by MS have  */
  /*  not been tampered with or added to.  For example, if someone adds a    */
  /*  timezone called "Michigan Standard Time" we can't handle it.           */
  /*                                                                         */
  /*  note that both Standard and Daylight get mapped the same way, so that  */
  /*  either "Eastern Standard Time" or "Eastern Standard Time" will convert */
  /*  to the same ID, "America/New_York".                                    */
  /***************************************************************************/

  static STDTIME_TZTRAN       Pvt_StdTimeTz_WinZoneTable[] =
    {
        /* Windows timezone name string */    /* timezone database TZ ID */

      { "AUS Central Daylight Time"         , "Australia/Darwin"            },
      { "AUS Central Standard Time"         , "Australia/Darwin"            },
      { "AUS Eastern Daylight Time"         , "Australia/Melbourne"         },
      { "AUS Eastern Standard Time"         , "Australia/Melbourne"         },
      { "Afghanistan Daylight Time"         , "Asia/Kabul"                  },
      { "Afghanistan Standard Time"         , "Asia/Kabul"                  },
      { "Alaskan Daylight Time"             , "America/Nome"                },
      { "Alaskan Standard Time"             , "America/Nome"                },
      { "Arab Daylight Time"                , "Asia/Riyadh"                 },
      { "Arab Standard Time"                , "Asia/Riyadh"                 },
      { "Arabian Daylight Time"             , "Asia/Muscat"                 },
      { "Arabian Standard Time"             , "Asia/Muscat"                 },
      { "Arabic Daylight Time"              , "Asia/Baghdad"                },
      { "Arabic Standard Time"              , "Asia/Baghdad"                },
      { "Atlantic Daylight Time"            , "America/Glace_Bay"           },
      { "Atlantic Standard Time"            , "America/Glace_Bay"           },
      { "Azores Daylight Time"              , "Atlantic/Azores"             },
      { "Azores Standard Time"              , "Atlantic/Azores"             },
      { "Canada Central Daylight Time"      , "America/Regina"              },
      { "Canada Central Standard Time"      , "America/Regina"              },
      { "Cape Verde Daylight Time"          , "Atlantic/Cape_Verde"         },
      { "Cape Verde Standard Time"          , "Atlantic/Cape_Verde"         },
      { "Caucasus Daylight Time"            , "Asia/Tbilisi"                },
      { "Caucasus Standard Time"            , "Asia/Tbilisi"                },
      { "Cen. Australia Daylight Time"      , "Australia/Adelaide"          },
      { "Cen. Australia Standard Time"      , "Australia/Adelaide"          },
      { "Central America Daylight Time"     , "America/El_Salvador"         },
      { "Central America Standard Time"     , "America/El_Salvador"         },
      { "Central Asia Daylight Time"        , "Asia/Dhaka"                  },
      { "Central Asia Standard Time"        , "Asia/Dhaka"                  },
      { "Central Daylight Time"             , "America/Chicago"             },
      { "Central Europe Daylight Time"      , "Europe/Prague"               },
      { "Central Europe Standard Time"      , "Europe/Prague"               },
      { "Central European Daylight Time"    , "Europe/Warsaw"               },
      { "Central European Standard Time"    , "Europe/Warsaw"               },
      { "Central Pacific Daylight Time"     , "Asia/Magadan"                },
      { "Central Pacific Standard Time"     , "Asia/Magadan"                },
      { "Central Standard Time"             , "America/Chicago"             },
      { "China Daylight Time"               , "Asia/Hong_Kong"              },
      { "China Standard Time"               , "Asia/Hong_Kong"              },
      { "Dateline Daylight Time"            , "Pacific/Kwajalein"           },
      { "Dateline Standard Time"            , "Pacific/Kwajalein"           },
      { "E. Africa Daylight Time"           , "Africa/Nairobi"              },
      { "E. Africa Standard Time"           , "Africa/Nairobi"              },
      { "E. Australia Daylight Time"        , "Australia/Brisbane"          },
      { "E. Australia Standard Time"        , "Australia/Brisbane"          },
      { "E. Europe Daylight Time"           , "Europe/Bucharest"            },
      { "E. Europe Standard Time"           , "Europe/Bucharest"            },
      { "E. South America Daylight Time"    , "America/Sao_Paulo"           },
      { "E. South America Standard Time"    , "America/Sao_Paulo"           },
      { "Eastern Daylight Time"             , "America/New_York"            },
      { "Eastern Standard Time"             , "America/New_York"            },
      { "Egypt Daylight Time"               , "Africa/Cairo"                },
      { "Egypt Standard Time"               , "Africa/Cairo"                },
      { "Ekaterinburg Daylight Time"        , "Asia/Yekaterinburg"          },
      { "Ekaterinburg Standard Time"        , "Asia/Yekaterinburg"          },
      { "FLE Daylight Time"                 , "Europe/Helsinki"             },
      { "FLE Standard Time"                 , "Europe/Helsinki"             },
      { "Fiji Daylight Time"                , "Pacific/Fiji"                },
      { "Fiji Standard Time"                , "Pacific/Fiji"                },
      { "GMT Daylight Time"                 , "Europe/London"               },
      { "GMT Standard Time"                 , "Europe/London"               },
      { "GTB Daylight Time"                 , "Europe/Athens"               },
      { "GTB Standard Time"                 , "Europe/Athens"               },
      { "Greenland Daylight Time"           , "America/Godthab"             },
      { "Greenland Standard Time"           , "America/Godthab"             },
      { "Greenwich Daylight Time"           , "Africa/Monrovia"             },
      { "Greenwich Standard Time"           , "Africa/Monrovia"             },
      { "Hawaiian Daylight Time"            , "Pacific/Honolulu"            },
      { "Hawaiian Standard Time"            , "Pacific/Honolulu"            },
      { "India Daylight Time"               , "Asia/Calcutta"               },
      { "India Standard Time"               , "Asia/Calcutta"               },
      { "Iran Daylight Time"                , "Asia/Tehran"                 },
      { "Iran Standard Time"                , "Asia/Tehran"                 },
      { "Jerusalem Daylight Time"           , "Asia/Jerusalem"              },
      { "Jerusalem Standard Time"           , "Asia/Jerusalem"              },
      { "Korea Daylight Time"               , "Asia/Seoul"                  },
      { "Korea Standard Time"               , "Asia/Seoul"                  },
      { "Malay Peninsula Daylight Time"     , "Asia/Singapore"              },
      { "Malay Peninsula Standard Time"     , "Asia/Singapore"              },
      { "Mexico Daylight Time"              , "America/Mexico_City"         },
      { "Mexico Standard Time"              , "America/Mexico_City"         },
      { "Mid-Atlantic Daylight Time"        , "Atlantic/South_Georgia"      },
      { "Mid-Atlantic Standard Time"        , "Atlantic/South_Georgia"      },
      { "Mountain Daylight Time"            , "America/Denver"              },
      { "Mountain Standard Time"            , "America/Denver"              },
      { "Myanmar Daylight Time"             , "Asia/Rangoon"                },
      { "Myanmar Standard Time"             , "Asia/Rangoon"                },
      { "N. Central Asia Daylight Time"     , "Asia/Novosibirsk"            },
      { "N. Central Asia Standard Time"     , "Asia/Novosibirsk"            },
      { "Nepal Daylight Time"               , "Asia/Katmandu"               },
      { "Nepal Standard Time"               , "Asia/Katmandu"               },
      { "New Zealand Daylight Time"         , "Pacific/Auckland"            },
      { "New Zealand Standard Time"         , "Pacific/Auckland"            },
      { "Newfoundland Daylight Time"        , "America/St_Johns"            },
      { "Newfoundland Standard Time"        , "America/St_Johns"            },
      { "North Asia Daylight Time"          , "Asia/Krasnoyarsk"            },
      { "North Asia East Daylight Time"     , "Asia/Irkutsk"                },
      { "North Asia East Standard Time"     , "Asia/Irkutsk"                },
      { "North Asia Standard Time"          , "Asia/Krasnoyarsk"            },
      { "Pacific Daylight Time"             , "America/Los_Angeles"         },
      { "Pacific SA Daylight Time"          , "America/Santiago"            },
      { "Pacific SA Standard Time"          , "America/Santiago"            },
      { "Pacific Standard Time"             , "America/Los_Angeles"         },
      { "Romance Daylight Time"             , "Europe/Paris"                },
      { "Romance Standard Time"             , "Europe/Paris"                },
      { "Russian Daylight Time"             , "Europe/Moscow"               },
      { "Russian Standard Time"             , "Europe/Moscow"               },
      { "SA Eastern Daylight Time"          , "America/Buenos_Aires"        },
      { "SA Eastern Standard Time"          , "America/Buenos_Aires"        },
      { "SA Pacific Daylight Time"          , "America/Bogota"              },
      { "SA Pacific Standard Time"          , "America/Bogota"              },
      { "SA Western Daylight Time"          , "America/Caracas"             },
      { "SA Western Standard Time"          , "America/Caracas"             },
      { "SE Asia Daylight Time"             , "Asia/Bangkok"                },
      { "SE Asia Standard Time"             , "Asia/Bangkok"                },
      { "Samoa Daylight Time"               , "Pacific/Midway"              },
      { "Samoa Standard Time"               , "Pacific/Midway"              },
      { "South Africa Daylight Time"        , "Africa/Harare"               },
      { "South Africa Standard Time"        , "Africa/Harare"               },
      { "Sri Lanka Daylight Time"           , "Asia/Colombo"                },
      { "Sri Lanka Standard Time"           , "Asia/Colombo"                },
      { "Taipei Daylight Time"              , "Asia/Taipei"                 },
      { "Taipei Standard Time"              , "Asia/Taipei"                 },
      { "Tasmania Daylight Time"            , "Australia/Hobart"            },
      { "Tasmania Standard Time"            , "Australia/Hobart"            },
      { "Tokyo Daylight Time"               , "Asia/Tokyo"                  },
      { "Tokyo Standard Time"               , "Asia/Tokyo"                  },
      { "Tonga Daylight Time"               , "Pacific/Tongatapu"           },
      { "Tonga Standard Time"               , "Pacific/Tongatapu"           },
      { "US Eastern Daylight Time"          , "America/New_York"            },
      { "US Eastern Standard Time"          , "America/New_York"            },
      { "US Mountain Daylight Time"         , "America/Phoenix"             },
      { "US Mountain Standard Time"         , "America/Phoenix"             },
      { "Vladivostok Daylight Time"         , "Asia/Vladivostok"            },
      { "Vladivostok Standard Time"         , "Asia/Vladivostok"            },
      { "W. Australia Daylight Time"        , "Australia/Perth"             },
      { "W. Australia Standard Time"        , "Australia/Perth"             },
      { "W. Central Africa Daylight Time"   , "Africa/Lagos"                },
      { "W. Central Africa Standard Time"   , "Africa/Lagos"                },
      { "W. Europe Daylight Time"           , "Europe/Rome"                 },
      { "W. Europe Standard Time"           , "Europe/Rome"                 },
      { "West Asia Daylight Time"           , "Asia/Karachi"                },
      { "West Asia Standard Time"           , "Asia/Karachi"                },
      { "West Pacific Daylight Time"        , "Pacific/Guam"                },
      { "West Pacific Standard Time"        , "Pacific/Guam"                },
      { "Yakutsk Daylight Time"             , "Asia/Yakutsk"                },
      { "Yakutsk Standard Time"             , "Asia/Yakutsk"                },
      { NULL                                , NULL                          }

    }; /* Pvt_StdTimeTz_WinZoneTable */


  STDTIME_ENUM_FUNC (TranslateStdTimeWinZoneName)

  if ((pZoneName == NULL) || (pZoneID == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  /* copy name to result field in case not found */
  strncpy (pZoneID, pZoneName, STDTIME_TZ_FLD_MAX);

  for (i=0; Pvt_StdTimeTz_WinZoneTable[i].pZoneAlias != NULL; i++)
    {
    if (Bool_StdTimeTz_StrEq (
          pZoneName, Pvt_StdTimeTz_WinZoneTable[i].pZoneAlias))
      {
      strncpy (pZoneID, Pvt_StdTimeTz_WinZoneTable[i].pZoneID,
        STDTIME_TZ_FLD_MAX);
      break;
      }
    }

  pZoneID[STDTIME_TZ_FLD_MAX] = 0;
  STDTIME_RET_OK;

  } /* TranslateStdTimeWinZoneName */


/*-***************************************************************************/
/*            Int_StdTimeTz_NameToID - PRIVATE FUNCTION                      */
/*  convert a zone name like EST to a zone ID like "America/New_York".       */
/*  this is required to look up values from the timezone database file,      */
/*  since its unique key is zone ID, not zone name (which is non-unique).    */
/*                                                                           */
/*  return ID of time zone and index into table, else return 0 if not found. */
/*****************************************************************************/

static int32_t              Int_StdTimeTz_NameToID (
  const char *              /*I*/ pZoneName,
  char *                    /*O*/ pZoneID)
  {
  int32_t                   i;
  int32_t                   n;
  char                      wZoneID [STDTIME_TZ_FLD_SIZE];
  char                      tzValue [STDTIME_TZ_FLD_SIZE];


  if ((pZoneName == NULL) || (pZoneID == NULL))
    {
    return 0;
    }

  if (*pZoneName == 0)      /* empty string */
    {
    return 0;
    }

  /* if env name has a translation, use it.                               */

  /* this is required when we only have a string like EST and we need     */
  /* to get to "America/New_York" even when EST is a non-unique key.      */

  /* the translation converts an acronym like EST into its 'preferred'    */
  /* timezone.  that is, EST can mean several things; but if provided,    */
  /* it will take on the most likely meaning (Eastern Standard Time)      */
  /* as defined by the "America/New_York" timezone database entry,        */
  /* because that is what the preferred translation results in.           */

  /* for example, EST also applies to "America/Jamaica" which has no DST, */
  /* and to "Australia/Sydney" which is in a completely different zone.   */
  /* however, users providing EST will get "America/New_York" by default. */

  if (TranslateStdTimeZoneName (pZoneName, pZoneID) != STDTIME_OK)
    {
    return 0;
    }

  /* look for name in complete timezone database table */

  /* we don't know which name is used (ID or zone name), so check them all */
  /* we look for the full timezone ID like "America/New_York" first. */
  /* then we try to find abbreviations like EST and EDT. */

  /* note that it makes NO DIFFERENCE whether EST or EDT is specified. */
  /* BOTH refer to "America/New_York".  The decision as to whether a */
  /* date and time are standard or DST time is made later. */

  /* even if translated, we look up the ID name to make sure it's valid */

  /* there is no guarantee that the table is sorted, so we go through it */
  /* the hard way, one at a time.  in fact, the Boost.org table is out of */
  /* order in places, and is not ordered by its unique (primary) key of */
  /* zone ID. */

  /* we don't have access to STDTIME_TZ_LINE_MAX because it's private to */
  /* Bool_StdTimeTz_GetFieldValue(). so, just call it until it returns */
  /* a usable value or false. */

  for (i=1;; i++)
    {
    if (! Bool_StdTimeTz_GetFieldValue (wZoneID, STDTIME_TZ_ID, i))
      {
      break;    /* error or reached end of list */
      }

    if (Bool_StdTimeTz_StrEq (wZoneID, pZoneID))
      {
      /* got value.  copy value from table to normalize it */

      strncpy (pZoneID, wZoneID, STDTIME_TZ_FLD_MAX);
      pZoneID[STDTIME_TZ_FLD_MAX] = 0;

      return i;     /* index into timezone table */
      }

    /* try other names.  if found, use wZoneID as return value */

    for (n=STDTIME_TZ_STD_ABBR; n <= STDTIME_TZ_DST_NAME; n++)
      {
      Bool_StdTimeTz_GetFieldValue (tzValue, n, i);

      if (Bool_StdTimeTz_StrEq (tzValue, pZoneID))
        {
        /* got value. copy saved wZoneID as the pZoneID value */

        strncpy (pZoneID, wZoneID, STDTIME_TZ_FLD_MAX);
        pZoneID[STDTIME_TZ_FLD_MAX] = 0;

        return i;     /* index into timezone table */
        }

      } /* for n */

    } /* for i */
    return 0;

  } /* Int_StdTimeTz_NameToID */


/*-***************************************************************************/
/*            StdTimeZoneDataToInfo                                          */
/*  copy raw char data from a STDTIMEZONE_DATA structure into a              */
/*  STDTIMEZONE_INFO, validating time and rule fields.                       */
/*  Note: only abbreviated zone names are processed.  The "full" names are   */
/*  not stored in STDTIMEZONE_INFO so the corresponding data fields are      */
/*  ignored.  in the Boost.org timezone database file, most "full" names     */
/*  are just copies of the abbreviated name anyway, so keeping the full name */
/*  is of almost no benefit.                                                 */
/*****************************************************************************/


STDTIME_RC                  StdTimeZoneDataToInfo (
  const STDTIMEZONE_DATA *  /*I*/ pTzData,
  STDTIMEZONE_INFO *        /*O*/ pTzInfo)
  {
  STDTIMEZONE_INFO          zeroTzInfo = {{0}};
  STDTIME_ENUM_FUNC (StdTimeZoneDataToInfo)

  if (pTzInfo == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pTzInfo = zeroTzInfo;

  if (pTzData == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  /***** zoneID **************************************************************/

  strncpy (pTzInfo->zoneID,
           pTzData->tzField[STDTIME_TZ_ID],
           STDTIME_TZ_FLD_MAX);

  pTzInfo->zoneID[STDTIME_TZ_FLD_MAX] = 0;

  /***** stdAbbr *************************************************************/

  strncpy (pTzInfo->stdAbbr,
           pTzData->tzField[STDTIME_TZ_STD_ABBR],
           STDTIME_TZ_ABBR_MAX);

  pTzInfo->stdAbbr[STDTIME_TZ_ABBR_MAX] = 0;

  /***** dstAbbr *************************************************************/

  strncpy (pTzInfo->dstAbbr,
           pTzData->tzField[STDTIME_TZ_DST_ABBR],
           STDTIME_TZ_ABBR_MAX);

  pTzInfo->dstAbbr[STDTIME_TZ_ABBR_MAX] = 0;

  /***** gmtToLocOffset ******************************************************/

  if STDTIME_IFNOT (Rc_StdTimeTz_GetTime (
        pTzData->tzField[STDTIME_TZ_GMT_TO_LOC_OFFSET],
        &(pTzInfo->gmtToLocOffset)))
    {
    STDTIME_RET_RC;
    }

  /***** stdToDstOffset ******************************************************/

  if STDTIME_IFNOT (Rc_StdTimeTz_GetTime (
        pTzData->tzField[STDTIME_TZ_STD_TO_DST_OFFSET],
        &(pTzInfo->stdToDstOffset)))
    {
    STDTIME_RET_RC;
    }

  /***** dstStartRule ********************************************************/

  if STDTIME_IFNOT (Rc_StdTimeTz_GetRule (
        pTzData->tzField[STDTIME_TZ_DST_START_RULE],
        &(pTzInfo->dstStartRule)))
    {
    STDTIME_RET_RC;
    }

  /***** dstStartTime ********************************************************/

  if STDTIME_IFNOT (Rc_StdTimeTz_GetTime (
        pTzData->tzField[STDTIME_TZ_DST_START_TIME],
        &(pTzInfo->dstStartTime)))
    {
    STDTIME_RET_RC;
    }

  if (pTzInfo->dstStartTime.sign < 0)
    {
    STDTIME_RET_EC (negative_dst_start_time);
    /* dst start/end times must be positive */
    }

  /***** dstEndRule **********************************************************/

  if STDTIME_IFNOT (Rc_StdTimeTz_GetRule (
        pTzData->tzField[STDTIME_TZ_DST_END_RULE],
        &(pTzInfo->dstEndRule)))
    {
    STDTIME_RET_RC;
    }

  /***** dstEndTime **********************************************************/

  if STDTIME_IFNOT (Rc_StdTimeTz_GetTime (
        pTzData->tzField[STDTIME_TZ_DST_END_TIME],
        &(pTzInfo->dstEndTime)))
    {
    STDTIME_RET_RC;
    }

  if (pTzInfo->dstEndTime.sign < 0)
    {
    STDTIME_RET_EC (negative_dst_end_time);
    /* dst start/end times must be positive */
    }

  /***************************************************************************/

  STDTIME_RET_OK;

  } /* StdTimeZoneDataToInfo */


/*-***************************************************************************/
/*            Rc_ParseStdTimeZoneData - PRIVATE FUNCTION                     */
/*  scan a line from the timezone database file, and store into a            */
/*  STDTIMEZONE_DATA structure.  then extract using StdTimeZoneDataToInfo.   */
/*  each line is supposed to contain 11 strings, enclosed in "" quotes, and  */
/*  separated by commas.  no provision for escapes or embedded quotes is     */
/*  provided, since no such strings exist in the timezone database file.     */
/*  spaces or tabs between fields are ignored.                               */
/*****************************************************************************/

static STDTIME_RC           Rc_ParseStdTimeZoneData (
  const char *              /*I*/ pText,
  STDTIMEZONE_INFO *        /*O*/ pZoneInfo)
  {
  STDTIMEZONE_INFO          zeroZoneInfo = STDTIMEZONE_INFO_ZERO;
  STDTIMEZONE_DATA          tzData;
  char                      wValue [STDTIME_TZ_FLD_SIZE];
  const char *              scan;
  int32_t                   len;
  int32_t                   i;

  STDTIME_ENUM_FUNC (Rc_ParseStdTimeZoneData)

  if (pZoneInfo == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pZoneInfo = zeroZoneInfo;

  if (pText == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  scan = pText;

  /* ignore a leading comma */

  while ((*scan == ' ') || (*scan == '\t')) scan++;

  if (*scan == ',') scan++;

  while ((*scan == ' ') || (*scan == '\t')) scan++;

  if (*scan != '"')         /* first (and every) field must be quoted */
    {
    STDTIME_RET_EC (invalid_delimiter);
    }

  /* parse each field */

  for (i=0; i < STDTIMEZONE_DATA_FLD_COUNT; i++)
    {
    if (i != 0)                 /* skip comma between fields */
      {
      if (*scan != ',')         /* comma is required */
        {
        STDTIME_RET_EC (invalid_delimiter);
        }

      scan++;
      while ((*scan == ' ') || (*scan == '\t')) scan++;
      }

    if (*scan != '"')           /* leading quote expected */
      {
      STDTIME_RET_EC (invalid_delimiter);
      }

    scan++;                     /* skip over leading quote */
    len = 0;

    while ((*scan) && (*scan != '"') && (len <= STDTIME_TZ_FLD_MAX))
      {
      wValue[len++] = *scan++;  /* copy field value */
      }

    wValue[len] = 0;

    while ((*scan) && (*scan != '"')) scan++;

    if (*scan != '"')           /* trailing quote expected */
      {
      STDTIME_RET_EC (invalid_delimiter);
      }

    /* field found; store into a STDTIMEZONE_DATA structure. element */

    strncpy (tzData.tzField[i], wValue, STDTIME_TZ_FLD_MAX);
    tzData.tzField[i][STDTIME_TZ_FLD_MAX] = 0;

    scan++;                     /* skip over trailing quote */
    while ((*scan == ' ') || (*scan == '\t')) scan++;

    } /* for i */

  /* trailing whitespace (blank, tab) ignored */
  /* line can end with comma, NUL, CR or LF, but nothing else */
  /* we allow for a trailing comma, in case additional fields are */
  /* present on the line. if first 11 fields are valid, ignore others. */

  if ((*scan != 0)
  &&  (*scan != ',')
  &&  (*scan != '\n')
  &&  (*scan != '\r'))
    {
    /* line is improperly terminated; contents questionable */
    STDTIME_RET_EC (invalid_delimiter);
    }

  /* STDTIMEZONE_DATA structure is now fully populated with raw data. */
  /* process individual data fields and convert to STDTIMEZONE_INFO struct */

  STDTIME_RET (StdTimeZoneDataToInfo (&tzData, pZoneInfo));

  } /* Rc_ParseStdTimeZoneData */


/*-***************************************************************************/
/*            GetStdTimeZoneInfo                                             */
/*  based on a zone name, initialize a STDTIMEZONE_INFO structure.           */
/*****************************************************************************/

STDTIME_RC                  GetStdTimeZoneInfo (
  const char *              /*I*/ pZoneName,
  STDTIMEZONE_INFO *        /*O*/ pZoneInfo)
  {
  char                      wZoneName [STDTIME_TZ_FLD_SIZE];
  char                      wZoneID   [STDTIME_TZ_FLD_SIZE];
  char                      wValue    [STDTIME_TZ_FLD_SIZE];
  const char *              scan;
  int32_t                   i;
  int32_t                   n;
  STDTIMEZONE_INFO          zeroZoneInfo = STDTIMEZONE_INFO_ZERO;
  STDTIMEZONE_DATA          tzData;

  STDTIME_ENUM_FUNC (GetStdTimeZoneInfo)

  if (pZoneInfo == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pZoneInfo = zeroZoneInfo;

  if (pZoneName == NULL)        /* NULL zone name means 'local' zone */
    {
    strcpy (wZoneName, "LOCAL");
    }

  else
    {
    /* see if 'name' is actually a timezone database text line */

    scan = pZoneName;
    while ((*scan == ' ') || (*scan == '\t')) scan++;

    if (*scan == 0)               /* empty string */
      {
      STDTIME_RET_EC (missing_timezone_name);
      }

    if ( ( scan[0] == '"')
    ||   ((scan[0] == ',') && (scan[1] == '"')) )
      {
      /* the input string is a timezone database CSV line */
      /* the file may have been 'unmerged' by putting ',' in column 1 */

      STDTIME_RET (Rc_ParseStdTimeZoneData (scan, pZoneInfo));
      }

    strncpy (wZoneName, pZoneName, STDTIME_TZ_FLD_MAX);
    wZoneName[STDTIME_TZ_FLD_MAX] = 0;

    } /* (pZoneName not NULL) */

  if (Bool_StdTimeTz_StrEq (wZoneName, "LOCAL"))
    {
    if (! Bool_StdTimeTz_GetName (wZoneName))
      {
      STDTIME_RET_EC (cannot_determine_local_timezone);
      /* could not find local zone name */
      }
    }

  n = Int_StdTimeTz_NameToID (wZoneName, wZoneID);

  if (n == 0)
    {
    STDTIME_RET_EC (cannot_find_timezone_entry);
    /* could not find timezone database entry */
    }

  /* copy TZ values into TZ data structure */

  /* don't refetch field[0] since we have to scan for it (high overhead) */
  /* just copy the wZoneID we already have. */

  strncpy (tzData.tzField[0], wZoneID, STDTIMEZONE_DATA_FLD_MAX);
  tzData.tzField[0][STDTIMEZONE_DATA_FLD_MAX] = 0;

  for (i=1; i < STDTIMEZONE_DATA_FLD_COUNT; i++)
    {
    if (! Bool_StdTimeTz_GetFieldValue (wValue, i, n))
      {
      STDTIME_RET_EC (cannot_extract_timezone_field);
      }

    strncpy (tzData.tzField[i], wValue, STDTIMEZONE_DATA_FLD_MAX);
    tzData.tzField[i][STDTIMEZONE_DATA_FLD_MAX] = 0;
    }

  /* STDTIMEZONE_DATA structure is now fully populated with raw data. */
  /* process individual data fields and convert to STDTIMEZONE_INFO struct */

  STDTIME_RET (StdTimeZoneDataToInfo (&tzData, pZoneInfo));

  } /* GetStdTimeZoneInfo */


/*-***************************************************************************/
/*            ReadStdTimeZoneInfo                                            */
/*  based on a zone name, initialize a STDTIMEZONE_INFO structure from an    */
/*  external timezone database text file.  The file is opened, searched,     */
/*  and closed once the information is found, or EOF reached.                */
/*****************************************************************************/

STDTIME_RC                  ReadStdTimeZoneInfo (
  const char *              /*I*/ pFileName,
  const char *              /*I*/ pZoneName,
  STDTIMEZONE_INFO *        /*O*/ pZoneInfo)
  {
  STDTIMEZONE_INFO          zoneInfo = {{0}};
  FILE *                    zoneFile;
  char                      wZoneID   [STDTIME_TZ_FLD_SIZE];
  char *                    scan;
  int32_t                   bufsize = 256;
  char                      buf[256+4];

  STDTIME_ENUM_FUNC (ReadStdTimeZoneInfo)

  if (pZoneInfo == NULL)
    {
    STDTIME_RET_EC (null_argument); /* no result parm */
    }

  *pZoneInfo = zoneInfo;

  if ((pFileName == NULL) || (pZoneName == NULL))
    {
    /* if no file name provided, get info from internal table */
    /* if pZoneName is NULL, caller asked for local time */

    STDTIME_RET (GetStdTimeZoneInfo (pZoneName, pZoneInfo));
    }

  if STDTIME_IFNOT (TranslateStdTimeZoneName (pZoneName, wZoneID))
    {
    STDTIME_RET_RC;
    }

  zoneFile = fopen (pFileName, "r");

  if (zoneFile == NULL)
    {
    STDTIME_RET_EC (cannot_open_timezone_file);
    }

  for (;;)
    {
    scan = fgets (buf, bufsize, zoneFile);
    if (scan == NULL)
      {
      break;
      }

    while ((*scan == ' ') || (*scan == '\t')) scan++;

    if (*scan != '"')
      {
      /* line is not from a timezone database file (blank line or comment) */
      continue;
      }

    if STDTIME_IFNOT (Rc_ParseStdTimeZoneData (scan, &zoneInfo))
      {
      /* line is not in right format (maybe header line) */
      continue;
      }

    if ( (Bool_StdTimeTz_StrEq (wZoneID, zoneInfo.zoneID))
    ||   (Bool_StdTimeTz_StrEq (wZoneID, zoneInfo.stdAbbr))
    ||   (Bool_StdTimeTz_StrEq (wZoneID, zoneInfo.dstAbbr)) )
      {
      *pZoneInfo = zoneInfo;
      fclose (zoneFile);
      STDTIME_RET_OK;       /* zone name found */
      }

    } /* for */

  fclose (zoneFile);
  STDTIME_RET_EC (cannot_find_timezone_name);
  /* zone name not found */

  } /* ReadStdTimeZoneInfo */


/*-***************************************************************************/
/*            StdTimeZoneDayOfRule                                           */
/*  given a year and a timezone rule, return the day of the month when the   */
/*  rule applies.  for example, if a rule of '1st Sun in Apr' is applied to  */
/*  the year 2006, the function returns 2, because the first Sunday in       */
/*  April of 2006 is April 2.                                                */
/*****************************************************************************/

STDTIME_RC                  StdTimeZoneDayOfRule (
  int32_t                   /*I*/ year,
  const STDTIME_TZ_RULE *   /*I*/ pRule,
  int32_t *                 /*O*/ pDay)
  {
  int32_t                   dayOfWeek;
  int32_t                   lastDayofMon;
  int32_t                   table[6];
  int32_t                   currDay = 1;
  int32_t                   i;

  STDTIME_ENUM_FUNC (StdTimeZoneDayOfRule)


  if (pDay == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pDay = 0;

  if (pRule == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if ((year < STDTIME_YEAR_MIN)
  ||  (year > STDTIME_YEAR_MAX)
  ||  (pRule->dayOrdinal < 1)
  ||  (pRule->dayOrdinal > STDTIME_TZ_RULE_MAX_DAY_ORDINAL)
  ||  (pRule->dayOfWeek  < 0)
  ||  (pRule->dayOfWeek  > 6)
  ||  (pRule->mon        < 1)
  ||  (pRule->mon        > 12)
  ||  (pRule->dayOfMonth < 0)
  ||  (pRule->dayOfMonth > 31))
    {
    STDTIME_RET_EC (invalid_timezone_rule);
    }

  /* how many days in this month for given year */

  lastDayofMon = StdTimeDaysInYearMon (year, pRule->mon);

  if (lastDayofMon == 0)
    {
    /* cannot determine last day of month - should not happen */
    STDTIME_RET_EC (invalid_timezone_rule);
    }

  if (pRule->dayOfMonth > lastDayofMon)
    {
    /* exact-date or lower-bound date is invalid */
    STDTIME_RET_EC (invalid_timezone_rule);
    }

  /* if exact-date mode, the rule specifies the day of month, just return it */

  if (pRule->dayOrdinal == STDTIME_TZ_RULE_EXACT)
    {
    *pDay = pRule->dayOfMonth;
    STDTIME_RET_OK;
    }

  /* determine what day (Sun-Sat) the first day of the month is */

  if STDTIME_IFNOT (StdTimeGetDayofWeekAndYear (
    year, pRule->mon, currDay, &dayOfWeek, NULL))
    {
    STDTIME_RET_EC (failure_in_api_StdTimeGetDayofWeekAndYear);
    }

  if ((dayOfWeek < 0) || (dayOfWeek > 6))
    {
    /* double-checking function result */
    STDTIME_RET_EC (day_out_of_range);
    }

  /* build a table of dates for the month on the given day */
  /* if the first day of the month is the same day as the rule, use it. */
  /* otherwise, go forward until the day is the same. */
  /* for example, if the rule is: 1st SUN in APR, but the APR 1 is FRI */
  /* then we must skip forward until the day is SUN.  That means the first */
  /* SUN in APR for that year is on APR 3. */

  while (dayOfWeek != pRule->dayOfWeek)
    {
    currDay++;
    dayOfWeek = (dayOfWeek + 1) % 7;
    }

  /* build date table.  for simplicity, table[0] is not used */
  /* because we want the 1st to the 5th dates of a given day */
  /* like 1st SUN, 2nd SUN, ... 5th SUN. */

  for (i=1; i <= 5; i++)
    {
    /* if the rule specifies a lower-bound for the date, check the currDay */
    /* value about to be stored in the table.  if it is >= the bound, we */
    /* have the required date. */

    if (pRule->dayOrdinal == STDTIME_TZ_RULE_LBOUND)
      {
      if (currDay >= pRule->dayOfMonth) /* day is >= the lower bound */
        {
        /* this is the desired date */
        *pDay = currDay;
        STDTIME_RET_OK;
        }
      }

    table [i] = currDay;
    /* once currDay reaches its limit, keep storing it into the table */
    /* at most one such extra value will be stored */
    /* this supports situations like the 5th SUN in FEB when FEB only */
    /* has four Sundays.  here, 5th == last. */

    if ((currDay + 7) <= lastDayofMon)
      {
      currDay += 7;
      }
    }

  /* if the rule specifies a lower-bound for the date, but we got here, */
  /* something went wrong; it should have been resolved by now. */
  /* this check is needed because dayOrdinal cannot be used as a table */
  /* index, since it has a special coded value, not an index value. */

  if (pRule->dayOrdinal == STDTIME_TZ_RULE_LBOUND)
    {
    STDTIME_RET_EC (invalid_timezone_rule);
    }

  /* now, simply grab the right date from the table */

  *pDay = table [pRule->dayOrdinal];
  STDTIME_RET_OK;

  } /* StdTimeZoneDayOfRule */


/*-***************************************************************************/
/*            StdTimeTzTimeToDelta                                           */
/*  convert timezone time offset to a StdTime delta                          */
/*****************************************************************************/

STDTIME_RC                  StdTimeTzTimeToDelta (
  const STDTIME_TZ_TIME *   /*I*/ pTzTime,
  STDTIME_DELTA *           /*O*/ pDelta)
  {
  STDTIME_DELTA             delta = {0};

  STDTIME_ENUM_FUNC (StdTimeTzTimeToDelta)

  if (pDelta == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pDelta = ZeroStdTimeDelta ();

  if (pTzTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if (pTzTime->sign > 0)
    {
    delta.hour = pTzTime->hour;
    delta.min  = pTzTime->min;
    delta.sec  = pTzTime->sec;
    }

  else if (pTzTime->sign < 0)
    {
    delta.hour = -(pTzTime->hour);
    delta.min  = -(pTzTime->min);
    delta.sec  = -(pTzTime->sec);
    }

  *pDelta = delta;
  STDTIME_RET_OK;

  } /* StdTimeTzTimeToDelta */


/*-***************************************************************************/
/*            Rc_FixStdTimeZoneRules                                         */
/*  adjust start/end rules for the given year, if necessary                  */
/*****************************************************************************/

static STDTIME_RC           Rc_FixStdTimeZoneRules (
  int32_t                   /*I*/ year,
  STDTIMEZONE_INFO *        /*IO*/ pZoneInfo)
  {
  char *                    scan;
  char                      group [STDTIME_FIX_TZ_GROUP_SIZE+1];
  char                      region[STDTIME_FIX_TZ_REGION_SIZE+1];
  int32_t                   i;
  int32_t                   len;

/* the struct defining type STDTIME_FIX_TZ_RULES is in stdtime.h */

  static STDTIME_FIX_TZ_RULES fixTable[] =
    {
#include "stdtime_tzrules.h"
    };

  STDTIME_ENUM_FUNC (Rc_FixStdTimeZoneRules)

  if (pZoneInfo == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  /* find group code */

  for (scan = pZoneInfo->zoneID; ; scan++)
    {
    if (*scan == 0)
      {
      /* zoneID has no group code, so cannot fix; OK */

      STDTIME_RET_OK;
      }

    if (*scan == ';') break;
    }

  scan++;     /* skip over ';' */

  if ((*scan == 0) || (*scan == '/'))
    {
    /* group code is zero length, so cannot fix; OK */

    STDTIME_RET_OK;
    }

  len = 0;
  region[0] = 0;

  for (; *scan; scan++)
    {
    if (*scan == '/')
      {
      /* region code follows group code after '/', like "US/NY" */

      strncpy (region, scan+1, STDTIME_FIX_TZ_REGION_SIZE);
      region[STDTIME_FIX_TZ_REGION_SIZE] = 0;
      break;
      }

    if (len >= STDTIME_FIX_TZ_GROUP_SIZE)
      {
      /* group code is too long, ignore it; OK */

      STDTIME_RET_OK;
      }

    group[len++] = *scan;
    group[len] = 0;
    }

  /* try to find year in table for given group and region */
  /* if region in table is null, it matches every region */

  for (i=0; i < (sizeof(fixTable) / sizeof(fixTable[0])); i++)
    {
    if (strcmp (fixTable[i].group, group) != 0)
      {
      continue;     /* group does not match */
      }

    if (fixTable[i].region[0] != 0)
      {
      /* there is a string defining a region in the fix table */

      if (strcmp (fixTable[i].region, region) != 0)
        {
        continue;     /* region does not match */
        }
      }

    if ((year >= fixTable[i].yearLo) && (year <= fixTable[i].yearHi))
      {
      pZoneInfo->dstStartRule = fixTable[i].dstStartRule;
      pZoneInfo->dstStartTime = fixTable[i].dstStartTime;

      pZoneInfo->dstEndRule   = fixTable[i].dstEndRule;
      pZoneInfo->dstEndTime   = fixTable[i].dstEndTime;

      STDTIME_RET_OK;
      }
    }

  /* year not found; accept supplied info rules without change */

  STDTIME_RET_OK;

  } /* Rc_FixStdTimeZoneRules */


/*-***************************************************************************/
/*            StdTimeApiZonedFileTimeToFileTime                              */
/*  convert time for a specific zone or for default zone to GMT time         */
/*****************************************************************************/

STDTIME_RC                  StdTimeApiZonedFileTimeToFileTime (
  const STDTIMEZONE_INFO *      /*I*/ pZoneInfo,
  const STDTIME_WIN_FILETIME *  /*I*/ pLocFileTime,
  STDTIME_WIN_FILETIME *        /*O*/ pGmtFileTime)
  {
  int32_t                   day;
  STDTIME_BOOL              bool_InDst;

  STDTIMEZONE_INFO          info;

  STDTIME_FIELDS            locStdTimeFields;

  STDTIME_FIELDS            locDstStartStdTimeFields = {0};
  STDTIME_FIELDS            locDstEndStdTimeFields   = {0};

  STDTIME_DELTA             gmtToLocDelta;
  STDTIME_DELTA             stdToDstDelta;

  STDTIME_ENUM_FUNC (StdTimeApiZonedFileTimeToFileTime)


  if ((pGmtFileTime == NULL) || (pLocFileTime == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IFNOT (FileTimeToStdTimeFields (pLocFileTime, &locStdTimeFields))
    {
    STDTIME_RET_RC;
    }

  if (pZoneInfo == NULL)
    {
    /* no timezone argument provided, so create default 'local' zone info */

    /* we don't know what the zone ID is. */
    /* NULL means: let library determine the local zone ID and timezone */

    if STDTIME_IFNOT (GetStdTimeZoneInfo (NULL, &info))
      {
      STDTIME_RET_RC;
      }
    }

  else
    {
    info = *pZoneInfo;      /* copy the supplied timezone */
    }

  /* adjust start/end rules for the given year, if necessary */

  if STDTIME_IFNOT (Rc_FixStdTimeZoneRules (locStdTimeFields.year, &info))
    {
    STDTIME_RET_RC;
    }

  /* if 'local' zone is already GMT, and DST not used, don't convert. */
  /* a STDTIME_TZ_TIME field has a 'sign' of 0 when field is ignored */

  if ((info.gmtToLocOffset.sign == 0)
  &&  (info.stdToDstOffset.sign == 0))
    {
    *pGmtFileTime = *pLocFileTime;
    STDTIME_RET_OK;
    }


  if STDTIME_IFNOT (StdTimeTzTimeToDelta (&info.gmtToLocOffset, &gmtToLocDelta))
    {
    STDTIME_RET_RC;
    }

  /* if a 'local' zone does not use DST, just apply the zone offset */
  /* gmtToLocDelta is subtracted from a local time to get a GMT time */
  /* StdTimeTzTimeToDelta() takes care of the sign of the offset */

  if ((info.stdToDstOffset.sign == 0)
  ||  (locStdTimeFields.year < STDTIME_DST_CUTOFF_YEAR))  /* before DST */
    {
    if STDTIME_IF (StdTimeFields_SubDelta (&locStdTimeFields, &gmtToLocDelta))
      {
      /* in spite of its name, 'locStdTimeFields' is a GMT time */
      STDTIME_RET (StdTimeFieldsToFileTime (&locStdTimeFields, pGmtFileTime));
      }

    STDTIME_RET_RC;
    }

  if (info.dstStartRule.mon == info.dstEndRule.mon)
    {
    /* rules are malformed; start and end should be in different months */
    STDTIME_RET_EC (invalid_timezone_rule);
    }

  if STDTIME_IFNOT (StdTimeTzTimeToDelta (&info.stdToDstOffset, &stdToDstDelta))
    {
    STDTIME_RET_RC;
    }

  /* the timezone rules are defined in terms of local times. */

  /* first, get local transition times */
  /* the start time is the local standard time at which DST begins */

  if STDTIME_IFNOT (StdTimeZoneDayOfRule (
       locStdTimeFields.year, &info.dstStartRule, &day))
    {
    STDTIME_RET_RC;
    }

  locDstStartStdTimeFields.year = locStdTimeFields.year;
  locDstStartStdTimeFields.mon  = info.dstStartRule.mon;
  locDstStartStdTimeFields.day  = day;

  locDstStartStdTimeFields.hour = info.dstStartTime.hour;
  locDstStartStdTimeFields.min  = info.dstStartTime.min;
  locDstStartStdTimeFields.sec  = info.dstStartTime.sec;

  /* in order to avoid a "spring-forward transition gap", we add the     */
  /* STD-to-DST offset to the start time.  example: if DST begins on the */
  /* 1st Sunday of April at 2:00 AM local standard time, then any time t */
  /* that is in the range 2:00 AM <= t < 3:00 AM is an "illegal" time.   */
  /* the STDTIME library chooses to treat this interval AS IF standard   */
  /* time.  when this is done, and such a time t is converted to GMT and */
  /* then back to local, it will get converted back to the correct time. */

  if STDTIME_IFNOT (StdTimeFields_AddDelta (
       &locDstStartStdTimeFields, &stdToDstDelta))
    {
    STDTIME_RET_RC;
    }

  /* the end time is the local DST time at which standard time resumes */
  /* since this represents a time for which stdToDstOffset has been added */
  /* we have to back out the DST offset to get the correct DST to STD */
  /* transition time; however, see note below. */

  if STDTIME_IFNOT (StdTimeZoneDayOfRule (
       locStdTimeFields.year, &info.dstEndRule, &day))
    {
    STDTIME_RET_RC;
    }

  locDstEndStdTimeFields.year = locStdTimeFields.year;
  locDstEndStdTimeFields.mon  = info.dstEndRule.mon;
  locDstEndStdTimeFields.day  = day;

  locDstEndStdTimeFields.hour = info.dstEndTime.hour;
  locDstEndStdTimeFields.min  = info.dstEndTime.min;
  locDstEndStdTimeFields.sec  = info.dstEndTime.sec;

  /* there is an ambiguous time period during the "fall-back" transition.  */
  /* if DST ends on the last Sunday in October at 2:00 local DST, there is */
  /* is a one-hour period after the time is set back to 1:00 AM local STD  */
  /* time, in which a local time that day might be either STD or DST.      */

  /* if the 'dstInEffect' flag is set, then times within this period are   */
  /* are assumed to be DST times, and STD time does not begin until 2:00   */
  /* local time.  if 'dstInEffect' is NOT set (which is the default),      */
  /* then STD time is assumed to begin at the set-back point of 1:00 AM.   */

  /* thus, if 'dstInEffect' is NOT set, the stdToDstDelta is subtracted,   */
  /* so that that the STD-time transition-point occurs an hour earlier.    */

  if (! info.dstInEffect)
    {
    if STDTIME_IFNOT (StdTimeFields_SubDelta (
         &locDstEndStdTimeFields, &stdToDstDelta))
      {
      STDTIME_RET_RC;
      }
    }

  /* determine northern vs. southern hemisphere rules */
  /* we could do a full compare on DST start/end times, but since the */
  /* rules normally involve the months of April and October, it is enough */
  /* to just look at the month fields in the rules.  we get the same result */
  /* and it's a lot faster check. */

  if (info.dstStartRule.mon < info.dstEndRule.mon)  /* APR < OCT */
    {
    /* northern hemisphere rules */

    if (CompareStdTimeFields (
          &locStdTimeFields,
          &locDstStartStdTimeFields) < 0)
      {
      bool_InDst = STDTIME_FALSE; /* before STD to DST transition */
      }

    else if (CompareStdTimeFields (
          &locStdTimeFields,
          &locDstEndStdTimeFields) < 0)
      {
      bool_InDst = STDTIME_TRUE; /* before DST to STD transition */
      }

    else
      {
      bool_InDst = STDTIME_FALSE; /* after DST to STD transition */
      }
    }

  else /* (OCT > APR) */
    {
    /* southern hemisphere rules */

    if (CompareStdTimeFields (
          &locStdTimeFields,
          &locDstEndStdTimeFields) < 0)
      {
      bool_InDst = STDTIME_TRUE; /* before DST to STD transition */
      }

    else if (CompareStdTimeFields (
          &locStdTimeFields,
          &locDstStartStdTimeFields) < 0)
      {
      bool_InDst = STDTIME_FALSE; /* before STD to DST transition */
      }

    else
      {
      bool_InDst = STDTIME_TRUE; /* after STD to DST transition */
      }
    }

  /* apply LOC to GMT unconditionally */
  /* 'locStdTimeFields' will become a GMT time */
  /* we subtract gmtToLocDelta to perform LOC to GMT operation */

  if STDTIME_IFNOT (StdTimeFields_SubDelta (&locStdTimeFields, &gmtToLocDelta))
    {
    STDTIME_RET_RC;
    }

  /* apply DST to STD if in effect */
  /* since GMT time does not use DST, we must back out the DST if in effect */

  if (bool_InDst)
    {
    if STDTIME_IFNOT (StdTimeFields_SubDelta (
         &locStdTimeFields, &stdToDstDelta))
      {
      STDTIME_RET_RC;
      }
    }

  STDTIME_RET (StdTimeFieldsToFileTime (&locStdTimeFields, pGmtFileTime));

  } /* StdTimeApiZonedFileTimeToFileTime */


/*-***************************************************************************/
/*            StdTimeApiFileTimeToZonedFileTime                              */
/*  convert GMT time to time for a specific zone or for default zone         */
/*****************************************************************************/

STDTIME_RC                  StdTimeApiFileTimeToZonedFileTime (
  const STDTIMEZONE_INFO *      /*I*/ pZoneInfo,
  const STDTIME_WIN_FILETIME *  /*I*/ pGmtFileTime,
  STDTIME_WIN_FILETIME *        /*O*/ pLocFileTime)
  {
  int32_t                   day;
  STDTIME_BOOL              bool_InDst;

  STDTIMEZONE_INFO          info;

  STDTIME_FIELDS            gmtStdTimeFields;

  STDTIME_FIELDS            gmtDstStartStdTimeFields;
  STDTIME_FIELDS            gmtDstEndStdTimeFields;
  STDTIME_FIELDS            locDstStartStdTimeFields = {0};
  STDTIME_FIELDS            locDstEndStdTimeFields   = {0};

  STDTIME_DELTA             gmtToLocDelta;
  STDTIME_DELTA             stdToDstDelta;

  STDTIME_ENUM_FUNC (StdTimeApiFileTimeToZonedFileTime)


  if ((pLocFileTime == NULL) || (pGmtFileTime == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IFNOT (FileTimeToStdTimeFields (pGmtFileTime, &gmtStdTimeFields))
    {
    STDTIME_RET_RC;
    }

  if (pZoneInfo == NULL)
    {
    /* no timezone argument provided, so create default 'local' zone info */

    /* we don't know what the zone ID is. */
    /* NULL means: let library determine the local zone ID and timezone */

    if STDTIME_IFNOT (GetStdTimeZoneInfo (NULL, &info))
      {
      STDTIME_RET_RC;
      }
    }

  else
    {
    info = *pZoneInfo;      /* copy the supplied timezone */
    }

  /* adjust start/end rules for the given year, if necessary */

  if STDTIME_IFNOT (Rc_FixStdTimeZoneRules (gmtStdTimeFields.year, &info))
    {
    STDTIME_RET_RC;
    }

  /* if 'local' zone is already GMT, and DST not used, don't convert. */
  /* a STDTIME_TZ_TIME field has a 'sign' of 0 when field is ignored */

  if ((info.gmtToLocOffset.sign == 0)
  &&  (info.stdToDstOffset.sign == 0))
    {
    *pLocFileTime = *pGmtFileTime;
    STDTIME_RET_OK;
    }

  if STDTIME_IFNOT (StdTimeTzTimeToDelta (&info.gmtToLocOffset, &gmtToLocDelta))
    {
    STDTIME_RET_RC;
    }

  /* if a 'local' zone does not use DST, just apply the zone offset */
  /* gmtToLocOffset is added to a GMT to get a local time */
  /* StdTimeTzTimeToDelta() takes care of the sign of the offset */

  if ((info.stdToDstOffset.sign == 0)
  ||  (gmtStdTimeFields.year < STDTIME_DST_CUTOFF_YEAR))  /* before DST */
    {
    if STDTIME_IF (StdTimeFields_AddDelta (&gmtStdTimeFields, &gmtToLocDelta))
      {
      /* in spite of its name, 'gmtStdTimeFields' is a local time */
      STDTIME_RET (StdTimeFieldsToFileTime (&gmtStdTimeFields, pLocFileTime));
      }

    STDTIME_RET_RC;
    }

  if (info.dstStartRule.mon == info.dstEndRule.mon)
    {
    /* rules are malformed; start and end should be in different months */
    STDTIME_RET_EC (invalid_timezone_rule);
    }

  if STDTIME_IFNOT (StdTimeTzTimeToDelta (&info.stdToDstOffset, &stdToDstDelta))
    {
    STDTIME_RET_RC;
    }

  /* the timezone rules are defined in terms of local times.  since it is */
  /* GMT that is being converted, the rules must also be converted to GMT.*/

  /* first, get local transition times */
  /* the start time is the local standard time at which DST begins */

  if STDTIME_IFNOT (StdTimeZoneDayOfRule (
       gmtStdTimeFields.year, &info.dstStartRule, &day))
    {
    STDTIME_RET_RC;
    }

  locDstStartStdTimeFields.year = gmtStdTimeFields.year;
  locDstStartStdTimeFields.mon  = info.dstStartRule.mon;
  locDstStartStdTimeFields.day  = day;

  locDstStartStdTimeFields.hour = info.dstStartTime.hour;
  locDstStartStdTimeFields.min  = info.dstStartTime.min;
  locDstStartStdTimeFields.sec  = info.dstStartTime.sec;

  /* copy loc to gmt data values, then convert */
  /* gmtToLocDelta must be subtracted to achieve LOC to GMT conversion */

  gmtDstStartStdTimeFields = locDstStartStdTimeFields;

  if STDTIME_IFNOT (StdTimeFields_SubDelta (
       &gmtDstStartStdTimeFields, &gmtToLocDelta))
    {
    STDTIME_RET_RC;
    }

  /* the end time is the local DST time at which standard time resumes */
  /* since this represents a time for which stdToDstOffset has been added */
  /* we have to back out the DST offset to get the correct DST to STD */
  /* transition time. */

  if STDTIME_IFNOT (StdTimeZoneDayOfRule (
       gmtStdTimeFields.year, &info.dstEndRule, &day))
    {
    STDTIME_RET_RC;
    }

  locDstEndStdTimeFields.year = gmtStdTimeFields.year;
  locDstEndStdTimeFields.mon  = info.dstEndRule.mon;
  locDstEndStdTimeFields.day  = day;

  locDstEndStdTimeFields.hour = info.dstEndTime.hour;
  locDstEndStdTimeFields.min  = info.dstEndTime.min;
  locDstEndStdTimeFields.sec  = info.dstEndTime.sec;

  /* copy loc to gmt data values, then convert */
  /* stdToDstDelta must be subtracted to achieve DST to STD conversion */
  /* gmtToLocDelta must be subtracted to achieve LOC to GMT conversion */

  gmtDstEndStdTimeFields = locDstEndStdTimeFields;

  if STDTIME_IFNOT (StdTimeFields_SubDelta (
       &gmtDstEndStdTimeFields, &stdToDstDelta))
    {
    STDTIME_RET_RC;
    }

  if STDTIME_IFNOT (StdTimeFields_SubDelta (
       &gmtDstEndStdTimeFields, &gmtToLocDelta))
    {
    STDTIME_RET_RC;
    }

  /* determine northern vs. southern hemisphere rules */
  /* we could do a full compare on DST start/end times, but since the */
  /* rules normally involve the months of April and October, it is enough */
  /* to just look at the month fields in the rules.  we get the same result */
  /* and it's a lot faster check. */

  if (info.dstStartRule.mon < info.dstEndRule.mon)  /* APR < OCT */
    {
    /* northern hemisphere rules */

    if (CompareStdTimeFields (
          &gmtStdTimeFields,
          &gmtDstStartStdTimeFields) < 0)
      {
      bool_InDst = STDTIME_FALSE; /* before STD to DST transition */
      }

    else if (CompareStdTimeFields (
          &gmtStdTimeFields,
          &gmtDstEndStdTimeFields) < 0)
      {
      bool_InDst = STDTIME_TRUE; /* before DST to STD transition */
      }

    else
      {
      bool_InDst = STDTIME_FALSE; /* after DST to STD transition */
      }
    }

  else /* (OCT > APR) */
    {
    /* southern hemisphere rules */

    if (CompareStdTimeFields (
          &gmtStdTimeFields,
          &gmtDstEndStdTimeFields) < 0)
      {
      bool_InDst = STDTIME_TRUE; /* before DST to STD transition */
      }

    else if (CompareStdTimeFields (
          &gmtStdTimeFields,
          &gmtDstStartStdTimeFields) < 0)
      {
      bool_InDst = STDTIME_FALSE; /* before STD to DST transition */
      }

    else
      {
      bool_InDst = STDTIME_TRUE; /* after STD to DST transition */
      }
    }

  /* apply GMT to LOC unconditionally */
  /* 'gmtStdTimeFields' will become a local time */

  if STDTIME_IFNOT (StdTimeFields_AddDelta (&gmtStdTimeFields, &gmtToLocDelta))
    {
    STDTIME_RET_RC;
    }

  /* apply STD to DST if in effect */

  if (bool_InDst)
    {
    if STDTIME_IFNOT (StdTimeFields_AddDelta (
         &gmtStdTimeFields, &stdToDstDelta))
      {
      STDTIME_RET_RC;
      }
    }

  STDTIME_RET (StdTimeFieldsToFileTime (&gmtStdTimeFields, pLocFileTime));

  } /* StdTimeApiFileTimeToZonedFileTime */


/*-***************************************************************************/
/*            StdTimeToZonedStdTime                                          */
/*  convert: StdTime structure from UTC/GMT time to zoned time               */
/*  method: StdTime -> FILETIME -> zoned FILETIME - zoned StdTime            */
/*****************************************************************************/

STDTIME_RC                  StdTimeToZonedStdTime (
  const STDTIMEZONE_INFO *  /*I*/ pZoneInfo,
  const STDTIME *           /*I*/ pStdTime,
  STDTIME *                 /*O*/ pStdTimeZoned)
  {
  STDTIME_WIN_FILETIME      gmtFileTime;
  STDTIME_WIN_FILETIME      locFileTime;

  STDTIME_ENUM_FUNC (StdTimeToZonedStdTime)

  if STDTIME_IF (StdTimeToFileTime (pStdTime, &gmtFileTime))
    {
    if STDTIME_IF (StdTimeApiFileTimeToZonedFileTime (
          pZoneInfo, &gmtFileTime, &locFileTime))
      {
      STDTIME_RET (FileTimeToStdTime (&locFileTime, pStdTimeZoned));
      }
    }

  STDTIME_RET_RC;

  } /* StdTimeToZonedStdTime */


/*-***************************************************************************/
/*            ZonedStdTimeToStdTime                                          */
/*  convert: StdTime structure from zoned time to UTC/GMT time               */
/*****************************************************************************/

STDTIME_RC                  ZonedStdTimeToStdTime (
  const STDTIMEZONE_INFO *  /*I*/ pZoneInfo,
  const STDTIME *           /*I*/ pStdTimeZoned,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_WIN_FILETIME      locFileTime;
  STDTIME_WIN_FILETIME      gmtFileTime;

  STDTIME_ENUM_FUNC (ZonedStdTimeToStdTime)

  if STDTIME_IF (StdTimeToFileTime (pStdTimeZoned, &locFileTime))
    {
    if STDTIME_IF (StdTimeApiZonedFileTimeToFileTime (
          pZoneInfo, &locFileTime, &gmtFileTime))
      {
      STDTIME_RET (FileTimeToStdTime (&gmtFileTime, pStdTime));
      }
    }

  STDTIME_RET_RC;

  } /* ZonedStdTimeToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToZonedStdTimeFields                              */
/*  convert: StdTimeFields structure from UTC/GMT time to zoned time         */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToZonedStdTimeFields (
  const STDTIMEZONE_INFO *  /*I*/ pZoneInfo,
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_FIELDS *          /*O*/ pStdTimeFieldsZoned)
  {
  STDTIME_WIN_FILETIME      gmtFileTime;
  STDTIME_WIN_FILETIME      locFileTime;

  STDTIME_ENUM_FUNC (StdTimeFieldsToZonedStdTimeFields)

  if ((pStdTimeFields == NULL) || (pStdTimeFieldsZoned == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IFNOT (StdTimeFieldsToFileTime (pStdTimeFields, &gmtFileTime))
    {
    STDTIME_RET_RC;
    }

  if STDTIME_IFNOT (StdTimeApiFileTimeToZonedFileTime (
          pZoneInfo, &gmtFileTime, &locFileTime))
    {
    STDTIME_RET_RC;
    }

  STDTIME_RET (FileTimeToStdTimeFields (&locFileTime, pStdTimeFieldsZoned));

  } /* StdTimeFieldsToZonedStdTimeFields */


/*-***************************************************************************/
/*            ZonedStdTimeFieldsToStdTimeFields                              */
/*  convert: StdTimeFields structure from zoned time to UTC/GMT time         */
/*****************************************************************************/

STDTIME_RC                  ZonedStdTimeFieldsToStdTimeFields (
  const STDTIMEZONE_INFO *  /*I*/ pZoneInfo,
  const STDTIME_FIELDS *    /*I*/ pStdTimeFieldsZoned,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_WIN_FILETIME      gmtFileTime;
  STDTIME_WIN_FILETIME      locFileTime;

  STDTIME_ENUM_FUNC (ZonedStdTimeFieldsToStdTimeFields)

  if ((pStdTimeFieldsZoned == NULL) || (pStdTimeFields == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IFNOT (StdTimeFieldsToFileTime (pStdTimeFieldsZoned, &locFileTime))
    {
    STDTIME_RET_RC;
    }

  if STDTIME_IFNOT (StdTimeApiZonedFileTimeToFileTime (
          pZoneInfo, &locFileTime, &gmtFileTime))
    {
    STDTIME_RET_RC;
    }

  STDTIME_RET (FileTimeToStdTimeFields (&gmtFileTime, pStdTimeFields));

  } /* ZonedStdTimeFieldsToStdTimeFields */


/*-***************************************************************************/
/*            StdTimeStringAToZonedStdTimeStringA                            */
/*  convert: StdTimeStringA structure from UTC/GMT time to zoned time        */
/*****************************************************************************/

STDTIME_RC                  StdTimeStringAToZonedStdTimeStringA (
  const STDTIMEZONE_INFO *  /*I*/ pZoneInfo,
  const STDTIME_STRINGA *   /*I*/ pGmtStdTimeString,
  STDTIME_STRINGA *         /*O*/ pLocStdTimeString)
  {
  STDTIME_FIELDS            gmtFields;
  STDTIME_FIELDS            locFields;

  STDTIME_ENUM_FUNC (StdTimeStringAToZonedStdTimeStringA)

  if (pLocStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pLocStdTimeString = ZeroStdTimeStringA ();

  if (pGmtStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  /* in case the 'pGmtStdTimeString' contains a timezone offset, that zone   */
  /* will override the GMT zone of 'pGmtStdTimeString' when converted.       */
  /* this would effectively cause a 'zone-to-zone' conversion.               */

  if STDTIME_IF (StdTimeStringAToStdTimeFields (pGmtStdTimeString, &gmtFields))
    {
    if STDTIME_IF (StdTimeFieldsToZonedStdTimeFields (
         pZoneInfo, &gmtFields, &locFields))
      {
      STDTIME_RET (StdTimeFieldsToStdTimeStringA (
        &locFields, pLocStdTimeString));
      }
    }

  STDTIME_RET_RC;

  } /* StdTimeStringAToZonedStdTimeStringA */


/*-***************************************************************************/
/*            StdTimeStringWToZonedStdTimeStringA                            */
/*  convert: StdTimeStringW structure from UTC/GMT time to zoned time        */
/*****************************************************************************/

STDTIME_RC                  StdTimeStringWToZonedStdTimeStringW (
  const STDTIMEZONE_INFO *  /*I*/ pZoneInfo,
  const STDTIME_STRINGW *   /*I*/ pGmtStdTimeString,
  STDTIME_STRINGW *         /*O*/ pLocStdTimeString)
  {
  STDTIME_FIELDS            gmtFields;
  STDTIME_FIELDS            locFields;

  STDTIME_ENUM_FUNC (StdTimeStringWToZonedStdTimeStringW)

  if (pLocStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pLocStdTimeString = ZeroStdTimeStringW ();

  if (pGmtStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeStringWToStdTimeFields (pGmtStdTimeString, &gmtFields))
    {
    if STDTIME_IF (StdTimeFieldsToZonedStdTimeFields (
         pZoneInfo, &gmtFields, &locFields))
      {
      STDTIME_RET (StdTimeFieldsToStdTimeStringW (
        &locFields, pLocStdTimeString));
      }
    }

  STDTIME_RET_RC;

  } /* StdTimeStringWToZonedStdTimeStringW */


/*-***************************************************************************/
/*            ZonedStdTimeStringAToStdTimeStringA                            */
/*  convert: StdTimeStringA structure from zoned time to UTC/GMT time        */
/*****************************************************************************/

STDTIME_RC                  ZonedStdTimeStringAToStdTimeStringA (
  const STDTIMEZONE_INFO *  /*I*/ pZoneInfo,
  const STDTIME_STRINGA *   /*I*/ pLocStdTimeString,
  STDTIME_STRINGA *         /*O*/ pGmtStdTimeString)
  {
  STDTIME_FIELDS            locFields;
  STDTIME_FIELDS            gmtFields;

  STDTIME_ENUM_FUNC (ZonedStdTimeStringAToStdTimeStringA)

  if (pGmtStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pGmtStdTimeString = ZeroStdTimeStringA ();

  if (pLocStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  /* issue: what happens if 'zoned' input (input string with zone info) has  */
  /* an explicit timezone offset? according to STDTIME reference manual, "an */
  /* an explicit embTzo field has priority over the STDTIMEZONE parameter    */
  /* when both are present."                                                 */

  /* method: if embTzo timezone offset is not blank, force its use by        */
  /* setting the zone info parameter to NULL, otherwise embTzo gets used.    */

  if (! Bool_StdTime_IsBlankA (pLocStdTimeString->embTzo))
    {
    pZoneInfo = NULL;   /* don't use zone info, just apply embTzo */
    }

  if STDTIME_IF (StdTimeStringAToStdTimeFields (pLocStdTimeString, &locFields))
    {
    if STDTIME_IF (ZonedStdTimeFieldsToStdTimeFields (
         pZoneInfo, &locFields, &gmtFields))
      {
      STDTIME_RET (StdTimeFieldsToStdTimeStringA (
        &gmtFields, pGmtStdTimeString));
      }
    }

  STDTIME_RET_RC;

  } /* ZonedStdTimeStringAToStdTimeStringA */


/*-***************************************************************************/
/*            ZonedStdTimeStringWToStdTimeStringW                            */
/*  convert: StdTimeStringW structure from zoned time to UTC/GMT time        */
/*****************************************************************************/

STDTIME_RC                  ZonedStdTimeStringWToStdTimeStringW (
  const STDTIMEZONE_INFO *  /*I*/ pZoneInfo,
  const STDTIME_STRINGW *   /*I*/ pLocStdTimeString,
  STDTIME_STRINGW *         /*O*/ pGmtStdTimeString)
  {
  STDTIME_FIELDS            locFields;
  STDTIME_FIELDS            gmtFields;

  STDTIME_ENUM_FUNC (ZonedStdTimeStringWToStdTimeStringW)

  if (pGmtStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pGmtStdTimeString = ZeroStdTimeStringW ();

  if (pLocStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeStringWToStdTimeFields (pLocStdTimeString, &locFields))
    {
    if STDTIME_IF (ZonedStdTimeFieldsToStdTimeFields (
         pZoneInfo, &locFields, &gmtFields))
      {
      STDTIME_RET (StdTimeFieldsToStdTimeStringW (
        &gmtFields, pGmtStdTimeString));
      }
    }

  STDTIME_RET_RC;

  } /* ZonedStdTimeStringWToStdTimeStringW */


/*-***************************************************************************/
/*            StdTimeHexStrAToZonedStdTimeHexStrA                            */
/*  convert: StdTimeHexStrA structure from UTC/GMT time to zoned time        */
/*****************************************************************************/

STDTIME_RC                  StdTimeHexStrAToZonedStdTimeHexStrA (
  const STDTIMEZONE_INFO *  /*I*/ pZoneInfo,
  const STDTIME_HEXSTRA *   /*I*/ pGmtStdTimeHexStr,
  STDTIME_HEXSTRA *         /*O*/ pLocStdTimeHexStr)
  {
  STDTIME_WIN_FILETIME      gmtFileTime;
  STDTIME_WIN_FILETIME      locFileTime;

  STDTIME_ENUM_FUNC (StdTimeHexStrAToZonedStdTimeHexStrA)

  if (pLocStdTimeHexStr == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pLocStdTimeHexStr = ZeroStdTimeHexStrA ();

  if (pGmtStdTimeHexStr == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeHexStrAToFileTime (pGmtStdTimeHexStr, &gmtFileTime))
    {
    if STDTIME_IF (StdTimeApiFileTimeToZonedFileTime (
          pZoneInfo, &gmtFileTime, &locFileTime))
      {
      STDTIME_RET (FileTimeToStdTimeHexStrA (&locFileTime, pLocStdTimeHexStr));
      }
    }

  STDTIME_RET_RC;

  } /* StdTimeHexStrAToZonedStdTimeHexStrA */


/*-***************************************************************************/
/*            StdTimeHexStrWToZonedStdTimeHexStrW                            */
/*  convert: StdTimeHexStrW structure from UTC/GMT time to zoned time        */
/*****************************************************************************/

STDTIME_RC                  StdTimeHexStrWToZonedStdTimeHexStrW (
  const STDTIMEZONE_INFO *  /*I*/ pZoneInfo,
  const STDTIME_HEXSTRW *   /*I*/ pGmtStdTimeHexStr,
  STDTIME_HEXSTRW *         /*O*/ pLocStdTimeHexStr)
  {
  STDTIME_WIN_FILETIME      gmtFileTime;
  STDTIME_WIN_FILETIME      locFileTime;

  STDTIME_ENUM_FUNC (StdTimeHexStrWToZonedStdTimeHexStrW)

  if (pLocStdTimeHexStr == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pLocStdTimeHexStr = ZeroStdTimeHexStrW ();

  if (pGmtStdTimeHexStr == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeHexStrWToFileTime (pGmtStdTimeHexStr, &gmtFileTime))
    {
    if STDTIME_IF (StdTimeApiFileTimeToZonedFileTime (
          pZoneInfo, &gmtFileTime, &locFileTime))
      {
      STDTIME_RET (FileTimeToStdTimeHexStrW (&locFileTime, pLocStdTimeHexStr));
      }
    }

  STDTIME_RET_RC;

  } /* StdTimeHexStrWToZonedStdTimeHexStrW */


/*-***************************************************************************/
/*            ZonedStdTimeHexStrAToStdTimeHexStrA                            */
/*  convert: StdTimeHexStrA structure from zoned time to UTC/GMT time        */
/*****************************************************************************/

STDTIME_RC                  ZonedStdTimeHexStrAToStdTimeHexStrA (
  const STDTIMEZONE_INFO *  /*I*/ pZoneInfo,
  const STDTIME_HEXSTRA *   /*I*/ pLocStdTimeHexStr,
  STDTIME_HEXSTRA *         /*O*/ pGmtStdTimeHexStr)
  {
  STDTIME_WIN_FILETIME      locFileTime;
  STDTIME_WIN_FILETIME      gmtFileTime;

  STDTIME_ENUM_FUNC (ZonedStdTimeHexStrAToStdTimeHexStrA)

  if (pGmtStdTimeHexStr == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pGmtStdTimeHexStr = ZeroStdTimeHexStrA ();

  if (pLocStdTimeHexStr == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeHexStrAToFileTime (pLocStdTimeHexStr, &locFileTime))
    {
    if STDTIME_IF (StdTimeApiZonedFileTimeToFileTime (
          pZoneInfo, &locFileTime, &gmtFileTime))
      {
      STDTIME_RET (FileTimeToStdTimeHexStrA (&gmtFileTime, pGmtStdTimeHexStr));
      }
    }

  STDTIME_RET_RC;

  } /* ZonedStdTimeHexStrAToStdTimeHexStrA */


/*-***************************************************************************/
/*            ZonedStdTimeHexStrWToStdTimeHexStrW                            */
/*  convert: StdTimeHexStrW structure from zoned time to UTC/GMT time        */
/*****************************************************************************/

STDTIME_RC                  ZonedStdTimeHexStrWToStdTimeHexStrW (
  const STDTIMEZONE_INFO *  /*I*/ pZoneInfo,
  const STDTIME_HEXSTRW *   /*I*/ pLocStdTimeHexStr,
  STDTIME_HEXSTRW *         /*O*/ pGmtStdTimeHexStr)
  {
  STDTIME_WIN_FILETIME      locFileTime;
  STDTIME_WIN_FILETIME      gmtFileTime;

  STDTIME_ENUM_FUNC (ZonedStdTimeHexStrWToStdTimeHexStrW)

  if (pGmtStdTimeHexStr == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pGmtStdTimeHexStr = ZeroStdTimeHexStrW ();

  if (pLocStdTimeHexStr == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeHexStrWToFileTime (pLocStdTimeHexStr, &locFileTime))
    {
    if STDTIME_IF (StdTimeApiZonedFileTimeToFileTime (
         pZoneInfo, &locFileTime, &gmtFileTime))
      {
      STDTIME_RET (FileTimeToStdTimeHexStrW (&gmtFileTime, pGmtStdTimeHexStr));
      }
    }

  STDTIME_RET_RC;

  } /* ZonedStdTimeHexStrWToStdTimeHexStrW */


/*-***************************************************************************/
/*            StdTimeToLocalStdTime                                          */
/*  convert: StdTime structure from UTC/GMT time to local time               */
/*  use of NULL timezone info forces use of default timezone                 */
/*****************************************************************************/

STDTIME_RC                  StdTimeToLocalStdTime (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME *                 /*O*/ pStdTimeLocal)
  {
  STDTIME_ENUM_FUNC (StdTimeToLocalStdTime)

  STDTIME_RET (StdTimeToZonedStdTime (NULL,
    pStdTime, pStdTimeLocal));

  } /* StdTimeToLocalStdTime */


/*-***************************************************************************/
/*            LocalStdTimeToStdTime                                          */
/*  convert: StdTime structure from local time to UTC/GMT time               */
/*  use of NULL timezone info forces use of default timezone                 */
/*****************************************************************************/

STDTIME_RC                  LocalStdTimeToStdTime (
  const STDTIME *           /*I*/ pStdTimeLocal,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_ENUM_FUNC (LocalStdTimeToStdTime)

  STDTIME_RET (ZonedStdTimeToStdTime (NULL,
    pStdTimeLocal, pStdTime));

  } /* LocalStdTimeToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToLocalStdTimeFields                              */
/*  convert: StdTimeFields structure from UTC/GMT time to local time         */
/*  use of NULL timezone info forces use of default timezone                 */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToLocalStdTimeFields (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_FIELDS *          /*O*/ pStdTimeFieldsLocal)
  {
  STDTIME_ENUM_FUNC (StdTimeFieldsToLocalStdTimeFields)

  STDTIME_RET (StdTimeFieldsToZonedStdTimeFields (NULL,
    pStdTimeFields, pStdTimeFieldsLocal));

  } /* StdTimeFieldsToLocalStdTimeFields */


/*-***************************************************************************/
/*            LocalStdTimeFieldsToStdTimeFields                              */
/*  convert: StdTimeFields structure from local time to UTC/GMT time         */
/*  use of NULL timezone info forces use of default timezone                 */
/*****************************************************************************/

STDTIME_RC                  LocalStdTimeFieldsToStdTimeFields (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFieldsLocal,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_ENUM_FUNC (LocalStdTimeFieldsToStdTimeFields)

  STDTIME_RET (ZonedStdTimeFieldsToStdTimeFields (NULL,
    pStdTimeFieldsLocal, pStdTimeFields));

  } /* LocalStdTimeFieldsToStdTimeFields */


/*-***************************************************************************/
/*            StdTimeStringAToLocalStdTimeStringA                            */
/*  convert: StdTimeStringA structure from UTC/GMT time to local time        */
/*  use of NULL timezone info forces use of default timezone                 */
/*****************************************************************************/

STDTIME_RC                  StdTimeStringAToLocalStdTimeStringA (
  const STDTIME_STRINGA *   /*I*/ pGmtStdTimeString,
  STDTIME_STRINGA *         /*O*/ pLocStdTimeString)
  {
  STDTIME_ENUM_FUNC (StdTimeStringAToLocalStdTimeStringA)

  STDTIME_RET (StdTimeStringAToZonedStdTimeStringA (NULL,
    pGmtStdTimeString, pLocStdTimeString));

  } /* StdTimeStringAToLocalStdTimeStringA */


/*-***************************************************************************/
/*            StdTimeStringWToLocalStdTimeStringA                            */
/*  convert: StdTimeStringW structure from UTC/GMT time to local time        */
/*  use of NULL timezone info forces use of default timezone                 */
/*****************************************************************************/

STDTIME_RC                  StdTimeStringWToLocalStdTimeStringW (
  const STDTIME_STRINGW *   /*I*/ pGmtStdTimeString,
  STDTIME_STRINGW *         /*O*/ pLocStdTimeString)
  {
  STDTIME_ENUM_FUNC (StdTimeStringWToLocalStdTimeStringW)

  STDTIME_RET (StdTimeStringWToZonedStdTimeStringW (NULL,
    pGmtStdTimeString, pLocStdTimeString));

  } /* StdTimeStringWToLocalStdTimeStringW */


/*-***************************************************************************/
/*            LocalStdTimeStringAToStdTimeStringA                            */
/*  convert: StdTimeStringA structure from local time to UTC/GMT time        */
/*  use of NULL timezone info forces use of default timezone                 */
/*****************************************************************************/

STDTIME_RC                  LocalStdTimeStringAToStdTimeStringA (
  const STDTIME_STRINGA *   /*I*/ pLocStdTimeString,
  STDTIME_STRINGA *         /*O*/ pGmtStdTimeString)
  {
  STDTIME_ENUM_FUNC (LocalStdTimeStringAToStdTimeStringA)

  STDTIME_RET (ZonedStdTimeStringAToStdTimeStringA (NULL,
    pLocStdTimeString, pGmtStdTimeString));

  } /* LocalStdTimeStringAToStdTimeStringA */


/*-***************************************************************************/
/*            LocalStdTimeStringWToStdTimeStringW                            */
/*  convert: StdTimeStringW structure from local time to UTC/GMT time        */
/*  use of NULL timezone info forces use of default timezone                 */
/*****************************************************************************/

STDTIME_RC                  LocalStdTimeStringWToStdTimeStringW (
  const STDTIME_STRINGW *   /*I*/ pLocStdTimeString,
  STDTIME_STRINGW *         /*O*/ pGmtStdTimeString)
  {
  STDTIME_ENUM_FUNC (LocalStdTimeStringWToStdTimeStringW)

  STDTIME_RET (ZonedStdTimeStringWToStdTimeStringW (NULL,
    pLocStdTimeString, pGmtStdTimeString));

  } /* LocalStdTimeStringWToStdTimeStringW */


/*-***************************************************************************/
/*            StdTimeHexStrAToLocalStdTimeHexStrA                            */
/*  convert: StdTimeHexStrA structure from UTC/GMT time to local time        */
/*  use of NULL timezone info forces use of default timezone                 */
/*****************************************************************************/

STDTIME_RC                  StdTimeHexStrAToLocalStdTimeHexStrA (
  const STDTIME_HEXSTRA *   /*I*/ pGmtStdTimeHexStr,
  STDTIME_HEXSTRA *         /*O*/ pLocStdTimeHexStr)
  {
  STDTIME_ENUM_FUNC (StdTimeHexStrAToLocalStdTimeHexStrA)

  STDTIME_RET (StdTimeHexStrAToZonedStdTimeHexStrA (NULL,
    pGmtStdTimeHexStr, pLocStdTimeHexStr));

  } /* StdTimeHexStrAToLocalStdTimeHexStrA */


/*-***************************************************************************/
/*            StdTimeHexStrWToLocalStdTimeHexStrW                            */
/*  convert: StdTimeHexStrW structure from UTC/GMT time to local time        */
/*  use of NULL timezone info forces use of default timezone                 */
/*****************************************************************************/

STDTIME_RC                  StdTimeHexStrWToLocalStdTimeHexStrW (
  const STDTIME_HEXSTRW *   /*I*/ pGmtStdTimeHexStr,
  STDTIME_HEXSTRW *         /*O*/ pLocStdTimeHexStr)
  {
  STDTIME_ENUM_FUNC (StdTimeHexStrWToLocalStdTimeHexStrW)

  STDTIME_RET (StdTimeHexStrWToZonedStdTimeHexStrW (NULL,
    pGmtStdTimeHexStr, pLocStdTimeHexStr));

  } /* StdTimeHexStrWToLocalStdTimeHexStrW */


/*-***************************************************************************/
/*            LocalStdTimeHexStrAToStdTimeHexStrA                            */
/*  convert: StdTimeHexStrA structure from local time to UTC/GMT time        */
/*  use of NULL timezone info forces use of default timezone                 */
/*****************************************************************************/

STDTIME_RC                  LocalStdTimeHexStrAToStdTimeHexStrA (
  const STDTIME_HEXSTRA *   /*I*/ pLocStdTimeHexStr,
  STDTIME_HEXSTRA *         /*O*/ pGmtStdTimeHexStr)
  {
  STDTIME_ENUM_FUNC (LocalStdTimeHexStrAToStdTimeHexStrA)

  STDTIME_RET (ZonedStdTimeHexStrAToStdTimeHexStrA (NULL,
    pLocStdTimeHexStr, pGmtStdTimeHexStr));

  } /* LocalStdTimeHexStrAToStdTimeHexStrA */


/*-***************************************************************************/
/*            LocalStdTimeHexStrWToStdTimeHexStrW                            */
/*  convert: StdTimeHexStrW structure from local time to UTC/GMT time        */
/*  use of NULL timezone info forces use of default timezone                 */
/*****************************************************************************/

STDTIME_RC                  LocalStdTimeHexStrWToStdTimeHexStrW (
  const STDTIME_HEXSTRW *   /*I*/ pLocStdTimeHexStr,
  STDTIME_HEXSTRW *         /*O*/ pGmtStdTimeHexStr)
  {
  STDTIME_ENUM_FUNC (LocalStdTimeHexStrWToStdTimeHexStrW)

  STDTIME_RET (ZonedStdTimeHexStrWToStdTimeHexStrW (NULL,
    pLocStdTimeHexStr, pGmtStdTimeHexStr));

  } /* LocalStdTimeHexStrWToStdTimeHexStrW */


/*-***************************************************************************/
/*            StdTimeApiZonedFileTimeIsDST                                   */
/*  determine if a local or timezone specific time is DST,                   */
/*  from the vantage point of a timezone.                                    */
/*****************************************************************************/

STDTIME_RC                  StdTimeApiZonedFileTimeIsDST (
  const STDTIMEZONE_INFO *      /*I*/ pZoneInfo,
  const STDTIME_WIN_FILETIME *  /*I*/ pLocFileTime,
  STDTIME_BOOL *                /*O*/ pDstFlag)
  {
  int32_t                   day;
  STDTIME_BOOL              inDst;

  STDTIMEZONE_INFO          info;

  STDTIME_FIELDS            locStdTimeFields;
  STDTIME_FIELDS            locDstStartStdTimeFields = {0};
  STDTIME_FIELDS            locDstEndStdTimeFields   = {0};

  STDTIME_DELTA             gmtToLocDelta;
  STDTIME_DELTA             stdToDstDelta;

  STDTIME_ENUM_FUNC (StdTimeApiZonedFileTimeIsDST)


  if (pDstFlag == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pDstFlag = STDTIME_FALSE;  /* set default result value */

  if (pLocFileTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IFNOT (FileTimeToStdTimeFields (pLocFileTime, &locStdTimeFields))
    {
    STDTIME_RET_RC;
    }

  if (pZoneInfo == NULL)
    {
    /* no timezone argument provided, so create default 'local' zone info */

    /* we don't know what the zone ID is. */
    /* NULL means: let library determine the local zone ID and timezone */

    if STDTIME_IFNOT (GetStdTimeZoneInfo (NULL, &info))
      {
      STDTIME_RET_RC;
      }
    }

  else
    {
    info = *pZoneInfo;      /* copy the supplied timezone */
    }

  /* adjust start/end rules for the given year, if necessary */

  if STDTIME_IFNOT (Rc_FixStdTimeZoneRules (locStdTimeFields.year, &info))
    {
    STDTIME_RET_RC;
    }

  /* if 'stdToDstOffset.sign' is zero, DST is not used in this timezone */

  if ((info.stdToDstOffset.sign == 0)
  ||  (locStdTimeFields.year < STDTIME_DST_CUTOFF_YEAR))  /* before DST */
    {
    STDTIME_RET_OK;         /* got valid answer, which is DST=false */
    }

  if STDTIME_IFNOT (StdTimeTzTimeToDelta (&info.gmtToLocOffset, &gmtToLocDelta))
    {
    STDTIME_RET_RC;
    }

  if (info.dstStartRule.mon == info.dstEndRule.mon)
    {
    /* rules are malformed; start and end should be in different months */
    STDTIME_RET_EC (invalid_timezone_rule);
    }

  if STDTIME_IFNOT (StdTimeTzTimeToDelta (&info.stdToDstOffset, &stdToDstDelta))
    {
    STDTIME_RET_RC;
    }

  /* the timezone rules are defined in terms of local times. */

  /* first, get local transition times */
  /* the start time is the local standard time at which DST begins */

  if STDTIME_IFNOT (StdTimeZoneDayOfRule (
       locStdTimeFields.year, &info.dstStartRule, &day))
    {
    STDTIME_RET_RC;
    }

  locDstStartStdTimeFields.year = locStdTimeFields.year;
  locDstStartStdTimeFields.mon  = info.dstStartRule.mon;
  locDstStartStdTimeFields.day  = day;

  locDstStartStdTimeFields.hour = info.dstStartTime.hour;
  locDstStartStdTimeFields.min  = info.dstStartTime.min;
  locDstStartStdTimeFields.sec  = info.dstStartTime.sec;

  /* in order to avoid a "spring-forward transition gap", we add the     */
  /* STD-to-DST offset to the start time.  example: if DST begins on the */
  /* 1st Sunday of April at 2:00 AM local standard time, then any time t */
  /* that is in the range 2:00 AM <= t < 3:00 AM is an "illegal" time.   */
  /* the STDTIME library chooses to treat this interval AS IF standard   */
  /* time.  when this is done, and such a time t is converted to GMT and */
  /* then back to local, it will get converted back to the correct time. */

  if STDTIME_IFNOT (StdTimeFields_AddDelta (
       &locDstStartStdTimeFields, &stdToDstDelta))
    {
    STDTIME_RET_RC;
    }

  /* the end time is the local DST time at which standard time resumes */
  /* since this represents a time for which stdToDstOffset has been added */
  /* we have to back out the DST offset to get the correct DST to STD */
  /* transition time; however, see note below. */

  if STDTIME_IFNOT (StdTimeZoneDayOfRule (
       locStdTimeFields.year, &info.dstEndRule, &day))
    {
    STDTIME_RET_RC;
    }

  locDstEndStdTimeFields.year = locStdTimeFields.year;
  locDstEndStdTimeFields.mon  = info.dstEndRule.mon;
  locDstEndStdTimeFields.day  = day;

  locDstEndStdTimeFields.hour = info.dstEndTime.hour;
  locDstEndStdTimeFields.min  = info.dstEndTime.min;
  locDstEndStdTimeFields.sec  = info.dstEndTime.sec;

  /* there is an ambiguous time period during the "fall-back" transition.  */
  /* if DST ends on the last Sunday in October at 2:00 local DST, there is */
  /* is a one-hour period after the time is set back to 1:00 AM local STD  */
  /* time, in which a local time that day might be either STD or DST.      */

  /* if the 'dstInEffect' flag is set, then times within this period are   */
  /* are assumed to be DST times, and STD time does not begin until 2:00   */
  /* local time.  if 'dstInEffect' is NOT set (which is the default),      */
  /* then STD time is assumed to begin at the set-back point of 1:00 AM.   */

  /* thus, if 'dstInEffect' is NOT set, the stdToDstDelta is subtracted,   */
  /* so that that the STD-time transition-point occurs an hour earlier.    */

  if (! info.dstInEffect)
    {
    if STDTIME_IFNOT (StdTimeFields_SubDelta (
         &locDstEndStdTimeFields, &stdToDstDelta))
      {
      STDTIME_RET_RC;
      }
    }

  /* determine northern vs. southern hemisphere rules */
  /* we could do a full compare on DST start/end times, but since the */
  /* rules normally involve the months of April and October, it is enough */
  /* to just look at the month fields in the rules.  we get the same result */
  /* and it's a lot faster check. */

  if (info.dstStartRule.mon < info.dstEndRule.mon)  /* APR < OCT */
    {
    /* northern hemisphere rules */

    if (CompareStdTimeFields (
          &locStdTimeFields,
          &locDstStartStdTimeFields) < 0)
      {
      inDst = STDTIME_FALSE;    /* before STD to DST transition */
      }

    else if (CompareStdTimeFields (
          &locStdTimeFields,
          &locDstEndStdTimeFields) < 0)
      {
      inDst = STDTIME_TRUE;     /* before DST to STD transition */
      }

    else
      {
      inDst = STDTIME_FALSE;    /* after DST to STD transition */
      }
    }

  else /* (OCT > APR) */
    {
    /* southern hemisphere rules */

    if (CompareStdTimeFields (
          &locStdTimeFields,
          &locDstEndStdTimeFields) < 0)
      {
      inDst = STDTIME_TRUE;     /* before DST to STD transition */
      }

    else if (CompareStdTimeFields (
          &locStdTimeFields,
          &locDstStartStdTimeFields) < 0)
      {
      inDst = STDTIME_FALSE;    /* before STD to DST transition */
      }

    else
      {
      inDst = STDTIME_TRUE;     /* after STD to DST transition */
      }
    }

  *pDstFlag = inDst;

  /* OK means we were able to determine the DST status */
  /* the pDstFlag contains the answer to the question */

  STDTIME_RET_OK;

  } /* StdTimeApiZonedFileTimeIsDST */


/*-***************************************************************************/
/*            StdTimeApiFileTimeIsDST                                        */
/*  determine if a GMT time is DST from the vantage point of a timezone      */
/*****************************************************************************/

STDTIME_RC                  StdTimeApiFileTimeIsDST (
  const STDTIMEZONE_INFO *      /*I*/ pZoneInfo,
  const STDTIME_WIN_FILETIME *  /*I*/ pGmtFileTime,
  STDTIME_BOOL *                /*O*/ pDstFlag)
  {
  int32_t                   day;
  STDTIME_BOOL              bool_InDst;

  STDTIMEZONE_INFO          info;

  STDTIME_FIELDS            gmtStdTimeFields;
  STDTIME_FIELDS            gmtDstStartStdTimeFields;
  STDTIME_FIELDS            gmtDstEndStdTimeFields;

  STDTIME_FIELDS            locDstStartStdTimeFields = {0};
  STDTIME_FIELDS            locDstEndStdTimeFields   = {0};

  STDTIME_DELTA             gmtToLocDelta;
  STDTIME_DELTA             stdToDstDelta;

  STDTIME_ENUM_FUNC (StdTimeApiFileTimeIsDST)

  if (pDstFlag == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pDstFlag = STDTIME_FALSE;  /* set default result value */

  if (pGmtFileTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IFNOT (FileTimeToStdTimeFields (pGmtFileTime, &gmtStdTimeFields))
    {
    STDTIME_RET_RC;
    }

  if (pZoneInfo == NULL)
    {
    /* no timezone argument provided, so create default 'local' zone info */

    /* we don't know what the zone ID is. */
    /* NULL means: let library determine the local zone ID and timezone */

    if STDTIME_IFNOT (GetStdTimeZoneInfo (NULL, &info))
      {
      STDTIME_RET_RC;
      }
    }

  else
    {
    info = *pZoneInfo;      /* copy the supplied timezone */
    }

  /* adjust start/end rules for the given year, if necessary */

  if STDTIME_IFNOT (Rc_FixStdTimeZoneRules (gmtStdTimeFields.year, &info))
    {
    STDTIME_RET_RC;
    }

  /* if 'stdToDstOffset.sign' is zero, DST is not used in this timezone */

  if ((info.stdToDstOffset.sign == 0)
  ||  (gmtStdTimeFields.year < STDTIME_DST_CUTOFF_YEAR))  /* before DST */
    {
    STDTIME_RET_OK;         /* got valid answer, which is DST=false */
    }

  if STDTIME_IFNOT (StdTimeTzTimeToDelta (&info.gmtToLocOffset, &gmtToLocDelta))
    {
    STDTIME_RET_RC;
    }

  if (info.dstStartRule.mon == info.dstEndRule.mon)
    {
    /* rules are malformed; start and end should be in different months */
    STDTIME_RET_EC (invalid_timezone_rule);
    }

  if STDTIME_IFNOT (StdTimeTzTimeToDelta (&info.stdToDstOffset, &stdToDstDelta))
    {
    STDTIME_RET_RC;
    }

  /* the timezone rules are defined in terms of local times.  since it is */
  /* GMT that is being converted, the rules must also be converted to GMT.*/

  /* first, get local transition times */
  /* the start time is the local standard time at which DST begins */

  if STDTIME_IFNOT (StdTimeZoneDayOfRule (
       gmtStdTimeFields.year, &info.dstStartRule, &day))
    {
    STDTIME_RET_RC;
    }

  locDstStartStdTimeFields.year = gmtStdTimeFields.year;
  locDstStartStdTimeFields.mon  = info.dstStartRule.mon;
  locDstStartStdTimeFields.day  = day;

  locDstStartStdTimeFields.hour = info.dstStartTime.hour;
  locDstStartStdTimeFields.min  = info.dstStartTime.min;
  locDstStartStdTimeFields.sec  = info.dstStartTime.sec;

  /* copy loc to gmt data values, then convert */
  /* gmtToLocDelta must be subtracted to achieve LOC to GMT conversion */

  gmtDstStartStdTimeFields = locDstStartStdTimeFields;

  if STDTIME_IFNOT (StdTimeFields_SubDelta (
       &gmtDstStartStdTimeFields, &gmtToLocDelta))
    {
    STDTIME_RET_RC;
    }

  /* the end time is the local DST time at which standard time resumes */
  /* since this represents a time for which stdToDstOffset has been added */
  /* we have to back out the DST offset to get the correct DST to STD */
  /* transition time. */

  if STDTIME_IFNOT (StdTimeZoneDayOfRule (
       gmtStdTimeFields.year, &info.dstEndRule, &day))
    {
    STDTIME_RET_RC;
    }

  locDstEndStdTimeFields.year = gmtStdTimeFields.year;
  locDstEndStdTimeFields.mon  = info.dstEndRule.mon;
  locDstEndStdTimeFields.day  = day;

  locDstEndStdTimeFields.hour = info.dstEndTime.hour;
  locDstEndStdTimeFields.min  = info.dstEndTime.min;
  locDstEndStdTimeFields.sec  = info.dstEndTime.sec;

  /* copy loc to gmt data values, then convert */
  /* stdToDstDelta must be subtracted to achieve DST to STD conversion */
  /* gmtToLocDelta must be subtracted to achieve LOC to GMT conversion */

  gmtDstEndStdTimeFields = locDstEndStdTimeFields;

  if STDTIME_IFNOT (StdTimeFields_SubDelta (
       &gmtDstEndStdTimeFields, &stdToDstDelta))
    {
    STDTIME_RET_RC;
    }

  if STDTIME_IFNOT (StdTimeFields_SubDelta (
       &gmtDstEndStdTimeFields, &gmtToLocDelta))
    {
    STDTIME_RET_RC;
    }

  /* determine northern vs. southern hemisphere rules */
  /* we could do a full compare on DST start/end times, but since the */
  /* rules normally involve the months of April and October, it is enough */
  /* to just look at the month fields in the rules.  we get the same result */
  /* and it's a lot faster check. */

  if (info.dstStartRule.mon < info.dstEndRule.mon)  /* APR < OCT */
    {
    /* northern hemisphere rules */

    if (CompareStdTimeFields (
          &gmtStdTimeFields,
          &gmtDstStartStdTimeFields) < 0)
      {
      bool_InDst = STDTIME_FALSE; /* before STD to DST transition */
      }

    else if (CompareStdTimeFields (
          &gmtStdTimeFields,
          &gmtDstEndStdTimeFields) < 0)
      {
      bool_InDst = STDTIME_TRUE; /* before DST to STD transition */
      }

    else
      {
      bool_InDst = STDTIME_FALSE; /* after DST to STD transition */
      }
    }

  else /* (OCT > APR) */
    {
    /* southern hemisphere rules */

    if (CompareStdTimeFields (
          &gmtStdTimeFields,
          &gmtDstEndStdTimeFields) < 0)
      {
      bool_InDst = STDTIME_TRUE; /* before DST to STD transition */
      }

    else if (CompareStdTimeFields (
          &gmtStdTimeFields,
          &gmtDstStartStdTimeFields) < 0)
      {
      bool_InDst = STDTIME_FALSE; /* before STD to DST transition */
      }

    else
      {
      bool_InDst = STDTIME_TRUE; /* after STD to DST transition */
      }
    }

  *pDstFlag = bool_InDst;

  /* OK means we were able to determine the DST status */
  /* the pDstFlag contains the answer to the question */

  STDTIME_RET_OK;

  } /* StdTimeApiFileTimeIsDST */


/*** timezone-offset support functions ***************************************/


/*-***************************************************************************/
/*            StdTimeStringAToTzoA                                           */
/*  copy the embedded timezone-offset embTzo of a STDTIME_STRINGA into a     */
/*  STDTIME_TZOA structure, which can be a STDTIME_STRINGA.extTzo field.     */
/*  within STDTIME_STRINGA, the embedded embTzo appears at an offset of      */
/*  STDTIME_STRING_LEN from the start of STDTIME_STRINGA.str                 */
/*  note that 'str' and 'embTzo' char string are adjacent.                   */
/*****************************************************************************/

STDTIME_RC                  StdTimeStringAToTzoA (
  const STDTIME_STRINGA *   /*I*/ pStdTimeString,
  STDTIME_TZOA *            /*O*/ pTzo)
  {
  STDTIME_ENUM_FUNC (StdTimeStringAToTzoA)

  if (pTzo == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pTzo = ZeroStdTimeTzoA  ();

  if (pStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  strncpy (pTzo->str, pStdTimeString->embTzo, STDTIME_TZO_LEN);

  pTzo->str[STDTIME_TZO_LEN] = 0;

  STDTIME_RET_OK;

  } /* StdTimeStringAToTzoA */


/*-***************************************************************************/
/*            StdTimeStringWToTzoW                                           */
/*  copy the embedded timezone-offset embTzo of a STDTIME_STRINGW into a     */
/*  STDTIME_TZOW structure, which can be a STDTIME_STRINGW.extTzo field.     */
/*  within STDTIME_STRINGW, the embedded embTzo appears at an offset of      */
/*  STDTIME_STRING_LEN from the start of STDTIME_STRINGW.str                 */
/*  note that 'str' and 'embTzo' char string are adjacent.                   */
/*****************************************************************************/

STDTIME_RC                  StdTimeStringWToTzoW (
  const STDTIME_STRINGW *   /*I*/ pStdTimeString,
  STDTIME_TZOW *            /*O*/ pTzo)
  {
  STDTIME_ENUM_FUNC (StdTimeStringWToTzoW)

  if (pTzo == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pTzo = ZeroStdTimeTzoW  ();

  if (pStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  Wchar_StdTime_StrncpyWW (pTzo->str, pStdTimeString->embTzo, STDTIME_TZO_LEN);

  pTzo->str[STDTIME_TZO_LEN] = 0;

  STDTIME_RET_OK;

  } /* StdTimeStringWToTzoW */


/*-***************************************************************************/
/*            TzoAToStdTimeStringA                                           */
/*  copy a STDTIME_TZOA structure which may be a STDTIME_STRINGA.extTzo      */
/*  field, into the timezone-offset portion of a STDTIME_STRINGA.            */
/*  within a STDTIME_STRINGA, the embedded TZO appears at an offset of       */
/*  STDTIME_STRING_LEN from the start of STDTIME_STRINGA.str                 */
/*****************************************************************************/

STDTIME_RC                  TzoAToStdTimeStringA (
  const STDTIME_TZOA *      /*I*/ pTzo,
  STDTIME_STRINGA *         /*O*/ pStdTimeString)
  {
  STDTIME_ENUM_FUNC (TzoAToStdTimeStringA)

  if (pStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  pStdTimeString->embTzo[0] = 0;

  if (pTzo == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  strncpy (pStdTimeString->embTzo, pTzo->str, STDTIME_TZO_LEN);

  pStdTimeString->embTzo[STDTIME_TZO_LEN] = 0;

  STDTIME_RET_OK;

  } /* TzoAToStdTimeStringA */


/*-***************************************************************************/
/*            TzoWToStdTimeStringW                                           */
/*  copy a STDTIME_TZOW structure, which may be a STDTIME_STRINGW.extTzo     */
/*  field, into the timezone-offset portion of a STDTIME_STRINGW.            */
/*  within STDTIME_STRINGW, the embedded embTzo appears at an offset of      */
/*  STDTIME_STRING_LEN from the start of STDTIME_STRINGW.str                 */
/*****************************************************************************/

STDTIME_RC                  TzoWToStdTimeStringW (
  const STDTIME_TZOW *      /*I*/ pTzo,
  STDTIME_STRINGW *         /*O*/ pStdTimeString)
  {
  STDTIME_ENUM_FUNC (TzoWToStdTimeStringW)

  if (pStdTimeString == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  pStdTimeString->embTzo[0] = 0;

  if (pTzo == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  Wchar_StdTime_StrncpyWW (pStdTimeString->embTzo, pTzo->str, STDTIME_TZO_LEN);

  pStdTimeString->embTzo[STDTIME_TZO_LEN] = 0;

  STDTIME_RET_OK;

  } /* TzoWToStdTimeStringW */


/*-***************************************************************************/
/*            ValidStdTimeTzoA                                               */
/*  test if timezone offset string is in a valid format                      */
/*  the string may be empty, and trailing blanks are ignored.                */
/*  a timezone offset may be one of the following:                           */
/*      Z                                                                    */
/*      +hh:mm                                                               */
/*      +hh:mm:ss                                                            */
/*      -hh:mm                                                               */
/*      -hh:mm:ss                                                            */
/* ---------------------                                                     */
/*      0123456789                                                           */
/*****************************************************************************/


STDTIME_RC                  ValidStdTimeTzoA (
  const STDTIME_TZOA *      /*I*/ pTzo)
  {
  int32_t                   hour;
  int32_t                   min;
  int32_t                   sec;

  STDTIME_ENUM_FUNC (ValidStdTimeTzoA)

  if (pTzo == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  /* see if timezone offset is omitted */

  if (Bool_StdTime_IsBlankA (pTzo->str))
    {
    STDTIME_RET_OK;
    }

  if ((pTzo->str[0] == 'z') || (pTzo->str[0] == 'Z'))
    {
    if (Bool_StdTime_IsBlankA (pTzo->str+1))
      {
      STDTIME_RET_OK;
      }
    }

  if ((pTzo->str[0] != '+') && (pTzo->str[0] != '-'))
    {
    STDTIME_RET_EC (invalid_timezone_offset);
    }

  if ( (! isdigit (pTzo->str[1]))
  ||   (! isdigit (pTzo->str[2]))
  ||   (           pTzo->str[3] != ':')
  ||   (! isdigit (pTzo->str[4]))
  ||   (! isdigit (pTzo->str[5])) )
    {
    STDTIME_RET_EC (invalid_timezone_offset);
    }

  hour = atoi (pTzo->str+1);
  min  = atoi (pTzo->str+4);

  if (! STDTIME_IN_RANGE (hour, 0, 23))
    {
    STDTIME_RET_EC (invalid_hour);
    }

  if (! STDTIME_IN_RANGE (min,  0, 59))
    {
    STDTIME_RET_EC (invalid_min);
    }

  /* determine whether we have short form or long form */
  /* long form: validate 'ss' digits */

  if (pTzo->str[6] == ':')
    {
    if ( (! isdigit (pTzo->str[7]))
    ||   (! isdigit (pTzo->str[8])) )
      {
      STDTIME_RET_EC (invalid_timezone_offset);
      }

    sec = atoi (pTzo->str+7);

    if (! STDTIME_IN_RANGE (sec, 0, 59))
      {
      STDTIME_RET_EC (invalid_sec);
      }

    if (Bool_StdTime_IsBlankA (pTzo->str+9))
      {
      STDTIME_RET_OK;
      }
    else
      {
      STDTIME_RET_EC (invalid_timezone_offset);
      }
    }

  /* short form: ensure we are at end of string */

  else
    {
    if (Bool_StdTime_IsBlankA (pTzo->str+6))
      {
      STDTIME_RET_OK;
      }
    else
      {
      STDTIME_RET_EC (invalid_timezone_offset);
      }
    }

  } /* ValidStdTimeTzoA */


/*-***************************************************************************/
/*            ValidStdTimeTzoW                                               */
/*  Unicode version of ValidStdTimeTzoA                                      */
/*  method: copy Unicode TZOW string to Ansi TZOA string, then validate the  */
/*  Ansi version of the timezone offset string.                              */
/*****************************************************************************/

STDTIME_RC                  ValidStdTimeTzoW (
  const STDTIME_TZOW *      /*I*/ pTzo)
  {
  STDTIME_TZOA              tzoA;

  STDTIME_ENUM_FUNC (ValidStdTimeTzoW)

  if (pTzo == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  Char_StdTime_StrncpyAW (tzoA.str, pTzo->str, STDTIME_TZO_LEN);

  STDTIME_RET (ValidStdTimeTzoA (&tzoA));

  } /* ValidStdTimeTzoW */


/*-***************************************************************************/
/*            NormalizeStdTimeTzoA                                           */
/*  if timezone offset string is in a valid format, normalize it.            */
/*  normalization involves the following:                                    */
/*                                                                           */
/*  1.  a 'z' code is converted to 'Z'                                       */
/*  2.  if the ss field is zero, it is dropped                               */
/*  3.  if all numeric fields are zero, the offset string becomes Z          */
/*  4.  trailing blanks are removed, and replaced by nuls                    */
/*                                                                           */
/*****************************************************************************/


STDTIME_RC                  NormalizeStdTimeTzoA (
  STDTIME_TZOA *            /*IO*/ pTzo)
  {
  STDTIME_TZOA              tzoA = {{0}};
  int32_t                   hour;
  int32_t                   min;
  int32_t                   sec;

  STDTIME_ENUM_FUNC (NormalizeStdTimeTzoA)

  if (pTzo == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  /* limit input tzo string to declared length, jic */

  pTzo->str[STDTIME_TZO_LEN] = 0;

  /* see if timezone offset is omitted */

  if (Bool_StdTime_IsBlankA (pTzo->str))
    {
    *pTzo = tzoA;           /* clear out entire TZO field */
    STDTIME_RET_OK;
    }

  if ((pTzo->str[0] == 'z') || (pTzo->str[0] == 'Z'))
    {
    if (Bool_StdTime_IsBlankA (pTzo->str+1))
      {
      /* normalize Z and pad field with nuls */
      tzoA.str[0] = 'Z';
      *pTzo = tzoA;
      STDTIME_RET_OK;
      }
    }

  if ((pTzo->str[0] != '+') && (pTzo->str[0] != '-'))
    {
    STDTIME_RET_EC (invalid_timezone_offset);
    }

  if ( (! isdigit (pTzo->str[1]))
  ||   (! isdigit (pTzo->str[2]))
  ||   (           pTzo->str[3] != ':')
  ||   (! isdigit (pTzo->str[4]))
  ||   (! isdigit (pTzo->str[5])) )
    {
    STDTIME_RET_EC (invalid_timezone_offset);
    }

  hour = atoi (pTzo->str+1);
  min  = atoi (pTzo->str+4);

  if (! STDTIME_IN_RANGE (hour, 0, 23))
    {
    STDTIME_RET_EC (invalid_hour);
    }

  if (! STDTIME_IN_RANGE (min, 0, 59))
    {
    STDTIME_RET_EC (invalid_min);
    }

  /* determine whether we have short form or long form */
  /* long form: validate 'ss' digits */

  if (pTzo->str[6] == ':')
    {
    if ( (! isdigit (pTzo->str[7]))
    ||   (! isdigit (pTzo->str[8])) )
      {
      STDTIME_RET_EC (invalid_timezone_offset);
      }

    sec = atoi (pTzo->str+7);

    if (! STDTIME_IN_RANGE (sec, 0, 59))
      {
      STDTIME_RET_EC (invalid_sec);
      }

    if (! Bool_StdTime_IsBlankA (pTzo->str+9))
      {
      STDTIME_RET_EC (invalid_timezone_offset);
      }
    }

  /* short form: ensure we are at end of string */

  else
    {
    if (! Bool_StdTime_IsBlankA (pTzo->str+6))
      {
      STDTIME_RET_EC (invalid_timezone_offset);
      }

    sec = 0;
    }

  /* now, normalize the format */

  if ((hour == 0) && (min == 0) && (sec == 0))
    {
    /* if all fields zero, it is GMT time */
    /* normalize Z and pad field with nuls */
    tzoA.str[0] = 'Z';
    *pTzo = tzoA;
    STDTIME_RET_OK;
    }

  if (sec == 0)
    {
    /* +hh:mm or -hh:mm format */
    sprintf (tzoA.str, "%c%02d:%02d", pTzo->str[0], hour, min);
    }

  else
    {
    /* +hh:mm:ss or -hh:mm:ss format */
    sprintf (tzoA.str, "%c%02d:%02d:%02d", pTzo->str[0], hour, min, sec);
    }

  *pTzo = tzoA;           /* copy back reformatted tzoA */
  STDTIME_RET_OK;

  } /* NormalizeStdTimeTzoA */


/*-***************************************************************************/
/*            NormalizeStdTimeTzoW                                           */
/*  Unicode version of NormalizeStdTimeTzoA                                  */
/*  method: copy Unicode TZOW string to Ansi TZOA string, normalize the Ansi */
/*  version of the timezone offset string, and copy back to Unicode string.  */
/*****************************************************************************/

STDTIME_RC                  NormalizeStdTimeTzoW (
  STDTIME_TZOW *            /*I*/ pTzo)
  {
  STDTIME_TZOA              tzoA;
  STDTIME_TZOW              tzoW = {{0}};

  STDTIME_ENUM_FUNC (NormalizeStdTimeTzoW)

  if (pTzo == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  Char_StdTime_StrncpyAW (tzoA.str, pTzo->str, STDTIME_TZO_LEN);

  if STDTIME_IF (NormalizeStdTimeTzoA (&tzoA))
    {
    /* copy back Ansi to Unicode, ensuring no junk chars at end of string */

    Wchar_StdTime_StrncpyWA (tzoW.str, tzoA.str, STDTIME_TZO_LEN);
    *pTzo = tzoW;
    STDTIME_RET_OK;
    }

  STDTIME_RET_RC;

  } /* NormalizeStdTimeTzoW */


/*-***************************************************************************/
/*            GetLocalStdTimeTzoA                                            */
/*  query operating system for timezone offset as numeric value, and return  */
/*  an appropriate string.  if the offset is zero, the string is Z.          */
/*  method: get current time as a FILETIME, then convert to local time.      */
/*  determine the time difference and convert to hh:mm:ss format.            */
/*  NOTE: this technique only works with the current time, unless            */
/*  STDTIME_LOCAL_USES_TZDB is defined.                                      */
/*****************************************************************************/

STDTIME_RC                  GetLocalStdTimeTzoA (
  STDTIME_TZOA *            /*O*/ pTzo)
  {
  STDTIME_WIN_FILETIME      gmtFileTime;
  STDTIME_WIN_FILETIME      locFileTime;

  QUADLIB_I64               qGmtTime;
  QUADLIB_I64               qLocTime;
  QUADLIB_I64               qDiff;
  QUADLIB_I64               qNum;
  QUADLIB_I64               qDiv = QUADLIB_ZERO;
  int32_t                   num;
  int32_t                   sec;
  int32_t                   min;
  int32_t                   hour;
  char                      sign;

  STDTIME_ENUM_FUNC (GetLocalStdTimeTzoA)

  if (pTzo == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pTzo = ZeroStdTimeTzoA ();

  STDTIME_API_GETSYSTEMTIMEASFILETIME (&gmtFileTime);

#ifdef STDTIME_LOCAL_USES_TZDB

  if STDTIME_IFNOT (StdTimeApiFileTimeToZonedFileTime (
       NULL, &gmtFileTime, &locFileTime))
    {
    STDTIME_RET_RC;
    }

#else

  if (! STDTIME_API_FILETIMETOLOCALFILETIME (&gmtFileTime, &locFileTime))
    {
    STDTIME_RET_EC (failure_in_api_FileTimeToLocalFileTime);
    }

#endif

  FILETIME_TO_QUADLIB_I64 (&gmtFileTime, &qGmtTime);
  FILETIME_TO_QUADLIB_I64 (&locFileTime, &qLocTime);

  /* to get the correct sign, calculate offset = loc - gmt */
  /* example: in EST zone, 11:12:34 EST - 16:12:34 GMT = -05:00:00 */

  qDiff = QUADLIB_I64_SUB (qLocTime, qGmtTime);

  /* if difference is zero, we are in GMT */

  if (QUADLIB_I64_EQ_0 (qDiff))
    {
    pTzo->str[0] = 'Z';     /* set zulu time */
    STDTIME_RET_OK;
    }

  if (QUADLIB_I64_LT_0 (qDiff))
    {
    sign = '-';
    qDiff = QUADLIB_I64_NEG (qDiff);
    }

  else
    {
    sign = '+';
    }

  /* calculate seconds */

  QUADLIB_U64_LO (qDiv) = 10000000;
  qNum = QUADLIB_I64_DIV (qDiff, qDiv);

  /* there should not be more than 86,400 seconds, which fits in an int32_t */
  /* this will simplify the remaining calculations */

  if (QUADLIB_U64_HI (qNum) != 0)
    {
    STDTIME_RET_EC (cannot_determine_local_timezone_offset);
    }

  num  = QUADLIB_I64_LO (qNum);
  sec  = num % 60;
  num  = num / 60;
  min  = num % 60;
  hour = num / 60;

  if (hour > 24)
    {
    STDTIME_RET_EC (cannot_determine_local_timezone_offset);
    }

  if (sec == 0)
    {
    /* +hh:mm or -hh:mm format */
    sprintf (pTzo->str, "%c%02d:%02d", sign, hour, min);
    }

  else
    {
    /* +hh:mm:ss or -hh:mm:ss format */
    sprintf (pTzo->str, "%c%02d:%02d:%02d", sign, hour, min, sec);
    }

  STDTIME_RET_OK;

  } /* GetLocalStdTimeTzoA */


/*-***************************************************************************/
/*            GetLocalStdTimeTzoW                                            */
/*  get Ansi timezone offset string from GetLocalStdTimeTzoA and then        */
/*  convert to Unicode.                                                      */
/*****************************************************************************/

STDTIME_RC                  GetLocalStdTimeTzoW (
  STDTIME_TZOW *            /*O*/ pTzo)
  {
  STDTIME_TZOA              tzoA = {{0}};

  STDTIME_ENUM_FUNC (GetLocalStdTimeTzoW)

  if (pTzo == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pTzo = ZeroStdTimeTzoW ();

  if STDTIME_IFNOT (GetLocalStdTimeTzoA (&tzoA))
    {
    STDTIME_RET_RC;
    }

  Wchar_StdTime_StrncpyWA (pTzo->str, tzoA.str, STDTIME_TZO_LEN);
  pTzo->str [STDTIME_TZO_LEN] = 0;

  STDTIME_RET_OK;

  } /* GetLocalStdTimeTzoW */



/*** error message decoding functions ****************************************/


/*-***************************************************************************/
/*            StdTimeRcToErrMsgA                                             */
/*  interpret STDTIME_RC value and convert to a STDTIME_ERRMSGA structure.   */
/*****************************************************************************/

STDTIME_RC                  StdTimeRcToErrMsgA (
  const STDTIME_RC          /*I*/ stdTimeRc,
  STDTIME_ERRMSGA *         /*O*/ pErrMsg)
  {
  STDTIME_ERRMSGA           errMsg = {{0}};
  int32_t                   hilevel;
  int32_t                   lolevel;
  int32_t                   reason;
  int32_t                   i;

  STDTIME_ENUM_FUNC (StdTimeRcToErrMsgA)

  if (pErrMsg == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pErrMsg = ZeroStdTimeErrMsgA ();

  /* a STDTIME_RC has the following bit layout */
  /* bits 31-30(2)  unused                     */
  /* bits 29-20(10) hi-level function enum     */
  /* bits 19-10(10) lo-level function enum     */
  /* bits 09-00(10) error reason code          */

  hilevel = (stdTimeRc >> 20) & 0x3FF;
  lolevel = (stdTimeRc >> 10) & 0x3FF;
  reason  =  stdTimeRc        & 0x3FF;

  /* an error code has the form   0xNNNNNNNN = HHHH.LLLL.RRRR#      */
  /*                              0123456789012345678901234567      */
  /* this holds a raw hex RC value, and the RC as decimal subfields */

  sprintf (errMsg.errcode, "0x%08X = %04d.%04d.%04d",
    stdTimeRc, hilevel, lolevel, reason);

  if ((stdTimeRc & 0xC0000000) != 0)
    {
    strncpy (errMsg.hilevel, "*** invalid STDTIME_RC value",
      STDTIME_ERRMSG_LEN);

    *pErrMsg = errMsg;          /* pass back result */
    STDTIME_RET_EC (invalid_stdtime_rc_value);
    }

  /* the first entry is at STDTIME_FUNC__0000 with an enum value of 0 */
  /* enum 0 is "valid" but 0 is not used for error return codes, because */
  /* a STDTIME_RC of 0 means there is no error, so 0 is skipped. */
  /* example: suppose there were 10 entries; they would have enum's 1 to 10 */
  /* the last entry is at STDTIME_FUNC__SIZE with (example) enum value of 11 */

  if (hilevel < (STDTIME_RC) STDTIME_FUNC__SIZE)
    {
    strncpy (errMsg.hilevel, enum_stdtime_func_text[hilevel],
      STDTIME_ERRMSG_LEN);
    }

  else
    {
    strncpy (errMsg.hilevel, "*** undefined hilevel function",
      STDTIME_ERRMSG_LEN);
    }

  if (lolevel < (STDTIME_RC) STDTIME_FUNC__SIZE)
    {
    strncpy (errMsg.lolevel, enum_stdtime_func_text[lolevel],
      STDTIME_ERRMSG_LEN);
    }

  else
    {
    strncpy (errMsg.lolevel, "*** undefined lolevel function",
      STDTIME_ERRMSG_LEN);
    }

  if (reason < (STDTIME_RC) STDTIME_ERR__SIZE)
    {
    strncpy (errMsg.reason, enum_stdtime_err_text[reason],
      STDTIME_ERRMSG_LEN);
    }

  else
    {
    strncpy (errMsg.reason, "*** undefined reason code",
      STDTIME_ERRMSG_LEN);
    }

  errMsg.hilevel[STDTIME_ERRMSG_LEN] = 0;
  errMsg.lolevel[STDTIME_ERRMSG_LEN] = 0;
  errMsg.reason [STDTIME_ERRMSG_LEN] = 0;

  /* remove underscores from reason message */
  /* the underscores were necessary for the macro to form an enum name */
  /* but we don't want them literally present in the message */

  for (i=0; errMsg.reason[i]; i++)
    {
    if (errMsg.reason[i] == '_')
      {
      errMsg.reason[i] = ' ';
      }
    }

 *pErrMsg = errMsg;         /* pass back result */

  STDTIME_RET_RC;

  } /* StdTimeRcToErrMsgA */


/*-***************************************************************************/
/*            StdTimeRcToErrMsgW                                             */
/*  interpret STDTIME_RC value and convert to a STDTIME_ERRMSGW structure.   */
/*  call StdTimeRcToErrMsgA to do conversion, then do Ansi to Unicode.       */
/*****************************************************************************/

STDTIME_RC                  StdTimeRcToErrMsgW (
  const STDTIME_RC          /*I*/ stdTimeRc,
  STDTIME_ERRMSGW *         /*O*/ pErrMsg)
  {
  STDTIME_ERRMSGA           errMsgA = {{0}};

  STDTIME_ENUM_FUNC (StdTimeRcToErrMsgW)

  if (pErrMsg == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pErrMsg = ZeroStdTimeErrMsgW ();

  rc = StdTimeRcToErrMsgA (stdTimeRc, &errMsgA);


  Wchar_StdTime_StrncpyWA (
    pErrMsg->errcode, errMsgA.errcode, STDTIME_ERRCODE_LEN);

  pErrMsg->errcode[STDTIME_ERRCODE_LEN] = 0;

  Wchar_StdTime_StrncpyWA (
    pErrMsg->hilevel, errMsgA.hilevel, STDTIME_ERRMSG_LEN);

  pErrMsg->hilevel[STDTIME_ERRMSG_LEN] = 0;

  Wchar_StdTime_StrncpyWA (
    pErrMsg->lolevel, errMsgA.lolevel, STDTIME_ERRMSG_LEN);

  pErrMsg->lolevel[STDTIME_ERRMSG_LEN] = 0;

  Wchar_StdTime_StrncpyWA (
    pErrMsg->reason, errMsgA.reason, STDTIME_ERRMSG_LEN);

  pErrMsg->reason[STDTIME_ERRMSG_LEN] = 0;


  STDTIME_RET_RC;

  } /* StdTimeRcToErrMsgW */


/*** END - STDTIME.C *********************************************************/

