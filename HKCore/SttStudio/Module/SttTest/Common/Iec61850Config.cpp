#include "stdafx.h"
#include"Iec61850Config.h"

#include"../../../../Module/API/GlobalConfigApi.h"

#ifdef _PSX_IDE_QT_
#include<QtDebug>
#endif


CString CIec61850Config::m_strMacroName = "Iec61850Config";
CString CIec61850Config::m_strMacroID = STT_MACRO_ID_Iec61850Config;
CString CIec61850Config::m_strMacroVer ="1.0";
CString CIec61850Config::m_strFilePostFix = "sttcfg";
CString g_strIecCfgVer = "";

CIec61850Config::CIec61850Config() : CSttTestBase()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	m_pIecCfgDatasMngr = NULL;
}

void CIec61850Config::Init()
{
}

CIec61850Config::~CIec61850Config(void)
{
#ifndef _PSX_QT_LINUX_

	if (m_pIecCfgDatasMngr != NULL)
	{
		delete m_pIecCfgDatasMngr;
		m_pIecCfgDatasMngr = NULL;
	}
#endif
}

void CIec61850Config::AfterSetParameter()
{
}

long CIec61850Config::CalReport(UINT nState)
{
	return 0;
}

void CIec61850Config::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef _PSX_QT_LINUX_
	m_pIecCfgDatasMngr=(CIecCfgDatasMngr*)(CSttDeviceBase::g_pSttDeviceBase->GetIecCfgDatasMngr());
#else
	if (m_pIecCfgDatasMngr == NULL)
	{
		m_pIecCfgDatasMngr = new CIecCfgDatasMngr;
	}
#endif
	//2020-4-6  lijq
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		CXmlRWNodeBase *pParasNode = pXmlSerialize->GetElement();

		if((pParasNode == NULL)||(!pParasNode->IsValid()))
		{
			return;
		}

		CXmlRWNodeBase *pCfgDatasNode = pParasNode->GetChildNode(CCfgDataMngrXmlRWKeys::CIecCfgDatasMngrKey());

		if((pCfgDatasNode == NULL)||(!pCfgDatasNode->IsValid()))
		{
			return;
		}

		m_pIecCfgDatasMngr->DeleteAll();
		m_pIecCfgDatasMngr->InitDatasMngr();
		m_pIecCfgDatasMngr->m_strDate = "";
		m_pIecCfgDatasMngr->XmlRead(*pCfgDatasNode, CCfgDataMngrXmlRWKeys::g_pXmlKeys);
		return;
	}

	//2020-4-6  lijq
	if (stt_xml_serialize_is_write(pXmlSerialize))
	{
		CXmlRWElementBase *pParasNode = pXmlSerialize->CreateElement(CCfgDataMngrXmlRWKeys::CIecCfgDatasMngrKey());
		m_pIecCfgDatasMngr->XmlWriteChildren(*pXmlSerialize->GetRWDoc(), *pParasNode, CCfgDataMngrXmlRWKeys::g_pXmlKeys);
	}
}

long CIec61850Config::SetParameter(DWORD dwState)
{
	CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("CIec61850Config::SetParameter >>>>>>"));
	TtmToDrv();
	return 0;
}

void CIec61850Config::StartTest()
{
	CSttTestBase::StartTest();
	CString strSaveIecCfgPath;
	strSaveIecCfgPath = _P_GetConfigPath();
	strSaveIecCfgPath.AppendFormat(_T("/SaveIecConfig.xml"));
#ifdef _PSX_IDE_QT_
	//m_oIecCfgDatasMngr.SaveAsIecCfgFile(strSaveIecCfgPath);
#endif
	CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("CIec61850Config::StartTest >>>>>>"));
	ReturnTestStateEvent_TestStart(0, 0, FALSE);
	TtmToDrv();

	//时间标识置为0,自动测试处理此消息
	ReturnTestStateEvent_TestFinish(0, 0, FALSE);
}

void CIec61850Config::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
	if(m_pIecCfgDatasMngr->m_strDate.length() > 0)
	{
		if(g_strIecCfgVer == m_pIecCfgDatasMngr->m_strDate)
		{
			Sleep(50);
			return;//无需更新IEC配置
		}
		else
		{
			g_strIecCfgVer = m_pIecCfgDatasMngr->m_strDate;
		}
	}

	CSttDeviceBase::g_pSttDeviceBase->SetIEC61850Para();
	//	g_theSystemConfig 变量更新
	CIecCfgSysParas *pSysParasMngr = m_pIecCfgDatasMngr->GetSysParasMngr();
	if(pSysParasMngr!=NULL)
	{
		g_theSystemConfig->m_nParaMode = pSysParasMngr->m_nPrimParas>0?0:1;
        g_theSystemConfig->m_nPkgOutMode = pSysParasMngr->m_nPrimOutput>0?0:1;
		g_theSystemConfig->m_bKeepSendIecPkt=!(pSysParasMngr->m_nPkgSendType);
		CIecCfgPrimRates *pPrimRates=pSysParasMngr->GetPrimRates();
		if(pPrimRates!=NULL)
		{
			CIecCfgPrimRate *pPrimRate;
			CString strID;
			for(int nIndex=0;nIndex<MAX_DIGITAL_GROUP_NUM;nIndex++)
			{
				strID.Format(_T("U%d-abc"),nIndex+1);
				pPrimRate = (CIecCfgPrimRate*)pPrimRates->FindByID(strID);
				if(pPrimRate!=NULL)
				{
					g_theSystemConfig->m_fVPrimary[nIndex]=pPrimRate->m_fPrimValue;
					g_theSystemConfig->m_fVSecondary[nIndex]=pPrimRate->m_fSecondValue;
				}

				strID.Format(_T("I%d-abc"),nIndex+1);
				pPrimRate = (CIecCfgPrimRate*)pPrimRates->FindByID(strID);
				if(pPrimRate!=NULL)
				{
					g_theSystemConfig->m_fIPrimary[nIndex]=pPrimRate->m_fPrimValue;
					g_theSystemConfig->m_fISecondary[nIndex]=pPrimRate->m_fSecondValue;
				}
			}
		}
	}

	CIecCfgDatasSMV* pSmvMngr = m_pIecCfgDatasMngr->GetSmvMngr();
	if(pSmvMngr!=NULL)
	{
		CIecCfgSmvRates* pSmvRates = pSmvMngr->GetIecCfgSmvRates();
		if(pSmvRates!=NULL)
		{
			g_theSystemConfig->m_fVRate[0] = pSmvRates->GetSmvRate(SMV_RATEID_STR_UABCZ);
			g_theSystemConfig->m_fIRate[0] = pSmvRates->GetSmvRate(SMV_RATEID_STR_IABC);

			g_theSystemConfig->m_fVRate[1] = pSmvRates->GetSmvRate(SMV_RATEID_STR_PUABCZ);
			g_theSystemConfig->m_fIRate[1] = pSmvRates->GetSmvRate(SMV_RATEID_STR_PIABC);

			g_theSystemConfig->m_fVRate[2] = pSmvRates->GetSmvRate(SMV_RATEID_STR_SUABCZ);
			g_theSystemConfig->m_fIRate[2] = pSmvRates->GetSmvRate(SMV_RATEID_STR_SIABC);

			g_theSystemConfig->m_fVRate[3] = pSmvRates->GetSmvRate(SMV_RATEID_STR_TUABCZ);
			g_theSystemConfig->m_fIRate[3] = pSmvRates->GetSmvRate(SMV_RATEID_STR_TIABC);

			g_theSystemConfig->m_fVRate[4] = pSmvRates->GetSmvRate(SMV_RATEID_STR_UABCZ5);
			g_theSystemConfig->m_fIRate[4] = pSmvRates->GetSmvRate(SMV_RATEID_STR_IABC5);

			g_theSystemConfig->m_fVRate[5] = pSmvRates->GetSmvRate(SMV_RATEID_STR_UABCZ6);
			g_theSystemConfig->m_fIRate[5] = pSmvRates->GetSmvRate(SMV_RATEID_STR_IABC6);
		}
	}

	CSttDeviceBase::g_pSttDeviceBase->SetSystemConfig();
#endif
}
