//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//WzdMatchFilterKeys.cpp  CWzdMatchFilterKeys


#include "stdafx.h"
#include "WzdMatchFilterKeys.h"

CWzdMatchFilterKeys *CWzdMatchFilterKeys::g_pFilterTextMngr = NULL;
long CWzdMatchFilterKeys::m_nFilterTextMngrRef = 0;

CWzdMatchFilterKeys::CWzdMatchFilterKeys()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("WbWzdMatchFilter.xml");
	OpenXmlFile(strFile);
}

CWzdMatchFilterKeys::~CWzdMatchFilterKeys()
{

}

CWzdMatchFilterKeys* CWzdMatchFilterKeys::Create()
{
	m_nFilterTextMngrRef++;

	if (m_nFilterTextMngrRef == 1)
	{
		g_pFilterTextMngr = new CWzdMatchFilterKeys();
	}

	return g_pFilterTextMngr;
}

CWzdMatchFilterKeys* CWzdMatchFilterKeys::GetWzdMatchFilterKeys()
{
	return g_pFilterTextMngr;
}

void CWzdMatchFilterKeys::Release()
{
	m_nFilterTextMngrRef--;

	if (m_nFilterTextMngrRef == 0)
	{
		delete g_pFilterTextMngr;
		g_pFilterTextMngr = NULL;
	}
}
