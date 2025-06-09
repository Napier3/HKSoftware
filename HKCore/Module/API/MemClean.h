#ifndef _MEMCLEAN_API_H__
#define _MEMCLEAN_API_H__

void  mem_AdjustTokenPrivilegesForNT();
BOOL mem_EmptyAllSet();
BOOL mem_EmptySet(HANDLE hProcess);
BOOL mem_EmptySet_CurrApp();

#endif
