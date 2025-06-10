//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Characteristic.cpp  CCharacteristic


#include "stdafx.h"
#include "Characteristic.h"
// #include "CharMacroDraws.h"
#include "../../Module/Expression/EpExpression.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "../GuideBook/GuideBookDefine.h"


CCharacteristic::CCharacteristic()
{
	//初始化属性

	//初始化成员变量
	m_pArea = NULL;
	m_pCharacteristicInterface = NULL;

	m_strTestLineMode = CHAR_TESTLINE_MODE_ID_PLUMB;
	m_strIndex = _T("1");
	m_nAutoClose = 0;

	m_fXMin = 0;
	m_fXMax = 10;
	m_fYMin = 0;
	m_fYMax = 10;

	m_bXMin = FALSE;
	m_bXMax = FALSE;
	m_bYMin = FALSE;
	m_bYMax = FALSE;
	m_bOldVersion = FALSE;
	m_pCharAttrs = NULL;
}

CCharacteristic::~CCharacteristic()
{
}

long CCharacteristic::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strAutoCloseKey, oNode, m_nAutoClose);
	xml_GetAttibuteValue(pXmlKeys->m_strAxisKey, oNode, m_strAxis);
	xml_GetAttibuteValue(pXmlKeys->m_strXMinKey, oNode, m_strXMin);
	xml_GetAttibuteValue(pXmlKeys->m_strXMaxKey, oNode, m_strXMax);
	xml_GetAttibuteValue(pXmlKeys->m_strYMinKey, oNode, m_strYMin);
	xml_GetAttibuteValue(pXmlKeys->m_strYMaxKey, oNode, m_strYMax);

// 	//2023.4.23 zhouhj 读取之后,给浮点赋值
// 	m_fXMin = CString_To_double(m_strXMin);
// 	m_fXMax = CString_To_double(m_strXMax);
// 	m_fYMin = CString_To_double(m_strYMin);
// 	m_fYMax = CString_To_double(m_strYMax);

	xml_GetAttibuteValue(pXmlKeys->m_strTestLineModeKey, oNode, m_strTestLineMode);
	xml_GetAttibuteValue(pXmlKeys->m_strIndexKey, oNode, m_strIndex);


	return 0;
}

long CCharacteristic::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
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
	xml_SetAttributeValue(pXmlKeys->m_strIndexKey, oElement, m_strIndex);

	return 0;
}

void CCharacteristic::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;
	CExBaseObject *pDraws = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == CHARCLASSID_CCHARACTERAREA)
		{
			m_pArea = (CCharacterArea*)p;
		}
		else if (nClassID == CHARCLASSID_CCHARINTERFACE)
		{
			m_pCharacteristicInterface = (CCharInterface*)p;
		}
		else if (nClassID == CHARCLASSID_CCHARMACRODRAWS)
		{
			pDraws = (CExBaseObject*)p;
		}
	}

	if (m_pArea == NULL)
	{
		m_pArea = (CCharacterArea*)AddNewChild(new CCharacterArea());
	}

	if (pDraws != NULL)
	{
		Delete(pDraws);
	}

	if (m_pCharacteristicInterface == NULL)
	{
		m_pCharacteristicInterface = (CCharInterface*)AddNewChild(new CCharInterface());
	}

	InitVariableValues();
}


BOOL CCharacteristic::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CCharacteristic *p = (CCharacteristic*)pObj;


	return TRUE;
}

BOOL CCharacteristic::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CCharacteristic *p = (CCharacteristic*)pDest;
	p->m_nAutoClose = m_nAutoClose;
	p->m_strAxis = m_strAxis;
	p->m_strXMin = m_strXMin;
	p->m_strXMax = m_strXMax;
	p->m_strYMin = m_strYMin;
	p->m_strYMax = m_strYMax;
	p->m_strTestLineMode = m_strTestLineMode;
	p->m_strIndex = m_strIndex;

	p->m_fXMin = m_fXMin;
	p->m_fXMax = m_fXMax;
	p->m_fYMin = m_fYMin;
	p->m_fYMax = m_fYMax;

	return TRUE;
}

CBaseObject* CCharacteristic::Clone()
{
	CCharacteristic *p = new CCharacteristic();
	Copy(p);
	return p;
}

BOOL CCharacteristic::CanPaste(UINT nClassID)
{
	if (nClassID == CHARCLASSID_CCHARACTERAREA)
	{
		return TRUE;
	}

	if (nClassID == CHARCLASSID_CCHARMACRODRAWS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CCharacteristic::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCCharacterAreaKey)
	{
		pNew = new CCharacterArea();
	}
	else if (strClassID == pXmlKeys->m_strCCharInterfaceKey)
	{
		pNew = new CCharInterface();
	}

	return pNew;
}

CExBaseObject* CCharacteristic::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CHARCLASSID_CCHARACTERAREA)
	{
		pNew = new CCharacterArea();
	}
	else if (nClassID == CHARCLASSID_CCHARINTERFACE)
	{
		pNew = new CCharInterface();
	}

	return pNew;
}


long CCharacteristic::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nAutoClose);
		BinarySerializeCalLen(oBinaryBuffer, m_strAxis);
		BinarySerializeCalLen(oBinaryBuffer, m_strXMin);
		BinarySerializeCalLen(oBinaryBuffer, m_strXMax);
		BinarySerializeCalLen(oBinaryBuffer, m_strYMin);
		BinarySerializeCalLen(oBinaryBuffer, m_strYMax);
		BinarySerializeCalLen(oBinaryBuffer, m_strTestLineMode);
		BinarySerializeCalLen(oBinaryBuffer, m_strIndex);//20211220 上位机软件用到 sf

		BinarySerializeCalLen(oBinaryBuffer, m_fXMin);
		BinarySerializeCalLen(oBinaryBuffer, m_fXMax);
		BinarySerializeCalLen(oBinaryBuffer, m_fYMin);
		BinarySerializeCalLen(oBinaryBuffer, m_fYMax);
		
		//2021-9-16  单机软件用得到，自动测试暂时用不到
		//BinarySerializeCalLen(oBinaryBuffer, m_strIndex);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		if (m_bOldVersion)
		{//兼容老版本测试记录文件，老版本中，是从CCharacteristicTmplate创建
			return 0;
		}

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

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_42)
		{
			BinarySerializeRead(oBinaryBuffer, m_strIndex);//20211220 上位机软件用到 sf
		}
		//2021-9-16  单机软件用得到，自动测试暂时用不到
		//BinarySerializeRead(oBinaryBuffer, m_strIndex);
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

		BinarySerializeWrite(oBinaryBuffer, m_strIndex);//20211220 上位机软件用到 sf
		////2021-9-16  单机软件用得到，自动测试暂时用不到
		//BinarySerializeWrite(oBinaryBuffer, m_strIndex);
	}

	return 0;
}

CCharacterArea* CCharacteristic::GetCharacterArea()
{
	if (m_pArea == NULL)
	{
		m_pArea = new CCharacterArea();
		AddNewChild(m_pArea);
	}

	return m_pArea;
}
// 
// CCharMacroDraws* CCharacteristic::GetCharMacroDraws()
// {
// 	if (m_pDraws == NULL)
// 	{
// 		m_pDraws = new CCharMacroDraws();
// 		AddNewChild(m_pDraws);
// 	}
// 
// 	return m_pDraws;
// }



CCharInterface* CCharacteristic::GetCharInterface()
{
	if (m_pCharacteristicInterface == NULL)
	{
		m_pCharacteristicInterface = new CCharInterface();
		AddNewChild(m_pCharacteristicInterface);
	}

	return m_pCharacteristicInterface;
}

BOOL CCharacteristic::CalCharElementExpression(const CString &strExpress, double &dValue, BOOL bLogError)
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

void CCharacteristic::AttachCCharInterface(CCharInterface *pCharInterface)
{
	if(m_pCharacteristicInterface != NULL)
	{
		Delete(m_pCharacteristicInterface);
	}

	m_pCharacteristicInterface = pCharInterface;
	AddNewChild(m_pCharacteristicInterface);
}


void CCharacteristic::InitVariableValues()
{
	CCharInterface *pCharInterface = GetCharInterface();
	pCharInterface->InitVariableValues();

	CCharacterArea *pCharArea = GetCharacterArea();
	pCharArea->InitElementTestLines(pCharInterface);
}

void CCharacteristic::CalCharElement(CExBaseList *pDrawList)
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

void CCharacteristic::CalTestLines(CExBaseList *pDrawList)
{
	CCharacterArea *pCharArea = GetCharacterArea();
	pCharArea->CalTestLines(char_GetTestLineModeIndex(m_strTestLineMode));
}

void CCharacteristic::GetAllMacroTestLines(CExBaseList *pList)
{
	CCharacterArea *pCharArea = GetCharacterArea();
	pCharArea->GetAllMacroTestLines(pList);
}

BOOL CCharacteristic::CmpAttrs(CDvmData *pAttrs)
{
	if (m_pCharAttrs == NULL || pAttrs == NULL)
	{
		return FALSE;
	}
	
	POS pos = pAttrs->GetHeadPosition();
	CDvmValue *pAttr = NULL;
	BOOL bTrue = FALSE;

	while (pos != NULL)
	{
		pAttr = (CDvmValue *)pAttrs->GetNext(pos);

		if (m_pCharAttrs->FindByName(pAttr->m_strName) == NULL)
		{
			return FALSE;
		}
	}

	return TRUE;
}

CDvmData* CCharacteristic::GetAttrs(BOOL bCreateNew)
{
	if (bCreateNew)
	{
		if (m_pCharAttrs == NULL)
		{
			m_pCharAttrs = new CDvmData();
			AddNewChild(m_pCharAttrs);
		}
	}

	return m_pCharAttrs;
}

//添加特性曲线与测试测试项目的接口
//2020-3-19
void CCharacteristic::DeleteAllTestLines()
{
	GetCharacterArea();
	ASSERT (m_pArea);
	m_pArea->DeleteAllTestLines();
}

void CCharacteristic::AddTestLines(CXDrawData_Line *pValRange, double dLenStep)
{
	GetCharacterArea();
	ASSERT (m_pArea);
	m_pArea->AddTestLines(pValRange, dLenStep);
}

void CCharacteristic::AddTestLine(CXDrawData_Line *pCurrValLine)
{
	GetCharacterArea();
	ASSERT (m_pArea);
	m_pArea->AddTestLine(pCurrValLine);
}

CXDrawList* CCharacteristic::InitCharDrawElement_ForDraw()
{
	CCharacterArea *pCharArea = GetCharacterArea();
	CXDrawList *pDrawList = (CXDrawList*)pCharArea->DettachDrawListRef();

	if (pDrawList == NULL)
	{
		pDrawList = new CXDrawList();
		pCharArea->SetDrawListRef(pDrawList);
	}
	else
	{
		pDrawList->DeleteAll();
	}

	pCharArea->InitCharDrawElement(pDrawList, FALSE);

	return pDrawList;
}

CXDrawList* CCharacteristic::InitCharDrawElement_ForCalOnly()
{
	CCharacterArea *pCharArea = GetCharacterArea();
	CXDrawList *pDrawList = (CXDrawList*)pCharArea->GetDrawListRef();

	if (pDrawList == NULL)
	{
		pDrawList = (CXDrawList*)pCharArea->CreateDrawListRef();
	}
	else
	{
		pDrawList->DeleteAll();
	}

	pCharArea->InitCharDrawElement(pDrawList, FALSE);

	return pDrawList;
}


void CCharacteristic::InitAllMacroTestLinesID()
{
	CExBaseList listLine;
	GetAllMacroTestLines(&listLine);
	CCharElementTestLine *p = NULL;
	POS pos = listLine.GetHeadPosition();
	long nIndex = 0;

	if (pos == NULL)
	{
		return;
	}

	p = (CCharElementTestLine *)listLine.GetAt(pos);

	//只初始化一次
	if (p->m_strID.GetLength() > 0)
	{
		return;
	}

	while (pos != NULL)
	{
		p = (CCharElementTestLine *)listLine.GetNext(pos);
		p->m_strID.Format(_T("%s"), CharElementTestLine_ID, nIndex);
		nIndex++;
	}
	
	listLine.RemoveAll();
}

CCharElementTestLine* CCharacteristic::FindTestLine(const CString &strID)
{
	CExBaseList listLine;
	GetAllMacroTestLines(&listLine);
	CCharElementTestLine *pFind = (CCharElementTestLine*)listLine.FindByID(strID);
	listLine.RemoveAll();

	return pFind;
}

