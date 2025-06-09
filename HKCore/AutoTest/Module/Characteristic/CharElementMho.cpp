//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementMho.cpp  CCharElementMho


#include "stdafx.h"
#include "CharElementMho.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharElementMho::CCharElementMho()
{
	//初始化属性
	m_strID = CHAR_ELEMENT_ID_MHO;

#ifndef NOT_USE_XLANGUAGE
	m_strName = g_sLangTxt_Mho/*_T("圆（mho）")*/;
#else
	m_strName = _T("圆（mho）");
#endif

	//初始化成员变量
	m_fForwardReach = 4;
	m_fAngle = 75;
	m_fOffset = 0.5;
}

CCharElementMho::~CCharElementMho()
{
}

long CCharElementMho::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharElement::XmlReadOwn(oNode, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strForwardReachKey, oNode, m_strForwardReach);
	xml_GetAttibuteValue(pXmlKeys->m_strAngleKey, oNode, m_strAngle);
	xml_GetAttibuteValue(pXmlKeys->m_strOffsetKey, oNode, m_strOffset);
	return 0;
}

long CCharElementMho::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharElement::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strForwardReachKey, oElement, m_strForwardReach);
	xml_SetAttributeValue(pXmlKeys->m_strAngleKey, oElement, m_strAngle);
	xml_SetAttributeValue(pXmlKeys->m_strOffsetKey, oElement, m_strOffset);

	return 0;
}

void CCharElementMho::InitAfterRead()
{
}

BOOL CCharElementMho::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementMho *p = (CCharElementMho*)pObj;

	if(m_strForwardReach != p->m_strForwardReach)
	{
		return FALSE;
	}

	if(m_strAngle != p->m_strAngle)
	{
		return FALSE;
	}

	if(m_strOffset != p->m_strOffset)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCharElementMho::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementMho *p = (CCharElementMho*)pDest;
	CCharElement::CopyOwn(pDest);

	p->m_strForwardReach = m_strForwardReach;
	p->m_strAngle = m_strAngle;
	p->m_strOffset = m_strOffset;

	p->m_fForwardReach = m_fForwardReach;
	p->m_fAngle = m_fAngle;
	p->m_fOffset = m_fOffset;

	return TRUE;
}

CBaseObject* CCharElementMho::Clone()
{
	CCharElementMho *p = new CCharElementMho();
	Copy(p);
	return p;
}
long CCharElementMho::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CCharElement::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strForwardReach);
		BinarySerializeCalLen(oBinaryBuffer, m_strAngle);
		BinarySerializeCalLen(oBinaryBuffer, m_strOffset);

		//2020-3-14   lijq  不需要保存实际的值，绘图前计算得到
		//BinarySerializeCalLen(oBinaryBuffer, m_fForwardReach);
		//BinarySerializeCalLen(oBinaryBuffer, m_fAngle);
		//BinarySerializeCalLen(oBinaryBuffer, m_fOffset);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strForwardReach);
		BinarySerializeRead(oBinaryBuffer, m_strAngle);
		BinarySerializeRead(oBinaryBuffer, m_strOffset);

		//2020-3-14  特性曲线的改进，兼容之前版本的二进制文件  lijq
		//#define GBVERSION_1_39        0X00010027
		//因为引用和包含的关系，不添加
		//如果单独使用，则可以不处理
		if (0 < oBinaryBuffer.m_dwVersion && oBinaryBuffer.m_dwVersion < 0X00010027)
		{
			BinarySerializeRead(oBinaryBuffer, m_fForwardReach);
			BinarySerializeRead(oBinaryBuffer, m_fAngle);
			BinarySerializeRead(oBinaryBuffer, m_fOffset);
		}
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strForwardReach);
		BinarySerializeWrite(oBinaryBuffer, m_strAngle);
		BinarySerializeWrite(oBinaryBuffer, m_strOffset);

		//2020-3-14   lijq  不需要保存实际的值，绘图前计算得到
		//BinarySerializeWrite(oBinaryBuffer, m_fForwardReach);
		//BinarySerializeWrite(oBinaryBuffer, m_fAngle);
		//BinarySerializeWrite(oBinaryBuffer, m_fOffset);
	}
	return 0;
}
CString CCharElementMho::ReturnXml()
{
	CString str;
    str.Format(_T("MHO angle=\"%s\" forward-reach=\"%s\" offset=\"%s\""),m_strAngle.GetString(),m_strForwardReach.GetString(),m_strOffset.GetString());
	return str;
}

void CCharElementMho::Draw(CDC *pDC)   //圆特性曲线
{

}


CXDrawBase* CCharElementMho::CreateDrawElement()
{	
// 	if (m_pDataRef != NULL)
// 	{
// 		return (CXDrawBase*)m_pDataRef;
// 	}

	CXDrawCircle *pNew = new CXDrawCircle();
	CXDrawData_Circle::DataCopy(pNew);
	m_pDataRef = pNew;	

	return (CXDrawBase*)m_pDataRef;
}


void CCharElementMho::CalByExpression(BOOL bCalLines, CExBaseList *pDrawList)
{
	//计算自身数据
	CalCharElementExpression(m_strForwardReach, m_fForwardReach, TRUE);
	CalCharElementExpression(m_strAngle, m_fAngle, TRUE);
	CalCharElementExpression(m_strOffset, m_fOffset, TRUE);

	//计算圆心
	double dLen = (m_fForwardReach - m_fOffset) / 2;
	m_fXCenter = dLen*cos(m_fAngle * _PI_D_180);
	m_fYCenter = dLen*sin(m_fAngle * _PI_D_180);
	m_fXRadius =( m_fForwardReach + m_fOffset) / 2;
	m_fYRadius = m_fXRadius;
}


void CCharElementMho::CalTestLines(UINT nTestLineMode)
{
	double dAngleGap = 360 / m_nTestPoints;
	double dErrorLen = GetErrorLength();

	POS pos = GetHeadPosition();
	CCharElementTestLine *pTestLine = NULL;
	double dAngle = 0, dX = 0, dY = 0, dXg = 0, dYg = 0;

	while (pos != NULL)
	{
		pTestLine = (CCharElementTestLine *)GetNext(pos);
		dAngle = pTestLine->m_fPos * dAngleGap;
		
		dXg = dErrorLen * cos(dAngle * _PI_D_180);
		dYg = dErrorLen * sin(dAngle * _PI_D_180);

		pTestLine->m_fXset = m_fXCenter + m_fXRadius * cos(dAngle * _PI_D_180);
		pTestLine->m_fYset = m_fYCenter + m_fXRadius * sin(dAngle * _PI_D_180);
		pTestLine->m_fXb = pTestLine->m_fXset + dXg;
		pTestLine->m_fYb = pTestLine->m_fYset + dYg;
		pTestLine->m_fXe = pTestLine->m_fXset - dXg;
		pTestLine->m_fYe = pTestLine->m_fYset - dYg;
	}
}

