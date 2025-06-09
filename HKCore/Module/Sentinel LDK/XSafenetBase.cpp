// XSafenetBase.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XSafenetBase.h"
#include "..\XLanguage\XLanguageResource.h"
#include "..\TestMacro\TestMacrosFileMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


extern unsigned char g_psz_def_develop[MAX_PATH];
extern unsigned char g_psz_def_ownership[MAX_PATH];
extern unsigned char g_psz_def_infor[MAX_PATH];
extern unsigned char g_psz_title_ownership[MAX_PATH];
extern unsigned char g_psz_title_develop[MAX_PATH];
extern unsigned char g_psz_title_user_cop[MAX_PATH];


BOOL hasp_read_string(CBufferBase &oBuffer, CString &strData)
{
	char *pszData = NULL;
	pszData = oBuffer.GetString();

	if (oBuffer.IsPoiterInBuffer(pszData))
	{
		oBuffer.NextString();
		strData = pszData;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

char* hasp_read_string(char *pBuffer, CString &strData)
{
	strData = pBuffer;
	pBuffer += strlen(pBuffer);
	pBuffer++;

	return pBuffer;
}

//////////////////////////////////////////////////////////////////////////
//CSafenet_Base
CSafenet_Base::CSafenet_Base()
{
	m_dwVersion = SAFENET_VERSION_0000;
	set_tm_authority_FF();
}

CSafenet_Base::~CSafenet_Base()
{

}

CString CSafenet_Base::get_develop(BOOL bHasTitle)
{
	CString strText;

	strText = g_str_develop;

	if (bHasTitle)
	{
		CString strTemp;
		strTemp = g_sLangTxt_SystemDevelop;//g_psz_title_develop;
		strText = strTemp + strText;
	}

	return strText;
}

CString CSafenet_Base::get_ownership(BOOL bHasTitle)
{
	CString strText;

	strText = g_str_ownership;

	if (bHasTitle)
	{
		CString strTemp;
		strTemp = g_sLangTxt_RightsReserved;//g_psz_title_ownership;
		strText = strTemp + strText;
	}

	return strText;
}

CString CSafenet_Base::get_user_cop(BOOL bHasTitle)
{
	CString strText;

	strText = g_str_user_cop;

	if (bHasTitle)
	{
		CString strTemp;
		strTemp = g_sLangTxt_ClientUnit;//g_psz_title_user_cop;
		strText = strTemp + strText;
	}

	return strText;
}

CString CSafenet_Base::get_user_name(BOOL bHasTitle)
{
	CString strText;

	strText = g_str_user_name;

	return strText;
}

CString CSafenet_Base::get_user_psw()
{
	return g_str_user_psw;
}


CString CSafenet_Base::get_sys_name()
{
	return g_str_sys_name;
}

CString CSafenet_Base::get_user_cop_sn()
{
	return g_str_user_cop_sn;
}

CString CSafenet_Base::get_test_apps()
{
	return g_str_test_apps;
}

CString CSafenet_Base::get_test_macros()
{
	return g_str_test_macros;
}

CString CSafenet_Base::get_template_authority_sn()
{
	return g_str_template_authority_sn;
}

CString CSafenet_Base::get_safenet_sn()
{
	return m_strSafenet_SN;
}

SYSTEMTIME CSafenet_Base::get_time_limit()
{
	return m_tmLimit;
}

void CSafenet_Base::set_develop(const CString &strData)
{
	g_str_develop = strData;
}

void CSafenet_Base::set_ownership(const CString &strData)
{
	g_str_ownership = strData;
}

void CSafenet_Base::set_user_cop(const CString &strData)
{
	g_str_user_cop = strData;
}

void CSafenet_Base::set_user_name(const CString &strData)
{
	g_str_user_name = strData;
}

void CSafenet_Base::set_user_psw(const CString &strData)
{
	g_str_user_psw = strData;
}


void CSafenet_Base::set_sys_name(const CString &strData)
{
	g_str_sys_name = strData;
}

void CSafenet_Base::set_user_cop_sn(const CString &strData)
{
	g_str_user_cop_sn = strData;
}

void CSafenet_Base::set_test_apps(const CString &strData)
{
	g_str_test_apps = strData;
}

void CSafenet_Base::set_test_macros(const CString &strData)
{
	g_str_test_macros = strData;
}

void CSafenet_Base::set_template_authority_sn(const CString &strData)
{
	g_str_template_authority_sn = strData;
}

void CSafenet_Base::set_time_limit(SYSTEMTIME tmLimit)
{
	m_tmLimit = tmLimit;
}

void CSafenet_Base::set_test(const CString &strData)
{
	long nPos1 = 0, nPos2 = 0;
	long nValue = 0;
	CString strValue;
	ZeroMemory(m_byteAuthority, SAFENET_AUTHORITY_BUF_LEN * sizeof(BYTE));

	while (TRUE)
	{
		nPos2 = strData.Find( _T("$"), nPos1);

		if (nPos2 < 0)
		{
			break;
		}

		strValue = strData.Mid(nPos1, nPos2-nPos1);
		nValue = CString_To_long(strValue);
		nPos1 = nPos2 + 1;

		long nIndex = 0;

		for (nIndex=0; nIndex<SAFENET_AUTHORITY_BUF_LEN; nIndex++)
		{
			if (m_byteAuthority[nIndex] == 0)
			{
				m_byteAuthority[nIndex] = (BYTE)nValue;
				break;
			}
		}
	}
}

void CSafenet_Base::set_safenet_sn(const CString &strData)
{
	m_strSafenet_SN = strData;
}

void CSafenet_Base::get_develop(CString &strData)
{
	strData = g_str_develop;
}

void CSafenet_Base::get_ownership(CString &strData)
{
	strData = g_str_ownership;
}

void CSafenet_Base::get_user_cop(CString &strData)
{
	strData = g_str_user_cop;
}

void CSafenet_Base::get_user_name(CString &strData)
{
	strData = g_str_user_name;
}

void CSafenet_Base::get_user_psw(CString &strData)
{
	strData = g_str_user_psw;
}

void CSafenet_Base::get_sys_name(CString &strData)
{
	strData = g_str_sys_name;
}

void CSafenet_Base::get_user_cop_sn(CString &strData)
{
	strData = g_str_user_cop_sn;
}

void CSafenet_Base::get_test_apps(CString &strData)
{
	strData = g_str_test_apps;
}

void CSafenet_Base::get_test_macros(CString &strData)
{
	strData = g_str_test_macros;
}

void CSafenet_Base::get_template_authority_sn(CString &strData)
{
	strData = g_str_template_authority_sn;
}

BOOL CSafenet_Base::get_time_limit(SYSTEMTIME &tmLimit)
{
	tmLimit = m_tmLimit;

	if (is_tm_authority_FF())
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

BOOL CSafenet_Base::is_power_sky()
{
	return is_power_sky(g_str_user_cop_sn);
}

BOOL CSafenet_Base::is_power_sky(const CString &strCopSN)
{
	if (strCopSN.GetLength() == 9)
	{
		CString strSN = strCopSN;
		strSN.MakeUpper();

		if (     strSN.GetAt(0) == 'P'
			&& strSN.GetAt(1) == 'O'
			&& strSN.GetAt(2) == 'W'
			&& strSN.GetAt(3) == 'E'
			&& strSN.GetAt(4) == 'R'
			&& strSN.GetAt(5) == '-'
			&& strSN.GetAt(6) == 'S'
			&& strSN.GetAt(7) == 'K'
			&& strSN.GetAt(8) == 'Y')
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CSafenet_Base::is_power_sky_register()
{
	return is_power_sky_register(g_str_template_authority_sn);
}

BOOL CSafenet_Base::is_power_sky_register(const CString &strAuthoritySN)
{
	if (strAuthoritySN.GetLength() == 18)
	{
		CString strSN = strAuthoritySN;
		strSN.MakeUpper();

		if (     strSN.GetAt(0) == 'P'
			&& strSN.GetAt(1) == 'O'
			&& strSN.GetAt(2) == 'W'
			&& strSN.GetAt(3) == 'E'
			&& strSN.GetAt(4) == 'R'
			&& strSN.GetAt(5) == '-'
			&& strSN.GetAt(6) == 'S'
			&& strSN.GetAt(7) == 'K'
			&& strSN.GetAt(8) == 'Y'
			&& strSN.GetAt(9) == '-'
			&& strSN.GetAt(10) == 'R'
			&& strSN.GetAt(11) == 'E'
			&& strSN.GetAt(12) == 'G'
			&& strSN.GetAt(13) == 'I'
			&& strSN.GetAt(14) == 'S'
			&& strSN.GetAt(15) == 'T'
			&& strSN.GetAt(16) == 'E'
			&& strSN.GetAt(17) == 'R'
			)
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CSafenet_Base::can_use_test_app(const CString &strTestApp)
{
	if (is_power_sky())
	{
		return TRUE;
	}

	return has_authority(strTestApp);
}

BOOL CSafenet_Base::can_use_test_macro(const CString &strTestMacro)
{
	if (is_power_sky())
	{
		return TRUE;
	}

	return has_authority_test_macro(strTestMacro);
}

BOOL CSafenet_Base::can_use_test(UINT nTestID)
{
	if (is_power_sky())
	{
		return TRUE;
	}

	return has_authority(nTestID);
}


void CSafenet_Base::read_infor(char *pBuffer)
{
	g_str_develop.Empty();
	g_str_ownership.Empty();
	g_str_user_cop.Empty();
	g_str_user_name.Empty();
	g_str_user_psw.Empty();
	g_str_user_cop_sn.Empty();
	g_str_test_apps.Empty();
	g_str_test_macros.Empty();
	g_str_template_authority_sn.Empty();
	ZeroMemory(m_byteAuthority, SAFENET_AUTHORITY_BUF_LEN * sizeof(BYTE));

	char *pTemp = pBuffer;

	if (strncmp(pBuffer, SAFENET_VERSION_KEY, 6) == 0)
	{
		read_infor_new(pTemp);
	}
	else
	{
		read_infor_old(pTemp);
	}
}
// 
// void CSafenet_Base::read_infor_old(CBufferBase &oBuffer)
// {
// 	if (!hasp_read_string(oBuffer, g_str_develop))
// 	{
// 		return;
// 	}
// 
// 	if (!hasp_read_string(oBuffer, g_str_ownership))
// 	{
// 		return;
// 	}
// 
// 	if (!hasp_read_string(oBuffer, g_str_user_cop))
// 	{
// 		return;
// 	}
// 
// 	if (!hasp_read_string(oBuffer, g_str_user_name))
// 	{
// 		return;
// 	}
// 
// 	if (!hasp_read_string(oBuffer, g_str_user_psw))
// 	{
// 		return;
// 	}
// 
// 	if (!hasp_read_string(oBuffer, g_str_sys_name))
// 	{
// 		return;
// 	}
// }
// 
// void CSafenet_Base::read_infor_new(CBufferBase &oBuffer)
// {
// 	//POWSKY
// 	oBuffer.OffsetPointer(6);
// 
// 	//Version
// 	char *pBuffer = oBuffer.GetPointer();
// 	m_dwVersion = *((DWORD*)pBuffer);
// 	oBuffer.OffsetPointer(sizeof(DWORD));
// 
// 	read_infor_old(oBuffer);
// 
// 	//g_str_user_cop_sn
// 	if (!hasp_read_string(oBuffer, g_str_user_cop_sn))
// 	{
// 		return;
// 	}
// 
// 	//g_str_test_apps
// 	if (!hasp_read_string(oBuffer, g_str_test_apps))
// 	{
// 		return;
// 	}
// 
// 	//Authority
// 	oBuffer.OffsetPointer(1);  //跳过字符串的结束符‘\0’
// 	pBuffer = oBuffer.GetPointer();
// 	memcpy(m_byteAuthority, pBuffer, SAFENET_AUTHORITY_BUF_LEN * sizeof(BYTE));
// 	oBuffer.OffsetPointer(SAFENET_AUTHORITY_BUF_LEN * sizeof(BYTE));
// 
// 	//初始化权限表
// 	read_authority_test();
// 	read_authority_testapp();
// }

char* CSafenet_Base::read_infor_old(char *pBuffer)
{
	char *pTemp = pBuffer;
	pTemp = hasp_read_string(pTemp, g_str_develop);
	pTemp = hasp_read_string(pTemp, g_str_ownership);
	pTemp = hasp_read_string(pTemp, g_str_user_cop);
	pTemp = hasp_read_string(pTemp, g_str_user_name);
	pTemp = hasp_read_string(pTemp, g_str_user_psw);
	pTemp = hasp_read_string(pTemp, g_str_sys_name);

	return pTemp;
}

char* CSafenet_Base::read_infor_new(char *pBuffer)
{
	char *pTemp = pBuffer;

	//POWSKY
	pTemp += 7;

	//Version
	m_dwVersion = *((DWORD*)pTemp);
	pTemp += sizeof(DWORD);

	pTemp = read_infor_old(pTemp);

	pTemp = hasp_read_string(pTemp, g_str_user_cop_sn);
	pTemp = hasp_read_string(pTemp, g_str_test_apps);

	//Authority
	memcpy(m_byteAuthority, pTemp, SAFENET_AUTHORITY_BUF_LEN * sizeof(BYTE));
	pTemp += SAFENET_AUTHORITY_BUF_LEN;

	//tmAuthority
	if (m_dwVersion >= SAFENET_VERSION_0002)
	{
		memcpy((BYTE*)&m_tmAuthority, pTemp, sizeof(hasp_time_t));
		pTemp += 8;
	}
	else
	{
		set_tm_authority_FF();
	}

	//2019-1-26
	if (m_dwVersion >= SAFENET_VERSION_0003)
	{
		pTemp = hasp_read_string(pTemp, g_str_test_macros);
		pTemp = hasp_read_string(pTemp, g_str_template_authority_sn);
	}

	//初始化权限表
	read_authority_test();
	read_authority_testapp();
	read_authority_testmacros();

	return pTemp;
}

void CSafenet_Base::read_authority_test()
{
	CSafenetAuthoritys *pTest = CSafenetAuthoritysMngr::GetAuthoritys_Test();

	if (pTest == NULL)
	{
		return;
	}

	POS pos = pTest->GetHeadPosition();
	CSafenetAuthority *p = NULL;

	while (pos != NULL)
	{
		p = (CSafenetAuthority*)pTest->GetNext(pos);
		p->m_nEnable = has_authority(CString_To_long(p->m_strID));
	}
}

void CSafenet_Base::read_authority_testapp()
{
	CSafenetAuthoritys *pTestApp = CSafenetAuthoritysMngr::GetAuthoritys_TestApp();

	if (pTestApp == NULL)
	{
		return;
	}

	pTestApp->InitByAuthoritys(g_str_test_apps);
// 	POS pos = pTestApp->GetHeadPosition();
// 	CSafenetAuthority *p = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		p = (CSafenetAuthority*)pTestApp->GetNext(pos);
// 		p->m_nEnable = has_authority(p->m_strID);
// 	}
}

void CSafenet_Base::read_authority_testmacros()
{
	CSafenetAuthoritys *pTestMacros = CSafenetAuthoritysMngr::GetAuthoritys_TestMacros();

	if (pTestMacros == NULL)
	{
		return;
	}

	pTestMacros->InitByAuthoritys(g_str_test_macros);
// 	POS pos = pTestMacros->GetHeadPosition();
// 	CSafenetAuthority *p = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		p = (CSafenetAuthority*)pTestMacros->GetNext(pos);
// 		p->m_nEnable = has_authority_test_macro(p->m_strID);
// 	}
}

void CSafenet_Base::init_authority_test()
{
	CSafenetAuthoritys *pTest = CSafenetAuthoritysMngr::GetAuthoritys_Test();
	POS pos = pTest->GetHeadPosition();
	CSafenetAuthority *p = NULL;
	long nIndex = 0;

	::ZeroMemory(m_byteAuthority, SAFENET_AUTHORITY_BUF_LEN);

	while (pos != NULL)
	{
		p = (CSafenetAuthority*)pTest->GetNext(pos);
		
		if (p->m_nEnable == 1)
		{
			m_byteAuthority[nIndex] = (BYTE)CString_To_long(p->m_strID);
			nIndex++;
		}
	}
}

void CSafenet_Base::init_authority_testapp()
{
	CSafenetAuthoritys *pTestApp = CSafenetAuthoritysMngr::GetAuthoritys_TestApp();
	ASSERT(pTestApp != NULL);

	if (pTestApp != NULL)
	{
		pTestApp->GetAuthoritys(g_str_test_apps);
	}
	else
	{
		g_str_test_apps.Empty();
	}

// 	POS pos = pTestApp->GetHeadPosition();
// 	CSafenetAuthority *p = NULL;
// 	g_str_test_apps.Empty();
// 
// 	while (pos != NULL)
// 	{
// 		p = (CSafenetAuthority*)pTestApp->GetNext(pos);
// 
// 		if (p->m_nEnable == 1)
// 		{
// 			g_str_test_apps.AppendFormat(_T("%s$"), p->m_strID);
// 		}
// 	}
}

void CSafenet_Base::init_authority_testmacro()
{
	CSafenetAuthoritys *pTestMacros = CSafenetAuthoritysMngr::GetAuthoritys_TestMacros();
	ASSERT (pTestMacros != NULL);

	if (pTestMacros != NULL)
	{
		pTestMacros->GetAuthoritys(g_str_test_macros);
	}
	else
	{
		g_str_test_macros.Empty();
	}

// 	POS pos = pTestMacros->GetHeadPosition();
// 	CSafenetAuthority *p = NULL;
// 	g_str_test_macros.Empty();
// 
// 	while (pos != NULL)
// 	{
// 		p = (CSafenetAuthority*)pTestMacros->GetNext(pos);
// 
// 		if (p->m_nEnable == 1)
// 		{
// 			g_str_test_macros.AppendFormat(_T("%s$"), p->m_strID);
// 		}
// 	}
}

BOOL CSafenet_Base::is_tm_authority_FF()
{
	long nCount = sizeof(hasp_time_t) / 8;
	BYTE *pByte = (BYTE*)&m_tmAuthority;
	long nIndex = 0;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		if (*pByte != 0xFF)
		{
			return FALSE;
		}

		pByte++;
	}

	return TRUE;
}

void CSafenet_Base::set_tm_authority_FF()
{
	memset(&m_tmAuthority, 0xFF, sizeof(hasp_time_t));
}

void CSafenet_Base::init_infor()
{
	g_str_develop.Empty();
	g_str_ownership.Empty();
	g_str_user_cop.Empty();
	g_str_user_name.Empty();
	g_str_sys_name.Empty();
}

char* hasp_write_string(char *pInforBuf, const char *pszString)
{
	strcpy(pInforBuf, pszString);
	return pInforBuf + strlen(pszString) + 1;
}

char* hasp_write_string(char *pInforBuf, const CString &strText)
{
	char *pDestBuff = NULL;
	CString_to_char(strText, &pDestBuff);
	char *pRet = hasp_write_string(pInforBuf, pDestBuff);
	delete pDestBuff;

	return pRet;
}

char* hasp_write_buffer(char *pInforBuf, BYTE *pSrcBuf, long nLen)
{
	memcpy(pInforBuf, pSrcBuf, nLen);
	return pInforBuf + nLen;
}

char* hasp_write_dword(char *pInforBuf, DWORD dwValue)
{
	memcpy(pInforBuf, &dwValue, sizeof(DWORD));
	return pInforBuf + sizeof(DWORD);
}

long CSafenet_Base::get_infor_buf(char* &pInforBuf)
{
	init_authority_test();
	init_authority_testapp();
	init_authority_testmacro();

	char *pTemp = pInforBuf;

	pTemp = hasp_write_string(pTemp, SAFENET_VERSION_KEY);
	pTemp = hasp_write_dword(pTemp, SAFENET_VERSION_CUR);
	pTemp = hasp_write_string(pTemp, g_str_develop);
	pTemp = hasp_write_string(pTemp, g_str_ownership);
	pTemp = hasp_write_string(pTemp, g_str_user_cop);
	pTemp = hasp_write_string(pTemp, g_str_user_name);
	pTemp = hasp_write_string(pTemp, g_str_user_psw);
	pTemp = hasp_write_string(pTemp, g_str_sys_name);
	pTemp = hasp_write_string(pTemp, g_str_user_cop_sn);
	pTemp = hasp_write_string(pTemp, g_str_test_apps);
	pTemp = hasp_write_buffer(pTemp, m_byteAuthority, SAFENET_AUTHORITY_BUF_LEN);
	pTemp = hasp_write_buffer(pTemp, (BYTE*)&m_tmAuthority, sizeof(hasp_time_t)); //20180525
	pTemp = hasp_write_string(pTemp, g_str_test_macros);
	pTemp = hasp_write_string(pTemp, g_str_template_authority_sn);

	long nLen = pTemp - pInforBuf;

	return nLen;
}

BOOL CSafenet_Base::has_authority(UINT nAuthority)
{
	long nIndex = 0;
	BOOL bFind = FALSE;

	for (nIndex=0; nIndex<SAFENET_AUTHORITY_BUF_LEN; nIndex++)
	{
		if (m_byteAuthority[nIndex] == 0)
		{
			break;
		}

		if (m_byteAuthority[nIndex] == nAuthority)
		{
			bFind = TRUE;
			break;
		}
	}

	return bFind;
}

BOOL CSafenet_Base::has_authority(const CString &strAuthority)
{
	return safenet_has_authority(g_str_test_apps, strAuthority);
}

BOOL CSafenet_Base::has_authority_test_macro(const CString &strAuthority)
{
	return safenet_has_authority(g_str_test_macros, strAuthority);
}

