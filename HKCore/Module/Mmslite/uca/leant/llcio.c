/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*		1994, All Rights Reserved				*/
/*									*/
/* MODULE NAME : llcio.c						*/
/* PRODUCT(S)  : OSI LLC NDIS Driver					*/
/* This module contains LLC Driver User Access functions		*/
/* Contains OS specific code sections.					*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 03/03/97  EJV    08     Added void for arg in _GetPSP () and		*/
/*			   redefinitions for MS Compiler v6.00.		*/
/* 12/26/96  MDE    07     Changes to LLcWrite, to avoid poss. lockup 	*/
/* 07/17/96  EJV    06     Added string.h				*/
/* 06/27/96  EJV    05     Added code for MSDOS (plain DOS)		*/
/* 10/14/94  DSF    04     Added retry code				*/
/* 08/29/94  DSF    03     Added DOS/16M support			*/
/* 08/05/94  DSF    02     renamed LLCIoctl () LlcIoctl ()		*/
/* 02/04/94  DSF    01     Initial Release				*/
/*									*/
/************************************************************************/

#ifdef _WINDOWS
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <io.h>
#include <fcntl.h>
#include <string.h>

#include "llcio.h"

#ifdef _DOS16M
#include "dos16.h"
#define _REGS		REGS
#define _SREGS		SREGS
#define _int86		int86
#define _int86x		int86x
#define FALSE		0
#define TRUE		1
#endif

#ifdef _WINDOWS
static DWORD _WriteConfirmSegSel;
#endif

#ifdef MSDOS
  /* plain DOS */
  /* when compiling with MS Compiler v6.00 */
#if defined(_MSC_VER) && (_MSC_VER <= 600)
#define _REGS		REGS
#define _SREGS		SREGS
#define _int86		int86
#define _int86x		int86x
#define FALSE		0
#define TRUE		1
#define _O_RDWR		O_RDWR
#define _O_BINARY	O_BINARY
#define _open		open
#define _close		close
#define _write		write
#define _read 		read 
#define _FP_SEG		FP_SEG
#define _FP_OFF		FP_OFF
#endif

static char 	fWriteConfirm;		/* write confirm flag */
#endif

static char *_pfPMWriteConfirm;


int _SetRawMode (int fd);
int _ResetEOF (int fd);
int _GetPSP (void);

/***********************************************************************
**			LlcOpen
***********************************************************************/

int LlcOpen (char *Name)
  {
int fd;
#ifdef _WINDOWS
static DWORD LlcSetWriteConfirmFlagSegSel;
#endif
#ifdef _DOS16M
short memStrat;
#endif
#ifdef MSDOS
LLCSETWRITECONFIRMFLAG	sLlcSetWriteConfirmFlag;
#endif
char *pfRMWriteConfirm;
LLCSETWRITECONFIRMFLAG *pPMLlcSetWriteConfirmFlag;
LLCSETWRITECONFIRMFLAG *pRMLlcSetWriteConfirmFlag;

  fd = _open (Name, _O_RDWR | _O_BINARY);
  if (fd == -1)
    return (-1);

  _SetRawMode (fd);		/* Re-configure Driver to suit our needs */

#ifdef _WINDOWS
  LlcSetWriteConfirmFlagSegSel = GlobalDosAlloc (sizeof (LLCSETWRITECONFIRMFLAG));
  pPMLlcSetWriteConfirmFlag = (LLCSETWRITECONFIRMFLAG *) 
          ((LlcSetWriteConfirmFlagSegSel & 0x0000FFFFL) << 16);
  pRMLlcSetWriteConfirmFlag = (LLCSETWRITECONFIRMFLAG *) 
          (LlcSetWriteConfirmFlagSegSel & 0xFFFF0000L);

  _WriteConfirmSegSel = GlobalDosAlloc (sizeof (char));
  _pfPMWriteConfirm = (char *) ((_WriteConfirmSegSel & 0x0000FFFFL) << 16);
  pfRMWriteConfirm = (char *) (_WriteConfirmSegSel & 0xFFFF0000L);
#endif

#ifdef _DOS16M
  memStrat = d16SetMemStrat (MForceLow);
  pPMLlcSetWriteConfirmFlag = (LLCSETWRITECONFIRMFLAG *) 
          d16AllocMem (sizeof (LLCSETWRITECONFIRMFLAG));
  pRMLlcSetWriteConfirmFlag = (LLCSETWRITECONFIRMFLAG *) 
          d16GetRealAddress (pPMLlcSetWriteConfirmFlag);

  _pfPMWriteConfirm = d16AllocMem (sizeof (char));
  pfRMWriteConfirm = d16GetRealAddress (_pfPMWriteConfirm);
  d16SetMemStrat (memStrat);
#endif

#ifdef MSDOS
  /* plain DOS, point to the static variable */
  _pfPMWriteConfirm = &fWriteConfirm;
   pfRMWriteConfirm = &fWriteConfirm;
  pPMLlcSetWriteConfirmFlag = &sLlcSetWriteConfirmFlag; /* on stack */
#endif

  pPMLlcSetWriteConfirmFlag->Opcode = LLC_SET_WRITE_CONFIRM_FLAG;
  pPMLlcSetWriteConfirmFlag->pfWriteConfirm = pfRMWriteConfirm;
  LlcIoctl (fd, pPMLlcSetWriteConfirmFlag, sizeof (*pPMLlcSetWriteConfirmFlag));

#ifdef _WINDOWS
  GlobalDosFree ((unsigned) LlcSetWriteConfirmFlagSegSel);
#endif
#ifdef _DOS16M
  d16FreeMem (pPMLlcSetWriteConfirmFlag);
#endif

  return (fd);
  }



/***********************************************************************
**			LlcClose
***********************************************************************/

int LlcClose (int fd)
  {

#ifdef _WINDOWS
  GlobalDosFree ((unsigned) _WriteConfirmSegSel);
#endif
#ifdef _DOS16M
  d16FreeMem (_pfPMWriteConfirm);
#endif

  return (_close (fd));
  }



/***********************************************************************
**			LlcWrite
***********************************************************************/

int LlcWrite (int fd, char *buffer, int size)
  {
int rc;
register i = 0;
register j;

/* We will try to write the PDU up to 100 times, if necessary		*/
  do 
    {
    *_pfPMWriteConfirm = 0;
    rc = _write (fd, buffer, size);

    if (rc > 0)		/* If the write was successful ... 		*/
      {			/* wait for the confirm, with an escape		*/
      j = 0;
      while (!*_pfPMWriteConfirm && ++j < 3000)
        _GetPSP ();

      if (j >= 3000)	/* If the confirm was not received, let's quit	*/
        {
        rc = -1;	/* Return an error code				*/
        break;		/* No more writes.				*/
        }
      }
    i++;
    }
  while (rc <= 0 && i < 100);

  return (rc);
  }


/***********************************************************************
**			LlcRead
***********************************************************************/

int LlcRead (int fd, char *buffer, int size)
  {
int rc;

  rc = _read (fd, buffer, size);
  if (rc == 0)
    {
    if (((unsigned long) buffer & 0x000f) == 0)		/* paragraph boundary */
      _ResetEOF (fd);
    }

  return (rc);
  }


/***********************************************************************
**			LlcIoctl
***********************************************************************/

int LlcIoctl (int fd, void *pArg, int size)
  {
union   _REGS    regs;
struct  _SREGS   segregs;

  memset ((char *) &regs, '\0', sizeof (regs));
  memset ((char *) &segregs, '\0', sizeof (segregs));
  regs.h.ah = 0x44;
  regs.h.al = 0x02;
  regs.x.bx = fd;
  regs.x.cx = size;

  segregs.ds = _FP_SEG (pArg);
  regs.x.dx = _FP_OFF (pArg);

  _int86x(0x21, &regs, &regs, &segregs);

  if (regs.x.cflag)
    return(-1);

  return(0);
  }




/***********************************************************************
**			_SetRawMode
***********************************************************************/


int _SetRawMode (int fd)
  {
union   _REGS    regs;

  memset ((char *) &regs, '\0', sizeof (regs));
  regs.h.ah = 0x44;
  regs.h.al = 0x00;
  regs.x.bx = fd;
  regs.x.cx = 0;

  _int86(0x21, &regs, &regs);

  if (regs.x.cflag)
    return(-1);

  regs.h.ah = 0x44;
  regs.h.al = 0x01;
  regs.x.bx = fd;
  regs.x.cx = 0;
  regs.h.dl |= 0x0020;
  regs.h.dh = 0x00;

  _int86(0x21, &regs, &regs);
  return(0);
  }


/***********************************************************************
**			_ResetEOF
***********************************************************************/


int _ResetEOF (int fd)
  {
union   _REGS    regs;

  memset ((char *) &regs, '\0', sizeof (regs));
  regs.h.ah = 0x44;
  regs.h.al = 0x00;
  regs.x.bx = fd;
  regs.x.cx = 0;

  _int86(0x21, &regs, &regs);

  if (regs.x.cflag)
    return(-1);

  regs.h.ah = 0x44;
  regs.h.al = 0x01;
  regs.x.bx = fd;
  regs.x.cx = 0;
  regs.h.dl |= 0x0040;
  regs.h.dh = 0x00;

  _int86(0x21, &regs, &regs);
  return(0);
  }


/***********************************************************************
**			_GetPSP
***********************************************************************/

int _GetPSP (void)
  {
union _REGS registers;

  /*
  ** Get the Program Segment Prefix.
  */
  registers.h.ah = 0x51;
  _int86(0x21, &registers, &registers);
  return (registers.x.bx);
  }
