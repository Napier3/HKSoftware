//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementLine.cpp  CCharElementLine


#include "stdafx.h"
#include "CharElementLine.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharElementLine::CCharElementLine()
{
	//初始化属性
	m_strID = "line";

#ifndef NOT_USE_XLANGUAGE
	m_strName = g_sLangTxt_Line/*_T("线（line）")*/;
#else
	m_strName = _T("线（line）");
#endif
	//初始化成员变量
}

CCharElementLine::~CCharElementLine()
{
}

long CCharElementLine::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharElement::XmlReadOwn(oNode, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strXKey, oNode, m_strX);
	xml_GetAttibuteValue(pXmlKeys->m_strYKey, oNode, m_strY);
	xml_GetAttibuteValue(pXmlKeys->m_strAngleKey, oNode, m_strAngle);

	return 0;
}

long CCharElementLine::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharElement::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strXKey, oElement, m_strX);
	xml_SetAttributeValue(pXmlKeys->m_strYKey, oElement, m_strY);
	xml_SetAttributeValue(pXmlKeys->m_strAngleKey, oElement, m_strAngle);

	return 0;
}

void CCharElementLine::InitAfterRead()
{
}

BOOL CCharElementLine::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementLine *p = (CCharElementLine*)pObj;

	if(m_strX != p->m_strX)
	{
		return FALSE;
	}

	if(m_strY != p->m_strY)
	{
		return FALSE;
	}

	if(m_strAngle != p->m_strAngle)
	{
		return FALSE;
	}

	if(m_strDir != p->m_strDir)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCharElementLine::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementLineBase::CopyOwn(pDest);
	CCharElementLine *p = (CCharElementLine*)pDest;

	p->m_strX = m_strX;
	p->m_strY = m_strY;
	p->m_strAngle = m_strAngle;

	return TRUE;
}

CBaseObject* CCharElementLine::Clone()
{
	CCharElementLine *p = new CCharElementLine();
	Copy(p);
	return p;
}

long CCharElementLine::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CCharElementLineBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strX);
		BinarySerializeCalLen(oBinaryBuffer, m_strY);
		BinarySerializeCalLen(oBinaryBuffer, m_strAngle);
		BinarySerializeCalLen(oBinaryBuffer, m_strDir);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strX);
		BinarySerializeRead(oBinaryBuffer, m_strY);
		BinarySerializeRead(oBinaryBuffer, m_strAngle);
		BinarySerializeRead(oBinaryBuffer, m_strDir);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strX);
		BinarySerializeWrite(oBinaryBuffer, m_strY);
		BinarySerializeWrite(oBinaryBuffer, m_strAngle);
		BinarySerializeWrite(oBinaryBuffer, m_strDir);
	}

	return 0;
}
CString CCharElementLine::ReturnXml()
{
	CString str;
    str.Format(_T("x=%s y=%s angle=%s dir=%s"),m_strX.GetString(),m_strY.GetString(),m_strAngle.GetString(),m_strDir.GetString());
	return str;
}

void CCharElementLine::Draw(CDC *pDC)
{
}


void CCharElementLine::CalByExpression(BOOL bCalLines, CExBaseList *pDrawList)
{
	//计算自身数据
	CalCharElementExpression(m_strX, m_fXb, TRUE);
	CalCharElementExpression(m_strY, m_fYb, TRUE);
	CalCharElementExpression(m_strAngle, m_fAngle, TRUE);
	Init_K_by_Angle();
	CXDrawData_Line::Set_Beeline();
	//CalCharElementExpression(m_strDir, m_nd, TRUE);
}

