#include "stdafx.h"
#include"Iec61850Config.h"

#include"../../../../Module/API/GlobalConfigApi.h"

#ifdef _PSX_IDE_QT_
#include"../../SttDevice/RelayTest/SttDriverOper.h"
#include<QtDebug>
#endif


CString CIec61850Config::m_strMacroName = "Iec61850Config";
CString CIec61850Config::m_strMacroID = ("Iec61850Config");
CString CIec61850Config::m_strMacroVer ="1.0";
CString CIec61850Config::m_strFilePostFix = "sttcfg";


CIec61850Config::CIec61850Config() : CSttTestBase()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
#ifdef _PSX_IDE_QT_
	CIEC61850CfgMngr::g_pIEC61850CfgMngr->m_oIecCfgDatasMngr=&m_oIecCfgDatasMngr;	
#endif
}

void CIec61850Config::Init()
{ 
}

CIec61850Config::~CIec61850Config(void)
{
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
		m_oIecCfgDatasMngr.XmlRead(*pCfgDatasNode, CCfgDataMngrXmlRWKeys::g_pXmlKeys);
		return;
	}

	//2020-4-6  lijq
	if (stt_xml_serialize_is_write(pXmlSerialize))
	{
		CXmlRWElementBase *pParasNode = pXmlSerialize->CreateElement(CCfgDataMngrXmlRWKeys::CIecCfgDatasMngrKey());
		m_oIecCfgDatasMngr.XmlWriteChildren(*pXmlSerialize->GetRWDoc(), *pParasNode, CCfgDataMngrXmlRWKeys::g_pXmlKeys);
	}
}

long CIec61850Config::SetParameter(DWORD dwState)
{
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

	//lijq 2020-3-28
	//qDebug()<<("CIec61850Config::DataDownload Finished");
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CIec61850Config::DataDownload Finished"));

	TtmToDrv();
}

void CIec61850Config::TtmToDrv()
{	
#ifdef _PSX_IDE_QT_
	CIEC61850CfgMngr::g_pIEC61850CfgMngr->InitPara();
	CIEC61850CfgMngr::g_pIEC61850CfgMngr->SetPara();
#endif
}
