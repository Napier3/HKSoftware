//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementLiner.cpp  CCharElementLiner


#include "stdafx.h"
#include "CharElementLiner.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharElementLiner::CCharElementLiner()
{
	//初始化属性
	m_strID = CHAR_ELEMENT_ID_LINER;

#ifndef NOT_USE_XLANGUAGE
	m_strName = g_sLangTxt_Liner/*_T("射线（liner）")*/;
#else
	m_strName = _T("射线（liner）");
#endif

	//初始化成员变量
// 	m_fXb = 0;
// 	m_fYb = 0;
// 	m_fAngle = 60;
	m_fLengthUse = 5;
}

CCharElementLiner::~CCharElementLiner()
{
}

long CCharElementLiner::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementLineBase::XmlReadOwn(oNode, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strXbKey, oNode, m_strXb);
	xml_GetAttibuteValue(pXmlKeys->m_strYbKey, oNode, m_strYb);
	xml_GetAttibuteValue(pXmlKeys->m_strAngleKey, oNode, m_strAngle);
	xml_GetAttibuteValue(pXmlKeys->m_strLengthUseKey, oNode, m_strLengthUse);
	
	return 0;
}

long CCharElementLiner::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementLineBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strXbKey, oElement, m_strXb);
	xml_SetAttributeValue(pXmlKeys->m_strYbKey, oElement, m_strYb);
	xml_SetAttributeValue(pXmlKeys->m_strAngleKey, oElement, m_strAngle);
	xml_SetAttributeValue(pXmlKeys->m_strLengthUseKey, oElement, m_strLengthUse);
	
	return 0;
}

void CCharElementLiner::InitAfterRead()
{
}

BOOL CCharElementLiner::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementLiner *p = (CCharElementLiner*)pObj;

	if(m_strXb != p->m_strXb)
	{
		return FALSE;
	}

	if(m_strYb != p->m_strYb)
	{
		return FALSE;
	}

	if(m_strAngle != p->m_strAngle)
	{
		return FALSE;
	}

	if(m_strLengthUse != p->m_strLengthUse)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCharElementLiner::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementLineBase::CopyOwn(pDest);
	CCharElementLiner *p = (CCharElementLiner*)pDest;

	p->m_strXb = m_strXb;
	p->m_strYb = m_strYb;
	p->m_strAngle = m_strAngle;
	p->m_strLengthUse = m_strLengthUse;
	p->m_fLengthUse = m_fLengthUse;

	return TRUE;
}

CBaseObject* CCharElementLiner::Clone()
{
	CCharElementLiner *p = new CCharElementLiner();
	Copy(p);
	return p;
}

long CCharElementLiner::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CCharElementLineBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strXb);
		BinarySerializeCalLen(oBinaryBuffer, m_strYb);
		BinarySerializeCalLen(oBinaryBuffer, m_strAngle);
		BinarySerializeCalLen(oBinaryBuffer, m_strLengthUse);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strXb);
		BinarySerializeRead(oBinaryBuffer, m_strYb);
		BinarySerializeRead(oBinaryBuffer, m_strAngle);
		BinarySerializeRead(oBinaryBuffer, m_strLengthUse);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strXb);
		BinarySerializeWrite(oBinaryBuffer, m_strYb);
		BinarySerializeWrite(oBinaryBuffer, m_strAngle);
		BinarySerializeWrite(oBinaryBuffer, m_strLengthUse);
	}

	return 0;
}


CString CCharElementLiner::ReturnXml()
{
	CString str;
    str.Format(_T("(%s,%s) (%s, %s)"),m_strXb.GetString(),m_strYb.GetString(),m_strAngle.GetString(),m_strLengthUse.GetString());
	return str;
}


void CCharElementLiner::Draw(CDC *pDC)
{
}



void CCharElementLiner::GetBeginPoint(CString &strX, CString &strY)
{
	strX = m_strXb;
	strY = m_strYb;
}

void CCharElementLiner::SetBeginPoint(const CString &strX, const CString &strY)
{
	m_strXb = strX;
	m_strYb = strY;
}

void CCharElementLiner::BeforeCalTestLines()
{
	CCharElement::BeforeCalTestLines();
	UpdateLengthUse();
}

void CCharElementLiner::UpdateLengthUse()
{
	if (m_pDataRef == NULL)
	{
		return;
	}

	CXDrawLine *pLine = (CXDrawLine*)m_pDataRef;
	double dX = pLine->m_fXe-pLine->m_fXb;
	double dY = pLine->m_fYe-pLine->m_fYb;
	m_fLengthUse = sqrt(pow(dX, 2) + pow(dY, 2));
	m_strLengthUse.Format(_T("%lf"),m_fLengthUse);
}


void CCharElementLiner::CalByExpression(BOOL bCalLines, CExBaseList *pDrawList)
{
	//计算自身数据
	CalCharElementExpression(m_strXb, m_fXb, TRUE);
	CalCharElementExpression(m_strYb, m_fYb, TRUE);
	CalCharElementExpression(m_strAngle, m_fAngle, TRUE);
	CalCharElementExpression(m_strLengthUse, m_fLengthUse, TRUE);

	Init_K_by_Angle();
	InitLine(m_fLengthUse);
}

void CCharElementLiner::CalTestLines_Plumb()
{
	double dX = m_fLengthUse * cos(m_fAngle*_PI_D_180);
	double dY = m_fLengthUse * sin(m_fAngle*_PI_D_180);

	double dAngle = m_fAngle;

	double dErrorLen = GetErrorLength();

	POS pos = GetHeadPosition();
	CCharElementTestLine *pTestLine = NULL;
	double dXg = dX / (m_nTestPoints + 1);
	double dYg = dY / (m_nTestPoints + 1);
	double dR90 = (dAngle+90)*_PI_D_180;
	//	double dR270 = dAngle - _PI_D_180 * 90;

	while (pos != NULL)
	{
		pTestLine = (CCharElementTestLine *)GetNext(pos);
		dX = m_fXb + pTestLine->m_fPos * dXg;
		dY = m_fYb + pTestLine->m_fPos * dYg;

		CComplexNumber oComplex(dErrorLen,dR90, COMPLEX_MODE_RADIAN);
		pTestLine->m_fXb = dX + oComplex.m_fReal;
		pTestLine->m_fYb = dY + oComplex.m_fImaginary;

		oComplex.Rotate(180, COMPLEX_MODE_DEGREE);

		pTestLine->m_fXe = dX + oComplex.m_fReal;
		pTestLine->m_fYe = dY + oComplex.m_fImaginary;

		pTestLine->m_fXset = (pTestLine->m_fXb + pTestLine->m_fXe) / 2;
		pTestLine->m_fYset = (pTestLine->m_fYb + pTestLine->m_fYe) / 2;
	}
}

void CCharElementLiner::CalTestLines_Vert()
{
	double dX = m_fLengthUse * cos(m_fAngle*_PI_D_180);
	double dY = m_fLengthUse * sin(m_fAngle*_PI_D_180);

	double dErrorLen = GetErrorLength();

	POS pos = GetHeadPosition();
	CCharElementTestLine *pTestLine = NULL;
	double dXg = dX / (m_nTestPoints + 1);
	double dYg = dY / (m_nTestPoints + 1);

	while (pos != NULL)
	{
		pTestLine = (CCharElementTestLine *)GetNext(pos);
		dX = m_fXb + pTestLine->m_fPos * dXg;
		dY = m_fYb + pTestLine->m_fPos * dYg;
		pTestLine->m_fXset = dX;
		pTestLine->m_fYset = dY;

		pTestLine->m_fXb = dX ;
		pTestLine->m_fYb = dY + dErrorLen;

		pTestLine->m_fXe = dX;
		pTestLine->m_fYe = dY - dErrorLen;
	}
}

void CCharElementLiner::CalTestLines_Horz()
{
	//计算角度
	double dX = m_fLengthUse * cos(m_fAngle*_PI_D_180);
	double dY = m_fLengthUse * sin(m_fAngle*_PI_D_180);
	double dErrorLen = GetErrorLength();

	POS pos = GetHeadPosition();
	CCharElementTestLine *pTestLine = NULL;
	double dXg = dX / (m_nTestPoints + 1);
	double dYg = dY / (m_nTestPoints + 1);

	while (pos != NULL)
	{
		pTestLine = (CCharElementTestLine *)GetNext(pos);
		dX = m_fXb + pTestLine->m_fPos * dXg;
		dY = m_fYb + pTestLine->m_fPos * dYg;
		pTestLine->m_fXset = dX;
		pTestLine->m_fYset = dY;

		pTestLine->m_fXb = dX + dErrorLen ;
		pTestLine->m_fYb = dY;

		pTestLine->m_fXe = dX - dErrorLen;
		pTestLine->m_fYe = dY;
	}
}

void CCharElementLiner::GetXeYe(double &dXe, double &dYe)
{
// 	dXe = m_fXb + m_fLengthUse * cos(m_fAngle * _PI_D_180);
// 	dYe = m_fYb + m_fLengthUse * sin(m_fAngle * _PI_D_180);
	dXe = m_fXe;
	dYe = m_fYe;
}

