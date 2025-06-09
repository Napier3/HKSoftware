//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Characteristic.cpp  CCharacteristic


#include "stdafx.h"
#include "Characteristic.h"

CCharacteristic::CCharacteristic()
{
	//初始化属性
	m_nAutoClose = 0;

	//初始化成员变量
	m_pArea = NULL;
	m_pDraws = NULL;
}

CCharacteristic::~CCharacteristic()
{
}

long CCharacteristic::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strAutoCloseKey, oNode, m_nAutoClose);
	xml_GetAttibuteValue(pXmlKeys->m_strAxisKey, oNode, m_strAxis);
	xml_GetAttibuteValue(pXmlKeys->m_strXMinKey, oNode, m_strXMin);
	xml_GetAttibuteValue(pXmlKeys->m_strXMaxKey, oNode, m_strXMax);
	xml_GetAttibuteValue(pXmlKeys->m_strYMinKey, oNode, m_strYMin);
	xml_GetAttibuteValue(pXmlKeys->m_strYMaxKey, oNode, m_strYMax);
	return 0;
}

long CCharacteristic::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strAutoCloseKey, oElement, m_nAutoClose);
	xml_SetAttributeValue(pXmlKeys->m_strAxisKey, oElement, m_strAxis);
	xml_SetAttributeValue(pXmlKeys->m_strXMinKey, oElement, m_strXMin);
	xml_SetAttributeValue(pXmlKeys->m_strXMaxKey, oElement, m_strXMax);
	xml_SetAttributeValue(pXmlKeys->m_strYMinKey, oElement, m_strYMin);
	xml_SetAttributeValue(pXmlKeys->m_strYMaxKey, oElement, m_strYMax);
	return 0;
}

void CCharacteristic::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == CHARCLASSID_CCHARACTERAREA)
		{
			m_pArea = (CCharacterArea*)p;
		}
		else if (nClassID == CHARCLASSID_CCHARMACRODRAWS)
		{
			m_pDraws = (CCharMacroDraws*)p;
		}
	}

	if (m_pArea == NULL)
	{
		m_pArea = (CCharacterArea*)AddNewChild(new CCharacterArea());
	}

	if (m_pDraws == NULL)
	{
		m_pDraws = (CCharMacroDraws*)AddNewChild(new CCharMacroDraws());
	}

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
	else if (strClassID == pXmlKeys->m_strCCharMacroDrawsKey)
	{
		pNew = new CCharMacroDraws();
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
	else if (nClassID == CHARCLASSID_CCHARMACRODRAWS)
	{
		pNew = new CCharMacroDraws();
	}

	return pNew;
}
