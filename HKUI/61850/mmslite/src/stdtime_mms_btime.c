/*****************************************************************************/
/* SISCO SOFTWARE MODULE HEADER **********************************************/
/*****************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,            */
/*            2006 All Rights Reserved                                       */
/*                                                                           */
/* MODULE NAME : stdtime_mms_btime.c                                         */
/* PRODUCT(S)  : Standard Time Management Library                            */
/*                                                                           */
/* MODULE DESCRIPTION:                                                       */
/*   Support for MMS Btime4, BTime6 and BTOD conversions to/from STDTIME     */
/*                                                                           */
/* MODIFICATION LOG:                                                         */
/*   Date    Who  Rev  Comments                                              */
/* --------  ---  ---  ----------------------------------------------------- */
/* 10/05/06  RLH   01  Created                                               */
/*****************************************************************************/


#include "stdtime.h"
#include "stdtime_mms_btime.h"


/*** MmsTimeOfDay4/6/BTOD initialization functions ***************************/


STDTIME_MMS_TIMEOFDAY4      StdTimeApiZeroMmsTimeOfDay4 ()
  {
  STDTIME_MMS_TIMEOFDAY4    zero = {0};

  return zero;

  } /* StdTimeApiZeroMmsTimeOfDay4 */


STDTIME_MMS_TIMEOFDAY6      StdTimeApiZeroMmsTimeOfDay6 ()
  {
  STDTIME_MMS_TIMEOFDAY6    zero = {0};

  return zero;

  } /* StdTimeApiZeroMmsTimeOfDay6 */


STDTIME_MMS_BTOD            StdTimeApiZeroMmsBtod ()
  {
  STDTIME_MMS_BTOD          zero = {0};

  return zero;

  } /* StdTimeApiZeroMmsBtod */


/*** MmsTimeOfDay4Ex functions ***********************************************/


/*-***************************************************************************/
/*            StdTimeToMmsTimeOfDay4Ex                                       */
/*  convert: StdTime struct to MMS_TIMEOFDAY4 and extra fields               */
/*  method:  calculate GMT midnight of current day, and subtract from        */
/*  supplied stdTime to form number of msec since midnight.                  */
/*****************************************************************************/

STDTIME_RC                  StdTimeToMmsTimeOfDay4Ex (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_MMS_TIMEOFDAY4 *  /*O*/ pMmsTimeOfDay4,
  int32_t *                 /*O*/ pUsec,
  int32_t *                 /*O*/ pNsec)
  {
  STDTIME_FIELDS            midnightFields;
  STDTIME                   midnight;
  STDTIME_DELTA             mms;

  STDTIME_ENUM_FUNC (StdTimeToMmsTimeOfDay4Ex)


  if (pMmsTimeOfDay4 == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pMmsTimeOfDay4 = StdTimeApiZeroMmsTimeOfDay4();

  /* form midnight of current day in GMT */

  if STDTIME_IFNOT (GetStdTimeFields (&midnightFields))
    {
    STDTIME_RET_RC;
    }

  midnightFields.hour = 0;
  midnightFields.min  = 0;
  midnightFields.sec  = 0;
  midnightFields.msec = 0;
  midnightFields.usec = 0;
  midnightFields.nsec = 0;

  if STDTIME_IFNOT (StdTimeFieldsToStdTime (&midnightFields, &midnight))
    {
    STDTIME_RET_RC;
    }

  /* form difference between supplied date and midnight */

  if STDTIME_IFNOT (StdTime_GetDelta (pStdTime, &midnight, &mms))
    {
    STDTIME_RET_RC;
    }

#if 0   /* IS THIS AN ERROR OR NOT ? */

  /* delta value 'mms' is the number of days, hours, etc. past midnight */

  if (mms.day < 0)          /* only true if date prior to midnight */
    {
    STDTIME_RET_EC (MMS_year_LT_1984);
    }

#endif

  pMmsTimeOfDay4->ms =
    (mms.day  * 24 * 60 * 60 * 1000) +
    (mms.hour      * 60 * 60 * 1000) +
    (mms.min            * 60 * 1000) +
    (mms.sec                 * 1000) + mms.msec;

  if (pUsec != NULL)
    {
    *pUsec = mms.usec;
    }

  if (pNsec != NULL)
    {
    *pNsec = mms.nsec;
    }

  STDTIME_RET_OK;

  } /* StdTimeToMmsTimeOfDay4Ex */


/*-***************************************************************************/
/*            MmsTimeOfDay4ExToStdTime                                       */
/*  convert: MMS_TIMEOFDAY4 and extra fields to StdTime struct               */
/*  method:  call MmsTimeOfDay4ExToStdTimeFields, then convert to STDTIME    */
/*****************************************************************************/

STDTIME_RC                  MmsTimeOfDay4ExToStdTime (
  const STDTIME_MMS_TIMEOFDAY4 * /*I*/ pMmsTimeOfDay4,
  int32_t                        /*I*/ nUsec,
  int32_t                        /*I*/ nNsec,
  STDTIME *                      /*O*/ pStdTime)
  {
  STDTIME_FIELDS            stdTimeFields = {0};

  STDTIME_ENUM_FUNC (MmsTimeOfDay4ExToStdTime)


  if (pStdTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTime = ZeroStdTime ();

  if (pMmsTimeOfDay4 == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (MmsTimeOfDay4ExToStdTimeFields (
        pMmsTimeOfDay4, nUsec, nNsec, &stdTimeFields))
    {
    STDTIME_RET (StdTimeFieldsToStdTime (&stdTimeFields, pStdTime));
    }

  STDTIME_RET_RC;

  } /* MmsTimeOfDay4ExToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToMmsTimeOfDay4Ex                                 */
/*  convert: StdTimeFields struct to MMS_TIMEOFDAY4 and extra fields         */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToMmsTimeOfDay4Ex (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_MMS_TIMEOFDAY4 *  /*O*/ pMmsTimeOfDay4,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME                   stdTime;

  STDTIME_ENUM_FUNC (StdTimeFieldsToMmsTimeOfDay4Ex)


  if (pMmsTimeOfDay4 == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pMmsTimeOfDay4 = StdTimeApiZeroMmsTimeOfDay4();

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeFieldsToStdTime (pStdTimeFields, &stdTime))
    {
    STDTIME_RET (StdTimeToMmsTimeOfDay4Ex (
        &stdTime, pMmsTimeOfDay4, pUsec, pNsec));
    }

  STDTIME_RET_RC;

  } /* StdTimeFieldsToMmsTimeOfDay4Ex */


/*-***************************************************************************/
/*            MmsTimeOfDay4ExToStdTimeFields                                 */
/*  convert: MMS_TIMEOFDAY4 and extra fields to StdTimeFields struct         */
/*****************************************************************************/

STDTIME_RC                  MmsTimeOfDay4ExToStdTimeFields (
  const STDTIME_MMS_TIMEOFDAY4 * /*I*/ pMmsTimeOfDay4,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_FIELDS            stdTimeFields = {0};

  STDTIME_ENUM_FUNC (MmsTimeOfDay4ExToStdTimeFields)


  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeFields = ZeroStdTimeFields ();

  if (pMmsTimeOfDay4 == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  /* form midnight of current day in GMT, add in msec, and convert */
  /* to STDTIME */

  if STDTIME_IFNOT (GetStdTimeFields (&stdTimeFields))
    {
    STDTIME_RET_RC;
    }

  stdTimeFields.hour = 0;
  stdTimeFields.min  = 0;
  stdTimeFields.sec  = 0;
  stdTimeFields.msec = 0;
  stdTimeFields.usec = 0;
  stdTimeFields.nsec = 0;

  if STDTIME_IFNOT (StdTimeFields_AddFraction (
        &stdTimeFields, pMmsTimeOfDay4->ms, nUsec, nNsec))
    {
    STDTIME_RET_RC;
    }

  *pStdTimeFields = stdTimeFields;

  STDTIME_RET_OK;

  } /* MmsTimeOfDay4ExToStdTimeFields */


/*** MmsTimeOfDay4 functions *************************************************/


/*-***************************************************************************/
/*            StdTimeToMmsTimeOfDay4                                         */
/*  convert: StdTime struct to MMS_TIMEOFDAY4 (without extra fields)         */
/*****************************************************************************/

STDTIME_RC                  StdTimeToMmsTimeOfDay4 (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_MMS_TIMEOFDAY4 *  /*O*/ pMmsTimeOfDay4)
  {
  STDTIME_ENUM_FUNC (StdTimeToMmsTimeOfDay4)

  STDTIME_RET (StdTimeToMmsTimeOfDay4Ex (pStdTime, pMmsTimeOfDay4, NULL, NULL));

  } /* StdTimeToMmsTimeOfDay4 */


/*-***************************************************************************/
/*            MmsTimeOfDay4ToStdTime                                         */
/*  convert: MMS_TIMEOFDAY4 (without extra fields) to StdTime struct         */
/*****************************************************************************/

STDTIME_RC                  MmsTimeOfDay4ToStdTime (
  const STDTIME_MMS_TIMEOFDAY4 * /*I*/ pMmsTimeOfDay4,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_ENUM_FUNC (MmsTimeOfDay4ToStdTime)

  STDTIME_RET (MmsTimeOfDay4ExToStdTime (pMmsTimeOfDay4, 0, 0, pStdTime));

  } /* MmsTimeOfDay4ToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToMmsTimeOfDay4                                   */
/*  convert: StdTimeFields struct to MMS_TIMEOFDAY4 (without extra fields)   */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToMmsTimeOfDay4 (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_MMS_TIMEOFDAY4 *  /*O*/ pMmsTimeOfDay4)
  {
  STDTIME_ENUM_FUNC (StdTimeFieldsToMmsTimeOfDay4)

  STDTIME_RET (StdTimeFieldsToMmsTimeOfDay4Ex (
    pStdTimeFields, pMmsTimeOfDay4, NULL, NULL));

  } /* StdTimeFieldsToMmsTimeOfDay4 */


/*-***************************************************************************/
/*            MmsTimeOfDay4ToStdTimeFields                                   */
/*  convert: MMS_TIMEOFDAY4 (without extra fields) to StdTimeFields struct   */
/*****************************************************************************/

STDTIME_RC                  MmsTimeOfDay4ToStdTimeFields (
  const STDTIME_MMS_TIMEOFDAY4 * /*I*/ pMmsTimeOfDay4,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_ENUM_FUNC (MmsTimeOfDay4ToStdTimeFields)

  STDTIME_RET (MmsTimeOfDay4ExToStdTimeFields (
      pMmsTimeOfDay4, 0, 0, pStdTimeFields));

  } /* MmsTimeOfDay4ToStdTimeFields */


/*** MmsTimeOfDay6Ex functions ***********************************************/


/*-***************************************************************************/
/*            StdTimeToMmsTimeOfDay6Ex                                       */
/*  convert: StdTime struct to MMS_TIMEOFDAY6 and extra fields               */
/*  method:  subtract 1984-01-01 from stdTime to form delta                  */
/*****************************************************************************/

STDTIME_RC                  StdTimeToMmsTimeOfDay6Ex (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_MMS_TIMEOFDAY6 *  /*O*/ pMmsTimeOfDay6,
  int32_t *                 /*O*/ pUsec,
  int32_t *                 /*O*/ pNsec)
  {
  /* pre-calculated STDTIME value of 1984-01-01 00:00:00.0000000 */
  STDTIME                   t84 = STDTIME_INIT (56280925, 1868185600);

  STDTIME_DELTA             mms;

  STDTIME_ENUM_FUNC (StdTimeToMmsTimeOfDay6Ex)

  if (pMmsTimeOfDay6 == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pMmsTimeOfDay6 = StdTimeApiZeroMmsTimeOfDay6();

  /* form difference between supplied date and 1984 */

  if STDTIME_IFNOT (StdTime_GetDelta (pStdTime, &t84, &mms))
    {
    STDTIME_RET_RC;
    }

#if 0   /* IS THIS AN ERROR OR NOT ? */

  /* delta value 'mms' is the number of days, hours, etc. past 1984-01-01 */

  if (mms.day < 0)          /* only true if date prior to 1984-01-01 */
    {
    STDTIME_RET_EC (MMS_year_LT_1984);
    }

#endif

  pMmsTimeOfDay6->day = mms.day;

  pMmsTimeOfDay6->ms =
    (mms.hour * 60 * 60 * 1000) +
    (mms.min       * 60 * 1000) +
    (mms.sec            * 1000) + mms.msec;

  if (pUsec != NULL)
    {
    *pUsec = mms.usec;
    }

  if (pNsec != NULL)
    {
    *pNsec = mms.nsec;
    }

  STDTIME_RET_OK;

  } /* StdTimeToMmsTimeOfDay6Ex */


/*-***************************************************************************/
/*            MmsTimeOfDay6ExToStdTime                                       */
/*  convert: MMS_TIMEOFDAY6 and extra fields to StdTime struct               */
/*  method:  add MMS days and msec to base value of 1984-01-01               */
/*****************************************************************************/

STDTIME_RC                  MmsTimeOfDay6ExToStdTime (
  const STDTIME_MMS_TIMEOFDAY6 * /*I*/ pMmsTimeOfDay6,
  int32_t                        /*I*/ nUsec,
  int32_t                        /*I*/ nNsec,
  STDTIME *                      /*O*/ pStdTime)
  {
  /* pre-calculated STDTIME value of 1984-01-01 00:00:00.0000000 */
  STDTIME                   t84 = STDTIME_INIT (56280925, 1868185600);
  STDTIME_DELTA             mms = {0};

  STDTIME_ENUM_FUNC (MmsTimeOfDay6ExToStdTime)


  if (pStdTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTime = ZeroStdTime ();

  if (pMmsTimeOfDay6 == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTime = ZeroStdTime();

  /* create delta from 1984-01-01 */

  mms.day  = pMmsTimeOfDay6->day;
  mms.msec = pMmsTimeOfDay6->ms;
  mms.usec = nUsec;
  mms.nsec = nNsec;

  /* add mms displacement to mms epoch date of Jan 1 1984 */

  if STDTIME_IFNOT (StdTime_AddDelta (&t84, &mms))
    {
    STDTIME_RET_RC;
    }

  *pStdTime = t84;

  STDTIME_RET_OK;

  } /* MmsTimeOfDay6ExToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToMmsTimeOfDay6Ex                                 */
/*  convert: StdTimeFields struct to MMS_TIMEOFDAY6 and extra fields         */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToMmsTimeOfDay6Ex (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_MMS_TIMEOFDAY6 *  /*O*/ pMmsTimeOfDay6,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME                   stdTime;

  STDTIME_ENUM_FUNC (StdTimeFieldsToMmsTimeOfDay6Ex)


  if (pMmsTimeOfDay6 == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pMmsTimeOfDay6 = StdTimeApiZeroMmsTimeOfDay6();

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeFieldsToStdTime (pStdTimeFields, &stdTime))
    {
    STDTIME_RET (StdTimeToMmsTimeOfDay6Ex (
        &stdTime, pMmsTimeOfDay6, pUsec, pNsec));
    }

  STDTIME_RET_RC;

  } /* StdTimeFieldsToMmsTimeOfDay6Ex */


/*-***************************************************************************/
/*            MmsTimeOfDay6ExToStdTimeFields                                 */
/*  convert: MMS_TIMEOFDAY6 and extra fields to StdTimeFields struct         */
/*****************************************************************************/

STDTIME_RC                  MmsTimeOfDay6ExToStdTimeFields (
  const STDTIME_MMS_TIMEOFDAY6 * /*I*/ pMmsTimeOfDay6,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME                   stdTime;

  STDTIME_ENUM_FUNC (MmsTimeOfDay6ExToStdTimeFields)


  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeFields = ZeroStdTimeFields ();

  if (pMmsTimeOfDay6 == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (MmsTimeOfDay6ExToStdTime (
        pMmsTimeOfDay6, nUsec, nNsec, &stdTime))
    {
    STDTIME_RET (StdTimeToStdTimeFields (&stdTime, pStdTimeFields));
    }

  STDTIME_RET_RC;

  } /* MmsTimeOfDay6ExToStdTimeFields */


/*** MmsTimeOfDay6 functions *************************************************/


/*-***************************************************************************/
/*            StdTimeToMmsTimeOfDay6                                         */
/*  convert: StdTime struct to MMS_TIMEOFDAY6 (without extra fields)         */
/*****************************************************************************/

STDTIME_RC                  StdTimeToMmsTimeOfDay6 (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_MMS_TIMEOFDAY6 *  /*O*/ pMmsTimeOfDay6)
  {
  STDTIME_ENUM_FUNC (StdTimeToMmsTimeOfDay6)

  STDTIME_RET (StdTimeToMmsTimeOfDay6Ex (pStdTime, pMmsTimeOfDay6, NULL, NULL));

  } /* StdTimeToMmsTimeOfDay6 */


/*-***************************************************************************/
/*            MmsTimeOfDay6ToStdTime                                         */
/*  convert: MMS_TIMEOFDAY6 (without extra fields) to StdTime struct         */
/*****************************************************************************/

STDTIME_RC                  MmsTimeOfDay6ToStdTime (
  const STDTIME_MMS_TIMEOFDAY6 * /*I*/ pMmsTimeOfDay6,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_ENUM_FUNC (MmsTimeOfDay6ToStdTime)

  STDTIME_RET (MmsTimeOfDay6ExToStdTime (pMmsTimeOfDay6, 0, 0, pStdTime));

  } /* MmsTimeOfDay6ToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToMmsTimeOfDay6                                   */
/*  convert: StdTimeFields struct to MMS_TIMEOFDAY6 (without extra fields)   */
/*****************************************************************************/


STDTIME_RC                  StdTimeFieldsToMmsTimeOfDay6 (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_MMS_TIMEOFDAY6 *  /*O*/ pMmsTimeOfDay6)
  {
  STDTIME_ENUM_FUNC (StdTimeFieldsToMmsTimeOfDay6)

  STDTIME_RET (StdTimeFieldsToMmsTimeOfDay6Ex (
    pStdTimeFields, pMmsTimeOfDay6, NULL, NULL));

  } /* StdTimeFieldsToMmsTimeOfDay6 */


/*-***************************************************************************/
/*            MmsTimeOfDay6ToStdTimeFields                                   */
/*  convert: MMS_TIMEOFDAY6 (without extra fields) to StdTimeFields struct   */
/*****************************************************************************/

STDTIME_RC                  MmsTimeOfDay6ToStdTimeFields (
  const STDTIME_MMS_TIMEOFDAY6 * /*I*/ pMmsTimeOfDay6,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_ENUM_FUNC (MmsTimeOfDay6ToStdTimeFields)

  STDTIME_RET (MmsTimeOfDay6ExToStdTimeFields (pMmsTimeOfDay6, 0, 0, pStdTimeFields));

  } /* MmsTimeOfDay6ToStdTimeFields */


/*** MmsBtodEx functions *****************************************************/


/*-***************************************************************************/
/*            StdTimeToMmsBtodEx                                             */
/*  convert: StdTime struct to MMS_BTOD and extra fields                     */
/*  note: form MMS_BTOD6 is forced for this conversion                       */
/*****************************************************************************/

STDTIME_RC                  StdTimeToMmsBtodEx (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_MMS_BTOD *        /*O*/ pMmsBtod,
  int32_t *                 /*O*/ pUsec,
  int32_t *                 /*O*/ pNsec)
  {
  STDTIME_MMS_TIMEOFDAY6    mmsTimeOfDay6;

  STDTIME_ENUM_FUNC (StdTimeToMmsBtodEx)

  if (pMmsBtod == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pMmsBtod = StdTimeApiZeroMmsBtod();

  if STDTIME_IF (StdTimeToMmsTimeOfDay6Ex (
      pStdTime, &mmsTimeOfDay6, pUsec, pNsec))
    {
    pMmsBtod->form = STDTIME_MMS_BTOD6;
    pMmsBtod->ms  = mmsTimeOfDay6.ms;
    pMmsBtod->day = mmsTimeOfDay6.day;
    STDTIME_RET_OK;
    }

  STDTIME_RET_RC;

  } /* StdTimeToMmsBtodEx */


/*-***************************************************************************/
/*            MmsBtodExToStdTime                                             */
/*  convert: MMS_BTOD and extra fields to StdTime struct                     */
/*****************************************************************************/

STDTIME_RC                  MmsBtodExToStdTime (
  const STDTIME_MMS_BTOD * /*I*/ pMmsBtod,
  int32_t                  /*I*/ nUsec,
  int32_t                  /*I*/ nNsec,
  STDTIME *                /*O*/ pStdTime)
  {
  STDTIME_MMS_TIMEOFDAY4    mmsTimeOfDay4;
  STDTIME_MMS_TIMEOFDAY6    mmsTimeOfDay6;

  STDTIME_ENUM_FUNC (MmsBtodExToStdTime)


  if (pStdTime == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTime = ZeroStdTime ();

  if (pMmsBtod == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if (pMmsBtod->form == STDTIME_MMS_BTOD4)
    {
    mmsTimeOfDay4.ms = pMmsBtod->ms;

    STDTIME_RET (MmsTimeOfDay4ExToStdTime (
        &mmsTimeOfDay4, nUsec, nNsec, pStdTime));
    }

  if (pMmsBtod->form == STDTIME_MMS_BTOD6)
    {
    mmsTimeOfDay6.ms  = pMmsBtod->ms;
    mmsTimeOfDay6.day = pMmsBtod->day;

    STDTIME_RET (MmsTimeOfDay6ExToStdTime (
        &mmsTimeOfDay6, nUsec, nNsec, pStdTime));
    }

  STDTIME_RET_EC (BTOD_form_code_not_4_or_6);

  } /* MmsBtodExToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToMmsBtodEx                                       */
/*  convert: StdTimeFields struct to MMS_BTOD and extra fields               */
/*****************************************************************************/

STDTIME_RC                  StdTimeFieldsToMmsBtodEx (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_MMS_BTOD *        /*O*/ pMmsBtod,
  int32_t *                 /*O*/ pUsec,  /* optional */
  int32_t *                 /*O*/ pNsec)  /* optional */
  {
  STDTIME                   stdTime;

  STDTIME_ENUM_FUNC (StdTimeFieldsToMmsBtodEx)


  if (pMmsBtod == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pMmsBtod = StdTimeApiZeroMmsBtod();

  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (StdTimeFieldsToStdTime (pStdTimeFields, &stdTime))
    {
    STDTIME_RET (StdTimeToMmsBtodEx (
        &stdTime, pMmsBtod, pUsec, pNsec));
    }

  STDTIME_RET_RC;

  } /* StdTimeFieldsToMmsBtodEx */


/*-***************************************************************************/
/*            MmsBtodExToStdTimeFields                                       */
/*  convert: MMS_BTOD and extra fields to StdTimeFields struct               */
/*****************************************************************************/

STDTIME_RC                  MmsBtodExToStdTimeFields (
  const STDTIME_MMS_BTOD *  /*I*/ pMmsBtod,
  int32_t                   /*I*/ nUsec,
  int32_t                   /*I*/ nNsec,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME                   stdTime;

  STDTIME_ENUM_FUNC (MmsBtodExToStdTimeFields)


  if (pStdTimeFields == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  *pStdTimeFields = ZeroStdTimeFields ();

  if (pMmsBtod == NULL)
    {
    STDTIME_RET_EC (null_argument);
    }

  if STDTIME_IF (MmsBtodExToStdTime (
        pMmsBtod, nUsec, nNsec, &stdTime))
    {
    STDTIME_RET (StdTimeToStdTimeFields (&stdTime, pStdTimeFields));
    }

  STDTIME_RET_RC;

  } /* MmsBtodExToStdTimeFields */


/*** MmsBtod functions *******************************************************/


/*-***************************************************************************/
/*            StdTimeToMmsBtod                                               */
/*  convert: StdTime struct to MMS_BTOD (without extra fields)               */
/*****************************************************************************/

STDTIME_RC                  StdTimeToMmsBtod (
  const STDTIME *           /*I*/ pStdTime,
  STDTIME_MMS_BTOD *        /*O*/ pMmsBtod)
  {
  STDTIME_ENUM_FUNC (StdTimeToMmsBtod)

  STDTIME_RET (StdTimeToMmsBtodEx (pStdTime, pMmsBtod, NULL, NULL));

  } /* StdTimeToMmsBtod */


/*-***************************************************************************/
/*            MmsBtodToStdTime                                               */
/*  convert: MMS_BTOD (without extra fields) to StdTime struct               */
/*****************************************************************************/

STDTIME_RC                  MmsBtodToStdTime (
  const STDTIME_MMS_BTOD *  /*I*/ pMmsBtod,
  STDTIME *                 /*O*/ pStdTime)
  {
  STDTIME_ENUM_FUNC (MmsBtodToStdTime)

  STDTIME_RET (MmsBtodExToStdTime (pMmsBtod, 0, 0, pStdTime));

  } /* MmsBtodToStdTime */


/*-***************************************************************************/
/*            StdTimeFieldsToMmsBtod                                         */
/*  convert: StdTimeFields struct to MMS_BTOD (without extra fields)         */
/*****************************************************************************/


STDTIME_RC                  StdTimeFieldsToMmsBtod (
  const STDTIME_FIELDS *    /*I*/ pStdTimeFields,
  STDTIME_MMS_BTOD *        /*O*/ pMmsBtod)
  {
  STDTIME_ENUM_FUNC (StdTimeFieldsToMmsBtod)

  STDTIME_RET (StdTimeFieldsToMmsBtodEx (
    pStdTimeFields, pMmsBtod, NULL, NULL));

  } /* StdTimeFieldsToMmsBtod */


/*-***************************************************************************/
/*            MmsBtodToStdTimeFields                                         */
/*  convert: MMS_BTOD (without extra fields) to StdTimeFields struct         */
/*****************************************************************************/

STDTIME_RC                  MmsBtodToStdTimeFields (
  const STDTIME_MMS_BTOD *  /*I*/ pMmsBtod,
  STDTIME_FIELDS *          /*O*/ pStdTimeFields)
  {
  STDTIME_ENUM_FUNC (MmsBtodToStdTimeFields)

  STDTIME_RET (MmsBtodExToStdTimeFields (pMmsBtod, 0, 0, pStdTimeFields));

  } /* MmsBtodToStdTimeFields */


