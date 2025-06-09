#include "stdafx.h"
#include "CharElementRXIDG.h"
#ifdef _PSX_IDE_QT_
#include <qmath.h> 
#endif
#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharElementRXIDG::CCharElementRXIDG()
{
	//初始化属性
	m_strID = CHAR_ELEMENT_ID_RXIDG;

#ifndef NOT_USE_XLANGUAGE
	m_strName = /*g_sLangTxt_IEEE*/_T("圆（RXIDG）");
#else
	m_strName = _T("圆（RXIDG）");
#endif

	//初始化成员变量
	m_strTp = _T("1.000");

	m_fTp = 1.0;
}

CCharElementRXIDG::~CCharElementRXIDG()
{
}

long CCharElementRXIDG::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementInverse::XmlReadOwn(oNode, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTpKey, oNode, m_strTp);

	return 0;
}

long CCharElementRXIDG::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementInverse::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTpKey, oElement, m_strTp);

	return 0;
}

void CCharElementRXIDG::InitAfterRead()
{
}

BOOL CCharElementRXIDG::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementRXIDG *p = (CCharElementRXIDG*)pObj;

	if(m_strTp != p->m_strTp)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCharElementRXIDG::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementRXIDG *p = (CCharElementRXIDG*)pDest;
	CCharElementInverse::CopyOwn(pDest);

	p->m_strTp = m_strTp;	

	return TRUE;
}

CBaseObject* CCharElementRXIDG::Clone()
{
	CCharElementRXIDG *p = new CCharElementRXIDG();
	Copy(p);
	return p;
}

long CCharElementRXIDG::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CCharElementInverse::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strTp);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strTp);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strTp);
	}
	return 0;
}
CString CCharElementRXIDG::ReturnXml()
{
	CString str;

	str.Format(_T("RXIDG Tp=\"%s\""),m_strTp.GetString());

	return str;
}

void CCharElementRXIDG::Draw(CDC *pDC)   //圆特性曲线
{

}


void CCharElementRXIDG::CalByExpression(BOOL bCalLines, CExBaseList *pDrawList)
{
	//计算自身数据
	CalCharElementExpression(m_strTp, m_fTp, TRUE);

	CCharElementInverse::CalByExpression(bCalLines, pDrawList);
}


void CCharElementRXIDG::CalInversePolyline()
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


BOOL CCharElementRXIDG::IncreaseX(double &dValX)
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

double CCharElementRXIDG::CalInverse(double dVal)
{
	double dTempVal = dVal/m_fTp;

	//if (math_IsEqual(dTempVal, 0))
	//{
	//	return -1;
	//}
	if(dTempVal <= 0)
	{
		return -1;
	}

#ifdef _PSX_IDE_QT_ 
	double dT =	5.8 - 1.35 * qLn(dTempVal);
#else
	double dT = 5.8 - 1.35 * log(dTempVal);
#endif

	return dT;
}

