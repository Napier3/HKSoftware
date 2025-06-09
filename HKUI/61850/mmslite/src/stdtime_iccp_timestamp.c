/*****************************************************************************/
/* SISCO SOFTWARE MODULE HEADER **********************************************/
/*****************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,            */
/*            2006 All Rights Reserved                                       */
/*                                                                           */
/* MODULE NAME : stdtime_iccp_timestamp.c                                    */
/* PRODUCT(S)  : Standard Time Management Library                            */
/*                                                                           */
/* MODULE DESCRIPTION:                                                       */
/*   Support for ICCP TIMESTAMP (aka "TIMESTAMP_EX")                         */
/*                                                                           */
/* NOTE:                                                                     */
/*   STDTIME refers to a "TIMESTAMP_EX" value as an "ICCP TIMESTAMP", but    */
/*   *without* the "_EX" suffix on the name.  This was done because STDTIME  */
/*   already uses the "Ex" notation to mean "extra fields", and the two      */
/*   uses would have been confusing.  We need to avoid the possibility of a  */
/*   name like "StdTimeToTimeStampExEx" which would have been confusing and  */
/*   hard to understand and document.                                        */
/*                                                                           */
/* NOTE:                                                                     */
/*   A "standard" ICCP "TimeStamp" is a simple 32-bit time_t value.          */
/*                                                                           */
/* MODIFICATION LOG:                                                         */
/*   Date    Who  Rev  Comments                                              */
/* --------  ---  ---  ----------------------------------------------------- */
/* 10/05/06  RLH   01  Created                                               */
/*****************************************************************************/


#include "stdtime.h"
#include "stdtime_iccp_timestamp.h"


/*** IccpTimeStamp initialization function ***********************************/


STDTIME_ICCP_TIMESTAMP      StdTimeApiZeroIccpTimeStamp ()
  {
  STDTIME_ICCP_TIMESTAMP zero = {0};

  return zero;

  } /* StdTimeApiZeroIccpTimeStamp */


/*** IccpTimeStampEx functions ***********************************************/


/*-***************************************************************************/
/*            StdTimeToIccpTimeStampEx                                       */
/*  convert: StdTime struct to TIMESTAMP_EX and extra fields                 */
/*****************************************************************************/

STDTIME_RC                  StdTimeToIccpTimeStampEx (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_ICCP_TIMESTAMP *  /*O*/ pIccpTimeStamp,
  int32_t *                 /*O*/ pUsec,
  int32_t *                 /*O*/ pNsec)
  {
  STDTIME_TIMETYPE          tt;
  int32_t                   msec;

  STDTIME_ENUM_FUNC (StdTimeToIccpTimeStampEx)

  if (pIccpTimeStamp == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pIccpTimeStamp = StdTimeApiZeroIccpTimeStamp();

  if STDTIME_IFNOT (StdTimeToTimeTypeEx (pStdTime, &tt, &msec, pUsec, pNsec))
    {
    STDTIME_RET_RC;
    }

  pIccpTimeStamp->GMTBasedS = (int32_t) tt.t;
  pIccpTimeStamp->Milliseconds = (int16_t) msec;

  STDTIME_RET_OK;

  } /* StdTimeToIccpTimeStampEx */


/*-***************************************************************************/
/*            IccpTimeStampExToStdTime                                       */
/*  convert: TIMESTAMP_EX and extra fields to StdTime struct                 */
/*****************************************************************************/

STDTIME_RC                  IccpTimeStampExToStdTime (
  const STDTIME_ICCP_TIMESTAMP * /*I*/ pIccpTimeStamp,
  int32_t                        /*I*/ nUsec,
  int32_t                        /*I*/ nNsec,
  STDTIME *                      /*O*/ pStdTime)
  {
  STDTIME_TIMETYPE          tt;
  int32_t                   msec;

  STDTIME_ENUM_FUNC (IccpTimeStampExToStdTime)


  if (pStdTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTime = ZeroStdTime ();

  if (pIccpTimeStamp == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTime = ZeroStdTime();

  tt.t = pIccpTimeStamp->GMTBasedS;
  msec = pIccpTimeStamp->Milliseconds;

  if STDTIME_IFNOT (TimeTypeExToStdTime (&tt, msec, nUsec, nNsec, pStdTime))
    {
    STDTIME_RET_RC;
    }

  STDTIME_RET_OK;

  } /* IccpTimeStampExToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToIccpTimeStampEx                                 */
/*  convert: StdTimeFields struct to TIMESTAMP_EX and extra fields           */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToIccpTimeStampEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_ICCP_TIMESTAMP *  /*O*/ pIccpTimeStamp,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME                   stdTime;

  STDTIME_ENUM_FUNC (StdTimeFieldsToIccpTimeStampEx)


  if (pIccpTimeStamp == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pIccpTimeStamp = StdTimeApiZeroIccpTimeStamp();

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeFieldsToStdTime (pStdTimeFields, &stdTime))
    {
    STDTIME_RET (StdTimeToIccpTimeStampEx (
        &stdTime, pIccpTimeStamp, pUsec, pNsec));
    }

  STDTIME_RET_RC;

  } /* StdTimeFieldsToIccpTimeStampEx */


/*-***************************************************************************/
/*            IccpTimeStampExToStdTimeFields                                 */
/*  convert: TIMESTAMP_EX and extra fields to StdTimeFields struct           */
/*****************************************************************************/

STDTIME_RC                  IccpTimeStampExToStdTimeFields (
  const STDTIME_ICCP_TIMESTAMP * /*I*/ pIccpTimeStamp,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME                   stdTime;

  STDTIME_ENUM_FUNC (IccpTimeStampExToStdTimeFields)


  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeFields = ZeroStdTimeFields ();

  if (pIccpTimeStamp == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (IccpTimeStampExToStdTime (
        pIccpTimeStamp, nUsec, nNsec, &stdTime))
    {
    STDTIME_RET (StdTimeToStdTimeFields (&stdTime, pStdTimeFields));
    }

  STDTIME_RET_RC;

  } /* IccpTimeStampExToStdTimeFields */


/*** IccpTimeStamp functions *************************************************/


/*-***************************************************************************/
/*            StdTimeToIccpTimeStamp                                         */
/*  convert: StdTime struct to TIMESTAMP_EX (without extra fields)           */
/*****************************************************************************/

STDTIME_RC                  StdTimeToIccpTimeStamp (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_ICCP_TIMESTAMP *  /*O*/ pIccpTimeStamp)
  {
  STDTIME_ENUM_FUNC (StdTimeToIccpTimeStamp)

  STDTIME_RET (StdTimeToIccpTimeStampEx (pStdTime, pIccpTimeStamp, NULL, NULL));

  } /* StdTimeToIccpTimeStamp */


/*-***************************************************************************/
/*            IccpTimeStampToStdTime                                         */
/*  convert: TIMESTAMP_EX (without extra fields) to StdTime struct           */
/*****************************************************************************/

STDTIME_RC                  IccpTimeStampToStdTime (
  const STDTIME_ICCP_TIMESTAMP * /*I*/ pIccpTimeStamp,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_ENUM_FUNC (IccpTimeStampToStdTime)

  STDTIME_RET (IccpTimeStampExToStdTime (pIccpTimeStamp, 0, 0, pStdTime));

  } /* IccpTimeStampToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToIccpTimeStamp                                   */
/*  convert: StdTimeFields struct to TIMESTAMP_EX (without extra fields)     */
/*****************************************************************************/


STDTIME_RC                  StdTimeFieldsToIccpTimeStamp (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_ICCP_TIMESTAMP *  /*O*/ pIccpTimeStamp)
  {
  STDTIME_ENUM_FUNC (StdTimeFieldsToIccpTimeStamp)

  STDTIME_RET (StdTimeFieldsToIccpTimeStampEx (
    pStdTimeFields, pIccpTimeStamp, NULL, NULL));

  } /* StdTimeFieldsToIccpTimeStamp */


/*-***************************************************************************/
/*            IccpTimeStampToStdTimeFields                                   */
/*  convert: TIMESTAMP_EX (without extra fields) to StdTimeFields struct     */
/*****************************************************************************/

STDTIME_RC                  IccpTimeStampToStdTimeFields (
  const STDTIME_ICCP_TIMESTAMP * /*I*/ pIccpTimeStamp,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_ENUM_FUNC (IccpTimeStampToStdTimeFields)

  STDTIME_RET (IccpTimeStampExToStdTimeFields (pIccpTimeStamp, 0, 0, pStdTimeFields));

  } /* IccpTimeStampToStdTimeFields */

