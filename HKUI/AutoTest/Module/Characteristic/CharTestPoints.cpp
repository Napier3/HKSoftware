//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharTestPoints.cpp  CCharTestPoints


#include "stdafx.h"
#include "CharTestPoints.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharTestPoints::CCharTestPoints()
{
	//初始化属性
	m_strFrom = _T("BeginValue");
	m_strTo = _T("EndValue");
	m_strStep = _T("StepValue");

	m_dFrom = 0.0;
	m_dTo = 0.0;
	m_dStep = 0.0;
	//初始化成员变量
}

CCharTestPoints::~CCharTestPoints()
{
}

long CCharTestPoints::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strFromKey, oNode, m_strFrom);
	xml_GetAttibuteValue(pXmlKeys->m_strToKey, oNode, m_strTo);
	xml_GetAttibuteValue(pXmlKeys->m_strStepKey, oNode, m_strStep);

	return 0;
}

long CCharTestPoints::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strFromKey, oElement, m_strFrom);
	xml_SetAttributeValue(pXmlKeys->m_strToKey, oElement, m_strTo);
	xml_SetAttributeValue(pXmlKeys->m_strStepKey, oElement, m_strStep);

	return 0;
}

void CCharTestPoints::InitAfterRead()
{
	m_dFrom = CString_To_double(m_strFrom);
	m_dTo = CString_To_double(m_strTo);
	m_dStep = CString_To_double(m_strStep);
}

BOOL CCharTestPoints::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

    CCharTestPoints *p = (CCharTestPoints*)pObj;

	if(m_strFrom != p->m_strFrom)
	{
		return FALSE;
	}

	if(m_strTo != p->m_strTo)
	{
		return FALSE;
	}

	if(m_strStep != p->m_strStep)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCharTestPoints::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

    CCharTestPoints *p = (CCharTestPoints*)pDest;

	p->m_strFrom = m_strFrom;
	p->m_strTo = m_strTo;
	p->m_strStep = m_strStep;

	return TRUE;
}

CBaseObject* CCharTestPoints::Clone()
{
    CCharTestPoints *p = new CCharTestPoints();
	Copy(p);
	return p;
}

CBaseObject* CCharTestPoints::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CCharTestPoints *p = new CCharTestPoints();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CCharTestPoints::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strFrom);
		BinarySerializeCalLen(oBinaryBuffer, m_strTo);
		BinarySerializeCalLen(oBinaryBuffer, m_strStep);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strFrom);
		BinarySerializeRead(oBinaryBuffer, m_strTo);
		BinarySerializeRead(oBinaryBuffer, m_strStep);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strFrom);
		BinarySerializeWrite(oBinaryBuffer, m_strTo);
		BinarySerializeWrite(oBinaryBuffer, m_strStep);
	}

	return 0;
}
CCharTestPoint::CCharTestPoint()
{
	//初始化属性
	m_fX = 0;
	m_fY = 0;
	
	//初始化成员变量
	m_nZoneType = -1;
	m_nFaultType = -1;
	m_nTestState = CHAR_TEST_OBJECT_STATE_NORMAL;
	m_pDrawPointRef = NULL;
}

CCharTestPoint::~CCharTestPoint()
{
}

long CCharTestPoint::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strExprXKey, oNode, m_fX);
	xml_GetAttibuteValue(pXmlKeys->m_strExprYKey, oNode, m_fY);

	xml_GetAttibuteValue(pXmlKeys->m_strFaultTypeKey, oNode, m_nFaultType);
	xml_GetAttibuteValue(pXmlKeys->m_strZoneTypeKey, oNode, m_nZoneType);
	xml_GetAttibuteValue(pXmlKeys->m_strTestStateKey, oNode, m_nTestState);

	return 0;
}

long CCharTestPoint::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strExprXKey, oElement, m_fX);
	xml_SetAttributeValue(pXmlKeys->m_strExprYKey, oElement, m_fY);

	xml_SetAttributeValue(pXmlKeys->m_strFaultTypeKey, oElement, m_nFaultType);
	xml_SetAttributeValue(pXmlKeys->m_strZoneTypeKey, oElement, m_nZoneType);
	xml_SetAttributeValue(pXmlKeys->m_strTestStateKey, oElement, m_nTestState);

	return 0;
}

BOOL CCharTestPoint::IsEqualOwn(CBaseObject* pObj)
{
	if (this == pObj)
	{
		return TRUE;
	}

	CCharTestPoint *p = (CCharTestPoint*)pObj;

	if (m_fX != p->m_fX)
	{
	return FALSE;
	}

	if (m_fY != p->m_fY)
	{
	return FALSE;
	}

	if (m_nFaultType != p->m_nFaultType)
	{
	return FALSE;
	}
	if (m_nZoneType != p->m_nZoneType)
	{
		return FALSE;
	}
	if (m_nTestState != p->m_nTestState)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCharTestPoint::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	CCharTestPoint *p = (CCharTestPoint*)pDest;

	p->m_fX = m_fX;
	p->m_fX = m_fY;
	p->m_nFaultType = m_nFaultType;
	p->m_nZoneType = m_nZoneType;
	p->m_nTestState = m_nTestState;

	return TRUE;
}

CBaseObject* CCharTestPoint::Clone()
{
	CCharTestPoint *p = new CCharTestPoint();
	Copy(p);
	return p;
}

long CCharTestPoint::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_fX);
		BinarySerializeCalLen(oBinaryBuffer, m_fY);

		BinarySerializeCalLen(oBinaryBuffer, m_nFaultType);
		BinarySerializeCalLen(oBinaryBuffer, m_nZoneType);
		BinarySerializeCalLen(oBinaryBuffer, m_nTestState);
	}
	else if (oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_fX);
		BinarySerializeRead(oBinaryBuffer, m_fY);

		BinarySerializeRead(oBinaryBuffer, m_nFaultType);
		BinarySerializeRead(oBinaryBuffer, m_nZoneType);
		BinarySerializeRead(oBinaryBuffer, m_nTestState);
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_fX);
		BinarySerializeWrite(oBinaryBuffer, m_fY);

		BinarySerializeWrite(oBinaryBuffer, m_nFaultType);
		BinarySerializeWrite(oBinaryBuffer, m_nZoneType);
		BinarySerializeWrite(oBinaryBuffer, m_nTestState);
	}

	return 0;
}
void CCharTestPoint::SetTestPoint(CString strIDPath, float fX, float fY, int  nFaultType, int nTestState, int  nZoneType)
{//20240822 luozibing 设置测试点参数
	m_strID = strIDPath;
	m_nZoneType = nZoneType;
	m_nFaultType = nFaultType;
	//	if ((fabs(m_fX - fX)>0.0001f) || (fabs(m_fY - fY)>0.0001f))//测试项坐标改变
	{
		m_fX = fX;
		m_fY = fY;
	}
	//20240903 luozibing 传入nTestState为-1时表明不修改状态 选中状态不处理
	if (nTestState == -1 || nTestState == CHAR_TEST_OBJECT_STATE_SELECT)
	{
		return;
	}
		m_nTestState = nTestState;
}
long CCharTestPoint::GetXDrawElement(CXDrawList *pDrawList)
{
	CXDrawPoint *pXPoint = new CXDrawPoint();
	pXPoint->m_fX = m_fX;
	pXPoint->m_fY = m_fY;
	pXPoint->m_dwDrawStyle = 0;
	//根据当前测试状态更新当前测试点的颜色20241024
	if (CHAR_TEST_OBJECT_STATE_NORMAL == m_nTestState)//测试点初始状态
	{
	pXPoint->m_crForeColor = RGB(0, 0, 255);
	}
	else if (CHAR_TEST_OBJECT_STATE_ELIGIBLE == m_nTestState)//测试点合格状态
	{
		pXPoint->m_crForeColor = RGB(255, 0, 255);
	}
	else if (CHAR_TEST_OBJECT_STATE_INELIGIBLE == m_nTestState)//测试点不合格状态
	{
		pXPoint->m_crForeColor = RGB(255, 0, 0);
	}
	pDrawList->AddNewChild(pXPoint);
	pXPoint->m_pXDrawDataRef = this;
	m_pDrawPointRef = pXPoint;
	return 1;
}