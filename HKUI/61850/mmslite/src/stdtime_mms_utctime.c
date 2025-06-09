/*****************************************************************************/
/* SISCO SOFTWARE MODULE HEADER **********************************************/
/*****************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,            */
/*            2006 All Rights Reserved                                       */
/*                                                                           */
/* MODULE NAME : stdtime_mms_utctime.c                                       */
/* PRODUCT(S)  : Standard Time Management Library                            */
/*                                                                           */
/* MODULE DESCRIPTION:                                                       */
/*   Support for MMS UTC TIME conversions to/from STDTIME                    */
/*                                                                           */
/* MODIFICATION LOG:                                                         */
/*   Date    Who  Rev  Comments                                              */
/* --------  ---  ---  ----------------------------------------------------- */
/* 10/05/06  RLH   01  Created                                               */
/*****************************************************************************/


#include "stdtime.h"
#include "stdtime_mms_utctime.h"


/*** MmsUtcTime initialization function **************************************/


STDTIME_MMS_UTC_TIME        StdTimeApiZeroMmsUtcTime ()
  {
  STDTIME_MMS_UTC_TIME      zero = {0};

  return zero;

  } /* StdTimeApiZeroMmsUtcTime */


/*** MmsUtcTime functions ****************************************************/


/*-***************************************************************************/
/*            StdTimeToMmsUtcTime                                            */
/*  convert: StdTime structure to MMS_UTC_TIME                               */
/*  method:  convert to TIMETYPE, then calculate binary fraction of second   */
/*****************************************************************************/

STDTIME_RC                  StdTimeToMmsUtcTime (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_MMS_UTC_TIME *    /*O*/ pMmsUtcTime)
  {
  STDTIME_TIMETYPE          tt;
  STDTIME_WIN_FILETIME      ft;
  QUADLIB_I64               qFrac;
  QUADLIB_I64               qRem;
  QUADLIB_I64               q10_7;
  QUADLIB_I64               q2_24;

  STDTIME_ENUM_FUNC (StdTimeToMmsUtcTime)


  if (pMmsUtcTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pMmsUtcTime = StdTimeApiZeroMmsUtcTime();

  if STDTIME_IFNOT (StdTimeToTimeType (pStdTime, &tt))
    {
    STDTIME_RET_RC;
    }

  /* get STDTIME into I64 format */

  if STDTIME_IFNOT (StdTimeToFileTime (pStdTime, &ft))
    {
    STDTIME_RET_RC;
    }

  FILETIME_TO_QUADLIB_I64 (&ft, &qFrac);

  /* obtain number of 100-ns intervals */

  QUADLIB_I64_HI(q10_7) = 0;
  QUADLIB_I64_LO(q10_7) = 10000000;

  QUADLIB_I64_HI(q2_24) = 0;
  QUADLIB_I64_LO(q2_24) = 0x1000000;

  QUADLIB_I64_MOD_EQ (qFrac, q10_7);

  /* multiply by range of UTC fraction */

  QUADLIB_I64_MUL_EQ (qFrac, q2_24);

  /* divide out number of 100-ns intervals */
  /* as 100-ns intervals approaches 10_7, frac approaches 2_24 */

  qFrac = QuadLibI64DivMod (qFrac, q10_7, &qRem);

  /* assign UTC values to output argument */

  pMmsUtcTime->secs = (int32_t) tt.t;
  pMmsUtcTime->fraction = (int32_t) QUADLIB_I64_LO(qFrac);

  if (QUADLIB_I64_LO(qRem) >= (0x1000000 / 2))
    {
    pMmsUtcTime->fraction++;    /* ROUND UP */
    }

  pMmsUtcTime->qflags = 0;      /* IS THIS CORRECT ? */

  STDTIME_RET_OK;

  } /* StdTimeToMmsUtcTime */


/*-***************************************************************************/
/*            MmsUtcTimeToStdTime                                            */
/*  convert: MMS_UTC_TIME to StdTime structure                               */
/*  method:  treat secs values as time_t, convert TIMETYPE to STDTIME, and   */
/*  add in fractional seconds after converting to STDTIME_SPAN.              */
/*****************************************************************************/

STDTIME_RC                  MmsUtcTimeToStdTime (
  const STDTIME_MMS_UTC_TIME * /*I*/ pMmsUtcTime,
  STDTIME *                      /*O*/ pStdTime)
  {
  STDTIME                   stdTime;
  STDTIME_SPAN              stdTimeSpan;
  STDTIME_TIMETYPE          tt;
  QUADLIB_I64               qFrac;
  QUADLIB_I64               qRem;
  QUADLIB_I64               q10_7;
  QUADLIB_I64               q2_24;


  STDTIME_ENUM_FUNC (MmsUtcTimeToStdTime)

  if (pStdTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTime = ZeroStdTime ();

  if (pMmsUtcTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  tt.t = pMmsUtcTime->secs;

  if STDTIME_IFNOT (TimeTypeToStdTime (&tt, &stdTime))
    {
    STDTIME_RET_RC;
    }


  /* obtain number of binary fractional units */

  QUADLIB_I64_HI(q10_7) = 0;
  QUADLIB_I64_LO(q10_7) = 10000000;

  QUADLIB_I64_HI(q2_24) = 0;
  QUADLIB_I64_LO(q2_24) = 0x1000000;

  QUADLIB_I64_HI(qFrac) = 0;
  QUADLIB_I64_LO(qFrac) = pMmsUtcTime->fraction;


  /* multiply by range of 100-ns intervals */

  QUADLIB_I64_MUL_EQ (qFrac, q10_7);

  /* divide out number of binary fractional units */
  /* as fractional units approach 2_24, frac approaches 10_7 */

  qFrac = QuadLibI64DivMod (qFrac, q2_24, &qRem);

  if (QUADLIB_I64_LO(qRem) >= (10000000 / 2))
    {
    QUADLIB_I64_LO(qFrac)++;    /* ROUND UP */
    }

  /* create a STDTIME_SPAN to add in fractional value to STDTIME */

  stdTimeSpan = StdTimeSpan (qFrac);

  if STDTIME_IF (StdTime_AddSpan (&stdTime, &stdTimeSpan))
    {
    *pStdTime = stdTime;
    STDTIME_RET_OK;
    }

  STDTIME_RET_RC;

  } /* MmsUtcTimeToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToMmsUtcTime                                      */
/*  convert: StdTimeFields structure to MMS_UTC_TIME                         */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToMmsUtcTime (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_MMS_UTC_TIME *    /*O*/ pMmsUtcTime)
  {
  STDTIME                   stdTime;

  STDTIME_ENUM_FUNC (StdTimeFieldsToMmsUtcTime)


  if (pMmsUtcTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pMmsUtcTime = StdTimeApiZeroMmsUtcTime();

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeFieldsToStdTime (pStdTimeFields, &stdTime))
    {
    STDTIME_RET (StdTimeToMmsUtcTime (&stdTime, pMmsUtcTime));
    }

  STDTIME_RET_RC;

  } /* StdTimeFieldsToMmsUtcTime */


/*-***************************************************************************/
/*            MmsUtcTimeToStdTimeFields                                      */
/*  convert: MMS_UTC_TIME to StdTimeFields structure                         */
/*****************************************************************************/

STDTIME_RC                  MmsUtcTimeToStdTimeFields (
  const STDTIME_MMS_UTC_TIME * /*I*/ pMmsUtcTime,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME                   stdTime;

  STDTIME_ENUM_FUNC (MmsUtcTimeToStdTimeFields)

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeFields = ZeroStdTimeFields ();

  if (pMmsUtcTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (MmsUtcTimeToStdTime (pMmsUtcTime, &stdTime))
    {
    STDTIME_RET (StdTimeToStdTimeFields (&stdTime, pStdTimeFields));
    }

  STDTIME_RET_RC;

  } /* MmsUtcTimeToStdTimeFields */


