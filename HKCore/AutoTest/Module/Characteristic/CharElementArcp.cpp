//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementArcp.cpp  CCharElementArcp


#include "stdafx.h"
#include "CharElementArcp.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharElementArcp::CCharElementArcp()
{
	//初始化属性
	m_strID = CHAR_ELEMENT_ID_ARCP;

#ifndef NOT_USE_XLANGUAGE
	m_strName = g_sLangTxt_Arcp/*_T("圆弧（arcp）")*/;
#else
	m_strName = _T("圆弧（arcp）");
#endif

	//初始化成员变量
}

CCharElementArcp::~CCharElementArcp()
{
}

long CCharElementArcp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementArcBase::XmlReadOwn(oNode, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strZKey, oNode, m_strZ);
	xml_GetAttibuteValue(pXmlKeys->m_strPhKey, oNode, m_strPh);
	
	return 0;
}

long CCharElementArcp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementArcBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strZKey, oElement, m_strZ);
	xml_SetAttributeValue(pXmlKeys->m_strPhKey, oElement, m_strPh);
	
	return 0;
}

void CCharElementArcp::InitAfterRead()
{
}

BOOL CCharElementArcp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementArcp *p = (CCharElementArcp*)pObj;


	return TRUE;
}

BOOL CCharElementArcp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementArcBase::CopyOwn(pDest);

	CCharElementArcp *p = (CCharElementArcp*)pDest;

	p->m_strZ = m_strZ;
	p->m_strPh = m_strPh;
	
	return TRUE;
}

CBaseObject* CCharElementArcp::Clone()
{
	CCharElementArcp *p = new CCharElementArcp();
	Copy(p);
	return p;
}

long CCharElementArcp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CCharElementArcBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strZ);
		BinarySerializeCalLen(oBinaryBuffer, m_strPh);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strZ);
		BinarySerializeRead(oBinaryBuffer, m_strPh);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strZ);
		BinarySerializeWrite(oBinaryBuffer, m_strPh);
	}

	return 0;
}

CString CCharElementArcp::ReturnXml()
{
	//Format会引发乱码
	CString strZ = _T("z=") + m_strZ;
	CString strPh = _T("ph=") + m_strPh;
	CString strR = _T("r=") + m_strRadius;
	CString strStartAngle = _T("start-angle=") + m_strAngleBegin;
	CString strEndAngle = _T("end-angle=") + m_strAngleEnd;
	CString strCw = _T("cw=") + m_strClockwise;
	CString strDir = _T("dir=") + m_strDir;

	CString str;
	str = strZ + " " + strPh + " " + strR + " " + strStartAngle + " " + strEndAngle + " " + strCw + " " + strDir;
	return str;
}

void CCharElementArcp::Draw(CDC *pDC)
{
}

void CCharElementArcp::CalByExpression(BOOL bCalLines, CExBaseList *pDrawList)
{
	CCharElementArcBase::CalByExpression(bCalLines, pDrawList);

	double fZ = 0, fPh = 0;

	CalCharElementExpression(m_strZ, fZ, TRUE);
	CalCharElementExpression(m_strPh, fPh, TRUE);

	m_fYRadius = m_fXRadius;

	fPh = fPh * _PI_D_180;
	m_fXCenter = fZ * cos(fPh);
	m_fYCenter = fZ * sin(fPh);
}

CXDrawDataBase* CCharElementArcp::GetCXDrawDataBase()
{
	return this;
}
