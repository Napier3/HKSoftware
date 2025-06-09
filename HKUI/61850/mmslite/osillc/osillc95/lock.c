//---------------------------------------------------------------------------
//
// File:         lock.c
//
// Copyright (c) 1998 SISCO, Inc. All rights reserved.
//
// Description:  Ring3 memory management routines.
//
// Author:       A. Shajenko/Stratos Technology, Inc.
//
// History:
// 13-Sep-98     A. Shajenko     Implemented.
//
//---------------------------------------------------------------------------

#include "osillc95.h"

//---------------------------------------------------------------------------
// Function:    OsillcPageLock
//
// Parameters:  DWORD lpBuffer -- pointer to memory buffer
//              DWORD dwSize   -- buffer size in bytes
//
// Returns:     Ring0 linear address pointer to Ring3 memory buffer
//
// Description: Locks a Ring3 memory buffer.
//
// Notes:
//
//---------------------------------------------------------------------------
DWORD OsillcPageLock(DWORD lpBuffer, DWORD dwSize)
{
	DWORD dwLinearPageNumber, dwLinearOffset, dwPages;
	DWORD dwLockedAddress = 0;

	// page offset of memory to map
	dwLinearOffset = lpBuffer & 0x00000FFF;
		
	// generate page number
	dwLinearPageNumber = lpBuffer >> 12;

	// calculate number of pages to map globally
	dwPages = ((lpBuffer + dwSize) >> 12) - dwLinearPageNumber + 1;

	//
	// return global mapping of passed in pointer, as this new pointer
	// is how the memory must be accessed out of context.
	//
	dwLockedAddress = LinPageLock(dwLinearPageNumber, dwPages, PAGEMAPGLOBAL);
	dwLockedAddress += dwLinearOffset;

	return dwLockedAddress;
}

//---------------------------------------------------------------------------
// Function:    OsillcPageUnlock
//
// Parameters:  DWORD lpBuffer -- pointer to memory buffer
//              DWORD dwSize   -- buffer size in bytes
//
// Returns:     Nothing
//
// Description: Unlocks a Ring3 memory buffer.
//
// Notes:
//
//---------------------------------------------------------------------------
VOID OsillcPageUnlock(DWORD lpBuffer, DWORD dwSize)
{
	DWORD dwLinearPageNumber, dwPages;

	// determine page number
	dwLinearPageNumber = lpBuffer >> 12;
	dwPages = ((lpBuffer + dwSize) >> 12) - dwLinearPageNumber + 1;

	// free globally mapped memory
	LinPageUnLock(dwLinearPageNumber, dwPages, PAGEMAPGLOBAL);
}
