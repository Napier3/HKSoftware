//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIWndDateTimeCtrl.cpp  CUIWndDateTimeCtrl


#include "stdafx.h"
#include "UIWndDateTimeCtrl.h"

CUIWndDateTimeCtrl::CUIWndDateTimeCtrl()
{
	//初始化属性
	m_nUseCurTime = 0;
	m_nYear = 0;
	m_nDay = 0;
	m_nHour = 0;
	m_nMinute = 0;
	m_nSecond = 0;

	//初始化成员变量
}

CUIWndDateTimeCtrl::~CUIWndDateTimeCtrl()
{
}

long CUIWndDateTimeCtrl::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowBase::XmlReadOwn(oNode, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strFormartKey, oNode, m_strFormart);
	xml_GetAttibuteValue(pXmlKeys->m_strUseCurTimeKey, oNode, m_nUseCurTime);
	xml_GetAttibuteValue(pXmlKeys->m_strYearKey, oNode, m_nYear);
	xml_GetAttibuteValue(pXmlKeys->m_strDayKey, oNode, m_nDay);
	xml_GetAttibuteValue(pXmlKeys->m_strHourKey, oNode, m_nHour);
	xml_GetAttibuteValue(pXmlKeys->m_strMinuteKey, oNode, m_nMinute);
	xml_GetAttibuteValue(pXmlKeys->m_strSecondKey, oNode, m_nSecond);
	return 0;
}

long CUIWndDateTimeCtrl::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strFormartKey, oElement, m_strFormart);
	xml_SetAttributeValue(pXmlKeys->m_strUseCurTimeKey, oElement, m_nUseCurTime);
	xml_SetAttributeValue(pXmlKeys->m_strYearKey, oElement, m_nYear);
	xml_SetAttributeValue(pXmlKeys->m_strDayKey, oElement, m_nDay);
	xml_SetAttributeValue(pXmlKeys->m_strHourKey, oElement, m_nHour);
	xml_SetAttributeValue(pXmlKeys->m_strMinuteKey, oElement, m_nMinute);
	xml_SetAttributeValue(pXmlKeys->m_strSecondKey, oElement, m_nSecond);
	return 0;
}

long CUIWndDateTimeCtrl::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CUIWindowBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strFormart);
		BinarySerializeCalLen(oBinaryBuffer, m_nUseCurTime);
		BinarySerializeCalLen(oBinaryBuffer, m_nYear);
		BinarySerializeCalLen(oBinaryBuffer, m_nDay);
		BinarySerializeCalLen(oBinaryBuffer, m_nHour);
		BinarySerializeCalLen(oBinaryBuffer, m_nMinute);
		BinarySerializeCalLen(oBinaryBuffer, m_nSecond);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strFormart);
		BinarySerializeRead(oBinaryBuffer, m_nUseCurTime);
		BinarySerializeRead(oBinaryBuffer, m_nYear);
		BinarySerializeRead(oBinaryBuffer, m_nDay);
		BinarySerializeRead(oBinaryBuffer, m_nHour);
		BinarySerializeRead(oBinaryBuffer, m_nMinute);
		BinarySerializeRead(oBinaryBuffer, m_nSecond);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strFormart);
		BinarySerializeWrite(oBinaryBuffer, m_nUseCurTime);
		BinarySerializeWrite(oBinaryBuffer, m_nYear);
		BinarySerializeWrite(oBinaryBuffer, m_nDay);
		BinarySerializeWrite(oBinaryBuffer, m_nHour);
		BinarySerializeWrite(oBinaryBuffer, m_nMinute);
		BinarySerializeWrite(oBinaryBuffer, m_nSecond);
	}
	return 0;
}

void CUIWndDateTimeCtrl::InitAfterRead()
{
	CUIWindowBase::InitAfterRead();
}

BOOL CUIWndDateTimeCtrl::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CUIWindowBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CUIWndDateTimeCtrl *p = (CUIWndDateTimeCtrl*)pObj;

	if(m_strFormart != p->m_strFormart)
	{
		return FALSE;
	}

	if(m_nUseCurTime != p->m_nUseCurTime)
	{
		return FALSE;
	}

	if(m_nYear != p->m_nYear)
	{
		return FALSE;
	}

	if(m_nDay != p->m_nDay)
	{
		return FALSE;
	}

	if(m_nHour != p->m_nHour)
	{
		return FALSE;
	}

	if(m_nMinute != p->m_nMinute)
	{
		return FALSE;
	}

	if(m_nSecond != p->m_nSecond)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CUIWndDateTimeCtrl::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUIWindowBase::CopyOwn(pDest);

	CUIWndDateTimeCtrl *p = (CUIWndDateTimeCtrl*)pDest;

	p->m_strFormart = m_strFormart;
	p->m_nUseCurTime = m_nUseCurTime;
	p->m_nYear = m_nYear;
	p->m_nDay = m_nDay;
	p->m_nHour = m_nHour;
	p->m_nMinute = m_nMinute;
	p->m_nSecond = m_nSecond;
	return TRUE;
}

CBaseObject* CUIWndDateTimeCtrl::Clone()
{
	CUIWndDateTimeCtrl *p = new CUIWndDateTimeCtrl();
	Copy(p);
	return p;
}

BOOL CUIWndDateTimeCtrl::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CUIWndDateTimeCtrl::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CUIWndDateTimeCtrl::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
