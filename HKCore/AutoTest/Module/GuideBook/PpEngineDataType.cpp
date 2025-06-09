#include "StdAfx.h"
#include "GbParaTypeMngr.h"
#include "GbXMLKeys.h"
#include "../XLanguageResourceAts.h"
#include "../../../Module/API/GlobalConfigApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CPpEngineDataType::CPpEngineDataType(void)
{
	
}

CPpEngineDataType::~CPpEngineDataType(void)
{
	
}


void CPpEngineDataType::InitPpEngineType()
{
	m_strID = g_strPpEngineDataTypeID;
	m_strName = g_strPpEngineDataTypeID;

	CString strFile;
	strFile = _P_GetCommonConfigPath();
	strFile += _T("ProtocolEngineConfig.xml");

	if (m_oDsEngineConfig.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys))
	{
		POS pos = m_oDsEngineConfig.GetHeadPosition();
		CDvmData *pData = NULL;
		long nIndex = 0;

		while (pos != NULL)
		{
			pData = (CDvmData *)m_oDsEngineConfig.GetNext(pos);
			AddNewValue(pData->m_strName, pData->m_strID, nIndex);
			nIndex++;
		}
	}
	else
	{
		AddNewValue(/*_T("传统规约")*/g_sLangTxt_TraProtocol, g_strPpEngineProgID, 0);
		AddNewValue(/*_T("61850规约")*/g_sLangTxt_61850Protocol, g_strPpEngineProgIDMms, 1);
	}

	AddNewValue(/*_T("无")*/g_sLangTxt_None, _T("none"), 0);
}

