#include "stdafx.h"
#include "CharElementLabIecCurve.h"
#ifdef _PSX_IDE_QT_
#include <qmath.h> 
#endif
#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharElementLabIecCurve::CCharElementLabIecCurve()
{
	//初始化属性
	m_strID = CHAR_ELEMENT_ID_LABIECCURVE;

#ifndef NOT_USE_XLANGUAGE
	m_strName = /*g_sLangTxt_IEEE*/_T("圆（LabIecCurve）");
#else
	m_strName = _T("圆（LabIecCurve）");
#endif

	//初始化成员变量
	m_strA =_T("1.000");
	m_strB = _T("0");

	m_fA = 1.0;
	m_fB = 0;
}

CCharElementLabIecCurve::~CCharElementLabIecCurve()
{
}

long CCharElementLabIecCurve::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementInverse::XmlReadOwn(oNode, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strAKey, oNode, m_strA);
	xml_GetAttibuteValue(pXmlKeys->m_strBKey, oNode, m_strB);

	return 0;
}

long CCharElementLabIecCurve::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementInverse::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strAKey, oElement, m_strA);
	xml_SetAttributeValue(pXmlKeys->m_strBKey, oElement, m_strB);

	return 0;
}

void CCharElementLabIecCurve::InitAfterRead()
{
}

BOOL CCharElementLabIecCurve::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementLabIecCurve *p = (CCharElementLabIecCurve*)pObj;

	if(m_strA != p->m_strA)
	{
		return FALSE;
	}

	if(m_strB != p->m_strB)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCharElementLabIecCurve::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementLabIecCurve *p = (CCharElementLabIecCurve*)pDest;
	CCharElementInverse::CopyOwn(pDest);

	p->m_strA = m_strA;
	p->m_strB = m_strB;

	return TRUE;
}

CBaseObject* CCharElementLabIecCurve::Clone()
{
	CCharElementLabIecCurve *p = new CCharElementLabIecCurve();
	Copy(p);
	return p;
}

long CCharElementLabIecCurve::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CCharElementInverse::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strA);
		BinarySerializeCalLen(oBinaryBuffer, m_strB);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strA);
		BinarySerializeRead(oBinaryBuffer, m_strB);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strA);
		BinarySerializeWrite(oBinaryBuffer, m_strB);
	}
	return 0;
}
CString CCharElementLabIecCurve::ReturnXml()
{
	CString str;

	str.Format(_T("LabIecCurve  A=\"%s\" B=\"%s\""),m_strA.GetString(),m_strB.GetString());

	return str;
}

void CCharElementLabIecCurve::Draw(CDC *pDC)   //圆特性曲线
{

}


void CCharElementLabIecCurve::CalByExpression(BOOL bCalLines, CExBaseList *pDrawList)
{
	//计算自身数据
	CalCharElementExpression(m_strA, m_fA, TRUE);
	CalCharElementExpression(m_strB, m_fB, TRUE);

	CCharElementInverse::CalByExpression(bCalLines, pDrawList);
}


void CCharElementLabIecCurve::CalInversePolyline()
{
	m_nPoints = 0;//每次计算，需要将当前使用的点数清零，否则就持续累加
	double dx = 0, dTime = 0;
	
	SetPointsMax(200); //初始化为200点
	BOOL bTrue = TRUE;

	//计算反时限部分
	while (bTrue)
	{
		bTrue = IncreaseX(dx);
		dTime = CalInverse(dx);

		if (dTime < 0)
		{
			continue;
		}

		if (dTime > m_fTmax)
		{
			continue;
		}

		if (!HasPoints())
		{
			ExpandPointsMax(50);
		}

		AddPoint(dx, dTime);
	}

	AddSectionPoints();	
}


BOOL CCharElementLabIecCurve::IncreaseX(double &dValX)
{
	double dStand = 0;

	if (m_nUseSection[2] == 1)
	{
		dStand = m_fValSection[2];
	}
	else if (m_nUseSection[1] == 1)
	{
		dStand = m_fValSection[1];
	}
	else if (m_nUseSection[0] == 1)
	{
		dStand = m_fValSection[0];
	}
	else
	{
		dStand = 1;
	}

	if (dValX > m_fXmax)
	{//最大值限制
		return FALSE;
	}

	if (dValX <= dStand*2)
	{
		dValX += 0.01*dStand;
	}
	else if (dValX <= dStand*4)
	{
		dValX += 0.02*dStand;
	}
	else if (dValX <= dStand*10)
	{
		dValX += 0.5*dStand;
	}
	else if (dValX <= dStand*100)
	{
		dValX += 2*dStand;
	}
	else if (dValX <= m_fXmax)
	{
		dValX += 0.02*m_fXmax;
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

double CCharElementLabIecCurve::CalInverse(double dVal)
{
	double dT = m_fA * dVal + m_fB;
	return dT;
}

