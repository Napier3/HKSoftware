//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementLined.cpp  CCharElementLined


#include "stdafx.h"
#include "CharElementLined.h"
#include "CharacteristicTmplate.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharElementLined::CCharElementLined()
{
	//初始化属性
	m_strID = CHAR_ELEMENT_ID_LINED;

#ifndef NOT_USE_XLANGUAGE
	m_strName = g_sLangTxt_Lined/*_T("线段（lined）")*/;
#else
	m_strName = _T("线段（lined）");
#endif

// 	m_fXb = 0;
// 	m_fYb = 0;
// 	m_fXe = 0;
// 	m_fYe = 0;
	m_nType = CURVE_LINE_TYPE_LINE_SEGMENT;

	//初始化成员变量
}

CCharElementLined::~CCharElementLined()
{
}

long CCharElementLined::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharElement::XmlReadOwn(oNode, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strXbKey, oNode, m_strXb);
	xml_GetAttibuteValue(pXmlKeys->m_strYbKey, oNode, m_strYb);
	xml_GetAttibuteValue(pXmlKeys->m_strXeKey, oNode, m_strXe);
	xml_GetAttibuteValue(pXmlKeys->m_strYeKey, oNode, m_strYe);
	return 0;
}

long CCharElementLined::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharElement::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strXbKey, oElement, m_strXb);
	xml_SetAttributeValue(pXmlKeys->m_strYbKey, oElement, m_strYb);
	xml_SetAttributeValue(pXmlKeys->m_strXeKey, oElement, m_strXe);
	xml_SetAttributeValue(pXmlKeys->m_strYeKey, oElement, m_strYe);

	return 0;
}

BOOL CCharElementLined::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementLined *p = (CCharElementLined*)pObj;

	if(m_strXb != p->m_strXb)
	{
		return FALSE;
	}

	if(m_strYb != p->m_strYb)
	{
		return FALSE;
	}

	if(m_strXe != p->m_strXe)
	{
		return FALSE;
	}

	if(m_strYe != p->m_strYe)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCharElementLined::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElement::CopyOwn(pDest);
	CCharElementLined *p = (CCharElementLined*)pDest;

	p->m_strXb = m_strXb;
	p->m_strYb = m_strYb;
	p->m_strXe = m_strXe;
	p->m_strYe = m_strYe;

	return TRUE;
}

CBaseObject* CCharElementLined::Clone()
{
	CCharElementLined *p = new CCharElementLined();
	Copy(p);
	return p;
}

// CExBaseObject* CCharElementLined::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
// {
// 	CExBaseObject *pNew  = NULL;
// 	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;
// 
// 	return CCharElement::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
// 
// 	return pNew;
// }
// 
// CExBaseObject* CCharElementLined::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
// {
// 	CExBaseObject *pNew  = NULL;
// 
// 
// 
// 	return pNew;
// }

long CCharElementLined::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CCharElementLineBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strXb);
		BinarySerializeCalLen(oBinaryBuffer, m_strYb);
		BinarySerializeCalLen(oBinaryBuffer, m_strXe);
		BinarySerializeCalLen(oBinaryBuffer, m_strYe);

		//2020-3-14   lijq  不需要保存实际的值，绘图前计算得到
		//BinarySerializeCalLen(oBinaryBuffer, m_fXb);
		//BinarySerializeCalLen(oBinaryBuffer, m_fYb);
		//BinarySerializeCalLen(oBinaryBuffer, m_fXe);
		//BinarySerializeCalLen(oBinaryBuffer, m_fYe);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strXb);
		BinarySerializeRead(oBinaryBuffer, m_strYb);
		BinarySerializeRead(oBinaryBuffer, m_strXe);
		BinarySerializeRead(oBinaryBuffer, m_strYe);

		//2020-3-14  特性曲线的改进，兼容之前版本的二进制文件  lijq
		//#define GBVERSION_1_39        0X00010027
		//因为引用和包含的关系，不添加
		//如果单独使用，则可以不处理
		if (0 < oBinaryBuffer.m_dwVersion && oBinaryBuffer.m_dwVersion < 0X00010027)
		{
			BinarySerializeRead(oBinaryBuffer, m_fXb);
			BinarySerializeRead(oBinaryBuffer, m_fYb);
			BinarySerializeRead(oBinaryBuffer, m_fXe);
			BinarySerializeRead(oBinaryBuffer, m_fYe);
		}
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strXb);
		BinarySerializeWrite(oBinaryBuffer, m_strYb);
		BinarySerializeWrite(oBinaryBuffer, m_strXe);
		BinarySerializeWrite(oBinaryBuffer, m_strYe);

		//2020-3-14   lijq  不需要保存实际的值，绘图前计算得到
		//BinarySerializeWrite(oBinaryBuffer, m_fXb);
		//BinarySerializeWrite(oBinaryBuffer, m_fYb);
		//BinarySerializeWrite(oBinaryBuffer, m_fXe);
		//BinarySerializeWrite(oBinaryBuffer, m_fYe);
	}

	return 0;
}
CString CCharElementLined::ReturnXml()
{
	CString str;
    str.Format(_T("(%s,%s) (%s, %s)"),m_strXb.GetString(),m_strYb.GetString(),m_strXe.GetString(),m_strYe.GetString());
	return str;
}

void CCharElementLined::Draw(CDC *pDC)
{

}


void CCharElementLined::GetBeginPoint(CString &strX, CString &strY)
{
	strX = m_strXb;
	strY = m_strYb;
}

void CCharElementLined::GetEndPoint(CString &strX, CString &strY)
{
	strX = m_strXe;
	strY = m_strYe;
}


void CCharElementLined::SetBeginPoint(const CString &strX, const CString &strY)
{
	m_strXb = strX;
	m_strYb = strY;
}

void CCharElementLined::SetEndPoint(const CString &strX, const CString &strY)
{
	m_strXe = strX;
	m_strYe = strY;
}

void CCharElementLined::CalByExpression(BOOL bCalLines, CExBaseList *pDrawList)
{
	//计算自身数据
	CalCharElementExpression(m_strXb, m_fXb, TRUE);
	CalCharElementExpression(m_strXe, m_fXe, TRUE);
	CalCharElementExpression(m_strYb, m_fYb, TRUE);
	CalCharElementExpression(m_strYe, m_fYe, TRUE);
	Init_K_B_by_XY();
}

void CCharElementLined::SetDoublePoint()
{
	m_fXb = CString_To_double(m_strXb);
	m_fXe = CString_To_double(m_strXe);
	m_fYb = CString_To_double(m_strYb);
	m_fYe = CString_To_double(m_strYe);
	Init_K_B_by_XY();
}
