/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*              1986-2001 All Rights Reserved                   	*/
/*									*/
/* MODULE NAME : memchk.cpp						*/
/* PRODUCT(S)  : MMSEASE						*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/*	This module contains enhanced memory allocation functions	*/
/*	for performing various integrity checks				*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 06/19/02  DSF    04     Allow for 0-byte allocations (valid for new)	*/
/* 09/06/01  EJV    03     Replaced non-existing anymore xxx_wipe funcs.*/
/* 05/17/01  EJV    02     Added usage NOTE from Dmitry.		*/
/* 01/25/01  DSF    01     Initial Release				*/
/************************************************************************/

#if defined (DEBUG_SISCO) && defined (DEBUG_NEW_SISCO)


/*----------------------------------------------------------------------*/
/* NOTE: memchk.cpp and DEBUG_NEW_SISCO are used together to detect	*/
/*       memory leaks caused by the new/delete calls (hence, the name	*/
/*       for the macro DEBUG_NEW_SISCO - Microsoft is already using	*/
/*       DEBUG_NEW for MFC). If you add this file to you project and	*/
/*       define the macro, you MUST (and I do mean MUST) recompile all	*/
/*       of the libraries contaning C++ modules with the same macro.	*/
/*       For instance, if you are working with daftest, and you want to	*/
/*       monitor C++ memory allocation, you would add memchk.cpp to the	*/
/*       daftest project and also add the DEBUG_NEW_SISCO macro. Then	*/
/*       you would have to add the macro to the UibAPI project and the	*/
/*       UIBED project and recompile those projects as well.		*/
/*----------------------------------------------------------------------*/


#include "glbtypes.h"
#include <iostream>

#define MEM_CHK
#include "mem_chk.h"

#ifdef DEBUG_SISCO
SD_CONST static ST_CHAR *SD_CONST thisFileName = __FILE__;
#endif


/************************************************************************/
/*			standard new					*/
/************************************************************************/

void * operator new(size_t nSize) throw (std::bad_alloc)
  {
  
  m_mem_debug = 1;

  if (nSize == 0)
    nSize = 1;
    
  void *p = chk_malloc (nSize);

  if (p == NULL)
    {
    std::bad_alloc ba;
    throw (ba);
    }
    
  return p;
  }
  
/************************************************************************/
/*			nothrow new					*/
/************************************************************************/

void * operator new(size_t nSize, const std::nothrow_t&) throw ()
  {
  
  m_mem_debug = 1;
  
  if (nSize == 0)
    nSize = 1;
    
  return chk_malloc (nSize);
  }
  
/************************************************************************/
/*			placement new					*/
/************************************************************************/

void * operator new(size_t nSize, const char *fileName, const int lineNum) throw (std::bad_alloc)
  {
  
  m_mem_debug = 1;
  
  if (nSize == 0)
    nSize = 1;
    
  void *p = x_chk_malloc (nSize, (ST_CHAR *) fileName, lineNum);

  if (p == NULL)
    {
    std::bad_alloc ba;
    throw (ba);
    }
    
  return p;
  }

/************************************************************************/
/*			standard array new				*/
/************************************************************************/

void * operator new[](size_t nSize) throw (std::bad_alloc)
  {
  
  m_mem_debug = 1;
  
  if (nSize == 0)
    nSize = 1;
    
  void *p = chk_malloc (nSize);

  if (p == NULL)
    {
    std::bad_alloc ba;
    throw (ba);
    }
    
  return p;
  }
  
/************************************************************************/
/*			nothrow array new 				*/
/************************************************************************/

void * operator new[](size_t nSize, const std::nothrow_t&) throw ()
  {
  
  m_mem_debug = 1;
  
  if (nSize == 0)
    nSize = 1;
    
  return chk_malloc (nSize);
  }
  
/************************************************************************/
/*			placement array new 				*/
/************************************************************************/

void * operator new[](size_t nSize, const char *fileName, const int lineNum) throw (std::bad_alloc)
  {
  
  m_mem_debug = 1;
  
  if (nSize == 0)
    nSize = 1;
    
  void *p = x_chk_malloc (nSize, (ST_CHAR *) fileName, lineNum);

  if (p == NULL)
    {
    std::bad_alloc ba;
    throw (ba);
    }
    
  return p;
  }

/************************************************************************/
/*			standard delete 				*/
/************************************************************************/

void operator delete(void *p) throw ()
  {
  
  if (p == NULL)
    return;
  chk_free (p);
  }
  
/************************************************************************/
/*			placement delete 				*/
/************************************************************************/

void operator delete(void *p, const char *fileName, const int lineNum) throw ()
  {
  
  if (p == NULL)
    return;
    
  x_chk_free (p, (ST_CHAR *) fileName, lineNum);
  }


/************************************************************************/
/*			standard array delete 				*/
/************************************************************************/

void operator delete[](void *p) throw ()
  {
  
  if (p == NULL)
    return;
    
  chk_free (p);
  }
  
/************************************************************************/
/*			placement array delete 				*/
/************************************************************************/

void operator delete[](void *p, const char *fileName, const int lineNum) throw ()
  {
  
  if (p == NULL)
    return;
    
  x_chk_free (p, (ST_CHAR *) fileName, lineNum);
  }

#endif
