//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XLanguageResourceBase.cpp  CXLanguageResourceAtsBase


#include "stdafx.h"
#include "XLanguageResourcePp.h"
#include "../../Module/API/GlobalConfigApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXLanguageResourcePpBase::CXLanguageResourcePpBase()
{
	
}


CXLanguageResourcePpBase::~CXLanguageResourcePpBase()
{

}

void CXLanguageResourcePpBase::InitLangFileForDebug(const CString &strModule)
{
	m_strXLangFile = _P_GetLanguagePath();
    m_strXLangFile.AppendFormat(_T("%s.xml"), strModule.GetString());
}

void CXLanguageResourcePpBase::RegisterLanguageResource()
{
	CXLanguageResourceBase::RegisterLanguageResource();
	AddString(g_sLangID_Home, &g_sLangTxt_Home);
	
}


CString CXLanguageResourcePpBase::g_sLangID_Home                 = _T("sHome");
CString CXLanguageResourcePpBase::g_sLangTxt_Home                = _T("��ҳ(H)");