//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementLinep.cpp  CCharElementLinep


#include "stdafx.h"
#include "CharElementLinep.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

CCharElementLinep::CCharElementLinep()
{
	//初始化属性
	m_strID = "linep";

#ifndef NOT_USE_XLANGUAGE
	m_strName = g_sLangTxt_Linep/*_T("线（linep）")*/;
#else
	m_strName = _T("线（linep）");
#endif
	//初始化成员变量
}

CCharElementLinep::~CCharElementLinep()
{
}

long CCharElementLinep::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharElement::XmlReadOwn(oNode, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strZKey, oNode, m_strZ);
	xml_GetAttibuteValue(pXmlKeys->m_strPhKey, oNode, m_strPh);
	xml_GetAttibuteValue(pXmlKeys->m_strAngleKey, oNode, m_strAngle);

	return 0;
}

long CCharElementLinep::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharElement::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strZKey, oElement, m_strZ);
	xml_SetAttributeValue(pXmlKeys->m_strPhKey, oElement, m_strPh);
	xml_SetAttributeValue(pXmlKeys->m_strAngleKey, oElement, m_strAngle);

	return 0;
}

void CCharElementLinep::InitAfterRead()
{
}

BOOL CCharElementLinep::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementLinep *p = (CCharElementLinep*)pObj;

	if(m_strZ != p->m_strZ)
	{
		return FALSE;
	}

	if(m_strPh != p->m_strPh)
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

BOOL CCharElementLinep::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementLineBase::CopyOwn(pDest);
	CCharElementLinep *p = (CCharElementLinep*)pDest;

	p->m_strZ = m_strZ;
	p->m_strPh = m_strPh;
	p->m_strAngle = m_strAngle;

	return TRUE;
}


CBaseObject* CCharElementLinep::Clone()
{
	CCharElementLinep *p = new CCharElementLinep();
	Copy(p);
	return p;
}

long CCharElementLinep::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CCharElementLineBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strZ);
		BinarySerializeCalLen(oBinaryBuffer, m_strPh);
		BinarySerializeCalLen(oBinaryBuffer, m_strAngle);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strZ);
		BinarySerializeRead(oBinaryBuffer, m_strPh);
		BinarySerializeRead(oBinaryBuffer, m_strAngle);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strZ);
		BinarySerializeWrite(oBinaryBuffer, m_strPh);
		BinarySerializeWrite(oBinaryBuffer, m_strAngle);
	}
	return 0;
}

CString CCharElementLinep::ReturnXml()
{
	CString str;
    str.Format(_T("linep angle=\"%s\" z=\"%s\" ph=\"%s\" dir=\"%s\" ")
               ,m_strAngle.GetString(),m_strZ.GetString(),m_strPh.GetString(),m_strDir.GetString());
	return str;
}


void CCharElementLinep::Draw(CDC *pDC)
{
}

void CCharElementLinep::CalByExpression(BOOL bCalLines, CExBaseList *pDrawList)
{
	//计算自身数据
	double fZ = 0, fPh = 0;

	CalCharElementExpression(m_strZ, fZ, TRUE);
	CalCharElementExpression(m_strPh, fPh, TRUE);
	CalCharElementExpression(m_strAngle, m_fAngle, TRUE);

	fPh = fPh * _PI_D_180;
	m_fXb = fZ * sin(fPh);
	m_fYb = fZ * cos(fPh);

	Init_K_by_Angle();
	CXDrawData_Line::Set_Beeline();
}
