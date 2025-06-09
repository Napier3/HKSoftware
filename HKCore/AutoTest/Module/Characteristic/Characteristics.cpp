//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Characteristics.cpp  CCharacteristics


#include "stdafx.h"
#include "Characteristics.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharacteristics::CCharacteristics()
{
	//初始化属性

#ifndef NOT_USE_XLANGUAGE
	m_strName = g_sLangTxt_ChrctCurDefn/*_T("特性曲线定义")*/;
#else
	m_strName = _T("特性曲线定义");
#endif
	m_strID = _T("_characteristics");

	//初始化成员变量
}

CCharacteristics::~CCharacteristics()
{
}

long CCharacteristics::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CCharacteristics::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	return 0;
}

void CCharacteristics::InitAfterRead()
{
	char_CChaTmplate_to_Characteristic(this);
}

BOOL CCharacteristics::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharacteristics *p = (CCharacteristics*)pObj;

	return TRUE;
}

BOOL CCharacteristics::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharacteristics *p = (CCharacteristics*)pDest;

	return TRUE;
}

CBaseObject* CCharacteristics::Clone()
{
	CCharacteristics *p = new CCharacteristics();
	Copy(p);
	return p;
}

BOOL CCharacteristics::CanPaste(UINT nClassID)
{
	if (nClassID == CHARCLASSID_CCHARACTERISTIC)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CCharacteristics::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCCharacteristicTmplateKey)
	{
		pNew = new CCharacteristicTmplate();
	}
	else if (strClassID == pXmlKeys->m_strCCharacteristicKey)
	{
		pNew = new CCharacteristic();
	}

	return pNew;
}

CExBaseObject* CCharacteristics::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CHARCLASSID_CCHARACTERISTICTMPLATE)
	{
		pNew = new CCharacteristicTmplate();
	}
	else if (nClassID == CHARCLASSID_CCHARACTERISTIC)
	{
		pNew = new CCharacteristic();
	}

	return pNew;
}

long CCharacteristics::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseList::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}

	return 0;
}

void CCharacteristics::InitVariableValues()
{
	POS pos = GetHeadPosition();
	CCharacteristic *pCharTempl = NULL;

	while (pos != NULL)
	{
		pCharTempl = (CCharacteristic*)GetNext(pos);
		ASSERT (pCharTempl->GetClassID() == CHARCLASSID_CCHARACTERISTIC);
		pCharTempl->InitVariableValues();
	}
}

void CCharacteristics::CalCharElement(CExBaseList *pDrawList)
{
	POS pos = GetHeadPosition();
	CCharacteristic *pCharTempl = NULL;

	while (pos != NULL)
	{
		pCharTempl = (CCharacteristic *)GetNext(pos);
		ASSERT (pCharTempl->GetClassID() == CHARCLASSID_CCHARACTERISTIC);
		pCharTempl->CalCharElement(pDrawList);
	}
}

BOOL CCharacteristics::IsCharTempExist(CCharacteristic *pCharTmp)
{
	POS pos = GetHeadPosition();
	CCharacteristic *p = NULL;
	BOOL bFind = FALSE;

	while (pos != NULL)
	{
		p = (CCharacteristic *)GetNext(pos);

		if (p->IsEqual(pCharTmp))
		{
			bFind = TRUE;
			break;
		}
	}

	return bFind;
}

BOOL CCharacteristics::AddCharTempClone(CCharacteristic *pCharTmp)
{
	if (IsCharTempExist(pCharTmp))
	{
		return FALSE;
	}

	CCharacteristic *pNew = (CCharacteristic*)pCharTmp->Clone();
	AddNewChild(pNew);

	return TRUE;
}

CCharacteristic* CCharacteristics::FindChar(CDvmData *pAttrs)
{
	POS pos = GetHeadPosition();
	CCharacteristic *p = NULL;
	CCharacteristic *pFind = NULL;

	while (pos != NULL)
	{
		p = (CCharacteristic *)GetNext(pos);

		if (p->CmpAttrs(pAttrs))
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

//2021-9-17  初始化空的特性曲线
void CCharacteristics::InitEmptyCharacter(const CString &strAxis)
{
	if (GetCount() > 0)
	{
		return;
	}

	CCharacteristic *pCharTemp = new CCharacteristic();
	pCharTemp->m_strAxis = strAxis;
	AddNewChild(pCharTemp);
}

//2023-2-15  shaolei   通过id和index，结合查找特性曲线
CCharacteristic* CCharacteristics::FindCharByID_Index(const CString &strID, const CString &strIndex)
{
	POS pos = GetHeadPosition();
	CCharacteristic *p = NULL;
	CCharacteristic *pFind = NULL;

	while (pos != NULL)
	{
		p = (CCharacteristic *)GetNext(pos);

		if (p->m_strID == strID
			&& p->m_strIndex == strIndex)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}