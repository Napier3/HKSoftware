//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementUIVP.cpp  CCharElementIUF


#include "stdafx.h"
#include "CharElementIUF.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharElementIUF::CCharElementIUF()
{
	//初始化属性
	m_strID = CHAR_ELEMENT_ID_IUF;

#ifndef NOT_USE_XLANGUAGE
	m_strName = _T("反时限（IUF）");
#else
	m_strName = _T("反时限（IUF）");
#endif

	//初始化成员变量
	m_strP = _T("1.0");
	m_strD = _T("1.2");
	m_strPickup = _T("1.05");
	m_strK = _T("1.05");

	m_fP = 1.0;
	m_fD = 1.2f;
	m_fPickup = 1.05f;
	m_fK = 1.05f;
}

CCharElementIUF::~CCharElementIUF()
{
}

long CCharElementIUF::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementInverse::XmlReadOwn(oNode, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDKey, oNode, m_strD);
	xml_GetAttibuteValue(pXmlKeys->m_strPKey, oNode, m_strP);
	xml_GetAttibuteValue(pXmlKeys->m_strPickupKey, oNode, m_strPickup);
	xml_GetAttibuteValue(pXmlKeys->m_strKKey, oNode, m_strK);

	return 0;
}

long CCharElementIUF::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementInverse::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strPKey, oElement, m_strP);
	xml_SetAttributeValue(pXmlKeys->m_strDKey, oElement, m_strD);
	xml_SetAttributeValue(pXmlKeys->m_strPickupKey, oElement, m_strPickup);
	xml_SetAttributeValue(pXmlKeys->m_strKKey, oElement, m_strK);

	return 0;
}

void CCharElementIUF::InitAfterRead()
{
}

BOOL CCharElementIUF::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementIUF *p = (CCharElementIUF*)pObj;

	if(m_strP != p->m_strP)
	{
		return FALSE;
	}

	if(m_strD != p->m_strD)
	{
		return FALSE;
	}

	if(m_strPickup != p->m_strPickup)
	{
		return FALSE;
	}

	if(m_strK != p->m_strK)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCharElementIUF::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementIUF *p = (CCharElementIUF*)pDest;
	CCharElementInverse::CopyOwn(pDest);

	p->m_strP = m_strP;
	p->m_strD = m_strD;
	p->m_strPickup = m_strPickup;
	p->m_strK = m_strK;

	return TRUE;
}

CBaseObject* CCharElementIUF::Clone()
{
	CCharElementIUF *p = new CCharElementIUF();
	Copy(p);
	return p;
}
long CCharElementIUF::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CCharElementInverse::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strP);
		BinarySerializeCalLen(oBinaryBuffer, m_strD);
		BinarySerializeCalLen(oBinaryBuffer, m_strPickup);
		BinarySerializeCalLen(oBinaryBuffer, m_strK);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strP);
		BinarySerializeRead(oBinaryBuffer, m_strD);
		BinarySerializeRead(oBinaryBuffer, m_strPickup);
		BinarySerializeRead(oBinaryBuffer, m_strK);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strP);
		BinarySerializeWrite(oBinaryBuffer, m_strD);
		BinarySerializeWrite(oBinaryBuffer, m_strPickup);
		BinarySerializeWrite(oBinaryBuffer, m_strK);
	}
	return 0;
}
CString CCharElementIUF::ReturnXml()
{
	CString str;

	str.Format(_T("IUF P=\"%s\" D=\"%s\" Pickup=\"%s\" K=\"%s\""),m_strP.GetString(),m_strD.GetString(),
		m_strPickup.GetString(),m_strK.GetString());

	return str;
}

void CCharElementIUF::Draw(CDC *pDC)   //圆特性曲线
{

}


void CCharElementIUF::CalByExpression(BOOL bCalLines, CExBaseList *pDrawList)
{
	//计算自身数据
	CalCharElementExpression(m_strP, m_fP, TRUE);
	CalCharElementExpression(m_strD, m_fD, TRUE);
	CalCharElementExpression(m_strPickup, m_fPickup, TRUE);
	CalCharElementExpression(m_strK, m_fK, TRUE);

	CCharElementInverse::CalByExpression(bCalLines, pDrawList);
}


void CCharElementIUF::CalInversePolyline()
{
	m_nPoints = 0;//每次计算，需要将当前使用的点数清零，否则就持续累加
	double dx = 1, dTime = 0;
	dx = 1;
	m_fXmax = 2;
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


BOOL CCharElementIUF::IncreaseX(double &dValX)
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
		dStand = 2;
	}

	if (dValX > m_fXmax)
	{//最大值限制
		return FALSE;
	}
	if (dValX > dStand && dStand != 2)
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

double CCharElementIUF::CalInverse(double dVal)
{
 	double dtemp =dVal/(m_fK*m_fPickup);
 	double dTempVal = pow(dtemp, m_fP) - 1;

	if (math_IsEqual(dTempVal, 0))
	{
		return -1;
	}
 
 	double dT = m_fD / dTempVal;

	return dT;
}

