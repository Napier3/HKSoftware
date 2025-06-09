//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapYcAnalysisItem.cpp  CEpCapYcAnalysisItem


#include "stdafx.h"
#include "EpCapYcAnalysisItem.h"

CEpCapYcAnalysisItem::CEpCapYcAnalysisItem()
{
	//初始化属性
	m_nItemIndex = 0;
	m_nColor = RGB(0, 0, 0);
	m_nDrawType = DRAWTYPE_STEPLINE;

	//初始化成员变量
}

CEpCapYcAnalysisItem::~CEpCapYcAnalysisItem()
{
}

long CEpCapYcAnalysisItem::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strItemIndexKey, oNode, m_nItemIndex);
	xml_GetAttibuteValue(pXmlKeys->m_strColorKey, oNode, m_nColor);
	xml_GetAttibuteValue(pXmlKeys->m_strDrawTypeKey, oNode, m_nDrawType);

	return 0;
}

long CEpCapYcAnalysisItem::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strItemIndexKey, oElement, m_nItemIndex);
	xml_SetAttributeValue(pXmlKeys->m_strColorKey, oElement, m_nColor);
	xml_SetAttributeValue(pXmlKeys->m_strDrawTypeKey, oElement, m_nDrawType);
	return 0;
}


BOOL CEpCapYcAnalysisItem::CopyOwn(CBaseObject* pDest)
{
	CEpCapYcAnalysisItem *p = (CEpCapYcAnalysisItem*)pDest;

	if (p == this)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	p->m_nItemIndex = m_nItemIndex;
	p->m_nColor = m_nColor;
	p->m_nDrawType = m_nDrawType;

	return TRUE;
}

CBaseObject* CEpCapYcAnalysisItem::Clone()
{
	CEpCapYcAnalysisItem *pNew = new CEpCapYcAnalysisItem();
	Copy(pNew);

	return pNew;
}

