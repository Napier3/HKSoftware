// RecordTest.cpp: implementation of the CRecordTest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "RecordTest.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// const char *CRecordTest::g_pszKeyRecordTest = "record-test";
// const char *CRecordTest::g_pszKeyUI         = "ui";
// const char *CRecordTest::g_pszKeyUseGps	    = "use-gps";
// const char *CRecordTest::g_pszKeyType		= "type";
// const char *CRecordTest::g_pszKeyTypeConfig = "config";
// const char *CRecordTest::g_pszKeyTypeAuto	= "auto";
// const char *CRecordTest::g_pszKeyOnlineRecordMode = "onlinerecord-mode";
// const char *CRecordTest::g_pszKeySets		= "sets";
// const char *CRecordTest::g_pszKeyRTOnline	= "RtOnlineAuto";
// const char *CRecordTest::g_pszKeyRTOscillograph	= "RtOscillographAuto";


CRecordTest *g_pCurrRecordTest = NULL;

double* rt_GetValueRefByID(const CString &strID)
{
	if (strncmp(strID.GetString(), "Mutation", 8) == 0)
	{
		CString strTemp;
		strTemp = strID.Mid(9, strID.GetLength() - 10);
		return g_pCurrRecordTest->m_pVariables->GetMutationValueRefByID(strTemp);
	}
	else
	{
		return g_pCurrRecordTest->m_pVariables->GetValueRefByID(strID);
	}
}

CRecordTest::CRecordTest()
{
	m_bCalPointByPoint = TRUE;
	m_pWaveAnalyseViewRef = NULL;
	g_nSampleGap = 1;
	g_nSampleRate        = 100000;
	Analyse_Cal_Length = 2000;
	ZeroMemory(g_pZeroValue, sizeof(float)*MAX_MR1200_CHANNELS);
	ZeroMemory(g_pCoefValue, sizeof(float)*MAX_MR1200_CHANNELS);

	USE_RT_FILTER_BUFFER_LEN =  81;
	RT_FILTER_DATA_LEN_PREV = 40;
	RT_FILTER_DATA_LEN_NEXT = 40;
	RTATTRIBUTECAL_MIN_BUFFER_LEN   =    (7000+RT_FILTER_BUFFER_LEN); //20000
	MR1200_DFT_CAL_LEN = 2000;
	MR1200_SAMPLE_RATE = 100000;

	m_pVariables = NULL;
	m_pStartup = NULL;
	m_pMemBuffer = NULL;
	m_pSpy = NULL;
	m_pRtFileWrite = NULL;
	m_nUseGps = 0;
	m_pGpsBuffer = NULL;
	m_pRtAttrSpyConfigs =  NULL;
	m_pRtAttrSpyConfigs = CRtAttrSpyConfigs::CreategRtAttrSpyConfigs();

	m_nOnlineRecordMode = -1;//0表示没有在线录波，1表示试验用在线录波，2表示通用在线录波
	m_bTestUseOnlineRecord = FALSE;//试验在线录波模式下，在线录波是否使用
	
	m_pClone = NULL;
	m_strType = _T("auto");
}

CRecordTest::~CRecordTest()
{
	if (m_pRtAttrSpyConfigs != NULL) 
	{
		m_pRtAttrSpyConfigs->Release();
	}

	if (m_pClone != NULL)
	{
		delete m_pClone;
	}
}

void CRecordTest::Get_RECORD_CAL_LEN_PARA(RECORD_CAL_LEN_PARA *pCalLenPara)
{
	m_oRECORD_CAL_LEN_PARA.g_nSampleGap = g_nSampleGap;
	m_oRECORD_CAL_LEN_PARA.g_dwSampleRate = g_nSampleRate;

	m_oRECORD_CAL_LEN_PARA.Analyse_Cal_Length = Analyse_Cal_Length;// = 2000;

	m_oRECORD_CAL_LEN_PARA.USE_RT_FILTER_BUFFER_LEN = USE_RT_FILTER_BUFFER_LEN;// =  81;
	m_oRECORD_CAL_LEN_PARA.RT_FILTER_DATA_LEN_PREV = RT_FILTER_DATA_LEN_PREV;// = 40;
	m_oRECORD_CAL_LEN_PARA.RT_FILTER_DATA_LEN_NEXT = RT_FILTER_DATA_LEN_NEXT;// = 40;
	m_oRECORD_CAL_LEN_PARA.RTATTRIBUTECAL_MIN_BUFFER_LEN = RTATTRIBUTECAL_MIN_BUFFER_LEN;//   =    (7000+RT_FILTER_BUFFER_LEN); //20000

	*pCalLenPara = m_oRECORD_CAL_LEN_PARA;
}

void CRecordTest::init_RTATTRIBUTECAL_MIN_BUFFER_LEN()
{
	Analyse_Cal_Length = 2000;

	USE_RT_FILTER_BUFFER_LEN =  81;
	RT_FILTER_DATA_LEN_PREV = 40;
	RT_FILTER_DATA_LEN_NEXT = 40;
	RTATTRIBUTECAL_MIN_BUFFER_LEN   =    (7000+RT_FILTER_BUFFER_LEN);
}

void CRecordTest::init_RTATTRIBUTECAL_MIN_BUFFER_LEN(long nSamRate)
{
	MR1200_SAMPLE_RATE = nSamRate;

	if (nSamRate <= 1000)//1K
	{
		USE_RT_FILTER_BUFFER_LEN =  11;
		RT_FILTER_DATA_LEN_PREV = 5;
		RT_FILTER_DATA_LEN_NEXT = 5;
	}
	else if (nSamRate <= 10000)//10K
	{
		USE_RT_FILTER_BUFFER_LEN =  21;
		RT_FILTER_DATA_LEN_PREV = 10;
		RT_FILTER_DATA_LEN_NEXT = 10;
	}
	else if (nSamRate <= 100000)//100K
	{
		USE_RT_FILTER_BUFFER_LEN =  41;
		RT_FILTER_DATA_LEN_PREV = 20;
		RT_FILTER_DATA_LEN_NEXT = 20;
	}
	else
	{
		USE_RT_FILTER_BUFFER_LEN =  81;
		RT_FILTER_DATA_LEN_PREV = 40;
		RT_FILTER_DATA_LEN_NEXT = 40;
	}

	long nPointsOneCycle = rcd_CalCyclePoints(nSamRate, 50, TRUE);//nSamRate / 50;
	RTATTRIBUTECAL_MIN_BUFFER_LEN = nPointsOneCycle * 2 + USE_RT_FILTER_BUFFER_LEN;

	RTATTRIBUTECAL_MIN_BUFFER_LEN = nPointsOneCycle * 6 + USE_RT_FILTER_BUFFER_LEN;
	//2020-07-21  lijunqing DFT - 20Hz
	RTATTRIBUTECAL_MIN_BUFFER_LEN = RT_FREQUENCY_CAL_LEN + USE_RT_FILTER_BUFFER_LEN;
	Analyse_Cal_Length = nPointsOneCycle;// *2 / 5;
	MR1200_DFT_CAL_LEN = nPointsOneCycle;//nSamRate / 50;
}

long CRecordTest::FindCoefAndZero(CExBaseObject *pRtVariable, double &dCoef, double &dZero)
{
	long nIndex = m_pVariables->FindIndex(pRtVariable);

	if (nIndex < 0)
	{
		return 0;
	}

	dCoef = g_pCoefValue[nIndex];
	dZero = g_pZeroValue[nIndex];

	return nIndex;
}

long CRecordTest::FindCoefAndZero(CExBaseObject *pRtVariable, double **ppdCoef, double **ppdZero)
{
	long nIndex = m_pVariables->FindIndex(pRtVariable);

	if (nIndex < 0)
	{
		return nIndex;
	}

	*ppdCoef = &g_pCoefValue[nIndex];
	*ppdZero = &g_pZeroValue[nIndex];

	return nIndex;
}

// 
// //重载的方法
// long CRecordTest::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
// {
// 	CExBaseList::ReadOwnXml(oNode);
// 
// 	if (!xml_GetAttibuteValue(g_pszKeyUI, oNode, m_strUI))
// 	{
// 		debug_trace("\nGet RecordTestAttibuteValue-UI failed!\n");
// 	}
// 
// 	if (!xml_GetAttibuteValue(g_pszKeyUseGps, oNode, m_nUseGps))
// 	{
// 		debug_trace("\nGet RecordTestAttibuteValue-UseGps failed!\n");
// 	}
// 
// 	if (!xml_GetAttibuteValue(g_pszKeyType, oNode, m_strType))
// 	{
// 		debug_trace("\nGet RecordTestAttibuteValue-Type failed!\n");
// 	}
// 	
// 	CString str;
// 	xml_GetAttibuteValue(g_pszKeyOnlineRecordMode, oNode, str);
// 
// 	if (_stricmp(str, "none") == 0)
// 	{
// 		m_nOnlineRecordMode = RecordTest_Mode_NoneWithOnlineRecord;
// 	}
// 	else if (_stricmp(str, "test") == 0)
// 	{
// 		m_nOnlineRecordMode = RecordTest_Mode_TestUseOnlineRecord;
// 	}
// 	else if (_stricmp(str, "common") == 0)
// 	{
// 		m_nOnlineRecordMode = RecordTest_Mode_CommonOnlineRecord;
// 	}
// 	else if(_stricmp(str, "oscillogragh") == 0)
// 	{
// 		m_nOnlineRecordMode = RecordTest_Mode_OscillographOnlineRecord;
// 	}
// 	else
// 	{
// 	}
// 
// 	return 0;
// }
// 
// CExBaseObject* CRecordTest::CreateNewChild(LPCTSTR pszClassID)
// {
// 	CExBaseObject *pNew = NULL;
// 	
// 	if (strcmp(CRtStartup::g_pszKeyStartup, pszClassID) == 0)
// 	{
// 		if (m_pStartup == NULL)
// 		{
// 			pNew = new CRtStartup();
// 			m_pStartup =(CRtStartup*) pNew;
// 		}
// 	}
// 	else if (strcmp(CRtBufferConfig::g_pszKeyRtBuffer, pszClassID) == 0)
// 	{
// 		if (m_pMemBuffer == NULL)
// 		{
// 			pNew = new CRtBufferConfig();
// 			m_pMemBuffer =(CRtBufferConfig*) pNew;
// 		}
// 	}
// 	else if (strcmp(CRtFileWrite::g_pszKeyFileWrite, pszClassID) == 0)
// 	{
// 		if (m_pRtFileWrite == NULL)
// 		{
// 			pNew = new CRtFileWrite();
// 			m_pRtFileWrite = (CRtFileWrite*)pNew;
// 		}
// 	}
// 	else if (strcmp(CRtVariables::g_pszKeyVariables, pszClassID) == 0)
// 	{
// 		if (m_pVariables == NULL)
// 		{
// 			pNew = new CRtVariables();
// 			m_pVariables = (CRtVariables*)pNew;
// 		}
// 	}
// 	else if (strcmp(CRtSpy::g_pszKeySpy, pszClassID) == 0)
// 	{
// 		if (m_pSpy == NULL)
// 		{
// 			pNew = new CRtSpy();
// 			m_pSpy = (CRtSpy*)pNew;
// 		}
// 	}
// 	else
// 	{
// 		debug_trace("CRecordTest Create New Child failed!");
// 		pNew = NULL;
// 	}
// 	
// 	return pNew;
// }
// 
// const char* CRecordTest::GetXmlElementKey()
// {
// 	return g_pszKeyRecordTest;
// }
// 
// long CRecordTest::WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement)
// {
// 	CExBaseList::WriteOwnXml(oXMLDoc, oElement);
// 
// 	if (m_strUI.GetLength() > 0)
// 	{
// 		oElement->setAttribute(_bstr_t(g_pszKeyUI), _bstr_t(m_strUI));
// 	}
// 	return 0;
// }
// 
// //试验相关的试验
// BOOL CRecordTest::ReadSetsValueXml(MSXML::IXMLDOMNodeListPtr &oNodes)
// {
// 	int nCount = oNodes->Getlength();
// 	MSXML::IXMLDOMNodePtr oNode = NULL;
// 	CString strNodeName, strTestName;
//  	
// 	for (int nIndex=0; nIndex < nCount; nIndex++)
// 	{
// 		oNode = oNodes->Getitem(nIndex);
// 		strNodeName = (char *)oNode->GetnodeName();
// 
// 		if (strcmp(g_pszKeyRecordTest, strNodeName) == 0)
// 		{
// 			xml_GetAttibuteValue(_bstr_t(g_pszKeyName), oNode, strTestName);
// 
// 			if (strcmp(m_strName, strTestName) != 0)
// 			{
// 				break;
// 			}
// 		}
// 		
// 		if (strcmp(CRtVariables::g_pszKeyVariables, strNodeName) == 0)
// 		{
// 			MSXML::IXMLDOMNodeListPtr &oChildNodes = oNode->GetchildNodes();
// 		
// 			if (m_pVariables != NULL)
// 			{
// 				m_pVariables->ReadSetsValueXml(oChildNodes);
// 			}
// 		}
// 
// 		if (strcmp(CRtStartup::g_pszKeyStartup, strNodeName) == 0)
// 		{			
// 			if (m_pStartup != NULL)
// 			{
// 				m_pStartup->ReadSetsValueXml(oNode);
// 			}
// 		}
// 
// 		if (strcmp(CRtBufferConfig::g_pszKeyRtBuffer, strNodeName) == 0)
// 		{			
// 			if (m_pMemBuffer != NULL)
// 			{
// 				m_pMemBuffer->ReadSetsValueXml(oNode);
// 			}
// 		}
// 
// 	}
// 	
// 	return TRUE;
// }
// 
// BOOL CRecordTest::WriteSetsValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent)
// {
// 	MSXML::IXMLDOMElementPtr oRecordTest;
// 	oRecordTest = oXMLDoc->createElement(_bstr_t(g_pszKeyRecordTest));
// 	oRecordTest->setAttribute(_bstr_t(g_pszKeyName), _bstr_t(m_strName));
// 	oParent->appendChild(oRecordTest);
// 
// 	if (m_pVariables != NULL)
// 	{
// 		m_pVariables->WriteSetsValueXml(oXMLDoc, oParent);
// 	}
// 
// 	if (m_pStartup != NULL)
// 	{
// 		m_pStartup->WriteSetsValueXml(oXMLDoc, oParent);
// 	}
// 
// 	if (m_pMemBuffer != NULL)
// 	{
// 		m_pMemBuffer->WriteSetsValueXml(oXMLDoc, oParent);
// 	}
// 
// 	return TRUE;
// }

void CRecordTest::CalValues()
{
	ASSERT(m_pVariables != NULL);

	RECORD_CAL_LEN_PARA oCalLenPara;
	Get_RECORD_CAL_LEN_PARA(&oCalLenPara);
	m_pVariables->CalValuesRealTime(&oCalLenPara, g_nSampleGap, g_nSampleRate, m_bCalPointByPoint);

	//与启动相关的功能
	if (g_nRecordStartup > 0)
	{
		m_pStartup->InitStartUp(TRUE, g_nSampleRate);
	}
}

void CRecordTest::CalValuesEx()
{
	ASSERT(m_pVariables != NULL);

	RECORD_CAL_LEN_PARA oCalLenPara;
	Get_RECORD_CAL_LEN_PARA(&oCalLenPara);
	m_pVariables->CalValuesRealTimeEx(&oCalLenPara, g_nSampleGap, g_nSampleRate, m_bCalPointByPoint);
}

void CRecordTest::CalValues_PeakVellay(long nBeginPos, long nUseLength)
{
	RECORD_CAL_LEN_PARA oCalLenPara;
	Get_RECORD_CAL_LEN_PARA(&oCalLenPara);
	BOOL bRet = m_pVariables->CalValues_PeakVellay(&oCalLenPara, nBeginPos, nUseLength, g_nSampleRate, FALSE, TRUE);
}

BOOL CRecordTest::CalCurrValuesFromPos(long nBeginPos)
{
	RECORD_CAL_LEN_PARA oCalLenPara;
	Get_RECORD_CAL_LEN_PARA(&oCalLenPara);

	m_pVariables->SetAttrUse(SingleVariableAttrID_PeakValue, 1);
	m_pVariables->SetAttrUse(SingleVariableAttrID_VellayValue, 1);
	m_pVariables->SetAttrUse(SingleVariableAttrID_EffecValue, 1);//20221015 lmy

	BOOL bRet = m_pVariables->CalValues(&oCalLenPara, nBeginPos, g_nSampleRate, FALSE, TRUE);
	
	m_pVariables->SetAttrUse(SingleVariableAttrID_PeakValue, 1);
	m_pVariables->SetAttrUse(SingleVariableAttrID_VellayValue, 1);
	m_pVariables->SetAttrUse(SingleVariableAttrID_EffecValue, 1);//20221015 lmy

	return bRet;
}
// 
// BOOL CRecordTest::ReadRecordTestFromFile(const CString &strFile)
// {
// 	MSXML::IXMLDOMDocumentPtr oDoc = NULL;
// 	HRESULT hr = oDoc.CreateInstance(__uuidof(MSXML::DOMDocument));
// 	
// 	if(!SUCCEEDED(hr)) 
// 	{ 
// 		return FALSE;
// 	} 
// 	
// 	MSXML::IXMLDOMNodePtr oRecordTest = NULL;
// 	BSTR bstrFile = strFile.AllocSysString();
// 	BOOL bTrue = oDoc->load(bstrFile);
// 	::SysFreeString(bstrFile);
// 	
// 	if (!bTrue)
// 	{
// 		TRACE("\nRead RecordTest file failed......\n");
// 	}
// 	
// 	oRecordTest = oDoc->selectSingleNode(_bstr_t(g_pszKeyRecordTest));
// 	
// 	if (oRecordTest == NULL)
// 	{
// 		return FALSE;
// 	}
// 	
// 	g_pCurrRecordTest = this;  //用户选择试验之后，将g_pCurrRecordTest指向当前对象
// 
// 	ReadXml(oRecordTest);
// 	
// 	g_theRecordApp.CloneRecordTest();
// 	
// 	//调整静态属性:包括频率、有效值、相位、基波有效值、基波相位
// 	//if (!IsRecordTestAutofit())
// 	//{
// 	m_pVariables->AdjustStaticAttrs();
// 	//}
// 	
// 	//初始化缓冲区管理
// 	m_pVariables->InitBufferMngr();
// 
// //	m_pVariables->ResetUseAndSpy();
// 
// 	if (m_nUseGps)
// 	{//add GPS spy membuffer.....
// 		m_pGpsBuffer = CRtMemBufferMngr::AddMR1200GPSChannel(g_pszGPSChannelID, g_pszGPSBufferID);
// 		CMemBuffer_UShort* pBuffer = m_pGpsBuffer->GetSpyMemBuffer();
// 		g_theRecordApp.m_pMrGpsSysTime->AttachGPSBuffer(pBuffer);
// 	}
// 
// 	//初始化FIFOIndex
// 	m_pVariables->InitVariablesFIFOIndex();
// 
// 	return TRUE;
// }

void CRecordTest::InitDataAttributeCalFunc(BOOL bCalUseRecordBuffer)
{
	//初始化各数据属性对象数值计算参数
	m_pVariables->InitDataAttributeCalFunc(bCalUseRecordBuffer);
	
	//构建定值判启动表达式
	m_pVariables->BuildExpression();
	
	m_pStartup->ResetStartUp();
}

// BOOL CRecordTest::ReadRecordTestFromFile()
// {
// 	CString strFile;
// 	strFile.Format("%s%s.xml", _P_GetConfigPath(), m_strID);
// 	return ReadRecordTestFromFile(strFile);
// }
// 
// BOOL CRecordTest::WriteRecordTestToFile(const CString &strFile)
// {
// 	MSXML::IXMLDOMDocumentPtr oDoc; 
// 	MSXML::IXMLDOMElementPtr oRoot;
// 	
// 	try
// 	{
// 		//创建DOMDocument对象
// 		HRESULT hr = oDoc.CreateInstance(__uuidof(MSXML::DOMDocument));
// 		
// 		if(!SUCCEEDED(hr)) 
// 		{ 
// 			return FALSE;
// 		} 
// 		
// 		//根节点的名称为set-manager
// 		oDoc->raw_createElement((_bstr_t)(char*)g_pszKeyRecordTest, &oRoot);
// 		oDoc->raw_appendChild(oRoot, NULL);
// 		
// 		WriteXml(oDoc, oRoot);
// 		
// 		BSTR bstrFile = strFile.AllocSysString();
// 		oDoc->save(bstrFile);
// 		::SysFreeString(bstrFile);
// 	}
// 	catch (...)
// 	{
// 		return FALSE;
// 	}
// 
// 	return TRUE;
// }
// 
// BOOL CRecordTest::WriteRecordTestToFile()
// {
// 	CString strFile;
// 	strFile.Format("%s%s.xml", _P_GetConfigPath(), m_strID);
// 	return WriteRecordTestToFile(strFile);
// }


BOOL CRecordTest::IsRecordTestAutofit()
{
	return m_strType  == "auto";
}

void CRecordTest::AutofitCreateMultiVariable()
{
	if (!IsRecordTestAutofit())
	{
		return;
	}

	ASSERT(m_pVariables != NULL);
	m_pVariables->AutofitCreateMultiVariable();
}

void CRecordTest::AutofitCreateFileWrite()
{	
	if (m_pRtFileWrite == NULL)
	{
		m_pRtFileWrite = new CRtFileWrite();
		AddTail(m_pRtFileWrite);
		m_pRtFileWrite->SetParent(this);
	}

	ASSERT(m_pRtFileWrite != NULL);
	m_pRtFileWrite->AutofitCreateFileWrite(m_pVariables);
}

void CRecordTest::ValidateAttrCal()
{
	POS posVar = m_pVariables->GetHeadPosition();
	CRtVariable *pVar = NULL;
	CRtDataAttributes *pAttrs = NULL;
	CRtDataAttribute *pAttr = NULL;
	POS posAttr = NULL;
	long nHarmCalCount = 0;
	long nCalCount = 0;
	CString str;

	while (posVar != NULL)
	{
		pVar = (CRtVariable*)m_pVariables->GetNext(posVar);
		pAttrs = pVar->m_pDataAttrs;
		posAttr = pAttrs->GetHeadPosition();

		while (posAttr != NULL)
		{
			pAttr = (CRtDataAttribute*)pAttrs->GetNext(posAttr);

			if (pAttr->m_pAssociateAttr != NULL)
			{
				continue;
			}

			if(pAttr->IsHarmValueAttr() )
			{
				if (pAttr->GetSpyState() || pAttr->GetUse() )
				{
					nHarmCalCount++;
					
					if (nHarmCalCount > MAX_HARM_INDEX)
					{
						pAttr->SetSpyState(0);
						pAttr->SetUse(0);
					}
					else
					{
						nCalCount++;
					}
				}
				else
				{
				}
			}
			else
			{
				if (pAttr->GetSpyState() || pAttr->GetUse() )
				{
					nCalCount++;
				}
				else
				{
				}

			}
		}
	}
}

void CRecordTest::CloneRecordTest(CMemBuffer_UShort** pAttachBuffer, BOOL bCalUseRecordBuffer)
{
	if (m_pClone == NULL)
	{
		m_pClone = new CRecordTest;
		m_pClone->CloneRecordTest(this,pAttachBuffer, bCalUseRecordBuffer);
	}
}

void CRecordTest::CloneRecordTest(CRecordTest* pSrc,CMemBuffer_UShort** pAttachBuffer, BOOL bCalUseRecordBuffer)
{
	ASSERT (pSrc->m_pVariables != NULL);

	if (pSrc->m_pVariables == NULL)
	{
		return;
	}

	m_pVariables = new  CRtVariables();
	m_pVariables->SetParent(this);
	AddTail(m_pVariables);
	m_pVariables->CloneVariables(pSrc->m_pVariables,pAttachBuffer);
	m_pVariables->InitDataAttributeCalFunc(bCalUseRecordBuffer);
}

void CRecordTest::ResetSets(CSystemSetsConfig* pSetsConfig)
{	
	//重新设置录波时间和追忆时间
	if (m_pStartup != NULL)
	{
		m_pStartup->m_dTimeLookBack = pSetsConfig->m_dLookBackTime;
		m_pStartup->m_dTotalRecordTimeLen = pSetsConfig->m_dTotalRecordTime;
	}

	//重新设置采样率
	if (m_pMemBuffer != NULL)
	{
		g_nSampleGap = (unsigned short)pSetsConfig->m_nRecordGap;
		m_pMemBuffer->SetRecordGap(g_nSampleGap);	
		g_nSampleRate = (MR1200_SAMPLE_RATE / g_nSampleGap);
	}

	//重新设置通道定值
	if (m_pVariables != NULL)
	{
		POS pos  = m_pVariables->GetHeadPosition();

		while(pos != NULL)
		{
			CRtVariable* pVar = (CRtVariable*)m_pVariables->GetNext(pos);

			if (pVar != NULL)
			{
				//设置定值
				UINT nClassID = pVar->GetClassID();

				switch (nClassID)
				{
				case RTCLASSID_SINGLEVARIABLE:
					ResetSets((CRtSingleVariable*)pVar,pSetsConfig);
					break;
				case RTCLASSID_BINARYVARIABLE:
					ResetSets((CRtBinaryVariable*)pVar,pSetsConfig);
					break;
				case RTCLASSID_COMPLEXVARIABLE:
					ResetSets((CRtComplexVariable*)pVar,pSetsConfig);
					break;
				case RTCLASSID_MULTIVARIABLE:
					ResetSets((CRtMultiVariable*)pVar,pSetsConfig);
					break;
				}

			}
		}
	}
}

void CRecordTest::ResetSets(CRtSingleVariable* pVariable,CSystemSetsConfig* pSetsConfig)
{
	//先设置通道的使用
	pVariable->SetVariableUseState(pSetsConfig->m_nChannelUse);
	double dRange = pVariable->GetRange();

	ResetAnalogAttrsSets(pVariable->m_pDataAttrs,dRange,pSetsConfig);
}

//开关通道只需要设置通道的录波状态和属性的使用，没有定值
void CRecordTest::ResetSets(CRtBinaryVariable* pVariable,CSystemSetsConfig* pSetsConfig)
{
	//先设置通道的使用
	pVariable->SetVariableUseState(pSetsConfig->m_nChannelUse);
	
	CSystemSetAttr* pSystemAttr = NULL;
	CRtDataAttribute* pAttr = NULL;
	
	POS pos  = pVariable->m_pDataAttrs->GetHeadPosition();
	
	while(pos != NULL)
	{
		pAttr = (CRtDataAttribute*)pVariable->m_pDataAttrs->GetNext(pos);
		pSystemAttr = pSetsConfig->FindSystemSetAttrByID(pAttr->m_strID);
		
		if (pSystemAttr != NULL)
		{
			pAttr->SetUse(pSystemAttr->m_nAttrUse);	
		}
	}
}

void CRecordTest::ResetSets(CRtComplexVariable* pVariable,CSystemSetsConfig* pSetsConfig)
{	
	//先设置通道的使用
	pVariable->SetVariableUseState(pSetsConfig->m_nChannelUse);
	double dRange = Multi_Default_Range;
	
	ResetAnalogAttrsSets(pVariable->m_pDataAttrs,dRange,pSetsConfig);
}

void CRecordTest::ResetSets(CRtMultiVariable* pVariable,CSystemSetsConfig* pSetsConfig)
{
	//先设置通道的使用
	pVariable->SetVariableUseState(pSetsConfig->m_nChannelUse);
	double dRange = Multi_Default_Range;
	
	ResetAnalogAttrsSets(pVariable->m_pDataAttrs,dRange,pSetsConfig);
}


void CRecordTest::ResetAnalogAttrsSets(CRtDataAttributes* pAttrs,double dRange,CSystemSetsConfig* pSetsConfig)
{
	CSystemSetAttr* pSystemAttr = NULL;
	CRtDataAttribute* pAttr = NULL;
	double dAttrRange = dRange;

	POS pos  = pAttrs->GetHeadPosition();
	
	while(pos != NULL)
	{
		pAttr = (CRtDataAttribute*)pAttrs->GetNext(pos);
		pSystemAttr = pSetsConfig->FindSystemSetAttrByID(pAttr->m_strID);

		if (pAttr->m_nAttributeID == SingleVariableAttrID_Frequancy)
		{
			dAttrRange = g_nFrequencyNom;//频率
		}
		else if ((pAttr->m_nAttributeID == SingleVariableAttrID_EffecPhase) || 
				 (pAttr->m_nAttributeID == SingleVariableAttrID_FundPhase) || 
				 ((pAttr->m_nAttributeID >= SingleVariableAttrID_Harm02Phase) && (pAttr->m_nAttributeID < SingleVariableAttrID_Harm25Phase)))
		{
			dAttrRange = 180;//相位
		}
		else
		{
			dAttrRange = dRange;//幅值
		}

		if (pSystemAttr != NULL)
		{	
			ResetAnalogAttrSets(pAttr,dAttrRange,pSystemAttr);
		}
	}
}

void CRecordTest::ResetAnalogAttrSets(CRtDataAttribute* pAttr,double dRange,CSystemSetAttr* pConfig)
{
#ifdef _record_use_all_mode_
	ASSERT(pAttr != NULL);
	
	CRtSet* pSet = NULL;

	if (pAttr->m_pSets != NULL)
	{
		POS pos  = pAttr->m_pSets->GetHeadPosition();

		while(pos != NULL)
		{
			pSet = (CRtSet*)pAttr->m_pSets->GetNext(pos);
			ASSERT(pSet != NULL);
			
			switch (pSet->m_nSetType)
			{
			case SET_TYPE_HIGH:
				pSet->SetUse(pConfig->m_nHighUse);
				pSet->m_dValue = pConfig->m_dHighPercentValue * dRange;
				break;
			case SET_TYPE_LOW:
				pSet->SetUse(pConfig->m_nLowUse);
				pSet->m_dValue = pConfig->m_dLowPercentValue * dRange;
				break;
			case SET_TYPE_MUTATION:
				pSet->SetUse(pConfig->m_nMutationUse);
				pSet->m_dValue = pConfig->m_dMutationPercentValue * dRange;
				break;
			}

		}
	}

	pAttr->SetUse(pConfig->m_nAttrUse);
#endif
}


void CRecordTest::InitDrawControl()
{
	long nBinarys = 0;
	long nAnalogs = 0;
	long nIndex   = 0;

	if (m_pVariables == NULL)
	{
		return;
	}

	POS pos = m_pVariables->GetHeadPosition();
	CRtVariable* pVariable = NULL;
	PRECORDDRAWOBJECTCONTROL pDrawSet = NULL;

	while(pos != NULL)
	{
		pVariable = (CRtVariable*)m_pVariables->GetNext(pos);
		UINT nClassID = pVariable->GetClassID();

		if (nClassID == RTCLASSID_SINGLEVARIABLE)
		{
			pDrawSet = &(m_oMR1200SysAnalyseMngr.oDrawControl[nIndex]);
			pDrawSet->nUse = pVariable->GetVariableUseState();				
			pDrawSet->nShow = pDrawSet->nUse;
			pDrawSet->dRange = ((CRtSingleVariable*)pVariable)->GetRangeEx();
			pDrawSet->dRangeGrid = pDrawSet->dRange * 2;
			nAnalogs++;
			nIndex++;
		}
		else if (nClassID == RTCLASSID_BINARYVARIABLE)
		{
			pDrawSet = &(m_oMR1200SysAnalyseMngr.oDrawControl[nIndex]);
			pDrawSet->nUse = pVariable->GetVariableUseState();
			pDrawSet->nShow = 0;
			pDrawSet->dRange = 100;
			pDrawSet->dRangeGrid = pDrawSet->dRange * 2;
			nBinarys++;
			nIndex++;
		}
		else
		{
		}
	}

	m_oMR1200SysAnalyseMngr.nCurrDrawObjectCount = nIndex;
	InitMR1200SysAnalyseMngrDrawControl(m_oMR1200SysAnalyseMngr, nAnalogs,nBinarys);
}

void CRecordTest::InitBufferMngr()
{
	m_pVariables->InitBufferMngr(&m_oRtMemBufferMngr);
}

void CRecordTest::ResetValueCal()
{
	m_pVariables->ResetValueCal();
}
