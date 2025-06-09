/*+***************************************************************************/
/* SISCO SOFTWARE MODULE HEADER **********************************************/
/* ***************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,            */
/*            2005 All Rights Reserved                                       */
/*                                                                           */
/* MODULE NAME : stdtime_cppsvcs.cpp                                         */
/* PRODUCT(S)  : Standard Time Management Library                            */
/*                                                                           */
/* MODULE DESCRIPTION:                                                       */
/*   Implementation of Standard Time Management C++ Services for Windows     */
/*                                                                           */
/*   Note:  most functions a produce a return-code value STDTIME_RC.         */
/*   the return code is zero if successful, otherwise it is a structured     */
/*   value in which the low-order 10 bits enumerates an error reason,        */
/*   and the upper 20 bits enumerates the high-level and low-level           */
/*   functions where the error was detected.                                 */
/*                                                                           */
/* MODIFICATION LOG:                                                         */
/*   Date    Who  Rev  Comments                                              */
/* --------  ---  ---  ----------------------------------------------------- */
/* 06/07/06  RLH   02  Numerous features added, see stdtime.doc              */
/* 05/12/06  RLH   01  Created                                               */
/*+***************************************************************************/

#define _CRT_SECURE_NO_DEPRECATE

#ifndef _SASSERTE
#define _SASSERTE(x)
#endif

#include <windows.h>
#include "comdate.h"
#include "stdtime_cppsvcs.h"


/*** private (helper) macros and static areas ********************************/


#define STDTIME_IF(x)       ((rc=(x)) == STDTIME_OK)
#define STDTIME_IFNOT(x)    ((rc=(x)) != STDTIME_OK)


/*** private (helper) functions **********************************************/

/* NOTE: function names beginning with Rc_, Int_, Char_, Wchar_ and Bool_    */
/* are private functions; the prefix identifies the return type.             */


/*-***************************************************************************/
/*            Rc_StdTimeRet - PRIVATE FUNCTION                               */
/*  assemble a STDTIME return code                                           */
/*  when basic error code is 0, always return 0                              */
/*****************************************************************************/

static STDTIME_RC           Rc_StdTimeRet (
  const STDTIME_RC          func,
  const STDTIME_RC          ec)
  {
  if (ec == 0) return 0;
  return ((func & STDTIME_10_BITS) << 20) | (ec & STDTIME_20_BITS);
  }


/*****************************************************************************/
/*** TIME FUNCTIONS **********************************************************/
/*****************************************************************************/


/*** CTimeEx functions *******************************************************/


#ifdef STDTIME_CPP_CTIME_ENABLED


/*-***************************************************************************/
/*            StdTimeToCTimeEx                                               */
/*  convert: StdTime structure to CTime and extra fields                     */
/*****************************************************************************/

STDTIME_RC                  StdTimeToCTimeEx (
  const STDTIME *           /*I*/ pStdTime,
  CTime *                   /*O*/ pCTime,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME_TIMETYPE          tt;

  STDTIME_ENUM_FUNC (StdTimeToCTimeEx)

  /* convert StdTime to TIMETYPE, then convert to CTime */

  if STDTIME_IF (StdTimeToTimeTypeEx (pStdTime, &tt, pMsec, pUsec, pNsec))
    {
    *pCTime = tt.t;         // operator = time_t || __time64_t
    STDTIME_RET_OK;
    }

  STDTIME_RET_RC;

  } /* StdTimeToCTimeEx */


/*-***************************************************************************/
/*            StdTimeFieldsToCTimeEx                                         */
/*  convert: StdTimeFields structure to CTime and extra fields               */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToCTimeEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  CTime *                   /*O*/ pCTime,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME_TIMETYPE          tt;

  STDTIME_ENUM_FUNC (StdTimeFieldsToCTimeEx)

  /* convert StdTimeFields to TIMETYPE, then convert to CTime */

  if STDTIME_IF (StdTimeFieldsToTimeTypeEx (
       pStdTimeFields, &tt, pMsec, pUsec, pNsec))
    {
    *pCTime = tt.t;         // operator = time_t || __time64_t
    STDTIME_RET_OK;
    }

  STDTIME_RET_RC;

  } /* StdTimeFieldsToCTimeEx */


/*-***************************************************************************/
/*            CTimeExToStdTime                                               */
/*  convert: CTime and extra fields to StdTime structure                     */
/*****************************************************************************/

STDTIME_RC                  CTimeExToStdTime (
  const CTime *             /*I*/ pCTime,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_TIMETYPE          tt;

  STDTIME_ENUM_FUNC (CTimeExToStdTime)

  if (pCTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  tt.t = pCTime->GetTime(); // returns time_t || __time64_t

  STDTIME_RET (TimeTypeExToStdTime (&tt, nMsec, nUsec, nNsec, pStdTime));

  } /* CTimeExToStdTime */


/*-***************************************************************************/
/*            CTimeExToStdTimeFields                                         */
/*  convert: CTime and extra fields to StdTimeFields structure               */
/*****************************************************************************/

STDTIME_RC                  CTimeExToStdTimeFields (
  const CTime *             /*I*/ pCTime,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_TIMETYPE          tt;

  STDTIME_ENUM_FUNC (CTimeExToStdTimeFields)

  if (pCTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  tt.t = pCTime->GetTime(); // returns time_t || __time64_t

  STDTIME_RET (TimeTypeExToStdTimeFields (
    &tt, nMsec, nUsec, nNsec, pStdTimeFields));

  } /* CTimeExToStdTimeFields */


/*** CTime functions *********************************************************/


/*-***************************************************************************/
/*            StdTimeToCTime                                                 */
/*  convert: StdTime struct to CTime (without extra fields)                  */
/*****************************************************************************/

STDTIME_RC                  StdTimeToCTime (
  const STDTIME *           /*I*/ pStdTime,
  CTime *                   /*O*/ pCTime)
  {
  STDTIME_ENUM_FUNC (StdTimeToCTime)

  STDTIME_RET (StdTimeToCTimeEx (pStdTime, pCTime, NULL, NULL, NULL));

  } /* StdTimeToCTime */


/*-***************************************************************************/
/*            CTimeToStdTime                                                 */
/*  convert: CTime (without extra fields) to StdTime struct                  */
/*****************************************************************************/

STDTIME_RC                  CTimeToStdTime (
  const CTime *             /*I*/ pCTime,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_ENUM_FUNC (CTimeToStdTime)

  STDTIME_RET (CTimeExToStdTime (pCTime, 0, 0, 0, pStdTime));

  } /* CTimeToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToCTime                                           */
/*  convert: StdTimeFields struct to CTime (without extra fields)            */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToCTime (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  CTime *                   /*O*/ pCTime)
  {
  STDTIME_ENUM_FUNC (StdTimeFieldsToCTime)

  STDTIME_RET (StdTimeFieldsToCTimeEx (
    pStdTimeFields, pCTime, NULL, NULL, NULL));

  } /* StdTimeFieldsToCTime */


/*-***************************************************************************/
/*            CTimeToStdTimeFields                                           */
/*  convert: CTime (without extra fields) to StdTimeFields struct            */
/*****************************************************************************/


STDTIME_RC                  CTimeToStdTimeFields (
  const CTime *             /*I*/ pCTime,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_ENUM_FUNC (CTimeToStdTimeFields)

  STDTIME_RET (CTimeExToStdTimeFields (pCTime, 0, 0, 0, pStdTimeFields));

  } /* CTimeToStdTimeFields */


#endif /* STDTIME_CPP_CTIME_ENABLED */


/*** CFileTime functions *****************************************************/


#ifdef STDTIME_CPP_CFILETIME_ENABLED


/*-***************************************************************************/
/*            StdTimeToCFileTime                                             */
/*  convert: StdTime structure to CFileTime class                            */
/*****************************************************************************/

STDTIME_RC                  StdTimeToCFileTime (
  const STDTIME *           /*I*/ pStdTime,
  CFileTime *               /*O*/ pCFileTime)
  {
  STDTIME_WIN_FILETIME      ft;

  STDTIME_ENUM_FUNC (StdTimeToCFileTime)

  if (pCFileTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeToFileTime (pStdTime, &ft))
    {
    *pCFileTime = ft;       // operator = FILETIME
    STDTIME_RET_OK;
    }

  STDTIME_RET_RC;

  } /* StdTimeToCFileTime */


/*-***************************************************************************/
/*            CFileTimeToStdTime                                             */
/*  convert: CFileTime class to StdTime structure                            */
/*****************************************************************************/

STDTIME_RC                  CFileTimeToStdTime (
  const CFileTime *         /*I*/ pCFileTime,
  STDTIME *                 /*O*/ pStdTime)
  {
  QUADLIB_U64               u64;
  STDTIME_WIN_FILETIME      ft;

  STDTIME_ENUM_FUNC (CFileTimeToStdTime)

  if (pCFileTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  u64 = (QUADLIB_U64) pCFileTime->GetTime();    // returns ULONGLONG

  QUADLIB_U64_TO_FILETIME (&u64, &ft);

  STDTIME_RET (FileTimeToStdTime (&ft, pStdTime));

  } /* CFileTimeToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToCFileTime                                       */
/*  convert: StdTimeFields structure to CFileTime class                      */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToCFileTime (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  CFileTime *               /*O*/ pCFileTime)
  {
  STDTIME_WIN_FILETIME      ft;

  STDTIME_ENUM_FUNC (StdTimeFieldsToCFileTime)

  if (pCFileTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeFieldsToFileTime (pStdTimeFields, &ft))
    {
    *pCFileTime = ft;       // operator = FILETIME
    STDTIME_RET_OK;
    }

  STDTIME_RET_RC;

  } /* StdTimeFieldsToCFileTime */


/*-***************************************************************************/
/*            CFileTimeToStdTimeFields                                       */
/*  convert: CFileTime class to StdTimeFields structure                      */
/*****************************************************************************/

STDTIME_RC                  CFileTimeToStdTimeFields (
  const CFileTime *         /*I*/ pCFileTime,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  QUADLIB_U64               u64;
  STDTIME_WIN_FILETIME      ft;

  STDTIME_ENUM_FUNC (CFileTimeToStdTimeFields)

  if (pCFileTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  u64 = (QUADLIB_U64) pCFileTime->GetTime();    // returns ULONGLONG

  QUADLIB_U64_TO_FILETIME (&u64, &ft);

  STDTIME_RET (FileTimeToStdTimeFields (&ft, pStdTimeFields));

  } /* CFileTimeToStdTimeFields */


#endif /* STDTIME_CPP_CFILETIME_ENABLED */


/*** HpCOleDateTimeEx functions **********************************************/


#ifdef STDTIME_CPP_COLEDATETIME_ENABLED


/*-***************************************************************************/
/*            StdTimeToCOleDateTimeEx                                        */
/*  convert: StdTime structure to COleDateTime time value and extra fields   */
/*****************************************************************************/

STDTIME_RC                  StdTimeToCOleDateTimeEx (
  const STDTIME *           /*I*/ pStdTime,
  COleDateTime *            /*O*/ pCOleDateTime,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME_WIN_DATE          cd;

  STDTIME_ENUM_FUNC (StdTimeToCOleDateTimeEx)

  if (pCOleDateTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeToDateEx (pStdTime, &cd, pMsec, pUsec, pNsec))
    {
    *pCOleDateTime = cd;    // operator = DATE
    STDTIME_RET_OK;
    }

  STDTIME_RET_RC;

  } /* StdTimeToCOleDateTimeEx */


/*-***************************************************************************/
/*            COleDateTimeExToStdTime                                        */
/*  convert: COleDateTime time value and extra fields to StdTime structure   */
/*****************************************************************************/

STDTIME_RC                  COleDateTimeExToStdTime (
  const COleDateTime *      /*I*/ pCOleDateTime,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_WIN_DATE          cd;

  STDTIME_ENUM_FUNC (COleDateTimeExToStdTime)

  if (pCOleDateTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  cd = (DATE) *pCOleDateTime;   // operator DATE typecast

  STDTIME_RET (DateExToStdTime (&cd, nMsec, nUsec, nNsec, pStdTime));

  } /* COleDateTimeExToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToCOleDateTimeEx                                  */
/*  convert: StdTime structure to COleDateTime time value                    */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToCOleDateTimeEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  COleDateTime *            /*O*/ pCOleDateTime,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME_WIN_DATE          cd;

  STDTIME_ENUM_FUNC (StdTimeFieldsToCOleDateTimeEx)

  if (pCOleDateTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeFieldsToDateEx (
       pStdTimeFields, &cd, pMsec, pUsec, pNsec))
    {
    *pCOleDateTime = cd;    // operator = DATE
    STDTIME_RET_OK;
    }

  STDTIME_RET_RC;

  } /* StdTimeFieldsToCOleDateTimeEx */


/*-***************************************************************************/
/*            COleDateTimeExToStdTimeFields                                  */
/*  convert: COleDateTime time value to StdTimeFields structure              */
/*****************************************************************************/

STDTIME_RC                  COleDateTimeExToStdTimeFields (
  const COleDateTime *      /*I*/ pCOleDateTime,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_WIN_DATE          cd;

  STDTIME_ENUM_FUNC (COleDateTimeExToStdTimeFields)

  if (pCOleDateTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  cd = (DATE) *pCOleDateTime;   // operator DATE typecast

  STDTIME_RET (DateExToStdTimeFields (
    &cd, nMsec, nUsec, nNsec, pStdTimeFields));

  } /* COleDateTimeExToStdTimeFields */


/*** COleDateTime functions **************************************************/


/*-***************************************************************************/
/*            StdTimeToCOleDateTime                                          */
/*  convert: StdTime structure to COleDateTime time value                    */
/*****************************************************************************/

STDTIME_RC                  StdTimeToCOleDateTime (
  const STDTIME *           /*I*/ pStdTime,
  COleDateTime *            /*O*/ pCOleDateTime)
  {
  STDTIME_ENUM_FUNC (StdTimeToCOleDateTime)

  STDTIME_RET (StdTimeToCOleDateTimeEx (
    pStdTime,
    pCOleDateTime, NULL, NULL, NULL));

  } /* StdTimeToCOleDateTime */


/*-***************************************************************************/
/*            COleDateTimeToStdTime                                          */
/*  convert: COleDateTime time value to StdTime structure                    */
/*****************************************************************************/

STDTIME_RC                  COleDateTimeToStdTime (
  const COleDateTime *      /*I*/ pCOleDateTime,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_ENUM_FUNC (COleDateTimeToStdTime)

  STDTIME_RET (COleDateTimeExToStdTime (
    pCOleDateTime, 0, 0, 0,
    pStdTime));

  } /* COleDateTimeToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToCOleDateTime                                    */
/*  convert: StdTime structure to COleDateTime time value                    */
/*****************************************************************************/


STDTIME_RC                  StdTimeFieldsToCOleDateTime (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  COleDateTime *            /*O*/ pCOleDateTime)
  {
  STDTIME_ENUM_FUNC (StdTimeFieldsToCOleDateTime)

  STDTIME_RET (StdTimeFieldsToCOleDateTimeEx (
    pStdTimeFields,
    pCOleDateTime, NULL, NULL, NULL));

  } /* StdTimeFieldsToCOleDateTime */


/*-***************************************************************************/
/*            COleDateTimeToStdTimeFields                                    */
/*  convert: COleDateTime time value to StdTimeFields structure              */
/*****************************************************************************/

STDTIME_RC                  COleDateTimeToStdTimeFields (
  const COleDateTime *      /*I*/ pCOleDateTime,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_ENUM_FUNC (COleDateTimeToStdTimeFields)

  STDTIME_RET (COleDateTimeExToStdTimeFields (
    pCOleDateTime, 0, 0, 0,
    pStdTimeFields));

  } /* COleDateTimeToStdTimeFields */


/*** HpCOleDateTimeEx functions **********************************************/


/*-***************************************************************************/
/*            StdTimeToHpCOleDateTimeEx                                      */
/*  convert: StdTime structure to COleDateTime time value and extra fields   */
/*****************************************************************************/

STDTIME_RC                  StdTimeToHpCOleDateTimeEx (
  const STDTIME *           /*I*/ pStdTime,
  COleDateTime *            /*O*/ pCOleDateTime,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME_WIN_DATE          cd;

  STDTIME_ENUM_FUNC (StdTimeToHpCOleDateTimeEx)

  if (pCOleDateTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeToHpDateEx (pStdTime, &cd, pUsec, pNsec))
    {
    *pCOleDateTime = cd;    // operator = DATE
    STDTIME_RET_OK;
    }

  STDTIME_RET_RC;

  } /* StdTimeToHpCOleDateTimeEx */


/*-***************************************************************************/
/*            HpCOleDateTimeExToStdTime                                      */
/*  convert: COleDateTime time value and extra fields to StdTime structure   */
/*****************************************************************************/

STDTIME_RC                  HpCOleDateTimeExToStdTime (
  const COleDateTime *      /*I*/ pCOleDateTime,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_WIN_DATE          cd;

  STDTIME_ENUM_FUNC (HpCOleDateTimeExToStdTime)

  if (pCOleDateTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  cd = (DATE) *pCOleDateTime;   // operator DATE typecast

  STDTIME_RET (HpDateExToStdTime (&cd, nUsec, nNsec, pStdTime));

  } /* HpCOleDateTimeExToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToHpCOleDateTimeEx                                */
/*  convert: StdTime structure to COleDateTime time value                    */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToHpCOleDateTimeEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  COleDateTime *            /*O*/ pCOleDateTime,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME_WIN_DATE          cd;

  STDTIME_ENUM_FUNC (StdTimeFieldsToHpCOleDateTimeEx)

  if (pCOleDateTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeFieldsToHpDateEx (
       pStdTimeFields, &cd, pUsec, pNsec))
    {
    *pCOleDateTime = cd;    // operator = DATE
    STDTIME_RET_OK;
    }

  STDTIME_RET_RC;

  } /* StdTimeFieldsToHpCOleDateTimeEx */


/*-***************************************************************************/
/*            HpCOleDateTimeExToStdTimeFields                                */
/*  convert: COleDateTime time value to StdTimeFields structure              */
/*****************************************************************************/

STDTIME_RC                  HpCOleDateTimeExToStdTimeFields (
  const COleDateTime *      /*I*/ pCOleDateTime,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_WIN_DATE          cd;

  STDTIME_ENUM_FUNC (HpCOleDateTimeExToStdTimeFields)

  if (pCOleDateTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  cd = (DATE) *pCOleDateTime;   // operator DATE typecast

  STDTIME_RET (HpDateExToStdTimeFields (
    &cd, nUsec, nNsec, pStdTimeFields));

  } /* HpCOleDateTimeExToStdTimeFields */


/*** HpCOleDateTime functions ************************************************/


/*-***************************************************************************/
/*            StdTimeToHpCOleDateTime                                        */
/*  convert: StdTime structure to COleDateTime time value                    */
/*****************************************************************************/

STDTIME_RC                  StdTimeToHpCOleDateTime (
  const STDTIME *           /*I*/ pStdTime,
  COleDateTime *            /*O*/ pCOleDateTime)
  {
  STDTIME_ENUM_FUNC (StdTimeToHpCOleDateTime)

  STDTIME_RET (StdTimeToHpCOleDateTimeEx (
    pStdTime,
    pCOleDateTime, NULL, NULL));

  } /* StdTimeToHpCOleDateTime */


/*-***************************************************************************/
/*            HpCOleDateTimeToStdTime                                        */
/*  convert: COleDateTime time value to StdTime structure                    */
/*****************************************************************************/

STDTIME_RC                  HpCOleDateTimeToStdTime (
  const COleDateTime *      /*I*/ pCOleDateTime,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_ENUM_FUNC (HpCOleDateTimeToStdTime)

  STDTIME_RET (HpCOleDateTimeExToStdTime (
    pCOleDateTime, 0, 0,
    pStdTime));

  } /* HpCOleDateTimeToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToHpCOleDateTime                                  */
/*  convert: StdTime structure to COleDateTime time value                    */
/*****************************************************************************/


STDTIME_RC                  StdTimeFieldsToHpCOleDateTime (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  COleDateTime *            /*O*/ pCOleDateTime)
  {
  STDTIME_ENUM_FUNC (StdTimeFieldsToHpCOleDateTime)

  STDTIME_RET (StdTimeFieldsToHpCOleDateTimeEx (
    pStdTimeFields,
    pCOleDateTime, NULL, NULL));

  } /* StdTimeFieldsToHpCOleDateTime */


/*-***************************************************************************/
/*            HpCOleDateTimeToStdTimeFields                                  */
/*  convert: COleDateTime time value to StdTimeFields structure              */
/*****************************************************************************/


STDTIME_RC                  HpCOleDateTimeToStdTimeFields (
  const COleDateTime *      /*I*/ pCOleDateTime,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_ENUM_FUNC (HpCOleDateTimeToStdTimeFields)

  STDTIME_RET (HpCOleDateTimeExToStdTimeFields (
    pCOleDateTime, 0, 0,
    pStdTimeFields));

  } /* HpCOleDateTimeToStdTimeFields */


#endif /* STDTIME_CPP_COLEDATETIME_ENABLED */


/*** CComDateEx functions **************************************************/


#ifdef STDTIME_CPP_CCOMDATE_ENABLED


/*-***************************************************************************/
/*            StdTimeToCComDateEx                                            */
/*  convert: StdTime structure to CComDATE time value and extra fields       */
/*****************************************************************************/

STDTIME_RC                  StdTimeToCComDateEx (
  const STDTIME *           /*I*/ pStdTime,
  CComDATE *                /*O*/ pCComDate,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME_WIN_DATE          cd;

  STDTIME_ENUM_FUNC (StdTimeToCComDateEx)

  if (pCComDate == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeToDateEx (pStdTime, &cd, pMsec, pUsec, pNsec))
    {
    *pCComDate = cd;        // operator = DATE
    STDTIME_RET_OK;
    }

  STDTIME_RET_RC;

  } /* StdTimeToCComDateEx */


/*-***************************************************************************/
/*            CComDateExToStdTime                                            */
/*  convert: CComDATE time value and extra fields to StdTime structure       */
/*****************************************************************************/

STDTIME_RC                  CComDateExToStdTime (
  const CComDATE *          /*I*/ pCComDate,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_WIN_DATE          cd;

  STDTIME_ENUM_FUNC (CComDateExToStdTime)

  if (pCComDate == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  cd = (DATE) *pCComDate;       // operator DATE typecast

  STDTIME_RET (DateExToStdTime (&cd, nMsec, nUsec, nNsec, pStdTime));

  } /* CComDateExToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToCComDateEx                                      */
/*  convert: StdTime structure to CComDATE time value                        */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToCComDateEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  CComDATE *                /*O*/ pCComDate,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME_WIN_DATE          cd;

  STDTIME_ENUM_FUNC (StdTimeFieldsToCComDateEx)

  if (pCComDate == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeFieldsToDateEx (
       pStdTimeFields, &cd, pMsec, pUsec, pNsec))
    {
    *pCComDate = cd;        // operator = DATE
    STDTIME_RET_OK;
    }

  STDTIME_RET_RC;

  } /* StdTimeFieldsToCComDateEx */


/*-***************************************************************************/
/*            CComDateExToStdTimeFields                                      */
/*  convert: CComDATE time value to StdTimeFields structure                  */
/*****************************************************************************/

STDTIME_RC                  CComDateExToStdTimeFields (
  const CComDATE *          /*I*/ pCComDate,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_WIN_DATE          cd;

  STDTIME_ENUM_FUNC (CComDateExToStdTimeFields)

  if (pCComDate == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  cd = (DATE) *pCComDate;       // operator DATE typecast

  STDTIME_RET (DateExToStdTimeFields (
    &cd, nMsec, nUsec, nNsec, pStdTimeFields));

  } /* CComDateExToStdTimeFields */


/*** CComDate functions ******************************************************/


/*-***************************************************************************/
/*            StdTimeToCComDate                                              */
/*  convert: StdTime structure to CComDATE time value                        */
/*****************************************************************************/

STDTIME_RC                  StdTimeToCComDate (
  const STDTIME *           /*I*/ pStdTime,
  CComDATE *                /*O*/ pCComDate)
  {
  STDTIME_ENUM_FUNC (StdTimeToCComDate)

  STDTIME_RET (StdTimeToCComDateEx (
    pStdTime,
    pCComDate, NULL, NULL, NULL));

  } /* StdTimeToCComDate */


/*-***************************************************************************/
/*            CComDateToStdTime                                              */
/*  convert: CComDATE time value to StdTime structure                        */
/*****************************************************************************/

STDTIME_RC                  CComDateToStdTime (
  const CComDATE *          /*I*/ pCComDate,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_ENUM_FUNC (CComDateToStdTime)

  STDTIME_RET (CComDateExToStdTime (
    pCComDate, 0, 0, 0,
    pStdTime));

  } /* CComDateToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToCComDate                                        */
/*  convert: StdTime structure to CComDATE time value                        */
/*****************************************************************************/


STDTIME_RC                  StdTimeFieldsToCComDate (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  CComDATE *                /*O*/ pCComDate)
  {
  STDTIME_ENUM_FUNC (StdTimeFieldsToCComDate)

  STDTIME_RET (StdTimeFieldsToCComDateEx (
    pStdTimeFields,
    pCComDate, NULL, NULL, NULL));

  } /* StdTimeFieldsToCComDate */


/*-***************************************************************************/
/*            CComDateToStdTimeFields                                        */
/*  convert: CComDATE time value to StdTimeFields structure                  */
/*****************************************************************************/

STDTIME_RC                  CComDateToStdTimeFields (
  const CComDATE *          /*I*/ pCComDate,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_ENUM_FUNC (CComDateToStdTimeFields)

  STDTIME_RET (CComDateExToStdTimeFields (
    pCComDate, 0, 0, 0,
    pStdTimeFields));

  } /* CComDateToStdTimeFields */


/*** HpCComDateEx functions **************************************************/


/*-***************************************************************************/
/*            StdTimeToHpCComDateEx                                          */
/*  convert: StdTime structure to CComDATE time value and extra fields       */
/*****************************************************************************/

STDTIME_RC                  StdTimeToHpCComDateEx (
  const STDTIME *           /*I*/ pStdTime,
  CComDATE *                /*O*/ pCComDate,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME_WIN_DATE          cd;

  STDTIME_ENUM_FUNC (StdTimeToHpCComDateEx)

  if (pCComDate == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeToHpDateEx (pStdTime, &cd, pUsec, pNsec))
    {
    *pCComDate = cd;        // operator = DATE
    STDTIME_RET_OK;
    }

  STDTIME_RET_RC;

  } /* StdTimeToHpCComDateEx */


/*-***************************************************************************/
/*            HpCComDateExToStdTime                                          */
/*  convert: CComDATE time value and extra fields to StdTime structure       */
/*****************************************************************************/

STDTIME_RC                  HpCComDateExToStdTime (
  const CComDATE *          /*I*/ pCComDate,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_WIN_DATE          cd;

  STDTIME_ENUM_FUNC (HpCComDateExToStdTime)

  if (pCComDate == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  cd = (DATE) *pCComDate;       // operator DATE typecast

  STDTIME_RET (HpDateExToStdTime (&cd, nUsec, nNsec, pStdTime));

  } /* HpCComDateExToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToHpCComDateEx                                    */
/*  convert: StdTime structure to CComDATE time value                        */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToHpCComDateEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  CComDATE *                /*O*/ pCComDate,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME_WIN_DATE          cd;

  STDTIME_ENUM_FUNC (StdTimeFieldsToHpCComDateEx)

  if (pCComDate == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeFieldsToHpDateEx (
       pStdTimeFields, &cd, pUsec, pNsec))
    {
    *pCComDate = cd;        // operator = DATE
    STDTIME_RET_OK;
    }

  STDTIME_RET_RC;

  } /* StdTimeFieldsToHpCComDateEx */


/*-***************************************************************************/
/*            HpCComDateExToStdTimeFields                                    */
/*  convert: CComDATE time value to StdTimeFields structure                  */
/*****************************************************************************/

STDTIME_RC                  HpCComDateExToStdTimeFields (
  const CComDATE *          /*I*/ pCComDate,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_WIN_DATE          cd;

  STDTIME_ENUM_FUNC (HpCComDateExToStdTimeFields)

  if (pCComDate == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  cd = (DATE) *pCComDate;       // operator DATE typecast

  STDTIME_RET (HpDateExToStdTimeFields (
    &cd, nUsec, nNsec, pStdTimeFields));

  } /* HpCComDateExToStdTimeFields */


/*** HpCComDate functions ****************************************************/


/*-***************************************************************************/
/*            StdTimeToHpCComDate                                            */
/*  convert: StdTime structure to CComDATE time value                        */
/*****************************************************************************/

STDTIME_RC                  StdTimeToHpCComDate (
  const STDTIME *           /*I*/ pStdTime,
  CComDATE *                /*O*/ pCComDate)
  {
  STDTIME_ENUM_FUNC (StdTimeToHpCComDate)

  STDTIME_RET (StdTimeToHpCComDateEx (
    pStdTime,
    pCComDate, NULL, NULL));

  } /* StdTimeToHpCComDate */


/*-***************************************************************************/
/*            HpCComDateToStdTime                                            */
/*  convert: CComDATE time value to StdTime structure                        */
/*****************************************************************************/

STDTIME_RC                  HpCComDateToStdTime (
  const CComDATE *          /*I*/ pCComDate,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_ENUM_FUNC (HpCComDateToStdTime)

  STDTIME_RET (HpCComDateExToStdTime (
    pCComDate, 0, 0,
    pStdTime));

  } /* HpCComDateToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToHpCComDate                                      */
/*  convert: StdTime structure to CComDATE time value                        */
/*****************************************************************************/


STDTIME_RC                  StdTimeFieldsToHpCComDate (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  CComDATE *                /*O*/ pCComDate)
  {
  STDTIME_ENUM_FUNC (StdTimeFieldsToHpCComDate)

  STDTIME_RET (StdTimeFieldsToHpCComDateEx (
    pStdTimeFields,
    pCComDate,  NULL, NULL));

  } /* StdTimeFieldsToHpCComDate */


/*-***************************************************************************/
/*            HpCComDateToStdTimeFields                                      */
/*  convert: CComDATE time value to StdTimeFields structure                  */
/*****************************************************************************/


STDTIME_RC                  HpCComDateToStdTimeFields (
  const CComDATE *          /*I*/ pCComDate,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_ENUM_FUNC (HpCComDateToStdTimeFields)

  STDTIME_RET (HpCComDateExToStdTimeFields (
    pCComDate, 0, 0,
    pStdTimeFields));

  } /* HpCComDateToStdTimeFields */


#endif /* STDTIME_CPP_CCOMDATE_ENABLED */

/*****************************************************************************/
/*** CComDate / DATE FUNCTIONS ***********************************************/
/*****************************************************************************/

/* because CComDATE defines an operator & that returns a pointer to a DATE,  */
/* the usual calling sequences won't work.  so, we define CComDATE functions */
/* that take a pointer to DATE, so we won't need type casting to call them.  */


/*** HpCComDateEx / DATE functions *******************************************/


STDTIME_RC                  StdTimeToHpCComDateEx (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_DATE *        /*O*/ pDate,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  return StdTimeToHpDateEx (pStdTime, pDate, pUsec, pNsec);
  }


STDTIME_RC                  HpCComDateExToStdTime (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime)
  {
  return HpDateExToStdTime (pDate, nUsec, nNsec, pStdTime);
  }


STDTIME_RC                  StdTimeFieldsToHpCComDateEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_DATE *        /*O*/ pDate,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  return StdTimeFieldsToHpDateEx (pStdTimeFields, pDate, pUsec, pNsec);
  }


STDTIME_RC                  HpCComDateExToStdTimeFields (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  return HpDateExToStdTimeFields (pDate, nUsec, nNsec, pStdTimeFields);
  }


/*** HpCComDate / DATE functions *********************************************/


STDTIME_RC                  StdTimeToHpCComDate (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_DATE *        /*O*/ pDate)
  {
  return StdTimeToHpDate (pStdTime, pDate);
  }


STDTIME_RC                  HpCComDateToStdTime (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  STDTIME *                 /*O*/ pStdTime)
  {
  return HpDateToStdTime (pDate, pStdTime);
  }


STDTIME_RC                  StdTimeFieldsToHpCComDate (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_DATE *        /*O*/ pDate)
  {
  return StdTimeFieldsToHpDate (pStdTimeFields, pDate);
  }


STDTIME_RC                  HpCComDateToStdTimeFields (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  return HpDateToStdTimeFields (pDate, pStdTimeFields);
  }


/*** CComDateEx / DATE functions *********************************************/


STDTIME_RC                  StdTimeToCComDateEx (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_DATE *        /*O*/ pDate,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  return StdTimeToDateEx (pStdTime, pDate, pMsec, pUsec, pNsec);
  }


STDTIME_RC                  CComDateExToStdTime (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME *                 /*O*/ pStdTime)
  {
  return DateExToStdTime (pDate, nMsec, nUsec, nNsec, pStdTime);
  }


STDTIME_RC                  StdTimeFieldsToCComDateEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_DATE *        /*O*/ pDate,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  return StdTimeFieldsToDateEx (pStdTimeFields, pDate, pMsec, pUsec, pNsec);
  }


STDTIME_RC                  CComDateExToStdTimeFields (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  return DateExToStdTimeFields (pDate, nMsec, nUsec, nNsec, pStdTimeFields);
  }


/*** CComDate / DATE functions ***********************************************/


STDTIME_RC                  StdTimeToCComDate (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_WIN_DATE *        /*O*/ pDate)
  {
  return StdTimeToDate (pStdTime, pDate);
  }


STDTIME_RC                  CComDateToStdTime (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  STDTIME *                 /*O*/ pStdTime)
  {
  return DateToStdTime (pDate, pStdTime);
  }


STDTIME_RC                  StdTimeFieldsToCComDate (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_WIN_DATE *        /*O*/ pDate)
  {
  return StdTimeFieldsToDate (pStdTimeFields, pDate);
  }


STDTIME_RC                  CComDateToStdTimeFields (
  const STDTIME_WIN_DATE *  /*I*/ pDate,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  return DateToStdTimeFields (pDate,pStdTimeFields);
  }


/*****************************************************************************/
/*** SPAN FUNCTIONS **********************************************************/
/*****************************************************************************/


/*** CTimeSpanEx functions ***************************************************/


/*****************************************************************************/
/*                                                                           */
/* CTimeSpan has an implementation type of time_t or __time64_t              */
/* in units of seconds.                                                      */
/*                                                                           */
/* CTimeSpan::GetTotalSeconds() returns the time span in seconds;            */
/* CTimeSpan::GetTimeSpan() also returns the time span in seconds.           */
/*                                                                           */
/* CTimeSpan::CTimeSpan( __time64_t time) may be used to construct a         */
/* CTimeSpan object, which may then be assigned; there is no explicit        */
/* assignment operator for this class.                                       */
/*                                                                           */
/*****************************************************************************/


#ifdef STDTIME_CPP_CTIME_ENABLED


/*-***************************************************************************/
/*            StdTimeSpanToCTimeSpanEx                                       */
/*  convert: StdTimeSpan structure to CTimeSpan and extra fields             */
/*****************************************************************************/
///
STDTIME_RC                  StdTimeSpanToCTimeSpanEx (
  const STDTIME_SPAN *      /*I*/ pStdTimeSpan,
  CTimeSpan *               /*O*/ pCTimeSpan,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME_TIMETYPE          tt;
  int32_t                   nRem;

  STDTIME_ENUM_FUNC (StdTimeSpanToCTimeSpanEx)

  /* convert StdTimeSpan to TIMETYPE, then convert to CTimeSpan via ctor */

  if ((pStdTimeSpan == NULL) || (pCTimeSpan == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  tt.t = pStdTimeSpan->value / 10000000;            // secs
  nRem = (int32_t) pStdTimeSpan->value % 10000000;  // num of 100-nsec units

  if (pMsec != NULL)
    {
    *pMsec = nRem / 10000;
    }

  if (pUsec != NULL)
    {
    *pUsec = (nRem / 10) % 1000;
    }

  if (pNsec != NULL)
    {
    *pNsec = (nRem % 10) * 100;
    }

  CTimeSpan     nCTimeSpan (tt.t);  // assign via ctor
  *pCTimeSpan = nCTimeSpan;

  STDTIME_RET_OK;

  } /* StdTimeSpanToCTimeSpanEx */


/*-***************************************************************************/
/*            StdTimeDeltaToCTimeSpanEx                                      */
/*  convert: StdTimeDelta structure to CTimeSpan and extra fields            */
/*****************************************************************************/
///
STDTIME_RC                  StdTimeDeltaToCTimeSpanEx (
  const STDTIME_DELTA *     /*I*/ pStdTimeDelta,
  CTimeSpan *               /*O*/ pCTimeSpan,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME_SPAN              stdTimeSpan;

  STDTIME_ENUM_FUNC (StdTimeDeltaToCTimeSpanEx)

  /* convert StdTimeDelta to StdTimeSpan to CTimeSPan */

  if STDTIME_IF (StdTimeDeltaToStdTimeSpan (pStdTimeDelta, &stdTimeSpan))
    {
    STDTIME_RET (StdTimeSpanToCTimeSpanEx (
       &stdTimeSpan, pCTimeSpan, pMsec, pUsec, pNsec));
    }

  STDTIME_RET_RC;

  } /* StdTimeDeltaToCTimeSpanEx */


/*-***************************************************************************/
/*            CTimeSpanExToStdTimeSpan                                       */
/*  convert: CTimeSpan and extra fields to StdTimeSpan structure             */
/*****************************************************************************/
///
STDTIME_RC                  CTimeSpanExToStdTimeSpan (
  const CTimeSpan *         /*I*/ pCTimeSpan,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_SPAN *            /*O*/ pStdTimeSpan)
  {
  STDTIME_TIMETYPE          tt;
  STDTIME_SPAN              nStdTimeSpan;

  STDTIME_ENUM_FUNC (CTimeSpanExToStdTimeSpan)

  if ((pCTimeSpan == NULL) || (pStdTimeSpan == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  tt.t = pCTimeSpan->GetTotalSeconds(); // returns time_t || __time64_t
  nStdTimeSpan.value = tt.t * (QUADLIB_I64N) 10000000;  // secs -> 100-ns units

  if (nMsec)
    {
    nStdTimeSpan.value += (QUADLIB_I64N) nMsec * (QUADLIB_I64N) 10000;
    }

  if (nUsec)
    {
    nStdTimeSpan.value += (QUADLIB_I64N) nUsec * (QUADLIB_I64N) 10;
    }

  if (nNsec)
    {
    nStdTimeSpan.value += (QUADLIB_I64N) nNsec / (QUADLIB_I64N) 100;
    }

  pStdTimeSpan->value = nStdTimeSpan.value;

  STDTIME_RET (ValidStdTimeSpan (pStdTimeSpan));

  } /* CTimeSpanExToStdTimeSpan */


/*-***************************************************************************/
/*            CTimeSpanExToStdTimeDelta                                      */
/*  convert: CTimeSpan and extra fields to StdTimeDelta structure            */
/*****************************************************************************/
///
STDTIME_RC                  CTimeSpanExToStdTimeDelta (
  const CTimeSpan *         /*I*/ pCTimeSpan,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_DELTA *           /*O*/ pStdTimeDelta)
  {
  STDTIME_TIMETYPE          tt;
  STDTIME_SPAN              stdTimeSpan;

  STDTIME_ENUM_FUNC (CTimeSpanExToStdTimeDelta)

  if (pCTimeSpan == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  tt.t = pCTimeSpan->GetTotalSeconds(); // returns time_t || __time64_t

  if STDTIME_IF (CTimeSpanExToStdTimeSpan (
       pCTimeSpan, nMsec, nUsec, nNsec, &stdTimeSpan))
    {
    STDTIME_RET (StdTimeSpanToStdTimeDelta (&stdTimeSpan, pStdTimeDelta));
    }

  STDTIME_RET_RC;

  } /* CTimeSpanExToStdTimeDelta */


/*** CTimeSpan functions *****************************************************/


/*-***************************************************************************/
/*            StdTimeSpanToCTimeSpan                                         */
/*  convert: StdTimeSpan struct to CTimeSpan (without extra fields)          */
/*****************************************************************************/
///
STDTIME_RC                  StdTimeSpanToCTimeSpan (
  const STDTIME_SPAN *      /*I*/ pStdTimeSpan,
  CTimeSpan *               /*O*/ pCTimeSpan)
  {
  STDTIME_ENUM_FUNC (StdTimeSpanToCTimeSpan)

  STDTIME_RET (StdTimeSpanToCTimeSpanEx (
    pStdTimeSpan, pCTimeSpan, NULL, NULL, NULL));

  } /* StdTimeSpanToCTimeSpan */


/*-***************************************************************************/
/*            CTimeSpanToStdTimeSpan                                         */
/*  convert: CTimeSpan (without extra fields) to StdTimeSpan struct          */
/*****************************************************************************/
///
STDTIME_RC                  CTimeSpanToStdTimeSpan (
  const CTimeSpan *         /*I*/ pCTimeSpan,
  STDTIME_SPAN *            /*O*/ pStdTimeSpan)
  {
  STDTIME_ENUM_FUNC (CTimeSpanToStdTimeSpan)

  STDTIME_RET (CTimeSpanExToStdTimeSpan (pCTimeSpan, 0, 0, 0, pStdTimeSpan));

  } /* CTimeSpanToStdTimeSpan */


/*-***************************************************************************/
/*            StdTimeDeltaToCTimeSpan                                        */
/*  convert: StdTimeDelta struct to CTimeSpan (without extra fields)         */
/*****************************************************************************/
///
STDTIME_RC                  StdTimeDeltaToCTimeSpan (
  const STDTIME_DELTA *     /*I*/ pStdTimeDelta,
  CTimeSpan *               /*O*/ pCTimeSpan)
  {
  STDTIME_ENUM_FUNC (StdTimeDeltaToCTimeSpan)

  STDTIME_RET (StdTimeDeltaToCTimeSpanEx (
    pStdTimeDelta, pCTimeSpan, NULL, NULL, NULL));

  } /* StdTimeDeltaToCTimeSpan */


/*-***************************************************************************/
/*            CTimeSpanToStdTimeDelta                                        */
/*  convert: CTimeSpan (without extra fields) to StdTimeDelta struct         */
/*****************************************************************************/
///
STDTIME_RC                  CTimeSpanToStdTimeDelta (
  const CTimeSpan *         /*I*/ pCTimeSpan,
  STDTIME_DELTA *           /*O*/ pStdTimeDelta)
  {
  STDTIME_ENUM_FUNC (CTimeSpanToStdTimeDelta)

  STDTIME_RET (CTimeSpanExToStdTimeDelta (pCTimeSpan, 0, 0, 0, pStdTimeDelta));

  } /* CTimeSpanToStdTimeDelta */


#endif /* STDTIME_CPP_CTIME_ENABLED */


/*** CFileTimeSpan functions *************************************************/


/*****************************************************************************/
/*                                                                           */
/* CFileTimeSpan has an implementation type of LONGLONG in 100-nsec units.   */
/*                                                                           */
/* CFileTimeSpan::GetTimeSpan() returns the time span in 100-nsec units.     */
/* CFileTimeSpan::SetTimeSpan( LONGLONG nSpan) may be used to set the value. */
/*                                                                           */
/* a CFileTimeSpan has the same numeric value as a STDTIME_SPAN.             */
/*                                                                           */
/*****************************************************************************/


#ifdef STDTIME_CPP_CFILETIME_ENABLED


/*-***************************************************************************/
/*            StdTimeSpanToCFileTimeSpan                                     */
/*  convert: StdTimeSpan structure to CFileTimeSpan class                    */
/*****************************************************************************/

STDTIME_RC                  StdTimeSpanToCFileTimeSpan (
  const STDTIME_SPAN *      /*I*/ pStdTimeSpan,
  CFileTimeSpan *           /*O*/ pCFileTimeSpan)
  {
  STDTIME_ENUM_FUNC (StdTimeSpanToCFileTimeSpan)

  if ((pStdTimeSpan == NULL) || (pCFileTimeSpan == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  pCFileTimeSpan->SetTimeSpan ((LONGLONG) pStdTimeSpan->value);

  STDTIME_RET_OK;

  } /* StdTimeSpanToCFileTimeSpan */


/*-***************************************************************************/
/*            CFileTimeSpanToStdTimeSpan                                     */
/*  convert: CFileTimeSpan class to StdTimeSpan structure                    */
/*****************************************************************************/

STDTIME_RC                  CFileTimeSpanToStdTimeSpan (
  const CFileTimeSpan *     /*I*/ pCFileTimeSpan,
  STDTIME_SPAN *            /*O*/ pStdTimeSpan)
  {
  STDTIME_ENUM_FUNC (CFileTimeSpanToStdTimeSpan)

  if ((pCFileTimeSpan == NULL) || (pCFileTimeSpan == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  pStdTimeSpan->value = (QUADLIB_I64N) pCFileTimeSpan->GetTimeSpan ();

  STDTIME_RET (ValidStdTimeSpan (pStdTimeSpan));

  } /* CFileTimeSpanToStdTimeSpan */


/*-***************************************************************************/
/*            StdTimeDeltaToCFileTimeSpan                                    */
/*  convert: StdTimeDelta structure to CFileTimeSpan class                   */
/*****************************************************************************/
///
STDTIME_RC                  StdTimeDeltaToCFileTimeSpan (
  const STDTIME_DELTA *     /*I*/ pStdTimeDelta,
  CFileTimeSpan *           /*O*/ pCFileTimeSpan)
  {
  STDTIME_SPAN              stdTimeSpan;

  STDTIME_ENUM_FUNC (StdTimeDeltaToCFileTimeSpan)

  if (pCFileTimeSpan == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeDeltaToStdTimeSpan (pStdTimeDelta, &stdTimeSpan))
    {
    STDTIME_RET (StdTimeSpanToCFileTimeSpan (&stdTimeSpan, pCFileTimeSpan));
    }

  STDTIME_RET_RC;

  } /* StdTimeDeltaToCFileTimeSpan */


/*-***************************************************************************/
/*            CFileTimeSpanToStdTimeDelta                                    */
/*  convert: CFileTimeSpan class to StdTimeDelta structure                   */
/*****************************************************************************/

STDTIME_RC                  CFileTimeSpanToStdTimeDelta (
  const CFileTimeSpan *     /*I*/ pCFileTimeSpan,
  STDTIME_DELTA *           /*O*/ pStdTimeDelta)
  {
  STDTIME_SPAN              stdTimeSpan;

  STDTIME_ENUM_FUNC (CFileTimeSpanToStdTimeDelta)

  if ((pCFileTimeSpan == NULL) || (pStdTimeDelta == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  stdTimeSpan.value = (QUADLIB_I64N) pCFileTimeSpan->GetTimeSpan ();

  STDTIME_RET (StdTimeSpanToStdTimeDelta (&stdTimeSpan, pStdTimeDelta));

  } /* CFileTimeSpanToStdTimeDelta */


#endif /* STDTIME_CPP_CFILETIME_ENABLED */


/*** HpCOleDateTimeSpanEx functions ******************************************/


#ifdef STDTIME_CPP_COLEDATETIME_ENABLED


/*****************************************************************************/
/*                                                                           */
/* COleDateTimeSpan has an implementation type of double.                    */
/* it has nominal precision in secs, maximum effective precision in msecs,   */
/* but it actually stored in terms of days and fractions of a day.           */
/*                                                                           */
/* operator double() returns the COleDateTimeSpan double value.              */
/*                                                                           */
/* operator = (double dblSpanSrc) will assign a COleDateTimeSpan double      */
/* value, and it sets the internal status to 'valid'.                        */
/*                                                                           */
/* COleDateTimeSpan::SetStatus(DateTimeSpanStatus status) may be used to     */
/* set the validity of a COleDateTimeSpan value.                             */
/*                                                                           */
/* if COleDateTimeSpan::DateTimeSpanStatus() does not return 'valid' (0),    */
/* the object value is 'invalid' or 'null' and cannot be converted.          */
/*                                                                           */
/*****************************************************************************/


/*-***************************************************************************/
/*            StdTimeSpanToCOleDateTimeSpanEx                                */
/*  convert: StdTimeSpan struct to COleDateTimeSpan value and extra fields   */
/*****************************************************************************/

STDTIME_RC                  StdTimeSpanToCOleDateTimeSpanEx (
  const STDTIME_SPAN *      /*I*/ pStdTimeSpan,
  COleDateTimeSpan *        /*O*/ pCOleDateTimeSpan,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  double                    nSpan;
  QUADLIB_I64N              qNum;
  int32_t                   nRem;

  STDTIME_ENUM_FUNC (StdTimeSpanToCOleDateTimeSpanEx)

  if ((pStdTimeSpan == NULL) || (pCOleDateTimeSpan == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  qNum = pStdTimeSpan->value / 10000000;            // secs
  nRem = (int32_t) pStdTimeSpan->value % 10000000;  // num of 100-nsec units

  nSpan = ((double) qNum) / (24.0 * 60.0 * 60.0);

  if (pMsec != NULL)
    {
    *pMsec = nRem / 10000;
    }

  if (pUsec != NULL)
    {
    *pUsec = (nRem / 10) % 1000;
    }

  if (pNsec != NULL)
    {
    *pNsec = (nRem % 10) * 100;
    }

  *pCOleDateTimeSpan = nSpan; // operator = double

  STDTIME_RET_OK;

  } /* StdTimeSpanToCOleDateTimeSpanEx */


/*-***************************************************************************/
/*            COleDateTimeSpanExToStdTimeSpan                                */
/*  convert: COleDateTimeSpan value and extra fields to StdTimeSpan struct   */
/*****************************************************************************/

STDTIME_RC                  COleDateTimeSpanExToStdTimeSpan (
  const COleDateTimeSpan *  /*I*/ pCOleDateTimeSpan,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_SPAN *            /*O*/ pStdTimeSpan)
  {
  double                    nSpan;

  STDTIME_ENUM_FUNC (COleDateTimeSpanExToStdTimeSpan)

  if ((pCOleDateTimeSpan == NULL) || (pStdTimeSpan == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  if (pCOleDateTimeSpan->GetStatus() == COleDateTimeSpan::null)
    {
    pStdTimeSpan->value = 0;
    STDTIME_RET_EC (COleDateTimeSpan_status_is_null);
    }

  else if (pCOleDateTimeSpan->GetStatus() != COleDateTimeSpan::valid)
    {
    pStdTimeSpan->value = 0;
    STDTIME_RET_EC (COleDateTimeSpan_status_is_invalid);
    }

  // invoke operator double()

  nSpan = (double) *pCOleDateTimeSpan;  // returns number of days

  pStdTimeSpan->value =
      ((QUADLIB_I64N) (nSpan * 24.0 * 60.0 * 60.0)) * 10000000
    + (nMsec * 10000)
    + (nUsec * 10)
    + (nNsec / 100);

  STDTIME_RET (ValidStdTimeSpan (pStdTimeSpan));

  } /* COleDateTimeSpanExToStdTimeSpan */


/*-***************************************************************************/
/*            StdTimeDeltaToCOleDateTimeSpanEx                               */
/*  convert: StdTimeSpan structure to COleDateTimeSpan value                 */
/*****************************************************************************/

STDTIME_RC                  StdTimeDeltaToCOleDateTimeSpanEx (
  const STDTIME_DELTA *     /*I*/ pStdTimeDelta,
  COleDateTimeSpan *        /*O*/ pCOleDateTimeSpan,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME_SPAN              stdTimeSpan;

  STDTIME_ENUM_FUNC (StdTimeDeltaToCOleDateTimeSpanEx)

  if STDTIME_IF (StdTimeDeltaToStdTimeSpan (pStdTimeDelta, &stdTimeSpan))
    {
    STDTIME_RET (StdTimeSpanToCOleDateTimeSpanEx (
       &stdTimeSpan, pCOleDateTimeSpan, pMsec, pUsec, pNsec));
    }

  STDTIME_RET_RC;

  } /* StdTimeDeltaToCOleDateTimeSpanEx */


/*-***************************************************************************/
/*            COleDateTimeSpanExToStdTimeDelta                               */
/*  convert: COleDateTimeSpan value to StdTimeDelta structure                */
/*****************************************************************************/

STDTIME_RC                  COleDateTimeSpanExToStdTimeDelta (
  const COleDateTimeSpan *  /*I*/ pCOleDateTimeSpan,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_DELTA *           /*O*/ pStdTimeDelta)
  {
  STDTIME_SPAN              stdTimeSpan;

  STDTIME_ENUM_FUNC (COleDateTimeSpanExToStdTimeDelta)

  if STDTIME_IF (COleDateTimeSpanExToStdTimeSpan (
       pCOleDateTimeSpan, nMsec, nUsec, nNsec, &stdTimeSpan))
    {
    STDTIME_RET (StdTimeSpanToStdTimeDelta (&stdTimeSpan, pStdTimeDelta));
    }

  STDTIME_RET_RC;

  } /* COleDateTimeSpanExToStdTimeDelta */


/*** COleDateTimeSpan functions **********************************************/


/*-***************************************************************************/
/*            StdTimeSpanToCOleDateTimeSpan                                  */
/*  convert: StdTimeSpan structure to COleDateTimeSpan value                 */
/*****************************************************************************/

STDTIME_RC                  StdTimeSpanToCOleDateTimeSpan (
  const STDTIME_SPAN *      /*I*/ pStdTimeSpan,
  COleDateTimeSpan *        /*O*/ pCOleDateTimeSpan)
  {
  STDTIME_ENUM_FUNC (StdTimeSpanToCOleDateTimeSpan)

  STDTIME_RET (StdTimeSpanToCOleDateTimeSpanEx (
    pStdTimeSpan,
    pCOleDateTimeSpan, NULL, NULL, NULL));

  } /* StdTimeSpanToCOleDateTimeSpan */


/*-***************************************************************************/
/*            COleDateTimeSpanToStdTimeSpan                                  */
/*  convert: COleDateTimeSpan value to StdTimeSpan structure                 */
/*****************************************************************************/

STDTIME_RC                  COleDateTimeSpanToStdTimeSpan (
  const COleDateTimeSpan *  /*I*/ pCOleDateTimeSpan,
  STDTIME_SPAN *            /*O*/ pStdTimeSpan)
  {
  STDTIME_ENUM_FUNC (COleDateTimeSpanToStdTimeSpan)

  STDTIME_RET (COleDateTimeSpanExToStdTimeSpan (
    pCOleDateTimeSpan, 0, 0, 0,
    pStdTimeSpan));

  } /* COleDateTimeSpanToStdTimeSpan */


/*-***************************************************************************/
/*            StdTimeDeltaToCOleDateTimeSpan                                 */
/*  convert: StdTimeSpan structure to COleDateTimeSpan value                 */
/*****************************************************************************/


STDTIME_RC                  StdTimeDeltaToCOleDateTimeSpan (
  const STDTIME_DELTA *     /*I*/ pStdTimeDelta,
  COleDateTimeSpan *        /*O*/ pCOleDateTimeSpan)
  {
  STDTIME_ENUM_FUNC (StdTimeDeltaToCOleDateTimeSpan)

  STDTIME_RET (StdTimeDeltaToCOleDateTimeSpanEx (
    pStdTimeDelta,
    pCOleDateTimeSpan, NULL, NULL, NULL));

  } /* StdTimeDeltaToCOleDateTimeSpan */


/*-***************************************************************************/
/*            COleDateTimeSpanToStdTimeDelta                                 */
/*  convert: COleDateTimeSpan value to StdTimeDelta structure                */
/*****************************************************************************/

STDTIME_RC                  COleDateTimeSpanToStdTimeDelta (
  const COleDateTimeSpan *  /*I*/ pCOleDateTimeSpan,
  STDTIME_DELTA *           /*O*/ pStdTimeDelta)
  {
  STDTIME_ENUM_FUNC (COleDateTimeSpanToStdTimeDelta)

  STDTIME_RET (COleDateTimeSpanExToStdTimeDelta (
    pCOleDateTimeSpan, 0, 0, 0,
    pStdTimeDelta));

  } /* COleDateTimeSpanToStdTimeDelta */


/*** HpCOleDateTimeSpanEx functions ******************************************/


/*-***************************************************************************/
/*            StdTimeSpanToHpCOleDateTimeSpanEx                              */
/*  convert: StdTimeSpan struct to COleDateTimeSpan value and extra fields   */
/*****************************************************************************/

STDTIME_RC                  StdTimeSpanToHpCOleDateTimeSpanEx (
  const STDTIME_SPAN *      /*I*/ pStdTimeSpan,
  COleDateTimeSpan *        /*O*/ pCOleDateTimeSpan,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  double                    nSpan;
  QUADLIB_I64N              qNum;
  int32_t                   nRem;

  STDTIME_ENUM_FUNC (StdTimeSpanToHpCOleDateTimeSpanEx)

  if ((pStdTimeSpan == NULL) || (pCOleDateTimeSpan == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  qNum = pStdTimeSpan->value / 10000;               // msecs
  nRem = (int32_t) pStdTimeSpan->value % 10000;     // num of 100-nsec units

  nSpan = ((double) qNum) / (24.0 * 60.0 * 60.0 * 1000.0);

  if (pUsec != NULL)
    {
    *pUsec = (nRem / 10) % 1000;
    }

  if (pNsec != NULL)
    {
    *pNsec = (nRem % 10) * 100;
    }

  *pCOleDateTimeSpan = nSpan; // operator = double

  STDTIME_RET_OK;

  } /* StdTimeSpanToHpCOleDateTimeSpanEx */


/*-***************************************************************************/
/*            HpCOleDateTimeSpanExToStdTimeSpan                              */
/*  convert: COleDateTimeSpan value and extra fields to StdTimeSpan struct   */
/*****************************************************************************/

STDTIME_RC                  HpCOleDateTimeSpanExToStdTimeSpan (
  const COleDateTimeSpan *  /*I*/ pCOleDateTimeSpan,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_SPAN *            /*O*/ pStdTimeSpan)
  {
  double                    nSpan;

  STDTIME_ENUM_FUNC (HpCOleDateTimeSpanExToStdTimeSpan)

  if ((pCOleDateTimeSpan == NULL) || (pStdTimeSpan == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  if (pCOleDateTimeSpan->GetStatus() == COleDateTimeSpan::null)
    {
    pStdTimeSpan->value = 0;
    STDTIME_RET_EC (COleDateTimeSpan_status_is_null);
    }

  else if (pCOleDateTimeSpan->GetStatus() != COleDateTimeSpan::valid)
    {
    pStdTimeSpan->value = 0;
    STDTIME_RET_EC (COleDateTimeSpan_status_is_invalid);
    }

  // invoke operator double()

  nSpan = (double) *pCOleDateTimeSpan;  // returns number of days

  pStdTimeSpan->value =
      ((QUADLIB_I64N) (nSpan * 24.0 * 60.0 * 60.0 * 1000.0)) * 10000
    + (nUsec * 10)
    + (nNsec / 100);

  STDTIME_RET (ValidStdTimeSpan (pStdTimeSpan));

  } /* HpCOleDateTimeSpanExToStdTimeSpan */


/*-***************************************************************************/
/*            StdTimeDeltaToHpCOleDateTimeSpanEx                             */
/*  convert: StdTimeSpan structure to COleDateTimeSpan value                 */
/*****************************************************************************/

STDTIME_RC                  StdTimeDeltaToHpCOleDateTimeSpanEx (
  const STDTIME_DELTA *     /*I*/ pStdTimeDelta,
  COleDateTimeSpan *        /*O*/ pCOleDateTimeSpan,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME_SPAN              stdTimeSpan;

  STDTIME_ENUM_FUNC (StdTimeDeltaToHpCOleDateTimeSpanEx)

  if STDTIME_IF (StdTimeDeltaToStdTimeSpan (pStdTimeDelta, &stdTimeSpan))
    {
    STDTIME_RET (StdTimeSpanToHpCOleDateTimeSpanEx (
       &stdTimeSpan, pCOleDateTimeSpan, pUsec, pNsec));
    }

  STDTIME_RET_RC;

  } /* StdTimeDeltaToHpCOleDateTimeSpanEx */


/*-***************************************************************************/
/*            HpCOleDateTimeSpanExToStdTimeDelta                             */
/*  convert: COleDateTimeSpan value to StdTimeDelta structure                */
/*****************************************************************************/

STDTIME_RC                  HpCOleDateTimeSpanExToStdTimeDelta (
  const COleDateTimeSpan *  /*I*/ pCOleDateTimeSpan,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_DELTA *           /*O*/ pStdTimeDelta)
  {
  STDTIME_SPAN              stdTimeSpan;

  STDTIME_ENUM_FUNC (HpCOleDateTimeSpanExToStdTimeDelta)

  if STDTIME_IF (HpCOleDateTimeSpanExToStdTimeSpan (
       pCOleDateTimeSpan, nUsec, nNsec, &stdTimeSpan))
    {
    STDTIME_RET (StdTimeSpanToStdTimeDelta (&stdTimeSpan, pStdTimeDelta));
    }

  STDTIME_RET_RC;

  } /* HpCOleDateTimeSpanExToStdTimeDelta */


/*** HpCOleDateTimeSpan functions ********************************************/


/*-***************************************************************************/
/*            StdTimeSpanToHpCOleDateTimeSpan                                */
/*  convert: StdTimeSpan structure to COleDateTimeSpan value                 */
/*****************************************************************************/

STDTIME_RC                  StdTimeSpanToHpCOleDateTimeSpan (
  const STDTIME_SPAN *      /*I*/ pStdTimeSpan,
  COleDateTimeSpan *        /*O*/ pCOleDateTimeSpan)
  {
  STDTIME_ENUM_FUNC (StdTimeSpanToHpCOleDateTimeSpan)

  STDTIME_RET (StdTimeSpanToHpCOleDateTimeSpanEx (
    pStdTimeSpan,
    pCOleDateTimeSpan, NULL, NULL));

  } /* StdTimeSpanToHpCOleDateTimeSpan */


/*-***************************************************************************/
/*            HpCOleDateTimeSpanToStdTimeSpan                                */
/*  convert: COleDateTimeSpan value to StdTimeSpan structure                 */
/*****************************************************************************/

STDTIME_RC                  HpCOleDateTimeSpanToStdTimeSpan (
  const COleDateTimeSpan *  /*I*/ pCOleDateTimeSpan,
  STDTIME_SPAN *            /*O*/ pStdTimeSpan)
  {
  STDTIME_ENUM_FUNC (HpCOleDateTimeSpanToStdTimeSpan)

  STDTIME_RET (HpCOleDateTimeSpanExToStdTimeSpan (
    pCOleDateTimeSpan, 0, 0,
    pStdTimeSpan));

  } /* HpCOleDateTimeSpanToStdTimeSpan */


/*-***************************************************************************/
/*            StdTimeDeltaToHpCOleDateTimeSpan                               */
/*  convert: StdTimeSpan structure to COleDateTimeSpan value                 */
/*****************************************************************************/


STDTIME_RC                  StdTimeDeltaToHpCOleDateTimeSpan (
  const STDTIME_DELTA *     /*I*/ pStdTimeDelta,
  COleDateTimeSpan *        /*O*/ pCOleDateTimeSpan)
  {
  STDTIME_ENUM_FUNC (StdTimeDeltaToHpCOleDateTimeSpan)

  STDTIME_RET (StdTimeDeltaToHpCOleDateTimeSpanEx (
    pStdTimeDelta,
    pCOleDateTimeSpan, NULL, NULL));

  } /* StdTimeDeltaToHpCOleDateTimeSpan */


/*-***************************************************************************/
/*            HpCOleDateTimeSpanToStdTimeDelta                               */
/*  convert: COleDateTimeSpan value to StdTimeDelta structure                */
/*****************************************************************************/


STDTIME_RC                  HpCOleDateTimeSpanToStdTimeDelta (
  const COleDateTimeSpan *  /*I*/ pCOleDateTimeSpan,
  STDTIME_DELTA *           /*O*/ pStdTimeDelta)
  {
  STDTIME_ENUM_FUNC (HpCOleDateTimeSpanToStdTimeDelta)

  STDTIME_RET (HpCOleDateTimeSpanExToStdTimeDelta (
    pCOleDateTimeSpan, 0, 0,
    pStdTimeDelta));

  } /* HpCOleDateTimeSpanToStdTimeDelta */


#endif /* STDTIME_CPP_COLEDATETIME_ENABLED */


/*** HpCComSpanEx functions **************************************************/


#ifdef STDTIME_CPP_CCOMDATE_ENABLED


/*****************************************************************************/
/*                                                                           */
/* CComSpan has an implementation type of double.                            */
/* it has nominal precision in secs, maximum effective precision in msecs,   */
/* but it actually stored in terms of days and fractions of a day.           */
/*                                                                           */
/* operator double() returns the CComSpan double value.                      */
/*                                                                           */
/* operator = (double dblSpanSrc) will assign a CComSpan double value.       */
/*                                                                           */
/* if CComSpan::IsValid() returns false, the object is invalid and cannot    */
/* be converted.                                                             */
/*                                                                           */
/*****************************************************************************/


/*-***************************************************************************/
/*            StdTimeSpanToCComSpanEx                                        */
/*  convert: StdTimeSpan struct to CComSpan value and extra fields           */
/*****************************************************************************/

STDTIME_RC                  StdTimeSpanToCComSpanEx (
  const STDTIME_SPAN *      /*I*/ pStdTimeSpan,
  CComSpan *                /*O*/ pCComSpan,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  double                    nSpan;
  QUADLIB_I64N              qNum;
  int32_t                   nRem;

  STDTIME_ENUM_FUNC (StdTimeSpanToCComSpanEx)

  if ((pStdTimeSpan == NULL) || (pCComSpan == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  qNum = pStdTimeSpan->value / 10000000;            // secs
  nRem = (int32_t) pStdTimeSpan->value % 10000000;  // num of 100-nsec units

  nSpan = ((double) qNum) / (24.0 * 60.0 * 60.0);

  if (pMsec != NULL)
    {
    *pMsec = nRem / 10000;
    }

  if (pUsec != NULL)
    {
    *pUsec = (nRem / 10) % 1000;
    }

  if (pNsec != NULL)
    {
    *pNsec = (nRem % 10) * 100;
    }

  *pCComSpan = nSpan; // operator = double
  STDTIME_RET_OK;

  } /* StdTimeSpanToCComSpanEx */


/*-***************************************************************************/
/*            CComSpanExToStdTimeSpan                                        */
/*  convert: CComSpan value and extra fields to StdTimeSpan struct           */
/*****************************************************************************/

STDTIME_RC                  CComSpanExToStdTimeSpan (
  const CComSpan *          /*I*/ pCComSpan,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_SPAN *            /*O*/ pStdTimeSpan)
  {
  double                    nSpan;

  STDTIME_ENUM_FUNC (CComSpanExToStdTimeSpan)

  if ((pCComSpan == NULL) || (pStdTimeSpan == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  if (pCComSpan->IsValid())
    {
    pStdTimeSpan->value = 0;
    STDTIME_RET_EC (CComSpan_range_is_invalid);
    }

  // invoke operator double()

  nSpan = (double) *pCComSpan;          // returns number of days

  pStdTimeSpan->value =
      ((QUADLIB_I64N) (nSpan * 24.0 * 60.0 * 60.0)) * 10000000
    + (nMsec * 10000)
    + (nUsec * 10)
    + (nNsec / 100);

  STDTIME_RET (ValidStdTimeSpan (pStdTimeSpan));

  } /* CComSpanExToStdTimeSpan */


/*-***************************************************************************/
/*            StdTimeDeltaToCComSpanEx                                       */
/*  convert: StdTimeSpan structure to CComSpan value                         */
/*****************************************************************************/

STDTIME_RC                  StdTimeDeltaToCComSpanEx (
  const STDTIME_DELTA *     /*I*/ pStdTimeDelta,
  CComSpan *                /*O*/ pCComSpan,
  int32_t *                 /*O*/ pMsec,  /* optional */
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME_SPAN              stdTimeSpan;

  STDTIME_ENUM_FUNC (StdTimeDeltaToCComSpanEx)

  if STDTIME_IF (StdTimeDeltaToStdTimeSpan (pStdTimeDelta, &stdTimeSpan))
    {
    STDTIME_RET (StdTimeSpanToCComSpanEx (
       &stdTimeSpan, pCComSpan, pMsec, pUsec, pNsec));
    }

  STDTIME_RET_RC;

  } /* StdTimeDeltaToCComSpanEx */


/*-***************************************************************************/
/*            CComSpanExToStdTimeDelta                                       */
/*  convert: CComSpan value to StdTimeDelta structure                        */
/*****************************************************************************/

STDTIME_RC                  CComSpanExToStdTimeDelta (
  const CComSpan *          /*I*/ pCComSpan,
  int32_t                   /*I*/ nMsec,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_DELTA *           /*O*/ pStdTimeDelta)
  {
  STDTIME_SPAN              stdTimeSpan;

  STDTIME_ENUM_FUNC (CComSpanExToStdTimeDelta)

  if STDTIME_IF (CComSpanExToStdTimeSpan (
       pCComSpan, nMsec, nUsec, nNsec, &stdTimeSpan))
    {
    STDTIME_RET (StdTimeSpanToStdTimeDelta (&stdTimeSpan, pStdTimeDelta));
    }

  STDTIME_RET_RC;

  } /* CComSpanExToStdTimeDelta */


/*** CComSpan functions ******************************************************/


/*-***************************************************************************/
/*            StdTimeSpanToCComSpan                                          */
/*  convert: StdTimeSpan structure to CComSpan value                         */
/*****************************************************************************/

STDTIME_RC                  StdTimeSpanToCComSpan (
  const STDTIME_SPAN *      /*I*/ pStdTimeSpan,
  CComSpan *                /*O*/ pCComSpan)
  {
  STDTIME_ENUM_FUNC (StdTimeSpanToCComSpan)

  STDTIME_RET (StdTimeSpanToCComSpanEx (
    pStdTimeSpan,
    pCComSpan, NULL, NULL, NULL));

  } /* StdTimeSpanToCComSpan */


/*-***************************************************************************/
/*            CComSpanToStdTimeSpan                                          */
/*  convert: CComSpan value to StdTimeSpan structure                         */
/*****************************************************************************/

STDTIME_RC                  CComSpanToStdTimeSpan (
  const CComSpan *          /*I*/ pCComSpan,
  STDTIME_SPAN *            /*O*/ pStdTimeSpan)
  {
  STDTIME_ENUM_FUNC (CComSpanToStdTimeSpan)

  STDTIME_RET (CComSpanExToStdTimeSpan (
    pCComSpan, 0, 0, 0,
    pStdTimeSpan));

  } /* CComSpanToStdTimeSpan */


/*-***************************************************************************/
/*            StdTimeDeltaToCComSpan                                         */
/*  convert: StdTimeSpan structure to CComSpan value                         */
/*****************************************************************************/


STDTIME_RC                  StdTimeDeltaToCComSpan (
  const STDTIME_DELTA *     /*I*/ pStdTimeDelta,
  CComSpan *                /*O*/ pCComSpan)
  {
  STDTIME_ENUM_FUNC (StdTimeDeltaToCComSpan)

  STDTIME_RET (StdTimeDeltaToCComSpanEx (
    pStdTimeDelta,
    pCComSpan, NULL, NULL, NULL));

  } /* StdTimeDeltaToCComSpan */


/*-***************************************************************************/
/*            CComSpanToStdTimeDelta                                         */
/*  convert: CComSpan value to StdTimeDelta structure                        */
/*****************************************************************************/

STDTIME_RC                  CComSpanToStdTimeDelta (
  const CComSpan *          /*I*/ pCComSpan,
  STDTIME_DELTA *           /*O*/ pStdTimeDelta)
  {
  STDTIME_ENUM_FUNC (CComSpanToStdTimeDelta)

  STDTIME_RET (CComSpanExToStdTimeDelta (
    pCComSpan, 0, 0, 0,
    pStdTimeDelta));

  } /* CComSpanToStdTimeDelta */


/*** HpCComSpanEx functions **************************************************/


/*-***************************************************************************/
/*            StdTimeSpanToHpCComSpanEx                                      */
/*  convert: StdTimeSpan struct to CComSpan value and extra fields           */
/*****************************************************************************/

STDTIME_RC                  StdTimeSpanToHpCComSpanEx (
  const STDTIME_SPAN *      /*I*/ pStdTimeSpan,
  CComSpan *                /*O*/ pCComSpan,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  double                    nSpan;
  QUADLIB_I64N              qNum;
  int32_t                   nRem;

  STDTIME_ENUM_FUNC (StdTimeSpanToHpCComSpanEx)

  if ((pStdTimeSpan == NULL) || (pCComSpan == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  qNum = pStdTimeSpan->value / 10000;               // msecs
  nRem = (int32_t) pStdTimeSpan->value % 10000;     // num of 100-nsec units

  nSpan = ((double) qNum) / (24.0 * 60.0 * 60.0 * 1000.0);

  if (pUsec != NULL)
    {
    *pUsec = (nRem / 10) % 1000;
    }

  if (pNsec != NULL)
    {
    *pNsec = (nRem % 10) * 100;
    }

  *pCComSpan = nSpan; // operator = double
  STDTIME_RET_OK;

  } /* StdTimeSpanToHpCComSpanEx */


/*-***************************************************************************/
/*            HpCComSpanExToStdTimeSpan                                      */
/*  convert: CComSpan value and extra fields to StdTimeSpan struct           */
/*****************************************************************************/

STDTIME_RC                  HpCComSpanExToStdTimeSpan (
  const CComSpan *          /*I*/ pCComSpan,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_SPAN *            /*O*/ pStdTimeSpan)
  {
  double                    nSpan;

  STDTIME_ENUM_FUNC (HpCComSpanExToStdTimeSpan)

  if ((pCComSpan == NULL) || (pStdTimeSpan == NULL))
    {
    STDTIME_RET_EC (null_argument);
    }

  if (pCComSpan->IsValid())
    {
    pStdTimeSpan->value = 0;
    STDTIME_RET_EC (CComSpan_range_is_invalid);
    }

  // invoke operator double()

  nSpan = (double) *pCComSpan;          // returns number of days

  pStdTimeSpan->value =
      ((QUADLIB_I64N) (nSpan * 24.0 * 60.0 * 60.0 * 1000.0)) * 10000
    + (nUsec * 10)
    + (nNsec / 100);

  STDTIME_RET (ValidStdTimeSpan (pStdTimeSpan));

  } /* HpCComSpanExToStdTimeSpan */


/*-***************************************************************************/
/*            StdTimeDeltaToHpCComSpanEx                                     */
/*  convert: StdTimeSpan structure to CComSpan value                         */
/*****************************************************************************/

STDTIME_RC                  StdTimeDeltaToHpCComSpanEx (
  const STDTIME_DELTA *     /*I*/ pStdTimeDelta,
  CComSpan *                /*O*/ pCComSpan,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME_SPAN              stdTimeSpan;

  STDTIME_ENUM_FUNC (StdTimeDeltaToHpCComSpanEx)

  if STDTIME_IF (StdTimeDeltaToStdTimeSpan (pStdTimeDelta, &stdTimeSpan))
    {
    STDTIME_RET (StdTimeSpanToHpCComSpanEx (
       &stdTimeSpan, pCComSpan, pUsec, pNsec));
    }

  STDTIME_RET_RC;

  } /* StdTimeDeltaToHpCComSpanEx */


/*-***************************************************************************/
/*            HpCComSpanExToStdTimeDelta                                     */
/*  convert: CComSpan value to StdTimeDelta structure                        */
/*****************************************************************************/

STDTIME_RC                  HpCComSpanExToStdTimeDelta (
  const CComSpan *          /*I*/ pCComSpan,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_DELTA *           /*O*/ pStdTimeDelta)
  {
  STDTIME_SPAN              stdTimeSpan;

  STDTIME_ENUM_FUNC (HpCComSpanExToStdTimeDelta)

  if STDTIME_IF (HpCComSpanExToStdTimeSpan (
       pCComSpan, nUsec, nNsec, &stdTimeSpan))
    {
    STDTIME_RET (StdTimeSpanToStdTimeDelta (&stdTimeSpan, pStdTimeDelta));
    }

  STDTIME_RET_RC;

  } /* HpCComSpanExToStdTimeDelta */


/*** HpCComSpan functions ****************************************************/


/*-***************************************************************************/
/*            StdTimeSpanToHpCComSpan                                        */
/*  convert: StdTimeSpan structure to CComSpan value                         */
/*****************************************************************************/

STDTIME_RC                  StdTimeSpanToHpCComSpan (
  const STDTIME_SPAN *      /*I*/ pStdTimeSpan,
  CComSpan *                /*O*/ pCComSpan)
  {
  STDTIME_ENUM_FUNC (StdTimeSpanToHpCComSpan)

  STDTIME_RET (StdTimeSpanToHpCComSpanEx (
    pStdTimeSpan,
    pCComSpan, NULL, NULL));

  } /* StdTimeSpanToHpCComSpan */


/*-***************************************************************************/
/*            HpCComSpanToStdTimeSpan                                        */
/*  convert: CComSpan value to StdTimeSpan structure                         */
/*****************************************************************************/

STDTIME_RC                  HpCComSpanToStdTimeSpan (
  const CComSpan *          /*I*/ pCComSpan,
  STDTIME_SPAN *            /*O*/ pStdTimeSpan)
  {
  STDTIME_ENUM_FUNC (HpCComSpanToStdTimeSpan)

  STDTIME_RET (HpCComSpanExToStdTimeSpan (
    pCComSpan, 0, 0,
    pStdTimeSpan));

  } /* HpCComSpanToStdTimeSpan */


/*-***************************************************************************/
/*            StdTimeDeltaToHpCComSpan                                       */
/*  convert: StdTimeSpan structure to CComSpan value                         */
/*****************************************************************************/


STDTIME_RC                  StdTimeDeltaToHpCComSpan (
  const STDTIME_DELTA *     /*I*/ pStdTimeDelta,
  CComSpan *                /*O*/ pCComSpan)
  {
  STDTIME_ENUM_FUNC (StdTimeDeltaToHpCComSpan)

  STDTIME_RET (StdTimeDeltaToHpCComSpanEx (
    pStdTimeDelta,
    pCComSpan, NULL, NULL));

  } /* StdTimeDeltaToHpCComSpan */


/*-***************************************************************************/
/*            HpCComSpanToStdTimeDelta                                       */
/*  convert: CComSpan value to StdTimeDelta structure                        */
/*****************************************************************************/


STDTIME_RC                  HpCComSpanToStdTimeDelta (
  const CComSpan *          /*I*/ pCComSpan,
  STDTIME_DELTA *           /*O*/ pStdTimeDelta)
  {
  STDTIME_ENUM_FUNC (HpCComSpanToStdTimeDelta)

  STDTIME_RET (HpCComSpanExToStdTimeDelta (
    pCComSpan, 0, 0,
    pStdTimeDelta));

  } /* HpCComSpanToStdTimeDelta */


#endif /* STDTIME_CPP_CCOMDATE_ENABLED */


/*** END - STDTIME_CPPSVCS.CPP ***********************************************/

