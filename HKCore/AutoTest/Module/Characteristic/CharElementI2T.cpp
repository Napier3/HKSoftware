//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementI2T.cpp  CCharElementI2T


#include "stdafx.h"
#include "CharElementI2T.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharElementI2T::CCharElementI2T()
{
	//初始化属性
	m_strID = CHAR_ELEMENT_ID_I2T;

#ifndef NOT_USE_XLANGUAGE
	m_strName = g_sLangTxt_I2T/*_T("圆（I2T）")*/;
#else
	m_strName = _T("圆（I2T）");
#endif

	//初始化成员变量
	m_fTp = 4;
	m_fA = 75;
}

CCharElementI2T::~CCharElementI2T()
{
}

long CCharElementI2T::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementInverse::XmlReadOwn(oNode, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTpKey, oNode, m_strTp);
	xml_GetAttibuteValue(pXmlKeys->m_strAKey, oNode, m_strA);
	
	return 0;
}

long CCharElementI2T::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementInverse::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTpKey, oElement, m_strTp);
	xml_SetAttributeValue(pXmlKeys->m_strAKey, oElement, m_strA);

	return 0;
}

void CCharElementI2T::InitAfterRead()
{
}

BOOL CCharElementI2T::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementI2T *p = (CCharElementI2T*)pObj;

	if(m_strTp != p->m_strTp)
	{
		return FALSE;
	}

	if(m_strA != p->m_strA)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCharElementI2T::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementI2T *p = (CCharElementI2T*)pDest;
	CCharElementInverse::CopyOwn(pDest);

	p->m_strTp = m_strTp;
	p->m_strA = m_strA;

	return TRUE;
}

CBaseObject* CCharElementI2T::Clone()
{
	CCharElementI2T *p = new CCharElementI2T();
	Copy(p);
	return p;
}
long CCharElementI2T::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CCharElementInverse::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strTp);
		BinarySerializeCalLen(oBinaryBuffer, m_strA);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strTp);
		BinarySerializeRead(oBinaryBuffer, m_strA);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strTp);
		BinarySerializeWrite(oBinaryBuffer, m_strA);
	}

	return 0;
}

CString CCharElementI2T::ReturnXml()
{
	CString str;
    str.Format(_T("I2T Tp=\"%s\" A=\"%s\""),m_strTp.GetString(),m_strA.GetString());
	return str;
}

void CCharElementI2T::Draw(CDC *pDC)   //圆特性曲线
{

}


void CCharElementI2T::CalByExpression(BOOL bCalLines, CExBaseList *pDrawList)
{
	//计算自身数据
	CalCharElementExpression(m_strTp, m_fTp, TRUE);
	CalCharElementExpression(m_strA, m_fA, TRUE);

	CCharElementInverse::CalByExpression(bCalLines, pDrawList);
}

double CCharElementI2T::CalInverse(double dVal)
{
	double dT = m_fTp * m_fA / (dVal * dVal);
	return dT;
}

