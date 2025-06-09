//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpDeviceNode.cpp  CEpDeviceNode


#include "stdafx.h"
#include "EpDeviceNode.h"

CEpDeviceNode::CEpDeviceNode()
{
	//初始化属性

	//初始化成员变量
	m_pArrDatas = NULL;
	m_nArrDatas = 0;
}

CEpDeviceNode::~CEpDeviceNode()
{
}

long CEpDeviceNode::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CEpDeviceXmlRWKeys *pXmlKeys = (CEpDeviceXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpDeviceNode::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CEpDeviceXmlRWKeys *pXmlKeys = (CEpDeviceXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpDeviceNode::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CEpDeviceNode::InitAfterRead()
{
}

BOOL CEpDeviceNode::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEpDeviceNode *p = (CEpDeviceNode*)pObj;

	return TRUE;
}

BOOL CEpDeviceNode::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CEpDeviceNode *p = (CEpDeviceNode*)pDest;

	return TRUE;
}

CBaseObject* CEpDeviceNode::Clone()
{
	CEpDeviceNode *p = new CEpDeviceNode();
	Copy(p);
	return p;
}

BOOL CEpDeviceNode::CanPaste(UINT nClassID)
{
	if (nClassID == EPDCLASSID_CEPDEVICENODE)
	{
		return TRUE;
	}

	if (nClassID == EPDCLASSID_CEPDEVICEDATA)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEpDeviceNode::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpDeviceXmlRWKeys *pXmlKeys = (CEpDeviceXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEpDeviceNodeKey)
	{
		pNew = new CEpDeviceNode();
	}
	else if (strClassID == pXmlKeys->m_strCEpDeviceDataKey)
	{
		pNew = new CEpDeviceData();
	}

	return pNew;
}

CExBaseObject* CEpDeviceNode::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EPDCLASSID_CEPDEVICENODE)
	{
		pNew = new CEpDeviceNode();
	}
	else if (nClassID == EPDCLASSID_CEPDEVICEDATA)
	{
		pNew = new CEpDeviceData();
	}

	return pNew;
}

void CEpDeviceNode::InitArrDatas()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	long nIndex = 0;

	m_nArrDatas = GetCount();
	m_pArrDatas = new LPVOID[m_nArrDatas+1];

	while (pos != NULL)
	{
		p = GetNext(pos);
		m_pArrDatas[nIndex] = p;
		nIndex++;
	}
}

CEpDeviceData* CEpDeviceNode::operator[] (long nIndex)
{
	if (nIndex < 0 || nIndex >= m_nArrDatas)
	{
		return NULL;
	}

	return ((CEpDeviceData*)m_pArrDatas[nIndex]);
}


CEpDeviceData* CEpDeviceNode::GetData(long nIndex)
{
	if (nIndex < 0 || nIndex >= m_nArrDatas)
	{
		return NULL;
	}

	return ((CEpDeviceData*)m_pArrDatas[nIndex]);
}
