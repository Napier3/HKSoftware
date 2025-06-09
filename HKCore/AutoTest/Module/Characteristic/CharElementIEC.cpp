//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementIEC.cpp  CCharElementIEC


#include "stdafx.h"
#include "CharElementIEC.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharElementIEC::CCharElementIEC()
{
	//初始化属性
	m_strID = CHAR_ELEMENT_ID_IEC;

#ifndef NOT_USE_XLANGUAGE
	m_strName = g_sLangTxt_IEC/*_T("圆（IEC）")*/;
#else
	m_strName = _T("圆（IEC）");
#endif

	//初始化成员变量
	m_strTp = _T("");
	m_strK = _T("");
	m_strAlpha = _T("");

	m_fTp = 0;
	m_fK = 0;
	m_fAlpha = 0;
}

CCharElementIEC::~CCharElementIEC()
{
}

long CCharElementIEC::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementInverse::XmlReadOwn(oNode, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTpKey, oNode, m_strTp);
	xml_GetAttibuteValue(pXmlKeys->m_strKKey, oNode, m_strK);
	xml_GetAttibuteValue(pXmlKeys->m_strAlphaKey, oNode, m_strAlpha);

	return 0;
}

long CCharElementIEC::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharElementInverse::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTpKey, oElement, m_strTp);
	xml_SetAttributeValue(pXmlKeys->m_strKKey, oElement, m_strK);
	xml_SetAttributeValue(pXmlKeys->m_strAlphaKey, oElement, m_strAlpha);

	return 0;
}

void CCharElementIEC::InitAfterRead()
{
}

BOOL CCharElementIEC::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementIEC *p = (CCharElementIEC*)pObj;

	if(m_strTp != p->m_strTp)
	{
		return FALSE;
	}

	if(m_strK != p->m_strK)
	{
		return FALSE;
	}

	if(m_strAlpha != p->m_strAlpha)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCharElementIEC::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementIEC *p = (CCharElementIEC*)pDest;
	CCharElementInverse::CopyOwn(pDest);

	p->m_strTp = m_strTp;
	p->m_strK = m_strK;
	p->m_strAlpha = m_strAlpha;

	p->m_fTp = m_fTp;
	p->m_fK = m_fK;
	p->m_fAlpha = m_fAlpha;

	return TRUE;
}

CBaseObject* CCharElementIEC::Clone()
{
	CCharElementIEC *p = new CCharElementIEC();
	Copy(p);
	return p;
}
long CCharElementIEC::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CCharElementInverse::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strTp);
		BinarySerializeCalLen(oBinaryBuffer, m_strK);
		BinarySerializeCalLen(oBinaryBuffer, m_strAlpha);

		BinarySerializeCalLen(oBinaryBuffer, m_fTp);
		BinarySerializeCalLen(oBinaryBuffer, m_fK);
		BinarySerializeCalLen(oBinaryBuffer, m_fAlpha);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strTp);
		BinarySerializeRead(oBinaryBuffer, m_strK);
		BinarySerializeRead(oBinaryBuffer, m_strAlpha);

		BinarySerializeRead(oBinaryBuffer, m_fTp);
		BinarySerializeRead(oBinaryBuffer, m_fK);
		BinarySerializeRead(oBinaryBuffer, m_fAlpha);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strTp);
		BinarySerializeWrite(oBinaryBuffer, m_strK);
		BinarySerializeWrite(oBinaryBuffer, m_strAlpha);

		BinarySerializeWrite(oBinaryBuffer, m_fTp);
		BinarySerializeWrite(oBinaryBuffer, m_fK);
		BinarySerializeWrite(oBinaryBuffer, m_fAlpha);
	}
	return 0;
}
CString CCharElementIEC::ReturnXml()
{
	CString str;
    str.Format(_T("IEC K=\"%s\" Tp=\"%s\" alpha=\"%s\""),m_strK.GetString(),m_fTp,m_strAlpha.GetString());
	return str;
}

void CCharElementIEC::Draw(CDC *pDC)   //圆特性曲线
{

}


void CCharElementIEC::CalByExpression(BOOL bCalLines, CExBaseList *pDrawList)
{
	//计算自身数据
	CalCharElementExpression(m_strTp, m_fTp, TRUE);
	CalCharElementExpression(m_strK, m_fK, TRUE);
	CalCharElementExpression(m_strAlpha, m_fAlpha, TRUE);

}

/*
double GBS_IEC(double dValue, double dTp, double dK, double dAlpha)
{
	double dVal = dTp * dK / (pow(dValue, dAlpha) - 1);
	return dVal;
}
*/

void CCharElementIEC::CalTestLines(UINT nTestLineMode)
{
// 	double dKGap = 360 / m_nTestPoints;
// 	double dErrorLen = GetErrorLength();
// 
// 	POS pos = GetHeadPosition();
// 	CCharElementTestLine *pTestLine = NULL;
// 	double dK = 0, dX = 0, dY = 0, dXg = 0, dYg = 0;
// 
// 	while (pos != NULL)
// 	{
// 		pTestLine = (CCharElementTestLine *)GetNext(pos);
// 		dK = pTestLine->m_fPos * dKGap;
// 		
// 		dXg = dErrorLen * cos(dK * _PI_D_180);
// 		dYg = dErrorLen * sin(dK * _PI_D_180);
// 
// 		pTestLine->m_fXset = m_fXCenter + m_fXRadius * cos(dK * _PI_D_180);
// 		pTestLine->m_fYset = m_fYCenter + m_fXRadius * sin(dK * _PI_D_180);
// 		pTestLine->m_fXb = pTestLine->m_fXset + dXg;
// 		pTestLine->m_fYb = pTestLine->m_fYset + dYg;
// 		pTestLine->m_fXe = pTestLine->m_fXset - dXg;
// 		pTestLine->m_fYe = pTestLine->m_fYset - dYg;
// 	}
}


double CCharElementIEC::CalInverse(double dVal)
{
	double dT = m_fTp * m_fK / (pow(dVal, m_fAlpha) - 1);
	return dT;
}
