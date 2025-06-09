//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttGdColDef.cpp  CSttGdColDef


#include "stdafx.h"
#include "SttGdColDef.h"
#include "../../../../../AutoTest/Module/XLanguageResourceAts.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttGdColDef::CSttGdColDef()
{
	//初始化属性
	m_nEditable = 0;
	m_nWidth = 50;
	m_fRate = 1.0;
	m_nSettingAttach = 0;
	//初始化成员变量
}

CSttGdColDef::~CSttGdColDef()
{
}

long CSttGdColDef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strData_TypeKey, oNode, m_strDataType);
	xml_GetAttibuteValue(pXmlKeys->m_strUnitKey, oNode, m_strUnit);
	xml_GetAttibuteValue(pXmlKeys->m_strDecimalKey, oNode, m_strDecimal);
	xml_GetAttibuteValue(pXmlKeys->m_strMaxKey, oNode, m_strMax);
	xml_GetAttibuteValue(pXmlKeys->m_strMinKey, oNode, m_strMin);
	xml_GetAttibuteValue(pXmlKeys->m_strEditableKey, oNode, m_nEditable);
	xml_GetAttibuteValue(pXmlKeys->m_strWidthKey, oNode, m_nWidth);
	xml_GetAttibuteValue(pXmlKeys->m_strCtrl_TypeKey, oNode, m_strCtrlType);
	xml_GetAttibuteValue(pXmlKeys->m_strRateKey, oNode, m_fRate);
	xml_GetAttibuteValue(pXmlKeys->m_strSetting_AttachKey, oNode, m_nSettingAttach);
	return 0;
}

long CSttGdColDef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strData_TypeKey, oElement, m_strDataType);
	xml_SetAttributeValue(pXmlKeys->m_strUnitKey, oElement, m_strUnit);
	xml_SetAttributeValue(pXmlKeys->m_strDecimalKey, oElement, m_strDecimal);
	xml_SetAttributeValue(pXmlKeys->m_strMaxKey, oElement, m_strMax);
	xml_SetAttributeValue(pXmlKeys->m_strMinKey, oElement, m_strMin);
	xml_SetAttributeValue(pXmlKeys->m_strEditableKey, oElement, m_nEditable);
	xml_SetAttributeValue(pXmlKeys->m_strWidthKey, oElement, m_nWidth);
	xml_SetAttributeValue(pXmlKeys->m_strCtrl_TypeKey, oElement, m_strCtrlType);
	xml_SetAttributeValue(pXmlKeys->m_strRateKey, oElement, m_fRate);
	xml_SetAttributeValue(pXmlKeys->m_strSetting_AttachKey, oElement, m_nSettingAttach);
	return 0;
}

long CSttGdColDef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDataType);
		BinarySerializeCalLen(oBinaryBuffer, m_strUnit);
		BinarySerializeCalLen(oBinaryBuffer, m_strDecimal);
		BinarySerializeCalLen(oBinaryBuffer, m_strMax);
		BinarySerializeCalLen(oBinaryBuffer, m_strMin);
		BinarySerializeCalLen(oBinaryBuffer, m_nEditable);
		BinarySerializeCalLen(oBinaryBuffer, m_nWidth);
		BinarySerializeCalLen(oBinaryBuffer, m_strCtrlType);
		BinarySerializeCalLen(oBinaryBuffer, m_fRate);
		BinarySerializeCalLen(oBinaryBuffer, m_nSettingAttach);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDataType);
		BinarySerializeRead(oBinaryBuffer, m_strUnit);
		BinarySerializeRead(oBinaryBuffer, m_strDecimal);
		BinarySerializeRead(oBinaryBuffer, m_strMax);
		BinarySerializeRead(oBinaryBuffer, m_strMin);
		BinarySerializeRead(oBinaryBuffer, m_nEditable);
		BinarySerializeRead(oBinaryBuffer, m_nWidth);
		BinarySerializeRead(oBinaryBuffer, m_strCtrlType);
		BinarySerializeRead(oBinaryBuffer, m_fRate);
		BinarySerializeRead(oBinaryBuffer, m_nSettingAttach);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDataType);
		BinarySerializeWrite(oBinaryBuffer, m_strUnit);
		BinarySerializeWrite(oBinaryBuffer, m_strDecimal);
		BinarySerializeWrite(oBinaryBuffer, m_strMax);
		BinarySerializeWrite(oBinaryBuffer, m_strMin);
		BinarySerializeWrite(oBinaryBuffer, m_nEditable);
		BinarySerializeWrite(oBinaryBuffer, m_nWidth);
		BinarySerializeWrite(oBinaryBuffer, m_strCtrlType);
		BinarySerializeWrite(oBinaryBuffer, m_fRate);
		BinarySerializeWrite(oBinaryBuffer, m_nSettingAttach);
	}
	return 0;
}

void CSttGdColDef::InitAfterRead()
{
}

BOOL CSttGdColDef::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttGdColDef *p = (CSttGdColDef*)pObj;

	if(m_strDataType != p->m_strDataType)
	{
		return FALSE;
	}

	if(m_strUnit != p->m_strUnit)
	{
		return FALSE;
	}

	if(m_strDecimal != p->m_strDecimal)
	{
		return FALSE;
	}

	if(m_strMax != p->m_strMax)
	{
		return FALSE;
	}

	if(m_strMin != p->m_strMin)
	{
		return FALSE;
	}

	if(m_nEditable != p->m_nEditable)
	{
		return FALSE;
	}

	if(m_nWidth != p->m_nWidth)
	{
		return FALSE;
	}

	if(m_strCtrlType != p->m_strCtrlType)
	{
		return FALSE;
	}

	if(m_fRate != p->m_fRate)
	{
		return FALSE;
	}

	if(m_nSettingAttach != p->m_nSettingAttach)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttGdColDef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttGdColDef *p = (CSttGdColDef*)pDest;

	p->m_strDataType = m_strDataType;
	p->m_strUnit = m_strUnit;
	p->m_strDecimal = m_strDecimal;
	p->m_strMax = m_strMax;
	p->m_strMin = m_strMin;
	p->m_nEditable = m_nEditable;
	p->m_nWidth = m_nWidth;
	p->m_strCtrlType = m_strCtrlType;
	p->m_fRate = m_fRate;
	p->m_nSettingAttach = m_nSettingAttach;
	return TRUE;
}

CBaseObject* CSttGdColDef::Clone()
{
	CSttGdColDef *p = new CSttGdColDef();
	Copy(p);
	return p;
}

CBaseObject* CSttGdColDef::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttGdColDef *p = new CSttGdColDef();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttGdColDef::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTGDCOLDEF_PARA)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTGDCOLDEF_SCRIPT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttGdColDef::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttGdColDef_ParaKey)
	{
		pNew = new CSttGdColDef_Para();
	}
	else if (strClassID == pXmlKeys->m_strCSttGdColDef_ScriptKey)
	{
		pNew = new CSttGdColDef_Script();
	}

	return pNew;
}

CExBaseObject* CSttGdColDef::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTGDCOLDEF_PARA)
	{
		pNew = new CSttGdColDef_Para();
	}
	else if (nClassID == MNGRCLASSID_CSTTGDCOLDEF_SCRIPT)
	{
		pNew = new CSttGdColDef_Script();
	}

	return pNew;
}

CString CSttGdColDef::GetParaID()
{
	CSttGdColDef_Para *pSttGdColDef_Para = (CSttGdColDef_Para*)FindByClassID(MNGRCLASSID_CSTTGDCOLDEF_PARA);

	if (pSttGdColDef_Para == NULL)
	{
		return "";
	}

	return pSttGdColDef_Para->m_strID;
}

BOOL CSttGdColDef::IsCombBoxCtrl()
{
	if (m_strCtrlType == STT_TESTGRID_COL_CTRL_TYPE_CombBox)
	{
		return TRUE;
	}

	if (m_strDataType.IsEmpty())
	{
		return FALSE;
	}

	if (m_strDataType == "double")
	{
		return FALSE;
	}
	else if (m_strDataType == "float")
	{
		return FALSE;
	}
	else if (m_strDataType == "long")
	{
		return FALSE;
	}
	else if (m_strDataType == "int")
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttGdColDef::IsRateItemCtrl()
{
	if (m_strCtrlType == STT_TESTGRID_COL_CTRL_TYPE_RateItem)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CSttGdColDef::IsZSettingItemCtrl()
{
	if (m_strCtrlType == STT_TESTGRID_COL_CTRL_TYPE_ZSettingItem)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CSttGdColDef::IsImpedanceCustomItemCtrl()
{
	if (m_strCtrlType == STT_TESTGRID_COL_CTRL_TYPE_ImpedanceCustomItem)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CSttGdColDef::GetTestRsltString(CDvmValues *pDvmValues, CShortDatas *pResults, CString &strText)
{
	if (pDvmValues == NULL)
	{
		return FALSE;
	}

	CSttGdColDef_Script *pSttGdColDef_Script = (CSttGdColDef_Script*)FindByClassID(MNGRCLASSID_CSTTGDCOLDEF_SCRIPT);

	//如果脚本计算为空,则采用直接获取结果参数的方式
	if (pSttGdColDef_Script == NULL)
	{
		return GetTestRsltStringByResultParas(pDvmValues, pResults, strText);
	}

	if (!pSttGdColDef_Script->m_strDataID.IsEmpty())
	{
		CDvmValue *pValue = (CDvmValue*)pDvmValues->FindByID(pSttGdColDef_Script->m_strDataID);

		if (pValue != NULL)
		{
			double dValue = CString_To_double(pValue->m_strValue);
			long nDecimal = 3;

			if (!m_strDecimal.IsEmpty())
			{
				nDecimal = CString_To_long(m_strDecimal);
			}

			CString strFormat;
			strFormat.Format(_T("%%.%dlf "),nDecimal);
			strText.Format(strFormat.GetString(),dValue);

			if (!m_strUnit.IsEmpty())
			{
				strText += m_strUnit;
			}

			return TRUE;
		}
	}

	CSttGdColDef_Fuc_Base *pCSttGdColDef_Fuc_Base = (CSttGdColDef_Fuc_Base*)pSttGdColDef_Script->GetHead();

	if (pCSttGdColDef_Fuc_Base == NULL)
	{
		return FALSE;
	}

	return pCSttGdColDef_Fuc_Base->GetTestRsltString(pDvmValues,strText);
}

BOOL CSttGdColDef::GetTestRsltStringByResultParas(CDvmValues *pDvmValues, CShortDatas *pResults, CString &strText)
{
	/*20240729 wanmj*/
	BOOL bRet = FALSE;
	CShortData *pRltData = NULL;    //获取结果单位
	CDvmValue *pCurrValue = NULL;
	CExBaseObject *pCurrObj = NULL;
	double dValue = 0.0f;
	CString strUnit, strFormat;
	strText = "";
	long nDecimal = 3;

	if (!m_strDecimal.IsEmpty())
	{
		nDecimal = CString_To_long(m_strDecimal);
	}

	strFormat.Format(_T("%%.%dlf "), nDecimal);
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pCurrObj = GetNext(pos);

		if (pCurrObj->GetClassID() != MNGRCLASSID_CSTTGDCOLDEF_PARA)
		{
			continue;
		}

		pCurrValue = (CDvmValue*)pDvmValues->FindByID(pCurrObj->m_strID);

		if (pCurrValue == NULL)
		{
			continue;
		}

		bRet = TRUE;
		strUnit = "";
		pRltData = (CShortData*)pResults->FindByID(pCurrObj->m_strID);

		if (pRltData != NULL)
		{
			strUnit = pRltData->m_strUnit;
		}

		dValue = CString_To_double(pCurrValue->m_strValue);

		if ((pCurrValue->m_strValue == g_sLangTxt_Unact)||//优先动作的值放在前面,如果前面的出现未动作,后面的都不会动作
			((strUnit != "°") && (dValue<0.0001f)))//后续把角度换成多语言
		{
			if (strText.IsEmpty())
			{
				strText = g_sLangTxt_Unact;
			}
			
			break;
		}

		if (!strText.IsEmpty())
		{
			strText += ",";
		}

		strText += pCurrObj->m_strName;
		strText.AppendFormat(strFormat.GetString(), dValue);
		strText += strUnit;
	}

	return bRet;
}
