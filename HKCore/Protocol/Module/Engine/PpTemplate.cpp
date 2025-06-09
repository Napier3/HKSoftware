#include "StdAfx.h"
#include "PpTemplate.h"
#include "ProtocolXmlRWKeys.h"
#include "PpParsePackage.h"
#include "DeviceModel/CmmOnConnect.h"
#include "../../../Module/API/FileApi.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "CmmChannel/CmmGlobalDefine.h"
#include "../../../Module/System/TickCount32.h"
#include "../XLanguageResourcePp.h"

#include "ScriptFunc_Engine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CAutoCriticSection g_oDeviceBindListCriticSection;

CPpTemplate::CPpTemplate(void)
{
	Init();

	m_dwPkgEncodedSend = 0;
	m_dwPkgEncodedReceive = 0;

	m_bUseOwnDefDevice = FALSE;
	m_pByteBlockDataTypes = new CByteBlockDataTypes();
	m_pDataInterface = new CBbVariables(_T(""));

	m_nDeviceModeType = PPTEMPLATE_DEVICEMODE_SINGLE;
	m_nDatasetMode = PPTEMPLATE_DATASETMODE_TREE;
	m_nEngineVersion = 0;
	m_nSndOptr_Value = 100;
	m_bHasOnRecvProcedure = FALSE;

	m_nEncoding = XSTR_EncodingIdx_Auto;
	m_pProtoPkgPrcss = NULL;
}

CPpTemplate::~CPpTemplate(void)
{
	m_oListReportDataset.RemoveAll();
	m_listRPackage.RemoveAll();			//解析的报文帧临时链表
	m_listTPackage.RemoveAll();			//模板帧临时链表
	m_listWPackage.RemoveAll();			//制造帧临时链表

	if (m_pByteBlockDataTypes != NULL)
	{
		delete m_pByteBlockDataTypes;
		m_pByteBlockDataTypes = NULL;
	}

	if (m_pDataInterface != NULL)
	{
		delete m_pDataInterface;
		m_pDataInterface = NULL;
	}

	if (m_bUseOwnDefDevice)
	{
		if (m_pDevice != NULL)
		{
			delete m_pDevice;
			m_pDevice = NULL;
		}
	}

	if (m_pProtoPkgPrcss != NULL)
	{
		delete m_pProtoPkgPrcss;
		m_pProtoPkgPrcss = NULL;
	}
}

DWORD  CPpTemplate::GetCommMode()
{
	return pp_GetCommMode(m_strCommMode);
}

void  CPpTemplate::SetCommMode(DWORD dwCommMode)
{
	m_strCommMode = pp_GetCommMode(dwCommMode);
}

BOOL CPpTemplate::IsTemplateValid()
{
	if (m_pPackages == NULL || m_pProcedures == NULL)
	{
		return FALSE;
	}

// 	if (m_pPackages->GetCount() == 0)
// 	{
// 		return FALSE;
// 	}
// 
// 	if (m_pProcedures->GetCount() == 0)
// 	{
// 		return FALSE;
// 	}

	return TRUE;
}

void CPpTemplate::InitByteBlockDataTypes()
{
	ASSERT (m_pByteBlockDataTypes != NULL);

	if (m_pByteBlockDataTypes != NULL)
	{
		m_pByteBlockDataTypes->InitByTemplate(m_strPackageEncoded);
	}
}

void CPpTemplate::Init()
{
	m_pPackages = NULL;
	m_pProcedures = NULL;
	m_pInitProcedure = NULL;
	m_pOnlineProcedure = NULL;
	//m_pDataInterface = NULL;
	m_pCmmConfig = NULL;
#ifdef _PP_DEV_MODE_
	m_pPpPackageText = NULL;
	m_pPpPackageTexts = NULL;
#endif

	//m_pDvTemplate = NULL;    //设备数据模型定义模板
	//m_pDeviceModel = NULL;           //设备数据模型定义
	m_pCmmConfig = NULL;           //设备通讯配置
	m_pDevice = NULL;

	m_strName = g_sLangTxt_PrtcTempName/*_T("规约模板名称")*/;
	m_strID = _T("EpPpID");
	m_strPackageMinLength = _T("1");
	m_strPackageMaxLength = _T("1024");
	m_strPackageEncoded = g_strEncodeModeSend;
	m_strPkgEncodedLen = _T("1");
	m_strDefaultChannel = _T("tcp-client");
	m_strVersion = _T("1.0");
	m_strDeviceModel = _T("MonitorDeviceModel.xml");
}

long CPpTemplate::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CProtocolXmlRWKeys *pKey = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pKey->m_strPackageMaxLengthKey,oNode,m_nLength);
	xml_GetAttibuteValue(pKey->m_strPackageMaxLengthKey,oNode,m_strPackageMaxLength);
	xml_GetAttibuteValue(pKey->m_strPackageMinLengthKey,oNode,m_strPackageMinLength);
	xml_GetAttibuteValue(pKey->m_strDeviceModelKey,oNode,m_strDeviceModel);
	xml_GetAttibuteValue(pKey->m_strPackageEncodedKey,oNode,m_strPackageEncoded);
	xml_GetAttibuteValue(pKey->m_strPkgEncodedLenKey,oNode,m_strPkgEncodedLen);
	xml_GetAttibuteValue(pKey->m_strDefaultChannelKey,oNode,m_strDefaultChannel);	
	xml_GetAttibuteValue(pKey->m_strVersionKey,oNode,m_strVersion);
	xml_GetAttibuteValue(pKey->m_strDeviceFileForDebugKey,oNode,m_strDeviceFileForDebug);

#ifdef UNICODE
	m_nPackageMaxLength = _wtol(m_strPackageMaxLength);
	m_nPackageMinLength = _wtol(m_strPackageMinLength);
#else
    m_nPackageMaxLength = atol(m_strPackageMaxLength.GetString());
    m_nPackageMinLength = atol(m_strPackageMinLength.GetString());
#endif

	xml_GetAttibuteValue(pKey->m_strCommModeKey,oNode,m_strCommMode);

	//设备数据模型的模式
	xml_GetAttibuteValue(pKey->m_strDeviceModeTypeKey,oNode, m_nDeviceModeType);
	xml_GetAttibuteValue(pKey->m_strEngineVersionKey,oNode, m_nEngineVersion);
	xml_GetAttibuteValue(pKey->m_strDatasetModeKey,oNode, m_nDatasetMode);

// 	if (!xml_GetAttibuteValue(pKey->m_strLengthKey, oNode, m_nLength))
// 	{
// 		TRACE("\nGet RecordTestAttibuteValue-UI failed!\n");
// 	}
// 
// 	if (!xml_GetAttibuteValue(pKey->m_strDataTypeKey, oNode, m_strDataType))
// 	{
// 		TRACE("\nGet RecordTestAttibuteValue-UseGps failed!\n");
// 	}

	xml_GetAttibuteValue(pKey->m_strOnRecvProcedureKey,oNode, m_strOnRecvProcedure);
	xml_GetAttibuteValue(pKey->m_strSndOptr_GlobalVarKey,oNode, m_strSndOptr_GlobalVar);
	xml_GetAttibuteValue(pKey->m_strSndOptr_OptrKey,oNode, m_strSndOptr_Optr);
	xml_GetAttibuteValue(pKey->m_nSndOptr_ValueKey,oNode, m_nSndOptr_Value);
	xml_GetAttibuteValue(pKey->m_strScriptTypeKey,oNode, m_strScriptType);
	xml_GetAttibuteValue(pKey->m_strPkgFullRcvJdgIDKey,oNode, m_strPkgFullRcvJdgID);
	xml_GetAttibuteValue(pKey->m_strEncodingKey,oNode, m_strEncoding);

	CString strProtoPkgProcess;
	xml_GetAttibuteValue(pKey->m_strProtoPkgProcessKey,oNode, strProtoPkgProcess);
	InitProtoPkgProcess(strProtoPkgProcess);

	m_nEncoding = XSTR_Encoding_GetIdx(m_strEncoding);

	return 0;
}

long CPpTemplate::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElemen, pXmlRWKeys);
	CProtocolXmlRWKeys *pKey = (CProtocolXmlRWKeys*)pXmlRWKeys;

//	xml_SetAttributeValue(pKey->m_strPackageMaxLengthKey, oElemen, m_nLength);
	xml_SetAttributeValue(pKey->m_strPackageMaxLengthKey, oElemen, m_strPackageMaxLength);
	xml_SetAttributeValue(pKey->m_strPackageMinLengthKey, oElemen, m_strPackageMinLength);
	xml_SetAttributeValue(pKey->m_strDeviceModelKey, oElemen, m_strDeviceModel);
	xml_SetAttributeValue(pKey->m_strPackageEncodedKey, oElemen, m_strPackageEncoded);
	xml_SetAttributeValue(pKey->m_strPkgEncodedLenKey, oElemen, m_strPkgEncodedLen);
	xml_SetAttributeValue(pKey->m_strDefaultChannelKey, oElemen, m_strDefaultChannel);
	xml_SetAttributeValue(pKey->m_strVersionKey, oElemen, m_strVersion);	
	xml_SetAttributeValue(pKey->m_strDeviceFileForDebugKey, oElemen, m_strDeviceFileForDebug);	
	xml_SetAttributeValue(pKey->m_strCommModeKey, oElemen, m_strCommMode);	

	xml_SetAttributeValue(pKey->m_strDeviceModeTypeKey, oElemen, m_nDeviceModeType);
	xml_SetAttributeValue(pKey->m_strDatasetModeKey, oElemen, m_nDatasetMode);	

	long nEngineVersion = ENGINE_VERSION;
	xml_SetAttributeValue(pKey->m_strEngineVersionKey, oElemen, nEngineVersion);	

	xml_SetAttributeValue(pKey->m_strOnRecvProcedureKey, oElemen, m_strOnRecvProcedure);	
	xml_SetAttributeValue(pKey->m_strSndOptr_GlobalVarKey,oElemen, m_strSndOptr_GlobalVar);
	xml_SetAttributeValue(pKey->m_strSndOptr_OptrKey,oElemen, m_strSndOptr_Optr);
	xml_SetAttributeValue(pKey->m_nSndOptr_ValueKey,oElemen, m_nSndOptr_Value);
	xml_SetAttributeValue(pKey->m_strScriptTypeKey,oElemen, m_strScriptType);
	xml_SetAttributeValue(pKey->m_strPkgFullRcvJdgIDKey,oElemen, m_strPkgFullRcvJdgID);
	xml_SetAttributeValue(pKey->m_strEncodingKey,oElemen, m_strEncoding);
	xml_SetAttributeValue(pKey->m_strProtoPkgProcessKey,oElemen, m_strProtoPkgProcess);

	return 0;
}


long CPpTemplate::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}



CExBaseObject* CPpTemplate::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPackagesKey)
	{
		ASSERT (m_pPackages == NULL);
		m_pPackages = new CPpPackages();
		return m_pPackages;
	}
	else if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPpProceduresKey)
	{
		m_pProcedures = new CPpProcedures();
		return  m_pProcedures;
	}
	else if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDvDataTypesKey)
	{
		return new CDvDataTypes();
	}
	else if (strClassID == CDeviceModelXmlKeys::g_pXmlRWKeys->m_strCmmConfigKey)
	{
		m_pCmmConfig = new CDeviceCmmConfig;
		return  m_pCmmConfig;
	}
	else if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strInitProcedureRefsKey)
	{
		m_pInitProcedure = new CPpProcedureRefs;
		m_pInitProcedure->m_strXmlKey = strClassID;
		return  m_pInitProcedure;
	}
	else if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strOnlineProcedureRefsKey)
	{
		m_pOnlineProcedure = new CPpProcedureRefs;
		m_pOnlineProcedure->m_strXmlKey = strClassID;
		return  m_pOnlineProcedure;
	}

#ifdef _PP_DEV_MODE_
	else if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPackageTextKey)
	{
		m_pPpPackageText = new CPpPackageText();
		return  m_pPpPackageText;
	}
	else if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPackageTextKey)
	{
		m_pPpPackageTexts = new CPpPackageTexts();
		return  m_pPpPackageTexts;
	}
#endif

	return NULL;
}

CExBaseObject* CPpTemplate::CreateNewChild(long nClassID)
{

	return NULL;
}

long pp_Init_SndOptr_Optr(const CString &strSndOptr_Optr)
{
	long nSndOptr_Optr = 0;

	if (strSndOptr_Optr == _T(">"))
	{
		nSndOptr_Optr = 0;
	}
	else if (strSndOptr_Optr == _T("<"))
	{
		nSndOptr_Optr = 1;
	}
	else if (strSndOptr_Optr == _T(">="))
	{
		nSndOptr_Optr = 2;
	}
	else if (strSndOptr_Optr == _T("<="))
	{
		nSndOptr_Optr = 3;
	}
	else if (strSndOptr_Optr == _T("=="))
	{
		nSndOptr_Optr = 4;
	}
	else
	{
		nSndOptr_Optr = 0;
	}

	return nSndOptr_Optr;
}

void CPpTemplate::InitAfterRead()
{
	//建立解析帧临时链表	//建立制造帧临时链表	//建立模板帧临时链表
	if (m_pPackages == NULL)
	{
		return;
	}

	POS pos = m_pPackages->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = m_pPackages->GetNext(pos);
		nClassID = p->GetClassID();

		switch (nClassID)
		{
		case PPCLASSID_PPTTPACKAGE:
			m_listTPackage.AddTail((CPpPackage*)p);
			break;
		case PPCLASSID_PPPARSEPACKGE:
			m_listRPackage.AddTail((CPpPackage*)p);
			break;
		case PPCLASSID_PPPRODUCEPACKGE:
			m_listWPackage.AddTail((CPpPackage*)p);
			break;
#ifdef _PP_DEV_MODE_
		case PPCLASSID_PPPAKAGE_TEXT:
			m_pPpPackageText = (CPpPackageText*)p;
			break;
		case PPCLASSID_PPPAKAGE_TEXTS:
			m_pPpPackageTexts = (CPpPackageTexts*)p;
			break;
#endif
		default:
			ASSERT (FALSE);
			break;
		}
	}

	int iTPackageCount = m_listTPackage.GetCount();
	int iRPackageCount = m_listRPackage.GetCount();
	int iWPackageCount = m_listWPackage.GetCount();

	if (iTPackageCount>0 && iRPackageCount>0)
	{
		CPpTtPackage *pTtPackage;
		CPpParsePackage *pParsePackage;

		for (int iTPackageIndex=0; iTPackageIndex<iTPackageCount; iTPackageIndex++)
		{
			pTtPackage = (CPpTtPackage*)m_listTPackage.GetAt(iTPackageIndex);
			
			for (int iRPackageIndex=0; iRPackageIndex<iRPackageCount; iRPackageIndex++)
			{
				pParsePackage = (CPpParsePackage*)m_listRPackage.GetAt(iRPackageIndex);

				if (pParsePackage->m_strTID == pTtPackage->m_strID)
				{
					pParsePackage->m_pTtPackage = pTtPackage;
					pTtPackage->m_nParseRef++;
					pTtPackage->m_listPackages.AddTail(pParsePackage);
				}
			}
		}
	}

	if (iTPackageCount>0 && iWPackageCount>0)
	{
		CPpTtPackage *pTtPackage;
		CPpProducePackage *pProducePackage;
		for (int iTPackageIndex=0; iTPackageIndex<iTPackageCount; iTPackageIndex++)
		{
			pTtPackage = (CPpTtPackage*)m_listTPackage.GetAt(iTPackageIndex);
			for (int iWPackageIndex=0; iWPackageIndex<iWPackageCount; iWPackageIndex++)
			{
				pProducePackage = (CPpProducePackage*)m_listWPackage.GetAt(iWPackageIndex);
				if (pProducePackage->m_strTID == pTtPackage->m_strID)
				{
					pProducePackage->m_pTtPackage = pTtPackage;
					pTtPackage->m_listPackages.AddTail(pProducePackage);
				}
			}
		}
	}

	GetDeviceCmmConfig();
	InitCommConfig(m_pCmmConfig);


#ifdef _PP_DEV_MODE_
	if (m_pPpPackageTexts == NULL)
	{
		m_pPpPackageTexts = new CPpPackageTexts();
		AddNewChild(m_pPpPackageTexts);
	}

	if (m_pPpPackageText != NULL)
	{
		m_pPpPackageText->SetParent(m_pPpPackageTexts);
		m_pPpPackageTexts->AddHead(m_pPpPackageText);
		Remove(m_pPpPackageText);
	}

#endif

	m_nSndOptr_Optr = pp_Init_SndOptr_Optr(m_strSndOptr_Optr);

	if (m_pProcedures->FindByID(m_strOnRecvProcedure) != NULL)
	{
		m_bHasOnRecvProcedure = TRUE;
	}
}

DWORD CPpTemplate::RunProcedure(const CString &strProcedureID, CBbVariables *pDataInterface, BOOL bIsInit)
{
	return 0;
}

DWORD CPpTemplate::Parse(PACKAGEBUFFERPOS &oPkgBufPos, CPpPackageDetail* &pDetail)
{
	DWORD nResult = 0;

	CTickCount32 oTickCount32;
	oTickCount32.Enter();
	PACKAGEBUFFERPOS oPkgBufPosForMatch = oPkgBufPos;
	PACKAGEBUFFERPOS oPkgBufPosForParse = oPkgBufPos;

	// 首先匹配没有模板帧的解析帧
	CPpParsePackage *pPkg = NULL;
// 	if (pPkg != NULL)
// 	{
// 		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"匹配没有模板帧的解析帧:[%s][%s]", pPkg->m_strName, pPkg->m_strID);
// 		//解析报文帧，获取数据
// 		nResult = pPkg->Parse(oPkgBufPosForParse, pDetail);
// 	}
// 	else
	
	pPkg = MatchPackge(oPkgBufPosForMatch);
	//CPpTtPackage *pTPkg = MatchHeadAndTail(oPkgBufPosForMatch);

// 	if (pPkg == NULL)
// 	{//匹配报文头不成功，返回“没有帧”
// 		//return PpParseHasNoPackage();
// 		oPkgBufPosForMatch = oPkgBufPos;
// 		pPkg = MatchPackge(oPkgBufPosForMatch);
// 	}
// 	else
	if (pPkg == NULL)
	{
		CPpTtPackage *pTPkg = MatchHeadAndTail(oPkgBufPosForMatch);

		if (pTPkg != NULL)
		{
			if (!pTPkg->IsWholeMatch())
			{//报文帧不完整
				return PpParseNotWholeMatch();
			}

			if (pTPkg->m_listPackages.GetCount() > 0)
			{
				pPkg = (CPpParsePackage*)pTPkg->MatchPackge(oPkgBufPosForMatch);
			}

			if (pPkg == NULL)
			{
				oPkgBufPosForMatch = oPkgBufPos;
				pPkg = MatchPackge(oPkgBufPosForMatch);
			}
		}
	}	
	
	if (pPkg == NULL)
	{//没有定义的报文帧种类
		return PpParseNoDefinePackage();
	}

	if (pPkg->m_nRequiredLen > 0)
	{
		if (PpGetLengthFromCurr(oPkgBufPos) < pPkg->m_nRequiredLen)
		{
			return PpParseBufNotEnough();
		}
	}

	long nMatchLong = oTickCount32.GetTickCountLong(TRUE);

	//解析报文帧，获取数据
	nResult = pPkg->Parse(oPkgBufPosForParse, pDetail);

	//解析完报文，执行过程匹配
	if (!IsPpParseError(nResult))
	{
		oPkgBufPos = oPkgBufPosForParse;

/*
		if (g_bLogPackageInfor)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"[%s][%s][%dms+%dms] {[%d~%d][%d~%d][%d]}", pPkg->m_strName, pPkg->m_strID,nMatchLong, oTickCount32.GetTickCountLong()
				, oPkgBufPosForParse.nBuffer1BeginPos, oPkgBufPosForParse.nBuffer1EndPos
				, oPkgBufPosForParse.nBuffer2BeginPos, oPkgBufPosForParse.nBuffer2EndPos
				, oPkgBufPosForParse.nIndex);
		}
*/

	}
	else
	{
		if (g_bLogPackageInfor)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("[%s][%s] {[%d~%d][%d~%d][%d]} Error")
                , pPkg->m_strName.GetString(), pPkg->m_strID.GetString()
				, oPkgBufPosForParse.nBuffer1BeginPos, oPkgBufPosForParse.nBuffer1EndPos
				, oPkgBufPosForParse.nBuffer2BeginPos, oPkgBufPosForParse.nBuffer2EndPos
				, oPkgBufPosForParse.nIndex);
		}
	}

	return nResult;
}

DWORD CPpTemplate::Produce(const CString &strPackageID, PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)
{
	CPpProducePackage *pPkg  = (CPpProducePackage*)m_listWPackage.FindByID(strPackageID);
	if (pPkg == NULL)
	{
		return PpProduceError();
	}
	else
	{
		return pPkg->Produce(oPkgBufPos, pDetail);
	}
}

//规约模板执行		执行当前的过程
DWORD CPpTemplate::Run()
{
	return 0;
}

DWORD CPpTemplate::PkgEncoded(const CString &strEncodeMode)
{
	if (strEncodeMode == g_strEncodeModeDataTypeSendID)
	{
		m_dwPkgEncodedSend++;
		return m_dwPkgEncodedSend;
	}

	if (strEncodeMode == g_strEncodeModeDataTypeReceiveID)
	{
		m_dwPkgEncodedReceive++;
		return m_dwPkgEncodedReceive;
	}

	if (strEncodeMode == g_strEncodeModeDataTypeEncodeID)
	{
		m_dwPkgEncodedSend++;
		return m_dwPkgEncodedSend;
	}

	m_dwPkgEncodedSend++;

	return m_dwPkgEncodedSend;
}

//当前执行的过程		解析完成一个报文帧后，由此进行匹配
CPpTtPackage* CPpTemplate::MatchHeadAndTail(PACKAGEBUFFERPOS &oPkgBufPos)
{
	POS pos = m_listTPackage.GetHeadPosition();
	CPpTtPackage *p = NULL;
	CPpTtPackage *pMatch = NULL;
	DWORD nResult = 0;

	PACKAGEBUFFERPOS oPkgBufPosBk = oPkgBufPos;
	while (pos != NULL)
	{
		p = (CPpTtPackage*)m_listTPackage.GetNext(pos);

		if (p->m_nParseRef == 0)
		{
			continue;
		}

		nResult = p->MatchHeadAndTail(oPkgBufPos);

		if (IsPpParseMatch(nResult))
		{
			pMatch = p;
			break;
		}
		oPkgBufPos = oPkgBufPosBk;
	}

	return pMatch;
}

CPpParsePackage* CPpTemplate::MatchPackge(PACKAGEBUFFERPOS &oPkgBufPos)
{
	POS pos = m_listRPackage.GetHeadPosition();
	CPpParsePackage *p = NULL;
	CPpParsePackage *pMatch = NULL;
	long nResult = 0;

	PACKAGEBUFFERPOS oPkgBufPosBk = oPkgBufPos;

	while (pos != NULL)
	{
		p = (CPpParsePackage*)m_listRPackage.GetNext(pos);
		if (p->m_pTtPackage != NULL)
		{
			continue;
		}

		nResult = p->Match(oPkgBufPos);

		if (IsPpParseWholeMatch(nResult))
		{
			pMatch = p;
			break;
		}

		oPkgBufPos = oPkgBufPosBk;
	}

	return pMatch;
}


//////////////////////////////////////////////////////////////////////////
//
//帧的添加、删除
BOOL CPpTemplate::AddPackage(CPpPackage *pPackage)
{
	UINT nClassID = pPackage->GetClassID();
	BOOL bTrue = TRUE;

	switch(nClassID)
	{
	case PPCLASSID_PPPARSEPACKGE:
		m_listRPackage.AddTail(pPackage);
		break;
	case PPCLASSID_PPPRODUCEPACKGE:
		m_listWPackage.AddTail(pPackage);
		break;
	case PPCLASSID_PPTTPACKAGE:
		m_listTPackage.AddTail(pPackage);
		break;

	default:
		bTrue = FALSE;
		break;
	}

	if (bTrue)
	{
		m_pPackages->AddTail(pPackage);
	}

	return bTrue;
}

BOOL CPpTemplate::DeletePackage(CPpPackage *pPackage)
{
	UINT nClassID = pPackage->GetClassID();
	BOOL bTrue = TRUE;
	POS pos = NULL;

	switch(nClassID)
	{
	case PPCLASSID_PPPARSEPACKGE:
		pos = m_listRPackage.Find(pPackage);

		if (pos != NULL)
		{
			m_listRPackage.RemoveAt(pos);
		}

		break;
	case PPCLASSID_PPPRODUCEPACKGE:
		pos = m_listWPackage.Find(pPackage);

		if (pos != NULL)
		{
			m_listWPackage.RemoveAt(pos);
		}
	
		break;
	case PPCLASSID_PPTTPACKAGE:
		pos = m_listTPackage.Find(pPackage);

		if (pos != NULL)
		{
			m_listTPackage.RemoveAt(pos);
		}
		
		break;

	default:
		bTrue = FALSE;
		break;
	}

	if (bTrue)
	{
		pos = m_pPackages->Find(pPackage);

		if (pos != NULL)
		{
			m_pPackages->RemoveAt(pos);
		}
	}

	delete pPackage;

	return bTrue;
}

//过程的添加、删除
void CPpTemplate::AddProcedure(CPpProcedure *pProcedure)
{

}

void CPpTemplate::DeleteProcedure(CPpProcedure *pProcedure)
{

}

CPpPackage* CPpTemplate::FindPackagebyID(const CString &strPackageID)
{
	CPpPackage *pPackage = NULL;

	pPackage = (CPpPackage*)m_listTPackage.FindByID(strPackageID);
	if (pPackage != NULL)
	{
		return pPackage;
	}

	pPackage = (CPpPackage*)m_listRPackage.FindByID(strPackageID);

	if (pPackage != NULL)
	{
		return pPackage;
	}

	pPackage = (CPpPackage*)m_listWPackage.FindByID(strPackageID);

	return pPackage;
}

//
BOOL CPpTemplate::IsScriptType_LUA()
{
	return  !IsScriptType_XVM();
}

BOOL CPpTemplate::IsScriptType_XVM()
{
	return (m_strScriptType == PPSCRIPT_TYPE_XVM);
}

void CPpTemplate::SetScriptType_LUA()
{
	m_strScriptType = PPSCRIPT_TYPE_LUA;
}

void CPpTemplate::SetScriptType_XVM()
{
	m_strScriptType = PPSCRIPT_TYPE_XVM;
}

BOOL CPpTemplate::IsEncoding_UTF8()
{
	return m_nEncoding == XSTR_EncodingIdx_utf8;
}

BOOL CPpTemplate::IsEncoding_ASCII()
{
	return m_nEncoding == XSTR_EncodingIdx_Auto;
}

void CPpTemplate::SetEncoding_UTF8()
{
	m_nEncoding = XSTR_EncodingIdx_utf8;
}

void CPpTemplate::SetEncoding_ASCII()
{
	m_nEncoding = XSTR_EncodingIdx_Auto;
}

void CPpTemplate::SetEncoding(long nEncoding)
{
	m_nEncoding = nEncoding;

	switch (m_nEncoding)
	{
	case XSTR_EncodingIdx_Auto:
		m_strEncoding = _T("");
		break;
	case XSTR_EncodingIdx_utf8:
		m_strEncoding = XSTR_EncodingID_utf8;
		break;
	case XSTR_EncodingIdx_gb2312:
		m_strEncoding = XSTR_EncodingID_gb2312;
		break;
	default:
		m_strEncoding = _T("");
		break;
	}
}

//文件相关的接口
BOOL CPpTemplate::Open(const CString &strFile)
{
	return TRUE;
}

BOOL CPpTemplate::Save(const CString &strFile)
{
	return TRUE;
}

CString CPpTemplate::GetXvmTasmExeFile()
{
	CString strFile;
	strFile = m_strTemplateFile;
	strFile = ChangeFilePostfix(strFile, PPSCRIPT_XVM_TASM_EXE);

	return strFile;
}

BOOL CPpTemplate::OpenXmlFile(const CString &strFile)
{
	m_strTemplateFile = strFile;

	m_listRPackage.RemoveAll();			//解析的报文帧临时链表
	m_listTPackage.RemoveAll();			//模板帧临时链表
	m_listWPackage.RemoveAll();			//制造帧临时链表

	DeleteAll();
	Init();

// 	MSXML2::IXMLDOMDocumentPtr docPtr = NULL;
// 	docPtr.CreateInstance(__uuidof(MSXML2::DOMDocument));
// 
// 	_variant_t varXml(strFile);
// 	_variant_t varOut((bool)TRUE);
// 	varOut = docPtr->load(varXml);
// 
// 	if((BOOL)varOut == FALSE)
// 	{
// 		//AfxMessageBox(L"打开XML文件失败或与XSD文件匹配失败！");
// 		return FALSE;
// 	}
// 
// 	MSXML2::IXMLDOMNodePtr oDocRoot = docPtr->GetdocumentElement();
// 	_bstr_t bstr = L"//";
// 	bstr += CProtocolXmlRWKeys::g_pXmlRWKeys->m_strTemplateKey;
// 
// 	MSXML2::IXMLDOMNodePtr oRoot = oDocRoot->selectSingleNode(bstr);
// 	ASSERT(oRoot != NULL);
// 
// 	if(oRoot == NULL)
// 	{
// 		//AfxMessageBox(L"打开XML文件失败！");
// 		return FALSE;
// 	}
// 
// 	XmlRead(oRoot,CProtocolXmlRWKeys::g_pXmlRWKeys);
	CBaseObject::OpenXmlFile(strFile, CProtocolXmlRWKeys::g_pXmlRWKeys);

	InitByteBlockDataTypes();
	InitPackageAllVariables();

	return TRUE;
}

BOOL CPpTemplate::SaveXmlFile(const CString &strFile)
{
	/*
		2010-12-06 添加
	*/
	InitTtPackageSystemVariables();
	ClearFileReadOnlyAttr(strFile);

// 	MSXML2::IXMLDOMDocumentPtr docPtr = NULL;
// 	docPtr.CreateInstance(__uuidof(MSXML2::DOMDocument));
// 
// 	//CProtocolXmlRWKeys::g_pXmlRWKeys->put_DocPtr(docPtr);
// 	XmlWrite(docPtr,NULL,CProtocolXmlRWKeys::g_pXmlRWKeys);
// 	BSTR strTemp = strFile.AllocSysString();
// 	docPtr->save(strTemp);
// 	::SysFreeString(strTemp);

	return CBaseObject::SaveXmlFile(strFile, CProtocolXmlRWKeys::g_pXmlRWKeys);
} 

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CPpTemplate::IsEqualOwn(CBaseObject* pObj)
{
	ASSERT (pObj == NULL);

	if (pObj == NULL)
	{
		return FALSE;
	}

	if (this == pObj)
	{
		return TRUE;
	}

	if (m_nLength != ((CPpTemplate*)pObj)->m_nLength)
	{
		return FALSE;
	}

	if (m_strVersion != ((CPpTemplate*)pObj)->m_strVersion)
	{
		return FALSE;
	}

	return CExBaseList::IsEqualOwn(pObj);
}

CBaseObject* CPpTemplate::Clone()
{
	CPpTemplate* pNew = new CPpTemplate();
	Copy(pNew);
	return pNew;
}

BOOL CPpTemplate::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CPpTemplate*)pDest)->m_nLength = m_nLength;
	((CPpTemplate*)pDest)->m_strVersion = m_strVersion;

	return CExBaseList::CopyOwn(pDest);
}

/*
2010-12-06 添加
*/
BOOL CPpTemplate::InitSystemVariableDataType(/*CPpDeviceModelDefine* pDeviceModelDefine*/)
{
// 	m_listSystemVariableDataType.DeleteAll();
// 
// 	m_listSystemVariableDataType.AddNew(g_strVariableDataTypeCPUName, g_strVariableDataTypeCPUID);
// 	m_listSystemVariableDataType.AddNew(g_strVariableDataTypeGROUPName, g_strVariableDataTypeGROUPID);
// 	m_listSystemVariableDataType.AddNew(g_strVariableDataTypeItemIndexName, g_strVariableDataTypeItemIndexID);
// 	m_listSystemVariableDataType.AddNew(g_strVariableDataTypeDeviceAddrName, g_strVariableDataTypeDeviceAddrID);

	return TRUE;
}

BOOL CPpTemplate::InitTtPackageSystemVariables()
{
	//遍历所有模板帧
	if(m_pPackages == NULL)
	{
		return FALSE;
	}

	POS pos = m_pPackages->GetHeadPosition();

	while(pos != NULL)
	{
		CExBaseObject* pObj = m_pPackages->GetNext(pos);

		if(pObj->GetClassID() == PPCLASSID_PPTTPACKAGE)
		{
			CPpTtPackage* pTtPkg = (CPpTtPackage*)pObj;
			//pTtPkg->AddSystemVariables();
		}
	}

	return TRUE;
}


void CPpTemplate::SetDevice(CPpDvmDevice *pDevice)
{
	if (m_bUseOwnDefDevice)
	{
		m_bUseOwnDefDevice = FALSE;
	}

	if (pDevice == NULL)
	{
		m_bUseOwnDefDevice = TRUE;
		CDevcieModel *p = new CDevcieModel();
		CString strFile( _P_GetConfigPath() );
		strFile += m_strDeviceFileForDebug;
		p->OpenFile(strFile);
		m_pDevice = p->GetPpDevice();

		if (m_pDevice != NULL)
		{
			POS pos = p->Find(m_pDevice);
			p->RemoveAt(pos);
			delete p;
		}		
	}
	else
	{
		m_pDevice = pDevice;
	}

	if (m_nDeviceModeType != m_pDevice->m_nDvmDeviceMode)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE
           , g_sLangTxt_PrtcTempDiff.GetString()/*_T("规约模板的模型模式【%s】与点表文件的模型模式【%s】不一致")*/
            , pp_GetDeviceModeModeString(m_nDeviceModeType).GetString()
            , pp_GetDeviceModeModeString(m_pDevice->m_nDvmDeviceMode).GetString());
	}

	if (m_pPackages == NULL)
	{
		return;
	}

	POS pos = m_pPackages->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = m_pPackages->GetNext(pos);
		UINT nClassID = p->GetClassID();

		if (nClassID == PPCLASSID_PPPARSEPACKGE || nClassID == PPCLASSID_PPPRODUCEPACKGE)
		{
			CPpPackage *pPkg = (CPpPackage*)p;
			CDataQueryBindStatck *pStack = pPkg->GetDataQueryBindStatck();
			pStack->m_pDevice = pDevice;
			pStack->m_nDatasetMode = m_nDatasetMode;
		}
	}

	//关联设备数据模型定义对象
	InitPpDeviceDefine();
}

CExBaseList* CPpTemplate::GetDevice()
{		
	return m_pDevice->GetDeviceModel();	
}

void CPpTemplate::InitPpDeviceDefine()
{
// 	if (m_pDeviceModel != NULL)
// 	{
// 		delete m_pDeviceModel;
// 		m_pDeviceModel = NULL;
// 	}
// 
// 	CPpDeviceModelDefine oDeviceModelDefine;
// 	CString strFile;
// 	strFile = _P_GetConfigPath();
// 	strFile += m_pDevice->m_strTemplateFile;
// 	oDeviceModelDefine.OpenXmlFile(strFile);
// 
// 	m_pDeviceModel = oDeviceModelDefine.m_pDeviceModel;
// 	POS pos = oDeviceModelDefine.Find(m_pDeviceModel);
// 
// 	if (pos != NULL)
// 	{
// 		oDeviceModelDefine.RemoveAt(pos);
// 	}
// 
}

void CPpTemplate::InitPackageAllVariables()
{
	if (m_pPackages == NULL)
	{
		return;
	}

	m_pPackages->InitPackageAllVariables(PPCLASSID_PPTTPACKAGE);
	m_pPackages->InitPackageAllVariables(PPCLASSID_PPPARSEPACKGE);
	m_pPackages->InitPackageAllVariables(PPCLASSID_PPPRODUCEPACKGE);
}

void CPpTemplate::InitCommConfig(CExBaseList *pCmmList)
{
	POS pos = pCmmList->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pCmmList->GetNext(pos);

		if (p->GetClassID() == DMCLASSID_CMM_ONCONNECT)
		{
			CCmmOnConnect *pOnConnect = (CCmmOnConnect*)p;
			CExBaseObject *pFind = m_pProcedures->FindByID(pOnConnect->m_strText);

			if (pFind != NULL)
			{
				pOnConnect->m_strName = pFind->m_strName;
				pOnConnect->m_strID = pFind->m_strID;
			}
			else
			{
				pOnConnect->m_strName = pOnConnect->m_strText + _T(" - Error - ");
				pOnConnect->m_strID = pOnConnect->m_strText;
			}
		}
		else if(p->IsBaseList())
		{
			InitCommConfig((CExBaseList*)p);
		}
	}
}

CString Pp_MakeFirstCharUpper(const CString& str)
{
	CString strRet(_T(""));

	if(str.GetLength() <= 1)
	{
		return strRet;
	}

	CString strTemp = str.Mid(1,str.GetLength()-1);
	CString strFirst = str.Left(1);
	strTemp.MakeLower();
	strFirst.MakeUpper();

	strRet = strFirst + strTemp;

	return strRet;
}

BOOL Pp_GetSystemVariableByNodeTypes(CString& retString,const CString& strAddToHead,
	const CString& strAddToTail,const CString& strInputString,const CString& strMatch,BOOL bNeedMatch)
{
	//首先将strInputString的首字母大写,其他字母小写
	CString strInputStringEx = Pp_MakeFirstCharUpper(strInputString);

	if(bNeedMatch)
	{
		//如果需要查找匹配字符串 strMatch
		CString strFind;
		int nFind = strInputString.Find(strMatch);
		if(nFind == -1 || nFind == 0)
		{
			return FALSE;
		}
		
		CString strTemp;
		strTemp = strInputStringEx.Left(nFind);
		retString = strAddToHead + strTemp + strAddToTail;
	}
	else
	{
		retString = strAddToHead + strInputStringEx + strAddToTail;
	}

	return TRUE;
}

BOOL CPpTemplate::SetPackageVariableByID(const CString &strPackageID,const CString& strVariableID,const CString& strValue)
{
	CExBaseObject* pObj = FindPackagebyID(strPackageID);
	CBbVariable* pVar = NULL;

	if (pObj == NULL)
	{
		return FALSE;
	}
	if (pObj->GetClassID() == PPCLASSID_PPTTPACKAGE)
	{
		pVar = ((CPpTtPackage*)pObj)->FindVariableByID(strVariableID);
	}
	else
	{
		pVar = ((CPpPackage*)pObj)->FindVariableByID(strVariableID);
	}

	if (pVar == NULL)
	{
		return FALSE;
	}

	pVar->m_strValue = strValue;
	return TRUE;
}

CString CPpTemplate::GetDeviceFileForDebug()
{
	if (m_strDeviceFileForDebug.GetLength() < 4)
	{
		m_strDeviceFileForDebug = m_strID + _T(".xml");
	}

	return m_strDeviceFileForDebug;
}

CString CPpTemplate::GetDeviceFilePathForDebug()
{
	CString strLibPath, strPath;
	strLibPath = _P_GetLibraryPath();
	CString strFileDebug = GetDeviceFileForDebug();

	GetPathFromRelative(strLibPath, strFileDebug, strPath);
	
	return strPath;
}

void CPpTemplate::RegisterReport(const CString &strDatasetPath)
{
	ASSERT (m_pDevice != NULL);

	if (m_pDevice == NULL)
	{
		return;
	}

	CAutoSimpleLock oLock(g_oDeviceBindListCriticSection);
	CDvmDataset *pDataset = (CDvmDataset*)m_pDevice->SelectData(strDatasetPath);

	if (pDataset->GetClassID() == DVMCLASSID_CDVMDATASET)
	{
		m_oListReportDataset.AddTail(pDataset);
	}
}

void CPpTemplate::UnRegisterReport(const CString &strDatasetPath)
{
	ASSERT (m_pDevice != NULL);

	if (m_pDevice == NULL)
	{
		return;
	}

	CAutoSimpleLock oLock(g_oDeviceBindListCriticSection);
	CDvmDataset *pDataset = (CDvmDataset*)m_pDevice->SelectData(strDatasetPath);

	if (pDataset->GetClassID() == DVMCLASSID_CDVMDATASET)
	{
		m_oListReportDataset.Remove(pDataset);
	}
}

void CPpTemplate::RegisterReport(CDvmDataset *pDataset)
{
	CAutoSimpleLock oLock(g_oDeviceBindListCriticSection);

	if (m_oListReportDataset.Find(pDataset) == NULL)
	{
		m_oListReportDataset.AddTail(pDataset);
	}
}

void CPpTemplate::UnRegisterReport(CDvmDataset *pDataset)
{
	CAutoSimpleLock oLock(g_oDeviceBindListCriticSection);

	m_oListReportDataset.Remove(pDataset);
}


void CPpTemplate::ResetReport()
{
	ASSERT (m_pDevice != NULL);

	if (m_pDevice == NULL)
	{
		return;
	}

	CAutoSimpleLock oLock(g_oDeviceBindListCriticSection);
	CDvmLogicDevice *pLdevice = (CDvmLogicDevice*)m_pDevice->FindByID(g_strReportLogicDeviceID);

	if (pLdevice == NULL)
	{
		return;
	}

	POS pos = pLdevice->GetHeadPosition();
	CDvmDataset *pDataset = NULL;

	while (pos != NULL)
	{
		pDataset = (CDvmDataset *)pLdevice->GetNext(pos);
		pDataset->DeleteAll();
	}
}

BOOL CPpTemplate::IsDvmDataCanAddToReport(CDvmData *pData)
{
	POS pos = m_oListReportDataset.GetHeadPosition();
	BOOL bTrue = FALSE;
	CDvmDataset *pDataset = NULL;

	while (pos != NULL)
	{
		pDataset = (CDvmDataset *)m_oListReportDataset.GetNext(pos);

		if (pDataset == pData->GetParent())
		{
			bTrue = TRUE;
			break;
		}
	}

	return bTrue;
}

CXPkgFullRcvJdgInterface* CPpTemplate::GetXPkgFullRcvJdgInterface()
{
	return CXPkgFullRcvJdgTool::CreateXPkgFullRcvJdg(m_strPkgFullRcvJdgID);
}

BOOL CPpTemplate::CanRunWPackageOnReceive()
{//2019-5-27  lijq
	if (!m_bHasOnRecvProcedure)
	{
		return FALSE;
	}

	if (m_strSndOptr_GlobalVar.GetLength() < 1)
	{
		return TRUE;
	}

// 	char pszGlobalVar[MAX_PATH];
// 	CString_to_char(m_strSndOptr_GlobalVar, pszGlobalVar);
	long nValue = script_GetGlobalEx(m_strSndOptr_GlobalVar, this);

	if (m_nSndOptr_Optr == 0)
	{
		return nValue > m_nSndOptr_Value;
	}
	else if (m_nSndOptr_Optr == 1)
	{
		return nValue < m_nSndOptr_Value;
	}
	else if (m_nSndOptr_Optr == 2)
	{
		return nValue >= m_nSndOptr_Value;
	}
	else if (m_nSndOptr_Optr == 3)
	{
		return nValue <= m_nSndOptr_Value;
	}
	else if (m_nSndOptr_Optr == 4)
	{
		return nValue == m_nSndOptr_Value;
	}
	else
	{
		return nValue > m_nSndOptr_Value;
	}
}

//2023-1-27  lijunqing
void CPpTemplate::InitProtoPkgProcess(const CString &strPkgPrcssID)
{
	m_strProtoPkgProcess = strPkgPrcssID;

	if (m_pProtoPkgPrcss != NULL)
	{
		delete m_pProtoPkgPrcss;
		m_pProtoPkgPrcss = NULL;
	}

	char *pszPkgPrcssID = NULL;
	CString_to_char(strPkgPrcssID, &pszPkgPrcssID);
	m_pProtoPkgPrcss = pp_CreateProtoPkgProcess(pszPkgPrcssID);
	delete pszPkgPrcssID;
}

