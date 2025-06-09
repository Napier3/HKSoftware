//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MqttPpTemplate.cpp  CMqttPpTemplate


#include "stdafx.h"
#include "MqttPpTemplate.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMqttPpTemplate::CMqttPpTemplate()
{
	//初始化属性

	//初始化成员变量
	m_pPpPrases = NULL;
	m_pPpproduces = NULL;
	m_pProcedures = NULL;
}

CMqttPpTemplate::~CMqttPpTemplate()
{
}

long CMqttPpTemplate::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMqttPpCfgXmlRWKeys *pXmlKeys = (CMqttPpCfgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDvm_FileKey, oNode, m_strDvm_File);
	return 0;
}

long CMqttPpTemplate::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMqttPpCfgXmlRWKeys *pXmlKeys = (CMqttPpCfgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDvm_FileKey, oElement, m_strDvm_File);
	return 0;
}

long CMqttPpTemplate::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDvm_File);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDvm_File);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDvm_File);
	}
	return 0;
}

void CMqttPpTemplate::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == MQTTCLASSID_CMQTTPPPRASES)
		{
			m_pPpPrases = (CMqttPpPrases*)p;
		}
		else if (nClassID == MQTTCLASSID_CMQTTPPPRODUCES)
		{
			m_pPpproduces = (CMqttPpProduces*)p;
		}
		else if (nClassID == MQTTCLASSID_CMQTTPPPROCEDURES)
		{
			m_pProcedures = (CMqttPpProcedures*)p;
		}
	}

	if (m_pPpPrases == NULL)
	{
		m_pPpPrases = (CMqttPpPrases*)AddNewChild(new CMqttPpPrases());
	}

	if (m_pPpproduces == NULL)
	{
		m_pPpproduces = (CMqttPpProduces*)AddNewChild(new CMqttPpProduces());
	}

	if (m_pProcedures == NULL)
	{
		m_pProcedures = (CMqttPpProcedures*)AddNewChild(new CMqttPpProcedures());
	}

}

BOOL CMqttPpTemplate::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CMqttPpTemplate *p = (CMqttPpTemplate*)pObj;

	if(m_strDvm_File != p->m_strDvm_File)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CMqttPpTemplate::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CMqttPpTemplate *p = (CMqttPpTemplate*)pDest;

	p->m_strDvm_File = m_strDvm_File;
	return TRUE;
}

CBaseObject* CMqttPpTemplate::Clone()
{
	CMqttPpTemplate *p = new CMqttPpTemplate();
	Copy(p);
	return p;
}

CBaseObject* CMqttPpTemplate::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CMqttPpTemplate *p = new CMqttPpTemplate();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CMqttPpTemplate::CanPaste(UINT nClassID)
{
	if (nClassID == MQTTCLASSID_CMQTTPPPRODUCES)
	{
		return TRUE;
	}

	if (nClassID == MQTTCLASSID_CMQTTPPPRASES)
	{
		return TRUE;
	}

	if (nClassID == MQTTCLASSID_CMQTTPPPROCEDURES)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CMqttPpTemplate::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMqttPpCfgXmlRWKeys *pXmlKeys = (CMqttPpCfgXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCMqttPpProducesKey)
	{
		pNew = new CMqttPpProduces();
	}
	else if (strClassID == pXmlKeys->m_strCMqttPpPrasesKey)
	{
		pNew = new CMqttPpPrases();
	}
	else if (strClassID == pXmlKeys->m_strCMqttPpProceduresKey)
	{
		pNew = new CMqttPpProcedures();
	}

	return pNew;
}

CExBaseObject* CMqttPpTemplate::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MQTTCLASSID_CMQTTPPPRODUCES)
	{
		pNew = new CMqttPpProduces();
	}
	else if (nClassID == MQTTCLASSID_CMQTTPPPRASES)
	{
		pNew = new CMqttPpPrases();
	}
	else if (nClassID == MQTTCLASSID_CMQTTPPPROCEDURES)
	{
		pNew = new CMqttPpProcedures();
	}

	return pNew;
}

CMqttPpProcedure *CMqttPpTemplate::FindProcedure(const CString &strProcedureID)
{
	if (m_pProcedures == NULL)
	{
		return NULL;
	}

	return (CMqttPpProcedure *)m_pProcedures->FindByID(strProcedureID);
}

CMqttPpProduce *CMqttPpTemplate::FindProduce(const CString &strID)
{
	if(m_pPpproduces == NULL)
	{
		return NULL;
	}

	return (CMqttPpProduce *)m_pPpproduces->FindByID(strID);
}

CMqttPpPrase *CMqttPpTemplate::FindPrase(int nPkgType,int nCtrlType,int nRequestSetFlag)
{
	if(m_pPpPrases == NULL)
	{
		return NULL;
	}

	POS pos = m_pPpPrases->GetHeadPosition();
	CMqttPpPrase *p = NULL;
	CMqttPpPkg *pPpPkg = NULL;

	while(pos != NULL)
	{
		p = (CMqttPpPrase *)m_pPpPrases->GetNext(pos);

		pPpPkg = p->Getpkg();

		if (pPpPkg->IsMatchPkg(nPkgType,nCtrlType,nRequestSetFlag))
		{
			return p;
		}
	}

	return NULL;
}

CString CMqttPpTemplate::FindReadAinDsID()
{
	if(m_pPpPrases == NULL)
	{
		return _T("");
	}

	POS pos = m_pPpPrases->GetHeadPosition();
	CMqttPpPrase *p = NULL;
	CMqttPpPkg *pPpPkg = NULL;

	while(pos != NULL)
	{
		p = (CMqttPpPrase *)m_pPpPrases->GetNext(pos);

		pPpPkg = p->Getpkg();

		if (pPpPkg->IsReadAinPkg())
		{
			return pPpPkg->m_strDs;
		}
	}

	return _T("");
}