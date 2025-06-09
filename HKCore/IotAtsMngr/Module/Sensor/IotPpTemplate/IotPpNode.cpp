//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IotPpNode.cpp  CIotPpNode


#include "stdafx.h"
#include "IotPpNode.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIotPpNode::CIotPpNode()
{
	//初始化属性
	GetLocalTime(&m_tmRunBegin);

	//初始化成员变量
	m_pIotPpAcks = NULL;
	m_pIotPpTimers = NULL;
}

CIotPpNode::~CIotPpNode()
{
}

long CIotPpNode::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strPkg_IdKey, oNode, m_strPkg_Id);
	return 0;
}

long CIotPpNode::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strPkg_IdKey, oElement, m_strPkg_Id);
	return 0;
}

long CIotPpNode::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strPkg_Id);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strPkg_Id);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strPkg_Id);
	}
	return 0;
}

void CIotPpNode::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == IOTCLASSID_CIOTPPACKS)
		{
			m_pIotPpAcks = (CIotPpAcks*)p;
		}
		else if (nClassID == IOTCLASSID_CIOTPPTIMERS)
		{
			m_pIotPpTimers = (CIotPpTimers*)p;
		}
	}

	if (m_pIotPpAcks == NULL)
	{
		m_pIotPpAcks = (CIotPpAcks*)AddNewChild(new CIotPpAcks());
	}

	if (m_pIotPpTimers == NULL)
	{
		m_pIotPpTimers = (CIotPpTimers*)AddNewChild(new CIotPpTimers());
	}

}

BOOL CIotPpNode::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIotPpNode *p = (CIotPpNode*)pObj;

	if(m_strPkg_Id != p->m_strPkg_Id)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIotPpNode::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIotPpNode *p = (CIotPpNode*)pDest;

	p->m_strPkg_Id = m_strPkg_Id;
	return TRUE;
}

CBaseObject* CIotPpNode::Clone()
{
	CIotPpNode *p = new CIotPpNode();
	Copy(p);
	return p;
}

CBaseObject* CIotPpNode::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIotPpNode *p = new CIotPpNode();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIotPpNode::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOTPPACKS)
	{
		return TRUE;
	}

	if (nClassID == IOTCLASSID_CIOTPPTIMERS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIotPpNode::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIotPpAcksKey)
	{
		pNew = new CIotPpAcks();
	}
	else if (strClassID == pXmlKeys->m_strCIotPpTimersKey)
	{
		pNew = new CIotPpTimers();
	}

	return pNew;
}

CExBaseObject* CIotPpNode::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOTPPACKS)
	{
		pNew = new CIotPpAcks();
	}
	else if (nClassID == IOTCLASSID_CIOTPPTIMERS)
	{
		pNew = new CIotPpTimers();
	}

	return pNew;
}

void CIotPpNode::BeginTimer(DWORD dwCurrTick)
{
	if (m_pIotPpTimers == NULL)
	{
		return;
	}

	POS pos = m_pIotPpTimers->GetHeadPosition();
	CIotPpTimer *pTimer = NULL;

	while(pos != NULL)
	{
		pTimer = (CIotPpTimer *)m_pIotPpTimers->GetNext(pos);

		pTimer->BeginTimer(dwCurrTick);
	}
}

void CIotPpNode::KillTimer()
{
	if (m_pIotPpTimers == NULL)
	{
		return;
	}

	POS pos = m_pIotPpTimers->GetHeadPosition();
	CIotPpTimer *pTimer = NULL;

	while(pos != NULL)
	{
		pTimer = (CIotPpTimer *)m_pIotPpTimers->GetNext(pos);

		pTimer->KillTimer();
	}
}

BOOL CIotPpNode::IsTimerOut(DWORD dwCurrTick,CIotPpNode **ppCurNode)
{
	if (m_pIotPpTimers == NULL)
	{
		return FALSE;
	}

	POS pos = m_pIotPpTimers->GetHeadPosition();
	CIotPpTimer *pTimer = NULL;

	while(pos != NULL)
	{
		pTimer = (CIotPpTimer *)m_pIotPpTimers->GetNext(pos);

		if (pTimer->IsTimerOut(dwCurrTick))
		{
			if (pTimer->m_strJump_To.IsEmpty())
			{//新建Node
				*ppCurNode = pTimer->GetIotPpNode();
			}
			else if (pTimer->m_strJump_To == PROCEDURE_END_NODE_ID)
			{
				*ppCurNode = NULL;
			}
			else
			{//根据id定位指定Node

			}

			return TRUE;
		}
	}

	return FALSE;
}

void CIotPpNode::UpdateTimers(CDvmDataset *pAttrDataset,CExBaseList *pInterface)
{	
	if (m_pIotPpAcks != NULL)
	{
		m_pIotPpAcks->UpdateTimers(pAttrDataset,pInterface);
	}
	if (m_pIotPpTimers != NULL)
	{
		m_pIotPpTimers->UpdateTimers(pAttrDataset,pInterface);
	}
}

CIotPpAck *CIotPpNode::FindPpAck(const CString &strPkgID)
{
	if (m_pIotPpAcks == NULL)
	{
		return NULL;
	}

	POS pos = m_pIotPpAcks->GetHeadPosition();
	CIotPpAck *p = NULL;

	while(pos != NULL)
	{
		p = (CIotPpAck *)m_pIotPpAcks->GetNext(pos);

		if (p->m_strPkg_Id == strPkgID)
		{
			return p;
		}
	}

	return NULL;
}
