#include "stdafx.h"
#include "CharElementIT.h"
//#ifdef _PSX_IDE_QT_
//#include <qmath.h> 
//#endif
#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharElementIT::CCharElementIT()
{
	//初始化属性
	m_strID = CHAR_ELEMENT_ID_IT;

#ifndef NOT_USE_XLANGUAGE
	m_strName = /*g_sLangTxt_IEEE*/_T("圆（IT）");
#else
	m_strName = _T("圆（IT）");
#endif

	//初始化成员变量
	m_strTp =_T("39");
	m_strP = _T("2.0");

	m_fTp = 39;
	m_fP = 2.0;
}

CCharElementIT::~CCharElementIT()
{
}

long CCharElementIT::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementInverse::XmlReadOwn(oNode, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTpKey, oNode, m_strTp);
	xml_GetAttibuteValue(pXmlKeys->m_strPKey, oNode, m_strP);

	return 0;
}

long CCharElementIT::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementInverse::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTpKey, oElement, m_strTp);
	xml_SetAttributeValue(pXmlKeys->m_strPKey, oElement, m_strP);

	return 0;
}

void CCharElementIT::InitAfterRead()
{
}

BOOL CCharElementIT::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementIT *p = (CCharElementIT*)pObj;

	if(m_strTp != p->m_strTp)
	{
		return FALSE;
	}

	if(m_strP != p->m_strP)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCharElementIT::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementIT *p = (CCharElementIT*)pDest;
	CCharElementInverse::CopyOwn(pDest);

	p->m_strTp = m_strTp;
	p->m_strP = m_strP;

	return TRUE;
}

CBaseObject* CCharElementIT::Clone()
{
	CCharElementIT *p = new CCharElementIT();
	Copy(p);
	return p;
}

long CCharElementIT::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CCharElementInverse::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strTp);
		BinarySerializeCalLen(oBinaryBuffer, m_strP);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strTp);
		BinarySerializeRead(oBinaryBuffer, m_strP);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strTp);
		BinarySerializeWrite(oBinaryBuffer, m_strP);
	}
	return 0;
}
CString CCharElementIT::ReturnXml()
{
	CString str;

	str.Format(_T("IT  Tp=\"%s\" P=\"%s\""),m_strTp.GetString(),m_strP.GetString());

	return str;
}

void CCharElementIT::Draw(CDC *pDC)   //圆特性曲线
{

}


void CCharElementIT::CalByExpression(BOOL bCalLines, CExBaseList *pDrawList)
{
	//计算自身数据
	CalCharElementExpression(m_strTp, m_fTp, TRUE);
	CalCharElementExpression(m_strP, m_fP, TRUE);

	CCharElementInverse::CalByExpression(bCalLines, pDrawList);
}


//void CCharElementIT::CalInversePolyline()
//{
//	m_nPoints = 0;//每次计算，需要将当前使用的点数清零，否则就持续累加
//	double dx = 1, dTime = 0;
//
//	SetPointsMax(200); //初始化为200点
//	BOOL bTrue = TRUE;
//
//	//计算反时限部分
//	while (bTrue)
//	{
//		bTrue = IncreaseX(dx);
//		dTime = CalInverse(dx);
//
//		if (dTime < 0)
//		{
//			continue;
//		}
//
//		if (dTime > m_fTmax)
//		{
//			continue;
//		}
//
//		if (!HasPoints())
//		{
//			ExpandPointsMax(50);
//		}
//
//		AddPoint(dx, dTime);
//	}
//
//	AddSectionPoints();	
//}
//
//
//BOOL CCharElementIT::IncreaseX(double &dValX)
//{
//	double dStand = 0;
//
//	if (m_nUseSection[2] == 1)
//	{
//		dStand = m_fValSection[2];
//	}
//	else if (m_nUseSection[1] == 1)
//	{
//		dStand = m_fValSection[1];
//	}
//	else if (m_nUseSection[0] == 1)
//	{
//		dStand = m_fValSection[0];
//	}
//	else
//	{
//		dStand = 1;
//	}
//
//	if (dValX > m_fXmax)
//	{//最大值限制
//		return FALSE;
//	}
//
//	if (dValX > dStand && dStand != 1)	//20211027 SF
//	{
//		return FALSE;
//	}
//
//	if (dValX <= dStand*2)
//	{
//		dValX += 0.01*dStand;
//	}
//	else if (dValX <= dStand*4)
//	{
//		dValX += 0.02*dStand;
//	}
//	else if (dValX <= dStand*10)
//	{
//		dValX += 0.5*dStand;
//	}
//	else if (dValX <= dStand*100)
//	{
//		dValX += 2*dStand;
//	}
//	else if (dValX <= m_fXmax)
//	{
//		dValX += 0.02*m_fXmax;
//	}
//	else
//	{
//		return FALSE;
//	}
//
//
//	return TRUE;
//}

double CCharElementIT::CalInverse(double dVal)
{
	double dTempVal = pow(3,m_fP);
	double dTemp = pow(dVal,m_fP);

	if (math_IsEqual(dTemp, 0))
	{
		return -1;
	}

	double dT = m_fTp * ((5 * dTempVal) / dTemp);
 
	return dT;
}

