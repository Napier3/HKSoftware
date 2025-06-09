/*
 *  time.c
 */

#include "gsp_hal_time.h"
#include <time.h>
#include <windows.h>

uint64_t
GSP_Hal_getTimeInMs()
{
	FILETIME ft;
	uint64_t now;

	static const uint64_t DIFF_TO_UNIXTIME = 11644473600000LL;

	GetSystemTimeAsFileTime(&ft);

	now = (LONGLONG)ft.dwLowDateTime + ((LONGLONG)(ft.dwHighDateTime) << 32LL);

	return (now / 10000LL) - DIFF_TO_UNIXTIME;
}
