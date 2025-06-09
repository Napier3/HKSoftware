#include "stdafx.h"
#include "CharElementI2TEx.h"
#ifdef _PSX_IDE_QT_
#include <qmath.h> 
#endif
#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharElementI2TEx::CCharElementI2TEx()
{
	//初始化属性
	m_strID = CHAR_ELEMENT_ID_I2TEx;

#ifndef NOT_USE_XLANGUAGE
	m_strName = /*g_sLangTxt_IEEE*/_T("圆（I2TEx）");
#else
	m_strName = _T("圆（I2TEx）");
#endif

	//初始化成员变量
	m_strA = _T("1.0");
	m_strP = _T("2.0");
	m_strQ = _T("1.1025");
	m_strTp = _T("39");

	m_fA = 1.0;
	m_fP = 2.0;
	m_fQ = 1.1025;
	m_strTp = _T("39");

}

CCharElementI2TEx::~CCharElementI2TEx()
{
}

long CCharElementI2TEx::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementInverse::XmlReadOwn(oNode, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strAKey, oNode, m_strA);
	xml_GetAttibuteValue(pXmlKeys->m_strPKey, oNode, m_strP);
	xml_GetAttibuteValue(pXmlKeys->m_strQKey, oNode, m_strQ);
	xml_GetAttibuteValue(pXmlKeys->m_strTpKey, oNode, m_strTp);

	return 0;
}

long CCharElementI2TEx::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementInverse::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strAKey, oElement, m_strA);
	xml_SetAttributeValue(pXmlKeys->m_strPKey, oElement, m_strP);
	xml_SetAttributeValue(pXmlKeys->m_strQKey, oElement, m_strQ);
	xml_SetAttributeValue(pXmlKeys->m_strTpKey, oElement, m_strTp);

	return 0;
}

void CCharElementI2TEx::InitAfterRead()
{
}

BOOL CCharElementI2TEx::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementI2TEx *p = (CCharElementI2TEx*)pObj;

	if(m_strA != p->m_strA)
	{
		return FALSE;
	}

	if(m_strP != p->m_strP)
	{
		return FALSE;
	}

	if(m_strQ != p->m_strQ)
	{
		return FALSE;
	}

	if(m_strTp != p->m_strTp)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCharElementI2TEx::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementI2TEx *p = (CCharElementI2TEx*)pDest;
	CCharElementInverse::CopyOwn(pDest);

	p->m_strTp = m_strTp;
	p->m_strP = m_strP;

	return TRUE;
}

CBaseObject* CCharElementI2TEx::Clone()
{
	CCharElementI2TEx *p = new CCharElementI2TEx();
	Copy(p);
	return p;
}

long CCharElementI2TEx::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CCharElementInverse::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strA);
		BinarySerializeCalLen(oBinaryBuffer, m_strP);
		BinarySerializeCalLen(oBinaryBuffer, m_strQ);
		BinarySerializeCalLen(oBinaryBuffer, m_strTp);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strA);
		BinarySerializeRead(oBinaryBuffer, m_strP);
		BinarySerializeRead(oBinaryBuffer, m_strQ);
		BinarySerializeRead(oBinaryBuffer, m_strTp);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strA);
		BinarySerializeWrite(oBinaryBuffer, m_strP);
		BinarySerializeWrite(oBinaryBuffer, m_strQ);
		BinarySerializeWrite(oBinaryBuffer, m_strTp);
	}
	return 0;
}
CString CCharElementI2TEx::ReturnXml()
{
	CString str;

	str.Format(_T("ITEx  A=\"%s\" P=\"%s\" Q=\"%s\" Tp=\"%s\""),m_strA.GetString(),m_strP.GetString(),m_strQ.GetString(),m_strTp.GetString());

	return str;
}

void CCharElementI2TEx::Draw(CDC *pDC)   //圆特性曲线
{

}


void CCharElementI2TEx::CalByExpression(BOOL bCalLines, CExBaseList *pDrawList)
{
	//计算自身数据
	CalCharElementExpression(m_strA, m_fA, TRUE);
	CalCharElementExpression(m_strP, m_fP, TRUE);
	CalCharElementExpression(m_strQ, m_fQ, TRUE);
	CalCharElementExpression(m_strTp, m_fTp, TRUE);

	CCharElementInverse::CalByExpression(bCalLines, pDrawList);
}


void CCharElementI2TEx::CalInversePolyline()
{
	m_nPoints = 0;//每次计算，需要将当前使用的点数清零，否则就持续累加
	double dx = 1, dTime = 0;
	
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


BOOL CCharElementI2TEx::IncreaseX(double &dValX)
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
	if (dValX > dStand && dStand != 1)	//20211027 SF
	{
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

double CCharElementI2TEx::CalInverse(double dVal)
{
	double dTempVal = pow(dVal,m_fP);
	double dTemp = dTempVal - m_fQ;

	if (math_IsEqual(dTemp, 0))
	{
		return -1;
	}	
	
#ifdef _PSX_IDE_QT_
	double dValue = qLn(dTempVal / dTemp);
#else
	double dValue = log(dTempVal / dTemp);
#endif

	if (math_IsEqual(dValue, 0))
	{
		return -1;
	}

	double dT = m_fA * m_fTp * dValue;
 
	return dT;
}

