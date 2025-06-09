#include "Stdafx.h"
#include "PEApi.h"

#include "Dbghelp.h"

#pragma comment(lib,"Dbghelp.lib")

BOOL PE_GetDLLFileExports(const CString &strFile, CStringArray &astrExports)
{
	HANDLE hFile;
	HANDLE hFileMapping;
	LPVOID lpFileBase;
	PIMAGE_DOS_HEADER pImg_DOS_Header;
	PIMAGE_NT_HEADERS pImg_NT_Header;
	PIMAGE_EXPORT_DIRECTORY pImg_Export_Dir;

	hFile = CreateFile(strFile, GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if(hFile == INVALID_HANDLE_VALUE)
		return false;

	hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
	if(hFileMapping == 0)
	{
		CloseHandle(hFile);
		return false;
	}

	lpFileBase = MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);
	if(lpFileBase == 0)
	{
		CloseHandle(hFileMapping);
		CloseHandle(hFile);
		return false;
	}

	pImg_DOS_Header = (PIMAGE_DOS_HEADER)lpFileBase;
	//pImg_NT_Header = (PIMAGE_NT_HEADERS)(pImg_DOS_Header->e_lfanew);
	pImg_NT_Header = (PIMAGE_NT_HEADERS)((LONG)pImg_DOS_Header + (LONG)pImg_DOS_Header->e_lfanew);

	if(IsBadReadPtr(pImg_NT_Header, sizeof(IMAGE_NT_HEADERS))
		|| pImg_NT_Header->Signature != IMAGE_NT_SIGNATURE)
	{
		UnmapViewOfFile(lpFileBase);
		CloseHandle(hFileMapping);
		CloseHandle(hFile);
		return false;
	}

	pImg_Export_Dir = (PIMAGE_EXPORT_DIRECTORY)pImg_NT_Header->OptionalHeader
		.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
	if(!pImg_Export_Dir)
	{
		UnmapViewOfFile(lpFileBase);
		CloseHandle(hFileMapping);
		CloseHandle(hFile);
		return false;
	}
	// 63 63 72 75 6E 2E 63 6F 6D
	pImg_Export_Dir= (PIMAGE_EXPORT_DIRECTORY)ImageRvaToVa(pImg_NT_Header,
		pImg_DOS_Header, (DWORD)pImg_Export_Dir, 0);

	DWORD **ppdwNames = (DWORD **)pImg_Export_Dir->AddressOfNames;

	ppdwNames = (PDWORD*)ImageRvaToVa(pImg_NT_Header,
		pImg_DOS_Header, (DWORD)ppdwNames, 0);
	if(!ppdwNames)
	{
		UnmapViewOfFile(lpFileBase);
		CloseHandle(hFileMapping);
		CloseHandle(hFile);
		return false;
	}

	UINT nNoOfExports = pImg_Export_Dir->NumberOfNames;

	for(UINT i=0; i < nNoOfExports; i++ )
	{
		char *szFunc=(PSTR)ImageRvaToVa(pImg_NT_Header, pImg_DOS_Header, (DWORD)ppdwNames[i], 0);
		//CString strFunc( szFunc );
		astrExports.Add(CString(szFunc));
	}

	UnmapViewOfFile(lpFileBase);
	CloseHandle(hFileMapping);
	CloseHandle(hFile);
	return true;
}


