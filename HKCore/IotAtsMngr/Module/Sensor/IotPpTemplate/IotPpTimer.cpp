//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IotPpTimer.cpp  CIotPpTimer


#include "stdafx.h"
#include "IotPpTimer.h"
#include "IotPpNode.h"
#include "../../../../Module/DataMngr/DvmDataset.h"
#include "IotPpInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIotPpTimer::CIotPpTimer()
{
	//初始化属性
	m_nTimeLong = 0;
	m_dwTimerBegin = 0;
	m_bTimerBegin = FALSE;

	//初始化成员变量
	m_pIotPpNode = NULL;
}

CIotPpTimer::~CIotPpTimer()
{
}

long CIotPpTimer::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	xml_GetAttibuteValue(pXmlKeys->m_strJump_ToKey, oNode, m_strJump_To);
	xml_GetAttibuteValue(pXmlKeys->m_strTimeKey, oNode, m_strTime);
	return 0;
}

long CIotPpTimer::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	xml_SetAttributeValue(pXmlKeys->m_strJump_ToKey, oElement, m_strJump_To);
	xml_SetAttributeValue(pXmlKeys->m_strTimeKey, oElement, m_strTime);
	return 0;
}

long CIotPpTimer::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
		BinarySerializeCalLen(oBinaryBuffer, m_strJump_To);
		BinarySerializeCalLen(oBinaryBuffer, m_strTime);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strType);
		BinarySerializeRead(oBinaryBuffer, m_strJump_To);
		BinarySerializeRead(oBinaryBuffer, m_strTime);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strType);
		BinarySerializeWrite(oBinaryBuffer, m_strJump_To);
		BinarySerializeWrite(oBinaryBuffer, m_strTime);
	}
	return 0;
}

void CIotPpTimer::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == IOTCLASSID_CIOTPPNODE)
		{
			m_pIotPpNode = (CIotPpNode*)p;
		}
	}
}

BOOL CIotPpTimer::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIotPpTimer *p = (CIotPpTimer*)pObj;

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	if(m_strJump_To != p->m_strJump_To)
	{
		return FALSE;
	}

	if(m_strTime != p->m_strTime)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIotPpTimer::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIotPpTimer *p = (CIotPpTimer*)pDest;

	p->m_strType = m_strType;
	p->m_strJump_To = m_strJump_To;
	p->m_strTime = m_strTime;
	return TRUE;
}

CBaseObject* CIotPpTimer::Clone()
{
	CIotPpTimer *p = new CIotPpTimer();
	Copy(p);
	return p;
}

CBaseObject* CIotPpTimer::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIotPpTimer *p = new CIotPpTimer();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIotPpTimer::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOTPPNODE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIotPpTimer::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIotPpNodeKey)
	{
		pNew = new CIotPpNode();
	}

	return pNew;
}

CExBaseObject* CIotPpTimer::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOTPPNODE)
	{
		pNew = new CIotPpNode();
	}

	return pNew;
}

void CIotPpTimer::BeginTimer(DWORD dwCurrTick)
{
	m_bTimerBegin = TRUE;
	m_dwTimerBegin = dwCurrTick;
}

void CIotPpTimer::ResetTimer(DWORD dwCurrTick)
{
	m_dwTimerBegin = dwCurrTick;
}

void CIotPpTimer::KillTimer()
{
	m_bTimerBegin = FALSE;
	m_dwTimerBegin = 0;
}

BOOL CIotPpTimer::IsTimerOut(DWORD dwCurrTick)
{
	if(!m_bTimerBegin)
	{//未启动定时器
		return FALSE;
	}

	long nTimer = dwCurrTick - m_dwTimerBegin;

	if (nTimer > m_nTimeLong)
	{
		return TRUE;
	}
	else
	{
		if (nTimer < 0)
		{
			m_dwTimerBegin = 0;
			return ((long)dwCurrTick > m_nTimeLong);
		}
		else
		{
			return FALSE;
		}
	}
}

void CIotPpTimer::UpdateTimers(CDvmDataset *pAttrDataset,CExBaseList *pInterface)
{
	m_nTimeLong = 5000;		//默认5s

	if (IsStringNum(m_strTime))
	{//m_strTime是数字
		m_nTimeLong = CString_To_long(m_strTime);
	}
	else
	{//m_strTime:是属性ID
		CDvmData *pData = (CDvmData *)pAttrDataset->FindByID(m_strTime);
		if (pData != NULL)
		{
			m_nTimeLong = CString_To_long(pData->m_strValue);
		}
		else if (pInterface != NULL)
		{
			((CIotPpInterface *)pInterface)->GetValueByID(m_strTime,m_nTimeLong);
		}
	}

	POS pos = GetHeadPosition();
	CIotPpNode *pNode = NULL;

	while(pos != NULL)
	{
		pNode = (CIotPpNode *)GetNext(pos);

		pNode->UpdateTimers(pAttrDataset,pInterface);
	}
}



//////////////////////////////////////

BOOL IsStringNum(const CString &str)
{
	CString strExceptNum = str;
	strExceptNum.TrimLeft(_T("+-0123456789."));

	return strExceptNum.IsEmpty();
}