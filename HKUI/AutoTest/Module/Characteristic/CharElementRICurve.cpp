#include "stdafx.h"
#include "CharElementRICurve.h"
#ifdef _PSX_IDE_QT_
#include <qmath.h> 
#endif
#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharElementRICurve::CCharElementRICurve()
{
	//��ʼ������
	m_strID = CHAR_ELEMENT_ID_RICURVE;

#ifndef NOT_USE_XLANGUAGE
	m_strName = /*g_sLangTxt_IEEE*/_T("Բ��RICurve��");
#else
	m_strName = _T("Բ��RICurve��");
#endif

	//��ʼ����Ա����
	m_strK =_T("1.000");

	m_fK = 1.0;
}

CCharElementRICurve::~CCharElementRICurve()
{
}

long CCharElementRICurve::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementInverse::XmlReadOwn(oNode, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strKKey, oNode, m_strK);

	return 0;
}

long CCharElementRICurve::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementInverse::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strKKey, oElement, m_strK);

	return 0;
}

void CCharElementRICurve::InitAfterRead()
{
}

BOOL CCharElementRICurve::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementRICurve *p = (CCharElementRICurve*)pObj;

	if(m_strK != p->m_strK)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCharElementRICurve::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementRICurve *p = (CCharElementRICurve*)pDest;
	CCharElementInverse::CopyOwn(pDest);

	p->m_strK = m_strK;

	return TRUE;
}

CBaseObject* CCharElementRICurve::Clone()
{
	CCharElementRICurve *p = new CCharElementRICurve();
	Copy(p);
	return p;
}

long CCharElementRICurve::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CCharElementInverse::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strK);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strK);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strK);
	}
	return 0;
}
CString CCharElementRICurve::ReturnXml()
{
	CString str;

	str.Format(_T("RICurve  K=\"%s\""),m_strK.GetString());

	return str;
}

void CCharElementRICurve::Draw(CDC *pDC)   //Բ��������
{

}


void CCharElementRICurve::CalByExpression(BOOL bCalLines, CExBaseList *pDrawList)
{
	//������������
	CalCharElementExpression(m_strK, m_fK, TRUE);

	CCharElementInverse::CalByExpression(bCalLines, pDrawList);
}


void CCharElementRICurve::CalInversePolyline()
{
	m_nPoints = 0;//ÿ�μ��㣬��Ҫ����ǰʹ�õĵ������㣬����ͳ����ۼ�
	double dx = 0, dTime = 0;
	
	SetPointsMax(200); //��ʼ��Ϊ200��
	BOOL bTrue = TRUE;

	//���㷴ʱ�޲���
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


BOOL CCharElementRICurve::IncreaseX(double &dValX)
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
	{//���ֵ����
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

double CCharElementRICurve::CalInverse(double dVal)
{
	double dT = m_fK /  (0.339- 0.236 / dVal);
	return dT;
}

