//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementArc.cpp  CCharElementArc


#include "stdafx.h"
#include "CharElementArc.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharElementArc::CCharElementArc()
{
	//初始化属性
	m_strID = CHAR_ELEMENT_ID_ARC;

#ifndef NOT_USE_XLANGUAGE
	m_strName = g_sLangTxt_Arc/*_T("圆弧（arc）")*/;
#else
	m_strName = _T("圆弧（arc）");
#endif


	//初始化成员变量
}

CCharElementArc::~CCharElementArc()
{
}

long CCharElementArc::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementArcBase::XmlReadOwn(oNode, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strXKey, oNode, m_strXCenter);
	xml_GetAttibuteValue(pXmlKeys->m_strYKey, oNode, m_strYCenter);

	return 0;
}

long CCharElementArc::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementArcBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strXKey, oElement, m_strXCenter);
	xml_SetAttributeValue(pXmlKeys->m_strYKey, oElement, m_strYCenter);

	return 0;
}

void CCharElementArc::InitAfterRead()
{
}

BOOL CCharElementArc::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementArc *p = (CCharElementArc*)pObj;

	return TRUE;
}

BOOL CCharElementArc::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementArcBase::CopyOwn(pDest);

	CCharElementArc *p = (CCharElementArc*)pDest;

	p->m_strXCenter = m_strXCenter;
	p->m_strYCenter = m_strYCenter;

	return TRUE;
}

CBaseObject* CCharElementArc::Clone()
{
	CCharElementArc *p = new CCharElementArc();
	Copy(p);
	return p;
}

long CCharElementArc::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CCharElementArcBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strXCenter);
		BinarySerializeCalLen(oBinaryBuffer, m_strYCenter);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strXCenter);
		BinarySerializeRead(oBinaryBuffer, m_strYCenter);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strXCenter);
		BinarySerializeWrite(oBinaryBuffer, m_strYCenter);
	}

	return 0;
}
CString CCharElementArc::ReturnXml()
{
	CString str;
    str.Format(_T("arcp start-angle=\" %s \" end-angle=\"%s \" x=\"%s\" y=\" %s \" radius=\"%s \" dir=\"%s \"")
               ,m_strAngleBegin.GetString(),m_strAngleEnd.GetString()
               ,m_strXCenter.GetString(),m_strYCenter.GetString()
               ,m_strRadius.GetString(),m_strDir.GetString());
	return str;
}

void CCharElementArc::Draw(CDC *pDC)
{

}

void CCharElementArc::CalByExpression(BOOL bCalLines, CExBaseList *pDrawList)
{
	CCharElementArcBase::CalByExpression(bCalLines, pDrawList);

	CalCharElementExpression(m_strXCenter, m_fXCenter, TRUE);
	CalCharElementExpression(m_strYCenter, m_fYCenter, TRUE);

	m_fYRadius = m_fXRadius;
}

CXDrawDataBase* CCharElementArc::GetCXDrawDataBase()
{
	return this;
}
