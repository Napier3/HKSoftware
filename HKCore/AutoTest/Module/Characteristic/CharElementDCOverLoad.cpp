#include "stdafx.h"
#include "CharElementDCOverLoad.h"
#ifdef _PSX_IDE_QT_
#include <qmath.h> 
#endif
#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharElementDCOverLoad::CCharElementDCOverLoad()
{
	//初始化属性
	m_strID = CHAR_ELEMENT_ID_DCOVERLOAD;

#ifndef NOT_USE_XLANGUAGE
	m_strName = g_sLangTxt_IEEE/*_T("圆（DCOVERLOAD）")*/;
#else
	m_strName = _T("圆（DCOVERLOAD）");
#endif

	//初始化成员变量
	m_strIb =_T("1.000");
	m_strK =_T("1.000");
	m_strConstant=_T("1.000");

	m_fIb = 1.0;
	m_fK = 1.0;
	m_fConstant= 1.0;
}

CCharElementDCOverLoad::~CCharElementDCOverLoad()
{
}

long CCharElementDCOverLoad::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementInverse::XmlReadOwn(oNode, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIBKey, oNode, m_strIb);
	xml_GetAttibuteValue(pXmlKeys->m_strKKey, oNode, m_strK);
	xml_GetAttibuteValue(pXmlKeys->m_strConstantKey, oNode, m_strConstant);

	return 0;
}

long CCharElementDCOverLoad::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementInverse::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIBKey, oElement, m_strIb);
	xml_SetAttributeValue(pXmlKeys->m_strKKey, oElement, m_strK);
	xml_SetAttributeValue(pXmlKeys->m_strConstantKey, oElement, m_strConstant);

	return 0;
}

void CCharElementDCOverLoad::InitAfterRead()
{
}

BOOL CCharElementDCOverLoad::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementDCOverLoad *p = (CCharElementDCOverLoad*)pObj;

	if(m_strIb != p->m_strIb)
	{
		return FALSE;
	}

	if(m_strK != p->m_strK)
	{
		return FALSE;
	}

	if(m_strConstant != p->m_strConstant)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCharElementDCOverLoad::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementDCOverLoad *p = (CCharElementDCOverLoad*)pDest;
	CCharElementInverse::CopyOwn(pDest);

	p->m_strIb = m_strIb;
	p->m_strK = m_strK;
	p->m_strConstant = m_strConstant;
	

	return TRUE;
}

CBaseObject* CCharElementDCOverLoad::Clone()
{
	CCharElementDCOverLoad *p = new CCharElementDCOverLoad();
	Copy(p);
	return p;
}

long CCharElementDCOverLoad::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CCharElementInverse::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strIb);
		BinarySerializeCalLen(oBinaryBuffer, m_strK);
		BinarySerializeCalLen(oBinaryBuffer, m_strConstant);

	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strIb);
		BinarySerializeRead(oBinaryBuffer, m_strK);
		BinarySerializeRead(oBinaryBuffer, m_strConstant);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strIb);
		BinarySerializeWrite(oBinaryBuffer, m_strK);
		BinarySerializeWrite(oBinaryBuffer, m_strConstant);

	}
	return 0;
}
CString CCharElementDCOverLoad::ReturnXml()
{
	CString str;

	str.Format(_T("DCOVERLOAD  IB=\"%s\" K=\"%s\" τ=\"%s\"")
        ,m_strIb.GetString(),m_strK.GetString(),m_strConstant.GetString());

	return str;
}

void CCharElementDCOverLoad::Draw(CDC *pDC)   //圆特性曲线
{

}


void CCharElementDCOverLoad::CalByExpression(BOOL bCalLines, CExBaseList *pDrawList)
{
	//计算自身数据
	CalCharElementExpression(m_strIb, m_fIb, TRUE);
	CalCharElementExpression(m_strK, m_fK, TRUE);
	CalCharElementExpression(m_strConstant, m_fConstant, TRUE);

	CCharElementInverse::CalByExpression(bCalLines, pDrawList);
}


void CCharElementDCOverLoad::CalInversePolyline()
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


BOOL CCharElementDCOverLoad::IncreaseX(double &dValX)
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

double CCharElementDCOverLoad::CalInverse(double dVal)
{
	double dtemp=(dVal*dVal)-(m_fK*m_fIb)*(m_fK*m_fIb);

	if (math_IsEqual(dtemp, 0))
	{
		return -1;
	}

	double dTempVal = (dVal*dVal)/dtemp;

	if(dTempVal <= 0)
	{
		return -1;
	}

#ifdef _PSX_IDE_QT_
	double dT =	m_fConstant * qLn(dTempVal);
#else
	double dT = m_fConstant * log(dTempVal);
#endif

	return dT;
}

