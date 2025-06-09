//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CharElementInvOwnDef.cpp  CCharElementInvOwnDef


#include "stdafx.h"
#include "CharElementInvOwnDef.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharElementInvOwnDef::CCharElementInvOwnDef()
{
	//��ʼ������
	m_strID = CHAR_ELEMENT_ID_INVOWNDEF;

#ifndef NOT_USE_XLANGUAGE
	m_strName = g_sLangTxt_INVOWNDEF/*�Զ���*/;
#else
	m_strName =_T("��ʱ��INVOWNDEF)");
#endif

	m_strTmax = _T("70000");
	m_strXmax = _T("200");
	m_fTmax = 70000;
	m_fXmax = 200;

	m_strPoints = _T("");

	m_oPoints.SetParent(this);
}

CCharElementInvOwnDef::~CCharElementInvOwnDef()
{
}

long CCharElementInvOwnDef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementInverse::XmlReadOwn(oNode, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strPointsKey, oNode, m_strPoints);

	m_oPoints.InitPoints(m_strPoints); //���������ַ�����ʽ�����ڶ�����

	return 0;
}

long CCharElementInvOwnDef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementInverse::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	m_oPoints.GetPointsString(m_strPoints);
	xml_SetAttributeValue(pXmlKeys->m_strPointsKey, oElement, m_strPoints);

	InitPoints(m_oPoints.GetCount());
	CalInversePolyline();

	return 0;
}

void CCharElementInvOwnDef::InitAfterRead()
{
}

BOOL CCharElementInvOwnDef::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementInvOwnDef *p = (CCharElementInvOwnDef*)pObj;

	if(m_strTmax != p->m_strTmax)
	{
		return FALSE;
	}

	if(m_strXmax != p->m_strXmax)
	{
		return FALSE;
	}

	if(m_strPoints != p->m_strPoints)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCharElementInvOwnDef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementInvOwnDef *p = (CCharElementInvOwnDef*)pDest;
	CCharElementInverse::CopyOwn(pDest);

	p->m_strTmax = m_strTmax;
	p->m_strXmax = m_strXmax;
	p->m_strPoints = m_strPoints;

	(p->m_oPoints).DeleteAll();
	(p->m_oPoints).AppendClone(m_oPoints);

	return TRUE;
}

CBaseObject* CCharElementInvOwnDef::Clone()
{
	CCharElementInvOwnDef *p = new CCharElementInvOwnDef();
	Copy(p);
	return p;
}

long CCharElementInvOwnDef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CCharElementInverse::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strTmax);
		BinarySerializeCalLen(oBinaryBuffer, m_strXmax);
		BinarySerializeCalLen(oBinaryBuffer, m_strPoints);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strTmax);
		BinarySerializeRead(oBinaryBuffer, m_strXmax);
		BinarySerializeRead(oBinaryBuffer, m_strPoints);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strTmax);
		BinarySerializeWrite(oBinaryBuffer, m_strXmax);
		BinarySerializeWrite(oBinaryBuffer, m_strPoints);
	}
	return 0;
}

CString CCharElementInvOwnDef::ReturnXml()
{
	CString str;
	str.Format(_T("IOWNDEF x-max=\"%s\" t-max=\"%s\""),m_strXmax.GetString(),m_strTmax.GetString());
	return str;
}

void CCharElementInvOwnDef::Draw(CDC *pDC)   //�Զ�����������
{

}


void CCharElementInvOwnDef::CalByExpression(BOOL bCalLines)
{
	CalCharElementExpression(m_strTmax, m_fTmax, TRUE);
	CalCharElementExpression(m_strXmax, m_fXmax, TRUE);

	m_oPoints.CalByExpression(TRUE); //���������������ַ�����ʾ����Ϊ����
}

void CCharElementInvOwnDef::CalInversePolyline()
{
	m_nPoints = 0;//ÿ�μ��㣬��Ҫ����ǰʹ�õĵ������㣬����ͳ����ۼ�
	SetPointsMax(m_oPoints.GetCount()); 

	POS pos = m_oPoints.GetHeadPosition();
	CCharElementTestPoint *pObj = NULL;

	while(pos != NULL)
	{
		pObj = (CCharElementTestPoint*)(m_oPoints.GetNext(pos));
		pObj->CalByExpression(TRUE);
		AddPoint(pObj->m_fX, pObj->m_fY);
	}

	AddSectionPoints();
}

double CCharElementInvOwnDef::CalInverse(double dVal)
{
	return 0;
}

