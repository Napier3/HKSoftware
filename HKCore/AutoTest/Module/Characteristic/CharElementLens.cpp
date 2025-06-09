//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementLens.cpp  CCharElementLens


#include "stdafx.h"
#include "CharElementLens.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharElementLens::CCharElementLens()
{
	//初始化属性
	m_strID = CHAR_ELEMENT_ID_LENS;

#ifndef NOT_USE_XLANGUAGE
	m_strName = g_sLangTxt_Lens/*_T("透镜（lens）")*/;
#else
	m_strName = _T("透镜（lens）");
#endif

	//初始化成员变量
	m_fForwardReach = 2;
	m_fAngle = 80;
	m_fOffset = 0.5;
	m_fWidth  = 0.5;

	m_oCharElementArc1.SetParent(this);
	m_oCharElementArc2.SetParent(this);
}

CCharElementLens::~CCharElementLens()
{
	
}

long CCharElementLens::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharElement::XmlReadOwn(oNode, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strForwardReachKey, oNode, m_strForwardReach);
	xml_GetAttibuteValue(pXmlKeys->m_strAngleKey, oNode, m_strAngle);
	xml_GetAttibuteValue(pXmlKeys->m_strOffsetKey, oNode, m_strOffset);
	xml_GetAttibuteValue(pXmlKeys->m_strWidthKey, oNode, m_strWidth);
	return 0;
}

long CCharElementLens::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharElement::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strForwardReachKey, oElement, m_strForwardReach);
	xml_SetAttributeValue(pXmlKeys->m_strAngleKey, oElement, m_strAngle);
	xml_SetAttributeValue(pXmlKeys->m_strOffsetKey, oElement, m_strOffset);
	xml_SetAttributeValue(pXmlKeys->m_strWidthKey, oElement, m_strWidth);
	return 0;
}

void CCharElementLens::InitAfterRead()
{
}

BOOL CCharElementLens::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementLens *p = (CCharElementLens*)pObj;

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

	if(m_strWidth != p->m_strWidth)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCharElementLens::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElement::CopyOwn(pDest);
	CCharElementLens *p = (CCharElementLens*)pDest;

	p->m_strForwardReach = m_strForwardReach;
	p->m_strAngle = m_strAngle;
	p->m_strOffset = m_strOffset;
	p->m_strWidth = m_strWidth;

	p->m_fForwardReach = m_fForwardReach;
	p->m_fAngle = m_fAngle;
	p->m_fOffset = m_fOffset;
	p->m_fWidth = m_fWidth;

	return TRUE;
}

CBaseObject* CCharElementLens::Clone()
{
	CCharElementLens *p = new CCharElementLens();
	Copy(p);
	return p;
}
long CCharElementLens::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CCharElement::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strForwardReach);
		BinarySerializeCalLen(oBinaryBuffer, m_strAngle);
		BinarySerializeCalLen(oBinaryBuffer, m_strOffset);
		BinarySerializeCalLen(oBinaryBuffer, m_strWidth);
		
		//2020-3-14   lijq  不需要保存实际的值，绘图前计算得到
		//BinarySerializeCalLen(oBinaryBuffer, m_fForwardReach);
		//BinarySerializeCalLen(oBinaryBuffer, m_fAngle);
		//BinarySerializeCalLen(oBinaryBuffer, m_fOffset);
		//BinarySerializeCalLen(oBinaryBuffer, m_fWidth);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strForwardReach);
		BinarySerializeRead(oBinaryBuffer, m_strAngle);
		BinarySerializeRead(oBinaryBuffer, m_strOffset);
		BinarySerializeRead(oBinaryBuffer, m_strWidth);

		//2020-3-14  特性曲线的改进，兼容之前版本的二进制文件  lijq
		//#define GBVERSION_1_39        0X00010027
		//因为引用和包含的关系，不添加
		//如果单独使用，则可以不处理
		if (0 < oBinaryBuffer.m_dwVersion && oBinaryBuffer.m_dwVersion < 0X00010027)
		{
			BinarySerializeRead(oBinaryBuffer, m_fForwardReach);
			BinarySerializeRead(oBinaryBuffer, m_fAngle);
			BinarySerializeRead(oBinaryBuffer, m_fOffset);
			BinarySerializeRead(oBinaryBuffer, m_fWidth);
		}
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strForwardReach);
		BinarySerializeWrite(oBinaryBuffer, m_strAngle);
		BinarySerializeWrite(oBinaryBuffer, m_strOffset);
		BinarySerializeWrite(oBinaryBuffer, m_strWidth);
	
		//2020-3-14   lijq  不需要保存实际的值，绘图前计算得到
		//BinarySerializeWrite(oBinaryBuffer, m_fForwardReach);
		//BinarySerializeWrite(oBinaryBuffer, m_fAngle);
		//BinarySerializeWrite(oBinaryBuffer, m_fOffset);
		//BinarySerializeWrite(oBinaryBuffer, m_fWidth);
	}
	
	return 0;
}

CString CCharElementLens::ReturnXml()
{
	CString str;
    str.Format(_T("LENS(angle=\"%s\",forward-reach=\"%s\",offset=\"%s\",width=\"%s\")"),m_strAngle.GetString(),m_strForwardReach.GetString()
               ,m_strOffset.GetString(), m_strWidth.GetString());
	return str;
}


CXDrawBase* CCharElementLens::CreateDrawElement()
{	
	CCharElementArc *pCharArc1 = GetCharElementArc1();
	CCharElementArc *pCharArc2 = GetCharElementArc2();
	CXDrawArc *pXArc1 = (CXDrawArc*)pCharArc1->CreateDrawElement();
	CXDrawArc *pXArc2 = (CXDrawArc*)pCharArc2->CreateDrawElement();

	CXDrawList *pNewList = new CXDrawList();
	m_pDataRef = pNewList;

	pNewList->AddNewChild(pXArc1);
	pNewList->AddNewChild(pXArc2);

	pXArc1->m_fXCenter = pCharArc1->m_fXCenter;
	pXArc1->m_fYCenter = pCharArc1->m_fYCenter;
	pXArc1->m_fXRadius = pCharArc1->m_fXRadius;
	pXArc1->m_fYRadius = pCharArc1->m_fYRadius;
	pXArc1->m_fAngleBegin = pCharArc1->m_fAngleBegin;
	pXArc1->m_fAngleEnd   = pCharArc1->m_fAngleEnd;
	pXArc1->m_pXDrawDataRef = this;
	pXArc2->m_pXDrawDataRef = this;
	pNewList->m_pXDrawDataRef = this;

	pXArc2->m_fXCenter = pCharArc2->m_fXCenter;
	pXArc2->m_fYCenter = pCharArc2->m_fYCenter;
	pXArc2->m_fXRadius = pCharArc2->m_fXRadius;
	pXArc2->m_fYRadius = pCharArc2->m_fYRadius;
	pXArc2->m_fAngleBegin = pCharArc2->m_fAngleBegin;
	pXArc2->m_fAngleEnd   = pCharArc2->m_fAngleEnd;

	return (CXDrawBase*)m_pDataRef;
}

void CCharElementLens::CalByExpression(BOOL bCalLines, CExBaseList *pDrawList)
{
	//计算自身数据
	CalCharElementExpression(m_strForwardReach, m_fForwardReach, TRUE);
	CalCharElementExpression(m_strAngle, m_fAngle, TRUE);
	CalCharElementExpression(m_strOffset, m_fOffset, TRUE);
	CalCharElementExpression(m_strWidth, m_fWidth, TRUE);
	CalCharElementExpression(m_strErrLength, m_dErrLength, TRUE);

	CComplexNumber cFr(m_fForwardReach, m_fAngle, COMPLEX_MODE_DEGREE);
	CComplexNumber cOff(m_fOffset, m_fAngle+180, COMPLEX_MODE_DEGREE);
	CComplexNumber c3, cArcC, c5;
	double dB = (m_fForwardReach + m_fOffset) / 2;
	double dA = m_fWidth;
	double dR = (dA * dA + dB * dB) / (dA * 2);

	double dLen = (m_fForwardReach - m_fOffset) / 2;
	CComplexNumber cc(dLen, m_fAngle, COMPLEX_MODE_DEGREE);

	c3.SetValueAngle(dR-dA, m_fAngle - 90);
	cArcC = cc + c3;
	cArcC.GetValue(m_oCharElementArc1.m_fXCenter, m_oCharElementArc1.m_fYCenter);
	c5 = cOff - cArcC;
	c5.GetValueAngle(dLen, m_oCharElementArc1.m_fAngleEnd);
	c5 = cFr - cArcC;
	c5.GetValueAngle(dLen, m_oCharElementArc1.m_fAngleBegin);
	m_oCharElementArc1.m_fXRadius = dR;
	m_oCharElementArc1.m_fYRadius = dR;

	c3.SetValueAngle(dR-dA, m_fAngle + 90);
	cArcC = cc + c3;
	cArcC.GetValue(m_oCharElementArc2.m_fXCenter, m_oCharElementArc2.m_fYCenter);
	c5 = cOff - cArcC;
	c5.GetValueAngle(dLen, m_oCharElementArc2.m_fAngleBegin);
	c5 = cFr - cArcC;
	c5.GetValueAngle(dLen, m_oCharElementArc2.m_fAngleEnd);
	m_oCharElementArc2.m_fXRadius = dR;
	m_oCharElementArc2.m_fYRadius = dR;
}

void CCharElementLens::SetTestPoint(long nPoints)
{
	m_nTestPoints = nPoints;
	m_oCharElementArc1.SetTestPoint(m_nTestPoints);
	m_oCharElementArc2.SetTestPoint(m_nTestPoints);
}

void CCharElementLens::CalTestLines(UINT nTestLineMode)
{
	m_oCharElementArc1.SetTestPoint(m_nTestPoints);
	m_oCharElementArc2.SetTestPoint(m_nTestPoints);
	m_oCharElementArc1.m_dErrLength = m_dErrLength;
	m_oCharElementArc2.m_dErrLength = m_dErrLength;

	m_oCharElementArc1.CalTestLines(nTestLineMode);
	m_oCharElementArc2.CalTestLines(nTestLineMode);

	DeleteAll();
	AppendCloneEx(m_oCharElementArc1, TRUE);
	AppendCloneEx(m_oCharElementArc2, TRUE);
}

