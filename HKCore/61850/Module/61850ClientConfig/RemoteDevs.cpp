//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RemoteDevs.cpp  CRemoteDevs


#include "stdafx.h"
#include "RemoteDevs.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRemoteDevs::CRemoteDevs()
{
	//初始化属性
	m_nIntgPd = 3000;
	m_nOptFlds_BR = 95;
	m_nOptFlds_RP = 231;
	m_nTrgOps_UI = 24;
	m_nUseEntryidUpdate = 0;
	m_nWriteCtrlType = DLT_WRITE_CTRL_TYPE_SWV;
	m_nCtrlTest = 0;
	m_nCtrlCheck = 0;
	m_nHasTimeAct = 0;

	//初始化成员变量
}

CRemoteDevs::~CRemoteDevs()
{
}

long CRemoteDevs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	C61850ClientCfgMngrXmlRWKeys *pXmlKeys = (C61850ClientCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIntg_PdKey, oNode, m_nIntgPd);
	xml_GetAttibuteValue(pXmlKeys->m_strOpt_Flds_BRKey, oNode, m_nOptFlds_BR);
	xml_GetAttibuteValue(pXmlKeys->m_strOpt_Flds_RPKey, oNode, m_nOptFlds_RP);
	xml_GetAttibuteValue(pXmlKeys->m_strTrg_Ops_UIKey, oNode, m_nTrgOps_UI);
	xml_GetAttibuteValue(pXmlKeys->m_strUse_Entryid_UpdateKey, oNode, m_nUseEntryidUpdate);
	xml_GetAttibuteValue(pXmlKeys->m_strWriteCtrlTypeKey, oNode, m_nWriteCtrlType);
	xml_GetAttibuteValue(pXmlKeys->m_strCtrlTestKey, oNode, m_nCtrlTest);
	xml_GetAttibuteValue(pXmlKeys->m_strCtrlCheckKey, oNode, m_nCtrlCheck);
	xml_GetAttibuteValue(pXmlKeys->m_strHasTimeActKey, oNode, m_nHasTimeAct);
	return 0;
}

long CRemoteDevs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	C61850ClientCfgMngrXmlRWKeys *pXmlKeys = (C61850ClientCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIntg_PdKey, oElement, m_nIntgPd);
	xml_SetAttributeValue(pXmlKeys->m_strOpt_Flds_BRKey, oElement, m_nOptFlds_BR);
	xml_SetAttributeValue(pXmlKeys->m_strOpt_Flds_RPKey, oElement, m_nOptFlds_RP);
	xml_SetAttributeValue(pXmlKeys->m_strTrg_Ops_UIKey, oElement, m_nTrgOps_UI);
	xml_SetAttributeValue(pXmlKeys->m_strUse_Entryid_UpdateKey, oElement, m_nUseEntryidUpdate);
	xml_SetAttributeValue(pXmlKeys->m_strWriteCtrlTypeKey, oElement, m_nWriteCtrlType);
	xml_SetAttributeValue(pXmlKeys->m_strCtrlTestKey, oElement, m_nCtrlTest);
	xml_SetAttributeValue(pXmlKeys->m_strCtrlCheckKey, oElement, m_nCtrlCheck);
	xml_SetAttributeValue(pXmlKeys->m_strHasTimeActKey, oElement, m_nHasTimeAct);
	return 0;
}

long CRemoteDevs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIntgPd);
		BinarySerializeCalLen(oBinaryBuffer, m_nOptFlds_BR);
		BinarySerializeCalLen(oBinaryBuffer, m_nOptFlds_RP);
		BinarySerializeCalLen(oBinaryBuffer, m_nTrgOps_UI);
		BinarySerializeCalLen(oBinaryBuffer, m_nUseEntryidUpdate);
		BinarySerializeCalLen(oBinaryBuffer, m_nWriteCtrlType);
		BinarySerializeCalLen(oBinaryBuffer, m_nCtrlTest);
		BinarySerializeCalLen(oBinaryBuffer, m_nCtrlCheck);
		BinarySerializeCalLen(oBinaryBuffer, m_nHasTimeAct);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIntgPd);
		BinarySerializeRead(oBinaryBuffer, m_nOptFlds_BR);
		BinarySerializeRead(oBinaryBuffer, m_nOptFlds_RP);
		BinarySerializeRead(oBinaryBuffer, m_nTrgOps_UI);
		BinarySerializeRead(oBinaryBuffer, m_nUseEntryidUpdate);
		BinarySerializeRead(oBinaryBuffer, m_nWriteCtrlType);
		BinarySerializeRead(oBinaryBuffer, m_nCtrlTest);
		BinarySerializeRead(oBinaryBuffer, m_nCtrlCheck);
		BinarySerializeRead(oBinaryBuffer, m_nHasTimeAct);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIntgPd);
		BinarySerializeWrite(oBinaryBuffer, m_nOptFlds_BR);
		BinarySerializeWrite(oBinaryBuffer, m_nOptFlds_RP);
		BinarySerializeWrite(oBinaryBuffer, m_nTrgOps_UI);
		BinarySerializeWrite(oBinaryBuffer, m_nUseEntryidUpdate);
		BinarySerializeWrite(oBinaryBuffer, m_nWriteCtrlType);
		BinarySerializeWrite(oBinaryBuffer, m_nCtrlTest);
		BinarySerializeWrite(oBinaryBuffer, m_nCtrlCheck);
		BinarySerializeWrite(oBinaryBuffer, m_nHasTimeAct);
	}

	return 0;
}

void CRemoteDevs::InitAfterRead()
{
}

BOOL CRemoteDevs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRemoteDevs *p = (CRemoteDevs*)pObj;

	if(m_nIntgPd != p->m_nIntgPd)
	{
		return FALSE;
	}

	if(m_nOptFlds_BR != p->m_nOptFlds_BR)
	{
		return FALSE;
	}

	if(m_nOptFlds_RP != p->m_nOptFlds_RP)
	{
		return FALSE;
	}

	if(m_nTrgOps_UI != p->m_nTrgOps_UI)
	{
		return FALSE;
	}

	if(m_nUseEntryidUpdate != p->m_nUseEntryidUpdate)
	{
		return FALSE;
	}

	if(m_nWriteCtrlType != p->m_nWriteCtrlType)
	{
		return FALSE;
	}

	if(m_nCtrlTest != p->m_nCtrlTest)
	{
		return FALSE;
	}

	if(m_nCtrlCheck != p->m_nCtrlCheck)
	{
		return FALSE;
	}

	if(m_nHasTimeAct != p->m_nHasTimeAct)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRemoteDevs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRemoteDevs *p = (CRemoteDevs*)pDest;

	p->m_nIntgPd = m_nIntgPd;
	p->m_nOptFlds_BR = m_nOptFlds_BR;
	p->m_nOptFlds_RP = m_nOptFlds_RP;
	p->m_nTrgOps_UI = m_nTrgOps_UI;
	p->m_nUseEntryidUpdate = m_nUseEntryidUpdate;
	p->m_nWriteCtrlType = m_nWriteCtrlType;
	p->m_nCtrlTest = m_nCtrlTest;
	p->m_nCtrlCheck = m_nCtrlCheck;
	p->m_nHasTimeAct = m_nHasTimeAct;
	return TRUE;
}

CBaseObject* CRemoteDevs::Clone()
{
	CRemoteDevs *p = new CRemoteDevs();
	Copy(p);
	return p;
}

CBaseObject* CRemoteDevs::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRemoteDevs *p = new CRemoteDevs();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CRemoteDevs::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CREMOTEDEV)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CRemoteDevs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	C61850ClientCfgMngrXmlRWKeys *pXmlKeys = (C61850ClientCfgMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRemoteDevKey)
	{
		pNew = new CRemoteDev();
	}

	return pNew;
}

CExBaseObject* CRemoteDevs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CREMOTEDEV)
	{
		pNew = new CRemoteDev();
	}

	return pNew;
}

#ifdef USE_61850CLient_STRCUT

ACSI_NODE* CRemoteDevs::FindAcsiNodeByID(const CString &strDeviceID)
{
	ACSI_NODE *pCurr = NULL;
	ACSI_NODE *pFind = NULL;
	char pszDeviceID[NAMESIZE];
	CString_to_char(strDeviceID, pszDeviceID);
	CRemoteDev *pCurRemote = NULL;
	POS pos = GetHeadPosition();

	while(pos)
	{
		pCurRemote = (CRemoteDev *)GetNext(pos);
		pCurr = pCurRemote->GetAcsiNode();

		if (strcmp(pCurr->devID, pszDeviceID) == 0)
		{
			pFind = pCurr;
			break;
		}
	}

	return pFind;
}

ACSI_NODE* CRemoteDevs::FindAcsiNode_UnConnect()
{
	ACSI_NODE *pCurr = NULL;
	ACSI_NODE *pFind = NULL;
	CRemoteDev *pCurRemote = NULL;
	POS pos = GetHeadPosition();

	while(pos)
	{
		pCurRemote = (CRemoteDev *)GetNext(pos);
		pCurr = pCurRemote->GetAcsiNode();

		if (strlen(pCurr->devID) == 0)
		{
			pFind = pCurr;
			break;
		}
	}

	return pFind;
}

#endif