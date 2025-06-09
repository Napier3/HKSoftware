#include "stdafx.h"
#include "Safety.h"
#include "CommCmd.h"

#include "../../../Module/MemBuffer/EquationBuffer.h"

#ifndef _PSX_QT_LINUX_		//yyj
#include "../../../Module/QRCode/XBarcodeEan13.h"
#include "../../../Module/QRCode/QRCodeRead.h"
#endif

#include "../XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


const CString CSafety::g_strQRCodeDataID = _T("QRCodeString");
const CString CSafety::g_strQRCodeFileID = _T("QRCodeFile");
const CString CSafety::g_strQRCodeFile = _T("QRCodeFile.png");
const CString CSafety::g_strEan13CodeFile = _T("QRCodeFile.bmp");

CShortDatas* CSafety::g_pQRCodeDatas = NULL;
long   CSafety::g_nQRCodeDatas = 0;

void CSafety::CreateQRCodeDatas()
{
	g_nQRCodeDatas++;

	if (g_nQRCodeDatas== 1)
	{
		g_pQRCodeDatas = new CShortDatas();
		AddQRCodeDatas(g_pQRCodeDatas);
	}
}

void CSafety::ReleaseQRCodeDatas()
{
	g_nQRCodeDatas--;

	if (g_nQRCodeDatas == 0)
	{
		delete g_pQRCodeDatas;
		g_pQRCodeDatas = NULL;
	}
}

CShortDatas* CSafety::GetQRCodeDatas()
{
	ASSERT (g_pQRCodeDatas != NULL);
	return g_pQRCodeDatas;
}

void CSafety::AddQRCodeDatas(CShortDatas *pDatas)
{
	CShortData *pData = NULL;
	pData = (CShortData*)pDatas->FindByID(g_strQRCodeDataID);

	if (pData == NULL)
	{
		pData = pDatas->AddNew();
		pData->m_strName = g_strQRCodeDataID;
		pData->m_strID = g_strQRCodeDataID;
	}

	//QRCode PNG file
	pData = (CShortData*)pDatas->FindByID(g_strQRCodeFileID);

	if (pData == NULL)
	{
		pData = pDatas->AddNew();
		pData->m_strName = g_strQRCodeFileID;
		pData->m_strID = g_strQRCodeFileID;
	}	
}

void CSafety::AddQRCodeValues(CValues *pValues)
{
	if (!IsSafetyDataModeQRCode())
	{
		return;
	}

	pValues->AddValue(g_strQRCodeDataID, m_strQRCodeData);
	pValues->AddValue(g_strQRCodeFileID, GetQRCodeFile());
}

BOOL CSafety::IsQRCode()
{
	return (m_strQRCodeData.GetLength() > 15);
}

CString CSafety::GetQRCodeFile()
{
	if (IsQRCode())
	{
		return g_strQRCodeFile;
	}
	else
	{
		return g_strEan13CodeFile;
	}
}

CSafety::CSafety()
{
	m_pScriptText = NULL;
	m_pStandard = NULL;
	m_pDatas = NULL;
	m_nDataMode = 0;
	m_pScriptText = NULL;
	m_pDllCall = NULL;
	m_nManyDeviceTestMode = GbMdItemTestMode_OneTime;
}

CSafety::~CSafety()
{
	m_oListMsgs.RemoveAll();
}

CGbItemBase* CSafety::CloneForTempFile()
{
	return new CSafety();
}


void  CSafety::InitDataMode()
{
	m_nDataMode = Gb_GetSafetyType(m_strType);
}

void  CSafety::InitDataModeType()
{
	m_strType = Gb_GetSafetyType(m_nDataMode);
}

BOOL CSafety::GetItemParaValue(const CString &strValueID, double &dValue)
{
	ASSERT (m_pDatas != NULL);

	CShortData  *pData = (CShortData*)m_pDatas->FindByID(strValueID);

	if (pData == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Item(%s[%s]) Para (%s) not exist"), m_strName.GetString(), m_strID.GetString(), strValueID.GetString());
	}
	else
	{
		CString strVal = pData->m_strValue;
		char *pString = NULL;
		CString_to_char(strVal, &pString);

		if (IsStringNumber(pString))
		{
			dValue = atof(pString);
		}
		else
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Item(%s[%s]) Para (%s) value(%s) is not number"), m_strName.GetString(), m_strID.GetString(), strValueID.GetString(), strVal.GetString());
		}

		delete pString;
	}


	return 0;
}

long CSafety::SetItemParaValue(const CString & strValueID, const CString & strValue, BOOL bAddNew)
{
	ASSERT (m_pDatas != NULL);

	CShortData  *pData = (CShortData*)m_pDatas->FindByID(CString(strValueID));

	if (pData == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Item(%s[%s]) Para (%s) not exist"), m_strName.GetString(),  m_strID.GetString(),  strValueID.GetString());
	}
	else
	{
		pData->m_strValue = strValue;
	}

	return 1;
}

CString CSafety::GetWaveFilePath()
{
	return Gb_GetWaveFilePath(m_strSoundFile);
}

BOOL CSafety::IsTypeDllCall(BOOL bValide)	
{	
	CDllCall* pDllCall = CreateDllCall()	;

	if (pDllCall == NULL)
	{
		return FALSE;
	}

	if (pDllCall->m_strID.GetLength() == 0)
	{
		return FALSE;
	}

	if (bValide)
	{
		return (pDllCall->IsDllPathValid());
	}
	else
	{
		return TRUE;
	}
}

//重写父类方法
long CSafety::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	//尚未完成
	//m_pDatas,m_oTable,m_pScriptText的处理
	CGbItemBase::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nDataMode);
		BinarySerializeCalLen(oBinaryBuffer, m_strSoundFile);
		BinarySerializeCalLen(oBinaryBuffer, m_nManyDeviceTestMode);
	}
	else if (oBinaryBuffer.IsReadMode())
	{	
		BinarySerializeRead(oBinaryBuffer,m_nDataMode);

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_1)
		{
			BinarySerializeRead(oBinaryBuffer,m_strSoundFile);
		}
		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_26)
		{
			BinarySerializeRead(oBinaryBuffer,m_nManyDeviceTestMode);
		}
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer,m_nDataMode);
		BinarySerializeWrite(oBinaryBuffer,m_strSoundFile);
		BinarySerializeWrite(oBinaryBuffer,m_nManyDeviceTestMode);
	}
	
	return 0;
}

long CSafety::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemBase::XmlReadOwn(oNode,pXmlRWKeys);

	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strTypeKey,oNode,m_strType);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strSoundFileKey,oNode,m_strSoundFile);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strManyDeviceTestModeKey,oNode,m_nManyDeviceTestMode);

	InitDataMode();

	return 0;
}

long CSafety::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemBase::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	if (g_bGbExportXmlReportFile)
	{
		if (CGuideBookExportConfig::g_pGuideBookExportConfig->m_nExportItemAttrSimplify)
		{
			return 0;
		}
	}

	if (g_bGbSaveGbStruDscFile)
	{
		return 0;
	}

	InitDataModeType();
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strTypeKey,oElement,m_strType);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strSoundFileKey,oElement,m_strSoundFile);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strManyDeviceTestModeKey,oElement,m_nManyDeviceTestMode);

	return 0;
}

CExBaseObject* CSafety::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strStandardKey)
	{
		m_pStandard = new CStandard();
		return m_pStandard;
	}
	else if(strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strScriptKey)
	{	
		m_pScriptText = new CScriptText();
		return m_pScriptText;
	}
	else if(strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strMsgKey)
	{
		CMsg* pMsg = new CMsg();
		return pMsg;
	}
	else if(strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strCShortDatasKey)
	{
		CShortDatas *pDatas = new CShortDatas();
		return pDatas;
	}
	else if(strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strDllCallKey)
	{
		m_pDllCall = new CDllCall();
		return m_pDllCall;
	}
	else if(strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strCommCmdKey)
	{
		CCommCmd* pCmd = new CCommCmd();
		return pCmd;
	}

	return CGbItemBase::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
}

CExBaseObject* CSafety::CreateNewChild(long nClassID)
{
	if(nClassID == GBCLASSID_STANDARD)
	{
		m_pStandard = new CStandard();
		return m_pStandard;
	}
	else if(nClassID == GBCLASSID_SCRIPTTEXT)
	{	
		m_pScriptText = new CScriptText();
		return m_pScriptText;
	}
	else if(nClassID == GBCLASSID_MSG)
	{
		CMsg* pMsg = new CMsg();
		return pMsg;
	}
	else if(nClassID == DTMCLASSID_CSHORTDATAS)
	{
		CShortDatas *pDatas = new CShortDatas();
		return pDatas;
	}
	else if(nClassID == GBCLASSID_DLLCALL)
	{
		m_pDllCall = new CDllCall();
		return m_pDllCall;
	}
	else if(nClassID == GBCLASSID_COMMCMD)
	{
		CCommCmd* pCmd = new CCommCmd();
		return pCmd;
	}

	return CGbItemBase::CreateNewChild(nClassID);
}

BOOL CSafety::IsEqual(CBaseObject* pObj)
{
	return FALSE;
}

//尚未完成
BOOL CSafety::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);

	if(pDesObj == this)
		return TRUE;

	CGbItemBase::CopyOwn(pDesObj);

	CSafety* pSafety = (CSafety*)pDesObj;
	pSafety->m_strType = m_strType;
	pSafety->m_nDataMode = m_nDataMode;
	pSafety->m_strSoundFile = m_strSoundFile;
	pSafety->m_nManyDeviceTestMode = m_nManyDeviceTestMode;

	return TRUE;
}

void CSafety::InitAfterRead()
{
	CGbItemBase::InitAfterRead();

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	m_oListMsgs.RemoveAll();
	long nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		switch (p->GetClassID())
		{
		case GBCLASSID_MSG:
			m_oListMsgs.AddTail(p);
			break;
		case GBCLASSID_STANDARD:
			m_pStandard = (CStandard*)p;
			break;
		case GBCLASSID_SCRIPTTEXT:
			m_pScriptText = (CScriptText*)p;
			break;
		case DTMCLASSID_CSHORTDATAS:
			m_pDatas = (CShortDatas*)p;
			break;
		case GBCLASSID_DLLCALL:
			m_pDllCall = (CDllCall*)p;
			break;

		case GBCLASSID_COMMCMD:
			m_oSubGbItems.AddTail(p);
			((CGbItemBase*)p)->m_bIsSubItem = TRUE;
			break;

		default:
			break;
		}
	}

	if (m_pDatas == NULL)
	{
		m_pDatas = new CShortDatas();
		AddNewChild(m_pDatas);
	}

	if (g_nGbCopyItemForMes == 1)
	{
		return;
	}

	if (m_pScriptText == NULL)
	{
		m_pScriptText = new CScriptText();
		AddNewChild(m_pScriptText);
	}


	if (m_pStandard == NULL)
	{
		m_pStandard = new CStandard();
		AddNewChild(m_pStandard);
	}
}


CBaseObject* CSafety::Clone()
{
	CSafety* pSafety = new CSafety();

	Copy(pSafety);

	return pSafety;
}


BOOL CSafety::CanPaste(UINT nClassID)
{
	if (nClassID == GBCLASSID_COMMCMD)
	{
		return TRUE;
	}

	return FALSE;
}

void CSafety::ReplaceSrciptText(CScriptText *pScript, UINT nScriptClassID, CGbItemBase *pSrcGbItem, BOOL bShowLog)
{
	if (nScriptClassID == GBCLASSID_SCRIPTTEXT)
	{
		pScript->CopyOwn(m_pScriptText);
		return;
	}

	CGbItemBase::ReplaceSrciptText(pScript, nScriptClassID, pSrcGbItem, bShowLog);
}

CString CSafety::GetQRCodePngFile()
{
	CString strFile;

	strFile = _P_GetBinPath();
	strFile += GetQRCodeFile();

	return strFile;
}



void CSafety::WriteQRCodePngFile()
{
	if (m_strQRCodeData.GetLength() < 5)
	{
		return;
	}

#ifndef guidebook_report_dev_mode
	CString strFile;
	strFile = GetQRCodePngFile();

	//条形码
	if (!IsQRCode())
	{
		CString strQRCode = m_strQRCodeData.Left(12);
#ifndef _PSX_QT_LINUX_  //yyj
		xena_WriteXEna13File(strFile, strQRCode);
#endif
		return;
	}

	char *pszQRData = NULL;
	char pszPngFile[MAX_PATH];

	CString_to_char(m_strQRCodeData, &pszQRData);
	CString_to_char(strFile, (char*)pszPngFile);
#ifndef _PSX_QT_LINUX_  //yyj
	QR_WriteQRCodePngFile(pszQRData, pszPngFile);
#endif
	delete pszQRData;

#endif
}

void CSafety::ParseBarCode(const char *pBuffer, char chSeparateChar, char chSeparateEndChar)
{
	long nBarCodeLen = strlen (pBuffer);
	CShortData *pData = NULL;

	if (nBarCodeLen <= 13)
	{
		pData = (CShortData*)m_pDatas->GetHead();

		if (pData != NULL)
		{
			pData->m_strValue = pBuffer;
		}

		return;
	}

	CEquationBuffer oBuffer;
	oBuffer.SetSeparateChar(chSeparateChar);
	oBuffer.SetSeparateEndChar(chSeparateEndChar);
	oBuffer.InitBuffer(pBuffer, pBuffer + nBarCodeLen);

	POS pos = m_pDatas->GetHeadPosition();
	long nIndex = 0;

	while (pos != NULL)
	{
		pData = (CShortData *)m_pDatas->GetNext(pos);
		pData->m_strValue.Empty();
		oBuffer.ParseString(pData->m_strName, pData->m_strValue);
	}
}

#ifdef GUIDEBOOK_DEV_MODE

void CSafety::GenerateDevReports()
{
	CReport* pReport = GetCurrReport();

	if (pReport == NULL)
	{
		pReport = AddReport(-1, -1);//2017.0518
	}

	pReport->m_pValues->DeleteAll();

	int nCount = pReport->m_pValues->GetCount();

	CValues* oValsTemp = NULL;

	CShortDatas  *pDatas = GetDatas();
	oValsTemp = pDatas->GetValues();
	Gb_AddResultJudgeKey(oValsTemp,0);
	pReport->m_pValues->Append(oValsTemp);
	oValsTemp->RemoveAll();
	delete oValsTemp;
}

 

#endif

void CSafety::DeleteAllDatas_DLL()
{
	CShortData *pData = NULL;
	POS pos = m_pDatas->GetHeadPosition();
	POS posPrev = NULL;

	while (pos != NULL)
	{
		posPrev = pos;
		pData = (CShortData *)m_pDatas->GetNext(pos);

		if (pData->m_strFormat == _T("dll"))
		{
			m_pDatas->RemoveAt(posPrev);
			delete pData;
		}
	}
}

void CSafety::AddDatas_DLL(CDvmData *pResults)
{
	POS pos = pResults->GetHeadPosition();
	CDvmValue *pValue = NULL;
	CShortData *pData = NULL;

	while (pos != NULL)
	{
		pValue = (CDvmValue *)pResults->GetNext(pos);
		pData = new CShortData();
		pData->m_strName = pValue->m_strName;
		pData->m_strID = pValue->m_strID;
		pData->m_strDataTypeID = pValue->m_strDataType;
		pData->m_strValue = pValue->m_strValue;
		m_pDatas->AddNewChild(pData);
		pData->m_strFormat = _T("dll");
	}
}

long CSafety::CalTestTimeLong()
{
	return 0;
}

//2021-3-28  lijunqing  根据数据集创建安全措施的数据对象
void CSafety::CreateSafetyDatasByDvmDataset(CDataSet *pDataSet, CValues *pAttrs,const CString &strDataType, const CString &strDataFormat, const CString &strDefValue)
{
	m_pDatas->DeleteAll();
	POS pos = pDataSet->GetHeadPosition();
	CDataObj *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDataObj *)pDataSet->GetNext(pos);

		if (!pData->IsAttrsMatch(pAttrs))
		{
			continue;
		}

		m_pDatas->AddNew2(pData->m_strName, pData->m_strID, pData->m_strUnit, strDataType
			, strDefValue, 0, strDataFormat, _T(""));
	}
}

//shaolei 20220607
void CSafety::SetItemState(long nShow, long nEnable, long nSelect, BOOL bSetShow, BOOL bSetEnable, BOOL bSetSelect)
{
	CGbItemBase::SetItemState(nShow, nEnable, nSelect, bSetShow, bSetEnable, bSetSelect);

	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		//安全措施下的子项目类型，只有通讯命令项目
		if (nClassID != GBCLASSID_COMMCMD)
		{
			continue;
		}

		CCommCmd* pCmd = (CCommCmd *)pObj;
		//此处是否应当考虑，如果设置成1，子项目是不是不需要设置？
		pCmd->SetItemState(nShow, nEnable, nSelect, bSetShow, bSetEnable, bSetSelect);
	}
}


void CSafety::AddMsg(const CString &strID, const CString &strMsg)
{
	CMsg *pMsg = new CMsg();
	pMsg->m_strMsg = strMsg;
	pMsg->m_strID = strID;
	pMsg->m_strName = strID;
	m_oListMsgs.AddTail(pMsg);
	AddNewChild(pMsg, TRUE);
}

long CSafety::GetItemTestCount()
{
	CGbItemBase *pParent = (CGbItemBase *)GetParent();

	return pParent->GetItemTestCount();
}

void CSafety::ClearReport(BOOL bBack)
{
	CGbItemBase::ClearReport(bBack);

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if(p->GetClassID() == GBCLASSID_COMMCMD)
		{
			CCommCmd *pCommCmd = (CCommCmd*)p;
			pCommCmd->ClearReport(bBack);
		}
	}	
}

void CSafety::DeleteAllMsgs()
{
	m_oListMsgs.RemoveAll();
	POS pos = GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != GBCLASSID_MSG)
		{
			continue;
		}
		
		CMsg *pMsg = (CMsg *)pObj;
		Delete(pMsg);
	}
}