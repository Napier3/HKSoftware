// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MMSAPI_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MMSAPI_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#pragma once

#include "MmsApi.h"

#define RECORD_FILE_POSTFIX_CFG    _T("cfg")
#define RECORD_FILE_POSTFIX_DAT    _T("dat")
#define RECORD_FILE_POSTFIX_HDR    _T("hdr")
#define RECORD_FILE_POSTFIX_DES    _T("des")
#define RECORD_FILE_POSTFIX_MID    _T("mid")

#define RECORD_FILE_POSTFIX_CFG_UPPER    _T("CFG")
#define RECORD_FILE_POSTFIX_DAT_UPPER     _T("DAT")
#define RECORD_FILE_POSTFIX_HDR_UPPER     _T("HDR")
#define RECORD_FILE_POSTFIX_DES_UPPER     _T("DES")
#define RECORD_FILE_POSTFIX_MID_UPPER     _T("MID")

bool mms_get_last_record_file(ACSI_NODE *pDevice, CString &strFileName);
bool mms_get_last_record_file(long nDvIndex, CString &strFileName);
