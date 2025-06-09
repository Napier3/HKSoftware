//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementUIVP.cpp  CCharElementUIVP


#include "stdafx.h"
#include "CharElementUIVP.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharElementUIVP::CCharElementUIVP()
{
	//初始化属性
	m_strID = CHAR_ELEMENT_ID_UIVP;

#ifndef NOT_USE_XLANGUAGE
	m_strName = g_sLangTxt_IEEE/*_T("圆（UIVP）")*/;
#else
	m_strName = _T("圆（UIVP）");
#endif

	//初始化成员变量
	m_strC = _T("0");
	m_strA = _T("2.0");
	m_strB = _T("1.0");
	m_strP = _T("1.0");
	m_strD = _T("0");
	m_strE = _T("0");
	m_strK = _T("1.0");
	m_strVp = _T("100.0");

	m_fC = 0;
	m_fA = 2.0;
	m_fB = 1.0;
	m_fP = 1.0;
	m_fD = 0;
	m_fE = 0;
	m_fK = 1;
	m_fVp = 100.0f;

	m_bUType = false;
}

CCharElementUIVP::~CCharElementUIVP()
{
}

long CCharElementUIVP::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementInverse::XmlReadOwn(oNode, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strAKey, oNode, m_strA);
	xml_GetAttibuteValue(pXmlKeys->m_strBKey, oNode, m_strB);
	xml_GetAttibuteValue(pXmlKeys->m_strCKey, oNode, m_strC);
	xml_GetAttibuteValue(pXmlKeys->m_strDKey, oNode, m_strD);
	xml_GetAttibuteValue(pXmlKeys->m_strEKey, oNode, m_strE);
	xml_GetAttibuteValue(pXmlKeys->m_strPKey, oNode, m_strP);
	xml_GetAttibuteValue(pXmlKeys->m_strKKey, oNode, m_strK);
	xml_GetAttibuteValue(pXmlKeys->m_strVpKey, oNode, m_strVp);

	return 0;
}

long CCharElementUIVP::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementInverse::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strCKey, oElement, m_strC);
	xml_SetAttributeValue(pXmlKeys->m_strAKey, oElement, m_strA);
	xml_SetAttributeValue(pXmlKeys->m_strBKey, oElement, m_strB);
	xml_SetAttributeValue(pXmlKeys->m_strPKey, oElement, m_strP);
	xml_SetAttributeValue(pXmlKeys->m_strDKey, oElement, m_strD);
	xml_SetAttributeValue(pXmlKeys->m_strEKey, oElement, m_strE);
	xml_SetAttributeValue(pXmlKeys->m_strKKey, oElement, m_strK);
	xml_SetAttributeValue(pXmlKeys->m_strVpKey, oElement, m_strVp);

	return 0;
}

void CCharElementUIVP::InitAfterRead()
{
}

BOOL CCharElementUIVP::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementUIVP *p = (CCharElementUIVP*)pObj;

	if(m_strC != p->m_strC)
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

	if(m_strD != p->m_strD)
	{
		return FALSE;
	}

	if(m_strE != p->m_strE)
	{
		return FALSE;
	}

	if(m_strK != p->m_strK)
	{
		return FALSE;
	}

	if(m_strVp != p->m_strVp)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CCharElementUIVP::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementUIVP *p = (CCharElementUIVP*)pDest;
	CCharElementInverse::CopyOwn(pDest);

	p->m_strC = m_strC;
	p->m_strA = m_strA;
	p->m_strB = m_strB;
	p->m_strP = m_strP;
	p->m_strD = m_strD;
	p->m_strE = m_strE;
	p->m_strK = m_strK;
	p->m_strVp = m_strVp;

	return TRUE;
}

CBaseObject* CCharElementUIVP::Clone()
{
	CCharElementUIVP *p = new CCharElementUIVP();
	Copy(p);
	return p;
}
long CCharElementUIVP::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CCharElementInverse::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strC);
		BinarySerializeCalLen(oBinaryBuffer, m_strA);
		BinarySerializeCalLen(oBinaryBuffer, m_strB);
		BinarySerializeCalLen(oBinaryBuffer, m_strP);
		BinarySerializeCalLen(oBinaryBuffer, m_strD);
		BinarySerializeCalLen(oBinaryBuffer, m_strE);
		BinarySerializeCalLen(oBinaryBuffer, m_strK);
		BinarySerializeCalLen(oBinaryBuffer, m_strVp);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strC);
		BinarySerializeRead(oBinaryBuffer, m_strA);
		BinarySerializeRead(oBinaryBuffer, m_strB);
		BinarySerializeRead(oBinaryBuffer, m_strP);
		BinarySerializeRead(oBinaryBuffer, m_strD);
		BinarySerializeRead(oBinaryBuffer, m_strE);
		BinarySerializeRead(oBinaryBuffer, m_strK);
		BinarySerializeRead(oBinaryBuffer, m_strVp);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strC);
		BinarySerializeWrite(oBinaryBuffer, m_strA);
		BinarySerializeWrite(oBinaryBuffer, m_strB);
		BinarySerializeWrite(oBinaryBuffer, m_strP);
		BinarySerializeWrite(oBinaryBuffer, m_strD);
		BinarySerializeWrite(oBinaryBuffer, m_strE);
		BinarySerializeWrite(oBinaryBuffer, m_strK);
		BinarySerializeWrite(oBinaryBuffer, m_strVp);
	}
	return 0;
}
CString CCharElementUIVP::ReturnXml()
{
	CString str;

	str.Format(_T("UIVP A=\"%s\" B=\"%s\" C=\"%s\" D=\"%s\" E=\"%s\" K=\"%s\" P=\"%s\" Vp=\"%s\"")
        ,m_strA.GetString(),m_strB.GetString(),m_strC.GetString(),m_strD.GetString()
               , m_strE.GetString(), m_strK.GetString(), m_strP.GetString(),m_strVp.GetString());

	return str;
}

void CCharElementUIVP::Draw(CDC *pDC)   //圆特性曲线
{

}


void CCharElementUIVP::CalByExpression(BOOL bCalLines, CExBaseList *pDrawList)
{
	//计算自身数据
	CalCharElementExpression(m_strC, m_fC, TRUE);
	CalCharElementExpression(m_strA, m_fA, TRUE);
	CalCharElementExpression(m_strB, m_fB, TRUE);
	CalCharElementExpression(m_strP, m_fP, TRUE);
	CalCharElementExpression(m_strD, m_fD, TRUE);
	CalCharElementExpression(m_strE, m_fE, TRUE);
	CalCharElementExpression(m_strK, m_fK, TRUE);
	CalCharElementExpression(m_strVp, m_fVp, TRUE);

	CCharElementInverse::CalByExpression(bCalLines, pDrawList);
}


void CCharElementUIVP::CalInversePolyline()
{
	m_nPoints = 0;//每次计算，需要将当前使用的点数清零，否则就持续累加
	double dx = 1, dTime = 0;
	if (!m_bUType)
	{
		dx = 0;
		m_fXmax = m_fVp;
	}
	else
	{
		dx = m_fVp;
		m_fXmax = 2*m_fVp;
	}
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


BOOL CCharElementUIVP::IncreaseX(double &dValX)
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
		if (m_bUType)
		{
			dStand = m_fVp;
		}
		else
		{
			dStand = 1;
		}
	}

	if (dValX > m_fXmax)
	{//最大值限制
		return FALSE;
	}
// 	if (dValX > dStand && dStand != 1)	//20211027 SF
// 	{
// 		return FALSE;
// 	}

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

double CCharElementUIVP::CalInverse(double dVal)
{
	double dtemp = m_fB * fabs(1 - dVal/m_fVp) - m_fC;
	double dTempVal = pow(dtemp, m_fP) - m_fE;

	if (math_IsEqual(dTempVal, 0))
	{
		return -1;
	}

	double dT = (m_fA * m_fK) / ( dTempVal ) + m_fD;

	return dT;
}

