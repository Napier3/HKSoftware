//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementIEEE.cpp  CCharElementIEEE


#include "stdafx.h"
#include "CharElementIEEE.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharElementIEEE::CCharElementIEEE()
{
	//初始化属性
	m_strID = CHAR_ELEMENT_ID_IEEE;

#ifndef NOT_USE_XLANGUAGE
	m_strName = g_sLangTxt_IEEE/*_T("圆（IEEE）")*/;
#else
	m_strName = _T("圆（IEEE）");
#endif

	//初始化成员变量
	m_strTp = _T("39");
	m_strA = _T("1.0");
	m_strB = _T("0");
	m_strP = _T("2.0");
	m_strQ = _T("1.1025");
	m_strK1 = _T("0");
	m_strK2 = _T("0");

	m_fTp = 39;
	m_fA = 1.0;
	m_fB = 0;
	m_fP = 2.0;
	m_fQ = 1.1025;
	m_fK1 = 0;
	m_fK2 = 0;
}

CCharElementIEEE::~CCharElementIEEE()
{
}

long CCharElementIEEE::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementInverse::XmlReadOwn(oNode, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTpKey, oNode, m_strTp);
	xml_GetAttibuteValue(pXmlKeys->m_strAKey, oNode, m_strA);
	xml_GetAttibuteValue(pXmlKeys->m_strBKey, oNode, m_strB);
	xml_GetAttibuteValue(pXmlKeys->m_strPKey, oNode, m_strP);
	xml_GetAttibuteValue(pXmlKeys->m_strQKey, oNode, m_strQ);
	xml_GetAttibuteValue(pXmlKeys->m_strK1Key, oNode, m_strK1);
	xml_GetAttibuteValue(pXmlKeys->m_strK2Key, oNode, m_strK2);

	return 0;
}

long CCharElementIEEE::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementInverse::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTpKey, oElement, m_strTp);
	xml_SetAttributeValue(pXmlKeys->m_strAKey, oElement, m_strA);
	xml_SetAttributeValue(pXmlKeys->m_strBKey, oElement, m_strB);
	xml_SetAttributeValue(pXmlKeys->m_strPKey, oElement, m_strP);
	xml_SetAttributeValue(pXmlKeys->m_strQKey, oElement, m_strQ);
	xml_SetAttributeValue(pXmlKeys->m_strK1Key, oElement, m_strK1);
	xml_SetAttributeValue(pXmlKeys->m_strK2Key, oElement, m_strK2);

	return 0;
}

void CCharElementIEEE::InitAfterRead()
{
}

BOOL CCharElementIEEE::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementIEEE *p = (CCharElementIEEE*)pObj;

	if(m_strTp != p->m_strTp)
	{
		return FALSE;
	}

	if(m_strA != p->m_strA)
	{
		return FALSE;
	}

	if(m_strB != p->m_strB)
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

	if(m_strK1 != p->m_strK1)
	{
		return FALSE;
	}

	if(m_strK2 != p->m_strK2)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCharElementIEEE::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementIEEE *p = (CCharElementIEEE*)pDest;
	CCharElementInverse::CopyOwn(pDest);

	p->m_strTp = m_strTp;
	p->m_strA = m_strA;
	p->m_strB = m_strB;
	p->m_strP = m_strP;
	p->m_strQ = m_strQ;
	p->m_strK1 = m_strK1;
	p->m_strK2 = m_strK2;

	return TRUE;
}

CBaseObject* CCharElementIEEE::Clone()
{
	CCharElementIEEE *p = new CCharElementIEEE();
	Copy(p);
	return p;
}
long CCharElementIEEE::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CCharElementInverse::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strTp);
		BinarySerializeCalLen(oBinaryBuffer, m_strA);
		BinarySerializeCalLen(oBinaryBuffer, m_strB);
		BinarySerializeCalLen(oBinaryBuffer, m_strP);
		BinarySerializeCalLen(oBinaryBuffer, m_strQ);
		BinarySerializeCalLen(oBinaryBuffer, m_strK1);
		BinarySerializeCalLen(oBinaryBuffer, m_strK2);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strTp);
		BinarySerializeRead(oBinaryBuffer, m_strA);
		BinarySerializeRead(oBinaryBuffer, m_strB);
		BinarySerializeRead(oBinaryBuffer, m_strP);
		BinarySerializeRead(oBinaryBuffer, m_strQ);
		BinarySerializeRead(oBinaryBuffer, m_strK1);
		BinarySerializeRead(oBinaryBuffer, m_strK2);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strTp);
		BinarySerializeWrite(oBinaryBuffer, m_strA);
		BinarySerializeWrite(oBinaryBuffer, m_strB);
		BinarySerializeWrite(oBinaryBuffer, m_strP);
		BinarySerializeWrite(oBinaryBuffer, m_strQ);
		BinarySerializeWrite(oBinaryBuffer, m_strK1);
		BinarySerializeWrite(oBinaryBuffer, m_strK2);
	}
	return 0;
}
CString CCharElementIEEE::ReturnXml()
{
	CString str;

	str.Format(_T("IEEE Tp=\"%s\" A=\"%s\" B=\"%s\" P=\"%s\" Q=\"%s\" K1=\"%s\" K2=\"%s\"")
        ,m_strTp.GetString(),m_strA.GetString(),m_strB.GetString(),m_strP.GetString()
               , m_strQ.GetString(), m_strK1.GetString(), m_strK2.GetString());

	return str;
}

void CCharElementIEEE::Draw(CDC *pDC)   //圆特性曲线
{

}


void CCharElementIEEE::CalByExpression(BOOL bCalLines, CExBaseList *pDrawList)
{
	//计算自身数据
	CalCharElementExpression(m_strTp, m_fTp, TRUE);
	CalCharElementExpression(m_strA, m_fA, TRUE);
	CalCharElementExpression(m_strB, m_fB, TRUE);
	CalCharElementExpression(m_strP, m_fP, TRUE);
	CalCharElementExpression(m_strQ, m_fQ, TRUE);
	CalCharElementExpression(m_strK1, m_fK1, TRUE);
	CalCharElementExpression(m_strK2, m_fK2, TRUE);

	CCharElementInverse::CalByExpression(bCalLines, pDrawList);
}


void CCharElementIEEE::CalInversePolyline()
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


BOOL CCharElementIEEE::IncreaseX(double &dValX)
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

double CCharElementIEEE::CalInverse(double dVal)
{
	double dTempVal = pow(dVal, m_fP) - m_fQ;

	if (math_IsEqual(dTempVal, 0))
	{
		return -1;
	}

	double dT = (m_fA * m_fTp + m_fK1) / ( dTempVal ) + m_fB * m_fTp + m_fK2;
	return dT;
}

