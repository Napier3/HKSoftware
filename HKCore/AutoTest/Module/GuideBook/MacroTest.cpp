#include "stdafx.h"
#include "MacroTest.h"
#include "Safety.h"
#include "GuideBook.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#include "../../../Module/TestMacro/TestMacroInterface.h"

CMacroTest::CMacroTest()
{
	m_strType = _T("macrotest");
	m_nRepeatTimes = 1;   //shaolei  2023-4-15  ��Ϊ����Ϊ1����ΪGuideBookDev�д�����������Ŀʱ��Ĭ��Ϊ1����ʵ�����������ǲ��Դ��� 
	m_nReportFillUseNoRepeat = 0;
	m_pPara = NULL;
	m_nTestTimes = 0;
	m_pUiParas = NULL;
}

CMacroTest::~CMacroTest()
{
	m_oListMsgs.RemoveAll();
}

CGbItemBase* CMacroTest::CloneForTempFile()
{
	return new CMacroTest();
}

void CMacroTest::InitMacroID()
{
// 	CTestMacros *pMacros = Gb_GetMacrosPtr(this);
// 	CTestMacro  *pMacro = (CTestMacro*)pMacros->GetHead();
// 
// 	if (pMacro != NULL)
// 	{
// 		m_pPara->SetMacroID(pMacro->m_strID);
// 	}
	CItems *pItems = GetRsltExprScriptItems();

	if (pItems == NULL)
	{
		m_pPara->InitMacroID();
	}
	else
	{
		CItemsRsltExprScript *pRsltExpr = pItems->GetItemsRsltExprScript(FALSE);
		m_pPara->SetMacroID(pRsltExpr->m_strTestMacroID);
	}
}

BOOL CMacroTest::GetItemParaValue(const CString &strValueID, double &dValue)
{
	CValues* pValues;
	CValue *pVal = NULL;
	BOOL bTrue = FALSE;

	//2020-10-16  shaolei
#ifdef GUIDEBOOK_DEV_MODE
	m_pPara->InitTestParaDatas();
#endif

	pValues = m_pPara->GetParaValues();
	int nCount = pValues->GetCount();

	CString str;

	pVal = (CValue*)pValues->FindByID(strValueID);

	if (pVal != NULL)
	{
		bTrue = TRUE;
#ifdef _UNICODE
		dValue = _wtof(pVal->m_strValue);
#else
		dValue = atof(pVal->m_strValue.GetString());
#endif
	}
	else
	{
		//��ʾ�����ݲ�����
	}

	return bTrue;
}

long CMacroTest::SetItemParaValue(const CString & strValueID, const CString & strValue, BOOL bAddNew)
{
	CValues* pValues;
	CValue *pVal = NULL;
	BOOL bTrue = FALSE;

//2020-10-15  lijq 
#ifdef GUIDEBOOK_DEV_MODE
	m_pPara->InitTestParaDatas();
#endif

	pValues = m_pPara->GetParaValues();
	pVal = (CValue*)pValues->FindByID(strValueID);

	if (pVal != NULL)
	{
		bTrue = TRUE;
		pVal->m_strValue = strValue;
		pVal->m_dwReserved = 1;
	}
	else
	{
		if (bAddNew)
		{
			pVal = new CValue();
			bTrue = TRUE;
			pVal->m_strValue = strValue;
			pVal->m_strID = strValueID;
			pVal->m_dwReserved = 1;
			pValues->AddNewChild(pVal);
		}
		//��ʾ�����ݲ�����
	}

	return bTrue;
}

void GB_FinishTest_ActTime(CValue *pValue)
{
#ifdef _UNICODE
	double dVal = _wtof(pValue->m_strValue);
#else
	double dVal = atof(pValue->m_strValue.GetString());
#endif

	if (dVal <= 0.00001)
	{
		pValue->m_strValue = /*g_pszTripTimeDesc_NoTrip*/g_sLangTxt_Unact;
	}
	else
	{
		pValue->m_strValue = /*g_pszTripTimeDesc_Trip*/g_sLangTxt_Act;
	}
}

double GB_FinishTest_TtripTime(CValue *pValue, BOOL bIsAngle)
{
#ifdef _UNICODE
	double dVal = _wtof(pValue->m_strValue);
#else
	double dVal = atof(pValue->m_strValue.GetString());
#endif

	//����ǽǶȣ����ж�С��-360
	if (bIsAngle)
	{
		if (dVal < -360.0)
		{
			pValue->m_strValue = /*g_pszTripTimeDesc_NoTrip*/g_sLangTxt_Unact;
		}
	}
	else
	{
        if (dVal <= 0.00001)
		{
			pValue->m_strValue = /*g_pszTripTimeDesc_NoTrip*/g_sLangTxt_Unact;
		}
	}

	return dVal;
}

void GB_FinishTest_RsltDsc(CValue *pValue)
{
#ifdef _UNICODE
	double dVal = _wtof(pValue->m_strValue);
#else
    double dVal = atof(pValue->m_strValue.GetString());
#endif

	if (dVal <= 0.00001)
	{
		pValue->m_strValue = /*g_strResultDescValueIncorrect*/g_sLangTxt_Unqualified;
	}
	else
	{
		pValue->m_strValue = /*g_strResultDescValueCorrect*/g_sLangTxt_Qualified;
	}
}

void CMacroTest::AdjustReprtDatas()
{
	CValue *pVal = NULL;
	CValue *pActVal = NULL;
	CValues* oVals = NULL;
	CReport *pReport = GetReport(-1);

	if (pReport == NULL)
	{
		return;
	}

	oVals = pReport->m_pValues;
	POS pos = oVals->GetHeadPosition();
	CString strActID;
	CString strMacroID = GetTestMacroID();

	while (pos != NULL)
	{
		pVal = (CValue*)oVals->GetNext(pos);
		BOOL bIsAngle = FALSE;

		//if (pVal->m_strID.Find(g_pszTripTimeKey_Trip) >= 0)
		if (Gb_IsTripKeyID(pVal->m_strID, bIsAngle) && !Gb_IsErrKeyID(pVal->m_strID))
		{
			double dVal = GB_FinishTest_TtripTime(pVal, bIsAngle);
			strActID = Gb_GetActKeyIDByTripKeyID(pVal->m_strID);
			pActVal = (CValue *)oVals->FindByID(strActID);

			if (pActVal != NULL)
			{
				if (bIsAngle)
				{
					if (dVal > -360.0)
					{
						pActVal->m_strValue =/* g_pszTripTimeDesc_Trip*/g_sLangTxt_Act;
					}
					else
					{
						pActVal->m_strValue = /*g_pszTripTimeDesc_NoTrip*/g_sLangTxt_Unact;
					}
				}
				else
				{
					if (dVal > 0)
					{
						pActVal->m_strValue = /*g_pszTripTimeDesc_Trip*/g_sLangTxt_Act;
					}
					else
					{
						pActVal->m_strValue = /*g_pszTripTimeDesc_NoTrip*/g_sLangTxt_Unact;
					}
				}
			}
		}
		// 		else if (pVal->m_strID.Find(g_pszTripTimeKey_Act) >= 0)
		// 		{
		// 			GB_FinishTest_ActTime(pVal);
		// 		}
		else
		{
		}

		//���ʷ��� + ��ѹ���������������Ͷ���ֵ��û�гɶԳ��֡�Trip��Act����������⴦�� shaole 2023-8-14
		if ( (strMacroID == _T("PsuPowerDirection") && pVal->m_strID == _T("ActDsec"))
			|| (strMacroID == _T("ULockOverCurrent") && pVal->m_strID == _T("ActDsec")) )
		{
#ifdef _UNICODE
			double dValAct = _wtof(pVal->m_strValue);
#else
			double dValAct = atof(pVal->m_strValue.GetString());
#endif

			if (dValAct <= 0.00001)
			{
				pVal->m_strValue = /*g_pszTripTimeDesc_NoTrip*/g_sLangTxt_Unact;
			}
			else
			{
				pVal->m_strValue = /*g_pszTripTimeDesc_Trip*/g_sLangTxt_Act;
			}
		}
	}
}

long CMacroTest::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CGbItemBase::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
		BinarySerializeCalLen(oBinaryBuffer, m_nRepeatTimes);
		BinarySerializeCalLen(oBinaryBuffer, m_strReportMode);
		BinarySerializeCalLen(oBinaryBuffer, m_nTestTimes);
		BinarySerializeCalLen(oBinaryBuffer, m_nReportFillUseNoRepeat);
	}
	else if (oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strType);
		BinarySerializeRead(oBinaryBuffer, m_nRepeatTimes);

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_5)
		{
			BinarySerializeRead(oBinaryBuffer, m_strReportMode);
		}
		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_6)
		{
			BinarySerializeRead(oBinaryBuffer, m_nTestTimes);
		}
		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_30)
		{
			BinarySerializeRead(oBinaryBuffer, m_nReportFillUseNoRepeat);
		}
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strType);
		BinarySerializeWrite(oBinaryBuffer, m_nRepeatTimes);
		BinarySerializeWrite(oBinaryBuffer, m_strReportMode);
		BinarySerializeWrite(oBinaryBuffer, m_nTestTimes);
		BinarySerializeWrite(oBinaryBuffer, m_nReportFillUseNoRepeat);
	}
	return 0;
}

long CMacroTest::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemBase::XmlReadOwn(oNode,pXmlRWKeys);

	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strTypeKey,oNode,m_strType);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strRepeatTimes,oNode,m_nRepeatTimes);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strCalModeKey,oNode,m_strReportMode);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strReportFillUseNoRepeatKey,oNode,m_nReportFillUseNoRepeat);

	return 0;
}

long CMacroTest::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemBase::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	if (g_bGbExportXmlReportFile)
	{
		if (CGuideBookExportConfig::g_pGuideBookExportConfig->m_nExportItemAttrSimplify)
		{
			return 0;
		}
	}

	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strRepeatTimes,oElement,m_nRepeatTimes);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strCalModeKey,oElement,m_strReportMode);

	if (g_bGbSaveGbStruDscFile)
	{
		return 0;
	}

	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strTypeKey,oElement,m_strType);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strReportFillUseNoRepeatKey,oElement,m_nReportFillUseNoRepeat);

	return 0;
}


////2022-10-4  lijunqing
long CMacroTest::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		//2022-10-4  lijunqing
		if (g_bGbSaveGbStruDscFile)
		{
			if (nClassID == GBCLASSID_TESTMACROUIPARAS)
			{
				continue;
			}
		}

		if (g_bGbExportXmlReportFile)
		{
			if (Gb_IsItemNeedExportRpt(nClassID))
			{
				pObj->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
			}
		}
		else
		{
// 			if (nClassID == GBCLASSID_REPORTS)
// 			{
// 				if (CGbXMLKeys::g_pGbXMLKeys->m_nSaveItemRpts <= 0)
// 				{
// 					continue;
// 				}
// 			}
		}

		pObj->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
	}

	return 0;
}


void CMacroTest::InitAfterRead()
{
	CGbItemBase::InitAfterRead();

	m_oListMsgs.RemoveAll();

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		switch (nClassID)
		{
		case GBCLASSID_MSG:
			m_oListMsgs.AddTail(p);
			break;
// 		case GBCLASSID_COMMCMD:
// 		case GBCLASSID_SAFETY:
// 			m_oSubGbItems.AddTail(p);
// 			break;
		case GBCLASSID_MACROPARA:
			m_pPara = (CMacroTestPara*)p;
			break;

		case GBCLASSID_COMMCMD:
		case GBCLASSID_SAFETY:
			m_oSubGbItems.AddTail(p);
			((CGbItemBase*)p)->m_bIsSubItem = TRUE;
			break;

		case GBCLASSID_TESTMACROUIPARAS:
			m_pUiParas = (CTestMacroUiParas*)p;
			break;

		default:
			break;
		}
	}

	if (m_pPara == NULL)
	{
		m_pPara = new CMacroTestPara();
		m_pPara->InitAfterRead();
		AddNewChild(m_pPara);
	}

    if(m_nRepeatTimes == 0)
    {
        m_nRepeatTimes = 1;
    }
}

CExBaseObject* CMacroTest::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strMsgKey)
	{
		CMsg* pMsg = new CMsg();
		return pMsg;
	}
	else if(strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strParaKey)
	{
		m_pPara = new CMacroTestPara();
		return m_pPara;
	}
	else if(strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strCommCmdKey)
	{
		CCommCmd* pCmd = new CCommCmd();
		return pCmd;
	}
	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strSafetyKey)
	{
		CSafety* pObject = new CSafety;
		return pObject;
	}
	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strTestMacroUiParasKey)
	{
		CTestMacroUiParas* pObject = new CTestMacroUiParas;
		return pObject;
	}

	return CGbItemBase::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
}

CExBaseObject* CMacroTest::CreateNewChild(long nClassID)
{
	if(nClassID == GBCLASSID_MSG)
	{
		CMsg* pMsg = new CMsg();
		return pMsg;
	}
	else if(nClassID == GBCLASSID_MACROPARA)
	{
		m_pPara = new CMacroTestPara();
		return m_pPara;
	}
	else if(nClassID == GBCLASSID_COMMCMD)
	{
		CCommCmd* pCmd = new CCommCmd();
		return pCmd;
	}
	else if (nClassID == GBCLASSID_SAFETY)
	{
		CSafety* pObject = new CSafety;
		return pObject;
	}
	else if (nClassID == GBCLASSID_TESTMACROUIPARAS)
	{
		CTestMacroUiParas* pObject = new CTestMacroUiParas;
		return pObject;
	}

	return CGbItemBase::CreateNewChild(nClassID);
}

BOOL CMacroTest::IsEqual(CBaseObject* pObj)
{
	return FALSE;
}

BOOL CMacroTest::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
		return TRUE;

 	CMacroTest* pMacroTest = (CMacroTest*)pDesObj;
	pMacroTest->m_strType = m_strType;
	pMacroTest->m_nRepeatTimes = m_nRepeatTimes;
	pMacroTest->m_strReportMode = m_strReportMode;
	pMacroTest->m_nReportFillUseNoRepeat = m_nReportFillUseNoRepeat;

	CGbItemBase::CopyOwn(pDesObj);

	return TRUE;
}

CBaseObject* CMacroTest::Clone()
{
	CMacroTest* pMacroTest = new CMacroTest();
	Copy(pMacroTest);

	return pMacroTest;
}

CBaseObject* CMacroTest::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CMacroTest *p = new CMacroTest();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CMacroTest::CanPaste(UINT nClassID)
{
	if (nClassID == GBCLASSID_COMMCMD || nClassID == GBCLASSID_SAFETY)
	{
		return TRUE;
	}

	return FALSE;
}

CTestMacroUiParas* CMacroTest::CreateTestMacroUiParas()
{	
	if (m_pUiParas == NULL)
	{
		m_pUiParas = new CTestMacroUiParas;
		AddNewChild(m_pUiParas);
	}

	return m_pUiParas;
}

void CMacroTest::SetTestMacroID(const CString &strTestMacroID)
{
	ASSERT (m_pPara != NULL);
	return m_pPara->SetMacroID(strTestMacroID);
}

CString CMacroTest::GetTestMacroID()
{
	if (m_pPara == NULL)
	{
		return _T("");
	}

	return m_pPara->GetMacroID();
}

CMacroTestPara* CMacroTest::GetMacroTestPara()
{		
	return m_pPara;		
}

CMacroTestParaDatas* CMacroTest::GetFaultParaDatas()
{
	CMacroTestParaDatas *pPara = NULL;

	if (m_pPara != NULL)
	{
		pPara = m_pPara->GetFaultParaDatas();
	}

	return pPara;
}

CMacroTestParaDatas* CMacroTest::GetFultParaDatasUser()
{
	CMacroTestParaDatas *pPara = NULL;

	if (m_pPara != NULL)
	{
		pPara = m_pPara->GetFaultParaDatasUser();
	}

	return pPara;
}

void CMacroTest::ClearReport(BOOL bBack)
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
		else if (p->GetClassID() == GBCLASSID_SAFETY)
		{
			CSafety *pSafety = (CSafety*)p;
			pSafety->ClearReport(bBack);
		}
	}	
}


void CMacroTest::ReplaceSrciptText(CScriptText *pScript, UINT nScriptClassID, CGbItemBase *pSrcGbItem, BOOL bShowLog)
{
	CMacroTest *pSrcMacroTest = (CMacroTest*)pSrcGbItem;

	if (pSrcMacroTest->GetTestMacroID() != GetTestMacroID())
	{
		return;
	}

	if (nScriptClassID == GBCLASSID_SCRIPTTEXT)
	{
		CScriptText *pDest = m_pPara->GetScriptText();
		pScript->CopyOwn(pDest);
		return;
	}

	CGbItemBase::ReplaceSrciptText(pScript, nScriptClassID, pSrcGbItem, bShowLog);
}

#ifdef GUIDEBOOK_DEV_MODE

void CMacroTest::GenerateDevReports()
{
	CReport* pReport = GetCurrReport();

	if (pReport == NULL)
	{
		pReport = AddReport(-1, -1);//2017.0518
	}
	else
	{
		pReport->m_pValues->DeleteAll();
	}

	CValues* oValsTemp = NULL;
	CTestMacro* oTestMacro = Gb_GetMacroPtr(this);
	
	ASSERT(oTestMacro != NULL);

	if(oTestMacro != NULL)
	{
		CShortDatas  *pDatas = oTestMacro->GetFaultParas();
		pDatas->AppendValues(pReport->m_pValues);

		pDatas = oTestMacro->GetSysParas();
		pDatas->AppendValues(pReport->m_pValues);

		pDatas = oTestMacro->GetResults();
		pDatas->AppendValues(pReport->m_pValues);
	}
	
}

#endif


long CMacroTest::CalTestTimeLong()
{
	return 0;
}


long CMacroTest::GetState()
{
	if (m_nSelect == 0)
	{//���û��ѡ�У�Ĭ��Ϊ�ϸ�
		return TEST_STATE_ELIGIBLE;
	}

// 	if (m_nState < TEST_STATE_NORMAL || m_nState > TEST_STATE_INLEGIBLE)
// 	{
// 		m_nState = TEST_STATE_INLEGIBLE;
// 	}

	POS pos = m_oSubGbItems.GetHeadPosition();
	CGbItemBase *pGbItem = NULL;

	while (pos != NULL)
	{
		pGbItem = (CGbItemBase *)m_oSubGbItems.GetNext(pos);

		if (pGbItem->GetState() == TEST_STATE_INLEGIBLE)
		{
			return TEST_STATE_INLEGIBLE;
		}
	}

	return CGbItemBase::GetState();
}

void CMacroTest::ClearItemInDbState()
{
	CGbItemBase::ClearItemInDbState();

	//m_pPara->ClearItemInDbState();
}

//��Ϊ�麯��������д����Ϊ�˷������
void CMacroTest::SetTkID(long nTkID)
{ 
	m_nTkID = nTkID;
}

//��Ϊ�麯��������д����Ϊ�˷������
void CMacroTest::SetSelect(long nSelect)
{ 
	m_nSelect = nSelect;
}

//shaolei 20220607
void CMacroTest::SetItemState(long nShow, long nEnable, long nSelect, BOOL bSetShow, BOOL bSetEnable, BOOL bSetSelect)
{
	CGbItemBase::SetItemState(nShow, nEnable, nSelect, bSetShow, bSetEnable, bSetSelect);

	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == GBCLASSID_COMMCMD)
		{
			CCommCmd* pCmd = (CCommCmd *)pObj;
			//�˴��Ƿ�Ӧ�����ǣ�������ó�1������Ŀ�ǲ��ǲ���Ҫ���ã�
			pCmd->SetItemState(nShow, nEnable, nSelect, bSetShow, bSetEnable, bSetSelect);
			continue;
		}

		if (nClassID == GBCLASSID_SAFETY)
		{
			CSafety* pSafety = (CSafety *)pObj;
			//�˴��Ƿ�Ӧ�����ǣ�������ó�1������Ŀ�ǲ��ǲ���Ҫ���ã�
			pSafety->SetItemState(nShow, nEnable, nSelect, bSetShow, bSetEnable, bSetSelect);
			continue;
		}
	}
}

void CMacroTest::GenSvMatchItems(CExBaseList *pDataSet)
{
	CCommCmd *pEnaOn = NULL;
	CCommCmd *pReadAin = NULL;
	CCommCmd *pEnaOff = NULL;
	long nIndex = 0;
	//��������Ŀ��������ͨѶ��������Ŀ��Ͷѹ�塢��ң�⡢��ѹ��
	GenSvMatchItems_GetSubCommCmd(&pEnaOn, &pReadAin, &pEnaOff);

	if (pEnaOn == NULL || pReadAin == NULL || pEnaOff == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("����SV����ѹ��һ���Լ����Ŀʧ�ܣ���Ŀ��%s��û�ҵ�����ͨѶ��������Ŀ"), m_strName.GetString());
		return;
	}

	POS pos = pDataSet->GetHeadPosition();
	CDataObj *pData = NULL;
	m_oSubGbItems.RemoveAll();

// 	CGuideBook *pGuideBook = (CGuideBook *)GetAncestor(GBCLASSID_GUIDEBOOK);
// 	CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetParent();

	while (pos != NULL)
	{
		pData = (CDataObj *)pDataSet->GetNext(pos);

		//����Ͷѹ��
		CCommCmd *pNewEnaOn = (CCommCmd *)pEnaOn->CloneEx(TRUE, TRUE);
        pNewEnaOn->m_strName.Format(_T("Ͷѹ��_%s"), pData->m_strName.GetString());
		pNewEnaOn->m_strID.Format(_T("EnaOn_%d"), nIndex + 1);
		pNewEnaOn->m_bIsSubItem = TRUE;
		CCmd *pCmd = pNewEnaOn->GetCmd();
		CValue *pValue = (CValue *)pCmd->GetHead();  //һ��ͨѶ���ֻͶ��һ��ѹ��

		//value�Ӷ����id��Ϊodata��id��valueΪ1
		if (pValue == NULL)
		{
			pValue = pCmd->AddValue(pData->m_strID, _T("1"));
		}
		else
		{
			pValue->m_strID = pData->m_strID;
			pValue->m_strValue = _T("1");
		}

		//pTestControl->m_oTCtrlMsgRcv.InsertItem(this, pNewEnaOn);
		AddNewChild(pNewEnaOn);
		m_oSubGbItems.AddTail(pNewEnaOn);

		//������ң��
		CCommCmd *pNewReadAin = (CCommCmd *)pReadAin->CloneEx(TRUE, TRUE);
        pNewReadAin->m_strName.Format(_T("��ң��_%s"), pData->m_strName.GetString());
		pNewReadAin->m_strID.Format(_T("ReadAin_%d"), nIndex + 1);
		pNewReadAin->m_bIsSubItem = TRUE;
		//��ң�⣬�滻����ű��еĹ̶��ַ���
		CScriptText *pScriptRslt = pNewReadAin->GetResultScriptText();
		pScriptRslt->m_strScriptText.Replace(_T("SV_ENA_TEST_DATA_ID"), pData->m_strID);

		//pTestControl->m_oTCtrlMsgRcv.InsertItem(this, pNewReadAin);
		AddNewChild(pNewReadAin);
		m_oSubGbItems.AddTail(pNewReadAin);

		//������ѹ��
		CCommCmd *pNewEnaOff = (CCommCmd *)pEnaOff->CloneEx(TRUE, TRUE);
        pNewEnaOff->m_strName.Format(_T("��ѹ��_%s"), pData->m_strName.GetString());
		//��ѹ�壬�滻����ű��еĹ̶��ַ���
		pScriptRslt = pNewEnaOff->GetResultScriptText();
		pScriptRslt->m_strScriptText.Replace(_T("ReadAin"), pNewReadAin->m_strID);

		pNewEnaOff->m_strID.Format(_T("EnaOff_%d"), nIndex + 1);
		pNewEnaOff->m_bIsSubItem = TRUE;
		pCmd = pNewEnaOff->GetCmd();
		pValue = (CValue *)pCmd->GetHead();  //һ��ͨѶ���ֻͶ��һ��ѹ��
		//value�Ӷ����id��Ϊodata��id��valueΪ0
		if (pValue == NULL)
		{
			pValue = pCmd->AddValue(pData->m_strID, _T("0"));
		}
		else
		{
			pValue->m_strID = pData->m_strID;
			pValue->m_strValue = _T("0");
		}

		//pTestControl->m_oTCtrlMsgRcv.InsertItem(this, pNewEnaOff);
		AddNewChild(pNewEnaOff);
		m_oSubGbItems.AddTail(pNewEnaOff);

		nIndex++;
	}

	//Delete(pEnaOn);
	//pTestControl->m_oTCtrlMsgRcv.DeleteItem(this, pEnaOn);
	//Delete(pReadAin);
	//pTestControl->m_oTCtrlMsgRcv.DeleteItem(this, pReadAin);
	//Delete(pEnaOff);
	//pTestControl->m_oTCtrlMsgRcv.DeleteItem(this, pEnaOff);
}

void CMacroTest::GenSvMatchItems_GetSubCommCmd(CCommCmd **ppEnaOn, CCommCmd **ppReadAin, CCommCmd **ppEnaOff)
{
	long nIndex = 0;
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		if (nIndex > 2)
		{
			return;
		}

		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != GBCLASSID_COMMCMD)
		{
			continue;
		}

		if (nIndex == 0)
		{
			*ppEnaOn = (CCommCmd *)pObj;
		}

		if (nIndex == 1)
		{
			*ppReadAin = (CCommCmd *)pObj;
		}

		if (nIndex == 2)
		{
			*ppEnaOff = (CCommCmd *)pObj;
		}

		nIndex++;
	}
}

long CMacroTest::GetItemTestCount()
{
	CGbItemBase *pParent = (CGbItemBase *)GetParent();

	return m_nRepeatTimes * pParent->GetItemTestCount();
}

//����״̬���к͵ݱ䣬�ظ����Դ������ڸ���ĿCItems�ϵġ�
void CMacroTest::GetTestTimes(long &nCurrTestTimes, long &nRepeatTimes)
{
	if (m_nRepeatTimes > 1)
	{
		//���������ظ���������1�ģ����ڴ˴���ȡ��ص���Ϣ
		return;
	}

	//��������û���ظ����ԣ��ڸ���ĿCItems�ظ����Եĵ�������Ŀ���ǲ��ᴴ�����㱨��ġ�
	nRepeatTimes = GetItemTestCount();

    if(nRepeatTimes == 0)
    {
        nRepeatTimes = 1;
    }

	CReports *pReports = GetReports();
	long nReportsCount = pReports->GetCount();

	if (nReportsCount == 0)
	{
		return;
	}

	CReport *pHeadReport = (CReport *)pReports->GetHead();
	
	//����ģ��ʱ����������Ŀ���ɵ�Ĭ�ϱ����ID���̶�ID
	if (pHeadReport->m_strID ==  _T("_Init_"))
	{
		nReportsCount = nReportsCount - 1;//��ʼ����Ĭ�ϱ��棬��������
	}

	//�������˴�����bug����α�֤ÿ�ζ���һ��ѭ���������?
	//��ѭ������5�Σ��Ҳ����κ�ֹͣ���ԡ������¿�ʼ���ԣ���ڶ���ѭ������һ�β��Ի���Ϊ�ǵ�����
	//�Ѵ����ڲ�ѯ��Ŀʱ�����б��汸�ݣ���֤ÿ��ѭ�����ԣ���ֻ�б���ѭ���ı���  2023-9-14
	if (nReportsCount >= 1)
	{
		nCurrTestTimes = nReportsCount % nRepeatTimes;

		if (nCurrTestTimes == 0)
		{
			nCurrTestTimes = nRepeatTimes;
		}
	}
}

void Gb_ResetMacroParas(CTestMacro* pMacro)
{
	if (pMacro == NULL)
	{
		return;
	}

	CShortDatas  *pDatas = pMacro->GetFaultParas();
	Gb_ResetDatas(pDatas);

	pDatas = pMacro->GetSysParas();
	Gb_ResetDatas(pDatas);
}

void Gb_ResetDatas(CShortDatas *pDatas)
{
	if (pDatas == NULL)
	{
		return;
	}

	pDatas->ResetDatas();
}

CString Gb_GetMacroScriptUiDll(CMacroTest *pMacroTest)
{
	if (pMacroTest == NULL)
	{
		return _T("");
	}

	CMacroTestPara *pTestPara = pMacroTest->GetMacroTestPara();
	CString strMacroID = pTestPara->GetMacroID();
	CTestMacros* pMacros = Gb_GetMacrosPtr(pMacroTest);

	if (pMacros == NULL)
	{
		return _T("");
	}

	CTestMacro *pMacro = (CTestMacro*)pMacros->FindByID(strMacroID);

	if (pMacro == NULL)
	{
		return _T("");
	}

#ifndef NOT_USE_TestMacroScriptMngr
	CTestMacroScript *pScript = TM_GetTestMacroScript(pMacro);

	if (pScript != NULL)
	{
		return pScript->m_strUIDLL;
	}
#endif

	return _T("");
}

