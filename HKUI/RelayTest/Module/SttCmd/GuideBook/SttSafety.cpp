//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttSafety.cpp  CSttSafety


#include "stdafx.h"
#include "SttSafety.h"
#include "../SttMsg.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttSafety::CSttSafety()
{
	//初始化属性
	m_nManyDeviceTestMode = 0;
	m_pDatas = NULL;

	//初始化成员变量
}

CSttSafety::~CSttSafety()
{
}

BSTR CSttSafety::GetXmlElementKey()
{
	if (CSttCmdDefineXmlRWKeys::stt_Is_GuideBookUseItemKey(NULL))
	{
		return CSttCmdDefineXmlRWKeys::CSttItemBaseKey();
	}
	else
	{
		return CSttCmdDefineXmlRWKeys::CSttSafetyKey();
	}
}

long CSttSafety::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttItemBase::XmlReadOwn(oNode, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	xml_GetAttibuteValue(pXmlKeys->m_strSoundFileKey, oNode, m_strSoundFile);
	xml_GetAttibuteValue(pXmlKeys->m_strManyDeviceTestModeKey, oNode, m_nManyDeviceTestMode);
	return 0;
}

long CSttSafety::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttItemBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	if (CSttCmdDefineXmlRWKeys::IsOnlyGetItem())
	{
		return 0;
	}

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	xml_SetAttributeValue(pXmlKeys->m_strSoundFileKey, oElement, m_strSoundFile);
	xml_SetAttributeValue(pXmlKeys->m_strManyDeviceTestModeKey, oElement, m_nManyDeviceTestMode);
	return 0;
}

long CSttSafety::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CSttItemBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
		BinarySerializeCalLen(oBinaryBuffer, m_strSoundFile);
		BinarySerializeCalLen(oBinaryBuffer, m_nManyDeviceTestMode);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strType);
		BinarySerializeRead(oBinaryBuffer, m_strSoundFile);
		BinarySerializeRead(oBinaryBuffer, m_nManyDeviceTestMode);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strType);
		BinarySerializeWrite(oBinaryBuffer, m_strSoundFile);
		BinarySerializeWrite(oBinaryBuffer, m_nManyDeviceTestMode);
	}
	return 0;
}

void CSttSafety::InitAfterRead()
{
	CSttItemBase::InitAfterRead();

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	long nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		switch (p->GetClassID())
		{
		case DTMCLASSID_CSHORTDATAS:
			m_pDatas = (CShortDatas*)p;
			break;
		default:
			break;
		}
	}
}

BOOL CSttSafety::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CSttItemBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttSafety *p = (CSttSafety*)pObj;

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	if(m_strSoundFile != p->m_strSoundFile)
	{
		return FALSE;
	}

	if(m_nManyDeviceTestMode != p->m_nManyDeviceTestMode)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttSafety::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttItemBase::CopyOwn(pDest);

	CSttSafety *p = (CSttSafety*)pDest;

	p->m_strType = m_strType;
	p->m_strSoundFile = m_strSoundFile;
	p->m_nManyDeviceTestMode = m_nManyDeviceTestMode;
	return TRUE;
}

CBaseObject* CSttSafety::Clone()
{
	CSttSafety *p = new CSttSafety();
	Copy(p);
	return p;
}

CBaseObject* CSttSafety::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttSafety *p = new CSttSafety();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttSafety::CanPaste(UINT nClassID)
{
	if (nClassID == STTGBXMLCLASSID_CSTTCOMMCMD)
	{
		return TRUE;
	}
	else if (nClassID == DTMCLASSID_CSHORTDATAS)
	{
		return TRUE;
	}
	else if (nClassID == STTCMDCLASSID_CSTTMSG)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttSafety::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttCommCmdKey)
	{
		pNew = new CSttCommCmd();
	}
	else if (strClassID == pXmlKeys->m_strCShortDatasKey)
	{
		pNew = new CShortDatas();
	}
	else if (strClassID == pXmlKeys->m_strCSttMsgKey)
	{
		pNew = new CSttMsg();
	}
	else
	{
		return CSttItemBase::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
	}

	return pNew;
}

CExBaseObject* CSttSafety::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == STTGBXMLCLASSID_CSTTCOMMCMD)
	{
		pNew = new CSttCommCmd();
	}
	else if (nClassID == DTMCLASSID_CSHORTDATAS)
	{
		pNew = new CShortDatas();
	}
	else if (nClassID == STTCMDCLASSID_CSTTMSG)
	{
		pNew = new CSttMsg();
	}
	else
	{
		return CSttItemBase::CreateNewChild(nClassID);
	}

	return pNew;
}

CShortDatas* CSttSafety::GetDatas()
{
	if (m_pDatas != NULL)
	{
		return m_pDatas;
	}

	m_pDatas = new CShortDatas();
	AddNewChild(m_pDatas);
	return m_pDatas;
}

void CSttSafety::GetMsgs(CExBaseList *pListMsgs)
{
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != STTCMDCLASSID_CSTTMSG)
		{
			continue;
		}

		CSttMsg *pMsg = (CSttMsg *)pObj;
		pListMsgs->AddTail(pMsg);
	}
}

void CSttSafety::GetMsgs(CString &strMsgs)
{
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != STTCMDCLASSID_CSTTMSG)
		{
			continue;
		}

		CSttMsg *pMsg = (CSttMsg *)pObj;
		strMsgs += pMsg->m_strMsg;

		if (pos != NULL)
		{
			strMsgs += _T("\r\n");
		}
	}
}

void CSttSafety::AddNewMsg(const CString &strMsg)
{
	CSttMsg *pNewMsg = new CSttMsg();
	pNewMsg->m_strMsg = strMsg;
	AddNewChild(pNewMsg);
}

void CSttSafety::UpdateMsgs(const CString &strMsg)
{
	DeleteAllMsgs();
	AddNewMsg(strMsg);
}

void CSttSafety::DeleteAllMsgs()
{
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != STTCMDCLASSID_CSTTMSG)
		{
			continue;
		}

		Delete(pObj);
	}
}
