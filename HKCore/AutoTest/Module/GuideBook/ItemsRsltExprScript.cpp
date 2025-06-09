#include "stdafx.h"
#include "ItemsRsltExprScript.h"
#include "Device.h"

#ifndef ItemsGlobalRsltScript_NoGb
#include "GbItemBase.h"
#include "GuideBook.h"
#endif

#include "../../../Module/API/FileApi.h"
#include "../XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CItemsRsltExpr::CItemsRsltExpr()
{
	m_dStandValue = 0;
	m_dDvmValue = 0;
	m_dAbsErrorCal = 0;
	m_dRelErrorCal = 0;
	m_dAbsError = 0;
	m_dRelError = 0;
	m_dwRsltJdg = 0;
}


CItemsRsltExpr::~CItemsRsltExpr()
{
	
}

long CItemsRsltExpr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	int nCount = 0;

	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strStandID);
		BinarySerializeCalLen(oBinaryBuffer, m_strAbsErrorCalExpr);
		BinarySerializeCalLen(oBinaryBuffer, m_strRelErrorCalExpr);
		BinarySerializeCalLen(oBinaryBuffer, m_strDvmDataID);
		BinarySerializeCalLen(oBinaryBuffer, m_strDvmDataAbsErrID);
		BinarySerializeCalLen(oBinaryBuffer, m_strDvmDataRelErrID);
		BinarySerializeCalLen(oBinaryBuffer, m_strVarAbsErr);
		BinarySerializeCalLen(oBinaryBuffer, m_strVarRelErr);
		BinarySerializeCalLen(oBinaryBuffer, m_strRsltVarAbsErr);
		BinarySerializeCalLen(oBinaryBuffer, m_strRsltVarRelErr);
	}
	else if (oBinaryBuffer.IsReadMode())
	{	
		BinarySerializeRead(oBinaryBuffer, m_strStandID);
		BinarySerializeRead(oBinaryBuffer, m_strAbsErrorCalExpr);
		BinarySerializeRead(oBinaryBuffer, m_strDvmDataID);
		BinarySerializeRead(oBinaryBuffer, m_strRelErrorCalExpr);
		BinarySerializeRead(oBinaryBuffer, m_strDvmDataAbsErrID);
		BinarySerializeRead(oBinaryBuffer, m_strDvmDataRelErrID);
		BinarySerializeRead(oBinaryBuffer, m_strVarAbsErr);
		BinarySerializeRead(oBinaryBuffer, m_strVarRelErr);
		BinarySerializeRead(oBinaryBuffer, m_strRsltVarAbsErr);
		BinarySerializeRead(oBinaryBuffer, m_strRsltVarRelErr);
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strStandID);
		BinarySerializeWrite(oBinaryBuffer, m_strAbsErrorCalExpr);
		BinarySerializeWrite(oBinaryBuffer, m_strDvmDataID);
		BinarySerializeWrite(oBinaryBuffer, m_strRelErrorCalExpr);
		BinarySerializeWrite(oBinaryBuffer, m_strDvmDataAbsErrID);
		BinarySerializeWrite(oBinaryBuffer, m_strDvmDataRelErrID);
		BinarySerializeWrite(oBinaryBuffer, m_strVarAbsErr);
		BinarySerializeWrite(oBinaryBuffer, m_strVarRelErr);
		BinarySerializeWrite(oBinaryBuffer, m_strRsltVarAbsErr);
		BinarySerializeWrite(oBinaryBuffer, m_strRsltVarRelErr);
	}

	return 0;
}

long CItemsRsltExpr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strStandIDKey, oNode, m_strStandID);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strAbsErrCalExprKey, oNode, m_strAbsErrorCalExpr);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDvmDataIDKey, oNode, m_strDvmDataID);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strRelErrCalExprKey, oNode, m_strRelErrorCalExpr);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDvmDataAbsErrIDKey, oNode, m_strDvmDataAbsErrID);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDvmDataRelErrIDKey, oNode, m_strDvmDataRelErrID);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strVarAbsErrKey, oNode, m_strVarAbsErr);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strVarRelErrKey, oNode, m_strVarRelErr);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strRsltVarAbsErrKey, oNode, m_strRsltVarAbsErr);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strRsltVarRelErrKey, oNode, m_strRsltVarRelErr);

	return 0;
}

long CItemsRsltExpr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strStandIDKey, oElement, m_strStandID);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strAbsErrCalExprKey, oElement, m_strAbsErrorCalExpr);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strDvmDataIDKey, oElement, m_strDvmDataID);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strRelErrCalExprKey, oElement, m_strRelErrorCalExpr);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strDvmDataAbsErrIDKey, oElement, m_strDvmDataAbsErrID);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strDvmDataRelErrIDKey, oElement, m_strDvmDataRelErrID);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strVarAbsErrKey, oElement, m_strVarAbsErr);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strVarRelErrKey, oElement, m_strVarRelErr);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strRsltVarAbsErrKey, oElement, m_strRsltVarAbsErr);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strRsltVarRelErrKey, oElement, m_strRsltVarRelErr);

	return 0;
}


BOOL CItemsRsltExpr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CItemsRsltExpr *p = (CItemsRsltExpr*)pObj;

	if (p->m_strStandID != m_strStandID)
	{
		return FALSE;
	}

	if (p->m_strDvmDataID != m_strDvmDataID)
	{
		return FALSE;
	}

	if (p->m_strDvmDataAbsErrID != m_strDvmDataAbsErrID)
	{
		return FALSE;
	}

	if (p->m_strDvmDataRelErrID != m_strDvmDataRelErrID)
	{
		return FALSE;
	}

	if (p->m_strVarAbsErr != m_strVarAbsErr)
	{
		return FALSE;
	}

	if (p->m_strVarRelErr != m_strVarRelErr)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CItemsRsltExpr::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
		return TRUE;

	CItemsRsltExpr* pItemsGlobalRsltScript = (CItemsRsltExpr*)pDesObj;

	 //输出的标准值
	pItemsGlobalRsltScript->m_strStandID = m_strStandID;
	pItemsGlobalRsltScript->m_strAbsErrorCalExpr = m_strAbsErrorCalExpr; 

	//数据ID
	pItemsGlobalRsltScript->m_strDvmDataID = m_strDvmDataID;    
	pItemsGlobalRsltScript->m_strRelErrorCalExpr = m_strRelErrorCalExpr; 
	pItemsGlobalRsltScript->m_strDvmDataAbsErrID = m_strDvmDataAbsErrID;
	pItemsGlobalRsltScript->m_strDvmDataRelErrID = m_strDvmDataRelErrID;

	pItemsGlobalRsltScript->m_strVarAbsErr = m_strVarAbsErr;
	pItemsGlobalRsltScript->m_strVarRelErr = m_strVarRelErr; 
	pItemsGlobalRsltScript->m_strRsltVarAbsErr = m_strRsltVarAbsErr;
	pItemsGlobalRsltScript->m_strRsltVarRelErr = m_strRsltVarRelErr; 

	CExBaseObject::CopyOwn(pItemsGlobalRsltScript);

	return TRUE;
}

CBaseObject* CItemsRsltExpr::Clone()
{
	CItemsRsltExpr* pNew = new CItemsRsltExpr();
	Copy(pNew);

	return pNew;
}

long CItemsRsltExpr::RunRsltExprScript(CDevice *pDevice, CValues *pRptValues, CValues *pAllValues)
{
	long nRslt = 1;
	double dStand = 0;
	double dDvmVal = 0;
	double dErrorAbs = 0;
	double dErrorRel = 0;
	double dAbsErrorCal = 0;
	double dAbsErrorCal_Abs = 0;
	double dRelErrorCal = 0;
	BOOL bUseAbsError = FALSE;
	BOOL bUseRelError = FALSE;

	GetStandVal(pDevice, pAllValues, dStand);
	GetDvmVal(pDevice, pAllValues, dDvmVal);
	CalAbsError(pDevice, pRptValues, pAllValues, dStand, dDvmVal, dAbsErrorCal);
	dAbsErrorCal_Abs = fabs(dAbsErrorCal);
	CalRelError(pDevice, pRptValues, pAllValues, dStand, dAbsErrorCal_Abs, dRelErrorCal);

	//误差限
	if (m_strVarAbsErr.GetLength() > 3)
	{
		bUseAbsError = TRUE;
		pDevice->GetVariableValue2(m_strVarAbsErr, dErrorAbs);
	}

	if (m_strVarRelErr.GetLength() > 3)
	{
		bUseRelError = TRUE;
		pDevice->GetVariableValue2(m_strVarRelErr, dErrorRel);
	}

	//绝对误差判别
	if (bUseAbsError)
	{
		if (dAbsErrorCal_Abs > dErrorAbs)
		{
			nRslt = 0;
		}
	}

	if (bUseRelError)
	{
		if (fabs(dRelErrorCal) > dErrorRel)
		{
			nRslt = 0;
		}
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Stand=%f CurrVal=%f AbsErrorCal=%f RelErrorCal=%f ")
		, dStand, dDvmVal, dAbsErrorCal, dRelErrorCal);

	m_dStandValue = dStand;
	m_dDvmValue = dDvmVal;
	m_dAbsErrorCal = dAbsErrorCal;
	m_dRelErrorCal = dRelErrorCal;
	m_dAbsError = dErrorAbs;
	m_dRelError = dErrorRel;
	m_dwRsltJdg = nRslt;

	return nRslt;
}

//绝对误差的计算
void CItemsRsltExpr::CalAbsError(CDevice *pDevice, CValues *pRptValues, CValues *pAllValues, double &dStand, double &dDvmVal, double &dAbsErrorCal)
{
	if (m_strAbsErrorCalExpr.GetLength() > 3)
	{
		Gb_CalParaExpression(m_strAbsErrorCalExpr, pDevice, dAbsErrorCal, TRUE, pAllValues);
	}
	else
	{
		BOOL bStand = GetStandVal(pDevice, pAllValues, dStand);
		BOOL bDvm = GetDvmVal(pDevice, pAllValues, dDvmVal);

		if (dStand && bDvm)
		{
			dAbsErrorCal = dDvmVal - dStand;
		}
		else
		{
			dAbsErrorCal = 10000;
		}
	}

	CString strAbsErrorID;

	if (m_strRsltVarAbsErr.GetLength() > 0)
	{
		strAbsErrorID = m_strRsltVarAbsErr;
	}
	else
	{
		strAbsErrorID = g_strAinExand_Abs + m_strDvmDataID;
	}

	CValue *pValue = (CValue*)pRptValues->FindByID(strAbsErrorID);

	if (pValue == NULL)
	{
		pValue = new CValue();
		pValue->m_strID = strAbsErrorID;
		pRptValues->AddNewChild(pValue);
		pAllValues->AddTail(pValue);
	}

	pValue->m_strValue.Format(_T("%f"), dAbsErrorCal);
}

//相对误差的计算
void CItemsRsltExpr::CalRelError(CDevice *pDevice, CValues *pRptValues, CValues *pAllValues, double &dStand, double &dAbsErrorCal, double &dRelErrorCal)
{
	if (m_strRelErrorCalExpr.GetLength() > 3)
	{
		Gb_CalParaExpression(m_strRelErrorCalExpr, pDevice, dRelErrorCal, TRUE, pAllValues);
	}
	else
	{
		dRelErrorCal = dAbsErrorCal / dStand;
	}

	CString strRelErrorID;

	if (m_strRsltVarAbsErr.GetLength() > 0)
	{
		strRelErrorID = m_strRsltVarRelErr;
	}
	else
	{
		strRelErrorID = g_strAinExand_Rel + m_strDvmDataID;
	}

	CValue *pValue = (CValue*)pRptValues->FindByID(strRelErrorID);

	if (pValue == NULL)
	{
		pValue = new CValue();
		pValue->m_strID = strRelErrorID;
		pRptValues->AddNewChild(pValue);
		pAllValues->AddTail(pValue);
	}

	//dRelErrorCal = fabs(dRelErrorCal);
	pValue->m_strValue.Format(_T("%f"), dRelErrorCal);
}

BOOL CItemsRsltExpr::GetStandVal(CDevice *pDevice, CValues *pAllValues, double &dStandVal)
{
	if (pAllValues->GetValue(m_strStandID, dStandVal))
	{
		return TRUE;
	}
	else
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("输出值ID[%s]不存在"), m_strStandID.GetString());
		return FALSE;
	}
}

BOOL CItemsRsltExpr::GetDvmVal(CDevice *pDevice, CValues *pAllValues, double &dDvmVal)
{
	if (pAllValues->GetValue(m_strDvmDataID, dDvmVal))
	{
		return TRUE;
	}

	if (pDevice->GetVariableValue2(m_strDvmDataID, dDvmVal))
	{
		return TRUE;
	}

    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("数据值ID[%s]不存在"), m_strDvmDataID.GetString());

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
//CItemsRsltExprScript
CItemsRsltExprScript::CItemsRsltExprScript()
{
	m_nIsRef = 0;
	m_nMaxReadTimes = 5;       //最大读数据次数
	m_dwReserved = 0;
}

CItemsRsltExprScript::~CItemsRsltExprScript()
{

}

long CItemsRsltExprScript::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	int nCount = 0;

	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strTestMacroID);
		BinarySerializeCalLen(oBinaryBuffer, m_strDatasetID);
		BinarySerializeCalLen(oBinaryBuffer, m_strTimeGapRead);
		BinarySerializeCalLen(oBinaryBuffer, m_nMaxReadTimes);
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
		BinarySerializeCalLen(oBinaryBuffer, m_nIsRef);
		BinarySerializeCalLen(oBinaryBuffer, m_strTimeIgnore);
	}
	else if (oBinaryBuffer.IsReadMode())
	{	
		//ItemScript修改带来的临时问题
		if (oBinaryBuffer.m_dwVersion > GBVERSION_1_25)
		{
			BinarySerializeRead(oBinaryBuffer, m_strTestMacroID);
			BinarySerializeRead(oBinaryBuffer, m_strDatasetID);
			BinarySerializeRead(oBinaryBuffer, m_strTimeGapRead);
			BinarySerializeRead(oBinaryBuffer, m_nMaxReadTimes);
			BinarySerializeRead(oBinaryBuffer, m_strID);
			BinarySerializeRead(oBinaryBuffer, m_nIsRef);
			BinarySerializeRead(oBinaryBuffer, m_strTimeIgnore);
		}
		else
		{
			BinarySerializeRead(oBinaryBuffer, m_strTestMacroID);
			//BinarySerializeRead(oBinaryBuffer, m_strDatasetID);
			BinarySerializeRead(oBinaryBuffer, m_strTimeGapRead);
			BinarySerializeRead(oBinaryBuffer, m_nMaxReadTimes);
			BinarySerializeRead(oBinaryBuffer, m_strID);
			BinarySerializeRead(oBinaryBuffer, m_nIsRef);
			//BinarySerializeRead(oBinaryBuffer, m_strTimeIgnore);
		}

		m_strName = m_strID;
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strTestMacroID);
		BinarySerializeWrite(oBinaryBuffer, m_strDatasetID);
		BinarySerializeWrite(oBinaryBuffer, m_strTimeGapRead);
		BinarySerializeWrite(oBinaryBuffer, m_nMaxReadTimes);
		BinarySerializeWrite(oBinaryBuffer, m_strID);
		BinarySerializeWrite(oBinaryBuffer, m_nIsRef);
		BinarySerializeWrite(oBinaryBuffer, m_strTimeIgnore);
	}

	return 0;
}


long CItemsRsltExprScript::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strScriptIsRefKey, oNode, m_nIsRef);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strMacroIDKey, oNode, m_strTestMacroID);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strTimeGapKey, oNode, m_strTimeGapRead);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strRetryTimesKey, oNode, m_nMaxReadTimes);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDataSetKey, oNode, m_strDatasetID);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strTimeIgnoreKey, oNode, m_strTimeIgnore);


	return 0;
}

long CItemsRsltExprScript::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strScriptIsRefKey, oElement, m_nIsRef);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strMacroIDKey, oElement, m_strTestMacroID);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strDataSetKey, oElement, m_strDatasetID);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strTimeGapKey, oElement, m_strTimeGapRead);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strRetryTimesKey, oElement, m_nMaxReadTimes);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strTimeIgnoreKey, oElement, m_strTimeIgnore);

	return 0;
}


BOOL CItemsRsltExprScript::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CItemsRsltExprScript *p = (CItemsRsltExprScript*)pObj;

	if (p->m_strTestMacroID != m_strTestMacroID)
	{
		return FALSE;
	}

	if (p->m_strTimeGapRead != m_strTimeGapRead)
	{
		return FALSE;
	}

	if (p->m_nMaxReadTimes != m_nMaxReadTimes)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CItemsRsltExprScript::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
		return TRUE;

	CItemsRsltExprScript* pItemsGlobalRsltScript = (CItemsRsltExprScript*)pDesObj;
	pItemsGlobalRsltScript->m_nIsRef = m_nIsRef;
	pItemsGlobalRsltScript->m_strTestMacroID = m_strTestMacroID;
	pItemsGlobalRsltScript->m_strTimeGapRead = m_strTimeGapRead;
	pItemsGlobalRsltScript->m_nMaxReadTimes = m_nMaxReadTimes;
	pItemsGlobalRsltScript->m_strDatasetID = m_strDatasetID;

	CExBaseObject::CopyOwn(pItemsGlobalRsltScript);

	return TRUE;
}

CBaseObject* CItemsRsltExprScript::Clone()
{
	CItemsRsltExprScript* pItemsGlobalRsltScript = new CItemsRsltExprScript();
	Copy(pItemsGlobalRsltScript);

	return pItemsGlobalRsltScript;
}

CExBaseObject* CItemsRsltExprScript::CreateNewChild(long nClassID)
{
	if(nClassID == GBCLASSID_ITEMSRSLTEXPR)
	{
		return new CItemsRsltExpr();
	}

	return NULL;
}

CExBaseObject* CItemsRsltExprScript::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CGbXMLKeys *pGbXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	if(strClassID == pGbXmlKeys->m_strRsltExprKey)
	{
		return new CItemsRsltExpr();
	}

	return NULL;
}

BOOL CItemsRsltExprScript::UpdateOwn(CBaseObject* pDest)
{
	CItemsRsltExprScript* pItemsGlobalRsltScript = (CItemsRsltExprScript*)pDest;
	pItemsGlobalRsltScript->m_nIsRef = m_nIsRef;
	pItemsGlobalRsltScript->m_strTestMacroID = m_strTestMacroID;
	pItemsGlobalRsltScript->m_strTimeGapRead = m_strTimeGapRead;
	pItemsGlobalRsltScript->m_nMaxReadTimes = m_nMaxReadTimes;
	pItemsGlobalRsltScript->m_strDatasetID = m_strDatasetID;
	pItemsGlobalRsltScript->m_strTimeIgnore = m_strTimeIgnore;

	return TRUE;
}

CExBaseObject* CItemsRsltExprScript::GetParentGbItem()
{
	CExBaseObject *pParent = (CExBaseObject*)GetParent();
	CExBaseObject *pItem = NULL;
	UINT nClassID = 0;
	ASSERT (pParent != NULL);

	while (TRUE)
	{
		nClassID = pParent->GetClassID();

		if (Gb_IsItemBaseClassID(nClassID))
		{
			pItem = pParent;
			break;
		}

		pParent = (CExBaseObject*)pParent->GetParent();

		if (pParent == NULL)
		{
			break;
		}
	}

	return pParent;
}

CExBaseObject* CItemsRsltExprScript::GetItemsGlobalRsltScriptMngr()
{
#ifndef ItemsGlobalRsltScript_NoGb
	CGuideBook *pGuideBook = (CGuideBook*)GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);
	return pGuideBook->GetScriptLibGlobal();
#else
	return NULL;
#endif
}

CItemsRsltExprScript* CItemsRsltExprScript::GetRefItemsGlobalRsltScript()
{
	CGuideBook *pGuideBook = (CGuideBook*)GetAncestor(GBCLASSID_GUIDEBOOK);
	CItemsRsltExprScript *pFind = pGuideBook->FindItemsRsltExprScript(m_strID);
	return pFind;
}

CItemsRsltExpr* CItemsRsltExprScript::AddNew(BOOL bClone)
{
	CItemsRsltExpr *pNew = NULL;

	if (bClone)
	{
		CItemsRsltExpr *pFind = (CItemsRsltExpr*)GetTail();

		if (pFind != NULL)
		{
			pNew = (CItemsRsltExpr*)pFind->Clone();
		}
		else
		{
			pNew = new CItemsRsltExpr();
		}
	}
	else
	{
		pNew = new CItemsRsltExpr();
	}

	AddNewChild(pNew);

	return pNew;
}

//选取相关联的全部数据对象
void CItemsRsltExprScript::SelectAllDatas(CExBaseList &listDatas, CDataSet *pDataset)
{
	POS pos = GetHeadPosition();
	CItemsRsltExpr *p = NULL;
	CDataObj *pData = NULL;
	CDataObj *pDataFind = NULL;

	while (pos != NULL)
	{
		p = (CItemsRsltExpr *)GetNext(pos);
		AddDataObj(p->m_strDvmDataID, listDatas, pDataset);
		AddDataObj(g_strAinExand_Abs + p->m_strDvmDataID, listDatas, pDataset);
		AddDataObj(g_strAinExand_Rel + p->m_strDvmDataID, listDatas, pDataset);
	}
}
void CItemsRsltExprScript::SelectAllDatas(CExBaseList &listDatas, CDvmDataset *pDataset)
{
	POS pos = GetHeadPosition();
	CItemsRsltExpr *p = NULL;

	while (pos != NULL)
	{
		p = (CItemsRsltExpr *)GetNext(pos);
		AddDataObj(p->m_strDvmDataID, listDatas, pDataset);
		AddDataObj(g_strAinExand_Abs + p->m_strDvmDataID, listDatas, pDataset);
		AddDataObj(g_strAinExand_Rel + p->m_strDvmDataID, listDatas, pDataset);
	}
}

BOOL CItemsRsltExprScript::Validate()
{
	if (m_strTestMacroID.GetLength() == 0)
	{
		return FALSE;
	}

	return TRUE;
}

void CItemsRsltExprScript::GetItemsRsltExprScriptTime(long &nTimeLong, long &nTimeIgnore)
{
	CDevice *pDevice = (CDevice*)GetAncestor(GBCLASSID_DEVICE);
	ASSERT (pDevice != NULL);
	CSysParas *pParas = pDevice->GetSysParas();
	nTimeLong = pParas->GetValueLong(m_strTimeGapRead);
	nTimeIgnore = pParas->GetValueLong(m_strTimeIgnore);
}

long CItemsRsltExprScript::RunRsltExprScript(CDevice *pDevice, CValues *pRptValues, CValues *pMacroTestValues)
{
	CExBaseObject *pTestControl = (CExBaseObject *)GetAncestor(GBCLASSID_TESTCONTROL);
    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CItemsRsltExprScript::RunRsltExprScript:%s "), pTestControl->m_strName.GetString());

	CValues listValues;
	listValues.Append(pRptValues);
	listValues.Append(pMacroTestValues);
	POS pos = GetHeadPosition();
	CItemsRsltExpr *pExpr = NULL;
	long nRslt = 0;

	while (pos != NULL)
	{
		pExpr = (CItemsRsltExpr *)GetNext(pos);
		nRslt += pExpr->RunRsltExprScript(pDevice, pRptValues, &listValues);
	}

	listValues.RemoveAll();

	return (nRslt == GetCount());
}

CDataObj* CItemsRsltExprScript::SelectDataInDs(const CString &strPath, CDataSet *pDataset)
{
	CExBaseObject *pObj = pDataset->FindChildByIDEx(strPath);

	if (pObj == NULL)
	{
		return NULL;
	}

	pObj->m_dwReserved = 1;
	CExBaseObject *pParent = (CExBaseObject*)pObj->GetParent();

	while (pParent != NULL)
	{
		pParent->m_dwReserved = 1;

		if (pParent->GetClassID() == GBCLASSID_DATAOBJ)
		{
			break;
		}

		pParent = (CExBaseObject*)pParent->GetParent();
	}

	CDataObj *pDataFind = (CDataObj *)pObj->GetAncestor(GBCLASSID_DATAOBJ);

	return pDataFind;
}

BOOL CItemsRsltExprScript::AddDataObj(const CString &strPath, CExBaseList &listDatas, CDataSet *pDataset)
{
	CDataObj *pDataFind = SelectDataInDs(strPath, pDataset);

	if (pDataFind != NULL)
	{
		if (listDatas.Find(pDataFind) == NULL)
		{
			listDatas.AddTail(pDataFind);
			return TRUE;
		}
	}

	return FALSE;
}


CDvmData* CItemsRsltExprScript::SelectDataInDs(const CString &strPath, CDvmDataset *pDataset)
{
	CExBaseObject *pObj = pDataset->FindChildByIDEx(strPath);

	if (pObj == NULL)
	{
		return NULL;
	}

	pObj->m_dwReserved = 1;
	CExBaseObject *pParent = (CExBaseObject*)pObj->GetParent();

	while (pParent != NULL)
	{
		pParent->m_dwReserved = 1;

		if (pParent->GetClassID() == GBCLASSID_DATAOBJ)
		{
			break;
		}

		pParent = (CExBaseObject*)pParent->GetParent();
	}

	CDvmData *pDataFind = (CDvmData *)pObj->GetAncestor(GBCLASSID_DATAOBJ);

	return pDataFind;
}

BOOL CItemsRsltExprScript::AddDataObj(const CString &strPath, CExBaseList &listDatas, CDvmDataset *pDataset)
{
	CDvmData *pDataFind = SelectDataInDs(strPath, pDataset);

	if (pDataFind != NULL)
	{
		if (listDatas.Find(pDataFind) == NULL)
		{
			listDatas.AddTail(pDataFind);
			return TRUE;
		}
	}

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
//CItemsRsltExprScriptMngr
CItemsRsltExprScriptMngr::CItemsRsltExprScriptMngr()
{
	m_bModifiedFlag = TRUE;
}

CItemsRsltExprScriptMngr::~CItemsRsltExprScriptMngr()
{

}

long CItemsRsltExprScriptMngr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);
	return 0;
}

long CItemsRsltExprScriptMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	return 0;
}

long CItemsRsltExprScriptMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	return 0;
}

BOOL CItemsRsltExprScriptMngr::IsEqual(CBaseObject* pObj)
{
	return TRUE;
}

BOOL CItemsRsltExprScriptMngr::CopyOwn(CBaseObject* pDesObj)
{
	return TRUE;
}

CBaseObject* CItemsRsltExprScriptMngr::Clone()
{
	CItemsRsltExprScriptMngr* pObj = new CItemsRsltExprScriptMngr();
	Copy(pObj);

	return pObj;
}


CExBaseObject* CItemsRsltExprScriptMngr::CreateNewChild(long nClassID)
{
	return new CItemsRsltExprScript();
}

CExBaseObject* CItemsRsltExprScriptMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	return new CItemsRsltExprScript();
}

CItemsRsltExprScript* CItemsRsltExprScriptMngr::AddNewItemsGlobalRsltScript(const CString &strID)
{
	CItemsRsltExprScript *p = new CItemsRsltExprScript();
	p->m_strID = strID;
	p->m_strName = strID;
	AddTail(p);
	return p;
}

BOOL CItemsRsltExprScriptMngr::OpenScriptMngrFile(const CString &strFile)
{
	CString strScriptMngrFile = strFile;
	strScriptMngrFile.Trim();

	if (strScriptMngrFile.GetLength() == 0)
	{
		strScriptMngrFile = _T("GbExprScriptLibrary.xml");
	}

	CString strPath;
	strPath = _P_GetConfigPath();
	strPath += strScriptMngrFile;

	if (IsFileExist(strPath))
	{
		DeleteAll();

		if ( OpenXmlFile(strPath, GetXmlElementKey(), CGbXMLKeys::g_pGbXMLKeys) )
		{
			m_strScriptMngrFile = strScriptMngrFile;
			m_strID = strFile;
			m_strName = strFile;
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL CItemsRsltExprScriptMngr::SaveScriptMngrFile(const CString &strFile)
{
	CString strScriptMngrFile = strFile;
	strScriptMngrFile.Trim();

	if (strScriptMngrFile.GetLength() == 0)
	{
		strScriptMngrFile = m_strScriptMngrFile;
	}

	if (strScriptMngrFile.GetLength() == 0)
	{
		strScriptMngrFile = _T("GbExprScriptLibrary.xml");
	}

	CString strPath;
	strPath = _P_GetConfigPath();
	strPath += strScriptMngrFile;

	return SaveXmlFile(strPath, CGbXMLKeys::g_pGbXMLKeys);
}

void CItemsRsltExprScriptMngr::Import(CItemsRsltExprScriptMngr *pSrc)
{
	POS pos = pSrc->GetHeadPosition();
	CItemsRsltExprScript *p    = NULL;
	CItemsRsltExprScript *pNew = NULL;

	while (pos != NULL)
	{
		p = (CItemsRsltExprScript *)pSrc->GetNext(pos);

		pNew = (CItemsRsltExprScript *)FindByID(p->m_strID);

		if (pNew == NULL)
		{
			pNew = (CItemsRsltExprScript*)p->Clone();
			AddNewChild(pNew);
		}
		else
		{
// 			if (p->m_strItemsGlobalRsltScript != pNew->m_strItemsGlobalRsltScript)
// 			{
// 				CString strMsg;
// 				strMsg.Format(g_sLangTxt_ScriptOverwrite/*_T("脚本【%s】已经存在，并且两个脚本不一致，是否覆盖?")*/, p->m_strID);
// 				UINT nRet = AfxMessageBox(strMsg, MB_YESNO | MB_ICONQUESTION);
// 
// 				if (nRet == IDYES)
// 				{
// 					pNew->m_strItemsGlobalRsltScript = p->m_strItemsGlobalRsltScript;
// 				}
// 			}
		}
	}
}


//////////////////////////////////////////////////////////////////////////
CItemsRsltExprScriptMngrGlobalPool* CItemsRsltExprScriptMngrGlobalPool::g_pItemsGlobalRsltScriptMngrGlobalPool = NULL;
long CItemsRsltExprScriptMngrGlobalPool::g_nItemsGlobalRsltScriptMngrGlobalPool = 0;

CItemsRsltExprScriptMngrGlobalPool::CItemsRsltExprScriptMngrGlobalPool()
{

}

CItemsRsltExprScriptMngrGlobalPool::~CItemsRsltExprScriptMngrGlobalPool()
{
	
}

CItemsRsltExprScriptMngr* CItemsRsltExprScriptMngrGlobalPool::CreateItemsGlobalRsltScriptMngr(const CString &strFile)
{
	ASSERT (g_pItemsGlobalRsltScriptMngrGlobalPool != NULL);
	
	CString strScriptMngrFile = strFile;

	if (strScriptMngrFile.GetLength() == 0)
	{
		strScriptMngrFile = _T("GbExprScriptLibrary.xml");
	}

	CItemsRsltExprScriptMngr *pFind = (CItemsRsltExprScriptMngr*)g_pItemsGlobalRsltScriptMngrGlobalPool->FindByID(strScriptMngrFile);

	if (pFind != NULL)
	{
		return pFind;
	}

	pFind = new CItemsRsltExprScriptMngr();
	BOOL b = pFind->OpenScriptMngrFile(strScriptMngrFile);

	if (!b)
	{
		pFind->SaveScriptMngrFile(strScriptMngrFile);
	}

	g_pItemsGlobalRsltScriptMngrGlobalPool->AddNewChild(pFind);
	return pFind;
}


void CItemsRsltExprScriptMngrGlobalPool::Create()
{
	g_nItemsGlobalRsltScriptMngrGlobalPool++;

	if (g_nItemsGlobalRsltScriptMngrGlobalPool == 1)
	{
		g_pItemsGlobalRsltScriptMngrGlobalPool = new CItemsRsltExprScriptMngrGlobalPool();
	}
}

void CItemsRsltExprScriptMngrGlobalPool::Release()
{
	g_nItemsGlobalRsltScriptMngrGlobalPool--;

	if (g_nItemsGlobalRsltScriptMngrGlobalPool == 0)
	{
		delete g_pItemsGlobalRsltScriptMngrGlobalPool;
		g_pItemsGlobalRsltScriptMngrGlobalPool = NULL;
	}
}

