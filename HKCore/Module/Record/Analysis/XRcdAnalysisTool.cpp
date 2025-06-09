// XRcdAnalysisTool.cpp: implementation of the CXRcdAnalysisTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XRcdAnalysisTool.h"
#include "XRcdAnalysisDrawMngr.h"

#include "../../API/FileApi.h"
#include "../XRecordDrawComtradeDib.h"
#include "../../DataMngr/DataMngrTrans.h"

#include "XRcdCalRespTime.h"
#include "XRcdSyncAnalysis.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CXRcdAnalysisTool
CXRcdAnalysisTool::CXRcdAnalysisTool()
{
	CXDrawXmlRWKeys::Create();
	m_fChValue = 0;
	m_nWidth = 800;
	m_nHeight = 600;
	m_pRcdAnalysis = NULL;
	m_pRcdDraw = NULL;
}

CXRcdAnalysisTool::~CXRcdAnalysisTool()
{
	CXDrawXmlRWKeys::Release();
}

/*
<?xml version="1.0" encoding="UTF-8"?>
<group name="RcdAnalysis" id="" data-type="">
	<data name="RcdAnalysis" id="RcdAnalysis" data-type="string" unit="" value="RespTime" format="" remark="" default="" reserved="0" time="0">【分析功能：RespTime、ChannelSyc】
		<value name="Channel" id="Channel" data-type="string" unit="" value="I"/>【通道ID或者通道的类型】
		<value name="ChValue" id="ChValue" data-type="float" unit="" value="50"/>【通道计算时用的通道值，用于计算Delta突变，如果没有定义，则使用便利得到的最大值】
	</data>
	<group name="RcdDraw" id="" data-type="">【绘图定义】
		<data name="width" id="width" data-type="number" unit="" value="800" format="" remark="" default="800" reserved="0" time="0"/>【绘图：宽度】
		<data name="height" id="height" data-type="number" unit="" value="600" format="" remark="" default="600" reserved="0" time="0"/>【绘图：高度】
		<group name="ChsGroup1" id="ChsGroup1" data-type="ChsGroup">【绘图时的通道分组，如果没有定义，则每个通道都是单独绘制的】
			<data name="Ua" id="Ua" data-type="Channel" unit="" value="Ua" format="" remark="" default="" reserved="0" time="0"/>
			<data name="Ia" id="Ia" data-type="Channel" unit="" value="Ia" format="" remark="" default="" reserved="0" time="0"/>
		</group>
	</group>
</group>
*/
void CXRcdAnalysisTool::OpenRcdAnalysisFile(const CString &strFile)
{
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
}

void CXRcdAnalysisTool::InitAfterRead()
{
	if (m_strID != _T("RcdAnalysis"))
	{
		return;
	}

	m_strRcdAnalysisID.Empty();
	m_strChID.Empty();
	m_fChValue = 0;
	m_pRcdAnalysis = (CDvmData *)FindByID(_T("RcdAnalysis"));
	m_pRcdDraw = (CDataGroup *)FindByID(_T("RcdDraw"));

	if (m_pRcdAnalysis != NULL)
	{
		m_strRcdAnalysisID = m_pRcdAnalysis->m_strValue;
		m_pRcdAnalysis->GetValueByID(_T("Channel"), m_strChID);
		m_pRcdAnalysis->GetValueByID(_T("ChValue"), m_fChValue);
	}

	if (m_pRcdDraw != NULL)
	{
		m_pRcdDraw->GetDataValue(_T("width"), m_nWidth);
		m_pRcdDraw->GetDataValue(_T("height"), m_nHeight);
	}
}

BOOL CXRcdAnalysisTool::RcdAnalysis(const CString &strComtradeFile)
{
	CRcdComtradeFile *pComtradeFile = CRcdComtradeFileMngr::OpenComtradeFile(strComtradeFile);
	BOOL bRet = RcdAnalysis(pComtradeFile);
	CRcdComtradeFileMngr::CloseComtradeFile(pComtradeFile);

	return bRet;
}

BOOL CXRcdAnalysisTool::RcdAnalysis(CRcdComtradeFile *pComtradeFile)
{
	if (m_strRcdAnalysisID == _T("RespTime"))
	{
		return RcdAnalysis_RespTime(pComtradeFile);
	}

	if (m_strRcdAnalysisID == _T("ChSyn"))
	{
		return RcdAnalysis_Sync(pComtradeFile);
	}

	return FALSE;
}


BOOL CXRcdAnalysisTool::RcdAnalysis_RespTime(CRcdComtradeFile *pComtradeFile)
{
	CXRcdCalRespConfig oConfig;
	oConfig.m_strChID = m_strChID;
	oConfig.m_fChValue = m_fChValue;

	CXRcdCalRespTime oRcdCal;
	oRcdCal.SetRcdComtradeFile(pComtradeFile);
	oRcdCal.Analysis(&oConfig);

	DvmDataset_to_Values(oRcdCal.GetResults(), &m_oResults);

	return TRUE;
}

BOOL CXRcdAnalysisTool::RcdAnalysis_Sync(CRcdComtradeFile *pComtradeFile)
{
	CXRcdCalRespConfig oConfig;
	oConfig.m_strChID = m_strChID;
	oConfig.m_fChValue = m_fChValue;

	CXRcdSyncAnalysis oRcdCal;
	oRcdCal.SetRcdComtradeFile(pComtradeFile);
	oRcdCal.Analysis(&oConfig);

	DvmDataset_to_Values(oRcdCal.GetResults(), &m_oResults);

	return TRUE;
}

