//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementIAC.cpp  CCharElementIAC


#include "stdafx.h"
#include "CharElementIAC.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharElementIAC::CCharElementIAC()
{
	//初始化属性
	m_strID = CHAR_ELEMENT_ID_IAC;

#ifndef NOT_USE_XLANGUAGE
	m_strName = g_sLangTxt_IAC/*_T("圆（IAC）")*/;
#else
	m_strName = _T("圆（IAC）");
#endif

	//初始化成员变量
	
}

CCharElementIAC::~CCharElementIAC()
{
}

long CCharElementIAC::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementInverse::XmlReadOwn(oNode, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTpKey, oNode, m_strTp);
	xml_GetAttibuteValue(pXmlKeys->m_strAKey, oNode, m_strA);
	xml_GetAttibuteValue(pXmlKeys->m_strBKey, oNode, m_strB);
	xml_GetAttibuteValue(pXmlKeys->m_strCKey, oNode, m_strC);
	xml_GetAttibuteValue(pXmlKeys->m_strDKey, oNode, m_strD);
	xml_GetAttibuteValue(pXmlKeys->m_strEKey, oNode, m_strE);
	xml_GetAttibuteValue(pXmlKeys->m_strBetaKey, oNode, m_strBeta);

	return 0;
}

long CCharElementIAC::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementInverse::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTpKey, oElement, m_strTp);
	xml_SetAttributeValue(pXmlKeys->m_strAKey, oElement, m_strA);
	xml_SetAttributeValue(pXmlKeys->m_strBKey, oElement, m_strB);
	xml_SetAttributeValue(pXmlKeys->m_strCKey, oElement, m_strC);
	xml_SetAttributeValue(pXmlKeys->m_strDKey, oElement, m_strD);
	xml_SetAttributeValue(pXmlKeys->m_strEKey, oElement, m_strE);
	xml_SetAttributeValue(pXmlKeys->m_strBetaKey, oElement, m_strBeta);

	return 0;
}

void CCharElementIAC::InitAfterRead()
{
}

BOOL CCharElementIAC::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementIAC *p = (CCharElementIAC*)pObj;

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

	if(m_strC != p->m_strC)
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

	if(m_strBeta != p->m_strBeta)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCharElementIAC::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementIAC *p = (CCharElementIAC*)pDest;
	CCharElementInverse::CopyOwn(pDest);

	p->m_strTp = m_strTp;
	p->m_strA = m_strA;
	p->m_strB = m_strB;
	p->m_strC = m_strC;
	p->m_strD = m_strD;
	p->m_strE = m_strE;
	p->m_strBeta = m_strBeta;

	p->m_fTp = m_fTp;
	p->m_fA = m_fA;
	p->m_fB = m_fB;
	p->m_fC = m_fC;
	p->m_fD = m_fD;
	p->m_fE = m_fE;
	p->m_fBeta = m_fBeta;

	return TRUE;
}

CBaseObject* CCharElementIAC::Clone()
{
	CCharElementIAC *p = new CCharElementIAC();
	Copy(p);
	return p;
}
long CCharElementIAC::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CCharElementInverse::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strTp);
		BinarySerializeCalLen(oBinaryBuffer, m_strA);
		BinarySerializeCalLen(oBinaryBuffer, m_strB);
		BinarySerializeCalLen(oBinaryBuffer, m_strC);
		BinarySerializeCalLen(oBinaryBuffer, m_strD);
		BinarySerializeCalLen(oBinaryBuffer, m_strE);
		BinarySerializeCalLen(oBinaryBuffer, m_strBeta);

		BinarySerializeCalLen(oBinaryBuffer, m_fTp);
		BinarySerializeCalLen(oBinaryBuffer, m_fA);
		BinarySerializeCalLen(oBinaryBuffer, m_fB);
		BinarySerializeCalLen(oBinaryBuffer, m_fC);
		BinarySerializeCalLen(oBinaryBuffer, m_fD);
		BinarySerializeCalLen(oBinaryBuffer, m_fE);
		BinarySerializeCalLen(oBinaryBuffer, m_fBeta);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strTp);
		BinarySerializeRead(oBinaryBuffer, m_strA);
		BinarySerializeRead(oBinaryBuffer, m_strB);
		BinarySerializeRead(oBinaryBuffer, m_strC);
		BinarySerializeRead(oBinaryBuffer, m_strD);
		BinarySerializeRead(oBinaryBuffer, m_strE);
		BinarySerializeRead(oBinaryBuffer, m_strBeta);

		BinarySerializeRead(oBinaryBuffer, m_fTp);
		BinarySerializeRead(oBinaryBuffer, m_fA);
		BinarySerializeRead(oBinaryBuffer, m_fB);
		BinarySerializeRead(oBinaryBuffer, m_fC);
		BinarySerializeRead(oBinaryBuffer, m_fD);
		BinarySerializeRead(oBinaryBuffer, m_fE);
		BinarySerializeRead(oBinaryBuffer, m_fBeta);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strTp);
		BinarySerializeWrite(oBinaryBuffer, m_strA);
		BinarySerializeWrite(oBinaryBuffer, m_strB);
		BinarySerializeWrite(oBinaryBuffer, m_strC);
		BinarySerializeWrite(oBinaryBuffer, m_strD);
		BinarySerializeWrite(oBinaryBuffer, m_strE);
		BinarySerializeWrite(oBinaryBuffer, m_strBeta);

		BinarySerializeWrite(oBinaryBuffer, m_fTp);
		BinarySerializeWrite(oBinaryBuffer, m_fA);
		BinarySerializeWrite(oBinaryBuffer, m_fB);
		BinarySerializeWrite(oBinaryBuffer, m_fC);
		BinarySerializeWrite(oBinaryBuffer, m_fD);
		BinarySerializeWrite(oBinaryBuffer, m_fE);
		BinarySerializeWrite(oBinaryBuffer, m_fBeta);
	}
	return 0;
}

CString CCharElementIAC::ReturnXml()
{
	CString str;
	str.Format(_T("IAC Tp=\"%s\" A=\"%s\" B=\"%s\" C=\"%s\" D=\"%s\" E=\"%s\" Beta=\"%s\"")
        ,m_strTp.GetString(),m_strA.GetString(),m_strB.GetString()
               ,m_strC.GetString(),m_strD.GetString(),m_strE.GetString(),m_strBeta.GetString());
	return str;
}

void CCharElementIAC::Draw(CDC *pDC)   //圆特性曲线
{

}


void CCharElementIAC::CalByExpression(BOOL bCalLines, CExBaseList *pDrawList)
{
	//计算自身数据
	CalCharElementExpression(m_strTp, m_fTp, TRUE);
	CalCharElementExpression(m_strA, m_fA, TRUE);
	CalCharElementExpression(m_strB, m_fB, TRUE);
	CalCharElementExpression(m_strC, m_fC, TRUE);
	CalCharElementExpression(m_strD, m_fD, TRUE);
	CalCharElementExpression(m_strE, m_fE, TRUE);
	CalCharElementExpression(m_strBeta, m_fBeta, TRUE);

	CCharElementInverse::CalByExpression(bCalLines, pDrawList);
}

/*

double GBS_IAC(double dValue, double dTp, double dA, double dB, double dC, double dD, double dE, double dBeta)
{
double d = dValue - dC;
double dVal = dA + dB / d + dD / (d * d) + dE / (d*d*d);
dVal = dVal * (dTp / dBeta);
return dVal;
}

*/

void CCharElementIAC::CalTestLines(UINT nTestLineMode)
{
// 	double dAngleGap = 360 / m_nTestPoints;
// 	double dErrorLen = GetErrorLength();
// 
// 	POS pos = GetHeadPosition();
// 	CCharElementTestLine *pTestLine = NULL;
// 	double dAngle = 0, dX = 0, dY = 0, dXg = 0, dYg = 0;
// 
// 	while (pos != NULL)
// 	{
// 		pTestLine = (CCharElementTestLine *)GetNext(pos);
// 		dAngle = pTestLine->m_fPos * dAngleGap;
// 		
// 		dXg = dErrorLen * cos(dAngle * _PI_D_180);
// 		dYg = dErrorLen * sin(dAngle * _PI_D_180);
// 
// 		pTestLine->m_fXset = m_fXCenter + m_fXRadius * cos(dAngle * _PI_D_180);
// 		pTestLine->m_fYset = m_fYCenter + m_fXRadius * sin(dAngle * _PI_D_180);
// 		pTestLine->m_fXb = pTestLine->m_fXset + dXg;
// 		pTestLine->m_fYb = pTestLine->m_fYset + dYg;
// 		pTestLine->m_fXe = pTestLine->m_fXset - dXg;
// 		pTestLine->m_fYe = pTestLine->m_fYset - dYg;
// 	}
}

void CCharElementIAC::CalInversePolyline()
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


BOOL CCharElementIAC::IncreaseX(double &dValX)
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

double CCharElementIAC::CalInverse(double dVal)
{
	double d = dVal - m_fC;
	double dT = m_fA + m_fB / d + m_fD / (d * d) + m_fE / (d*d*d);
	dT = dT * (m_fTp / m_fBeta);
	return dT;
}

