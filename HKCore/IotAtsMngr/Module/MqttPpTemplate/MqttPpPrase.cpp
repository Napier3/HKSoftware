//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MqttPpPrase.cpp  CMqttPpPrase


#include "stdafx.h"
#include "MqttPpPrase.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMqttPpPrase::CMqttPpPrase()
{
	//初始化属性

	//初始化成员变量
	m_ppkg = NULL;
}

CMqttPpPrase::~CMqttPpPrase()
{
}

long CMqttPpPrase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDvmDataset::XmlReadOwn(oNode, pXmlRWKeys);
	CMqttPpCfgXmlRWKeys *pXmlKeys = (CMqttPpCfgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDs_OptrKey, oNode, m_strDs_Optr);
	return 0;
}

long CMqttPpPrase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDvmDataset::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CMqttPpCfgXmlRWKeys *pXmlKeys = (CMqttPpCfgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDs_OptrKey, oElement, m_strDs_Optr);
	return 0;
}

long CMqttPpPrase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CDvmDataset::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDs_Optr);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDs_Optr);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDs_Optr);
	}
	return 0;
}

void CMqttPpPrase::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == MQTTCLASSID_CMQTTPPPKG)
		{
			m_ppkg = (CMqttPpPkg*)p;
		}
	}

	if (m_ppkg == NULL)
	{
		m_ppkg = (CMqttPpPkg*)AddNewChild(new CMqttPpPkg());
	}

}

BOOL CMqttPpPrase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CDvmDataset::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CMqttPpPrase *p = (CMqttPpPrase*)pObj;

	if(m_strDs_Optr != p->m_strDs_Optr)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CMqttPpPrase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDvmDataset::CopyOwn(pDest);

	CMqttPpPrase *p = (CMqttPpPrase*)pDest;

	p->m_strDs_Optr = m_strDs_Optr;
	return TRUE;
}

CBaseObject* CMqttPpPrase::Clone()
{
	CMqttPpPrase *p = new CMqttPpPrase();
	Copy(p);
	return p;
}

CBaseObject* CMqttPpPrase::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CMqttPpPrase *p = new CMqttPpPrase();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CMqttPpPrase::CanPaste(UINT nClassID)
{
	if (nClassID == MQTTCLASSID_CMQTTPPPKG)
	{
		return TRUE;
	}

	if (nClassID == DVMCLASSID_CDVMDATA)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CMqttPpPrase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMqttPpCfgXmlRWKeys *pXmlKeys = (CMqttPpCfgXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCMqttPpPkgKey)
	{
		pNew = new CMqttPpPkg();
	}
	else if (strClassID == pXmlKeys->m_strCDvmDataKey)
	{
		pNew = new CDvmData();
	}

	return pNew;
}

CExBaseObject* CMqttPpPrase::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MQTTCLASSID_CMQTTPPPKG)
	{
		pNew = new CMqttPpPkg();
	}
	else if (nClassID == DVMCLASSID_CDVMDATA)
	{
		pNew = new CDvmData();
	}

	return pNew;
}

void CMqttPpPrase::UpdateParaValue(CDvmDataset *pSrcDataset)
{
	POS pos = GetHeadPosition();
	CDvmData *pData = NULL;
	CDvmData *pFind = NULL;

	while(pos != NULL)
	{
		pData = (CDvmData *)GetNext(pos);

		if (pData->GetClassID() != DVMCLASSID_CDVMDATA)
		{
			continue;
		}

		pFind = (CDvmData *)pSrcDataset->FindByID(pData->m_strID);
		if (pFind == NULL)
		{
			continue;
		}

		pData->m_strValue = pFind->m_strValue;
	}
}

CString CMqttPpPrase::GetDsID()
{
	if (m_ppkg == NULL)
	{
		return _T("");
	}

	return m_ppkg->m_strDs;
}