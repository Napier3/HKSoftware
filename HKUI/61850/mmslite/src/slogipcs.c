/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*		2004 - 2007, All Rights Reserved 			*/
/*									*/
/* MODULE NAME : slogipcs.c						*/
/* PRODUCT(S)  : SLOG							*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 01/08/07  EJV    04     slogIpcStop: added lc param.			*/
/* 11/03/05  EJV    02     Added slogIpcEvent.				*/
/* 02/22/05  JRB    02     slogIpc: add SD_CONST to some args.		*/
/* 05/18/04  MDE    01     Initial Release				*/
/************************************************************************/

#include "glbtypes.h"
#include "sysincs.h"
#include "stime.h"
#include "slog.h"
#include "gensock2.h"

/************************************************************************/
/*                              slogIpcInit				*/
/************************************************************************/

ST_RET slogIpcInit (LOG_CTRL *lc)
  {
  return (SD_SUCCESS);
  }

/************************************************************************/
/*                              slogIpcStop				*/
/************************************************************************/

ST_RET slogIpcStop (LOG_CTRL *lc)
  {
  return (SD_SUCCESS);
  }

/************************************************************************/
/*                              slogIpcEvent				*/
/************************************************************************/
ST_RET slogIpcEvent (ST_VOID)
{
  return (SD_SUCCESS);
}

/************************************************************************/
/*                              slogIpc					*/
/************************************************************************/

ST_VOID slogIpc (LOG_CTRL *lc, ST_INT logType,
		 SD_CONST ST_CHAR *SD_CONST logTypeStr, 
		 SD_CONST ST_CHAR *SD_CONST sourceFile,
		 ST_INT lineNum, ST_INT bufLen, 
                 ST_CHAR *buf)
  {
  }

