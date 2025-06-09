//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharacteristicTmplate.cpp  CCharacteristicTmplate


#include "stdafx.h"
#include "CharacteristicTmplate.h"
#include "../../../Module/Expression/EpExpression.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharacteristicTmplate::CCharacteristicTmplate()
{
	//初始化属性
	m_nAutoClose = 0;

	//初始化成员变量
	m_pCharacteristic = NULL;
	m_pCharacteristicInterface = NULL;
	m_strTestLineMode = CHAR_TESTLINE_MODE_ID_PLUMB;

	m_fXMin = 0;
	m_fXMax = 10;
	m_fYMin = 0;
	m_fYMax = 10;

	m_bXMin = FALSE;
	m_bXMax = FALSE;
	m_bYMin = FALSE;
	m_bYMax = FALSE;
}

CCharacteristicTmplate::~CCharacteristicTmplate()
{
}

long CCharacteristicTmplate::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strAutoCloseKey, oNode, m_nAutoClose);
	xml_GetAttibuteValue(pXmlKeys->m_strAxisKey, oNode, m_strAxis);
	xml_GetAttibuteValue(pXmlKeys->m_strXMinKey, oNode, m_strXMin);
	xml_GetAttibuteValue(pXmlKeys->m_strXMaxKey, oNode, m_strXMax);
	xml_GetAttibuteValue(pXmlKeys->m_strYMinKey, oNode, m_strYMin);
	xml_GetAttibuteValue(pXmlKeys->m_strYMaxKey, oNode, m_strYMax);
	xml_GetAttibuteValue(pXmlKeys->m_strTestLineModeKey, oNode, m_strTestLineMode);

	return 0;
}

long CCharacteristicTmplate::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strAutoCloseKey, oElement, m_nAutoClose);
	xml_SetAttributeValue(pXmlKeys->m_strAxisKey, oElement, m_strAxis);
	xml_SetAttributeValue(pXmlKeys->m_strXMinKey, oElement, m_strXMin);
	xml_SetAttributeValue(pXmlKeys->m_strXMaxKey, oElement, m_strXMax);
	xml_SetAttributeValue(pXmlKeys->m_strYMinKey, oElement, m_strYMin);
	xml_SetAttributeValue(pXmlKeys->m_strYMaxKey, oElement, m_strYMax);
	xml_SetAttributeValue(pXmlKeys->m_strTestLineModeKey, oElement, m_strTestLineMode);

	return 0;
}

void CCharacteristicTmplate::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == CHARCLASSID_CCHARACTERISTIC)
		{
			m_pCharacteristic = (CCharacteristic*)p;
		}
		else if (nClassID == CHARCLASSID_CCHARINTERFACE)
		{
			m_pCharacteristicInterface = (CCharInterface*)p;
		}
	}

	if (m_pCharacteristic == NULL)
	{
		m_pCharacteristic = (CCharacteristic*)AddNewChild(new CCharacteristic());
		m_pCharacteristic->InitAfterRead();
	}

	if (m_pCharacteristicInterface == NULL)
	{
		m_pCharacteristicInterface = (CCharInterface*)AddNewChild(new CCharInterface());
	}

}

BOOL CCharacteristicTmplate::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CCharacteristicTmplate *p = (CCharacteristicTmplate*)pDest;
	p->m_nAutoClose = m_nAutoClose;
	p->m_strAxis = m_strAxis;
	p->m_strXMin = m_strXMin;
	p->m_strXMax = m_strXMax;
	p->m_strYMin = m_strYMin;
	p->m_strYMax = m_strYMax;
	p->m_strTestLineMode = m_strTestLineMode;

	p->m_fXMin = m_fXMin;
	p->m_fXMax = m_fXMax;
	p->m_fYMin = m_fYMin;
	p->m_fYMax = m_fYMax;

	return TRUE;
}

BOOL CCharacteristicTmplate::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CCharacteristicTmplate *p = (CCharacteristicTmplate*)pObj;
	if(m_nAutoClose != p->m_nAutoClose)
	{
		return FALSE;
	}

	if(m_strAxis != p->m_strAxis)
	{
		return FALSE;
	}

	if(m_strXMin != p->m_strXMin)
	{
		return FALSE;
	}

	if(m_strXMax != p->m_strXMax)
	{
		return FALSE;
	}

	if(m_strYMin != p->m_strYMin)
	{
		return FALSE;
	}

	if(m_strYMax != p->m_strYMax)
	{
		return FALSE;
	}
	return TRUE;
}

CBaseObject* CCharacteristicTmplate::Clone()
{
	CCharacteristicTmplate *p = new CCharacteristicTmplate();
	Copy(p);
	return p;
}

CExBaseObject* CCharacteristicTmplate::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCCharInterfaceKey)
	{
		pNew = new CCharInterface();
	}
	else if (strClassID == pXmlKeys->m_strCCharacteristicKey)
	{
		pNew = new CCharacteristic();
		((CCharacteristic*)pNew)->m_bOldVersion = TRUE;
	}

	return pNew;
}

CExBaseObject* CCharacteristicTmplate::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CHARCLASSID_CCHARINTERFACE)
	{
		pNew = new CCharInterface();
	}
	else if (nClassID == CHARCLASSID_CCHARACTERISTIC)
	{
		pNew = new CCharacteristic();
		((CCharacteristic*)pNew)->m_bOldVersion = TRUE;
	}

	return pNew;
}

long CCharacteristicTmplate::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseList::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nAutoClose);
		BinarySerializeCalLen(oBinaryBuffer, m_strAxis);
		BinarySerializeCalLen(oBinaryBuffer, m_strXMin);
		BinarySerializeCalLen(oBinaryBuffer, m_strXMax);
		BinarySerializeCalLen(oBinaryBuffer, m_strYMin);
		BinarySerializeCalLen(oBinaryBuffer, m_strYMax);
		BinarySerializeCalLen(oBinaryBuffer, m_strTestLineMode);

		BinarySerializeCalLen(oBinaryBuffer, m_fXMin);
		BinarySerializeCalLen(oBinaryBuffer, m_fXMax);
		BinarySerializeCalLen(oBinaryBuffer, m_fYMin);
		BinarySerializeCalLen(oBinaryBuffer, m_fYMax);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nAutoClose);
		BinarySerializeRead(oBinaryBuffer, m_strAxis);
		BinarySerializeRead(oBinaryBuffer, m_strXMin);
		BinarySerializeRead(oBinaryBuffer, m_strXMax);
		BinarySerializeRead(oBinaryBuffer, m_strYMin);
		BinarySerializeRead(oBinaryBuffer, m_strYMax);
		BinarySerializeRead(oBinaryBuffer, m_strTestLineMode);

		BinarySerializeRead(oBinaryBuffer, m_fXMin);
		BinarySerializeRead(oBinaryBuffer, m_fXMax);
		BinarySerializeRead(oBinaryBuffer, m_fYMin);
		BinarySerializeRead(oBinaryBuffer, m_fYMax);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nAutoClose);
		BinarySerializeWrite(oBinaryBuffer, m_strAxis);
		BinarySerializeWrite(oBinaryBuffer, m_strXMin);
		BinarySerializeWrite(oBinaryBuffer, m_strXMax);
		BinarySerializeWrite(oBinaryBuffer, m_strYMin);
		BinarySerializeWrite(oBinaryBuffer, m_strYMax);
		BinarySerializeWrite(oBinaryBuffer, m_strTestLineMode);

		BinarySerializeWrite(oBinaryBuffer, m_fXMin);
		BinarySerializeWrite(oBinaryBuffer, m_fXMax);
		BinarySerializeWrite(oBinaryBuffer, m_fYMin);
		BinarySerializeWrite(oBinaryBuffer, m_fYMax);
	}

	return 0;
}

CCharInterface* CCharacteristicTmplate::GetCharInterface()
{
	if (m_pCharacteristicInterface == NULL)
	{
		m_pCharacteristicInterface = new CCharInterface();
		AddNewChild(m_pCharacteristicInterface);
	}

	return m_pCharacteristicInterface;
}

CCharacteristic* CCharacteristicTmplate::GetCharacteristic()
{
	if (m_pCharacteristic == NULL)
	{
		m_pCharacteristic = new CCharacteristic();
		AddNewChild(m_pCharacteristic);
	}

	return m_pCharacteristic;
}

CCharInterface* CCharacteristicTmplate::DettachCCharInterface()
{
	Remove(m_pCharacteristicInterface);
	CCharInterface *pCharInterface = m_pCharacteristicInterface;
	m_pCharacteristicInterface = NULL;

	return pCharInterface;
}

BOOL CCharacteristicTmplate::CalCharElementExpression(const CString &strExpress, double &dValue, BOOL bLogError)
{
	if (strExpress.GetLength() == 0)
	{
		return FALSE;
	}

	CEpExpression oEpExp;

	if (oEpExp.ChangeEpExpression(strExpress) == -1)
	{
#ifndef NOT_USE_XLANGUAGE
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ExpressionError.GetString()/*_T("表达式【%s】 错误")*/
#else
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("表达式【%s】 错误")
#endif
                                   , strExpress.GetString());
		return FALSE;
	}

	CString strValue;
	POS pos = oEpExp.GetHeadPosition();
	CEpExpVariable *pExpVar = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pExpVar = oEpExp.GetNext(pos);

		if (m_pCharacteristicInterface->GetVariableValue(pExpVar->m_strVarID, strValue))
		{
            pExpVar->m_dValue = CString_To_double(strValue);
		}
		else
		{
			if (bLogError)
			{

#ifndef NOT_USE_XLANGUAGE
                CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ExpressionVariable.GetString()/*_T("表达式变量【%s】 错误")*/
#else
                CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("表达式变量【%s】 错误")
#endif
                                           , pExpVar->m_strVarID.GetString());
				bTrue = FALSE;
			}
		}
	}

	oEpExp.Value(dValue);

	return bTrue;
}

CCharacterArea* CCharacteristicTmplate::GetCharacterArea()
{
	ASSERT (m_pCharacteristic != NULL);
	return m_pCharacteristic->GetCharacterArea();
}

// CCharMacroDraws* CCharacteristicTmplate::GetCharMacroDraws()
// {
// 	ASSERT (m_pCharacteristic != NULL);
// 	return m_pCharacteristic->GetCharMacroDraws();
// }


void CCharacteristicTmplate::InitVariableValues()
{
	CCharInterface *pCharInterface = GetCharInterface();
	pCharInterface->InitVariableValues();
}

void CCharacteristicTmplate::CalCharElement(CExBaseList *pDrawList)
{
	m_strXMin.Trim();
	m_strYMin.Trim();
	m_strXMax.Trim();
	m_strYMax.Trim();

// 	m_pCharacteristicInterface->InitVariableValues();

	m_bXMin = CalCharElementExpression(m_strXMin, m_fXMin, TRUE);
	m_bYMin = CalCharElementExpression(m_strYMin, m_fYMin, TRUE);
	m_bXMax = CalCharElementExpression(m_strXMax, m_fXMax, TRUE);
	m_bYMax = CalCharElementExpression(m_strYMax, m_fYMax, TRUE);

	CCharacterArea *pCharArea = GetCharacterArea();
	pCharArea->CalCharElement(pDrawList, char_GetTestLineModeIndex(m_strTestLineMode));
}

void CCharacteristicTmplate::CalTestLines(CExBaseList *pDrawList)
{
	CCharacterArea *pCharArea = GetCharacterArea();
	pCharArea->CalTestLines(char_GetTestLineModeIndex(m_strTestLineMode));
}

void CCharacteristicTmplate::GetAllMacroTestLines(CExBaseList *pList)
{
	CCharacterArea *pCharArea = GetCharacterArea();
	pCharArea->GetAllMacroTestLines(pList);
}

void char_CChaTmplate_to_Characteristic(CCharacteristicTmplate *pCharTemplate, CCharacteristic* &pChar)
{
	pChar = pCharTemplate->GetCharacteristic();
	pChar->m_strName = pCharTemplate->m_strName;
	pChar->m_strID = pCharTemplate->m_strID;
	pChar->m_nAutoClose = pCharTemplate->m_nAutoClose;
	pChar->m_strAxis = pCharTemplate->m_strAxis;
	pChar->m_strXMin = pCharTemplate->m_strXMin;
	pChar->m_strXMax = pCharTemplate->m_strXMax;
	pChar->m_strYMin = pCharTemplate->m_strYMin;
	pChar->m_strYMax = pCharTemplate->m_strYMax;
	pChar->m_strTestLineMode = pCharTemplate->m_strTestLineMode;

	pChar->m_fXMin = pCharTemplate->m_fXMin;
	pChar->m_fXMax = pCharTemplate->m_fXMax;
	pChar->m_fYMin = pCharTemplate->m_fYMin;
	pChar->m_fYMax = pCharTemplate->m_fYMax;

	pChar->m_bXMin = pCharTemplate->m_bXMin;
	pChar->m_bXMax = pCharTemplate->m_bXMax;
	pChar->m_bYMin = pCharTemplate->m_bYMin;
	pChar->m_bYMax = pCharTemplate->m_bYMax;

	pChar->AttachCCharInterface(pCharTemplate->DettachCCharInterface());
	pCharTemplate->RemoveAll();
}

void char_CChaTmplate_to_Characteristic(CExBaseList *pList)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	POS posPrev = NULL;
	CCharacteristic *pNew = NULL;
	CCharacteristicTmplate *pCharTemplate = NULL;

	while (pos != NULL)
	{
		posPrev = pos;
		p = (CExBaseObject *)pList->GetNext(pos);

		if (p->GetClassID() == CHARCLASSID_CCHARACTERISTICTMPLATE)
		{
			pCharTemplate = (CCharacteristicTmplate *)p;
			char_CChaTmplate_to_Characteristic((CCharacteristicTmplate*)p, pNew);
			pList->SetAt(posPrev, pNew);
			pNew->SetParent(pList);
			delete p;
		}
	}
}

