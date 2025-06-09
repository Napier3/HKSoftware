// PpDeviceModelEditInterface.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SentinelLDKInterface.h"
#include "..\XLanguage\XLanguageResource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#pragma comment(lib,"hasp_windows_100161.lib")

unsigned char vendor_code[] =
"UP15KFm1GV0XcCmadJkzdqm1dtfTmLkEp+11CbFrKOn/aPLfVGPJhMjc8y2xZeqp8NPz9na2lS3DMrGO"
"O+D7pjfi7UUr9uKAyMSi3oHPlXWWdPELcxtkeqlvxtqmPeB9acU6EecAfL/Pd35g0YrJDqwKtIuW0KcZ"
"9lIk+4VjOizsVd4+jAksM1kJvtMLZx4j6J08KYUaf7AvReXWdlw3GUuhiIL2fx/P++snh/OuDmczbANR"
"t0BXN7bKPYtH+H6KwNIjnAM0lGnPYK7no5u9xVQ3G0F5aVoy54+occVLeEFiQ/wfCsgK4UvqSjlxBN8m"
"mPamuJi6YU3A6kR7aoQjd0d0Pzris/vTKmKxf5DQSn/upOC550oADwXa8YanPdjYCqPdgDTMwkkrfyEt"
"UUoJPV2e+AUsdEmE4WHORhNx2g2A4IdHkyciepA03FwgU6rzo6hbHcMPJLKDYe/XcIVHQPCFqTyQBwKK"
"EXiuXKisKYzmlvaMK6c/bX18WlLTSdOm2XuF8k4kMn0egY/+agF+zeSsNjKg5478FmuZ9wXHDecgMx9W"
"uhRI6CM0lA2gGjszUgJzAS7mEzWE+KcLxbxoufXXXQhjeQKvMqk4p/5BnZ9waGNBeHGVKGE1DvTe3AZ+"
"izh0oT8CWKrb3mmfqf4E1ETg7UBIVaskBfRQJFMxnEy85u2cXvGfgJH37xBc7fiZHRiHOEL70xidMoi2"
"8KMr2QS0SNea1/rFvCIbnCl2CyVxdhVmXxUjwSmwfJtBruNACovp1ULSFM11f5JwLKbKO7SX+1uZ9y/g"
"yZhe2FmbFFi3RJJP3LLlIEgZaHGFGleZRtytpBTusDSOT1MDXswgModXHOJVblg05PygeQI8AHHxA2FZ"
"gv3NlUxkVavv96is1WauP3CFKbJRh1tLl8GO781WBTuz3V1G7BfpPn9paTg=";

unsigned char g_psz_def_develop[MAX_PATH];
unsigned char g_psz_def_ownership[MAX_PATH];
unsigned char g_psz_def_infor[MAX_PATH];
unsigned char g_psz_title_ownership[MAX_PATH];
unsigned char g_psz_title_develop[MAX_PATH];
unsigned char g_psz_title_user_cop[MAX_PATH];

class _CDevAndOwnNameInit
{
public:
	_CDevAndOwnNameInit()
	{
		unsigned char *pTemp = g_psz_def_ownership;
		*(pTemp++) = 0XB1;		*(pTemp++) = 0XB1;
		*(pTemp++) = 0XBE;		*(pTemp++) = 0XA9;
		*(pTemp++) = 0XB2;		*(pTemp++) = 0XA9;
		*(pTemp++) = 0XB5;		*(pTemp++) = 0XE7;
		*(pTemp++) = 0XD0;		*(pTemp++) = 0XC2;
		*(pTemp++) = 0XC1;		*(pTemp++) = 0XA6;
		*(pTemp++) = 0XB5;		*(pTemp++) = 0XE7;
		*(pTemp++) = 0XC6;		*(pTemp++) = 0XF8;
		*(pTemp++) = 0XB9;		*(pTemp++) = 0XC9;
		*(pTemp++) = 0XB7;		*(pTemp++) = 0XDD;
		*(pTemp++) = 0XD3;		*(pTemp++) = 0XD0;
		*(pTemp++) = 0XCF;		*(pTemp++) = 0XDE;
		*(pTemp++) = 0XB9;		*(pTemp++) = 0XAB;
		*(pTemp++) = 0XCB;		*(pTemp++) = 0XBE;
		*(pTemp++) = 0;

		pTemp = g_psz_def_develop;
		*(pTemp++) = 0XC4;		*(pTemp++) = 0XCF;
		*(pTemp++) = 0XBE;		*(pTemp++) = 0XA9;
		*(pTemp++) = 0XC4;		*(pTemp++) = 0XDC;
		*(pTemp++) = 0XD4;		*(pTemp++) = 0XC6;
		*(pTemp++) = 0XB5;		*(pTemp++) = 0XE7;
		*(pTemp++) = 0XC1;		*(pTemp++) = 0XA6;
		*(pTemp++) = 0XBF;		*(pTemp++) = 0XC6;
		*(pTemp++) = 0XBC;		*(pTemp++) = 0XBC;
		*(pTemp++) = 0XD3;		*(pTemp++) = 0XD0;
		*(pTemp++) = 0XCF;		*(pTemp++) = 0XDE;
		*(pTemp++) = 0XB9;		*(pTemp++) = 0XAB;
		*(pTemp++) = 0XCB;		*(pTemp++) = 0XBE;
		*(pTemp++) = 0;

		pTemp = g_psz_def_infor;
		*(pTemp++) = 0XC4;		*(pTemp++) = 0XE3;
		*(pTemp++) = 0XCA;		*(pTemp++) = 0XB9;
		*(pTemp++) = 0XD3;		*(pTemp++) = 0XC3;
		*(pTemp++) = 0XB5;		*(pTemp++) = 0XC4;
		*(pTemp++) = 0XCF;		*(pTemp++) = 0XB5;
		*(pTemp++) = 0XCD;		*(pTemp++) = 0XB3;
		*(pTemp++) = 0XC3;		*(pTemp++) = 0XBB;
		*(pTemp++) = 0XD3;		*(pTemp++) = 0XD0;
		*(pTemp++) = 0XCA;		*(pTemp++) = 0XDA;
		*(pTemp++) = 0XC8;		*(pTemp++) = 0XA8;
 		*(pTemp++) = '!';
// 		*(pTemp++) = 0XC7;		*(pTemp++) = 0XEB;
// 		*(pTemp++) = 0XC1;		*(pTemp++) = 0XAA;
// 		*(pTemp++) = 0XCF;		*(pTemp++) = 0XB5;
// 		*(pTemp++) = ':';
		*(pTemp++) = 0X0;

		pTemp = g_psz_title_ownership;
		*(pTemp++) = 0XB0;		*(pTemp++) = 0XE6;
		*(pTemp++) = 0XC8;		*(pTemp++) = 0XA8;
		*(pTemp++) = 0XCB;		*(pTemp++) = 0XF9;
		*(pTemp++) = 0XD3;		*(pTemp++) = 0XD0;
		*(pTemp++) = 0X0;		*(pTemp++) = 0X0;
		*(pTemp++) = 0X0;		*(pTemp++) = 0X0;

		pTemp = g_psz_title_develop;
		*(pTemp++) = 0XBF;		*(pTemp++) = 0XAA;
		*(pTemp++) = 0XB7;		*(pTemp++) = 0XA2;
		*(pTemp++) = 0X00;		*(pTemp++) = 0X00;
		*(pTemp++) = 0X0;		*(pTemp++) = 0X0;

		pTemp = g_psz_title_user_cop;
		*(pTemp++) = 0XD3;		*(pTemp++) = 0XC3;
		*(pTemp++) = 0XBB;		*(pTemp++) = 0XA7;
		*(pTemp++) = 0XB5;		*(pTemp++) = 0XA5;
		*(pTemp++) = 0XCE;		*(pTemp++) = 0XBB;
		*(pTemp++) = 0X0;		*(pTemp++) = 0X0;
	}

	virtual ~_CDevAndOwnNameInit(){}
};

_CDevAndOwnNameInit g_oCDevAndOwnNameInit;

CString hasp_get_login_error()
{
	CString strMsg;
	strMsg = g_sLangTxt_NotAuthorized;//g_psz_def_infor;
	//strMsg += (char*)g_psz_def_ownership;

	return strMsg;
}

void hasp_view_login_error()
{
	CString strMsg = hasp_get_login_error();
	CLogPrint::LogString(XLOGLEVEL_TRACE, strMsg);
}

BOOL hasp_check_status(hasp_status_t status, BOOL bShowMsg=TRUE)
{
	if (!bShowMsg)
	{
		return (status == HASP_STATUS_OK);
	}

	/* check if operation was successful */
	if (status != HASP_STATUS_OK)
	{
		switch (status)
		{
		case HASP_FEATURE_NOT_FOUND:
			break;
		case HASP_HASP_NOT_FOUND:
			CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_USBKey/*_T("请插入授权加密狗！")*/);
			break;
		case HASP_OLD_DRIVER:
			CLogPrint::LogString(XLOGLEVEL_TRACE,g_sLangTxt_USBKeyUpdate /*_T("授权加密狗驱动程序版本过低，请更新驱动程序！")*/);
			break;
		case HASP_NO_DRIVER:
			CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_NoUSBkey/*_T("没有安装授权加密狗驱动程序，请安装驱动程序！")*/);
			break;
		case HASP_INV_VCODE:
			CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_SystemError/*_T("系统错误！")*/);
			break;
		case HASP_FEATURE_TYPE_NOT_IMPL:
			CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_SystemError/*_T("系统错误！")*/);
			break;
		case HASP_TMOF:
			CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_SystemError/*_T("系统错误！")*/);
			break;
		case HASP_TS_DETECTED:
			CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_SystemError/*_T("系统错误！")*/);
			break;
		case HASP_INV_HND:
			CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_SystemError2/*_T("系统错误：HASP_INV_HND：Invalid login handle passed to function")*/);
			break;
		case HASP_INV_FILEID:
			CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_SystemError3/*_T("系统错误：HASP_INV_FILEID：Specified File ID not recognized by API")*/);
			break;
		case HASP_MEM_RANGE:
			CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_SystemError4/*_T("系统错误：HASP_MEM_RANGE：Request exceeds memory range of a Sentinel file")*/);
			break;

		default:
			CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_SystemError/*_T("系统错误！")*/);
			break;
		}

		return FALSE;
	}

	return TRUE;
}
// 
// BOOL hasp_has_catalog(UINT nFetureID)
// {
// 	const hasp_feature_t feature = 7;
// 
// 	hasp_handle_t handle = HASP_INVALID_HANDLE_VALUE;
// 	hasp_status_t status;
// 
// 	status = hasp_login(feature, vendor_code, &handle);
// 
// 	return hasp_check_status(status);
// }
// 
// void hasp_get_develop(CString &strDevelop)
// {
// 	strDevelop = CSafenet_hasp::hasp_get_develop();
// }
// 
// void hasp_get_ownership(CString &strOwnership)
// {
// 	strOwnership = CSafenet_hasp::hasp_get_ownership();
// }
// 
// void hasp_get_user_cop(CString &strUserCop)
// {
// 	strUserCop = CSafenet_hasp::hasp_get_user_cop();
// }
// 
// void hasp_get_user_name(CString &strUserName)
// {
// 	strUserName = CSafenet_hasp::hasp_get_user_name();
// }
// 
// void hasp_get_user_psw(CString &strUserPsw)
// {
// 	strUserPsw = CSafenet_hasp::hasp_get_user_psw();
// }
// 
// CString hasp_get_develop(BOOL bHasTitle)
// {
// 	return CSafenet_hasp::hasp_get_develop(bHasTitle);
// }
// 
// CString hasp_get_ownership(BOOL bHasTitle)
// {
// 	return CSafenet_hasp::hasp_get_ownership(bHasTitle);
// }
// 
// CString hasp_get_user_cop(BOOL bHasTitle)
// {
// 	return CSafenet_hasp::hasp_get_user_cop(bHasTitle);
// }
// 
// CString hasp_get_user_name(BOOL bHasTitle)
// {
// 	return CSafenet_hasp::hasp_get_user_name(bHasTitle);
// }
// 
// CString hasp_get_user_psw()
// {
// 	return CSafenet_hasp::hasp_get_user_psw();
// }
// 
// void hasp_ViewEntitlementInfor(UINT nFetureID)
// {
// 	CString strMsg;
// 	hasp_get_ownership(strMsg);
// 	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("版权所有：%s"), strMsg);
// 
// 	hasp_get_develop(strMsg);
// 	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("系统开发：%s"), strMsg);
// 
// 	hasp_get_user_cop(strMsg);
// 	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s：%s"), CString(g_psz_title_user_cop), strMsg);
// 
// 	hasp_get_user_name(strMsg);
// 	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("使用用户：%s"), strMsg);
// }
// 


//////////////////////////////////////////////////////////////////////////
//CSafenet_hasp

long CSafenet_hasp::g_nSafenetHaspRef = 0;
CSafenet_hasp *CSafenet_hasp::g_pSafenetHasp = NULL;
hasp_handle_t CSafenet_hasp::g_hasp_handle = HASP_INVALID_HANDLE_VALUE;
BOOL CSafenet_hasp::g_hasp_oa_server_mode = FALSE;

CSafenet_hasp::CSafenet_hasp(UINT nFetureID)
{
	g_nFetureID = nFetureID;

// 	//登录功能ID
// 	login_catalog();
// 
// 	//如果失败，则返回
// 	if (g_hasp_handle == HASP_INVALID_HANDLE_VALUE)
// 	{
// 		return;
// 	}
// 
// 	hasp_read_infor();
	g_hasp_oa_server_mode = FALSE;
}

void CSafenet_hasp::init_hasp_login()
{
	//登录功能ID
	login_catalog();

	//如果失败，则返回
	if (g_hasp_handle == HASP_INVALID_HANDLE_VALUE)
	{
		return;
	}

	hasp_read_infor();
}


void CSafenet_hasp::hasp_read_infor()
{
	ASSERT (g_pSafenetHasp != NULL);
	hasp_status_t status;
	hasp_size_t memSize;

	status = hasp_get_size(g_hasp_handle, HASP_FILEID_RW, &memSize);

	if (!hasp_check_status(status))
	{
		return;
	}

	unsigned char data[401];

	status = hasp_read(g_hasp_handle, HASP_FILEID_RW, 0, 400, data);

	/* check if operation was successful */
	if (!hasp_check_status(status))
	{
		return;
	}

	g_pSafenetHasp->read_infor((char*)data);
	g_pSafenetHasp->read_safenet_infor();
	g_pSafenetHasp->time_hasp_to_system();
}

long CSafenet_hasp::hasp_infor_get_id(char **ppszBegin, char *pszKey)
{
	char pszID[32];
	long nValue = 0;
	pszID[0] = 0;
	char *pPos = *ppszBegin;
	pPos = hasp_infor_get_id_str(pPos, pszKey, pszID);
	*ppszBegin = pPos;

	if (pPos != NULL)
	{
		nValue = atol(pszID);
	}

	return nValue;
}

char* CSafenet_hasp::hasp_infor_get_id_str(char *pszBegin, char *pszKey, char *pszID)
{
	*pszID = 0;
	char *pTemp = pszBegin;
	long nValue = -1;
	char *pValue = NULL;

	pTemp = strstr(pTemp, pszKey);

	if (pTemp == NULL)
	{
		return NULL;
	}

	while (*pTemp != 0)
	{
		if (*pTemp == '\"')
		{
			if (pValue == NULL)
			{
				pValue = pTemp + 1;
			}
			else
			{
				long nLen = pTemp - pValue;
				memcpy(pszID, pValue, nLen);
				pszID[nLen] = 0;
				pValue = pTemp + 1;
				break;
			}
		}

		pTemp++;
	}

	return pValue;
}

void CSafenet_hasp::read_safenet_infor()
{
	char *info = 0;
	hasp_status_t status;

	const char* scope = 
		"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"
		"<haspscope/>";
	const char* format = 
		"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"
		"<haspformat root=\"hasp_info\">"
		"    <hasp>"
		"        <attribute name=\"id\" />"
		"        <attribute name=\"type\" />"
		"        <feature>"
		"            <attribute name=\"id\" />"
		"        </feature>"
		"    </hasp>"
		"</haspformat>";

	status = hasp_get_info(scope, format, vendor_code, &info);

	/* check if operation was successful */
	if (status != HASP_STATUS_OK)
	{
		switch (status)
		{
		case HASP_INV_FORMAT:
			break;
		default:
			break;
		}
	}

	char *pPos = info;
	//<hasp id="2087229556" type="HASP-HL">
	char pszID[32];
	pszID[0] = 0;
	CString strID;
	CSafenetAuthority *pAuthority = NULL;

	pPos = hasp_infor_get_id_str(pPos, "hasp ", pszID);
	CSafenetAuthoritys *pHaspInfo = CSafenetAuthoritysMngr::GetAuthoritys_HaspInfo();
	pHaspInfo->ClearAuthority();

	if(pPos != NULL)
	{
		m_strSafenet_SN = pszID;
	}
	if (pPos != NULL && pHaspInfo != NULL)
	{
		while (pPos != NULL)
		{
			pPos = hasp_infor_get_id_str(pPos, "feature ", pszID);

			if (pPos == NULL)
			{
				break;
			}

			strID = pszID;
			pAuthority = (CSafenetAuthority *)pHaspInfo->FindByID(strID);

			if (pAuthority != NULL)
			{
				pAuthority->m_nEnable = 1;
			}
		}
	}

	hasp_free(info);
}

BOOL CSafenet_hasp::hasp_get_curr_time(hasp_time_t *time)
{
	hasp_status_t status;
	status = hasp_get_rtc(g_hasp_handle,time);

	if (!hasp_check_status(status))
	{
		*time = 0;
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}


void CSafenet_hasp::time_hasp_to_system(hasp_time_t &time, SYSTEMTIME &tmSys)
{
	unsigned int day=0,month=0,year=0,hour=0,minute=0,second=0;
	hasp_hasptime_to_datetime(time, &day, &month, &year, &hour, &minute, &second);
	tmSys.wYear = year;
	tmSys.wMonth = month;
	tmSys.wDay = day;
	tmSys.wHour = hour;
	tmSys.wMinute = minute;
	tmSys.wSecond = second;
}

void CSafenet_hasp::time_system_to_hasp(SYSTEMTIME &tmSys, hasp_time_t &time)
{
	unsigned int day=0,month=0,year=0,hour=0,minute=0,second=0;
	year = tmSys.wYear;
	month = tmSys.wMonth;
	day = tmSys.wDay;
	hour = tmSys.wHour;
	minute = tmSys.wMinute;
	second = tmSys.wSecond;
	hasp_datetime_to_hasptime(day, month, year, hour, minute, second, &time);
}

void CSafenet_hasp::time_hasp_to_system()
{
	if (is_tm_authority_FF())
	{
		return;
	}

	time_hasp_to_system(m_tmAuthority, m_tmLimit);
}

void CSafenet_hasp::time_system_to_hasp()
{
	if (m_tmLimit.wYear == 0 && m_tmLimit.wMonth == 0 && m_tmLimit.wDay == 0)
	{
		set_tm_authority_FF();
	}
	else
	{
		time_system_to_hasp(m_tmLimit, m_tmAuthority);
	}
}

CSafenet_hasp::~CSafenet_hasp()
{
	if (HASP_INVALID_HANDLE_VALUE != g_hasp_handle)
	{
		hasp_status_t status = hasp_logout(g_hasp_handle);
		g_hasp_handle = HASP_INVALID_HANDLE_VALUE;
		hasp_check_status(status);	
	}
}

CSafenet_hasp* CSafenet_hasp::Create(UINT nFetureID)
{

	g_nSafenetHaspRef++;
	
	if (g_nSafenetHaspRef == 1)
	{
		g_pSafenetHasp = new CSafenet_hasp(nFetureID);
		g_pSafenetHasp->init_hasp_login();
	}
	else
	{
		g_pSafenetHasp->g_nFetureID = nFetureID;
	}

	return g_pSafenetHasp;
}

void CSafenet_hasp::Release()
{
	if (g_nSafenetHaspRef == 0)
	{
		return;
	}

	g_nSafenetHaspRef--;

	if (g_nSafenetHaspRef == 0)
	{
		delete g_pSafenetHasp;
		g_pSafenetHasp = NULL;
	}
}

BOOL CSafenet_hasp::login_catalog()
{
	hasp_status_t status;

	status = hasp_login(g_nFetureID, vendor_code, &g_hasp_handle);

	if (status != HASP_STATUS_OK)
	{
		hasp_view_login_error();
	}

	return hasp_check_status(status);
};

BOOL CSafenet_hasp::hasp_has_catalog()
{
	ASSERT (g_pSafenetHasp != NULL);

	if (g_pSafenetHasp == NULL)
	{
		return FALSE;
	}

	if (g_pSafenetHasp->g_hasp_oa_server_mode)
	{//lijq 2020-03-04  OA_Server_Mode
		if (g_pSafenetHasp->g_nFetureID == 107
			|| g_pSafenetHasp->g_nFetureID == 108)
		{
			return FALSE;
		}

		return TRUE;
	}

	if (g_hasp_handle == HASP_INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	hasp_status_t status;
	hasp_handle_t handle;

	status = hasp_login(g_pSafenetHasp->g_nFetureID, vendor_code, &handle);

	if (status == HASP_STATUS_OK)
	{
		hasp_logout(handle);
	}

	return hasp_check_status(status);
}

BOOL CSafenet_hasp::hasp_has_catalog(UINT nFetureID, BOOL bShowHaspMsg)
{
// 	ASSERT (g_pSafenetHasp != NULL);
// 
// 	if (g_hasp_handle == HASP_INVALID_HANDLE_VALUE)
// 	{
// 		hasp_view_login_error();
// 		return FALSE;
// 	}

	if (g_hasp_oa_server_mode)
	{//lijq 2020-03-04  OA_Server_Mode
		if (nFetureID == 107
			|| nFetureID == 108)
		{
			return FALSE;
		}

		return TRUE;
	}

	hasp_status_t status;
	hasp_handle_t handle;

	status = hasp_login(nFetureID, vendor_code, &handle);

	if (status == HASP_STATUS_OK)
	{
		hasp_logout(handle);
	}
	else
	{
		hasp_view_login_error();
	}

	return hasp_check_status(status, bShowHaspMsg);
}

CString CSafenet_hasp::hasp_get_develop(BOOL bHasTitle)
{
	ASSERT (g_pSafenetHasp != NULL);
	CString strText;

	return g_pSafenetHasp->get_develop(bHasTitle);
}

CString CSafenet_hasp::hasp_get_ownership(BOOL bHasTitle)
{
	ASSERT (g_pSafenetHasp != NULL);
	return g_pSafenetHasp->get_ownership(bHasTitle);
}

CString CSafenet_hasp::hasp_get_user_cop(BOOL bHasTitle)
{
	ASSERT (g_pSafenetHasp != NULL);
	return g_pSafenetHasp->get_user_cop(bHasTitle);
}

CString CSafenet_hasp::hasp_get_user_name(BOOL bHasTitle)
{
	ASSERT (g_pSafenetHasp != NULL);
	return g_pSafenetHasp->get_user_name(bHasTitle);
}

CString CSafenet_hasp::hasp_get_user_psw()
{
	ASSERT (g_pSafenetHasp != NULL);

	return g_pSafenetHasp->get_user_psw();
}

CString CSafenet_hasp::hasp_get_sys_name()
{
	ASSERT (g_pSafenetHasp != NULL);

	CString strSysName = g_pSafenetHasp->get_sys_name();

	if (hasp_has_time_authority())
	{
		strSysName += _T("[试用版]");
	}

	return strSysName;
}

CString CSafenet_hasp::hasp_get_user_cop_sn()
{
	ASSERT (g_pSafenetHasp != NULL);

	return g_pSafenetHasp->get_user_cop_sn();
}

CString CSafenet_hasp::hasp_get_safenet_sn()
{
	ASSERT (g_pSafenetHasp != NULL);

	return g_pSafenetHasp->m_strSafenet_SN;
}

CString CSafenet_hasp::hasp_get_test()
{
	ASSERT (g_pSafenetHasp != NULL);
	long nIndex = 0;
	CString strTest;

	for (nIndex=0; nIndex<SAFENET_AUTHORITY_BUF_LEN; nIndex++)
	{
		if (g_pSafenetHasp->m_byteAuthority[nIndex] != 0)
		{
			strTest.AppendFormat(_T("%d$"), g_pSafenetHasp->m_byteAuthority[nIndex]);
		}
	}

	return strTest;
}

CString CSafenet_hasp::hasp_get_test_apps()
{
	ASSERT (g_pSafenetHasp != NULL);

	return g_pSafenetHasp->g_str_test_apps;
}

CString CSafenet_hasp::hasp_get_test_macros()
{
	ASSERT (g_pSafenetHasp != NULL);

	return g_pSafenetHasp->g_str_test_macros;
}

CString CSafenet_hasp::hasp_get_template_authority_sn()
{
	ASSERT (g_pSafenetHasp != NULL);

	return g_pSafenetHasp->g_str_template_authority_sn;
}

void CSafenet_hasp::hasp_set_develop(const CString &strData)
{
	ASSERT (g_pSafenetHasp != NULL);
	g_pSafenetHasp->set_develop(strData);
}

void CSafenet_hasp::hasp_set_ownership(const CString &strData)
{
	ASSERT (g_pSafenetHasp != NULL);
	g_pSafenetHasp->set_ownership(strData);
}

void CSafenet_hasp::hasp_set_user_cop(const CString &strData)
{
	ASSERT (g_pSafenetHasp != NULL);
	g_pSafenetHasp->set_user_cop(strData);
}

void CSafenet_hasp::hasp_set_user_name(const CString &strData)
{
	ASSERT (g_pSafenetHasp != NULL);
	g_pSafenetHasp->set_user_name(strData);
}

void CSafenet_hasp::hasp_set_user_psw(const CString &strData)
{
	ASSERT (g_pSafenetHasp != NULL);
	g_pSafenetHasp->set_user_psw(strData);
}

void CSafenet_hasp::hasp_set_sys_name(const CString &strData)
{
	ASSERT (g_pSafenetHasp != NULL);
	g_pSafenetHasp->set_sys_name(strData);
}

void CSafenet_hasp::hasp_set_user_cop_sn(const CString &strData)
{
	ASSERT (g_pSafenetHasp != NULL);
	g_pSafenetHasp->set_user_cop_sn(strData);
}

void CSafenet_hasp::hasp_set_template_authority_sn(const CString &strData)
{
	ASSERT (g_pSafenetHasp != NULL);
	g_pSafenetHasp->set_template_authority_sn(strData);
}

void CSafenet_hasp::hasp_set_time_limit(SYSTEMTIME tmLimit)
{
	ASSERT (g_pSafenetHasp != NULL);
	g_pSafenetHasp->set_time_limit(tmLimit);
}

void CSafenet_hasp::hasp_get_develop(CString &strData)
{
	ASSERT (g_pSafenetHasp != NULL);
	g_pSafenetHasp->get_develop(strData);
}

void CSafenet_hasp::hasp_get_ownership(CString &strData)
{
	ASSERT (g_pSafenetHasp != NULL);
	g_pSafenetHasp->get_ownership(strData);
}

void CSafenet_hasp::hasp_get_user_cop(CString &strData)
{
	ASSERT (g_pSafenetHasp != NULL);
	g_pSafenetHasp->get_user_cop(strData);
}

void CSafenet_hasp::hasp_get_user_name(CString &strData)
{
	ASSERT (g_pSafenetHasp != NULL);
	g_pSafenetHasp->get_user_name(strData);
}

void CSafenet_hasp::hasp_get_user_psw(CString &strData)
{
	ASSERT (g_pSafenetHasp != NULL);
	g_pSafenetHasp->get_user_psw(strData);
}

void CSafenet_hasp::hasp_get_sys_name(CString &strData)
{
	ASSERT (g_pSafenetHasp != NULL);
	g_pSafenetHasp->get_sys_name(strData);
}

void CSafenet_hasp::hasp_get_user_cop_sn(CString &strData)
{
	ASSERT (g_pSafenetHasp != NULL);
	g_pSafenetHasp->get_user_cop_sn(strData);
}

void CSafenet_hasp::hasp_get_template_authority_sn(CString &strData)
{
	ASSERT (g_pSafenetHasp != NULL);
	g_pSafenetHasp->get_template_authority_sn(strData);
}

BOOL CSafenet_hasp::hasp_get_time_limit(SYSTEMTIME &tmLimit)
{
	ASSERT (g_pSafenetHasp != NULL);
	return g_pSafenetHasp->get_time_limit(tmLimit);
}

BOOL CSafenet_hasp::hasp_can_use_test_app(const CString &strTestApp)
{
	ASSERT (g_pSafenetHasp != NULL);
	return g_pSafenetHasp->can_use_test_app(strTestApp);
}

BOOL CSafenet_hasp::hasp_can_use_test_macro(const CString &strTestMacro)
{
	ASSERT (g_pSafenetHasp != NULL);
	return g_pSafenetHasp->can_use_test_macro(strTestMacro);
}

BOOL CSafenet_hasp::hasp_can_use_test(UINT nTestID)
{
	ASSERT (g_pSafenetHasp != NULL);
	return g_pSafenetHasp->can_use_test(nTestID);
}

BOOL CSafenet_hasp::hasp_is_power_sky()
{
	ASSERT (g_pSafenetHasp != NULL);
	return g_pSafenetHasp->is_power_sky();
}

BOOL CSafenet_hasp::hasp_is_power_sky(const CString &strCopSN)
{
	ASSERT (g_pSafenetHasp != NULL);
	return g_pSafenetHasp->is_power_sky(strCopSN);
}

BOOL CSafenet_hasp::hasp_is_power_sky_register()
{
	ASSERT (g_pSafenetHasp != NULL);
	return g_pSafenetHasp->is_power_sky_register();
}

BOOL CSafenet_hasp::hasp_is_power_sky_register(const CString &strAuthoritySN)
{
	ASSERT (g_pSafenetHasp != NULL);
	return g_pSafenetHasp->is_power_sky_register(strAuthoritySN);
}

BOOL CSafenet_hasp::hasp_has_time_authority()
{
	ASSERT (g_pSafenetHasp != NULL);

	if (hasp_is_power_sky())
	{
		return FALSE;
	}

	if (g_pSafenetHasp->is_tm_authority_FF())
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSafenet_hasp::hasp_is_overdue()
{
	ASSERT (g_pSafenetHasp != NULL);
	
	//没有时间的限制
	if (!hasp_has_time_authority())
	{
		return FALSE;
	}

	hasp_time_t  tmAuthority;

	//如果获取时间失败，期限到
	if (!g_pSafenetHasp->hasp_get_curr_time(&tmAuthority))
	{
		return TRUE;
	}

	if (tmAuthority > g_pSafenetHasp->m_tmAuthority)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

DWORD CSafenet_hasp::hasp_get_days_left()
{
	ASSERT (g_pSafenetHasp != NULL);
	DWORD dwDaysLeft = 0xFFFFFFFF;

// 	if (hasp_is_power_sky())
// 	{
// 		return dwDaysLeft;
// 	}

	if (g_pSafenetHasp->is_tm_authority_FF())
	{
		return dwDaysLeft;
	}

	hasp_time_t  tmAuthority;

	if (!g_pSafenetHasp->hasp_get_curr_time(&tmAuthority))
	{
		dwDaysLeft = 0;
		return dwDaysLeft;
	}

	if (tmAuthority > g_pSafenetHasp->m_tmAuthority)
	{
		dwDaysLeft = 0;
	}
	else
	{
		SYSTEMTIME tmSysCurr;
		g_pSafenetHasp->time_hasp_to_system(tmAuthority, tmSysCurr);
		CTime tmCurr(tmSysCurr);
		CTime tmLimit(g_pSafenetHasp->m_tmLimit);
		CTimeSpan tmSpan;
		tmSpan = tmLimit - tmCurr;
		dwDaysLeft = tmSpan.GetDays();

		if (dwDaysLeft == 0)
		{
			if (tmSpan.GetTotalHours() > 0)
			{
				dwDaysLeft = 1;
			}
		}
	}

	return dwDaysLeft;
}

BOOL CSafenet_hasp::hasp_get_curr_time(SYSTEMTIME &tmSys)
{
	ZeroMemory(&tmSys, sizeof(SYSTEMTIME));

	hasp_time_t  tmAuthority;

	if (!g_pSafenetHasp->hasp_get_curr_time(&tmAuthority))
	{
		return FALSE;
	}

	unsigned int day=0,month=0,year=0,hour=0,minute=0,second=0;
	hasp_hasptime_to_datetime(tmAuthority, &day, &month, &year, &hour, &minute, &second);
	tmSys.wYear = year;
	tmSys.wMonth = month;
	tmSys.wDay = day;
	tmSys.wHour = hour;
	tmSys.wMinute = minute;
	tmSys.wSecond = second;

	return TRUE;
}


CSafenetAuthoritys* CSafenet_hasp::hasp_get_authoritys_test()
{
	return CSafenetAuthoritysMngr::GetAuthoritys_Test();
}

CSafenetAuthoritys* CSafenet_hasp::hasp_get_authoritys_testapp()
{
	return CSafenetAuthoritysMngr::GetAuthoritys_TestApp();
}

CSafenetAuthoritys* CSafenet_hasp::hasp_get_authoritys_hasp_info()
{
	return CSafenetAuthoritysMngr::GetAuthoritys_HaspInfo();
}

CSafenetAuthoritys* CSafenet_hasp::hasp_get_authoritys_testmacros()
{
	return CSafenetAuthoritysMngr::GetAuthoritys_TestMacros();
}


void CSafenet_hasp::hasp_write_infor()
{
	hasp_status_t status;

	hasp_size_t offset = 0; 
	hasp_size_t len = 70;
	unsigned char data[400];
	ZeroMemory(data, 400);
	char *pData = (char*)data;

	g_pSafenetHasp->time_system_to_hasp();
	len = g_pSafenetHasp->get_infor_buf(pData);

	status = hasp_write(g_hasp_handle, HASP_FILEID_RW, offset, len, data);

	/* check if operation was successful */
	if (status != HASP_STATUS_OK)
	{
		switch (status)
		{
		case HASP_FEATURE_NOT_FOUND:
			break;
		case HASP_INV_HND:
			break;
		case HASP_INV_FILEID:
			break;
		case HASP_MEM_RANGE:
			break;
		default:
			break;
		}
	}

}

void CSafenet_hasp::hasp_set_oa_server_mode()
{
	g_pSafenetHasp->g_hasp_oa_server_mode = TRUE;
}
